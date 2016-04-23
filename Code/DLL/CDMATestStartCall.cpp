#include "stdafx.h"
#include "CDMATestStartCall.h"

RF_IMPLEMENT_DYNCREATE(CCDMATestStartCall)

CCDMATestStartCall::CCDMATestStartCall()
{
	m_mapClassFunc[_T("CDMACallMainFunc")]=&CCDMATestStartCall::CCDMATestStartCallMainFunc;
	m_mapClassFunc[_T("CDMA_NS_Call")]=&CCDMATestStartCall::CCDMATest_NS_StartCallFunc;
}

CCDMATestStartCall::~CCDMATestStartCall()
{
	
}

bool CCDMATestStartCall::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CCDMATestStartCall::Handle()
{
	if((!DoProcess())||(m_iFailFlag!=0))
	{
      return false;
	}
		
	return true;
}

bool CCDMATestStartCall::CCDMATestStartCallMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CCDMATestStartCall:: CCDMATest_NS_StartCallFunc()
{
	int iDLChannel;
	int iErrorcode;
	CString strMsg,strESN;
	iDLChannel=CCDMABandInfo::GetDLChannel(m_iCallBand,m_iCallULChannel);

	m_iItemCode=CDMA_TestTestCall_BaseItemCode;
	m_pPhone->CloseComport();
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		m_iFailFlag++;
		return false;
	}


	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Set Phone FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("Set Phone FTM Mode Fail!"))
			return false;
	}
	
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestInitCDMANStest(m_strDeviceAddr,m_strWavefile))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("CDMA NonSignaling Test InitDev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),m_iErrorcode,_T("InitDev Fail!"))
					m_iFailFlag++;
			return false;
	}
	CalPassLog(_T("-"),_T("-"),_T("InitDev Pass!"))

	iErrorcode=m_pPhone->DIAG_READ_ESN_F(strESN);
	iErrorcode=m_pFunCDMATestDev->ICDMATestSetESN(strESN);
	if(iErrorcode!=DEVICE_SUCCESS)
	{
		strMsg.Format("DevSetESN Fail,ESN:%s",strESN);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("DevSetESN Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunCDMATestDev->ICDMATestHandover(m_iCallBand,m_iCallULChannel))!=DEVICE_SUCCESS)
	{
		strMsg.Format("DevHandOver Fail,Band:%d,Channel:%d",m_iCallBand,m_iCallULChannel);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("DevHandOver Fail!"))
					m_iFailFlag++;
			return false;
	}

	iErrorcode=m_pPhone->FTM_CDMA_BER_Handover(1,0,m_iCallBand,m_iCallULChannel,0,FTM_CDMA2000_NS_RC_1);
	if(iErrorcode!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("FTM_CDMA2000_NS_Start fail"))
					m_iFailFlag++;
		return false;
	}

	CalPassLog(CStr::IntToStr(m_iCallBand),CStr::IntToStr(m_iCallULChannel),_T("StartCall Pass!"))
	return true;
}

 bool CCDMATestStartCall::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
    CStringStringMapItr itrFind;
	CString strValue,strTemp;
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
   

	   itrFind=pcSettingMap->find(_T("CALLBand"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'CALLBand' from ini file!");
		 return false;
		 
	 }
	 else
	 {
		 strValue=itrFind->second;
		 if (!strcmp(strValue,"800"))
		 {
			 m_strCallBand=_T("800");
			 m_iCallBand=CDMA_BC0_BAND_ID;
		 }
		 else if(!strcmp(strValue,"1900"))
		 {
			 m_strCallBand=_T("1900");
			 m_iCallBand=CDMA_BC1_BAND_ID;
		 }
		 if (m_iCallBand!=CDMA_BC0_BAND_ID && m_iCallBand!=CDMA_BC1_BAND_ID)
		 {
			 strTemp.Format("Band=%s,not support yet",strValue);
			 LogTrace(MSG_ERROR,_T(strTemp));
			 return false;
		 }
	 }


	 itrFind=pcSettingMap->find(_T("CALLChannel"));

	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'CALLChannel' from ini file!");
		 return false;

	 }
	 else
	 {
		 m_iCallULChannel=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("RadioConfig"));

	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RadioConfig' from ini file!");
		 return false;

	 }
	 else
	 {
		 m_iRadioConfig=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("CellPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'CellPower' from ini file,Use default -75 dBm!");
		 m_dCallCellPower=-75;

	 }
	 else
	 {
		 m_dCallCellPower=CStr::StrToFloat(itrFind->second);

	 }
	 itrFind=pcSettingMap->find(_T("TargetPower"));

	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TargetPower' from ini file,Use default -10 dBm!");
		 m_dCallTargetPower=-10;

	 }
	 else
	 {
		 m_dCallTargetPower=CStr::StrToFloat(itrFind->second);

	 }
	 itrFind=pcSettingMap->find(_T("BERSessionTimeOut"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'BERSessionTimeOut' from ini file!Use default 10000 ms");
		 m_dBERSessionTimeOut=2000;

	 }
	 else
	 {
		 m_dBERSessionTimeOut=CStr::StrToFloat(itrFind->second);

	 }

	 itrFind=pcSettingMap->find(_T("RegistTimeOut"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RegistTimeOut' from ini file,Use default 30 ms!");
		 m_dRegistTimeOut=30;

	 }
	 else
	 {
		 m_dRegistTimeOut=CStr::StrToFloat(itrFind->second);

	 }

	 itrFind=pcSettingMap->find(_T("CMW_WaveFile"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'CMW_WaveFile' from ini file,Use default!");
		 m_strWavefile.Format("D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\c2k_ch387_hold_up_down_up.wv");
	 }
	 else
	 {
		 m_strWavefile=itrFind->second;
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

 bool CCDMATestStartCall::InitData()
 {
	 m_pFunCDMATestDev=m_piTesterDevice->m_piFuncCDMATest;
	 m_iFailFlag=0;
	 return true;
 }