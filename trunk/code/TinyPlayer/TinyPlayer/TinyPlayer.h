// TinyPlayer.h : main header file for the TINYPLAYER application
//

#if !defined(AFX_TINYPLAYER_H__71BD84E7_0B72_4B04_A88F_1E232B337FD8__INCLUDED_)
#define AFX_TINYPLAYER_H__71BD84E7_0B72_4B04_A88F_1E232B337FD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTinyPlayerApp:
// See TinyPlayer.cpp for the implementation of this class
//

class CTinyPlayerApp : public CWinApp
{
public:
	CTinyPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTinyPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTinyPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TINYPLAYER_H__71BD84E7_0B72_4B04_A88F_1E232B337FD8__INCLUDED_)
