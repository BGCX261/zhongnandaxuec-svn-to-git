// TinyPlayerDlg.h : header file
//

#if !defined(AFX_TINYPLAYERDLG_H__34B322FA_D877_44EB_85B8_21BEDDAC4BB0__INCLUDED_)
#define AFX_TINYPLAYERDLG_H__34B322FA_D877_44EB_85B8_21BEDDAC4BB0__INCLUDED_

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

private:
	LONG InitDS();
	LONG RelsDS();
	CString m_sFilePathName;

private:
	INT m_PlayState;
// Dialog Data
	//{{AFX_DATA(CTinyPlayerDlg)
	enum { IDD = IDD_TINYPLAYER_DIALOG };
	CSliderCtrl	m_sliderCurPos;
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
	afx_msg void OnClose();
	afx_msg void OnButton1();
	afx_msg LONG OnButton2();
	afx_msg LONG OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnStaticScree();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TINYPLAYERDLG_H__34B322FA_D877_44EB_85B8_21BEDDAC4BB0__INCLUDED_)
