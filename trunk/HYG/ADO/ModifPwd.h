#if !defined(AFX_MODIFPWD_H__4451F7CE_3D33_4B9B_AB8E_0EF6E8425FC1__INCLUDED_)
#define AFX_MODIFPWD_H__4451F7CE_3D33_4B9B_AB8E_0EF6E8425FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifPwd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifPwd dialog

class CModifPwd : public CDialog
{
// Construction
public:
	CModifPwd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifPwd)
	enum { IDD = IDD_MD_PWD };
	CEdit	m_CrnewPwd;
	CEdit	m_CnewPwd;
	CString	m_newpwd;
	CString	m_renewpwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifPwd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifPwd)
	afx_msg void OnButok();
	afx_msg void OnButcan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFPWD_H__4451F7CE_3D33_4B9B_AB8E_0EF6E8425FC1__INCLUDED_)
