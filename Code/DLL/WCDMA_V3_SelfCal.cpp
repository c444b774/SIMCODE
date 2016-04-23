#include "StdAfx.h"
#include "WCDMA_V3_SelfCal.h"
RF_IMPLEMENT_DYNCREATE(CWCDMA_V3_SelfCal)

CWCDMA_V3_SelfCal::CWCDMA_V3_SelfCal(void)
{
	m_mapClassFunc[_T("CWCDMA_V3_SelfCal_MainFunc")]=&CWCDMA_V3_SelfCal::CWCDMA_V3_SelfCal_MainFunc;
	m_mapClassFunc[_T("CWCDMA_V3_CAL_Self_Cal")]=&CWCDMA_V3_SelfCal::CWCDMA_V3_CAL_Self_Cal;
	
}

CWCDMA_V3_SelfCal::~CWCDMA_V3_SelfCal(void)
{
}


bool CWCDMA_V3_SelfCal::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CWCDMA_V3_SelfCal::Handle()
{
	if(!DoProcess())
	{

		m_pPhone->CloseComport();	
		return false;
	}

	CalPassLog("_","_","SelfCal_V3 Pass");

	return true;
}

bool CWCDMA_V3_SelfCal::CWCDMA_V3_SelfCal_MainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CWCDMA_V3_SelfCal::CWCDMA_V3_CAL_Self_Cal()
{
	CString strMsg;
	int iErrorcode;
	unsigned short iStatus=0; 	
	if((iErrorcode=m_pPhone->FTM_SET_Cal_STATE(1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Cal State ON  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	Sleep(m_DelaymsBeforeSelfCal);
	if((iErrorcode=m_pPhone->FTM_DO_SELFCAL(m_iCalType))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("SelfCal Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	if (m_bWriteEFS)
	{
		if((iErrorcode=m_pPhone->WriteEFS(3000))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Sync NV to EFS Fail!");
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
	}

	return true;
}

bool CWCDMA_V3_SelfCal::InitData(PCStringStrMap     pcSettingMap,CRFObjectMap&   cObjectMap)
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
	itrFind=pcSettingMap->find(_T("WriteEFS"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'WriteEFS' from ini file!.default 'true'");
		m_bWriteEFS=true;
	}
	else
	{
		m_bWriteEFS=CStr::StrToBool(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("DelayMS"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'DelayMS' from ini file!.default '3000'");
		m_DelaymsBeforeSelfCal=3000;
	}
	else
	{
		m_DelaymsBeforeSelfCal=CStr::StrToInt(itrFind->second);
	}	
	itrFind=pcSettingMap->find(_T("CalType"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'CalType' from ini file!.default '0'");
		m_iCalType=0;
	}
	else
	{
		m_iCalType=CStr::StrToInt(itrFind->second);
	}
	
	return true;
}
bool CWCDMA_V3_SelfCal::InitData()
{
	 m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	return true;
}