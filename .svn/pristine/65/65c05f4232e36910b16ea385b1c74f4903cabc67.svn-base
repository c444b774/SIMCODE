#include "StdAfx.h"
#include "FuncWCDMACal_8960.h"

CFunWCDMACal_8960::CFunWCDMACal_8960(void)
{
}

CFunWCDMACal_8960::~CFunWCDMACal_8960(void)
{
  
}

CFunWCDMACal_8960::CFunWCDMACal_8960(PCTesterDevice pDev):CFuncDev_8960(pDev)
{
  
}
int CFunWCDMACal_8960::ICDMACalInit(const CString& strAddr)
{

   CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

     
      strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
      DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();
	  if(strRes.Find("IS-2000")==-1)
	  {
         strCmd=_T("SYSTEM:APPLICATION:CURRENT:NAME?");
		DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
		if(strRes.Find("\"Fast Switch Test App\"")!=-1)
		{
             strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME 'IS-2000/IS-95/AMPS'");
	         DEVICE_WRITE(strCmd) 
			 strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
	         DEVICE_QUERY(strCmd)
		     strRes=Device_GetReadBuf();
			if(strRes.Find("IS-2000")==-1)
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
      DEVICE_QUERY_DELAY(strCmd,1000)

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

		}

     strCmd=_T("CALL:CELL:OPERATING:MODE D2KTEST");
	  DEVICE_WRITE(strCmd)

		

		  strCmd=_T("CALL:CONTROL:DOWNLINK:FREQUENCY:AUTO OFF");
	  DEVICE_WRITE(strCmd)
		   strCmd=_T("CALL:AWGN:POW:STAT:SEL OFF");
	  DEVICE_WRITE(strCmd)
 
		   return DEVICE_SUCCESS;  

}
int CFunWCDMACal_8960::IWCDMACalInit(const CString& strAddr)
{
     CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

     
      strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
      DEVICE_QUERY(strCmd)
      strRes=Device_GetReadBuf();
	  if(strRes.Find("WCDMA")==-1)
	  {
         strCmd=_T("SYSTEM:APPLICATION:CURRENT:NAME?");
		DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
		if(strRes.Find("Fast Switch")!=-1)
		{
             strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME 'WCDMA'");
	         DEVICE_WRITE(strCmd) 
			 strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
	         DEVICE_QUERY(strCmd)
		     strRes=Device_GetReadBuf();
			if(strRes.Find("WCDMA")==-1)
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

		}

     strCmd=_T("CALL:CELL:OPERATING:MODE FDDTEST");
	  DEVICE_WRITE(strCmd)

		  strCmd=_T("CALL:SERVice:RBTest:RAB RMC12");
	  DEVICE_WRITE(strCmd)

		  strCmd=_T("CALL:CONTROL:DOWNLINK:FREQUENCY:AUTO OFF");
	  DEVICE_WRITE(strCmd)
		   strCmd=_T("CALL:AWGN:POW:STAT:SEL OFF");
	  DEVICE_WRITE(strCmd)
		   strCmd=_T("SETUP:WCPOWER:COUNT:STATE OFF");
	  DEVICE_WRITE(strCmd)
		   strCmd=_T("SETUP:WCPOWER:CONTINUOUS OFF");
	  DEVICE_WRITE(strCmd)


        
	  
   return DEVICE_SUCCESS;  
}
int  CFunWCDMACal_8960::IWCDMACalSetMaxPower(double dMaxPower)
{

	 CString strCmd;
   int iDeviceErr;

    
   strCmd.Format("RFAN:CONT:POW:AUTO OFF");
   DEVICE_WRITE(strCmd)
   
   strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %0.2f;*OPC?",dMaxPower);
   DEVICE_QUERY(strCmd)

   

   return DEVICE_SUCCESS;  

}
int CFunWCDMACal_8960::IWCDMAFetchCPRResult(int iMeasCount,double & dCPWR)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   int iRetryTimes=20; 
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
	 Sleep(500);

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
int CFunWCDMACal_8960::IWCDMAFetchWTDPResults(DblVtr & dvtrResults)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   CStringVtr vtrResults;
   int iRetryTimes=20;
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
	 Sleep(500);

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
	 if(strTemp.Find("0")==-1&&strTemp.Find("6")==-1&&strTemp.Find("5")==-1)
	 return  DEVICE_INTEGERITY_NOTRIGHT;
     
	 CStr::StrVtr2DblVtr(dvtrTemp,vtrResults);
	
	 dvtrResults.assign(dvtrTemp.begin()+1,dvtrTemp.end());
  //   for(int i=0;i<dvtrResults.size();++i)
//	dvtrResults[i]-=0.26;  // according to QSPR
      strCmd.Format("INITIATE:WTDP:OFF");
      DEVICE_WRITE(strCmd)

     return DEVICE_SUCCESS;  
}
int CFunWCDMACal_8960::IWCDMASetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz)
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
	   int iRetryTimes=50;
   do
   {
	   strCmd.Format("*CLS");
	   DEVICE_WRITE(strCmd)
		   strCmd.Format("INITiate:ON?");
	   DEVICE_QUERY(strCmd)
		   strRes=Device_GetReadBuf();
	   if(strRes.Find("WTDP")!=-1)
		   break;
	   Sleep(15);

   }while(--iRetryTimes>0);

   if(iRetryTimes==0)
	   return DEVICE_FINDRES_FAIL;
   
   return DEVICE_SUCCESS;  
}

int CFunWCDMACal_8960::IWCDMACalSetChannel(int iBand,int iULChannel)
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
int CFunWCDMACal_8960::ILTECalSetLoss(int iBand,const DblVtr & vLossList)
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
	switch(iBand)
	{
	case 1:
		strCmd=_T("SYST:CORR:SFR 2110MHZ,2140MHZ,2170MHZ,1920MHZ,1950MHZ,1980MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 2:
		strCmd=_T("SYST:CORR:SFR 1930MHZ,1960MHZ,1990MHZ,1850MHZ,1880MHZ,1910MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 3:
		strCmd=_T("SYST:CORR:SFR 1805MHZ,1843MHZ,1880MHZ,1711MHZ,1748MHZ,1785MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 4:
		strCmd=_T("SYST:CORR:SFR 2110MHZ,2132MHZ,2155MHZ,1711MHZ,1748MHZ,1785MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 5:
		strCmd=_T("SYST:CORR:SFR 869MHZ,882MHZ,894MHZ,824MHZ,837MHZ,849MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 7:
		strCmd=_T("SYST:CORR:SFR 2620MHZ,2652MHZ,2690MHZ,2500MHZ,2536MHZ,2570MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 8:
		strCmd=_T("SYST:CORR:SFR 925MHZ,942MHZ,960MHZ,880MHZ,897MHZ,915MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 12:
		strCmd=_T("SYST:CORR:SFR 728MHZ,737MHZ,746MHZ,698MHZ,707MHZ,716MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 14:
		strCmd=_T("SYST:CORR:SFR 758MHZ,763MHZ,768MHZ,788MHZ,795MHZ,798MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 17:
		strCmd=_T("SYST:CORR:SFR 734MHZ,740MHZ,746MHZ,704MHZ,710MHZ,716MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 20:
		strCmd=_T("SYST:CORR:SFR 791MHZ,806MHZ,821MHZ,832MHZ,847MHZ,862MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 25:
		strCmd=_T("SYST:CORR:SFR 1930MHZ,1950MHZ,1970MHZ,1850MHZ,1870MHZ,1890MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 26:
		strCmd=_T("SYST:CORR:SFR 859MHZ,869MHZ,879MHZ,814MHZ,824MHZ,834MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2],-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;

	case 34:
		strCmd=_T("SYST:CORR:SFR 2110 MHZ,2117MHZ,2124 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 38:
		strCmd=_T("SYST:CORR:SFR 2570 MHZ,2590MHZ,2620 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 39:
		strCmd=_T("SYST:CORR:SFR 1880 MHZ,1900 MHZ,1920 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 40:
		strCmd=_T("SYST:CORR:SFR 2300 MHZ,2350 MHZ,2400 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f",-vLossList[0],-vLossList[1],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	default:
		return DEVICE_WRITE_FAIL;
	}
	return DEVICE_SUCCESS;

}
int  CFunWCDMACal_8960::IWCDMACalSetLoss(int iWCDMABand,const DblVtr & vLossList)
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
	case 1800:
		strCmd.Format("SYST:CORR:FREQ 1807.6 MHZ,1712.6 MHZ, 1840 MHZ,1745 MHZ, 1877.4 MHZ,1782.4 MHZ");
		DEVICE_WRITE(strCmd)

			strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)

			break;
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
int CFunWCDMACal_8960::IWCDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName)
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
int CFunWCDMACal_8960::IDevicesSetIOPort(int iIOPort)
{
	return DEVICE_SUCCESS;
}
int CFunWCDMACal_8960::IGPSSetLoss(double dLoss)
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
	
	strCmd=_T("SYST:CORR:SFR 1575.42MHZ");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SYST:CORR:GAIN %.2f",-dLoss);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SYST:CORR:STATE ON");
	DEVICE_WRITE(strCmd)
	return DEVICE_SUCCESS;

}
int CFunWCDMACal_8960::IWCDMACalSetXOSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower)
{
     CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 

	  strCmd=_T("CALL:CELL:OPERating:MODE CW;*OPC?");
     DEVICE_QUERY(strCmd)
      double doffset=(double)((double)iFreqOffKhz/(double)1000);
     iDlMHz+=doffset;

	 
	 strCmd.Format("CALL:CONTrol:DOWNLINK:FREQuency:AUTO OFF");
	  DEVICE_WRITE(strCmd)

	 strCmd.Format("CALL:RFG:FREQ %0.2fMHz;*OPC?",iDlMHz);
     DEVICE_QUERY(strCmd)
	strCmd=_T("RFANalyzer:CONTrol:MEASurement:FREQuency:AUTO OFF");
	 DEVICE_WRITE(strCmd)
		 strCmd.Format("RFANalyzer:MANual:MEASurement:MFREQuency %0.2fMHz;*OPC?",dUlMHz);
	 DEVICE_QUERY(strCmd)

	 
	  strCmd.Format("CALL:POW %0.2f;*OPC?",dDlPower);
     DEVICE_QUERY(strCmd)

	   
	  strCmd.Format("CALL:POW:STAT ON;*OPC?");
     DEVICE_QUERY(strCmd)
		 Sleep(20);
	 
     return DEVICE_SUCCESS;
}


//CDMA OPERATION
int CFunWCDMACal_8960::ICDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName)
{
  CString strCmd;
	 int iDeviceErr;
   
	CString strRes;

     strCmd=_T("CALL:CELL:OPERating:MODE D2KTEST;*OPC?");
     DEVICE_QUERY(strCmd)
     
	 strCmd.Format("CALL:CONTrol:DOWNLINK:FREQuency:AUTO OFF");
	  DEVICE_WRITE(strCmd)

	 strCmd.Format("CALL:RFG:FREQ %0.2fMHz;*OPC?",iDlMHz+iFreqOffKhz/1000);
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
int CFunWCDMACal_8960::ICDMACalSetMaxPower(double dMaxPower)
{
    return   IWCDMACalSetMaxPower(dMaxPower);
}
int CFunWCDMACal_8960::ICDMAFetchCPRResult(int iMeasCount,double & dCPWR)
{
    CString strCmd;
   int iDeviceErr;
   CString strRes;
   int iRetryTimes=20; 
   CStringVtr vtrResults;

   strCmd.Format("SETup:CPOWer:CONTinuous OFF");
   DEVICE_WRITE(strCmd)

   strCmd.Format("SETup:CPOWer:COUNt %d",iMeasCount);
   DEVICE_WRITE(strCmd)

   strCmd.Format("INITiate:CPOWer;*OPC?");
   DEVICE_QUERY(strCmd)

    do
   {
     strCmd.Format("INITiate:DONE?");
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 if(strRes.Find("CPOW")!=-1)
		 break;
	 Sleep(500);

   }while(--iRetryTimes>0);

   if(iRetryTimes==0)
	   return DEVICE_FINDRES_FAIL;

    strCmd.Format("FETCh:CPOWer?");
    DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",vtrResults);
	dCPWR=CStr::StrToFloat(vtrResults[1]);
   return DEVICE_SUCCESS;  

}
int CFunWCDMACal_8960::ICDMAFetchCTDPResults(DblVtr & dvtrResults)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   CStringVtr vtrResults;
   int iRetryTimes=50;
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
	 if(strRes.Find("CTDP")!=-1)
		 break;
	 Sleep(100);

   }while(--iRetryTimes>0);

   if(iRetryTimes==0)
	   return DEVICE_FINDRES_FAIL;

   strCmd.Format("FETCH:CTDP:COUNT:STEP?");
     DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	 iReadCount=CStr::StrToInt(strRes);
     
     strCmd.Format("FETC:CTDP?",iReadCount);
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 CStr::ParseString(strRes,",",vtrResults);
	 strTemp=vtrResults[0];
	 if(strTemp.Find("0")==-1&&strTemp.Find("5")==-1&&strTemp.Find("6")==-1)
	 return  DEVICE_INTEGERITY_NOTRIGHT;
     
	 CStr::StrVtr2DblVtr(dvtrTemp,vtrResults);
	 dvtrResults.assign(dvtrTemp.begin()+1,dvtrTemp.end());

      strCmd.Format("INITIATE:CTDP:OFF");
      DEVICE_WRITE(strCmd)

     return DEVICE_SUCCESS;  
}
int CFunWCDMACal_8960::ICDMACalSetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
    
   strCmd.Format("SET:CTDP:STEP:TIME MS20");
   DEVICE_WRITE(strCmd)

   strCmd.Format("SET:CTDP:STEP:COUN %d",iCount);
   DEVICE_WRITE(strCmd)
  
	   
	   strCmd.Format("SET:CTDP:STEP:LEVEL %0.4f DB",dStepPower);
   DEVICE_WRITE(strCmd)

   strCmd.Format("SETUP:CTDP:TIMEOUT:STIME %d MS",iCount*20+5000);
   DEVICE_WRITE(strCmd)

   strCmd.Format("INIT:CTDP");
   DEVICE_WRITE(strCmd)
	   strCmd.Format("*CLS");
   DEVICE_WRITE(strCmd)
	int iRetryTimes=50;
	   do
	   {
		   strCmd.Format("*CLS");
		   DEVICE_WRITE(strCmd)
		   strCmd.Format("INITiate:ON?");
		   DEVICE_QUERY(strCmd)
			   strRes=Device_GetReadBuf();
		   if(strRes.Find("CTDP")!=-1)
			   break;
		   Sleep(15);

	   }while(--iRetryTimes>0);

	   if(iRetryTimes==0)
		   return DEVICE_FINDRES_FAIL;
   
   return DEVICE_SUCCESS;  
}
int CFunWCDMACal_8960::ICDMACalSet_DLPowe(double dDlPower)
{
	 CString strCmd,strRes;
	int iDeviceErr;
     strCmd.Format("CALL:CELL:POWER:AMPLITUDE %0.2fDBM;*OPC?",dDlPower);
	 DEVICE_QUERY(strCmd)
		 strRes=Device_GetReadBuf();
	 if (-1!=strRes.Find("1"))
	 {
		 return DEVICE_SUCCESS;
	 }
     
    return DEVICE_FINDRES_FAIL; 
}
int CFunWCDMACal_8960::ICDMACalSet_DLPower_On(bool bIsOn)
{
     CString strCmd;
	 int iDeviceErr;
   
	CString strRes;
	if(bIsOn)

     strCmd.Format("CALL:POW:STAT ON;*OPC?");
	else
	  strCmd.Format("CALL:POW:STAT OFF;*OPC?");
     DEVICE_QUERY(strCmd)

	 return DEVICE_SUCCESS;
}
int CFunWCDMACal_8960::ICDMACalSetLoss(int iCDMABand,const DblVtr & vLossList)
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

	switch(iCDMABand)
	{
	case 820:
		strCmd.Format("SYST:CORR:FREQ 824.85 MHZ,869.85 MHZ, 835.74 MHZ,880.74 MHZ, 848.22 MHZ,893.22 MHZ");
		DEVICE_WRITE(strCmd)

			strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)

			break;
	case 800:
        strCmd.Format("SYST:CORR:FREQ 824.85 MHZ,869.85 MHZ, 835.74 MHZ,880.74 MHZ, 848.22 MHZ,893.22 MHZ");
		 DEVICE_WRITE(strCmd)

		  strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		 DEVICE_WRITE(strCmd)

		break;
	case 1900:
         strCmd.Format("SYST:CORR:FREQ 1851.25 MHZ,1931.25 MHZ, 1878.15 MHZ,1958.15 MHZ, 1908.75 MHZ,1988.75 MHZ");
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