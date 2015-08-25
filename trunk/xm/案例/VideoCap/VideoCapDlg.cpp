// VideoCapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VideoCap.h"
#include "VideoCapDlg.h"

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
ICaptureGraphBuilder2 *g_pCapGB=NULL;
IBaseFilter *g_pVCap=NULL;
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
// CVideoCapDlg dialog

CVideoCapDlg::CVideoCapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoCapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoCapDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsInitOK = FALSE;
}

void CVideoCapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoCapDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVideoCapDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoCapDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENUITEM_CAP_START, OnCapStart)
	ON_COMMAND(ID_MENUITEM_CAP_STOP, OnCapStop)
	ON_COMMAND(ID_MENUITEM_PREVIEW_START, OnPreviewStart)
	ON_COMMAND(ID_MENUITEM_PREVIEW_STOP, OnPreviewStop)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoCapDlg message handlers

BOOL CVideoCapDlg::OnInitDialog()
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
	m_MyMenu.LoadMenu(IDR_MENU1);
	SetMenu(&m_MyMenu);

	CoInitialize(NULL);

	LONG lRet = InitDS();
	if (0 == lRet)
	{
		m_bIsInitOK = TRUE;
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVideoCapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVideoCapDlg::OnPaint() 
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

LONG CVideoCapDlg::InitDS()
{
	HRESULT hr;
	
	// Create the capture graph builder.
    VERIF(CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, 
		IID_ICaptureGraphBuilder2, (void **)&g_pCapGB));

    IEnumMoniker *pEnumCat = NULL;
	ICreateDevEnum *pSysDevEnum=NULL;

    // Instantiate the system device enumerator if it doesn't exist
    VERIF(CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC, IID_ICreateDevEnum, (void **)&pSysDevEnum));

    // Enumerate all filters of the selected category  
    VERIF(pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0));
	
	IMoniker *pMoniker=0;
	IBaseFilter *pVCap=0;
    ULONG cFetched=0;
	VARIANT varName={0};
	int nFilters=0;
	CString str;
	
	// Enumerate all items associated with the moniker
    while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
    {
        IPropertyBag *pPropBag;
        ASSERT(pMoniker);
		
        // Associate moniker with a file
        hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, 
			(void **)&pPropBag);
        ASSERT(SUCCEEDED(hr));
        ASSERT(pPropBag);
        if (FAILED(hr))
            continue;
		
        // Read filter name from property bag
        varName.vt = VT_BSTR;
        hr = pPropBag->Read(L"FriendlyName", &varName, 0);
        if (FAILED(hr))
            continue;
		
        // Get filter name (converting BSTR name to a CString)
        str=varName.bstrVal;
        SysFreeString(varName.bstrVal);
        nFilters++;
    }
	
	VERIF(pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pVCap));
	g_pVCap = pVCap;
	
	// Create the filter graph.
    VERIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void **)&g_pGB));

    // Associate the filter graph with the capture graph builder
    VERIF(g_pCapGB->SetFiltergraph(g_pGB));    

	VERIF(g_pGB->AddFilter(pVCap, L"Video Capture"));
	
	//	IBaseFilter *pCap;
	VERIF(g_pCapGB->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, pVCap, NULL, NULL));

	// QueryInterface for DirectShow interfaces
	VERIF(g_pGB->QueryInterface(IID_IMediaEventEx, (void **)&g_pME));
	VERIF(g_pGB->QueryInterface(IID_IMediaSeeking, (void **)&g_pMS));
	VERIF(g_pGB->QueryInterface(IID_IMediaPosition, (void **)&g_pMP));
	
	// Query for video interfaces, which may not be relevant for audio files
	VERIF(g_pGB->QueryInterface(IID_IVideoWindow, (void **)&g_pVW));
	VERIF(g_pGB->QueryInterface(IID_IBasicVideo, (void **)&g_pBV));
	
	// Query for audio interfaces, which may not be relevant for video-only files
	VERIF(g_pGB->QueryInterface(IID_IBasicAudio, (void **)&g_pBA));
	
	return 0;
}

LONG CVideoCapDlg::RelsDS()
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVideoCapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVideoCapDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	RelsDS();
	CoUninitialize();
}

void CVideoCapDlg::OnCapStart() 
{
	// TODO: Add your command handler code here
	if (!m_bIsInitOK)
	{
		return;
	}

	CString sFile;
	TCHAR szFilters[]= _T("Media Type Files (*.avi *.wav)|*.avi;*.wav|All Files (*.*)|*.*||");
	   
	// Create an Open dialog; the default file name extension is ".avi".
	CFileDialog fileDlg (FALSE, NULL, NULL, OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	
	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	if( fileDlg.DoModal ()==IDOK )
	{
		sFile = fileDlg.GetPathName();
		SetWindowText(sFile);
	}

	g_pGB->QueryInterface(IID_IMediaControl, (void **)&g_pMC);
	if (g_pMC)
	{
		g_pMC->Stop();
	}
	SAFE_RELEASE(g_pMC);

	IBaseFilter *pRender=NULL;
	g_pCapGB->SetOutputFileName(&MEDIASUBTYPE_Avi, sFile, &pRender, NULL);
	g_pCapGB->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, g_pVCap, NULL, pRender);

	OnPreviewStart();
}

void CVideoCapDlg::OnCapStop() 
{
	// TODO: Add your command handler code here
	if (!m_bIsInitOK)
	{
		return;
	}
	
	OnPreviewStop();
	OnPreviewStart();	
}

void CVideoCapDlg::OnPreviewStart() 
{
	// TODO: Add your command handler code here
	if (!m_bIsInitOK)
	{
		return;
	}

	RECT rcWin, rcClient;
	g_pVW->put_Owner((OAHWND)m_hWnd);    // We own the window now
	g_pVW->put_WindowStyle(WS_CHILD);    // you are now a child

	LONG lWidth, lHeight;
	g_pVW->get_Width(&lWidth);
	g_pVW->get_Height(&lHeight);
	
	// give the preview window all our space but where the status bar is
	GetWindowRect(&rcWin);
	GetClientRect(&rcClient);
	
	LONG lMenu = (rcWin.bottom-rcWin.top)-(rcClient.bottom-rcClient.top);
	rcWin.bottom = rcWin.top+lMenu+lHeight;
	rcWin.right  = rcWin.left+lWidth;
	MoveWindow(&rcWin);
	
	GetClientRect(&rcClient);
	g_pVW->SetWindowPosition(0, 0, rcClient.right, rcClient.bottom); // be this big
    g_pVW->put_Visible(OATRUE);
	
	g_pGB->QueryInterface(IID_IMediaControl, (void **)&g_pMC);
	if (g_pMC)
	{
		g_pMC->Run();
	}
	SAFE_RELEASE(g_pMC);

}

void CVideoCapDlg::OnPreviewStop() 
{
	// TODO: Add your command handler code here
	if (!m_bIsInitOK)
	{
		return;
	}
	g_pGB->QueryInterface(IID_IMediaControl, (void **)&g_pMC);
	if (g_pMC)
	{
		g_pMC->Stop();
	}
	SAFE_RELEASE(g_pMC);
}


