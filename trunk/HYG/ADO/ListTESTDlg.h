// ListTESTDlg.h : header file
//

#if !defined(AFX_LISTTESTDLG_H__8D6377A8_E957_470C_9815_FB5AFC021923__INCLUDED_)
#define AFX_LISTTESTDLG_H__8D6377A8_E957_470C_9815_FB5AFC021923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListTESTDlg dialog
struct LDATA 
{
	int subitmindex; //表头的列
	CListCtrl * plist;//listCtrl的指针
};
class CListTESTDlg : public CDialog
{
// Construction
public:
	static int CALLBACK lictComparePro(LPARAM lparm1,LPARAM lparm2,LPARAM lparamsort);
	CListTESTDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListTESTDlg)
	enum { IDD = IDD_LISTTEST_DIALOG };
	CComboBox	m_serchComb;
	CListCtrl	m_ShowDList;
	CString	m_serchstr;
	BOOL	m_ckall;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListTESTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    BOOL DeleteStuForSql(CString stuId);
	// Generated message map functions
	//{{AFX_MSG(CListTESTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtserch();
	afx_msg void OnChall();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuModif();
	afx_msg void OnMenuDelet();
	afx_msg void OnMenuSele();
	afx_msg void OnButAdddl();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddStuif();
	afx_msg void OnBtClearall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	_RecordsetPtr m_pRrd;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTESTDLG_H__8D6377A8_E957_470C_9815_FB5AFC021923__INCLUDED_)
