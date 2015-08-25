// MainStuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListTEST.h"
#include "MainStuDlg.h"
#include "ModifPwd.h"
#include "ListTESTDlg.h"
#include "SpeciDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainStuDlg dialog


CMainStuDlg::CMainStuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainStuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainStuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainStuDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainStuDlg, CDialog)
	//{{AFX_MSG_MAP(CMainStuDlg)
	ON_BN_CLICKED(IDC_BTStu, OnBTStu)
	ON_BN_CLICKED(IDC_BTPwd, OnBTPwd)
	ON_BN_CLICKED(IDC_BTPro, OnBTPro)
	ON_BN_CLICKED(IDC_BT_EXIT, OnBtExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainStuDlg message handlers

void CMainStuDlg::OnBTStu() 
{
	// TODO: Add your control notification handler code here
	CListTESTDlg cldlg;
	this->ShowWindow(SW_HIDE);
	cldlg.DoModal();
	this->ShowWindow(SW_NORMAL);
	
}

void CMainStuDlg::OnBTPwd() 
{
	// TODO: Add your control notification handler code here
	CModifPwd mp;
	mp.DoModal();

}

void CMainStuDlg::OnBTPro() 
{
	// TODO: Add your control notification handler code here
	CSpeciDlg spdlg;
	spdlg.DoModal();
}

void CMainStuDlg::OnBtExit() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}
