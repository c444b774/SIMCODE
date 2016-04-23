#include "StdAfx.h"
#include "FuncWLAN_CMW.h"

CFuncWLAN_CMW::CFuncWLAN_CMW(void)
{
}

CFuncWLAN_CMW::~CFuncWLAN_CMW(void)
{
}
CFuncWLAN_CMW::CFuncWLAN_CMW(PCTesterDevice pDev):CFuncDev_CMW(pDev)
{

}
  int CFuncWLAN_CMW::IWLANTestInit(const CString& strAddr,const CString & strWLANAddr)
  {
	 
   
	 CString strCmd;
	 int iDeviceErr;
     int iConnector;
	 
	 if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;
	

	 strCmd=_T("*RST;*OPC?");
     if((iDeviceErr=Device_Query(strCmd,0))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd=_T("*CLS;*OPC?");
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
     if(m_pTesterDevice->m_iInputPort==1 || m_pTesterDevice->m_iInputPort==3)
     iConnector=1;
	 else
	  iConnector=2;
     if(m_pTesterDevice->m_bIsCommandRX1CMW)
	 strCmd.Format("ROUTe:WLAN:MEAS%d:SCENario:SALone RF%dC,RX1",m_pTesterDevice->m_iChannelPort,iConnector);
	 else
     strCmd.Format("ROUTe:WLAN:MEAS%d:SCENario:SALone RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 strCmd.Format("ROUTe:GPRF:GEN%d:RFS:CONN RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     return DEVICE_SUCCESS;


  }
 int CFuncWLAN_CMW::IWLANTestSetFreq(double AnalyFreq,double dUlPowerMax,double dCableloss)
  {
    CString strCmd;
	int iDeviceErr;

     strCmd.Format(_T("CONFigure:WLAN:MEAS%d:RFSettings:ENPower %.2f"),m_pTesterDevice->m_iChannelPort,dUlPowerMax);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;  
		
	strCmd.Format(_T("CONFigure:WLAN:MEAS%d:RFSettings:UMARgin %d"),m_pTesterDevice->m_iChannelPort,10);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 strCmd.Format(_T("CONFigure:WLAN:MEAS%d:RFSettings:MLOF %d"),m_pTesterDevice->m_iChannelPort,1);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    
      strCmd.Format(_T("CONFigure:WLAN:MEAS%d:RFSettings:FREQuency %.2f MHz"),m_pTesterDevice->m_iChannelPort,AnalyFreq);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd.Format("CONFigure:WLAN:MEAS%d:RFSettings:EATTenuation %.2f",m_pTesterDevice->m_iChannelPort,dCableloss);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     return DEVICE_SUCCESS;
  }
 int CFuncWLAN_CMW::IWLANTestSetDLSigOn(bool bIsOn)
 {
    CString strCmd;
	int iDeviceErr;

	CString strONOFF;
	strONOFF=bIsOn?"ON":"OFF";

    strCmd.Format(_T("SOURce:GPRF:GEN%d:STATe %s;*OPC?"),m_pTesterDevice->m_iChannelPort,strONOFF);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

    return DEVICE_SUCCESS;

 }
  int CFuncWLAN_CMW::IWLANTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss)
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
int CFuncWLAN_CMW::IWLANTestSetDLType(const CString& strWavePath)
{
  
       CString strCmd;
	  int iDeviceErr;
       strCmd.Format(_T("SOUR:GPRF:GEN%d:BBM ARB;*OPC?"),m_pTesterDevice->m_iChannelPort);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

		strCmd.Format(_T("SOURce:GPRF:GEN%d:ARB:FILE \'%s\';*OPC?"),m_pTesterDevice->m_iChannelPort,strWavePath);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
         strCmd.Format(_T("SOURce:GPRF:GEN%d:ARB:REPetition CONTinuous"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd.Format(_T("SOURce:GPRF:GEN%d:ARB:CYCLes 1000"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	   strCmd.Format(_T("SOURce:GPRF:GEN%d:LIST OFF"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 return DEVICE_SUCCESS;

}
int CFuncWLAN_CMW::IWLANTestSetTrackingAllOn()
{
	 CString strCmd;
	  int iDeviceErr;

     strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:COMPensation:TRACking:PHASe ON"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	
     strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:COMPensation:TRACking:TIMing ON"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	   strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:COMPensation:TRACking:LEVel ON"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

       return DEVICE_SUCCESS;
}
int CFuncWLAN_CMW::IWLANTestSetType(const CString& iBurstType)
    {
   
       CString strCmd;
	  int iDeviceErr;

     strCmd.Format(_T("CONFigure:WLAN:MEAS%d:ISIGnal:STANdard %s"),m_pTesterDevice->m_iChannelPort,iBurstType);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

       return DEVICE_SUCCESS;
    }


int CFuncWLAN_CMW::IWLANTestSetTrigger(double TriggerLevel,int iTimeout,int evmGap)
	 {

	  CString strCmd;
	  int iDeviceErr;
    
	    strCmd.Format(_T("TRIGger:WLAN:MEAS%d:MEValuation:SOURce 'IF Power'"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     strCmd.Format(_T("TRIGger:WLAN:MEAS%d:MEValuation:THReshold %.2f"),m_pTesterDevice->m_iChannelPort,TriggerLevel);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

        strCmd.Format(_T("TRIGger:WLAN:MEAS%d:MEValuation:TOUT %d"),m_pTesterDevice->m_iChannelPort,iTimeout);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		 return iDeviceErr;

	   strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:TOUT %d"),m_pTesterDevice->m_iChannelPort,iTimeout);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		 return iDeviceErr;

		  strCmd.Format(_T("TRIGger:WLAN:MEAS%d:MEValuation:SLOP REDG"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	   strCmd.Format(_T("TRIGger:WLAN:MEAS%d:MEValuation:MGAP %d us"),m_pTesterDevice->m_iChannelPort,evmGap);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     return DEVICE_SUCCESS;
      }

int CFuncWLAN_CMW::IWLANTestInitMeasure(int iAvgCount)
	{

  CString strCmd;
	  int iDeviceErr;

	  strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:REPetition SINGleshot"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	   strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:SCONdition NONE"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 
		  strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:SCOunt:MODulation %d"),m_pTesterDevice->m_iChannelPort,iAvgCount);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;
		  strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:SCOunt:TSMask %d"),m_pTesterDevice->m_iChannelPort,iAvgCount);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;
	
		/*   strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:RESult ON,ON,ON,ON,ON,ON,ON"),m_pTesterDevice->m_iChannelPort);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;*/
      
		strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:RES:EVM ON"),m_pTesterDevice->m_iChannelPort);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;

		 strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:RESult:EVMSymbol ON"),m_pTesterDevice->m_iChannelPort);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;

		  strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:RESult:EVMCarrier ON"),m_pTesterDevice->m_iChannelPort);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;

		 
		  strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:RESult:SFLatness ON"),m_pTesterDevice->m_iChannelPort);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;
		 strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:RESult:TSMask ON"),m_pTesterDevice->m_iChannelPort);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;

		  strCmd.Format(_T("CONFigure:WLAN:MEAS%d:MEValuation:RESult:MSCalar ON"),m_pTesterDevice->m_iChannelPort);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;

  

			    strCmd.Format(_T("ABORt:WLAN:MEAS%d:MEValuation;*OPC?"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  
    Sleep(50);

    return DEVICE_SUCCESS;
     }
int CFuncWLAN_CMW::IWLANTestModFetchResults(int RateType,double &dPower,double &dEVM,double &FER)
{
	CString strCmd,strRes;
	CStringVtr strvRes;
	int iDeviceErr;
	int iRes=0;
	strCmd.Format(_T("INIT:WLAN:MEAS%d:MEValuation;*OPC?"),m_pTesterDevice->m_iChannelPort);
	if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	strCmd.Format("FETCh:WLAN:MEAS%d:MEValuation:STATe?",m_pTesterDevice->m_iChannelPort);
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(20);
		strRes=Device_GetReadBuf();	
		iRes=strRes.Find("RDY");
	} while (iRes!=0&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	if (3==RateType)
	{
		strCmd.Format("FETCh:WLAN:MEAS%d:MEValuation:MODulation:DSSS:AVERage?",m_pTesterDevice->m_iChannelPort);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,",",strvRes);
		iRes=CStr::StrToInt(strvRes[0]);
		if (0!=iRes)
		{
			return DEVICE_QUERY_FAIL;
		}

		dPower=CStr::StrToFloat(strvRes[4]);
		dEVM=CStr::StrToFloat(strvRes[6]);
		FER=CStr::StrToFloat(strvRes[7])/1000;
	} 
	else
	{
		strCmd.Format("FETCh:WLAN:MEAS%d:MEValuation:MODulation:OFDM:AVERage?",m_pTesterDevice->m_iChannelPort);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,",",strvRes);
		iRes=CStr::StrToInt(strvRes[0]);
		if (0!=iRes)
		{
			return DEVICE_QUERY_FAIL;
		}

		dPower=CStr::StrToFloat(strvRes[3]);
		dEVM=CStr::StrToFloat(strvRes[4]);
		FER=CStr::StrToFloat(strvRes[7])/1000;
	}

	strCmd.Format("STOP:WLAN:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncWLAN_CMW::IWLANTestFetchResults(int RateType,CStringVtr & dVtr)
	   {
      CString strCmd;
	  int iDeviceErr;
	  int iRetryTimes=50;
	 
	   CString strPVTRes;
	  bool bOk=false;
      do
	  {
		  strCmd.Format(_T("FETCh:WLAN:MEAS%d:MEValuation:STATe:ALL?"),m_pTesterDevice->m_iChannelPort);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
         CString strRes=Device_GetReadBuf();

		
		 if(strRes.Find(_T("RDY"))!=-1)
		 {
			 bOk=true;
			 break;
		 }
		 Sleep(500);

	  }while(--iRetryTimes);

	  if(!bOk)
	  {
		  
		  return -1;
	  }
       if(RateType==1||RateType==4 ||RateType==5) //OFDM
	   {
		   strCmd.Format(_T("FETCh:WLAN:MEAS%d:MEValuation:MODulation:OFDM:AVERage?"),m_pTesterDevice->m_iChannelPort);
			 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
				return iDeviceErr;
			  strPVTRes=Device_GetReadBuf();

			 if(strPVTRes.Find("NAV")!=-1)
		 {
					strCmd.Format(_T("INIT:WLAN:MEAS%d:MEValuation;*OPC?"),m_pTesterDevice->m_iChannelPort);
				if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
					return iDeviceErr;
					Sleep(500); 
                  iRetryTimes=30;
                  bOk=false;
					   do
				  {
					  strCmd.Format(_T("FETCh:WLAN:MEAS%d:MEValuation:STATe:ALL?"),m_pTesterDevice->m_iChannelPort);
					 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
						return iDeviceErr;
					 CString strRes=Device_GetReadBuf();

					
					 if(strRes.Find(_T("RDY"))!=-1)
					 {
						 bOk=true;
						 break;
					 }
					 Sleep(500);

				  }while(--iRetryTimes);
				 if(!bOk)
					  {
						  
						  return -1;
					  }

				  strCmd.Format(_T("FETCh:WLAN:MEAS%d:MEValuation:MODulation:OFDM:AVERage?"),m_pTesterDevice->m_iChannelPort);
			 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
				return iDeviceErr;
			  strPVTRes=Device_GetReadBuf();


		 }

			
			
			 CStr::ParseString(strPVTRes,",",dVtr,false,false);
	   }

     
        strCmd.Format(_T("ABORt:WLAN:MEAS%d:MEValuation"),m_pTesterDevice->m_iChannelPort);
        if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
       return DEVICE_SUCCESS;
   }

int CFuncWLAN_CMW::IWLANTestSetInOutPort(int iInport,int iOutPort)
{

	   CString strCmd;
	 int iDeviceErr;
     int iConnector;
	 
	
     if(iInport==1 || iInport==3)
     iConnector=1;
	 else
	  iConnector=2;

	  if(m_pTesterDevice->m_bIsCommandRX1CMW)
	 strCmd.Format("ROUTe:WLAN:MEAS%d:SCENario:SALone RF%dC,RX1",m_pTesterDevice->m_iChannelPort,iConnector);
	  else
      strCmd.Format("ROUTe:WLAN:MEAS%d:SCENario:SALone RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	   if(iOutPort==1 || iOutPort==3)
     iConnector=1;
	 else
	  iConnector=2;

	 strCmd.Format("ROUTe:GPRF:GEN%d:RFS:CONN RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;


 return DEVICE_SUCCESS;
}
