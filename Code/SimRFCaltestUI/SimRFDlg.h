#pragma once

#include "MyMSXML.h"
#include "PageInterface.h"
#include "afxcmn.h"
typedef CArray<CPageInterface*, CPageInterface*> PropertyPageAry;
class CSimRFDlg : public CDialog
{
	DECLARE_DYNAMIC(CSimRFDlg)

public:
	CSimRFDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSimRFDlg();

// Dialog Data
	enum { IDD = IDD_SIMRFCALTESTUI_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
     
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnMainDlgSize(WPARAM wParam, LPARAM lParam);
protected:
	CTabCtrl m_pagelistctrl;
public:
	virtual BOOL OnInitDialog();

	void ReSizeMainWnd(bool IsBack);

private:
	    RECT m_RectRFDlg;
		PropertyPageAry m_PageArray;
		
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
