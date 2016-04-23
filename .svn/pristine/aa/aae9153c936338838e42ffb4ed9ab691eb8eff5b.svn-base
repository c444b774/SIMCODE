#include "stdafx.h"
#include "CDMATXRXCal.h"
RF_IMPLEMENT_DYNCREATE(CCDMATXRXCal)

CCDMATXRXCal::CCDMATXRXCal()
{
	m_mapClassFunc[_T("CDMACalMainFunc")]=&CCDMATXRXCal::CCDMATXRXCalMainFunc;
	m_mapClassFunc[_T("TXLIN_CalFunc")]=&CCDMATXRXCal::CCDMATXRXCalTX_LIN_CalFunc;
    m_mapClassFunc[_T("TXLIMComp_Cal")]=&CCDMATXRXCal::CCDMATXRXCalTX_LIMComPen_CalFunc;
	m_mapClassFunc[_T("RXCalFunc")]=&CCDMATXRXCal::CCDMATXRXCalRXCalFunc;
    
}

CCDMATXRXCal::~CCDMATXRXCal()
{
	
}

bool CCDMATXRXCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CCDMATXRXCal::Handle()
{
	if(!DoProcess())
	{
		m_pPhone->FTM_SET_TX_ON(false);
        m_pPhone->CloseComport();
		m_pFunWCDMACalDev->Deivce_Exit();
		return false;
	}


	return true;
}
bool CCDMATXRXCal::GetChannelPower_PDM(int iPARange,int iPDM,double dExpectedPwr,double & dMeasuredPwr)
{
	  CString strMsg;
	  int iErrorcode;

		if((iErrorcode=m_pPhone->FTM_SET_PA_RANGE(iPARange))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("Se tPA Range Fail");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
					

		if((iErrorcode=m_pPhone->FTM_SET_PDM(2,iPDM))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("Set PDM Fail");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetMaxPower(dExpectedPwr))
			{
				LogTrace(MSG_ERROR,"Set TestDeivce Max power fail");
				CalFailLog(_T("_"),_T("_"),WCDMACAL_SETMAXPOW,"Set TestDeivce Max power fail");
				return false;
					  
			}

				if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMAFetchCPRResult(5,dMeasuredPwr))
		    {
				LogTrace(MSG_ERROR,"Fetch CDMA Channel power fail");
				CalFailLog(_T("_"),_T("_"),CDMACAL_FETCHCHPWR,"Fetch CDMA Channel power fail");
				return false;
					  
			}
				return true;
}
bool CCDMATXRXCal::CalculateLimPDM(int iExpectPDMNum,double dExpectPower,int iPDMSize,IntVtr & vtrLimPDMList)
{
   CString strMsg;
   double dSlope,dCalPower,dCalPDM;
   int iCalPDM,iExPDM;
   for(int i=1;i<m_refChanTxLim.iNumMeasurement;++i)
   {
      if(m_refChanTxLim.aiTxMeasuredPower[i-1]>=dExpectPower && m_refChanTxLim.aiTxMeasuredPower[i]<=dExpectPower)
	  {
		  dSlope=(m_refChanTxLim.aiTxMeasuredPower[i-1]-m_refChanTxLim.aiTxMeasuredPower[i])/(m_refChanTxLim.aiTxAGC[i-1]-m_refChanTxLim.aiTxAGC[i]);
		  dCalPower=m_refChanTxLim.aiTxMeasuredPower[i]-dSlope*m_refChanTxLim.aiTxAGC[i];
          dCalPDM=(dExpectPower-dCalPower)/dSlope;
          iCalPDM=dCalPDM+0.5;
		  strMsg.Format("TXLimPower=%.2f TXLimPDM=%d",dExpectPower,iCalPDM);
		  LogTrace(MSG_MID,strMsg)
		  break;

	  }
   }
   strMsg="TX lim PDM list:";
   for(int i=0;i<iExpectPDMNum;++i)
   {
	   iExPDM=iCalPDM-iPDMSize*iExpectPDMNum/2+iPDMSize*i;
	   vtrLimPDMList.push_back(iExPDM);
	   strMsg+=CStr::IntToStr(iExPDM)+", ";
   }

    LogTrace(MSG_MID,strMsg)


   return true;
}

bool CCDMATXRXCal::SetCDMACALLOSS()
{
   CString strMsg;
     double dLoss;
	m_vCableLoss.clear();
    for(int i=0;i<3;i++)
	{
      if(!m_LossFinder.GetCDMALoss(m_strCurrBand,i,dLoss))
	  {
		  strMsg.Format("CDMA Get Loss Band=%s ,ChannelType=%d Fail",m_strCurrBand,i);
          LogTrace(MSG_ERROR,strMsg);
		  CalFailLog(_T("_"),_T("_"),1001,strMsg);
		  return false;
	  }
	  m_vCableLoss.push_back(dLoss);
	}


      
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSetLoss(m_iCurrBand,m_vCableLoss))
	   {
			LogTrace(MSG_ERROR,"Set Cableloss device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
			return false;
		  
	   }
        



	return  true;

}
bool CCDMATXRXCal::CCDMATXRXCalRXCalFunc()
{
   CString strMsg;
   int iErrorcode;
   double  dUlMHz,dDLMhz;
   unsigned short uiDVGAList[128];
   unsigned short uiLNAList[128];
   unsigned char  ucCount=128;
   short iConvertAGC;
   

   	QMSL_CDMA_RxFreq_Measurement_struct aRX_Measured;
	QMSL_CDMA_MeasuredChannels_struct  aRX_MeasuredChannels;
	QMSL_CDMA_NVChannels_struct  aRX_NV_Channels;
	QMSL_CDMA_Rx_DVGA_LNA_Cal_NV_Result aRX_DVGA_LNA_Cal_NV;

	aRX_MeasuredChannels.iNumMeasuredChannels=m_vRXCalCHList.size();
	aRX_MeasuredChannels.iRefChannel=m_iRefCH;
	aRX_Measured.iPath=m_iRXPath;
	aRX_Measured.iNumMeasuredPowerModes=2;
	aRX_Measured.iNumMeasured_LNA_States=m_vRXOffsetPower.size()-1;
	for(int i=0;i<m_vRXOffsetPower.size()-1;++i)
	aRX_Measured.aiLNA_States[i]=i;
	for(int i=0;i<m_vRXCalCHList.size();++i)
	{
		aRX_MeasuredChannels.aiMeasuredChannels[i]=m_vRXCalCHList[i];
		aRX_NV_Channels.aiNVChannels[i]=m_vRXCalCHList[i];
	}

       if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(m_iRXPath))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
     if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iCDMAIDMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("SET_MODE_ID Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	  if((iErrorcode=m_pPhone->FTM_SET_MODE(CCDMABandInfo::GetPhoneMode(m_iCurrBand)))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Band Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	  for(int iCHIndex=0;iCHIndex<m_vRXCalCHList.size();++iCHIndex)
	{
		    strMsg.Format("RX Freq Comp :Band=%s Channel=%d",m_strCurrBand,m_vRXCalCHList[iCHIndex]);
			LogTrace(MSG_MID,strMsg);
			 dUlMHz=CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_vRXCalCHList[iCHIndex],0);
			 dDLMhz=CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_vRXCalCHList[iCHIndex],1);

	    if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iCDMAIDMode))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
				if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_vRXCalCHList[iCHIndex]))!=PHONE_SUCCESS)
				{ 
					strMsg.Format("Set Channel Fail!");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				}

				if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
				{ 
					strMsg.Format("Set TX OFF Fail!");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				}
				 



				   
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSetNormalSig(dUlMHz,dDLMhz,0,-80))
		   {
				LogTrace(MSG_ERROR,"Set Normal CDMA200 signal fail");
				CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Set Normal CDMA200 signal fail");
				return false;
			  
		   }

        if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPowe(m_vRXOffsetPower[0]))
		   {
				LogTrace(MSG_ERROR,"Set  CDMA200 DL power fail");
				CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set  CDMA200 DL power fail");
				return false;
			  
		   }

		if(iCHIndex==0)
			Sleep(1000);

		short sDVGAAGC=-512 + 10*(m_vRXOffsetPower[0]+m_dDyRange);
		
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
			  if(iConvertAGC>m_vRXOffsetUpLimit[i] || iConvertAGC<m_vRXOffsetLowLimit[i])
			 {
				strMsg.Format("DVGA offset[%d]=%d Limit=[%.2f,%.2f] Fail!",i,iConvertAGC,m_vRXOffsetLowLimit[i],m_vRXOffsetUpLimit[i]);
				LogTrace(MSG_ERROR,strMsg)
                CalFailLog(_T("_"),_T("_"),CDMACAL_FETCHCHPWR,strMsg);
				return false;
			 }
			  else
			  {
				  strMsg.Format("DVGA offset[%d]=%d Limit=[%.2f,%.2f]",i,iConvertAGC,m_vRXOffsetLowLimit[i],m_vRXOffsetUpLimit[i]);
				 LogTrace(MSG_MID,strMsg);
			  }

			  aRX_Measured.aiDVGA_Measured[iCHIndex][i]=iConvertAGC;
			
		 }

		 


		for(int iRXIndex=1;iRXIndex<m_vRXOffsetPower.size();++iRXIndex)
		{
			
			short sDVGAAGC=-512 + 10*(m_vRXOffsetPower[iRXIndex]+m_dDyRange);

			 if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPowe(m_vRXOffsetPower[iRXIndex]))
		   {
				LogTrace(MSG_ERROR,"Set  CDMA200 DL power fail");
				CalFailLog(_T("_"),_T("_"),CDMACAL_SETDLPOW,"Set  CDMA200 DL power fail");
				return false;
			  
		   }

			 if((iErrorcode=m_pPhone->FTM_CDMA_API2_CALIBRATE_LNA(m_iRXPath,sDVGAAGC,iRXIndex-1,&ucCount,uiLNAList))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_CDMA_API2_CALIBRATE_DVGA Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}

		    for(int i=0;i<ucCount;++i)
			{
				 
				if(uiLNAList[i] & 0x8000)  //if it is minus 
                iConvertAGC=0-(0xffff-uiLNAList[i]);
				else
				iConvertAGC=uiLNAList[i];
				 if(iConvertAGC>m_vRXOffsetUpLimit[iRXIndex*ucCount+i] || iConvertAGC<m_vRXOffsetLowLimit[iRXIndex*ucCount+i])
			 {
				strMsg.Format("LNA%d offset[%d]=%d Limit=[%.2f,%.2f] Fail!",iRXIndex-1,i,iConvertAGC,m_vRXOffsetUpLimit[iRXIndex*ucCount+i],m_vRXOffsetLowLimit[iRXIndex*ucCount+i]);
				LogTrace(MSG_ERROR,strMsg)
				CalFailLog(_T("_"),_T("_"),CDMACAL_FETCHCHPWR,strMsg);
				return false;
			 }
			  else
			  {
				 strMsg.Format("LNA%d offset[%d]=%d Limit=[%.2f,%.2f]",iRXIndex-1,i,iConvertAGC,m_vRXOffsetUpLimit[iRXIndex*ucCount+i],m_vRXOffsetLowLimit[iRXIndex*ucCount+i]);
				 LogTrace(MSG_MID,strMsg);
			  }

			 aRX_Measured.aiLNA_Measured[iCHIndex][iRXIndex-1][i]=iConvertAGC;
			}

		  
			
		}




	}

	if((iErrorcode=m_pPhone->RFCAL_CDMA_RxCal_Results(m_iNVModeID,1,1,&aRX_Measured,&aRX_MeasuredChannels,&aRX_NV_Channels,&aRX_DVGA_LNA_Cal_NV,1,1))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("RFCAL_CDMA_RxCal_Results Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
	
	strMsg.Format("RX DVGA and LNA Offset NV Value");
	LogTrace(MSG_MID,strMsg);
	
	strMsg.Format("RefChannel DVGA offset=%d",aRX_DVGA_LNA_Cal_NV.aDVGA.iDVGAOffset);
	LogTrace(MSG_MID,strMsg);
	for(int iLNARangeIndex=0;iLNARangeIndex<aRX_Measured.iNumMeasured_LNA_States;++iLNARangeIndex)
	{
      strMsg.Format("RefChannel LNA%d offset=%d",iLNARangeIndex,aRX_DVGA_LNA_Cal_NV.aLNA[iLNARangeIndex].iLNAOffset);
	  LogTrace(MSG_MID,strMsg);
	}

	for(int iCHIndex=0;iCHIndex<m_vRXCalCHList.size();++iCHIndex)
	{
		for(int iNumPMMode=0;iNumPMMode<2;++iNumPMMode)
		{
			strMsg.Format("Channel= %d DVGAOffsetVsFreq[%d]=%d",m_vRXCalCHList[iCHIndex],iNumPMMode,aRX_DVGA_LNA_Cal_NV.aDVGAvsFreq.iDVGAOffsetVsFreqItem[iCHIndex][iNumPMMode]);
			LogTrace(MSG_MID,strMsg);
		}
       for(int iLNAIndex=0;iLNAIndex<aRX_Measured.iNumMeasured_LNA_States;++iLNAIndex)
	   {
           for(int iNumPMMode=0;iNumPMMode<2;++iNumPMMode)
		   {
			strMsg.Format("Channel= %d LNA%d offset [%d]=%d",m_vRXCalCHList[iCHIndex],iLNAIndex,iNumPMMode,aRX_DVGA_LNA_Cal_NV.aLNAvsFreq[iLNAIndex].iLNAOffsetVsFreqItem[iCHIndex][iNumPMMode]);
		    LogTrace(MSG_MID,strMsg);
		   }
	   }
     
	}
	
     
	CalPassLog(m_strCurrBand,CStr::IntToStr(m_iRefCH),"RX_DVGA_LNA Calibration PASS")
	return true;
}
bool CCDMATXRXCal::CCDMATXRXCalMainFunc()
{
    switch(m_iCurrBand)
	{
	case CDMA_BC0_BAND_ID:

        m_iNVModeID=100;
		break;
	case CDMA_BC1_BAND_ID:

        m_iNVModeID=101;
		break;
	default:
		break;
	
	}
    if(!SetCDMACALLOSS())
		return false;
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CCDMATXRXCal::CCDMATXRXCalTX_LIMComPen_CalFunc()
{
    CString strMsg;
	int iErrorcode;
    IntVtr iTXLimPDMList;
	double dUlMHz,dDLMhz;
	double dChannelPower;

	int iTxMeasToNVMapping[4]={0,1,2,3};     

	QMSL_CDMA_TxLimVsFreq_struct  aTx_LimVsFreqMeasured={0};
	QMSL_CDMA_Tx_LimVsFreq_NV_struct aTx_LimVsFreq_NV_Result={0};  
	
	QMSL_CDMA_TxLinVsFreq_struct aTx_Measured_Power={0};
	QMSL_CDMA_Tx_LinVsFreq_Cal_NV_Result_struct aTx_LinVsFreq_NV_Result={0};
	
	QMSL_CDMA_MeasuredChannels_struct aTx_MeasuredChannels={0};
	QMSL_CDMA_NVChannels_struct aTx_NV_Channels={0};
    
	aTx_MeasuredChannels.iNumMeasuredChannels=m_vTXCalCHList.size();
	for(int i=0;i<m_vTXCalCHList.size();++i)
	{ 
      aTx_MeasuredChannels.aiMeasuredChannels[i]=m_vTXCalCHList[i];
	  aTx_MeasuredChannels.iRefChannel=m_iRefCH;
	  aTx_NV_Channels.aiNVChannels[i]=m_vTXCalCHList[i];  
	}

     
     CalculateLimPDM(19,m_dTXLimPower,m_iTXLimPDMSize,iTXLimPDMList);
	 aTx_Measured_Power.iNumMeasuredTxGainStates=m_vPARange.size();
	 aTx_Measured_Power.iTxCompType=0;
	 aTx_Measured_Power.a2ndTxCompHasMeas[0]=1;
	 aTx_Measured_Power.a2ndTxCompHasMeas[1]=0;
	 aTx_Measured_Power.a2ndTxCompHasMeas[2]=0;
	 aTx_Measured_Power.a2ndTxCompHasMeas[3]=0;
	 aTx_Measured_Power.a2ndTxCompPDM[0]=149;
	 aTx_Measured_Power.a2ndTxCompPDM[1]=0;
	 aTx_Measured_Power.a2ndTxCompPDM[2]=0;
	 aTx_Measured_Power.a2ndTxCompPDM[3]=0;

     aTx_LimVsFreqMeasured.oRefChMeas.iNumMeasurement=m_refChanTxLim.iNumMeasurement;
	 for(int i=0;i<m_vPARange.size();++i)
	 {
       aTx_Measured_Power.aiTxMeasToNVMapping[i]=iTxMeasToNVMapping[i];
	 }
	 for(int i=0;i<m_refChanTxLim.iNumMeasurement;++i)
	 {
       aTx_LimVsFreqMeasured.oRefChMeas.aiTxAGC[i]=m_refChanTxLim.aiTxAGC[i];
	   aTx_LimVsFreqMeasured.oRefChMeas.aiTxMeasuredHDET[i]=m_refChanTxLim.aiTxMeasuredHDET[i];
	   aTx_LimVsFreqMeasured.oRefChMeas.aiTxMeasuredPower[i]=m_refChanTxLim.aiTxMeasuredPower[i];
	 }
     
      if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(m_iRXPath))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
     if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iCDMAIDMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("SET_MODE_ID Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	  if((iErrorcode=m_pPhone->FTM_SET_MODE(CCDMABandInfo::GetPhoneMode(m_iCurrBand)))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Band Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
     if((iErrorcode=m_pPhone->FTM_CDMA_CW_WAVEFORM())!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set WCDMA waveform Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	  

	 //Loop for channel list
	  for(int iChIndex=0;iChIndex<m_vTXCalCHList.size();++iChIndex)
	  {
		   dUlMHz=CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_vTXCalCHList[iChIndex],0);
		   dDLMhz=CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_vTXCalCHList[iChIndex],1);
                 if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iCDMAIDMode))!=PHONE_SUCCESS)
					{ 
						strMsg.Format("SET_MODE_ID Fail!");
						PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
					}
				if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_vTXCalCHList[iChIndex]))!=PHONE_SUCCESS)
				{ 
					strMsg.Format("Set Channel Fail!");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				}

				if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iCDMAIDMode))!=PHONE_SUCCESS)
					{ 
						strMsg.Format("SET_MODE_ID Fail!");
						PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
					}

				if((iErrorcode=m_pPhone->FTM_SET_TX_ON())!=PHONE_SUCCESS)
				{ 
					strMsg.Format("Set TX ON Fail!");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				}

               if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSetNormalSig(dUlMHz,dDLMhz,0,-80))
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
		        //TX ComPen
				for(int iPRIndex=0;iPRIndex<m_vPARange.size();++iPRIndex)
				{
					if(!GetChannelPower_PDM(m_vPARange[iPRIndex],m_vTXCompPDM[iPRIndex],m_vTXCompPower[iPRIndex],dChannelPower))
						return false;
                  	aTx_Measured_Power.aiTxMeasuredPower[iPRIndex][iChIndex]=dChannelPower; 
					strMsg.Format("TX linCompen :Band=%s,Channel=%d,PARange=%d,PDM=%d,Power=%.2f",m_strCurrBand,m_vTXCalCHList[iChIndex],m_vPARange[iPRIndex],m_vTXCompPDM[iPRIndex],dChannelPower);
                    LogTrace(MSG_MID,strMsg) 

                    if(dChannelPower>dChannelPower+m_vTXComPowerUpLimit[iPRIndex] || dChannelPower<dChannelPower+m_vTXComPowerLowLimit[iPRIndex])
					{
						strMsg.Format("Channel power is not in [%.2f,%.2f]!",dChannelPower+m_vTXComPowerLowLimit[iPRIndex],dChannelPower+m_vTXComPowerUpLimit[iPRIndex]);
						LogTrace(MSG_ERROR,strMsg) 
						return false;
					}
				}
                    
					//TX lim Compen
					aTx_LimVsFreqMeasured.iNumOfTxLimMeasurement[iChIndex]=19;

                    for(int j=0;j<19;j++)
					{
	       				aTx_LimVsFreqMeasured.aiTxMeasuredPDM[iChIndex][j]=iTXLimPDMList[j];
	          		    aTx_LimVsFreqMeasured.aiTxMeasuredPower[iChIndex][j]=25;		
						aTx_LimVsFreqMeasured.aiTxMeasuredHDET[iChIndex][j]=200;	
					}

					if(!GetChannelPower_PDM(m_vPARange[m_vPARange.size()-1],iTXLimPDMList[9],m_dTXLimPower+2,dChannelPower))
						return false;
					int iHDETValueSum=0;
					unsigned short piADC_value;
				   for(int k=0;k<5;k++)
					{
						if((iErrorcode=m_pPhone->FTM_GET_ADC_VAL(m_iHDET_ADC_Channel,&piADC_value))!=PHONE_SUCCESS)
							{ 
								strMsg.Format("FTM_GET_ADC_VAL Fail");
								PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
							}
									
						iHDETValueSum=iHDETValueSum+piADC_value;
					}
				   aTx_LimVsFreqMeasured.aiTxMeasuredHDET[iChIndex][9]=iHDETValueSum/5;
                   aTx_LimVsFreqMeasured.aiTxMeasuredPower[iChIndex][9]=dChannelPower;
				   strMsg.Format("TX lim Compen :Band=%s,Channel=%d,PARange=%d,PDM=%d,Power=%.2f HDET=%d ",m_strCurrBand,m_vTXCalCHList[iChIndex],m_vPARange[m_vPARange.size()-1],iTXLimPDMList[9],dChannelPower,iHDETValueSum/5);
                   LogTrace(MSG_MID,strMsg)  
                   if(dChannelPower>=m_dTXLimPower)
				   {
                     for(int j=8;j>=0;j--)
					 {
                       	if(!GetChannelPower_PDM(m_vPARange[m_vPARange.size()-1],iTXLimPDMList[j],m_dTXLimPower+2,dChannelPower))
						return false;
                        aTx_LimVsFreqMeasured.aiTxMeasuredPower[iChIndex][j]=dChannelPower;
                       iHDETValueSum=0;
                        for(int k=0;k<5;k++)
						{
							if((iErrorcode=m_pPhone->FTM_GET_ADC_VAL(m_iHDET_ADC_Channel,&piADC_value))!=PHONE_SUCCESS)
								{ 
									strMsg.Format("FTM_GET_ADC_VAL Fail");
									PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
								}
										
							iHDETValueSum=iHDETValueSum+piADC_value;
						}
                        aTx_LimVsFreqMeasured.aiTxMeasuredHDET[iChIndex][j]=iHDETValueSum/5;
                        strMsg.Format("TX lim Compen :Band=%s,Channel=%d,PARange=%d,PDM=%d,Power=%.2f HDET=%d ",m_strCurrBand,m_vTXCalCHList[iChIndex],m_vPARange[m_vPARange.size()-1],iTXLimPDMList[j],dChannelPower,iHDETValueSum/5);
						LogTrace(MSG_MID,strMsg)  
						if(dChannelPower<m_dTXLimPower)
							break;

					 }
				   }
				   else
				   {
					   for(int j=10;j<=18;j++)
					 {
                       	if(!GetChannelPower_PDM(m_vPARange[m_vPARange.size()-1],iTXLimPDMList[j],m_dTXLimPower+2,dChannelPower))
						return false;
                        aTx_LimVsFreqMeasured.aiTxMeasuredPower[iChIndex][j]=dChannelPower;
                       iHDETValueSum=0;
                        for(int k=0;k<5;k++)
						{
							if((iErrorcode=m_pPhone->FTM_GET_ADC_VAL(m_iHDET_ADC_Channel,&piADC_value))!=PHONE_SUCCESS)
								{ 
									strMsg.Format("FTM_GET_ADC_VAL Fail");
									PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
								}
										
							iHDETValueSum=iHDETValueSum+piADC_value;
						}
                        aTx_LimVsFreqMeasured.aiTxMeasuredHDET[iChIndex][j]=iHDETValueSum/5;
                        strMsg.Format("TX lim Compen :Band=%s,Channel=%d,PARange=%d,PDM=%d,Power=%.2f HDET=%d ",m_strCurrBand,m_vTXCalCHList[iChIndex],m_vPARange[m_vPARange.size()-1],iTXLimPDMList[j],dChannelPower,iHDETValueSum/5);
						LogTrace(MSG_MID,strMsg)  
						if(dChannelPower>m_dTXLimPower)
							break;

					 }

				   }
					if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
					{ 
						strMsg.Format("Set TX ON Fail!");
						PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
					}

				} 
             
   
				

	if((iErrorcode=m_pPhone->RFCAL_CDMA_Tx_LinVsFreq_Results(m_iNVModeID,&aTx_Measured_Power,&aTx_MeasuredChannels,&aTx_NV_Channels,10,0,&aTx_LinVsFreq_NV_Result,1,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_Tx_LinVsFreq_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	strMsg="TX Lin Compen NV Value:";
	LogTrace(MSG_MID,strMsg)  
	for(int i=0;i<m_vPARange.size();++i)
	{
		for(int j=0;j<m_vTXCalCHList.size();++j)
		{
			strMsg.Format("PA Range=%d Channel=%d TXLin_CompenNV_Value=%d",m_vPARange[i],m_vTXCalCHList[j],aTx_LinVsFreq_NV_Result.aTx_FreqComp[i].aiTxCompValue[j]);
			LogTrace(MSG_MID,strMsg)  
		}
	  		
	}

    if((iErrorcode=m_pPhone->RFCAL_CDMA_Tx_LimVsFreq_Results(m_iNVModeID,m_dTXLimPower,&aTx_LimVsFreqMeasured,&aTx_MeasuredChannels,&aTx_NV_Channels,&aTx_LimVsFreq_NV_Result,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_Tx_LimVsFreq_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	strMsg.Format("TX Lim Compen NV Value:OutPower at RefHDET =%.2f , Expected PDM at RefHDET=%d Expected HDET =%d",aTx_LimVsFreq_NV_Result.adTxMaxPower[8],aTx_LimVsFreq_NV_Result.aiExpectedTxAGCatMaxPower[8],aTx_LimVsFreq_NV_Result.aiExpectedHDETatMaxPower[8]);
	LogTrace(MSG_MID,strMsg)  
	
	for(int i=0;i<m_vTXCalCHList.size();++i)
		{
			strMsg.Format("Channel=%d TXLim_CompenNV_Value=%d",m_vTXCalCHList[i],aTx_LimVsFreq_NV_Result.aiLimVsFreq[i]);
			LogTrace(MSG_MID,strMsg)  
		}

   
	  		

    CalPassLog(m_strCurrBand,CStr::IntToStr(m_iRefCH),"TXLinCompen Calibration PASS");

	return true;
}

bool CCDMATXRXCal::CCDMATXRXCalTX_LIN_CalFunc()
{
	 
	CString strMsg;
	int iErrorcode;
	int aiExtrapolated[4]={0,0,0,0};
	int iExtrapolation_PDM_StepSize[4]={0,0,3,3};
	int iHeadRoomPDMCountList[4]={0,0,0,0};
	int iTxMeasToNVMapping[4]={0,1,2,3}; 
    int iPDMNum=0,iTimeOut=0;
	double stepPower=0.0;
	unsigned short usHDETValue;
    DblVtr dMeasuredPowerList;

	double dUlMHz,dDLMhz;
    //iDLChannel=CCDMABandInfo::GetDLChannel(m_iCurrBand,m_iChannel);
    dUlMHz=CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_iRefCH,0);
	dDLMhz=CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_iRefCH,1);
    
    QMSL_CDMA_TxLin_BetaScaling_struct  aTx_Measured;
	QMSL_CDMA_TxLin_BetaScaling_Result_struct aTx_Result;
	memset(&aTx_Measured,0,sizeof(aTx_Measured));
	memset(&aTx_Result,0,sizeof(aTx_Result));
	memset(&m_refChanTxLim,0,sizeof(m_refChanTxLim));
	m_vTXCompPDM.clear();
     
	 aTx_Measured.iNumMeasuredTxGainStates=m_vPARange.size();
	 
	 aTx_Measured.iDo_Not_Extrapolate_Lower_Powers=0;
	 aTx_Measured.iEnh_Linearizer_0_NV=1;
	 aTx_Measured.iHDET_MaxLim=4095;
	 aTx_Measured.iNV_Resolution=10;
	 aTx_Measured.iSkip_NonMonotonic_Items=0;
	 aTx_Measured.iSortingOrder=0;
	 aTx_Measured.iSortNVTxLin=0;
	 aTx_Measured.iTxMeasIndexUsedForHDET=m_vPARange.size()-1;
	 aTx_Measured.iUMTS_TxAGC_PDM_Max=127;
	 aTx_Measured.iUse_HDET_V2=1;
	 aTx_Measured.i_TxAGC_PDM_MinGain=0;
	 aTx_Measured.HDET_OffsetPower_dBm=m_dTXLimPower-3;
	 aTx_Measured.HDET_SpanPower_dBm=m_dTXLimPower+5;	
	 int iHighestStartPdm=*(m_vStartPDM.end()-1);
	 int iHighestStopPdm=*(m_vStopPDM.end()-1);
	 int iHighestStepSize=*(m_vStepSize.end()-1);
	 m_refChanTxLim.iNumMeasurement=(iHighestStartPdm-iHighestStopPdm)/iHighestStepSize+1;  
    
	 strMsg.Format("TXLinCal Band=%s  Channel = %d ",m_strCurrBand,m_iRefCH);
	 LogTrace(MSG_MID,strMsg)
	 strMsg.Format("HDET_MaxLim=4095,NV_Resolution=10,Skip_NonMonotonic_Items=1,TxAGC_PDM_Max=127,HDET_OffsetPower_dBm=20,HDET_SpanPower_dBm=28");
	 LogTrace(MSG_MID,strMsg)
     
     strMsg.Format("PA Range List: "); 
	 for(IntItr itrP=m_vPARange.begin();itrP!=m_vPARange.end();++itrP)
	 {
		 strMsg+=","+CStr::IntToStr(*itrP);   
	 }
     LogTrace(MSG_MID,strMsg)

		  strMsg.Format("Step Size List: "); 
	 for(IntItr itrP=m_vStepSize.begin();itrP!=m_vStepSize.end();++itrP)
	 {
		 strMsg+=","+CStr::IntToStr(*itrP);   
	 }
     LogTrace(MSG_MID,strMsg)
	 strMsg.Format("Start Power List: "); 
	 for(DblVtrItr itrP=m_vTargetPower.begin();itrP!=m_vTargetPower.end();++itrP)
	 {
		 strMsg+=","+CStr::FloatToStr(*itrP);   
	 }
     LogTrace(MSG_MID,strMsg)
     strMsg.Format("Stop Power List: "); 
	 for(DblVtrItr itrP=m_vStopPower.begin();itrP!=m_vStopPower.end();++itrP)
	 {
		 strMsg+=","+CStr::FloatToStr(*itrP);   
	 }
     LogTrace(MSG_MID,strMsg)

	  strMsg.Format("Start PDM List: "); 
	 for(IntItr itrP=m_vStartPDM.begin();itrP!=m_vStartPDM.end();++itrP)
	 {
		 strMsg+=","+CStr::IntToStr(*itrP);   
	 }
     LogTrace(MSG_MID,strMsg)

	  strMsg.Format("Stop PDM List: "); 
	 for(IntItr itrP=m_vStopPDM.begin();itrP!=m_vStopPDM.end();++itrP)
	 {
		 strMsg+=","+CStr::IntToStr(*itrP);   
	 }
     LogTrace(MSG_MID,strMsg)

		 //For Calibration

	  if((iErrorcode=m_pPhone->FTM_SET_CALIBRATION_STATE())!=PHONE_SUCCESS)
	{ 
		strMsg.Format("SET_CALIBRATION_STATE Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

      if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iCDMAIDMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("SET_MODE_ID Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	  if((iErrorcode=m_pPhone->FTM_SET_MODE(CCDMABandInfo::GetPhoneMode(m_iCurrBand)))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Band Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	  
      if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(m_iRXPath))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_SECONDARY_CHAIN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	  
	  if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_iRefCH))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Channel Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	  if((iErrorcode=m_pPhone->FTM_CDMA_CW_WAVEFORM())!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set WCDMA waveform Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	  if((iErrorcode=m_pPhone->FTM_SET_TX_ON())!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set TX ON Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}


	    if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSetNormalSig(dUlMHz,dDLMhz,0,-80))
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
      
	  
        
		for(int iLoopIndex=0;iLoopIndex<m_vPARange.size();++iLoopIndex)
	  {
        aTx_Measured.adMaxPower[iLoopIndex]=m_vTargetPower[iLoopIndex];
		aTx_Measured.adMinPower[iLoopIndex]=m_vStopPower[iLoopIndex];
		aTx_Measured.aiExtrapolatedMaxPower[iLoopIndex]=aiExtrapolated[iLoopIndex];
		aTx_Measured.aiExtrapolatedMinPower[iLoopIndex]=aiExtrapolated[iLoopIndex];
		aTx_Measured.aiExtrapolation_PDM_StepSize[iLoopIndex]=iExtrapolation_PDM_StepSize[iLoopIndex];
		aTx_Measured.aiHeadRoomPDMCountList[iLoopIndex]=iHeadRoomPDMCountList[iLoopIndex];
		aTx_Measured.aiTxMeasToNVMapping[iLoopIndex]=iTxMeasToNVMapping[iLoopIndex];
		aTx_Measured.aiTxSweepStepSize[iLoopIndex]=m_vStepSize[iLoopIndex];

		iPDMNum=(m_vStartPDM[iLoopIndex]-m_vStopPDM[iLoopIndex])/m_vStepSize[iLoopIndex]+1;
		//aTx_Measured.iTotalNVItems=iPDMNum;
        aTx_Measured.iTotalNVItems=64;
		aTx_Measured.iNumTxPowerMeasurementsPerGainState[iLoopIndex]=iPDMNum; 
        iTimeOut=5000+iPDMNum*20;
		stepPower=-(m_vTargetPower[iLoopIndex]-m_vStopPower[iLoopIndex])/iPDMNum;  
        strMsg.Format("Step Power=%.2f",stepPower);
        LogTrace(MSG_MID,strMsg)
        
        if((iErrorcode=m_pPhone->FTM_SET_PA_RANGE(m_vPARange[iLoopIndex]))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Se tPA Range Fail");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		

		  if((iErrorcode=m_pPhone->FTM_SET_PDM(2,m_vStartPDM[iLoopIndex]))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Set PDM Fail");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}	
        
        
	  	if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetMaxPower(m_vExpectPower[iLoopIndex]))
	   {
			LogTrace(MSG_ERROR,"Set TestDeivce Max power fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_SETMAXPOW,"Set TestDeivce Max power fail");
			return false;
		  
	   }

		if((iErrorcode=m_pPhone->FTM_CONFIGURE_TX_SWEEP_CAL(20,5))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("CONFIGURE_TX_SWEEP_CAL Fail");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}	
		if((iErrorcode=m_pPhone->FTM_SET_TX_SWEEP_STEP_SIZE(m_vStepSize[iLoopIndex]))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("SET_TX_SWEEP_STEP_SIZE Fail");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}	

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSetupWTDP(iPDMNum,iTimeOut,stepPower,m_vExpectPower[iLoopIndex],dUlMHz))
	   {
			LogTrace(MSG_ERROR,"Set CDMA Dynamic range power fail");
			CalFailLog(_T("_"),_T("_"),CDMACAL_SETCDTP,"Set CDMA Dynamic range power fail");
			return false;
		  
	   }
       LogTrace(MSG_MID,"Start QLIB_FTM_TX_SWEEP_CAL!")
      // Sleep(300);
       if((iErrorcode=m_pPhone->FTM_TX_SWEEP_CAL())!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Start TX_SWEEP_CAL Fail");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}

	   if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMAFetchCTDPResults(dMeasuredPowerList))
	   {
			LogTrace(MSG_ERROR,"Fethch WTDP Results fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_FETCHRESULTS,"Fethch WTDP Results fail");
			return false;  
	   }

	    if(dMeasuredPowerList[0]<m_vTargetPower[iLoopIndex])
	   {
		   strMsg.Format("Band=%s Channel=%d PARange=%d PDM=%d Power=%.2f not reach target power=%.2f",m_strCurrBand,m_iRefCH,m_vPARange[iLoopIndex],m_vStartPDM[iLoopIndex],dMeasuredPowerList[0],m_vTargetPower[iLoopIndex]);
	       LogTrace(MSG_ERROR,strMsg)
		   return false;

	   }
	 
        if((iErrorcode=m_pPhone->FTM_TX_SWEEP_CAL(false))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Stop TX_SWEEP_CAL Fail");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
	   strMsg.Format("TXLinTable: Band=%s Channel=%d",m_strCurrBand,m_iRefCH);
	   LogTrace(MSG_MID,strMsg)
	  
       for(int i=0;i<iPDMNum;++i)
	   {
	      if(iLoopIndex==m_vPARange.size()-1)
		  {
		   if((iErrorcode=m_pPhone->FTM_GET_HDET_FROM_TX_SWEEP_CAL(i,&usHDETValue))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_GET_HDET_FROM_TX_SWEEP_CAL Fail");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			aTx_Measured.aiTxHDET[i]=usHDETValue;
			m_refChanTxLim.aiTxMeasuredHDET[i]=usHDETValue;
			m_refChanTxLim.iNumMeasurement=iPDMNum;
            strMsg.Format("PA Range=%d PDM=%d Power=%.2f HDET=%d",m_vPARange[iLoopIndex],m_vStartPDM[iLoopIndex]-m_vStepSize[iLoopIndex]*i,dMeasuredPowerList[i],aTx_Measured.aiTxHDET[i]);
			LogTrace(MSG_MID,strMsg)
		  }
		  else
		  {
			 strMsg.Format("PA Range=%d PDM=%d Power=%.2f",m_vPARange[iLoopIndex],m_vStartPDM[iLoopIndex]-m_vStepSize[iLoopIndex]*i,dMeasuredPowerList[i]);
			 LogTrace(MSG_MID,strMsg)
		  }

			  if(i==iPDMNum-1)
			   {
			    
				  if(dMeasuredPowerList[i]>m_vStopPower[iLoopIndex])
				   {
					   strMsg.Format("Band=%s Channel=%d PARange=%d PDM=%d Power=%.2f not reach Min power=%.2f",m_strCurrBand,m_iRefCH,m_vPARange[iLoopIndex],m_vStartPDM[iLoopIndex]-m_vStepSize[iLoopIndex]*i,dMeasuredPowerList[i],m_vStopPower[iLoopIndex]);
					   LogTrace(MSG_ERROR,strMsg)
					   return false;
				   }
			   }
         aTx_Measured.aiTxLinPower[iLoopIndex][i]=dMeasuredPowerList[i];
         aTx_Measured.aiTxLinPDM[iLoopIndex][i]=m_vStartPDM[iLoopIndex]-m_vStepSize[iLoopIndex]*i;

			 if(iLoopIndex==m_vPARange.size()-1)
			 { 
			   m_refChanTxLim.aiTxAGC[i]=m_vStartPDM[iLoopIndex]-m_vStepSize[iLoopIndex]*i;
			   m_refChanTxLim.aiTxMeasuredPower[i]=dMeasuredPowerList[i]; 

			 }

		 if(i>=1)
		 {
            if(dMeasuredPowerList[i-1]>=m_vTXCompPower[iLoopIndex] && dMeasuredPowerList[i]<=m_vTXCompPower[iLoopIndex])
			{
				double dSlope=(dMeasuredPowerList[i-1]-dMeasuredPowerList[i])/(aTx_Measured.aiTxLinPDM[iLoopIndex][i-1]-aTx_Measured.aiTxLinPDM[iLoopIndex][i]);
			    int    iTempPDM=0.5+(m_vTXCompPower[iLoopIndex]-dMeasuredPowerList[i]+dSlope*aTx_Measured.aiTxLinPDM[iLoopIndex][i])/dSlope;
				m_vTXCompPDM.push_back(iTempPDM);
			}
		 }

          
	   }        

	 }

    if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set TX OFF Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}

	if((iErrorcode=m_pPhone->RFCAL_CDMA_TxLinCal_BetaScaling_Results(m_iNVModeID,&aTx_Measured,&aTx_Result,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_CDMA_TxLinCal_BetaScaling_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	

	 strMsg.Format("TXLinTableNVItem: Band=%s Channel=%d",m_strCurrBand,m_iRefCH);
	 LogTrace(MSG_MID,strMsg)
   /* for(int iPAIndex=0;iPAIndex<m_vPARange.size();++iPAIndex)
	{
		int iPDMValue;
		int iPowerAGC;
        for(int iPDMIndex=0;iPDMIndex<QMSL_NV_MANAGER_CDMA_BETA_SCALING_NV_SIZE;++iPDMIndex)
		{
		  iPDMValue=aTx_Result.aTx_GainState[iPAIndex].aiPDM[iPDMIndex];
          iPowerAGC=aTx_Result.aTx_GainState[iPAIndex].aiPower[iPDMIndex];
		  strMsg.Format("PA Range=%d PDM=%d Power=%d",m_vPARange[iPAIndex],iPDMValue,iPowerAGC);
		  LogTrace(MSG_MID,strMsg)
		}
	}*/
	 strMsg.Format("HDET vs AGC Table: Band=%s Channel=%d",m_strCurrBand,m_iRefCH);
	 LogTrace(MSG_MID,strMsg)
	for(int iHDETIndex=0;iHDETIndex<QMSL_NV_MANAGER_HDET_VS_AGC_NV_SIZE;++iHDETIndex)
	{
		
       strMsg.Format("Power=%.2f HDET=%d",aTx_Result.aHDET_vs_AGC.adTxPowerLevel[iHDETIndex],aTx_Result.aHDET_vs_AGC.aHDET_vs_AGC[iHDETIndex]);

	   if(aTx_Result.aHDET_vs_AGC.aHDET_vs_AGC[iHDETIndex] <100)
		{
           strMsg.Format("HDET Value not Correct,Decrease the Start PDM value!");  
		   LogTrace(MSG_FATAL,strMsg)
		   return false;
		}
	   LogTrace(MSG_MID,strMsg)
	}
     
	strMsg.Format("End TXLin Calibration!");
	LogTrace(MSG_MID,strMsg)

	 CalPassLog(m_strCurrBand,CStr::IntToStr(m_iRefCH),"TXLin Calibration PASS");

	return true;
}

 bool CCDMATXRXCal::InitData(
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

	 	

	  itrFind=pcSettingMap->find(_T("DynamicRange"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'DynamicRange'  default is 115");
		  m_dDyRange=115;
	 }
	 else
	 {
		 m_dDyRange=CStr::StrToFloat(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("UseTXRXCal"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'UseTXRXCal' from ini file!.default is false ");
		 m_bIsUseTXRXCAL=false;
	 }
	 else
	 {
		 m_bIsUseTXRXCAL=CStr::StrToBool(itrFind->second);
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

	 if(m_iRXPath==0)
		 m_iCDMAIDMode=0;
	 else
        m_iCDMAIDMode=3;

	   itrFind=pcSettingMap->find(_T("HDET_ADC_CH"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'HDET_ADC_CH' from ini file!.default use 25");
		 m_iHDET_ADC_Channel=25;
	 }
	 else
	 {
		 m_iHDET_ADC_Channel=CStr::StrToInt(itrFind->second);
	 }

	 
	  itrFind=pcSettingMap->find(_T("TXlimPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TXlimPower' from ini file!.default use 23");
		 m_dTXLimPower=25;
	 }
	 else
	 {
		 m_dTXLimPower=CStr::StrToFloat(itrFind->second);
	 }

	 
	  
	  itrFind=pcSettingMap->find(_T("TXlimPDMSize"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TXlimPDMSize' from ini file!.default use 1");
		 m_iTXLimPDMSize=1;
	 }
	 else
	 {
		 m_iTXLimPDMSize=CStr::StrToInt(itrFind->second);
	 }



	 itrFind=pcSettingMap->find(_T("Band"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'Band' from ini file!");
		 return false;
	 }
	 else
	 {
		 m_iCurrBand=CStr::StrToInt(itrFind->second);
		 m_strCurrBand="CDMA"+itrFind->second;
	 }

	  itrFind=pcSettingMap->find(_T("RefChannel"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RefChannel' from ini file!");
		 return false;
	 }
	 else
	 {
		 m_iRefCH=CStr::StrToInt(itrFind->second);
	 }

	   itrFind=pcSettingMap->find(_T("StepSize"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'StepSize' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vStepSize,strVtr);
	 }

	 itrFind=pcSettingMap->find(_T("PARangeList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'PARangeList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vPARange,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("TargetpowerList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'TargetpowerList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vTargetPower,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("StoppowerList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'StoppowerList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vStopPower,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("StartPDMList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'StartPDMList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vStartPDM,strVtr);
	 }

	 itrFind=pcSettingMap->find(_T("StopPDMList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'StopPDMList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vStopPDM,strVtr);
	 }

    
  

     

	  itrFind=pcSettingMap->find(_T("ExpectPowerList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'ExpectPowerList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vExpectPower,strVtr);
	 }

	   itrFind=pcSettingMap->find(_T("TXCalCHList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'TXCalCHList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vTXCalCHList,strVtr);
	 }


	 itrFind=pcSettingMap->find(_T("RXCalCHList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RXCalCHList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vRXCalCHList,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("TXComPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'TXComPower' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vTXCompPower,strVtr);
	 }

	   itrFind=pcSettingMap->find(_T("RXOffsetPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RXOffsetPower' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vRXOffsetPower,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("TXComPwrUpLmt"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'TXComPwrUpLmt' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vTXComPowerUpLimit,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("TXComPwrLowLmt"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'TXComPwrLowLmt' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vTXComPowerLowLimit,strVtr);
	 }


	  itrFind=pcSettingMap->find(_T("RXOffsetLowLmt"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RXOffsetLowLmt' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vRXOffsetLowLimit,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("RXOffsetUpLmt"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RXOffsetUpLmt' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
	     CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vRXOffsetUpLimit,strVtr);
	 }
  

	 InitData();
	 return true;
 }

 bool CCDMATXRXCal::InitData()
 {
	 m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	 return true;
 }