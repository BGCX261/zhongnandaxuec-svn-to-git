// XMLReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMLRead.h"
#include "XMLReadDlg.h"
#include "tinyxml.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
bool fav=false;
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
// CXMLReadDlg dialog
struct LDATA 
{
	int subitmindex; //表头的列
	CListCtrl * plist;//listCtrl的指针
};

CXMLReadDlg::CXMLReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXMLReadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMLReadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXMLReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMLReadDlg)
	DDX_Control(pDX, IDC_LIST_SHW, m_listshow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXMLReadDlg, CDialog)
	//{{AFX_MSG_MAP(CXMLReadDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_SHW, OnColumnclickListShw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMLReadDlg message handlers

BOOL CXMLReadDlg::OnInitDialog()
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
		m_listshow.InsertColumn(0,"ID",LVCFMT_CENTER,50);
	m_listshow.InsertColumn(0,"姓名",LVCFMT_CENTER,100);
	m_listshow.InsertColumn(1,"年龄",LVCFMT_CENTER,200);
	m_listshow.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
	// TODO: Add extra initialization here
	TiXmlDocument * myDocument=new TiXmlDocument("XMPConfig.xml");
	bool bReult;
	 bReult=myDocument->LoadFile();
	 if (bReult)
	 {
		 TiXmlElement *RootElement=myDocument->RootElement();//根节点 Persons
		 TRACE0(RootElement->Value());
		 TiXmlElement *FirstPerson=RootElement->FirstChildElement();//Person
		 TiXmlElement *NameElement;
         TiXmlElement *AgeElement;
         int item=0;
		 while(FirstPerson)
		 {
			 NameElement=FirstPerson->FirstChildElement();//获取Person元素的Name属性
		     AgeElement=NameElement->NextSiblingElement();//获取Person元素的Age属性

			 m_listshow.InsertItem(item,FirstPerson->FirstAttribute()->Value());
			 m_listshow.SetItemText(item,1,NameElement->FirstChild()->Value());

			 TRACE0(NameElement->FirstChild()->Value());

	         m_listshow.SetItemText(item,2,AgeElement->FirstChild()->Value());
			 FirstPerson=FirstPerson->NextSiblingElement();
		 }
	
	 }
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXMLReadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXMLReadDlg::OnPaint() 
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
HCURSOR CXMLReadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXMLReadDlg::OnColumnclickListShw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
    for (int i=0;i<m_listshow.GetItemCount();i++)
    {
		m_listshow.SetItemData(i,i);
    }
	LDATA data;
	data.subitmindex=pNMListView->iSubItem;
	data.plist=&m_listshow;
	fav=!fav;
	m_listshow.SortItems(lictComparePro,(DWORD)&data);
	
	*pResult = 0;
}

int CALLBACK CXMLReadDlg::lictComparePro(LPARAM lparm1,LPARAM lparm2,LPARAM lparamsort)
{
    LDATA * pdata=(LDATA*)lparamsort;
	int colomindex=pdata->subitmindex;
	switch (colomindex)
	{
	case 0:
		{ 
			CListCtrl * plistctrl=(CListCtrl*)pdata->plist;
			CString strItem1=plistctrl->GetItemText(lparm1,0);
			CString strItem2=plistctrl->GetItemText(lparm2,0);
			LPCTSTR s1=(LPCTSTR)strItem1;
			LPCTSTR s2=(LPCTSTR)strItem2;
			int n1=atoi(s1);
			int n2=atoi(s2);
			if (fav)
			{
				if (n1>n2)
				{
					return -1;
				}else
					return 1;
			}else
			{
				if (n1>n2)
				{
					return 1;
				}else
					return -1;
			}
			
		}
		break;
	case 1:
		
		{
			CString strItem1=((CListCtrl*)pdata->plist)->GetItemText(lparm1,2);
			CString strItem2=((CListCtrl*)pdata->plist)->GetItemText(lparm2,2);
			if (fav)
			{
				
				return _tcscmp(strItem2.GetBuffer(MAX_PATH),strItem1.GetBuffer(MAX_PATH));
			}
			else
			{
				return _tcscmp(strItem1.GetBuffer(MAX_PATH),strItem2.GetBuffer(MAX_PATH));
				
			}
			
		}
		break;
	case 2:
		{
			CString strItem1=((CListCtrl*)pdata->plist)->GetItemText(lparm1,3);
			CString strItem2=((CListCtrl*)pdata->plist)->GetItemText(lparm2,3);
			if (fav)
			{
				
				return _tcscmp(strItem2.GetBuffer(MAX_PATH),strItem1.GetBuffer(MAX_PATH));
			}
			else
			{
				return _tcscmp(strItem1.GetBuffer(MAX_PATH),strItem2.GetBuffer(MAX_PATH));
			}
		}
		break;
	default:
		return 0;
	}
}
