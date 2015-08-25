#if !defined(AFX_SHOWCONTDB_H__20A8A9D3_3950_4CC7_8C51_262010B93757__INCLUDED_)
#define AFX_SHOWCONTDB_H__20A8A9D3_3950_4CC7_8C51_262010B93757__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowContDB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowContDB dialog

class CShowContDB : public CDialog
{
// Construction
public:
	bool SetProgressStep(int );
	bool SetShowText(CString );
	CShowContDB(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowContDB)
	enum { IDD = IDD_DIALOG1 };
	CProgressCtrl	m_mprogres;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowContDB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowContDB)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWCONTDB_H__20A8A9D3_3950_4CC7_8C51_262010B93757__INCLUDED_)
