// VideoCap.h : main header file for the VIDEOCAP application
//

#if !defined(AFX_VIDEOCAP_H__78DC084C_0C6F_4946_8BE9_B8B0965CEFFB__INCLUDED_)
#define AFX_VIDEOCAP_H__78DC084C_0C6F_4946_8BE9_B8B0965CEFFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVideoCapApp:
// See VideoCap.cpp for the implementation of this class
//

class CVideoCapApp : public CWinApp
{
public:
	CVideoCapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoCapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVideoCapApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOCAP_H__78DC084C_0C6F_4946_8BE9_B8B0965CEFFB__INCLUDED_)
