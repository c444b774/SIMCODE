#include "stdafx.h"
#include "CDMATestMeasureloop.h"

RF_IMPLEMENT_DYNCREATE(CCDMATestMeasureLoop)

CCDMATestMeasureLoop::CCDMATestMeasureLoop()
{
	m_mapClassFunc[_T("CDMAMeasMainFunc")]=&CCDMATestMeasureLoop::CCDMATestMeasureLoopMainFunc;
	m_mapClassFunc[_T("CDMAMaxPower")]=&CCDMATestMeasureLoop::CDMATestMaxPower;
	m_mapClassFunc[_T("CDMAMinPower")]=&CCDMATestMeasureLoop::CDMATestMinPower;
	m_mapClassFunc[_T("CDMAWFQ")]=&CCDMATestMeasureLoop::CDMATestWFQ;
	m_mapClassFunc[_T("CDMAACPR")]=&CCDMATestMeasureLoop::CDMATestACPR;
	m_mapClassFunc[_T("CDMARx")]=&CCDMATestMeasureLoop::CDMATestRx;
	m_mapClassFunc[_T("CDMATestTROLPC")]=&CCDMATestMeasureLoop::CDMATestTROLPC;
	m_mapClassFunc[_T("CDMAHandOver")]=&CCDMATestMeasureLoop::CDMATestHandOver;
	

}

CCDMATestMeasureLoop::~CCDMATestMeasureLoop()
{
	
}

bool CCDMATestMeasureLoop::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CCDMATestMeasureLoop::Handle()
{
	if((!DoProcess())||(m_iFailFlag!=0))
	{
		m_pPhone->FTM_CDMA2000_EndCall(300);
      return false;
	}
		
	return true;
}

bool CCDMATestMeasureLoop::CCDMATestMeasureLoopMainFunc()
{
	m_iItemCode=CDMA_SetCableLoss_BaseItemCode;
	if (!SetCDMATestLOSS())
	{
		LogTrace(MSG_ERROR,_T("SetCDMATestLOSS Fail!"))
			CalFailLog(_T("_"),_T("_"),LOSS_SET_FAIL,"SetCDMATestLOSS Fail!");
		//		   m_iErrorcode=iErrorcode;
		m_iFailFlag++;
		return false;
	}
	TestPassLog(m_strCurBand,"_","_","_","_","_","Set CableLOSS Pass");
	for (int i=0;i<m_iTestChan.size();i++)
	{
		m_iCurrentCH=m_iTestChan[i];
		for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)			
		{
			FPClassFunc fpTestFunc=*itrFP;
			if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
				return false;
		}
	}
	return true;
}

bool CCDMATestMeasureLoop::CDMATestTROLPC()
{
	int iErrorcode;
	bool bRet=false;
	m_iItemCode=CDMA_MaxPower_Test_BaseItemCode;
	int isFail=1;
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestTROLPC(&isFail))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("ICDMATestTROLPC(Device) Fail!"))
			m_iErrorcode=iErrorcode;
		m_iFailFlag++;
		return false;
	}	

	if (isFail==0)
	{
		TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),"0","0","0","-","TROLPC Pass","TROLPC");
	}
	else
	{
		TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),m_iErrorcode,"0","0",CStr::IntToStr(isFail),"-","TROLPC Fail","TROLPC");
		m_iFailFlag++;
		if (m_bIsStopWhileFail)
		{
			return false;
		}
	}

	return true;

}

bool CCDMATestMeasureLoop::CDMATestMaxPower()
{ 
	int iErrorcode;
	bool bRet=false;
	m_iItemCode=CDMA_MaxPower_Test_BaseItemCode;
	double dMaxPower=0;
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestMaxPower(m_iBurstQty,&dMaxPower))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("ICDMATestMaxPower(Device) Fail!"))
		m_iErrorcode=iErrorcode;
		m_iFailFlag++;
		return false;
	}	

	if (dMaxPower>m_dVtrMaxPwrLim[0]&&dMaxPower<m_dVtrMaxPwrLim[1])
	{
		TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(m_dVtrMaxPwrLim[1]),CStr::FloatToStr(m_dVtrMaxPwrLim[0]),CStr::FloatToStr(dMaxPower),"dBm","MaxPower Pass","MaxPower");
	}
	else
	{
		TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),m_iErrorcode,CStr::FloatToStr(m_dVtrMaxPwrLim[1]),CStr::FloatToStr(m_dVtrMaxPwrLim[0]),CStr::FloatToStr(dMaxPower),"dBm","MaxPower Fail","MaxPower");
		m_iFailFlag++;
		if (m_bIsStopWhileFail)
		{
			return false;
		}
	}
	
	return true;
}
bool CCDMATestMeasureLoop::CDMATestHandOver()
{
	int iErrorcode;
	bool bRet=false;
	m_iItemCode=CDMA_Call_HandOver_Device_BaseItemCode;
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestHandover(m_iCurrBand,m_iCurrentCH))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("ICDMATestHandOver(Device) Fail!"))
			m_iErrorcode=iErrorcode;
		m_iFailFlag++;
		return false;
	}
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestSetPower(-65,0,2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("ICDMATestSetPower(Device) Fail!"))
			m_iErrorcode=iErrorcode;
		m_iFailFlag++;
		return false;
	}

	CString strESN,strMsg;
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

	m_iItemCode=CDMA_Call_HandOver_Phone_BaseItemCode;
	if((iErrorcode=m_pPhone->FTM_CDMA_BER_Handover(1,0,m_iCurrBand,m_iCurrentCH,0,FTM_CDMA2000_NS_RC_1))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("FTM_CDMA_HandoverCall(Handset) Fail!"))
			m_iErrorcode=iErrorcode;

		CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA_HandoverCall Fail!");
		m_iFailFlag++;
		return false;
	}

	if (m_strTesterDevice=="CMW500")
	{
		if((iErrorcode=m_pPhone->FTM_CDMA_2000_HardHandOff(m_iCurrBand,m_iCurrentCH))!=PHONE_SUCCESS)
		{           
			LogTrace(MSG_ERROR,_T("FTM_CDMA_2000_HardHandOff(Handset) Fail!"))
				m_iErrorcode=iErrorcode;

			CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA_2000_HardHandOff Fail!");
			m_iFailFlag++;
			return false;
		}

	}
	TestPassLog(m_strCurBand,CStr::IntToStr(m_iCurrentCH),"_","_","_","_","HandOver Pass");
	return true;
	
}
bool CCDMATestMeasureLoop::CDMATestRx()
{
	int iErrorcode,iLogRXLev;
	bool bRet=false;
	m_iItemCode=CDMA_MaxPower_Test_BaseItemCode;
	double dCellPower=-105;
	double dRxSens=0,EbNt=0;
	double dSER_Calculated=0,dFER_Calculated=0,dRxlevRes=0;
	unsigned long iTotalSymbols=0;
	unsigned long iTotalErrorSymbols=0;
	unsigned long iTotalFrames=0;
	unsigned long iTotalFrameErrors=0;
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestSetPower(dCellPower,24,2)!=DEVICE_SUCCESS))
	{
		LogTrace(MSG_ERROR,_T("CDMA Test Device set power device Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,"CDMA Test Device set power device Fail!");
		m_iFailFlag++;
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_CDMA2000_NS_GetRXRESULT_BYPHONE(m_iCurrBand,1,0,FTM_CDMA2000_NS_RC_1,FTM_CDMA2000_NS_REV_FCH_FULL_RATE,53760,70,iTotalSymbols,iTotalErrorSymbols,iTotalFrames,iTotalFrameErrors,dSER_Calculated,dFER_Calculated,0)!=PHONE_SUCCESS))
	{
		LogTrace(MSG_ERROR,_T("CDMA Test StartRXMeasurment phone Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,"CDMA Test StartRXMeasurment phone Fail!");
		m_iFailFlag++;
		return false;
	}
	if (dSER_Calculated<6.3)
	{
		dCellPower=-108;
		if((iErrorcode=m_pFunCDMATestDev->ICDMATestSetPower(dCellPower,24,2)!=DEVICE_SUCCESS))
		{
			LogTrace(MSG_ERROR,_T("CDMA Test Device set power device Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,"CDMA Test Device set power device Fail!");
			m_iFailFlag++;
			return false;
		}

		if((iErrorcode=m_pPhone->FTM_CDMA2000_NS_GetRXRESULT_BYPHONE(m_iCurrBand,1,0,FTM_CDMA2000_NS_RC_1,FTM_CDMA2000_NS_REV_FCH_FULL_RATE,53760,70,iTotalSymbols,iTotalErrorSymbols,iTotalFrames,iTotalFrameErrors,dSER_Calculated,dFER_Calculated,0)!=PHONE_SUCCESS))
		{
			LogTrace(MSG_ERROR,_T("CDMA Test StartRXMeasurment phone Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,"CDMA Test StartRXMeasurment phone Fail!");
			m_iFailFlag++;
			return false;
		}
	}
	m_pPhone->FTM_CDMA2000_NS_Stop();
	EbNt = (-1)*(log10 (dSER_Calculated/100)+0.67123)/0.087401;
	dRxSens = dCellPower - (EbNt-3.67);	

	
	if (dRxSens<=m_dRxSenLim)
	{
		TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(m_dRxSenLim),"_",CStr::FloatToStr(dRxSens),"_","RxSens Pass","RxSens");
	}
	else
	{
		TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(m_dRxSenLim),"_",CStr::FloatToStr(dRxSens),"_","RxSens Fail","RxSens");
		m_iFailFlag++;
		if (m_bIsStopWhileFail)
		{
			return false;
		}
	}
	CRangePair<double> RxLevSpec;
	for (int j=0;j<m_dVtrRxLevPwrLev.size();j++)
	{
		if((iErrorcode=m_pFunCDMATestDev->ICDMATestSetPower(m_dVtrRxLevPwrLev[j],24,2)!=DEVICE_SUCCESS))
		{
			LogTrace(MSG_ERROR,_T("CDMA Test RxLevelMeasurment device Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,"CDMA Test RxLevelMeasurment device Fail!");
			m_iFailFlag++;
			return false;
		}

		if(iErrorcode=m_pPhone->FTM_CDMA2000_NS_Start(FTM_CDMA2000_NS_DR_102_4,m_iCurrBand,FALSE)!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("FTM_CDMA2000_NS_Start Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA2000_NS_Start Fail!");
			m_iFailFlag++;
			return false;
		}

		if(iErrorcode=m_pPhone->FTM_CDMA2000_NS_GetRxLevel_BYPHONE(m_iCurrBand,m_iCurrentCH,dRxlevRes,m_iDelayForRxlev)!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("FTM_CDMA2000_NS_GetRxLevel_BYPHONE Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA2000_NS_GetRxLevel_BYPHONE Fail!");
			m_iFailFlag++;
			return false;
		}
		CString strTemp,strTemp1;
		RxLevSpec.SetRange(m_dVtrRxLevLimMax[j],m_dVtrRxLevLimMin[j]);

		iLogRXLev=-m_dVtrRxLevPwrLev[j]+0.5;
		if (RxLevSpec.InRange(dRxlevRes))
		{
			strTemp.Format("RxLev Pass,PwrLev=%.1f",m_dVtrRxLevPwrLev[j]);
			strTemp1.Format("RxLev_%d",iLogRXLev);
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(RxLevSpec.GetMax()),CStr::FloatToStr(RxLevSpec.GetMin()),CStr::FloatToStr(dRxlevRes),"_",_T(strTemp),strTemp1);
		}
		else
		{
			strTemp.Format("RxLev Fail,PwrLev=%.1f",m_dVtrRxLevPwrLev[j]);
			strTemp1.Format("RxLev_%d",iLogRXLev);
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(RxLevSpec.GetMax()),CStr::FloatToStr(RxLevSpec.GetMin()),CStr::FloatToStr(dRxlevRes),"_",_T(strTemp),strTemp1);
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
	
	}
	return true;

}
bool CCDMATestMeasureLoop::CDMATestMinPower()
{
	int iErrorcode;
	bool bRet=false;
	m_iItemCode=CDMA_MaxPower_Test_BaseItemCode;
	double dMinPower=0;
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestMinPower(m_iBurstQty,&dMinPower))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("ICDMATestMinPower(Device) Fail!"))
			m_iErrorcode=iErrorcode;
		m_iFailFlag++;
		return false;
	}	

	if (dMinPower>m_dVtrMinPwrLim[0]&&dMinPower<m_dVtrMinPwrLim[1])
	{
		TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(m_dVtrMinPwrLim[1]),CStr::FloatToStr(m_dVtrMinPwrLim[0]),CStr::FloatToStr(dMinPower),"dBm","MinPower Pass","MinPower");
	}
	else
	{
		TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),m_iErrorcode,CStr::FloatToStr(m_dVtrMinPwrLim[1]),CStr::FloatToStr(m_dVtrMinPwrLim[0]),CStr::FloatToStr(dMinPower),"dBm","MinPower Fail","MinPower");
		m_iFailFlag++;
		if (m_bIsStopWhileFail)
		{
			return false;
		}
	}	
	return true;
}
bool CCDMATestMeasureLoop::CDMATestWFQ()
{
	int iErrorcode;
	bool bRet=false;
	m_iItemCode=CDMA_MaxPower_Test_BaseItemCode;
	double dRho=0,dFER=0,dTER=0,dCFT=0,dPER=0,dMER=0,dEVM=0;
	CString strReservedTemp;
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestWFQ(m_iBurstQty,&dRho,&dFER,&dTER,&dCFT,&dPER,&dMER,&dEVM))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("ICDMATestWFQ(Device) Fail!"))
			m_iErrorcode=iErrorcode;
		m_iFailFlag++;
		return false;
	}
	
	
		CRangePair<double> FeedthruSpec;
		FeedthruSpec.SetRange(m_dVtrFeedLim[0],m_dVtrFeedLim[1]);
		
		strReservedTemp.Format("%.2f",dCFT);
		if (FeedthruSpec.InRange(dCFT))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(FeedthruSpec.GetMax()),CStr::FloatToStr(FeedthruSpec.GetMin()),strReservedTemp,"dBc","FeedThr Pass","FeedThr");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(FeedthruSpec.GetMax()),CStr::FloatToStr(FeedthruSpec.GetMin()),strReservedTemp,"dBc","FeedThr Fail","FeedThr");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
		
		CRangePair<double> EVMSpec;
		EVMSpec.SetRange(m_dVtrEVMLim[0],m_dVtrEVMLim[1]);

		strReservedTemp.Format("%.2f",dEVM);
		if (EVMSpec.InRange(dEVM))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(EVMSpec.GetMax()),CStr::FloatToStr(EVMSpec.GetMin()),strReservedTemp,"%","EVM Pass","EVM");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(EVMSpec.GetMax()),CStr::FloatToStr(EVMSpec.GetMin()),strReservedTemp,"%","EVM Fail","EVM");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
		
		CRangePair<double> FERSpec;
		FERSpec.SetRange(m_dVtrFERLim[0],m_dVtrFERLim[1]);

		strReservedTemp.Format("%.2f",dFER);
		if (FERSpec.InRange(dFER))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(FERSpec.GetMax()),CStr::FloatToStr(FERSpec.GetMin()),strReservedTemp,"Hz","FER Pass","FER");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(FERSpec.GetMax()),CStr::FloatToStr(FERSpec.GetMin()),strReservedTemp,"Hz","FER Fail","FER");
			m_iFailFlag++;		  
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
		
		CRangePair<double> MagSpec;
		MagSpec.SetRange(m_dVtrMagLim[0],m_dVtrMagLim[1]);

		strReservedTemp.Format("%.2f",dMER);
		if (MagSpec.InRange(dMER))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(MagSpec.GetMax()),CStr::FloatToStr(MagSpec.GetMin()),strReservedTemp,"%","Magnitude Pass","Mag");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(MagSpec.GetMax()),CStr::FloatToStr(MagSpec.GetMin()),strReservedTemp,"%","Magnitude Fail","Mag");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
	
		CRangePair<double> PERSpec;
		PERSpec.SetRange(m_dVtrPhaseLim[0],m_dVtrPhaseLim[1]);

		strReservedTemp.Format("%.2f",dPER);
		if (PERSpec.InRange(dPER))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(PERSpec.GetMax()),CStr::FloatToStr(PERSpec.GetMin()),strReservedTemp,"deg","PhaseERR Pass","PhaseERR");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(PERSpec.GetMax()),CStr::FloatToStr(PERSpec.GetMin()),strReservedTemp,"deg","PhaseERR Fail","PhaseERR");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
		
	
		CRangePair<double> RHOSpec;
		RHOSpec.SetRange(m_dVtrRHOLim[0],m_dVtrRHOLim[1]);
		strReservedTemp.Format("%.4f",dRho);
		if (RHOSpec.InRange(dRho))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(RHOSpec.GetMax()),CStr::FloatToStr(RHOSpec.GetMin()),strReservedTemp,"dBm","RHO Pass","RHO");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(RHOSpec.GetMax()),CStr::FloatToStr(RHOSpec.GetMin()),strReservedTemp,"dBm","RHO Fail","RHO");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
	
	
		CRangePair<double> TERSpec;
		TERSpec.SetRange(m_dVtrTimeLim[0],m_dVtrTimeLim[1]);

		strReservedTemp.Format("%.2f",dTER);
		if (TERSpec.InRange(dTER))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(TERSpec.GetMax()),CStr::FloatToStr(TERSpec.GetMin()),strReservedTemp,"us","TimeERR Pass","TimeERR");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(TERSpec.GetMax()),CStr::FloatToStr(TERSpec.GetMin()),strReservedTemp,"us","TimeERR Fail","TimeERR");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
	
	return true;
}
bool CCDMATestMeasureLoop::CDMATestACPR()
{
	int iErrorcode;
	bool bRet=false;
	m_iItemCode=CDMA_MaxPower_Test_BaseItemCode;
	int isFail=1;
	double dACPR[4];
	if((iErrorcode=m_pFunCDMATestDev->ICDMATestACPR(m_iBurstQty,dACPR,&isFail))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("ICDMATestACPR(Device) Fail!"))
			m_iErrorcode=iErrorcode;
		m_iFailFlag++;
		return false;
	}
	if (isFail==0)
	{
		TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),_T("0"),_T("0"),CStr::IntToStr(isFail),"_","ACPR Pass","ACPR");
	}
	else
	{
		CRangePair<double> ACPR_ADJSpec;
		ACPR_ADJSpec.SetRange(m_dVtrADJLim[0],m_dVtrADJLim[1]);

		CString strReservedTemp;
		strReservedTemp.Format("%.2f",dACPR[0]);
		if (ACPR_ADJSpec.InRange(dACPR[0]))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(ACPR_ADJSpec.GetMax()),CStr::FloatToStr(ACPR_ADJSpec.GetMin()),strReservedTemp,"dBc","ACPR_ADJ_L Pass","ACPR_ADJ_L");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(ACPR_ADJSpec.GetMax()),CStr::FloatToStr(ACPR_ADJSpec.GetMin()),strReservedTemp,"dBc","ACPR_ADJ_L Fail","ACPR_ADJ_L");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}
		strReservedTemp.Format("%.2f",dACPR[1]);
		if (ACPR_ADJSpec.InRange(dACPR[1]))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(ACPR_ADJSpec.GetMax()),CStr::FloatToStr(ACPR_ADJSpec.GetMin()),strReservedTemp,"dBc","ACPR_ADJ_H Pass","ACPR_ADJ_H");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(ACPR_ADJSpec.GetMax()),CStr::FloatToStr(ACPR_ADJSpec.GetMin()),strReservedTemp,"dBc","ACPR_ADJ_H Fail","ACPR_ADJ_H");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}

		CRangePair<double> ACPR_ALTSpec;
		ACPR_ALTSpec.SetRange(m_dVtrALTLim[0],m_dVtrALTLim[1]);
		strReservedTemp.Format("%.2f",dACPR[2]);
		if (ACPR_ALTSpec.InRange(dACPR[2]))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(ACPR_ALTSpec.GetMax()),CStr::FloatToStr(ACPR_ALTSpec.GetMin()),strReservedTemp,"dBc","ACPR_ALT_L Pass","ACPR_ALT_L");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(ACPR_ALTSpec.GetMax()),CStr::FloatToStr(ACPR_ALTSpec.GetMin()),strReservedTemp,"dBc","ACPR_ALT_L Fail","ACPR_ALT_L");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}	
		strReservedTemp.Format("%.2f",dACPR[3]);
		if (ACPR_ALTSpec.InRange(dACPR[3]))
		{
			TestPassLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),CStr::FloatToStr(ACPR_ALTSpec.GetMax()),CStr::FloatToStr(ACPR_ALTSpec.GetMin()),strReservedTemp,"dBc","ACPR_ALT_H Pass","ACPR_ALT_H");
		}
		else
		{
			TestFailLogEx(m_strCurBand,CStr::IntToStr(m_iCurrentCH),iErrorcode,CStr::FloatToStr(ACPR_ALTSpec.GetMax()),CStr::FloatToStr(ACPR_ALTSpec.GetMin()),strReservedTemp,"dBc","ACPR_ALT_H Fail","ACPR_ALT_H");
			m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				return false;
			}
		}

	}
	return true;
}

 bool CCDMATestMeasureLoop::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
    CStringStringMapItr itrFind;
	CString strTemp;
    CString strMainFun;
	CStringVtr strVtrTemp;

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
		 strTemp=itrFind->second;
		 m_iCurrBand=CStr::StrToInt(strTemp);
		 m_strCurBand.Format("CDMA%d",m_iCurrBand);		
		 if (m_iCurrBand!=CDMA_BC0_BAND_ID && m_iCurrBand!=CDMA_BC1_BAND_ID&&m_iCurrBand!=CDMA_BC10_BAND_ID)
		 {
			 strTemp.Format("Band=%s,not support yet",strTemp);
			 LogTrace(MSG_ERROR,_T(strTemp));
				 return false;
		 }
	 }

	 itrFind=pcSettingMap->find(_T("UseFollowPara"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,_T("Not Find UseFollowPara"));
		 return false;
	 }
	 else
	 {
		 m_bUseCfgPara=CStr::StrToBool(itrFind->second);
	 }


	 if (m_bUseCfgPara)
	 {
		 itrFind=pcSettingMap->find(_T("TestChan"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find TestChan"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2IntVtr(m_iTestChan,strVtrTemp);
		 }
		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("RxSen"));
		 if(itrFind==pcSettingMap->end())
		 {
			 itrFind=pcSettingMap->find(_T("CellPwr"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_FATAL,_T("Not Find CellPwr"));
				 return false;
			 }
			 else
			 {
				 strTemp=itrFind->second;
				 CStr::ParseString(strTemp,_T(","),strVtrTemp);
				 m_dRxSenLim=CStr::StrToFloat(strVtrTemp[3]);
				 
			 }
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 m_dRxSenLim=CStr::StrToFloat(strTemp);			
		 }	
		 
		 strTemp.Empty();
		 itrFind=pcSettingMap->find(_T("BurstQty"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find BurstQty"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 m_iBurstQty=CStr::StrToInt(strTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("RHO"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find RHO"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrRHOLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("FER"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find FER"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrFERLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("TimeERR"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find TimeERR"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrTimeLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("FeedThrough"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find FeedThrough"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrFeedLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("PhaseERR"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find PhaseERR"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrPhaseLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("MagnitudeERR"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find MagnitudeERR"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrMagLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("EVM"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find EVM"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrEVMLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("MaxPower"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find MaxPower"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrMaxPwrLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("MinPower"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find MinPower"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrMinPwrLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("ADJ_ACPR"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find ADJ_ACPR"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrADJLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("ALT_ACPR"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find ALT_ACPR"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrALTLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("SER"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find SER"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrSerLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("RXLevelPower"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find RXLevelPower"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrRxLevPwrLev,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("RXLevelLimMax"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find RXLevelLimMax"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrRxLevLimMax,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("RXLevelLimMin"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find RXLevelLimMin"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrRxLevLimMin,strVtrTemp);
		 }

		 strTemp.Empty();
		 itrFind=pcSettingMap->find(_T("RXLevelDelay"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_WARNING,_T("Not Find RXLevelDelay use default 1000"));
			 m_iDelayForRxlev=500;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 m_iDelayForRxlev=CStr::StrToInt(strTemp);
		 }
	 }

	    strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("FailRunList"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_WARNING,_T("Not Find FailRunList,default is """));
			 m_strFailRunList="";
		 }
		 else
		 {
			 m_strFailRunList=itrFind->second;
	
		 }

		   strTemp.Empty();
		
		 itrFind=pcSettingMap->find(_T("IsRandomChannel"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_WARNING,_T("Not Find IsRandomChannel,default is false"));
			 m_bIsRandomCH=false;
		 }
		 else
		 {
			 m_bIsRandomCH=CStr::StrToBool(itrFind->second);
	
		 }

		if(m_bIsRandomCH)
		{
		     srand(GetTickCount()); 
		     int iRandCh=m_iTestChan[rand()%(m_iTestChan.size())];
			 m_iTestChan.clear();
			 m_iTestChan.push_back(iRandCh);

		 }



	 InitData();
	 return true;
 }

 bool CCDMATestMeasureLoop::InitData()
 {
	 m_pFunCDMATestDev=m_piTesterDevice->m_piFuncCDMATest;
	 m_bIsStopWhileFail=m_bIsStopWhenFail;
	 m_iFailFlag=0;
	 return true;
 }

 bool CCDMATestMeasureLoop::SetCDMATestLOSS()
 {
	 CString strMsg;
	 double dLoss;
	 m_vCableLoss.clear();
	 for(int i=0;i<3;i++)
	 {
		 if(!m_LossFinder.GetCDMALoss(m_strCurBand,i,dLoss))
		 {
			 strMsg.Format("CDMA Get Loss Band=CDMA%s ,ChannelType=%d Fail",m_strCurBand,i);
			 LogTrace(MSG_ERROR,strMsg);
			 CalFailLog(_T("_"),_T("_"),1001,strMsg);
			 m_iFailFlag++;
			 return false;
		 }
		 m_vCableLoss.push_back(dLoss);
	 }

	 if(DEVICE_SUCCESS!=m_pFunCDMATestDev->ICDMATestSetLoss(m_iCurrBand,m_vCableLoss))
	 {
		 LogTrace(MSG_ERROR,"Set Cableloss device fail");
		 CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		 m_iFailFlag++;
		 return false;

	 }

	 return  true;

 }

 int CCDMATestMeasureLoop::GetItemCode(int nMode,int Band,int Channel)
 {
	 int nItemCode=CDMA_Init_Test_BaseItemCode;
	 //nItemCode+=nMode*100000;

	 switch(Band)
	 {
	 case CDMA_BC0_BAND_ID:
		 nItemCode+=1*10000;
		 break;
	 case CDMA_BC1_BAND_ID:
		 nItemCode+=2*10000;
		 break;

	 default:
		 return -1;
	 }

	 nItemCode+=CCDMABandInfo::GetChannelType(Band,Channel)*1000;

	 return nItemCode;
 }


  void CCDMATestMeasureLoop::EndCall()
  {
	  m_iItemCode=CDMA_Call_HandOver_Device_BaseItemCode;
	  m_pFunCDMATestDev->ICDMATestEndCall();
	
	  //m_pPhone->FTM_CDMA2000_EndCall();

	  TestPassLog("_","_","_","_","_","_"," End call Pass");
  }