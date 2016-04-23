
#pragma once
#include "afxcmn.h"
#include "MyMSXML.h"
#include "SimRFCaltestUI.h"


class CPageInterface: public CPropertyPage
{

public:
	virtual void Refresh()
	{
		return;
	}
 
	virtual void EnableWindows(BOOL bEnable=TRUE)
	{
		return;
	}

	void InitializeUI()
	{
		
	}
	void GetPageName(CString & strName)
	{
      strName=m_strPageName;
	}
 
protected:
	CString m_strPageName;

public:
	CPageInterface(UINT nIDTemplate)
		: CPropertyPage(nIDTemplate)
	{
      m_strPageName="NA";
	}
	CPageInterface(const CString & strPageName)
	{
      m_strPageName=strPageName;

	}
	virtual ~CPageInterface()
	{
		return;
	}
};
