// ListTESTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListTEST.h"
#include "ListTESTDlg.h"
#include "AddStudenInf.h"
#include "ModifStudentInfo.h"

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
// CListTESTDlg dialog

CListTESTDlg::CListTESTDlg(CWnd* pParent /*=NULL*/)
: CDialog(CListTESTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListTESTDlg)
	m_serchstr = _T("");
	m_ckall = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListTESTDlg)
	DDX_Control(pDX, IDC_COMBO1, m_serchComb);
	DDX_Control(pDX, IDC_LIST1, m_ShowDList);
	DDX_Text(pDX, IDC_EDIT1, m_serchstr);
	DDX_Check(pDX, IDC_CHALL, m_ckall);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListTESTDlg, CDialog)
//{{AFX_MSG_MAP(CListTESTDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
ON_BN_CLICKED(IDC_BTSERCH, OnBtserch)
ON_BN_CLICKED(IDC_CHALL, OnChall)
ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_COMMAND(IDCL_MENU_MODIF, OnMenuModif)
	ON_COMMAND(IDCL_MENU_DELET, OnMenuDelet)
	ON_BN_CLICKED(IDC_BUT_ADDDL, OnButAdddl)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_COMMAND(IDM_ADD_STUIF, OnAddStuif)
	ON_BN_CLICKED(IDC_BT_CLEARALL, OnBtClearall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListTESTDlg message handlers

BOOL CListTESTDlg::OnInitDialog()
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
	m_serchComb.InsertString(0,"学号");
    m_serchComb.InsertString(1,"性别");
	m_serchComb.InsertString(2,"姓名");
	m_serchComb.InsertString(3,"入学日期");
	m_serchComb.InsertString(4,"身份证号码");
	m_serchComb.InsertString(5,"出生地");
	
	
	m_serchComb.SetCurSel(0);
	
	
	m_ShowDList.InsertColumn(0,"学号",LVCFMT_CENTER,90);
	m_ShowDList.InsertColumn(1,"姓名",LVCFMT_CENTER,150);
	m_ShowDList.InsertColumn(2,"性别",LVCFMT_CENTER,50);
	m_ShowDList.InsertColumn(3,"入学日期",LVCFMT_CENTER,100);
	m_ShowDList.InsertColumn(4,"生日",LVCFMT_CENTER,100);
	m_ShowDList.InsertColumn(5,"身份证号码",LVCFMT_CENTER,250);
	m_ShowDList.InsertColumn(6,"家庭地址",LVCFMT_LEFT,300);
    m_ShowDList.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	
	
    m_serchComb.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListTESTDlg::OnPaint() 
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
HCURSOR CListTESTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CListTESTDlg::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
    for (int i=0;i<m_ShowDList.GetItemCount();i++)
    {
		m_ShowDList.SetItemData(i,i);
    }
	LDATA data;
	data.subitmindex=pNMListView->iSubItem;
	data.plist=&m_ShowDList;
	fav=!fav;
	
	m_ShowDList.SortItems(lictComparePro,(DWORD)&data);
	*pResult = 0;
}

int CALLBACK CListTESTDlg::lictComparePro(LPARAM lparm1,LPARAM lparm2,LPARAM lparamsort)
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
			CString strItem1=((CListCtrl*)pdata->plist)->GetItemText(lparm1,1);
			CString strItem2=((CListCtrl*)pdata->plist)->GetItemText(lparm2,1);
			
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
	case 3:
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

void CListTESTDlg::OnBtserch() 
{
	// TODO: Add your control notification handler code here
    UpdateData();
	
	if (!m_ckall)
	{
		if (m_serchstr.IsEmpty())
		{
			CString strmeg;
			m_serchComb.GetLBText(m_serchComb.GetCurSel(),strmeg.GetBuffer(0));
			strmeg="查询字段 "+strmeg+"不能为空,请输入数据";
			MessageBox(strmeg,"提示");
			GetDlgItem(IDC_EDIT1)-> SetFocus();
			return;
		}
	}
    CString sqlquery="SELECT * FROM Student WHERE 1=1";
	if (!m_ckall)
	{
		if (0==m_serchComb.GetCurSel())//查询学号
		{
			sqlquery+=" and SID =\'"+m_serchstr+"\'";
		}
		if (1==m_serchComb.GetCurSel())//性别
		{
			sqlquery+=" and SSex =\'"+m_serchstr+"\'";
		}
		if (2==m_serchComb.GetCurSel())//姓名
		{
			sqlquery+=" and SName =\'"+m_serchstr+"\'";
		}
		if (3==m_serchComb.GetCurSel())//入学日期
		{   
			sqlquery+=" and EntryTime =\'"+m_serchstr+"\'";
		}
		if (4==m_serchComb.GetCurSel())//身份证号码
		{   
			sqlquery+=" and ID =\'"+m_serchstr+"\'";
		}
		if (5==m_serchComb.GetCurSel())//出生地
		{   
			sqlquery+=" and NativePlace like \'"+m_serchstr+"\%\'";
		}
	}

    _variant_t strQuery;
	strQuery = sqlquery;

	
	theApp.ADOExecute(theApp.m_pRs,strQuery);

    try
	{
		if(!theApp.m_pRs->BOF)
		{
			theApp.m_pRs->MoveFirst();
		}
		else
		{
			MessageBox("没有查询到学生信息!","查询结果");
			return ;
		}
	     m_ShowDList.DeleteAllItems();
		 GetDlgItem(IDC_STATIC_SW)->ShowWindow(SW_NORMAL);
		 GetDlgItem(IDC_STATIC_SW)->SetWindowText("");
		 int incount=theApp.m_pRs->GetRecordCount();
		 char inta[10];
		 itoa(incount,inta,10);
         CString strShowInfo="本次查询，共查询到：";
		 strShowInfo+=inta;
		 strShowInfo+=" 条！";
	     GetDlgItem(IDC_STATIC_SW)->SetWindowText(strShowInfo);
		//将数据显示到列表中
		while(!theApp.m_pRs->adoEOF)
		{
			int iItemCnt=0;
			iItemCnt=m_ShowDList.GetItemCount();
			
			m_ShowDList.InsertItem(iItemCnt,(_bstr_t)theApp.m_pRs->GetCollect("SID"));
			m_ShowDList.SetItemText(iItemCnt,1,(_bstr_t)theApp.m_pRs->GetCollect("SName"));
			m_ShowDList.SetItemText(iItemCnt,2,(_bstr_t)theApp.m_pRs->GetCollect("SSex"));
			m_ShowDList.SetItemText(iItemCnt,3,(_bstr_t)theApp.m_pRs->GetCollect("EntryTime"));
			m_ShowDList.SetItemText(iItemCnt,4,(_bstr_t)theApp.m_pRs->GetCollect("BirthDay"));
			m_ShowDList.SetItemText(iItemCnt,5,(_bstr_t)theApp.m_pRs->GetCollect("ID"));
			m_ShowDList.SetItemText(iItemCnt,6,(_bstr_t)theApp.m_pRs->GetCollect("Address"));
			theApp.m_pRs->MoveNext();
		}
	}
	catch(...) 
	{
		
	}
	
	
}

void CListTESTDlg::OnChall() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_ckall)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO1))->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	}else
	{
		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	}
}

void CListTESTDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    NM_LISTVIEW * pNMListView=(NM_LISTVIEW*)pNMHDR;

		DWORD dwpos=GetMessagePos();
		CPoint point(LOWORD(dwpos),HIWORD(dwpos));
        CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU1));
		CMenu * popup=menu.GetSubMenu(0);
		ASSERT(popup!=NULL);
		popup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);

	*pResult = 0;
}

void CListTESTDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UINT nFlag;
	   DWORD dwpos=GetMessagePos();
	   CPoint point(LOWORD(dwpos),HIWORD(dwpos));
       m_ShowDList.ScreenToClient(&point);
	   int nitem=m_ShowDList.HitTest(point,&nFlag);
	   if (nitem!=-1)
	   {
		   if(MessageBox("是否需要该学生信息","提示",MB_YESNO)==IDYES) 
		   {
			  CModifStudentInfo midfdlg;
              CString subitem=m_ShowDList.GetItemText(nitem,0);
			  CString strsql="select * from student where sid=\'"+subitem+"\'";
			  _variant_t strQuery;
			  strQuery = strsql;
              theApp.ADOExecute(theApp.m_pRs,strQuery);
			  try
			  {
				  if(!theApp.m_pRs->BOF)
				  {
					  theApp.m_pRs->MoveFirst();
                      _variant_t var;
					  midfdlg.m_stuidnum= (LPCSTR)(_bstr_t)theApp.m_pRs->GetCollect("SID");
					  midfdlg.m_stuname= (LPCSTR)(_bstr_t)theApp.m_pRs->GetCollect("SName");
					  CString strsex=(LPCSTR)(_bstr_t)theApp.m_pRs->GetCollect("SSex");
					 
					  midfdlg.m_stuintsex=(strsex=="男"?0:1);
					  midfdlg.m_stuaddr=(LPCSTR)(_bstr_t)theApp.m_pRs->GetCollect("Address");
					  midfdlg.m_stupstcode=(LPCSTR)(_bstr_t)theApp.m_pRs->GetCollect("PostCode");
					  midfdlg.m_stunatiplace= (LPCSTR)(_bstr_t)theApp.m_pRs->GetCollect("NativePlace");
					  midfdlg.m_stuID=(LPCSTR)(_bstr_t)theApp.m_pRs->GetCollect("ID");
					  var=theApp.m_pRs->GetCollect("Birthday");
                       
					  midfdlg.m_oletimebirth=var.date;
					  var=theApp.m_pRs->GetCollect("EntryTime");
				
					  midfdlg.m_oletimeeEntry=var.date;
				      midfdlg.m_strspeNO=(LPCTSTR)(_bstr_t)theApp.m_pRs->GetCollect("SpNo");
					  midfdlg.m_strCollageNo=(LPCTSTR)(_bstr_t)theApp.m_pRs->GetCollect("CNo");
					  midfdlg.m_strSym=(LPCTSTR)(_bstr_t)theApp.m_pRs->GetCollect("Symbol");

				  }
				  else
				  {
					  MessageBox("没有查询到该学生信息!","查询结果");
					  return ;
				  }		
			  }
			  catch(...) 
			  {	}
			  
	          midfdlg.DoModal();

	   }
      


	}
	*pResult = 0;
}

void CListTESTDlg::OnMenuModif() 
{
	// TODO: Add your command handler code here

// 	DWORD dwpos=GetMessagePos();
// 	CPoint point(LOWORD(dwpos),HIWORD(dwpos));
//     m_ShowDList.ScreenToClient(&point);
// 	LVHITTESTINFO lvinfo;


	MessageBox("修改","提示");
}
BOOL CListTESTDlg::DeleteStuForSql(CString stuId)
{   
    if (stuId.IsEmpty())
    {
		return FALSE;
    }
	CString strsql="delete from student where sid =\'"+stuId+"\'";
	_variant_t strQuery;
	strQuery = strsql;
    return theApp.ADOExecute(theApp.m_pRs,strQuery);
}
void CListTESTDlg::OnMenuDelet() 
{
	// TODO: Add your command handler code here
   POSITION pos=m_ShowDList.GetFirstSelectedItemPosition();
   int delsucc=0;
   int delerr=0;
   if (pos==NULL)
   {
	   TRACE0("NO Items were Selected!\n");
       MessageBox("请选择需要删除的行!","提示");
   }
   else
   { 
	   if(MessageBox("你确认需要删除选择中的行吗？","提示",MB_YESNO)==IDYES) 
	   {
		   while(pos)
		   {
			   int nItem=m_ShowDList.GetNextSelectedItem(pos);
			   TRACE1("Item %d was selected!\n",nItem);
			   m_ShowDList.DeleteItem(nItem);
			   CString subitem=m_ShowDList.GetItemText(nItem,0);
               if(DeleteStuForSql(subitem))
			   {
                   delsucc++;
			   }else
			   {
                   delerr++;
			   }

			   pos=m_ShowDList.GetFirstSelectedItemPosition();
		   }
		   CString showinfo;
		   showinfo.Format("此次删除操作共成功删除：%d 删除失败：%d",delsucc,delerr);
		   MessageBox(showinfo,"提示");
	   }

   }
}

void CListTESTDlg::OnButAdddl() 
{
	// TODO: Add your control notification handler code here
	CAddStudenInf cadddlg;
	cadddlg.DoModal();
}

void CListTESTDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	for (int i=0;i<m_ShowDList.GetItemCount();i++)
	{
		if(m_ShowDList.GetCheck(i))
		{
			m_ShowDList.SetItemState(i,LVIS_SELECTED|LVIS_FOCUSED,LVIS_FOCUSED|LVIS_SELECTED);

		}else
		{
	m_ShowDList.SetItemState(i,0,LVIS_FOCUSED|LVIS_SELECTED);
		}
	}
	*pResult = 0;
}

void CListTESTDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UINT nFlag;
	DWORD dwpos=GetMessagePos();
	CPoint point(LOWORD(dwpos),HIWORD(dwpos));
	m_ShowDList.ScreenToClient(&point);
	int nitem=m_ShowDList.HitTest(point,&nFlag);
	
	if (nitem!=-1)
	{

    	if (nFlag&LVHT_ONITEMLABEL)
	 	 {
	    	if (m_ShowDList.GetCheck(nitem))
			{
		    	m_ShowDList.SetCheck(nitem,FALSE);
		    	m_ShowDList.SetItemState(nitem,0,LVIS_SELECTED|LVIS_FOCUSED);
			}else
			{
		    	m_ShowDList.SetCheck(nitem);
		    	m_ShowDList.SetItemState(nitem,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			} 
	 	 }
	}
	*pResult = 0;
}

void CListTESTDlg::OnAddStuif() 
{
	// TODO: Add your command handler code here
	CAddStudenInf cadddlg;
	cadddlg.DoModal();
}

void CListTESTDlg::OnBtClearall() 
{
	// TODO: Add your control notification handler code here
	m_ShowDList.DeleteAllItems();
}
