// VideoCapDlg.h : header file
//

#if !defined(AFX_VIDEOCAPDLG_H__C60CCF5A_5943_4A9B_AE3D_62A62B8C6113__INCLUDED_)
#define AFX_VIDEOCAPDLG_H__C60CCF5A_5943_4A9B_AE3D_62A62B8C6113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVideoCapDlg dialog

class CVideoCapDlg : public CDialog
{
// Construction
public:
	CVideoCapDlg(CWnd* pParent = NULL);	// standard constructor
	LONG InitDS();
	LONG RelsDS();
	


private:
	BOOL  m_bIsInitOK;
	CMenu m_MyMenu;
// Dialog Data
	//{{AFX_DATA(CVideoCapDlg)
	enum { IDD = IDD_VIDEOCAP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoCapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVideoCapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCapStart();
	afx_msg void OnCapStop();
	afx_msg void OnPreviewStart();
	afx_msg void OnPreviewStop();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOCAPDLG_H__C60CCF5A_5943_4A9B_AE3D_62A62B8C6113__INCLUDED_)
