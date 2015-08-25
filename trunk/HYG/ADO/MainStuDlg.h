#if !defined(AFX_MAINSTUDLG_H__B46DE32C_F7DB_46FD_ACB2_7D827AC0FB17__INCLUDED_)
#define AFX_MAINSTUDLG_H__B46DE32C_F7DB_46FD_ACB2_7D827AC0FB17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainStuDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainStuDlg dialog

class CMainStuDlg : public CDialog
{
// Construction
public:
	CMainStuDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainStuDlg)
	enum { IDD = IDD_DIA_MAIN };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainStuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainStuDlg)
	afx_msg void OnBTStu();
	afx_msg void OnBTPwd();
	afx_msg void OnBTPro();
	afx_msg void OnBtExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSTUDLG_H__B46DE32C_F7DB_46FD_ACB2_7D827AC0FB17__INCLUDED_)
