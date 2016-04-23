#include "StdAfx.h"
#include "FuncGSMTest_CMU.h"

CFuncGSMTest_CMU::CFuncGSMTest_CMU(void)
{
}

CFuncGSMTest_CMU::CFuncGSMTest_CMU(PCTesterDevice pDev):CFuncDev_CMU(pDev)
{
    	
}
CFuncGSMTest_CMU::~CFuncGSMTest_CMU(void)
{
}
int CFuncGSMTest_CMU::IGSMTestConfigTestPara()
{
  	CString strCmd;
   int iDeviceErr;
   strCmd.Format(_T("%d;CONFigure:MODulation:PERRor:GMSK:CONTrol SCALar, 200;*OPC?"),m_iCMUMode);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 strCmd.Format(_T("%d;CONFigure:POWer:NORMal:GMSK:CONTrol:REPetition SINGleshot,NONE,NONE;*OPC?"),m_iCMUMode);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

      strCmd.Format(_T("%d;CONFigure:SPECtrum:SWITching:CONTrol SCALar, 200; *OPC?"),m_iCMUMode);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd.Format(_T("%d;CONFigure:SPECtrum:MODulation:CONTrol SCALar, 200;*OPC?"),m_iCMUMode);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 for(int i=1;i<5;++i)
	 {
	     strCmd.Format(_T("%d;CONFigure:SPECtrum:SWITching:CONTrol:MPOint%d:ENABle ON;*OPC?"),m_iCMUMode,i); 
		  if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		  return iDeviceErr;
	 } 

    return DEVICE_SUCCESS;
}
int CFuncGSMTest_CMU::IGSMTestInitGSMtest(const CString& strAddr)
{
	m_iPrimaryAddr=strAddr;
    CString strSecAddr;
	CString strCmd;
	int iDeviceErr;
    if((iDeviceErr=OpenSecAddr(strAddr,SAD_BASE))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 strCmd=_T("0;*CLS;*OPC?");
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
     strCmd=_T("SYST:NONV:DIS");

     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	strCmd=_T("TRAC:REM:MODE:DISP ON");
    
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	if(m_pTesterDevice->m_bInternalReference)
	{
		strCmd=_T("CONF:SYNC:FREQ:REF:MODE INT");

     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	}

	strCmd=_T("SYSTem:REMote:RDMode ON");

     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
     //RF_NSig
	 strCmd.Format(_T(MAP_COMMAND),_RF_NSIG,IDSTR_RF_NSIG);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

    //RF_GSM900Sig
	 strCmd.Format(_T(MAP_COMMAND),_GSM900MS_SIG,IDSTR_GSM900MS_SIG);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  //RF_GSM850Sig
	 strCmd.Format(_T(MAP_COMMAND),_GSM850MS_SIG,IDSTR_GSM850MS_SIG);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

      //RF_GSM1800Sig
	 strCmd.Format(_T(MAP_COMMAND),_GSM1800MS_SIG,IDSTR_GSM1800MS_SIG);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
      //RF_GSM1900Sig
     strCmd.Format(_T(MAP_COMMAND),_GSM1900MS_SIG,IDSTR_GSM1900MS_SIG);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     
      if((iDeviceErr=OpenSecAddr(strAddr,SAD_BASE+_RF_NSIG))!=DEVICE_SUCCESS)
		return iDeviceErr;

      m_iCMUMode=_RF_NSIG;

        if((iDeviceErr=SetInput(m_pTesterDevice->m_iInputPort))!=DEVICE_SUCCESS)
		return iDeviceErr;

		if((iDeviceErr=SetOutput(m_pTesterDevice->m_iOutputPort))!=DEVICE_SUCCESS)
		return iDeviceErr;


      if((iDeviceErr=Device_Clear())!=DEVICE_SUCCESS)
		return iDeviceErr;

	return DEVICE_SUCCESS;
}
int CFuncGSMTest_CMU::IGSMTestSetBand(int iBand)
{
   int iSecAddr;
   CString strCMuModeStr;
   CString strCmd;
   int iDeviceErr;
	switch(iBand)
	{
	case 850:
		m_iCMUMode = _GSM850MS_SIG;
        iSecAddr=SAD_BASE+_GSM850MS_SIG;
		strCMuModeStr=IDSTR_GSM850MS_SIG;
		break;
	case 900:
		m_iCMUMode = _GSM900MS_SIG;
        iSecAddr=SAD_BASE+_GSM900MS_SIG;
		strCMuModeStr=IDSTR_GSM900MS_SIG;
		break;
	case 1800:
		m_iCMUMode = _GSM1800MS_SIG;
        iSecAddr=SAD_BASE+_GSM1800MS_SIG;
		strCMuModeStr=IDSTR_GSM1800MS_SIG;
		break;
	case 1900:
			m_iCMUMode = _GSM1900MS_SIG;
        iSecAddr=SAD_BASE+_GSM1900MS_SIG;
		strCMuModeStr=IDSTR_GSM1900MS_SIG;
		break;

	default:
		return ERR_DEVICE_GSMTEST_SET_BAND;
	}

	  //iSecAddr=SAD_BASE+1;

	 if((iDeviceErr=OpenSecAddr(m_iPrimaryAddr,iSecAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 strCmd.Format(_T("0;SYST:REM:ADDR:SEC %d,NONE;*OPC?; :SYST:REM:ADDR:SEC %d,\"%s\""),m_iCMUMode,m_iCMUMode,strCMuModeStr);
       if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	   strCmd.Format("0;SYST:REM:ADDR:SEC? %d",m_iCMUMode);
       if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	return DEVICE_SUCCESS;
}
int CFuncGSMTest_CMU::IGSMTestSetPCL(int iPCL)
{
	CString strCmd;
   int iDeviceErr;
   strCmd.Format(_T("%d;CONFigure:MSSignal:CSWitched:TCH:SSLot:MS:PCL %d;*OPC?"),m_iCMUMode,iPCL);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    return DEVICE_SUCCESS;
}
int CFuncGSMTest_CMU::IGSMTestSetBSLev(double dLev)
{
     CString strCmd;
   int iDeviceErr;
   strCmd.Format(_T("%d;CONFigure:BSSignal:CSWitched:TCH:LEVel:UTIMeslot %f;*OPC?"),m_iCMUMode,dLev);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    
	return DEVICE_SUCCESS;
}

int CFuncGSMTest_CMU::IGSMTestSetCH(int iBCCH,int iTCCH)
{
     CString strCmd;
    int iDeviceErr;

	strCmd.Format(_T("%d;CONFigure:BSSignal:CCH:TX:CHANnel %d; :CONFigure:BSSignal:CSWitched:TCH:CHANnel %d;*OPC?"),m_iCMUMode,iBCCH,iTCCH);
   if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    

	return DEVICE_SUCCESS;


}
int CFuncGSMTest_CMU::IGSMTestProceMTC()
{
  
    CString strCmd;
    int iDeviceErr;
	strCmd.Format(_T("%d;PROCedure:SIGNalling:ACTion MTC;*OPC?"),m_iCMUMode);
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
     return DEVICE_SUCCESS; 

}
int  CFuncGSMTest_CMU::IGSMTestProceActOnOff(bool bOn)
{
    CString strCmd;
    int iDeviceErr;
	CString strSub;
	bOn?strSub=_T("SON"):strSub=_T("SOFF");
	strCmd.Format(_T("%d;PROCedure:SIGNalling:CSWitched:ACTion %s;*OPC?"),m_iCMUMode,strSub);
    if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
   return DEVICE_SUCCESS;
}
int CFuncGSMTest_CMU::IGSMTestQueryCallState(CString & strState)
{
    CString strCmd;
    int iDeviceErr;
	strCmd.Format(_T("%d;SIGNalling:STATe?"),m_iCMUMode);
    if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

   strState=Device_GetReadBuf();
   return DEVICE_SUCCESS;
}

int CFuncGSMTest_CMU::IGSMTestConfigGSMTest()
{
  CString strCmd;
    int iDeviceErr;
	strCmd.Format(_T("%d;CONFigure:NETWork:CSWitched:SMODe:TRAFfic FRV1;*OPC?"),m_iCMUMode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
   
    strCmd.Format(_T("%d;CONFigure:BSSignal:CSWitched:TCH:SSLot:TIMeslot 2;:CONFigure:NETWork:NSUPport GSM;*OPC?"),m_iCMUMode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

    strCmd.Format(_T("%d;CONFigure:MSSignal:TCH:TADVance 0;*OPC?"),m_iCMUMode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

   
    strCmd.Format(_T("%d;CONFigure:MSSignal:CSWitched:TCH:SSLot:LOOP C; :CONFigure:BSSignal:CCH:TX:MODE BATC;*OPC?"),m_iCMUMode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    strCmd.Format(_T("%d;CONFigure:NETWork:CSWitched:SMODe:SCHannel NONE"),m_iCMUMode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     strCmd.Format(_T(" %d;CONFigure:NETWork:IDENtity:LAC 0001; :PROCedure:SIGNalling:CSWitched:ACTion SOFF;*OPC?"),m_iCMUMode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    return DEVICE_SUCCESS;
}
int CFuncGSMTest_CMU::IGSMTestSetBitStream(BitDataType eType)
{
     CString strCmd;
    int iDeviceErr;
	CString strType;

	switch(eType)
	{
	case PR9:
     strType=_T("PR9");
		  break;
    case PR11:
     strType=_T("PR11");
		  break;
	case PR15:
     strType=_T("PR15");
		  break;
     case ECHO:
     strType=_T("ECHO");
		  break;
 
	 default:
      strType=_T("PR15");
		  break;
	}
	strCmd.Format(_T("%d;CONFigure:NETWork:CSWitched:SMODe:BITStream %s;*OPC?"),m_iCMUMode,strType);

   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

   return DEVICE_SUCCESS;

}
int CFuncGSMTest_CMU::IGSMTestSetInputLevel(double dMax,bool bAuto)
{
	 CString strCmd;
    int iDeviceErr;
	if(bAuto)
	{
		strCmd.Format(_T("%d;LEVel:MODE AUTomatic;:LEVel:MAXimum %4.1f"),m_iCMUMode,dMax);
	}
	else
	{
        strCmd.Format(_T("%d;LEVel:MODE MAN;:LEVel:MAXimum %4.1f"),m_iCMUMode,dMax); 
	}
  
   if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    
  return DEVICE_SUCCESS;
}
