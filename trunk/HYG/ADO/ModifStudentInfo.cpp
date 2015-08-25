// ModifStudentInfo.cpp : implementation file
//

#include "stdafx.h"
#include "listtest.h"
#include "ModifStudentInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifStudentInfo dialog


CModifStudentInfo::CModifStudentInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CModifStudentInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifStudentInfo)
	m_stuidnum = _T("");
	m_stuID = _T("");
	m_stuaddr = _T("");
	m_stunatiplace = _T("");
	m_stupstcode = _T("");
	m_stuname = _T("");
	m_stuintsex = -1;
	m_oletimebirth = COleDateTime::GetCurrentTime();
	m_oletimeeEntry = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CModifStudentInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifStudentInfo)
	DDX_Control(pDX, IDC_DTM_ENTRYTIME, m_entrytime);
	DDX_Control(pDX, IDC_DTM_BIRTH, m_timebirth);
	DDX_Control(pDX, IDC_COMM_COLAGE, m_comcollage);
	DDX_Control(pDX, IDC_CMBM_SYMB, m_comsymb);
	DDX_Control(pDX, IDC_CMBM_SPE, m_comspe);
	DDX_Text(pDX, IDC_EDITM_SID, m_stuidnum);
	DDX_Text(pDX, IDC_EDITM_ID, m_stuID);
	DDX_Text(pDX, IDC_EDITM_ADDR, m_stuaddr);
	DDX_Text(pDX, IDC_EDITM_NATIPLACE, m_stunatiplace);
	DDX_Text(pDX, IDC_EDITM_POSTCD, m_stupstcode);
	DDX_Text(pDX, IDC_EDITM_STNAME, m_stuname);
	DDX_Radio(pDX, IDC_RADIOM_SEX, m_stuintsex);
	DDX_DateTimeCtrl(pDX, IDC_DTM_BIRTH, m_oletimebirth);
	DDX_DateTimeCtrl(pDX, IDC_DTM_ENTRYTIME, m_oletimeeEntry);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifStudentInfo, CDialog)
	//{{AFX_MSG_MAP(CModifStudentInfo)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BT_UPDATE, OnBtUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifStudentInfo message handlers

void CModifStudentInfo::OnOK() 
{
	// TODO: Add extra validation here
	




	CDialog::OnOK();
}

void CModifStudentInfo::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

bool CModifStudentInfo::InitComBoxMCollageDt()
{
	
    ((CComboBox*)GetDlgItem(IDC_COMM_COLAGE))->ResetContent();//情况列表项
	
	
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

bool CModifStudentInfo::initCombMSpeci()
{
	
	((CComboBox*)GetDlgItem(IDC_CMBM_SPE))->ResetContent();//情况列表项
	
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
			iItemCnt=m_comspe.GetCount();
			/*	m_comctrlSpe.InsertString(iItemCnt,(_bstr_t)theApp.m_pRs->GetCollect("SpNo"));*/
			m_comspe.InsertString(iItemCnt,(_bstr_t)theApp.m_pRs->GetCollect("SpName"));
			CString * pstr=new CString;
			*pstr=(LPCTSTR)(_bstr_t)theApp.m_pRs->GetCollect("SpNo");
			m_comspe.SetItemDataPtr(iItemCnt,(void*)pstr);
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
BOOL CModifStudentInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	initCombMSpeci();
	InitComBoxMCollageDt();
	m_comsymb.SetCurSel(m_comsymb.FindString(0,m_strSym));
	SelectSpciNo();
	SelectCollageNo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CModifStudentInfo::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

bool CModifStudentInfo::SelectSpciNo()
{

	// Check all the items in the combo box; if an item's
	// data pointer is equal to my pointer then reset it to NULL.
	for (int i = 0; i < m_comspe.GetCount(); i++)
	{
		CString * lpmyPtr=(CString*)m_comspe.GetItemDataPtr(i);
    
        if ((*lpmyPtr)==m_strspeNO)
        {
			m_comspe.SetCurSel(i);
			return TRUE;
        }
	}
	return FALSE;
}

bool CModifStudentInfo::SelectCollageNo()
{
	for (int i = 0; i < m_comcollage.GetCount(); i++)
	{
		CString * lpmyPtr=(CString*)m_comcollage.GetItemDataPtr(i);
		
        if ((*lpmyPtr)==m_strCollageNo)
        {
			m_comcollage.SetCurSel(i);
			return TRUE;
        }
	}
	return FALSE;
}

void CModifStudentInfo::OnBtUpdate() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	////////////////////////////////验证数据//////////////////////////////////////////

	if (m_stuname.IsEmpty())
	{
		MessageBox("请输入学生姓名!","提示");
		GetDlgItem(IDC_EDITM_STNAME)->SetFocus();
		return;
	}
	if (m_stuID.IsEmpty())
	{
		MessageBox("请输入学生身份证号码!","提示");
		GetDlgItem(IDC_EDITM_ID)->SetFocus();
		return;
	}
	if (m_stunatiplace.IsEmpty())
	{
		MessageBox("请输入学生的籍贯!","提示");
		GetDlgItem(IDC_EDITM_NATIPLACE)->SetFocus();
		return;
	}
	if (m_stuaddr.IsEmpty())
	{
		MessageBox("请输入学生的家庭住址!","提示");
		GetDlgItem(IDC_EDITM_ADDR)->SetFocus();
		return;
	}
	///////////////////////////////END验证数据///////////////////////////////////////////
	
	CString * lpmyPtr=(CString*)m_comspe.GetItemDataPtr(m_comspe.GetCurSel());
	CString * lpmyPtr1=(CString*)m_comcollage.GetItemDataPtr(m_comcollage.GetCurSel());
	CString strsymb="";
	int length=0;
	length=m_comsymb.GetLBTextLen(m_comsymb.GetCurSel());
	m_comsymb.GetLBText(m_comsymb.GetCurSel(),strsymb.GetBuffer(length));
	strsymb.ReleaseBuffer();
	
    CString strsex=((m_stuintsex==1)?"男":"女");

	CString strsql="update Student set SpNo='"+(*lpmyPtr)+"',CNo='"+(*lpmyPtr1)+"',SName='"+m_stuname+"',Birthday='"+m_oletimebirth.Format("%Y-%m-%d")+"',";
	strsql+="ID='"+m_stuID+"',EntryTime='"+m_oletimeeEntry.Format("%Y-%m-%d")+"',Address='"+m_stuaddr+"',Symbol='"+strsymb+"',PostCode='"+m_stupstcode+"' where SID='"+m_stuidnum+"'";

	_variant_t strQuery=strsql;
	
	if(theApp.ADOExecute(theApp.m_pRs,strQuery))
	{
		MessageBox("学生信息添加成功！","提示");
    	OnOK();
		
	}
	else
	{
		MessageBox("学生信息添加失败！","提示");
	}
}


