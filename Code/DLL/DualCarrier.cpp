#include "StdAfx.h"
#include "DualCarrier.h"
RF_IMPLEMENT_DYNCREATE(CDualCarrier)

CDualCarrier::CDualCarrier(void)
{
	m_mapClassFunc[_T("CDualCarrierMainFunc")]=&CDualCarrier::CDualCarrierMainFunc;
	m_mapClassFunc[_T("CDualCarrierFunc")]=&CDualCarrier::CDualCarrierFunc;
	m_mapClassFunc[_T("CDualCarrierFastFunc")]=&CDualCarrier::CDualCarrierFastFunc;

}

CDualCarrier::~CDualCarrier(void)
{
}

bool CDualCarrier::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CDualCarrier::Handle()
{
	if(!DoProcess())
	{

		m_pPhone->CloseComport();
		m_pFunWCDMACalDev->Deivce_Exit();
		return false;
	}

	CalPassLog("_","_","WCDMA DualCarrier Cal Pass");

	return true;
}

bool CDualCarrier::CDualCarrierMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}

	return true;
}

bool CDualCarrier::CDualCarrierFunc()
{
	CString strMsg;
	int iErrorcode;
	unsigned short iStatus=0; 
	double dUlMHz,dDLMhz;
	double DYNAMICRANGE=102.3;
	double MIN_RSSI=-106;

	QMSL_CDMA_RxFreq_Measurement_struct aRX_Measured;
	QMSL_CDMA_MeasuredChannels_struct  aRX_MeasuredChannels;
	QMSL_CDMA_NVChannels_struct  aRX_NV_Channels;
	QMSL_CDMA_Rx_DVGA_LNA_Cal_NV_Result aRX_DVGA_LNA_Cal_NV;
	memset(&aRX_Measured,0,sizeof(QMSL_CDMA_RxFreq_Measurement_struct));
	memset(&aRX_MeasuredChannels,0,sizeof(QMSL_CDMA_MeasuredChannels_struct));
	memset(&aRX_NV_Channels,0,sizeof(QMSL_CDMA_NVChannels_struct));
	memset(&aRX_DVGA_LNA_Cal_NV,0,sizeof(QMSL_CDMA_Rx_DVGA_LNA_Cal_NV_Result));
	aRX_Measured.iPath=m_iRxPath;
	
	aRX_Measured.iNumMeasured_LNA_States=m_ivRxAction.size()-1;
	aRX_Measured.iNumMeasuredPowerModes=1;
	aRX_MeasuredChannels.iNumMeasuredChannels=1;
	//aRX_MeasuredChannels.iRefChannel=m_iCHannel;
	aRX_MeasuredChannels.aiMeasuredChannels[0]=m_iCHannel;

	for (int i=0;i<16;i++)
	{
		aRX_NV_Channels.aiNVChannels[i]=m_iCHannel;

	}


	dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,1);
	dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iBand,CWCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel),0);
	if((iErrorcode=m_pPhone->FTM_SET_Cal_STATE(1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone SET_Cal_STATE  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(FTM_MODE_ID_WCDMA))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set mode id to WCDMA  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iRFMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set mode (BAND)  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(m_iRxPath))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Secondary CHAIN 0  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_MULTI_CHAN(m_iCHannel,m_iCHannel+25))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Secondary CHAIN 0  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetNormalSig(dUlMHz,dDLMhz,0,-80))
	{
		LogTrace(MSG_ERROR,"Set Normal CDMA200 signal fail");
		CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set Normal CDMA200 signal fail");
		return false;

	}
	for (int i=0;i<m_ivRxAction.size();i++)
	{
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPowe(m_dvExpectedPower[i]))
		{
			LogTrace(MSG_ERROR,"Set DL power fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set DL power fail");
			return false;

		}
		Sleep(20);

		short iExpectedAGC=(1024/DYNAMICRANGE)*(m_dvExpectedPower[i]-(MIN_RSSI+DYNAMICRANGE/2));
		short iOffsetValue0=0;
		if((iErrorcode=m_pPhone->GET_RX_OFFSET_MULTI_CHAN(m_iRxPath,m_iFTM_MODE_ID,m_ivRxAction[i],iExpectedAGC,&iOffsetValue0))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Get Rx Offset Fail!");
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
		if (0==m_ivRxAction[i])
		{
			aRX_Measured.aiDVGA_Measured[0][0]=iOffsetValue0;
			
		} 
		else
		{
			aRX_Measured.aiLNA_States[m_ivRxAction[i]-1]=m_ivRxAction[i];			
			aRX_Measured.aiLNA_Measured[0][m_ivRxAction[i]-1][0]=iOffsetValue0;

		}
	}

	if((iErrorcode=m_pPhone->RFCAL_WCDMA_MultiCarrier_RxCal_Results(BH_WCDMA_BAND_I,m_iNVMode,0,1,&aRX_Measured,&aRX_MeasuredChannels,&aRX_NV_Channels,&aRX_DVGA_LNA_Cal_NV,0,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_WCDMA_MultiCarrier_RxCal_Results Primary  Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	strMsg.Format("RX DVGA and LNA Offset NV Value");
	LogTrace(MSG_MID,strMsg);

	strMsg.Format("DualCarrier DVGA offset=%d",aRX_DVGA_LNA_Cal_NV.aDVGA.iDVGAOffset);
	LogTrace(MSG_MID,strMsg);
	for(int iLNARangeIndex=0;iLNARangeIndex<aRX_Measured.iNumMeasured_LNA_States;++iLNARangeIndex)
	{
		strMsg.Format("DualCarrier LNA%d offset=%d",iLNARangeIndex,aRX_DVGA_LNA_Cal_NV.aLNA[iLNARangeIndex].iLNAOffset);
		LogTrace(MSG_MID,strMsg);
	}
	return true;
}

bool CDualCarrier::CDualCarrierFastFunc()
{
	CalFailLog("_","_",0,"CDualCarrierFastFunc DO NOT support yet");
	return false;
}

bool CDualCarrier::InitData(
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


	itrFind=pcSettingMap->find(_T("RxPath"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RxPath' from ini file!.default is 0.");
		m_iRxPath=0;
		m_iFTM_MODE_ID=FTM_MODE_ID_WCDMA;
	}
	else
	{
		m_iRxPath=CStr::StrToInt(itrFind->second);
		switch (m_iRxPath)
		{
		case 0:
			m_iFTM_MODE_ID=FTM_MODE_ID_WCDMA;
			break;
		case 1:
			m_iFTM_MODE_ID=FTM_MODE_WCDMA_RX1;
			break;
		default:
			LogTrace(MSG_FATAL,"'RxPath' in ini file must be 0 or 1");
			return false;
		}
	}

	itrFind=pcSettingMap->find(_T("Band"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'Band' from ini file!.default is 2100");
		m_iBand=2100;
		m_iRFMode=CWCDMABandInfo::GetPhoneMode(m_iBand);
	}
	else
	{
		m_iBand=CStr::StrToInt(itrFind->second);
		m_iRFMode=CWCDMABandInfo::GetPhoneMode(m_iBand);

	}

	itrFind=pcSettingMap->find(_T("NVMode"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'NVMode' from ini file!.default is 43");
		m_iNVMode=43;
	}
	else
	{
		m_iNVMode=CStr::StrToInt(itrFind->second);

	}

	itrFind=pcSettingMap->find(_T("Channel"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'Channel' from ini file!.default is 9750");
		m_iCHannel=9750;
	}
	else
	{
		m_iCHannel=CStr::StrToInt(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("RxActionlist"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RxActionlist' from ini file!.");
		return false;
	}
	else
	{
		CStr::ParseString(itrFind->second,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivRxAction,strVtr);
	}

	itrFind=pcSettingMap->find(_T("ExpectedPowerlist"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'ExpectedPowerlist' from ini file!.");
		return false;
	}
	else
	{
		CStr::ParseString(itrFind->second,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvExpectedPower,strVtr);
	}
	itrFind=pcSettingMap->find(_T("RxMaxLimits"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RxMaxLimits' from ini file!.");
		return false;
	}
	else
	{
		CStr::ParseString(itrFind->second,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivRxMaxLimits,strVtr);
	}
	itrFind=pcSettingMap->find(_T("RxMinLimits"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RxMinLimits' from ini file!.");
		return false;
	}
	else
	{
		CStr::ParseString(itrFind->second,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivRxMinLimits,strVtr);
	}



	InitData();
	return true;
}

bool CDualCarrier::InitData()
{
	m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	return true;
}
