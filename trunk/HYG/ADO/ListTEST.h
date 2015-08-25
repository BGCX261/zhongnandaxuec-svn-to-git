// ListTEST.h : main header file for the LISTTEST application
//

#if !defined(AFX_LISTTEST_H__61AE497E_E37A_433B_9C8C_04373EDE07F5__INCLUDED_)
#define AFX_LISTTEST_H__61AE497E_E37A_433B_9C8C_04373EDE07F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListTESTApp:
// See ListTEST.cpp for the implementation of this class
//

class CListTESTApp : public CWinApp
{
public:
	CListTESTApp();
	_ConnectionPtr m_pConn;
    _RecordsetPtr m_pRs;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListTESTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	bool ADOExecute(_RecordsetPtr &ADOSet, _variant_t &strSQL);

// Implementation

	//{{AFX_MSG(CListTESTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CListTESTApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTEST_H__61AE497E_E37A_433B_9C8C_04373EDE07F5__INCLUDED_)
