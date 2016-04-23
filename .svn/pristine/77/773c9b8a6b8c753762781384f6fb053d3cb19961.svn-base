#include "StdAfx.h"
#include "LteCableLossCal.h"
RF_IMPLEMENT_DYNCREATE(CLteCableLossCal)

CLteCableLossCal::CLteCableLossCal(void)
{
	m_mapClassFunc[_T("CableLossMainFunc")]=&CLteCableLossCal::LteCableLossMainFunc;
	m_mapClassFunc[_T("MakeGoldenSemple")]=&CLteCableLossCal::LteMakeGoldenSemple;
	m_mapClassFunc[_T("SetCableLoss")]=&CLteCableLossCal::LteSetCableLoss;
}

CLteCableLossCal::~CLteCableLossCal(void)
{
}
bool CLteCableLossCal::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}
bool  CLteCableLossCal::Handle()
{
	if(!DoProcess())
	{
		m_pFuncLteTestDev->Deivce_Exit();
//****************************
	m_pPhone->LTE_NS_IDLE();

	m_pPhone->LTE_NS_STOP();
		return false;
	}	
	m_pFuncLteTestDev->Deivce_Exit();
//****************************
	m_pPhone->LTE_NS_IDLE();

	m_pPhone->LTE_NS_STOP();

	return true;
}
bool CLteCableLossCal::LteCableLossMainFunc()
{


	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

	{

		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}

	return true;
}
bool CLteCableLossCal::LteMakeGoldenSemple()
{

	if (m_bPowerMeasType)
	{
		if (!LteMeasPowerEx())
		{
			return false;
		}
	} 
	else
	{
		if (!LteMeasPower())
		{
			return false;
		}
	}
	

	m_dvGoldenPower.clear();
	m_dvGoldenPower=m_dvPowerMeas;
	if (!WriteGoldenPower())
	{
		CalFailLog(m_strTestBand,"-",1003,"SetCableLoss Fail");
		return false;
	}	
	return true;
}
bool CLteCableLossCal::LteSetCableLoss()
{
	CStringVtr cvChannel;
	CStringVtr cvLoss;
	CStringStringMap mapString2String;

	if (m_bPowerMeasType)
	{
		if (!LteMeasPowerEx())
		{
			return false;
		}
	} 
	else
	{
		if (!LteMeasPower())
		{
			return false;
		}
	}
	if (!ReadGoldenPower())
	{
		return true;
	}
	double dTemp;
	CString strTemp,strTemp1;
	for (int i=0;i<3;i++)
	{
		dTemp=m_dvGoldenPower[i]-m_dvPowerMeas[i]+m_vCableLoss[i];
		strTemp.Format("%.2f",dTemp);
		strTemp1.Format("cableloss=%.2f",dTemp);
		TestPassLog(m_strTestBand,"_","_","_",strTemp,"_",strTemp1);
		cvLoss.push_back(strTemp);
	}


	cvChannel.clear();
	cvChannel.push_back("0");cvChannel.push_back("1");cvChannel.push_back("2");
	CStr::MakeVector2Map(cvChannel,cvLoss,mapString2String);	
	if(!m_LossFinder.UpdateLossIniFromMap(m_strTestBand,mapString2String))
	{
		CalFailLog("_","_",1003,"Cable loss ini not exist");
		return false;
	}
	CalPassLog(m_strTestBand,"-","SetCableLoss pass");


	return true;
}
bool CLteCableLossCal::LteMeasPowerEx()
{
	int iErrorcode;
	CString strMsg;
	m_dvPowerMeas.clear();
	FTM_Cal_Sweep_Request stSweep[50];
	int iNumConfigSigment=25;
	
	short iPhoneMode=CLTEBandInfo::GetPhoneMode(m_iTestBand);
	int iCallChannel=m_ivTestChannelList[0];
	if((iErrorcode=m_pFuncLteDev->IWCDMACalInit(m_strDeviceAddr))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Init Lte Test Dev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Init Lte Test Dev Fail!"))
			return false;
	}
	for( int i = 0; i < 50; i++)
	{
		stSweep[i].segLen = 2000;//
		stSweep[i].masterDev = 1;
		stSweep[i].slaveDev = -1;
		stSweep[i].rfmode=iPhoneMode;
		stSweep[i].ulChan=iCallChannel;
		stSweep[i].txBW = 3;	// don't care for WCDMA
		stSweep[i].rxBW = 3;	// don't care for WCDMA
		stSweep[i].chanOffset = 0;
		stSweep[i].txWaveform = 255;
		stSweep[i].numRBs = 6;
		stSweep[i].startRB = 22;
		stSweep[i].txAction=0;
		stSweep[i].txFlag = 1;
		stSweep[i].hdetFlag =1;
		stSweep[i].rxActions = 0xffff;
		stSweep[i].txPurpose=0x00;
		stSweep[i].rxPM = 0;
		stSweep[i].expRxAGC = 0;
		stSweep[i].rxFlag = 1;	 		
	}
	int iSegmentNum=0;

	stSweep[iSegmentNum].opcode = 0x0001;
	stSweep[iSegmentNum].ulChan = iCallChannel;
	stSweep[iSegmentNum].paState = 255; // no-op
	stSweep[iSegmentNum].paBias = 511;
	stSweep[iSegmentNum].rgi = 0;
	iSegmentNum++;



	// Segment 1-14, no op for Set mode channel to take effect
	for(int i = 1; i < 15; i++)
	{		
		stSweep[iSegmentNum].opcode = 0x0000;
		stSweep[iSegmentNum].ulChan = iCallChannel;
		stSweep[iSegmentNum].paState = 255; // no-op
		stSweep[iSegmentNum].paBias = 511;
		stSweep[iSegmentNum].rgi = 0;
		iSegmentNum++;
	}

	

	if (!SetLteLoss())
		return false;
	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Lte Test Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Lte Test Phone Open Comport Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Lte Test Phone Set FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Lte Test Phone Set FTM Mode Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_SET_MODE(iPhoneMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set RF Mode Fail!");
		
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	if((iErrorcode=m_pPhone->FTM_SET_Cal_STATE(1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Calibration State Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	DblVtr dvTRxFreq;
	dvTRxFreq.clear();
	for (int ichan=0;ichan<m_ivTestChannelList.size();ichan++)
	{
		int iCurrChannel=m_ivTestChannelList[ichan];
		int iDLChannel=CLTEBandInfo::GetDLChannel(m_iTestBand,iCurrChannel);
		double dUlMHz=CLTEBandInfo::ArfcnToHz(m_iTestBand,iCurrChannel);
		double dDLMhz=CLTEBandInfo::ArfcnToHz(m_iTestBand,iDLChannel);
		// Segment 15, no op for Set mode channel to take effect
		if (0==ichan)
		{
			stSweep[iSegmentNum].opcode = 0x0004;
			stSweep[iSegmentNum].ulChan = iCurrChannel;
			stSweep[iSegmentNum].paState = 255; // no-op
			stSweep[iSegmentNum].paBias = 511;
			stSweep[iSegmentNum].txWaveform=1;
			stSweep[iSegmentNum].rgi = 0;
		} 
		else
		{
			stSweep[iSegmentNum].opcode = 0x0002;
			stSweep[iSegmentNum].ulChan = iCurrChannel;
			stSweep[iSegmentNum].paState = 255; // no-op
			stSweep[iSegmentNum].paBias = 511;
			stSweep[iSegmentNum].rgi = 0;
		}
		iSegmentNum++;
		for (int i=1;i<2;i++)
		{
			stSweep[iSegmentNum].opcode = 0x0000;
			stSweep[iSegmentNum].ulChan = iCurrChannel;
			stSweep[iSegmentNum].paState = 255; // no-op
			stSweep[iSegmentNum].paBias = 511;
			stSweep[iSegmentNum].rgi = 0;
			iSegmentNum++;
		}


		
		for( int i = 0; i < 8; i++)
		{
			stSweep[iSegmentNum].opcode = 0x0008;
			stSweep[iSegmentNum].paState = m_iPARange; // no-op
			stSweep[iSegmentNum].paBias = m_iBias;
			stSweep[iSegmentNum].rgi = m_iPDM; 
			stSweep[iSegmentNum].ulChan=iCurrChannel;
			stSweep[iSegmentNum].numHdetAvg=0;
			stSweep[iSegmentNum].numLpmHdetAvg=0;		
			iSegmentNum++;
		}
		
		dvTRxFreq.push_back(dDLMhz);
		dvTRxFreq.push_back(dUlMHz);
	}

		DblVtr dvTxLvlRef;
		dvTxLvlRef.clear();
		dvTxLvlRef.push_back(m_dMaxPowerLimit.GetMax());	
		


		DblVtr dvRxLvl;
		dvRxLvl.clear();
		dvRxLvl.push_back(-70);
		dvRxLvl.push_back(-70);

		if ((iErrorcode=m_pFuncLteDev->IWCDMAESCalLinearconfig(0,10,2,dvTRxFreq,dvTxLvlRef,dvRxLvl,10,m_ivTestChannelList.size()))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Config Enhanced Sweep Cal equiment fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Config Enhanced Sweep Cal equiment fail");

			return false;
		}

		if((iErrorcode=m_pPhone->FTM_CFG_AND_EXEC_CAL_SWEEP((void*)stSweep,iSegmentNum,false,true))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Linear first Sweep Fail!");
	
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)

		}
		DblVtr dvTRxResult;
		dvTRxResult.clear();
		if ((iErrorcode=m_pFuncLteDev->IWCDMAFetchTXRXResults(dvTRxResult))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Fetch ESCal Linear full bias result fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Fetch ESCal Linear full bias result fail");

			return false;
		}
		int iNumOfSigmentPerSeuence=0;
		if (m_strTesterDevice.Find("8820")!=-1)
		{
			iNumOfSigmentPerSeuence=9;
		}
		else
		{
			iNumOfSigmentPerSeuence=10;
		}
		for (int iSequenceloop=0;iSequenceloop<m_ivTestChannelList.size();iSequenceloop++)
		{
			int iCurrChannel=m_ivTestChannelList[iSequenceloop];
			double dPowerSum=0;
			for (int i=0;i<iNumOfSigmentPerSeuence-1;i++)
			{
				dPowerSum+=dvTRxResult[i+iNumOfSigmentPerSeuence*iSequenceloop];
			}
			double dPowerMeasured=dPowerSum/(iNumOfSigmentPerSeuence-1);
			if (m_dMaxPowerLimit.InRange(dPowerMeasured))
			{
				TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower PASS"),"MaxPower")

			}
			else
			{
				TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower FAIL"),"MaxPower")
					return false;
			}
			m_dvPowerMeas.push_back(dPowerMeasured);
		}
		



	m_pFuncLteDev->Deivce_Exit();
	m_pPhone->CloseComport();
	return true;

}
bool CLteCableLossCal::LteMeasPower()
{
	int iErrorcode;
	m_dvPowerMeas.clear();
	CString strLTEMode;
	if (m_iTestBand<33)
	{strLTEMode="FDD";
	} 
	else
	{strLTEMode="TDD";
	}
	int iconfig=2;
	if (m_strTesterDevice=="CMW500")
	{
		iconfig=1;
	}
	int iDLChannel=CLTEBandInfo::GetDLChannel(m_iTestBand,m_ivTestChannelList[0]);
	//ÐèÒªÐÞ¸Ä
	if((iErrorcode=m_pFuncLteTestDev->ILteInitSet(m_strDeviceAddr,"D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\library1\\LTE_ProductionTest_1_v01.wv",strLTEMode))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Init Lte Test Dev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Init Lte Test Dev Fail!"))
			return false;
	}
	if (!SetLteLoss())
		return false;
	if((iErrorcode=m_pFuncLteTestDev->ILteHandOver(m_iTestBand,m_ivTestChannelList[0]))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Lte Test Dev HandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Lte Test Dev HandOver Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteConfigWaveForm(50,0,6))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Lte Test Dev ConfigWaveForm Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Lte Test Dev ConfigWaveForm Fail!"))
			return false;
	}

	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-50,23,2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Lte Test Dev SetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Lte Test Dev SetPower Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone Open Comport Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone Set FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone Set FTM Mode Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->TDLTE_Cal_Setup(m_iTestBand-1,iDLChannel,iconfig))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone StartCall Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone StartCall Fail!"))
			return false;
	}	 


	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_WAVEFORM(1,0,0,50,6))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->LTE_NS_IS_CONNECTED())!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
			return false;
	}




	CalPassLog(_T(m_strTestBand),_T(CStr::IntToStr(m_ivTestChannelList[0])),_T("Lte StartCall Pass"))
		
	for (int i=0;i<m_ivTestChannelList.size();i++)
	{
		int iErrorcode,iFailFlag=0;;
		m_iItemCode=WCDMA_Call_HandOver_Phone_BaseItemCode;
		int m_iCurrentCH=m_ivTestChannelList[i];

		m_pPhone->LTE_NS_IDLE();
		m_pPhone->LTE_NS_STOP();
		iDLChannel=CLTEBandInfo::GetDLChannel(m_iTestBand,m_iCurrentCH);
		if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,23,2))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
				return false;
		}
		if((iErrorcode=m_pFuncLteTestDev->ILteConfigWaveForm(50,0,6))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteConfigWaveForm Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteConfigWaveForm Fail!"))
				return false;
		}
		if((iErrorcode=m_pFuncLteTestDev->ILteHandOver(m_iTestBand,m_iCurrentCH))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteHandOver Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteHandOver Fail!"))
				return false;
		}	

		if((iErrorcode=m_pPhone->TDLTE_Cal_Setup(m_iTestBand-1,iDLChannel,iconfig))!=PHONE_SUCCESS)
		{           
			LogTrace(MSG_ERROR,_T("Phone StartCall Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T(m_strTestBand),_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone StartCall Fail!"))
				return false;
		}	

		if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_WAVEFORM(1,0,0,50,6))!=PHONE_SUCCESS)
		{           
			LogTrace(MSG_ERROR,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
				return false;
		}
		if((iErrorcode=m_pPhone->LTE_NS_IS_CONNECTED())!=PHONE_SUCCESS)
		{           
			LogTrace(MSG_ERROR,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
				return false;
		}

		m_iItemCode=WCDMA_MaxPower_Test_BaseItemCode;
		double dPowerMeasured=0;
		if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,28,1))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
				return false;
		}

		if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,280))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
				return false;
		}
		if((iErrorcode=m_pFuncLteTestDev->ILteTestPower(m_iMeasureCount,&dPowerMeasured))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteTestPower Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteTestPower Fail!"))
				return false;
		}
		if (m_dMaxPowerLimit.InRange(dPowerMeasured))
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower PASS"),"MaxPower")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower FAIL"),"MaxPower")
				return false;
		}
		m_dvPowerMeas.push_back(dPowerMeasured);
		
		
		

	}
	m_pPhone->LTE_NS_IDLE();

	m_pPhone->LTE_NS_STOP();
	m_pFuncLteDev->Deivce_Exit();
	m_pPhone->CloseComport();
	return true;
}
bool CLteCableLossCal::ReadGoldenPower()
{
	int  iErrorcode;
	unsigned char uiData[128]={0},uiFlagData[128]={0};
	CString strMsg;
	LogTrace(MSG_MID,_T(" Open Comport....!"))
		if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
		}

		strMsg.Format("Reading NV : %d ",2500);
		LogTrace(MSG_MID,strMsg)

			if((iErrorcode=m_pPhone->ReadNV(2500,uiData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Read NV :2500  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}
			if((iErrorcode=m_pPhone->ReadNV(2499,uiFlagData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Read NV :2499  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}
			m_pPhone->CloseComport();

			byte CheckSum126 = 0;
			byte CheckSum127 = 0;
			for (int index = 0; index < 63; index++)
			{
				CheckSum126 ^= uiData[2 * index];
				CheckSum127 ^= uiData[2 * index + 1];
			}
			for (int index=0;index<64;index++)
			{
				CheckSum126 ^= uiFlagData[2*index];
				CheckSum127 ^= uiFlagData[2 * index+1];
			}
			if ((uiData[126] != CheckSum126) || (uiData[127] != CheckSum127))
			{
				strMsg=_T("Golden NV CheckSum is not right!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}

			strMsg.Format("Golden Sample modified time:%d-%d-%d %d:%d:%d",uiData[120],uiData[121],uiData[122],uiData[123],uiData[124],uiData[125]);
			LogTrace(MSG_MID,strMsg)
				double dGoldenPower=0;
			int iNVoffset=m_iNVOffset;
		/*
			switch (m_iTestBand)
					{
					case 38:
						iNVoffset=78;
						break;
					case 39:
						iNVoffset=84;
						break;
					case 40:
						iNVoffset=90;
						break;
					default:
						strMsg=_T("unkown band!");
						LogTrace(MSG_ERROR,strMsg)
							m_iErrorcode=iErrorcode;
						CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
						return false;
		
					}*/
		
			m_dvGoldenPower.clear();
			for (int i=0;i<3;i++)
			{
				dGoldenPower=(double)uiData[iNVoffset+2*i]+(double)uiData[iNVoffset+2*i+1]/100.0;
				m_dvGoldenPower.push_back(dGoldenPower);
				strMsg.Format("GoldenPower:%.2f",dGoldenPower);
				CalPassLog(m_strTestBand,CStr::IntToStr(i+1),strMsg);
			}
			strMsg.Format("Band%d GoldenPower:%.2f,%.2f,%.2f",m_iTestBand,m_dvGoldenPower[0],m_dvGoldenPower[1],m_dvGoldenPower[2]);
			LogTrace(MSG_MID,strMsg)


				return true;

}

bool CLteCableLossCal::WriteGoldenPower()
{

	int  iErrorcode;
	unsigned char uiData[128]={0},uiFlagData[128]={0};
	CString strMsg;

	LogTrace(MSG_MID,_T(" Open Comport....!"))
		if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
		}

		strMsg.Format("Reading NV : %d ",2500);
		LogTrace(MSG_MID,strMsg)

			if((iErrorcode=m_pPhone->ReadNV(2500,uiData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Read NV :2500  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}


			int iNVoffset=m_iNVOffset;
/*
			switch (m_iTestBand)
			{
			case 38:
				iNVoffset=79;
				break;
			case 39:
				iNVoffset=84;
				break;
			case 40:
				iNVoffset=90;
				break;
			default:
				strMsg=_T("unkown band!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;

			}*/

			for (int i=0;i<m_dvGoldenPower.size();i++)
			{
				double dGoldenPower=m_dvGoldenPower[i];
				int n1 = (int)dGoldenPower;
				int n2 = (int)(dGoldenPower * 100.0) - n1 * 100;
				uiData[iNVoffset++] = (byte)n1;
				uiData[iNVoffset++] = (byte)n2;		
			}
			SYSTEMTIME st;
			::GetLocalTime(&st);
			uiData[120]=(byte)(st.wYear-2000);
			uiData[121]=(byte)st.wMonth;
			uiData[122]=(byte)st.wDay;
			uiData[123]=(byte)st.wHour;
			uiData[124]=(byte)st.wMinute;
			uiData[125]=(byte)st.wSecond;

			byte CheckSum126 = 0;
			byte CheckSum127 = 0;
			for (int index = 0; index < 63; index++)
			{
				CheckSum126 ^= uiData[2*index];
				CheckSum127 ^= uiData[2 * index+1];
			}
			for (int index=0;index<64;index++)
			{
				CheckSum126 ^= uiFlagData[2*index];
				CheckSum127 ^= uiFlagData[2 * index+1];
			}
			uiData[126] = CheckSum126;
			uiData[127] = CheckSum127;

			if((iErrorcode=m_pPhone->WriteNV(2500,uiData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Write NV :2500  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}
			if((iErrorcode=m_pPhone->WriteNV(2499,uiFlagData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Write NV :2499  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}

			if((iErrorcode=m_pPhone->WriteEFS(3000))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone WriteEFS  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}
			m_pPhone->CloseComport();
			TestPassLogEx(m_strTestBand,_T("-"),_T("-"),_T("-"),_T("-"),_T("-"),_T("WriteGoldNV PASS"),"WriteGoldNV")

				return true;

}
bool CLteCableLossCal::InitData(
								PCStringStrMap     pcSettingMap,
								CRFObjectMap&   cObjectMap
								) 
{
	CStringStringMapItr itrFind;
	CString strValue;
	CString strMainFun;
	CStringVtr strVtr;
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
		LogTrace(MSG_FATAL,"Not Find 'TestBand' from ini file! ");
		return false;

	}
	else
	{
		m_iTestBand=CStr::StrToInt(itrFind->second);
		m_strTestBand.Format("B%d",m_iTestBand);

	}
	itrFind=pcSettingMap->find(_T("NVOffset"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'NVOffset' from ini file! ");
		return false;

	}
	else
	{
		m_iNVOffset=CStr::StrToInt(itrFind->second);
		
	}
	itrFind=pcSettingMap->find(_T("PowerMeasType"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'PowerMeasType' from ini file! defualt is true:CalType");
		m_bPowerMeasType=true;

	}
	else
	{
		m_bPowerMeasType=CStr::StrToBool(itrFind->second);

	}

	itrFind=pcSettingMap->find(_T("TestChannelList"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TestChannelList' from ini file!");
		return false;

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivTestChannelList,strVtr);

	}
	itrFind=pcSettingMap->find(_T("MeasureCount"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'MeasureCount' from ini file! defult is 10 ");
		m_iMeasureCount=10;

	}
	else
	{
		m_iMeasureCount=CStr::StrToInt(itrFind->second);

	}
	itrFind=pcSettingMap->find(_T("Bias"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'Bias' from ini file! defult is 3700 ");
		m_iBias=3700;

	}
	else
	{
		m_iBias=CStr::StrToInt(itrFind->second);

	}

	itrFind=pcSettingMap->find(_T("PARange"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'PARange' from ini file! defult is 1 ");
		m_iPARange=0;

	}
	else
	{
		m_iPARange=CStr::StrToInt(itrFind->second);

	}

	itrFind=pcSettingMap->find(_T("PDM"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'PDM' from ini file! defult is 80 ");
		m_iPDM=80;

	}
	else
	{
		m_iPDM=CStr::StrToInt(itrFind->second);

	}

	itrFind=pcSettingMap->find(_T("MaxPowerLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'MaxPowerLimit' from ini file!Use default 18-25");
		m_dMaxPowerLimit.SetRange(18,25);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_dMaxPowerLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	InitData();
	return true;
}

bool CLteCableLossCal::InitData()
{
	m_pFuncLteDev=m_piTesterDevice->m_piFuncWCDMACal;
	m_pFuncLteTestDev=m_piTesterDevice->m_piFuncWCDMATest;
	return true;
}
bool CLteCableLossCal::SetLteLoss()
{
	CString strMsg;
	double dLoss;
	m_vCableLoss.clear();
	for(int i=0;i<3;i++)
	{
		if(!m_LossFinder.GetWCDMALoss(m_strTestBand,i,dLoss))
		{
			strMsg.Format("Get Loss Band=%s ,ChannelType=%d Fail",m_strTestBand,i);
			LogTrace(MSG_ERROR,strMsg);
			CalFailLog(_T("_"),_T("_"),1001,strMsg);
			return false;
		}
		m_vCableLoss.push_back(dLoss);
	}

	if(DEVICE_SUCCESS!=m_pFuncLteDev->ILTECalSetLoss(m_iTestBand,m_vCableLoss))
	{
		LogTrace(MSG_ERROR,"Set Cableloss device fail");
		CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		return false;

	}

	return  true;
}
