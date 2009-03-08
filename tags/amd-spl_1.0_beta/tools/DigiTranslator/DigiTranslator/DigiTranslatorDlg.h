// DigiTranslatorDlg.h : header file
//

#pragma once
#include "afxwin.h"

enum NUM_TYPE
{
    TYPE_FLOAT,
    TYPE_INT,
    TYPE_UINT,
    TYPE_DOUBLE,
    TYPE_SHORT,
    TYPE_USHORT
};

// CDigiTranslatorDlg dialog
class CDigiTranslatorDlg : public CDialog
{
// Construction
public:
	CDigiTranslatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DIGITRANSLATOR_DIALOG };

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
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeInputNum();

    void    ProcessingNumber(const CString& inputNum);
private:
	CEdit m_InputEdit;
	CComboBox m_TypeCombo;
	CEdit m_DecOutputEdit;
	CEdit m_HexOutputEdit;

	BYTE m_Data[sizeof(double)];

	NUM_TYPE m_CurType;
public:
    afx_msg void OnCbnSelchangeDigittype();
};
