// GetDirectoryFileMFCDlg.h : header file
//

#if !defined(AFX_GETDIRECTORYFILEMFCDLG_H__D752F1A7_AEBE_4131_A0C2_1832895DC709__INCLUDED_)
#define AFX_GETDIRECTORYFILEMFCDLG_H__D752F1A7_AEBE_4131_A0C2_1832895DC709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetDirectoryFileMFCDlg dialog

class CGetDirectoryFileMFCDlg : public CDialog
{
// Construction
public:
	CString GetFiles(CString strFileName,CString strPath);
	CGetDirectoryFileMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetDirectoryFileMFCDlg)
	enum { IDD = IDD_GETDIRECTORYFILEMFC_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetDirectoryFileMFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetDirectoryFileMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETDIRECTORYFILEMFCDLG_H__D752F1A7_AEBE_4131_A0C2_1832895DC709__INCLUDED_)
