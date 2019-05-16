// TestHfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestHf.h"
#include "TestHfDlg.h"
#include "Picture.h"
#include "quwu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString  FilePathName;

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
// CTestHfDlg dialog

CTestHfDlg::CTestHfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestHfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestHfDlg)
	m_Block = _T("");
	m_w = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestHfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestHfDlg)
	DDX_Control(pDX, IDC_SLIDER2, m_Slider2);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider1);
	DDX_Text(pDX, IDC_STATIC3, m_Block);
	DDX_Text(pDX, IDC_STATIC4, m_w);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestHfDlg, CDialog)
	//{{AFX_MSG_MAP(CTestHfDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestHfDlg message handlers

BOOL CTestHfDlg::OnInitDialog()
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
	m_Slider1.SetRange(1,10);
    m_Slider1.SetTicFreq(1);
	m_Slider2.SetRange(0,10);
    m_Slider2.SetTicFreq(1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestHfDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestHfDlg::OnPaint() 
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
HCURSOR CTestHfDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestHfDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CRect rect;
	CPicture m_Pic;

	 GetDlgItem(IDC_SHOWPIC)->GetWindowRect(&rect);
	 ScreenToClient(&rect);
 
	 CFile f;
	 CFileException e;
	 CFileDialog dlg(TRUE,NULL,NULL,0,_T("All Files (*.*)|*.*|BMP (*.bmp)|*.bmp|DIB (*.dib)|*.dib|EMF (*.emf)|*.emf|GIF (*.gif)|*.gif|ICO (*.ico)|*.ico|JPG (*.jpg)|*.jpg|WMF (*.wmf)|*.wmf||"),NULL);
	 if(dlg.DoModal()==IDOK)
	 {
		  FilePathName=dlg.GetPathName();
		  if(m_Pic.m_IPicture != NULL) m_Pic.FreePictureData(); 
		  m_Pic.Load(FilePathName);
		  CClientDC dc(this);
		  m_Pic.UpdateSizeOnDC(&dc); 
		  m_Pic.Show(&dc, &rect);
		  //IplImage *quw(CString srcFile,int block,double w);
		  UpdateData(TRUE); 
		  m_Slider1.SetPos(1);
		
         
	 }
	
}

void CTestHfDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CRect rect;
	CPicture m_Pic;
    quw(FilePathName, atoi(m_Block), atof(m_w));

	 GetDlgItem(IDC_SHOWPIC1)->GetWindowRect(&rect);
	 ScreenToClient(&rect);
	 if(m_Pic.m_IPicture != NULL) m_Pic.FreePictureData(); 
	 m_Pic.Load(DES_FILE);
	 CClientDC dc(this);
	 m_Pic.UpdateSizeOnDC(&dc); 
	 m_Pic.Show(&dc, &rect);
	
}

void CTestHfDlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	char buf[32];
	UpdateData(TRUE);
	
	itoa(m_Slider1.GetPos(), buf, 10);
	m_Block=CString(buf);
	UpdateData(FALSE); 

	
	*pResult = 0;
}

void CTestHfDlg::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int a;
	double b;
	UpdateData(TRUE);
	a = m_Slider2.GetPos();
	b = (double)a*1.0/10.0;
	
	m_w.Format("%0.1f", b);
	UpdateData(FALSE); 
	*pResult = 0;
}
