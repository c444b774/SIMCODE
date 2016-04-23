#include "StdAfx.h"
#include "FuncGPS_CMW.h"

CFuncGPS_CMW::CFuncGPS_CMW(void)
{
}

CFuncGPS_CMW::~CFuncGPS_CMW(void)
{
}
CFuncGPS_CMW::CFuncGPS_CMW(PCTesterDevice pDev):CFuncDev_CMW(pDev)
{

}
  int CFuncGPS_CMW::IGPSTestInit(const CString& strAddr,const CString& strDlSignal)
  {
	 
   
	 CString strCmd;
	 int iDeviceErr;

	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;
	

	 strCmd=_T("*RST;*OPC?");
     if((iDeviceErr=Device_Query(strCmd,0))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd=_T("*CLS;*OPC?");
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
  

       strCmd.Format(_T("SOUR:GPRF:GEN%d:BBM ARB;*OPC?"),m_pTesterDevice->m_iChannelPort);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

		strCmd.Format(_T("SOURce:GPRF:GEN%d:ARB:FILE \'%s\';*OPC?"),m_pTesterDevice->m_iChannelPort,strDlSignal);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
         strCmd.Format(_T("SOURce:GPRF:GEN%d:ARB:REPetition CONT"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	   strCmd.Format(_T("SOURce:GPRF:GEN%d:LIST OFF"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;




     return DEVICE_SUCCESS;


  }

 
  int CFuncGPS_CMW::IGPSTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss)
  {
        CString strCmd;
	   int iDeviceErr;
       strCmd.Format(_T("SOURce:GPRF:GEN%d:RFSettings:FREQuency %.2f MHz;*OPC?"),m_pTesterDevice->m_iChannelPort,DLFreq);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
		  strCmd.Format(_T("SOURce:GPRF:GEN%d:RFSettings:LEVel %.2f dBm"),m_pTesterDevice->m_iChannelPort,DlPower);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation %.2f",m_pTesterDevice->m_iChannelPort,dCableloss);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
   return DEVICE_SUCCESS;

  }

 int CFuncGPS_CMW::IGPSTestSetOn(bool bIsOn)
 {
    CString strONOFF;
	 CString strCmd;
	 int iDeviceErr;
	strONOFF=bIsOn?"ON":"OFF";

    strCmd.Format(_T("SOURce:GPRF:GEN%d:STATe %s;*OPC?"),m_pTesterDevice->m_iChannelPort,strONOFF);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

    return DEVICE_SUCCESS;
 }
 int CFuncGPS_CMW::IGPSTestSetInOutPort(int iOutPort)
 {
     CString strCmd;
	 int iDeviceErr;
     int iConnector;
	 
	if(iOutPort==5 || iOutPort==6)
	{
       if(iOutPort==5)
       iConnector=1;
	   else if(iOutPort==6)
		iConnector=3;

      strCmd.Format("ROUTe:GPRF:GEN%d:RFS:CONN RF%dO",m_pTesterDevice->m_iChannelPort,iConnector);
	}
	else
	{
		 if(iOutPort==1 || iOutPort==3)
		 iConnector=1;
		 else if(iOutPort==2 || iOutPort==4)
		  iConnector=2;
  
      strCmd.Format("ROUTe:GPRF:GEN%d:RFS:CONN RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
		 
	}
    
	
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;


 return DEVICE_SUCCESS;
 }