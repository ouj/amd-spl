// ILPreprocessorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ILPreprocessor.h"
#include "ILPreprocessorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CILPreprocessorDlg dialog




CILPreprocessorDlg::CILPreprocessorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CILPreprocessorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CILPreprocessorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FILEPATH_EDIT, m_FilePathEdit);
    DDX_Control(pDX, IDC_CPP_ILSRC_EDIT, m_CppILSrcEdit);
}

BEGIN_MESSAGE_MAP(CILPreprocessorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_ABOUT, &CILPreprocessorDlg::OnBnClickedAbout)
    ON_BN_CLICKED(IDC_BROWSE, &CILPreprocessorDlg::OnBnClickedBrowse)
    ON_BN_CLICKED(IDC_RELOAD, &CILPreprocessorDlg::OnBnClickedReload)
    ON_BN_CLICKED(IDC_COPY_TO_CLIPBROAD, &CILPreprocessorDlg::OnBnClickedCopyToClipbroad)
END_MESSAGE_MAP()


// CILPreprocessorDlg message handlers

BOOL CILPreprocessorDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CILPreprocessorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CILPreprocessorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CILPreprocessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CILPreprocessorDlg::OnBnClickedAbout()
{
    CAboutDlg dlg;
    dlg.DoModal();
}

void CILPreprocessorDlg::OnBnClickedBrowse()
{
    CString szFilter;
    szFilter.LoadString(IDS_OPENFILE_FILTERSTRING);
    CFileDialog fileOpenDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, szFilter);
    if(fileOpenDlg.DoModal() == IDOK)
    {
        CString filePath = fileOpenDlg.GetPathName();
        m_FilePathEdit.SetWindowText(filePath);
        if (LoadILSource(filePath))
        {

            return;
        }
    }
}

bool CILPreprocessorDlg::LoadILSource(CString filePath)
{
    CStdioFile file;
    if(!file.Open(filePath, CFile::modeRead))
        return false;

    CString cppILSrc;
    cppILSrc.Empty();
    CString str;
    while (file.ReadString(str))
    {
        str.Trim();
        if (str.IsEmpty())
        {
            continue;
        }
        if (str[0] == TEXT(';'))
        {
            continue;
        }
        cppILSrc += TEXT("\"");
        cppILSrc += str;
        cppILSrc += TEXT("\\n\"\r\n");
    }
    m_CppILSrcEdit.SetWindowText(cppILSrc);

    return true;
}

void CILPreprocessorDlg::OnBnClickedReload()
{
    CString filePath;
    m_FilePathEdit.GetWindowText(filePath);

    if (!LoadILSource(filePath))
    {
        CString err;
        err.LoadString(IDS_LOAD_ILSRC_ERROR);
        AfxMessageBox(err);
    }
}

void CILPreprocessorDlg::OnBnClickedCopyToClipbroad()
{
    m_CppILSrcEdit.Copy();
}
