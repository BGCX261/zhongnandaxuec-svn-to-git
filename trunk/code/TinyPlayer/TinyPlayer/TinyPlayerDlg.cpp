// TinyPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TinyPlayer.h"
#include "TinyPlayerDlg.h"

#include <atlbase.h>
#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTinyPlayerDlg dialog

CTinyPlayerDlg::CTinyPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTinyPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTinyPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	pGraphBuilder = NULL;
	pFilterGraph = NULL;
	pMediaControl = NULL;
	pEvent = NULL;
	pVideoWin = NULL;
	pMS = NULL;
}

void CTinyPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTinyPlayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTinyPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CTinyPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnOpenFile)
	ON_BN_CLICKED(IDC_BUTTON2, OnPlay)
	ON_BN_CLICKED(IDC_BUTTON3, OnStop)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTinyPlayerDlg message handlers

BOOL CTinyPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetTimer(1, 1000,   NULL   );   //   设置一个定时器1，   3   秒  
	SetTimer(10,   500,   NULL   );   //   设置一个定时器10，   500毫秒   
	iTest = 0;


	return TRUE;  // return TRUE  unless you set the focus to a control
}


HRESULT CTinyPlayerDlg::DisplayFileDuration(void)
{
    HRESULT hr;
	
    if (!pMS)
        return E_NOINTERFACE;
	
    // Initialize the display in case we can't read the duration
    //m_StrDuration.SetWindowText(TEXT("<00:00.000>"));
	
    // Is media time supported for this file?
    if (S_OK != pMS->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME))
        return E_NOINTERFACE;
	
    // Read the time format to restore later
    GUID guidOriginalFormat;
    hr = pMS->GetTimeFormat(&guidOriginalFormat);
    if (FAILED(hr))
        return hr;
	
    // Ensure media time format for easy display
    hr = pMS->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
    if (FAILED(hr))
        return hr;
	
    // Read the file's duration
    LONGLONG llDuration;
    hr = pMS->GetDuration(&llDuration);
    if (FAILED(hr))
        return hr;
	
    // Return to the original format
    if (guidOriginalFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = pMS->SetTimeFormat(&guidOriginalFormat);
        if (FAILED(hr))
            return hr;
    }
	
    // Convert the LONGLONG duration into human-readable format
    unsigned long nTotalMS = (unsigned long) llDuration / 10000; // 100ns -> ms
    int nMS = nTotalMS % 1000;
    int nSeconds = nTotalMS / 1000;
    int nMinutes = nSeconds / 60;
    nSeconds %= 60;
	
    // Update the display
    TCHAR szDuration[24];
    wsprintf(szDuration, _T("%02dm:%02d.%03ds\0"), nMinutes, nSeconds, nMS);


	int hrs, mins, secs;
	
	REFTIME rt = llDuration/10000000;
    rt += 0.49;
	
    hrs  =  (int)rt / 3600;
    mins = ((int)rt % 3600) / 60;
    secs = ((int)rt % 3600) % 60;
	
    wsprintf(szDuration, TEXT("%02d:%02d:%02d - \0"),hrs, mins, secs);

	m_sLength = szDuration;


	GetDlgItem(IDC_STATIC)->SetWindowText(m_sLength);
    return hr;
}

void CTinyPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTinyPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
		pVideoWin->put_Owner((OAHWND)GetSafeHwnd());
		
	}
	else
	{
		CDialog::OnPaint();
		
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTinyPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTinyPlayerDlg::OnOpenFile() 
{
	// TODO: Add your control notification handler code here
	OnStop();
	
	TCHAR szFilters[]= _T("Media Type Files (*.avi *.wav)|*.avi;*.wav|All Files (*.*)|*.*||");
	   
	// Create an Open dialog; the default file name extension is ".avi".
	CFileDialog fileDlg (TRUE, NULL, NULL, OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	if( fileDlg.DoModal ()==IDOK )
	{
		m_sFilePathName = fileDlg.GetPathName();
		SetWindowText(m_sFilePathName);
	}
}

int CTinyPlayerDlg::OnPlay() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr;
	OAFilterState State;

	if (pMediaControl)
	{
		hr = pMediaControl->GetState(1000, &State);
		if (State_Running == State)
		{
			GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("Pause"));
			pMediaControl->Pause();
		}
		else if (State_Paused == State)
		{
			GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("Play"));
			pMediaControl->Run();
		}
		return 0;
	}
	else
	{
		if (pMediaControl)
		{
			pMediaControl->Release();
			pEvent->Release();
			pVideoWin->Release();
			pGraphBuilder->Release();

			pMediaControl = NULL;
			pEvent = NULL;
			pVideoWin = NULL;
			pGraphBuilder = NULL;
		}


		
		HRESULT   hres;
		WCHAR     FileName[MAX_PATH];

		CComPtr<IFilterGraph> pFG;
		CComPtr<IGraphBuilder> pGB;
		HRESULT hr   = S_FALSE;

		
		
		IFilterGraph  *pUnk;
		CoInitialize(NULL);

		hres = pFG.CoCreateInstance(CLSID_FilterGraph);
		pFG->QueryInterface(&pGB);

		hres = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IFilterGraph, (LPVOID *)&pUnk);
		if(SUCCEEDED(hres))
		{
			hres = pUnk->QueryInterface(IID_IFilterGraph, (LPVOID *)&pFilterGraph);
			if(FAILED(hres))
			{
				pUnk->Release();
				return hres;
			}			
			hres = pUnk->QueryInterface(IID_IGraphBuilder, (LPVOID *)&pGraphBuilder);
			if(FAILED(hres))
			{
				pUnk->Release();
				pFilterGraph->Release(); pFilterGraph = NULL;
				return hres;
			}
			
			hres = pGraphBuilder->RenderFile((LPCTSTR)m_sFilePathName, NULL);
			if(FAILED(hres))
			{
				pUnk->Release();
				pFilterGraph->Release(); pFilterGraph = NULL;
				pGraphBuilder->Release(); pGraphBuilder = NULL;
				return hres;
			}
			
			hres = pUnk->QueryInterface(IID_IMediaControl, (LPVOID *)&pMediaControl);
			if(FAILED(hres))
			{
				pUnk->Release();
				pFilterGraph->Release(); pFilterGraph = NULL;
				pGraphBuilder->Release(); pGraphBuilder = NULL;
				return hres;
			}
			
			//
			// Not being able to get the IMediaEvent interface does not
			// necessarly mean that we can't play the graph.
			//
			pUnk->QueryInterface(IID_IMediaEvent, (LPVOID *)&pEvent);
			pUnk->QueryInterface(IID_IMediaSeeking, (LPVOID *)&pMS);
			pUnk->QueryInterface(IID_IVideoWindow, (LPVOID *)&pVideoWin);
			
			pUnk->Release();


			pVideoWin->put_Owner((OAHWND)GetSafeHwnd());
		
		LONG lHeight, lWidth;
		pVideoWin->get_Height(&lHeight);
		pVideoWin->get_Width(&lWidth);

		LONG lDx;
		RECT rtPos;
		GetWindowRect(&rtPos);

		// 移动主窗口
		rtPos.right = rtPos.left+lWidth+50;
		rtPos.bottom = rtPos.top+lHeight+110;
		MoveWindow(&rtPos);

		// 移动子控件
		RECT rtItemPos; 
		rtItemPos.left = 20;
		rtItemPos.top = lHeight+40;
		rtItemPos.right = rtItemPos.left + 60;
		rtItemPos.bottom = rtItemPos.top + 30;
		GetDlgItem(IDC_BUTTON1)->MoveWindow(&rtItemPos);

		rtItemPos.left = rtItemPos.left + 80;
		rtItemPos.right = rtItemPos.right + 80;
		GetDlgItem(IDC_BUTTON2)->MoveWindow(&rtItemPos);

		rtItemPos.left = rtItemPos.left + 80;
		rtItemPos.right = rtItemPos.right + 80;
		GetDlgItem(IDC_BUTTON3)->MoveWindow(&rtItemPos);

		rtItemPos.left = rtItemPos.left + 80;
		rtItemPos.right = rtItemPos.right + 100/*(lWidth-rtItemPos.left-40)*/;
		GetDlgItem(IDC_SLIDER1)->MoveWindow(&rtItemPos);

		rtItemPos.left = lWidth-120;
		rtItemPos.right = lWidth;
		GetDlgItem(IDC_STATIC)->MoveWindow(&rtItemPos);
		

		// 增加消息处理
		pVideoWin->put_MessageDrain((OAHWND)GetSafeHwnd());


		// 设置video窗口模式
		pVideoWin->put_WindowStyle(WS_CHILD   |   WS_CLIPSIBLINGS   |   WS_CLIPCHILDREN);  
		pVideoWin->SetWindowPosition(20, 20, 800, 600); //   定位播放子窗口 
		
		// 主窗口移到屏幕中央
		CenterWindow();
		
		DisplayFileDuration();

		// Run the graph
		pMediaControl->Run();
	}
	}
}

void CTinyPlayerDlg::SetFormat(const GUID Format)
{
	HRESULT hr = pMS->SetTimeFormat(&Format);
    if(SUCCEEDED(hr))
    {
        m_TimeFormat = Format;
    }
}

INT CTinyPlayerDlg::StatusMovie()
{
	INT m_Mode;
    if(pMediaControl)
    {
        FILTER_STATE    fs;
        HRESULT         hr;
		
        hr = pMediaControl->GetState(100, (OAFilterState *)&fs);
		
        // Don't know what the state is so just stay at old state.
        if(hr == VFW_S_STATE_INTERMEDIATE)
        {
            return m_Mode;
        }
		
        switch(fs)
        {
		case State_Stopped:
			m_Mode = 0;
			break;
			
		case State_Paused:
			m_Mode = 1;
			break;
			
		case State_Running:
			m_Mode = 2;
			break;
        }
    }
	
    return m_Mode;
}

int CTinyPlayerDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr;
	OAFilterState State;

	if (!pMediaControl)
	{
		return -1;
	}

	hr = pMediaControl->GetState(1000, &State);
	if (State_Stopped != State)
	{
		pMediaControl->Stop();
	}	
	pVideoWin->put_Visible(0);
	SendMessage(WM_ERASEBKGND);
//	pEvent->Release();
//	pMediaControl->Release ();
//	pGraph->Release ();
	return 0;
}

void CTinyPlayerDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (pVideoWin)
	{
		LONG lFull, lLeft, lTop, lWidth, lHeight;
		pVideoWin->get_Left(&lLeft);
		pVideoWin->get_Top(&lTop);
		pVideoWin->get_Width(&lWidth);
		pVideoWin->get_Height(&lHeight);

		CRect rt(20, 20, 20+lWidth, 20+lHeight);
		if (!rt.PtInRect(point))
		{
			return;
		}

		pVideoWin->get_FullScreenMode(&lFull);
		if (lFull)
		{
			pVideoWin->put_FullScreenMode(OAFALSE);
		}
		else
		{
			pVideoWin->put_FullScreenMode(OATRUE);
		}
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}


BOOL CTinyPlayerDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch (pMsg->wParam)
		{ 
		case VK_ESCAPE:
			if (pVideoWin)
			{
				LONG lFull;
				pVideoWin->get_FullScreenMode(&lFull);
				if (lFull)
				{
					pVideoWin->put_FullScreenMode(OAFALSE);
				}
			}
			break;
		default:
			break;
		}
		return TRUE;
	} 

	return CDialog::PreTranslateMessage(pMsg);
}

void CTinyPlayerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//     if(pVideoWin)
//     {
//         RECT client;
// 		
// 		LONG lFull, lLeft, lTop, lWidth, lHeight;
// 		pVideoWin->get_Width(&lWidth);
// 		pVideoWin->get_Height(&lHeight);
// 
// 		pVideoWin->put_Owner((OAHWND)GetSafeHwnd());
// 		pVideoWin->put_WindowStyle(WS_CHILD   |   WS_CLIPSIBLINGS   |   WS_CLIPCHILDREN);
//         pVideoWin->SetWindowPosition(20, 20, lWidth, lHeight);
//     }
}

BOOL CTinyPlayerDlg::OnEraseBkgnd(CDC*   pDC)    
{  
	LONG lFull, lLeft, lTop, lWidth, lHeight;
	if (pVideoWin)
	{
		pVideoWin->get_Width(&lWidth);
		pVideoWin->get_Height(&lHeight);
		
		pVideoWin->put_Owner((OAHWND)GetSafeHwnd());
	}
	return   CDialog::OnEraseBkgnd(pDC);;  
 }

void CTinyPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString s;
	CString sShow;

	HRESULT hr;
    LONGLONG Duration;
	double dbDuration;
	REFTIME rt;
	
	if (!pMS)
	{
		return;
	}


	switch (nIDEvent)
	{
	case 1:
		LONG lCurPos;
		LONGLONG llCurPos;

		pMS->GetCurrentPosition(&llCurPos);


		TCHAR szDuration[64];
		int hrs, mins, secs;
		
		rt = llCurPos/10000000;
		rt += 0.49;
		
		hrs  =  (int)rt / 3600;
		mins = ((int)rt % 3600) / 60;
		secs = ((int)rt % 3600) % 60;
		
		wsprintf(szDuration, TEXT("%02d:%02d:%02d\0"),hrs, mins, secs);

		sShow = m_sLength;
		sShow += szDuration;
		GetDlgItem(IDC_STATIC)->SetWindowText(sShow);
		break;

	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}
