#pragma once

#include "afxwin.h"
#include  "PageInterface.h"
// CLossConfigPage dialog

class CLossConfigPage : public CPageInterface
{


public:
	CLossConfigPage();
	virtual ~CLossConfigPage();

// Dialog Data
	enum { IDD = IDD_LOSSCONFIGPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	void Refresh();


private:
	map<CString,CWnd*> m_UICtrlListMap;
	map<CString,int>   m_pMapItemList;
	
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
