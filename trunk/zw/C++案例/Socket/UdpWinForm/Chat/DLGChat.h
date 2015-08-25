#if !defined(AFX_DLGCHAT_H__A34A4357_094A_499D_BA2C_F21E48E52437__INCLUDED_)
#define AFX_DLGCHAT_H__A34A4357_094A_499D_BA2C_F21E48E52437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGChat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDLGChat dialog
#define WM_RECVDATA		WM_USER+1
struct RECVPARAM 
{
	SOCKET sock;
	HWND hwnd;
};
class CDLGChat : public CDialog
{
// Construction
public:
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
	BOOL InitSocket();
	CDLGChat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGChat)
	enum { IDD = IDD_DIALOG_CHAT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGChat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hicon;

	// Generated message map functions
	//{{AFX_MSG(CDLGChat)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCancelMode();
	virtual BOOL OnInitDialog();
	afx_msg void onRecvData(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBtnSend();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	SOCKET m_socket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHAT_H__A34A4357_094A_499D_BA2C_F21E48E52437__INCLUDED_)
