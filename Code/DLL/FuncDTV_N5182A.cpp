#include "StdAfx.h"
#include "FuncDTV_N5182A.h"

CFuncDTV_N5182A::CFuncDTV_N5182A(void)
{
}

CFuncDTV_N5182A::~CFuncDTV_N5182A(void)
{
}
CFuncDTV_N5182A::CFuncDTV_N5182A(PCTesterDevice pDev):CFuncDev_N5182A(pDev)
{

}
  int CFuncDTV_N5182A::IDTVTestInit(const CString& strAddr)
  {
	 
   
	 CString strCmd;
	 int iDeviceErr;
 
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;
	

	 strCmd=_T("*RST;*OPC?");
     if((iDeviceErr=Device_Query(strCmd,30))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd=_T("*CLS;*OPC?");
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
   
     return DEVICE_SUCCESS;


  }
 
 int CFuncDTV_N5182A::IDTVTestSetDLSigOn(bool bIsOn)
 {
    CString strCmd;
	int iDeviceErr;

	CString strONOFF;
	strONOFF=bIsOn?"ON":"OFF";

    strCmd.Format(_T(":OUTP:STAT %s;*OPC?"),strONOFF);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

		 strCmd.Format(_T(":OUTP:MODulation:STAT %s;*OPC?"),strONOFF);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

    return DEVICE_SUCCESS;

 }
  int CFuncDTV_N5182A::IDTVTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss)
  {
        CString strCmd;
	   int iDeviceErr;
       strCmd.Format(_T(":SOUR:FREQ %.2f MHz;*OPC?"),DLFreq);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
		dCableloss=0-dCableloss;  
	  strCmd.Format(":SOUR:POW:LEV:IMM:OFFSet %.2f dBm",dCableloss);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 strCmd.Format(_T(":SOUR:POW:LEV:IMM:AMPL %.2f dBm"),DlPower);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
   return DEVICE_SUCCESS;

  }
int CFuncDTV_N5182A::IDTVTestSetDLType(const CString& strWavePath)
{
  
       CString strCmd;
	  int iDeviceErr;
      

	  
       strCmd.Format(_T(":SOUR:RAD:ARB:WAV \"%s\";*OPC?"),strWavePath);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

		strCmd.Format(_T(":SOUR:RAD:ARB:STAT ON;*OPC?"));
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

     
	 return DEVICE_SUCCESS;

}




int CFuncDTV_N5182A::IDTVTestSetInOutPort(int iInport,int iOutPort)
{

	

 return DEVICE_SUCCESS;
}
