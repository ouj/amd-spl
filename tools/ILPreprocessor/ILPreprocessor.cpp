// ILPreprocessor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ILPreprocessor.h"
#include "ILPreprocessorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CILPreprocessorApp

BEGIN_MESSAGE_MAP(CILPreprocessorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CILPreprocessorApp construction

CILPreprocessorApp::CILPreprocessorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CILPreprocessorApp object

CILPreprocessorApp theApp;


// CILPreprocessorApp initialization

BOOL CILPreprocessorApp::InitInstance()
{
	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CILPreprocessorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
