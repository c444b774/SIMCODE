#include "stdafx.h"
#include "CRFNVItem.h"
#include "QualPhone.h"

RF_IMPLEMENT_DYNCREATE(CQualPhone)
#pragma warning(disable : 4800)

CQualPhone::CQualPhone()
{
  m_bIsAtMode=false;
}

CQualPhone::~CQualPhone()
{

}
bool CQualPhone::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
{
    CStringStringMapItr itrMap;
	CRFObjectMap::iterator itrObjMap;
    CString strMsg;
	CString strVaule;
	itrMap=pcSettingMap->find(_T("IsUseQPST"));
	if(itrMap==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,_T("Can not find IsUseQPST use default :IsUseQPST =0"))

			m_eLibMode=QPHONEMS;
	}
	else
	{
		strVaule=itrMap->second;
		if(CStr::StrToBool(strVaule))
		m_eLibMode=QPST;
		else
			m_eLibMode=QPHONEMS;

	}

	itrMap=pcSettingMap->find(_T("IsEFS"));
	if(itrMap==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,_T("Can not find IsEFS use default :Use EFS"))

			m_iIsEFS=1;
	}
	else
	{
		strVaule=itrMap->second;
		m_iIsEFS=CStr::StrToInt(strVaule);

	}
    
	/*itrMap=pcSettingMap->find("RFNVItemObject");
	if(itrMap==pcSettingMap->end())
	{
       LogTrace(MSG_WARNING,_T("Can not find RFNVItemObject   use default :RFNVItemObj"))
		strVaule=_T("RFNVItemObj");
	}
	else
	{
		strVaule=itrMap->second;

	}
	
	itrObjMap=cObjectMap.find(strVaule);
	if(itrObjMap==cObjectMap.end())
	{
		 strMsg=_T("Can not find Object: '") +strVaule+_T(" ' from objectlist. spell_check name ");
		LogTrace(MSG_ERROR,strMsg)
			return false;
	}
	else
	{
		m_pcRFNVItems = dynamic_cast<PCRFNVItems>(itrObjMap->second);
	    m_pcRFNVItems->SetPhonePtr(this);
	}*/
	return true;
}
 
bool CQualPhone::InitData()
{
	return true;
}
int CQualPhone::WriteRFNVItemInBatchMode(unsigned short iItemID, unsigned char* piItemData, int iLength, unsigned short* piStatus)
{
	
	CString strMsg = _T("QLIB_DIAG_NV_WRITE_F (iItemID = ") + CStr::IntToStr(iItemID) + _T(" , pItemData[0] = ") + CStr::IntToStr(*piItemData) + _T(", iLength = ") + CStr::IntToStr(iLength) + _T(")");
	LogPhoneStartCommand(strMsg);
	 bool bRet= QLIB_DIAG_NV_WRITE_F(m_hResourceContext, iItemID, piItemData, iLength, piStatus) ;
	 if(!bRet)
	 {
	    strMsg = _T("WriteRFNVItemInBatchMode failed! iStatus = ") + CStr::IntToStr(*piStatus) +_T("Item ID = ") + CStr::IntToStr(iItemID);
		LogTrace(MSG_FATAL, strMsg);
	 }
	
	ReleaseMutex( m_hResourceContext );
	 return bRet?PHONE_SUCCESS:PHONE_CONNECT_FAIL;
}
bool CQualPhone::IsPhoneConnected()
{
	LogPhoneStartCommand(_T("QLIB_IsPhoneConnected"));
	bool bRet=QLIB_IsPhoneConnected(m_hResourceContext);

	ReleaseMutex(m_hResourceContext);
	return bRet;
}
int CQualPhone::FTM_GENERATE_OPCODE(void * sweep_req,bool rfmode_seg,bool tuning_seg,bool rx_cfg_seg,bool rx_meas_seg)
{
	CString strMsg;
	strMsg.Format("FTM_GENERATE_OPCODE(FRMode = %s,Retune =%s,RxCFG = %s,RxmMeas =%s ) ",rfmode_seg?"true":"false",tuning_seg?"true":"false",rx_cfg_seg?"true":"false",rx_meas_seg?"true":"false");
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_FTM_GENERATE_OPCODE(m_hResourceContext,sweep_req,rfmode_seg,tuning_seg,rx_cfg_seg,rx_meas_seg);
	return bRet?PHONE_SUCCESS:ERR_QLIB_FUNCTION_FAILED;

}

int CQualPhone::RFCal_LinearInterpolation(double * adRawX, int *aiRawY, int iNumRawData, double* aInputX, int* aOutputY, int iNumDataPoint, int iMinValue, int iMaxValue)
{
	CString strMsg;
	strMsg.Format("QLIB_RFCal_LinearInterpolation");
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_RFCAL_LinearInterpolation(m_hResourceContext,adRawX,aiRawY,iNumRawData,aInputX,aOutputY,iNumDataPoint,iMinValue,iMaxValue);
	return bRet?PHONE_SUCCESS:ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::RFCal_LinearInterpolation(double * adRawX, double *aiRawY, int iNumRawData, double* aInputX, double* aOutputY, int iNumDataPoint, double iMinValue, double iMaxValue,int iNumOfPtsToAverageSlope)
{
	CString strMsg;
	strMsg.Format("QLIB_RFCal_LinearInterpolation");
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_RFCAL_LinearInterpolation_SlopeAveragingExtrapolation(m_hResourceContext,adRawX,aiRawY,iNumRawData,aInputX,aOutputY,iNumDataPoint,iNumOfPtsToAverageSlope,iMinValue,iMaxValue);
	return bRet?PHONE_SUCCESS:ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SET_Cal_STATE(unsigned char icalState)
{
	CString strMsg;
	strMsg.Format("QLIB_FTM_SET_CALIBRATION_STATE(icalState = %d) ",icalState);
	LogPhoneStartCommand(strMsg);
	QLIB_ConfigureTimeOut(m_hResourceContext,QMSL_Timeout_General,6000);
	bool bRet=QLIB_FTM_SET_CALIBRATION_STATE(m_hResourceContext,icalState);
	return PHONE_SUCCESS;

}

int CQualPhone::FTM_CFG_AND_EXEC_CAL_SWEEP(void* sweep_req, unsigned long num_seg, bool is_Last_Sweep, bool enableDbgMsgs )
{
	CString strMsg;
	strMsg.Format("QLIB_FTM_CFG_AND_EXEC_CAL_SWEEP(num_seg = %d) ",num_seg);
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_FTM_CFG_AND_EXEC_CAL_SWEEP(m_hResourceContext,sweep_req,num_seg,is_Last_Sweep,enableDbgMsgs);
	return bRet?PHONE_SUCCESS:ERR_QLIB_FUNCTION_FAILED;
}

int CQualPhone::FTM_GET_CAL_SWEEP_RESULTS_V2(void * sweep_resp, void * sweep_req, unsigned long num_seg, unsigned int * err_code_1, unsigned int * err_code_2 )
{
	CString strMsg;
	strMsg.Format("QLIB_FTM_GET_CAL_SWEEP_RESULTS_V2(num_seg = %d) ",num_seg);
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_FTM_GET_CAL_SWEEP_RESULTS_V2(m_hResourceContext,sweep_resp,sweep_req,num_seg,err_code_1,err_code_2);
	return bRet?PHONE_SUCCESS:ERR_QLIB_FUNCTION_FAILED;

}
int CQualPhone::FTM_DO_SELFCAL(unsigned char ical_type)
{
	CString strMsg;
	strMsg.Format("QLIB_FTM_DO_SELF_CAL (ical_type = %d) ",ical_type);
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_FTM_DO_SELF_CAL(m_hResourceContext,ical_type);
	return bRet?PHONE_SUCCESS:ERR_QLIB_FUNCTION_FAILED;

}

int CQualPhone::FTM_FTM_RFNV_WRITE(unsigned short iRFNV_ID, unsigned char* pData, unsigned short iDataSz, unsigned short* iFTM_Error_Code)
{
	CString strMsg;
	strMsg.Format("QLIB_FTM_FTM_RFNV_WRITE (iRFNV_ID = %d) ",iRFNV_ID);
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_FTM_RFNV_WRITE(m_hResourceContext,iRFNV_ID,pData,iDataSz,iFTM_Error_Code);
	return bRet?PHONE_SUCCESS:ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_GSM_BER_StopSession()
{
	 LogPhoneStartCommand(_T("QLIB_FTM_GSM_BER_StopSession"));
	  bool bRet=QLIB_FTM_GSM_BER_StopSession(m_hResourceContext);
	 ReleaseMutex(m_hResourceContext);
	 return bRet?PHONE_SUCCESS:PHONE_CONNECT_FAIL;
	 
}
int CQualPhone::FTM_GSM_BER_StartSession(unsigned long iTimeOut_ms)
{
     LogPhoneStartCommand(_T("QLIB_FTM_GSM_BER_StartSession"));
	 bool bRet=QLIB_FTM_GSM_BER_StartSession(m_hResourceContext,iTimeOut_ms);
	 ReleaseMutex(m_hResourceContext);
	 return bRet?PHONE_SUCCESS:PHONE_CONNECT_FAIL;
}

int CQualPhone::FTM_GSM_BER_AssignBCCH(unsigned short iChannel, unsigned char iBand)
{
	CString strMsg=_T("QLIB_FTM_GSM_BER_AssignBCCH(iCHannel=")+CStr::IntToStr(iChannel) +_T(" , iBand=")+CStr::IntToStr(iBand) +_T(" )");
    LogPhoneStartCommand(strMsg);
    bool bRet=QLIB_FTM_GSM_BER_AssignBCCH(m_hResourceContext,iChannel,iBand);
	ReleaseMutex(m_hResourceContext);
	return bRet?PHONE_SUCCESS:PHONE_CONNECT_FAIL;


}
int CQualPhone::FTM_GSM_BER_Handover(unsigned short iChannel, unsigned char iBand, unsigned char iTSC, unsigned char iSlot, unsigned char iMode, unsigned char iPowerLevel, unsigned char iLoopbackType,int iQueryValidTimes,int iFreqMode)
{
	int iRetryTimes=iQueryValidTimes;
	bool bRet;
	CString strMsg;
	
	if (iFreqMode==0)
	{
		strMsg.Format("QLIB_FTM_GSM_BER_Handover(iChannel=%d,iBand=%d,iTSC=%d,iSlot=%d,iMode=%d,iPowerLevel=%d,iLoopbackType=%d)",iChannel, iBand, iTSC, iSlot, iMode, iPowerLevel, iLoopbackType); 
		LogPhoneStartCommand(strMsg);
		bRet=QLIB_FTM_GSM_BER_Handover_NoLoopbackConfig(m_hResourceContext,iChannel,iBand,iTSC,iSlot,iMode,iPowerLevel);

		//bRet=QLIB_FTM_GSM_BER_Handover(m_hResourceContext, iChannel, iBand, iTSC, iSlot, iMode, iPowerLevel,iLoopbackType);
		ReleaseMutex(m_hResourceContext);
		if(!bRet)
		{
			LogPhoneStopCommand(_T("QLIB_FTM_GSM_BER_Handover():Fail"));
			return PHONE_CONNECT_FAIL;
		}

		LogPhoneStartCommand(_T(""));
		do{
			bRet=QLIB_FTM_GSM_BER_IsTrafficValid(m_hResourceContext);

			if(bRet)
			{
				LogPhoneStopCommand(_T("QLIB_FTM_GSM_BER_IsTrafficValid() = VALID"));
				break;
			}
			else
			{
				LogPhoneStopCommand(_T("QLIB_FTM_GSM_BER_IsTrafficValid() = INVALID"));
			}
			Sleep(100);
		}while(--iRetryTimes>0);
	}
	else if (iFreqMode==1)
	{
		strMsg.Format("QLIB_FTM_EGPRS_BER_Release_All_TBF");
		LogPhoneStartCommand(strMsg);
		bRet=QLIB_FTM_EGPRS_BER_Release_All_TBF(m_hResourceContext);
		if (!bRet)
		{
			LogPhoneStopCommand(_T("QLIB_FTM_EGPRS_BER_Release_All_TBF():Fail"));
			return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_FTM_EGPRS_BER_Configure_DL_TBF()");
		LogPhoneStartCommand(strMsg);
		bRet=QLIB_FTM_EGPRS_BER_Configure_DL_TBF(m_hResourceContext,0,1,iChannel,iBand,1,3,1,4);
		if (!bRet)
		{
			LogPhoneStopCommand(_T("QLIB_FTM_EGPRS_BER_Release_All_TBF():Fail"));
			return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_FTM_EGPRS_BER_Configure_UL_TBF()");
		LogPhoneStartCommand(strMsg);
		bRet=QLIB_FTM_EGPRS_BER_Configure_UL_TBF(m_hResourceContext,0,0,iPowerLevel,1,3,1,4);
		if (!bRet)
		{
			LogPhoneStopCommand(_T("QLIB_FTM_EGPRS_BER_Release_All_TBF():Fail"));
			return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_FTM_EGPRS_BER_Establish_SRB_LOOPBACK()");
		LogPhoneStartCommand(strMsg);
		bRet=QLIB_FTM_EGPRS_BER_Establish_SRB_LOOPBACK(m_hResourceContext);
		if (!bRet)
		{
			LogPhoneStopCommand(_T("QLIB_FTM_EGPRS_BER_Establish_SRB_LOOPBACK():Fail"));
			return ERR_QLIB_FUNCTION_FAILED;
		}
	}
	else
	{
		return PHONE_CONNECT_FAIL;
	}

	Sleep(500);

	if(!bRet)
		return PHONE_CONNECT_FAIL;
	
	return PHONE_SUCCESS;	
}
int  CQualPhone::WriteEFS(int iTimout)
{
   CString strMsg;
   int iRetrytimes=3;

   if(m_iIsEFS)
   {
	   unsigned char uiStatus;
	   unsigned char * szPathFile=reinterpret_cast<unsigned char *>("/");
	   do 
	   {
		   strMsg.Format("QLIB_EFS2_SyncWithWait: timeout=%d",iTimout); 

		   bool bRet= QLIB_EFS2_SyncWithWait(m_hResourceContext,szPathFile,iTimout,&uiStatus); 

		   LogPhoneStartCommand(strMsg);
		   ReleaseMutex(m_hResourceContext);
		   strMsg.Format("QLIB_EFS2_SyncWithWait: status=%d",uiStatus);

		   LogPhoneStopCommand(strMsg);

		   if(bRet && uiStatus==0)
			   return PHONE_SUCCESS;
	   } while (--iRetrytimes>=0);
	   return ERR_QLIB_FUNCTION_FAILED;
   }
   else
   {
	   strMsg.Format("Not Write EFS");
	    LogPhoneStopCommand(strMsg);
		return PHONE_SUCCESS;

   }


}
int CQualPhone::FTM_GET_RX_AGC(unsigned short * piRX_AGC )
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_GET_RX_AGC:") ;
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_GET_RX_AGC(m_hResourceContext,piRX_AGC);

	strMsg.Format("QLIB_FTM_GET_RX_AGC: AGCValue=%d",*piRX_AGC);
	LogPhoneStopCommand(strMsg)

		if(bRet)
			return PHONE_SUCCESS;
		else
			return ERR_QLIB_FUNCTION_FAILED;  

}
int CQualPhone::FTM_GET_LNA_OFFSET(unsigned short iLNAindex ,short iExpectedRX_AGC,short* piLNAoffsetValue)
{
   CString strMsg;
  
   strMsg.Format("QLIB_FTM_GET_LNA_OFFSET: LNAindex=%d,ExpectedRX_AGC=%d",iLNAindex,iExpectedRX_AGC) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_GET_LNA_OFFSET(m_hResourceContext,iLNAindex,iExpectedRX_AGC,piLNAoffsetValue);

  strMsg.Format("QLIB_FTM_GET_LNA_OFFSET: LNAoffsetValue=%d",*piLNAoffsetValue);
  LogPhoneStopCommand(strMsg)

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;   
}
int CQualPhone::FTM_GET_DVGA_OFFSET(short iExpectedRX_AGC, short* piDVGAoffset)
{
    CString strMsg;
  
   strMsg.Format("QLIB_FTM_GET_DVGA_OFFSET: iExpectedRX_AGC=%d",iExpectedRX_AGC) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_GET_DVGA_OFFSET(m_hResourceContext,iExpectedRX_AGC,piDVGAoffset);

  strMsg.Format("QLIB_FTM_GET_DVGA_OFFSET: VGAOffset=%d",*piDVGAoffset);
  LogPhoneStopCommand(strMsg)

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;   
   
}
int CQualPhone::RFCAL_Complete_TxRxCal(unsigned short iNvModeId, void* aFTM_Request, void* aFTM_Response, void* aTx_NV_Structure, unsigned short numRecords, void* aTx_Lin_Cal_NV_Info, unsigned short* numLin, unsigned short iNVPath, unsigned char bCachedByNVManager )
{

	CString strMsg;

	strMsg.Format("QLIB_RFCAL_Complete_TxRxCal:bCachedByNVManagere=%d",bCachedByNVManager) ;
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_RFCAL_Complete_TxRxCal(m_hResourceContext,iNvModeId,aFTM_Request,aFTM_Response,aTx_NV_Structure,numRecords,aTx_Lin_Cal_NV_Info,numLin,iNVPath,bCachedByNVManager);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED; 
}

int CQualPhone::RFCAL_CDMA_RxCal_Results( unsigned short iNV_Mode_ID,
										  unsigned char iIsIntelliceiver,
										  double dDVGAOffsetScalingFactor,
										  void* aRX_Measured,
										  void* aRX_MeasuredChannels,
										  void* aRX_NV_Channels,
										  void* aRX_DVGA_LNA_Cal_NV,
										  unsigned char bWriteNVChList,
										  unsigned char bCachedByNVManager)
{

   CString strMsg;
  
	 strMsg.Format("QLIB_RFCAL_CDMA_RxCal_Results:bCachedByNVManagere=%d",bCachedByNVManager) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_RFCAL_CDMA_RxCal_Results(m_hResourceContext,iNV_Mode_ID,iIsIntelliceiver,dDVGAOffsetScalingFactor,aRX_Measured,aRX_MeasuredChannels,aRX_NV_Channels,aRX_DVGA_LNA_Cal_NV,bWriteNVChList,bCachedByNVManager);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;  

}
int CQualPhone::RFCAL_CDMA_Tx_LimVsFreq_Results(unsigned short iNvModeId,
																	double dDesiredMaxPower,
																	void* aTx_LimVsFreqMeasured,
																	void* aTx_MeasuredChannels,
																	void* aTx_NV_Channels,
																	void* aTx_LimVsFreq_NV_Result,
																	unsigned char bCachedByNVManager)
{
    CString strMsg;
  
	 strMsg.Format("QLIB_RFCAL_CDMA_Tx_LimVsFreq_Results:bCachedByNVManagere=%d",bCachedByNVManager) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_RFCAL_CDMA_Tx_LimVsFreq_Results(m_hResourceContext,iNvModeId,dDesiredMaxPower,aTx_LimVsFreqMeasured,aTx_MeasuredChannels,aTx_NV_Channels,aTx_LimVsFreq_NV_Result,bCachedByNVManager);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;  
}
int CQualPhone::RFCAL_CDMA_TxLinCal_BetaScaling_Results(unsigned short iNvModeId,
																		void* aTx_Measured,
																		void* aTx_Result,
																		unsigned char bCachedByNVManager)
{
  CString strMsg;
  
	 strMsg.Format("QLIB_RFCAL_CDMA_TxLinCal_BetaScaling_Results:bCachedByNVManagere=%d",bCachedByNVManager) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_RFCAL_CDMA_TxLinCal_BetaScaling_Results(m_hResourceContext,iNvModeId,aTx_Measured,aTx_Result,bCachedByNVManager);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;  
}
int CQualPhone::FTM_TX_RX_FREQ_CAL_SWEEP(void* pFTM_Tx_Rx_Freq_Cal_Sweep_Request_Response)
{
     CString strMsg;
  
	 strMsg.Format("QLIB_FTM_TX_RX_FREQ_CAL_SWEEP") ;
     LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_TX_RX_FREQ_CAL_SWEEP(m_hResourceContext,pFTM_Tx_Rx_Freq_Cal_Sweep_Request_Response);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;    
}
int CQualPhone::RFCAL_CDMA_Tx_LinVsFreq_Results(unsigned short iNvModId,
																	void* aTx_Measured_Power,
																	void* aTx_MeasuredChannels,
																	void* aTx_NV_Channels,
																	int	  iNV_Resolution_Type,
																	int   iNV_Tx_Comp_Type,
																	void* aTx_LinVsFreq_NV_Result,
																	unsigned char bWriteNVChList,
																	unsigned char bCachedByNVManager)
{
     CString strMsg;
  
	 strMsg.Format("QLIB_RFCAL_CDMA_Tx_LinVsFreq_Results:bCachedByNVManagere=%d",bCachedByNVManager) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_RFCAL_CDMA_Tx_LinVsFreq_Results(m_hResourceContext,iNvModId,aTx_Measured_Power,aTx_MeasuredChannels,aTx_NV_Channels,iNV_Resolution_Type,iNV_Tx_Comp_Type,aTx_LinVsFreq_NV_Result,bWriteNVChList,bCachedByNVManager);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;  
}
int CQualPhone::FTM_GET_ADC_VAL(unsigned short iADC_type, unsigned short* piADC_value)
{
   CString strMsg;
  
	 strMsg.Format("QLIB_FTM_GET_ADC_VAL:ADCType=%d",iADC_type) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_GET_ADC_VAL(m_hResourceContext,iADC_type,piADC_value);
  strMsg.Format("QLIB_FTM_GET_ADC_VAL : ADCValue=%d",*piADC_value);
  LogPhoneStopCommand(strMsg)

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;   
}
int CQualPhone::FTM_SET_SECONDARY_CHAIN(unsigned short iMode)
{
   CString strMsg;
  
	 strMsg.Format("QLIB_FTM_SET_SECONDARY_CHAIN: iMode=%d",iMode) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_SECONDARY_CHAIN(m_hResourceContext,iMode);


  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;   
}

int CQualPhone::FTM_SET_MULTI_CHAN(unsigned short iChannel0,unsigned short iChannel1)
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_SET_MULTI_CHAN: iChannel0=%d,iChannel1=%d",iChannel0,iChannel1) ;
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_SET_MULTI_CHAN(m_hResourceContext,iChannel0,iChannel1);


	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED; 


}

int CQualPhone::GET_RX_OFFSET_MULTI_CHAN(unsigned short iSecondaryMode,int iMode_ID,int iRxAction,short iExpectedAGC,short * piRxoffsetValue)
{	
	if (PHONE_SUCCESS!=FTM_SET_SECONDARY_CHAIN(iSecondaryMode))
		return ERR_QLIB_FUNCTION_FAILED; 

	if (PHONE_SUCCESS!=FTM_SET_MODE_ID(iMode_ID))
		return ERR_QLIB_FUNCTION_FAILED; 

	if (PHONE_SUCCESS!=FTM_SET_MODE_ID(iMode_ID))
		return ERR_QLIB_FUNCTION_FAILED; 

	if (0==iRxAction)
	{
		if (PHONE_SUCCESS!=FTM_GET_DVGA_OFFSET(iExpectedAGC,piRxoffsetValue))
			return ERR_QLIB_FUNCTION_FAILED; 
	}
	else
	{
		if (PHONE_SUCCESS!=FTM_GET_LNA_OFFSET(iRxAction,iExpectedAGC,piRxoffsetValue))
			return ERR_QLIB_FUNCTION_FAILED; 
	}

	return PHONE_SUCCESS;



	
}
int CQualPhone::RFCAL_WCDMA_MultiCarrier_RxCal_Results(unsigned int iBand, unsigned short iNV_Mode_ID, unsigned char iIsIntelliceiver, double dDVGAOffsetScalingFactor, void * aRX_Measured, void * aRX_MeasuredChannels, void * aRX_NV_Channels, void * aRX_DVGA_LNA_Cal_NV, unsigned char bWriteNVChList, unsigned char bCachedByNVManager )
{
	CString strMsg;

	strMsg.Format("QLIB_RFCAL_WCDMA_MultiCarrier_RxCal_Results") ;
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_RFCAL_WCDMA_MultiCarrier_RxCal_Results(m_hResourceContext,iBand,iNV_Mode_ID,iIsIntelliceiver,dDVGAOffsetScalingFactor,aRX_Measured,aRX_MeasuredChannels,aRX_NV_Channels,aRX_DVGA_LNA_Cal_NV,bWriteNVChList,bCachedByNVManager);
	
	LogPhoneStopCommand(strMsg)

		if(bRet)
			return PHONE_SUCCESS;
		else
			return ERR_QLIB_FUNCTION_FAILED; 

}
int CQualPhone::FTM_GET_HDET_FROM_TX_SWEEP_CAL(unsigned short iIndex, unsigned short* piHDETvalue)
{
    CString strMsg;
  
   strMsg.Format("QLIB_FTM_GET_HDET_FROM_TX_SWEEP_CAL: index=%d",iIndex) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_GET_HDET_FROM_TX_SWEEP_CAL(m_hResourceContext,iIndex,piHDETvalue);
  strMsg.Format("QLIB_FTM_GET_HDET_FROM_TX_SWEEP_CAL: HDETValue=%d",*piHDETvalue);
  LogPhoneStopCommand(strMsg)

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;   
}
int CQualPhone::FTM_TX_SWEEP_CAL(unsigned char bOnOff)
{
     CString strMsg;
  
	 strMsg.Format("QLIB_FTM_TX_SWEEP_CAL: bOnOff=%d",bOnOff) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_TX_SWEEP_CAL(m_hResourceContext,bOnOff);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;   
}
int CQualPhone::FTM_SET_TX_SWEEP_STEP_SIZE(unsigned char iStepSize)
{
   CString strMsg;
  
	 strMsg.Format("QLIB_FTM_SET_TX_SWEEP_STEP_SIZE: size=%d",iStepSize) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_TX_SWEEP_STEP_SIZE(m_hResourceContext,iStepSize);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;   
}
int CQualPhone::FTM_CONFIGURE_TX_SWEEP_CAL(unsigned short iTimeInterval, unsigned short iNumofHDETReadingsPerStep)
{
    CString strMsg;
  
	 strMsg.Format("QLIB_FTM_CONFIGURE_TX_SWEEP_CAL: TimeInterval=%d  HDETReadingPerStep=%d",iTimeInterval,iNumofHDETReadingsPerStep) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_CONFIGURE_TX_SWEEP_CAL(m_hResourceContext,iTimeInterval,iNumofHDETReadingsPerStep);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}

int CQualPhone::FTM_CDMA_CW_WAVEFORM(unsigned char bSelectCW)
{
   CString strMsg;
  
	 strMsg.Format("QLIB_FTM_CDMA_CW_WAVEFORM: bSelectCW=%d",bSelectCW) ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_CDMA_CW_WAVEFORM(m_hResourceContext,bSelectCW);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::FTM_SET_CALIBRATION_STATE(bool bActivate)
{
     CString strMsg;
    if(bActivate)
	 strMsg.Format("QLIB_FTM_SET_CALIBRATION_STATE: Activate=true");
	else
	 strMsg.Format("QLIB_FTM_SET_CALIBRATION_STATE: Activate=false") ;
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_CALIBRATION_STATE(m_hResourceContext,(unsigned char)bActivate);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SET_PDM(int iPDMType,int iPDMValue)
{
   CString strMsg;

   strMsg.Format("QLIB_FTM_SET_PDM : PDM Type=%d, PDM Value=%d",iPDMType,iPDMValue);
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_PDM(m_hResourceContext,(unsigned short)iPDMType,(unsigned short)iPDMValue);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SET_RGI(unsigned short iTxGainIndex)
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_SET_TX_GAIN_INDEX : RGI =%d",iTxGainIndex);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_SET_TX_GAIN_INDEX(m_hResourceContext,iTxGainIndex);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SET_PA_RANGE(int iPARange)
{
    CString strMsg;

   strMsg.Format("QLIB_FTM_SET_PA_RANGE : PA Range=%d",iPARange);
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_PA_RANGE(m_hResourceContext,(unsigned short)iPARange);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SET_PA_STATE(int iState)
{
	CString strMsg;
	unsigned short iErrorCode=1;
	strMsg.Format("QLIB_FTM_SET_PA_STATE : PA State=%d",iState);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_SET_PA_STATE(m_hResourceContext,(unsigned char)iState,&iErrorCode);

	if((bRet)&&(0==iErrorCode))
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;

}
int CQualPhone::FTM_SET_TX_ON(bool bIsOn)
{
   CString strMsg;

   if(bIsOn)
   {
	   strMsg.Format("QLIB_FTM_SET_TX_ON");
	   LogPhoneStartCommand(strMsg);
		bool bRet=QLIB_FTM_SET_TX_ON(m_hResourceContext);

	  if(bRet)
		return PHONE_SUCCESS;
	  else
		 return ERR_QLIB_FUNCTION_FAILED;
	   }
   else
   {
       strMsg.Format("QLIB_FTM_SET_TX_OFF");
	   LogPhoneStartCommand(strMsg);
		bool bRet=QLIB_FTM_SET_TX_OFF(m_hResourceContext);

	  if(bRet)
		return PHONE_SUCCESS;
	  else
		 return ERR_QLIB_FUNCTION_FAILED;
	 

   }
  
 
}
int CQualPhone::FTM_SET_LNA_RANGE(int iLNARange)
{
   CString strMsg;

   strMsg.Format("QLIB_FTM_SET_LNA_RANGE : LNA Range=%d",iLNARange);
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_LNA_RANGE(m_hResourceContext,(unsigned char)iLNARange);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SET_CHAN(unsigned short uiChannel)
{
    CString strMsg;

   strMsg.Format("QLIB_FTM_SET_CHAN : Channel=%d",uiChannel);
   LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_CHAN(m_hResourceContext,uiChannel);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SET_MODE(short iNewMode)
{
   CString strMsg;

  strMsg.Format("QLIB_FTM_SET_MODE : Mode=%d",iNewMode);
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_MODE(m_hResourceContext,iNewMode);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SET_BANDWIDTH(short iTxChanBW,short iRxChanBW)
{
	CString strMsg;
	strMsg.Format("FTM_SET_BANDWIDTH TxChanBW : TxChanBW=%d",iTxChanBW);
	LogPhoneStartCommand(strMsg);
	bool bRet1=QLIB_FTM_LTE_SET_TX_BANDWIDTH(m_hResourceContext,iTxChanBW);
	if(bRet1==0)
		return ERR_QLIB_FUNCTION_FAILED;

	strMsg.Format("FTM_SET_BANDWIDTH RxChanBW : RxChanBW=%d",iRxChanBW);
	LogPhoneStartCommand(strMsg);
	bool bRet2=QLIB_FTM_LTE_SET_RX_BANDWIDTH(m_hResourceContext,iRxChanBW);
	if(bRet2)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}

int CQualPhone::FTM_DO_DC_CAL()
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_DO_DC_CAL()");
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_DO_DC_CAL(m_hResourceContext);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}

int CQualPhone::FTM_SET_TX_WAVEFORM(unsigned char iWaveformType , unsigned char iWaveformAttrib)
{

   CString strMsg;

  strMsg.Format("QLIB_FTM_SET_TX_WAVEFORM : iWaveformType=%d iWaveformAttrib=%d",iWaveformType,iWaveformAttrib);
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_TX_WAVEFORM(m_hResourceContext,iWaveformType,iWaveformAttrib);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::RFCAL_Rx_Intellieceiver_Cal_Results(unsigned short iNvModeId,void* aIntelliceiverValue,void* aIntelliceiver_NV,unsigned char bCachedByNVManager)

{
    CString strMsg;

  strMsg.Format("QLIB_RFCAL_Rx_Intelliceiver_Cal_Results : iNvModeId=%d ",iNvModeId);
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_RFCAL_Rx_Intelliceiver_Cal_Results(m_hResourceContext,iNvModeId,aIntelliceiverValue,aIntelliceiver_NV,bCachedByNVManager);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_CDMA_API2_CALIBRATE_INTELLICEIVER(unsigned char iPath,short iInputPower,unsigned char* iSizeOfBLOB,unsigned char* iCalibrationBLOC)
{
  CString strMsg;

  strMsg.Format("QLIB_FTM_CDMA_API2_CALIBRATE_INTELLICEIVER : iPath=%d  iInputPower=%d",iPath,iInputPower);
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_CDMA_API2_CALIBRATE_INTELLICEIVER(m_hResourceContext,iPath,iInputPower,iSizeOfBLOB,iCalibrationBLOC);
  strMsg.Format("QLIB_FTM_CDMA_API2_CALIBRATE_INTELLICEIVER:iSizeOfBLOB=%d CalibrationBLOC=%s",*iSizeOfBLOB,iCalibrationBLOC);
  LogPhoneStopCommand(strMsg)


  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;  
}
int CQualPhone::FTM_CDMA_API2_CALIBRATE_LNA(unsigned char	iPath,short  iInputPower,unsigned char	iLNAstep,unsigned char*	iCount,unsigned short* iLNAarray )
{
	CString strMsg;

  strMsg.Format("QLIB_FTM_CDMA_API2_CALIBRATE_LNA : iPath=%d  iInputPower=%d iLNAstep=%d",iPath,iInputPower,iLNAstep);
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_CDMA_API2_CALIBRATE_LNA(m_hResourceContext,iPath,iInputPower,iLNAstep,iCount,iLNAarray);
  strMsg.Format("QLIB_FTM_CDMA_API2_CALIBRATE_LNA:Count=%d",*iCount);
  LogPhoneStopCommand(strMsg)
  for(int i=0;i<*iCount;i++)
  {
     strMsg.Format("QLIB_FTM_CDMA_API2_CALIBRATE_LNA: LNAArray[%d]=%d",i,iLNAarray[i]);
      LogPhoneStopCommand(strMsg)
  }


  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;  
}
int CQualPhone::FTM_CDMA_API2_CALIBRATE_DVGA(unsigned char iPath,short iInputPower,unsigned char* iCoun,unsigned short* iDVGAarray)
{
   CString strMsg;

  strMsg.Format("QLIB_FTM_CDMA_API2_CALIBRATE_DVGA : iPath=%d  iInputPower=%d",iPath,iInputPower);
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_CDMA_API2_CALIBRATE_DVGA(m_hResourceContext,iPath,iInputPower,iCoun,iDVGAarray);
  strMsg.Format("QLIB_FTM_CDMA_API2_CALIBRATE_DVGA:Count=%d",*iCoun);
  LogPhoneStopCommand(strMsg)
  for(int i=0;i<*iCoun;i++)
  {
     strMsg.Format("QLIB_FTM_CDMA_API2_CALIBRATE_DVGA: DVGAArray[%d]=%d",i,iDVGAarray[i]);
      LogPhoneStopCommand(strMsg)
  }


  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;  
}
int CQualPhone::FTM_SET_RF_POWER_MODE(int iMode)
{
   CString strMsg;

  strMsg.Format("QLIB_FTM_SET_RF_POWER_MODE : Mode=%d",iMode);
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_RF_POWER_MODE(m_hResourceContext,iMode);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
 
}
int CQualPhone::FTM_SET_MODE_ID(int iMODE_ID)
{
  CString strMsg;

  strMsg.Format("QLIB_FTM_SET_MODE_ID : ModeID=%d",iMODE_ID);
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_SET_MODE_ID(m_hResourceContext,iMODE_ID);

  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;


}
int CQualPhone::RFCAL_NV_Manager_WriteToPhone(void *pWriteToPhoneStatus,bool bIsShowNVStatus)
{
    CString strMsg;

	 strMsg.Format("QLIB_RFCAL_NV_Manager_WriteToPhone");
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_RFCAL_NV_Manager_WriteToPhone(m_hResourceContext,pWriteToPhoneStatus);
       QMSL_RFCal_WriteToPhone_Status   QMSL_RFCal_WriteToPhone;
       QMSL_RFCal_WriteToPhone=*((QMSL_RFCal_WriteToPhone_Status*)pWriteToPhoneStatus);
      if(bIsShowNVStatus)
	  {
		  strMsg.Format("QLIB_RFCAL_NV_Manager_WriteToPhone : NV Status below :");
           LogPhoneStopCommand(strMsg);
		  for(int i=0;i<QMSL_RFCal_WriteToPhone.iNumOfItemsInCache;i++)
		  {
			  strMsg.Format("NVID=%d Status=%d",QMSL_RFCal_WriteToPhone.aNVItemStatus[i].iNVenum,QMSL_RFCal_WriteToPhone.aNVItemStatus[i].iStatus);
		       LogPhoneStopCommand(strMsg);
		  }
     
	  }

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::RFCAL_Internal_Thermistor_Calibration_Results(void *pInt_Therm_Cal_Meas,void *pInt_Therm_Cal_NV,unsigned char bCachedByNVManager)
{
    CString strMsg;

	 strMsg.Format("QLIB_RFCAL_Internal_Thermistor_Calibration_Results");
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_RFCAL_Internal_Thermistor_Calibration_Results(m_hResourceContext,pInt_Therm_Cal_Meas,pInt_Therm_Cal_NV,bCachedByNVManager);
      
	  int *piMaxNV;
	  int *piMinNV;
	  piMaxNV=(int*)(((QMSL_Internal_Thermistor_Cal_NV_struct*)pInt_Therm_Cal_NV)->oNV_Therm_Max.aNVItemData);
	  piMinNV=(int*)(((QMSL_Internal_Thermistor_Cal_NV_struct*)pInt_Therm_Cal_NV)->oNV_Therm_Min.aNVItemData);

	  strMsg.Format("QLIB_RFCAL_Internal_Thermistor_Calibration_Results   : Max NVValue=%d ,Min NVValue=%d",*piMaxNV,*piMinNV);
      LogPhoneStopCommand(strMsg);

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::RFCAL_GSM_CAL_ARFCN(	unsigned short iNvModeId,
													unsigned short* aGSM_Cal_ARFCN_List,
													unsigned char iNumOfChannel,
													void * pGSM_Cal_ARFCN_NV,
													unsigned char bCachedByNVManager)
{

     CString strMsg;

	 strMsg.Format("QLIB_RFCAL_GSM_CAL_ARFCN : bCachedByNVManager=%d",bCachedByNVManager);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_RFCAL_GSM_CAL_ARFCN(m_hResourceContext,iNvModeId,aGSM_Cal_ARFCN_List,iNumOfChannel,pGSM_Cal_ARFCN_NV,bCachedByNVManager);
	 
   
	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::RFCAL_GSM_Rx_Gain_Range_Results(	unsigned short iNvModeId,
													void* aGSM_Rx_Gain_Range_Result,
													void* aGSM_Rx_Gain_Range_NV,
													unsigned char bCachedByNVManager)
{
	   CString strMsg;

	 strMsg.Format("QLIB_RFCAL_GSM_Rx_Gain_Range_Results : bCachedByNVManager=%d",bCachedByNVManager);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_RFCAL_GSM_Rx_Gain_Range_Results(m_hResourceContext,iNvModeId,aGSM_Rx_Gain_Range_Result,aGSM_Rx_Gain_Range_NV,bCachedByNVManager);
	 
   
	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
   
}
int CQualPhone::RFCAL_GSM_RX_CALIBRATION_GENERATE_NV(	unsigned short iNvModeId,
												void* aGSM_Rx_Calibration_Params_n_Meas,
												void* aGSM_Rx_Gain_Range_NV,
												unsigned char bCachedByNVManager)
{
	CString strMsg;

	strMsg.Format("QLIB_GSM_RX_CALIBRATION_GENERATE_NV : bCachedByNVManager=%d",bCachedByNVManager);
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_GSM_RX_CALIBRATION_GENERATE_NV(m_hResourceContext,iNvModeId,aGSM_Rx_Calibration_Params_n_Meas,aGSM_Rx_Gain_Range_NV,bCachedByNVManager);
	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED; 

}
int CQualPhone::FTM_RX_GAIN_RANGE_CAL(unsigned char iRxRangeBitMask,
			unsigned char iNumAverages,
			unsigned char bToggleRx,
			unsigned long aiRSSI_Result[8])
{
     CString strMsg;

	 strMsg.Format("QLIB_FTM_RX_GAIN_RANGE_CAL : iRxRangeBitMask=%d,iNumAverages=%d,bToggleRx=%d",iRxRangeBitMask,iNumAverages,bToggleRx);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_RX_GAIN_RANGE_CAL(m_hResourceContext,iRxRangeBitMask,iNumAverages,bToggleRx,aiRSSI_Result);
	 
   
	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 

}
int CQualPhone::FTM_SET_RX_BURST(unsigned char iSlotNum, short iRxFunction)
{
    CString strMsg;

	 strMsg.Format("QLIB_FTM_SET_RX_BURST : iSlotNum=%d,iRxFunction=%d",iSlotNum,iRxFunction);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_SET_RX_BURST(m_hResourceContext,iSlotNum,iRxFunction);
	 
   
	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::FTM_GSM_DO_TX_KV_CAL(	unsigned short iLowChan,
										unsigned short iHiChan,
										unsigned short *piLowChanKvco,
										unsigned short *piHiChanKvco)
{
     CString strMsg;

	 strMsg.Format("QLIB_FTM_GSM_DO_TX_KV_CAL : iLowChan=%d,iHiChan=%d",iLowChan,iHiChan);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_GSM_DO_TX_KV_CAL(m_hResourceContext,iLowChan,iHiChan,piLowChanKvco,piHiChanKvco);
	   strMsg.Format("QLIB_FTM_GSM_DO_TX_KV_CAL : LowChanKvco=%d,HiChanKvco",*piLowChanKvco,*piHiChanKvco);
     LogPhoneStopCommand(strMsg);
      
    

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::FTM_GSM_DO_TX_KV_CAL_V2( unsigned short iNumBands, unsigned short iNumTxCycles, unsigned short iNumMeas, unsigned short *piRfModeList, unsigned short *piKvChanCode )
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_GSM_DO_TX_KV_CAL_V2 iNumBands=%d,iNumTxCycles=%d,iNumMeas=%d",iNumBands,iNumTxCycles,iNumMeas);
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_FTM_GSM_DO_TX_KV_CAL_V2(m_hResourceContext,iNumBands,iNumTxCycles,iNumMeas,piRfModeList,piKvChanCode);
	for (int i=0;i<2*iNumMeas;i++)
	{
		strMsg.Format(" LowChanKvco=%d,HiChanKvco=%d",piKvChanCode[2*i],piKvChanCode[2*i+1]);
		LogPhoneStopCommand(strMsg);

	}
	

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::RFCAL_GSM_Carrier_Suppression(unsigned short iNvModeId,short iIdc,short iQdc, void *pGSM_Carrier_Suppression_NV,unsigned char bCatchedByNvManager)
{
	CString strMsg;

	 strMsg.Format("QLIB_RFCAL_GSM_CARRIER_SUPRRESSION : bCachedByNVManager=%d",bCatchedByNvManager);
     LogPhoneStartCommand(strMsg);
	bool bRet = QLIB_RFCAL_GSM_CARRIER_SUPRRESSION(m_hResourceContext,iNvModeId,iIdc,iQdc,pGSM_Carrier_Suppression_NV,bCatchedByNvManager);
 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::RFCAL_GSM_Tx_Polar_Cal_Results(unsigned short iNvModeId,
													void* aGSM_Polar_Cal,
													void *aGSM_Polar_Cal_NV,
													unsigned char bCachedByNVManager)
{	 CString strMsg;

	 strMsg.Format("FTM_GSM_POLAR_TX_SWEEP_CAL");
     LogPhoneStartCommand(strMsg);
	
	 bool bRet=QLIB_RFCAL_GSM_Tx_Polar_Cal_Results(m_hResourceContext,iNvModeId,aGSM_Polar_Cal,aGSM_Polar_Cal_NV,bCachedByNVManager);
	 if(bRet)
		return PHONE_SUCCESS;
	  else
		 return ERR_QLIB_FUNCTION_FAILED; 
	
}
int CQualPhone::RFCAL_GSM_Tx_Polar_ProcessTxSweep( void *  aGSM_Polar_Cal_Measurement,  
  void *  aGSM_Polar_Cal_Processed 
 )  
{ CString strMsg;

	 strMsg.Format("QLIB_RFCAL_GSM_Tx_Polar_ProcessTxSweep");
     LogPhoneStartCommand(strMsg);
	
	 bool bRet=QLIB_RFCAL_GSM_Tx_Polar_ProcessTxSweep (m_hResourceContext,aGSM_Polar_Cal_Measurement,aGSM_Polar_Cal_Processed);
	  if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::FTM_GSM_POLAR_TX_SWEEP_CAL(unsigned long  numDac,  
  unsigned long *  dacList,  
  unsigned long *  dacDuration 
 )  
{
	 CString strMsg;

	 strMsg.Format("FTM_GSM_POLAR_TX_SWEEP_CAL");
     LogPhoneStartCommand(strMsg);
	
	 bool bRet=QLIB_FTM_GSM_POLAR_TX_SWEEP_CAL  (m_hResourceContext,  
															  numDac,  
															  dacList,  
															  dacDuration 
															  );

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 

}

int CQualPhone::RFCAL_GSM_Tx_DA_Cal_Results(unsigned short iNvModeId,
													void* aGSM_DA_Cal,
													void *aGSM_DA_Cal_NV,
													unsigned char bCachedByNVManager)
{
    CString strMsg;

	 strMsg.Format("QLIB_RFCAL_GSM_Tx_DA_Cal_Results : bCachedByNVManager=%d",bCachedByNVManager);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_RFCAL_GSM_Tx_DA_Cal_Results(m_hResourceContext,iNvModeId,aGSM_DA_Cal,aGSM_DA_Cal_NV,bCachedByNVManager);
      
    

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
 int CQualPhone::RFCAL_GSM_Tx_Linear_Process_PreDist_Cal_Results(	unsigned short iNvModeId,
													void* aGSM_PreDist_Cal,
													void *aGSM_PreDist_Cal_NV,
													unsigned char bCachedByNVManager)
 {

      CString strMsg;

	   strMsg.Format("QLIB_RFCAL_GSM_Tx_Linear_Process_PreDist_Cal_Results");
     LogPhoneStartCommand(strMsg);

        bool bRet=QLIB_RFCAL_GSM_Tx_Linear_Process_PreDist_Cal_Results(m_hResourceContext,iNvModeId,aGSM_PreDist_Cal,aGSM_PreDist_Cal_NV,bCachedByNVManager);
    	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 

 }
 int CQualPhone::RFCAL_GSM_Tx_Linear_Process_Swapped_PreDist_Cal_Results(unsigned short iNvModeId, void* aGSM_PreDist_Cal, void *aGSM_PreDist_Cal_NV, unsigned char bCachedByNVManager)
 {
	 CString strMsg;

	 strMsg.Format("RFCAL_GSM_Tx_Linear_Process_Swapped_PreDist_Cal_Results");
	 LogPhoneStartCommand(strMsg);

	 bool bRet=QLIB_RFCAL_GSM_Tx_Linear_Process_Swapped_PreDist_Cal_Results(m_hResourceContext,iNvModeId,aGSM_PreDist_Cal,aGSM_PreDist_Cal_NV,bCachedByNVManager);
	 if(bRet)
		 return PHONE_SUCCESS;
	 else
		 return ERR_QLIB_FUNCTION_FAILED; 

 }
 int CQualPhone::RFCal_GSM_Tx_DA_Cal_IQ_Predist_Cal_Generate_NV(unsigned short iNvModeId, unsigned char iChainId,void* aGSM_DA_Cal,void* aGSM_PreDist_Cal,void* aGSM_Tx_Cx_Cal_NV,unsigned char bCachedByNVManager)
 {
	 CString strMsg;

	 strMsg.Format("RFCal_GSM_Tx_DA_Cal_IQ_Predist_Cal_Generate_NV");
	 LogPhoneStartCommand(strMsg);

	 bool bRet=QLIB_RFCal_GSM_Tx_DA_Cal_IQ_Predist_Cal_Generate_NV(	m_hResourceContext,iNvModeId,iChainId,aGSM_DA_Cal,aGSM_PreDist_Cal,aGSM_Tx_Cx_Cal_NV,bCachedByNVManager);
	 if(bRet)
		 return PHONE_SUCCESS;
	 else
		 return ERR_QLIB_FUNCTION_FAILED; 

 }
int CQualPhone::FTM_TX_CFG2_AMAM_SWEEP(unsigned long iPreDcDuration, unsigned long iEdgeDuration,unsigned long iCalRgi, unsigned long * piDigScale)
{
       CString strMsg;

	   strMsg.Format("QLIB_FTM_TX_CFG2_AMAM_SWEEP :iPreDcDuration=%d,iEdgeDuration=%d,iCalRgi=%d",iPreDcDuration,iEdgeDuration,iCalRgi);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_TX_CFG2_AMAM_SWEEP(m_hResourceContext,iPreDcDuration,iEdgeDuration,iCalRgi,piDigScale);

      
     strMsg.Format("QLIB_FTM_TX_CFG2_AMAM_SWEEP :DigScale=%d",*piDigScale);
     LogPhoneStopCommand(strMsg);
	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::FTM_TX_CFG2_AMAM_SWEEP_V2(unsigned long iDcDuration, unsigned long iEdgeDuration, unsigned long iCalRgi, unsigned long iWaveformType, unsigned long * piDigScale )
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_TX_CFG2_AMAM_SWEEP_V2 :iPreDcDuration=%d,iEdgeDuration=%d,iCalRgi=%d,iWaveformType=%d",iDcDuration,iEdgeDuration,iCalRgi,iWaveformType);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_TX_CFG2_AMAM_SWEEP_V2(m_hResourceContext,iDcDuration,iEdgeDuration,iCalRgi,iWaveformType,piDigScale);


	strMsg.Format("QLIB_FTM_TX_CFG2_AMAM_SWEEP_V2 :DigScale=%d",*piDigScale);
	LogPhoneStopCommand(strMsg);
	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED; 

}
int CQualPhone::FTM_SET_GSM_LINEAR_PA_RANGE(unsigned short iSlotNum,unsigned short iPaRange )
{
   CString strMsg;

   strMsg.Format("QLIB_FTM_SET_GSM_LINEAR_PA_RANGE:iSlotNum=%d,iPaRange=%d",iSlotNum,iPaRange);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_SET_GSM_LINEAR_PA_RANGE(m_hResourceContext,iSlotNum,iPaRange);

    

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
int CQualPhone::FTM_SET_TRANSMIT_BURS( unsigned char iSlotNum, short iDataSource, unsigned char iTSCindex,unsigned long iNumBursts, unsigned char bIsInfiniteDuration )
{
   CString strMsg;

   strMsg.Format("QLIB_FTM_SET_TRANSMIT_BURST :iSlotNum=%d,iDataSource=%d,iTSCindex=%d,iNumBursts=%d,bIsInfiniteDuration=%d",iSlotNum,iDataSource,iTSCindex,iNumBursts,bIsInfiniteDuration);
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_SET_TRANSMIT_BURST(m_hResourceContext,iSlotNum,iDataSource,iTSCindex,iNumBursts,bIsInfiniteDuration);

    

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED; 
}
 int CQualPhone::FTM_DA_CAL(	unsigned short iListSize,
				unsigned short*  aiSegLength,
				unsigned char *  aiRgi,
				unsigned char *  aiGsmMode,
				unsigned char *  aiPaRange)
 {
        CString strMsg;

	 strMsg.Format("QLIB_FTM_DA_CAL");
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_DA_CAL(m_hResourceContext,iListSize,aiSegLength,aiRgi,aiGsmMode,aiPaRange);

    

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
 }
int CQualPhone::FTM_GET_ENH_THERM(unsigned long* iThermValue )
{
     CString strMsg;

	 strMsg.Format("QLIB_FTM_GET_ENH_THERM");
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_GET_ENH_THERM(m_hResourceContext,iThermValue);


	  strMsg.Format("QLIB_FTM_GET_ENH_THERM   : Therm value=%d",iThermValue);
      LogPhoneStopCommand(strMsg);

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}

int CQualPhone::FTM_GET_THERM(unsigned char* iThermValue )
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_GET_THERM");
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_GET_THERM(m_hResourceContext,iThermValue);


	strMsg.Format("QLIB_FTM_GET_THERM   : Therm value=%d",iThermValue);
	LogPhoneStopCommand(strMsg);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}

int CQualPhone::FTM_DO_ENH_XO_FT_CURVE_CAL(void * pFTM_ENH_XO_Cal_Request, void *pFTM_XO_Cal_Response)
{
    CString strMsg;

	 strMsg.Format("QLIB_FTM_DO_ENH_XO_FT_CURVE_CAL");
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_DO_ENH_XO_FT_CURVE_CAL_V2(m_hResourceContext,pFTM_ENH_XO_Cal_Request,pFTM_XO_Cal_Response);


	  strMsg.Format("QLIB_FTM_DO_ENH_XO_FT_CURVE_CAL : response  status=%d",((FTM_XO_Cal_Response_v2*)pFTM_XO_Cal_Response)->state);
     LogPhoneStopCommand(strMsg);

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}

int CQualPhone::FTM_DO_ENH_XO_FT_COLLECT_SAMPLE(void * pFTM_ENH_XO_Cal_Request, void *pFTM_XO_Cal_Response)
{
     CString strMsg;

	 strMsg.Format("QLIB_FTM_DO_ENH_XO_FT_COLLECT_SAMPLE ");
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_DO_ENH_XO_FT_COLLECT_SAMPLE_V2(m_hResourceContext,pFTM_ENH_XO_Cal_Request,pFTM_XO_Cal_Response);


	  strMsg.Format("QLIB_FTM_DO_ENH_XO_FT_COLLECT_SAMPLE : response  status=%d",((FTM_XO_Cal_Response_v2*)pFTM_XO_Cal_Response)->state);
     LogPhoneStopCommand(strMsg);

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;
}
int  CQualPhone::FTM_DO_ENH_XO_DC_CAL(void * pFTM_ENH_XO_Cal_Request, void *pFTM_XO_Cal_Response)
{

     CString strMsg;

	 strMsg.Format("QLIB_FTM_DO_ENH_XO_DC_CAL ");
     LogPhoneStartCommand(strMsg);

      bool bRet=QLIB_FTM_DO_ENH_XO_DC_CAL_V2(m_hResourceContext,pFTM_ENH_XO_Cal_Request,pFTM_XO_Cal_Response);


	  strMsg.Format("QLIB_FTM_DO_ENH_XO_DC_CAL : response  status=%d",((FTM_XO_Cal_Response_v2*)pFTM_XO_Cal_Response)->state);
     LogPhoneStopCommand(strMsg);

	 if(bRet)
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;

}
int  CQualPhone::FTM_XO_CALIBRATION(unsigned short xo_cal_command,unsigned char xo_cal_version,void * pFTM_XO_Cal_Request, void *pFTM_XO_Cal_Response)
{
	CString strMsg;
	strMsg.Format("QLIB_FTM_XO_CALIBRATION ");
	LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_FTM_XO_CALIBRATION(m_hResourceContext,xo_cal_command,xo_cal_version,pFTM_XO_Cal_Request,pFTM_XO_Cal_Response);
	strMsg.Format("QLIB_FTM_XO_CALIBRATION : response  status=%d",((FTM_XO_Cal_Response_v2*)pFTM_XO_Cal_Response)->state);
	LogPhoneStopCommand(strMsg);
	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}

int  CQualPhone::ReloadNV()
{
  CString strMsg;
  unsigned short uiStatus;
  strMsg="QLIB_FTM_LOAD_RF_NV";
  LogPhoneStartCommand(strMsg);
  
  bool bRet=QLIB_FTM_LOAD_RF_NV(m_hResourceContext,&uiStatus);
  ReleaseMutex(m_hResourceContext);

  strMsg.Format("QLIB_FTM_LOAD_RF_NV :status=%d",uiStatus);
  LogPhoneStopCommand(strMsg);
  if(bRet && (uiStatus==0 ||  uiStatus==2))
    return PHONE_SUCCESS;
  else
     return ERR_QLIB_FUNCTION_FAILED;

}
int CQualPhone::ReadNV(int iNVID,unsigned char* uiNVValue,int iLength)
{
	CString strMsg;
	unsigned short uiStatus;
	strMsg.Format("QLIB_DIAG_NV_Read_F : NVID=%d ",iNVID);
    LogPhoneStartCommand(strMsg);
	bool bRet=QLIB_DIAG_NV_READ_F(m_hResourceContext,iNVID,uiNVValue,iLength,&uiStatus);
	ReleaseMutex(m_hResourceContext);

	strMsg.Format("QLIB_DIAG_NV_Read_F : NVID=%d ; data=%s ;length=%d",iNVID,uiNVValue,iLength);
	LogPhoneStopCommand(strMsg);
	 if(bRet && uiStatus==0)
		 return PHONE_SUCCESS;
	 else
	    return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::ReadEnvGainNV(int iNVID,unsigned char* uiNVValue,unsigned short iLength)
{
	CString strMsg;
	unsigned short uiStatus;

	strMsg.Format("QLIB_FTM_GSM_API_ReadEnvGainNV : NVID=%d ",iNVID);
	LogPhoneStartCommand(strMsg);
    bool bRet=QLIB_FTM_GSM_API_ReadEnvGainNV (m_hResourceContext, iNVID, uiNVValue,&iLength, &uiStatus, 2 );//2 to get EDGE Env in byte 0 and 1.
	ReleaseMutex(m_hResourceContext);

	strMsg.Format("QLIB_DIAG_NV_Read_F : NVID=%d ; data=%s ;length=%d",iNVID,uiNVValue,iLength);
	LogPhoneStopCommand(strMsg);
	 if(bRet && uiStatus==0)
		 return PHONE_SUCCESS;
	 else
	    return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::WriteNV(int iNVID,unsigned char* uiNVValue,int iLength)
{
    CString strMsg;
	unsigned short uiStatus;
	strMsg.Format("QLIB_DIAG_NV_WRITE_F : NVID=%d ; data=%s ;length=%d",iNVID,uiNVValue,iLength);
	
    LogPhoneStartCommand(strMsg);
	 bool bRet=QLIB_DIAG_NV_WRITE_F(m_hResourceContext,iNVID,uiNVValue,iLength,&uiStatus);
	 ReleaseMutex(m_hResourceContext);

	 if(bRet && uiStatus==0)
		 return PHONE_SUCCESS;
	 else
	    return ERR_QLIB_FUNCTION_FAILED;
}
int  CQualPhone::SetPhoneMode(mode_enum_type eMode)
{
	CString strMsg;
	unsigned long iPhoneOperMode=1;
	BOOL bRet;
	int iWaitPowerON=0;

	bRet=QLIB_GetPhoneOperatingMode(m_hResourceContext,&iPhoneOperMode);

	strMsg.Format("QLIB_GetPhoneOperatingMode() iPhoneMode= %d",iPhoneOperMode);
	LogPhoneStartCommand(strMsg);

 
    if(iPhoneOperMode==SYS_OPRT_MODE_PWROFF||iPhoneOperMode==SYS_OPRT_MODE_LPM)
	{
		QLIB_DIAG_CONTROL_F(m_hResourceContext,MODE_ONLINE_F);
		Sleep(500);
		 do 
		{
			iWaitPowerON++;
			bRet=QLIB_GetPhoneOperatingMode(m_hResourceContext,&iPhoneOperMode);

			strMsg.Format("QLIB_GetPhoneOperatingMode() iPhoneMode= %d",iPhoneOperMode);
			LogPhoneStartCommand(strMsg);
			Sleep(100);


		} while((iPhoneOperMode==SYS_OPRT_MODE_PWROFF||iPhoneOperMode==SYS_OPRT_MODE_LPM)&&iWaitPowerON<120);
	}
	  
	if(iWaitPowerON==120)
	   return PHONE_CONNECT_FAIL;
      
	
    LogPhoneStartCommand(strMsg);
	do 
	{
		iWaitPowerON++;
		bRet=QLIB_DIAG_CONTROL_F(m_hResourceContext,eMode);

		strMsg=_T("QLIB_DIAG_CONTROL_F(")+CStr::IntToStr((int)eMode)+_T(")");
		LogPhoneStartCommand(strMsg);
		Sleep(100);


	} while((!bRet)&&iWaitPowerON<120);
	 ReleaseMutex(m_hResourceContext);
	 return bRet?PHONE_SUCCESS:PHONE_CONNECT_FAIL;
}
int CQualPhone::GetPhoneMode(unsigned long *piPhonemode)
{
	CString strMsg;
	BOOL bRet=QLIB_GetPhoneOperatingMode(m_hResourceContext,piPhonemode);
	strMsg.Format("QLIB_GetPhoneOperatingMode() PhoneMode= %d",*piPhonemode);
	LogPhoneStartCommand(strMsg);
	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;

}
void CQualPhone::CloseComport()
{
	 LogPhoneStartCommand(_T("QLIB_DisconnectServer"));
		QLIB_DisconnectServer(m_hResourceContext);
		
		m_hResourceContext = 0;
}
bool  CQualPhone::OpenATComport(int iComport)
{
	return m_SerialInterface.OpenComport(iComport);
}
void CQualPhone::CloseATComport()
{
     return m_SerialInterface.CloseCom();
}
int CQualPhone::OpenComport(int iComport,int iRetrytimes)
{
	CString strMsg;
	unsigned short iComportNow;
    
     strMsg=_T("QLIB_SetLibraryMode(")+CStr::IntToStr((int)m_eLibMode)+_T(")");
    LogPhoneStartCommand(strMsg);
    QLIB_SetLibraryMode(m_eLibMode);
	do
	{
		if (iComport==0)
		{
			m_hResourceContext=QLIB_ConnectServer(QLIB_COM_AUTO_DETECT);
		}
		else
		{
			m_hResourceContext = QLIB_ConnectServer(iComport);

		}

		m_bConnected=QLIB_IsPhoneConnected(m_hResourceContext);
		if(m_bConnected)
			break;
		Sleep(1000);
	}while(--iRetrytimes>0);


	if(!m_bConnected)
	{
	    QLIB_DisconnectServer(m_hResourceContext);
		m_hResourceContext = 0;
		return false;
	}
	QLIB_GetComPortNumber(m_hResourceContext,&iComportNow);
	strMsg.Format("Connect Phone Use ComPort %d",iComportNow);
	LogPhoneStartCommand(strMsg);

	ReleaseMutex(m_hResourceContext);
	return m_bConnected?PHONE_SUCCESS:PHONE_CONNECT_FAIL;
}
bool   CQualPhone::SetAtMode(bool IsAtMode)
{
    m_bIsAtMode=IsAtMode;
	return true;
}
bool  CQualPhone::BT_Enable(bool bOn)
{
	/*CString strBatName;
	int iResult;
	CString strDllPathName;

	::GetModuleFileName(NULL, strDllPathName.GetBuffer(_MAX_PATH), _MAX_PATH);
	strDllPathName.ReleaseBuffer();
     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
		
	
	strBatName=strDllPathName+"\\BlueTooth_Nonsignaling_Batch\\Single CH\\bt_enable.bat";

	iResult=WinExec(strBatName,SW_SHOWNORMAL);
	if(iResult>31)
   return true;
	else
	return false;
	*/

	if(m_bIsAtMode)
	{
       	 char szCmd[1024];
		char szRev[1024]={0};
		 bool bret;
   
    
	 bret=m_SerialInterface.AT_Init();
	 if(!bret)
		 return false;
     if(bOn)
	 {
		 sprintf(szCmd,"at+setbt=1");

		 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,1000);
	    
		 if(!bret)
			 return false;   
	 } 
	 else
	 {
        sprintf(szCmd,"at+setbt=0");

		bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,1000);
	    
		if(!bret)
			 return false;  
	 }
	}
	return true;
	
}
 bool CQualPhone::GPS_Enable(bool bIsOn)
 {
   CString strMsg;
   	unsigned char iStatus=0;    
   if(bIsOn)
   strMsg.Format("QLIB_DIAG_GPS_SA_RF_VERIF_MODE_SWITCH_WithWait() ON");
   else
    strMsg.Format("QLIB_DIAG_GPS_SA_RF_VERIF_MODE_SWITCH_WithWait() OFF");
    LogPhoneStartCommand(strMsg);
	if(bIsOn)
    return QLIB_DIAG_GPS_SA_RF_VERIF_MODE_SWITCH_WithWait(m_hResourceContext,GPS_SA_RF_VERIF_MODE_SWITCH_ENTER_MODE,&iStatus);   
	else
    return QLIB_DIAG_GPS_SA_RF_VERIF_MODE_SWITCH_WithWait(m_hResourceContext,GPS_SA_RF_VERIF_MODE_SWITCH_EXIT_MODE,&iStatus);   

 }
 bool CQualPhone::GPS_GEN8_GetCNo(unsigned char iCollectMode,double * pdCNoDBHz,int * piFreqInHz)
 {
	 CString strMsg;
	 unsigned char iStatus=0;    
	 
		 strMsg.Format("QLIB_DIAG_GEN8_GET_EMBEDDED_CALCULATED_CTON(%d,32,10)",iCollectMode);

	 LogPhoneStartCommand(strMsg);
	 return QLIB_DIAG_GEN8_GET_EMBEDDED_CALCULATED_CTON (m_hResourceContext,iCollectMode,32,10,pdCNoDBHz,piFreqInHz);   	 

 }
 bool CQualPhone::DTV_GetBerCNO(int iChannel,double & dCNO,double & SBER)
 {
     CString strMsg;
	 char szCmd[1024];
	 char szRev[1024]={0};
	 char *token = NULL; 
	 char seps[] = ",";
	 bool bret;
	 char *chCNO;
    
	 bret=m_SerialInterface.AT_Init();
	 if(!bret)
		 return false;
	 sprintf(szCmd,"AT+DTVTEST=%d",iChannel);

     bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,10000);
    
	 if(!bret)
		 return false;

	 if(!strstr(szRev,","))
	 {
       dCNO=-99; 
        SBER=-99;
       return true;
	 }
   
     token=strtok(szRev,seps);
     
	 chCNO=token+15;
      if(strlen(chCNO)>4)
	  {
        dCNO=-99; 
	  }
	  else
	  {
        dCNO=atof(chCNO);
	  }
	 token=strtok(NULL,seps);
    
	  if(strlen(token)>6)
       SBER=-99;
	  else
      SBER=atof(token); 
	 return true;
 }

bool CQualPhone::CDMA_GSMWCDMA_Mode_AT(int iSVID)  //0: To CDMA;    1: To GSMWCDMA
 {
	  CString strMsg;
	 char szCmd[1024];
	 char szRev[1024]={0};
	 bool bret;
	
	/* bret=m_SerialInterface.AT_Init();
	 if(!bret)
		 return false;*/
	 sprintf(szCmd,"AT+GCSWAP=%d",iSVID);

     bret=m_SerialInterface.AT_SendCmd(szCmd,NULL);
    
	 if(!bret)
		 return false;
	 return true;
 }


 bool CQualPhone::Efssyn_AT()
  {
 	  CString strMsg;
 	 char szCmd[1024];
 	 char szRev[1024]={0};
 	 bool bret;
 	
 	/* bret=m_SerialInterface.AT_Init();
 	 if(!bret)
 		 return false;*/
 	 sprintf(szCmd,"AT+EFSSYNC");
 
      bret=m_SerialInterface.AT_SendCmd(szCmd,NULL);
     
 	 if(!bret)
 		 return false;
 	 return true;
  }
 

 bool CQualPhone::GPS_StartAT(int iSVID)
 {
	  CString strMsg;
	 char szCmd[1024];
	 char szRev[1024]={0};
	 bool bret;
	
	/* bret=m_SerialInterface.AT_Init();
	 if(!bret)
		 return false;*/
	 sprintf(szCmd,"AT+GPSTEST=%d",iSVID);

     bret=m_SerialInterface.AT_SendCmd(szCmd,NULL);
    
	 if(!bret)
		 return false;
	 return true;

 }
 bool CQualPhone::GPS_GetCNO_AT(int & iCNO)
 {
	  CString strMsg,strTemp;
	  CStringVtr strVtr,strVtrV;
	 char szRev[1024]={0};
	 bool bret;
    
     bret=m_SerialInterface.AT_SendCmd(NULL,szRev);
    
	 if(!bret)
		 return false;

	strTemp=szRev;
	strTemp.Replace("/r","");
	strTemp.Replace("/n","");
	CStr::ParseString(strTemp,":",strVtr);
	for (int i=0;i<strVtr.size();i++)
	{
		CStr::ParseString(strVtr[i],"+",strVtrV);
		if (CStr::StrToInt(strVtrV[0])>0)
		{
			iCNO=CStr::StrToInt(strVtrV[0]);
			return true;
		}
	}
	iCNO=0;
	return true;
	
	 //chCNO=szRev+9;

  //  iCNO=atoi(chCNO);
	 //return true;


 }
 bool CQualPhone::GPS_GetCNO(int iSVID,word wLogID,int & iCNO)
 {
	CString strMsg;
   	unsigned char iStatus=0;
	int iRet;
	int iRetryTimes=10;
	unsigned char szSigLog[1024]={0};   
    unsigned short usLogSize=0;	
	bool bIsCNOFind=false;

	CGPS_Gen8_Rx_RfMode_Struct_type RXMODEtype; 
	CGPS_Gen8_SvTrack_Struct_type  SVTrackPara;
	CGPS_GEN8_MeasurementReportLog_SvRow_Struct sGen8Report; 
    memset(&RXMODEtype,0,sizeof(CGPS_Gen8_Rx_RfMode_Struct_type));			
	memset(&SVTrackPara,0,sizeof(CGPS_Gen8_SvTrack_Struct_type));
	memset(&sGen8Report,0,sizeof(CGPS_GEN8_MeasurementReportLog_SvRow_Struct));
	
	SVTrackPara.u_TestMode=0;
	SVTrackPara.u_GloHwChan=0;
    SVTrackPara.u_GpsOrSbasSvId=iSVID;
	SVTrackPara.b_GloFreqencyId=0;
	SVTrackPara.u_GpsSbasBitEdgeAction=1;
	SVTrackPara.u_GloBitEdgeAction=1;
	SVTrackPara.u_Command=1;
    strMsg.Format("QLIB_DIAG_SetExtendedLogCode() LogID=%x",wLogID);
    LogPhoneStartCommand(strMsg);
	iRet=QLIB_DIAG_SetExtendedLogCode(m_hResourceContext,1,wLogID,wLogID);
	if(!iRet)
		return false;
   strMsg.Format("QLIB_DIAG_SetPhoneLoggingState ON");
   LogPhoneStartCommand(strMsg);
   iRet=QLIB_DIAG_SetPhoneLoggingState(m_hResourceContext,1);
   if(!iRet)
		return false;

    strMsg.Format("QLIB_GPS_GEN8_PRx_Mode_Config");
    LogPhoneStartCommand(strMsg);

	iRet=QLIB_GPS_GEN8_PRx_Mode_Config(m_hResourceContext,&RXMODEtype);
	 if(!iRet)
		return false;

    strMsg.Format("QLIB_DIAG_GPS_GEN8_SV_TRACK() SVID=%d",iSVID);
    LogPhoneStartCommand(strMsg);

   	iRet=QLIB_DIAG_GPS_GEN8_SV_TRACK(m_hResourceContext,&SVTrackPara,&iStatus) ;

	 if(!iRet)
		return false;


	do
	{
    strMsg.Format("QLIB_DIAG_GetSingleLog()");
    LogPhoneStartCommand(strMsg);
    iRet=QLIB_DIAG_GetSingleLog(m_hResourceContext,1,wLogID,10000,szSigLog,&usLogSize);
	if(!iRet)
		return false;
	memset(&sGen8Report,0,sizeof(sGen8Report));
	memcpy(&sGen8Report,szSigLog+44,sizeof(sGen8Report));
	if(sGen8Report.OBS_STATE==5)
	{
		bIsCNOFind=true;
		break;

	}
		Sleep(300);
	}while(iRetryTimes-->0);
	
	if(!bIsCNOFind)
	{   
		strMsg.Format("QLIB_DIAG_GetSingleLog() OBS=%d",sGen8Report.OBS_STATE);
         LogPhoneStartCommand(strMsg);
		return false;
	}

	iCNO=sGen8Report.CNO;
    QLIB_DIAG_SetPhoneLoggingState(m_hResourceContext,0);

	 return true;
 }
 bool CQualPhone::WLAN_Driverop(bool bLoad)
 {
     CString strRev;
     CString strMsg;
	 CString strSend;
	 if(!m_bIsAtMode)
	 {
		if(bLoad)
		{
	            
				  strSend.Format("adb shell wbtest winsmod");

				  bool bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);

					
					//if(!bret || strRev!="")
					if(!bret)
					{ 
					  return false;   
					}
		}
		else
		{
                strSend.Format("adb shell wbtest wrmmod");

				  bool bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);

					
					//if(!bret || strRev!="")
					if(!bret)
					{ 
					  return false;   
					}
		}
	 }

	 return true;

 }
 bool CQualPhone::WLAN_Rmmod()
 {
			CString strSend,strRev;
					bool bret;


					bret=m_SerialInterface.ADB_SendCmd("adb shell rmmod ar6000",strRev,false);
					if(!bret )
					{ 
					  return false;   
					}
					Sleep(1000);
					return true;
 }
 bool CQualPhone::Adb_Push(CString filePath,CString targetPath)
 {
	CString strSend,strRev;
	bool bret;
	bret=m_SerialInterface.ADB_SendCmd("adb remount",strRev,false);
		if(!bret)
					{ 
					  return false;   
					}
	


	strSend.Format("adb push %s %s",filePath,targetPath);
	
	bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
					if(!bret)
					{ 
					  return false;   
					}
					Sleep(300);


	strSend.Format("adb shell chmod 777 %s",targetPath);
		
	bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
					if(!bret)
					{ 
					  return false;   
					}
	return true;
 }
 int CQualPhone::BTTestAdbInit()
 {
	 CString strSend,strRev;
	 bool bret;
	 int iRetry=3;
	 BOOL bstatus=FALSE;

	 bret=m_SerialInterface.ADB_SendCmdEx("kill-server",strRev,false);
	 if(!bret )
	 { 
		 return PHONE_CONNECT_FAIL;   
	 }

	 do 
	 {
		 bret=m_SerialInterface.ADB_SendCmdEx("start-server",strRev,true,1000);
		 if(!bret )
		 { 
			 return PHONE_CONNECT_FAIL;   
		 }	
		 if (-1<strRev.Find("successfully"))
		 {
			 break;
		 }
		 Sleep(2000);
	 } while (0<iRetry--);
	 if(0>=iRetry )
	 { 
		 return PHONE_CONNECT_FAIL;   
	 }		
     iRetry=3;
	 do 
	 {
		 bret=m_SerialInterface.ADB_SendCmdEx("devices",strRev,true);
		 if(!bret )
		 { 
			 return PHONE_CONNECT_FAIL;   
		 }	
		 if (-1<strRev.Find("device"))
		 {
			 break;
		 }
		 Sleep(2000);
	 } while (0<iRetry--);
	 if(0>=iRetry )
	 { 
		 return PHONE_CONNECT_FAIL;   
	 }	
	 
	 bret=m_SerialInterface.ADB_SendCmdEx("shell setprop service.adb.root 1",strRev,false,1000);

	if(!bret)
	{ 
		return PHONE_CONNECT_FAIL;   
	}	
	//bstatus=m_SerialInterface.PipeWriteAndWait("ping localhost > nul\n","NULL",200);		
	iRetry=3;
	do 
	{
		bret=m_SerialInterface.ADB_SendCmdEx("shell ftmdaemon",strRev,true,1000);
		if(!bret )
		{ 
			return PHONE_CONNECT_FAIL;   
		}	
		if (-1<strRev.Find("Diag_LSM_Init succeeded"))
		{
			break;
		}
		Sleep(2000);
	} while (0<iRetry--);
	if(0>=iRetry )
	{ 
		return PHONE_CONNECT_FAIL;   
	}
	
	 return PHONE_SUCCESS;
 }
 int CQualPhone::WLANTestAdbRelease()
 {
	 BOOL bstatus=FALSE;
	 bstatus=m_SerialInterface.CmdPipeRelease();
	 return PHONE_SUCCESS;
 }
 int CQualPhone::WLANTestAdbInit()
 {
	 CString strSend,strRev;
	 CStringVtr svTemp;
	 bool bret=false;
	 int iRetry=3;
	 BOOL bstatus=FALSE;
	 char szRet[2048];
	 memset(szRet,0,sizeof(szRet));
	 if (m_SerialInterface.GetCmdPipeStatus())
	 {
		 m_SerialInterface.CmdPipeRelease();
	 }
	 bstatus= m_SerialInterface.CmdPipeInit();

	 bret=m_SerialInterface.ADB_SendCmdEx("kill-server",strRev,false,1000);
	 if(!bret )
	 { 
		return PHONE_CONNECT_FAIL;   
	 }

	do 
	 {
		bret=m_SerialInterface.ADB_SendCmdEx("start-server",strRev,true,3000);
		if(!bret )
		{ 
			return PHONE_CONNECT_FAIL;   
		}	
		if (-1<strRev.Find("successfully"))
		{
			break;
		}
		Sleep(1000);
	 } while (0<iRetry--);
	 if(0>=iRetry )
	 { 
		return PHONE_CONNECT_FAIL;   
	 }	
	
	 iRetry=3;
	 do 
	 {
		bret=m_SerialInterface.ADB_SendCmdEx("devices",strRev,true);
		if(!bret )
		{ 
			return PHONE_CONNECT_FAIL;   
		}	
		if (-1<strRev.Find("device"))
		{
			break;
		}
		Sleep(1000);
	 } while (0<iRetry--);
	 if(0>=iRetry )
	 { 
		return PHONE_CONNECT_FAIL;   
	 }		

	 bret=m_SerialInterface.ADB_SendCmdEx("shell setprop service.adb.root 1",strRev,false,1000);
	 if(!bret)
	 { 
		return PHONE_CONNECT_FAIL;   
	 }


	 bret=m_SerialInterface.ADB_SendCmdEx("shell insmod /system/lib/modules/wlan.ko con_mode=5",strRev,false,2000);//must need 2000ms to wait for wlan loaded
	 if(!bret)
	 { 
		return PHONE_CONNECT_FAIL;   
	 }

	 bret=m_SerialInterface.ADB_SendCmdEx("shell ptt_socket_app -v -d -f",strRev,false,1000);
	 if(!bret)
	 { 
		return PHONE_CONNECT_FAIL;   
	 }

        //===========================//
		/*
		bstatus=m_SerialInterface.PipeWriteAndWait("adb shell\n","#",200);
		bstatus=m_SerialInterface.CmdPipeWrite("ptt_socket_app\n");  
		Sleep(2000);
		memset(szRet,0,sizeof(szRet));
		bstatus=m_SerialInterface.CmdPipeRead(szRet);
		bstatus=m_SerialInterface.CmdPipeWrite("insmod /system/lib/modules/wlan.ko con_mode=5\n");
        //bstatus=m_SerialInterface.PipeWriteAndWait("insmod /system/lib/modules/wlan.ko con_mode=5\n","insmod /system/lib/modules/wlan.ko con_mode=5",20);
		memset(szRet,0,sizeof(szRet));
		bstatus=m_SerialInterface.CmdPipeRead(szRet);
		bstatus=m_SerialInterface.CmdPipeWrite("exit\n");  
		memset(szRet,0,sizeof(szRet));
		bstatus=m_SerialInterface.CmdPipeRead(szRet);
		*/
		//=========================//
	/*bstatus = m_SerialInterface.PipeWriteAndWait("adb remount\n","NULL",20);
	bstatus = m_SerialInterface.FlushPipe();
	bstatus=m_SerialInterface.CmdPipeWrite("adb push c:\\wlan.ko /system/lib/modules/prima\n");
	bstatus=m_SerialInterface.CmdPipeRead(szRet);*/
/*
		bstatus=m_SerialInterface.PipeWriteAndWait("adb shell\n","#",20);
		bstatus=m_SerialInterface.CmdPipeWrite("rmmod wlan\n");
		memset(szRet,0,sizeof(szRet));
		bstatus=m_SerialInterface.CmdPipeRead(szRet);
		bstatus=m_SerialInterface.CmdPipeWrite("ps\n");
		do 
		{
			memset(szRet,0,sizeof(szRet));
			if(m_SerialInterface.CmdPipeReadLine(szRet,20)==FALSE) break;	
			strRev.Format("%s",szRet);
			if (-1<strRev.Find("ptt_socket_app"))
			{
				CStr::ParseString(strRev," ",svTemp);
				bret=true;
				break;
			}
			
		} while (1);
		if (bret)
		{
			if (svTemp[4]=="")
			{strSend="kill "+svTemp[6]+"\n";
			} 
			else
			{strSend="kill "+svTemp[4]+"\n";
			}
			
			bstatus = m_SerialInterface.FlushPipe();
			m_SerialInterface.CmdPipeWrite(strSend.GetBuffer(strSend.GetLength()));
			strSend.ReleaseBuffer();
			memset(szRet,0,sizeof(szRet));
			
			bstatus=m_SerialInterface.CmdPipeRead(szRet);
	
		}
	
		bstatus=m_SerialInterface.CmdPipeWrite("ptt_socket_app\n");
		memset(szRet,0,sizeof(szRet));
		bstatus=m_SerialInterface.CmdPipeRead(szRet);
	
		bstatus=m_SerialInterface.CmdPipeWrite("insmod /system/lib/modules/wlan.ko con_mode=5\n");
		memset(szRet,0,sizeof(szRet));
		bstatus=m_SerialInterface.CmdPipeRead(szRet);
*/	
		/*
		CString strBatName;
		int iResult;
		CString strDllPathName;

		::GetModuleFileName(NULL, strDllPathName.GetBuffer(_MAX_PATH), _MAX_PATH);
		strDllPathName.ReleaseBuffer();
		 strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
			
		
		//if(iChannel==1 && iModulationType==9)
		strBatName=strDllPathName+"\\SriptFile\\BTTX.bat";

		iResult=WinExec(strBatName,SW_HIDE);
		if(iResult>31)
			return PHONE_SUCCESS;
		else
			return PHONE_CONNECT_FAIL;*/
	return PHONE_SUCCESS;
	 

 }
 int CQualPhone::ADB_KILL_SERVER()
 {
	 CString strSend,strRev;
	 bool bret;	


	 bret=m_SerialInterface.ADB_SendCmdEx("kill-server",strRev,false);
	 if(!bret )
	 { 
		 return PHONE_CONNECT_FAIL;   
	 }
	 return PHONE_SUCCESS;

 }
 int CQualPhone::BTTestFTMInit()
 {
	 CString strMsg;
	 int iRetry=5;

	
	
	 strMsg.Format("QLIB_FTM_BT_SET_CHIP_ID");
	 LogPhoneStartCommand(strMsg)
	BOOL bRet=QLIB_FTM_BT_SET_CHIP_ID (m_hResourceContext,0);
	 if (!bRet)
	 {
		 strMsg=_T("QLIB_FTM_BT_SET_CHIP_ID() Fail");
		 LogPhoneStartCommand(strMsg);	
		 return PHONE_CONNECT_FAIL;
	 } 
	 strMsg.Format("QLIB_FTM_BT_SET_LegacyLoggingMode");
	 LogPhoneStartCommand(strMsg)
	 bRet=QLIB_FTM_BT_SET_LegacyLoggingMode(m_hResourceContext,0);
	 if (!bRet)
	 {
		 strMsg=_T("QLIB_FTM_BT_SET_LegacyLoggingMode() Fail");
		 LogPhoneStartCommand(strMsg);	
		 return PHONE_CONNECT_FAIL;
	 } 
	 strMsg.Format("QLIB_FTM_BT_HCI_Reset");
	 LogPhoneStartCommand(strMsg)
	 do 
	 {
		 
			 bRet=QLIB_FTM_BT_HCI_Reset (m_hResourceContext);
		 if (!bRet)
		 {
			 strMsg=_T("QLIB_FTM_BT_HCI_Reset() Fail");
			 LogPhoneStartCommand(strMsg);	
			 Sleep(1000);
		 } 
		 else
		 {
			 break;
		 }
	 } while (0<iRetry--);
	 if (0>=iRetry)
	 {
		 return PHONE_CONNECT_FAIL;
	 }

	return PHONE_SUCCESS;
 }
 int CQualPhone::BTTestReset()
 {
	 CString strMsg;
	 strMsg.Format("QLIB_FTM_BT_HCI_Reset");
	 LogPhoneStartCommand(strMsg)
		 bool bRet=QLIB_FTM_BT_HCI_Reset (m_hResourceContext);
	 if (!bRet)
	 {
		 strMsg=_T("QLIB_FTM_BT_HCI_Reset() Fail");
		 LogPhoneStartCommand(strMsg);	
		 return PHONE_CONNECT_FAIL;
	 } 
	 return PHONE_SUCCESS;

 }
 int CQualPhone::BTTestTxBurst( unsigned char ihopChannels, unsigned char itransmitPattern, unsigned char ipacketType, unsigned char idataWhiteningEnable, unsigned char itransitOutputPower, unsigned char itragetDeviceAddress[6], unsigned char ilogicalTransportAddress )
 {
	 CString strMsg;
	 int iRetry=5;
	 unsigned char iahopChennels[5];
	 unsigned short ipayloadLength=0;
	 strMsg.Format("QLIB_FTM_BT_HCI_Reset");
	 LogPhoneStartCommand(strMsg)
		 bool bRet=QLIB_FTM_BT_HCI_Reset (m_hResourceContext);
	 if (!bRet)
	 {
		 strMsg=_T("QLIB_FTM_BT_HCI_Reset() Fail");
		 LogPhoneStartCommand(strMsg);	
		 return PHONE_CONNECT_FAIL;
	 } 
	 for(int i=0;i<5;i++)
	 {iahopChennels[i]=ihopChannels;
	 }
	 switch (ipacketType)
	 {
	 case BT_DH1:
		 ipayloadLength=27;
	 	break;
	 case BT_DH3:
		 ipayloadLength=183;
		 break;
	 case BT_DH5:
		 ipayloadLength=339;
		 break;
	 case BT_2_DH1:
		 ipayloadLength=54;
		 break;
	 case BT_2_DH3:
		 ipayloadLength=367;
		 break;
	 case BT_2_DH5:
		 ipayloadLength=679;
		 break;
	 case BT_3_DH1:
		 ipayloadLength=83;
		 break;
	 case BT_3_DH3:
		 ipayloadLength=552;
		 break;
	 case BT_3_DH5:
		 ipayloadLength=1021;
		 break;
	 }

	 bRet=QLIB_FTM_BT_PROD_TEST_SUBCOMMAND_TEST_TX(m_hResourceContext,iahopChennels,itransmitPattern,ipacketType,0,itransitOutputPower,1,itragetDeviceAddress,0,ipayloadLength,0);
	 if (!bRet)
	 {
		 strMsg=_T("QLIB_FTM_BT_PROD_TEST_SUBCOMMAND_TEST_TX() Fail");
		 LogPhoneStartCommand(strMsg);	
		 return PHONE_CONNECT_FAIL;
	 } 
	 return PHONE_SUCCESS;

 }
 int CQualPhone::BTTestRxEnable( unsigned char ihopChannels, unsigned char itransmitPattern, unsigned char ipacketType, unsigned char idataWhiteningEnable, unsigned char itransitOutputPower, unsigned char itragetDeviceAddress[6], unsigned char ilogicalTransportAddress )
 {
	 CString strMsg;
	 int iRetry=5;
	 unsigned char iahopChennels[5];
	 unsigned short ipayloadLength=0;
	 strMsg.Format("QLIB_FTM_BT_HCI_Reset");
	 LogPhoneStartCommand(strMsg)
		 bool bRet=QLIB_FTM_BT_HCI_Reset (m_hResourceContext);
	 if (!bRet)
	 {
		 strMsg=_T("QLIB_FTM_BT_HCI_Reset() Fail");
		 LogPhoneStartCommand(strMsg);	
		 return PHONE_CONNECT_FAIL;
	 } 
	 for(int i=0;i<5;i++)
	 {iahopChennels[i]=ihopChannels;
	 }
	 switch (ipacketType)
	 {
	 case BT_DH1:
		 ipayloadLength=27;
		 break;
	 case BT_DH3:
		 ipayloadLength=183;
		 break;
	 case BT_DH5:
		 ipayloadLength=339;
		 break;
	 case BT_2_DH1:
		 ipayloadLength=54;
		 break;
	 case BT_2_DH3:
		 ipayloadLength=367;
		 break;
	 case BT_2_DH5:
		 ipayloadLength=679;
		 break;
	 case BT_3_DH1:
		 ipayloadLength=83;
		 break;
	 case BT_3_DH3:
		 ipayloadLength=552;
		 break;
	 case BT_3_DH5:
		 ipayloadLength=1021;
		 break;
	 }

	 bRet=QLIB_FTM_BT_PROD_TEST_SUBCOMMAND_TEST_RX_ONLY(m_hResourceContext,iahopChennels,itransmitPattern,ipacketType,0,itransitOutputPower,1,itragetDeviceAddress,0,ipayloadLength,0);
	 if (!bRet)
	 {
		 strMsg=_T("QLIB_FTM_BT_PROD_TEST_SUBCOMMAND_TEST_TX() Fail");
		 LogPhoneStartCommand(strMsg);	
		 return PHONE_CONNECT_FAIL;
	 } 
	 return PHONE_SUCCESS;

 }
 bool CQualPhone::WLAN_Do_SelfInit()
 {
		CString strSend,strRev;
					bool bret;


					bret=m_SerialInterface.ADB_SendCmd("adb devices",strRev,false);
					if(!bret )
					{ 
					  return false;   
					}
					
 					bret=m_SerialInterface.ADB_SendCmd("adb shell insmod /system/wifi/ar6000.ko testmode=2",strRev,false);
					if(!bret )
					{ 
					  return false;   
					}
					Sleep(2000);

					bret=m_SerialInterface.ADB_SendCmd("adb shell sh /system/wifi/wifi_selfInit.sh",strRev,false);
					 FactoryLog(111, "WifiLog", "1", 0, "--", "--", strRev, "--",TRUE, "--");
						

					if(!bret)
					{ 
					  return false;   
					}
					
					Sleep(2000);
					return true;
 }
bool CQualPhone::WLAN_Enable(bool bOn,bool bIsTx,int iAdbType)
{
	CString strMsg;
	  CString strRev;
	 if(m_bIsAtMode)
	{

		 char szCmd[1024];
		 char szRev[1024]={0};
		 bool bret;
	   
	    
		 bret=m_SerialInterface.AT_Init();
		 if(!bret)
			 return false;
		 if(bOn)
		 {
			 if(bIsTx)
			 {
				 sprintf(szCmd,"at+wifitx=1");

				 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,500);
			    
				 if(!bret)
					 return false;
			 }
		 }
		 else
		 {
			 if(bIsTx)
			 {
				 sprintf(szCmd,"at+wifitx=0");

				 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,500);
			    
				 if(!bret)
					 return false;   
			 }
			 else
			 {
				  sprintf(szCmd,"at+wifirx=0");

				 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,1000);
			    
				 if(!bret)
					 return false;  
			 }

		 }
	}
	else
	{
		CString strRev;
		CString strMsg;
		CString strSend;
	
		if(bOn)
		{
		         
		         
							/* CString strBatName;
				int iResult;
				CString strDllPathName;

				::GetModuleFileName(NULL, strDllPathName.GetBuffer(_MAX_PATH), _MAX_PATH);
				strDllPathName.ReleaseBuffer();
				 strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
					
				
				strBatName=strDllPathName+"\\SriptFile\\WLAN_Batch\\Enable_Wifi.bat";
				strMsg.Format("Wlan Enable : File =%s",strBatName);
				LogPhoneStartCommand(strMsg);
				iResult=WinExec(strBatName,SW_HIDE);
				Sleep(3000);
				if(iResult<32)
				return false;*/
				
			  
				CString strSend;
				bool bret;


				bret=m_SerialInterface.ADB_SendCmd("adb devices",strRev,false);
				if(!bret )
				{ 
				  return false;   
				}

				if (iAdbType==1)
				{
					//m_SerialInterface.ADB_SendCmd("adb shell insmod /system/wifi/ar6000.ko testmode=1",strRev,false);
					bret=m_SerialInterface.ADB_SendCmd("adb shell insmod /system/wifi/ar6000.ko testmode=1",strRev,false);

					if(!bret)
					{ 
					  return false;   
					}
				

					if(!bret)
					{ 
					  return false;   
					}
				}

				Sleep(2000);			
		}
		else
		{
			bool bret;

			if (iAdbType==1)
			{
				if(bIsTx)
				{
					bret=m_SerialInterface.ADB_SendCmd("adb shell athtestcmd -i wlan0 --tx off",strRev,false);


					if(!bret || strRev!="")
					{ 
						return false;   
					}
				}
				else
				{
					bret=m_SerialInterface.ADB_SendCmd("adb shell athtestcmd -i wlan0 --rx off",strRev,false);


					if(!bret || strRev!="")
					{ 
						return false;   
					}
				}
			}
		}
	 }
	return true;
}
bool CQualPhone::WLAN_TX_Test(const CString& strWLANAddr,int iChannel,int iSignalType,int iBurstType,int iBandWidth,int iTxPower,int iRate,int selfinit,int iAdbType)
{
    CString strRev;
	CString strMsg;
	CString strSend;
	bool bret;
	if(m_bIsAtMode)
	{

		 char szCmd[1024];
	     char szRev[1024]={0};
	     bool bret;
        bret=m_SerialInterface.AT_Init();
	  if(!bret)
		 return false;
    
		 sprintf(szCmd,"at+wifitxparam=%d,%d,%d",iRate,iChannel,iTxPower);

		 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,500);
	    
		 if(!bret)
			 return false;   
	     
	}
	else
	{
		if (iAdbType==1)
		{
			if(iSignalType==2)
			{
				iRate=3;
			}
			else if(iSignalType==4)
			{
				iRate=11;
			}
			else if(iSignalType==5)
			{
				iRate=19;
			}
			strSend.Format("adb shell athtestcmd -i wlan0 --tx off"); 
		}
		else 
		{
			strSend.Format("adb shell wbtest wtx -n 0 -c %d -p %d",iChannel,iRate,iTxPower);
			bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
			//if(!bret || strRev!="")
			if(!bret)
			{ 
				return false;   
			}
			else
				return true;
		}
		bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
		//if(!bret || strRev!="")
		if(!bret)
		{ 
		 return false;   
		}
		Sleep(500);
		if(selfinit==0)
		{
			strSend.Format("adb shell athtestcmd -i wlan0 --tx tx99 --txrate %d --tgtpwr --txfreq %d",iRate,iChannel); 
		}
		else
		{
			strSend.Format("adb shell athtestcmd -i wlan0 --tx tx99 --txrate %d --tgtpwr --txfreq %d",iRate,iChannel); 
		}
		bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
		Sleep(1000);
		//if(!bret || strRev!="")
		if(!bret)
		{ 
		 return false;   
		}
         //bret=m_SerialInterface.ADB_SendCmd("adb shell wl down",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}
		//bret=m_SerialInterface.ADB_SendCmd("adb shell wl down",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}

		//	bret=m_SerialInterface.ADB_SendCmd("adb shell wl up",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}

		//bret=m_SerialInterface.ADB_SendCmd("adb shell wl mpc 0",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}
	 //   
		//	bret=m_SerialInterface.ADB_SendCmd("adb shell wl up",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}


		//bret=m_SerialInterface.ADB_SendCmd("adb shell wl country ALL",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}

	 //   
		//

		///*bret=m_SerialInterface.ADB_SendCmd("adb shell wl scansuppress 1",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}*/

		//bret=m_SerialInterface.ADB_SendCmd("adb shell wl up",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}

		//strSend.Format("adb shell wl channel %d",iChannel);
		//bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}

		//strSend.Format("adb shell wl rate %d",iRate);
		//bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}

		///*bret=m_SerialInterface.ADB_SendCmd("adb shell wl PM 0",strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}*/


		//	strSend.Format("adb shell wl txpwr1 -o -d %d",iTxPower);
		//bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}

		// 
		//	strSend.Format("adb shell wl pkteng_start %s tx 100 1024 0",strWLANAddr);
		//bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
		//if(!bret || strRev!="")
		//{ 
		//  return false;   
		//}

	}
   return true;
}
bool CQualPhone::WLAN_RXCount_ValidPackets(int &refCount)
{

    CString strRev;
	CString strMsg;
	CString strSend;
	CString strTemp;
	CString strCount;
	bool bret;
	if(m_bIsAtMode)
	{
      	 char szCmd[1024];
	     char szRev[1024]={0};
	     bool bret;

    
		 sprintf(szCmd,"at+wifirx=0");

		 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,500);
	    
		 if(!bret)
			 return false; 
         Sleep(1000);
		 sprintf(szCmd,"at+wifipacket?");

		 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,1500);
	    
		 if(!bret)
			 return false; 
         CString strTemp=szRev;
		 int iFindIndex=strTemp.Find(":");
         CString strPacketNum=strTemp.Mid(iFindIndex+1);
		 refCount=10*CStr::StrToInt(strPacketNum);


	}
	else
	{

        bret=m_SerialInterface.ADB_SendCmd("adb shell wbtest wrc -n 1000",strRev,false,1000);
		//Sleep(1000);
		if(!bret)
		{ 
		  return false;   
		}

		int iRXFindex=strRev.Find("RecvNum");
		strTemp=strRev.Right(strRev.GetLength()-iRXFindex-8);
		iRXFindex=strTemp.Find(":");
		strCount=strTemp.Left(iRXFindex);
		refCount=CStr::StrToInt(strCount);
	

		/*LogTrace(MSG_MID,"adb shell wl counters command delay 1s");
		bret=m_SerialInterface.ADB_SendCmd("adb shell wl counters",strRev,false,1000);
		Sleep(1000);
		if(!bret)
		{ 
		  return false;   
		}

		int iRXFindex=strRev.Find("rxmfrmocast");
		strTemp=strRev.Right(strRev.GetLength()-iRXFindex-12);
		iRXFindex=strTemp.Find(" ");
		strCount=strTemp.Left(iRXFindex);
		refCount=CStr::StrToInt(strCount);*/
	}

	return true;
}
bool CQualPhone::WLAN_RXBegin_Test(const CString& strWLANAddr,int iChannel,int iSignalType,int iBurstType,int iBandWidth,int iTxPower,int iRate)
{
    CString strRev;
	CString strMsg;
	CString strSend;
	bool bret;
    if(m_bIsAtMode)
	{
       char szCmd[1024];
	     char szRev[1024]={0};
	     bool bret;
        bret=m_SerialInterface.AT_Init();
		 if(!bret)
			 return false;
    
		 sprintf(szCmd,"at+wifirxparam=%d,%d",iRate,iChannel);

		 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,1000);
	    
		 if(!bret)
			 return false;  

		 //Sleep(7000);  //Delay 10 s to wait to load driver  Set delay outside
	}
	else
	{
		strSend.Format("adb shell wbtest wrx -c %d -r %d -n 0",iChannel,iRate);

		 bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
		//if(!bret || strRev!="")
		if(!bret)
		{ 
		  return false;   
		}


	//bret=m_SerialInterface.ADB_SendCmd("adb shell wl disassoc",strRev,false);
	//	if(!bret || strRev!="")
	//	{ 
	//	  return false;   
	//	}
	//	bret=m_SerialInterface.ADB_SendCmd("adb shell wl down",strRev,false);
	//	if(!bret || strRev!="")
	//	{ 
	//	  return false;   
	//	}

	//	bret=m_SerialInterface.ADB_SendCmd("adb shell wl up",strRev,false);
	//	if(!bret || strRev!="")
	//	{ 
	//	  return false;   
	//	}

	//	strSend.Format("adb shell wl channel %d",iChannel);
	//	bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
	//	if(!bret || strRev!="")
	//	{ 
	//	  return false;   
	//	}

	//	bret=m_SerialInterface.ADB_SendCmd("adb shell wl bi 50000",strRev,false);
	//	if(!bret || strRev!="")
	//	{ 
	//	  return false;   
	//	}

	//	bret=m_SerialInterface.ADB_SendCmd("adb shell wl join test imode adhoc",strRev,false);
	//	if(!bret || strRev!="")
	//	{ 
	//	  return false;   
	//	}

	//   strSend.Format("adb shell wl rate %d",iRate);
	//	bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false);
	//	if(!bret || strRev!="")
	//	{ 
	//	  return false;   
	//	}
	//	//Sleep(3000); Set delay outside
	}


  return true;
}
bool  CQualPhone::BT_TX_Test(int iChannel,int iDataPattern,int iModulationType,int iTxPower)
{
	if(m_bIsAtMode)
	{
        char szCmd[1024];
		char szRev[1024]={0};
		bool bret;
   
    
	 bret=m_SerialInterface.AT_Init();
	 if(!bret)
		 return false;
    
		 sprintf(szCmd,"at+btparam=%d,0,%d,%d",iTxPower,iDataPattern,iModulationType);

		 bret=m_SerialInterface.AT_SendCmd(szCmd,szRev,1000);
	    
		 if(!bret)
			 return false;   
  
		 //Sleep(1000);
		return true;
	}
	else
	{

     
		CString strRev;
		CString strMsg;
		CString strSend;

       // bool bret;
		/*//strSend.Format("adb shell wbtest -b -f %d -t %d",iChannel,iModulationType);
		strSend.Format("adb shell wbtest bt -f %d -t %d",iChannel,iModulationType);
		bret=m_SerialInterface.ADB_SendCmd(strSend,strRev,false,6000);
		//if(!bret || strRev!="")
		if(!bret)
		{ 
		  return false;   
		}
		return true;*/
		
		CString strBatName;
		int iResult;
		CString strDllPathName;

		::GetModuleFileName(NULL, strDllPathName.GetBuffer(_MAX_PATH), _MAX_PATH);
		strDllPathName.ReleaseBuffer();
		 strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
			
		
		//if(iChannel==1 && iModulationType==9)
		strBatName=strDllPathName+"\\SriptFile\\BlueTooth_Nonsignaling_Batch\\Single CH\\BTTX.bat";

		iResult=WinExec(strBatName,SW_HIDE);
		if(iResult>31)
			return true;
		else
			return false;

	}
}
bool  CQualPhone::BT_RX_Test()
{
   
   return true;
}


int CQualPhone::FTM_WCDMA_BER_StopSession()
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_WCDMA_BER_StopSession()");
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_WCDMA_BER_StopSession(m_hResourceContext);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(unsigned char eTFCS_Select,unsigned char aiTFCS_Config[])
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(): eTFCS_Select=%d,aiTFCS_Config=%s",eTFCS_Select,aiTFCS_Config);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(m_hResourceContext,eTFCS_Select,aiTFCS_Config);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_TDSCDMA_BER_StartSession(unsigned long iTimeOut_ms)
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_TDSCDMA_BER_StartSession(): TimeOut_ms=%ld",iTimeOut_ms);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_TDSCDMA_BER_StartSession(m_hResourceContext,iTimeOut_ms);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;

}
int CQualPhone::FTM_TDSCDMA_BER_SetupRMC_DCH(unsigned char iRMC_Type,unsigned char iDL_Slot,unsigned char iUL_Slot,unsigned char iUL_MaxTxPwr,unsigned char iUL_TPC_StepSize)
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_TDSCDMA_BER_SetupRMC_DCH(): iRMC_Type=%d,iDL_Slot=%d,iUL_Slot=%ld,iUL_MaxTxPwr=%d,iUL_TPC_StepSize=%d",
		iRMC_Type,iDL_Slot,iUL_Slot,iUL_MaxTxPwr,iUL_TPC_StepSize);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_TDSCDMA_BER_SetupRMC_DCH(m_hResourceContext,iRMC_Type,iDL_Slot,iUL_Slot,iUL_MaxTxPwr,iUL_TPC_StepSize);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;

}
int CQualPhone::FTM_TDSCDMA_BER_AcquirePilot(unsigned short iChannel )
{
	CString strMsg;

	strMsg.Format("QLIB_FTM_TDSCDMA_BER_AcquirePilot(): iChannel=%d",iChannel);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_TDSCDMA_BER_AcquirePilot(m_hResourceContext,iChannel);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_TDSCDMA_BER_Handover(unsigned char iRMC_Type,unsigned char iDL_Slot,unsigned char iUL_Slot,unsigned char iUL_MaxTxPwr,unsigned char iUL_TPC_StepSize,unsigned short iChannel)
{

	CString strMsg;

	strMsg.Format("QLIB_FTM_TDSCDMA_BER_Handover(): iRMC_Type=%d,iDL_Slot=%d,iUL_Slot=%ld,iUL_MaxTxPwr=%d,iUL_TPC_StepSize=%d,iChannel=%d",
		iRMC_Type,iDL_Slot,iUL_Slot,iUL_MaxTxPwr,iUL_TPC_StepSize,iChannel);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_TDSCDMA_BER_Handover(m_hResourceContext,iRMC_Type,iDL_Slot,iUL_Slot,iUL_MaxTxPwr,iUL_TPC_StepSize,iChannel);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::DIAG_CHANGE_RX_DIVERSITY(unsigned char bSysMode, unsigned char bChainSelection)
{
	CString strMsg;

	strMsg.Format("QLIB_DIAG_CHANGE_RX_DIVERSITY(): bSysMode=%d,bChainSelection=%d",bSysMode,bChainSelection);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_DIAG_CHANGE_RX_DIVERSITY(m_hResourceContext,bSysMode,bChainSelection);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;

}
int CQualPhone::FTM_WCDMA_BER_StartSession(unsigned long iTimeOut_ms)
{
	CString strMsg;

	strMsg.Format("FTM_WCDMA_BER_StartSession(): TimeOut_ms=%ld",iTimeOut_ms);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_WCDMA_BER_StartSession(m_hResourceContext,iTimeOut_ms);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_WCDMA_BER_AcquirePilot(unsigned short  iChannel )
{
	CString strMsg;

	strMsg.Format("FTM_WCDMA_BER_AcquirePilot(): iChannel=%d",iChannel);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_WCDMA_BER_AcquirePilot(m_hResourceContext,iChannel);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_WCDMA_BER_Handover(unsigned char iRMC_Type,
									   unsigned char iUL_MaxTxPwr,
									   unsigned long iUL_DPCH_ScrCode,
									   unsigned char iUL_PCA,
									   unsigned char iUL_TPC_StepSize,
									   unsigned short  iDL_PriCPICH_Scr_Code,
									   unsigned short iDL_ChanCode,
									   unsigned char iBetaC,
									   unsigned char iBetaD,
									   unsigned short iChannel)
{
	CString strMsg;

	strMsg.Format("FTM_WCDMA_BER_Handover(): iRMC_Type=%d,iUL_MaxTxPwr=%d,iUL_DPCH_ScrCode=%ld,iUL_PCA=%d,iUL_TPC_StepSize=%d,iDL_PriCPICH_Scr_Code=%d,iDL_ChanCode=%d,iBetaC=%d,iBetaD=%d,iChannel=%d",
		iRMC_Type,iUL_MaxTxPwr,iUL_DPCH_ScrCode,iUL_PCA,iUL_TPC_StepSize,iDL_PriCPICH_Scr_Code,iDL_ChanCode,iBetaC,iBetaD,iChannel);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_WCDMA_BER_Handover(m_hResourceContext,iRMC_Type,iUL_MaxTxPwr,iUL_DPCH_ScrCode,iUL_PCA,iUL_TPC_StepSize,iDL_PriCPICH_Scr_Code,iDL_ChanCode,iBetaC,iBetaD,iChannel);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_WCDMA_BER_SetupRMC_DCH(unsigned char iRMC_Type,unsigned char iUL_MaxTxPwr,unsigned long iUL_DPCH_ScrCode,unsigned char iUL_PCA,unsigned char iUL_TPC_StepSize,unsigned short iDL_PriCPICH_Scr_Code,unsigned short iDL_ChanCode)
{
	CString strMsg;

	strMsg.Format("FTM_WCDMA_BER_SetupRMC_DCH(): iRMC_Type=%d,iUL_MaxTxPwr=%d,iUL_DPCH_ScrCode=%ld,iUL_PCA=%d,iUL_TPC_StepSize=%d,iDL_PriCPICH_Scr_Code=%d,iDL_ChanCode=%d",
		iRMC_Type,iUL_MaxTxPwr,iUL_DPCH_ScrCode,iUL_PCA,iUL_TPC_StepSize,iDL_PriCPICH_Scr_Code,iDL_ChanCode);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_WCDMA_BER_SetupRMC_DCH(m_hResourceContext,iRMC_Type,iUL_MaxTxPwr,iUL_DPCH_ScrCode,iUL_PCA,iUL_TPC_StepSize,iDL_PriCPICH_Scr_Code,iDL_ChanCode);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_SECOND_CHAIN_TEST_CALL(unsigned char iMode)
{
	CString strMsg;

	strMsg.Format("FTM_SECOND_CHAIN_TEST_CALL(): iMode=%d",iMode);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_SECOND_CHAIN_TEST_CALL(m_hResourceContext,iMode);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_WCDMA_BER_Handover_V2B(unsigned short iChannel)
{
	CString strMsg;

	strMsg.Format("FTM_WCDMA_BER_Handover_V2B(): iChannel=%d",iChannel);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_WCDMA_BER_Handover_V2B(m_hResourceContext,FTM_WCDMA_BER_RMC_Type12_2kpbs,30,0,FTM_WCDMA_BER_PCA_Type_Alg1,FTM_WCDMA_BER_PCA_Size_1dB,0,9,8,15,-60,FTM_WCDMA_BER_N312_s1,FTM_WCDMA_BER_N313_s20,FTM_WCDMA_BER_N315_s1,1,3,iChannel);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}
int CQualPhone::FTM_Init6285()
{
	CString strMsg;
	int ret=0;
	int iKey=111;
	unsigned char iHold=0;
	strMsg.Format("QLIB_ConfigureTimeOut");
	
	ret = QLIB_ConfigureTimeOut(m_hResourceContext, 18, 5000 );

	LogPhoneStartCommand(strMsg);
	if (!ret)
	{
		LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}

	strMsg.Format("QLIB_ConfigureTimeOut");
	LogPhoneStartCommand(strMsg);

	ret = QLIB_IsPhoneConnected(m_hResourceContext);
	if (!ret)
	{
		LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}

	strMsg.Format("QLIB_DIAG_HS_KEY_F");

	
	/*ret = QLIB_DIAG_HS_KEY_F(m_hResourceContext,iKey,iHold);
	if (!ret)
	{
		LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}*/


	strMsg.Format("FTM_SET_COMMAND_CODE():75");
	LogPhoneStartCommand(strMsg);
	ret=QLIB_FTM_SET_COMMAND_CODE(m_hResourceContext,75);
	if (!ret)
	{
		LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_EnterOnlineBeforeFTM_Delay(int IsPreOnlineToFTM,unsigned long iTimeOut_ms)
{
	CString strMsg;
	int iRet=0;

	if (IsPreOnlineToFTM)
	{
		strMsg.Format("QLIB_ConfigureTimeOut():QMSL_Timeout_Delay_ONLINE_FTM");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_ConfigureTimeOut(m_hResourceContext,QMSL_Timeout_Delay_ONLINE_FTM,iTimeOut_ms);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_ConfigureTimeOut():QMSL_Timeout_Delay_ONLINE");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_ConfigureTimeOut(m_hResourceContext,QMSL_Timeout_Delay_ONLINE,iTimeOut_ms);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_DIAG_CONTROL_F():MODE_ONLINE_F");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_DIAG_CONTROL_F(m_hResourceContext,MODE_ONLINE_F);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_ConfigureTimeOut():QMSL_Timeout_Delay_Offline");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_ConfigureTimeOut(m_hResourceContext,QMSL_Timeout_Delay_OFFLINE,iTimeOut_ms);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}
	}
	strMsg.Format("FTM_SET_COMMAND_CODE():75");
	LogPhoneStartCommand(strMsg);
	iRet=QLIB_FTM_SET_COMMAND_CODE(m_hResourceContext,75);
	if (!iRet)
	{
		LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}

	strMsg.Format("QLIB_DIAG_CONTROL_F():MODE_FTM_F");
	LogPhoneStartCommand(strMsg);
	iRet=QLIB_DIAG_CONTROL_F(m_hResourceContext,MODE_FTM_F);
	if (!iRet)
	{
		LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}

	strMsg.Format("QLIB_FTM_SET_MODE_ID():FTM_MODE_ID_CDMA_1X");
	LogPhoneStartCommand(strMsg);
	iRet=QLIB_FTM_SET_MODE_ID(m_hResourceContext,FTM_MODE_ID_CDMA_1X);
	if (!iRet)
	{
		LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}
	Sleep(1000);

	return PHONE_SUCCESS;
}

int CQualPhone::FTM_GSM_StartCall( int isPreOnlineToFTM, 
								   int iChainID,
								   int iFreqMode,
								   unsigned long iTimeOut_ms,
								   unsigned short iChannel, 
								   unsigned char iBand, 
								   unsigned char iTSC, 
								   unsigned char iSlot,
								   unsigned char iMode,
								   unsigned char iPowerLevel,
								   unsigned char  iLoopbackType)
{
	iMode=iFreqMode;

	CString strMsg;
	int iAssBCCHTimes=13,iLoopTimes=16,iStartcall=50;
	int iRet=0;

/*
	strMsg.Format("FTM_SET_COMMAND_CODE():75");
				LogPhoneStartCommand(strMsg);
	iRet=QLIB_FTM_SET_COMMAND_CODE(m_hResourceContext,75);
	if (!iRet)
	{
				LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}

	strMsg.Format("QLIB_ConfigureTimeOut():QMSL_Timeout_Delay_ONLINE_FTM");
				LogPhoneStartCommand(strMsg);
	iRet=QLIB_ConfigureTimeOut(m_hResourceContext,QMSL_Timeout_Delay_ONLINE_FTM,iTimeOut_ms);
	if (!iRet)
	{
				LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}

	if (isPreOnlineToFTM)
	{
		strMsg.Format("QLIB_ConfigureTimeOut():QMSL_Timeout_Delay_ONLINE");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_ConfigureTimeOut(m_hResourceContext,QMSL_Timeout_Delay_ONLINE,iTimeOut_ms);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_DIAG_CONTROL_F():MODE_ONLINE_F");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_DIAG_CONTROL_F(m_hResourceContext,MODE_ONLINE_F);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}
	}

	strMsg.Format("QLIB_ConfigureTimeOut():QMSL_Timeout_Delay_Offline");
	LogPhoneStartCommand(strMsg);
	iRet=QLIB_ConfigureTimeOut(m_hResourceContext,QMSL_Timeout_Delay_OFFLINE,iTimeOut_ms);
	if (!iRet)
	{
		LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}

	strMsg.Format("QLIB_DIAG_CONTROL_F():MODE_FTM_F");
				LogPhoneStartCommand(strMsg);
	iRet=QLIB_DIAG_CONTROL_F(m_hResourceContext,MODE_FTM_F);
	if (!iRet)
	{
				LogPhoneStartCommand(strMsg+"-fail");
		return ERR_QLIB_FUNCTION_FAILED;
	}

	Sleep(1000);*/

    if (iChainID==0)
    {
		strMsg.Format("QLIB_FTM_SET_MODE_ID():FTM_MODE_GSM_BER");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_SET_MODE_ID(m_hResourceContext,FTM_MODE_GSM_BER);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}
    } 
    else
    {
		strMsg.Format("QLIB_FTM_SET_MODE_ID():FTM_MODE_GSM_BER");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_SET_MODE_ID(m_hResourceContext,FTM_MODE_ID_GSM_BER_C2);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}
    }
	

	if (iMode==0)
	{
		/*strMsg.Format("QLIB_FTM_GSM_BER_ReleaseTCH");
				LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_GSM_BER_ReleaseTCH(m_hResourceContext);
		if (!iRet)
		{
				LogPhoneStartCommand(strMsg+"-fail");
		//return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_FTM_GSM_BER_StopSession");
				LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_GSM_BER_StopSession(m_hResourceContext);
		if (!iRet)
		{
				LogPhoneStartCommand(strMsg+"-fail");
		//return ERR_QLIB_FUNCTION_FAILED;
		}*/

				
	
		do{

			strMsg.Format("QLIB_FTM_GSM_BER_StartSession():timeout=%d",iTimeOut_ms);
			LogPhoneStartCommand(strMsg);
			iRet=QLIB_FTM_GSM_BER_StartSession(m_hResourceContext,iTimeOut_ms);
			if (!iRet)
			{
				Sleep(1500);
				strMsg.Format("QLIB_FTM_GSM_BER_StartSession():RetryTimes=%d",iStartcall);
				LogPhoneStartCommand(strMsg);
			}
			else
				break;
			
		}while(--iStartcall>0);

		if(iStartcall==0)
		{
			strMsg.Format("QLIB_FTM_GSM_BER_StartSession fail after retry 15 times!");
			LogPhoneStartCommand(strMsg);
			return ERR_QLIB_FUNCTION_FAILED ;
		}



		do{

			strMsg.Format("QLIB_FTM_GSM_BER_AssignBCCH():iChannel=%d,iBand=%d",iChannel,iBand);
					LogPhoneStartCommand(strMsg);
			iRet=QLIB_FTM_GSM_BER_AssignBCCH(m_hResourceContext,iChannel,iBand);
			if (!iRet)
			{
				Sleep(500);
				strMsg.Format("QLIB_FTM_GSM_BER_AssignBCCH():RetryTimes=%d",iAssBCCHTimes);
					LogPhoneStartCommand(strMsg);
			}
			else
				break;			
		}while(--iAssBCCHTimes>0);

		if(iAssBCCHTimes==0)
		{
			strMsg.Format("Assign BCCH fail after retry 12 times!");
				LogPhoneStartCommand(strMsg);
			return ERR_QLIB_FUNCTION_FAILED ;
		}

		strMsg.Format("QLIB_FTM_GSM_BER_Handover():iChannel=%d,iBand=%d,iTSC=%d,iSlot=%d,iMode=%d,iPowerLevel=%d,iLoopbackType=%d",iChannel,iBand,iTSC,iSlot,iMode,iPowerLevel,iLoopbackType);
		LogPhoneStartCommand(strMsg);
		//iRet=QLIB_FTM_GSM_BER_Handover_NoLoopbackConfig(m_hResourceContext,iChannel,iBand,iTSC,iSlot,iMode,iPowerLevel);
		iRet=QLIB_FTM_GSM_BER_Handover(m_hResourceContext, iChannel, iBand, iTSC, iSlot, iMode, iPowerLevel,iLoopbackType);
		if (!iRet)
		{
					LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;	
		}

		do
		{
			strMsg.Format("QLIB_FTM_GSM_BER_IsTrafficValid()");
					LogPhoneStartCommand(strMsg);
			iRet=QLIB_FTM_GSM_BER_IsTrafficValid(m_hResourceContext); 
			if(iRet==1)
				break;

			Sleep(500);
		}while(iLoopTimes-->0);

		if(iRet!=1)
		{
			strMsg.Format("Qlib Traffic is not valid!");
						LogPhoneStartCommand(strMsg);
	
			return ERR_QLIB_FUNCTION_FAILED;	  
		}
	}
	else if (iMode==1)
	{
		strMsg.Format("QLIB_FTM_GSM_BER_StartSession():1st");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_GSM_BER_StartSession(m_hResourceContext,10000);
		if (!iRet)
		{
			Sleep(2000);

			strMsg.Format("QLIB_FTM_GSM_BER_StartSession():2nd");
			LogPhoneStartCommand(strMsg);
			iRet=QLIB_FTM_GSM_BER_StartSession(m_hResourceContext,10000);
			if (!iRet)
			{
				LogPhoneStartCommand(strMsg+"-fail");
				return ERR_QLIB_FUNCTION_FAILED;
			}
		}

		strMsg.Format("QLIB_FTM_EGPRS_BER_AssignBCCH():iChannel=%d,iBand=%d",iChannel,iBand);
			LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_EGPRS_BER_AssignBCCH(m_hResourceContext,iChannel,iBand);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}

		strMsg.Format("QLIB_FTM_EGPRS_BER_Configure_UL_TBF():iDL_TSC=%d, iDL_TFI=%d, iChannel=%d, iBand=%d, bFirstSlotActive=%d, iFirstSlotNum=%d, bSecondSlotActive=%d,iSecondSlotNum=%d",0,0,iChannel,iBand,1,3,1,4);
			LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_EGPRS_BER_Configure_DL_TBF(m_hResourceContext,0,0,iChannel,iBand,1,3,1,4);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}


		strMsg.Format("QLIB_FTM_EGPRS_BER_Configure_UL_TBF():iUL_TSC=%d, iUSF=%d, iGamma=%d, bFirstSlotActive=%d, iFirstSlotNum=%d, bSecondSlotActive=%d, iSecondSlotNum=%d",0,0,7,1,3,1,4);
			LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_EGPRS_BER_Configure_UL_TBF(m_hResourceContext,0,0,7,1,3,1,4);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}


		strMsg.Format("QLIB_FTM_EGPRS_BER_Establish_SRB_LOOPBACK()");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_EGPRS_BER_Establish_SRB_LOOPBACK(m_hResourceContext);
		if (!iRet)
		{
			LogPhoneStartCommand(strMsg+"-fail");
			return ERR_QLIB_FUNCTION_FAILED;
		}
	}
	else
	{
		strMsg.Format("iBand=%d",iBand);
		LogPhoneStartCommand(strMsg);

		LogTrace(MSG_ERROR,_T(strMsg+",Config iBand error!"));
		return ERR_QLIB_FUNCTION_FAILED;
	}
	
	return PHONE_SUCCESS;
}

int CQualPhone::FTM_GSM_BER_GetRxMetrics(int &iRxlev,int iRetryTimes)
{
	CString strMsg;
	int iRet=0;
	unsigned char RxLev_Full;
	unsigned char RxQual_Full;

	do 
	{
		strMsg.Format("QLIB_FTM_GSM_BER_GetRxMetrics():RetryTimeLeft=%d",iRetryTimes);
		LogPhoneStartCommand(strMsg);
		Sleep(2000);
		iRet=QLIB_FTM_GSM_BER_GetRxMetrics(m_hResourceContext,&RxLev_Full,&RxQual_Full);


	} while (((iRetryTimes-->0)&&(!iRet))||((RxLev_Full==0)&&(iRetryTimes-->0)));

	if (!iRet)
	{
		strMsg.Format("QLIB_FTM_GSM_BER_GetRxMetrics(): fuction fail");
		LogPhoneStartCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}

	iRxlev=RxLev_Full;

	return PHONE_SUCCESS;
}

int CQualPhone::FTM_GSM_EndCall(int nDelay)
{
	CString strMsg;
	bool bRet=FALSE;
		strMsg.Format("FTM_GSM_EndCall(%d)",nDelay);
	LogPhoneStartCommand(strMsg)

	bRet=QLIB_FTM_GSM_BER_ReleaseTCH(m_hResourceContext);
	if (bRet)
	{
		strMsg=_T("QLIB_FTM_GSM_BER_ReleaseTCH() Pass");
		LogPhoneStartCommand(strMsg);	
	} 
	else
	{
		strMsg=_T("QLIB_FTM_GSM_BER_ReleaseTCH() Fail");
		LogPhoneStartCommand(strMsg);			
	}
	Sleep(nDelay);

	bRet=QLIB_FTM_GSM_BER_StopSession(m_hResourceContext);
	if (bRet)
	{
		strMsg=_T("QLIB_FTM_GSM_BER_StopSession() Pass");
		LogPhoneStartCommand(strMsg);	
	} 
	else
	{
		strMsg=_T("QLIB_FTM_GSM_BER_StopSession() Fail");
		LogPhoneStartCommand(strMsg);			
	}

	return PHONE_SUCCESS;
}

int CQualPhone::FTM_EndCall(int iFreqMode)
{
	CString strMsg;
	int iRet=0;

	if(iFreqMode==0)
	{
		Sleep(500);

		strMsg.Format("QLIB_FTM_GSM_BER_ReleaseTCH()");
			LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_GSM_BER_ReleaseTCH(m_hResourceContext);
		if (!iRet)
		{
			strMsg.Format("QLIB_FTM_GSM_BER_ReleaseTCH(): fuction fail");
			LogPhoneStartCommand(strMsg);
		}

		Sleep(500);

		strMsg.Format("QLIB_FTM_GSM_BER_StopSession()");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_GSM_BER_StopSession(m_hResourceContext);
		if (!iRet)
		{
			strMsg.Format("QLIB_FTM_GSM_BER_StopSession(): fuction fail");
			LogPhoneStartCommand(strMsg);
		}
	}
	else if(iFreqMode==1)
	{
		Sleep(500);

		strMsg.Format("QLIB_FTM_EGPRS_BER_Release_All_TBF()");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_EGPRS_BER_Release_All_TBF(m_hResourceContext);
		if (!iRet)
		{
			strMsg.Format("QLIB_FTM_EGPRS_BER_Release_All_TBF(): fuction fail");
			LogPhoneStartCommand(strMsg);
		}

		Sleep(500);

		strMsg.Format("QLIB_FTM_GSM_BER_StopSession()");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_GSM_BER_StopSession(m_hResourceContext);
		if (!iRet)
		{
			strMsg.Format("QLIB_FTM_GSM_BER_StopSession(): fuction fail");
			LogPhoneStartCommand(strMsg);
		}
	}	
	else if(iFreqMode==2)
	{
		Sleep(500);

		strMsg.Format("QLIB_FTM_WCDMA_BER_StopSession()");
		LogPhoneStartCommand(strMsg);
		iRet=QLIB_FTM_WCDMA_BER_StopSession(m_hResourceContext);
		if (!iRet)
		{
			strMsg.Format("QLIB_FTM_WCDMA_BER_StopSession(): fuction fail");
			LogPhoneStartCommand(strMsg);
		}
	}

	if(iRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;
}

int CQualPhone::FTM_CDMA2000_NS_Start(unsigned char eDR_Type,unsigned long iBand_Class,unsigned char bEnableDiversityAGCLog)
{
	CString strMsg;
	double dTurnAroundConstant;
	//param dTurnAroundConstant = cdma turn around constant, -73dBm for BC0, -76 for BC1. Qlib.
	//bool bRet=QLIB_DIAG_FLUSH_BUFFER(m_hResourceContext);
	//bRet=QLIB_FTM_CDMA2000_NS_ClearStatus(m_hResourceContext,true);
	//bRet=QLIB_ConfigureTimeOut(m_hResourceContext,3,5000);

	if (iBand_Class==CDMA_BC0_BAND_ID)
	{
		dTurnAroundConstant=-73;
	}
	else if(iBand_Class==CDMA_BC1_BAND_ID)
	{
		dTurnAroundConstant=-76;
	}
	else
	{
		dTurnAroundConstant=-73;
	}
	strMsg.Format("FTM_CDMA2000_NS_Start(): %d,%.2f,%d",eDR_Type,dTurnAroundConstant,bEnableDiversityAGCLog);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_CDMA2000_NS_Start(m_hResourceContext,eDR_Type,dTurnAroundConstant,bEnableDiversityAGCLog);

	if(bRet)
		return PHONE_SUCCESS;
	else
		return ERR_QLIB_FUNCTION_FAILED;

}
int CQualPhone::FTM_CDMA2000_NS_Stop()
{
	CString strMsg;
	strMsg=_T("FTM_CDMA2000_NS_Stop()");
	LogPhoneStartCommand(strMsg)
		bool bRet=QLIB_FTM_CDMA2000_NS_Stop(m_hResourceContext);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

}
int CQualPhone::FTM_CDMA2000_DEMOD_FCH(unsigned long iRadio_Cfg)
{
	CString strMsg;
	unsigned char iQOF_Mask_ID = 0;
	unsigned char iBypass_LC = 0;
	unsigned char iFrame_Offset = 0;
	unsigned char iSubChan_Gain = 0;
	unsigned long iFPC_Mode = 0;
	unsigned char iInit_Setpt = 0;
	unsigned char iOLC_Params_Target_FER = 0;
	unsigned char iOLC_Params_Min_Setpt = 0;
	unsigned char iOLC_Params_Max_Setpt = 0;
	unsigned char iWalsh = 10;	
	unsigned char iFFPC_Enable = 0; 
	strMsg.Format("FTM_CDMA2000_DEMOD_FCH(): RadioConfig %d",iRadio_Cfg);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_CDMA2000_DEMOD_FCH(m_hResourceContext,iRadio_Cfg,iWalsh,iQOF_Mask_ID,iBypass_LC,iFrame_Offset,iSubChan_Gain,iFFPC_Enable,iFPC_Mode,iInit_Setpt,iOLC_Params_Target_FER,iOLC_Params_Min_Setpt,iOLC_Params_Max_Setpt);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}
int CQualPhone::FTM_CDMA2000_PILOT_ACQ(unsigned long iBand_Class,unsigned short iCDMA_Freq, unsigned long iAcq_Mode)
{
	CString strMsg;
	strMsg.Format("FTM_CDMA2000_PILOT_ACQ(): BC%d,Channel%d,ACQMode%d",iBand_Class,iCDMA_Freq,iAcq_Mode);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_CDMA2000_PILOT_ACQ(m_hResourceContext,iBand_Class,iCDMA_Freq,iAcq_Mode);

	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}
int CQualPhone::FTM_CDMA_2000_HardHandOff(unsigned long iBand_Class,unsigned short iCDMA_Freq)
{
	CString strMsg;
	strMsg.Format("QLIB_FTM_CDMA2000_FTM_FWD_HHO_SC(): BC%d,Channel%d",iBand_Class,iCDMA_Freq);
	LogPhoneStartCommand(strMsg);

	bool bRet=QLIB_FTM_CDMA2000_FTM_FWD_HHO_SC(m_hResourceContext,CCDMABandInfo::GetPhoneBandClassMode(iBand_Class),iCDMA_Freq,FALSE);

	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

}

int CQualPhone::FTM_CDMA2000_DEMOD_SYNC()
{
	CString strMsg;
	strMsg=_T("FTM_CDMA2000_DEMOD_SYNC()");
	LogPhoneStartCommand(strMsg)
		bool bRet=QLIB_FTM_CDMA2000_DEMOD_SYNC(m_hResourceContext);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

}
int CQualPhone::FTM_CDMA2000_NS_SetSER_RCandRS(unsigned long eCurrentCDMA2000_RC,unsigned long eCurrentCDMA2000_DataRate)
{
	CString strMsg;
	strMsg.Format("FTM_CDMA2000_NS_SetSER_RCandRS(): RadioConfig%d,DataRate%d",eCurrentCDMA2000_RC,eCurrentCDMA2000_DataRate);
	LogPhoneStartCommand(strMsg)
		bool bRet =QLIB_FTM_CDMA2000_NS_SetSER_RCandRS(m_hResourceContext,eCurrentCDMA2000_RC,eCurrentCDMA2000_DataRate);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}

int CQualPhone::FTM_CDMA2000_FCH_LOOPBACK()
{
	CString strMsg;
	strMsg.Format("FTM_CDMA2000_FCH_LOOPBACK()");
	LogPhoneStartCommand(strMsg)
	bool bRet= QLIB_FTM_CDMA2000_FCH_LOOPBACK(m_hResourceContext);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}

int CQualPhone::FTM_CDMA2000_MOD_FCH(unsigned long iRadio_Cfg)
{
	CString strMsg;
	strMsg.Format("FTM_CDMA2000_MOD_FCH(): FTM_REV_RC%d",iRadio_Cfg);
	LogPhoneStartCommand(strMsg)
		bool bRet= QLIB_FTM_CDMA2000_MOD_FCH(m_hResourceContext,iRadio_Cfg,0,FTM_CDMA2000_NS_REV_FCH_FULL_RATE,1,0,0);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

}
int CQualPhone::FTM_CDMA2000_NS_Get_FCH_SER_FER(unsigned long iMinimumNumSymbols,unsigned long iMinimumNumFrames,unsigned long *piTotalSymbols,unsigned long *piTotalErrorSymbols,unsigned long *piTotalFrames,unsigned long *piTotalFrameErrors,double *pdSER_Calculated, double *pdFER_Calculated,unsigned long iTimeOut_ms)
{
	CString strMsg;
	bool bRet;

	//bRet=QLIB_FTM_CDMA2000_NS_ClearFER_Status(m_hResourceContext);
	bRet=QLIB_FTM_CDMA2000_NS_Get_FCH_SER_FER(m_hResourceContext,iMinimumNumSymbols,iMinimumNumFrames,piTotalFrameErrors,piTotalErrorSymbols,piTotalFrames,piTotalFrameErrors,pdSER_Calculated,pdFER_Calculated,iTimeOut_ms);
	strMsg.Format("FTM_CDMA2000_NS_Get_FCH_SER_FER(): SymbolsMin %d,FramesMin %d,SymbolsTotal %d,ErrSymbolsTotal %d,FramesTotal %d,ErrFrameTotal %d,SER %.2f, FER %.2f,TimeOut %d ms",iMinimumNumSymbols,iMinimumNumFrames,*piTotalErrorSymbols,*piTotalErrorSymbols,*piTotalFrames,*piTotalFrameErrors,*pdSER_Calculated,*pdFER_Calculated,iTimeOut_ms);
    LogPhoneStartCommand(strMsg)
	if (!bRet)
	{
		LogPhoneStartCommand(strMsg+":Fail");
		return ERR_QLIB_FUNCTION_FAILED;
	} 
	return PHONE_SUCCESS;

}
int CQualPhone::FTM_CDMA2000_CMD_RELEASE()
{
	CString strMsg;
	strMsg=_T("FTM_CDMA2000_CMD_RELEASE()");
	LogPhoneStartCommand(strMsg)
		bool bRet=QLIB_FTM_CDMA2000_CMD_RELEASE(m_hResourceContext);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}

int CQualPhone::DIAG_READ_ESN_F(CString &strESN)
{
	unsigned long iRet[128];
	bool bRet;
	CString strMsg;
	strESN.Format("");
    bRet=QLIB_DIAG_READ_ESN_F(m_hResourceContext,iRet);
	strESN.Format(_T("%x"),iRet[0]);
	strMsg.Format("DIAG_READ_ESN_F(): ESN %s",strESN);
	LogPhoneStartCommand(strMsg)
		if (bRet)
		{
			return PHONE_SUCCESS;
		} 
		else
		{
			return ERR_QLIB_FUNCTION_FAILED;
		}



}

int CQualPhone::FTM_CDMA_BER_Handover(unsigned char eDR_Type,unsigned char bEnableDiversityAGCLog,unsigned long iBand_Class,unsigned short iCDMA_Freq, unsigned long iAcq_Mode,unsigned long iRadio_Cfg)
{
	int iRet;

	iRet=FTM_CDMA2000_NS_Start(eDR_Type,iBand_Class,bEnableDiversityAGCLog);
	if (iRet!=PHONE_SUCCESS)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

	iRet=FTM_CDMA2000_PILOT_ACQ(CCDMABandInfo::GetPhoneBandClassMode(iBand_Class),iCDMA_Freq,iAcq_Mode);
	if (iRet!=PHONE_SUCCESS)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

	iRet=FTM_CDMA2000_DEMOD_SYNC();
	if (iRet!=PHONE_SUCCESS)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

	iRet=FTM_CDMA2000_DEMOD_FCH(iRadio_Cfg);
	if (iRet!=PHONE_SUCCESS)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}


	iRet=FTM_CDMA2000_MOD_FCH(iRadio_Cfg);
	if (iRet!=PHONE_SUCCESS)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

	iRet=FTM_CDMA2000_NS_SetSER_RCandRS(iRadio_Cfg,FTM_CDMA2000_NS_REV_FCH_FULL_RATE);
	if (iRet!=PHONE_SUCCESS)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
	//BOOL b1=QLIB_FTM_CDMA2000_FTM_FWD_HHO_SC(m_hResourceContext,CCDMABandInfo::GetPhoneBandClassMode(iBand_Class),iCDMA_Freq,FALSE);



	//iRet=FTM_CDMA2000_FCH_LOOPBACK();
	//if (iRet!=PHONE_SUCCESS)
	//{
	//	return ERR_QLIB_FUNCTION_FAILED;
	//}

	//iRet=FTM_CDMA2000_NS_Stop();

/*
	if (!b1)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}*/
	if (iRet!=PHONE_SUCCESS)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}

	return PHONE_SUCCESS;

}

int CQualPhone::FTM_CDMA2000_NS_GetRXRESULT_BYPHONE(unsigned long iBand_Class,													
													unsigned char eDR_Type,
													unsigned char bEnableDiversityAGCLog,
													unsigned long eCurrentCDMA2000_RC,
													unsigned long eCurrentCDMA2000_DataRate,
													unsigned long iMinimumNumSymbols,
													unsigned long iMinimumNumFrames,
													unsigned long &iTotalSymbols,
													unsigned long &iTotalErrorSymbols,
													unsigned long &iTotalFrames,
													unsigned long &iTotalFrameErrors,
													double &dSER_Calculated, 
													double &dFER_Calculated,
													unsigned long iTimeOut_ms)
{
	int iRet;

	
		//QLIB_FTM_CDMA2000_NS_ClearStatus(m_hResourceContext,0);
		iRet=FTM_CDMA2000_NS_Start(eDR_Type,iBand_Class,bEnableDiversityAGCLog);
		if (iRet!=PHONE_SUCCESS)
		{
			return ERR_QLIB_FUNCTION_FAILED;
		}
		iRet=FTM_CDMA2000_NS_SetSER_RCandRS(eCurrentCDMA2000_RC,eCurrentCDMA2000_DataRate);
		if (iRet!=PHONE_SUCCESS)
		{
			return ERR_QLIB_FUNCTION_FAILED;
		}		
		Sleep(1000);
		iRet=FTM_CDMA2000_NS_Get_FCH_SER_FER(iMinimumNumSymbols,iMinimumNumFrames,&iTotalSymbols,&iTotalErrorSymbols,&iTotalFrames,&iTotalFrameErrors,&dSER_Calculated, &dFER_Calculated,iTimeOut_ms);
		if (iRet!=PHONE_SUCCESS)
		{
			return ERR_QLIB_FUNCTION_FAILED;
		}

		iRet=FTM_CDMA2000_NS_Stop();
		

	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCDMA_Measure_BER(double * dBER)
{
	CString strMsg;
	bool bRet;
	SE_BER_Status se_ber_stat;
	bRet=QLIB_FTM_SE_BER_Stop_Log(m_hResourceContext);
	strMsg=_T("QLIB_FTM_SE_BER_Stop_Log()");
	LogPhoneStartCommand(strMsg);
	if (!bRet)
		return ERR_QLIB_FUNCTION_FAILED;
	bRet=QLIB_FTM_SE_BER_Start_Log(m_hResourceContext,8,1,0,20,30,LOG_FTM2_FTM_LOG_SE_BER_LB_TYPE_WCDMA_RMC122K,5);
	strMsg.Format("QLIB_FTM_SE_BER_Start_Log() 8,1,0,20,30,RMC_112K,5");
	LogPhoneStartCommand(strMsg);
	if (!bRet)
		return ERR_QLIB_FUNCTION_FAILED;
	Sleep(2000);
	bRet=QLIB_FTM_SE_BER_DoMeasurement(m_hResourceContext,(void*)&se_ber_stat,LOG_FTM2_FTM_LOG_SE_BER_LB_TYPE_WCDMA_RMC122K, 10000, 100);
	strMsg=_T("QLIB_FTM_SE_BER_DoMeasurement RMC_112K,10000,100");
	LogPhoneStartCommand(strMsg);
	if (!bRet)
		return ERR_QLIB_FUNCTION_FAILED;
	bRet=QLIB_FTM_SE_BER_Stop_Log(m_hResourceContext);
	strMsg=_T("QLIB_FTM_SE_BER_Stop_Log()");
	LogPhoneStartCommand(strMsg);
	if (!bRet)
		return ERR_QLIB_FUNCTION_FAILED;
	* dBER=se_ber_stat.ber_stats.BER;
	* dBER/=100;
	return PHONE_SUCCESS;
}

int CQualPhone::FTM_WCDMA_Measure_RXLV(double * dRXPower,int iScaleFactor,double dMinPower)
{
	CString strMsg;
	bool bRet;
	//unsigned short iStatus;
	short iRxAGC;
	double dRxPowerdBm; 
	WCDMA_BER_State pWCDMA_BER_State;

	bRet=QLIB_FTM_WCDMA_BER_GetStatus(m_hResourceContext,(unsigned char*)&pWCDMA_BER_State);
	strMsg.Format("QLIB_FTM_WCDMA_BER_GetStatus()");
	LogPhoneStartCommand(strMsg);
	iRxAGC=pWCDMA_BER_State.oWCDMA_AGC.iRX_AGC;
	if (10==iScaleFactor)
	{
		dRxPowerdBm=iRxAGC/(1024/102.3)+dMinPower+102.3/2;
	}
	else
	{
		dRxPowerdBm=(iRxAGC+512.00)/iScaleFactor+dMinPower;
	}
	
	*dRXPower=dRxPowerdBm;
	if (!bRet)
		return ERR_QLIB_FUNCTION_FAILED;
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCDMA_AGC_START_LOG()
{
	CString strMsg;
	bool bRet;
	bRet=QLIB_FTM_WCDMA_AGC_Start_Log(m_hResourceContext);
	strMsg=_T("QLIB_FTM_WCDMA_AGC_Start_Log()");
	LogPhoneStartCommand(strMsg);
	if(!bRet)
		return ERR_QLIB_FUNCTION_FAILED;
	return PHONE_SUCCESS;
}

int CQualPhone::FTM_WCDMA_AGC_STOP_LOG()
{
	CString strMsg;
	bool bRet;
	bRet=QLIB_FTM_WCDMA_AGC_Stop_Log(m_hResourceContext);
	strMsg=_T("QLIB_FTM_WCDMA_AGC_Stop_Log()");
	LogPhoneStartCommand(strMsg);
	if(!bRet)
		return ERR_QLIB_FUNCTION_FAILED;
	return PHONE_SUCCESS;
}


int CQualPhone::FTM_CDMA2000_EndCall(int nDelay)
{
	CString strMsg;
	strMsg.Format("FTM_CDMA2000_EndCall(%d)",nDelay);
	LogPhoneStartCommand(strMsg)
		bool bRet=QLIB_FTM_CDMA2000_CMD_RELEASE(m_hResourceContext);
	if (bRet)
	{
		strMsg=_T("QLIB_FTM_CDMA2000_CMD_RELEASE() Pass");
		LogPhoneStartCommand(strMsg);	
	} 
	else
	{
		strMsg=_T("QLIB_FTM_CDMA2000_CMD_RELEASE() Fail");
		LogPhoneStartCommand(strMsg);			
	}

	Sleep(nDelay);

	bRet=QLIB_FTM_CDMA2000_NS_Stop(m_hResourceContext);
	if (bRet)
	{
		strMsg=_T("QLIB_FTM_CDMA2000_NS_Stop() Pass");
		LogPhoneStartCommand(strMsg);	
	} 
	else
	{
		strMsg=_T("QLIB_FTM_CDMA2000_NS_Stop() Fail");
		LogPhoneStartCommand(strMsg);			
	}

	return PHONE_SUCCESS;
}
int CQualPhone::FTM_TDSCDMA_BER_RxLevel(unsigned char iRxChain,float* fRxPower)
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned short iStatus=0;
	short iRxAGC=0,iRxPowerdbm=0;

	strMsg=_T("QLIB_FTM_TDSCDMA_BER_RX_LEVEL_REQ()");
	LogPhoneStartCommand(strMsg)

		bRet=QLIB_FTM_TDSCDMA_BER_RX_LEVEL_REQ(m_hResourceContext,iRxChain,&iStatus,&iRxAGC,&iRxPowerdbm);
	if (!bRet||(iStatus==1))
	{
		strMsg.Format("QLIB_FTM_TDSCDMA_BER_RX_LEVEL_REQ() Fail RxChain=%d,Status=%d,RxAGC=%d,RxPowerdbm10=%d",iRxChain,iStatus,iRxAGC,iRxPowerdbm);
		LogPhoneStopCommand(strMsg);	
		return ERR_QLIB_FUNCTION_FAILED;
	} 
	else
	{
		strMsg=_T("QLIB_FTM_TDSCDMA_BER_RX_LEVEL_REQ() Pass");
		LogPhoneStopCommand(strMsg);		
	}
	*fRxPower=(float)iRxPowerdbm/10.0;
	

	return PHONE_SUCCESS;

}
int CQualPhone::FTM_TDSCDMA_EndCall()
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg=_T("FTM_TDSCDMA_EndCall()");
	LogPhoneStartCommand(strMsg)

		bRet=QLIB_FTM_TDSCDMA_BER_DropAll(m_hResourceContext);
	if (bRet)
	{
		strMsg=_T("QLIB_FTM_TDSCDMA_BER_DropAll() Pass");
		LogPhoneStartCommand(strMsg);	
	} 
	else
	{
		strMsg=_T("QLIB_FTM_TDSCDMA_BER_DropAll() Fail");
		LogPhoneStartCommand(strMsg);	
		return ERR_QLIB_FUNCTION_FAILED;
	}
	bRet=QLIB_FTM_TDSCDMA_BER_StopSession(m_hResourceContext);
	if (bRet)
	{
		strMsg=_T("QLIB_FTM_TDSCDMA_BER_StopSession() Pass");
		LogPhoneStartCommand(strMsg);	
	} 
	else
	{
		strMsg=_T("QLIB_FTM_TDSCDMA_BER_StopSession() Fail");
		LogPhoneStartCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}

	return PHONE_SUCCESS;

}
int CQualPhone::FTM_WCDMA_EndCall()
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg=_T("FTM_WCDMA_EndCall()");
	LogPhoneStartCommand(strMsg)

		bRet=QLIB_FTM_WCDMA_BER_StopSession(m_hResourceContext);
	if (bRet)
	{
		strMsg=_T("QLIB_FTM_WCDMA_BER_StopSession() Pass");
		LogPhoneStartCommand(strMsg);	
	} 
	else
	{
		strMsg=_T("QLIB_FTM_WCDMA_BER_StopSession() Fail");
		LogPhoneStartCommand(strMsg);			
	}

	return PHONE_SUCCESS;
}

int CQualPhone::FTM_CDMA2000_NS_GetRxLevel_BYPHONE(unsigned long iBand_Class,unsigned long iChan,double &dRxLevResult,int iDelay)
{
	//unsigned char iStatus=-1;
	//short iRxAGC=-1; 
	//short iRxPowerdBm=-1 ;

	/*CString strMsg;
	strMsg=_T("QLIB_FTM_CDMA2000_NS_GetStatus()");
	LogPhoneStartCommand(strMsg)*/

	//cdmaNsSt=new FTM_CDMA2000_NS_Status_Struct(sizeof(FTM_CDMA2000_NS_Status_Struct));
	FTM_CDMA2000_NS_Status_Struct* cdmaNsSt=(FTM_CDMA2000_NS_Status_Struct*)malloc(sizeof(FTM_CDMA2000_NS_Status_Struct));

	//FTM_CDMA2000_NS_Status_Struct cdmaNsSt;
	memset(cdmaNsSt,0,sizeof(FTM_CDMA2000_NS_Status_Struct));
	Sleep(iDelay);
	
	bool bRet=QLIB_FTM_CDMA2000_NS_GetStatus(m_hResourceContext,cdmaNsSt);
	//bool bRet=QLIB_FTM_CDMA2000_RX_LEVEL_REQ(m_hResourceContext,0,&iStatus,&iRxAGC,&iRxPowerdBm);
	if (bRet)
	{
		dRxLevResult=(cdmaNsSt->oCDMA2000_AGC_C0.rx_agc+512.00)/10-115;
		
		QLIB_FTM_CDMA2000_NS_ClearStatus(m_hResourceContext,1);
		free(cdmaNsSt);
		return PHONE_SUCCESS;	
	} 
	else
	{
		//strMsg.Format("QLIB_FTM_CDMA2000_NS_GetStatus() fail");
		//LogPhoneStartCommand(strMsg)
		QLIB_StopLogging(m_hResourceContext);
		free(cdmaNsSt);
		return ERR_QLIB_FUNCTION_FAILED;
	}
}

int  CQualPhone::FTM_SET_PA_DAC_INPUT  ( unsigned short  iDACinput)
{
	CString strMsg;
	strMsg=_T("FTM_SET_PA_DAC_INPUT()");
	LogPhoneStartCommand(strMsg)
		bool bRet=QLIB_FTM_SET_PA_DAC_INPUT(m_hResourceContext,iDACinput);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}
int  CQualPhone:: FTM_TX_CS_SWEEP  (  
  unsigned char  iListSize,  
  short *  aiI_DC_Correction,  
  short *  aiQ_DC_Correction,  
  unsigned short *  aiSegmentLength,  
  unsigned short *  piStatus 
 )
{
	
	


	CString strMsg;
	strMsg=_T("FTM_TX_CS_SWEEP()");
	LogPhoneStartCommand(strMsg)

		bool bRet=QLIB_FTM_TX_CS_SWEEP (m_hResourceContext,iListSize,aiI_DC_Correction,aiQ_DC_Correction,aiSegmentLength,piStatus);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}
int CQualPhone::FTM_SET_TX_FRAME_MATRIX(unsigned char  iSlotNum,  
  unsigned char  iTurnSlotOn,  
  unsigned short  iPwrLevel,  
  unsigned char  iModScheme )

{
	CString strMsg;
	strMsg=_T("FTM_SET_TX_FRAME_MATRIX()");
	LogPhoneStartCommand(strMsg)

		bool bRet=QLIB_FTM_SET_TX_FRAME_MATRIX(m_hResourceContext,iSlotNum,iTurnSlotOn,iPwrLevel,iModScheme );
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}
int CQualPhone::FTM_SET_PATH_DELAY( short *  piDelay )
{
	CString strMsg;
	strMsg=_T("FTM_SET_TX_FRAME_MATRIX()");
	LogPhoneStartCommand(strMsg)

	bool bRet=QLIB_FTM_SET_PATH_DELAY(m_hResourceContext,piDelay);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}
int CQualPhone::RFCAL_GSM_Tx_Delay_Cal_Results(unsigned short  iNvModeId,  
  unsigned short  iPolarDelayPathValue,  
  void *  pDelay_Cal_NVItem,  
  unsigned char  bCachedByNVManager 
 )  
{
	CString strMsg;
	strMsg=_T("QLIB_RFCAL_GSM_Tx_Delay_Cal_Results");
	LogPhoneStartCommand(strMsg)

	bool bRet=QLIB_RFCAL_GSM_Tx_Delay_Cal_Results(m_hResourceContext, iNvModeId,iPolarDelayPathValue,pDelay_Cal_NVItem,bCachedByNVManager);
	if (bRet)
	{
		return PHONE_SUCCESS;
	} 
	else
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
}
int CQualPhone::UploadQCNFile(char* sFileName,char* sSPC,unsigned char bAutoRestor,unsigned char bAutoReset,unsigned char bAllowEsnMismatch,unsigned char bIgnorePhoneMode)
{
	CString strMsg;
	
	strMsg.Format("QLIB_UploadQcnFile(%s,%s,%d,%d,%d,%d)",sFileName,sSPC,bAutoRestor,bAutoReset,bAllowEsnMismatch,bIgnorePhoneMode);
	LogPhoneStartCommand(strMsg);
	int iStatus=QLIB_UploadQcnFile(m_hResourceContext,sFileName,sSPC,bAutoRestor,bAutoReset,bAllowEsnMismatch,bIgnorePhoneMode);
	if (iStatus==false)
	{
		return ERR_QLIB_FUNCTION_FAILED
	}
	return PHONE_SUCCESS;

}
void CQualPhone::ConfigureCallBacks( EfsDirCB pEfsDirCallback, generalSWDownloadCB pGeneralSwDownloadCB, asyncMessageCB pAsyncMessageCB )
{
	CString strMsg;
	QLIB_ConfigureCallBacks(m_hResourceContext,pEfsDirCallback,pGeneralSwDownloadCB,pAsyncMessageCB);
	strMsg.Format("QLIB_ConfigureCallBacks");
	LogPhoneStartCommand(strMsg);
	return;
}

unsigned char CQualPhone::generalDownloadEvent(unsigned char* pGeneralSwDownloadEvent_union)
{
	CString strMsg;
	generalSwDownloadEvent_struct* _pEvent= (generalSwDownloadEvent_struct*)pGeneralSwDownloadEvent_union;
	
	switch (_pEvent->eEventType)
	{

	case SWD_nvBackupEvent:
		//	uses struct nvBackupEvent_struct;
		strMsg.Format("NV Upload error %d",_pEvent->uEventData.nvBackupEvent.error);
		LogPhoneStopCommand(strMsg);
		strMsg.Format("NV Upload Percent Completed %d",_pEvent->uEventData.nvBackupEvent.percentCompleted);
		LogPhoneStopCommand(strMsg);
		strMsg.Format("NV Upload status %ld",_pEvent->uEventData.nvBackupEvent.status);
		LogPhoneStopCommand(strMsg);
		strMsg.Format("NV Upload nvItem %d",_pEvent->uEventData.nvBackupEvent.nvItem);
		LogPhoneStopCommand(strMsg);

		break;

	default:
		//printf("\n Event: Default");
		break;
	}	

	return 0;
	
}
int CQualPhone::TDLTE_Cal_Setup(int iBand,int iChannel,int iconfig)
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long iStatus=0;
	strMsg=_T("QLIB_FTM_LTE_NS_START()");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_NS_START(m_hResourceContext,&iStatus);
	if ((!bRet)||(0!=iStatus&&13!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_START() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	strMsg.Format("QLIB_FTM_LTE_NS_ACQ Band=%d,EARFCN=%d",iBand,iChannel);
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_NS_ACQ(m_hResourceContext,iBand,iChannel,&iStatus);
	if ((!bRet)||(0!=iStatus&&13!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_ACQ() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	strMsg=_T("QLIB_FTM_LTE_NS_TDD_CONFIG()");
	LogPhoneStartCommand(strMsg);
	
	bRet=QLIB_FTM_LTE_NS_TDD_CONFIG(m_hResourceContext,1,4,&iStatus);
		if ((!bRet)||(0!=iStatus&&13!=iStatus))
		{
			strMsg.Format("Failed:QLIB_FTM_LTE_NS_TDD_CONFIG() Status=%d",iStatus);
			LogPhoneStopCommand(strMsg);
			//return ERR_QLIB_FUNCTION_FAILED;
		}
	
	strMsg=_T("QLIB_FTM_LTE_NS_START_DP()");
	LogPhoneStartCommand(strMsg);
	if (1==iconfig)
	{
		bRet=QLIB_FTM_LTE_NS_START_DP(m_hResourceContext,14,1,30,1,2,&iStatus);
	} 
	else
	{
		bRet=QLIB_FTM_LTE_NS_START_DP(m_hResourceContext,43690,1,30,3,2,&iStatus);
	}
	if ((!bRet)||(0!=iStatus&&13!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_START_DP() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}	

	return PHONE_SUCCESS;
}
int CQualPhone::LTE_GET_BLER(unsigned int iRxSamples,double *dBLER)
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long iStatus=0,iTBR=0,iTBE=0,iTP=0;
	int iTimeOut=50;
	QLIB_LTE_PDSCH_BLER_Start_Log(m_hResourceContext);
	strMsg=_T("QLIB_FTM_LTE_NS_RESET_DL_BLER_REPORT");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_NS_RESET_DL_BLER_REPORT(m_hResourceContext,&iStatus);
	if ((!bRet)||(0!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_RESET_DL_BLER_REPORT() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	do 
	{
		
		Sleep(100);
		strMsg=_T("QLIB_FTM_LTE_NS_GET_DL_BLER_REPORT");
		LogPhoneStartCommand(strMsg);
		bRet=QLIB_FTM_LTE_NS_GET_DL_BLER_REPORT(m_hResourceContext,&iTBR,&iTBE,&iTP,&iStatus);
		if ((!bRet)||(0!=iStatus))
		{
			strMsg.Format("Failed:QLIB_FTM_LTE_NS_GET_DL_BLER_REPORT() Status=%d",iStatus);
			LogPhoneStopCommand(strMsg);
			return ERR_QLIB_FUNCTION_FAILED;
		}
		strMsg.Format("QLIB_FTM_LTE_NS_GET_DL_BLER_REPORT() TBR=%d,TBE=%d,TP=%d",iTBR,iTBE,iTP);
		LogPhoneStopCommand(strMsg);
	} while (--iTimeOut>0&&iTBR<iRxSamples);
	QLIB_LTE_PDSCH_BLER_Stop_Log(m_hResourceContext);
	if (iTBR<iRxSamples)
	{
		strMsg=_T("Failed:QLIB_FTM_LTE_NS_GET_DL_BLER_REPORT() Timeout");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	*dBLER=(double)iTBE/((double)iTBR)*100;
	return PHONE_SUCCESS;

}
int CQualPhone::LTE_NS_CONFIG_UL_POWER(unsigned char iTxChain,unsigned char iTxPwrCtrlMode,short iTxLevel)
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long iStatus=0;
	strMsg.Format("QLIB_FTM_LTE_NS_CONFIG_UL_POWER,txchain=%d,tpcm=%d,txlevel=%d",iTxChain,iTxPwrCtrlMode,iTxLevel);
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_NS_CONFIG_UL_POWER(m_hResourceContext,iTxChain,iTxPwrCtrlMode,iTxLevel,&iStatus);
	if ((!bRet)||(0!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_CONFIG_UL_POWER() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;

}
INT CQualPhone::LTE_NS_IS_CONNECTED()
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long iStatus=0;
	strMsg=_T("QLIB_FTM_LTE_NS_IS_CONNECTED()");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_NS_IS_CONNECTED(m_hResourceContext,&iStatus);
	if ((!bRet)||(0!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_IS_CONNECTED() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;

}
int CQualPhone::LTE_NS_STOP()
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long iStatus=0;
	strMsg=_T("QLIB_FTM_LTE_NS_STOP()");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_NS_STOP(m_hResourceContext,&iStatus);
	if ((!bRet)||(0!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_STOP() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;

}
int CQualPhone::LTE_NS_IDLE()
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long iStatus=0;
	strMsg=_T("QLIB_FTM_LTE_NS_IDLE()");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_NS_IDLE(m_hResourceContext,&iStatus);
	if ((!bRet)||(0!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_IDLE() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;

}
int CQualPhone::LTE_NS_CONFIG_UL_WAVEFORM(unsigned char iConfigOverride, unsigned char iTxChain, unsigned char iStartRB, unsigned char iNumRB, unsigned char iMCS)
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long iStatus=0;
	strMsg.Format("QLIB_FTM_LTE_NS_CONFIG_UL_WAVEFORM,CO=%d,TC=%d,SRB=%d,NRB=%d,MCS=%d",iConfigOverride,iTxChain,iStartRB,iNumRB,iMCS);
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_NS_CONFIG_UL_WAVEFORM(m_hResourceContext,iConfigOverride,iTxChain,iStartRB,iNumRB,iMCS,&iStatus);
	if ((!bRet)||(0!=iStatus))
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_NS_CONFIG_UL_WAVEFORM() Status=%d",iStatus);
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;

}
int CQualPhone::FTM_LTE_SET_TX_MOD_TYPE(unsigned long iModType)
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("FTM_LTE_SET_TX_MOD_TYPE,iModType=%d",iModType);
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_SET_TX_MODULATION_TYPE(m_hResourceContext,iModType);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_SET_TX_MODULATION_TYPE()");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_LTE_SET_TX_WAVEFORM(unsigned char  iTxWaveform,unsigned char  inumRBsPUSCH,unsigned char  inumRBsPUCCH,unsigned char  iPUSCHStartRBIndex)
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("FTM_LTE_SET_TX_WAVEFORM");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_LTE_SET_TX_WAVEFORM(m_hResourceContext,iTxWaveform,inumRBsPUSCH,inumRBsPUCCH,iPUSCHStartRBIndex);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_LTE_SET_TX_WAVEFORM");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GEN6_START()
{
	CString strMsg;
	int iRetry=10;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_START");
	LogPhoneStartCommand(strMsg);
	do 
	{
		bRet=QLIB_FTM_WLAN_GEN6_START(m_hResourceContext,3660);
		if (bRet)
		{
			break;
		}
	} while (0<iRetry--);
	
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_START");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GEN6_STOP()
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_STOP");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_STOP(m_hResourceContext);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_STOP");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GEN6_SET_CHANNEL(int chan)
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_SET_CHANNEL");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_SET_CHANNEL_V2(m_hResourceContext,chan,0);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_SET_CHANNEL");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GEN6_ENABLE_TX()
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_ENABLE_TX");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_ENABLE_CHAINS(m_hResourceContext,6);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_ENABLE_TX");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GEN6_ENABLE_RX()
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_ENABLE_RX");
	LogPhoneStartCommand(strMsg);
	
	bRet=QLIB_FTM_WLAN_GEN6_GET_UNICAST_MAC_PKT_RSSI_CONF(m_hResourceContext,0);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_GET_UNICAST_MAC_PKT_RSSI_CONF");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	bRet=QLIB_FTM_WLAN_GEN6_ENABLE_CHAINS(m_hResourceContext,4);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_ENABLE_RX");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}

	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GEN6_SET_FRAME(int iPayloadSize,int iRate,int iPreamble)
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_SET_TX_FRAME");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_SET_TX_FRAME_V2(m_hResourceContext,0,iPayloadSize,2,165,200,1,iRate,iPreamble);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_SET_TX_FRAME");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GEN6_SET_POWER(double dPower)
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_CLOSE_TPC_LOOP_V2");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_CLOSE_TPC_LOOP_V2(m_hResourceContext,1);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_CLOSE_TPC_LOOP_V2");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	strMsg.Format("QLIB_FTM_WLAN_GEN6_SET_CLOSED_LOOP_POWER");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_SET_CLOSED_LOOP_POWER(m_hResourceContext,dPower);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_SET_CLOSED_LOOP_POWER");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;

}
int CQualPhone::FTM_WCN_GEN6_TXSTART()
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_TX_PKT_START");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_TX_PKT_START_STOP(m_hResourceContext,1);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_TX_PKT_START");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;

}
int CQualPhone::FTM_WCN_GEN6_TXSTOP()
{
	CString strMsg;
	bool bRet=FALSE;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_TX_PKT_STOP");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_TX_PKT_START_STOP(m_hResourceContext,0);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_TX_PKT_STOP");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GEN6_SET_RX_DISABLE(int iRate)
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long mask=0;
	switch (iRate)
	{
	case 3:
		mask=6;
		break;
	case 14:
		mask=5;
			break;
	case 30:
		mask=5;
			break;
	default:
		mask=0;
	}
	strMsg.Format("QLIB_FTM_WLAN_GEN6_SET_RX_DISABLE_MODE");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_SET_RX_DISABLE_MODE_V2(m_hResourceContext,mask);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_SET_RX_DISABLE_MODE");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;

}
int CQualPhone::FTM_WCN_GEN6_GET_RX_RSSI(short* rssiVals)
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned short chain=0;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_GET_RX_RSSI_VAL");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_GET_RX_RSSI_VAL(m_hResourceContext,rssiVals,&chain);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_GET_RX_RSSI_VAL");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	return PHONE_SUCCESS;
}
int CQualPhone::FTM_WCN_GET_PER(unsigned long count,double *dPER)
{
	CString strMsg;
	bool bRet=FALSE;
	unsigned long currentcount=0,maccount=0,errorcount=0;
	int timeout=50;
	*dPER=1;
	strMsg.Format("QLIB_FTM_WLAN_GEN6_RESET_RX_PACKET_STATISTICS");
	LogPhoneStartCommand(strMsg);
	bRet=QLIB_FTM_WLAN_GEN6_RESET_RX_PACKET_STATISTICS(m_hResourceContext);
	if (!bRet)
	{
		strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_RESET_RX_PACKET_STATISTICS");
		LogPhoneStopCommand(strMsg);
		return ERR_QLIB_FUNCTION_FAILED;
	}
	do 
	{
		strMsg.Format("QLIB_FTM_WLAN_GEN6_RESET_RX_PACKET_STATISTICS");
		LogPhoneStartCommand(strMsg);
		bRet=QLIB_FTM_WLAN_GEN6_GET_RX_PACKET_COUNTS(m_hResourceContext,&currentcount,&maccount,&errorcount);
		if (!bRet)
		{
			strMsg.Format("Failed:QLIB_FTM_WLAN_GEN6_RESET_RX_PACKET_STATISTICS");
			LogPhoneStopCommand(strMsg);
			return ERR_QLIB_FUNCTION_FAILED;
		}
		Sleep(300);
	} while (0<timeout--&&currentcount<count);
	if (0>=timeout||0==currentcount)
	{
		return ERR_QLIB_FUNCTION_FAILED;
	}
	*dPER=(double )errorcount/(double) currentcount;
	return PHONE_SUCCESS;

}