// TinyPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TinyPlayer.h"
#include "TinyPlayerDlg.h"

#include <dshow.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;
	
    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);
	
    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);
	
    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');
	
    // Display a message box with the formatted string
    MessageBox(NULL, szBuffer, TEXT("TinyPlayer Info"), MB_OK);
}

#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }
#define VERIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}

// Gobal var
IGraphBuilder *g_pGB   = NULL;
IMediaControl *g_pMC   = NULL;
IMediaEventEx *g_pME   = NULL;
IVideoWindow  *g_pVW   = NULL;
IBasicAudio   *g_pBA   = NULL;
IBasicVideo   *g_pBV   = NULL;
IMediaSeeking *g_pMS   = NULL;
IMediaPosition *g_pMP  = NULL;
IVideoFrameStep *g_pFS = NULL;

// Rate
double    g_PlaybackRate=1.0;

double    g_dbTotalDur = 0.0;
CString   g_sTotalTime;

enum PlayState
{
	INVALID = 0,
	PLAY,
	PAUSE,
	STOP
};


HRESULT ModifyRate(double dRateAdjust)
{
    HRESULT hr=S_OK;
    double dRate;
	
    // If the IMediaPosition interface exists, use it to set rate
    if ((g_pMP) && (dRateAdjust != 0))
    {
        if ((hr = g_pMP->get_Rate(&dRate)) == S_OK)
        {
            // Add current rate to adjustment value
            double dNewRate = dRate + dRateAdjust;
            hr = g_pMP->put_Rate(dNewRate);
			
            // Save global rate
            if (SUCCEEDED(hr))
            {
                g_PlaybackRate = dNewRate;
            }
        }
    }
	
    return hr;
}

HRESULT GetTotalDuration(double &dbTotalDur, CString &sDuration)
{
    HRESULT hr;
	
    if (!g_pMS)
        return E_NOINTERFACE;
	
    // Initialize the display in case we can't read the duration
    //m_StrDuration.SetWindowText(TEXT("<00:00.000>"));
	
    // Is media time supported for this file?
    if (S_OK != g_pMS->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME))
        return E_NOINTERFACE;
	
    // Read the time format to restore later
    GUID guidOriginalFormat;
    hr = g_pMS->GetTimeFormat(&guidOriginalFormat);
    if (FAILED(hr))
        return hr;
	
    // Ensure media time format for easy display
    hr = g_pMS->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
    if (FAILED(hr))
        return hr;
	
    // Read the file's duration
    LONGLONG llDuration;
    hr = g_pMS->GetDuration(&llDuration);
    if (FAILED(hr))
        return hr;
	
    // Return to the original format
    if (guidOriginalFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = g_pMS->SetTimeFormat(&guidOriginalFormat);
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
	
    wsprintf(szDuration, TEXT("%02d:%02d:%02d\0"),hrs, mins, secs);
	
	dbTotalDur = rt;
	sDuration = szDuration;
	
    return hr;
}

HRESULT GetCurrentDuration(double &dbCur, CString &sDuration)
{
	REFTIME rt;
	LONGLONG llCurPos;
	TCHAR szDuration[64];
	int hrs, mins, secs;
	
	if (!g_pMS)
        return E_NOINTERFACE;

	g_pMS->GetCurrentPosition(&llCurPos);
	rt = llCurPos/10000000;
	rt += 0.49;
	
	hrs  =  (int)rt / 3600;
	mins = ((int)rt % 3600) / 60;
	secs = ((int)rt % 3600) % 60;
	
	wsprintf(szDuration, TEXT("%02d:%02d:%02d\0"),hrs, mins, secs);
	dbCur = rt;
	sDuration = szDuration;
}

HRESULT SetCurPos(double dbCur)
{
	#define ONE_SECOND 10000000

	HRESULT hr;
	if (!g_pMS)
        return E_NOINTERFACE;

	REFERENCE_TIME rtNow = (REFERENCE_TIME)dbCur*10000000;

	hr = g_pMS->SetPositions(&rtNow, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);

	return hr;
}
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

	m_PlayState = 0;
}

void CTinyPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTinyPlayerDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_sliderCurPos);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTinyPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CTinyPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_STATIC_SCREE, OnStaticScree)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
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
	// Get the interface for DirectShow's GraphBuilder
	CoInitialize(NULL);
	
	SetTimer(1, 1000, NULL);
	// Open file
	OnButton1();
	return TRUE;  // return TRUE  unless you set the focus to a control
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

void CTinyPlayerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	HRESULT hr = RelsDS();
	
	CoUninitialize();
	CDialog::OnClose();
}

LONG CTinyPlayerDlg::InitDS()
{
	HRESULT hr;

	if (m_sFilePathName.IsEmpty())
	{
		return -1;
	}

    VERIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
		IID_IGraphBuilder, (void **)&g_pGB));
	
    if(SUCCEEDED(hr))
    {
        // Have the graph builder construct its the appropriate graph automatically
        VERIF(g_pGB->RenderFile((LPCTSTR)m_sFilePathName, NULL));
		
        // QueryInterface for DirectShow interfaces
        VERIF(g_pGB->QueryInterface(IID_IMediaControl, (void **)&g_pMC));
        VERIF(g_pGB->QueryInterface(IID_IMediaEventEx, (void **)&g_pME));
        VERIF(g_pGB->QueryInterface(IID_IMediaSeeking, (void **)&g_pMS));
        VERIF(g_pGB->QueryInterface(IID_IMediaPosition, (void **)&g_pMP));
		
        // Query for video interfaces, which may not be relevant for audio files
        VERIF(g_pGB->QueryInterface(IID_IVideoWindow, (void **)&g_pVW));
        VERIF(g_pGB->QueryInterface(IID_IBasicVideo, (void **)&g_pBV));
		
        // Query for audio interfaces, which may not be relevant for video-only files
        VERIF(g_pGB->QueryInterface(IID_IBasicAudio, (void **)&g_pBA));

		IVideoFrameStep *pFSTest = NULL;
		// Get the frame step interface, if supported
		hr = g_pGB->QueryInterface(__uuidof(IVideoFrameStep), (PVOID *)&pFSTest);
		if (FAILED(hr))
			return FALSE;
		// Check if this decoder can step
		hr = pFSTest->CanStep(0L, NULL);
		
		if (hr == S_OK)
		{
			g_pFS = pFSTest;  // Save interface to global variable for later use
			return TRUE;
		}
		else
		{
			pFSTest->Release();
			return FALSE;
		}
	}
	
	return 0;
}

LONG CTinyPlayerDlg::RelsDS()
{
	SAFE_RELEASE(g_pGB);
	SAFE_RELEASE(g_pMC);
	SAFE_RELEASE(g_pME);
	SAFE_RELEASE(g_pVW);
	SAFE_RELEASE(g_pBA);
	SAFE_RELEASE(g_pBV);
	SAFE_RELEASE(g_pMS);
	SAFE_RELEASE(g_pMP);
	SAFE_RELEASE(g_pFS);
	
	return 0;
}

// Open file
void CTinyPlayerDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
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

// Start
LONG CTinyPlayerDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr;

	if (PLAY == m_PlayState)
	{
		g_pMC->Pause();
		m_PlayState = PAUSE;
		SetDlgItemText(IDC_BUTTON2, _T("Play"));
	}
	else if (PAUSE == m_PlayState)
	{
		g_pMC->Run();
		m_PlayState = PLAY;
		SetDlgItemText(IDC_BUTTON2, _T("Pause"));
	}
	// Ready to run
	else
	{
		InitDS();
		
		LONG lHeight, lWidth;
		if (!g_pVW)
		{
			return -1;
		}
		g_pVW->get_Height(&lHeight);
		g_pVW->get_Width(&lWidth);
		
		g_pVW->put_Owner((OAHWND)GetDlgItem(IDC_STATIC_SCREE)->GetSafeHwnd());
		g_pVW->put_WindowStyle(WS_CHILD   |   WS_CLIPSIBLINGS   |   WS_CLIPCHILDREN);
		g_pVW->SetWindowPosition(0, 0, lHeight, lWidth); //   定位播放子窗口
		g_pVW->put_MessageDrain((OAHWND)GetSafeHwnd());
		
		VERIF(g_pMC->Run());

		
		m_PlayState = PLAY;
		SetDlgItemText(IDC_BUTTON2, _T("Play"));
		CRect rt;
		GetWindowRect(&rt);
		rt.left += 1;
		rt.right += 1;
		MoveWindow(&rt);

		CString sDur;
		GetTotalDuration(g_dbTotalDur, sDur);
		g_sTotalTime = sDur;
		SetDlgItemText(IDC_STATIC, g_sTotalTime);

		m_sliderCurPos.SetRange(0, 100);
		m_sliderCurPos.SetTic(1);

		CString sSize;
		sSize.Format(_T("H: %d, W: %d"), lHeight, lWidth);
		SetDlgItemText(IDC_STATIC_TEST, sSize);
	}


	return 0;
}

// Stop
LONG CTinyPlayerDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if (STOP == m_PlayState)
	{
		return 0;
	}
	HRESULT hr;
	if (g_pMC)
	{
		VERIF(g_pMC->Stop());
		RelsDS();

		m_PlayState = STOP;
	}
	
	return 0;
}

// faster
void CTinyPlayerDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	ModifyRate(0.5);
}

// slower
void CTinyPlayerDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	ModifyRate(-0.5);
}

// step
void CTinyPlayerDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	if (g_pMC)
	{
		if (PAUSE != m_PlayState)
		{
			g_pMC->Pause();
			m_PlayState = PAUSE;
		}
		g_pFS->Step(1, NULL);
	}
	
}

// 恢复原来大小
BOOL CTinyPlayerDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch (pMsg->wParam)
		{ 
		case VK_ESCAPE:
			if (g_pVW)
			{
				LONG lFull;
				g_pVW->get_FullScreenMode(&lFull);
				if (lFull)
				{
					g_pVW->put_FullScreenMode(OAFALSE);
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

// 最大化
void CTinyPlayerDlg::OnStaticScree() 
{
	// TODO: Add your control notification handler code here
	if (g_pVW)
	{
		LONG lFull, lLeft, lTop, lWidth, lHeight;
		g_pVW->get_Left(&lLeft);
		g_pVW->get_Top(&lTop);
		g_pVW->get_Width(&lWidth);
		g_pVW->get_Height(&lHeight);
		
		g_pVW->get_FullScreenMode(&lFull);
		if (lFull)
		{
			g_pVW->put_FullScreenMode(OAFALSE);
		}
		else
		{
			g_pVW->put_FullScreenMode(OATRUE);
		}
	}
}



void CTinyPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (1 == nIDEvent)
	{
		double dbCurPos;
		CString sCur, sTime(g_sTotalTime);
		sTime += _T(" - ");
		GetCurrentDuration(dbCurPos, sCur);
		sTime += sCur;
		SetDlgItemText(IDC_STATIC, sTime);

		if (dbCurPos <= g_dbTotalDur)
		{
			int i = (double)100*dbCurPos/g_dbTotalDur;
			m_sliderCurPos.SetPos(i);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CTinyPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl   *pSlider   =   (CSliderCtrl   *)pScrollBar;
	int   nID   =   pSlider-> GetDlgCtrlID();
	if (IDC_SLIDER1 == nID)
	{
		double db;
		int iCurPos = m_sliderCurPos.GetPos();
 		db = (double)iCurPos/(double)100;
 		db *= g_dbTotalDur;
 		SetCurPos(db);
 		CString s;
		s.Format(_T("%f"), db);
		SetDlgItemText(IDC_STATIC_TEST, s);
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
