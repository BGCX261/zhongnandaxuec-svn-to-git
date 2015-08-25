// XMLReadDlg.h : header file
//

#if !defined(AFX_XMLREADDLG_H__BB45E633_AF39_42DE_BA65_655B2452BDD2__INCLUDED_)
#define AFX_XMLREADDLG_H__BB45E633_AF39_42DE_BA65_655B2452BDD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXMLReadDlg dialog

class CXMLReadDlg : public CDialog
{
// Construction
public:
   
	static int CALLBACK lictComparePro(LPARAM lparm1,LPARAM lparm2,LPARAM lparamsort);
	CXMLReadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXMLReadDlg)
	enum { IDD = IDD_XMLREAD_DIALOG };
	CListCtrl	m_listshow;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLReadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXMLReadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnColumnclickListShw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLREADDLG_H__BB45E633_AF39_42DE_BA65_655B2452BDD2__INCLUDED_)
