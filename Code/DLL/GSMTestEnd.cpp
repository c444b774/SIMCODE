#include "stdafx.h"
#include "GSMTestEnd.h"

RF_IMPLEMENT_DYNCREATE(CGSMTestEnd)

CGSMTestEnd::CGSMTestEnd()
{
	m_mapClassFunc[_T("GSMEndCallMainFunc")]=&CGSMTestEnd::CGSMTestEndMainFunc;
	m_mapClassFunc[_T("GSMEndCall")]=&CGSMTestEnd::CGSMTestEndFunc;
}

CGSMTestEnd::~CGSMTestEnd()
{
	
}

bool CGSMTestEnd::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSMTestEnd::Handle()
{
	if(!DoProcess())
	{
      return false;
	}
		
	return true;
}

bool CGSMTestEnd::CGSMTestEndMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CGSMTestEnd::CGSMTestEndFunc()
{
  
  
     
	return true;
}

 bool CGSMTestEnd::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
    CStringStringMapItr itrFind;
	CString strValue;
     CString strMainFun;
	 itrFind=pcSettingMap->find(_T("MainFunc"));
	 if(itrFind==pcSettingMap->end())
		 return false;
	 else
	 {
		 if(!SetMainFunc(itrFind->second))
			 return false;
	 }

	 CString strFuncList;
	 itrFind=pcSettingMap->find(_T("List"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,_T("Not Find List"));
		 return false;
	 }
	 strFuncList=itrFind->second;
     CStringVtr strVtr;

	 CStr::ParseString(strFuncList,_T(","),strVtr);
     CString strfunc;
	 m_vFPTestFunc.clear();
	 for(CStringItr itrFunc=strVtr.begin();itrFunc!=strVtr.end();++itrFunc)
	 {
		strfunc=*itrFunc;
		map<CString,FPClassFunc>::iterator itrMap=m_mapClassFunc.find(strfunc);
		if(itrMap==m_mapClassFunc.end())
			return false;
		m_vFPTestFunc.push_back(itrMap->second);
	 }
   

	  
	 InitData();
	 return true;
 }

 bool CGSMTestEnd::InitData()
 {
	 //m_pFunGSMTestDev=m_piTesterDevice->m_piFuncGSMTest;
	 return true;
 }