#include "stdafx.h"
#include "GSMTXCal.h"
RF_IMPLEMENT_DYNCREATE(CGSMTXCal)

CGSMTXCal::CGSMTXCal()
{
	m_mapClassFunc[_T("GSMTXCalMainFunc")]=&CGSMTXCal::CGSMTXCalMainFunc;
	m_mapClassFunc[_T("TXDACal")]=&CGSMTXCal::CGSMTXDACalFunc;
	m_mapClassFunc[_T("TXDAV2Cal")]=&CGSMTXCal::CGSMTXDACalV2Func;
	m_mapClassFunc[_T("TXPredisCal")]=&CGSMTXCal::CGSMTXPredistCalFunc;
	m_mapClassFunc[_T("TXPredisV2Cal")]=&CGSMTXCal::CGSMTXPredistCalV2Func;
	m_mapClassFunc[_T("TXDAAndPredisCal_9x25")]=&CGSMTXCal::CGSMTXDAAndPredistCalFunc_MDM9x25;
}

CGSMTXCal::~CGSMTXCal()
{
	
}

bool CGSMTXCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSMTXCal::Handle()
{
	if(!DoProcess())
	{

		m_pPhone->CloseComport();
		m_pFunGSMCalDev->Deivce_Exit();
		return false;
	}

    

	return true;
}

bool CGSMTXCal::CGSMTXCalMainFunc()
{
	 if(!SetGSMCableLoss())
		return false;

	/* switch(m_iBand)
	 {
		case 850:
	
			m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);

		 break;
		  case 900:
			 m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);
		 break;
		 case 1800:
			 m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);
	     break;
	    case 1900:
			m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);
		 break;
	 }*/

	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CGSMTXCal::CGSMTXDACalFunc()
{
  
			CString strMsg;
			strMsg=_T("CGSMTXDACalFunc not support now!");
			CalFailLog("_","_",0,strMsg);
			
			/*int iErrorcode;
			
	  		int iRet=0;
		   		
			unsigned char* aiRgi;
			unsigned char* aiGSMMode;
			unsigned char* aiPARange;
			unsigned short* aiRGISegment;
		    int iTemp;
			float aiPowerlist[3][300];
			float aiPahselist[3][300];
			float aiFErrlist[3][300]; 
		
			
			int iStepLengh=3.692*m_iSegmentTime+0.5;
			
			int *paList;
			 unsigned long chanLoopVar = 0;
			int rgi,mode,pa;
			float pwr;
			int paIndex[4];
			double dLimitPower=0.0; 
	
			 int rgiAllChan = 0;
			int rgiMatch = 0;
	        int predistCalPARange = 0;
			int iIsShowFrr=0;
            double dExpectPower=m_dDATrigPower+2;
			 double dDLMhz=0.0;
			 double dULMhz=0.0;
		   QMSL_GSM_DA_Cal_NV_Chan_struct daCalNV;
	       QMSL_GSM_DA_Cal_Result calResultsToQmsl;
		   memset(&calResultsToQmsl,0,sizeof(QMSL_GSM_DA_Cal_Result));

		aiRgi=(unsigned char*)malloc(m_iListSize*sizeof(unsigned char));   
		aiGSMMode=(unsigned char*)malloc(m_iListSize*sizeof(unsigned char));    
		aiPARange=(unsigned char*)malloc(m_iListSize*sizeof(unsigned char));
		
		aiRGISegment=(unsigned short*)malloc(m_iListSize*sizeof(unsigned short));
		memset(aiRgi,0,sizeof(aiRgi));
		memset(aiGSMMode,0,sizeof(aiGSMMode)); 
	    memset(aiPARange,0,sizeof(aiPARange));
		memset(aiPowerlist,0,sizeof(aiPowerlist)); 
		memset(aiPahselist,0,sizeof(aiPahselist));
		memset(aiRGISegment,0,sizeof(aiRGISegment)); 
		 aiRgi[0]=31;  //trigger 
		 aiGSMMode[0]=1;
		 aiPARange[0]=0;
		 aiRGISegment[0]=m_iSegmentTime;
		 
		for(int i=1;i<m_iListSize;i++)
		{
		   
			aiRGISegment[i]=m_iSegmentTime;
			if(i%2==0) //even
			{
			 aiGSMMode[i]=1;
			  iTemp=i/2-1;
			}
			else
			{
			 aiGSMMode[i]=0;
			 iTemp=(i-1)/2;
			}
			 while(iTemp > 31)
			 {
		       iTemp -= 32;
			 }
			
			 aiRgi[i]=iTemp;
			
			if(m_iRangeNum==4)
		    aiPARange[i]=(i-1)/((m_iListSize-1)/4);
			else
			{
				 iTemp=(i-1)/((m_iListSize-1)/3);
				if(iTemp>0)
					iTemp++;
				aiPARange[i]=iTemp;
					
			}
			
		}

		strMsg.Format("Start DA Calibration....");
		LogTrace(MSG_MID,strMsg)



		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	   if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iPhoneMode))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

	   for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
	   {
		   dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
			dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);
			dULMhz+=0.0667;
           int iChannel=m_vChannelList[iCHIndex];

		    if((iErrorcode=m_pPhone->FTM_SET_CHAN(iChannel))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

		   if((iErrorcode=m_pPhone->FTM_SET_PDM(0,0))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

		   
		   if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_TX_ON Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

            if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Set Freq device fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Freq device fail");
				return false;
			  
		   }

			if((iErrorcode=m_pFunGSMCalDev->IGSMCalInitAMAM_AMPM(dExpectPower,m_iListSize,m_iMeasLength,iStepLengh,90))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Init AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init AMAM_AMPM fail");
				return false;
			  
		   }
			Sleep(1000);

			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(17))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pPhone->FTM_DA_CAL(m_iListSize,aiRGISegment,aiRgi,aiGSMMode,aiPARange))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_DA_CAL Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			  { 
				  strMsg.Format("FTM_SET_MODE_ID Fail!");
				  PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			  } 

			  if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchMAM_AMPM_Results(aiPowerlist[iCHIndex],aiPahselist[iCHIndex],aiFErrlist[iCHIndex],m_iListSize))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Fectch AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init AMAM_AMPM fail");
				return false;
			  
		   }


		   if(aiPowerlist[iCHIndex][0]<m_dDATrigPower)
		   {
               strMsg.Format("trigger power =%.2f < limit power=%.2f  Fail",aiPowerlist[iCHIndex][0],m_dDATrigPower);
               PHONE_CAL_ERR_LOG(strMsg,-1)
                
		   }

			for(int j=1;j<m_iListSize;j+=2)
			{
		 
				//if(m_strTesterDeviceCurr=="MT8820")
					strMsg.Format("band=%s ,channel= %d ,PA range= %d ,RGI =%d,  GSM_PMEAS =%.3f ,EDGE_PMEAS=%.3f",m_strBand,iChannel,aiPARange[j],aiRgi[j],aiPowerlist[iCHIndex][j+1],aiPowerlist[iCHIndex][j]);      
				//else
					//strMsg.Format("band=%s ,channel= %d ,PA range= %d ,RGI =%d,  GSM_PMEAS =%.3f ,EDGE_PMEAS=%.3f, GSM_FErr=%.4f Hz, EDGE_FErr=%.4f Hz",m_strBand,iChannel,aiPARange[j],aiRgi[j],aiPowerlist[iCHIndex][j+1],aiPowerlist[iCHIndex][j],aiFErrlist[iCHIndex][j+1],aiFErrlist[iCHIndex][j]);
				 LogTrace(MSG_MID,strMsg)
		     
		  }  
	   }

		  paList=(int*)malloc(m_iRangeNum*sizeof(int)); 

		  	if(3==m_iRangeNum){
				paList[0] = 0;
				paList[1] = 2;
				paList[2] = 3;
	
		
			}
			else if(4==m_iRangeNum){
				paList[0] = 0;
				paList[1] = 1;
				paList[2] = 2;
				paList[3] = 3;
				
			}

			calResultsToQmsl.iNumMeasuredTxGainStates = m_iRangeNum; //Number of PA Ranges (Low Bands: 4, High Bands: 3)
			calResultsToQmsl.iNumChannels =m_vChannelList.size();
			calResultsToQmsl.iNumTxPowerMeasurementsPerRange = 32; //0 to 31

				for(int i=0;i<m_iRangeNum; i++)
			{
				calResultsToQmsl.aiTxMeasToNVMapping[i] = paList[i];
				paIndex[paList[i]] = i; // Create reverse mapping to use later

			}

				for(int chanLoopVar = 0;chanLoopVar < m_vChannelList.size();chanLoopVar++)
				{
					int chan = m_vChannelList[chanLoopVar];

					calResultsToQmsl.iChannel[chanLoopVar] = chan;

					calResultsToQmsl.iFreqMapping[chanLoopVar] = (QMSL_GSM_Polar_Cal_Frequency)(chanLoopVar+1);
			        
					for(int i=1;i<m_iListSize;i++)
					{
					  rgi = aiRgi[i];
					  pwr = aiPowerlist[chanLoopVar][i];
					  mode = aiGSMMode[i];
					  pa = aiPARange[i];
					  
					 switch(mode)
					 {
					  case 1:  //GMSK
						calResultsToQmsl.aiGSMTxRGI[chanLoopVar][paIndex[pa]][rgi] = rgi;
						calResultsToQmsl.aiGSMTxPowerMeas[chanLoopVar][paIndex[pa]][rgi] = pwr;
						break;
					  case 0:  //8PSK
						calResultsToQmsl.aiEDGETxRGI[chanLoopVar][paIndex[pa]][rgi] = rgi;
						calResultsToQmsl.aiEDGETxPowerMeas[chanLoopVar][paIndex[pa]][rgi] = pwr;
						break;
					 }
					}

				}


     if((iErrorcode=m_pPhone->RFCAL_GSM_Tx_DA_Cal_Results(m_iPhoneMode,&calResultsToQmsl,&daCalNV,1))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("RFCAL_GSM_Tx_DA_Cal_Results Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

	 for(int chanLoopVar = 0;chanLoopVar < m_vChannelList.size();chanLoopVar++)
	{

		for(int rgiLoopVar = 0;rgiLoopVar < 32;rgiLoopVar++)
		{
			if(calResultsToQmsl.aiEDGETxPowerMeas[chanLoopVar][0][rgiLoopVar] >  m_dPredisRGIPower)
			{
				rgiMatch = calResultsToQmsl.aiEDGETxRGI[chanLoopVar][0][rgiLoopVar];
				break;
			}
		}
		if(rgiMatch > rgiAllChan)
		{
			rgiAllChan = rgiMatch;
		}
	}
	
	  m_iRGIForDist=rgiAllChan;
	  
	    free(paList);
		free(aiRgi);
		free(aiGSMMode);  
		free(aiPARange);  

    
    CalPassLog(m_strBand,"_","TX DACalibration Pass")*/
	return false;
}

bool CGSMTXCal::CGSMTXDACalV2Func()
{

	CString strMsg;
	int iErrorcode;

	int iRet=0;

	unsigned char aiRgi[300];
	unsigned char aiGSMMode[300];
	unsigned char aiPARange[300];
	unsigned short aiRGISegment[300];
	float aiPowerlist[3][300];
	float aiPahselist[3][300];
	float aiFErrlist[3][300]; 


	float iStepLengh=3.692*m_idDAStepDuration;	

	int rgiAllChan = 0;
	int rgiMatch = 0;
	int predistCalPARange = 0;
	int iIsShowFrr=0;	
	double dDLMhz=0.0;
	double dULMhz=0.0;
	QMSL_GSM_DA_Cal_NV_Chan_struct daCalNV;
	QMSL_GSM_DA_Cal_Result calResultsToQmsl;
	memset(&calResultsToQmsl,0,sizeof(QMSL_GSM_DA_Cal_Result));
	memset(aiRgi,0,sizeof(aiRgi));
	memset(aiGSMMode,0,sizeof(aiGSMMode)); 
	memset(aiPARange,0,sizeof(aiPARange));
	memset(aiPowerlist,0,sizeof(aiPowerlist)); 
	memset(aiPahselist,0,sizeof(aiPahselist));
	memset(aiRGISegment,0,sizeof(aiRGISegment)); 
	aiRgi[0]=m_iDATrigRGI;  //trigger 
	aiGSMMode[0]=1;
	aiPARange[0]=m_iDATrigPA;
	aiRGISegment[0]=m_idDAStepDuration;
	int iNumRGI=(m_iDAStopRGI-m_iDAStartRGI)/m_iDAStepRGI+1;
	int iListSize=1;
	for (int i=0;i<m_ivPARange.size();i++)
	{
		for (int j=0;j<iNumRGI;j++)
		{
			aiRgi[iListSize]=m_iDAStartRGI+j*m_iDAStepRGI;  
			aiGSMMode[iListSize]=0;
			aiPARange[iListSize]=m_ivPARange[i];
			aiRGISegment[iListSize]=m_idDAStepDuration;
			iListSize++;
			aiRgi[iListSize]=m_iDAStartRGI+j*m_iDAStepRGI;  
			aiGSMMode[iListSize]=1;
			aiPARange[iListSize]=m_ivPARange[i];
			aiRGISegment[iListSize]=m_idDAStepDuration;
			iListSize++;
		}
		
	}
	strMsg.Format("Start DA Calibration....");
	LogTrace(MSG_MID,strMsg)

		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

		if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iPhoneMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		if((iErrorcode=m_pPhone->FTM_SET_TRANSMIT_BURS(0,0,5,0,1))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_TRANSMIT_BURS! FAIL");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

		for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
		{
			dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
			dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);
			dULMhz+=0.0667;
			int iChannel=m_vChannelList[iCHIndex];
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			if((iErrorcode=m_pPhone->FTM_SET_CHAN(iChannel))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_CHAN Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			if((iErrorcode=m_pPhone->FTM_SET_PDM(0,0))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_TX_ON Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Set Freq device fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Freq device fail");
				return false;
			}

			if((iErrorcode=m_pFunGSMCalDev->IGSMCalInitAMAM_AMPM(m_dDATrigPower,iListSize,m_iDAMeasLength,iStepLengh,m_iDAMeasOffset,"ENAR"))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Init AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init AMAM_AMPM fail");
				return false;
			}			

			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(17))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			if((iErrorcode=m_pPhone->FTM_DA_CAL(iListSize,aiRGISegment,aiRgi,aiGSMMode,aiPARange))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_DA_CAL Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchMAM_AMPM_Results(aiPowerlist[iCHIndex],aiPahselist[iCHIndex],aiFErrlist[iCHIndex],iListSize))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Fectch AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Fectch AMAM_AMPM fail");
				return false;
			}			

			strMsg.Format("Band	Chan	PA	RGI	GSMP	EDGEP");
			LogTrace(MSG_MID,strMsg)
			for(int j=1;j<iListSize;j+=2)
			{
				//if(m_strTesterDeviceCurr=="MT8820")
				strMsg.Format("%s	%d	%d	%d	%.4f	%.4f",m_strBand,iChannel,aiPARange[j],aiRgi[j],aiPowerlist[iCHIndex][j+1],aiPowerlist[iCHIndex][j]);      
				//else
				//strMsg.Format("band=%s ,channel= %d ,PA range= %d ,RGI =%d,  GSM_PMEAS =%.3f ,EDGE_PMEAS=%.3f, GSM_FErr=%.4f Hz, EDGE_FErr=%.4f Hz",m_strBand,iChannel,aiPARange[j],aiRgi[j],aiPowerlist[iCHIndex][j+1],aiPowerlist[iCHIndex][j],aiFErrlist[iCHIndex][j+1],aiFErrlist[iCHIndex][j]);
				LogTrace(MSG_MID,strMsg)

			} 

			if(aiPowerlist[iCHIndex][0]<m_dvDATrigeLimit[0]||aiPowerlist[iCHIndex][0]>m_dvDATrigeLimit[1])
			{
				strMsg.Format("Channel= %d,trigger power =%.2f < limit power=%.2f to%.2f  Fail",iChannel,aiPowerlist[iCHIndex][0],m_dvDATrigeLimit[0],m_dvDATrigeLimit[1]);
				PHONE_CAL_ERR_LOG(strMsg,-1)
			}
		}	

		calResultsToQmsl.iNumMeasuredTxGainStates = m_ivPARange.size(); //Number of PA Ranges (Low Bands: 4, High Bands: 3)
		calResultsToQmsl.iNumChannels =m_vChannelList.size();
		calResultsToQmsl.iNumTxPowerMeasurementsPerRange = iNumRGI; 

		for(int i=0;i<m_ivPARange.size(); i++)
		{
			calResultsToQmsl.aiTxMeasToNVMapping[i] = m_ivPARange[i];
			//paIndex[paList[i]] = i; // Create reverse mapping to use later
		}
		
		for(int chanLoopVar = 0;chanLoopVar < m_vChannelList.size();chanLoopVar++)
		{	
			calResultsToQmsl.iChannel[chanLoopVar] = m_vChannelList[chanLoopVar];

			calResultsToQmsl.iFreqMapping[chanLoopVar] = (QMSL_GSM_Polar_Cal_Frequency)m_ivNVMap[chanLoopVar];
			iListSize=1;
			for (int ipaIndex=0;ipaIndex<m_ivPARange.size();ipaIndex++)
			{
				for (int irgiIndex=0;irgiIndex<iNumRGI;irgiIndex++)
				{
					calResultsToQmsl.aiEDGETxRGI[chanLoopVar][ipaIndex][irgiIndex] = aiRgi[iListSize];
					calResultsToQmsl.aiEDGETxPowerMeas[chanLoopVar][ipaIndex][irgiIndex] = aiPowerlist[chanLoopVar][iListSize];
					iListSize++;
					calResultsToQmsl.aiGSMTxRGI[chanLoopVar][ipaIndex][irgiIndex] = aiRgi[iListSize];
					calResultsToQmsl.aiGSMTxPowerMeas[chanLoopVar][ipaIndex][irgiIndex] = aiPowerlist[chanLoopVar][iListSize];
					iListSize++;
				}
			}
		}
		if((iErrorcode=m_pPhone->RFCAL_GSM_Tx_DA_Cal_Results(m_iPhoneMode,&calResultsToQmsl,&daCalNV,1))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("RFCAL_GSM_Tx_DA_Cal_Results Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

		/*for(int chanLoopVar = 0;chanLoopVar < m_vChannelList.size();chanLoopVar++)
		{

			for(int rgiLoopVar = 0;rgiLoopVar < 32;rgiLoopVar++)
			{
				if(calResultsToQmsl.aiEDGETxPowerMeas[chanLoopVar][0][rgiLoopVar] >  m_dPredisRGIPower)
				{
					rgiMatch = calResultsToQmsl.aiEDGETxRGI[chanLoopVar][0][rgiLoopVar];
					break;
				}
			}
			if(rgiMatch > rgiAllChan)
			{
				rgiAllChan = rgiMatch;
			}
		}*/

		for(int chanLoopVar = 0;chanLoopVar < m_vChannelList.size();chanLoopVar++)
		{

			for(int rgiLoopVar = 0;rgiLoopVar < 32;rgiLoopVar++)
			{
				if(calResultsToQmsl.aiEDGETxPowerMeas[chanLoopVar][m_iDATrigPA][rgiLoopVar] >  m_dPredisRGIPower)
				{
					rgiMatch = calResultsToQmsl.aiEDGETxRGI[chanLoopVar][m_iDATrigPA][rgiLoopVar];
					break;
				}
			}
			if(rgiMatch > rgiAllChan)
			{
				rgiAllChan = rgiMatch;
			}
		}

		m_iRGIForDist=rgiAllChan;
		strMsg.Format("RGI For Predistcal :RGI=%d",m_iRGIForDist);
		LogTrace(MSG_MID,strMsg)
	
		CalPassLog(m_strBand,"_","TX DACalibration Pass")
			return true;
}
bool CGSMTXCal::CGSMTXPredistCalV2Func()
{
	 CString strMsg;
	   /* int iErrorcode;
    	int iRet=0;
	 double dDLMhz=0.0;
	 double dULMhz=0.0;
	 unsigned char nvArr[128];



	 
	 unsigned char *aiBinArray;
	  unsigned char* aiAMAM;
	 unsigned char* aiAMPM;
	 double ExpertPower=0; 	

	 int iSamplecount=12538; 
	 int iTriggerdelay=-50; //unit :us
    
      unsigned char temp[4];  
	 unsigned long iPreDCDuration=1000;
	unsigned long  iEdgeduration=1000;
	unsigned long  iDigScale=0; //out for scale 
	float samplingRateHz = 10.0e6;
    float symbolrate = 270833.0;
	float fIValue, fQValue;
    
     double dExpectPower=35;

     static QMSL_GSM_PreDist_Cal_Result pcalResult;	 
	 memset(&pcalResult,0,sizeof(QMSL_GSM_PreDist_Cal_Result));
	 QMSL_GSM_PreDist_Cal_NV_Chan_struct calNV={0}; 
   

	   
		aiBinArray=(unsigned char*)malloc(iSamplecount*2*sizeof(float));
		aiAMAM=(unsigned char*)malloc(iSamplecount*sizeof(float));
	    aiAMPM=(unsigned char*)malloc(iSamplecount*sizeof(float));
	
     strMsg="Start Predis Calibration"; 
     LogTrace(MSG_MID,strMsg)

	 	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	   if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iPhoneMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	   if((iErrorcode=m_pPhone->FTM_SET_TRANSMIT_BURS(0,0,5,0,1))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_TRANSMIT_BURS Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
	   for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
	   {
		   int iChannel=m_vChannelList[iCHIndex];  
		    dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
			dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);
		   
			memset(aiBinArray,0,sizeof(aiBinArray));
			memset(aiAMAM,0,sizeof(aiAMAM));
			memset(aiAMPM,0,sizeof(aiAMPM));	


			
              if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Set GSM Channel  fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Set GSM Channel  fail");
				return false;
			  
		   }

			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pPhone->FTM_SET_CHAN(iChannel))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_TX_ON Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			  if((iErrorcode=m_pPhone->FTM_SET_GSM_LINEAR_PA_RANGE(0,0))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_GSM_LINEAR_PA_RANGE Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

		    strMsg.Format("Init AMAM_AMPM Predist Device......."); 
		 LogTrace(MSG_MID,strMsg)

            if((iErrorcode=m_pFunGSMCalDev->IGSMCalInit_IQSample(dExpectPower,iSamplecount,iTriggerdelay))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Init IQSample fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init IQSample fail");
				return false;
			  
		   }
	   
            if((iErrorcode=m_pPhone->FTM_TX_CFG2_AMAM_SWEEP_V2(m_iDcDuration,m_iEdgeDuration,m_iRGIForDist,0,&iDigScale))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_TX_CFG2_AMAM_SWEEP Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
            Sleep(20);

              

			pcalResult.iFreqMapping[iCHIndex] = (QMSL_GSM_Polar_Cal_Frequency)(iCHIndex+1);  

		    if(m_strTesterDeviceCurr.Find("8960")!=-1)
			{
				 if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchIQ_Results(0,aiAMAM,aiAMPM,iSamplecount))!=DEVICE_SUCCESS)
			   {
					LogTrace(MSG_ERROR,"Fetch IQSample fail");
					CalFailLog(_T("_"),_T("_"),iErrorcode,"Fetch IQSample fail");
					return false;
				  
			   }
				  for(int j=0;j<iSamplecount;j++)
			   {
				   temp[0]=aiAMAM[j*4+3];
				   temp[1]=aiAMAM[j*4+2];
				   temp[2]=aiAMAM[j*4+1];
				   temp[3]=aiAMAM[j*4];
				   memcpy(&pcalResult.adTxAmpl[iCHIndex][j],temp,4);
				   
				   temp[0]=aiAMPM[j*4+3];
				   temp[1]=aiAMPM[j*4+2];
				   temp[2]=aiAMPM[j*4+1];
				   temp[3]=aiAMPM[j*4];
					memcpy(&pcalResult.adTxPhaseArr[iCHIndex][j],temp,4); 
				
			   }

			}
			else
			{

					 if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchIQ_Results(aiBinArray,0,0,iSamplecount))!=DEVICE_SUCCESS)
			   {
					LogTrace(MSG_ERROR,"Fetch IQSample fail");
					CalFailLog(_T("_"),_T("_"),iErrorcode,"Fetch IQSample fail");
					return false;
				  
			   }
				 for(int j=0;j<iSamplecount;j++)
				 {		 
				memcpy(&fIValue,&aiBinArray[2*j*4],4);
				memcpy(&fQValue,&aiBinArray[2*j*4+4],4);
				
					/ *if(fIValue>-0.001 && fIValue<0.001)
					{
					  pcalResult->adTxAmpl[iCHIndex][j]=0;
					   pcalResult->adTxPhaseArr[iCHIndex][j]=0;
					}* /
					//else
					{
				
					 if(m_strTesterDeviceCurr.Find("CMW")!=-1)
					  pcalResult.adTxAmpl[iCHIndex][j]=10*log10(20*(fIValue*fIValue+fQValue*fQValue)); //V->MV
					 else
					 pcalResult.adTxAmpl[iCHIndex][j]=10*log10(fIValue*fIValue+fQValue*fQValue);

					 pcalResult.adTxPhaseArr[iCHIndex][j]=(atan2(fQValue,fIValue))*180/3.1415926;
					}
				}
			}
		
		
	   }

	 
	 free(aiBinArray);
	 free(aiAMAM);
	 free(aiAMPM);

	   pcalResult.iEDGETxCalScale=iDigScale;
	   pcalResult.iNoiseSamples = 500;//This also configured on the call box (as trigger delay)
   	   pcalResult.iNumChannels = 3;
       pcalResult.iNumPredistortionWaveformSamples = iSamplecount;
       pcalResult.iSamplingRateHz = samplingRateHz;
       pcalResult.iCalRgi = m_iRGIForDist;
       pcalResult.iDcSamples = (long)((m_iDcDuration/4)*(samplingRateHz/symbolrate));
       pcalResult.iEdgeSamples =(long)((m_iEdgeDuration/4)*(samplingRateHz/symbolrate));
	   pcalResult.iDCTransientPercent=60;
	   pcalResult.iEDGETransientSymbols=90;

	  
	   if((iErrorcode=m_pPhone->ReadNV(m_iGainParamNVID,nvArr,128))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("ReadNV Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	   pcalResult.iEDGETxGainParam = *(short *)(&nvArr[0]);        

	   strMsg.Format("GainParamNVID=%d NVValue=%d",m_iGainParamNVID, pcalResult.iEDGETxGainParam);
	   LogTrace(MSG_MID,strMsg)

	    if((iErrorcode=m_pPhone->RFCAL_GSM_Tx_Linear_Process_PreDist_Cal_Results(m_iPhoneMode,&pcalResult,&calNV,1))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("RFCAL_GSM_Tx_Linear_Process_PreDist_Cal_Results Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

		

    strMsg.Format("Dynamic range :min : %d, max : %d ! Predist RGI =%d",calNV.aDyanmicRange.iMinPower,calNV.aDyanmicRange.iMaxPower,calNV.aCalRGI.iPredistRGI);
    LogTrace(MSG_MID,strMsg) 

    for(int i=0;i<3;++i)
	{
       strMsg.Format("Channel=%d ,Frequency Error=%.2f",m_vChannelList[i],calNV.afreqErrEstimate[i]*1000);
       LogTrace(MSG_MID,strMsg) 
		   for(int m=0;m<2;++m)
		   {
			   for(int n=0;n<64;++n)
			   {
					strMsg.Format("Channel = %d ,index=%d ,NV_AMAM =%d ,NV_AMPM=%d",m_vChannelList[i],n,calNV.aAMAM_AMPM_NV[i].aAMAM_NV[m].AMAM[n],calNV.aAMAM_AMPM_NV[i].aAMPM_NV[m].AMPM[n]);
					LogTrace(MSG_MID,strMsg) 
			   }

		   }
	}*/

	CalFailLog(m_strBand,"_",0,"TX PredistCalibration not support now")
	return false;

}
bool CGSMTXCal::CGSMTXPredistCalFunc()
{
  
	 CString strMsg;
	 int iErrorcode;
     int iRet=0;
	 double dDLMhz=0.0;
	 double dULMhz=0.0;
	 unsigned char nvArr[128];
	 float afPower[64000];
	 float afPhase[64000];	 
	 int iTriggerdelay=-50; //unit :us
	 unsigned long  iDigScale=0; 
	 float samplingRateHz = 10.0e6;
     float symbolrate = 270833.0;    
     double dExpectPower=35;

	 static QMSL_GSM_PreDist_Cal_Result preDic_Cal_Result;
	 QMSL_GSM_PreDist_Cal_NV_Chan_struct calNV;
	memset(&preDic_Cal_Result,0,sizeof(QMSL_GSM_PreDist_Cal_Result));
	memset(&calNV,0,sizeof(QMSL_GSM_PreDist_Cal_NV_Chan_struct));
     strMsg="Start Predist Calibration"; 
     LogTrace(MSG_MID,strMsg)

	preDic_Cal_Result.iNoiseSamples = -iTriggerdelay*10;//This also configured on the call box (as trigger delay)
	 preDic_Cal_Result.iDcSamples = (long)((m_iDcDuration/4)*(samplingRateHz/symbolrate));
	 preDic_Cal_Result.iEdgeSamples =(long)((m_iEdgeDuration/4)*(samplingRateHz/symbolrate));
	 preDic_Cal_Result.iNumChannels = m_vChannelList.size();
	 unsigned short iSamplecount=preDic_Cal_Result.iDcSamples+preDic_Cal_Result.iEdgeSamples+preDic_Cal_Result.iNoiseSamples*2; 
	 
	 preDic_Cal_Result.iSamplingRateHz = (long)samplingRateHz;
	 preDic_Cal_Result.iCalRgi = m_iRGIForDist;

	 preDic_Cal_Result.iDCTransientPercent=(float)10.0;
	 preDic_Cal_Result.iEDGETransientSymbols=20;

	   for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
	   {
		   int iChannel=m_vChannelList[iCHIndex];  
		    dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
			dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);
		   
	
			memset(afPower,0,sizeof(afPower));
			memset(afPhase,0,sizeof(afPhase));


			
              if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Set GSM Channel  fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Set GSM Channel  fail");
				return false;
			  
		   }

			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pPhone->FTM_SET_CHAN(iChannel))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_TX_ON Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			  if((iErrorcode=m_pPhone->FTM_SET_GSM_LINEAR_PA_RANGE(0,m_iDATrigPA))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_GSM_LINEAR_PA_RANGE Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

		    strMsg.Format("Init AMAM_AMPM Predist Device......."); 
		 LogTrace(MSG_MID,strMsg)
			
		

            if((iErrorcode=m_pFunGSMCalDev->IGSMCalInit_IQSample(dExpectPower,iSamplecount,iTriggerdelay))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Init IQSample fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init IQSample fail");
				return false;
			  
		   }
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(17))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
	
            if((iErrorcode=m_pPhone->FTM_TX_CFG2_AMAM_SWEEP_V2(m_iDcDuration,m_iEdgeDuration,m_iRGIForDist,0,&iDigScale))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_TX_CFG2_AMAM_SWEEP Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

              

			preDic_Cal_Result.iFreqMapping[iCHIndex] = (QMSL_GSM_Polar_Cal_Frequency)m_ivNVMap[iCHIndex];  

			if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchIQ_Results_V2(afPower,afPhase,&iSamplecount))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Fetch IQSample fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Fetch IQSample fail");
				return false;

			}
			float a=10;
			float b=a/0;			
			for(int j=0;j<iSamplecount;j++)
			{				
				if(afPower[j] == b||afPower[j]==-b)
				{
					if (0==j)
					{
						afPower[j]=afPower[j+1];
					}
					else
					{
						afPower[j]=afPower[j-1];
					}
					
				}
				
				
				preDic_Cal_Result.adTxAmpl[iCHIndex][j]=afPower[j];
				preDic_Cal_Result.adTxPhaseArr[iCHIndex][j]=afPhase[j]; 

			}

		    /*if(m_strTesterDeviceCurr.Find("8960")!=-1)
			{
				 if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchIQ_Results(0,aiAMAM,aiAMPM,iSamplecount))!=DEVICE_SUCCESS)
			   {
					LogTrace(MSG_ERROR,"Fetch IQSample fail");
					CalFailLog(_T("_"),_T("_"),iErrorcode,"Fetch IQSample fail");
					return false;
				  
			   }
				  for(int j=0;j<iSamplecount;j++)
			   {
				   temp[0]=aiAMAM[j*4+3];
				   temp[1]=aiAMAM[j*4+2];
				   temp[2]=aiAMAM[j*4+1];
				   temp[3]=aiAMAM[j*4];
				   memcpy(&pcalResult->adTxAmpl[iCHIndex][j],temp,4);
				   
				   temp[0]=aiAMPM[j*4+3];
				   temp[1]=aiAMPM[j*4+2];
				   temp[2]=aiAMPM[j*4+1];
				   temp[3]=aiAMPM[j*4];
					memcpy(&pcalResult->adTxPhaseArr[iCHIndex][j],temp,4); 
				
			   }

			}
			else
			{

					 if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchIQ_Results(aiBinArray,0,0,iSamplecount))!=DEVICE_SUCCESS)
			   {
					LogTrace(MSG_ERROR,"Fetch IQSample fail");
					CalFailLog(_T("_"),_T("_"),iErrorcode,"Fetch IQSample fail");
					return false;
				  
			   }
				 for(int j=0;j<iSamplecount;j++)
				 {		 
				memcpy(&fIValue,&aiBinArray[2*j*4],4);
				memcpy(&fQValue,&aiBinArray[2*j*4+4],4);
				
					/ *if(fIValue>-0.001 && fIValue<0.001)
					{
					  pcalResult->adTxAmpl[iCHIndex][j]=0;
					   pcalResult->adTxPhaseArr[iCHIndex][j]=0;
					}* /
					//else
					{
				
					 if(m_strTesterDeviceCurr.Find("CMW")!=-1)
					  pcalResult->adTxAmpl[iCHIndex][j]=10*log10(20*(fIValue*fIValue+fQValue*fQValue)); //V->MV
					 else
					 pcalResult->adTxAmpl[iCHIndex][j]=10*log10(fIValue*fIValue+fQValue*fQValue);

					 pcalResult->adTxPhaseArr[iCHIndex][j]=(atan2(fQValue,fIValue))*180/3.1415926;
					}
				}
			}*/
		
		
	   }
	   
	   preDic_Cal_Result.iEDGETxCalScale=iDigScale;
	   
		preDic_Cal_Result.iNumPredistortionWaveformSamples = iSamplecount;

	   preDic_Cal_Result.iOverRideModemConstants=m_iOverRideModemConstants;
	   preDic_Cal_Result.dDigGainUnity=m_dDigGainUnity;
	   preDic_Cal_Result.dRampUnity=m_dRampUnity;
	   preDic_Cal_Result.dExtensionFloor=m_dExtensionFloor;
	   preDic_Cal_Result.dDacScale=m_dDacScale;

	   preDic_Cal_Result.iOverrideSmooothingDefaults=m_iOverrideSmooothingDefaults;
	   preDic_Cal_Result.iEnableAmAmSmoothing=m_iEnableAmAmSmoothing;
	   preDic_Cal_Result.dAmAmKnot=m_dAmAmKnot;
	   preDic_Cal_Result.dAmPmKnot=m_dAmPmKnot;

	   switch (m_iBand)
	   {
	   case 850:
		   m_iGainParamNVID=6475;  //24972   6475
		   break;
	   case 900:
		   m_iGainParamNVID=5478;   //24973   5478
		   break;
	   case 1800:
		   m_iGainParamNVID=6476;   //24974   6476
		   break;
	   case 1900:
		   m_iGainParamNVID=6477;   //24975   6477
		   break;
	   }
	  
	   if((iErrorcode=m_pPhone->ReadNV(m_iGainParamNVID,nvArr,128))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("ReadNV Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	   preDic_Cal_Result.iEDGETxGainParam = *(short *)(&nvArr[0]);        

	   strMsg.Format("GainParamNVID=%d NVValue=%d",m_iGainParamNVID, preDic_Cal_Result.iEDGETxGainParam);
	   LogTrace(MSG_MID,strMsg)		

	    if((iErrorcode=m_pPhone->RFCAL_GSM_Tx_Linear_Process_Swapped_PreDist_Cal_Results((nv_mode_id_type)m_iPhoneMode,&preDic_Cal_Result,&calNV,1))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("RFCAL_GSM_Tx_Linear_Process_PreDist_Cal_Results Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 


		strMsg.Format("AMAM Dynamic Range - Max Power: %d ! Limit =%.0f",calNV.aDyanmicRange.iMaxPower,(m_dPredisRGIPower+1.5)*100);
		LogTrace(MSG_MID,strMsg) 
	if (calNV.aDyanmicRange.iMaxPower<(m_dPredisRGIPower+1.5)*100)
	{
		strMsg=_T("AMAM Dynamic Range Fail");
		LogTrace(MSG_MID,strMsg)
			return false;

	}
	strMsg=_T("NV_GSM_PreDist_CAL Measured Delay");
	LogTrace(MSG_MID,strMsg)
    for (int i=0;i<3;++i)
    {
		strMsg.Format("%d,	%d,	-50,	100",m_vChannelList[i],calNV.aDelayEstimate[i]);
		LogTrace(MSG_MID,strMsg)
			if (calNV.aDelayEstimate[i]<-50||calNV.aDelayEstimate[i]>100)
			{
				strMsg=_T("NV_GSM_PreDist_CAL Fail");
				LogTrace(MSG_MID,strMsg)
					return false;
			}
    }

	strMsg=_T("NV_GSM_PreDist_CAL EDGE Duration Min Power");
	LogTrace(MSG_MID,strMsg)
		for (int i=0;i<3;++i)
		{
			strMsg.Format("%d,	%.5f,	-20",m_vChannelList[i],calNV.aMinPowerInEdgeDuration[i]);
			LogTrace(MSG_MID,strMsg)
				if (calNV.aMinPowerInEdgeDuration[i]<-20)
				{
					strMsg=_T("NV_GSM_PreDist_CAL Fail");
					LogTrace(MSG_MID,strMsg)
						return false;
				}
		}
		

    for(int i=0;i<3;++i)
	{     
		strMsg.Format("Channel=%d ,Frequency Error=%.2f",m_vChannelList[i],calNV.afreqErrEstimate[i]*1000);
		LogTrace(MSG_MID,strMsg) 
		   for(int m=0;m<2;++m)
		   {
			   for(int n=0;n<64;++n)
			   {
					strMsg.Format("Channel = %d ,index=%d ,NV_AMAM =%d ,NV_AMPM=%d",m_vChannelList[i],n,calNV.aAMAM_AMPM_NV[i].aAMAM_NV[m].AMAM[n],calNV.aAMAM_AMPM_NV[i].aAMPM_NV[m].AMPM[n]);
					LogTrace(MSG_MID,strMsg) 
			   }

		   }
	}

	CalPassLog(m_strBand,"_","TX PredistCalibration Pass")
	return true;
}
bool CGSMTXCal::CGSMTXDAAndPredistCalFunc_MDM9x25()
{  
	CString strMsg;
	int iErrorcode;
	int iRet=0;
	int iMode_id,iMode_id_ex;
	if (0==m_iChainId)
	{
		iMode_id=2;
		iMode_id_ex=17;
	}else
	{
		iMode_id=49;
		iMode_id_ex=50;
	}
	unsigned char aiRgi[300];
	unsigned char aiGSMMode[300];
	unsigned char aiPARange[300];
	unsigned short aiRGISegment[300];
	float aiPowerlist[3][300];
	float aiPahselist[3][300];
	float aiFErrlist[3][300]; 
	float iStepLengh=3.6923*m_idDAStepDuration;   //origin is 3.692,change by yu 20141029
	int rgiAllChan = 0;
	int rgiMatch = 0;
	int predistCalPARange = 0;
	int iIsShowFrr=0;	
	double dDLMhz=0.0;
	double dULMhz=0.0;
	//QMSL_GSM_DA_Cal_NV_Chan_struct daCalNV;
	static QMSL_GSM_DA_Cal_Result calResultsToQmsl;
	memset(&calResultsToQmsl,0,sizeof(QMSL_GSM_DA_Cal_Result));
	memset(aiRgi,0,sizeof(aiRgi));
	memset(aiGSMMode,0,sizeof(aiGSMMode)); 
	memset(aiPARange,0,sizeof(aiPARange));
	memset(aiPowerlist,0,sizeof(aiPowerlist)); 
	memset(aiPahselist,0,sizeof(aiPahselist));
	memset(aiRGISegment,0,sizeof(aiRGISegment)); 
	aiRgi[0]=m_iDATrigRGI;  //trigger 
	aiGSMMode[0]=1;
	aiPARange[0]=m_iDATrigPA;
	aiRGISegment[0]=m_idDAStepDuration;
	int iNumRGI=(m_iDAStopRGI-m_iDAStartRGI)/m_iDAStepRGI+1;
	int iListSize=1;
	for (int i=0;i<m_ivPARange.size();i++)
	{
		for (int j=0;j<iNumRGI;j++)
		{
			aiRgi[iListSize]=m_iDAStartRGI+j*m_iDAStepRGI;  
			aiGSMMode[iListSize]=0;
			aiPARange[iListSize]=m_ivPARange[i];
			aiRGISegment[iListSize]=m_idDAStepDuration;
			iListSize++;
			aiRgi[iListSize]=m_iDAStartRGI+j*m_iDAStepRGI;  
			aiGSMMode[iListSize]=1;
			aiPARange[iListSize]=m_ivPARange[i];
			aiRGISegment[iListSize]=m_idDAStepDuration;
			iListSize++;
		}
		
	}
	strMsg.Format("Start DA Calibration....");
	LogTrace(MSG_MID,strMsg)
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iPhoneMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		if((iErrorcode=m_pPhone->FTM_SET_TRANSMIT_BURS(0,0,5,0,1))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_TRANSMIT_BURS! FAIL");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
		{
			dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
			dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);
			dULMhz+=0.0667;
			int iChannel=m_vChannelList[iCHIndex];
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if((iErrorcode=m_pPhone->FTM_SET_CHAN(iChannel))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if((iErrorcode=m_pPhone->FTM_SET_PDM(0,0))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_TX_ON Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Set Freq device fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Freq device fail");
				return false;
			}
			if((iErrorcode=m_pFunGSMCalDev->IGSMCalInitAMAM_AMPM(m_dDATrigPower,iListSize,m_iDAMeasLength,iStepLengh,m_iDAMeasOffset,"ENAR"))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Init AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init AMAM_AMPM fail");
				return false;
			}
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id_ex))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if((iErrorcode=m_pPhone->FTM_DA_CAL(iListSize,aiRGISegment,aiRgi,aiGSMMode,aiPARange))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_DA_CAL Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}
			if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchMAM_AMPM_Results(aiPowerlist[iCHIndex],aiPahselist[iCHIndex],aiFErrlist[iCHIndex],iListSize))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Fectch AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Fectch AMAM_AMPM fail");
				return false;
			}
			strMsg.Format("Band	Chan	PA	RGI	GSMP	EDGEP");
			LogTrace(MSG_MID,strMsg)
			for(int j=1;j<iListSize;j+=2)
			{
				//if(m_strTesterDeviceCurr=="MT8820")
				strMsg.Format("%s	%d	%d	%d	%.4f	%.4f",m_strBand,iChannel,aiPARange[j],aiRgi[j],aiPowerlist[iCHIndex][j+1],aiPowerlist[iCHIndex][j]);      
				//else
				//strMsg.Format("band=%s ,channel= %d ,PA range= %d ,RGI =%d,  GSM_PMEAS =%.3f ,EDGE_PMEAS=%.3f, GSM_FErr=%.4f Hz, EDGE_FErr=%.4f Hz",m_strBand,iChannel,aiPARange[j],aiRgi[j],aiPowerlist[iCHIndex][j+1],aiPowerlist[iCHIndex][j],aiFErrlist[iCHIndex][j+1],aiFErrlist[iCHIndex][j]);
				LogTrace(MSG_MID,strMsg)
			} 

			if(aiPowerlist[iCHIndex][0]<m_dvDATrigeLimit[0]||aiPowerlist[iCHIndex][0]>m_dvDATrigeLimit[1])
			{
				strMsg.Format("Channel= %d,trigger power =%.2f < limit power=%.2f to%.2f  Fail",iChannel,aiPowerlist[iCHIndex][0],m_dvDATrigeLimit[0],m_dvDATrigeLimit[1]);
				PHONE_CAL_ERR_LOG(strMsg,-1)

			}
		}	

		calResultsToQmsl.iNumMeasuredTxGainStates = m_ivPARange.size(); //Number of PA Ranges (Low Bands: 4, High Bands: 3)
		calResultsToQmsl.iNumChannels =m_vChannelList.size();
		calResultsToQmsl.iNumTxPowerMeasurementsPerRange = iNumRGI; 

		for(int i=0;i<m_ivPARange.size(); i++)
		{
			calResultsToQmsl.aiTxMeasToNVMapping[i] = m_ivPARange[i];
			//paIndex[paList[i]] = i; // Create reverse mapping to use later
		}
		
		for(int chanLoopVar = 0;chanLoopVar < m_vChannelList.size();chanLoopVar++)
		{	
			calResultsToQmsl.iChannel[chanLoopVar] = m_vChannelList[chanLoopVar];

			calResultsToQmsl.iFreqMapping[chanLoopVar] = (QMSL_GSM_Polar_Cal_Frequency)m_ivNVMap[chanLoopVar];
			iListSize=1;
			for (int ipaIndex=0;ipaIndex<m_ivPARange.size();ipaIndex++)
			{
				for (int irgiIndex=0;irgiIndex<iNumRGI;irgiIndex++)
				{
					calResultsToQmsl.aiEDGETxRGI[chanLoopVar][ipaIndex][irgiIndex] = aiRgi[iListSize];
					calResultsToQmsl.aiEDGETxPowerMeas[chanLoopVar][ipaIndex][irgiIndex] = aiPowerlist[chanLoopVar][iListSize];
					iListSize++;
					calResultsToQmsl.aiGSMTxRGI[chanLoopVar][ipaIndex][irgiIndex] = aiRgi[iListSize];
					calResultsToQmsl.aiGSMTxPowerMeas[chanLoopVar][ipaIndex][irgiIndex] = aiPowerlist[chanLoopVar][iListSize];
					iListSize++;
				}
			}
		}
/*
		if((iErrorcode=m_pPhone->RFCAL_GSM_Tx_DA_Cal_Results(m_iPhoneMode,&calResultsToQmsl,&daCalNV,1))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("RFCAL_GSM_Tx_DA_Cal_Results Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} */

		for(int chanLoopVar = 0;chanLoopVar < m_vChannelList.size();chanLoopVar++)
		{

			for(int rgiLoopVar = 0;rgiLoopVar < 32;rgiLoopVar++)
			{
				if(calResultsToQmsl.aiEDGETxPowerMeas[chanLoopVar][m_iDATrigPA][rgiLoopVar] >  m_dPredisRGIPower)
				{
					rgiMatch = calResultsToQmsl.aiEDGETxRGI[chanLoopVar][m_iDATrigPA][rgiLoopVar];
					break;
				}
			}
			if(rgiMatch > rgiAllChan)
			{
				rgiAllChan = rgiMatch;
			}
		}

		m_iRGIForDist=rgiAllChan;
		strMsg.Format("RGI For Predistcal :RGI=%d",m_iRGIForDist);
		LogTrace(MSG_MID,strMsg)
	
		CalPassLog(m_strBand,"_","TX DACalibration Pass")
	
	 //Predistortion calibration
     iRet=0;
	 dDLMhz=0.0;
	 dULMhz=0.0;
	 unsigned char nvArr[128]="";
	 float *afPower,*afPhase;
     afPower = new float[64000];
	 afPhase = new float[64000];
	 int iTriggerdelay=-50; //unit :us 
	 unsigned long  iDigScale=0; 
	 float samplingRateHz = 10.0e6;
     float symbolrate = 270833.0;    
     double dExpectPower=35;

	 static QMSL_GSM_PreDist_Cal_Result preDic_Cal_Result;
//	 QMSL_GSM_PreDist_Cal_NV_Chan_struct calNV;
	 memset(&preDic_Cal_Result,0,sizeof(QMSL_GSM_PreDist_Cal_Result));
//	 memset(&calNV,0,sizeof(QMSL_GSM_PreDist_Cal_NV_Chan_struct));

     strMsg="Start Predist Calibration"; 
     LogTrace(MSG_MID,strMsg)

	 preDic_Cal_Result.iNoiseSamples = -iTriggerdelay*10;//This also configured on the call box (as trigger delay)
	 preDic_Cal_Result.iDcSamples = (long)((m_iDcDuration/4)*(samplingRateHz/symbolrate));
	 preDic_Cal_Result.iEdgeSamples =(long)((m_iEdgeDuration/4)*(samplingRateHz/symbolrate));
	 preDic_Cal_Result.iNumChannels = m_vChannelList.size();
	 unsigned short iSamplecount=preDic_Cal_Result.iDcSamples+preDic_Cal_Result.iEdgeSamples+preDic_Cal_Result.iNoiseSamples*2; 	 
	 preDic_Cal_Result.iSamplingRateHz = (long)samplingRateHz;
	 preDic_Cal_Result.iCalRgi = m_iRGIForDist;
	 preDic_Cal_Result.iDCTransientPercent=(float)10.0;
	 preDic_Cal_Result.iEDGETransientSymbols=20;

	 for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
	 {
	    int iChannel=m_vChannelList[iCHIndex];  
		dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
		dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);	
		memset(afPower,0,sizeof(afPower));
		memset(afPhase,0,sizeof(afPhase));		
		if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Set GSM Channel  fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Set GSM Channel  fail");
			return false;			  
		}
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		if((iErrorcode=m_pPhone->FTM_SET_CHAN(iChannel))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_PDM Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_TX_ON Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		if((iErrorcode=m_pPhone->FTM_SET_GSM_LINEAR_PA_RANGE(0,m_iDATrigPA))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_GSM_LINEAR_PA_RANGE Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		strMsg.Format("Init AMAM_AMPM Predist Device......."); 
		LogTrace(MSG_MID,strMsg)
		if((iErrorcode=m_pFunGSMCalDev->IGSMCalInit_IQSample(dExpectPower,iSamplecount,iTriggerdelay))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Init IQSample fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Init IQSample fail");
			return false;			  
		}
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id_ex))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		//Do Predistortion calibration
		if((iErrorcode=m_pPhone->FTM_TX_CFG2_AMAM_SWEEP_V2(m_iDcDuration,m_iEdgeDuration,m_iRGIForDist,0,&iDigScale))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_TX_CFG2_AMAM_SWEEP Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
	    // Sleep(200);  
		preDic_Cal_Result.iFreqMapping[iCHIndex] = (QMSL_GSM_Polar_Cal_Frequency)m_ivNVMap[iCHIndex];  
		if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchIQ_Results_V2(afPower,afPhase,&iSamplecount))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Fetch IQSample fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Fetch IQSample fail");
			return false;
		}
		float a=10;
		float b=a/0;			
		for(int j=0;j<iSamplecount;j++)
		{				
			if(afPower[j] == b||afPower[j]==-b)
			{
				if (0==j)	{afPower[j]=afPower[j+1];}
				else  {	afPower[j]=afPower[j-1];}				
			}				
			preDic_Cal_Result.adTxAmpl[iCHIndex][j]=afPower[j];
			preDic_Cal_Result.adTxPhaseArr[iCHIndex][j]=afPhase[j]; 
		}		
	 }

     //delete dynamic memory 
     delete []afPower;  //?
     delete []afPhase;  //?
	   
     preDic_Cal_Result.iEDGETxCalScale=iDigScale;	   
     preDic_Cal_Result.iNumPredistortionWaveformSamples = iSamplecount;
     preDic_Cal_Result.iOverRideModemConstants=m_iOverRideModemConstants;
     preDic_Cal_Result.dDigGainUnity=m_dDigGainUnity;
     preDic_Cal_Result.dRampUnity=m_dRampUnity;
     preDic_Cal_Result.dExtensionFloor=m_dExtensionFloor;
     preDic_Cal_Result.dDacScale=m_dDacScale;
     preDic_Cal_Result.iOverrideSmooothingDefaults=m_iOverrideSmooothingDefaults;
     preDic_Cal_Result.iEnableAmAmSmoothing=m_iEnableAmAmSmoothing;
     preDic_Cal_Result.dAmAmKnot=m_dAmAmKnot;
     preDic_Cal_Result.dAmPmKnot=m_dAmPmKnot;
     //DIAG_NV_READ_F
/*
     if((iErrorcode=m_pPhone->ReadNV(m_iGainParamNVID,nvArr,128))!=PHONE_SUCCESS)
     { 
		strMsg.Format("ReadNV Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
     } */

     //FTM_GSM_API_ReadEnvGainNV
     if (m_iChainId==0)
     {
		 switch (m_iBand)
		 {
		 case 850:
			 m_iGainParamNVID=25052;  //24972   6475
			 break;
		 case 900:
			 m_iGainParamNVID=25053;   //24973   5478
			 break;
		 case 1800:
			 m_iGainParamNVID=25054;   //24974   6476
			 break;
		 case 1900:
			 m_iGainParamNVID=25055;   //24975   6477
			 break;
		 }
     }else
	 {
		 switch (m_iBand)
		 {
		 case 850:
			 m_iGainParamNVID=25056;  
			 break;
		 case 900:
			 m_iGainParamNVID=25057;   
			 break;
		 case 1800:
			 m_iGainParamNVID=25058;   
			 break;
		 case 1900:
			 m_iGainParamNVID=25059;   
			 break;
		 }
	 }


     if((iErrorcode=m_pPhone->ReadEnvGainNV(m_iGainParamNVID,nvArr,128))!=PHONE_SUCCESS)
     { 
	   strMsg.Format("ReadEnvGainNV Fail!");
	   PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
     }
	 ftm_gsm_env_gain_nv_data_type *fgndt = (ftm_gsm_env_gain_nv_data_type*)nvArr;
     preDic_Cal_Result.iEDGETxGainParam = fgndt->gsm_linear_tx_gain_val; //changed from edge_linear_tx_gain_val to gsm_linear_tx_gain_val in 20140905
     strMsg.Format("GainParamNVID=%d NVValue=%d",m_iGainParamNVID, preDic_Cal_Result.iEDGETxGainParam);
     LogTrace(MSG_MID,strMsg)

/*
    if((iErrorcode=m_pPhone->RFCAL_GSM_Tx_Linear_Process_Swapped_PreDist_Cal_Results((nv_mode_id_type)m_iPhoneMode,&preDic_Cal_Result,&calNV,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_GSM_Tx_Linear_Process_PreDist_Cal_Results Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	} */


	QMSL_GSM_Tx_Calibration_NV multiChainResult;
	memset(&multiChainResult,0,sizeof(QMSL_GSM_Tx_Calibration_NV));
	//Queue NV
	unsigned char queue_nv_indicator = 1;
    //printf("Call QLIB_RFCal_GSM_Tx_DA_Cal_IQ_Predist_Cal_Generate_NV to transform DA and PreDistortion Calibration data into MultiChain NV\n");
	if((iErrorcode=m_pPhone->RFCal_GSM_Tx_DA_Cal_IQ_Predist_Cal_Generate_NV((nv_mode_id_type)m_iPhoneMode,m_iChainId,&calResultsToQmsl,&preDic_Cal_Result,&multiChainResult,queue_nv_indicator))!=PHONE_SUCCESS)	
	{ 
		strMsg.Format("RFCal_GSM_Tx_DA_Cal_IQ_Predist_Cal_Generate_NV Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	} 	

    //AMAM Max Pwr         AMAM Max Pwr Min
	strMsg.Format("AMAM Dynamic Range - Max Power: %d ! Limit =%.0f",multiChainResult.nvRev0.aNvHeader.iamamMaxPowerDbm100,(m_dPredisRGIPower+1.5)*100);
	LogTrace(MSG_MID,strMsg) 
	if (multiChainResult.nvRev0.aNvHeader.iamamMaxPowerDbm100<(m_dPredisRGIPower+1.5)*100)
	{
		strMsg=_T("AMAM Dynamic Range Fail");
		LogTrace(MSG_MID,strMsg)
		return false;
	} 
	//Correlation Delay         Correlation Delay Min          Correlation Delay Max 
	strMsg=_T("NV_GSM_DA_PreDist_CAL Measured Delay");
	LogTrace(MSG_MID,strMsg)
	for (int i=0;i<3;++i)
	{
		strMsg.Format("%d,	%d,	-50,	100",m_vChannelList[i],multiChainResult.iqCalData.aDelayEstimate[i]);
		LogTrace(MSG_MID,strMsg)
			if (multiChainResult.iqCalData.aDelayEstimate[i]<-50||multiChainResult.iqCalData.aDelayEstimate[i]>100)
			{
				strMsg=_T("NV_GSM_DA_PreDist_CAL Fail");
				LogTrace(MSG_MID,strMsg)
				return false;
			}
	}
	//DPD EDGE Min Pwr	     DPD EDGE Min Pwr Min
	strMsg=_T("NV_GSM_DA_PreDist_CAL EDGE Duration Min Power");
	LogTrace(MSG_MID,strMsg)
	for (int i=0;i<3;++i)
	{
		strMsg.Format("%d,	%.5f,	-20",m_vChannelList[i],multiChainResult.iqCalData.aMinPowerInEdgeDuration[i]);
		LogTrace(MSG_MID,strMsg)
			if (multiChainResult.iqCalData.aMinPowerInEdgeDuration[i]<-20)
			{
				strMsg=_T("NV_GSM_DA_PreDist_CAL Duration Min Power Fail");
				LogTrace(MSG_MID,strMsg)
				return false;
			}
	}	
	/**DPD Measured Freq Error (Hz)
	106 RFNV_DATA_RGI_LIST_TYPE		
	107	RFNV_DATA_PMEAS_LIST_TYPE		
	108	RFNV_DATA_AMAM_LIST_TYPE		
	109	RFNV_DATA_AMPM_LIST_TYPE		
	110	RFNV_DATA_TX_PWR_ERROR_LIST_TYPE		
	**/
//begin by y
	/*
    strMsg=_T("NV_GSM_DA_PreDist_CAL GSM DA Cal Data And EDGE DA Cal Data,GSM(GMSK):0;  EDGE(8PSK):1");
	LogTrace(MSG_MID,strMsg)
    int Mod_Num = 2;
    int PA_State_Range_Num = m_ivPARange.size();
	int Channel_Num = m_vChannelList.size();
	int Node107StartPos = 14 + Mod_Num * PA_State_Range_Num * 37; 
	int iPMEAS_GMSK[128],iPMEAS_8PSK[128];
    int Num107 = Mod_Num * Channel_Num * PA_State_Range_Num; 
	int iChan,iPA_State;
	//int iMod;
    //CString strMod;
	for (int i=0;i<Num107;i+=2)
	{
         //iMod = multiChainResult.oNVitem.aRFNVItemData[Node107StartPos + i*69 + 2];
         iChan = multiChainResult.oNVitem.aRFNVItemData[Node107StartPos + i*69 + 3];
		 iPA_State = multiChainResult.oNVitem.aRFNVItemData[Node107StartPos + i*69 + 4];
         //iPA_State =  m_ivPARange[];       

	  
		 
		 for (int j=0,m=0;m<32;j+=2,m++)
		 {
			 iPMEAS_GMSK[m] = multiChainResult.oNVitem.aRFNVItemData[Node107StartPos+i*69 + 6+j]*256 + multiChainResult.oNVitem.aRFNVItemData[Node107StartPos +i*69+ 5+j];
             iPMEAS_8PSK[m] = multiChainResult.oNVitem.aRFNVItemData[Node107StartPos+(i+1)*69 + 6+j]*256 + multiChainResult.oNVitem.aRFNVItemData[Node107StartPos+(i+1)*69 + 5+j];		
			 strMsg.Format("Channel = %d,PA State = %d,RGI index = %d ,PMEAS_GMSK = %d ,PMEAS_8PSK = %d",m_vChannelList[iChan],iPA_State,m,iPMEAS_GMSK[m],iPMEAS_8PSK[m]);
			 LogTrace(MSG_MID,strMsg) 
		 }
	}	
    //use Node108StartPos can get NV_AMAM NV_AMPM one time
	strMsg=_T("NV_GSM_DA_PreDist_CAL GSM NV_AMAM And EDGE NV_AMPM,   GSM(GMSK):0;  EDGE(8PSK):1");
	LogTrace(MSG_MID,strMsg)
	int amam_ampm_indentifier_Num = 2;   //0: AMAM (GMSK)	1: AMPM (8PSK)
    int Node108StartPos = Node107StartPos + Num107 * 69;
	int Num108 = amam_ampm_indentifier_Num * Channel_Num;
    int NV_AMAM[256],NV_AMPM[256];
    //int iamam_ampm_indentifier;
	for (int n=0;n<Num108;n+=2)
	{
		//iamam_ampm_indentifier = multiChainResult.oNVitem.aRFNVItemData[Node108StartPos + n*260 + 2];
		iChan = multiChainResult.oNVitem.aRFNVItemData[Node108StartPos + n*260 + 3];
		for (int p=0,k=0;k<128;p+=2,k++)
		{
			NV_AMAM[k] = multiChainResult.oNVitem.aRFNVItemData[Node108StartPos+n*260 + 5+p]*256 + multiChainResult.oNVitem.aRFNVItemData[Node108StartPos +n*260+ 4+p];
			NV_AMPM[k] = multiChainResult.oNVitem.aRFNVItemData[Node108StartPos+(n+1)*260 + 5+p]*256 + multiChainResult.oNVitem.aRFNVItemData[Node108StartPos+(n+1)*260 + 4+p];		
			strMsg.Format("Channel = %d,RGI index = %d ,NV_AMAM = %d ,NV_AMPM = %d",m_vChannelList[iChan],k,NV_AMAM[k],NV_AMPM[k]);
			LogTrace(MSG_MID,strMsg) 
		}
	}
*/

//end by y
	CalPassLog(m_strBand,"_","TX DA And PredistCalibration Pass")
	return true;
}

 bool CGSMTXCal::InitData(
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
 
    

      itrFind=pcSettingMap->find(_T("TesterDeviceUse"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not find TestDeviceUse,use TesterDeviceCommon");
		 //return false;
		 m_piTesterDeviceCurr=m_piTesterDevice;
		 m_strTesterDeviceCurr=m_strTesterDevice;
		 m_strDeviceAddrCurr=m_strDeviceAddr;
	 }
	 else
	 {
		 if(itrFind->second=="TesterDeviceCommon")
		 {
			 m_piTesterDeviceCurr=m_piTesterDevice;
			 m_strTesterDeviceCurr=m_strTesterDevice;
			 m_strDeviceAddrCurr=m_strDeviceAddr;
		 }
	 }

	 itrFind=pcSettingMap->find(_T("Band"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'Band' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iBand=CStr::StrToInt(itrFind->second);
		 m_strBand="GSM"+itrFind->second;
		 m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);
		
/*
		  switch (m_iBand)
		 		 {
		 		 case 850:
		 			 m_iGainParamNVID=6475;  //24972   6475
		 		 	break;
		 		 case 900:
		 			 m_iGainParamNVID=5478;   //24973   5478
		 			 break;
		 		 case 1800:
		 			 m_iGainParamNVID=6476;   //24974   6476
		 			 break;
		 		 case 1900:
		 			 m_iGainParamNVID=6477;   //24975   6477
		 			 break;
		 		 }	*/
 
		 
	 }	

	
		  itrFind=pcSettingMap->find(_T("GainParaNVID"));
		 		 if(itrFind==pcSettingMap->end())
		 		 {
		 			 LogTrace(MSG_ERROR,"Not Find 'GainParaNVID' from ini file!.");
		 			 return false;
		 		 }
		 		 else
		 		 {
		 			 m_iGainParamNVID=CStr::StrToInt(itrFind->second);
		 		 }
		 

	  itrFind=pcSettingMap->find(_T("ChannelList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'ChannelList' from ini file!.");
		 return false;
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vChannelList,strVtr);
	 }	 
	 
	 //m_iChainId   
	 itrFind=pcSettingMap->find(_T("ChainId"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'ChainId' from ini file!.defualt is 0");
		 m_iChainId=0;
	 }
	 else
	 {
		 m_iChainId=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("NVMap"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'NVMap' from ini file!.");
		 CStr::ParseString("1,2,3",",",strVtr);
		 CStr::StrVtr2IntVtr(m_ivNVMap,strVtr);
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2IntVtr(m_ivNVMap,strVtr);
	 }

	 itrFind=pcSettingMap->find(_T("PARange"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'PARange' from ini file!.");
		 return false;
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2IntVtr(m_ivPARange,strVtr);
	 }

	 itrFind=pcSettingMap->find(_T("DAStepDuration"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DAStepDuration' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_idDAStepDuration=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("DATrigRGI"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DATrigRGI' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iDATrigRGI=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("DATrigPA"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DATrigPA' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iDATrigPA=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("DAStartRGI"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DAStartRGI' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iDAStartRGI=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("DAStopRGI"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DAStopRGI' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iDAStopRGI=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("DAStepRGI"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DAStepRGI' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iDAStepRGI=CStr::StrToInt(itrFind->second);	
		 if ((m_iDAStopRGI-m_iDAStartRGI)/m_iDAStepRGI<0)
		 {
			 LogTrace(MSG_ERROR,"'DAStepRGI' is wrong");
			 return false;

		 }
	 }

	 itrFind=pcSettingMap->find(_T("DAMeasOffset"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DAMeasOffset' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iDAMeasOffset=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("DAMeasLength"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DAMeasLength' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iDAMeasLength=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("DATrigeLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DATrigeLimit' from ini file!.");
		 return false;
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2DblVtr(m_dvDATrigeLimit,strVtr);		 
	 }

	 itrFind=pcSettingMap->find(_T("DcDuration"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DcDuration' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iDcDuration=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("EdgeDuration"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'EdgeDuration' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iEdgeDuration=CStr::StrToInt(itrFind->second);		 
	 }
	  itrFind=pcSettingMap->find(_T("DATriggerPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DATriggerPower' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_dDATrigPower=CStr::StrToFloat(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("PreDistRGIPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'PreDistRGIPower' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_dPredisRGIPower=CStr::StrToFloat(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("OverrideSmooothingDefaults"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'OverrideSmooothingDefaults' from ini file!.defult 1");
		 m_iOverrideSmooothingDefaults=1;
	 }
	 else
	 {
		 m_iOverrideSmooothingDefaults=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("EnableAmAmSmoothing"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'EnableAmAmSmoothing' from ini file!.defult 0");
		 m_iEnableAmAmSmoothing=0;
	 }
	 else
	 {
		 m_iEnableAmAmSmoothing=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("AmAmKnot"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'AmAmKnot' from ini file!.defult is 2");
		 m_dAmAmKnot=2;
	 }
	 else
	 {
		 m_dAmAmKnot=CStr::StrToFloat(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("AmPmKnot"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'AmPmKnot' from ini file!.defult 2");
		 m_dAmPmKnot=2;
	 }
	 else
	 {
		 m_dAmPmKnot=CStr::StrToFloat(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("OverRideModemConstants"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'OverRideModemConstants' from ini file!.defult is 1");
		 m_iOverRideModemConstants=1;
	 }
	 else
	 {
		 m_iOverRideModemConstants=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("DigGainUnity"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'DigGainUnity' from ini file!.defult is 64");
		 m_dDigGainUnity=64;
	 }
	 else
	 {
		 m_dDigGainUnity=CStr::StrToFloat(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("RampUnity"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'RampUnity' from ini file!.defult is 8192");
		 m_dRampUnity=8192;
	 }
	 else
	 {
		 m_dRampUnity=CStr::StrToFloat(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("ExtensionFloor"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'ExtensionFloor' from ini file!.defult is 5200");
		 m_dExtensionFloor=5200;
	 }
	 else
	 {
		 m_dExtensionFloor=CStr::StrToFloat(itrFind->second);		 
	 }
	 itrFind=pcSettingMap->find(_T("DacScale"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'DacScale' from ini file!.defult is 4");
		 m_dDacScale=4;
	 }
	 else
	 {
		 m_dDacScale=CStr::StrToFloat(itrFind->second);		 
	 }

	 InitData();
	 return true;
 }
 bool CGSMTXCal::SetGSMCableLoss()
{
   CString strMsg;
     double dLoss;
	m_vCableLoss.clear();
    for(int i=0;i<3;i++)
	{
      if(!m_LossFinder.GetGSMLoss(m_strBand,i,dLoss))
	  {
		  strMsg.Format("GSM Get Loss Band=%s ,ChannelType=%d Fail",m_strBand,i);
          LogTrace(MSG_ERROR,strMsg);
		  CalFailLog(_T("_"),_T("_"),1001,strMsg);
		  return false;
	  }
	  m_vCableLoss.push_back(dLoss);
	}


      
		if(DEVICE_SUCCESS!=m_pFunGSMCalDev->IGSMCalSetLoss(m_iBand,m_vCableLoss))
	   {
			LogTrace(MSG_ERROR,"Set Cableloss device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
			return false;
		  
	   }
        


  return true;
}

 bool CGSMTXCal::InitData()
 {
	 m_pFunGSMCalDev=m_piTesterDevice->m_piFuncGSMCal;
	 return true;
 }