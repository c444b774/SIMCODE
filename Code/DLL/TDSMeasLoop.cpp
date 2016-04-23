#include "StdAfx.h"
#include "TDSMeasLoop.h"
RF_IMPLEMENT_DYNCREATE(CTDSMeasLoop)

CTDSMeasLoop::CTDSMeasLoop(void)
{
	m_mapClassFunc[_T("TDSCDMAMeasMainFunc")]=&CTDSMeasLoop::TDTestMeasureLoopMainFunc;
	m_mapClassFunc[_T("TDTestPower")]=&CTDSMeasLoop::TDTestPower;
	m_mapClassFunc[_T("TDTestFreqErr")]=&CTDSMeasLoop::TDTestFreqErr;
	m_mapClassFunc[_T("TDTestACLR")]=&CTDSMeasLoop::TDTestACLR;
	m_mapClassFunc[_T("TDTestModAnalysis")]=&CTDSMeasLoop::TDTestModAnalysis;
	m_mapClassFunc[_T("TDTestOBW")]=&CTDSMeasLoop::TDTestOBW;
	m_mapClassFunc[_T("TDTestPeakCDP")]=&CTDSMeasLoop::TDTestPeakCDP;
	m_mapClassFunc[_T("TDTestPwrTempate")]=&CTDSMeasLoop::TDTestPwrTempate;
	m_mapClassFunc[_T("TDTestRxBER")]=&CTDSMeasLoop::TDTestRxBER;
	m_mapClassFunc[_T("TDTestSEMask")]=&CTDSMeasLoop::TDTestSEMask;
	m_mapClassFunc[_T("TDHandOver")]=&CTDSMeasLoop::TDHandOver;
	m_mapClassFunc[_T("TDTestCLPC")]=&CTDSMeasLoop::TDTestCLPC;
	m_mapClassFunc[_T("TDTestRxLevel")]=&CTDSMeasLoop::TDTestRxLevel;
}

CTDSMeasLoop::~CTDSMeasLoop(void)
{
}

bool CTDSMeasLoop::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CTDSMeasLoop::Handle()
{
	if(!DoProcess())
	{
		m_pPhone->FTM_TDSCDMA_EndCall();
		return false;
	}	

	return true;
}
bool CTDSMeasLoop::TDTestMeasureLoopMainFunc()
{
	if (!SetTDTestLOSS())
	return false;
	for (int i=0;i<m_ivTestChannelList.size();i++)
	{
		m_iCurrentCH=m_ivTestChannelList[i];
		for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

		{

			FPClassFunc fpTestFunc=*itrFP;
			if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
				return false;
		}

	}
	
	return true;
}
bool CTDSMeasLoop::TDTestRxLevel()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_RxLevel_Test_BaseItemCode;
	float fRxPower=0;
	for (int i=0;i<m_dvRxPowerList.size();i++)
	{
		if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMASetPower(m_dvRxPowerList[i],-10,2))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ITDSCDMASetPower Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMASetPower Fail!"))
				return false;
		}
		Sleep(m_iRxlevelDelayMs);

		if((iErrorcode=m_pPhone->FTM_TDSCDMA_BER_RxLevel(0,&fRxPower))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Phone FTM_TDSCDMA_BER_RxLevel Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Phone FTM_TDSCDMA_BER_RxLevel Fail!"))
				return false;
		}

		if (fRxPower>m_dvRxLevelHLList[i]||fRxPower<m_dvRxLevelLLList[i])
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_RSCP_OUTOFRANGE,_T(CStr::FloatToStr(m_dvRxLevelHLList[i])),_T(CStr::FloatToStr(m_dvRxLevelLLList[i])),_T(CStr::FloatToStr(fRxPower)),_T("dbm"),_T("RxLevel FAIL"),"RxLevel")
				iFailFlag++;
		} 
		else
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dvRxLevelHLList[i])),_T(CStr::FloatToStr(m_dvRxLevelLLList[i])),_T(CStr::FloatToStr(fRxPower)),_T("dbm"),_T("RxLevel PASS"),"RxLevel")

		}

	}	
	
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::TDTestCLPC()
{

	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_ILPC_E_Test_BaseItemCode;
	bool bCLPCResult;
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMACLPC(m_iMeasureCount,&bCLPCResult))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMACLPC Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMACLPC Fail!"))
			return false;
	}
	if (bCLPCResult)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T("1"),_T("-"),_T("CLPC PASS"),"CLPC")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ILPC_A_OUTOFRANGE,_T("1"),_T("1"),_T("0"),_T("-"),_T("CLPC FAIL"),"CLPC")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::TDHandOver()
{	
	/*unsigned char ucTFCIConfig[4]={0,1,2,3};

	if(m_strTesterDevice=="A8960")
	{	 ucTFCIConfig[1]=2;
	ucTFCIConfig[2]=1;}*/
	int iErrorcode;
	m_iItemCode=WCDMA_Call_HandOver_Device_BaseItemCode;
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAHandOver(m_iTestBand,m_iCurrentCH))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device HandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device HandOver Fail!"))
			return false;
	}

	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMASetPower(-65,0,2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device HandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device HandOver Fail!"))
			return false;
	}

	m_iItemCode=WCDMA_Call_HandOver_Phone_BaseItemCode;
	if((iErrorcode=m_pPhone->FTM_TDSCDMA_BER_Handover(0,4,2,24,1,m_iCurrentCH))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone FTM_TDSCDMA_BER_Handover fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone FTM_TDSCDMA_BER_Handover fail!"))
			return false;
	}
/*
	if((iErrorcode=m_pPhone->DIAG_CHANGE_RX_DIVERSITY(5,1))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone DIAG_CHANGE_RX_DIVERSITY fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone DIAG_CHANGE_RX_DIVERSITY fail!"))
			return false;
	}*/
	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	CalPassLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("HandOver Pass"))
	return true;

}
bool CTDSMeasLoop::TDTestPower()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_MaxPower_Test_BaseItemCode;
	double dPowerMeasured;
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAMaxPower(m_iMeasureCount,&dPowerMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAMaxPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMAMaxPower Fail!"))
			return false;
	}
	if (m_dMaxPowerLimit.InRange(dPowerMeasured))
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower PASS"),"MaxPower")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower FAIL"),"MaxPower")
		iFailFlag++;
	}

	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAMinPower(m_iMeasureCount,&dPowerMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAMinPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMAMinPower Fail!"))
			return false;
	}
	if (m_dMinPowerLimit.InRange(dPowerMeasured))
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MinPower PASS"),"MinPower")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MINPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMinPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MinPower FAIL"),"MinPower")
		iFailFlag++;
	}
	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
		return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::TDTestFreqErr()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_FrequencyError_Test_BaseItemCode;
	double dFERMeasured;
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAFreqErr(m_iMeasureCount,m_dRxCellPower,&dFERMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAFreqErr Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMAFreqErr Fail!"))
			return false;
	}
	if (abs(dFERMeasured)<m_dFERLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dFERLimit)),_T("-"),_T(CStr::FloatToStr(dFERMeasured)),_T("PPM"),_T("Frequency Error PASS"),"FerqErr")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_dFERLimit)),_T("-"),_T(CStr::FloatToStr(dFERMeasured)),_T("PPM"),_T("Frequency Error FAIL"),"FerqErr")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::TDTestPeakCDP()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_FrequencyError_Test_BaseItemCode;
	double dPCDErrMeasured;
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAPeakCDP(m_iMeasureCount,&dPCDErrMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAPeakCDP Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMAPeakCDP Fail!"))
			return false;
	}
	if (dPCDErrMeasured<m_dPCDPLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dPCDPLimit)),_T("-"),_T(CStr::FloatToStr(dPCDErrMeasured)),_T("dB"),_T("Peak CDP PASS"),"Peak CDP")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_dPCDPLimit)),_T("-"),_T(CStr::FloatToStr(dPCDErrMeasured)),_T("dB"),_T("Peak CDP FAIL"),"Peak CDP")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::TDTestOBW()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_OccupiedBandWidth_Test_BaseItemCode;
	double dOBWMeasured;
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAOBW(m_iMeasureCount,&dOBWMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAOBW Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMAOBW Fail!"))
			return false;
	}
	if (dOBWMeasured<m_dOBWLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dOBWLimit)),_T("-"),_T(CStr::FloatToStr(dOBWMeasured)),_T("dB"),_T("OBW PASS"),"OBW")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_OBW_OUTOFRANGE,_T(CStr::FloatToStr(m_dOBWLimit)),_T("-"),_T(CStr::FloatToStr(dOBWMeasured)),_T("dB"),_T("OBW FAIL"),"OBW")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;
}
bool CTDSMeasLoop::TDTestACLR()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_ACLR_N10_Test_BaseItemCode;
	double dACLRMeasured[4];
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAACLR(m_iMeasureCount,dACLRMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAACLR Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMAACLR Fail!"))
			return false;
	}
	for (int i=0;i<4;i++)
	{
		if (dACLRMeasured[i]<m_dvACLRLimit[i])
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dvACLRLimit[i])),_T("-"),_T(CStr::FloatToStr(dACLRMeasured[i])),_T("dBc"),_T("ACLR PASS"),"ACLR")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ACLR_OUTOFRANGE,_T(CStr::FloatToStr(m_dvACLRLimit[i])),_T("-"),_T(CStr::FloatToStr(dACLRMeasured[i])),_T("dBc"),_T("ACLR FAIL"),"ACLR")
				iFailFlag++;
		}
	}
	

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::TDTestSEMask()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_ACLR_N10_Test_BaseItemCode;
	int iPass=0;
	double dSEMaskMeasured[4];
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMASEMask(m_iMeasureCount,&iPass,dSEMaskMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMASEMask Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMASEMask Fail!"))
			return false;
	}
	
		if (0!=iPass)
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("-"),_T("-"),_T("-"),_T("-"),_T("SEMASK PASS"),"SEMASK")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_SEMASK_OUTOFRANGE,_T("-"),_T("-"),_T("-"),_T("-"),_T("SEMASK FAIL"),"SEMASK")
				iFailFlag++;
		}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;
}
bool CTDSMeasLoop::TDTestPwrTempate()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_ACLR_N10_Test_BaseItemCode;
	int iPass=0;
	double dPwrTpMeasured[3];
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAPwrTemplate(m_iMeasureCount,dPwrTpMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAPwrTemplate Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMAPwrTemplate Fail!"))
			return false;
	}

	if (dPwrTpMeasured[0]<m_dvPwrTemLimit[0])
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(dPwrTpMeasured[0])),_T("-"),_T(CStr::FloatToStr(m_dvPwrTemLimit[0])),_T("dBm"),_T("OffPwrM PASS"),"OffPwrM")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_SEMASK_OUTOFRANGE,_T(CStr::FloatToStr(dPwrTpMeasured[0])),_T("-"),_T(CStr::FloatToStr(m_dvPwrTemLimit[0])),_T("dBm"),_T("OffPwrM FAIL"),"OffPwrM")
			iFailFlag++;
	}
	if (dPwrTpMeasured[1]<m_dvPwrTemLimit[1])
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(dPwrTpMeasured[1])),_T("-"),_T(CStr::FloatToStr(m_dvPwrTemLimit[1])),_T("dBm"),_T("OffPwrP PASS"),"OffPwrP")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_SEMASK_OUTOFRANGE,_T(CStr::FloatToStr(dPwrTpMeasured[1])),_T("-"),_T(CStr::FloatToStr(m_dvPwrTemLimit[1])),_T("dBm"),_T("OffPwrP FAIL"),"OffPwrP")
			iFailFlag++;
	}

	if (dPwrTpMeasured[2]<m_dvPwrTemLimit[2])
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(dPwrTpMeasured[2])),_T("-"),_T(CStr::FloatToStr(m_dvPwrTemLimit[2])),_T("dBm"),_T("Pwr50  PASS"),"Pwr50 ")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_SEMASK_OUTOFRANGE,_T(CStr::FloatToStr(dPwrTpMeasured[2])),_T("-"),_T(CStr::FloatToStr(m_dvPwrTemLimit[2])),_T("dBm"),_T("Pwr50  FAIL"),"Pwr50 ")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::TDTestRxBER()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_BER_Test_BaseItemCode;
	double dBERMeasured;
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMABER(m_iBERSamples,m_dRxCellPower,&dBERMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMABER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMABER Fail!"))
			return false;
	}
	if (dBERMeasured<m_dBERLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dBERLimit)),_T("-"),_T(CStr::FloatToStr(dBERMeasured)),_T("%"),_T("BER PASS"),"BER")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_BER_OUTOFRANGE,_T(CStr::FloatToStr(m_dBERLimit)),_T("-"),_T(CStr::FloatToStr(dBERMeasured)),_T("%"),_T("BER FAIL"),"BER")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::TDTestModAnalysis()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_EVMRMSAvg_Test_BaseItemCode;
	double dRho,dEVM,dPVE,dPER,dMER,dOgnOfs,dIQI;
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAModAnalysis(m_iMeasureCount,&dRho,&dEVM,&dPVE,&dPER,&dMER,&dOgnOfs,&dIQI))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAModAnalysis Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ITDSCDMAModAnalysis Fail!"))
			return false;
	}
	if (dRho>m_dRhoLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T(CStr::FloatToStr(m_dRhoLimit)),_T(CStr::FloatToStr(dRho)),_T("-"),_T("Rho PASS"),"Rho")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_EVM_OUTOFRANGE,_T("1"),_T(CStr::FloatToStr(m_dRhoLimit)),_T(CStr::FloatToStr(dRho)),_T("-"),_T("Rho FAIL"),"Rho")
			iFailFlag++;
	}
	if (dEVM<m_dEVMLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dEVMLimit)),_T("-"),_T(CStr::FloatToStr(dEVM)),_T("%"),_T("EVM PASS"),"EVM")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_EVM_OUTOFRANGE,_T(CStr::FloatToStr(m_dEVMLimit)),_T("-"),_T(CStr::FloatToStr(dEVM)),_T("%"),_T("EVM FAIL"),"EVM")
			iFailFlag++;
	}
/*
	if (dPVE<m_dPVELimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dPVELimit)),_T("-"),_T(CStr::FloatToStr(dPVE)),_T("%"),_T("Peak Vec Err PASS"),"Peak Vec Err")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_EVM_OUTOFRANGE,_T(CStr::FloatToStr(m_dPVELimit)),_T("-"),_T(CStr::FloatToStr(dPVE)),_T("%"),_T("Peak Vec Err FAIL"),"Peak Vec Err")
			iFailFlag++;
	}
	if (dPER<m_dPERLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dPERLimit)),_T("-"),_T(CStr::FloatToStr(dPER)),_T("deg"),_T("Phase Error PASS"),"Phase Err")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_PHASEERR_OUTOFRANGE,_T(CStr::FloatToStr(m_dPERLimit)),_T("-"),_T(CStr::FloatToStr(dPER)),_T("deg"),_T("Phase Error FAIL"),"Phase Err")
			iFailFlag++;
	}
	if (dMER<m_dMagERRLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMagERRLimit)),_T("-"),_T(CStr::FloatToStr(dMER)),_T("%"),_T("Mag Error PASS"),"Mag Err")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MAGTDERR_OUTOFRANGE,_T(CStr::FloatToStr(m_dMagERRLimit)),_T("-"),_T(CStr::FloatToStr(dMER)),_T("%"),_T("Mag Error FAIL"),"Mag Err")
			iFailFlag++;
	}
	if (dOgnOfs<m_dIQOffsetLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dIQOffsetLimit)),_T("-"),_T(CStr::FloatToStr(dOgnOfs)),_T("dB"),_T("Origin Offset PASS"),"Origin Offset")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ORIGINOFFSET_OUTOFRANGE,_T(CStr::FloatToStr(m_dIQOffsetLimit)),_T("-"),_T(CStr::FloatToStr(dOgnOfs)),_T("dB"),_T("Origin Offset FAIL"),"Origin Offset")
			iFailFlag++;
	}

	if (dIQI<m_dIQImLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dIQImLimit)),_T("-"),_T(CStr::FloatToStr(dIQI)),_T("dBc"),_T("IQ Imbalance PASS"),"IQ Imbalance")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MINPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dIQImLimit)),_T("-"),_T(CStr::FloatToStr(dIQI)),_T("dBc"),_T("IQ Imbalance FAIL"),"IQ Imbalance")
			iFailFlag++;
	}*/

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CTDSMeasLoop::InitData(
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

	itrFind=pcSettingMap->find(_T("BERSamples"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'BERSamples' from ini file,Use default 10000!");
		m_iBERSamples=10000;

	}
	else
	{
		m_iBERSamples=CStr::StrToInt(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("MaxPowerLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'MaxPowerLimit' from ini file!Use default 21-25");
		m_dMaxPowerLimit.SetRange(21,25);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_dMaxPowerLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("MinPowerLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'MinPowerLimit' from ini file!Use default -70~-50!");
		m_dMinPowerLimit.SetRange(-70,-50);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_dMinPowerLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("FERLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'FERLimit' from ini file,Use default 0.1!");
		m_dFERLimit=0.1;

	}
	else
	{
		m_dFERLimit=CStr::StrToFloat(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("PCDPLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'PCDPLimit' from ini file,Use default -20!");
		m_dPCDPLimit=-20;

	}
	else
	{
		m_dPCDPLimit=CStr::StrToFloat(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("OBWLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'OBWLimit' from ini file,Use default 1.6!");
		m_dOBWLimit=1.6;

	}
	else
	{
		m_dOBWLimit=CStr::StrToFloat(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("RhoLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RhoLimit' from ini file,Use default 0.9!");
		m_dRhoLimit=0.9;

	}
	else
	{
		m_dRhoLimit=CStr::StrToFloat(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("EVMLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'EVMLimit' from ini file,Use default 17.5!");
		m_dEVMLimit=17.5;

	}
	else
	{
		m_dEVMLimit=CStr::StrToFloat(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("PVELimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'PVELimit' from ini file,Use default 223!");
		m_dPVELimit=223;

	}
	else
	{
		m_dPVELimit=CStr::StrToFloat(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("PERLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'PERLimit' from ini file,Use default 223!");
		m_dPERLimit=223;

	}
	else
	{
		m_dPERLimit=CStr::StrToFloat(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("MagERRLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'MagERRLimit' from ini file,Use default 223!");
		m_dMagERRLimit=223;

	}
	else
	{
		m_dMagERRLimit=CStr::StrToFloat(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("ORGOFSLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'ORGOFSLimit' from ini file,Use default 223!");
		m_dIQOffsetLimit=223;

	}
	else
	{
		m_dIQOffsetLimit=CStr::StrToFloat(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("IQImLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'IQImLimit' from ini file,Use default 223!");
		m_dIQImLimit=223;

	}
	else
	{
		m_dIQImLimit=CStr::StrToFloat(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("SEMaskLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'SEMaskLimit' from ini file! Use default value");
		strValue="0,0,0,0";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvSEMaskLimit,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvSEMaskLimit,strVtr);

	}

	itrFind=pcSettingMap->find(_T("PwrTemLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'PwrTemLimit' from ini file! Use default value");
		strValue="-63.5,-63.5,-63.5";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvPwrTemLimit,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvPwrTemLimit,strVtr);

	}
	itrFind=pcSettingMap->find(_T("ACLRLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'ACLRLimit' from ini file! Use default value");
		strValue="-33,-33,-43,-43";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvACLRLimit,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvACLRLimit,strVtr);

	}
	itrFind=pcSettingMap->find(_T("RxCellPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RxCellPower' from ini file,Use default -106!");
		m_dRxCellPower=-106;

	}
	else
	{
		m_dRxCellPower=CStr::StrToFloat(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("BERLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'BERLimit' from ini file,Use default 0.1!");
		m_dBERLimit=0.1;

	}
	else
	{
		m_dBERLimit=CStr::StrToFloat(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("RxPowerList"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RxPowerList' from ini file,Use default -65!");
		strValue="-65";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvRxPowerList,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvRxPowerList,strVtr);
	}
	itrFind=pcSettingMap->find(_T("RxLevelHiLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RxLevelHiLimit' from ini file,Use default -63!");
		strValue="-63";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvRxLevelHLList,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvRxLevelHLList,strVtr);
	}
	itrFind=pcSettingMap->find(_T("RxLevelLoLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RxLevelLoLimit' from ini file,Use default -67!");
		strValue="-67";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvRxLevelLLList,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvRxLevelLLList,strVtr);
	}
	itrFind=pcSettingMap->find(_T("RxLevelDelayMs"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RxLevelDelayMs' from ini file,Use default 1000!");
		m_iRxlevelDelayMs=1000;

	}
	else
	{
		strValue=itrFind->second;
		m_iRxlevelDelayMs=CStr::StrToFloat(strValue);
	}
	InitData();
	return true;
}

bool CTDSMeasLoop::InitData()
{
	m_pFuncTDSTestDev=m_piTesterDevice->m_piFuncWCDMATest;
	return true;
}
bool CTDSMeasLoop::SetTDTestLOSS()
{
	CString strMsg;
	double dLoss;
	m_vCableLoss.clear();
	for(int i=0;i<3;i++)
	{
		if(!m_LossFinder.GetWCDMALoss(m_strTestBand,i,dLoss))
		{
			strMsg.Format("WCDMA Get Loss Band=%s ,ChannelType=%d Fail",m_strTestBand,i);
			LogTrace(MSG_ERROR,strMsg);
			CalFailLog(_T("_"),_T("_"),1001,strMsg);
			return false;
		}
		m_vCableLoss.push_back(dLoss);
	}

	if(DEVICE_SUCCESS!=m_pFuncTDSTestDev->ITDSCDMASetLoss(m_iTestBand,m_vCableLoss))
	{
		LogTrace(MSG_ERROR,"Set Cableloss device fail");
		CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		return false;

	}

	return  true;
}