// ILPreprocessor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CILPreprocessorApp:
// See ILPreprocessor.cpp for the implementation of this class
//

class CILPreprocessorApp : public CWinApp
{
public:
	CILPreprocessorApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedAbout();
};

extern CILPreprocessorApp theApp;