// Login.cpp : implementation file
//

#include "stdafx.h"
#include "ListTEST.h"
#include "Login.h"
#include "ListTESTDlg.h"
#include "MainStuDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogin dialog

extern CString strAdminName;
CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogin)
	m_username = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT
	isLogin=false;
}


void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogin)
	DDX_Control(pDX, IDC_EPWD, m_PassWordCtr);
	DDX_Control(pDX, IDC_EUSER, m_UserNameCtr);
	DDX_Text(pDX, IDC_EUSER, m_username);
	DDX_Text(pDX, IDC_EPWD, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	//{{AFX_MSG_MAP(CLogin)
	ON_BN_CLICKED(IDC_BT_LOG, OnBtLog)
	ON_BN_CLICKED(IDC_BT_CAN, OnBtCan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogin message handlers

void CLogin::OnBtLog() 
{
	// TODO: Add your control notification handler code here
	CString strSql;
	_variant_t strQuery;
	UpdateData(TRUE);
	
	if (m_username.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
	{
		MessageBox("�������¼�û��û���!","��ʾ");
        m_UserNameCtr.SetFocus();
		return;
	}
	if (m_password.IsEmpty())
	{
		MessageBox("�������¼�û�����!","��ʾ");
        m_PassWordCtr.SetFocus();
		return;
	}


	strQuery = "SELECT * FROM Login WHERE Loginname='"+m_username+ "' AND password='" + m_password+ "'";
	theApp.ADOExecute(theApp.m_pRs, strQuery);

    int iCount = theApp.m_pRs->GetRecordCount();
	if ( 0==iCount ) 
	{
	    MessageBox("�û������������!","��ʾ");
		m_username="";
		m_password="";
		m_UserNameCtr.SetFocus();
		UpdateData(false);
		
	}
	else
	{
		strAdminName=m_username;
	    isLogin=true;
        this->ShowWindow(SW_HIDE);
//         CListTESTDlg dlg;
// 		dlg.DoModal();
        CMainStuDlg stdlg;
		stdlg.DoModal();
		OnOK();
	}
}

void CLogin::OnBtCan() 
{
	// TODO: Add your control notification handler code here
	isLogin=false;
	OnCancel();
}

bool CLogin::initComAdo()
{
    ::CoInitialize(NULL);//��ʼ��COM����
	try
	{
		m_pConn.CreateInstance(__uuidof(Connection));
		m_pConn->ConnectionTimeout=10;
		_bstr_t strcon="driver={SQL Server};Server=127.0.0.1;DATABASE=STD;UID=sa;PWD=sa";
		m_pConn->Open(strcon,"","",adModeUnknown);
		if (!(m_pConn->State==adStateOpen))
		{
			MessageBox("���ݿ��ʧ�ܣ�","��ʾ");
			return FALSE;
		}
	}
	catch (_com_error e)
	{
		::CoUninitialize();
		CString str="���ݿ����ӳ�ʼ������";
		str+=e.ErrorMessage();
		MessageBox(str,"����");
		return FALSE; 
	}
	return TRUE;
}
