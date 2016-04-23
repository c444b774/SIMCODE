#include "StdAfx.h"
#include "FuncGSMCal_8820.h"

CFuncGSMCAL_8820::CFuncGSMCAL_8820(void)
{
}

CFuncGSMCAL_8820::~CFuncGSMCAL_8820(void)
{
}

CFuncGSMCAL_8820::CFuncGSMCAL_8820(PCTesterDevice pDev):CFuncDev_8820(pDev)
{


}

int CFuncGSMCAL_8820::IGSMTestInitTxDelay(double powLevel)
{
	 int iDeviceErr;
   CString strCmd,strRes;
    strCmd=_T("TSPAT TSC5");
	  DEVICE_WRITE(strCmd)
     strCmd=_T("OPEMODE EGPRS;*OPC?");
       DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();
	  if(strRes.Find("1")==-1)
	  {
		    strCmd=_T("OPEMODE EGPRS;*OPC?");
		    DEVICE_QUERY(strCmd)
		  strRes=Device_GetReadBuf();

		  if(strRes.Find("1")==-1)
		  {
            return  -99; 
		  }

	  }
	
	  strCmd=_T("USFBLER_MEAS OFF");
	  DEVICE_WRITE(strCmd)
	  
	  strCmd=_T("CS MCS5");
	  DEVICE_WRITE(strCmd)
		  strCmd.Format("ILVL %.2lf;*OPC?",powLevel);
       DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();
	
	  if(strRes.Find("1")==-1)
	  {return -99;}
	  strCmd=_T("ORFSMD_COUNT 64");
	  DEVICE_WRITE(strCmd)



  return DEVICE_SUCCESS;
}
int CFuncGSMCAL_8820::IGSMTestGetAllMod(float * mod)
{
	 int iDeviceErr;
	  CString strCmd,strRes;
	    CStringVtr strVtr;
		DblVtr dVtr;
	  strCmd=_T("ORFSMD_MEAS ON");
	  DEVICE_WRITE(strCmd)

	  strCmd=_T("SWP");
	  DEVICE_WRITE(strCmd)  

	  strCmd=_T("*CLS");
	  DEVICE_WRITE(strCmd)  

	  strCmd=_T("SWP?");
	  DEVICE_QUERY(strCmd)  
		
	  strRes=Device_GetReadBuf();
	  if(strRes.Find("0")==-1)
	  {return -99;}
	  
	  strCmd=_T("ALLMEAS? ORFSMD");
	  DEVICE_QUERY(strCmd)  
	  strRes=Device_GetReadBuf();
	  
	  CStr::ParseString(strRes,",",strVtr);
	  strVtr.erase(strVtr.begin());//discard first one "ON" is a illegal value
	 
	   CStr::StrVtr2DblVtr(dVtr,strVtr);
       if(strVtr.size()<1)
		   return DEVICE_VECTORSIZE_NOT_ENOUGH;
	   for(int i=0;i<78;++i)
           mod[i]=dVtr[i];
	    strCmd=_T("ORFSMD_MEAS OFF");
	  DEVICE_WRITE(strCmd)
	  return DEVICE_SUCCESS;
}
int CFuncGSMCAL_8820::IGSMCalInit(const CString& strAddr)
{
	  CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;


	  strCmd=_T("BANDCAL;*OPC");
	  DEVICE_WRITE(strCmd)

	  Sleep(200);
      strCmd=_T("SCRSEL FMEAS");
	  DEVICE_WRITE(strCmd)

     
    
	  strCmd=_T("CALLSO");
      DEVICE_WRITE(strCmd)

	  strCmd=_T("STDSEL?");
       DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();

	    if(strRes.Find("GSM")==-1)
	  {
			 strCmd=_T("STDSEL GSM");
		    DEVICE_WRITE(strCmd)

		   Sleep(3000);
          
		    strCmd=_T("STDSEL?");
		    DEVICE_QUERY(strCmd)
		  strRes=Device_GetReadBuf();

		  if(strRes.Find("GSM")==-1)
		  {
            return  -99; 
		  }

	  }

	   strCmd=_T("*RST;*OPC?");
    DEVICE_QUERY(strCmd)

	  strCmd=_T("*CLS;*OPC?");
     DEVICE_QUERY(strCmd)

	 if(m_pTesterDevice->m_bIsScreenOff)
	 {
         strCmd=_T("SCREEN OFF");
        DEVICE_WRITE(strCmd)

	   strCmd=_T("MEASMODE FAST");
       DEVICE_WRITE(strCmd)
	 }
	 else

	 {
         strCmd=_T("SCREEN ON");
       DEVICE_WRITE(strCmd)

	   strCmd=_T("MEASMODE NORM");
        DEVICE_WRITE(strCmd)
	 }

       strCmd=_T("CALLPROC OFF");
        DEVICE_WRITE(strCmd)

			  strCmd=_T("RFOUT MAIN");
        DEVICE_WRITE(strCmd)

			  strCmd=_T("MOD OFF");
        DEVICE_WRITE(strCmd)

			  strCmd=_T("MOD ON");
        DEVICE_WRITE(strCmd)


			CString strBuf;
		strCmd.Format("*IDN?");
		DEVICE_QUERY(strCmd);
		strBuf=Device_GetReadBuf();

		/*	strCmd.Format(_T("DLEXTLOSSW COMMON"));
			if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
				return iDeviceErr;
			strCmd.Format(_T("ULEXTLOSSW COMMON"));
			if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
				return iDeviceErr;*/

			strCmd.Format(_T("EXTLOSSW COMMON"));
			if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
				return iDeviceErr;
	

	     strCmd=_T("ILVLCTRL MANUAL");
       DEVICE_WRITE(strCmd)


	     strCmd=_T("OSIGPAT CCH");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("TEMP_MEAS OFF;VSTIME_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("MOD_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("ORFSSW_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("ORFSMD_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("PWR_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("BER_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("BITOFS 0.5");
       DEVICE_WRITE(strCmd)

	
       

    return DEVICE_SUCCESS;
}
int CFuncGSMCAL_8820::IGSMCalSetWaveForm(const CString & strWaveFile)
{
     CString strCmd;
	 int iDeviceErr;
     strCmd=_T("RFOUT MAIN");
        DEVICE_WRITE(strCmd)

	   strCmd=_T("MOD OFF");
        DEVICE_WRITE(strCmd)

	   strCmd=_T("MOD ON");
        DEVICE_WRITE(strCmd)

       strCmd=_T("OSIGPAT CCH");
        DEVICE_WRITE(strCmd)

	   return DEVICE_SUCCESS;




}

int CFuncGSMCAL_8820::IGSMCalFetchIQ_Results(unsigned char* uIQData,unsigned char* uPower,unsigned char* uPhse,int iListNum)
{
	  CString strCmd;
	 int iDeviceErr;

     
	  CString strRes;
        int iRetryTimes=20;
		int iRetNum;
		strCmd.Format("MSTAT?");
     
      do
	  {

		  
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("0")!=-1)
	     break;

       Sleep(50);
         

	  }while(--iRetryTimes>0);

     strCmd.Format("IQCAP_NUM?");
	  DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();
	  iRetNum=CStr::StrToInt(strRes);

	  if((iRetNum/10)!=iListNum/10)
		  return DEVICE_IQCAPSIZE_NOT_EQUAL;  
      
	  strCmd.Format("IQCAP_BIN? 2,0,%d",iRetNum);
	  DEVICE_QUERY_CHAR(strCmd,uIQData)



      strCmd=_T("IQCAP_MEAS OFF"); 
       DEVICE_WRITE(strCmd)

  
	   return DEVICE_SUCCESS;
    
}
int CFuncGSMCAL_8820::IGSMCalFetchIQ_Results_V2(float* uPower,float* uPhse,unsigned short *iListNum)
{
	CString strCmd;
	int iDeviceErr;

	float uIQData[64000];
	CString strRes;
	int iRetryTimes=20;
	int iRetNum;
	strCmd.Format("MSTAT?");

	do
	{
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if(strRes.Find("0")!=-1)
			break;
		Sleep(50);
	}while(--iRetryTimes>0);
	if (iRetryTimes<1)
		return DEVICE_INTEGERITY_NOTRIGHT;

	strCmd.Format("IQCAP_NUM?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	iRetNum=CStr::StrToInt(strRes);
	
	if((iRetNum/10)!=*iListNum/10)
		return DEVICE_IQCAPSIZE_NOT_EQUAL; 
	*iListNum=iRetNum;

	strCmd.Format("IQCAP_BIN? 2,0,%d",iRetNum);
	DEVICE_QUERY_CHAR(strCmd,(unsigned char*)uIQData)
	for (int i=0;i<iRetNum;i++)
	{
		uPhse[i]=(atan2(uIQData[2*i+1],uIQData[2*i]))*180/3.1416;
		uPower[i]=10*log10(uIQData[2*i]*uIQData[2*i]+uIQData[2*i+1]*uIQData[2*i+1]);
	}

		strCmd=_T("IQCAP_MEAS OFF"); 
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;

}
int CFuncGSMCAL_8820::IGSMCalInit_IQSample(double dExpectPower,int iSampleCount,int iTriggerDelay,const CString & strFilterType)
{
	  CString strCmd;
	  int iDeviceErr;
	int iTimSPan=iSampleCount/10;

	/*strCmd.Format("LVL OFF;*OPC?");
    DEVICE_QUERY(strCmd)*/

      strCmd.Format("ILVL %.2f;*OPC?",dExpectPower);
	   DEVICE_QUERY(strCmd)
	   Sleep(200);

       strCmd=_T("IQCAP_MEAS ON");
       DEVICE_WRITE(strCmd)
		    strCmd=_T("IQCAP_BW 5MHz");
       DEVICE_WRITE(strCmd)
		    strCmd=_T("IQCAP_TRGLVL -25");
       DEVICE_WRITE(strCmd)
		    strCmd.Format("IQCAP_TSPAN %d",iTimSPan);
       DEVICE_WRITE(strCmd)
		     strCmd.Format("IQCAP_TRGDLY %d",iTriggerDelay);
       DEVICE_WRITE(strCmd)
		 strCmd.Format("SNGLS");
       DEVICE_WRITE(strCmd)

		 Sleep(500);
    return DEVICE_SUCCESS;
}
int CFuncGSMCAL_8820::IGSMCalFetchMAM_AMPM_Results(float *fPower,float *fPhase,float *fFER,int iListNum)
{
   CString strCmd;
   int iDeviceErr;
   int iRetryTimes=20;
   CStringVtr strVtr;
   DblVtr     dVtr;
   DblVtr     dVtrPhase;
   CString strRes;
    do
	{
             strCmd.Format("PREDISTQ_READY?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("0")!=-1)
	     break;

       Sleep(500);
		   }while(--iRetryTimes>0);

		   if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

    
       strCmd.Format("PREDISTQ_POWER? %d",iListNum);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   CStr::ParseString(strRes,",",strVtr);
	    for(int i=0;i<strVtr.size();i++)
	 {
		 if(strVtr[i].Find("Inf")!=-1)
			 strVtr[i]="-99";
	 }
	   CStr::StrVtr2DblVtr(dVtr,strVtr);
	   
	
       fPower[0]=dVtr[0];
       if(strVtr.size()<iListNum)
		   return DEVICE_VECTORSIZE_NOT_ENOUGH;
	   for(int i=1;i<iListNum;++i)
	   {
		  
           fPower[i]=fPower[0]+dVtr[i];
	   }

	     strCmd.Format("PREDISTQ_PHASE? %d",iListNum);
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtrPhase,strVtr);
       fPhase[0]=dVtrPhase[0];
       if(strVtr.size()<iListNum)
		   return DEVICE_VECTORSIZE_NOT_ENOUGH;
	   for(int i=1;i<iListNum;++i)
           fPhase[i]=fPhase[0]+dVtrPhase[i];

  return DEVICE_SUCCESS;
}

int CFuncGSMCAL_8820::IGSMCalInitAMAM_AMPM(double dExpectPower,int iStepNum,int iMeasLen,double iStepLen,int iTriggerOffset,const CString & strFilterType)
{
   CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	  int iRetryTimes=20;

	   strCmd.Format("LVL OFF;*OPC?");
    DEVICE_QUERY(strCmd)

		   strCmd=_T("TSPAT TSC5");
	   DEVICE_WRITE(strCmd)
		   strCmd=_T("OPEMODE GSM");
	   DEVICE_WRITE(strCmd)
		   strCmd.Format("ILVL %0.2f",dExpectPower);
	   DEVICE_WRITE(strCmd)
		   strCmd.Format("SNGLSPREDISTQ %.3f,%d,%.2f",iStepLen,iStepNum,iMeasLen/iStepLen);
       DEVICE_WRITE(strCmd)

		   do
		   {
             strCmd.Format("PREDISTQ_READY?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("1")!=-1)
	     break;
         Sleep(500);

		   }while(--iRetryTimes>0);

		   if(iRetryTimes==0)
			   return DEVICE_INTEGERITY_NOTRIGHT;

		 
   return DEVICE_SUCCESS;

}
int CFuncGSMCAL_8820::IGSMCalSetDLPower(double dDlPower)
{
   CString strCmd;
	 int iDeviceErr;   
	  CString strRes;
   strCmd.Format("OLVL %.2fDBM;*OPC?",dDlPower);
    DEVICE_QUERY(strCmd)	

    strCmd.Format("LVL ON;*OPC?");
    DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();


    return DEVICE_SUCCESS;

}
int CFuncGSMCAL_8820::IGSMCalSetFreq(double dDLMhz,double dULMhz)
{ 
	 CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	   strCmd.Format("ULFREQ %.2fMHz;*OPC?",dULMhz);
    DEVICE_QUERY(strCmd)	
		 strCmd.Format("CTRLULFREQ %.2fMHz;*OPC?",dULMhz);
    DEVICE_QUERY(strCmd)		
		strCmd.Format("DLFREQ %.2fMHz;*OPC?",dDLMhz);
    DEVICE_QUERY(strCmd)	
		strCmd.Format("CTRLDLFREQ %.2fMHz;*OPC?",dDLMhz);
    DEVICE_QUERY(strCmd)	
		strRes=Device_GetReadBuf();
		return DEVICE_SUCCESS;


}
int CFuncGSMCAL_8820::IGSMCalSetLoss(int iGSMBand,const DblVtr & vLossList)
{
	CString strCmd;
	 int iDeviceErr;
	 CString strBuf;
	 strCmd.Format("*IDN?");
	 DEVICE_QUERY(strCmd);
	 strBuf=Device_GetReadBuf();

		/* strCmd.Format(_T("DLEXTLOSSW COMMON"));
		 if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			 return iDeviceErr;
		 strCmd.Format(_T("ULEXTLOSSW COMMON"));
		 if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			 return iDeviceErr;*/

		 strCmd.Format(_T("EXTLOSSW COMMON"));
		 if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			 return iDeviceErr;
	

   strCmd=_T("DELLOSSTBL");
	   DEVICE_WRITE(strCmd) 

	CString strRes;
	switch(iGSMBand)
	{
	case 850:
		strCmd.Format("LOSSTBLVAL 824.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 836.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 848.8MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		 break;
	case 900:
        strCmd.Format("LOSSTBLVAL 880.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 902.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 914.8MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;
	case 1800:
         strCmd.Format("LOSSTBLVAL 1710.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 1747.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 1784.8MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;
	case 1900:
		 strCmd.Format("LOSSTBLVAL 1850.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 1909.8MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;
	
	default:
		return DEVICE_WRITE_FAIL;
	}


  return DEVICE_SUCCESS;
}

