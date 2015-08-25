// ShowContDB.cpp : implementation file
//

#include "stdafx.h"
#include "listtest.h"
#include "ShowContDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowContDB dialog


CShowContDB::CShowContDB(CWnd* pParent /*=NULL*/)
	: CDialog(CShowContDB::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowContDB)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShowContDB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowContDB)
	DDX_Control(pDX, IDC_PROGRESS1, m_mprogres);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowContDB, CDialog)
	//{{AFX_MSG_MAP(CShowContDB)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowContDB message handlers

bool CShowContDB::SetShowText(CString strTitle)
{
  GetDlgItem(IDC_STATIC)->SetWindowText(strTitle);
  
  return TRUE;
}

bool CShowContDB::SetProgressStep(int intstep)
{
  
  m_mprogres.SetPos(intstep);
  return TRUE;

}

BOOL CShowContDB::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_mprogres.SetRange(0,100);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowContDB::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnTimer(nIDEvent);
}
