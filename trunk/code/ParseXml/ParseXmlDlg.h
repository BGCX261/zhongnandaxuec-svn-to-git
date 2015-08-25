// ParseXmlDlg.h : header file
//

#if !defined(AFX_PARSEXMLDLG_H__F5B14847_786C_47DD_A335_3438589D7F08__INCLUDED_)
#define AFX_PARSEXMLDLG_H__F5B14847_786C_47DD_A335_3438589D7F08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CParseXmlDlg dialog

class CParseXmlDlg : public CDialog
{
// Construction
public:
	CParseXmlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CParseXmlDlg)
	enum { IDD = IDD_PARSEXML_DIALOG };
	CListCtrl	m_listXML;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParseXmlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CParseXmlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSEXMLDLG_H__F5B14847_786C_47DD_A335_3438589D7F08__INCLUDED_)
