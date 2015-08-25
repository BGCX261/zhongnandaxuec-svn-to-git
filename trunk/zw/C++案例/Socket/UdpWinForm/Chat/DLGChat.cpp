// DLGChat.cpp : implementation file
//

#include "stdafx.h"
#include "Chat.h"
#include "DLGChat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGChat dialog


CDLGChat::CDLGChat(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGChat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGChat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDLGChat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGChat)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGChat, CDialog)
	//{{AFX_MSG_MAP(CDLGChat)
	ON_WM_CREATE()
	ON_WM_CANCELMODE()
	ON_MESSAGE(WM_RECVDATA,onRecvData)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGChat message handlers

BOOL CDLGChat::InitSocket()
{
	m_socket=socket(AF_INET,SOCK_DGRAM,0);
	if (INVALID_SOCKET==m_socket)
	{
		AfxMessageBox("创建套接字失败!");
		return FALSE;
	}
	SOCKADDR_IN addrScok;
	addrScok.sin_family=AF_INET;
	addrScok.sin_port=htons(6000);
	addrScok.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	int retval;
	retval=bind(m_socket,(SOCKADDR*)&addrScok,sizeof(SOCKADDR));
	if (SOCKET_ERROR==retval)
	{
		closesocket(m_socket);
		MessageBox("绑定失败");
		return FALSE;
	}
	return TRUE;
}

int CDLGChat::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CDLGChat::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}


BOOL CDLGChat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitSocket();
	RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->sock=m_socket;
	pRecvParam->hwnd=m_hWnd;
	HANDLE hthread=CreateThread(NULL,0,RecvProc,(LPVOID)pRecvParam,0,NULL);
	CloseHandle(hthread);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD WINAPI CDLGChat::RecvProc(LPVOID lpParameter)
{
	RECVPARAM *para=(RECVPARAM*)lpParameter;
	SOCKET sock=para->sock;
	HWND hwnd=para->hwnd;
	SOCKADDR_IN addrFrom;
	int len=sizeof(SOCKADDR);
	char recvBuf[200];
	char tempBuf[300];
	int retval;
	while (1)
	{
		retval=recvfrom(sock,recvBuf,200,0,(SOCKADDR*)&addrFrom,&len);
		if (SOCKET_ERROR==retval)
		{
			break;
		}
		else
		{
			sprintf(tempBuf,"%s 说: %s",inet_ntoa(addrFrom.sin_addr),recvBuf);
			//SetDlgItemText(IDC_EDIT_RECV,recvBuf);
			
			::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)tempBuf);
		}
	}
	return 0;
}

void CDLGChat::onRecvData(WPARAM wParam,LPARAM lParam)
{
	CString str=(char*)lParam;
	CString strtemp;
	GetDlgItemText(IDC_EDIT_RECV,strtemp);
	strtemp+="\r\n";
	strtemp+=str;
//	str+="\r\n";
//	str+=strtemp;
	SetDlgItemText(IDC_EDIT_RECV,strtemp);
}

void CDLGChat::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	DWORD dwIp;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDR_SEND))->GetAddress(dwIp);
	SOCKADDR_IN addrTo;
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6000);
	addrTo.sin_addr.S_un.S_addr=htonl(dwIp);

	CString strSend;
	GetDlgItemText(IDC_EDIT_SEND,strSend);
	sendto(m_socket,strSend,strSend.GetLength()+1,0,(SOCKADDR*)&addrTo,sizeof(SOCKADDR));
	SetDlgItemText(IDC_EDIT_SEND,"");
	
}

void CDLGChat::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hicon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
