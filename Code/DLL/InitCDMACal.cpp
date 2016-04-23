#include "stdafx.h"
#include "InitCDMACal.h"
RF_IMPLEMENT_DYNCREATE(CInitCDMACal)

CInitCDMACal::CInitCDMACal()
{
	m_mapClassFunc[_T("InitCDMACalMainFunc")]=&CInitCDMACal::CInitCDMACalMainFunc;
	m_mapClassFunc[_T("InitCDMACalFunc")]=&CInitCDMACal::CInitCDMACalFunc;
}

CInitCDMACal::~CInitCDMACal()
{
	
}

bool CInitCDMACal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CInitCDMACal::Handle()
{
	if(!DoProcess())
	{

		m_pPhone->CloseComport();
		m_pFunWCDMACalDev->Deivce_Exit();
		return false;
	}

    
	CalPassLog("_","_","Init CDMA Cal Pass");

	return true;
}

bool CInitCDMACal::CInitCDMACalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CInitCDMACal::CInitCDMACalFunc()
{
  
    CString strMsg;
    int iErrorcode;
    LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}



     
			/*	 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
		{           LogTrace(MSG_ERROR,_T("Phone Enter OnlineMode Fail!"))
					m_iErrorcode=iErrorcode;

					CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
					return false;
		}*/
/*
		unsigned long iPhonemode;

		if((iErrorcode=m_pPhone->GetPhoneMode(&iPhonemode))!=PHONE_SUCCESS)
		{           LogTrace(MSG_ERROR,_T("Get Phone Mode Fail!"))
		m_iErrorcode=iErrorcode;

		CalFailLog(_T("_"),_T("_"),iErrorcode,"Get Phone Mode Fail!!");
		return false;
		}

		if (iPhonemode!=SYS_OPRT_MODE_ONLINE)
		{
			if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
			{           LogTrace(MSG_ERROR,_T("Phone Enter FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;

			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
			return false;
			}

		}*/

			 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
		{           LogTrace(MSG_ERROR,_T("Phone Enter FTM Mode Fail!"))
					m_iErrorcode=iErrorcode;

					CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
					return false;
		}

			 if((iErrorcode=m_pPhone->FTM_SET_CALIBRATION_STATE())!=PHONE_SUCCESS)
			 { 
				 strMsg.Format("SET_CALIBRATION_STATE Fail!");
				 PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			 }

     LogTrace(MSG_MID,_T("Init Device....!"))
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalInit(m_strDeviceAddrCurr))
	   {
			LogTrace(MSG_ERROR,"Init WCDMA device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Init WCDMA device fail");
			return false;
		  
	   }

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->SetInput(m_iInPortOutPort))
	   {
			LogTrace(MSG_ERROR,"WCDMA device Set input port fail");
			CalFailLog(_T("_"),_T("_"),1001,"WCDMA device Set input port fail");
			return false;
		  
	   }

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->SetOutput(m_iInPortOutPort))
	   {
			LogTrace(MSG_ERROR,"WCDMA device Set out port fail");
			CalFailLog(_T("_"),_T("_"),1001,"WCDMA device Set out port fail");
			return false;
		  
	   }

   
	return true;
}

 bool CInitCDMACal::InitData(
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
 
      itrFind=pcSettingMap->find(_T("WCDMACalDevicePort"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'WCDMACalDevicePort' from ini file!.default use pre config");
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

	 InitData();
	 return true;
 }

 bool CInitCDMACal::InitData()
 {
	 m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	 return true;
 }