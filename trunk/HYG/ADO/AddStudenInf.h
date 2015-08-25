#if !defined(AFX_ADDSTUDENINF_H__00F0C58B_7C41_40A8_A3CF_503413F9918F__INCLUDED_)
#define AFX_ADDSTUDENINF_H__00F0C58B_7C41_40A8_A3CF_503413F9918F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddStudenInf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddStudenInf dialog

class CAddStudenInf : public CDialog
{
// Construction
public:
	CAddStudenInf(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddStudenInf)
	enum { IDD = IDD_DADD_STU };
	CDateTimeCtrl	m_ctlentrytime;
	CDateTimeCtrl	m_ctlbirth;
	CComboBox	m_cmbsymb;
	CComboBox	m_comcollage;
	CComboBox	m_comctrlSpe;
	CString	m_stuid;
	CString	m_stuname;
	CTime	m_stubirthday;
	CTime	m_stuentytime;
	CString	m_stuaddress;
	CString	m_studentid;
	CString	m_stuNativeplace;
	int		m_stuSexint;
	CString	m_strpostcode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddStudenInf)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddStudenInf)
	afx_msg void OnBtAcance();
	afx_msg void OnBtAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnKillfocusEditSid();
	afx_msg void OnChangeEditSid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool InitComBoxCollageDt();
    void ClearDlgText();
	bool initCombSpeci();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSTUDENINF_H__00F0C58B_7C41_40A8_A3CF_503413F9918F__INCLUDED_)
