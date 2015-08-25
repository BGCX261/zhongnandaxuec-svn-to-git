// AddStudenInf.cpp : implementation file
//

#include "stdafx.h"
#include "listtest.h"
#include "AddStudenInf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddStudenInf dialog


CAddStudenInf::CAddStudenInf(CWnd* pParent /*=NULL*/)
: CDialog(CAddStudenInf::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddStudenInf)
	m_stuid = _T("");
	m_stuname = _T("");
	m_stubirthday = 0;
	m_stuentytime = 0;
	m_stuaddress = _T("");
	m_studentid = _T("");
	m_stuNativeplace = _T("");
	m_stuSexint = -1;
	m_strpostcode = _T("");
	//}}AFX_DATA_INIT
}


void CAddStudenInf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddStudenInf)
	DDX_Control(pDX, IDC_DT_ENTRYTIME, m_ctlentrytime);
	DDX_Control(pDX, IDC_DT_BIRTH, m_ctlbirth);
	DDX_Control(pDX, IDC_CMB_SYMB, m_cmbsymb);
	DDX_Control(pDX, IDC_COM_COLAGE, m_comcollage);
	DDX_Control(pDX, IDC_CMB_SPE, m_comctrlSpe);
	DDX_Text(pDX, IDC_EDIT_SID, m_stuid);
	DDX_Text(pDX, IDC_EDIT_STNAME, m_stuname);
	DDX_DateTimeCtrl(pDX, IDC_DT_BIRTH, m_stubirthday);
	DDX_DateTimeCtrl(pDX, IDC_DT_ENTRYTIME, m_stuentytime);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_stuaddress);
	DDX_Text(pDX, IDC_EDIT_ID, m_studentid);
	DDX_Text(pDX, IDC_EDIT_NATIPLACE, m_stuNativeplace);
	DDX_Radio(pDX, IDC_RADIO_SEX, m_stuSexint);
	DDX_Text(pDX, IDC_EDIT_POSTCD, m_strpostcode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddStudenInf, CDialog)
//{{AFX_MSG_MAP(CAddStudenInf)
ON_BN_CLICKED(IDC_BT_ACANCE, OnBtAcance)
ON_BN_CLICKED(IDC_BT_ADD, OnBtAdd)
ON_WM_CANCELMODE()
	ON_EN_KILLFOCUS(IDC_EDIT_SID, OnKillfocusEditSid)
	ON_EN_CHANGE(IDC_EDIT_SID, OnChangeEditSid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddStudenInf message handlers

void CAddStudenInf::OnBtAcance() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
void CAddStudenInf::ClearDlgText()
{
   	m_stuid = _T("");
	m_stuname = _T("");
	m_stuaddress = _T("");
	m_studentid = _T("");
	m_stuNativeplace = _T("");
	m_stuSexint = 1;
	m_strpostcode = _T("");
   UpdateData(false);
}
void CAddStudenInf::OnBtAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	////////////////////////////////验证数据//////////////////////////////////////////
	if (m_stuid.IsEmpty())
	{
		MessageBox("请输入学号!","提示");
		GetDlgItem(IDC_EDIT_SID)->SetFocus();
		return;
	}
	if (m_stuname.IsEmpty())
	{
		MessageBox("请输入学生姓名!","提示");
		GetDlgItem(IDC_EDIT_STNAME)->SetFocus();
		return;
	}
	if (m_studentid.IsEmpty())
	{
		MessageBox("请输入学生身份证号码!","提示");
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
		return;
	}
	if (m_stuNativeplace.IsEmpty())
	{
		MessageBox("请输入学生的籍贯!","提示");
		GetDlgItem(IDC_EDIT_NATIPLACE)->SetFocus();
		return;
	}
	if (m_stuaddress.IsEmpty())
	{
		MessageBox("请输入学生的家庭住址!","提示");
		GetDlgItem(IDC_EDIT_ADDR)->SetFocus();
		return;
	}
   ///////////////////////////////END验证数据///////////////////////////////////////////

	CString * lpmyPtr=(CString*)m_comctrlSpe.GetItemDataPtr(m_comctrlSpe.GetCurSel());
	CString * lpmyPtr1=(CString*)m_comcollage.GetItemDataPtr(m_comcollage.GetCurSel());
	CString strsymb="";
	int length=0;
	length=m_cmbsymb.GetLBTextLen(m_cmbsymb.GetCurSel());
	m_cmbsymb.GetLBText(m_cmbsymb.GetCurSel(),strsymb.GetBuffer(length));
	strsymb.ReleaseBuffer();

    CString strsex=((m_stuSexint==1)?"男":"女");
    CString strsql="insert into Student(SID,SpNo,CNo,SName,SSex,Birthday,ID,EntryTime,NativePlace,Address,Symbol,PostCode) values (";
            strsql+="'"+m_stuid+"','"+*lpmyPtr+"','"+(*lpmyPtr1)+"','"+m_stuname+"','"+strsex+"','"+m_stubirthday.Format("%Y-%m-%d")+"','"+m_studentid+"','"+m_stuentytime.Format("%Y-%m-%d")+"','"+m_stuNativeplace+"','"+m_stuaddress+"'";
			strsql+=",'"+strsymb+"','"+m_strpostcode+"')";
	_variant_t strQuery=strsql;
	
	if(theApp.ADOExecute(theApp.m_pRs,strQuery))
	{
		MessageBox("学生信息添加成功！","提示");
		ClearDlgText();
			
	}
	else
	{
	   MessageBox("学生信息添加失败！","提示");
	}
}

BOOL CAddStudenInf::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initCombSpeci();
	InitComBoxCollageDt();
    if (m_comctrlSpe.GetCount()>0)
    {
		m_comctrlSpe.SetCurSel(0);
    }

	if (m_comcollage.GetCount()>0)
    {
		m_comcollage.SetCurSel(0);
    }
	m_cmbsymb.SetCurSel(0);


    m_ctlbirth.SetTime(COleDateTime::GetCurrentTime());
	m_ctlentrytime.SetTime(COleDateTime::GetCurrentTime());

	((CButton*)(GetDlgItem(IDC_RADIO_SEX)))->SetCheck(BST_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CAddStudenInf::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

bool CAddStudenInf::initCombSpeci()
{

	((CComboBox*)GetDlgItem(IDC_CMB_SPE))->ResetContent();//情况列表项

    _variant_t strQuery="SELECT * FROM Special WHERE 1=1";
	
	theApp.ADOExecute(theApp.m_pRs,strQuery);
    try
	{
		if(!theApp.m_pRs->BOF)
		{
			theApp.m_pRs->MoveFirst();
		}
		else
		{
			MessageBox("查询的专业信息为空!","提示");
			return FALSE;
		}
		//将数据显示到列表中
		while(!theApp.m_pRs->adoEOF)
		{
			int iItemCnt=0;
			iItemCnt=m_comctrlSpe.GetCount();
			/*	m_comctrlSpe.InsertString(iItemCnt,(_bstr_t)theApp.m_pRs->GetCollect("SpNo"));*/
			m_comctrlSpe.InsertString(iItemCnt,(_bstr_t)theApp.m_pRs->GetCollect("SpName"));
		    CString * pstr=new CString;
			*pstr=(LPCTSTR)(_bstr_t)theApp.m_pRs->GetCollect("SpNo");
			m_comctrlSpe.SetItemDataPtr(iItemCnt,(void*)pstr);
			theApp.m_pRs->MoveNext();
		}
	}
	catch(...) 
	{
		MessageBox("初始化信息出错!","提示");
		return FALSE;
	}
	return TRUE;
}

bool CAddStudenInf::InitComBoxCollageDt()
{
	
    ((CComboBox*)GetDlgItem(IDC_COM_COLAGE))->ResetContent();//情况列表项


    _variant_t strQuery="SELECT * FROM Collage WHERE 1=1";
	
	theApp.ADOExecute(theApp.m_pRs,strQuery);
    try
	{
		if(!theApp.m_pRs->BOF)
		{
			theApp.m_pRs->MoveFirst();
		}
		else
		{
			MessageBox("查询的学院信息为空!","提示");
			return FALSE;
		}
		//将数据显示到列表中
		while(!theApp.m_pRs->adoEOF)
		{
			int iItemCnt=0;
			iItemCnt=m_comcollage.GetCount();
			m_comcollage.InsertString(iItemCnt,(_bstr_t)theApp.m_pRs->GetCollect("CName"));

			CString * pstr=new CString;
			*pstr=(LPCTSTR)(_bstr_t)theApp.m_pRs->GetCollect("CNo");
			m_comcollage.SetItemDataPtr(iItemCnt,(void*)pstr);

			theApp.m_pRs->MoveNext();
		}
	}
	catch(...) 
	{
		MessageBox("初始化信息出错!","提示");
		return FALSE;
	}
	return TRUE;
}

void CAddStudenInf::OnKillfocusEditSid() 
{
	// TODO: Add your control notification handler code here
	 UpdateData();
	 CString strsql="SELECT SID FROM Student WHERE 1=1 and SID =\'"+m_stuid+"\'";
	 _variant_t strQuery=strsql;
	
	 try
	 {
		 theApp.ADOExecute(theApp.m_pRs,strQuery);
		 int iCount = theApp.m_pRs->GetRecordCount();
	     if ( 1<=iCount ) 
         {
            MessageBox("你输入的学号已经存在!","提示");
			GetDlgItem(IDC_EDIT_SID)->SetFocus();
		 }
	 }
	 catch(...) 
	 {
		 MessageBox("初始化信息出错!","提示");
	 }


}

void CAddStudenInf::OnChangeEditSid() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	
}

BOOL CAddStudenInf::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
    if (m_comcollage.GetCount()>0)
	{
		for (int i=0;i<m_comcollage.GetCount();i++)
		{
			CString *p=(CString*) m_comcollage.GetItemDataPtr(i);
			delete p;
		}
	}
	if (m_comctrlSpe.GetCount()>0)
	{
		for (int i=0;i<m_comctrlSpe.GetCount();i++)
		{
			CString *p=(CString*) m_comctrlSpe.GetItemDataPtr(i);
			delete p;
		}
	}

	return CDialog::DestroyWindow();
}
