#include "StdAfx.h"
#include "FuncWCDMACal_CMU.h"

CFuncWCDMACAL_CMU::CFuncWCDMACAL_CMU(void)
{
}

CFuncWCDMACAL_CMU::~CFuncWCDMACAL_CMU(void)
{
}

CFuncWCDMACAL_CMU::CFuncWCDMACAL_CMU(PCTesterDevice pDev):CFuncDev_CMU(pDev)
{

}

int CFuncWCDMACAL_CMU::ICDMACalInit(const CString& strAddr)
{

 return IWCDMACalInit(strAddr);

}
int CFuncWCDMACAL_CMU::IWCDMACalInit(const CString& strAddr)
{
     CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

/*
	  strCmd.Format(_T("%s::%s"),strAddr,"96::INSTR");
	  if((iDeviceErr=Device_Init(strCmd))!=DEVICE_SUCCESS)
		  return iDeviceErr;*/

/*
	 strCmd.Format(_T("%s::%s"),strAddr,"0::INSTR");
	 if((iDeviceErr=Device_Init(strCmd))!=DEVICE_SUCCESS)
		 return iDeviceErr;*/

     
	   strCmd=_T("*RST");
	   DEVICE_WRITE(strCmd)
      	   if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		   return iDeviceErr;
	  strCmd=_T("*OPC?");
      DEVICE_QUERY_DELAY(strCmd,100)


      strCmd=_T("0;SYSTem:OPTions:INFO?");
      DEVICE_QUERY(strCmd)

		   strCmd=_T("0;*OPT?");
      DEVICE_QUERY(strCmd)

		   strCmd=_T("0;SYST:REM:RDM ON;*OPC?");
      DEVICE_QUERY(strCmd)

      

	if(m_pTesterDevice->m_bIsScreenOff)
		  { 
            strCmd=_T("0;DISPlay OFF");
	        DEVICE_WRITE(strCmd)

			strCmd=_T("0;TRACe:REMote:MODE:DISPlay OFF");
	        DEVICE_WRITE(strCmd)

		  }
		else
		{
			strCmd=_T("0;DISPlay ON");
	        DEVICE_WRITE(strCmd)

			strCmd=_T("0;TRACe:REMote:MODE:DISPlay ON");
	        DEVICE_WRITE(strCmd)

		}

  
      	strCmd=_T("0;SYST:REM:ADDR:SEC? 1");
	  DEVICE_QUERY(strCmd)

	 
	strCmd=_T("1;OUTP RF2");
	DEVICE_WRITE(strCmd)
    strCmd=_T("1;INP RF2");
	DEVICE_WRITE(strCmd)        
	  
   return DEVICE_SUCCESS;  
}
int  CFuncWCDMACAL_CMU::IWCDMACalSetMaxPower(double dMaxPower)
{

	 CString strCmd;
   int iDeviceErr;

    
   
   
   strCmd.Format("1;LEVel:MODE MANual;:LEVel:MAXimum %.2f;*OPC?",dMaxPower);
   DEVICE_QUERY(strCmd)

   

   return DEVICE_SUCCESS;  

}
int CFuncWCDMACAL_CMU::IWCDMAFetchCPRResult(int iMeasCount,double & dCPWR)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   int iRetryTimes=200; 
   CStringVtr vtrResults;

   strCmd.Format("SETup:WCPOWer:CONTinuous OFF");
   DEVICE_WRITE(strCmd)

   strCmd.Format("SETup:WCPOWer:COUNt %d",iMeasCount);
   DEVICE_WRITE(strCmd)

   strCmd.Format("INITiate:WCPOWer;*OPC?");
   DEVICE_QUERY(strCmd)

    do
   {
     strCmd.Format("INITiate:DONE?");
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 if(strRes.Find("WCP")!=-1)
		 break;
	 Sleep(50);

   }while(--iRetryTimes>0);

   if(iRetryTimes==0)
	   return DEVICE_FINDRES_FAIL;

    strCmd.Format("FETCh:WCPOWer?");
    DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",vtrResults);
	dCPWR=CStr::StrToFloat(vtrResults[1]);
   return DEVICE_SUCCESS;  
}
int CFuncWCDMACAL_CMU::IWCDMAFetchWTDPResults(DblVtr & dvtrResults)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   CStringVtr vtrResults;
   int iRetryTimes=200;
   int  iret=-1;
   int iReadCount;
   DblVtr dvtrTemp;
   CString strTemp;
    strCmd.Format("*CLS");
   DEVICE_WRITE(strCmd)

   do
   {
     strCmd.Format("INITiate:DONE?");
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 if(strRes.Find("WTDP")!=-1)
		 break;
	 Sleep(50);

   }while(--iRetryTimes>0);

   if(iRetryTimes==0)
	   return DEVICE_FINDRES_FAIL;

   strCmd.Format("FETCH:WTDP:COUNT:STEP?");
     DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	 iReadCount=CStr::StrToInt(strRes);
     
     //strCmd.Format("FETC:WTDP?",iReadCount);
	 strCmd.Format("FETC:WTDP?");
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 CStr::ParseString(strRes,",",vtrResults);
	 strTemp=vtrResults[0];
	 if(strTemp.Find("0")==-1)
	 return  DEVICE_INTEGERITY_NOTRIGHT;
     
	 CStr::StrVtr2DblVtr(dvtrTemp,vtrResults);
	
	 dvtrResults.assign(dvtrTemp.begin()+1,dvtrTemp.end());
     for(int i=0;i<dvtrResults.size();++i)
	dvtrResults[i]-=0.26;  // according to QSPR
      strCmd.Format("INITIATE:WTDP:OFF");
      DEVICE_WRITE(strCmd)

     return DEVICE_SUCCESS;  
}
int CFuncWCDMACAL_CMU::IWCDMASetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
    
   strCmd.Format("SET:WTDP:STEP:TIME MS20");
   DEVICE_WRITE(strCmd)

   strCmd.Format("SET:WTDP:STEP:COUN %d",iCount);
   DEVICE_WRITE(strCmd)
  
	   
   strCmd.Format("SET:WTDP:STEP %0.4f",dStepPower);
   DEVICE_WRITE(strCmd)

   strCmd.Format("SETUP:WTDP:TIMEOUT:STIME %d MS",iTimeout);
   DEVICE_WRITE(strCmd)

   strCmd.Format("INIT:WTDP");
   DEVICE_WRITE(strCmd)
   
   return DEVICE_SUCCESS;  
}

int CFuncWCDMACAL_CMU::IWCDMACalSetChannel(int iBand,int iULChannel)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   double freq=0.0;  
   freq=CWCDMABandInfo::ArfcnToHz(iBand,iULChannel,1);

   strCmd.Format("LVL OFF");
   DEVICE_WRITE(strCmd)

   strCmd.Format("ULFREQ %0.2fMHz;*OPC?",freq);
   DEVICE_QUERY(strCmd)


   return DEVICE_SUCCESS;

}
int  CFuncWCDMACAL_CMU::IWCDMACalSetLoss(int iWCDMABand,const DblVtr & vLossList)
{
     CString strCmd;
	 int iDeviceErr;
   
	CString strRes;

	 strCmd.Format("SYSTem:CORRection:GAIN");
	 DEVICE_WRITE(strCmd)
     strCmd.Format("SYSTem:CORRection:FREQ");
	 DEVICE_WRITE(strCmd)

	 strCmd.Format("SYSTem:CORRection:STATe OFF");
	 DEVICE_WRITE(strCmd)

	switch(iWCDMABand)
	{
	case 2100:
        strCmd.Format("SYST:CORR:FREQ 2112.6 MHZ,1922.6 MHZ, 2140 MHZ,1950 MHZ, 2167.4 MHZ,1977.4 MHZ");
		 DEVICE_WRITE(strCmd)

		  strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		 DEVICE_WRITE(strCmd)

		break;
	case 1900:
         strCmd.Format("SYST:CORR:FREQ 1854.2 MHZ,1934.2 MHZ,1880 MHZ,1960 MHZ,1906.6 MHZ,1986.6MHZ");
		 DEVICE_WRITE(strCmd)

		strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;

	case 1500:
         strCmd.Format("SYST:CORR:FREQ 1478.4 MHZ,1430.4 MHZ,1486 MHZ,1438 MHZ,1493.4 MHZ,1445.4 MHZ");
		 DEVICE_WRITE(strCmd)

		strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;

	 case 900:
         strCmd.Format("SYST:CORR:FREQ 882.4 MHZ,927.4 MHZ,897.6 MHZ,942.6 MHZ,912.6 MHZ,957.6 MHZ");
		 DEVICE_WRITE(strCmd)

		strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;

	  case 850:
         strCmd.Format("SYST:CORR:FREQ 871.4 MHZ,826.4 MHZ,881.8 MHZ,836.8 MHZ,891.6 MHZ,846.6 MHZ");
		 DEVICE_WRITE(strCmd)

		strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		 DEVICE_WRITE(strCmd)
		break;
      
		default:
		return DEVICE_WRITE_FAIL;
	}

	 strCmd.Format("SYSTem:CORRection:STATe ON");
	 DEVICE_WRITE(strCmd)
    return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_CMU::IWCDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName)
{

      CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 

	  strCmd=_T("CALL:CELL:OPERATING:MODE FDDTEST;*OPC?");
     DEVICE_QUERY(strCmd)
      double doffset=(double)((double)iFreqOffKhz/(double)1000000);
     iDlMHz+=doffset;

	 strCmd.Format("CALL:CONTrol:DOWNLINK:FREQuency:AUTO OFF");
	  DEVICE_WRITE(strCmd)

	 strCmd.Format("CALL:RFG:FREQ %0.2fMHz;*OPC?",iDlMHz);
     DEVICE_QUERY(strCmd)

      strCmd.Format("RFANalyzer:CONTrol:MEASurement:FREQuency:AUTO OFF");
	  DEVICE_WRITE(strCmd)

	   strCmd.Format("RFANalyzer:MANual:MEASurement:FREQuency %0.2fMHz;*OPC?",dUlMHz);
     DEVICE_QUERY(strCmd)


	  strCmd.Format("CALL:POW  %0.2f;*OPC?",dDlPower);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("CALL:POW:STAT ON;*OPC?");
     DEVICE_QUERY(strCmd)
	 
     return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_CMU::IWCDMACalSetXOSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower)
{
     CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 

	  strCmd=_T("0;SYST:REM:ADDR:SEC 1,NONE");
	  DEVICE_WRITE(strCmd)
	  strCmd=_T("0;SYST:REM:ADDR:SEC 1,\"RF_NSig\"");
		DEVICE_WRITE(strCmd)
		
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)

	  strCmd=_T("1;TRIG:SOUR IMM");
     DEVICE_WRITE(strCmd)

	  strCmd.Format("1;SOUR:RFG:LSM:STAT ON;*OPC?");
     DEVICE_QUERY(strCmd)
		
		  strCmd.Format("1;SOUR:RFG:MOD OFF;*OPC?");
     DEVICE_QUERY(strCmd)

      double doffset=(double)((double)iFreqOffKhz/(double)1000);
     iDlMHz+=doffset;

	    strCmd.Format("1;RFAN:FREQ %.2f MHZ;*OPC?",dUlMHz);
     DEVICE_QUERY(strCmd)

		  strCmd.Format("1;SOUR:RFG:FREQ %.2f MHZ;*OPC?",iDlMHz);
     DEVICE_QUERY(strCmd)


		 strCmd.Format("1;SOUR:RFG:LEV %.2f;*OPC?",dDlPower);
     DEVICE_QUERY(strCmd)

		 strCmd.Format("1;INIT:RFG;*OPC?");
     DEVICE_QUERY(strCmd)

     return DEVICE_SUCCESS;
}


//CDMA OPERATION
int CFuncWCDMACAL_CMU::ICDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName)
{

        CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;

	  double doffset=(double)((double)iFreqOffKhz/(double)1000000);
     iDlMHz+=doffset;

    strCmd.Format("1;RFAN:FREQ %.2f MHZ;*OPC?",dUlMHz);
     DEVICE_QUERY(strCmd)

		  strCmd.Format("1;SOUR:RFG:FREQ %.2f MHZ;*OPC?",iDlMHz);
     DEVICE_QUERY(strCmd)


		 strCmd.Format("1;SOUR:RFG:POW:CDMA %.2f;*OPC?",dDlPower);
     DEVICE_QUERY(strCmd)

		 strCmd=_T("1;TRIG:SOUR FRUN");
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;SOURce:RFGenerator:MODulation:MODe AUTomatic");
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;SOURce:RFGenerator:LEVel:FFCH -15.6;FPCH -12.0;FSYNc -16.0;FPICh -7.0;OCNS:ENABle ON");
	DEVICE_WRITE(strCmd)

		 // strCmd.Format("1;INIT:RFG;*OPC?");
     //DEVICE_QUERY(strCmd)
      


    return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_CMU::ICDMACalSetBand(int iCDMABand)
{
	 
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("0;SYST:REM:ADDR:SEC 1,NONE");
	DEVICE_WRITE(strCmd)
	switch(iCDMABand)
	{
	case CDMA_BC0_BAND_ID:
		strCmd=_T("0;SYST:REM:ADDR:SEC 1,\"CDMA2KCellMS_NSig\"");
		DEVICE_WRITE(strCmd)
		
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)

		break;
	case CDMA_BC1_BAND_ID:
		strCmd=_T("0;SYST:REM:ADDR:SEC 1,\"CDMA2KPCSMS_NSig\"");
		DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)
		break;
	}


	return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_CMU::ICDMACalSetMaxPower(double dMaxPower)
{
    return   IWCDMACalSetMaxPower(dMaxPower);
}
int CFuncWCDMACAL_CMU::ICDMAFetchCPRResult(int iMeasCount,double & dCPWR)
{
    CString strCmd;
   int iDeviceErr;
   CString strRes;
   int iRetryTimes=200; 
   CStringVtr vtrResults;

 

   	strCmd.Format("1;CONF:NPOW:CONT %d,SING,NONE,NONE",iMeasCount);
    DEVICE_WRITE(strCmd)

     strCmd=_T("1;ABOR:RFG;*OPC?");
    DEVICE_QUERY(strCmd)

   strCmd.Format("1;INIT:NPOW;*OPC?");
   DEVICE_QUERY(strCmd)

    do
   {
     strCmd.Format("1;FETC:NPOW:STAT?");
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 if(strRes.Find("RDY")!=-1)
		 break;
	 Sleep(50);

   }while(--iRetryTimes>0);

   if(iRetryTimes==0)
	   return DEVICE_FINDRES_FAIL;

    strCmd.Format("1;FETCH:NPOW?");
    DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",vtrResults);
	dCPWR=CStr::StrToFloat(vtrResults[0]);

    strCmd=_T("1;ABOR:NPOW");
    DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;  

}
int CFuncWCDMACAL_CMU::ICDMAFetchCTDPResults(DblVtr & dvtrResults)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   CStringVtr vtrResults;
   int iRetryTimes=200;
   int  iret=-1;

   DblVtr dvtrTemp;
   CString strTemp;
    strCmd.Format("*CLS");
   DEVICE_WRITE(strCmd)

   do
   {
     strCmd.Format("1;FETC:POW:XSL:STAT?");
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 if(strRes.Find("RDY")!=-1)
		 break;
	 Sleep(50);

   }while(--iRetryTimes>0);

   if(iRetryTimes==0)
	   return DEVICE_FINDRES_FAIL;

   
     strCmd.Format("1;FETC:POW:XSL:CURR?");
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 CStr::ParseString(strRes,",",vtrResults);

	 CStr::StrVtr2DblVtr(dvtrTemp,vtrResults);
	 dvtrResults.assign(dvtrTemp.begin(),dvtrTemp.end());

      strCmd.Format("1;ABORt:POWer:XSLot");
      DEVICE_WRITE(strCmd)

     return DEVICE_SUCCESS;  
}
int CFuncWCDMACAL_CMU::IWCDMASetupTXRXComposite(double * dUlFreqMHz,double * dDLFreqMHz,int iNumSteps,double *dRxPowerList,double *dTxMaxLevList)
{
    CString strCmd;
   int iDeviceErr;
   CString strRes;
   int iRetrytimes=200;

  
   char cCmd[4096]="";
    strCmd.Format("1;SOUR:RFG:FREQ %.2f MHZ;*OPC?",dDLFreqMHz[0]);
   DEVICE_QUERY(strCmd)

	    strCmd.Format("1;RFAN:FREQ %.2f MHZ;*OPC?",dUlFreqMHz[0]);
   DEVICE_QUERY(strCmd)


	    strCmd.Format("1;LEVel:MODE MANual;:LEVel:MAXimum %.2f;*OPC?",dTxMaxLevList[0]);
   DEVICE_QUERY(strCmd)

	    strCmd.Format("1;SOUR:RFG:POW:CDMA %.2f;*OPC?",dRxPowerList[0]);
   DEVICE_QUERY(strCmd)

	    strCmd.Format("1;INIT:RFG;*OPC?");
   DEVICE_QUERY(strCmd)

	     strCmd.Format("1;CONFigure:POWer:SALignment:CONTrol:REPetition SING,NONE,NONE;SCOunt %d;SWIDth 0.02;SQCOunt 16",iNumSteps);
   DEVICE_WRITE(strCmd)
          
	     sprintf(cCmd,  "1;CONFigure:POWer:SALignment:CONTrol:SQUence2 %.2fMHZ,%.2fMHZ;",dDLFreqMHz[1],dUlFreqMHz[1]);
	for(int i =2; i< FTM_TX_RX_FREQ_MAX_FREQUENCIES; i++)
	{

		sprintf(cCmd,  "%sSQUence%d %.2fMHZ,%.2fMHZ;",cCmd,i+1,dDLFreqMHz[i],dUlFreqMHz[i]);
	}
	strCmd.Format("%s*OPC?",cCmd);
	 DEVICE_QUERY(strCmd)

		 sprintf(cCmd,  "1;CONFigure:POWer:SALignment:CONTrol:STEP2 %.1f,%.1f;",dRxPowerList[1],dTxMaxLevList[1]);
	for(int i =2; i< iNumSteps; i++)
	{

		sprintf(cCmd,  "%sSTEP%d %.1f,%.1f;",cCmd,i+1,dRxPowerList[i],dTxMaxLevList[i]);
	}
	strCmd.Format("%s*OPC?",cCmd);
	 DEVICE_QUERY(strCmd)


    strCmd.Format("1;TRIG:SOUR IFP");
   DEVICE_WRITE(strCmd)
	    strCmd.Format("1;TRIG:THR:IFP -20.5");
   DEVICE_WRITE(strCmd)

	    strCmd.Format("1;TRIG:SLOP POS");
   DEVICE_WRITE(strCmd)

	    strCmd.Format("1;ABORT:POWer:SALignment");
   DEVICE_WRITE(strCmd)

	    strCmd.Format("1;INITiate:POWer:SALignment");
   DEVICE_WRITE(strCmd)
		strCmd.Format("1;*OPC?");
   do
   {
	   DEVICE_QUERY(strCmd);
	   strRes=Device_GetReadBuf();
	   if(strRes.Find("1")!=-1)
		   break;
	   Sleep(50);


   }while(--iRetrytimes>0);


	return DEVICE_SUCCESS;  

}
int CFuncWCDMACAL_CMU::IWCDMAFetchTXRXResults(DblVtr & dvtrResults)
	{

         CString strCmd;
	   int iDeviceErr;
	   CString strRes;

	    CStringVtr strVtr;
	    DblVtr     dVtr;
	 

	     strCmd.Format("1;FETCh:POWer:SALignment?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   CStr::ParseString(strRes,",",strVtr);
	   CStr::StrVtr2DblVtr(dVtr,strVtr);
       dvtrResults.assign(dVtr.begin(),dVtr.end());


	   strCmd.Format("1;ABORt:POWer:SALignment");
       DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;  
	}
int CFuncWCDMACAL_CMU::ICDMACalSetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
    
    strCmd.Format("1;CONF:POW:XSL:CONT:REP SING,NONE,NONE");
   DEVICE_WRITE(strCmd)


   strCmd.Format("1;CONF:POW:XSL:CONT:SWID 20 MS");
   DEVICE_WRITE(strCmd)

	    strCmd.Format("1;CONF:POW:XSL:CONT:PMW 10 MS");
   DEVICE_WRITE(strCmd)

   strCmd.Format("1;CONF:POW:XSL:CONT:SCO %d",iCount);
   DEVICE_WRITE(strCmd)

	   strCmd.Format("1;CONF:POW:XSL:CONT:SDEL 0");
   DEVICE_WRITE(strCmd)
  
	   
   strCmd.Format("1;TRIG:SOUR IFP");
   DEVICE_WRITE(strCmd)

   strCmd.Format("1;TRIG:THR:IFP -18.5");
   DEVICE_WRITE(strCmd)

    strCmd.Format("1;TRIG:SLOP POS");
   DEVICE_WRITE(strCmd)

   strCmd.Format("1;ABORT:POW:XSL");
   DEVICE_WRITE(strCmd)

    strCmd.Format("1;INIT:POW:XSL;*OPC?");
   DEVICE_QUERY(strCmd)
   
   return DEVICE_SUCCESS;  
}
int CFuncWCDMACAL_CMU::ICDMACalSet_DLPowe(double dDlPower)
{
	 CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRetrytimes=20;
     	 strCmd.Format("1;SOUR:RFG:POW:CDMA %.2f",dDlPower);
     DEVICE_WRITE(strCmd)
		 strCmd.Format("1;*OPC?");
	 do
	 {
		 DEVICE_QUERY(strCmd);
		 strRes=Device_GetReadBuf();
		 if(strRes.Find("1")!=-1)
			 break;
		 Sleep(50);

	 }while(--iRetrytimes>0);
     
    return DEVICE_SUCCESS; 
}
int CFuncWCDMACAL_CMU::ICDMACalSet_DLPower_On(bool bIsOn)
{
     CString strCmd;
	 int iDeviceErr;
   
	CString strRes;
	if(bIsOn)

     strCmd.Format("1;INIT:RFG;*OPC?");
    
	else
	  strCmd.Format("1;ABOR:RFG;*OPC?");
     DEVICE_QUERY(strCmd)

	 return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_CMU::ICDMACalSetLoss(int iCDMABand,const DblVtr & vLossList)
{
  CString strCmd;
	int iDeviceErr;
	CString strRes;
	//double dLossAverage;
			strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:ENABle ON");
	DEVICE_WRITE(strCmd)
		switch(iCDMABand)
	{
		case 800:
			strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE1 824.85 MHZ,OFF,%f,OFF,OFF",vLossList[0]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE2 869.85 MHZ,OFF,%f,OFF,OFF",vLossList[0]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE3 835.74 MHZ,OFF,%f,OFF,OFF",vLossList[1]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE4 880.74 MHZ,OFF,%f,OFF,OFF",vLossList[1]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE5 848.22 MHZ,OFF,%f,OFF,OFF",vLossList[2]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE6 893.22 MHZ,OFF,%f,OFF,OFF",vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 1900:
			strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE1 1851.25 MHZ,OFF,%f,OFF,OFF",vLossList[0]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE2 1931.25 MHZ,OFF,%f,OFF,OFF",vLossList[0]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE3 1878.15 MHZ,OFF,%f,OFF,OFF",vLossList[1]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE4 1958.15 MHZ,OFF,%f,OFF,OFF",vLossList[1]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE5 1908.75 MHZ,OFF,%f,OFF,OFF",vLossList[2]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE6 1988.75 MHZ,OFF,%f,OFF,OFF",vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		default:
			return DEVICE_WRITE_FAIL;
	}


	return DEVICE_SUCCESS;
}