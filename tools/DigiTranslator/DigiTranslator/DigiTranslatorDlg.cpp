// DigiTranslatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DigiTranslator.h"
#include "DigiTranslatorDlg.h"

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


// CDigiTranslatorDlg dialog




CDigiTranslatorDlg::CDigiTranslatorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDigiTranslatorDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDigiTranslatorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_INPUT_NUM, m_InputEdit);
    DDX_Control(pDX, IDC_DIGITTYPE, m_TypeCombo);
    DDX_Control(pDX, IDC_DEC_OUT, m_DecOutputEdit);
    DDX_Control(pDX, IDC_HEX_OUT, m_HexOutputEdit);
}

BEGIN_MESSAGE_MAP(CDigiTranslatorDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_EN_CHANGE(IDC_INPUT_NUM, &CDigiTranslatorDlg::OnEnChangeInputNum)
    ON_CBN_SELCHANGE(IDC_DIGITTYPE, &CDigiTranslatorDlg::OnCbnSelchangeDigittype)
END_MESSAGE_MAP()


// CDigiTranslatorDlg message handlers

BOOL CDigiTranslatorDlg::OnInitDialog()
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

    m_TypeCombo.InsertString(TYPE_FLOAT, TEXT("float"));
    m_TypeCombo.InsertString(TYPE_INT, TEXT("int"));
    m_TypeCombo.InsertString(TYPE_UINT, TEXT("unsigned int"));

    m_CurType = TYPE_FLOAT;
    m_TypeCombo.SetCurSel(m_CurType);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDigiTranslatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDigiTranslatorDlg::OnPaint()
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
HCURSOR CDigiTranslatorDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CDigiTranslatorDlg::OnEnChangeInputNum()
{
    CString inputNumStr;
    m_InputEdit.GetWindowText(inputNumStr);

    ProcessingNumber(inputNumStr);
}


void CDigiTranslatorDlg::ProcessingNumber(const CString& inputNumStr)
{
    int numType = m_TypeCombo.GetCurSel();

    CString formatString;
    CString decOutStr;
    CString hexOutStr;

    if (numType == TYPE_FLOAT)
    {
        if(!_stscanf_s((LPCTSTR)inputNumStr, TEXT("%f"), m_Data))
        {
            decOutStr = TEXT("#####");
        }
        else
        {
            decOutStr.Format(TEXT("%f"), *((float*)m_Data));
        }
    }
    else if (numType == TYPE_INT)
    {
        if(!_stscanf_s((LPCTSTR)inputNumStr, TEXT("%d"), m_Data))
        {
            decOutStr = TEXT("#####");
        }
        else
        {
            decOutStr.Format(TEXT("%d"), *((int*)m_Data));
        }
    }
    else if (numType == TYPE_UINT)
    {
        if(!_stscanf_s((LPCTSTR)inputNumStr, TEXT("%u"), m_Data))
        {
            decOutStr = TEXT("#####");
        }
        else
        {
            decOutStr.Format(TEXT("%u"), *((unsigned int*)m_Data));
        }
    }
    else
    {
        decOutStr = TEXT("#####");
    }

    if (decOutStr != TEXT("#####"))
    {
        TCHAR hexDigiStr[32];
        _stprintf(hexDigiStr, TEXT("%.8X"), *((unsigned int*)m_Data));
        hexOutStr = hexDigiStr;
    }
    else
    {
        hexOutStr = TEXT("#####");
    }

    m_HexOutputEdit.SetWindowText(TEXT("0x") + hexOutStr);
    m_DecOutputEdit.SetWindowText(decOutStr);
}
void CDigiTranslatorDlg::OnCbnSelchangeDigittype()
{
    OnEnChangeInputNum();
}
