// ILPreprocessorDlg.h : header file
//

#pragma once
#include "string"
#include "afxwin.h"

using namespace std;

// CILPreprocessorDlg dialog
class CILPreprocessorDlg : public CDialog
{
// Construction
public:
	CILPreprocessorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ILPREPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBnClickedAbout();
    afx_msg void OnBnClickedBrowse();
    bool LoadILSource(CString filePath);
    afx_msg void OnBnClickedReload();
	DECLARE_MESSAGE_MAP()
private:
    CEdit m_FilePathEdit;
    CEdit m_CppILSrcEdit;
public:
    afx_msg void OnBnClickedCopyToClipbroad();
};
