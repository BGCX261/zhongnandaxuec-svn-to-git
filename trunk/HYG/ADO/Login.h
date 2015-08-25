#if !defined(AFX_LOGIN_H__02D0CEF6_922C_49FC_8F0C_83F0ED40B63D__INCLUDED_)
#define AFX_LOGIN_H__02D0CEF6_922C_49FC_8F0C_83F0ED40B63D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Login.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogin dialog

class CLogin : public CDialog
{
// Construction
public:
	CLogin(CWnd* pParent = NULL);   // standard constructor
   	_ConnectionPtr m_pConn;
    _RecordsetPtr m_pRs;
// Dialog Data
	//{{AFX_DATA(CLogin)
	enum { IDD = IDD_DLG_LOGIN };
	CEdit	m_PassWordCtr;
	CEdit	m_UserNameCtr;
	CString	m_username;
	CString	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogin)
	afx_msg void OnBtLog();
	afx_msg void OnBtCan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	bool initComAdo();
	bool isLogin;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__02D0CEF6_922C_49FC_8F0C_83F0ED40B63D__INCLUDED_)
