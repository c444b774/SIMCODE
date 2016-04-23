#include "StdAfx.h"
#include "FuncWCDMACAL_8820.h"

CFuncWCDMACAL_8820::CFuncWCDMACAL_8820(void)
{
}

CFuncWCDMACAL_8820::~CFuncWCDMACAL_8820(void)
{
}

CFuncWCDMACAL_8820::CFuncWCDMACAL_8820(PCTesterDevice pDev):CFuncDev_8820(pDev)
{

}

int CFuncWCDMACAL_8820::IWCDMACalInit(const CString& strAddr)
{
     CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr; 
	 

	  strCmd=_T("BANDCAL;*OPC");
	  DEVICE_WRITE(strCmd)
      strCmd=_T("SCRSEL FMEAS");
	  DEVICE_WRITE(strCmd)
    
	  strCmd=_T("CALLSO");
      DEVICE_WRITE(strCmd)
		strCmd.Format("STDSEL?");
	  DEVICE_QUERY(strCmd)
		  strRes=Device_GetReadBuf();

	  if(strRes.Find("WCDMA")==-1&&strRes.Find("LTE")==-1)
	  {
		  for (int i=1;i<5;i++)
		  {
			  strCmd.Format("MCMSV? %d",i);
			  DEVICE_QUERY(strCmd)
				  strRes=Device_GetReadBuf();

			  if(strRes.Find("WCDMA")>-1)
			  {
				  strCmd=_T("STDSEL WCDMA");
				  DEVICE_WRITE(strCmd)
					  Sleep(3000);
				  strCmd=_T("STDSEL?");
				  DEVICE_QUERY(strCmd)
					  strRes=Device_GetReadBuf();

				  if(strRes.Find("WCDMA")>-1)
				  {
					  break; 
				  }

			  }
			  if(strRes.Find("LTE")>-1)
			  {
				  strCmd=_T("STDSEL LTE");
				  DEVICE_WRITE(strCmd)
					  Sleep(3000);
				  strCmd=_T("STDSEL?");
				  DEVICE_QUERY(strCmd)
					  strRes=Device_GetReadBuf();

				  if(strRes.Find("LTE")>-1)
				  {
					  break; 
				  }

			  }
		  }
		  strCmd.Format("STDSEL?");
		  DEVICE_QUERY(strCmd)
			  strRes=Device_GetReadBuf();

		  if(strRes.Find("WCDMA")==-1&&strRes.Find("LTE")==-1)
		  {
			  return DEVICE_FINDRES_FAIL;
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
	 strCmd=_T("STDSEL?");
	 DEVICE_QUERY(strCmd)
		 strRes=Device_GetReadBuf();

	 if(-1<strRes.Find("LTE"))
	 {
		 strCmd=_T("CALLPROC ARB");
		 DEVICE_WRITE(strCmd)

	 }
	 if(-1<strRes.Find("WCDMA"))
	 {
		 strCmd=_T("CALLPROC OFF");
		 DEVICE_WRITE(strCmd)
			 strCmd=_T("ADJ_MEAS OFF");
		 DEVICE_WRITE(strCmd)

			 strCmd=_T("BER_MEAS OFF");
		 DEVICE_WRITE(strCmd)

			 strCmd=_T("BLER_MEAS OFF");
		 DEVICE_WRITE(strCmd)

			 strCmd=_T("FREQ_MEAS OFF");
		 DEVICE_WRITE(strCmd)

			 strCmd=_T("MOD_MEAS OFF");
		 DEVICE_WRITE(strCmd)

			 strCmd=_T("OBW_MEAS OFF");
		 DEVICE_WRITE(strCmd)

			 strCmd=_T("PCDE_MEAS OFF");
		 DEVICE_WRITE(strCmd)

			 strCmd=_T("SMASK_MEAS OFF");
		 DEVICE_WRITE(strCmd)

			 strCmd=_T("PWR_MEAS OFF");
		 DEVICE_WRITE(strCmd)

	 }

       

			  strCmd=_T("RFOUT MAIN");
        DEVICE_WRITE(strCmd)

			  strCmd=_T("MOD OFF");
        DEVICE_WRITE(strCmd)

			  strCmd=_T("MOD ON");
        DEVICE_WRITE(strCmd)


		/*	CString strBuf;
		strCmd.Format("*IDN?");
		DEVICE_QUERY(strCmd);
		strBuf=Device_GetReadBuf();*/
		//if (strBuf.Find("8820B")!=-1)
		//{
		//	strCmd.Format(_T("DLEXTLOSSW COMMON"));
		//	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		//		return iDeviceErr;
		//	strCmd.Format(_T("ULEXTLOSSW COMMON"));
		//	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		//		return iDeviceErr;
		//	strCmd=_T("AUEXTLOSSW COMMON");
		//	DEVICE_WRITE(strCmd)
		//}
		//else
		//{
		//	strCmd.Format(_T("EXTLOSSW COMMON"));
		//	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		//		return iDeviceErr;
		//}

	/*	strCmd.Format(_T("DLEXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
		strCmd.Format(_T("ULEXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;*/

		/*strCmd.Format(_T("EXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;*/

		/*    strCmd=_T("ADJ_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("BER_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("BLER_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("FREQ_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("MOD_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("OBW_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("PCDE_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("SMASK_MEAS OFF");
       DEVICE_WRITE(strCmd)

		    strCmd=_T("PWR_MEAS OFF");
       DEVICE_WRITE(strCmd)*/

		    strCmd=_T("RFOUT MAIN");
       DEVICE_WRITE(strCmd)

	return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_8820::IWCDMACalSetMaxPower(double dMaxPower)
{
    CString strCmd;
   int iDeviceErr;
   CString strRes;
    
  
   
   strCmd.Format("ILVL %0.2f;*OPC?",dMaxPower);
   DEVICE_QUERY(strCmd)

   return DEVICE_SUCCESS;  
}
int CFuncWCDMACAL_8820::IWCDMAFetchWTDPResults(DblVtr & dvtrResults)
{
   CString strCmd;
   int iDeviceErr;
   CString strRes;
   CStringVtr vtrResults;
   int iRetryTimes=10;
   int  iret=-1;
   int iReadCount;
    strCmd.Format("*CLS");
   DEVICE_WRITE(strCmd)

   do
   {
     strCmd.Format("SWP?");
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 iret=CStr::StrToInt(strRes);
	 if(iret==0)
		 break;

   }while(--iRetryTimes>0);

   if(iret!=0)
	   return DEVICE_FINDRES_FAIL;

   strCmd.Format("MPMEAS_NUMSTEP?");
     DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	 iReadCount=CStr::StrToInt(strRes);
     
     strCmd.Format("MRFPWR? 0,%d",iReadCount);
     DEVICE_QUERY(strCmd)
     strRes=Device_GetReadBuf();
	 CStr::ParseString(strRes,",",vtrResults);
     dvtrResults.clear();
	 CStr::StrVtr2DblVtr(dvtrResults,vtrResults);
     return DEVICE_SUCCESS;  
}
int CFuncWCDMACAL_8820::IWCDMASetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz)
{
    CString strCmd;
   int iDeviceErr;
   CString strRes;
    
   strCmd.Format("MPMEAS_STEPTIME 20");
   DEVICE_WRITE(strCmd)

   strCmd.Format("MPMEAS_NUMSTEP %d",iCount);
   DEVICE_WRITE(strCmd)

   strCmd.Format("MPMEAS_TIMEOUT %dMS",iTimeout);
   DEVICE_WRITE(strCmd)

   strCmd.Format("SWPMPMEAS");
   DEVICE_WRITE(strCmd)
   

   return DEVICE_SUCCESS;  
}

int CFuncWCDMACAL_8820::IWCDMACalSetChannel(int iBand,int iULChannel)
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
int CFuncWCDMACAL_8820::ILTECalSetLoss(int iBand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;

	strCmd.Format("DELLOSSTBL"); 
	DEVICE_WRITE(strCmd)

		strCmd.Format("STDSEL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();

	if(-1<strRes.Find("WCDMA"))
	{
		strCmd.Format(_T("DLEXTLOSSW COMMON"));
		DEVICE_WRITE(strCmd)
			strCmd.Format(_T("ULEXTLOSSW COMMON"));
		DEVICE_WRITE(strCmd)
	}
	if(-1<strRes.Find("LTE"))
	{
		strCmd.Format(_T("EXTLOSSW COMMON"));
		DEVICE_WRITE(strCmd)		
	}


	switch(iBand)
	{
	case 1:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1920MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2140MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1950MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2170MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1980MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 2:
		strCmd.Format("LOSSTBLVAL 1930MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1850MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1960MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1990MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1910MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 3:
		strCmd.Format("LOSSTBLVAL 1805MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1711MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1843MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1748MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1785MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 4:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1710MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2132MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1732MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2155MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1755MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 5:
		strCmd.Format("LOSSTBLVAL 869MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 824MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 882MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 837MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 894MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 849MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 7:
		strCmd.Format("LOSSTBLVAL 2620MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2500MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2656MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2536MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2690MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2570MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 8:
		strCmd.Format("LOSSTBLVAL 925MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 880MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 942MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 897MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 960MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 915MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 12:
		strCmd.Format("LOSSTBLVAL 728MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 698MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 737MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 707MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 746MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 716MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 14:
		strCmd.Format("LOSSTBLVAL 758MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 788MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 763MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 793MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 768MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 798MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 17:
		strCmd.Format("LOSSTBLVAL 734MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 704MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 740MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 710MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 746MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 716MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 19:
		strCmd.Format("LOSSTBLVAL 830MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 875MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 837MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 882MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 845MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 890MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 20:
		strCmd.Format("LOSSTBLVAL 791MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 832MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 806MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 847MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 821MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 862MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 21:
		strCmd.Format("LOSSTBLVAL 1448MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1496MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1455MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1503MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1463MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1511MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 25:
		strCmd.Format("LOSSTBLVAL 1930MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1850MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1950MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1870MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1970MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1890MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 26:
		strCmd.Format("LOSSTBLVAL 859MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 814MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 869MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 824MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 879MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 834MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 28:
		strCmd.Format("LOSSTBLVAL 758MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 703MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 779.5MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 724.5MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 803MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 748MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 34:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2010MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2117MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2017MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2124MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2024MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 38:
		strCmd.Format("LOSSTBLVAL 2570MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2470MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2595MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2495MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2620MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2520MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 39:
		strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1780MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1900MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1800MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1920MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1820MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 40:
		strCmd.Format("LOSSTBLVAL 2300MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2200MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2350MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2250MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2400MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2290MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;	
	case 41:
		strCmd.Format("LOSSTBLVAL 2496MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2450MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2590MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2550MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2690MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2650MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	default:
		return DEVICE_WRITE_FAIL;
	}

	return DEVICE_SUCCESS;
}
int  CFuncWCDMACAL_8820::IWCDMACalSetLoss(int iWCDMABand,const DblVtr & vLossList)
{
    CString strCmd;
	 int iDeviceErr;
   
	CString strRes;

     strCmd.Format("DELLOSSTBL");
     DEVICE_WRITE(strCmd)

		 strCmd.Format("STDSEL?");
	 DEVICE_QUERY(strCmd)
		 strRes=Device_GetReadBuf();

	 if(-1<strRes.Find("WCDMA"))
	 {
		 strCmd.Format(_T("DLEXTLOSSW COMMON"));
		 DEVICE_WRITE(strCmd)
			 strCmd.Format(_T("ULEXTLOSSW COMMON"));
		 DEVICE_WRITE(strCmd)
	 }
	 if(-1<strRes.Find("LTE"))
	 {
		 strCmd.Format(_T("EXTLOSSW COMMON"));
		 DEVICE_WRITE(strCmd)		
	 }

	/* strCmd.Format(_T("EXTLOSSW COMMON"));
	 if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		 return iDeviceErr;*/

	switch(iWCDMABand)
	{
	case 1800:
		strCmd.Format("LOSSTBLVAL 1712.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1807.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1840MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1745MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1877.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1782.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 2100:
		strCmd.Format("LOSSTBLVAL 2112.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1922.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 2140MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1950MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 2167.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1977.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		 break;
	case 1900:
        strCmd.Format("LOSSTBLVAL 1854.2MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1934.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1960MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 1906.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1986.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;
	case 1500:
         strCmd.Format("LOSSTBLVAL 1478.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1430.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 1486MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1438MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 1493.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1445.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;
	case 900:
		 strCmd.Format("LOSSTBLVAL 882.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 927.46MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 897.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 942.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 912.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 957.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;
	case 850:
		 strCmd.Format("LOSSTBLVAL 871.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 826.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		 DEVICE_WRITE(strCmd)
        strCmd.Format("LOSSTBLVAL 880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 835MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
		  strCmd.Format("LOSSTBLVAL 891.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 846.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
		break;
	default:
		return DEVICE_WRITE_FAIL;
	}

    return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_8820::ICDMACalSetMaxPower(double dMaxPower)
{
   return IWCDMACalSetMaxPower(dMaxPower);
}
int CFuncWCDMACAL_8820::ICDMAFetchCPRResult(int iMeasCount,double & dCPWR)
{
	  CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;

	  strCmd.Format("PWR_MEAS ON");
	  DEVICE_WRITE(strCmd)
		  strCmd.Format("PWR_AVG %d",iMeasCount);
	  DEVICE_WRITE(strCmd)

	   strCmd.Format("SWP");
	  DEVICE_WRITE(strCmd)

	   strCmd.Format("AVG_POWER?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   dCPWR=CStr::StrToFloat(strRes);

	    strCmd.Format("PWR_MEAS OFF");
	  DEVICE_WRITE(strCmd)
    return DEVICE_SUCCESS;

}
int CFuncWCDMACAL_8820::ICDMACalSet_DLPowe(double dDlPower)
{
	  CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;

	  
     strCmd.Format("OLVL %0.2fDBM;*OPC?",dDlPower);
	
	 DEVICE_QUERY(strCmd)
    return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_8820::ICDMACalSet_DLPower_On(bool bIsOn)
{
    CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
		
	  if(bIsOn)
		  strCmd.Format("LVL ON;*OPC?");
	  else
		   strCmd.Format("LVL OFF;*OPC?");

	 DEVICE_QUERY(strCmd)
    return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_8820::IWCDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName)
{
	return 	ICDMACalSetNormalSig(dUlMHz,iDlMHz,iFreqOffKhz,dDlPower,strWavaFileName);
}
int CFuncWCDMACAL_8820:: IWCDMAFetchCPRResult(int iMeasCount,double & dCPWR)
{

	return ICDMAFetchCPRResult(iMeasCount,dCPWR);

}

int CFuncWCDMACAL_8820::IWCDMAESCalLinearconfig(int Mod,double dBandWidth,int iSegmentTime,DblVtr dvTRxFreq,DblVtr dvTxLvlRef,DblVtr dvRxLvl,int iNumSegment,int iNumSequence)
{
	CString strCmd;
	CString strBuff;
	int iDeviceErr;
	CString strRes;
	int iloop=0;


	strCmd.Format("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)

		strCmd=_T("STDSEL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();

	if(-1<strRes.Find("LTE"))
	{
		strCmd=_T("CALLPROC ARB");
		DEVICE_WRITE(strCmd)

	}
	if(-1<strRes.Find("WCDMA"))
	{
		strCmd=_T("CALLPROC OFF");
		DEVICE_WRITE(strCmd)

	}
		strCmd.Format("MOD OFF");
	DEVICE_WRITE(strCmd)
		if (Mod==1)
		{
			strCmd.Format("MOD ON");
			DEVICE_WRITE(strCmd)
		}
		

		strCmd.Format("ILVL %.2f",dvTxLvlRef[0]);
	DEVICE_WRITE(strCmd)

		/*strCmd.Format("OLVL -80.0");
	DEVICE_WRITE(strCmd)

		strCmd.Format("ILVL %.2f",dvTxLvlRef[0]);
	DEVICE_WRITE(strCmd)


		strCmd.Format("LVLCONT OFF");
	DEVICE_WRITE(strCmd)*/

		
	if (20<dvTRxFreq.size())
	{
		strCmd.Format("REGTX_RX_FREQ %.2f",dvTRxFreq[0]);
		for (iloop=1;iloop<20;iloop++)
		{
			strBuff.Format(",%.2f",dvTRxFreq[iloop]);	
			strCmd=strCmd+strBuff;
		}
		DEVICE_WRITE(strCmd)
		strCmd.Format("REGTX_RX_FREQ2 %.2f",dvTRxFreq[20]);
		for (iloop=21;iloop<dvTRxFreq.size();iloop++)
		{
			strBuff.Format(",%.2f",dvTRxFreq[iloop]);	
			strCmd=strCmd+strBuff;
		}
		DEVICE_WRITE(strCmd)

	} 
	else
	{
		strCmd.Format("REGTX_RX_FREQ %.2f",dvTRxFreq[0]);
		for (iloop=1;iloop<dvTRxFreq.size();iloop++)
		{
			strBuff.Format(",%.2f",dvTRxFreq[iloop]);	
			strCmd=strCmd+strBuff;
		}
		DEVICE_WRITE(strCmd)
	}
	

	

		strCmd.Format("REGMTXREF ON,%.2f",dvTxLvlRef[0]);
	for (iloop=1;iloop<dvTxLvlRef.size();iloop++)
	{
		strBuff.Format(",%.0f",dvTxLvlRef[iloop]);	
		strCmd=strCmd+strBuff;
	}
	
	DEVICE_WRITE(strCmd)

		strCmd.Format("REGMRXPWR %.2f",dvRxLvl[0]);
	for (iloop=1;iloop<dvRxLvl.size();iloop++)
	{
		strBuff.Format(",%.2f",dvRxLvl[iloop]);	
		strCmd=strCmd+strBuff;
	}
	DEVICE_WRITE(strCmd)

		strCmd.Format("TX_RX_SEG_DURATION %d",iSegmentTime);
	DEVICE_WRITE(strCmd)

		strCmd.Format("TX_RX_MW 10,75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("STDSEL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();

	if(-1<strRes.Find("WCDMA"))
	{
		strCmd.Format("LVLCONT OFF");
		DEVICE_WRITE(strCmd)

	}
		
		strCmd.Format("LVL ON");
	DEVICE_WRITE(strCmd)

		strCmd.Format("TX_RX_TRG_TYPE RISE_CONFIG");
	DEVICE_WRITE(strCmd)

		strCmd.Format("TX_RX_TRG_LVL -30");
	DEVICE_WRITE(strCmd)
		if (3==dBandWidth)
		{
			strCmd.Format("TX_RX_FLT RRC;*OPC?");
			DEVICE_QUERY(strCmd)
		}
		else if(10==dBandWidth)
		{
			strCmd.Format("TX_RX_FLT BW10MHz;*OPC?");
			DEVICE_QUERY(strCmd)
		}	

		strCmd.Format("SNGLSTX_RX_FREQ %d,%d",iNumSegment,iNumSequence);
	DEVICE_WRITE(strCmd)

	strCmd.Format("TX_RX_FREQ_READY?");
	int iRetryTimes=20;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();
		if(strRes.Find("1")!=-1)
			break;	
	} while (--iRetryTimes>0);
	if (iRetryTimes==0)
	{
		return DEVICE_INTEGERITY_NOTRIGHT;
	}
	
	return DEVICE_SUCCESS;
	
}
int CFuncWCDMACAL_8820::IWCDMAFetchTXRXResults(DblVtr & dvtrResults)
{
  
     CString strCmd;
   int iDeviceErr;
   int iRetryTimes=20;
   CStringVtr strVtr;
   DblVtr     dVtr;
   CString strRes;

   
   do
	{
             strCmd.Format("SWP?");
	   DEVICE_QUERY(strCmd)
       strRes=Device_GetReadBuf();
	   if(strRes.Find("0")!=-1)
	     break;

       Sleep(500);
	}while(--iRetryTimes>0);

   if(iRetryTimes==0)
	   return DEVICE_INTEGERITY_NOTRIGHT;
   strCmd.Format("MSTAT?");
   DEVICE_QUERY(strCmd)
	   strRes=Device_GetReadBuf();
   if (strRes.Find("0")==-1)
	   return DEVICE_INTEGERITY_NOTRIGHT;
	  
    
   strCmd.Format("TX_RX_FREQ?");
   DEVICE_QUERY(strCmd)
   strRes=Device_GetReadBuf();
   CStr::ParseString(strRes,",",strVtr);
   CStr::StrVtr2DblVtr(dvtrResults,strVtr);
   

   

   strCmd.Format("SCRSEL FMEAS");
	 DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;

}
int CFuncWCDMACAL_8820::IWCDMASetupTXRXComposite(double * dUlFreqMHz,double * dDLFreqMHz,int iNumSteps,double *dRxPowerList,double *dTxMaxLevList)
 {
	 CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
      char cCmd[4096]="";

	   strCmd.Format("SCRSEL FMEAS");
		 DEVICE_WRITE(strCmd)

	  strCmd.Format("ILVL 27;*OPC?");
	 DEVICE_QUERY(strCmd)

		  strCmd.Format("OLVL %.2f;*OPC?",dRxPowerList[0]);
	   DEVICE_QUERY(strCmd)

		   	 strCmd.Format("RXFREQ %.1fMHZ;*OPC?",dDLFreqMHz[0]);
	   DEVICE_QUERY(strCmd)

		
      if(FTM_TX_RX_FREQ_MAX_FREQUENCIES>10)
	{
		 sprintf(cCmd,  "REGTX_RX_FREQ %4.1f,%4.1f",dDLFreqMHz[0],dUlFreqMHz[0]);
	   
		for(int i = 1 ; i< 10; i++)
		{
				sprintf(cCmd,  "%s, %4.1f,%4.1f",cCmd, dDLFreqMHz[i],dUlFreqMHz[i]);
		}

		strCmd.Format("%s;*OPC?",cCmd);
		DEVICE_QUERY(strCmd)

		sprintf(cCmd,  "REGTX_RX_FREQ2 %4.1f,%4.1f",dDLFreqMHz[10],dUlFreqMHz[10]);
	    for(int i = 11 ; i<FTM_TX_RX_FREQ_MAX_FREQUENCIES; i++)
		{
				sprintf(cCmd,  "%s, %4.1f,%4.1f",cCmd, dDLFreqMHz[i],dUlFreqMHz[i]);
		}

		strCmd.Format("%s;*OPC?",cCmd);
		DEVICE_QUERY(strCmd)

	}
	 else
	  {
			 sprintf(cCmd,  "REGTX_RX_FREQ %4.1f,%4.1f",dDLFreqMHz[0],dUlFreqMHz[0]);
		   
			for(int i = 1 ; i< FTM_TX_RX_FREQ_MAX_FREQUENCIES; i++)
			{
					sprintf(cCmd,  "%s, %4.1f,%4.1f",cCmd, dDLFreqMHz[i],dUlFreqMHz[i]);
			}

			strCmd.Format("%s;*OPC?",cCmd);
			DEVICE_QUERY(strCmd)
	  }

        sprintf(cCmd,  "REGMRXPWR %.2f",dRxPowerList[0]);
	   
		for(int i = 1 ; i< iNumSteps; i++)
		{
			    if(dRxPowerList[i]==-110)
					dRxPowerList[i]=dRxPowerList[i-1];
				sprintf(cCmd, "%s, %.2f",cCmd,dRxPowerList[i]);
		}

		strCmd.Format("%s;*OPC?",cCmd);
		DEVICE_QUERY(strCmd)
	

	
            strCmd.Format("TX_RX_SEG_DURATION 20;*OPC?");
	   DEVICE_QUERY(strCmd)
	

		 strCmd.Format("LVLCONT OFF");
	   DEVICE_WRITE(strCmd)


      strCmd.Format("SWPTX_RX_FREQ %d,%d",iNumSteps+1,FTM_TX_RX_FREQ_MAX_FREQUENCIES);
     
	   DEVICE_WRITE(strCmd)

      Sleep(30);
     
    return DEVICE_SUCCESS;  
 }
int CFuncWCDMACAL_8820::ICDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName)
{
	 CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 

       strCmd=_T("MOD ON;*OPC?");
     DEVICE_QUERY(strCmd)

     strCmd.Format("ULFREQ %0.2fMHz;*OPC?",dUlMHz);
     DEVICE_QUERY (strCmd)

	 strCmd.Format("DLFREQ %0.2fMHz;*OPC?",iDlMHz+iFreqOffKhz/1000);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("OLVL %0.2f;*OPC?",dDlPower);
     DEVICE_QUERY(strCmd)

	  strCmd.Format("LVL ON;*OPC?");
     DEVICE_QUERY(strCmd)
		 
    return DEVICE_SUCCESS;



}
int CFuncWCDMACAL_8820::IDevicesSetIOPort(int iIOPort)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_8820::IGPSSetLoss(double dLoss)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	strCmd.Format("DELLOSSTBL"); 
	DEVICE_WRITE(strCmd)
	strCmd.Format(_T("DLEXTLOSSW COMMON"));
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	strCmd.Format(_T("ULEXTLOSSW COMMON"));
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;


	strCmd.Format("LOSSTBLVAL 1575.42MHZ,%0.2f,%0.2f,%0.2f",dLoss,dLoss,dLoss);
	DEVICE_WRITE(strCmd)

	return DEVICE_SUCCESS;
}
int CFuncWCDMACAL_8820::IWCDMACalSetXOSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower)
{
     CString strCmd;
	 int iDeviceErr;
   
	  CString strRes;
	 

	  double doffset=(double)((double)iFreqOffKhz/(double)1000);
     iDlMHz+=doffset;

       strCmd=_T("MOD OFF;*OPC?");
     DEVICE_QUERY(strCmd)
     
     strCmd=_T("RFOUT MAIN;*OPC?");
     DEVICE_QUERY(strCmd)
     strCmd.Format("ULFREQ %0.2fMHz;*OPC?",dUlMHz);
     DEVICE_QUERY (strCmd)	 
	   strCmd.Format("DLFREQ %0.2fMHz;*OPC?",iDlMHz);
     DEVICE_QUERY(strCmd)


	  strCmd.Format("OLVL %0.2f;*OPC?",dDlPower);
     DEVICE_QUERY(strCmd)		

	  strCmd.Format("LVL ON;*OPC?");
     DEVICE_QUERY(strCmd)
		 
    return DEVICE_SUCCESS;
}