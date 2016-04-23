#include "stdafx.h"
#include "InitGSMCal.h"
RF_IMPLEMENT_DYNCREATE(CInitCGSMCal)

CInitCGSMCal::CInitCGSMCal()
{
	m_mapClassFunc[_T("InitGSMCalMainFunc")]=&CInitCGSMCal::CInitCGSMCalMainFunc;
	m_mapClassFunc[_T("InitGSMCalFunc")]=&CInitCGSMCal::CInitCGSMCalCalFunc;
	m_mapClassFunc[_T("InitGSMCalFunc6285")]=&CInitCGSMCal::CInitCGSMCalCalFunc6285;
}

CInitCGSMCal::~CInitCGSMCal()
{
	
}

bool CInitCGSMCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CInitCGSMCal::Handle()
{
	if(!DoProcess())
	{

		m_pPhone->CloseComport();
		m_pFunGSMCalDev->Deivce_Exit();
		return false;
	}

    
	CalPassLog("_","_","Init GSM Cal Pass");

	return true;
}

bool CInitCGSMCal::CInitCGSMCalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CInitCGSMCal::CInitCGSMCalCalFunc6285()
{
  
    CString strMsg;
    int iErrorcode;
    LogTrace(MSG_MID,_T(" Open Comport...."))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}


		 if((iErrorcode=m_pPhone->FTM_Init6285())!=PHONE_SUCCESS)
		{           LogTrace(MSG_ERROR,_T("FTM_Init6285"))
					m_iErrorcode=iErrorcode;

					CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
					return false;
		}
     
				 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
		{           LogTrace(MSG_ERROR,_T("Phone Enter OnlineMode Fail!"))
					m_iErrorcode=iErrorcode;

					CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
					return false;
		}

			 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
		{           LogTrace(MSG_ERROR,_T("Phone Enter FTM Mode Fail!"))
					m_iErrorcode=iErrorcode;

					CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
					return false;
		}
		


     LogTrace(MSG_MID,_T("Init Device...."))
		if((iErrorcode=m_pFunGSMCalDev->IGSMCalInit(m_strDeviceAddrCurr))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Init GSM  device fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Init GSM device fail");
			return false;
		  
	   }

		if((iErrorcode=m_pFunGSMCalDev->SetInput(m_iInPortOutPort))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"GSM device Set input port fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM device Set input port fail");
			return false;
		  
	   }

		if((iErrorcode=m_pFunGSMCalDev->SetOutput(m_iInPortOutPort))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"GSM device Set out port fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM device Set out port fail");
			return false;
		  
	   }

   
	return true;
}



bool CInitCGSMCal::CInitCGSMCalCalFunc()
{
  
    CString strMsg;
    int iErrorcode;
    LogTrace(MSG_MID,_T(" Open Comport...."))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}



     if (m_isPreOnlineToFTM)
     {
		 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
		 {           LogTrace(MSG_ERROR,_T("Phone Enter OnlineMode Fail!"))
		 m_iErrorcode=iErrorcode;

		 CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter online Mode Fail!");
		 return false;
		 }
     }
	

			 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
		{           LogTrace(MSG_ERROR,_T("Phone Enter FTM Mode Fail!"))
					m_iErrorcode=iErrorcode;

					CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
					return false;
		}
     LogTrace(MSG_MID,_T("Init Device...."))
		if((iErrorcode=m_pFunGSMCalDev->IGSMCalInit(m_strDeviceAddrCurr))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Init GSM  device fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Init GSM device fail");
			return false;
		  
	   }

		if((iErrorcode=m_pFunGSMCalDev->SetInput(m_iInPortOutPort))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"GSM device Set input port fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM device Set input port fail");
			return false;
		  
	   }

		if((iErrorcode=m_pFunGSMCalDev->SetOutput(m_iInPortOutPort))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"GSM device Set out port fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM device Set out port fail");
			return false;
		  
	   }

   
	return true;
}

 bool CInitCGSMCal::InitData(
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
 
      itrFind=pcSettingMap->find(_T("GSMCalDevicePort"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'GSMCalDevicePort' from ini file!.default use pre config");
		 m_iInPortOutPort=m_piTesterDeviceCurr->m_iInputPort;
	 }
	 else
	 {
		 m_iInPortOutPort=CStr::StrToInt(itrFind->second);
	 }

      itrFind=pcSettingMap->find(_T("TesterDeviceUse"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not find TestDeviceUse,use TesterDeviceCommon");
		 //return false;
		 m_piTesterDeviceCurr=m_piTesterDevice;
		 m_strTesterDeviceCurr=m_strTesterDevice;
		 m_strDeviceAddrCurr=m_strDeviceAddr;
	 }
	 else
	 {
		 if(itrFind->second=="TesterDeviceCommon")
		 {
			 m_piTesterDeviceCurr=m_piTesterDevice;
			 m_strTesterDeviceCurr=m_strTesterDevice;
			 m_strDeviceAddrCurr=m_strDeviceAddr;
		 }
	 }

	 itrFind=pcSettingMap->find(_T("PreOnlineToFTM"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,_T("Not Find PreOnlineToFTM,Use default 0"));
		 m_isPreOnlineToFTM=0;
	 }
	 else
		 m_isPreOnlineToFTM=CStr::StrToInt(itrFind->second);	

	 InitData();
	 return true;
 }

 bool CInitCGSMCal::InitData()
 {
	 m_pFunGSMCalDev=m_piTesterDevice->m_piFuncGSMCal;
	 return true;
 }