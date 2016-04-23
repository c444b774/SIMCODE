#include "StdAfx.h"
#include "FuncGSMCal_CMW.h"

CFunGSMCal_CMW::CFunGSMCal_CMW(void)
{
}

CFunGSMCal_CMW::~CFunGSMCal_CMW(void)
{
}

CFunGSMCal_CMW::CFunGSMCal_CMW(PCTesterDevice pDev):CFuncDev_CMW(pDev)
{


}
int CFunGSMCal_CMW::SetInput(int iInput)
	{
	 CString strCmd;
    int iDeviceErr;

     int iConnector;
	 
	
     if(iInput==1 || iInput==3)
     iConnector=1;
	 else
	  iConnector=2;

	  if(m_pTesterDevice->m_bIsCommandRX1CMW)
	 strCmd.Format("ROUTe:GPRF:MEAS:SCENario:SALone RFAC,RX1");

	  else
      strCmd.Format("ROUTe:GPRF:MEAS:SCENario:SALone RFAC");
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 	m_pTesterDevice->m_iInputPort=iInput;
	   
    return DEVICE_SUCCESS;  

	}
int CFunGSMCal_CMW::SetOutput(int iOutput)
	{
		  CString strCmd;
     int iDeviceErr;
     int iConnector;
	 
	    if(iOutput==1 || iOutput==3)
     iConnector=1;
	 else
	  iConnector=2;

	// strCmd.Format("ROUTe:GPRF:GEN%d:RFS:CONN RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
	 strCmd.Format("ROUTe:GPRF:MEAS:SCENario:SALone RFAC,TX1");
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  m_pTesterDevice->m_iOutputPort=iOutput;
	  return DEVICE_SUCCESS;  

	}

int CFunGSMCal_CMW::IGSMCalInit(const CString& strAddr)
{
	  CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

    

	   strCmd=_T("*RST;*OPC?");
    DEVICE_QUERY(strCmd)

	  strCmd=_T("*CLS;*OPC?");
     DEVICE_QUERY(strCmd)

      strCmd=_T("*OPC?");
      DEVICE_QUERY_DELAY(strCmd,100)

		  strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	  DEVICE_WRITE(strCmd)

		  strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	  DEVICE_WRITE(strCmd)

/*
		  strCmd.Format("CONFigure:FDCorrection:ACTivate RF%dC,\'mytable\',TX",m_pTesterDevice->m_iOutputPort);
	  DEVICE_WRITE(strCmd)

		  strCmd.Format("CONFigure:FDCorrection:ACTivate RF%dC,\'mytable\',RX",m_pTesterDevice->m_iInputPort);
	  DEVICE_WRITE(strCmd)*/

		 
		  strCmd=_T("CONF:BASE:FDC:CTAB:CATalog?");
	  DEVICE_QUERY(strCmd)

		  strCmd=_T("CONF:BASE:FDC:CTAB:DEL \"mytable\";*OPC?");
	  DEVICE_QUERY(strCmd)	

		  strCmd=_T("CONF:BASE:FDC:CTAB:CATalog?");
	  DEVICE_QUERY(strCmd)

    return DEVICE_SUCCESS;
}
int CFunGSMCal_CMW::IGSMCalFetchIQ_Results(unsigned char* uIQData,unsigned char* uPower,unsigned char* uPhse,int iListNum)
{
	  CString strCmd;
	 int iDeviceErr;

	 unsigned char *uiCharDatTemp=(unsigned char*)malloc(200000);
     
	  CString strRes;
        int iRetryTimes=20;
		strCmd.Format("FETCh:GPRF:MEAS%d:IQRecorder:STATe?",m_pTesterDevice->m_iChannelPort);
     
      do
	  {

		  
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("RDY")!=-1)
	     break;

       Sleep(500);
         

	  }while(--iRetryTimes>0);

	  if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

   
      
	  strCmd.Format("FETCh:GPRF:MEAS%d:IQRecorder?",m_pTesterDevice->m_iChannelPort);
	  DEVICE_QUERY_CHAR(strCmd,uiCharDatTemp)
      memcpy(uIQData,uiCharDatTemp+10,2*iListNum*sizeof(float));


   
	   strCmd.Format("FORMAT:DATA ASCII");
      DEVICE_WRITE(strCmd)

		  free(uiCharDatTemp);
	   return DEVICE_SUCCESS;
    
}

int CFunGSMCal_CMW::IGSMCalInit_IQSample(double dExpectPower,int iSampleCount,int iTriggerDelay,const CString & strFilterType)
{
	  CString strCmd;
	  int iDeviceErr;

     int iTriggerNum=(0-iTriggerDelay)*10;
	 int iTriggerAfterNum=iSampleCount-iTriggerNum;
    
       strCmd.Format("CONF:GPRF:MEAS%d:RFS:ENP %4.4f;*OPC?",m_pTesterDevice->m_iChannelPort,dExpectPower);
   DEVICE_QUERY(strCmd)
 
      strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:UMARgin 10;*OPC?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)

        strCmd.Format("TRIG:GPRF:MEAS%d:IQR:SOUR \'IF Power\'",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

   strCmd.Format("TRIG:GPRF:MEAS%d:IQR:THR -45",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
 
    strCmd.Format("TRIG:GPRF:MEAS%d:IQR:SLOP REDG",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:IQR:FILT:TYPE BAND",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:IQR:FILT:BAND:BWID 10000000",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
	    strCmd.Format("CONF:GPRF:MEAS%d:IQR:RAT 0.2",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)


   

	    
	   strCmd.Format("TRIG:GPRF:MEAS%d:IQR:TOUT 10",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("TRIG:GPRF:MEAS%d:IQR:CAPT %d,%d",m_pTesterDevice->m_iChannelPort,iTriggerNum,iTriggerAfterNum);
   DEVICE_WRITE(strCmd)

	   //strCmd.Format("FORMAT:DATA REAL,32");
	 
			  strCmd.Format("FORMat:DATA REAL,32");
   DEVICE_WRITE(strCmd)

	    strCmd.Format("INIT:GPRF:MEAS%d:IQR;*OPC?",m_pTesterDevice->m_iChannelPort);
    DEVICE_QUERY(strCmd)


		 Sleep(500);

    return DEVICE_SUCCESS;
}
int CFunGSMCal_CMW::IGSMCalFetchMAM_AMPM_Results(float *fPower,float *fPhase,float *fFER,int iListNum)
{
   CString strCmd;
   int iDeviceErr;
   int iRetryTimes=20;
   CStringVtr strVtr;
   DblVtr     dVtr;
   CString strRes;
    do
	{
             strCmd.Format("FETC:GPRF:MEAS%d:IQVS:STAT?",m_pTesterDevice->m_iChannelPort);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("RDY")!=-1)
	     break;

       Sleep(500);
	}while(--iRetryTimes>0);

		   if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

    
       strCmd.Format("FETC:GPRF:MEAS%d:IQVS:LEV?",m_pTesterDevice->m_iChannelPort);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtr,strVtr);

       if(strVtr.size()<iListNum)
		   return DEVICE_VECTORSIZE_NOT_ENOUGH;
	   for(int i=1;i<iListNum+1;++i)
           fPower[i-1]=dVtr[i];

  return DEVICE_SUCCESS;
}

int CFunGSMCal_CMW::IGSMCalInitAMAM_AMPM(double dExpectPower,int iStepNum,int iMeasLen,double iStepLen,int iTriggerOffset,const CString & strFilterType)
{
   CString strCmd;
	 int iDeviceErr;
   
	
    strCmd.Format("CONF:GPRF:MEAS%d:RFS:ENP %4.4f;*OPC?",m_pTesterDevice->m_iChannelPort,dExpectPower);
   DEVICE_QUERY(strCmd)
 
   strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:UMARgin 5;*OPC?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)
 
  strCmd.Format("TRIG:GPRF:MEAS%d:IQVS:SOUR \'IF Power\'",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

   strCmd.Format("TRIG:GPRF:MEAS%d:IQVS:THR -40",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)
 
    strCmd.Format("TRIG:GPRF:MEAS%d:IQVS:SLOP REDG",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

   strCmd.Format("CONFigure:GPRF:MEAS%d:IQVSlot:REPetition SING",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

    strCmd.Format("CONFigure:GPRF:MEAS%d:IQVSlot:LIST OFF",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	    strCmd.Format("CONF:GPRF:MEAS%d:IQVS:SCO %d",m_pTesterDevice->m_iChannelPort,iStepNum);
   DEVICE_WRITE(strCmd)

	    strCmd.Format("CONF:GPRF:MEAS%d:IQVS:SLEN %dus",m_pTesterDevice->m_iChannelPort,iStepLen);
   DEVICE_WRITE(strCmd)

	     strCmd.Format("CONF:GPRF:MEAS%d:IQVS:MLEN %dus",m_pTesterDevice->m_iChannelPort,iMeasLen);
   DEVICE_WRITE(strCmd)

	    strCmd.Format("CONF:GPRF:MEAS%d:IQVS:FEL -50",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("CONF:GPRF:MEAS%d:IQVS:FTYP GAUSS",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	      strCmd.Format("TRIG:GPRF:MEAS%d:IQVS:OFFS %dus",m_pTesterDevice->m_iChannelPort,iTriggerOffset);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("TRIG:GPRF:MEAS%d:IQVS:TOUT 5",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("TRIG:GPRF:MEAS%d:IQVS:MGAP 0",m_pTesterDevice->m_iChannelPort);
   DEVICE_WRITE(strCmd)

	   
	 strCmd.Format("ABORt:GPRF:MEAS%d:IQVSlot;*OPC?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)

	    strCmd.Format("INIT:GPRF:MEAS%d:IQVS;*OPC?",m_pTesterDevice->m_iChannelPort);
   DEVICE_QUERY(strCmd)

   return DEVICE_SUCCESS;

}
int CFunGSMCal_CMW::IGSMCalSetWaveForm(const CString & strWaveFile)
{

   CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;

    strCmd.Format("SOURce:GPRF:GEN%d:BBM ARB;*OPC?",m_pTesterDevice->m_iChannelPort);
     DEVICE_QUERY(strCmd)

		 strCmd.Format("SOURce:GPRF:GEN%d:ARB:FILE \'%s\';*OPC?",m_pTesterDevice->m_iChannelPort,strWaveFile);
     DEVICE_QUERY(strCmd)


    return DEVICE_SUCCESS;
}
int CFunGSMCal_CMW::IGSMCalSetDLPower(double dDlPower)
{
   CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;

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
int CFunGSMCal_CMW::IGSMCalSetFreq(double dDLMhz,double dULMhz)
{ 
	 CString strCmd;
	 int iDeviceErr;
   
	 
	   strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:FREQuency %.2fMHz;*OPC?",m_pTesterDevice->m_iChannelPort,dDLMhz);
     DEVICE_QUERY(strCmd)

	  Sleep(20);
	 
	 strCmd.Format("SOUR:GPRF:GEN:RFS:EATT 1;*OPC?");
	 DEVICE_QUERY(strCmd)

   
	 strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:FREQuency %.2fMHz;*OPC?",m_pTesterDevice->m_iChannelPort,dULMhz);
     DEVICE_QUERY(strCmd)

	 Sleep(20);

	 strCmd.Format("CONF:GPRF:GEN:RFS:EATT 1;*OPC?");
	 DEVICE_QUERY(strCmd)

		return DEVICE_SUCCESS;


}
int CFunGSMCal_CMW::IGSMCalSetLoss(int iGSMBand,const DblVtr & vLossList)
{
	  CString strCmd;
	 int iDeviceErr;   
	 CString strRes;
 
	 strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:DELete \'mytable\'");
	 DEVICE_WRITE(strCmd)
     strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:CREate \'mytable\'");
	 DEVICE_WRITE(strCmd)	 

	switch(iGSMBand)
	{
	case 850:     
        strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 824.2 MHZ ,%.2f ,836.6 MHZ,%.2f,848.8 MHZ,%.2f",vLossList[0],vLossList[1],vLossList[2]);
		DEVICE_WRITE(strCmd)
         
		break;
	case 900:        	 
		  strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 880.2 MHZ ,%.2f ,902.4 MHZ,%.2f,914.8 MHZ,%.2f",vLossList[0],vLossList[1],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;

	case 1800:      
		  strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1710.2 MHZ ,%.2f ,1747.4 MHZ,%.2f,1784.8 MHZ,%.2f",vLossList[0],vLossList[1],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;

	 case 1900:       
		 strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1850.2 MHZ ,%.2f ,1880 MHZ,%.2f,1909.8 MHZ,%.2f",vLossList[0],vLossList[1],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;
      
		default:
		return DEVICE_WRITE_FAIL;
	}
    
	 strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	 DEVICE_WRITE(strCmd)

	 strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	 DEVICE_WRITE(strCmd)

    return DEVICE_SUCCESS;

}

