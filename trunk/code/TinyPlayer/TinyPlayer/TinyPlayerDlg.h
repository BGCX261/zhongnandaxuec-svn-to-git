// TinyPlayerDlg.h : header file
//
#include <DShow.h>

#if !defined(AFX_TINYPLAYERDLG_H__4678705C_6B41_4BA7_ACF2_0D6D6CF33546__INCLUDED_)
#define AFX_TINYPLAYERDLG_H__4678705C_6B41_4BA7_ACF2_0D6D6CF33546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTinyPlayerDlg dialog

class CTinyPlayerDlg : public CDialog
{
// Construction
public:
	CTinyPlayerDlg(CWnd* pParent = NULL);	// standard constructor
	void SetFormat(const GUID Format);
	INT StatusMovie();
	HRESULT DisplayFileDuration(void);
	
	IGraphBuilder *pGraphBuilder;
	IFilterGraph  *pFilterGraph;
	IMediaControl *pMediaControl;
	IMediaEvent   *pEvent;
	IVideoWindow  *pVideoWin;
	IMediaSeeking *pMS;

	CString       m_sFilePathName;
	CString       m_sLength;
	int iTest;
	GUID             m_TimeFormat;

// Dialog Data
	//{{AFX_DATA(CTinyPlayerDlg)
	enum { IDD = IDD_TINYPLAYER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTinyPlayerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTinyPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenFile();
	afx_msg int OnPlay();
	afx_msg int OnStop();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC*   pDC); 
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TINYPLAYERDLG_H__4678705C_6B41_4BA7_ACF2_0D6D6CF33546__INCLUDED_)
