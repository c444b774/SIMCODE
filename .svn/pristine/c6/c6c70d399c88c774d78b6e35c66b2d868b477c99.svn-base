#include "stdafx.h"
#include "GSMTXCal6285.h"

RF_IMPLEMENT_DYNCREATE(CGSMTXCal6285)

CGSMTXCal6285::CGSMTXCal6285()
{
	m_mapClassFunc[_T("GSMTXCalMainFunc6285")]=&CGSMTXCal6285::CGSMTXCalMainFunc6285;
	m_mapClassFunc[_T("TXCSCal6285")]=&CGSMTXCal6285::CGSMTXCSCalFunc6285;
	m_mapClassFunc[_T("TXPolarCal6285")]=&CGSMTXCal6285::CGSMTXPolarCalFunc6285;
	m_mapClassFunc[_T("TXDelayCal6285")]=&CGSMTXCal6285::CGSMTXDelayCalFunc6285;

}

CGSMTXCal6285::~CGSMTXCal6285()
{
	
}

bool CGSMTXCal6285::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSMTXCal6285::Handle()
{
	if(!DoProcess())
	{

		m_pPhone->CloseComport();
		m_pFunGSMCalDev->Deivce_Exit();
		return false;
	}

    

	return true;
}

bool CGSMTXCal6285::CGSMTXCalMainFunc6285()
{
	 if(!SetGSMCableLoss())
		return false;

	 switch(m_iBand)
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
	 }

	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CGSMTXCal6285::CGSMTXDelayCalFunc6285()
{
		unsigned short piStatus=0;
		CString strMsg;
		int iErrorcode;
		double dExpectPower=m_dDATrigPower+2;
		double dDLMhz=0.0;
		double dULMhz=0.0;	
	  	int iRet=0;
		int modIdx=0;
		int pathDelayList=0;
		timeDelay arrtimeDelay[256]={0};
		QMSL_RFCAL_NV_Item TxDelayNV;
		for(int i=m_pathDelayStart;i<=0;i+=4,pathDelayList++)
		{
			arrtimeDelay[pathDelayList].piDelay=i;
		}

		strMsg.Format("Start Path Delay Calibration....");
		LogTrace(MSG_MID,strMsg)
			if((iErrorcode=m_pFunGSMCalDev->IGSMTestInitTxDelay(dExpectPower))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Set Freq device fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Freq device fail");
				return false;
			  
		   }
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
		 dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[0]); 
		 dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[0]);
	
         int iChannel=m_vChannelList[0];
		
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
			if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Set Freq device fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Freq device fail");
				return false;
			  
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
			if((iErrorcode=m_pPhone->FTM_SET_TX_FRAME_MATRIX(0,1,2550,4)!=PHONE_SUCCESS))
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			
			if((iErrorcode=m_pPhone->FTM_SET_TX_ON(true)!=PHONE_SUCCESS))
			{ 
				strMsg.Format("FTM_SET_TX_ON");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			int startdelay=-100;
			for(int i=0;i<pathDelayList;i++)
			{
				if((iErrorcode=m_pPhone->FTM_SET_PATH_DELAY(&arrtimeDelay[i].piDelay)!=PHONE_SUCCESS))
				{
					strMsg.Format("FTM_SET_PATH_DELAY");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				}
				Sleep(50);
				float allmod[255]={0};
				if((iErrorcode=m_pFunGSMCalDev->IGSMTestGetAllMod(allmod))!=DEVICE_SUCCESS)
			   {
					LogTrace(MSG_ERROR,"Set FIGSMCalSetFreq fail");
					CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Freq device fail");
					return false;
				  
			   }
				if(m_strTesterDeviceCurr.Find("8960")!=-1)
				{
					arrtimeDelay[i].modN400=allmod[0];
					arrtimeDelay[i].modP400=allmod[1];
				}
				else
				{
					arrtimeDelay[i].modN400=allmod[29];
					arrtimeDelay[i].modP400=allmod[32];
				}
			}
				float modMin=arrtimeDelay[0].modN400+arrtimeDelay[0].modP400;
				strMsg.Format("Tx pathDelay +400: %lf -400: %lf",arrtimeDelay[0].modP400,arrtimeDelay[0].modN400);
				
				for(int i=0;i<pathDelayList;i++)
				{
					if(modMin<=arrtimeDelay[i].modN400+arrtimeDelay[i].modP400)
					{
						modIdx=i;
						modMin=arrtimeDelay[i].modN400+arrtimeDelay[i].modP400;
					}
					strMsg.Format("Tx pathDelay +400: %lf -400: %lf",arrtimeDelay[i].modP400,arrtimeDelay[i].modN400);
					LogTrace(MSG_MID,strMsg) 
				}
				for (int i=0;i<pathDelayList;i++)
				{
					if(arrtimeDelay[i].modN400>-20||arrtimeDelay[i].modN400>-20)
					{	
						strMsg.Format("RFCAL_GSM_Tx_Delay_Cal_Results");
						PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
							return false;
					}
				}
					
				strMsg.Format("Tx pathDelay find piDelay %d",arrtimeDelay[modIdx].piDelay);
				LogTrace(MSG_MID,strMsg) ;
			//QLIB_RFCAL_GSM_Tx_Delay_Cal_Results
			if((iErrorcode=m_pPhone->RFCAL_GSM_Tx_Delay_Cal_Results(m_iPhoneMode,arrtimeDelay[modIdx].piDelay,&TxDelayNV,1)!=PHONE_SUCCESS))
				{
					strMsg.Format("RFCAL_GSM_Tx_Delay_Cal_Results");
					PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
				}
		
	return true;
}
bool CGSMTXCal6285::CGSMTXCSCalFunc6285()
{
  


	short aiI_DC_Correction[3][300]={0};
	short aiQ_DC_Correction[3][300]={0};
	unsigned short arrSegmentLength[300]={0};
			unsigned short aiSegmentLength=(unsigned short)m_iSegmentTime;
			short findQ=0,findI=0;
			 
			unsigned short piStatus=0;
			 CString strMsg;
			int iErrorcode;
			
	  		int iRet=0;
		   		
			
			float aiPowerlist[3][300]={0};
			float aiPahselist[3][300]={0};
			float aiFErrlist[3][300]={0}; 
		int iChannel=0;
			
			int iStepLengh=3.692*m_iSegmentTime;
			
			
			int iIsShowFrr=0;
            double dExpectPower=m_dDATrigPower+2;
			 double dDLMhz=0.0;
			 double dULMhz=0.0;
		   QMSL_RFCAL_NV_Item csCalNV;
		int add=0;

		for(int j=0;j<41;j++)
		{
				arrSegmentLength[j]=91;
				aiI_DC_Correction[0][j]=-1000+add;					
				aiQ_DC_Correction[0][j]=0;
				add+=50;/*xiaoyang mark , 50 is Trigger offset Add to XML later*/			
		}
		//

		
		strMsg.Format("Start CS Calibration....");
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

	   for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)//this is single channel test ,so ......just put these code there
	   {
		   dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
			dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);
	
           iChannel=m_vChannelList[iCHIndex];


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

		   if((iErrorcode=m_pPhone->FTM_SET_PDM(0,0))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_PDM Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

		      if((iErrorcode=m_pPhone->FTM_SET_PA_DAC_INPUT  (8000/*xiaoyang mark,should add to XML*/)!=PHONE_SUCCESS))
			{ 
				strMsg.Format("FTM_SET_PA_DAC_INPUT!");
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
		
		for(int i=0;i<3;i++)
		{
			if(1==i)
			{
				float minPower=aiPowerlist[0][0];
			    int dsMinpowIdx;
				add=0;
				for(int j=0;j<41;j++)
				{
					if(minPower>=aiPowerlist[0][j])
					{
						minPower=aiPowerlist[0][j];
						dsMinpowIdx=j;
					}
				}
				for(int j=0;j<41;j++)
				{
						aiI_DC_Correction[1][j]=aiI_DC_Correction[0][dsMinpowIdx];					
						aiQ_DC_Correction[1][j]=-1000+add;
						add+=50;/*xiaoyang mark , 50 is Trigger offset Add to XML later*/
				}
			}
			else if(2==i)
			{
				add=0;
				float minPower=aiPowerlist[0][0];
			    int dsMinpowIdx;
				for(int j=0;j<41;j++)
				{
					if(minPower>=aiPowerlist[0][j])
					{
						minPower=aiPowerlist[0][j];
						dsMinpowIdx=j;
					}
				}
				findQ=aiQ_DC_Correction[1][dsMinpowIdx];
				for(int j=0;j<41;j++)
				{
						aiI_DC_Correction[2][j]=-1000+add;					
						aiQ_DC_Correction[2][j]=findQ;
						add+=50;/*xiaoyang mark , 50 is Trigger offset Add to XML later*/
				}
			}

			if((iErrorcode=m_pFunGSMCalDev->IGSMCalInitAMAM_AMPM(dExpectPower,m_iListSize,m_iMeasLength,iStepLengh,91))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Init AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init AMAM_AMPM fail");
				return false;
			  
		   }
			Sleep(850);

			  if((iErrorcode=m_pPhone->FTM_TX_CS_SWEEP (m_iListSize-1,aiI_DC_Correction[i],aiQ_DC_Correction[i],arrSegmentLength,&piStatus))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_TX_CS_SWEEP");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

			  if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchMAM_AMPM_Results(aiPowerlist[iCHIndex],aiPahselist[iCHIndex],aiFErrlist[iCHIndex],m_iListSize))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Fectch AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init AMAM_AMPM fail");
				return false;
			  
		   }
			  for(int i=1;i<42;i++)
			  {
				 aiPowerlist[iCHIndex][i]-=aiPowerlist[iCHIndex][0];//
			  }
			  for(int i=0;i<42;i++)
			  {
				 aiPowerlist[iCHIndex][i]=aiPowerlist[iCHIndex][i+1];//
			  }
			   
		}

				float minPower=aiPowerlist[0][0];
			    int dsMinpowIdx;
				for(int j=0;j<41;j++)
				{
					if(minPower>=aiPowerlist[0][j])
					{
						minPower=aiPowerlist[0][j];
						dsMinpowIdx=j;
					}
				}
		findI=aiI_DC_Correction[2][dsMinpowIdx];
		//find minPower;QLIB_RFCAL_GSM_CARRIER_SUPRRESSION
		    
	   }

		 
	   if((iErrorcode=m_pPhone->RFCAL_GSM_Carrier_Suppression(m_iPhoneMode,findI,findQ,&csCalNV,1))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("RFCAL_GSM_Carrier_Suppression fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 

	   strMsg.Format("CS CAL:Channel: %d findI:%d findQ:%d",iChannel,findI,findQ);
			LogTrace(MSG_MID,strMsg);
    CalPassLog(m_strBand,"_","TX CS Calibration Pass")
	return true;
}
bool CGSMTXCal6285::CGSMTXPolarCalFunc6285()
{
  
	int iErrorcode;
    int iRet=0;
					
				
			
	 CString strMsg;
	  
	 double dDLMhz=0.0;
	 double dULMhz=0.0;
	int moveidx=0;
//	QMSL_GSM_Polar_Cal_Result 
	 
	int iChannel;
	double ExpertPower=0;
	float aiPowerlist[512]={0};
	float aiPahselist[512]={0};
	float aiFErrlist[512]={0}; 
	 unsigned long polar_dacList[2][512]={0};

	 unsigned short aiSegmentLength=(unsigned short)m_iSegmentTime;
     double dExpectPower=m_dDATrigPower;
	double dStepLengh=1024.01;
	int maxPowIdx=0;
	
	int stepsize=85;
	int steps=(stopDac-startDac)/stepsize+1;
	int total_steps=(steps)*2+1;
	QMSL_GSM_Polar_Cal_Measurement polarmes,polarprossessed;
	memset(&polarmes,0,sizeof(QMSL_GSM_Polar_Cal_Measurement));
	memset(&polarprossessed,0,sizeof(QMSL_GSM_Polar_Cal_Measurement));

	QMSL_GSM_Polar_Cal_Result polarRes={0};
	QMSL_GSM_Polar_Cal_NV_struct polarNv={0};
	 //memset(&calResult,0,sizeof(QMSL_GSM_PreDist_Cal_Result));
   
/////////////////////////// initilize aiPowerlist

	polar_dacList[0][0]=stopDac;
	polar_dacList[1][0]=13;
	int dacadd=0;
	for(int i=total_steps;i>0;i--)
	{
		polar_dacList[1][i]=13;
		if(i%2==1)
			polar_dacList[0][i] = 4500;
		else
		{
			polar_dacList[0][i] = stopDac-dacadd;
			dacadd+=stepsize;
		}
	}
	total_steps++;


	////////////////////////////
	   

	
     strMsg="Start PolarCal Calibration"; 
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
	   	 	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	   for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
	   {
		   iChannel=m_vChannelList[iCHIndex];  
		    dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
			dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);
		   
			

			
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
			
		      strMsg.Format("Init AMAM_AMPM  Device......."); 
			LogTrace(MSG_MID,strMsg)
			
          	if((iErrorcode=m_pFunGSMCalDev->IGSMCalInitAMAM_AMPM(dExpectPower,total_steps,m_iMeasLength,dStepLengh,150,"WIDE"))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Init AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init AMAM_AMPM fail");
				return false;
			  
		   }
			Sleep(850);
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(17))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			   if((iErrorcode=m_pPhone->FTM_GSM_POLAR_TX_SWEEP_CAL(total_steps,polar_dacList[0],polar_dacList[1]))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_GSM_LINEAR_PA_RANGE Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
			  if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE_ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			} 
		 
			
           
            Sleep(200);

              
			if((iErrorcode=m_pFunGSMCalDev->IGSMCalFetchMAM_AMPM_Results(aiPowerlist,aiPahselist,aiFErrlist,total_steps))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Fectch AMAM_AMPM fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"Init AMAM_AMPM fail");
				return false;
			  
		   }
			
			
	
			
			for(int i=0;i<total_steps;i++)
			{
				polarmes.aPolar_Cal_Sweep_Result[i].amp_dBm=aiPowerlist[i];
				polarmes.aPolar_Cal_Sweep_Result[i].phase_rad=(double)aiPahselist[i]*(3.141592/180);
				
				polarmes.aPolar_Cal_Sweep_Result[i].dac=polar_dacList[0][i];
				polarmes.aPolar_Cal_Sweep_Result[i].duration_counts=13;
			}
			polarmes.iNumOfPoloarCalSweepRecord=total_steps;
			m_pPhone->RFCAL_GSM_Tx_Polar_ProcessTxSweep(&polarmes,&polarprossessed);
		
			/*for(int i =0;i<300;i++)
			{
				if(polarprossessed.aPolar_Cal_Sweep_Result[i]>
			}*/
			/*bool needunwrap=true;
			for(int i=0;i<299;i++)
			{
				if(aiPahselist[i]>180||aiPahselist[i]<-180)
				{
					needunwrap=false;
					break;
				}
			}
			if(needunwrap)
			{
				for(int i=0;i<299;i++)
				{
					if((aiPahselist[i]+360>180)&&aiPahselist[i]+360<360)
						aiPahselist[i]+=360;					
				}
			}*/
			/*
			for(int i=0;i<299;i++)
			{
				polar_dacList[0][i]=polar_dacList[0][i+1];
				aiPowerlist[i]=aiPowerlist[i+1];
				aiPahselist[i]=aiPahselist[i+1];
				aiPahselist[i]=aiPahselist[i]*(3.141592/180);
			}
		
		
			for(int i=1;i<299;i++)
			{
				if(i%2==1)
					aiPahselist[i]-=((aiPahselist[i-1]+aiPahselist[i+1])/2);
			}



			
			moveidx=0;
			for(int i=1;i<299;i++)
			{
				if(i%2==1)
				{
					aiPahselist[moveidx]=aiPahselist[i];
					aiPowerlist[moveidx]=aiPowerlist[i];
					polar_dacList[0][moveidx]=polar_dacList[0][i];
					moveidx++;
				}
			}*/
			//findmax

			
			int maxPowIdx=0;
			for(int i=0;i<total_steps;i++)
			{
				if(polarprossessed.aPolar_Cal_Sweep_Result[i].amp_dBm>dNVMinPower)
				{
					maxPowIdx=i-1;
					break;
				}
			}
			double max=polarprossessed.aPolar_Cal_Sweep_Result[maxPowIdx].phase_rad;//max power index from HTML log
			int maxidx=0;
			for(int i=maxPowIdx;i<total_steps;i++)
			{
				
				if(max<=polarprossessed.aPolar_Cal_Sweep_Result[i].phase_rad)
					{
						max=polarprossessed.aPolar_Cal_Sweep_Result[i].phase_rad;
						maxidx=i;
					}
				
			}
		    double shiftto3=3.0-max;
			for(int i=0;i<total_steps;i++)
			{
				polarprossessed.aPolar_Cal_Sweep_Result[i].phase_rad+=shiftto3;
			}
		}
		
		
	//	memset(&polarRes,0,sizeof(QMSL_GSM_Polar_Cal_Result));
	//	memset(&polarNv,0,sizeof(QMSL_GSM_Polar_Cal_NV_struct));
		

		
	//polarprossessed
		memcpy(&polarRes.aPolar_Cal_Sweep_Result,&polarprossessed,sizeof(QMSL_GSM_Polar_Cal_Measurement));
		//polarRes
		/*for(int i =0;i<149;i++)
		{
			polarRes.aPolar_Cal_Sweep_Result[i].amp_dBm=(double)aiPowerlist[i+maxPowIdx];
			polarRes.aPolar_Cal_Sweep_Result[i].dac=polar_dacList[0][i+maxPowIdx];
			polarRes.aPolar_Cal_Sweep_Result[i].duration_counts=polar_dacList[1][i+maxPowIdx];
			polarRes.aPolar_Cal_Sweep_Result[i].phase_rad=(double)aiPahselist[i+maxPowIdx];

		}*/
		polarRes.dNVMaxPower=dNVMaxPower;// this should from xml
		polarRes.dNVMinPower=dNVMinPower;// this should from xml
		polarRes.dSmoothingWindowSize=3;// this should from xml
		polarRes.iChannel=iChannel;
		polarRes.iFreqnecyLocation=(QMSL_GSM_Polar_Cal_Frequency)iFreqnecyLocation;// this should from xml
		polarRes.iNumOfPoloarCalSweepRecord=polarprossessed.iNumOfPoloarCalSweepRecord;
		bool isPass=false;
		for(int i=0;i<total_steps;i++)
		{
			if(polarprossessed.aPolar_Cal_Sweep_Result[i].amp_dBm>dNVMaxPower-2) //Changed by Strong  for exe crashed issue
			{
				isPass=true;
				break;
			}
		}
		if(!isPass)
		{
			LogTrace(MSG_ERROR,"RFCAL_GSM_Tx_Polar_Cal_fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"RFCAL_GSM_Tx_Polar_Cal_fail");
				return false;
		}
		if(iErrorcode=m_pPhone->RFCAL_GSM_Tx_Polar_Cal_Results(m_iPhoneMode,&polarRes,&polarNv,1)!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"RFCAL_GSM_Tx_Polar_Cal_Results fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"RFCAL_GSM_Tx_Polar_Cal_Results fail");
				return false;
		}
		/*
		   long	dac;

		   //! Duration count
		   long	duration_counts;

		   //! Amplitude in dBm
		   double	amp_dBm;

		   //! Phase in Radian
		   double	phase_rad;
		*/
		for(int i =0;i<polarRes.iNumOfPoloarCalSweepRecord;i++)
		{
			strMsg.Format("Polar channel: %d,dac %d , dbm %lf, phase %lf",iChannel,polarRes.aPolar_Cal_Sweep_Result[i].dac,polarRes.aPolar_Cal_Sweep_Result[i].amp_dBm,polarRes.aPolar_Cal_Sweep_Result[i].phase_rad);
			LogTrace(MSG_MID,strMsg);
		}
		//QMSL_GSM_Polar_Cal_Measurement(
	// QLIB_RFCAL_GSM_Tx_Polar_Cal_Results






	CalPassLog(m_strBand,"_","TX PolarCalibration Pass");
	return true;
}

 bool CGSMTXCal6285::InitData(
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
     
	  itrFind=pcSettingMap->find(_T("ListSize"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'ListSize' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iListSize=CStr::StrToInt(itrFind->second);
	 }


	  itrFind=pcSettingMap->find(_T("PARangeNum"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'PARangeNum' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iRangeNum=CStr::StrToInt(itrFind->second);
	 }






    /*
		double dNVMaxPower;// this should from xml
		double dNVMinPower;// this should from xml
		double dSmoothingWindowSize;// this should from xml
		
		int iFreqnecyLocation=0;// 
	*/
		  itrFind=pcSettingMap->find(_T("PolarMaxPower"));
			 if(itrFind==pcSettingMap->end())
			 {
				dNVMaxPower=30;
				
			 }
			 else
			 {
				dNVMaxPower=CStr::StrToFloat(itrFind->second);
			 }


			itrFind=pcSettingMap->find(_T("PolarMinPower"));
			 if(itrFind==pcSettingMap->end())
			 {
				 dNVMinPower=-12;
			 }
			 else
			 {
				dNVMinPower=CStr::StrToFloat(itrFind->second);
			 }

			itrFind=pcSettingMap->find(_T("SmoothingWindowSize"));
			 if(itrFind==pcSettingMap->end())
			 {
				dSmoothingWindowSize=3;
			 }
			 else
			 {
				dSmoothingWindowSize=CStr::StrToFloat(itrFind->second);
			 }


			itrFind=pcSettingMap->find(_T("FreqnecyLocation"));
			 if(itrFind==pcSettingMap->end())
			 {
				iFreqnecyLocation=1;
			 }
			 else
			 {
				iFreqnecyLocation=CStr::StrToInt(itrFind->second);
			 }








	  itrFind=pcSettingMap->find(_T("SegmentTime"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'SegmentTime' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iSegmentTime=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("MeasLenUS"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'MeasLenUS' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iMeasLength=CStr::StrToInt(itrFind->second);
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
		//m_pathDelayStart
	  itrFind=pcSettingMap->find(_T("pathDelayStart"));
	 if(itrFind==pcSettingMap->end())
	 {
		m_pathDelayStart=-100;
	 }
	 else
	 {
		 m_pathDelayStart=CStr::StrToInt(itrFind->second);
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

	   itrFind=pcSettingMap->find(_T("startDac"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'startDac' from ini file!.");
		startDac=1715;    
	 }
	 else
	 {
		 startDac=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("stopDac"));
	 if(itrFind==pcSettingMap->end())
	 {
		LogTrace(MSG_ERROR,"Not Find 'stopDac' from ini file!.");
		stopDac=14295;
	 }
	 else
	 {
		 stopDac=CStr::StrToInt(itrFind->second);
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

	 InitData();
	 return true;
 }
 bool CGSMTXCal6285::SetGSMCableLoss()
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

 bool CGSMTXCal6285::InitData()
 {
	 m_pFunGSMCalDev=m_piTesterDevice->m_piFuncGSMCal;
	 return true;
 }