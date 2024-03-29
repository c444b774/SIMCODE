#include "stdafx.h"
#include "ESCalWCDMA.h"
RF_IMPLEMENT_DYNCREATE(CESCalWCDMA)

CESCalWCDMA::CESCalWCDMA()
{
	m_mapClassFunc[_T("ESCalWCDMAMainFunc")]=&CESCalWCDMA::ESCalWCDMAMainFunc;
	m_mapClassFunc[_T("TxLinearizerFunc")]=&CESCalWCDMA::TxLinearizerFunc;
	m_mapClassFunc[_T("TxLinOldFunc")]=&CESCalWCDMA::TxLinOldFunc;
	m_mapClassFunc[_T("TxRxFreqCompFunc")]=&CESCalWCDMA::TxRxFreqCompFunc;
	m_mapClassFunc[_T("TxFreqCompFunc")]=&CESCalWCDMA::TxFreqCompFunc;
	m_mapClassFunc[_T("RxFreqCompFunc")]=&CESCalWCDMA::RxFreqCompFunc;
	m_mapClassFunc[_T("GenerateAndWriteNV")]=&CESCalWCDMA::GenerateAndWriteNV;

}

CESCalWCDMA::~CESCalWCDMA()
{

}

bool CESCalWCDMA::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CESCalWCDMA::Handle()
{
	if(!DoProcess())
	{

		return false;
	}

	CalPassLog("_","_","Enhanced Sweep Calibration Pass");

	return true;
}

bool CESCalWCDMA::ESCalWCDMAMainFunc()
{
	if(!SetWCDMACALLOSS())
		return false;
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CESCalWCDMA::TxLinOldFunc()
{
	CString strMsg;
	int iErrorcode;
	double dUlMHz,dDLMhz;
	int iSegmentNum[4];
	int iNumConfigSigment=60;
	USHORT iSegmentTimeMS=20;
	inumTxlin=0;
	int iTxpurpose=m_bAPTenabled?FTM_Tx_Purpose_Linearizer_Multi_Carrier:m_iTxPurpose;
		

	QMSL_CDMA_TxLin_BetaScaling_struct  aTx_Measured;
	QMSL_CDMA_TxLin_BetaScaling_Result_struct aTx_Result;
	memset(&myTxLinStruct,0,sizeof(TxlinStruct));
	memset(&aTx_Measured,0,sizeof(QMSL_CDMA_TxLin_BetaScaling_struct));
	memset(&aTx_Result,0,sizeof(QMSL_CDMA_TxLin_BetaScaling_Result_struct));
	FTM_Cal_Sweep_Request stSweep[4][128];
	FTM_Cal_Sweep_Response stResponse[4][128];
	memset(&stResponse,0,512*sizeof(FTM_Cal_Sweep_Response));

	//aTx_Measured.iNumMeasuredTxGainStates=m_vPAState.size();
	//aTx_Measured.iTotalNVItems=64;

	aTx_Measured.HDET_OffsetPower_dBm=18;
	aTx_Measured.HDET_SpanPower_dBm=26;
	aTx_Measured.LPM_HDET_OffsetPower_dBm=18;
	aTx_Measured.LPM_HDET_SpanPower_dBm=26;
	aTx_Measured.LPM_HDET_Start_Power_dBm=16;
	aTx_Measured.LPM_HDET_Threshold_Power_dBm=1;
	aTx_Measured.iDo_Not_Extrapolate_Lower_Powers=0;
	aTx_Measured.iEnh_Linearizer_0_NV=0;
	aTx_Measured.iHDET_MaxLim=4095;
	aTx_Measured.iNV_Resolution=10;
	//aTx_Measured.iSkip_NonMonotonic_Items=1;
	//aTx_Measured.iSortingOrder=0;
	//aTx_Measured.iSortNVTxLin=0;	
	//aTx_Measured.iUMTS_TxAGC_PDM_Max=127;
	aTx_Measured.iUse_HDET_V2=1;
	//aTx_Measured.i_TxAGC_PDM_MinGain=0;
	for (int ipaloop=0;ipaloop<4;ipaloop++)
	{	
		for (int i=0;i<128;i++)
		{
			stSweep[ipaloop][i].segLen = iSegmentTimeMS*1000;//
			stSweep[ipaloop][i].masterDev = 1;
			stSweep[ipaloop][i].slaveDev = -1;
			stSweep[ipaloop][i].rfmode=m_iRFmode;
			stSweep[ipaloop][i].ulChan=m_iTxLinChannel;
			stSweep[ipaloop][i].txBW = 3;	// don't care for WCDMA
			stSweep[ipaloop][i].rxBW = 3;	// don't care for WCDMA
			stSweep[ipaloop][i].chanOffset = 0;
			stSweep[ipaloop][i].txWaveform = 255;
			stSweep[ipaloop][i].numRBs = 12;
			stSweep[ipaloop][i].startRB = 1;
			stSweep[ipaloop][i].txAction=0;
			stSweep[ipaloop][i].txFlag = 1;
			stSweep[ipaloop][i].hdetFlag =1;
			stSweep[ipaloop][i].rxActions = 0xffff;
			stSweep[ipaloop][i].txPurpose=0x00;
			stSweep[ipaloop][i].rxPM = 0;
			stSweep[ipaloop][i].expRxAGC = 0;
			stSweep[ipaloop][i].rxFlag = 1;		
		}
	}

	//**********************************************************************************
	int iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iTxLinChannel);
	dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,m_iTxLinChannel,1);
	dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,0);
	//***********************************************************************************
	if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iRFmode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set RF Mode Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	if((iErrorcode=m_pPhone->FTM_SET_Cal_STATE(1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Calibration State Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}	
	myTxLinStruct.iNumPAStates=m_vPAState.size();
	for(int iLoopIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;++iLoopIndex)
	{
		word iOpCode=0;
		byte iHDETNum = 0;
		byte iLPMHDETNum = 0;		
		myTxLinStruct.aiPAState[iLoopIndex]=m_vPAState[iLoopIndex];
		myTxLinStruct.aiNumTxRGI[iLoopIndex]=(m_vStopRGI[iLoopIndex]-m_vStartRGI[iLoopIndex])/m_vRGIStep[iLoopIndex]+1;	
		myTxLinStruct.aiTxPurpose[iLoopIndex]=m_iTxPurpose;

		aTx_Measured.iNumTxPowerMeasurementsPerGainState[iLoopIndex]=myTxLinStruct.aiNumTxRGI[iLoopIndex]; 
		int iTimeOut=5000+myTxLinStruct.aiNumTxRGI[iLoopIndex]*20;
		double stepPower=(m_vStopPower[iLoopIndex]-m_vStartPower[iLoopIndex])/myTxLinStruct.aiNumTxRGI[iLoopIndex]; 

		if (m_iHDETSample[iLoopIndex]||m_iLPMHDETSample[iLoopIndex])
		{
			iOpCode=0x0008|0x0010; // Tx only + HDET
			iHDETNum=m_iHDETSample[iLoopIndex];
			iLPMHDETNum=m_iLPMHDETSample[iLoopIndex];
			aTx_Measured.iTxMeasIndexUsedForHDET=iLoopIndex;

		} 
		else
		{
			iOpCode=0x0008; // Tx only
		}
		iSegmentNum[iLoopIndex]=0;
		//if (0==iLoopIndex)// Waveform Config Segment
		//{
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].opcode = 0x0001;
			//stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].txWaveform=1;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].paState = 255; // no-op
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].paBias = 511;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].rgi = 0;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].numHdetAvg=0;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].numLpmHdetAvg=0;
			iSegmentNum[iLoopIndex]++;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].opcode = 0x0000;
			//stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].txWaveform=1;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].paState = 255; // no-op
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].paBias = 511;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].rgi = 0;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].numHdetAvg=0;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].numLpmHdetAvg=0;
			iSegmentNum[iLoopIndex]++;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].opcode = 0x0000;
			//stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].txWaveform=1;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].paState = 255; // no-op
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].paBias = 511;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].rgi = 0;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].numHdetAvg=0;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].numLpmHdetAvg=0;
			iSegmentNum[iLoopIndex]++;

		//}		
		for(int  i = 0; i <myTxLinStruct.aiNumTxRGI[iLoopIndex]; i++)
		{
			myTxLinStruct.aiRGI[iLoopIndex][i]=m_vStartRGI[iLoopIndex]+i*m_vRGIStep[iLoopIndex];
			myTxLinStruct.aiBias[iLoopIndex][i]=m_iPABiasValue[iLoopIndex];

			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].opcode = iOpCode;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].paState = myTxLinStruct.aiPAState[iLoopIndex]; 
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].txPurpose=iTxpurpose;			
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].paBias = m_iPABiasValue[iLoopIndex];
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].rgi = m_vStartRGI[iLoopIndex]+i*m_vRGIStep[iLoopIndex];
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].numHdetAvg=iHDETNum;
			stSweep[iLoopIndex][iSegmentNum[iLoopIndex]].numLpmHdetAvg=iLPMHDETNum;
			iSegmentNum[iLoopIndex]++;
		}

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetNormalSig(dUlMHz,dDLMhz,0,-80))
		{
			LogTrace(MSG_ERROR,"Set WCDMA ul and dl channel fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCH,"Set WCDMA ul and dl channel fail");
			return false;

		}
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPower_On(false))
		{
			LogTrace(MSG_ERROR,"Set DL Power OFF fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set DL Power OFF fail");
			return false;

		}
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetMaxPower(m_vExpectPower[iLoopIndex]))
		{
			LogTrace(MSG_ERROR,"Set TestDeivce Max power fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_SETMAXPOW,"Set TestDeivce Max power fail");
			return false;

		}

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMASetupWTDP(iSegmentNum[iLoopIndex],iTimeOut,stepPower,m_vExpectPower[iLoopIndex],dUlMHz))
		{
			LogTrace(MSG_ERROR,"Set CDMA Dynamic range power fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Set CDMA Dynamic range power fail");
			return false;

		}

		if((iErrorcode=m_pPhone->FTM_CFG_AND_EXEC_CAL_SWEEP((void*)stSweep[iLoopIndex],iSegmentNum[iLoopIndex],true,true))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Linear first Sweep Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				return false;
		}
		DblVtr dPowerListResults;
		dPowerListResults.clear();
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMAFetchWTDPResults(dPowerListResults))
		{
			LogTrace(MSG_ERROR,"Fethch WTDP Results fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_FETCHRESULTS,"Fethch WTDP Results fail");
			return false;  
		}
		unsigned int err_code1=0,err_code2=0;
		//FTM_Cal_Sweep_Response sweep_resp[256]={0};
		for (int i=0;i<iSegmentNum[iLoopIndex];i++)
		{
			stResponse[iLoopIndex][i+3].aiTxPower=(int)(10*dPowerListResults[i]);					
		}
		if (0!=m_iHDETSample[iLoopIndex])
		{
			if((iErrorcode=m_pPhone->FTM_GET_CAL_SWEEP_RESULTS_V2((void*)stResponse[iLoopIndex],(void*)stSweep[iLoopIndex],iSegmentNum[iLoopIndex],&err_code1,&err_code2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("Get Cal Sweep Result Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
					return false;
			}
		}
		
		for (int i=0;i<iSegmentNum[iLoopIndex];i++)
		{
			tx_Sweep[inumTxlin]=stSweep[iLoopIndex][i];
			sweep_resp[inumTxlin]=stResponse[iLoopIndex][i];
			inumTxlin++;
		}

		strMsg.Format("MEASUREMENTS: Tx Linearizer Sweep Full Bias: Band :%d,Tx Linearizer Channel:%d",m_iBand,m_iTxLinChannel);
		LogTrace(MSG_MID,strMsg);
		strMsg.Format("PAState	TxRGI	Bias	Power	DPower	HDET	LPMHDET");
		LogTrace(MSG_MID,strMsg);
		double adDeltaPower[4][128]={0};
		for (int i=0;i<myTxLinStruct.aiNumTxRGI[iLoopIndex];i++)
		{
			myTxLinStruct.adPower[iLoopIndex][i]=dPowerListResults[i];
			aTx_Measured.aiTxLinPower[iLoopIndex][i]=dPowerListResults[i];
			if (0==i)
			{
				myTxLinStruct.adMaxPower[iLoopIndex]=myTxLinStruct.adPower[iLoopIndex][0];
				myTxLinStruct.adMinPower[iLoopIndex]=myTxLinStruct.adPower[iLoopIndex][0];
				adDeltaPower[iLoopIndex][i]=0;
			}
			else
			{
				adDeltaPower[iLoopIndex][i]=myTxLinStruct.adPower[iLoopIndex][i]-myTxLinStruct.adPower[iLoopIndex][i-1];
				myTxLinStruct.adMaxPower[iLoopIndex]=myTxLinStruct.adMaxPower[iLoopIndex]>myTxLinStruct.adPower[iLoopIndex][i]?myTxLinStruct.adMaxPower[iLoopIndex]:myTxLinStruct.adPower[iLoopIndex][i];
				myTxLinStruct.adMinPower[iLoopIndex]=myTxLinStruct.adMinPower[iLoopIndex]<myTxLinStruct.adPower[iLoopIndex][i]?myTxLinStruct.adMinPower[iLoopIndex]:myTxLinStruct.adPower[iLoopIndex][i];
			}
			myTxLinStruct.aiHDET[iLoopIndex][i]=stResponse[iLoopIndex][i+3].aiHDETResults;	
			myTxLinStruct.aiHDETLPM[iLoopIndex][i]=stResponse[iLoopIndex][i+3].aiLPMHDETResults;
			
			if (0!=m_iHDETSample[iLoopIndex])
			{
				aTx_Measured.aiTxHDET[i]=myTxLinStruct.aiHDET[iLoopIndex][i];

			}
			if (0!=m_iLPMHDETSample[iLoopIndex])
			{
				aTx_Measured.aiTxHDETLPM[i]=myTxLinStruct.aiHDETLPM[iLoopIndex][i];
			}

			strMsg.Format("%d	%d	%f	%.2f	%.2f	%d	%d",myTxLinStruct.aiPAState[iLoopIndex],myTxLinStruct.aiRGI[iLoopIndex][i],myTxLinStruct.aiBias[iLoopIndex][i],myTxLinStruct.adPower[iLoopIndex][i],adDeltaPower[iLoopIndex][i],myTxLinStruct.aiHDET[iLoopIndex][i],myTxLinStruct.aiHDETLPM[iLoopIndex][i]);
			LogTrace(MSG_MID,strMsg);

		
		}		

	}
	if (m_bAPTenabled)
	{
		for(int iLoopIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;++iLoopIndex)
		{
			double af_power[256]={0};
			dword ai_bias[256]={0};
			double aiICQ[256]={0};
			double aiVCC[256]={0};
			double aiICQi[256]={0};
			double aiVCCi[256]={0};
			int i_biasnum=0;
	
			GetPowerVsBiasIni(m_strBiasIniname,m_iRFmode,0,m_iTxLinChannel,m_vPAState[iLoopIndex],af_power,ai_bias,&i_biasnum);
			double imaxICQ=(double)((ai_bias[0]& 0xFFFF0000)>>16);
			double iminICQ=(double)((ai_bias[0]& 0xFFFF0000)>>16);
			double imaxVCC=(double)(ai_bias[0]& 0x0000FFFF);
			double iminVCC=(double)(ai_bias[0]& 0x0000FFFF);
			for (int i=0;i<i_biasnum;i++)
			{
				aiICQ[i]=double((ai_bias[i]& 0xFFFF0000)>>16);
				aiVCC[i]=double(ai_bias[i]& 0x0000FFFF);
				if (imaxICQ<aiICQ[i])
				{
					imaxICQ=aiICQ[i];
				}
				if (iminICQ>aiICQ[i])
				{
					iminICQ=aiICQ[i];
				}
				if (imaxVCC<aiVCC[i])
				{
					imaxVCC=aiVCC[i];
				}
				if (iminVCC>aiVCC[i])
				{
					iminVCC=aiVCC[i];
				}

			}
			m_pPhone->RFCal_LinearInterpolation(af_power,aiICQ,i_biasnum,myTxLinStruct.adPower[iLoopIndex],aiICQi,myTxLinStruct.aiNumTxRGI[iLoopIndex],iminICQ,imaxICQ);

			m_pPhone->RFCal_LinearInterpolation(af_power,aiVCC,i_biasnum,myTxLinStruct.adPower[iLoopIndex],aiVCCi,myTxLinStruct.aiNumTxRGI[iLoopIndex],iminVCC,imaxVCC);

			for (int i=0;i<myTxLinStruct.aiNumTxRGI[iLoopIndex];i++)
			{	
				myTxLinStruct.aiBias[iLoopIndex][i]=(((unsigned long)aiICQi[i])<<16)+((unsigned long)aiVCCi[i]);
				stSweep[iLoopIndex][i+3].paBias=(((unsigned long)aiICQi[i])<<16)+((unsigned long)aiVCCi[i]);
				stSweep[iLoopIndex][i+3].txPurpose=m_iTxPurpose;
			}		

		}
		memset(&stResponse,0,512*sizeof(FTM_Cal_Sweep_Response));
		for(int iLoopIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;++iLoopIndex)
		{
			int iTimeOut=5000+myTxLinStruct.aiNumTxRGI[iLoopIndex]*20;
			double stepPower=(m_vStopPower[iLoopIndex]-m_vStartPower[iLoopIndex])/myTxLinStruct.aiNumTxRGI[iLoopIndex]; 
			if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetNormalSig(dUlMHz,dDLMhz,0,-80))
			{
				LogTrace(MSG_ERROR,"Set CDMA ul and dl channel fail");
				CalFailLog(_T("_"),_T("_"),CDMACAL_SETCH,"Set CDMA ul and dl channel fail");
				return false;

			}
			if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPower_On(false))
			{
				LogTrace(MSG_ERROR,"Set DL Power OFF fail");
				CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set DL Power OFF fail");
				return false;

			}
			if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetMaxPower(m_vExpectPower[iLoopIndex]))
			{
				LogTrace(MSG_ERROR,"Set TestDeivce Max power fail");
				CalFailLog(_T("_"),_T("_"),WCDMACAL_SETMAXPOW,"Set TestDeivce Max power fail");
				return false;

			}

			if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMASetupWTDP(iSegmentNum[iLoopIndex],iTimeOut,stepPower,m_vExpectPower[iLoopIndex],dUlMHz))
			{
				LogTrace(MSG_ERROR,"Set CDMA Dynamic range power fail");
				CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Set CDMA Dynamic range power fail");
				return false;

			}

			if((iErrorcode=m_pPhone->FTM_CFG_AND_EXEC_CAL_SWEEP((void*)stSweep[iLoopIndex],iSegmentNum[iLoopIndex],true,true))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("Phone Linear first Sweep Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
					return false;
			}
			DblVtr dPowerListResults;
			dPowerListResults.clear();
			if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMAFetchWTDPResults(dPowerListResults))
			{
				LogTrace(MSG_ERROR,"Fethch WTDP Results fail");
				CalFailLog(_T("_"),_T("_"),WCDMACAL_FETCHRESULTS,"Fethch WTDP Results fail");
				return false;  
			}
			unsigned int err_code1=0,err_code2=0;
			//FTM_Cal_Sweep_Response sweep_resp[256]={0};
			for (int i=0;i<iSegmentNum[iLoopIndex];i++)
			{
				stResponse[iLoopIndex][i+3].aiTxPower=(int)(10*dPowerListResults[i]);
			}

			if (0!=m_iHDETSample[iLoopIndex])
			{
				if((iErrorcode=m_pPhone->FTM_GET_CAL_SWEEP_RESULTS_V2((void*)stResponse[iLoopIndex],(void*)stSweep[iLoopIndex],iSegmentNum[iLoopIndex],&err_code1,&err_code2))!=PHONE_SUCCESS)
				{ 
					strMsg.Format("Get Cal Sweep Result Fail!");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
						return false;
				}
			}
			for (int i=0;i<iSegmentNum[iLoopIndex];i++)
			{
				tx_Sweep[inumTxlin]=stSweep[iLoopIndex][i];
				sweep_resp[inumTxlin]=stResponse[iLoopIndex][i];
				inumTxlin++;
			}

			strMsg.Format("MEASUREMENTS: Tx Linearizer Sweep Full Bias: Band :%d,Tx Linearizer Channel:%d",m_iBand,m_iTxLinChannel);
			LogTrace(MSG_MID,strMsg);
			strMsg.Format("PAState	TxRGI	Bias	Power	DPower	HDET	LPMHDET");
			LogTrace(MSG_MID,strMsg);
			double adDeltaPower[4][128]={0};
			for (int i=0;i<myTxLinStruct.aiNumTxRGI[iLoopIndex];i++)
			{
				myTxLinStruct.adPower[iLoopIndex][i]=dPowerListResults[i];
				aTx_Measured.aiTxLinPower[iLoopIndex][i]=dPowerListResults[i];
				if (0==i)
				{
					myTxLinStruct.adMaxPower[iLoopIndex]=myTxLinStruct.adPower[iLoopIndex][0];
					myTxLinStruct.adMinPower[iLoopIndex]=myTxLinStruct.adPower[iLoopIndex][0];
					adDeltaPower[iLoopIndex][i]=0;
				}
				else
				{
					adDeltaPower[iLoopIndex][i]=myTxLinStruct.adPower[iLoopIndex][i]-myTxLinStruct.adPower[iLoopIndex][i-1];
					myTxLinStruct.adMaxPower[iLoopIndex]=myTxLinStruct.adMaxPower[iLoopIndex]>myTxLinStruct.adPower[iLoopIndex][i]?myTxLinStruct.adMaxPower[iLoopIndex]:myTxLinStruct.adPower[iLoopIndex][i];
					myTxLinStruct.adMinPower[iLoopIndex]=myTxLinStruct.adMinPower[iLoopIndex]<myTxLinStruct.adPower[iLoopIndex][i]?myTxLinStruct.adMinPower[iLoopIndex]:myTxLinStruct.adPower[iLoopIndex][i];
				}			
				myTxLinStruct.aiHDET[iLoopIndex][i]=stResponse[iLoopIndex][i+3].aiHDETResults;		
				myTxLinStruct.aiHDETLPM[iLoopIndex][i]=stResponse[iLoopIndex][i+3].aiLPMHDETResults;

				if (0!=m_iHDETSample[iLoopIndex])
				{
					aTx_Measured.aiTxHDET[i]=myTxLinStruct.aiHDET[iLoopIndex][i];

				}
				if (0!=m_iLPMHDETSample[iLoopIndex])
				{
					aTx_Measured.aiTxHDETLPM[i]=myTxLinStruct.aiHDETLPM[iLoopIndex][i];
				}

				strMsg.Format("%d	%d	%.0f	%.2f	%.2f	%d	%d",myTxLinStruct.aiPAState[iLoopIndex],myTxLinStruct.aiRGI[iLoopIndex][i],myTxLinStruct.aiBias[iLoopIndex][i],myTxLinStruct.adPower[iLoopIndex][i],adDeltaPower[iLoopIndex][i],myTxLinStruct.aiHDET[iLoopIndex][i],myTxLinStruct.aiHDETLPM[iLoopIndex][i]);
				LogTrace(MSG_MID,strMsg);


			}	

		}
	}
	
	for(int iLoopIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;++iLoopIndex)
	{
		if (myTxLinStruct.adMaxPower[iLoopIndex]<m_vStartPower[iLoopIndex])
		{
			strMsg.Format("PA state %d MaxPower %.2f can NOT reach StartPower %.2f",m_vPAState[iLoopIndex],myTxLinStruct.adMaxPower[iLoopIndex],m_vStartPower[iLoopIndex]);
			LogTrace(MSG_MID,strMsg);
			return false;
		}
		if (myTxLinStruct.adMinPower[iLoopIndex]>m_vStopPower[iLoopIndex])
		{
			strMsg.Format("PA state %d MinPower %.2f can NOT reach StartPower %.2f",m_vPAState[iLoopIndex],myTxLinStruct.adMinPower[iLoopIndex],m_vStopPower[iLoopIndex]);
			LogTrace(MSG_MID,strMsg);
			return false;
		}
	}

	if((iErrorcode=m_pPhone->RFCAL_CDMA_TxLinCal_BetaScaling_Results(m_iNVModeID,(void*)&aTx_Measured,(void*)&aTx_Result,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_TxLinCal_BetaScaling_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}


	strMsg.Format("HDET vs AGC Table: Band=%d Channel=%d",m_iBand,m_iTxLinChannel);
	LogTrace(MSG_MID,strMsg)

		strMsg.Format("%s:%d",aTx_Result.aHDET_vs_AGC.oNVitem.sNVName,aTx_Result.aHDET_vs_AGC.oNVitem.iNVenum);
	LogTrace(MSG_MID,strMsg)
		for(int iHDETIndex=0;iHDETIndex<QMSL_NV_MANAGER_HDET_VS_AGC_NV_SIZE;++iHDETIndex)
		{
			strMsg.Format("Power=%.2f HDET=%d",aTx_Result.aHDET_vs_AGC.adTxPowerLevel[iHDETIndex],aTx_Result.aHDET_vs_AGC.aHDET_vs_AGC[iHDETIndex]);
			LogTrace(MSG_MID,strMsg)
		} 
		strMsg.Format("%s:%d",aTx_Result.aHDET_offset.oNVitem.sNVName,aTx_Result.aHDET_offset.oNVitem.iNVenum);
		LogTrace(MSG_MID,strMsg)
			strMsg.Format("HDET offset:%d",aTx_Result.aHDET_offset.iHDET_offset);
		LogTrace(MSG_MID,strMsg)
			strMsg.Format("%s:%d",aTx_Result.aHDET_span.oNVitem.sNVName,aTx_Result.aHDET_span.oNVitem.iNVenum);
		LogTrace(MSG_MID,strMsg)
			strMsg.Format("HDET span:%d",aTx_Result.aHDET_span.iHDET_span);
		LogTrace(MSG_MID,strMsg)
		ArrangeMyTxLinStruct(&myTxLinStruct);


		strMsg.Format("B%d",m_iBand);
		CalPassLog(strMsg,"_","TxLinearizer measured Pass");
		return true;


	return true;
}

bool CESCalWCDMA::RxFreqCompFunc()
{
	CString strMsg;
	int iErrorcode;
	double  dUlMHz,dDLMhz;	
	short iLNAValue=0;
	int iMode_id=FTM_MODE_ID_WCDMA;
	int iMode_id1=(0==m_iRXPath)?FTM_MODE_ID_WCDMA:FTM_MODE_WCDMA_RX1;
	double DYNAMICRANGE=102.4;
	double MIN_RSSI=-106;
	int iFailflag=0;
	

	QMSL_CDMA_RxFreq_Measurement_struct aRX_Measured;
	QMSL_CDMA_MeasuredChannels_struct  aRX_MeasuredChannels;
	QMSL_CDMA_NVChannels_struct  aRX_NV_Channels;
	memset(&aRX_NV_Channels,0,sizeof(QMSL_CDMA_NVChannels_struct));
	QMSL_CDMA_Rx_DVGA_LNA_Cal_NV_Result aRX_DVGA_LNA_Cal_NV;
	memset(&aRX_DVGA_LNA_Cal_NV,0,sizeof(QMSL_CDMA_Rx_DVGA_LNA_Cal_NV_Result));

	aRX_MeasuredChannels.iNumMeasuredChannels=m_ivChannellist.size();
	aRX_MeasuredChannels.iRefChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iTxLinChannel);
	aRX_Measured.iPath=m_iRXPath;
	aRX_Measured.iNumMeasuredPowerModes=m_ivRxPM.size();
	aRX_Measured.iNumMeasured_LNA_States=0;
	for(int i=0;i<m_ivRxAction.size();++i)
	{
		if (0!=m_ivRxAction[i])
		{
			aRX_Measured.aiLNA_States[aRX_Measured.iNumMeasured_LNA_States]=m_ivRxAction[i];
			aRX_Measured.iNumMeasured_LNA_States++;
		}
		
	}	
	

	strMsg.Format("RX Freq Comp :Band=B%d ",m_iBand);
	LogTrace(MSG_MID,strMsg);

	if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(0))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("SET_MODE_ID Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iRFmode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Band Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	for(int iCHIndex=0;iCHIndex<m_ivChannellist.size();++iCHIndex)
	{

		int iChannel=m_ivChannellist[iCHIndex];
		int iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,iChannel);
		aRX_NV_Channels.aiNVChannels[iCHIndex]=iDLChannel;
		aRX_MeasuredChannels.aiMeasuredChannels[iCHIndex]=iDLChannel;
		dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,iChannel,1);
		dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,0);

		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
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

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetNormalSig(dUlMHz,dDLMhz,0,-80))
		{
			LogTrace(MSG_ERROR,"Set Normal CDMA signal fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set Normal CDMA signal fail");
			return false;

		}
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPower_On(true))
		{
			LogTrace(MSG_ERROR,"Set DL Power ON fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set DL Power ON fail");
			return false;

		}

		for (int iPWIndex=0;iPWIndex<m_ivRxAction.size();iPWIndex++)
		{
			double dRxPower=m_dvRxPower[iPWIndex];
			if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPowe(dRxPower))
			{
				LogTrace(MSG_ERROR,"Set  CDMA DL power fail");
				CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set  CDMA DL power fail");
				return false;

			}
			//**********************************************************
			Sleep(20);		
			
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id1))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(m_iRXPath))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			short iInputPower=(1024/DYNAMICRANGE)*(dRxPower-(MIN_RSSI+DYNAMICRANGE/2));
			if (0==m_ivRxAction[iPWIndex])
			{
				if((iErrorcode=m_pPhone->FTM_GET_DVGA_OFFSET(iInputPower,&iLNAValue))!=PHONE_SUCCESS)
				{ 
					strMsg.Format("FTM_GET_DVGA_OFFSET Fail!");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				}
			}
			else
			{
				if((iErrorcode=m_pPhone->FTM_GET_LNA_OFFSET(m_ivRxAction[iPWIndex],iInputPower,&iLNAValue))!=PHONE_SUCCESS)
				{ 
					strMsg.Format("FTM_CDMA_API2_CALIBRATE_LNA Fail!");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				}
			}
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id1))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(0))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}

			
			if(iLNAValue>m_ivLNAOffsetMax[iPWIndex] || iLNAValue<m_ivLNAOffsetMin[iPWIndex])
			{
				strMsg.Format("%d	%d	%.2f	%d	%d	%d	%d Fail!",iChannel,m_iRXPath,dRxPower,m_ivRxAction[iPWIndex],iLNAValue,m_ivLNAOffsetMax[iPWIndex],m_ivLNAOffsetMin[iPWIndex]);
				LogTrace(MSG_ERROR,strMsg)
					iFailflag++;
			}
			else
			{
				strMsg.Format("%d	%d	%.2f	%d	%d	%d	%d Pass!",iChannel,m_iRXPath,dRxPower,m_ivRxAction[iPWIndex],iLNAValue,m_ivLNAOffsetMax[iPWIndex],m_ivLNAOffsetMin[iPWIndex]);
				LogTrace(MSG_ERROR,strMsg)	
			}
			
			if (0==m_ivRxAction[iPWIndex])
			{
				aRX_Measured.aiDVGA_Measured[iCHIndex][0]=iLNAValue;
			}
			else
			{
				aRX_Measured.aiLNA_Measured[iCHIndex][m_ivRxAction[iPWIndex]-1][0]=iLNAValue;
			}
				
			


		}

	}

	if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPower_On(false))
	{
		LogTrace(MSG_ERROR,"Set DL Power ON fail");
		CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set DL Power ON fail");
		return false;

	}
	if (iFailflag>0)
	{
		CalFailLog(_T("_"),_T("_"),CDMACAL_FETCHCHPWR,strMsg);
		return false;
	}


	if((iErrorcode=m_pPhone->RFCAL_CDMA_RxCal_Results(m_iNVModeID,0,1,&aRX_Measured,&aRX_MeasuredChannels,&aRX_NV_Channels,&aRX_DVGA_LNA_Cal_NV,1,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_RxCal_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	strMsg.Format("RX DVGA and LNA Offset NV Value");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("%s:%d",aRX_DVGA_LNA_Cal_NV.aDVGA.oNVitem.sNVName,aRX_DVGA_LNA_Cal_NV.aDVGA.oNVitem.iNVenum);
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("RefChannel DVGA offset=%d",aRX_DVGA_LNA_Cal_NV.aDVGA.iDVGAOffset);
	LogTrace(MSG_MID,strMsg);
	for(int iLNARangeIndex=0;iLNARangeIndex<aRX_Measured.iNumMeasured_LNA_States;++iLNARangeIndex)
	{
		strMsg.Format("%s:%d",aRX_DVGA_LNA_Cal_NV.aLNA[iLNARangeIndex].oNVitem.sNVName,aRX_DVGA_LNA_Cal_NV.aLNA[iLNARangeIndex].oNVitem.iNVenum);
		LogTrace(MSG_MID,strMsg);
		strMsg.Format("RefChannel LNA%d offset=%d",iLNARangeIndex,aRX_DVGA_LNA_Cal_NV.aLNA[iLNARangeIndex].iLNAOffset);
		LogTrace(MSG_MID,strMsg);
	}
	strMsg.Format("NV_VGA_GAIN_OFFSET_VS_FREQ");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("%s:%d",aRX_DVGA_LNA_Cal_NV.aDVGAvsFreq.oNVitem.sNVName,aRX_DVGA_LNA_Cal_NV.aDVGAvsFreq.oNVitem.iNVenum);
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("chan	RxPath	 RxPM	NV");
	LogTrace(MSG_MID,strMsg);
	for(int iNumPMMode=0;iNumPMMode<m_ivRxPM.size();++iNumPMMode)
	{
		for(int iCHIndex=0;iCHIndex<m_ivChannellist.size();++iCHIndex)
		{
			strMsg.Format("%d	%d	%d	%d",m_ivChannellist[iCHIndex],m_iRXPath,iNumPMMode,aRX_DVGA_LNA_Cal_NV.aDVGAvsFreq.iDVGAOffsetVsFreqItem[iCHIndex][iNumPMMode]);
			LogTrace(MSG_MID,strMsg);
		}
	}
	strMsg.Format("NV_LNA_OFFSET_VS_FREQ");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("chan	LNA	 RxPM	NV");
	LogTrace(MSG_MID,strMsg);
	for(int iLNAIndex=0;iLNAIndex<aRX_Measured.iNumMeasured_LNA_States;++iLNAIndex)
	{
		strMsg.Format("%s:%d",aRX_DVGA_LNA_Cal_NV.aLNAvsFreq[iLNAIndex].oNVitem.sNVName,aRX_DVGA_LNA_Cal_NV.aLNAvsFreq[iLNAIndex].oNVitem.iNVenum);
		LogTrace(MSG_MID,strMsg);
		for(int iNumPMMode=0;iNumPMMode<m_ivRxPM.size();++iNumPMMode)
		{
			for(int iCHIndex=0;iCHIndex<m_ivChannellist.size();++iCHIndex)
			{
				strMsg.Format("%d	%d	%d	%d",m_ivChannellist[iCHIndex],aRX_Measured.aiLNA_States[iLNAIndex],iNumPMMode,aRX_DVGA_LNA_Cal_NV.aLNAvsFreq[iLNAIndex].iLNAOffsetVsFreqItem[iCHIndex][iNumPMMode]);
				LogTrace(MSG_MID,strMsg);
			}
		}

	}

	CalPassLog("_","_","RX_DVGA_LNA Calibration PASS")
		return true;
}
bool CESCalWCDMA::TxLinearizerFunc()
{
	CString strMsg;
	int iErrorcode;
	double dUlMHz,dDLMhz;
	int iSegmentNum=0;
	int iNumConfigSigment=29;
	USHORT iSegmentTimeMS=2;
	FTM_Cal_Sweep_Request *stSweep=new FTM_Cal_Sweep_Request[512];
	FTM_Cal_Sweep_Response *stResponse=new FTM_Cal_Sweep_Response[512];
	int iTxpurpose=m_bAPTenabled?FTM_Tx_Purpose_Linearizer_Multi_Carrier:m_iTxPurpose;
	
	QMSL_CDMA_TxLin_BetaScaling_struct  aTx_Measured;
	QMSL_CDMA_TxLin_BetaScaling_Result_struct aTx_Result;
	memset(&myTxLinStruct,0,sizeof(TxlinStruct));	
	memset(&aTx_Measured,0,sizeof(QMSL_CDMA_TxLin_BetaScaling_struct));
	memset(&aTx_Result,0,sizeof(QMSL_CDMA_TxLin_BetaScaling_Result_struct));

	
	aTx_Measured.HDET_OffsetPower_dBm=18;
	aTx_Measured.HDET_SpanPower_dBm=26;
	aTx_Measured.LPM_HDET_OffsetPower_dBm=18;
	aTx_Measured.LPM_HDET_SpanPower_dBm=26;
	aTx_Measured.LPM_HDET_Start_Power_dBm=16;
	aTx_Measured.LPM_HDET_Threshold_Power_dBm=1;
	aTx_Measured.iDo_Not_Extrapolate_Lower_Powers=0;
	aTx_Measured.iEnh_Linearizer_0_NV=0;
	aTx_Measured.iHDET_MaxLim=4095;
	aTx_Measured.iNV_Resolution=10;
	aTx_Measured.iUse_HDET_V2=1;

	

	for( int i = 0; i < 512; i++)
	{
		stSweep[i].segLen = iSegmentTimeMS*1000;//
		stSweep[i].masterDev = 1;
		stSweep[i].slaveDev = -1;
		stSweep[i].rfmode=m_iRFmode;
		stSweep[i].ulChan=m_iTxLinChannel;
		stSweep[i].txBW = 3;	// don't care for WCDMA
		stSweep[i].rxBW = 3;	// don't care for WCDMA
		stSweep[i].chanOffset = 0;
		stSweep[i].txWaveform = 255;
		stSweep[i].numRBs = 12;
		stSweep[i].startRB = 1;
		stSweep[i].txAction=0;
		stSweep[i].txFlag = 1;
		stSweep[i].hdetFlag =1;
		stSweep[i].rxActions = 0xffff;
		stSweep[i].txPurpose=0x00;
		stSweep[i].rxPM = 0;
		stSweep[i].expRxAGC = 0;
		stSweep[i].rxFlag = 1;	 		
	}
	int iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iTxLinChannel);
	dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,m_iTxLinChannel,1);
	dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,0);

	if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iRFmode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set RF Mode Fail!");
		free((void*)stSweep);
		free((void*)stResponse);
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	if((iErrorcode=m_pPhone->FTM_SET_Cal_STATE(1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Calibration State Fail!");
		free((void*)stSweep);
		free((void*)stResponse);
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	

	// Segment 0, Configure, do not turn on PA
	stSweep[0].opcode = 0x0001;
	stSweep[0].paState = 255; // no-op
	stSweep[0].paBias = 511;
	stSweep[0].rgi = 0;
	stSweep[0].numHdetAvg=0;
	stSweep[0].numLpmHdetAvg=0;	
	iSegmentNum++;

	for( int i = 1; i < iNumConfigSigment; i++)
	{
		stSweep[iSegmentNum].opcode = 0x0000;
		stSweep[iSegmentNum].paState = 255; // no-op
		stSweep[iSegmentNum].paBias = 511;
		stSweep[iSegmentNum].rgi = 0; 
		stSweep[iSegmentNum].numHdetAvg=0;
		stSweep[iSegmentNum].numLpmHdetAvg=0;		
		iSegmentNum++;
	}
	myTxLinStruct.iNumPAStates=m_vPAState.size();
	
	for(int iLoopIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;++iLoopIndex)
	{
	
		myTxLinStruct.aiNumTxRGI[iLoopIndex]=(m_vStopRGI[iLoopIndex]-m_vStartRGI[iLoopIndex])/m_vRGIStep[iLoopIndex]+1;
		aTx_Measured.iNumTxPowerMeasurementsPerGainState[iLoopIndex]=myTxLinStruct.aiNumTxRGI[iLoopIndex];
		myTxLinStruct.aiTxPurpose[iLoopIndex]=iTxpurpose;
		word iOpCode=0;
		byte iHDETNum = 0;
		byte iLPMHDETNum = 0;
		byte iPAState=m_vPAState[iLoopIndex];
		myTxLinStruct.aiPAState[iLoopIndex]=iPAState;

		if (m_iHDETSample[iLoopIndex]||m_iLPMHDETSample[iLoopIndex])
		{
			iOpCode=0x0008|0x0010; // Tx only + HDET
			iHDETNum=m_iHDETSample[iLoopIndex];
			iLPMHDETNum=m_iLPMHDETSample[iLoopIndex];
			aTx_Measured.iTxMeasIndexUsedForHDET=iLoopIndex;

		} 
		else
		{
			iOpCode=0x0008; // Tx only
		}
		stSweep[iSegmentNum].opcode = 0x0000;
		stSweep[iSegmentNum].paState = 255; // no-op
		stSweep[iSegmentNum].paBias = 511;
		stSweep[iSegmentNum].rgi = 0;
		stSweep[iSegmentNum].numHdetAvg=0;
		stSweep[iSegmentNum].numLpmHdetAvg=0;
	
		iSegmentNum++;

		for( int i = 0; i < myTxLinStruct.aiNumTxRGI[iLoopIndex]; i++)
		{
			stSweep[iSegmentNum].opcode = iOpCode;
			stSweep[iSegmentNum].paState = iPAState; 
			stSweep[iSegmentNum].txPurpose=iTxpurpose;
			myTxLinStruct.aiBias[iLoopIndex][i]=m_iPABiasValue[iLoopIndex];
			stSweep[iSegmentNum].paBias = m_iPABiasValue[iLoopIndex];			
			myTxLinStruct.aiRGI[iLoopIndex][i]=m_vStartRGI[iLoopIndex]+i*m_vRGIStep[iLoopIndex];
			stSweep[iSegmentNum].rgi = m_vStartRGI[iLoopIndex]+i*m_vRGIStep[iLoopIndex];
			stSweep[iSegmentNum].numHdetAvg=iHDETNum;
			stSweep[iSegmentNum].numLpmHdetAvg=iLPMHDETNum;
			iSegmentNum++;
		}

	}	
	DblVtr dvTRxFreq;
	dvTRxFreq.clear();
	dvTRxFreq.push_back(dDLMhz);
	dvTRxFreq.push_back(dUlMHz);

	DblVtr dvTxLvlRef;
	dvTxLvlRef.clear();
	dvTxLvlRef.push_back(m_vExpectPower[0]);
	int iTxLvlchange=0;
	for (int iLoopIndex=1;iLoopIndex<m_vExpectPower.size();iLoopIndex++)
	{
		iTxLvlchange+=myTxLinStruct.aiNumTxRGI[iLoopIndex-1];
		dvTxLvlRef.push_back(iTxLvlchange);
		dvTxLvlRef.push_back(m_vExpectPower[iLoopIndex]);
	}


	DblVtr dvRxLvl;
	dvRxLvl.clear();
	dvRxLvl.push_back(-70);
	dvRxLvl.push_back(-70);
	
	if ((iErrorcode=m_pFunWCDMACalDev->IWCDMAESCalLinearconfig(1,3,iSegmentTimeMS,dvTRxFreq,dvTxLvlRef,dvRxLvl,iSegmentNum-iNumConfigSigment,1))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Config Enhanced Sweep Cal equiment fail");
		CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Config Enhanced Sweep Cal equiment fail");
		free((void*)stSweep);
		free((void*)stResponse);
		return false;
	}
	
	if((iErrorcode=m_pPhone->FTM_CFG_AND_EXEC_CAL_SWEEP((void*)stSweep,iSegmentNum,false,true))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Linear first Sweep Fail!");
		free((void*)stSweep);
		free((void*)stResponse);
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			return false;
	}
	DblVtr dvTRxResult;
	dvTRxResult.clear();
	if ((iErrorcode=m_pFunWCDMACalDev->IWCDMAFetchTXRXResults(dvTRxResult))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Fetch ESCal Linear full bias result fail");
		CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Fetch ESCal Linear full bias result fail");
		free((void*)stSweep);
		free((void*)stResponse);
		return false;

	}
	memset((void*)stResponse,0,512*sizeof(FTM_Cal_Sweep_Response));
	unsigned int err_code1=0,err_code2=0;	
	double dDeltaPower=0;
	for(int iLoopIndex=0,iSigIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;iLoopIndex++)
	{
		for (int i=0;i<myTxLinStruct.aiNumTxRGI[iLoopIndex];i++)
		{
			myTxLinStruct.adPower[iLoopIndex][i]=dvTRxResult[iSigIndex];
			if (1==i)
			{
				dDeltaPower=myTxLinStruct.adPower[iLoopIndex][1]-myTxLinStruct.adPower[iLoopIndex][0];
				if (abs(dDeltaPower)>4)
				{
					dvTRxResult[iSigIndex]=dvTRxResult[iSigIndex-1];
					myTxLinStruct.adPower[iLoopIndex][1]=dvTRxResult[iSigIndex];
				}
			}
			else if(1<i)
			{
				dDeltaPower=myTxLinStruct.adPower[iLoopIndex][i]-myTxLinStruct.adPower[iLoopIndex][i-1];
				if (abs(dDeltaPower)>4)
				{

					dvTRxResult[iSigIndex]=2*dvTRxResult[iSigIndex-1]-dvTRxResult[iSigIndex-2];
					myTxLinStruct.adPower[iLoopIndex][i]=dvTRxResult[iSigIndex];
				}

			}


			iSigIndex++;
		}
		iSigIndex++;
	}
	for (int i=0;i<dvTRxResult.size();i++)
	{
		stResponse[i+iNumConfigSigment+1].aiTxPower=(int)(10*dvTRxResult[i]);
	}

	if((iErrorcode=m_pPhone->FTM_GET_CAL_SWEEP_RESULTS_V2((void*)stResponse,(void*)stSweep,iSegmentNum,&err_code1,&err_code2))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Get Cal Sweep Result Fail!");
		free((void*)stSweep);
		free((void*)stResponse);
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			return false;
	}
	inumTxlin=0;
	for ( int i=0;i<iSegmentNum;i++)
	{
		tx_Sweep[inumTxlin]=stSweep[i];
		sweep_resp[inumTxlin]=stResponse[i];
		inumTxlin++;
	}
	
	strMsg.Format("MEASUREMENTS: Tx Linearizer Sweep Full Bias: Band :%d,Tx Linearizer Channel:%d",m_iBand,m_iTxLinChannel);
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("PAState	TxRGI	Bias	Power	DPower	HDET	LPMHDET");
	LogTrace(MSG_MID,strMsg);
	double adDeltaPower[4][128]={0};
	for(int iLoopIndex=0,iSigIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;iLoopIndex++)
	{
		for (int i=0;i<myTxLinStruct.aiNumTxRGI[iLoopIndex];i++)
		{
			myTxLinStruct.adPower[iLoopIndex][i]=dvTRxResult[iSigIndex];
			if (0==i)
			{
				myTxLinStruct.adMaxPower[iLoopIndex]=myTxLinStruct.adPower[iLoopIndex][0];
				myTxLinStruct.adMinPower[iLoopIndex]=myTxLinStruct.adPower[iLoopIndex][0];
				adDeltaPower[iLoopIndex][i]=0;
			}
			else
			{
				adDeltaPower[iLoopIndex][i]=myTxLinStruct.adPower[iLoopIndex][i]-myTxLinStruct.adPower[iLoopIndex][i-1];
				myTxLinStruct.adMaxPower[iLoopIndex]=myTxLinStruct.adMaxPower[iLoopIndex]>myTxLinStruct.adPower[iLoopIndex][i]?myTxLinStruct.adMaxPower[iLoopIndex]:myTxLinStruct.adPower[iLoopIndex][i];
				myTxLinStruct.adMinPower[iLoopIndex]=myTxLinStruct.adMinPower[iLoopIndex]<myTxLinStruct.adPower[iLoopIndex][i]?myTxLinStruct.adMinPower[iLoopIndex]:myTxLinStruct.adPower[iLoopIndex][i];
			}
			aTx_Measured.aiTxLinPower[iLoopIndex][i]=dvTRxResult[iSigIndex];
			myTxLinStruct.aiHDET[iLoopIndex][i]=stResponse[iSigIndex+iNumConfigSigment+1].aiHDETResults;
			myTxLinStruct.aiHDETLPM[iLoopIndex][i]=stResponse[iSigIndex+iNumConfigSigment+1].aiLPMHDETResults;
			if (0!=m_iHDETSample[iLoopIndex])
			{
				aTx_Measured.aiTxHDET[i]=myTxLinStruct.aiHDET[iLoopIndex][i];
			}
			if (0!=m_iLPMHDETSample[iLoopIndex])
			{
				aTx_Measured.aiTxHDETLPM[i]=myTxLinStruct.aiHDETLPM[iLoopIndex][i];
			}
			strMsg.Format("%d	%d	%.0f	%.2f	%.2f	%d	%d",myTxLinStruct.aiPAState[iLoopIndex],myTxLinStruct.aiRGI[iLoopIndex][i],myTxLinStruct.aiBias[iLoopIndex][i],myTxLinStruct.adPower[iLoopIndex][i],adDeltaPower[iLoopIndex][i],myTxLinStruct.aiHDET[iLoopIndex][i],myTxLinStruct.aiHDETLPM[iLoopIndex][i]);
			LogTrace(MSG_MID,strMsg);

			iSigIndex++;
		}
		iSigIndex++;
	}


	if (m_bAPTenabled)
	{
		iSegmentNum=iNumConfigSigment;
		for(int iLoopIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;++iLoopIndex)
		{
			double af_power[256]={0};
			dword ai_bias[256]={0};
			double aiICQ[256]={0};
			double aiVCC[256]={0};
			double aiICQi[256]={0};
			double aiVCCi[256]={0};
			int i_biasnum=0;

			GetPowerVsBiasIni(m_strBiasIniname,m_iRFmode,0,m_iTxLinChannel,m_vPAState[iLoopIndex],af_power,ai_bias,&i_biasnum);
			double imaxICQ=(double)((ai_bias[0]& 0xFFFF0000)>>16);
			double iminICQ=(double)((ai_bias[0]& 0xFFFF0000)>>16);
			double imaxVCC=(double)(ai_bias[0]& 0x0000FFFF);
			double iminVCC=(double)(ai_bias[0]& 0x0000FFFF);
			for (int i=0;i<i_biasnum;i++)
			{
				aiICQ[i]=(DOUBLE)((ai_bias[i]& 0xFFFF0000)>>16);
				aiVCC[i]=(double)(ai_bias[i]& 0x0000FFFF);
				if (imaxICQ<aiICQ[i])
				{
					imaxICQ=aiICQ[i];
				}
				if (iminICQ>aiICQ[i])
				{
					iminICQ=aiICQ[i];
				}
				if (imaxVCC<aiVCC[i])
				{
					imaxVCC=aiVCC[i];
				}
				if (iminVCC>aiVCC[i])
				{
					iminVCC=aiVCC[i];
				}

			}
			m_pPhone->RFCal_LinearInterpolation(af_power,aiICQ,i_biasnum,myTxLinStruct.adPower[iLoopIndex],aiICQi,myTxLinStruct.aiNumTxRGI[iLoopIndex],iminICQ,imaxICQ);
			
			m_pPhone->RFCal_LinearInterpolation(af_power,aiVCC,i_biasnum,myTxLinStruct.adPower[iLoopIndex],aiVCCi,myTxLinStruct.aiNumTxRGI[iLoopIndex],iminVCC,imaxVCC);
			iSegmentNum++;
			for (int i=0;i<myTxLinStruct.aiNumTxRGI[iLoopIndex];i++)
			{

				myTxLinStruct.aiBias[iLoopIndex][i]=(((unsigned long)aiICQi[i])<<16)+((unsigned long)aiVCCi[i]);
				stSweep[iSegmentNum].txPurpose=m_iTxPurpose;
				stSweep[iSegmentNum].paBias=(((unsigned long)aiICQi[i])<<16)+((unsigned long)aiVCCi[i]);
				iSegmentNum++;
			}		

		}
		if ((iErrorcode=m_pFunWCDMACalDev->IWCDMAESCalLinearconfig(1,3,iSegmentTimeMS,dvTRxFreq,dvTxLvlRef,dvRxLvl,iSegmentNum-iNumConfigSigment,1))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Config Enhanced Sweep Cal equiment fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Config Enhanced Sweep Cal equiment fail");
			free((void*)stSweep);
			free((void*)stResponse);
			return false;
		}
		if((iErrorcode=m_pPhone->FTM_CFG_AND_EXEC_CAL_SWEEP((void*)stSweep,iSegmentNum,false,true))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Linear Second Sweep Fail!");
			free((void*)stSweep);
			free((void*)stResponse);
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				return false;
		}
		dvTRxResult.clear();
		if ((iErrorcode=m_pFunWCDMACalDev->IWCDMAFetchTXRXResults(dvTRxResult))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Fetch ESCal Linear diff bias result fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Fetch ESCal Linear full bias result fail");
			free((void*)stSweep);
			free((void*)stResponse);
			return false;

		}

		memset((void*)stResponse,0,512*sizeof(FTM_Cal_Sweep_Response));
		for (int i=0;i<dvTRxResult.size();i++)
		{
			stResponse[i+iNumConfigSigment+1].aiTxPower=(int)(10*dvTRxResult[i]);
		}

		if((iErrorcode=m_pPhone->FTM_GET_CAL_SWEEP_RESULTS_V2((void*)stResponse,(void*)stSweep,iSegmentNum,&err_code1,&err_code2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Get Cal Sweep Result Fail!");
			free((void*)stSweep);
			free((void*)stResponse);
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				return false;
		}
		for ( int i=0;i<iSegmentNum;i++)
		{
			tx_Sweep[inumTxlin]=stSweep[i];
			sweep_resp[inumTxlin]=stResponse[i];
			inumTxlin++;
		}

		strMsg.Format("MEASUREMENTS: Tx Linearizer Sweep : Band :%d,Tx Linearizer Channel:%d",m_iBand,m_iTxLinChannel);
		LogTrace(MSG_MID,strMsg);
		strMsg.Format("PAState	TxRGI	Bias	Power	DPower	HDET	LPMHDET");
		LogTrace(MSG_MID,strMsg);
		for(int iLoopIndex=0,iSigIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;iLoopIndex++)
		{
			for (int i=0;i<myTxLinStruct.aiNumTxRGI[iLoopIndex];i++)
			{
				myTxLinStruct.adPower[iLoopIndex][i]=dvTRxResult[iSigIndex];
				if (0==i)
				{
					myTxLinStruct.adMaxPower[iLoopIndex]=myTxLinStruct.adPower[iLoopIndex][0];
					myTxLinStruct.adMinPower[iLoopIndex]=myTxLinStruct.adPower[iLoopIndex][0];
					adDeltaPower[iLoopIndex][i]=0;
				}
				else
				{
					adDeltaPower[iLoopIndex][i]=myTxLinStruct.adPower[iLoopIndex][i]-myTxLinStruct.adPower[iLoopIndex][i-1];
					myTxLinStruct.adMaxPower[iLoopIndex]=myTxLinStruct.adMaxPower[iLoopIndex]>myTxLinStruct.adPower[iLoopIndex][i]?myTxLinStruct.adMaxPower[iLoopIndex]:myTxLinStruct.adPower[iLoopIndex][i];
					myTxLinStruct.adMinPower[iLoopIndex]=myTxLinStruct.adMinPower[iLoopIndex]<myTxLinStruct.adPower[iLoopIndex][i]?myTxLinStruct.adMinPower[iLoopIndex]:myTxLinStruct.adPower[iLoopIndex][i];
				}
				aTx_Measured.aiTxLinPower[iLoopIndex][i]=dvTRxResult[iSigIndex];
				myTxLinStruct.aiHDET[iLoopIndex][i]=stResponse[iSigIndex+iNumConfigSigment+1].aiHDETResults;
				myTxLinStruct.aiHDETLPM[iLoopIndex][i]=stResponse[iSigIndex+iNumConfigSigment+1].aiLPMHDETResults;
				if (0!=m_iHDETSample[iLoopIndex])
				{
					aTx_Measured.aiTxHDET[i]=myTxLinStruct.aiHDET[iLoopIndex][i];
				}
				if (0!=m_iLPMHDETSample[iLoopIndex])
				{
					aTx_Measured.aiTxHDETLPM[i]=myTxLinStruct.aiHDETLPM[iLoopIndex][i];
				}
				strMsg.Format("%d	%d	%.0f	%.2f	%.2f	%d	%d",myTxLinStruct.aiPAState[iLoopIndex],myTxLinStruct.aiRGI[iLoopIndex][i],myTxLinStruct.aiBias[iLoopIndex][i],myTxLinStruct.adPower[iLoopIndex][i],adDeltaPower[iLoopIndex][i],myTxLinStruct.aiHDET[iLoopIndex][i],myTxLinStruct.aiHDETLPM[iLoopIndex][i]);
				LogTrace(MSG_MID,strMsg);
				iSigIndex++;
			}
			iSigIndex++;
		}
	}
	
	for(int iLoopIndex=0,iSigIndex=0;iLoopIndex<myTxLinStruct.iNumPAStates;iLoopIndex++)
	{
		if (myTxLinStruct.adMaxPower[iLoopIndex]<m_vStartPower[iLoopIndex])
		{
			strMsg.Format("PA state %d MaxPower %.2f can NOT reach StartPower %.2f",m_vPAState[iLoopIndex],myTxLinStruct.adMaxPower[iLoopIndex],m_vStartPower[iLoopIndex]);
			LogTrace(MSG_MID,strMsg);
			free((void*)stSweep);
			free((void*)stResponse);
			return false;
		}
		if (myTxLinStruct.adMinPower[iLoopIndex]>m_vStopPower[iLoopIndex])
		{
			strMsg.Format("PA state %d MinPower %.2f can NOT reach StartPower %.2f",m_vPAState[iLoopIndex],myTxLinStruct.adMinPower[iLoopIndex],m_vStopPower[iLoopIndex]);
			LogTrace(MSG_MID,strMsg);
			free((void*)stSweep);
			free((void*)stResponse);
			return false;
		}
	}
	if((iErrorcode=m_pPhone->RFCAL_CDMA_TxLinCal_BetaScaling_Results(m_iNVModeID,(void*)&aTx_Measured,(void*)&aTx_Result,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_TxLinCal_BetaScaling_Results Fail!");
		free((void*)stSweep);
		free((void*)stResponse);
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}


	strMsg.Format("HDET vs AGC Table: Band=%d Channel=%d",m_iBand,m_iTxLinChannel);
	LogTrace(MSG_MID,strMsg)

		strMsg.Format("%s:%d",aTx_Result.aHDET_vs_AGC.oNVitem.sNVName,aTx_Result.aHDET_vs_AGC.oNVitem.iNVenum);
	LogTrace(MSG_MID,strMsg)
		for(int iHDETIndex=0;iHDETIndex<QMSL_NV_MANAGER_HDET_VS_AGC_NV_SIZE;++iHDETIndex)
		{
			strMsg.Format("Power=%.2f HDET=%d",aTx_Result.aHDET_vs_AGC.adTxPowerLevel[iHDETIndex],aTx_Result.aHDET_vs_AGC.aHDET_vs_AGC[iHDETIndex]);
			LogTrace(MSG_MID,strMsg)
		} 
		strMsg.Format("%s:%d",aTx_Result.aHDET_offset.oNVitem.sNVName,aTx_Result.aHDET_offset.oNVitem.iNVenum);
		LogTrace(MSG_MID,strMsg)
			strMsg.Format("HDET offset:%d",aTx_Result.aHDET_offset.iHDET_offset);
		LogTrace(MSG_MID,strMsg)
			strMsg.Format("%s:%d",aTx_Result.aHDET_span.oNVitem.sNVName,aTx_Result.aHDET_span.oNVitem.iNVenum);
		LogTrace(MSG_MID,strMsg)
			strMsg.Format("HDET span:%d",aTx_Result.aHDET_span.iHDET_span);
		LogTrace(MSG_MID,strMsg)
		ArrangeMyTxLinStruct(&myTxLinStruct);


		strMsg.Format("B%d",m_iBand);
		CalPassLog(strMsg,"_","TxLinearizer measured Pass");
		free((void*)stSweep);
		free((void*)stResponse);
		return true;

}

bool CESCalWCDMA::TxFreqCompFunc()
{
	CString strMsg;
	int iErrorcode;
	inumTRxFreq=0;		

	QMSL_CDMA_MeasuredChannels_struct  aTxF_MeasuredChannels={0};	
	QMSL_CDMA_NVChannels_struct  aTxF_NV_Channels={0};
	aTxF_MeasuredChannels.iRefChannel=m_iTxLinChannel;
	aTxF_MeasuredChannels.iNumMeasuredChannels=m_ivChannellist.size();
	QMSL_CDMA_TxLimVsFreq_struct  aTx_LimVsFreqMeasured={0};
	QMSL_CDMA_Tx_LimVsFreq_NV_struct aTx_LimVsFreq_NV_Result={0};
	memset(&aTx_LimVsFreqMeasured,0,sizeof(QMSL_CDMA_TxLimVsFreq_struct));

	aTx_LimVsFreqMeasured.oRefChMeas.iNumMeasurement=myTxLinStruct.aiNumTxRGI[0];
	for (int i=0;i<myTxLinStruct.aiNumTxRGI[0];i++)
	{
		aTx_LimVsFreqMeasured.oRefChMeas.aiTxAGC[i]=myTxLinStruct.aiRGI[0][i];
		aTx_LimVsFreqMeasured.oRefChMeas.aiTxMeasuredPower[i]=myTxLinStruct.adPower[0][i];
		aTx_LimVsFreqMeasured.oRefChMeas.aiTxMeasuredHDET[i]=myTxLinStruct.aiHDET[0][i];
	}
	int iNumOfTxLimMeasurement=0;
	int iNumOfTxLinGainStates=0;
	for (int i=0;i<m_ivFreqTxPurpose.size();i++)
	{
		if (5==m_ivFreqTxPurpose[i])
		{
			iNumOfTxLimMeasurement++;

		}
		if (4==m_ivFreqTxPurpose[i])
		{
			iNumOfTxLinGainStates++;
		}
	}

	USHORT iSegmentTimeMS=20;
	FTM_Cal_Sweep_Request tx_freq_Sweep[11];
	FTM_Cal_Sweep_Response tx_freq_Response[11];
	memset(tx_freq_Sweep,0,11*sizeof(FTM_Cal_Sweep_Request));
	memset(tx_freq_Response,0,11*sizeof(FTM_Cal_Sweep_Response));
	for (int i=0;i<11;i++)
	{
		tx_freq_Sweep[i].opcode=0;
		tx_freq_Sweep[i].segLen = iSegmentTimeMS*1000;
		tx_freq_Sweep[i].rfmode=m_iRFmode;
		tx_freq_Sweep[i].masterDev = 1;
		tx_freq_Sweep[i].slaveDev = -1;
		tx_freq_Sweep[i].txBW = 3;	 
		tx_freq_Sweep[i].rxBW = 3;	
		tx_freq_Sweep[i].chanOffset = 0;
		tx_freq_Sweep[i].txWaveform = 0x01;  
		tx_freq_Sweep[i].numRBs = 12;  
		tx_freq_Sweep[i].startRB = 1;
		tx_freq_Sweep[i].txAction=0;
		tx_freq_Sweep[i].paState = 255; // no-op
		tx_freq_Sweep[i].paBias = 511;
		tx_freq_Sweep[i].rgi = 0;
		tx_freq_Sweep[i].txPurpose=0;
		tx_freq_Sweep[i].txFlag = 1;
		tx_freq_Sweep[i].hdetFlag = 1;
		tx_freq_Sweep[i].numHdetAvg = 0;
		tx_freq_Sweep[i].numLpmHdetAvg = 0; // NA
		tx_freq_Sweep[i].rxActions = 0xffff;
		tx_freq_Sweep[i].rxPM = 0;
		tx_freq_Sweep[i].expRxAGC = 0;
		tx_freq_Sweep[i].rxFlag = 1;
	}

	TRx_Request myTRxRequest[16];	
	memset(myTRxRequest,0,16*sizeof(TRx_Request));
	GetTxFreqRGI(m_ivTxFreqPAState,m_dvTxFreqPower,aiRGI,aiBias);


	tx_freq_Sweep[0].opcode=1;
	for (int i=0;i<m_ivTxFreqPAState.size();i++)
	{
		tx_freq_Sweep[i+3].paState=m_ivTxFreqPAState[i];
		tx_freq_Sweep[i+3].rgi=aiRGI[i];
		tx_freq_Sweep[i+3].paBias=(dword)aiBias[i];
		tx_freq_Sweep[i+3].numHdetAvg=m_ivFreqHDETSample[i];
		tx_freq_Sweep[i+3].txPurpose=m_ivFreqTxPurpose[i];
		if (0!=m_ivFreqHDETSample[i])
		{
			tx_freq_Sweep[i+3].opcode=0x0018;
		} 
		else
		{
			tx_freq_Sweep[i+3].opcode=0x0008;
		}

	}

	for (int ichindex=0;ichindex<m_ivChannellist.size();ichindex++)
	{
		aTx_LimVsFreqMeasured.iNumOfTxLimMeasurement[ichindex]=iNumOfTxLimMeasurement;
		for (int i=0;i<iNumOfTxLimMeasurement;i++)
		{
			aTx_LimVsFreqMeasured.aiTxMeasuredPDM[ichindex][i]=aiRGI[i];
		}
		aTxF_MeasuredChannels.aiMeasuredChannels[ichindex]=m_ivChannellist[ichindex];
		aTxF_NV_Channels.aiNVChannels[ichindex]=m_ivChannellist[ichindex];
		for (int i=0;i<11;i++)
		{
			tx_freq_Sweep[i].ulChan=m_ivChannellist[ichindex];
		}
		int iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iTxLinChannel);
		double dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,m_ivChannellist[ichindex],1);
		double dDLMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,0);

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetNormalSig(dUlMHz,dDLMHz,0,-80))
		{
			LogTrace(MSG_ERROR,"Set CDMA ul and dl channel fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCH,"Set CDMA ul and dl channel fail");
			return false;

		}
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPower_On(false))
		{
			LogTrace(MSG_ERROR,"Set DL Power OFF fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set DL Power OFF fail");
			return false;

		}
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetMaxPower(m_dvTxFreqPower[0]+2))
		{
			LogTrace(MSG_ERROR,"Set TestDeivce Max power fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_SETMAXPOW,"Set TestDeivce Max power fail");
			return false;

		}

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMASetupWTDP(11,5000,-0.01,m_dvTxFreqPower[0]+2,dUlMHz))
		{
			LogTrace(MSG_ERROR,"Set CDMA Dynamic range power fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Set CDMA Dynamic range power fail");
			return false;

		}

		if((iErrorcode=m_pPhone->FTM_CFG_AND_EXEC_CAL_SWEEP((void*)tx_freq_Sweep,11,true,true))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Linear first Sweep Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				return false;
		}
		DblVtr dPowerListResults;
		dPowerListResults.clear();
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMAFetchWTDPResults(dPowerListResults))
		{
			LogTrace(MSG_ERROR,"Fethch WTDP Results fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_FETCHRESULTS,"Fethch WTDP Results fail");
			return false;  
		}
		unsigned int err_code1=0,err_code2=0;
		//FTM_Cal_Sweep_Response sweep_resp[256]={0};
		int iResult=0;
		CString strResult;
		for (int i=0;i<m_ivTxFreqPAState.size();i++)
		{
			tx_freq_Response[i+3].aiTxPower=(int)(100*dPowerListResults[i]);
			if (5==m_ivFreqTxPurpose[i])
			{
				aTx_LimVsFreqMeasured.aiTxMeasuredPower[ichindex][i]=dPowerListResults[i];
				if (aTx_LimVsFreqMeasured.aiTxMeasuredPower[ichindex][i]>m_dvTFPLimitMax[i]||aTx_LimVsFreqMeasured.aiTxMeasuredPower[ichindex][i]<m_dvTFPLimitMin[i])
				{
					iResult++;
					strResult=_T("Failed");
				}
				else
				{
					strResult=_T("Passed");
				}
				strMsg.Format("%d	%d	%d	%.0f	%.2f	%.2f	%.2f	%s",m_ivChannellist[ichindex],m_ivTxFreqPAState[i],aiRGI[i],aiBias[i],aTx_LimVsFreqMeasured.aiTxMeasuredPower[ichindex][i],m_dvTFPLimitMin[i],m_dvTFPLimitMax[i],strResult);
				LogTrace(MSG_MID,strMsg);
			}	

			if (4==m_ivFreqTxPurpose[i])
			{			
				if (dPowerListResults[i]>m_dvTFPLimitMax[i]||dPowerListResults[i]<m_dvTFPLimitMin[i])
				{
					iResult++;
					strResult=_T("Failed");
				}
				else
				{
					strResult=_T("Passed");
				}
				strMsg.Format("%d	%d	%d	%.0f	%.2f	%.2f	%.2f	%s",m_ivChannellist[ichindex],m_ivTxFreqPAState[i],aiRGI[i],aiBias[i],dPowerListResults[i],m_dvTFPLimitMin[i],m_dvTFPLimitMax[i],strResult);
				LogTrace(MSG_MID,strMsg);
			}

		}

		if((iErrorcode=m_pPhone->FTM_GET_CAL_SWEEP_RESULTS_V2((void*)tx_freq_Response,(void*)tx_freq_Sweep,11,&err_code1,&err_code2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Get Cal Sweep Result Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				return false;
		}

		for (int i=0;i<m_ivTxFreqPAState.size();i++)
		{			
			if (5==m_ivFreqTxPurpose[i])
			{
				aTx_LimVsFreqMeasured.aiTxMeasuredHDET[ichindex][i]=tx_freq_Response[i+3].aiHDETResults;
			}


		}
		for (int i=0;i<11;i++)
		{
			tx_rx_Sweep[inumTRxFreq]=tx_freq_Sweep[i];
			tx_rx_Response[inumTRxFreq]=tx_freq_Response[i];
			inumTRxFreq++;
		}
		if (iResult>0)
		{
			strMsg.Format("Result of Tx Freq Comp is out of limit");

			LogTrace(MSG_ERROR,strMsg);

			return false;

		}

	}

	if((iErrorcode=m_pPhone->RFCAL_CDMA_Tx_LimVsFreq_Results(m_iNVModeID,m_dvTxFreqPower[0],&aTx_LimVsFreqMeasured,&aTxF_MeasuredChannels,&aTxF_NV_Channels,&aTx_LimVsFreq_NV_Result,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_Tx_LimVsFreq_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	strMsg.Format("NV_TX_LIM_VS_FREQ");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("%s:%d",aTx_LimVsFreq_NV_Result.oNVitem.sNVName,aTx_LimVsFreq_NV_Result.oNVitem.iNVenum);
	LogTrace(MSG_MID,strMsg)
	strMsg.Format("Channel	TxAGC	Index	NV	Power	HDET");
	LogTrace(MSG_MID,strMsg);

	for (int i=0;i<m_ivChannellist.size();i++)
	{
		strMsg.Format("%d		%d	%d	%d	%.4f	%d",m_ivChannellist[i],aTx_LimVsFreq_NV_Result.aiExpectedTxAGCatMaxPower[i],i,aTx_LimVsFreq_NV_Result.aiLimVsFreq[i],aTx_LimVsFreq_NV_Result.adTxMaxPower[i],aTx_LimVsFreq_NV_Result.aiExpectedHDETatMaxPower[i]);
		LogTrace(MSG_MID,strMsg);

	}
	CalPassLog("_","_","Tx_FreqComp Calibration PASS")
		return true;
}
bool CESCalWCDMA::SetWCDMACALLOSS()
{
	CString strMsg;
	double dLoss;
	CString strCurrBand;
	DblVtr dvCableLoss;
	strCurrBand.Format("W%d",m_iBand);
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



	if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetLoss(m_iBand,dvCableLoss))
	{
		LogTrace(MSG_ERROR,"Set Cableloss device fail");
		CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		return false;

	}




	return   true;

}

bool CESCalWCDMA::TxRxFreqCompFunc()
{
	CString strMsg;
	int iErrorcode;
	inumTRxFreq=0;
	double MIN_RSSI=-106;
	int iRefCH=7;
	double DYNAMICRANGE= 102.3;
	int const NUM_SEGMENT_PER_SEQUENCE=m_ivFreqTxPurpose.size()>m_ivRxAction.size()?m_ivFreqTxPurpose.size():m_ivRxAction.size();
	int NUM_NOP_SEGMENTS = 10;
	int NUM_NOP_SIGMENTS_PERCH=5;
	int SIZE_OF_SIGMENT=NUM_NOP_SEGMENTS+16*(NUM_NOP_SIGMENTS_PERCH+NUM_SEGMENT_PER_SEQUENCE);
	QMSL_CDMA_RxFreq_Measurement_struct aRX_Measured={0};
	QMSL_CDMA_Rx_DVGA_LNA_Cal_NV_Result aRX_DVGA_LNA_Cal_NV={0};
	memset(&aRX_Measured,0,sizeof(QMSL_CDMA_RxFreq_Measurement_struct));
	aRX_Measured.iPath=0;
	aRX_Measured.iNumMeasuredPowerModes=1;
	aRX_Measured.iNumMeasured_LNA_States=m_ivRxAction.size()-1;

	for(int i=1;i<m_ivRxAction.size();++i)
	{
		aRX_Measured.aiLNA_States[i-1]=m_ivRxAction[i];		
	}
	QMSL_CDMA_MeasuredChannels_struct  aTX_MeasuredChannels={0};
	QMSL_CDMA_MeasuredChannels_struct aRx_MeasuredChannels={0};
	QMSL_CDMA_NVChannels_struct  aTX_NV_Channels={0};
	QMSL_CDMA_NVChannels_struct  aRX_NV_Channels={0};
	memset(&aTX_NV_Channels,0,sizeof(QMSL_CDMA_NVChannels_struct));	
	memset(&aRX_NV_Channels,0,sizeof(QMSL_CDMA_NVChannels_struct));	
	aTX_MeasuredChannels.iRefChannel=m_iTxLinChannel;
	aRx_MeasuredChannels.iRefChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iTxLinChannel);
	QMSL_CDMA_TxLimVsFreq_struct  aTx_LimVsFreqMeasured={0};
	QMSL_CDMA_Tx_LimVsFreq_NV_struct aTx_LimVsFreq_NV_Result={0};
	memset(&aTx_LimVsFreqMeasured,0,sizeof(QMSL_CDMA_TxLimVsFreq_struct));
	aTx_LimVsFreqMeasured.oRefChMeas.iNumMeasurement=myTxLinStruct.aiNumTxRGI[0];
	for (int i=0;i<myTxLinStruct.aiNumTxRGI[0];i++)
	{
		aTx_LimVsFreqMeasured.oRefChMeas.aiTxAGC[i]=myTxLinStruct.aiRGI[0][i];
		aTx_LimVsFreqMeasured.oRefChMeas.aiTxMeasuredPower[i]=myTxLinStruct.adPower[0][i];
		aTx_LimVsFreqMeasured.oRefChMeas.aiTxMeasuredHDET[i]=myTxLinStruct.aiHDET[0][i];
	}

	int iNumOfTxLimMeasurement=0;
	int iNumOfTxLinGainStates=0;
	for (int i=0;i<m_ivFreqTxPurpose.size();i++)
	{
		if (5==m_ivFreqTxPurpose[i])
		{
			iNumOfTxLimMeasurement++;
			
		}
		if (4==m_ivFreqTxPurpose[i])
		{
			iNumOfTxLinGainStates++;
		}
	}
	USHORT iSegmentTimeMS=4;
	memset(tx_rx_Sweep,0,200*sizeof(FTM_Cal_Sweep_Request));
	memset(tx_rx_Response,0,200*sizeof(FTM_Cal_Sweep_Response));
	TRx_Request myTRxRequest[7];
	memset(myTRxRequest,0,7*sizeof(TRx_Request));
	GetTxFreqRGI(m_ivTxFreqPAState,m_dvTxFreqPower,aiRGI,aiBias);

	for (int i = 0;i< m_ivTxFreqPAState.size();i++)
	{	
		myTRxRequest[i].opcode=0x08;
		myTRxRequest[i].txPurpose=m_ivFreqTxPurpose[i];
		myTRxRequest[i].paState=m_ivTxFreqPAState[i];
		myTRxRequest[i].paBias=(dword)aiBias[i];
		myTRxRequest[i].rgi=aiRGI[i];
		myTRxRequest[i].numHdetAvg=m_ivFreqHDETSample[i];
		myTRxRequest[i].numLpmHdetAvg=m_ivFreqLPMHDETSample[i];
		if (0!=m_ivFreqHDETSample[i])
		{
			myTRxRequest[i].opcode|=0x10;
		}
	}
	for (int i=0;i<m_ivRxAction.size();i++)
	{
		myTRxRequest[i].opcode|=0x60;
		myTRxRequest[i].rxActions=0x1 << m_ivRxAction[i];
		myTRxRequest[i].expRxAGC= (1024/DYNAMICRANGE)*(m_dvRxPower[i]-(MIN_RSSI+DYNAMICRANGE/2));
	}

	
	for (int i=0;i<200;i++)
	{
		tx_rx_Sweep[i].segLen = iSegmentTimeMS*1000;
		tx_rx_Sweep[i].rfmode=m_iRFmode;
		tx_rx_Sweep[i].masterDev = 1;
		tx_rx_Sweep[i].slaveDev = -1;
		tx_rx_Sweep[i].txBW = 3;	 
		tx_rx_Sweep[i].rxBW = 3;	
		tx_rx_Sweep[i].chanOffset = 0;
		tx_rx_Sweep[i].txWaveform = 0x01;  
		tx_rx_Sweep[i].numRBs = 1;  
		tx_rx_Sweep[i].startRB = 1;
		tx_rx_Sweep[i].paState = 255; // no-op
		tx_rx_Sweep[i].paBias = 511;
		tx_rx_Sweep[i].rgi = 0;
		tx_rx_Sweep[i].txFlag = 1;
		tx_rx_Sweep[i].hdetFlag = 1;
		tx_rx_Sweep[i].numHdetAvg = 0;
		tx_rx_Sweep[i].numLpmHdetAvg = 0; // NA
		tx_rx_Sweep[i].rxActions = 0xffff;
		tx_rx_Sweep[i].rxPM = 0;
		tx_rx_Sweep[i].expRxAGC = 0;
		tx_rx_Sweep[i].rxFlag = 1;
	}
	
	// Segment 0, Set channel and mode, do not turn on PA
	tx_rx_Sweep[inumTRxFreq].opcode = 0x0001;
	tx_rx_Sweep[inumTRxFreq].ulChan = m_ivChannellist[0];
	tx_rx_Sweep[inumTRxFreq].paState = 255; // no-op
	tx_rx_Sweep[inumTRxFreq].paBias = 511;
	tx_rx_Sweep[inumTRxFreq].rgi = 0;
	inumTRxFreq++;

	

	// Segment 1-9, no op for Set mode channel to take effect
	for(int i = 1; i < NUM_NOP_SEGMENTS; i++)
	{		
		tx_rx_Sweep[inumTRxFreq].opcode = 0x0000;
		tx_rx_Sweep[inumTRxFreq].ulChan = m_ivChannellist[0];
		tx_rx_Sweep[inumTRxFreq].paState = 255; // no-op
		tx_rx_Sweep[inumTRxFreq].paBias = 511;
		tx_rx_Sweep[inumTRxFreq].rgi = 0;
		inumTRxFreq++;
	}
	
	
	aTX_MeasuredChannels.iNumMeasuredChannels=m_ivChannellist.size();
	aRx_MeasuredChannels.iNumMeasuredChannels=m_ivChannellist.size();

	DblVtr dvTRxFreq;
	dvTRxFreq.clear();
	
	for (int iChannelloop=0;iChannelloop<aTX_MeasuredChannels.iNumMeasuredChannels;iChannelloop++)
	{
		aTX_MeasuredChannels.aiMeasuredChannels[iChannelloop]=m_ivChannellist[iChannelloop];
		aTX_NV_Channels.aiNVChannels[iChannelloop]=m_ivChannellist[iChannelloop];
		
		int iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,aTX_MeasuredChannels.aiMeasuredChannels[iChannelloop]);
		aRx_MeasuredChannels.aiMeasuredChannels[iChannelloop]=iDLChannel;
		aRX_NV_Channels.aiNVChannels[iChannelloop]=iDLChannel;
		double dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,aTX_MeasuredChannels.aiMeasuredChannels[iChannelloop],1);
		double dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,0);

		aTx_LimVsFreqMeasured.iNumOfTxLimMeasurement[iChannelloop]=iNumOfTxLimMeasurement;
		for (int i=0;i<iNumOfTxLimMeasurement;i++)
		{
			aTx_LimVsFreqMeasured.aiTxMeasuredPDM[iChannelloop][i]=aiRGI[i];
		}
		
		
		dvTRxFreq.push_back(dDLMhz);
		dvTRxFreq.push_back(dUlMHz);
			
		if (0==iChannelloop)
		{
			tx_rx_Sweep[inumTRxFreq].opcode = 0x0000;
			tx_rx_Sweep[inumTRxFreq].ulChan = aTX_MeasuredChannels.aiMeasuredChannels[iChannelloop];
			tx_rx_Sweep[inumTRxFreq].paState = 255; // no-op
			tx_rx_Sweep[inumTRxFreq].paBias = 511;
			tx_rx_Sweep[inumTRxFreq].rgi = 0;
			inumTRxFreq++;
		} 
		else
		{
			tx_rx_Sweep[inumTRxFreq].opcode = 0x0002;//�л�channel
			tx_rx_Sweep[inumTRxFreq].ulChan = aTX_MeasuredChannels.aiMeasuredChannels[iChannelloop];
			tx_rx_Sweep[inumTRxFreq].paState = 255; // no-op
			tx_rx_Sweep[inumTRxFreq].paBias = 511;
			tx_rx_Sweep[inumTRxFreq].rgi = 0;
			inumTRxFreq++;
		}
		for (int i=1;i<NUM_NOP_SIGMENTS_PERCH;i++)
		{
			tx_rx_Sweep[inumTRxFreq].opcode = 0x0000;
			tx_rx_Sweep[inumTRxFreq].ulChan = aTX_MeasuredChannels.aiMeasuredChannels[iChannelloop];
			tx_rx_Sweep[inumTRxFreq].paState = 255; // no-op
			tx_rx_Sweep[inumTRxFreq].paBias = 511;
			tx_rx_Sweep[inumTRxFreq].rgi = 0;
			inumTRxFreq++;

		}
		for (int i=0;i<NUM_SEGMENT_PER_SEQUENCE;i++)
		{
			tx_rx_Sweep[inumTRxFreq].opcode = myTRxRequest[i].opcode;
			tx_rx_Sweep[inumTRxFreq].ulChan = aTX_MeasuredChannels.aiMeasuredChannels[iChannelloop];
			tx_rx_Sweep[inumTRxFreq].paState = myTRxRequest[i].paState;
			tx_rx_Sweep[inumTRxFreq].paBias = myTRxRequest[i].paBias;
			tx_rx_Sweep[inumTRxFreq].rgi = myTRxRequest[i].rgi;
			tx_rx_Sweep[inumTRxFreq].rxActions=myTRxRequest[i].rxActions;
			tx_rx_Sweep[inumTRxFreq].expRxAGC=myTRxRequest[i].expRxAGC;
			tx_rx_Sweep[inumTRxFreq].numHdetAvg=myTRxRequest[i].numHdetAvg;
			tx_rx_Sweep[inumTRxFreq].numLpmHdetAvg=myTRxRequest[i].numLpmHdetAvg;
			tx_rx_Sweep[inumTRxFreq].txPurpose=myTRxRequest[i].txPurpose;
			inumTRxFreq++;			
			
		}


	}


	DblVtr dvTxLvlRef;
	dvTxLvlRef.clear();
	dvTxLvlRef.push_back(m_dvTFPLimitMax[0]);
	for (int iLoopIndex=1;iLoopIndex<m_dvTxFreqPower.size();iLoopIndex++)
	{
		dvTxLvlRef.push_back(iLoopIndex);
		dvTxLvlRef.push_back(m_dvTFPLimitMax[iLoopIndex]);
	}


	DblVtr dvRxLvl;
	dvRxLvl.clear();
	for (int i=0;i<m_dvRxPower.size();i++)
	{
		dvRxLvl.push_back(m_dvRxPower[i]);
	}
	dvRxLvl.push_back(m_dvRxPower[m_dvRxPower.size()-1]);
	dvRxLvl.push_back(m_dvRxPower[m_dvRxPower.size()-1]);
	dvRxLvl.push_back(m_dvRxPower[m_dvRxPower.size()-1]);
	dvRxLvl.push_back(m_dvRxPower[m_dvRxPower.size()-1]);

	if ((iErrorcode=m_pFunWCDMACalDev->IWCDMAESCalLinearconfig(1,3,iSegmentTimeMS,dvTRxFreq,dvTxLvlRef,dvRxLvl,NUM_NOP_SIGMENTS_PERCH+NUM_SEGMENT_PER_SEQUENCE,m_ivChannellist.size()))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Config Enhanced Sweep Cal equiment fail");
		CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Config Enhanced Sweep Cal equiment fail");
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_CFG_AND_EXEC_CAL_SWEEP((void*)tx_rx_Sweep,inumTRxFreq,false,true))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone TRx Freq Sweep Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			return false;
	}
	DblVtr dvTRxResult;
	dvTRxResult.clear();
	if ((iErrorcode=m_pFunWCDMACalDev->IWCDMAFetchTXRXResults(dvTRxResult))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Fetch ESCal TRx Freq result fail");
		CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Fetch ESCal Linear full bias result fail");
		return false;
	}
	unsigned int err_code1=0,err_code2=0;
	strMsg.Format("MEASUREMENTS: Tx Freq Comp");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("Channel	PAState	TxRGI	Bias	Power	Min	Max	Result");
	LogTrace(MSG_MID,strMsg);
	int iResult=0;
	CString strResult;
	int indexTRxResult=0,indexTRxResponse=NUM_NOP_SEGMENTS+NUM_NOP_SIGMENTS_PERCH;
	int iNumOfSigmentPerSeuence=0;
	if (m_strTesterDevice.Find("8820")!=-1)
	{
		iNumOfSigmentPerSeuence=NUM_NOP_SIGMENTS_PERCH+NUM_SEGMENT_PER_SEQUENCE-1;
	}
	else
	{
		iNumOfSigmentPerSeuence=NUM_NOP_SIGMENTS_PERCH+NUM_SEGMENT_PER_SEQUENCE;
	}
	for (int iSequenceloop=0;iSequenceloop<m_ivChannellist.size();iSequenceloop++)
	{
		for (int i=0;i<iNumOfTxLimMeasurement;i++)
		{
			aTx_LimVsFreqMeasured.aiTxMeasuredPower[iSequenceloop][i]=dvTRxResult[iSequenceloop*(iNumOfSigmentPerSeuence)+i];
			if (aTx_LimVsFreqMeasured.aiTxMeasuredPower[iSequenceloop][i]>m_dvTFPLimitMax[i]||aTx_LimVsFreqMeasured.aiTxMeasuredPower[iSequenceloop][i]<m_dvTFPLimitMin[i])
			{
				iResult++;
				strResult=_T("Failed");
			}
			else
			{
				strResult=_T("Passed");
			}
			strMsg.Format("%d	%d	%d	%.0f	%.2f	%.2f	%.2f	%s",m_ivChannellist[iSequenceloop],m_ivTxFreqPAState[i],aiRGI[i],aiBias[i],aTx_LimVsFreqMeasured.aiTxMeasuredPower[iSequenceloop][i],m_dvTFPLimitMin[i],m_dvTFPLimitMax[i],strResult);
			LogTrace(MSG_MID,strMsg);

		}
		
		for (int i=0;i<m_ivFreqTxPurpose.size()-iNumOfTxLimMeasurement;i++)
		{
			double dPower=0;
			if (4==m_ivFreqTxPurpose[i+iNumOfTxLimMeasurement])
			{
				dPower=dvTRxResult[iSequenceloop*(iNumOfSigmentPerSeuence)+iNumOfTxLimMeasurement+i];
				if (dPower>m_dvTFPLimitMax[i+iNumOfTxLimMeasurement]||dPower<m_dvTFPLimitMin[i+iNumOfTxLimMeasurement])
				{
					iResult++;
					strResult=_T("Failed");
				}
				else
				{
					strResult=_T("Passed");
				}
				strMsg.Format("%d	%d	%d	%.0f	%.2f	%.2f	%.2f	%s",m_ivChannellist[iSequenceloop],m_ivTxFreqPAState[i+iNumOfTxLimMeasurement],aiRGI[i+iNumOfTxLimMeasurement],aiBias[i+iNumOfTxLimMeasurement],dPower,m_dvTFPLimitMin[i+iNumOfTxLimMeasurement],m_dvTFPLimitMax[i+iNumOfTxLimMeasurement],strResult);
				LogTrace(MSG_MID,strMsg);
			}
			
		}
		for (int iSegmentloop=0;iSegmentloop<iNumOfSigmentPerSeuence;iSegmentloop++)
		{
			tx_rx_Response[indexTRxResponse].aiTxPower=(int)(100*dvTRxResult[indexTRxResult]);
			indexTRxResponse++;
			indexTRxResult++;
		}
		if (m_strTesterDevice.Find("8820")!=-1)
		{
			indexTRxResponse++;
		}
		
	}
	if (iResult>0)
	{
		strMsg.Format("Result of Tx Freq Comp is out of limit");

		LogTrace(MSG_ERROR,strMsg);

		return false;

	}
	if((iErrorcode=m_pPhone->FTM_GET_CAL_SWEEP_RESULTS_V2((void*)tx_rx_Response,(void*)tx_rx_Sweep,inumTRxFreq,&err_code1,&err_code2))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Get Cal Sweep Result Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)

			return false;
	}

	strMsg.Format("MEASUREMENTS:Rx LNA Offset Freq Comp");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("Channel	RxPath	RxLevel	Range	LNA	Min	Max	Result");
	LogTrace(MSG_MID,strMsg);
	indexTRxResponse=NUM_NOP_SEGMENTS+NUM_NOP_SIGMENTS_PERCH;
	
	for (int iSequenceloop=0;iSequenceloop<m_ivChannellist.size();iSequenceloop++)
	{
		for (int i=0;i<iNumOfTxLimMeasurement;i++)
		{
			aTx_LimVsFreqMeasured.aiTxMeasuredHDET[iSequenceloop][i]=tx_rx_Response[iSequenceloop*(NUM_NOP_SIGMENTS_PERCH+NUM_SEGMENT_PER_SEQUENCE)+i+NUM_NOP_SEGMENTS+NUM_NOP_SIGMENTS_PERCH].aiHDETResults;
		}
		aRX_Measured.aiDVGA_Measured[iSequenceloop][0]=tx_rx_Response[iSequenceloop*(NUM_NOP_SIGMENTS_PERCH+NUM_SEGMENT_PER_SEQUENCE)+NUM_NOP_SEGMENTS+NUM_NOP_SIGMENTS_PERCH].aiRxResults[0][0];
		
		if (aRX_Measured.aiDVGA_Measured[iSequenceloop][0]>m_ivLNAOffsetMax[0]||aRX_Measured.aiDVGA_Measured[iSequenceloop][0]<m_ivLNAOffsetMin[0])
		{
			iResult++;
			strResult=_T("Failed");
		}
		else
		{
			strResult=_T("Passed");
		}
		strMsg.Format("%d	0	%.2f	%d	%d	%d	%d	%s",m_ivChannellist[iSequenceloop],m_dvRxPower[0],m_ivRxAction[0],aRX_Measured.aiDVGA_Measured[iSequenceloop][0],m_ivLNAOffsetMin[0],m_ivLNAOffsetMax[0],strResult);
		LogTrace(MSG_MID,strMsg);
		
		for (int i=1;i<m_ivRxAction.size();i++)
		{

			aRX_Measured.aiLNA_Measured[iSequenceloop][i-1][0]=tx_rx_Response[iSequenceloop*(NUM_NOP_SIGMENTS_PERCH+NUM_SEGMENT_PER_SEQUENCE)+i+NUM_NOP_SEGMENTS+NUM_NOP_SIGMENTS_PERCH].aiRxResults[0][i];
			if (aRX_Measured.aiLNA_Measured[iSequenceloop][i-1][0]>m_ivLNAOffsetMax[i]||aRX_Measured.aiLNA_Measured[iSequenceloop][i-1][0]<m_ivLNAOffsetMin[i])
			{
				iResult++;
				strResult=_T("Failed");
			}
			else
			{
				strResult=_T("Passed");
			}
			strMsg.Format("%d	0	%.2f	%d	%d	%d	%d	%s",m_ivChannellist[iSequenceloop],m_dvRxPower[i],m_ivRxAction[i],aRX_Measured.aiLNA_Measured[iSequenceloop][i-1][0],m_ivLNAOffsetMin[i],m_ivLNAOffsetMax[i],strResult);
			LogTrace(MSG_MID,strMsg);			
		}
				
	}
	if (iResult>0)
	{
		strMsg.Format("Result of Rx LNA Offset Freq Comp is out of limit");
		LogTrace(MSG_MID,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->RFCAL_CDMA_Tx_LimVsFreq_Results(m_iNVModeID,m_dvTxFreqPower[0],&aTx_LimVsFreqMeasured,&aTX_MeasuredChannels,&aTX_NV_Channels,&aTx_LimVsFreq_NV_Result,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_Tx_LimVsFreq_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	strMsg.Format("NV_TX_LIM_VS_FREQ");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("%s:%d",aTx_LimVsFreq_NV_Result.oNVitem.sNVName,aTx_LimVsFreq_NV_Result.oNVitem.iNVenum);
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("Channel	TxAGC	Index	NV	Power	HDET");
	LogTrace(MSG_MID,strMsg);

	for (int i=0;i<m_ivChannellist.size();i++)
	{
		strMsg.Format("%d		%d	%d	%d	%.4f	%d",m_ivChannellist[i],aTx_LimVsFreq_NV_Result.aiExpectedTxAGCatMaxPower[i],i,aTx_LimVsFreq_NV_Result.aiLimVsFreq[i],aTx_LimVsFreq_NV_Result.adTxMaxPower[i],aTx_LimVsFreq_NV_Result.aiExpectedHDETatMaxPower[i]);
		LogTrace(MSG_MID,strMsg);

	}
	strMsg.Format("B%d",m_iBand);
	CalPassLog(strMsg,"_","TxFreqComp Pass");
	if((iErrorcode=m_pPhone->RFCAL_CDMA_RxCal_Results(m_iNVModeID,0,1,&aRX_Measured,&aRx_MeasuredChannels,&aRX_NV_Channels,&aRX_DVGA_LNA_Cal_NV,1,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_RxCal_Results Primary Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	strMsg.Format("RX DVGA and LNA Offset NV Value");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("%s:%d",aRX_DVGA_LNA_Cal_NV.aDVGA.oNVitem.sNVName,aRX_DVGA_LNA_Cal_NV.aDVGA.oNVitem.iNVenum);
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("RefChannel DVGA offset=%d",aRX_DVGA_LNA_Cal_NV.aDVGA.iDVGAOffset);
	LogTrace(MSG_MID,strMsg);
	for(int iLNARangeIndex=0;iLNARangeIndex<aRX_Measured.iNumMeasured_LNA_States;++iLNARangeIndex)
	{
		strMsg.Format("%s:%d",aRX_DVGA_LNA_Cal_NV.aLNA[iLNARangeIndex].oNVitem.sNVName,aRX_DVGA_LNA_Cal_NV.aLNA[iLNARangeIndex].oNVitem.iNVenum);
		LogTrace(MSG_MID,strMsg);
		strMsg.Format("RefChannel LNA%d offset=%d",iLNARangeIndex,aRX_DVGA_LNA_Cal_NV.aLNA[iLNARangeIndex].iLNAOffset);
		LogTrace(MSG_MID,strMsg);
	}
	strMsg.Format("NV_VGA_GAIN_OFFSET_VS_FREQ");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("%s:%d",aRX_DVGA_LNA_Cal_NV.aDVGAvsFreq.oNVitem.sNVName,aRX_DVGA_LNA_Cal_NV.aDVGAvsFreq.oNVitem.iNVenum);
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("chan	RxPath	 RxPM	NV");
	LogTrace(MSG_MID,strMsg);
	for(int iNumPMMode=0;iNumPMMode<m_ivRxPM.size();++iNumPMMode)
	{
		for(int iCHIndex=0;iCHIndex<m_ivChannellist.size();++iCHIndex)
		{
			strMsg.Format("%d	%d	%d	%d",m_ivChannellist[iCHIndex],m_iRXPath,iNumPMMode,aRX_DVGA_LNA_Cal_NV.aDVGAvsFreq.iDVGAOffsetVsFreqItem[iCHIndex][iNumPMMode]);
			LogTrace(MSG_MID,strMsg);
		}
	}
	strMsg.Format("NV_LNA_OFFSET_VS_FREQ");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("chan	LNA	 RxPM	NV");
	LogTrace(MSG_MID,strMsg);
	for(int iLNAIndex=0;iLNAIndex<aRX_Measured.iNumMeasured_LNA_States;++iLNAIndex)
	{
		strMsg.Format("%s:%d",aRX_DVGA_LNA_Cal_NV.aLNAvsFreq[iLNAIndex].oNVitem.sNVName,aRX_DVGA_LNA_Cal_NV.aLNAvsFreq[iLNAIndex].oNVitem.iNVenum);
		LogTrace(MSG_MID,strMsg);
		for(int iNumPMMode=0;iNumPMMode<m_ivRxPM.size();++iNumPMMode)
		{
			for(int iCHIndex=0;iCHIndex<m_ivChannellist.size();++iCHIndex)
			{
				strMsg.Format("%d	%d	%d	%d",m_ivChannellist[iCHIndex],aRX_Measured.aiLNA_States[iLNAIndex],iNumPMMode,aRX_DVGA_LNA_Cal_NV.aLNAvsFreq[iLNAIndex].iLNAOffsetVsFreqItem[iCHIndex][iNumPMMode]);
				LogTrace(MSG_MID,strMsg);
			}
		}

	}
	strMsg.Format("B%d",m_iBand);
	CalPassLog(strMsg,"_","RxFreqComp Pass");
	return true;
}
bool CESCalWCDMA::ArrangeMyTxLinStruct(TxlinStruct *txlinstruct)
{
	TxlinStruct txlinstructold={0};
	int iNumPAState=0;

	//memcpy(txlinstructold,txlinstruct,sizeof(TxlinStruct));
	txlinstructold=*txlinstruct;
	memset(txlinstruct,0,sizeof(TxlinStruct));

	txlinstruct->aiNumTxRGI[iNumPAState]=txlinstructold.aiNumTxRGI[0];
	txlinstruct->aiPAState[iNumPAState]=txlinstructold.aiPAState[0];
	txlinstruct->aiTxPurpose[iNumPAState]=txlinstructold.aiTxPurpose[0];	
	for (int i=0;i<txlinstructold.aiNumTxRGI[0];i++)
	{
		txlinstruct->adPower[iNumPAState][i]=txlinstructold.adPower[0][i];
		txlinstruct->aiRGI[iNumPAState][i]=txlinstructold.aiRGI[0][i];
		txlinstruct->aiBias[iNumPAState][i]=txlinstructold.aiBias[0][i];
		txlinstruct->aiHDET[iNumPAState][i]=txlinstructold.aiHDET[0][i];
		txlinstruct->aiHDETLPM[iNumPAState][i]=txlinstructold.aiHDETLPM[0][i];		
		
	}
	iNumPAState++;
	txlinstruct->iNumPAStates=iNumPAState;
	
	for (int i=1;i<txlinstructold.iNumPAStates;i++)
	{
		bool bFindit=false;
		for (int j=0;j<txlinstruct->iNumPAStates;j++)
		{
			if (txlinstructold.aiPAState[i]==txlinstruct->aiPAState[j])
			{
				for (int k=0;k<txlinstructold.aiNumTxRGI[i];k++)
				{
					bool bInsertIt=false;
					for (int l=0;l<txlinstruct->aiNumTxRGI[j];l++)
					{
						if (txlinstructold.aiRGI[i][k]==txlinstruct->aiRGI[j][l])
						{
							txlinstruct->adPower[j][l]=txlinstructold.adPower[i][k];
							txlinstruct->aiRGI[j][l]=txlinstructold.aiRGI[i][k];
							txlinstruct->aiBias[j][l]=txlinstructold.aiBias[i][k];
							txlinstruct->aiHDET[j][l]=txlinstructold.aiHDET[i][k];
							txlinstruct->aiHDETLPM[j][l]=txlinstructold.aiHDETLPM[i][k];
							bInsertIt=true;					
							break;

						}
						else if (txlinstructold.aiRGI[i][k]>txlinstruct->aiRGI[j][l])
						{	
							for (int m= txlinstruct->aiNumTxRGI[j];m>l;m--)
							{
								txlinstruct->adPower[j][m]=txlinstruct->adPower[j][m-1];
								txlinstruct->aiRGI[j][m]=txlinstruct->aiRGI[j][m-1];
								txlinstruct->aiBias[j][m]=txlinstruct->aiBias[j][m-1];
								txlinstruct->aiHDET[j][m]=txlinstruct->aiHDET[j][m-1];
								txlinstruct->aiHDETLPM[j][m]=txlinstruct->aiHDETLPM[j][m-1];
							}
							txlinstruct->adPower[j][l]=txlinstructold.adPower[i][k];
							txlinstruct->aiRGI[j][l]=txlinstructold.aiRGI[i][k];
							txlinstruct->aiBias[j][l]=txlinstructold.aiBias[i][k];
							txlinstruct->aiHDET[j][l]=txlinstructold.aiHDET[i][k];
							txlinstruct->aiHDETLPM[j][l]=txlinstructold.aiHDETLPM[i][k];
							txlinstruct->aiNumTxRGI[j]++;
							bInsertIt=true;				
							break;

						}

					}
					if (false==bInsertIt)
					{
						unsigned short l=txlinstruct->aiNumTxRGI[j];
						txlinstruct->adPower[j][l]=txlinstructold.adPower[i][k];
						txlinstruct->aiRGI[j][l]=txlinstructold.aiRGI[i][k];
						txlinstruct->aiBias[j][l]=txlinstructold.aiBias[i][k];
						txlinstruct->aiHDET[j][l]=txlinstructold.aiHDET[i][k];
						txlinstruct->aiHDETLPM[j][l]=txlinstructold.aiHDETLPM[i][k];
						txlinstruct->aiNumTxRGI[j]++;
					}
				}
				bFindit=true;

			}

		}
		if (false==bFindit)
		{
			txlinstruct->aiNumTxRGI[iNumPAState]=txlinstructold.aiNumTxRGI[i];
			txlinstruct->aiPAState[iNumPAState]=txlinstructold.aiPAState[i];
			txlinstruct->aiTxPurpose[iNumPAState]=txlinstructold.aiTxPurpose[i];	
			for (int k=0;k<txlinstructold.aiNumTxRGI[i];k++)
			{
				txlinstruct->adPower[iNumPAState][k]=txlinstructold.adPower[i][k];
				txlinstruct->aiRGI[iNumPAState][k]=txlinstructold.aiRGI[i][k];
				txlinstruct->aiBias[iNumPAState][k]=txlinstructold.aiBias[i][k];
				txlinstruct->aiHDET[iNumPAState][k]=txlinstructold.aiHDET[i][k];
				txlinstruct->aiHDETLPM[iNumPAState][k]=txlinstructold.aiHDETLPM[i][k];	
			}
			iNumPAState++;
			txlinstruct->iNumPAStates=iNumPAState;
		}
		
		
		
	}
	return true;

}

bool CESCalWCDMA::GetTxFreqRGI(IntVtr ivPAState,DblVtr dvPower,int* aiRGIList,double* aiBiasList)
{
	CString strMsg;
	strMsg.Format("Get RGI form refChannel;");
	LogTrace(MSG_MID,strMsg);
	int iRGI=0;
	double iBias=0;
	for (int i=0;i<ivPAState.size();i++)
	{
		
		for (int j=0;j<myTxLinStruct.iNumPAStates;j++)
		{

			if (ivPAState[i]==myTxLinStruct.aiPAState[j])
			{
				
				m_pPhone->RFCal_LinearInterpolation(myTxLinStruct.adPower[j],myTxLinStruct.aiBias[j],myTxLinStruct.aiNumTxRGI[j],&dvPower[i],&iBias,1,0,0xFFFFFFFF);
				aiBiasList[i]=iBias;
				m_pPhone->RFCal_LinearInterpolation(myTxLinStruct.adPower[j],(int *)myTxLinStruct.aiRGI[j],myTxLinStruct.aiNumTxRGI[j],&dvPower[i],&iRGI,1,0,127);
				aiRGIList[i]=iRGI;

				strMsg.Format("PAState %d Power %.2f Bias %.0f RGI %d",ivPAState[i],dvPower[i],iBias,iRGI);
				LogTrace(MSG_MID,strMsg);
				
			}
		}
		

	}
	return true;
}

bool CESCalWCDMA::GetPowerVsBiasXml(CString xmlpath,int rf_mode,int device,int channel,int paState,double* pwrlist,int* biaslist,int* biasNum )
{
	/*CoInitialize(NULL);
	CComPtr<IXMLDOMDocument> spDoc;
	spDoc.CoCreateInstance(CLSID_DOMDocument);
	VARIANT_BOOL vb;
	char szXmlPath[MAX_PATH];
	szXmlPath = xmlpath.GetBuffer();
	xmlpath.ReleaseBuffer();
	spDoc->load(CComVariant(OLESTR(szXmlPath)),&vb);
	CComPtr<IXMLDOMElement> spRootEle;
	CComPtr<IXMLDOMNodeList> spNodelist;
	spDoc->get_documentElement(&spRootEle);
	spRootEle->get_childNodes(&spNodelist);
	long nNodelen;
	spNodelist->get_length(&nNodelen);
	for (int i=0;i!=nNodelen;i++)
	{
		CComPtr<IXMLDOMNode> spNode;
		CComPtr<IXMLDOMNamedNodeMap> spNodeMap;
		spNodelist->get_item(i,&spNode);
		spNode->get_attributes(&spNodeMap);
		
	}*/
	return true;

}

bool CESCalWCDMA::GetPowerVsBiasIni(CString IniName,int rf_mode,int device,int channel,int paState,double* pwrlist,dword* biaslist,int* biasNum )
{

	CString strIniPathName;
	CStringVtr strVtr;
	DblVtr dvPowerlist;
	DblVtr ivBiaslist;
	FILE* fp1;
	CString strTemp;
	_TCHAR _tKeyValue[1000];
	CString strKeyValue;
	char szTemp[_MAX_PATH];
	::GetModuleFileName(NULL, szTemp, _MAX_PATH);
	strIniPathName.Format("%s",szTemp);
	strIniPathName = strIniPathName.Left(strIniPathName.ReverseFind(_T('\\')));	
	
	strIniPathName=strIniPathName+_T("\\RFCalInput\\")+IniName;
	
	if((fp1=fopen(strIniPathName,"r"))==NULL)
	{
		strTemp=strIniPathName+_T("  not exist");
		LogTrace(MSG_ERROR,strTemp);
		return false;
	}	
	strTemp=_T("Read PowerVsBias from ")+strIniPathName;
	LogTrace(MSG_MID,strTemp);
	CString strSection;
	strSection.Format("rf_mode%ddevice%dchannel%dpa_state%d",rf_mode,device,channel,paState);
	::GetPrivateProfileString(strSection,_T("pwr"),NULL,_tKeyValue,sizeof(_tKeyValue),strIniPathName);
	strKeyValue.Format("%s",_tKeyValue);
	CStr::ParseString(strKeyValue,_T(","),strVtr);
	CStr::StrVtr2DblVtr(dvPowerlist,strVtr);
	::GetPrivateProfileString(strSection,_T("bias"),NULL,_tKeyValue,sizeof(_tKeyValue),strIniPathName);	
	strKeyValue.Format("%s",_tKeyValue);
	CStr::ParseString(strKeyValue,_T(","),strVtr);
	CStr::StrVtr2DblVtr(ivBiaslist,strVtr);
	if (ivBiaslist.size()!=dvPowerlist.size()||0==ivBiaslist.size())
	{
		strTemp.Format("Power number or Bias number is wrong; Power number %d,Bias number %d",dvPowerlist.size(),ivBiaslist.size());
		LogTrace(MSG_MID,strTemp);
		fclose(fp1);
		return false;
	}
	strTemp.Format("Power number Vs Bias RFMode = %d,Device = %d,Channel = %d,PAstate = %d",rf_mode,device,channel,paState);
	LogTrace(MSG_MID,strTemp);
	for (int i=0;i<ivBiaslist.size();i++)
	{
		pwrlist[i]=dvPowerlist[i];
		biaslist[i]=(dword)ivBiaslist[i];
		/*strTemp.Format("power = %.2f, bias = %d",pwrlist[i],biaslist[i]);
		LogTrace(MSG_MID,strTemp);*/
	}
	*biasNum=ivBiaslist.size();
	
	fclose(fp1);
	return true;
}

bool CESCalWCDMA::GenerateAndWriteNV()
{
	CString strMsg;
	int iErrorcode;
	FTM_Cal_Sweep_Request aTx_MuliLin_request[1000];
	FTM_Cal_Sweep_Response aTx_MuliLin_response[1000];
	QMSL_Tx_Cal_Complete_NV_Type tx_nv_struct;
	QMSL_Tx_Cal_NV_Gen_Info tx_lin_nv_gen;
	unsigned short numLin=0;
	// Decides which NV should be written to. Prx or SV. 0 = PRx, 2= SV Path.
	unsigned short nvPath = 0;	

	memset((void*)aTx_MuliLin_request,0,1000*sizeof(FTM_Cal_Sweep_Request));
	memset((void*)aTx_MuliLin_response,0,1000*sizeof(FTM_Cal_Sweep_Response));

	memset(&tx_nv_struct,0,sizeof(QMSL_Tx_Cal_Complete_NV_Type));
	memset(&tx_lin_nv_gen,0,sizeof(QMSL_Tx_Cal_NV_Gen_Info));
	int numRecords=0;
	for (int i=0;i<inumTxlin;i++)
	{
		aTx_MuliLin_request[numRecords]=tx_Sweep[i];
		aTx_MuliLin_response[numRecords]=sweep_resp[i];
		numRecords++;

	}

	for (int i=0;i<inumTRxFreq;i++)
	{
		aTx_MuliLin_request[numRecords]=tx_rx_Sweep[i];
		aTx_MuliLin_response[numRecords]=tx_rx_Response[i];
		numRecords++;

	}

	for (int i=0;i<m_vPAState.size();i++)
	{
		tx_lin_nv_gen.ref_chan_list[m_vPAState[i]][0][0]=m_iTxLinChannel;
		tx_lin_nv_gen.upper_bound_chan_list[m_vPAState[i]][0][0]=m_iUpperBoundChan;

		tx_lin_nv_gen.ref_chan_list[m_vPAState[i]][2][0]=m_iTxLinChannel;
		tx_lin_nv_gen.upper_bound_chan_list[m_vPAState[i]][2][0]=m_iUpperBoundChan;

	}
	for ( int i=0;i<16;i++)
	{
		tx_lin_nv_gen.freq_comp_ch_list[i]=-1;
	}

	for ( int i=0;i<m_ivChannellist.size();i++)
	{
		tx_lin_nv_gen.freq_comp_ch_list[i]=m_ivChannellist[i];
	}
	for (int i=0;i<m_ivFreqTxPurpose.size();i++)
	{
		if (4==m_ivFreqTxPurpose[i])
		{
			tx_lin_nv_gen.freq_comp_ref_ch_list[m_ivTxFreqPAState[i]]=m_iTxLinChannel;

			tx_lin_nv_gen.freq_comp_rgi_list[m_ivTxFreqPAState[i]][0]=aiRGI[i];
			tx_lin_nv_gen.freq_comp_bias_list[m_ivTxFreqPAState[i]][0]=aiBias[i];
			tx_lin_nv_gen.rgi_threshold_list[m_ivTxFreqPAState[i]][0]=128;	

		}
	}



	iErrorcode=m_pPhone->RFCAL_Complete_TxRxCal(m_iNVModeID,aTx_MuliLin_request,aTx_MuliLin_response,&tx_nv_struct,numRecords,&tx_lin_nv_gen,&numLin,nvPath,true);
	strMsg.Format("NV_Cal_V3_FreqComp");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("Channel	PA	TxCal");
	LogTrace(MSG_MID,strMsg);
	
	for (int i=0;i<m_ivTxFreqPAState.size();i++)
	{
		if (4==m_ivFreqTxPurpose[i])
		{
			for (int j =0;j<m_ivChannellist.size();j++)
			{
				strMsg.Format("%d		%d	%d",m_ivChannellist[j],m_ivTxFreqPAState[i],tx_nv_struct.band_cal_data.tx_pa_state_cal_data[m_ivTxFreqPAState[i]].tx_freq_offsets->freq_comp[j]);
				LogTrace(MSG_MID,strMsg);

			}
		}

	}

	strMsg.Format("NV_Cal_V3_Lin_Tables");
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("%s:%d",tx_nv_struct.oTxCalNVItem.sNVName,tx_nv_struct.oTxCalNVItem.iNVenum);
	LogTrace(MSG_MID,strMsg);
	strMsg.Format("Index	Channel	RGI	Power	Bias");
	LogTrace(MSG_MID,strMsg);
	for (int i=0;i<numLin;i++)
	{
		for (int j =0;j<64;j++)
		{
			strMsg.Format("%d	%d	%d	%d	%d",i,tx_nv_struct.tx_lin_data[i].tx_chan,tx_nv_struct.tx_lin_data[i].rgi[j],tx_nv_struct.tx_lin_data[i].power[j],tx_nv_struct.tx_lin_data[i].apt[j]);
			LogTrace(MSG_MID,strMsg);
		}
	}

	strMsg.Format("B%d",m_iBand);
	CalPassLog(strMsg,"_","TxLinearizer Generate and WriteNV Pass");
	return true;
}

bool CESCalWCDMA::InitData(
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
	itrFind=pcSettingMap->find(_T("Band"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'Band' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		m_iBand=CStr::StrToInt(strValue);
	}

	m_iRFmode=CWCDMABandInfo::GetPhoneMode(m_iBand);
	m_iNVModeID=CWCDMABandInfo::GetNVModeID(m_iBand);
	itrFind=pcSettingMap->find(_T("TxLinChannel"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TxLinChannel' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		m_iTxLinChannel=CStr::StrToInt(strValue);
	}

	itrFind=pcSettingMap->find(_T("UpperBoundChan"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'UpperBoundChan' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		m_iUpperBoundChan=CStr::StrToInt(strValue);
	}

	itrFind=pcSettingMap->find(_T("TxWaveform"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TxWaveform' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		m_iTxWaveform=CStr::StrToInt(strValue);
	}	
	itrFind=pcSettingMap->find(_T("RGIStep"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RGIStep' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_vRGIStep,strVtr);
	}

	itrFind=pcSettingMap->find(_T("PAState"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'PAState' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_vPAState,strVtr);
	}
	itrFind=pcSettingMap->find(_T("StartPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'StartPower' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_vStartPower,strVtr);
	}

	itrFind=pcSettingMap->find(_T("StopPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'StopPower' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_vStopPower,strVtr);
	}

	itrFind=pcSettingMap->find(_T("StartRGI"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'StartRGI' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_vStartRGI,strVtr);
	}	

	itrFind=pcSettingMap->find(_T("StopRGI"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'StopRGI' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_vStopRGI,strVtr);
	}	

	itrFind=pcSettingMap->find(_T("ExpectPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'ExpectPower' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_vExpectPower,strVtr);
	}


	itrFind=pcSettingMap->find(_T("RFDevices"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RFDevices' from ini file!");
		strValue="0,-1";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_vRFDevices,strVtr);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_vRFDevices,strVtr);
	}
	itrFind=pcSettingMap->find(_T("TxPurpose"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TxPurpose' from ini file!");
		m_iTxPurpose=1;
	}
	else
	{
		strValue=itrFind->second;
		m_iTxPurpose=CStr::StrToInt(strValue);
	}

	itrFind=pcSettingMap->find(_T("HDETSample"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'HDETSample' from ini file!");
		strValue="1,0,0,0";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_iHDETSample,strVtr);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_iHDETSample,strVtr);
	}

	itrFind=pcSettingMap->find(_T("LPMHDETSample"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'LPMHDETSample' from ini file!");
		strValue="0,0,0,0";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_iLPMHDETSample,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_iLPMHDETSample,strVtr);
	}
	itrFind=pcSettingMap->find(_T("APTenabled"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'APTenabled' from ini file! defualt is 'true'");
		m_bAPTenabled=true;
	}
	else
	{
		m_bAPTenabled=CStr::StrToBool(itrFind->second);		
	}

	itrFind=pcSettingMap->find(_T("PABiasValue"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'PABiasValue' from ini file!");
		strValue="780,780,780,780";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_iPABiasValue,strVtr);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_iPABiasValue,strVtr);
	}
	if (m_bAPTenabled)
	{
		itrFind=pcSettingMap->find(_T("BiasIniname"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,"Not Find 'BiasIniname' from ini file!");
			return false;
		}
		else
		{
			m_strBiasIniname=itrFind->second;

		}
	}
	

	itrFind=pcSettingMap->find(_T("Channellist"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'Channellist' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivChannellist,strVtr);
	}

	itrFind=pcSettingMap->find(_T("TxFreqPAState"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TxFreqPAState' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivTxFreqPAState,strVtr);
	}

	itrFind=pcSettingMap->find(_T("TxFreqPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TxFreqPower' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvTxFreqPower,strVtr);
	}

	itrFind=pcSettingMap->find(_T("TFPLimitMax"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TFPLimitMax' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvTFPLimitMax,strVtr);
	}

	itrFind=pcSettingMap->find(_T("TFPLimitMin"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TFPLimitMin' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvTFPLimitMin,strVtr);
	}
	itrFind=pcSettingMap->find(_T("FreqHDETSample"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'FreqHDETSample' from ini file!");
		strValue="1,0,0,0";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivFreqHDETSample,strVtr);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivFreqHDETSample,strVtr);
	}

	itrFind=pcSettingMap->find(_T("FreqLPMHDETSample"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_LOW,"Not Find 'FreqLPMHDETSample' from ini file!");
		strValue="0,0,0,0";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivFreqLPMHDETSample,strVtr);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivFreqLPMHDETSample,strVtr);
	}

	itrFind=pcSettingMap->find(_T("FreqTxPurpose"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'FreqTxPurpose' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivFreqTxPurpose,strVtr);
	}

	itrFind=pcSettingMap->find(_T("RxAction"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RxAction' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivRxAction,strVtr);
	}

	itrFind=pcSettingMap->find(_T("RXPath"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RXPath' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		m_iRXPath=CStr::StrToInt(strValue);
	}

	itrFind=pcSettingMap->find(_T("RxPM"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'RxPM' from ini file!defult is 0");
		strValue="0";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivRxPM,strVtr);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivRxPM,strVtr);
	}

	itrFind=pcSettingMap->find(_T("RxPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RxPower' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvRxPower,strVtr);
	}

	itrFind=pcSettingMap->find(_T("LNAOffsetMax"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'LNAOffsetMax' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivLNAOffsetMax,strVtr);
	}

	itrFind=pcSettingMap->find(_T("LNAOffsetMin"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'LNAOffsetMin' from ini file!");
		return false;
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivLNAOffsetMin,strVtr);
	}



	InitData();
	return true;
}

bool CESCalWCDMA::InitData()
{
	m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	return true;
}