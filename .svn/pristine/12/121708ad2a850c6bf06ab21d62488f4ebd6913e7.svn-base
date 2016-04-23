#include "stdafx.h"
#include "GSMtestMeasLoop.h"

RF_IMPLEMENT_DYNCREATE(CGSMTestMeasureLoop)

CGSMTestMeasureLoop::CGSMTestMeasureLoop()
{
	m_mapClassFunc[_T("GSMTestMeasMainFunc")]=&CGSMTestMeasureLoop::CGSMTestMeasureLoopMainFunc;
	m_mapClassFunc[_T("MaxPower")]=&CGSMTestMeasureLoop::CGSMTestMaxPowerFunc;
}

CGSMTestMeasureLoop::~CGSMTestMeasureLoop()
{
	
}

bool CGSMTestMeasureLoop::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSMTestMeasureLoop::Handle()
{
	if(!DoProcess())
	{
      return false;
	}
		
	return true;
}

bool CGSMTestMeasureLoop::CGSMTestMeasureLoopMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CGSMTestMeasureLoop::CGSMTestMaxPowerFunc()
{
  
 
	return true;
}

 bool CGSMTestMeasureLoop::InitData(
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
   

	   itrFind=pcSettingMap->find(_T("TestBand"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TestBand' from ini file!");
		 return false;
		 
	 }
	 else
	 {
		 m_strtestBand=itrFind->second;
	 }

	 InitData();
	 return true;
 }

 bool CGSMTestMeasureLoop::InitData()
 {
	 //m_pFunGSMTestDev=m_piTesterDevice->m_piFuncGSMTest;
	 return true;
 }