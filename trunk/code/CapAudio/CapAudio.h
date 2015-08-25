// CapAudio.h : main header file for the CAPAUDIO application
//

#if !defined(AFX_CAPAUDIO_H__43833A31_F14C_47A8_B596_DFEAFA9A35C7__INCLUDED_)
#define AFX_CAPAUDIO_H__43833A31_F14C_47A8_B596_DFEAFA9A35C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCapAudioApp:
// See CapAudio.cpp for the implementation of this class
//

class CCapAudioApp : public CWinApp
{
public:
	CCapAudioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCapAudioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCapAudioApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPAUDIO_H__43833A31_F14C_47A8_B596_DFEAFA9A35C7__INCLUDED_)
