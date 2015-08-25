#if !defined(AFX_MODIFSTUDENTINFO_H__0C829E14_740B_4C13_AC5B_19BEB31DDF6B__INCLUDED_)
#define AFX_MODIFSTUDENTINFO_H__0C829E14_740B_4C13_AC5B_19BEB31DDF6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifStudentInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifStudentInfo dialog

class CModifStudentInfo : public CDialog
{
// Construction
public:
	CModifStudentInfo(CWnd* pParent = NULL);   // standard constructor
    bool initCombMSpeci();
	bool InitComBoxMCollageDt();
	bool SelectSpciNo();
	bool SelectCollageNo();
	CString m_strspeNO;
	CString m_strCollageNo;
	CString m_strSym;
// Dialog Data
	//{{AFX_DATA(CModifStudentInfo)
	enum { IDD = IDD_DIA_STDMODIF };
	CDateTimeCtrl	m_entrytime;
	CDateTimeCtrl	m_timebirth;
	CComboBox	m_comcollage;
	CComboBox	m_comsymb;
	CComboBox	m_comspe;
	CString	m_stuidnum;
	CString	m_stuID;
	CString	m_stuaddr;
	CString	m_stunatiplace;
	CString	m_stupstcode;
	CString	m_stuname;
	int		m_stuintsex;
	COleDateTime	m_oletimebirth;
	COleDateTime	m_oletimeeEntry;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifStudentInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifStudentInfo)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnBtUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFSTUDENTINFO_H__0C829E14_740B_4C13_AC5B_19BEB31DDF6B__INCLUDED_)
