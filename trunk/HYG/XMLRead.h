// XMLRead.h : main header file for the XMLREAD application
//

#if !defined(AFX_XMLREAD_H__871BA1A9_10F0_4135_9544_AED94F89C971__INCLUDED_)
#define AFX_XMLREAD_H__871BA1A9_10F0_4135_9544_AED94F89C971__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXMLReadApp:
// See XMLRead.cpp for the implementation of this class
//

class CXMLReadApp : public CWinApp
{
public:
	CXMLReadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLReadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXMLReadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLREAD_H__871BA1A9_10F0_4135_9544_AED94F89C971__INCLUDED_)
