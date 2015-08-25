// ModifPwd.cpp : implementation file
//

#include "stdafx.h"
#include "ListTEST.h"
#include "ModifPwd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifPwd dialog

extern CString strAdminName;
CModifPwd::CModifPwd(CWnd* pParent /*=NULL*/)
	: CDialog(CModifPwd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifPwd)
	m_newpwd = _T("");
	m_renewpwd = _T("");
	//}}AFX_DATA_INIT
}


void CModifPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifPwd)
	DDX_Control(pDX, IDC_EDIT2, m_CrnewPwd);
	DDX_Control(pDX, IDC_EDIT1, m_CnewPwd);
	DDX_Text(pDX, IDC_EDIT1, m_newpwd);
	DDX_Text(pDX, IDC_EDIT2, m_renewpwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifPwd, CDialog)
	//{{AFX_MSG_MAP(CModifPwd)
	ON_BN_CLICKED(IDC_BUTOK, OnButok)
	ON_BN_CLICKED(IDC_BUTCAN, OnButcan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifPwd message handlers

void CModifPwd::OnButok() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_newpwd.IsEmpty())
	{
		MessageBox("新密码不能为空！","提示");
		return;
	}
	if (m_renewpwd.IsEmpty())
	{
		MessageBox("请再次输入新密码！","提示");
		return;
	}

    if (0!=m_newpwd.Compare(m_renewpwd))
    {
		MessageBox("两次密码输入的不一致！","提示");
        m_newpwd="";
		m_renewpwd="";
		UpdateData(FALSE);
		return;
    }
	

    _variant_t strQuery="Update Login set password='"+m_renewpwd+"' where Loginname='"+strAdminName+"'";
	
	
	if(theApp.ADOExecute(theApp.m_pRs,strQuery))
	{
		MessageBox("密码修改成功","提示");
		OnOK();
			
	}
	else
	{
	   MessageBox("密码修改失败！","提示");
	}
}

void CModifPwd::OnButcan() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
