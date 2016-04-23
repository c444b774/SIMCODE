#pragma once
#include "afxwin.h"


// CPasswordDlg dialog

class CPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CPasswordDlg)

public:
	CPasswordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPasswordDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	bool IsPSWRgiht(){return m_bPswCorrect;}
	bool IsPSWRightEx(){return m_bPSWCorrect2;}
protected:
	CEdit m_ePSW;
	bool m_bPswCorrect;
	bool m_bPSWCorrect2;
	
public:
	afx_msg void OnEnChangePsw();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
protected:
	CStatic m_PSWSTa;
public:
	
	afx_msg void OnStnDblclickPswSta();
	afx_msg void OnBnClickedCancel();
	

};
