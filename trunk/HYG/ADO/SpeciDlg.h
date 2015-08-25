#if !defined(AFX_SPECIDLG_H__A5AE1E1D_1FD2_4A22_B5A0_56DECFE88F89__INCLUDED_)
#define AFX_SPECIDLG_H__A5AE1E1D_1FD2_4A22_B5A0_56DECFE88F89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpeciDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpeciDlg dialog

class CSpeciDlg : public CDialog
{
// Construction
public:
	CSpeciDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpeciDlg)
	enum { IDD = IDD_DLG_SPECI };
	CComboBox	m_combserc;
	CListCtrl	m_showlistSercResult;
	CString	m_strserchv;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeciDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpeciDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnBtspeserch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECIDLG_H__A5AE1E1D_1FD2_4A22_B5A0_56DECFE88F89__INCLUDED_)
