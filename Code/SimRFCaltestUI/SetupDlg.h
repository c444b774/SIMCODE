#pragma once
#include "FolderDlg.h"
#include "afxwin.h"

// CSetupDlg dialog

class CSetupDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetupDlg)

public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetupDlg();

// Dialog Data
	enum { IDD = IDD_Setup };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3();
protected:
	CListBox m_listProcessAll;
	CListBox m_listProcessEnable;

	bool m_bChangeProcess;
public:
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton10();
};
