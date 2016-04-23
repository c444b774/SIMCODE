#include "StdAfx.h"
#include "RxTest.h"
RF_IMPLEMENT_DYNCREATE(CRxTest)

CRxTest::CRxTest(void)
{
	m_mapClassFunc[_T("RxTestMainFunc")]=&CRxTest::RxTestMainFunc;
	m_mapClassFunc[_T("RxTestFunc")]=&CRxTest::RxTestFunc;
}

CRxTest::~CRxTest(void)
{
}

bool CRxTest::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CRxTest::Handle()
{
	if(!DoProcess())
	{

		return false;
	}
	return true;
}

bool CRxTest::RxTestMainFunc()
{	

	if (!SetRxTestLoss())
		return false;
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CRxTest::RxTestFunc()
{
	CString strMsg;
	int iErrorcode;
	double  dUlMHz,dDLMhz;
	int iFailFlag=0;

	strMsg.Format("RX Freq Comp :Band=B%d ",m_iTestBand);
	LogTrace(MSG_MID,strMsg);

	if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(0))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iMainFTMMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("SET_MODE_ID Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iRFmode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Band Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	for(int iCHIndex=0;iCHIndex<m_ivTestChannelList.size();++iCHIndex)
	{

		int iChannel=m_ivTestChannelList[iCHIndex];
		int iDLChannel=0;
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iMainFTMMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		
		switch(m_iMainFTMMode)
		{
		case FTM_MODE_ID_LTE:
			iDLChannel=CLTEBandInfo::GetDLChannel(m_iTestBand,iChannel);	
			dUlMHz=CLTEBandInfo::ArfcnToHz(m_iTestBand,iChannel);
			dDLMhz=CLTEBandInfo::ArfcnToHz(m_iTestBand,iDLChannel)+0.5;
			if((iErrorcode=m_pPhone->FTM_SET_BANDWIDTH(3,3))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_BANDWIDTH Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if(DEVICE_SUCCESS!=m_pFunCalDev->IWCDMACalSetXOSig(dUlMHz,dDLMhz,0,m_fCellPower))
			{
				LogTrace(MSG_ERROR,"Set Normal CW signal fail");
				CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set Normal CW signal fail");
				return false;

			}
			break;
		case FTM_MODE_ID_WCDMA:
			iDLChannel=CWCDMABandInfo::GetDLChannel(m_iTestBand,iChannel);	
			dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iTestBand,iChannel,1);
			dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iTestBand,iDLChannel,0);
			if(DEVICE_SUCCESS!=m_pFunCalDev->IWCDMACalSetNormalSig(dUlMHz,dDLMhz,0,m_fCellPower))
			{
				LogTrace(MSG_ERROR,"Set Normal CDMA signal fail");
				CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set Normal CDMA signal fail");
				return false;

			}
			break;
		case FTM_MODE_ID_TDSCDMA:
			dUlMHz=0.2*iChannel;
			dDLMhz=dUlMHz+0.5;
			if(DEVICE_SUCCESS!=m_pFunCalDev->IWCDMACalSetXOSig(dUlMHz,dDLMhz,0,m_fCellPower))
			{
				LogTrace(MSG_ERROR,"Set Normal CW signal fail");
				CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set Normal CW signal fail");
				return false;

			}
			break;
		case FTM_MODE_ID_CDMA_1X:
			dUlMHz=CCDMABandInfo::ArfcnToHz(m_iTestBand,iChannel,0);
			dDLMhz=CCDMABandInfo::ArfcnToHz(m_iTestBand,iChannel,1);
			if(DEVICE_SUCCESS!=m_pFunCalDev->ICDMACalSetNormalSig(dUlMHz,dDLMhz,0,m_fCellPower))
			{
				LogTrace(MSG_ERROR,"Set Normal CDMA signal fail");
				CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set Normal CDMA signal fail");
				return false;

			}
			break;


		}
		if(DEVICE_SUCCESS!=m_pFunCalDev->IDevicesSetIOPort(m_iOutPort))
		{
			LogTrace(MSG_ERROR,"DevicesSetIOPort fail");
			CalFailLog(_T("_"),_T("_"),1001,"DevicesSetIOPort  fail");
			return false;
		}
		if((iErrorcode=m_pPhone->FTM_SET_CHAN(iChannel))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Set Channel Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}

		if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Set TX OFF Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
	
		if(DEVICE_SUCCESS!=m_pFunCalDev->ICDMACalSet_DLPower_On(true))
		{
			LogTrace(MSG_ERROR,"Set DL Power ON fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set DL Power ON fail");
			return false;

		}


		Sleep(20);		
		
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iFTMMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(m_bEnableSecChain))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		if((iErrorcode=m_pPhone->FTM_SET_LNA_RANGE(m_iLNARange))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_LNA_RANGE Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		short iAGC=0;
		int SumAGC=0;
		for (int i=0;i<5;i++)
		{
			if((iErrorcode=m_pPhone->FTM_GET_RX_AGC((unsigned short*)&iAGC))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_GET_RX_AGC Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			Sleep(200);
			SumAGC+=iAGC;
		}
		iAGC=SumAGC/5;
		if (m_dAGCLimit.InRange(iAGC))
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(iChannel)),_T(CStr::FloatToStr(m_dAGCLimit.GetMax())),_T(CStr::FloatToStr(m_dAGCLimit.GetMin())),_T(CStr::IntToStr(iAGC)),_T("-"),_T("AGC PASS"),"AGC")
		} 
		else
		{
			iFailFlag++;
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(iChannel)),WCDMATEST_BER_OUTOFRANGE,_T(CStr::FloatToStr(m_dAGCLimit.GetMax())),_T(CStr::FloatToStr(m_dAGCLimit.GetMin())),_T(CStr::IntToStr(iAGC)),_T("-"),_T("AGC FAIL"),"AGC")
		}
		

		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iFTMMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(0))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iMainFTMMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}					


	}

	if(DEVICE_SUCCESS!=m_pFunCalDev->ICDMACalSet_DLPower_On(false))
	{
		LogTrace(MSG_ERROR,"Set DL Power ON fail");
		CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set DL Power ON fail");
		return false;

	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;
}

bool CRxTest::InitData(
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
	itrFind=pcSettingMap->find(_T("EnableSecChain"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'EnableSecChain' from ini file!.default is true");
		m_bEnableSecChain=true;
	}
	else
	{
		m_bEnableSecChain=CStr::StrToBool(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("Tech"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'Tech' from ini file!");
		return false;

	}
	else
	{
		strValue=itrFind->second;		
	}
	itrFind=pcSettingMap->find(_T("TestBand"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TestBand' from ini file!");
		return false;

	}
	else
	{
		m_iTestBand=CStr::StrToInt(itrFind->second);
		m_strTestBand="B"+itrFind->second;
		if (-1<strValue.Find("LTE"))
		{
			m_iMainFTMMode=FTM_MODE_ID_LTE;
			m_iFTMMode=m_bEnableSecChain?FTM_MODE_LTE_RX1:FTM_MODE_ID_LTE;
			m_iRFmode=CLTEBandInfo::GetPhoneMode(m_iTestBand);
		}
		else if(-1<strValue.Find("WCDMA"))
		{
			m_iMainFTMMode=FTM_MODE_ID_WCDMA;
			m_iFTMMode=m_bEnableSecChain?FTM_MODE_WCDMA_RX1:FTM_MODE_ID_WCDMA;
			m_iRFmode=CWCDMABandInfo::GetPhoneMode(m_iTestBand);
		}
		else if(-1<strValue.Find("TDSCDMA"))
		{
			m_iMainFTMMode=FTM_MODE_ID_TDSCDMA;
			m_iFTMMode=m_bEnableSecChain?FTM_MODE_ID_TDSCDMA_RX1:FTM_MODE_ID_TDSCDMA;
			m_iRFmode=CTDSBandInfo::GetPhoneMode(m_iTestBand);
		}
		else if(-1<strValue.Find("CDMA"))
		{
			m_iMainFTMMode=FTM_MODE_ID_CDMA_1X;
			m_iFTMMode=m_bEnableSecChain?FTM_MODE_ID_CDMA_1X_RX1:FTM_MODE_ID_CDMA_1X;
			m_iRFmode=CCDMABandInfo::GetPhoneMode(m_iTestBand);
		}
		else
		{
			strValue=_T("Do NOT support Technology:")+strValue;
		}
			
	}
	itrFind=pcSettingMap->find(_T("ChannelList"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'ChannelList' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivTestChannelList,strVtr);
	}
	itrFind=pcSettingMap->find(_T("LNARagne"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'LNARagne' from ini file! defualt 0");
		m_iLNARange=0;

	}
	else
	{
		m_iLNARange=CStr::StrToInt(itrFind->second);		
	}
	
	itrFind=pcSettingMap->find(_T("CellPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'CellPower' from ini file!");
		return false;

	}
	else
	{
		m_fCellPower=CStr::StrToFloat(itrFind->second);		
	}
	itrFind=pcSettingMap->find(_T("DevicePort"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'DevicePort' from ini file!.default use pre config");
		//return false;
		m_iOutPort=m_piTesterDevice->m_iInputPort;
	}
	else
	{
		m_iOutPort=CStr::StrToInt(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("AGCLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'AGCLimit' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_dAGCLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}




	InitData();
	return true;
}

bool CRxTest::InitData()
{
	m_pFunCalDev=m_piTesterDevice->m_piFuncWCDMACal;
	return true;
}
bool CRxTest::SetRxTestLoss()
{
	CString strMsg,strCurrBand;
	double dLoss;
	DblVtr dvCableLoss;
	dvCableLoss.clear();
	switch(m_iMainFTMMode)
	{
	case FTM_MODE_ID_LTE:
		strCurrBand.Format("B%d",m_iTestBand);
		for(int i=0;i<3;i++)
		{
			if(!m_LossFinder.GetWCDMALoss(strCurrBand,i,dLoss))
			{
				strMsg.Format("LTE Get Loss Band=%s ,ChannelType=%d Fail",strCurrBand,i);
				LogTrace(MSG_ERROR,strMsg);
				CalFailLog(_T("_"),_T("_"),1001,strMsg);
				return false;
			}
			dvCableLoss.push_back(dLoss);
		}



		if(DEVICE_SUCCESS!=m_pFunCalDev->ILTECalSetLoss(m_iTestBand,dvCableLoss))
		{
			LogTrace(MSG_ERROR,"Set Cableloss device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
			return false;

		}

		break;
	case FTM_MODE_ID_WCDMA:

		strCurrBand.Format("W%d",m_iTestBand);
		dvCableLoss.clear();
		for(int i=0;i<3;i++)
		{
			if(!m_LossFinder.GetWCDMALoss(strCurrBand,i,dLoss))
			{
				strMsg.Format("WCDMA Get Loss Band=%s ,ChannelType=%d Fail",strCurrBand,i);
				LogTrace(MSG_ERROR,strMsg);
				CalFailLog(_T("_"),_T("_"),1001,strMsg);
				return false;
			}
			dvCableLoss.push_back(dLoss);
		}



		if(DEVICE_SUCCESS!=m_pFunCalDev->IWCDMACalSetLoss(m_iTestBand,dvCableLoss))
		{
			LogTrace(MSG_ERROR,"Set Cableloss device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
			return false;

		}
		break;
	case FTM_MODE_ID_TDSCDMA:
		strCurrBand.Format("B%d",m_iTestBand);
		for(int i=0;i<3;i++)
		{
			if(!m_LossFinder.GetWCDMALoss(strCurrBand,i,dLoss))
			{
				strMsg.Format("LTE Get Loss Band=%s ,ChannelType=%d Fail",strCurrBand,i);
				LogTrace(MSG_ERROR,strMsg);
				CalFailLog(_T("_"),_T("_"),1001,strMsg);
				return false;
			}
			dvCableLoss.push_back(dLoss);
		}
		if(DEVICE_SUCCESS!=m_pFunCalDev->ILTECalSetLoss(m_iTestBand,dvCableLoss))
		{
			LogTrace(MSG_ERROR,"Set Cableloss device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
			return false;

		}

		break;
	case FTM_MODE_ID_CDMA_1X:
		strCurrBand.Format("CDMA%d",m_iTestBand);
		for(int i=0;i<3;i++)
		{
			//******************************************************************************
			if(!m_LossFinder.GetCDMALoss(strCurrBand,i,dLoss))
			{
				strMsg.Format("LTE Get Loss Band=%s ,ChannelType=%d Fail",strCurrBand,i);
				LogTrace(MSG_ERROR,strMsg);
				CalFailLog(_T("_"),_T("_"),1001,strMsg);
				return false;
			}
			dvCableLoss.push_back(dLoss);
		}
		if(DEVICE_SUCCESS!=m_pFunCalDev->ICDMACalSetLoss(m_iTestBand,dvCableLoss))
		{
			LogTrace(MSG_ERROR,"Set Cableloss device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
			return false;

		}
		break;


	}
	return true;
}
bool CRxTest::EndTest()
{
	int iErrorcode;
	CString strMsg;
	unsigned char NVItemValue[128]={0};
	LogTrace(MSG_MID,_T(" Write NV 453=0 !"))
		if((iErrorcode=m_pPhone->WriteNV(453,NVItemValue,128))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Write NV :%d  Fail!",453);
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}


		LogTrace(MSG_MID,_T(" Write EFS !"))
			if((iErrorcode=m_pPhone->WriteEFS(30000))!=PHONE_SUCCESS)
			{
				LogTrace(MSG_ERROR,_T(" Phone WriteEFS Fail!"))
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode," Phone WriteEFS Fail!");
				return false;
			}
			m_pFunCalDev->Deivce_Exit();

			m_pPhone->CloseComport();

			TestPassLog(_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("EndCall Pass"));
	return true;
}
