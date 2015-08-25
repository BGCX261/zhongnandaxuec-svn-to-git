// ObjectDlg.h : header file
//

#if !defined(AFX_OBJECTDLG_H__CC3643C4_3EC6_48EE_8B61_D3C8EB9DF3A5__INCLUDED_)
#define AFX_OBJECTDLG_H__CC3643C4_3EC6_48EE_8B61_D3C8EB9DF3A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CObjectDlg dialog

class CObjectDlg : public CDialog
{
// Construction
public:
	CObjectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CObjectDlg)
	enum { IDD = IDD_OBJECT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CObjectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTDLG_H__CC3643C4_3EC6_48EE_8B61_D3C8EB9DF3A5__INCLUDED_)
