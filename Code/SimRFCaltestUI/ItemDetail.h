#pragma once

#include "SimRFCaltestUI.h"
// CItemDetail dialog
typedef map<CString,CWnd*> CStringWndMap;
typedef CStringWndMap::iterator CStringWndMapItr;
typedef vector<CWnd*> VtrStaticWnd;
class CItemDetail : public CDialog
{
	DECLARE_DYNAMIC(CItemDetail)

public:
	CItemDetail(CWnd* pParent = NULL);   // standard constructor
	virtual ~CItemDetail();
	

	void SetDataMap(const CStringPairVtr & vtrData){m_MapData=vtrData;}
	void SetItemString(const CString & strName){m_strItemName=strName;}
// Dialog Data
	enum { IDD = IDD_ITEMDETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
    CStringPairVtr m_MapData;
	CString m_strItemName;

     CStringWndMap m_UICtrlistMap;
	 VtrStaticWnd m_StaticList;
public:
	virtual BOOL OnInitDialog();
};
