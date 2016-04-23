#include "StdAfx.h"
#include "FuncBT_CMW.h"

CFuncBT_CMW::CFuncBT_CMW(void)
{
}

CFuncBT_CMW::~CFuncBT_CMW(void)
{
}
CFuncBT_CMW::CFuncBT_CMW(PCTesterDevice pDev):CFuncDev_CMW(pDev)
{

}
  int CFuncBT_CMW::IBTTestInit(const CString& strAddr,const CString & strBTAddr)
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
	 strCmd.Format("ROUTe:BLUetooth:MEAS%d:SCENario:SALone RF%dC,RX1",m_pTesterDevice->m_iChannelPort,iConnector);
	 else
     strCmd.Format("ROUTe:BLUetooth:MEAS%d:SCENario:SALone RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
	 
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;


	 
	 strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:LAP #H",m_pTesterDevice->m_iChannelPort);
	 strCmd+=strBTAddr.Right(6);

	 

     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
     strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:UAP #H",m_pTesterDevice->m_iChannelPort); 
      strCmd+=strBTAddr.Mid(4,2);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
     
	 strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:NAP #H",m_pTesterDevice->m_iChannelPort);
	 strCmd+=strBTAddr.Left(4);

     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     return DEVICE_SUCCESS;


  }
 int CFuncBT_CMW::IBTTestSetFreq(double AnalyFreq,double dUlPowerMax,double dLoss)
  {
    CString strCmd;
	int iDeviceErr;

     strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:RFSettings:ENPower %.2f"),m_pTesterDevice->m_iChannelPort,dUlPowerMax);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;  
		
	strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:RFSettings:UMARgin %d"),m_pTesterDevice->m_iChannelPort,3);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    
      strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:RFSettings:FREQuency %.2f"),m_pTesterDevice->m_iChannelPort,AnalyFreq);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	  strCmd.Format("CONFigure:BLUetooth:MEAS%d:RFSettings:EATTenuation %.2f",m_pTesterDevice->m_iChannelPort,dLoss);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     return DEVICE_SUCCESS;
  }

int CFuncBT_CMW::IBTTestSetType(const CString& iBurstType,const CString& iPacketType)
    {
   
       CString strCmd;
	  int iDeviceErr;

     strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:ISIGnal:BTYPe %s"),m_pTesterDevice->m_iChannelPort,iBurstType);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	   strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:ISIGnal:PTYPe:%s %s"),m_pTesterDevice->m_iChannelPort,iBurstType,iPacketType);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr; 

      strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:ISIGnal:PLENgth:%s?"),m_pTesterDevice->m_iChannelPort,iBurstType);
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

       return DEVICE_SUCCESS;
    }

int CFuncBT_CMW::IBTTestSetBitPattern(const CString& iBitPattern)
    {

    CString strCmd;
	  int iDeviceErr;

     strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:ISIGnal:PATTern %s"),m_pTesterDevice->m_iChannelPort,iBitPattern);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     return DEVICE_SUCCESS;
    }

int CFuncBT_CMW::IBTTestSetTrigger(double TriggerLevel,int iTimeout)
	 {

		  CString strCmd;
		  int iDeviceErr;

		 strCmd.Format(_T("TRIGger:BLUetooth:MEAS%d:MEValuation:THREShold %.2f"),m_pTesterDevice->m_iChannelPort,TriggerLevel);
		 if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

			 strCmd.Format(_T("TRIGger:BLUetooth:MEAS%d:MEValuation:TOUT %d"),m_pTesterDevice->m_iChannelPort,iTimeout);
		 if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;


		 return DEVICE_SUCCESS;
      }

int CFuncBT_CMW::IBTTestInitMeasure(int iAvgCount)
	{

	 CString strCmd;
	  int iDeviceErr;

	  strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:MEValuation:SCONdition NONE"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	   strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:PVTime %d"),m_pTesterDevice->m_iChannelPort,iAvgCount);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;

		  strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:MODulation %d"),m_pTesterDevice->m_iChannelPort,iAvgCount);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;
		  strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:SOBW %d"),m_pTesterDevice->m_iChannelPort,iAvgCount);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;
		  strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:SACP %d"),m_pTesterDevice->m_iChannelPort,iAvgCount);
	     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
       return iDeviceErr;
       
		 strCmd.Format(_T("ABORt:BLUetooth:MEAS%d:MEValuation;*OPC?"),m_pTesterDevice->m_iChannelPort);
        if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

		 strCmd.Format(_T("INIT:BLUetooth:MEAS%d:MEValuation;*OPC?"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd.Format(_T("ABORt:BLUetooth:MEAS%d:MEValuation;*OPC?"),m_pTesterDevice->m_iChannelPort);
        if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

		 strCmd.Format(_T("INIT:BLUetooth:MEAS%d:MEValuation;*OPC?"),m_pTesterDevice->m_iChannelPort);
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
        Sleep(500);

    return DEVICE_SUCCESS;
     }

int CFuncBT_CMW::IBTTestFetchResults(int RateType,CStringVtr & dVtr)
	   {
      CString strCmd;
	  int iDeviceErr;
	  int iRetryTimes=50;
	 
	   CString strPVTRes;
	  bool bOk=false;
      do
	  {
		  strCmd.Format(_T("FETCh:BLUetooth:MEAS%d:MEValuation:STATe:ALL?"),m_pTesterDevice->m_iChannelPort);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
         CString strRes=Device_GetReadBuf();
		 if(strRes.Find(_T("RDY"))!=-1)
		 {
			 bOk=true;
			 break;
		 }
		 Sleep(400);

	  }while(--iRetryTimes);

	  if(!bOk)
	  {
		  
		  return -1;
	  }

	  iRetryTimes=50;
	  bOk=false;
         do
	  {
		  strCmd.Format(_T("FETCh:BLUetooth:MEAS%d:MEValuation:STATe:ALL?"),m_pTesterDevice->m_iChannelPort);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
         CString strRes=Device_GetReadBuf();
		 if(strRes.Find(_T("RDY"))!=-1)
		 {
			 bOk=true;
			 break;
		 }
		 Sleep(200);

	  }while(--iRetryTimes);

	  if(!bOk)
	  {
		  
		  return -1;
	  }
       if(RateType>3)
	   {
       strCmd.Format(_T("FETCh:BLUetooth:MEAS%d:MEValuation:PVTime:EDRate:AVERage?"),m_pTesterDevice->m_iChannelPort);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
		 strPVTRes=Device_GetReadBuf();
		
		 CStr::ParseString(strPVTRes,",",dVtr,false,false);

		  strCmd.Format(_T("FETCh:BLUetooth:MEAS%d:MEValuation:MODulation:EDRate:AVERage?"),m_pTesterDevice->m_iChannelPort);
		 if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
		 strPVTRes=Device_GetReadBuf();
		
		 CStr::ParseString(strPVTRes,",",dVtr,false,false);



         strCmd.Format(_T("ABORt:BLUetooth:MEAS%d:MEValuation"),m_pTesterDevice->m_iChannelPort);
        if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	   }
   
       return DEVICE_SUCCESS;
   }

int CFuncBT_CMW::IBTTestSetInOutPort(int iInPort,int iOutPort)
{
  	 CString strCmd;
	 int iDeviceErr;
     int iConnector;
	 
	
     if(iInPort==1 || iInPort==3)
     iConnector=1;
	 else
	  iConnector=2;
	 if(m_pTesterDevice->m_bIsCommandRX1CMW)
	 {
		 strCmd.Format("ROUTe:BLUetooth:MEAS%d:SCENario:SALone RF%dC,RX1",m_pTesterDevice->m_iChannelPort,iConnector);
		 DEVICE_WRITE(strCmd)		
			 strCmd.Format("ROUTe:GPRF:GENerator%d:SCENario:SALone RF%dC, TX1",m_pTesterDevice->m_iChannelPort,iConnector);
		 DEVICE_WRITE(strCmd)
	 }	 
	 else
	 {
		 strCmd.Format("ROUTe:BLUetooth:MEAS%d:SCENario:SALone RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
		 DEVICE_WRITE(strCmd)
			 strCmd.Format("ROUTe:GPRF:GENerator%d:SCENario:SALone RF%dC",m_pTesterDevice->m_iChannelPort,iConnector);
		 DEVICE_WRITE(strCmd)
	 }
	 return DEVICE_SUCCESS;


}
int CFuncBT_CMW::IBTTestSetChannel(int iChannel)
{
	CString strCmd;
	int iDeviceErr;
	double dFreqHz=2402+iChannel;


	strCmd.Format(_T("CONFigure:BLUetooth:MEAS%d:RFSettings:FREQuency %fMHZ"),m_pTesterDevice->m_iChannelPort,dFreqHz);
	DEVICE_WRITE(strCmd);

	strCmd.Format("SOURce:GPRF:GENerator%d:RFSettings:FREQuency %fMHZ",m_pTesterDevice->m_iChannelPort,dFreqHz);
	DEVICE_WRITE(strCmd);


	return DEVICE_SUCCESS;

}
int CFuncBT_CMW::IBTTestSetCellPower(double dPower)
{
	CString strCmd;
	int iDeviceErr;

	strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:LEVel %.2f",m_pTesterDevice->m_iChannelPort,dPower);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncBT_CMW::IBTTestSetLoss(double dLoss)
{
	CString strCmd;
	int iDeviceErr;

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:RFSettings:EATTenuation %f",m_pTesterDevice->m_iChannelPort,dLoss);
	DEVICE_WRITE(strCmd);

	strCmd.Format("SOUR:GPRF:GEN%d:RFS:EATT %f",m_pTesterDevice->m_iChannelPort,dLoss);
	DEVICE_WRITE(strCmd)
	return DEVICE_SUCCESS;

}
int CFuncBT_CMW::IBTTestPowerMeas(double dExpPower,int iMeasCount,int iBTType,int iDH,double* dPower)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:RFSettings:ENPower %f",m_pTesterDevice->m_iChannelPort,dExpPower);
	DEVICE_WRITE(strCmd);
	if (1==iBTType)
	{
		strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:BTYPe BR",m_pTesterDevice->m_iChannelPort);
		DEVICE_WRITE(strCmd);
		strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PTYPe:BRATe DH%d",m_pTesterDevice->m_iChannelPort,iDH);
		DEVICE_WRITE(strCmd);
	} 
	else
	{
		strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:BTYPe EDR",m_pTesterDevice->m_iChannelPort);
		DEVICE_WRITE(strCmd);
		strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PTYPe:EDRate E%d%dP",m_pTesterDevice->m_iChannelPort,iBTType,iDH);
		DEVICE_WRITE(strCmd);
	}
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PATTern OTHer",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:TOUT 5s",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:REPetition SINGleshot",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:PVTime %d",m_pTesterDevice->m_iChannelPort,iMeasCount);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:PSCalar ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("INITiate:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:STATe?",m_pTesterDevice->m_iChannelPort);
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
	if (1==iBTType)
	{
		strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:PVTime:BRATe:AVERage?",m_pTesterDevice->m_iChannelPort);
		
	} 
	else
	{
		strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:PVTime:EDRate:AVERage?",m_pTesterDevice->m_iChannelPort);
	
	}	
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	*dPower=CStr::StrToFloat(strvRes[2]);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:PSCalar OFF",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("STOP:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);

	return DEVICE_SUCCESS;
}

int CFuncBT_CMW::IBTTestModMeas(double dExpPower,int iMeasCount,int iFreqType,double* dDeltaF)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:RFSettings:ENPower %f",m_pTesterDevice->m_iChannelPort,dExpPower);
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:BTYPe BR",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PTYPe:BRATe DH5",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);	
	if (1==iFreqType)
	{
		strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PATTern P44",m_pTesterDevice->m_iChannelPort);
	} 
	else
	{
		strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PATTern P11",m_pTesterDevice->m_iChannelPort);
	}
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:TOUT 5s",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:REPetition SINGleshot",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:MODulation %d",m_pTesterDevice->m_iChannelPort,iMeasCount);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:MSCalar ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("INITiate:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:STATe?",m_pTesterDevice->m_iChannelPort);
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
	
	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:MODulation:BRATe:AVERage?",m_pTesterDevice->m_iChannelPort);
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	if (1==iFreqType)
	{*dDeltaF=CStr::StrToFloat(strvRes[6])/1000;
	} 
	else
	{*dDeltaF=CStr::StrToFloat(strvRes[11])/1000;
	}
	
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:MSCalar OFF",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("STOP:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}

int CFuncBT_CMW::IBTTestCFDMeas(double dExpPower,int iMeasCount,double* dCFD)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:RFSettings:ENPower %f",m_pTesterDevice->m_iChannelPort,dExpPower);
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:BTYPe BR",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PTYPe:BRATe DH5",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);	
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PATTern P11",m_pTesterDevice->m_iChannelPort);	
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:TOUT 5s",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:REPetition SINGleshot",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:MODulation %d",m_pTesterDevice->m_iChannelPort,iMeasCount);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:MSCalar ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("INITiate:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:STATe?",m_pTesterDevice->m_iChannelPort);
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

	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:MODulation:BRATe:AVERage?",m_pTesterDevice->m_iChannelPort);
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}

	*dCFD=CStr::StrToFloat(strvRes[4])/1000;
	

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:MSCalar OFF",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("STOP:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}

int CFuncBT_CMW::IBTTestICFTMeas(double dExpPower,int iMeasCount,double* dICFTkHz)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:RFSettings:ENPower %f",m_pTesterDevice->m_iChannelPort,dExpPower);
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:BTYPe BR",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PTYPe:BRATe DH1",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);	
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PATTern OTHer",m_pTesterDevice->m_iChannelPort);	
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:TOUT 5s",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:REPetition SINGleshot",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:MODulation %d",m_pTesterDevice->m_iChannelPort,iMeasCount);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:MSCalar ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("INITiate:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:STATe?",m_pTesterDevice->m_iChannelPort);
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

	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:MODulation:BRATe:AVERage?",m_pTesterDevice->m_iChannelPort);
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}

	*dICFTkHz=CStr::StrToFloat(strvRes[3])/1000;


	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:MSCalar OFF",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("STOP:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}

int CFuncBT_CMW::IBTTestEDRModMeas(double dExpPower,int iMeasCount,int iBTType,double* dEVM_RMS,double* dEVM_PEAK)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:RFSettings:ENPower %f",m_pTesterDevice->m_iChannelPort,dExpPower);
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:BTYPe EDR",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PTYPe:EDRATe E%d1P",m_pTesterDevice->m_iChannelPort,iBTType);
	DEVICE_WRITE(strCmd);	
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:PATTern OTHer",m_pTesterDevice->m_iChannelPort);	
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:TOUT 5s",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:REPetition SINGleshot",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:SCOunt:MODulation %d",m_pTesterDevice->m_iChannelPort,iMeasCount);
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:MSCalar ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("INITiate:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:STATe?",m_pTesterDevice->m_iChannelPort);
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

	strCmd.Format("FETCh:BLUetooth:MEAS%d:MEValuation:MODulation:EDRate:AVERage?",m_pTesterDevice->m_iChannelPort);
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}

	*dEVM_RMS=CStr::StrToFloat(strvRes[5])/1000;
	*dEVM_PEAK=CStr::StrToFloat(strvRes[6])/1000;


	strCmd.Format("CONFigure:BLUetooth:MEAS%d:MEValuation:RESult:MSCalar OFF",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("STOP:BLUetooth:MEAS%d:MEValuation",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncBT_CMW::IBTTestInitEx(const CString& strAddr,const CString strWaveForm,const CString & strBTAddr)
{
	CString strCmd,strRes;
	int iDeviceErr;	
	int iRty=50;

	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;


	strCmd=_T("*RST;*OPC?");
	DEVICE_QUERY(strCmd)	

	strCmd=_T("*CLS;*OPC?");
	DEVICE_QUERY(strCmd)
		strCmd=_T("SYSTem:DISPlay:UPDate ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SYSTem:BASE:OPTion:LIST? SWOPtion, VALid");
	DEVICE_QUERY(strCmd);
	strCmd.Format("ROUTe:GPRF:GEN%d:SCENario:SALone RF1C, TX1;*OPC?",m_pTesterDevice->m_iChannelPort);
	DEVICE_QUERY(strCmd);
	strCmd.Format("SOURce:GPRF:GEN%d:BBMode ARB",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)
	strCmd.Format("SOURce:GPRF:GEN%d:ARB:REP CONT",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("SOURce:GPRF:GEN%d:ARB:FILE '%s'",m_pTesterDevice->m_iChannelPort,strWaveForm);
	DEVICE_WRITE(strCmd);
	strCmd.Format("SOURce:GPRF:GEN%d:ARB:FILE?",m_pTesterDevice->m_iChannelPort);
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	if (strRes.Find("BT")==-1)
	{		
		return DEVICE_FINDRES_FAIL;
	}
	strCmd.Format("SOURce:GPRF:GEN%d:STATe ON",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd);
	strCmd.Format("SOURce:GPRF:GEN%d:STATe?",m_pTesterDevice->m_iChannelPort);
	do
	{
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		Sleep(100);
	}while(strRes.Find("ON")==-1&&iRty-->0);
	if (strRes.Find("ON")==-1)
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:ISIGnal:BDADdress #H",m_pTesterDevice->m_iChannelPort);
	strCmd+=strBTAddr;
	DEVICE_WRITE(strCmd)
	strCmd.Format("CONFigure:BLUetooth:MEAS%d:RFSettings:UMARgin 10",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)	

	return DEVICE_SUCCESS;

}