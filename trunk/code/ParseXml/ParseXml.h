// ParseXml.h : main header file for the PARSEXML application
//

#if !defined(AFX_PARSEXML_H__9E059D40_82BB_48F4_AF7C_33F0E503327A__INCLUDED_)
#define AFX_PARSEXML_H__9E059D40_82BB_48F4_AF7C_33F0E503327A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CParseXmlApp:
// See ParseXml.cpp for the implementation of this class
//

class CParseXmlApp : public CWinApp
{
public:
	CParseXmlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParseXmlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CParseXmlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSEXML_H__9E059D40_82BB_48F4_AF7C_33F0E503327A__INCLUDED_)
