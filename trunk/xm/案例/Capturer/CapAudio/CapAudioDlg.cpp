// CapAudioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CapAudio.h"
#include "CapAudioDlg.h"

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
	CMenu m_MyMenu;
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
// CCapAudioDlg dialog

CCapAudioDlg::CCapAudioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCapAudioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCapAudioDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCapAudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCapAudioDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCapAudioDlg, CDialog)
	//{{AFX_MSG_MAP(CCapAudioDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENUITEM_StartView, OnMENUITEMStartView)
	ON_COMMAND(ID_MENUITEM_StopView, OnMENUITEMStopView)
	ON_COMMAND(ID_MENUITEM_StartCapture, OnMENUITEMStartCapture)
	ON_COMMAND(ID_MENUITEM_StopCapture, OnMENUITEMStopCapture)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCapAudioDlg message handlers

BOOL CCapAudioDlg::OnInitDialog()
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
	ShowWindow(SW_HIDE);
	m_MyMenu.LoadMenu(IDR_MENU1);
	SetMenu(&m_MyMenu);


    HRESULT hr;

	CoInitialize(NULL);
	
    // Create the capture graph builder.
    hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, 
		IID_ICaptureGraphBuilder2, (void **)&m_pCapture);
    if (FAILED(hr) || !m_pCapture)
        return E_NOINTERFACE;
	

    IEnumMoniker *pEnumCat = NULL;
	ICreateDevEnum *pSysDevEnum=NULL;
	
    // Instantiate the system device enumerator if it doesn't exist
    if (pSysDevEnum == NULL)
    {
        hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, 
			CLSCTX_INPROC, IID_ICreateDevEnum, 
			(void **)&pSysDevEnum);
        if FAILED(hr)
            return hr;
    }
	
    // Enumerate all filters of the selected category  
    hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);

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

	hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pVCap); 

	// Create the filter graph.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
		IID_IGraphBuilder, (void **)&m_pGB);
    if (FAILED(hr) || !m_pGB)
        return E_NOINTERFACE;
	
    // Associate the filter graph with the capture graph builder
    hr = m_pCapture->SetFiltergraph(m_pGB);    
    if (FAILED(hr))
        return hr;

	hr = m_pGB->AddFilter(pVCap, L"Video Capture");

	//	IBaseFilter *pCap;
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, pVCap, NULL, NULL);

	IBaseFilter *pRender=NULL;

	m_pCapture->SetOutputFileName(&MEDIASUBTYPE_Avi, _T("D:\\xYx.avi"), &pRender, NULL);


	hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, pVCap, NULL, pRender);

	
	REFERENCE_TIME start = 0x7FFFFFFFFFFFFFFF, stop = 0x7FFFFFFFFFFFFFFF;
	
    // don't capture quite yet...
  //  hr = m_pCapture->ControlStream(&PIN_CATEGORY_CAPTURE, NULL,
  //                                    NULL, &start, NULL, 0, 0);

	hr = m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC);
	hr = m_pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW);

	INT cy, cyBorder;
	RECT rc;
	pVW->put_Owner((OAHWND)m_hWnd);    // We own the window now
	pVW->put_WindowStyle(WS_CHILD);    // you are now a child

	long lWidth, lHeight;
	pVW->get_Width(&lWidth);
	pVW->get_Height(&lHeight);

	CString s;
	s.Format(_T("w: %d, h: %d"), lWidth, lHeight);
	AfxMessageBox(s);
	// give the preview window all our space but where the status bar is
	GetClientRect(&rc);
	
	pVW->SetWindowPosition(0, 0, rc.right, rc.bottom); // be this big
    pVW->put_Visible(OATRUE);

	hr = m_pMC->Run();


	IEnumFilters *pEnum = NULL;
    IBaseFilter *pFilter = NULL;
    BOOL bFound = FALSE;
	
    // Verify graph builder interface
    if (!m_pGB)
        return NULL;
	
    // Get filter enumerator
    hr = m_pGB->EnumFilters(&pEnum);
    if (FAILED(hr))
        return NULL;
	
	CString sName;
    // Enumerate all filters in the graph
    while((pEnum->Next(1, &pFilter, &cFetched) == S_OK) && (!bFound))
    {
        FILTER_INFO FilterInfo;
        TCHAR szName[256];
        
        hr = pFilter->QueryFilterInfo(&FilterInfo);
        if (FAILED(hr))
        {
            pFilter->Release();
            pEnum->Release();
            return NULL;
        }
		
        // Compare this filter's name with the one we want
        sName = FilterInfo.achName;
        szName[255] = 0;        // NULL-terminate
		
        // If the name matches, we have found the requested filter        
    //    if (! lstrcmp(szName, szNameToFind))
  //          bFound = TRUE;
		
        FilterInfo.pGraph->Release();
		
        // If we found the right filter, don't release its interface.
        // The caller will use it and release it later.
        if (!bFound)
            pFilter->Release();
        else
            break;
    }
	
	CenterWindow();
	ShowWindow(SW_SHOW);


	SetTimer(1, 20000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCapAudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCapAudioDlg::OnPaint() 
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
HCURSOR CCapAudioDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CCapAudioDlg::OnMENUITEMStartView() 
{
	// TODO: Add your command handler code here
//	AfxMessageBox(_T()"startview");

	IGraphBuilder *pGb = NULL;
	ICaptureGraphBuilder2 *pCapGb2 = NULL;

	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)pCapGb2);
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGb);
		if (SUCCEEDED(hr))
		{
			pCapGb2->SetFiltergraph(pGb);
		}
		else
		{
			pCapGb2->Release();
		}
	}


}

void CCapAudioDlg::OnMENUITEMStopView() 
{
	// TODO: Add your command handler code here
//	AfxMessageBox("stopview");
}

void CCapAudioDlg::OnMENUITEMStartCapture() 
{
	// TODO: Add your command handler code here
//	AfxMessageBox("startcapture");
}

void CCapAudioDlg::OnMENUITEMStopCapture() 
{
	// TODO: Add your command handler code here
//	AfxMessageBox("stopcapture");
}

void CCapAudioDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	// stop the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = m_pGB->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Stop();
        pMC->Release();
    }
    if(FAILED(hr))
    {
        return;
    }
	KillTimer(1);
	CDialog::OnTimer(nIDEvent);

	AfxMessageBox(_T("OK"));
}
