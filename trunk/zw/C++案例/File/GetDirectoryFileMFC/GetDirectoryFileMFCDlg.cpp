// GetDirectoryFileMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetDirectoryFileMFC.h"
#include "GetDirectoryFileMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetDirectoryFileMFCDlg dialog

CGetDirectoryFileMFCDlg::CGetDirectoryFileMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetDirectoryFileMFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetDirectoryFileMFCDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetDirectoryFileMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetDirectoryFileMFCDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetDirectoryFileMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CGetDirectoryFileMFCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetDirectoryFileMFCDlg message handlers

BOOL CGetDirectoryFileMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_list.InsertColumn(0,"文件名",LVCFMT_CENTER,200);
	m_list.InsertColumn(1,"大小",LVCFMT_CENTER,200);
	CString strfileName;
	CString strPath="files\\*.*";
	strfileName=GetFiles(strfileName,strPath);
	//MessageBox(strfileName);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetDirectoryFileMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetDirectoryFileMFCDlg::OnPaint() 
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetDirectoryFileMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/******
注意:CFileFind类各个成员调用的顺序
1、创建CFileFind类的对象
2、执行FindFile()函数
3、执行FindNextFile()函数
4、调用获取文件属性，或者判断函数
*******/
CString CGetDirectoryFileMFCDlg::GetFiles(CString strFileName,CString strPath)
{
	//CString strFileName;
	CFileFind finder;
	BOOL bWorking=FALSE;
	bWorking=finder.FindFile(strPath);
	//bWorking=finder.FindFile("files\\*.*");
	CString strLen;
	int iItemCnt=0;
	while(bWorking)
	{
		bWorking=finder.FindNextFile();
		if (!finder.IsDirectory())
		{
			m_list.InsertItem(iItemCnt,finder.GetFileName());
			itoa(finder.GetLength(),strLen.GetBuffer(32),10);
			strLen.ReleaseBuffer();
			m_list.SetItemText(iItemCnt,1,strLen);
			iItemCnt++;
			strFileName+=finder.GetFileName()+"\r\n";
		}
		else
		{
			if (!finder.IsDots())
			{
				//如果是目录，则递归调用该函数。
				strFileName+=GetFiles(strFileName,finder.GetRoot()+"\\"+finder.GetFileTitle()+"\\*.*");
			}
		}
	}
	finder.Close();
	return strFileName;
}
