#include "StdAfx.h"
#include "FuncWCDMACal_CMW.h"

CFunWCDMACal_CMW::CFunWCDMACal_CMW(void)
{
}

CFunWCDMACal_CMW::~CFunWCDMACal_CMW(void)
{
  
}

CFunWCDMACal_CMW::CFunWCDMACal_CMW(PCTesterDevice pDev):CFuncDev_CMW(pDev)
{
   
}

int CFunWCDMACal_CMW::IWCDMACalInit(const CString& strAddr)
{
     CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;



	   strCmd=_T("*RST");
	   DEVICE_WRITE(strCmd)

	      strCmd=_T("*CLS");
	   DEVICE_WRITE(strCmd)
      
	  strCmd=_T("*OPC?");
      DEVICE_QUERY_DELAY(strCmd,100)

	
	  
   return DEVICE_SUCCESS;  
}

int CFunWCDMACal_CMW::SetInput(int iInput)
{
	 CString strCmd;
    int iDeviceErr;

     int iConnector;
	 
	
     if(iInput==1 || iInput==3)
     iConnector=1;
	 else
	  iConnector=2;

	  if(m_pTesterDevice->m_bIsCommandRX1CMW)
	 strCmd.Format("ROUTe:GPRF:MEAS%d:SCENario:SALone RF%dC,RX1",m_pTesterDevice->m_iChannelPort,iConnector);
	  else
      strCmd.Format("ROUTe:GPRF:MEAS%d:SCENario:SALone RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 	m_pTesterDevice->m_iInputPort=iInput;
	   
    return DEVICE_SUCCESS;  
}
int CFunWCDMACal_CMW::SetOutput(int iOutput)
{

     CString strCmd;
     int iDeviceErr;
     int iConnector;
	 
	    if(iOutput==1 || iOutput==3)
     iConnector=1;
	 else
	  iConnector=2;

	 strCmd.Format("ROUTe:GPRF:GEN%d:RFS:CONN RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  m_pTesterDevice->m_iOutputPort=iOutput;
	  return DEVICE_SUCCESS;  

}
int  CFunWCDMACal_CMW::IWCDMACalSetMaxPower(double dMaxPower)
{

	 CString strCmd;
   int iDeviceErr;

   
   strCmd.Format("CONF:GPRF:MEAS%d:RFS:ENP %4.4f;*OPC?",m_pTesterDevice->m_iChannelPort,dMaxPower);
   DEVICE_QUERY(strCmd)
 
   strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:UMARgin 5;*OPC?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)
 
   strCmd.Format("CONF:GPRF:MEAS%d:POW:FILT:TYPE WCDMA;*OPC?",m_pTesterDevice->m_iChannelPort);
  DEVICE_QUERY(strCmd)

	    strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST OFF",m_pTesterDevice->m_iChannelPort);
		 DEVICE_WRITE(strCmd)

   return DEVICE_SUCCESS;  

}
int CFunWCDMACal_CMW::IWCDMAFetchTXRXResults(DblVtr & dvtrResults)
{
     CString strCmd;
   int iDeviceErr;
   int iRetryTimes=20;
   CStringVtr strVtr;
   DblVtr     dVtr;
   CString strRes;
    do
	{
             strCmd.Format("FETC:GPRF:MEAS%d:POW:STAT?",m_pTesterDevice->m_iChannelPort);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("RDY")!=-1)
	     break;

       Sleep(500);
	}while(--iRetryTimes>0);

		   if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

    
       strCmd.Format("FETC:GPRF:MEAS%d:POW:CURR?",m_pTesterDevice->m_iChannelPort);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtr,strVtr);
       dvtrResults.assign(dVtr.begin()+1,dVtr.end());

	     strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST OFF",m_pTesterDevice->m_iChannelPort);
		 DEVICE_WRITE(strCmd)

			 strCmd.Format("SOUR:GPRF:GEN%d:LIST OFF",m_pTesterDevice->m_iChannelPort);
		 DEVICE_WRITE(strCmd)

			 strCmd.Format("SOUR:GPRF:GEN%d:STAT OFF",m_pTesterDevice->m_iChannelPort);
		 DEVICE_WRITE(strCmd)

	     strCmd.Format("ABORT:GPRF:MEAS%d:POW",m_pTesterDevice->m_iChannelPort);
		 DEVICE_WRITE(strCmd)
       return DEVICE_SUCCESS;



}
int CFunWCDMACal_CMW::IWCDMAESCalLinearconfig(int Mod,double dBandWidth,int iSegmentTime,DblVtr dvTRxFreq,DblVtr dvTxLvlRef,DblVtr dvRxLvl,int iNumSegment,int iNumSequence)
{
	CString strCmd,strBuff,strRes;
	int iDeviceErr;

	char cCmd[4096]="";

		//MEAS************************************************
		strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:FREQ:ALL %4.1fMHZ",m_pTesterDevice->m_iChannelPort,dvTRxFreq[1]);
	for (int iloop=0;iloop<iNumSequence;iloop++)
	{
		int jloop =0;
		if (0==iloop)
		{
			jloop=1;
		} 
		
		for (;jloop<iNumSegment;jloop++)
		{
			strBuff.Format(",%4.1fMHZ",dvTRxFreq[2*iloop+1]);	
			strCmd=strCmd+strBuff;
		}
		
	}
	DEVICE_WRITE(strCmd)
	dvTxLvlRef.push_back(iNumSegment);
		strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:ENP:ALL %.2f",m_pTesterDevice->m_iChannelPort,dvTxLvlRef[0]);
	for (int iloop=0;iloop<iNumSequence;iloop++)
	{
		int jloop =0;
		int kloop=0;
		int lloop=0;
		if (0==iloop)
		{
			jloop=1;
			
		} 

		for (;jloop<iNumSegment;jloop++)
		{

			for (int kloop=0;kloop<(dvTxLvlRef.size()+1)/2;kloop++)
			{
				if (jloop<dvTxLvlRef[kloop*2+1])
				{
					strBuff.Format(",%.2f",dvTxLvlRef[2*kloop]);	
					strCmd=strCmd+strBuff;
					break;

				}
			}

		}

	}
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:POW:SLEN %f",m_pTesterDevice->m_iChannelPort,iSegmentTime/1000.0);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONF:GPRF:MEAS%d:POW:MLEN %f",m_pTesterDevice->m_iChannelPort,0.8*iSegmentTime/1000.0);
	DEVICE_WRITE(strCmd)

		strCmd.Format("TRIG:GPRF:MEAS%d:POW:OFFS %f",m_pTesterDevice->m_iChannelPort,iSegmentTime/10000.0);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:STAR 0",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:STOP %d",m_pTesterDevice->m_iChannelPort,iNumSegment*iNumSequence-1);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONF:GPRF:MEAS%d:POW:SCO 1",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:POW:REP SING",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:RFS:UMAR 10",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:POW:FILT:TYPE BAND",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:POW:FILT:BAND:BWID %2.0fMHz",m_pTesterDevice->m_iChannelPort,dBandWidth);
	DEVICE_WRITE(strCmd)

		strCmd.Format("TRIG:GPRF:MEAS%d:POW:SOUR \'IF Power\'",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("TRIG:GPRF:MEAS%d:POW:THR -25",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("TRIG:GPRF:MEAS%d:POW:SLOP REDG",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("TRIG:GPRF:MEAS%d:POW:TOUT 5.632",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("TRIG:GPRF:MEAS%d:POW:MODE ONCE",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("TRIG:GPRF:MEAS%d:POW:MGAP 0.061",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:GPRF:MEAS%d:POW:TOUT 10.632",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)
		//*********************************************************
		strCmd.Format("SOUR:GPRF:GEN%d:LIST ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN%d:BBM CW",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONF:SELF:REF:FREQ:SOUR INT");
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOURce:GPRF:GEN%d:LIST:INCRement \'GPRF Meas1: Power\'",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN%d:LIST:MODE BBM",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN%d:LIST:STAR 0",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN%d:LIST:STOP %d",m_pTesterDevice->m_iChannelPort,iNumSegment*iNumSequence -1);
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN%d:LIST:FREQ:ALL %4.1fMHZ",m_pTesterDevice->m_iChannelPort,dvTRxFreq[0]);
	for (int iloop=0;iloop<iNumSequence;iloop++)
	{
		int jloop =0;
		if (0==iloop)
		{
			jloop=1;
		} 

		for (;jloop<iNumSegment;jloop++)
		{
			strBuff.Format(",%4.1fMHZ",dvTRxFreq[2*iloop]);	
			strCmd=strCmd+strBuff;
		}

	}
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN%d:LIST:RFL:ALL %.2f",m_pTesterDevice->m_iChannelPort,dvRxLvl[0]);
	for (int iloop=0;iloop<iNumSequence;iloop++)
	{
		int jloop =0;
		if (0==iloop)
		{
			jloop=1;
		} 

		for (;jloop<iNumSegment;jloop++)
		{
			if (jloop<dvRxLvl.size())
			{
				strBuff.Format(",%.2f",dvRxLvl[jloop]);	
				strCmd=strCmd+strBuff;
			}
			else
			{
				strBuff.Format(",%.2f",dvRxLvl[dvRxLvl.size()-1]);	
				strCmd=strCmd+strBuff;

			}
			
		}

	}
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN%d:LIST:MOD:ALL ON",m_pTesterDevice->m_iChannelPort);	
	for (int iloop=0;iloop<iNumSequence*iNumSegment;iloop++)
	{
		strBuff.Format(",ON");	
		strCmd=strCmd+strBuff;

	}
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN%d:STAT ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("ABOR:GPRF:MEAS%d:POW;",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("INIT:GPRF:MEAS%d:POW;*OPC?",m_pTesterDevice->m_iChannelPort);
	DEVICE_QUERY(strCmd)

	int iRetryTimes=5;
		do
		{
			Sleep(40);
			strRes=Device_GetReadBuf();
			if(strRes.Find("1")!=-1)
				break;
		}while(--iRetryTimes>0);


	return DEVICE_SUCCESS;  

}

int CFunWCDMACal_CMW::IWCDMASetupTXRXComposite(double * dUlFreqMHz,double * dDLFreqMHz,int iNumSteps,double *dRxPowerList,double *dTxMaxLevList)
{
	 CString strCmd;
   int iDeviceErr;

   char cCmd[4096]="";

    strCmd.Format("CONF:GPRF:MEAS%d:RFS:ENP %.2f;*OPC?",m_pTesterDevice->m_iChannelPort,29.0);
   DEVICE_QUERY(strCmd)

	strCmd.Format("CONF:SELF:REF:FREQ:SOUR INT");
   DEVICE_WRITE(strCmd)

     strCmd.Format("SOUR:GPRF:GEN%d:LIST:MODE BBM",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	 strCmd.Format("SOUR:GPRF:GEN%d:LIST:STAR 0",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

     strCmd.Format("SOUR:GPRF:GEN%d:LIST:STOP %d",m_pTesterDevice->m_iChannelPort,(iNumSteps+1)*(FTM_TX_RX_FREQ_MAX_FREQUENCIES) -1);
   DEVICE_WRITE(strCmd)

     strCmd.Format("SOUR:GPRF:GEN%d:LIST ON",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("SOUR:GPRF:GEN%d:LIST ON",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:POW:SLEN 0.02",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	    strCmd.Format("CONF:GPRF:MEAS%d:POW:MLEN 0.018666",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:POW:SCO 1",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	    strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST ON",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:OFFS 0.000667",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:RFS:UMAR 10",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:STAR 0",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:STOP %d",m_pTesterDevice->m_iChannelPort,(iNumSteps+1)*(FTM_TX_RX_FREQ_MAX_FREQUENCIES) -1);
   DEVICE_WRITE(strCmd)

	    strCmd.Format("TRIG:GPRF:MEAS%d:POW:SOUR \'IF Power\'",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	    strCmd.Format("TRIG:GPRF:MEAS%d:POW:THR -30",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	    strCmd.Format("TRIG:GPRF:MEAS%d:POW:SLOP REDG",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   sprintf(cCmd,  "SOUR:GPRF:GEN%d:LIST:FREQ:ALL %4.1fMHZ",m_pTesterDevice->m_iChannelPort,dDLFreqMHz[0]);
	for(int i = 0 ; i< FTM_TX_RX_FREQ_MAX_FREQUENCIES; i++)
	{
		int j = 1;
		if(i != 0)
		{
			j=0;
		}
	    for(; j < (iNumSteps+1) ; j++)
			sprintf(cCmd,  "%s, %4.1fMHZ",cCmd, dDLFreqMHz[i]);
	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)

		sprintf(cCmd,  "CONF:GPRF:MEAS%d:POW:LIST:FREQ:ALL %4.1fMHZ",m_pTesterDevice->m_iChannelPort,dUlFreqMHz[0]);
	for(int i = 0 ; i< FTM_TX_RX_FREQ_MAX_FREQUENCIES; i++)
	{
		int j = 1;
		if(i != 0)
		{
			j=0;
		}
		for(; j < (iNumSteps+1) ; j++)
			sprintf(cCmd,  "%s, %4.1fMHZ",cCmd, dUlFreqMHz[i]);
	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)

	    sprintf(cCmd,  "SOUR:GPRF:GEN%d:LIST:RFL:ALL %3.1f",m_pTesterDevice->m_iChannelPort,dRxPowerList[0]);//for primary chain
	for(int i = 0 ; i< FTM_TX_RX_FREQ_MAX_FREQUENCIES; i++)
	{
		int j = 1;
		if(i != 0)
		{
			j=0;
		}
		for(; j < (iNumSteps+1) ; j++)
			sprintf(cCmd,  "%s, %3.1f", cCmd,dRxPowerList[j]);//for primary chain
	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)

	    sprintf(cCmd,  "CONF:GPRF:MEAS%d:POW:LIST:ENP:ALL %3.1f", m_pTesterDevice->m_iChannelPort,dTxMaxLevList[0]);//for primary chain
	for(int i = 0 ; i< FTM_TX_RX_FREQ_MAX_FREQUENCIES; i++)
	{
		int j = 1;
		if(i != 0)
		{
			j=0;
		}
		for(; j < (iNumSteps+1) ; j++)
			sprintf(cCmd,  "%s, %3.1f",cCmd, dTxMaxLevList[j]);//for primary chain
	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)

	sprintf(cCmd,  "SOUR:GPRF:GEN%d:LIST:MOD:ALL ON", m_pTesterDevice->m_iChannelPort);
	for(int i=0;i<(iNumSteps+1)*FTM_TX_RX_FREQ_MAX_FREQUENCIES-1;++i)
	{
         
		  sprintf(cCmd,  "%s, ON",cCmd);  

	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)


	
	strCmd.Format("INIT:GPRF:MEAS%d:POW;*OPC?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)

	   Sleep(600);
	 return DEVICE_SUCCESS;  

}
int CFunWCDMACal_CMW::IWCDMAFetchCPRResult(int iMeasCount,double & dCPWR)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   int iRetryTimes=20; 
   CStringVtr vtrResults;

   strCmd.Format("TRIG:GPRF:MEAS%d:POW:SOUR \'Free Run\'",m_pTesterDevice->m_iChannelPort,iMeasCount);
   DEVICE_WRITE(strCmd)


	  strCmd.Format("CONF:GPRF:MEAS%d:POW:REP SING",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

  strCmd.Format("CONF:GPRF:MEAS%d:POW:SCO %d",m_pTesterDevice->m_iChannelPort,iMeasCount);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("READ:GPRF:MEAS%d:POW:CURR?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",vtrResults);
	dCPWR=CStr::StrToFloat(vtrResults[1]);

	  strCmd.Format("ABORT:GPRF:MEAS%d:POW",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;  
}
int CFunWCDMACal_CMW::IWCDMAFetchWTDPResults(DblVtr & dvtrResults)
{
    CString strCmd;
   int iDeviceErr;
   int iRetryTimes=20;
   CStringVtr strVtr;
   DblVtr     dVtr;
   CString strRes;
    do
	{
             strCmd.Format("FETC:GPRF:MEAS%d:POW:STAT?",m_pTesterDevice->m_iChannelPort);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("RDY")!=-1)
	     break;

       Sleep(500);
	}while(--iRetryTimes>0);

		   if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

    
       strCmd.Format("FETC:GPRF:MEAS%d:POW:CURR?",m_pTesterDevice->m_iChannelPort);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtr,strVtr);
       dvtrResults.assign(dVtr.begin()+1,dVtr.end());

	     strCmd.Format("ABORT:GPRF:MEAS%d:POW",m_pTesterDevice->m_iChannelPort);
		 DEVICE_WRITE(strCmd)
       return DEVICE_SUCCESS;
}
int CFunWCDMACal_CMW::IWCDMASetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
    char cCmd[2048]="";

	  strCmd.Format("CONF:GPRF:MEAS%d:POW:REP SING",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
   strCmd.Format("CONF:GPRF:MEAS%d:POW:SCO 1",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

   strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:STAR 0",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
  
	   
   strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:STOP %d",m_pTesterDevice->m_iChannelPort,iCount-1);
   DEVICE_WRITE(strCmd)

   sprintf(cCmd, "CONF:GPRF:MEAS%d:POW:LIST:FREQ:ALL %4.3fMHZ",m_pTesterDevice->m_iChannelPort,dULFreqMHz);
	for(int i = 1 ; i < iCount; i++)
	{
		sprintf(cCmd, "%s,%4.3fMHZ", cCmd, dULFreqMHz);
	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)

	 sprintf(cCmd, "CONF:GPRF:MEAS%d:POW:LIST:ENP:ALL %4.4f",m_pTesterDevice->m_iChannelPort,dMaxinputPwl);
	for(int i = 1 ; i < iCount; i++)
	{
		sprintf(cCmd, "%s,%4.4f", cCmd, dMaxinputPwl);
	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)

  
   
   strCmd.Format("TRIG:GPRF:MEAS%d:POW:OFFS 667us",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)

   strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:SLOP REDG",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
   strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:THR -27",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
   strCmd.Format("CONF:GPRF:MEAS%d:POW:SLEN 20ms",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    strCmd.Format("CONF:GPRF:MEAS%d:POW:MLEN 18ms",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    strCmd.Format("TRIG:GPRF:MEAS%d:POW:MGAP 0.002",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:TOUT 5",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:MODE ONCE",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    strCmd.Format("TRIG:GPRF:MEAS%d:POWer:SOUR \'IF Power\';*OPC?",m_pTesterDevice->m_iChannelPort);
  DEVICE_QUERY(strCmd)
	   strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST ON;*OPC?",m_pTesterDevice->m_iChannelPort);
  DEVICE_QUERY(strCmd)
	  strCmd.Format("INIT:GPRF:MEAS%d:POW;*OPC?",m_pTesterDevice->m_iChannelPort);
  DEVICE_QUERY(strCmd)

   return DEVICE_SUCCESS;  
}

int CFunWCDMACal_CMW::IWCDMACalSetChannel(int iBand,int iULChannel)
{


   return DEVICE_SUCCESS;

}
int  CFunWCDMACal_CMW::IWCDMACalSetLoss(int iWCDMABand,const DblVtr & vLossList)
{
     CString strCmd;
	 int iDeviceErr;
   
	CString strRes;
 
	 strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:DELete \'mytable\'");
	 DEVICE_WRITE(strCmd)
     strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:CREate \'mytable\'");
	 DEVICE_WRITE(strCmd)

	 

	switch(iWCDMABand)
	{
	case 2100:
     
        strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2112.6 MHZ ,%.2f ,1922.6 MHZ,%.2f,2140 MHZ,%.2f,1950 MHZ,%.2f,2167.4 MHZ,%.2f,1977.4 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
         
		break;
	case 1900:
        	 
		 strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1854.2 MHZ ,%.2f ,1934.2 MHZ,%.2f,1880 MHZ,%.2f,1960 MHZ,%.2f,1906.6 MHZ,%.2f,1986.6 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;

	case 1500:
      
		 strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1478.4 MHZ ,%.2f ,1430.4 MHZ,%.2f,1486 MHZ,%.2f,1438 MHZ,%.2f,1493.4 MHZ,%.2f,1445.4 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;

	 case 900:
       
		strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 882.4 MHZ ,%.2f ,927.4 MHZ,%.2f,897.6 MHZ,%.2f,942.6 MHZ,%.2f,912.6 MHZ,%.2f,957.6 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;

	  case 850:
         strCmd.Format("SYST:CORR:FREQ 871.4 MHZ,826.4 MHZ,881.8 MHZ,836.8 MHZ,891.6 MHZ,846.6 MHZ");
		 DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 871.4 MHZ ,%.2f ,826.4 MHZ,%.2f,881.8 MHZ,%.2f,836.8 MHZ,%.2f,891.6 MHZ,%.2f,846.6 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;
      
		default:
		return DEVICE_WRITE_FAIL;
	}

	 strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	 DEVICE_WRITE(strCmd)

		 strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	 DEVICE_WRITE(strCmd)

	 strCmd.Format("CONFigure:FDCorrection:ACTivate RF%dC,\'mytable\',TX",m_pTesterDevice->m_iOutputPort);
	 DEVICE_WRITE(strCmd)

	  strCmd.Format("CONFigure:FDCorrection:ACTivate RF%dC,\'mytable\',RX",m_pTesterDevice->m_iInputPort);
	 DEVICE_WRITE(strCmd)

    return DEVICE_SUCCESS;
}
int  CFunWCDMACal_CMW::ILTECalSetLoss(int iBand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;

	strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:DELete \'mytable\'");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:CREate \'mytable\'");
	DEVICE_WRITE(strCmd)



		switch(iBand)
	{

		case 1:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2110 MHZ ,%.2f ,2140 MHZ,%.2f,2170 MHZ,%.2f,1920 MHZ,%.2f,1950 MHZ,%.2f,1980 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 2:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1930 MHZ ,%.2f ,1960 MHZ,%.2f,1990 MHZ,%.2f,1850 MHZ,%.2f,1880 MHZ,%.2f,1909 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 3:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1805 MHZ ,%.2f ,1711 MHZ,%.2f,1843 MHZ,%.2f,1748 MHZ,%.2f,1880 MHZ,%.2f,1785 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 4:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2110 MHZ ,%.2f ,1710 MHZ,%.2f,2132 MHZ,%.2f,1732 MHZ,%.2f,2155 MHZ,%.2f,1755 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 5:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 869 MHZ ,%.2f ,824 MHZ,%.2f,882 MHZ,%.2f,837 MHZ,%.2f,894 MHZ,%.2f,849 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 7:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2620 MHZ ,%.2f ,2500 MHZ,%.2f,2656 MHZ,%.2f,2536 MHZ,%.2f,2690 MHZ,%.2f,2570 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 8:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 925 MHZ ,%.2f ,880 MHZ,%.2f,942 MHZ,%.2f,897 MHZ,%.2f,960 MHZ,%.2f,915 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 12:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 728 MHZ ,%.2f ,698 MHZ,%.2f,737 MHZ,%.2f,707 MHZ,%.2f,746 MHZ,%.2f,716 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 14:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 758 MHZ ,%.2f ,788 MHZ,%.2f,763 MHZ,%.2f,793 MHZ,%.2f,768 MHZ,%.2f,798 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 17:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 734 MHZ ,%.2f ,704 MHZ,%.2f,740 MHZ,%.2f,710 MHZ,%.2f,746 MHZ,%.2f,716 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 19:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 830 MHZ ,%.2f ,875 MHZ,%.2f,837 MHZ,%.2f,882 MHZ,%.2f,845 MHZ,%.2f,890 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 20:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 791 MHZ ,%.2f ,832 MHZ,%.2f,806 MHZ,%.2f,847 MHZ,%.2f,821 MHZ,%.2f,862 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 21:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1448 MHZ ,%.2f ,1496 MHZ,%.2f,1455 MHZ,%.2f,1503 MHZ,%.2f,1463 MHZ,%.2f,1511 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 25:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1930 MHZ ,%.2f ,1850 MHZ,%.2f,1950 MHZ,%.2f,1870 MHZ,%.2f,1970 MHZ,%.2f,1890 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 26:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 859 MHZ ,%.2f ,814 MHZ,%.2f,869 MHZ,%.2f,824 MHZ,%.2f,879 MHZ,%.2f,834 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;

		case 34:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2110 MHZ ,%.2f ,2110 MHZ,%.2f,2117 MHZ,%.2f,2117 MHZ,%.2f,2124 MHZ,%.2f,2124 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 38:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2570 MHZ ,%.2f ,2570 MHZ,%.2f,2595 MHZ,%.2f,2595 MHZ,%.2f,2620 MHZ,%.2f,2620 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		case 39:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1880 MHZ ,%.2f ,1880 MHZ,%.2f,1900 MHZ,%.2f,1900 MHZ,%.2f,1920 MHZ,%.2f,1920 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		case 40:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2300 MHZ ,%.2f ,2300 MHZ,%.2f,2350 MHZ,%.2f,2350 MHZ,%.2f,2400 MHZ,%.2f,2400 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;
		case 41:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2496 MHZ ,%.2f ,2450 MHZ,%.2f,2590 MHZ,%.2f,2550 MHZ,%.2f,2690 MHZ,%.2f,2650 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;



		default:
			return DEVICE_WRITE_FAIL;
	}

	strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:FDCorrection:ACTivate RF%dC,\'mytable\',TX",m_pTesterDevice->m_iInputPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:FDCorrection:ACTivate RF%dC,\'mytable\',RX",m_pTesterDevice->m_iOutputPort);
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;
}
int CFunWCDMACal_CMW::IWCDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName)
{
	 CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	

      strCmd.Format("SOUR:GPRF:GEN%d:BBM ARB;*OPC?;*OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)

	    strCmd.Format(_T("SOURce:GPRF:GEN%d:ARB:FILE \'%s\';*OPC?"),m_pTesterDevice->m_iChannelPort,strWavaFileName);
	DEVICE_QUERY(strCmd)

      double doffset=(double)((double)iFreqOffKhz/(double)1000000);
     iDlMHz+=doffset;


	 strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:FREQuency %.2fMHz;*OPC?",m_pTesterDevice->m_iChannelPort,iDlMHz);
     DEVICE_QUERY(strCmd)

     strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST OFF;*OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)

	 strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:FREQuency %.2fMHz;*OPC?",m_pTesterDevice->m_iChannelPort,dUlMHz);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:LEVel %d;*OPC?",m_pTesterDevice->m_iChannelPort,dDlPower);
     DEVICE_QUERY(strCmd)

      strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:PEPower?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("SOURce:GPRF:GEN%d:STATe ON; *OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
	 
      strCmd.Format("SOURce:GPRF:GEN%d:STATe?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 if(strRes.Find("ON")==-1)
		 return WCDMACAL_DLSIGON;
     return DEVICE_SUCCESS;
}
int CFunWCDMACal_CMW::IDevicesSetIOPort(int iIOPort)
{
	CString strCmd;
	int iDeviceErr;
	strCmd.Format("ROUTe:GPRF:GEN%d:RFS:CONN RF%dC",m_pTesterDevice->m_iChannelPort,iIOPort);
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;


	return DEVICE_SUCCESS;
}
int CFunWCDMACal_CMW::IGPSSetLoss(double dLoss)
{
	CString strCmd;
	int iDeviceErr;

	strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation %.2f",m_pTesterDevice->m_iChannelPort,dLoss);
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	return DEVICE_SUCCESS;
}
int CFunWCDMACal_CMW::IWCDMACalSetXOSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower)
{
     CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 

	  strCmd.Format("SOURce:GPRF:GEN%d:BBMode CW;*OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
      double doffset=(double)((double)iFreqOffKhz/(double)1000);
     iDlMHz+=doffset;


	 strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:FREQuency %.2fMHz;*OPC?",m_pTesterDevice->m_iChannelPort,iDlMHz);
     DEVICE_QUERY(strCmd)

	 strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:FREQuency %.2fMHz;*OPC?",m_pTesterDevice->m_iChannelPort,dUlMHz);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:LEVel %.2f;*OPC?",m_pTesterDevice->m_iChannelPort,dDlPower);
     DEVICE_QUERY(strCmd)

      strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:PEPower?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("SOURce:GPRF:GEN%d:STATe ON; *OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
	 
      strCmd.Format("SOURce:GPRF:GEN%d:STATe?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
     if(strRes.Find("ON")==-1)
     return WCDMACAL_DLSIGON;
     return DEVICE_SUCCESS;
}


//CDMA OPERATION
int CFunWCDMACal_CMW::ICDMACalSetMaxPower(double dMaxPower)
{
	 CString strCmd;
   int iDeviceErr;

   
   strCmd.Format("CONF:GPRF:MEAS%d:RFS:ENP %4.4f;*OPC?",m_pTesterDevice->m_iChannelPort,dMaxPower);
   DEVICE_QUERY(strCmd)
 
   strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:UMARgin 5;*OPC?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)
 
   strCmd.Format("CONF:GPRF:MEAS%d:POW:FILT:TYPE CDMA;*OPC?",m_pTesterDevice->m_iChannelPort);
  DEVICE_QUERY(strCmd)

	    strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST OFF",m_pTesterDevice->m_iChannelPort);
		 DEVICE_WRITE(strCmd)

   return DEVICE_SUCCESS;  
  
}
int CFunWCDMACal_CMW::ICDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName)
{
    CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	  
	 

	  strCmd.Format("SOUR:GPRF:GEN%d:BBM ARB;*OPC?;*OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
      double doffset=(double)((double)iFreqOffKhz/(double)1000000);
     iDlMHz+=doffset;

	     strCmd.Format(_T("SOURce:GPRF:GEN%d:ARB:FILE \'%s\';*OPC?"),m_pTesterDevice->m_iChannelPort,strWavaFileName);
	DEVICE_QUERY(strCmd)

	 strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:FREQuency %.2fMHz;*OPC?",m_pTesterDevice->m_iChannelPort,iDlMHz);
     DEVICE_QUERY(strCmd)

	 strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:FREQuency %.2fMHz;*OPC?",m_pTesterDevice->m_iChannelPort,dUlMHz);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:LEVel %.2f;*OPC?",m_pTesterDevice->m_iChannelPort,dDlPower);
     DEVICE_QUERY(strCmd)

      strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:PEPower?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("SOURce:GPRF:GEN%d:STATe ON; *OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
	 
      strCmd.Format("SOURce:GPRF:GEN%d:STATe?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)

	strRes=Device_GetReadBuf();
     if(strRes.Find("ON")==-1)
     return WCDMACAL_DLSIGON;
     return DEVICE_SUCCESS;

     
}
int CFunWCDMACal_CMW::ICDMAFetchCPRResult(int iMeasCount,double & dCPWR)
{
  CString strCmd;
   int iDeviceErr;
   CString strRes;
   int iRetryTimes=20; 
   CStringVtr vtrResults;

   strCmd.Format("TRIG:GPRF:MEAS%d:POW:SOUR \'Free Run\'",m_pTesterDevice->m_iChannelPort,iMeasCount);
   DEVICE_WRITE(strCmd)


	  strCmd.Format("CONF:GPRF:MEAS%d:POW:REP SING",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

  strCmd.Format("CONF:GPRF:MEAS%d:POW:SCO %d",m_pTesterDevice->m_iChannelPort,iMeasCount);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("READ:GPRF:MEAS%d:POW:CURR?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",vtrResults);
	dCPWR=CStr::StrToFloat(vtrResults[1]);

	  strCmd.Format("ABORT:GPRF:MEAS%d:POW",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;  
}
int CFunWCDMACal_CMW::ICDMAFetchCTDPResults(DblVtr & dvtrResults)
{
   CString strCmd;
   int iDeviceErr;
   int iRetryTimes=20;
   CStringVtr strVtr;
   DblVtr     dVtr;
   CString strRes;
    do
	{
             strCmd.Format("FETC:GPRF:MEAS%d:POW:STAT?",m_pTesterDevice->m_iChannelPort);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("RDY")!=-1)
	     break;

       Sleep(500);
	}while(--iRetryTimes>0);

		   if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

    
       strCmd.Format("FETC:GPRF:MEAS%d:POW:CURR?",m_pTesterDevice->m_iChannelPort);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtr,strVtr);
       dvtrResults.assign(dVtr.begin()+1,dVtr.end());

	     strCmd.Format("ABORT:GPRF:MEAS%d:POW",m_pTesterDevice->m_iChannelPort);
		 DEVICE_WRITE(strCmd)
       return DEVICE_SUCCESS;
}
int CFunWCDMACal_CMW::ICDMACalSetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
    char cCmd[2048]="";

	  strCmd.Format("CONF:GPRF:MEAS%d:POW:REP SING",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
   strCmd.Format("CONF:GPRF:MEAS%d:POW:SCO 1",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

   strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:STAR 0",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
  
	   
   strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST:STOP %d",m_pTesterDevice->m_iChannelPort,iCount-1);
   DEVICE_WRITE(strCmd)

   sprintf(cCmd, "CONF:GPRF:MEAS%d:POW:LIST:FREQ:ALL %4.3fMHZ",m_pTesterDevice->m_iChannelPort,dULFreqMHz);
	for(int i = 1 ; i < iCount; i++)
	{
		sprintf(cCmd, "%s,%4.3fMHZ", cCmd, dULFreqMHz);
	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)

	 sprintf(cCmd, "CONF:GPRF:MEAS%d:POW:LIST:ENP:ALL %4.4f",m_pTesterDevice->m_iChannelPort,dMaxinputPwl);
	for(int i = 1 ; i < iCount; i++)
	{
		sprintf(cCmd, "%s,%4.4f", cCmd, dMaxinputPwl);
	}
	strCmd.Format("%s",cCmd);
	 DEVICE_WRITE(strCmd)

  
   
   strCmd.Format("TRIG:GPRF:MEAS%d:POW:OFFS 20677us",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)

	 

   strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:SLOP FEDGe",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)

	
  /*   strCmd.Format("TRIG:GPRF:MEAS%d:POW:OFFS 677us",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)

	 

   strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:SLOP REDGe",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)*/

   strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:THR -40",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
   strCmd.Format("CONF:GPRF:MEAS%d:POW:SLEN 20ms",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    
	    strCmd.Format("CONF:GPRF:MEAS%d:POW:MLEN 18ms",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)


    strCmd.Format("TRIG:GPRF:MEAS%d:POW:MGAP 0.002",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:TOUT 20",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    strCmd.Format("CONF:GPRF:MEAS%d:POW:TRIG:MODE ONCE",m_pTesterDevice->m_iChannelPort);
  DEVICE_WRITE(strCmd)
    strCmd.Format("TRIG:GPRF:MEAS%d:POWer:SOUR \'IF Power\';*OPC?",m_pTesterDevice->m_iChannelPort);
  DEVICE_QUERY(strCmd)
	   strCmd.Format("CONF:GPRF:MEAS%d:POW:LIST ON;*OPC?",m_pTesterDevice->m_iChannelPort);
  DEVICE_QUERY(strCmd)
	  strCmd.Format("INIT:GPRF:MEAS%d:POW;*OPC?",m_pTesterDevice->m_iChannelPort);
  DEVICE_QUERY(strCmd)

   return DEVICE_SUCCESS;  
}
int CFunWCDMACal_CMW::ICDMACalSet_DLPowe(double dDlPower)
{
     CString strCmd;
	 int iDeviceErr;
   
	CString strRes;


   strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:LEVel %.2f;*OPC?",m_pTesterDevice->m_iChannelPort,dDlPower);
		 DEVICE_QUERY(strCmd)

  
	return DEVICE_SUCCESS;

}
int CFunWCDMACal_CMW::ICDMACalSet_DLPower_On(bool bIsOn)
{
     CString strCmd;
	 int iDeviceErr;
   
	CString strRes;
	if(bIsOn)
    
	{
     strCmd.Format("SOURce:GPRF:GEN%d:STATe ON; *OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)

	 
      strCmd.Format("SOURce:GPRF:GEN%d:STATe?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 if(strRes.Find("ON")==-1)
		 return WCDMACAL_DLSIGON;
	}
	else
	{
	  strCmd.Format("SOURce:GPRF:GEN%d:STATe OFF; *OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
	 
      strCmd.Format("SOURce:GPRF:GEN%d:STATe?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 if(strRes.Find("OFF")==-1)
		 return WCDMACAL_DLSIGON;
	}

	 return DEVICE_SUCCESS;
}
int CFunWCDMACal_CMW::ICDMACalInit(const CString& strAddr)
{
   CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;



	   strCmd=_T("*RST");
	   DEVICE_WRITE(strCmd)
 
	      strCmd=_T("*CLS");
	   DEVICE_WRITE(strCmd)
      
	  strCmd=_T("*OPC?");
      DEVICE_QUERY_DELAY(strCmd,100)

	
	  
   return DEVICE_SUCCESS;  
}
int CFunWCDMACal_CMW::ICDMACalSetLoss(int iCDMABand,const DblVtr & vLossList)
{
  CString strCmd;
	 int iDeviceErr;
   
	CString strRes;
 
	 strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:DELete \'mytable\'");
	 DEVICE_WRITE(strCmd)
     strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:CREate \'mytable\'");
	 DEVICE_WRITE(strCmd)

	



	switch(iCDMABand)
	{
	case 800:
     
        strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 824.85 MHZ ,%.2f ,869.85 MHZ,%.2f,835.74 MHZ,%.2f,880.74 MHZ,%.2f,848.22 MHZ,%.2f,893.22 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
         
		break;
	case 1900:
        	 
		 strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1851.25 MHZ ,%.2f ,1931.25 MHZ,%.2f,1878.15 MHZ,%.2f,1958.15 MHZ,%.2f,1908.75 MHZ,%.2f,1988.75 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;

	
		default:
		return DEVICE_WRITE_FAIL;
	}

	 strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	 DEVICE_WRITE(strCmd)

		 strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	 DEVICE_WRITE(strCmd)

	 strCmd.Format("CONFigure:FDCorrection:ACTivate RF%dC,\'mytable\',TX",m_pTesterDevice->m_iOutputPort);
	 DEVICE_WRITE(strCmd)

	  strCmd.Format("CONFigure:FDCorrection:ACTivate RF%dC,\'mytable\',RX",m_pTesterDevice->m_iInputPort);
	 DEVICE_WRITE(strCmd)

    return DEVICE_SUCCESS;
}