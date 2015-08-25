// ListTEST.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ListTEST.h"
#include "ListTESTDlg.h"
#include "Login.h"
#include "ShowContDB.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListTESTApp

BEGIN_MESSAGE_MAP(CListTESTApp, CWinApp)
	//{{AFX_MSG_MAP(CListTESTApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListTESTApp construction

CListTESTApp::CListTESTApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CListTESTApp object

CListTESTApp theApp;
CString strAdminName;
/////////////////////////////////////////////////////////////////////////////
// CListTESTApp initialization

BOOL CListTESTApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	CShowContDB sdbdlg;
	sdbdlg.Create(IDD_DIALOG1,this->m_pMainWnd);
    sdbdlg.ShowWindow(SW_NORMAL);
    sdbdlg.SetShowText("���ڳ�ʼ��COM!");
	sdbdlg.SetProgressStep(10);
   if (!AfxOleInit())
   {
	   AfxMessageBox("��ʼ��COMʧ��!");
	   return FALSE;
   }
   sdbdlg.SetShowText("��ʼ��COM�ɹ�!");
	sdbdlg.SetProgressStep(20);
   ::CoInitialize(NULL);//��ʼ��COM����
   try
   {
	   m_pConn.CreateInstance(__uuidof(Connection));
	   m_pConn->ConnectionTimeout=10;
	   _bstr_t strcon="driver={SQL Server};Server=127.0.0.1;DATABASE=STD;UID=sa;PWD=sa";
	   sdbdlg.SetShowText("���ڴ����ݿ�����!");
       sdbdlg.SetProgressStep(30);
	   m_pConn->Open(strcon,"","",adModeUnknown);
	   if (!(m_pConn->State==adStateOpen))
	   {
		   AfxMessageBox("���ݿ��ʧ�ܣ�");
		   return FALSE;
	   }
   }
   catch (_com_error e)
   {
	   ::CoUninitialize();
	   CString str="���ݿ����ӳ�ʼ������";
	   str+=e.ErrorMessage();
	   AfxMessageBox(str);
	   return FALSE; 
	}
   sdbdlg.SetShowText("�����ݿ����ӳɹ�!");
   sdbdlg.SetProgressStep(100);
   m_pRs.CreateInstance(__uuidof(Recordset));
   sdbdlg.CloseWindow();
   CLogin ldlg;
   m_pMainWnd=&ldlg;
 
  ldlg.DoModal();


// 	CListTESTDlg dlg;
// 	m_pMainWnd = &dlg;
//  
// 	int nResponse = dlg.DoModal();
// 	if (nResponse == IDOK)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with OK
// 	}
// 	else if (nResponse == IDCANCEL)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with Cancel
// 	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
bool CListTESTApp::ADOExecute(_RecordsetPtr &ADOSet, _variant_t &strSQL)
{
	if ( ADOSet->State == adStateOpen)	
		ADOSet->Close();
	try
	{
       	ADOSet->Open(strSQL, m_pConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdUnknown);
		return true;
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("ADO Error: %s",(char*)e.Description());
		AfxMessageBox(err);
		return false;
	}
}
