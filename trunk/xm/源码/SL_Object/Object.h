// Object.h : main header file for the OBJECT application
//

#if !defined(AFX_OBJECT_H__BA5FA8A6_459E_4B53_809E_8AD424377F9F__INCLUDED_)
#define AFX_OBJECT_H__BA5FA8A6_459E_4B53_809E_8AD424377F9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CObjectApp:
// See Object.cpp for the implementation of this class
//

class CObjectApp : public CWinApp
{
public:
	CObjectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CObjectApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECT_H__BA5FA8A6_459E_4B53_809E_8AD424377F9F__INCLUDED_)
