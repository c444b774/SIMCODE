#include "stdafx.h"
#include "IntelliCeiverCal.h"
RF_IMPLEMENT_DYNCREATE(CIntelliCeivierCal)

CIntelliCeivierCal::CIntelliCeivierCal()
{
	m_mapClassFunc[_T("InterCelMainFunc")]=&CIntelliCeivierCal::CIntelliCeivierCalMainFunc;
	m_mapClassFunc[_T("InterCelFunc")]=&CIntelliCeivierCal::CIntelliCeivierCalFunc;
}

CIntelliCeivierCal::~CIntelliCeivierCal()
{
	
}

bool CIntelliCeivierCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CIntelliCeivierCal::Handle()
{
	if(!DoProcess())
	{
        m_pPhone->CloseComport();
		m_pFunWCDMACalDev->Deivce_Exit();
		return false;
	}

	CalPassLog("_","_","IntelliCeiver Cal Pass");

	return true;
}

bool CIntelliCeivierCal::CIntelliCeivierCalMainFunc()
{
	switch(m_iCurrBand)
	{
	case CDMA_BC0_BAND_ID:
		m_iPhoneMode=CCDMABandInfo::GetPhoneMode(CDMA_BC0_BAND_ID);
        m_iNVModeID=100;
		break;
	case CDMA_BC1_BAND_ID:
		m_iPhoneMode=CCDMABandInfo::GetPhoneMode(CDMA_BC1_BAND_ID);
        m_iNVModeID=101;
		break;
	default:
		break;
	
	}
	SetCDMACALLOSS();

	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CIntelliCeivierCal::SetCDMACALLOSS()
{
	  CString strMsg;
     double dLoss;
	 m_vCableLoss.clear();
    for(int i=0;i<3;i++)
	{
		if(!m_LossFinder.GetCDMALoss(m_strCurrBand,i,dLoss))
	  {
		  strMsg.Format("CDMA Get Loss Band=%s ,ChannelT pe=%d Fail",m_strCurrBand,i);
          LogTrace(MSG_ERROR,strMsg);
		  CalFailLog(_T("_"),_T("_"),LOSS_NOT_FIND,strMsg);
		  return false;
	  }
	  m_vCableLoss.push_back(dLoss);
	}


      
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSetLoss(m_iCurrBand,m_vCableLoss))
	   {
			LogTrace(MSG_ERROR,"Set Cableloss device fail");
			CalFailLog(_T("_"),_T("_"),LOSS_SET_FAIL,"Set Cableloss device fail");
			return false;
		  
	   }
        



	return  true;

	return true;
}
bool CIntelliCeivierCal::CIntelliCeivierCalFunc()
{
  
    CString strMsg;
    int iErrorcode;

	 QMSL_CDMA_Intelliceiver_Value  aiQMSL_CDMA_Intelliceiver_Value;

	  QMSL_RFCAL_NV_Item  aiQMSL_RFCAL_NV_Item;
    double dUlMHz,dDLMhz;
    //iDLChannel=CCDMABandInfo::GetDLChannel(m_iCurrBand,m_iChannel);
    dUlMHz=CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_iChannel,0);
	dDLMhz=CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_iChannel,1);
    short iConvertAGC;
	unsigned short uiDVGAList[128];
	unsigned char aiBLOBData[128];
    unsigned char  ucCount=m_ivRxPM.size();
	unsigned char ucIntelliCount=128;
    short sDVGAAGC=-512 + 10*(m_dDVGARXPower-m_dMinRSSI);
	short sIntelliAGC=-512 + 10*(m_dIntelliRXLevel-m_dMinRSSI);
    
    if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSetNormalSig(dUlMHz,dDLMhz,0,m_dDVGARXPower,m_strWaveFile))
	   {
			LogTrace(MSG_ERROR,"Set Normal CDMA200 signal fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set Normal CDMA200 signal fail");
			return false;
		  
	   }
     
	 if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(0))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_MODE_ID Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	  if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iPhoneMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_MODE Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	  if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(m_iRXPath))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	

	 if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_iChannel))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_CHAN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	 
	 if((iErrorcode=m_pPhone->FTM_CDMA_API2_CALIBRATE_DVGA(m_iRXPath,sDVGAAGC,&ucCount,uiDVGAList))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_CDMA_API2_CALIBRATE_DVGA Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
     for(int i=0;i<ucCount;++i)
	 {
		  if(uiDVGAList[i] & 0x8000)  //if it is minus 
                iConvertAGC=0-(0xffff-uiDVGAList[i]);
			 else
				iConvertAGC=uiDVGAList[i];
		 strMsg.Format("DVGA[%d]=%d",i,iConvertAGC);
		 LogTrace(MSG_MID,strMsg);
	 }

     if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetXOSig(dUlMHz,dDLMhz,m_dIntelliFreqOffsetKhz,m_dIntelliRXLevel))
	   {
			LogTrace(MSG_ERROR,"Set CW signal fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set CW signal fail");
			return false;
		  
	   }

	  if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iPhoneMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_MODE Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	 if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_iChannel))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_CHAN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	 if((iErrorcode=m_pPhone->FTM_SET_LNA_RANGE(m_iIntelliLNARange))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_LNA_RANGE Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	  if((iErrorcode=m_pPhone->FTM_CDMA_API2_CALIBRATE_INTELLICEIVER(m_iRXPath,sIntelliAGC,&ucIntelliCount,aiBLOBData))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_CDMA_API2_CALIBRATE_INTELLICEIVER Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

    

	memcpy(aiQMSL_CDMA_Intelliceiver_Value.aiIntelliceiverValue,aiBLOBData,sizeof(aiBLOBData));
    aiQMSL_CDMA_Intelliceiver_Value.iSizeOfIntelliceiverValue=ucIntelliCount;
	 if((iErrorcode=m_pPhone->RFCAL_Rx_Intellieceiver_Cal_Results(m_iNVModeID,&aiQMSL_CDMA_Intelliceiver_Value,&aiQMSL_RFCAL_NV_Item,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_Rx_Intellieceiver_Cal_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	 }  

   
	return true;
}

 bool CIntelliCeivierCal::InitData(
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

	 itrFind=pcSettingMap->find(_T("WaveFilePath"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'WaveFilePath' from ini file!.Default is \'D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\CDMA_DL.wv\'");
		 m_strWaveFile="D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\CDMA_DL.wv";
	 }
	 else
	 {

		 m_strWaveFile=itrFind->second;
	 }

	  itrFind=pcSettingMap->find(_T("RXPath"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RXPath' from ini file!.default use 0");
		 m_iRXPath=0;
	 }
	 else
	 {
		 m_iRXPath=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("Channel"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'Channel' ");
		 return false;
	 }
	 else
	 {
		 m_iChannel=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("Band"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'Band' ");
		 return false;
	 }
	 else
	 {
		 m_iCurrBand=CStr::StrToInt(itrFind->second);
		  m_strCurrBand="CDMA"+itrFind->second;
	 }

	 itrFind=pcSettingMap->find(_T("MinRSSI"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'MinRSSI' ");
		 return false;
	 }
	 else
	 {
		 m_dMinRSSI=CStr::StrToFloat(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("DynamicRange"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DynamicRange' ");
		 return false;
	 }
	 else
	 {
		 m_dDyRange=CStr::StrToFloat(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("DVGARXPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DVGARXPower' ");
		 return false;
	 }
	 else
	 {
		  m_dDVGARXPower=CStr::StrToFloat(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("RxPM"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RxPM' from ini file!");
		 strValue="0,1";
		 CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_ivRxPM,strVtr);;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_ivRxPM,strVtr);
	 }

		 
	  itrFind=pcSettingMap->find(_T("LNARange"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'LNARange' ");
		 return false;
	 }
	 else
	 {
		 m_iIntelliLNARange=CStr::StrToInt(itrFind->second);
	 }
       
	 
	  itrFind=pcSettingMap->find(_T("FreqOffsetKHz"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'FreqOffsetKHz' ");
		 return false;
	 }
	 else
	 {
		 m_dIntelliFreqOffsetKhz=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("IntelliRXPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'IntelliRXPower' ");
		 return false;
	 }
	 else
	 {
		 m_dIntelliRXLevel=CStr::StrToFloat(itrFind->second);
	 }
     CString strCloseMaxLimit,strCloseMinLimit,strFarMaxLimit,strFarMinLimit;
     CStringVtr strVtr1,strVtr2;
	 CStringItr itrTemp1,itrTemp2;
	 CRangePair<int> limitpair;
	 itrFind=pcSettingMap->find(_T("CloseMaxlimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'CloseMaxlimit' ");
		 return false;
	 }
	 else
	 {
		 strCloseMaxLimit=itrFind->second;
	 }

	 itrFind=pcSettingMap->find(_T("CloseMinlimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'CloseMinlimit' ");
		 return false;
	 }
	 else
	 {
		 strCloseMinLimit=itrFind->second;
	 }
	  CStr::ParseString(strCloseMaxLimit,",",strVtr1);
      CStr::ParseString(strCloseMinLimit,",",strVtr2);
	  m_vrCloseLimit.clear();
	  if(strVtr1.size()!=strVtr2.size())
	  {
         LogTrace(MSG_ERROR,"CloseMaxlimit Size not equal to CloseMinlimit! ");
		 return false;
	  }
	  for(itrTemp1=strVtr1.begin(),itrTemp2=strVtr2.begin();itrTemp1!=strVtr1.end();++itrTemp1,++itrTemp2)
	  {
		  limitpair.SetRange(CStr::StrToInt(*itrTemp1),CStr::StrToInt(*itrTemp2));
		  m_vrCloseLimit.push_back(limitpair);  
	  }


	  itrFind=pcSettingMap->find(_T("FarMaxlimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'FarMaxlimit' ");
		 return false;
	 }
	 else
	 {
		 strFarMaxLimit=itrFind->second;
	 }

	 itrFind=pcSettingMap->find(_T("FarMinlimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'FarMinlimit' ");
		 return false;
	 }
	 else
	 {
		 strFarMinLimit=itrFind->second;
	 }
	  CStr::ParseString(strFarMaxLimit,",",strVtr1);
      CStr::ParseString(strFarMinLimit,",",strVtr2);
	  m_vrCloseLimit.clear();
	  if(strVtr1.size()!=strVtr2.size())
	  {
         LogTrace(MSG_ERROR,"FarMaxlimit Size not equal to FarMinlimit! ");
		 return false;
	  }
	  for(itrTemp1=strVtr1.begin(),itrTemp2=strVtr2.begin();itrTemp1!=strVtr1.end();++itrTemp1,++itrTemp2)
	  {
		  limitpair.SetRange(CStr::StrToInt(*itrTemp1),CStr::StrToInt(*itrTemp2));
		  m_vrFarLimit.push_back(limitpair);  
	  }

   

	 InitData();
	 return true;
 }

 bool CIntelliCeivierCal::InitData()
 {
	 m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	 return true;
 }