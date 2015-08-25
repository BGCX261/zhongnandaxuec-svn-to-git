// CapAudioDlg.h : header file
//
#include <dshow.h>

#if !defined(AFX_CAPAUDIODLG_H__30D57213_FC4F_4B2A_805C_F8AAA943C4A7__INCLUDED_)
#define AFX_CAPAUDIODLG_H__30D57213_FC4F_4B2A_805C_F8AAA943C4A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCapAudioDlg dialog

class CCapAudioDlg : public CDialog
{
// Construction
public:
	CMenu m_MyMenu;
	CCapAudioDlg(CWnd* pParent = NULL);	// standard constructor
    IGraphBuilder *m_pGB;
    IMediaControl *m_pMC;
	IVideoWindow  *pVW;
	IMediaEventEx *m_pME;

	ICaptureGraphBuilder2 *m_pCapture;

// Dialog Data
	//{{AFX_DATA(CCapAudioDlg)
	enum { IDD = IDD_CAPAUDIO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCapAudioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCapAudioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMENUITEMStartView();
	afx_msg void OnMENUITEMStopView();
	afx_msg void OnMENUITEMStartCapture();
	afx_msg void OnMENUITEMStopCapture();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPAUDIODLG_H__30D57213_FC4F_4B2A_805C_F8AAA943C4A7__INCLUDED_)
