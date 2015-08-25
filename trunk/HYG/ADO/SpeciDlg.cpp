// SpeciDlg.cpp : implementation file
//

#include "stdafx.h"
#include "listtest.h"
#include "SpeciDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpeciDlg dialog


CSpeciDlg::CSpeciDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpeciDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpeciDlg)
	m_strserchv = _T("");
	//}}AFX_DATA_INIT
}


void CSpeciDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpeciDlg)
	DDX_Control(pDX, IDC_COMSER_SPE, m_combserc);
	DDX_Control(pDX, IDC_LTSHOW_SPE, m_showlistSercResult);
	DDX_Text(pDX, IDC_ETSERCH, m_strserchv);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpeciDlg, CDialog)
	//{{AFX_MSG_MAP(CSpeciDlg)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTSPESERCH, OnBtspeserch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeciDlg message handlers

BOOL CSpeciDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_combserc.InsertString(0,"专业代码");
	m_combserc.InsertString(1,"专业名称");
	m_combserc.InsertString(2,"学院名称");

	m_combserc.SetCurSel(0);
    
	m_showlistSercResult.InsertColumn(0,"编号",LVCFMT_CENTER,90);
    m_showlistSercResult.InsertColumn(1,"专业名称",LVCFMT_CENTER,200);
    m_showlistSercResult.InsertColumn(2,"学院名称",LVCFMT_CENTER,200);
    m_showlistSercResult.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpeciDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();






	// TODO: Add your message handler code here
	
}

void CSpeciDlg::OnBtspeserch() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString sqlquery="select distinct a.SpNo,a.SpName,b.CName from Special a ,Collage b  where a.CNo=b.CNo ";
	if (m_strserchv.IsEmpty())
	{
// 		CString strmeg;
// 		m_combserc.GetLBText(m_combserc.GetCurSel(),strmeg.GetBuffer(0));
// 		strmeg="查询字段 "+strmeg+"不能为空,请输入数据";
// 		MessageBox(strmeg,"提示");
// 		GetDlgItem(IDC_ETSERCH)-> SetFocus();
// 		return;
	}else
	{
		if (0==m_combserc.GetCurSel())//专业编号
		{
			sqlquery+=" and a.SpNo =\'"+m_strserchv+"\'";
		}
		if (1==m_combserc.GetCurSel())//专业名称
		{
			sqlquery+=" and a.SpName like \'"+m_strserchv+"\%\'";
		}
		if (2==m_combserc.GetCurSel())//学院名称
		{
			sqlquery+=" and b.CName like \'"+m_strserchv+"\%\'";
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
			MessageBox("没有查询到专业信息!","查询结果");
			return ;
		}
		m_showlistSercResult.DeleteAllItems();
		GetDlgItem(IDC_STATIC_SWSP)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STATIC_SWSP)->SetWindowText("");
		int incount=theApp.m_pRs->GetRecordCount();
		char inta[10];
		itoa(incount,inta,10);
		CString strShowInfo="本次查询，共查询到：";
		strShowInfo+=inta;
		strShowInfo+=" 条！";
		GetDlgItem(IDC_STATIC_SWSP)->SetWindowText(strShowInfo);
		//将数据显示到列表中
		while(!theApp.m_pRs->adoEOF)
		{
			int iItemCnt=0;
			iItemCnt=m_showlistSercResult.GetItemCount();
			
			m_showlistSercResult.InsertItem(iItemCnt,(_bstr_t)theApp.m_pRs->GetCollect("SpNo"));
			m_showlistSercResult.SetItemText(iItemCnt,1,(_bstr_t)theApp.m_pRs->GetCollect("SpName"));
			m_showlistSercResult.SetItemText(iItemCnt,2,(_bstr_t)theApp.m_pRs->GetCollect("CName"));
		
			theApp.m_pRs->MoveNext();
		}
	}
	catch(...) 
	{
		
	}

}
