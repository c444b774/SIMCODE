#include "StdAfx.h"
#include "FuncGSMCal_8960.h"

CFuncGSMCAL_8960::CFuncGSMCAL_8960(void)
{
}

CFuncGSMCAL_8960::~CFuncGSMCAL_8960(void)
{
}

CFuncGSMCAL_8960::CFuncGSMCAL_8960(PCTesterDevice pDev):CFuncDev_8960(pDev)
{


}


int CFuncGSMCAL_8960::IGSMCalInit(const CString& strAddr)
{
	  CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

      strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
      DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();
	  if(strRes.Find("GSM/GPRS")==-1)
	  {
         strCmd=_T("SYSTEM:APPLICATION:CURRENT:NAME?");
		DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
		if(strRes.Find("\"Fast Switch Test App\"")!=-1)
		{
             strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME 'GSM/GPRS'");
	         DEVICE_WRITE(strCmd) 
			 strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
	         DEVICE_QUERY(strCmd)
		     strRes=Device_GetReadBuf();
			if(strRes.Find("GSM/GPRS")==-1)
			return DEVICE_1XEVDO_NOTSUPPORT;

		}
		else
		{
		   return DEVICE_NOTIN_FASTSWITCH;	
		}
	  }

	   strCmd=_T("*RST");
	   DEVICE_WRITE(strCmd)

	  strCmd=_T("*OPC?");
      DEVICE_QUERY_DELAY(strCmd,100)


/*
	if(m_pTesterDevice->m_bIsScreenOff)
		  { 
            strCmd=_T("DISP:MODE FAST");
	        DEVICE_WRITE(strCmd)
		  }
		else
		{
			strCmd=_T("DISP:MODE TRAC");
	        DEVICE_WRITE(strCmd)
		     strCmd=_T("SYSTEM:COMMUNICATE:GPIB:DEBUG:STATE ON");
	        DEVICE_WRITE(strCmd)
	}*/
		

      

    return DEVICE_SUCCESS;
}
int CFuncGSMCAL_8960::IGSMTestGetAllMod(float * mod)
{
	   CString strCmd,strRes;
	   int iDeviceErr;
	    int iRetryTimes=20;
	    CStringVtr strVtr;
		 DblVtr     dVtr;
		strCmd.Format("INIT:ORFS");

	  DEVICE_WRITE(strCmd)
		strCmd.Format("*CLS");
		 DEVICE_WRITE(strCmd)


		strCmd.Format("INITiate:Done?");
     
      do
	  {

		  
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("NONE")!=-1)
	     break;

       Sleep(500);
         

	  }while(--iRetryTimes>0);

	  if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;


		strCmd.Format("FETCH:ORFSPECTRUM:MODULATION:ALL?");
		DEVICE_QUERY(strCmd)
		  strRes=Device_GetReadBuf();
		
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtr,strVtr);

    
		mod[0]=dVtr[1];
		mod[1]=dVtr[2];



	   return DEVICE_SUCCESS;
}
int CFuncGSMCAL_8960::IGSMTestInitTxDelay(double powLevel)
{
	CString strCmd;
	   CString strRes;
	   int iDeviceErr;

		strCmd.Format("CALL:BURSt:TYPE TSC5");
	  DEVICE_WRITE(strCmd)
			strCmd.Format("CALL:CELL:OPERATING:MODE EBPT;*OPC?");
	  DEVICE_QUERY(strCmd)
		  Sleep(50);
	strCmd.Format("CALL:PDTCH:MCSC:EBPT MCS5P1");
	  DEVICE_WRITE(strCmd)



	strCmd.Format("RFAN:CONT:POW:AUTO OFF");
	  DEVICE_WRITE(strCmd)
	strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED:BURST1 %lf;*OPC?",powLevel);
	 Sleep(50);

		  strCmd.Format("SETup:ORFSpectrum:CONTinuous OFF");
	  DEVICE_WRITE(strCmd)
		  strCmd.Format("SETup:ORFSpectrum:TRIGger:SOURce AUTO");
	  DEVICE_WRITE(strCmd)
		  strCmd.Format("SETup:ORFSpectrum:TRIGger:DELay 0S");
	  DEVICE_WRITE(strCmd)
		  strCmd.Format("SETup:ORFSpectrum:FAST OFF");
	  DEVICE_WRITE(strCmd)
		  strCmd.Format("SETup:ORFSpectrum:FILTer:TYPE ANALog");
	  DEVICE_WRITE(strCmd)
		  strCmd.Format("SETup:ORFSpectrum:TIMeout 5352MS");
	  DEVICE_WRITE(strCmd)
		  strCmd.Format("SET:ORFS:MOD:COUN:SNUM 64");
	  DEVICE_WRITE(strCmd)
		  		  strCmd.Format("SETup:ORFSpectrum:MODulation:FREQuency -400KHZ,400KHZ");
	  DEVICE_WRITE(strCmd)
		  		  strCmd.Format("SET:ORFS:SWIT:COUN:SNUM 1");
	  DEVICE_WRITE(strCmd)
		  		  strCmd.Format("SET:ORFS:SWIT:FREQ:ALL OFF");
	  DEVICE_WRITE(strCmd)
    
	return DEVICE_SUCCESS;
}
int CFuncGSMCAL_8960::IGSMCalSetWaveForm(const CString & strWaveFile)
{	
	
	   CString strCmd;
	   CString strRes;
	   int iDeviceErr;
	   strCmd=_T("CALL:OPER:MODE GBTTest;*OPC?");
		DEVICE_QUERY(strCmd)
		  strRes=Device_GetReadBuf();
		
         strCmd=_T("CALL:OPER:MODE?");
			DEVICE_QUERY(strCmd)

          strCmd=_T("CALL:CONTROL:DOWNLINK:FREQUENCY:AUTO OFF");
		DEVICE_WRITE(strCmd)

    
	return DEVICE_SUCCESS;


}

int CFuncGSMCAL_8960::IGSMCalFetchIQ_Results(unsigned char* uIQData,unsigned char* uPower,unsigned char* uPhse,int iListNum)
{
	  CString strCmd;
	 int iDeviceErr;
	 CString strRes;
	 unsigned char *readBufferSuperLarge;
	 unsigned char *readBufferSuperLarge2;
	 int iIntegerity;
        int iRetryTimes=20;
		int iRetNum;
		strCmd.Format("INITiate:Done?");
     
      do
	  {

		  
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("PCAL")!=-1)
	     break;

       Sleep(100);
         

	  }while(--iRetryTimes>0);

	  if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

	 

	  strCmd.Format("FETCh:PCALibration:INTegrity?");
	  DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();
	  iIntegerity=CStr::StrToInt(strRes);
	  if(iIntegerity!=0 && iIntegerity!=5 && iIntegerity!=6) 
		  return DEVICE_INTEGERITY_NOTRIGHT;

     strCmd.Format("FETCh:PCALibration:SAMPle:COUNt?");
	  DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();
	  iRetNum=CStr::StrToInt(strRes);

	  if(iRetNum!=iListNum)
		  return DEVICE_IQCAPSIZE_NOT_EQUAL;  

	  readBufferSuperLarge=(unsigned char*)malloc(100000);
	  readBufferSuperLarge2=(unsigned char*)malloc(100000);
      
	  strCmd.Format("FETCh:PCALibration:SAMPle:AMPLitude:DBM:BINary?");
	  DEVICE_QUERY_CHAR(strCmd,readBufferSuperLarge)
      
       strCmd.Format("FETCh:PCALibration:SAMPle:PHASe:BINary?");
	  DEVICE_QUERY_CHAR(strCmd,readBufferSuperLarge2)

	 memcpy(uPhse,readBufferSuperLarge2+7,iListNum*sizeof(float)-8);
     memcpy(uPower,readBufferSuperLarge+7,iListNum*sizeof(float)-8);

      strCmd=_T("INIT:PCALibration:OFF"); 
       DEVICE_WRITE(strCmd)

  
      	free(readBufferSuperLarge);
		free(readBufferSuperLarge2); 
	   return DEVICE_SUCCESS;
    
}


int CFuncGSMCAL_8960::IGSMCalFetchIQ_Results_V2(float* uPower,float* uPhse,unsigned short *iListNum)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iIntegerity;
	
	int iRetryTimes=20;
	int iRetNum;
	CStringVtr strVtr;
	DblVtr dvTemp;
	float fPhasetmp=0;
	strCmd.Format("FETCh:PCALibration:INTegrity?");     
	do
	{		  
		DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
		if(strRes.Find("0")!=-1)
		 break;
		Sleep(100);
	}while(--iRetryTimes>0);

	if(iRetryTimes==0)
		return DEVICE_INTEGERITY_NOTRIGHT;
/*

	strCmd.Format("FETCh:PCALibration:INTegrity?");
	DEVICE_QUERY(strCmd)
	strRes=Device_GetReadBuf();
	iIntegerity=CStr::StrToInt(strRes);

	if(iIntegerity!=0 && iIntegerity!=5 && iIntegerity!=6) 
		return DEVICE_INTEGERITY_NOTRIGHT;*/

	strCmd.Format("FETCh:PCALibration:SAMPle:COUNt?");
	DEVICE_QUERY(strCmd)
	strRes=Device_GetReadBuf();
	iRetNum=CStr::StrToInt(strRes);


	if(iRetNum!=*iListNum)
		return DEVICE_IQCAPSIZE_NOT_EQUAL;  
	*iListNum=iRetNum;
	//The range of <range> is 1 to N, where N is the Sample Count/1000 rounded up to the nearest integer.
	//For example, if the Sample Count is 15,366 samples, then N is 16. 


	unsigned short iNumRange=iRetNum/1000+1;
	unsigned short iMod=iRetNum%1000;

	for (int i=0;i<iNumRange-1;i++)
	{	dvTemp.clear();
		strCmd.Format("FETCh:PCALibration:SAMPle:PHASe? %d",i+1);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,",",strVtr);
		CStr::StrVtr2DblVtr(dvTemp,strVtr);
		
			for (int j=0;j<1000;j++)
			{
				fPhasetmp=dvTemp[j];
				do 
				{
					if (-180>=fPhasetmp)
					{
						fPhasetmp=fPhasetmp+360;
					}
					if (180<fPhasetmp)
					{
						fPhasetmp=fPhasetmp-360;
					}
					
				} while (fPhasetmp>180||fPhasetmp<=-180);

				uPhse[1000*i+j]=fPhasetmp;
			}
		
		dvTemp.clear();
		strCmd.Format("FETCh:PCALibration:SAMPle:AMPLitude:DBM? %d",i+1);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,",",strVtr);
		CStr::StrVtr2DblVtr(dvTemp,strVtr);

		for (int j=0;j<1000;j++)
		{
			uPower[1000*i+j]=dvTemp[j];
		}

	}

	dvTemp.clear();
	strCmd.Format("FETCh:PCALibration:SAMPle:PHASe? %d",iNumRange);
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strVtr);
	CStr::StrVtr2DblVtr(dvTemp,strVtr);

	for (int j=0;j<iMod;j++)
	{		
		fPhasetmp=dvTemp[j];
		do 
		{
			if (-180>=fPhasetmp)
			{
				fPhasetmp=fPhasetmp+360;
			}
			if (180<fPhasetmp)
			{
				fPhasetmp=fPhasetmp-360;
			}

		} while (fPhasetmp>180||fPhasetmp<=-180);
		uPhse[1000*(iNumRange-1)+j]=fPhasetmp;
	}

	dvTemp.clear();
	strCmd.Format("FETCh:PCALibration:SAMPle:AMPLitude? %d",iNumRange);
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strVtr);
	CStr::StrVtr2DblVtr(dvTemp,strVtr);

	for (int j=0;j<iMod;j++)
	{
		fPhasetmp=20*log10(dvTemp[j]);		
		uPower[1000*(iNumRange-1)+j]=fPhasetmp;
	}
	

	

	

/*
	strCmd.Format("FETCh:PCALibration:SAMPle:AMPLitude:DBM:BINary?");
	DEVICE_QUERY_CHAR(strCmd,(unsigned char*) uPower);

/ *
	memcpy(uPower,cBuff,iRetNum*sizeof(float));
	strCmd.Format("FETCh:PCALibration:SAMPle:AMPLitude:DBM? 1");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();* /

	strCmd.Format("FETCh:PCALibration:SAMPle:PHASe:BINary?");
	DEVICE_QUERY_CHAR(strCmd,(unsigned char*) uPhse);*/

	 


	strCmd=_T("INIT:PCALibration:OFF"); 
	DEVICE_WRITE(strCmd)


	return DEVICE_SUCCESS;
    
}
int CFuncGSMCAL_8960::IGSMCalInit_IQSample(double dExpectPower,int iSampleCount,int iTriggerDelay,const CString & strFilterType)
{
	  CString strCmd;
	  int iDeviceErr;
    
	   strCmd=_T("RFAN:CONT:POW:AUTO OFF");
       DEVICE_WRITE(strCmd)
		   strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED:BURST1 %0.2f",dExpectPower);
       DEVICE_WRITE(strCmd)

		    strCmd.Format("SETup:PCALibration:TIMeout:STIMe 10s");
       DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:TRIGger:SOUR RISE");
       DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:TRIGger:THREShold 25");
       DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:WAVeform:TYPe CONT3");
       DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCALibration:MEASurement:COUNt %d",iSampleCount);
       DEVICE_WRITE(strCmd)

			  strCmd.Format("SETup:PCALibration:TRIGger:DELay %dus",iTriggerDelay);
       DEVICE_WRITE(strCmd)

              strCmd.Format("INIT:PCALibration:ON");
	    DEVICE_WRITE(strCmd)
	   Sleep(50);

    
    return DEVICE_SUCCESS;
}
int CFuncGSMCAL_8960::IGSMCalFetchMAM_AMPM_Results(float *fPower,float *fPhase,float *fFER,int iListNum)
{
   CString strCmd;
   int iDeviceErr;
   int iRetryTimes=20;
   CStringVtr strVtr;
   DblVtr     dVtr,dVtrPhase;
   CString strRes;
    do
	{
             strCmd.Format("INITiate:Done?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("PCAL")!=-1)
	     break;

       Sleep(500);
	 }while(--iRetryTimes>0);

		   if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

      
       strCmd.Format("FETCh:PCALibration:INTegrity?");
	   DEVICE_QUERY(strCmd)
	   strRes=Device_GetReadBuf();
      
	   strCmd.Format("FETCh:PCALibration:POWer?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();

	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtr,strVtr);
       fPower[0]=dVtr[0];
       if(strVtr.size()<iListNum)
		   return DEVICE_VECTORSIZE_NOT_ENOUGH;
	   for(int i=1;i<iListNum;++i)
           fPower[i]=fPower[0]+dVtr[i];

		 strCmd.Format("FETCh:PCALibration:PHASe?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	  
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtrPhase,strVtr);
       fPhase[0]=(float)dVtrPhase[0];
       if(strVtr.size()<iListNum)
		   return DEVICE_VECTORSIZE_NOT_ENOUGH;
	   for(int i=1;i<iListNum;++i)
	   {
		   if(dVtrPhase[i]>360)
				dVtrPhase[i]=0;
           fPhase[i]=fPhase[0]+(float)dVtrPhase[i];
	   }

		
	    strCmd.Format("FETCh:PCALibration:FERRor?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();

	   dVtr.clear();
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtr,strVtr);
       fFER[0]=dVtr[0];
       if(strVtr.size()<iListNum)
		   return DEVICE_VECTORSIZE_NOT_ENOUGH;
	   for(int i=1;i<iListNum;++i)
           fFER[i]=fFER[0]+dVtr[i];


    strCmd.Format("INIT:PCALibration:OFF");
	   DEVICE_WRITE(strCmd)
  return DEVICE_SUCCESS;
}

int CFuncGSMCAL_8960::IGSMCalInitAMAM_AMPM(double dExpectPower,int iStepNum,int iMeasLen,double iStepLen,int iTriggerOffset,const CString & strFilterType)
{
   CString strCmd;
	 int iDeviceErr;
   
   CString strRes;

    char cmdstrbuf[5000]={'\0'}; 
	char cmdstrbuf2[3000]={'\0'}; 
	char cmdstr[10]={'\0'};   
    
     float fMlen;
	 float fStep;
	 float ftd;
	  float TimeCenter=0;
	 float TimeWidth=0;
	 fMlen=(double)iMeasLen/1000000;
	 fStep=(double)iStepLen/1000000;
	  ftd=(double)iTriggerOffset/1000000;

	  	for(int i=0;i<iStepNum;i++)
		{
		   TimeCenter=(fStep*i)+ftd+fMlen/2; 
		   sprintf(cmdstr,"%.6f,",TimeCenter);
		   strcat(cmdstrbuf,cmdstr);
		   sprintf(cmdstr,"%.6f,",fMlen);
		   strcat(cmdstrbuf2,cmdstr);
		}
		cmdstrbuf[strlen(cmdstrbuf)-1]='\0';
		cmdstrbuf2[strlen(cmdstrbuf2)-1]='\0';
	    
	   strCmd.Format("CALL:BURSt:TYPE TSC5");
	   DEVICE_WRITE(strCmd)

	   strCmd.Format("CALL:CELL:OPERATING:MODE GBTT");
	   DEVICE_WRITE(strCmd)

	   strCmd.Format("RFAN:CONT:POW:AUTO OFF");
	   DEVICE_WRITE(strCmd)

	   strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED:BURST1 %0.2f",dExpectPower);
	   DEVICE_WRITE(strCmd)

		    strCmd.Format("CALL:CELL:OPERating:MODE CW");
	   DEVICE_WRITE(strCmd)

		    strCmd.Format("RFAnalyzer:CW:EXPected:POWer %0.2f",dExpectPower);
	   DEVICE_WRITE(strCmd)

		    strCmd.Format("SETup:PCALibration:TIMeout:STIMe 20s");
	   DEVICE_WRITE(strCmd)

		    strCmd.Format("SETup:PCAL:TRIGger:SOUR RISE");
	   DEVICE_WRITE(strCmd)
 
		   strCmd.Format("SETup:PCAL:TRIGger:THREShold 20");
	   DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:WAVeform:TYPe DISCrete");
	   DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:TRIGger:DELay 0");
	   DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCALibration:FILTer %s",strFilterType);
	   DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:RESult:TYPE PCAL");
	   DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:STEP:COUNt %d",iStepNum);
	   DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:STEP:CENTer %s",cmdstrbuf);
	   DEVICE_WRITE(strCmd)

		   strCmd.Format("SETup:PCAL:STEP:WIDth %s",cmdstrbuf2);
	   DEVICE_WRITE(strCmd)

		   strCmd.Format("INIT:PCALibration:ON");
	     DEVICE_WRITE(strCmd)
		 
			Sleep(50);
   return DEVICE_SUCCESS;

}
int CFuncGSMCAL_8960::IGSMCalSetDLPower(double dDlPower)
{
   CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;

   strCmd.Format("CALL:CELL:POWER:AMPLITUDE %0.2fDBM;*OPC?",dDlPower);
    DEVICE_QUERY(strCmd)
    strCmd.Format("CALL:CELL:POWER:STATE ON;*OPC?");
    DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
    return DEVICE_SUCCESS;

}
int CFuncGSMCAL_8960::IGSMCalSetFreq(double dDLMhz,double dULMhz)
{ 
	 CString strCmd;
	 int iDeviceErr;   
	  CString strRes;	 
	   strCmd.Format("RFANalyzer:CONTrol:MEASurement:FREQuency:AUTO OFF");
    DEVICE_WRITE(strCmd)

		 strCmd.Format("RFANalyzer:MANual:MEASurement:FREQuency %0.2fMHz;*OPC?",dULMhz);
    DEVICE_QUERY(strCmd)		
		strCmd.Format("CALL:CELL:RFGENERATOR:FREQUENCY %0.2fMHz;*OPC?",dDLMhz);
    DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
		return DEVICE_SUCCESS;


}
int CFuncGSMCAL_8960::IGSMCalSetLoss(int iGSMBand,const DblVtr & vLossList)
{
	CString strCmd;
	 int iDeviceErr;
    strCmd=_T("SYSTem:CORRection:GAIN");
	   DEVICE_WRITE(strCmd) 

   strCmd=_T("SYSTem:CORRection:FREQ");
	   DEVICE_WRITE(strCmd) 

   strCmd=_T("SYSTem:CORRection:STATe OFF");
	   DEVICE_WRITE(strCmd) 

  

	CString strRes;
	switch(iGSMBand)
	{
	case 850:
		strCmd.Format("SYST:CORR:FREQ 824.2MHZ,836.6MHZ,848.8MHZ");
		 DEVICE_WRITE(strCmd)
       
		 break;
	case 900:
        strCmd.Format("SYST:CORR:FREQ 880.2MHZ,902.4MHZ,914.8MHZ");
		 DEVICE_WRITE(strCmd)
       
		break;
	case 1800:
         strCmd.Format("SYST:CORR:FREQ 1710.2MHZ,1747.4MHZ,1784.8MHZ");
		 DEVICE_WRITE(strCmd)
       
		break;
	case 1900:
		 strCmd.Format("SYST:CORR:FREQ 1850.2MHZ,1880MHZ,1909.8MHZ");
		 DEVICE_WRITE(strCmd)
        
		break;
	
	default:
		return DEVICE_WRITE_FAIL;
	}


	strCmd.Format("SYST:CORR:GAIN %f,%f,%f",-vLossList[0],-vLossList[1],-vLossList[2]);
	   DEVICE_WRITE(strCmd) 

    strCmd=_T("SYSTem:CORRection:STATe ON");
	   DEVICE_WRITE(strCmd) 

  return DEVICE_SUCCESS;
}

