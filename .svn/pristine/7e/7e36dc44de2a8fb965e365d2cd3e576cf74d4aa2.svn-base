#include "StdAfx.h"
#include "FuncGSMTest_8820.h"

CFuncGSMTest_8820::CFuncGSMTest_8820(void)
{
}

CFuncGSMTest_8820::~CFuncGSMTest_8820(void)
{
}

CFuncGSMTest_8820::CFuncGSMTest_8820(PCTesterDevice pDev):CFuncDev_8820(pDev)
{

}

int CFuncGSMTest_8820::IGSMTestConfigTestPara()
{

  	CString strCmd;
   int iDeviceErr;
   strCmd.Format(_T("%d;CONFigure:MODulation:PERRor:GMSK:CONTrol SCALar, 200;*OPC?"),m_i8820Mode);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 strCmd.Format(_T("%d;CONFigure:POWer:NORMal:GMSK:CONTrol:REPetition SINGleshot,NONE,NONE;*OPC?"),m_i8820Mode);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

      strCmd.Format(_T("%d;CONFigure:SPECtrum:SWITching:CONTrol SCALar, 200; *OPC?"),m_i8820Mode);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	  strCmd.Format(_T("%d;CONFigure:SPECtrum:MODulation:CONTrol SCALar, 200;*OPC?"),m_i8820Mode);

     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 for(int i=1;i<5;++i)
	 {
	     strCmd.Format(_T("%d;CONFigure:SPECtrum:SWITching:CONTrol:MPOint%d:ENABle ON;*OPC?"),m_i8820Mode,i); 
		  if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		  return iDeviceErr;
	 } 

    return DEVICE_SUCCESS;
}
int CFuncGSMTest_8820::IGSMTestInitGSMtest(const CString& strAddr,int iMode)
{
	m_iPrimaryAddr=strAddr;
    CString strSecAddr;
	CString strCmd;
	CString strReadBuf;
	int iDeviceErr;
	int opcint=0,wait=5;

	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;


	//strCmd=_T("*RST;");
	//DEVICE_WRITE(strCmd);

	 strCmd=_T("BANDCAL;*OPC");
	  DEVICE_WRITE(strCmd)

	  Sleep(200);

	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALLSO;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();

	strCmd=_T("STDSEL?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();


	if(strncmp(strReadBuf,"GSM",3)!=0)	
	{
		strCmd=_T("STDSEL GSM");
		DEVICE_WRITE(strCmd);
		Sleep(500);

		strCmd=_T("STDSEL?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();

		if(strncmp(strReadBuf,"GSM",3)!=0)
		{
			return -1;				
		}  
	}

	strCmd=_T("*RST;");
	DEVICE_WRITE(strCmd);


	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);

	strCmd=_T("RFOUT MAIN");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALLPROC OFF;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();
 
	strCmd=_T("OSIGPAT CCH;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();

	strCmd=_T("OSIGPAT CCHTCH;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();
	
	if (iMode==1)
	{
		strCmd=_T("OPEMODE EGPRS");
		DEVICE_WRITE(strCmd);

		strCmd=_T("SCELL EGPRS;*OPC?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();

		strCmd=_T("CONNTYPE SRBLB");
		DEVICE_WRITE(strCmd);
	}
	else if(iMode==0)
	{
		strCmd=_T("OPEMODE GSM");
		DEVICE_WRITE(strCmd);

		strCmd=_T("SCELL GSM;*OPC?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
	}
	else
	{
		return -1;
	}

	strCmd=_T("ILVLCTRL PCL");
	DEVICE_WRITE(strCmd);
 
	strCmd=_T("SYSCMB DCS1800;BANDIND DCS1800");
	DEVICE_WRITE(strCmd);

	strCmd=_T("LOWESTLIMIT ON;RBWFLT 30KHZ");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CTRLCH 975;*OPC?");
	DEVICE_WRITE(strCmd);

	strCmd=_T("OLVL -60;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();

	strCmd=_T("CHAN 975;*OPC?	");
	DEVICE_WRITE(strCmd);

	if(iMode==1)
	{
		strCmd=_T("MEASOBJ 8PSK");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CS MCS9");
		DEVICE_WRITE(strCmd);

		strCmd=_T("PS P1");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MLTSLTCFG 2DL2UL");
		DEVICE_WRITE(strCmd);

		strCmd=_T("USF 0");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MEASSLOT 2");
		DEVICE_WRITE(strCmd);

		strCmd=_T("PDUS 0");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MSPWR 9");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MSPWR 9");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MSPWR_2ND 9");
		DEVICE_WRITE(strCmd);

	}
	else
	{
		strCmd=_T("MEASOBJ MSNB");
		DEVICE_WRITE(strCmd);
 
		strCmd=_T("MSPWR 5");
		DEVICE_WRITE(strCmd);

	}

	if(iMode==0)
	{
		strCmd=_T("LOOPBACK ON");
		DEVICE_WRITE(strCmd);
	}

	strCmd=_T("TESTPAT PN15");
	DEVICE_WRITE(strCmd);

	Sleep(1000); 
	do 
	{
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		opcint=CStr::StrToInt(strReadBuf);
		Sleep(100);
		wait--;   
	}while( opcint!=1&&wait>=0);

	return DEVICE_SUCCESS;
}
int CFuncGSMTest_8820::IGSMTestInitGSMtest_NSFT(const CString& strAddr,int iFreqMode,int iChan,int iPcl,int iBand)
{
	m_iPrimaryAddr=strAddr;
	CString strSecAddr;
	CString strCmd;
	CString strReadBuf;
	int iDeviceErr;
	int opcint=0,wait=5;

	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;
 

	//strCmd=_T("*RST;");
	//DEVICE_WRITE(strCmd);

	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALLSO;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();

	strCmd=_T("STDSEL?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();


	if(strncmp(strReadBuf,"GSM",3)!=0)	
	{
		strCmd=_T("STDSEL GSM");
		DEVICE_WRITE(strCmd);
		Sleep(500);

		strCmd=_T("STDSEL?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();

		if(strncmp(strReadBuf,"GSM",3)!=0)
		{
			return -1;				
		}  
	}


	strCmd=_T("*RST");
	DEVICE_WRITE(strCmd);
	strCmd=_T("BANDCAL;*OPC");
	DEVICE_WRITE(strCmd)


	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);

	strCmd=_T("RFOUT MAIN");
	DEVICE_WRITE(strCmd);

	//strCmd=_T("LVL OFF;*OPC?");
	//DEVICE_QUERY(strCmd);
	//strReadBuf=Device_GetReadBuf();

	strCmd=_T("CALLPROC OFF;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();

	strCmd=_T("OSIGPAT CCHTCH;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();

	if (iFreqMode==1)
	{
		strCmd=_T("OPEMODE EGPRS");
		DEVICE_WRITE(strCmd);

		strCmd=_T("SCELL EGPRS;*OPC?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf(); 

		strCmd=_T("CONNTYPE SRBLB");
		DEVICE_WRITE(strCmd);
	}
	else if(iFreqMode==0)
	{
		strCmd=_T("OPEMODE GSM");
		DEVICE_WRITE(strCmd);

		strCmd=_T("SCELL GSM;*OPC?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
	}
	else
	{
		return -1;
	}

	strCmd=_T("ILVLCTRL PCL");
	DEVICE_WRITE(strCmd);

	if (iBand==FTM_GSM_BER_PCS_1900)
	{
		strCmd=_T("SYSCMB PCS1900;BANDIND PCS1900");
		DEVICE_WRITE(strCmd);
	}
	else
	{
		strCmd=_T("SYSCMB DCS1800;BANDIND DCS1800");
		DEVICE_WRITE(strCmd);
	}
	

	strCmd=_T("LOWESTLIMIT ON;RBWFLT 30KHZ");
	DEVICE_WRITE(strCmd);

	strCmd.Format("CTRLCH %d;*OPC",iChan);
	DEVICE_WRITE(strCmd);

	strCmd=_T("OLVL -60;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();

	strCmd.Format("CHAN %d;*OPC",iChan);
	DEVICE_WRITE(strCmd);

	if(iFreqMode==1)
	{
		strCmd=_T("MEASOBJ 8PSK");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CS MCS9");
		DEVICE_WRITE(strCmd);

		strCmd=_T("PS P1");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MLTSLTCFG 2DL2UL");
		DEVICE_WRITE(strCmd);

		strCmd=_T("USF 0");
		DEVICE_WRITE(strCmd);

		//strCmd=_T("MEASSLOT 2");
		//DEVICE_WRITE(strCmd);

		strCmd=_T("PDUS 0");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MSPWR 9");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MSPWR 9");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MSPWR_2ND 9");
		DEVICE_WRITE(strCmd);

	}
	else
	{
		strCmd=_T("MEASOBJ MSNB");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MSPWR 5");
		DEVICE_WRITE(strCmd);
		strCmd=_T("SLTNUM 2");
		DEVICE_WRITE(strCmd);
		

	}

	if(iFreqMode==0)
	{
		strCmd=_T("LOOPBACK ON");
		DEVICE_WRITE(strCmd);
	}

	strCmd=_T("TESTPAT PN15");
	DEVICE_WRITE(strCmd);

	do 
	{
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		opcint=CStr::StrToInt(strReadBuf);
		Sleep(100);
		wait--;   
	}while( opcint!=1&&wait>=0);

	return DEVICE_SUCCESS;
}

int CFuncGSMTest_8820::IGSMTestSetBand(int iBand)
{
   int iSecAddr;
   CString strCMuModeStr;
   CString strCmd;
   int iDeviceErr;
	switch(iBand)
	{
	case 850:
		m_i8820Mode = _GSM850MS_SIG;
        iSecAddr=SAD_BASE+_GSM850MS_SIG;
		strCMuModeStr=IDSTR_GSM850MS_SIG;
		break;
	case 900:
		m_i8820Mode = _GSM900MS_SIG;
        iSecAddr=SAD_BASE+_GSM900MS_SIG;
		strCMuModeStr=IDSTR_GSM900MS_SIG;
		break;
	case 1800:
		m_i8820Mode = _GSM1800MS_SIG;
        iSecAddr=SAD_BASE+_GSM1800MS_SIG;
		strCMuModeStr=IDSTR_GSM1800MS_SIG;
		break;
	case 1900:
			m_i8820Mode = _GSM1900MS_SIG;
        iSecAddr=SAD_BASE+_GSM1900MS_SIG;
		strCMuModeStr=IDSTR_GSM1900MS_SIG;
		break;

	default:
		return ERR_DEVICE_GSMTEST_SET_BAND;
	}

	  iSecAddr=SAD_BASE+1;

	 if((iDeviceErr=OpenSecAddr(m_iPrimaryAddr,iSecAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

	 strCmd.Format(_T("0;SYST:REM:ADDR:SEC %d,NONE;*OPC?; :SYST:REM:ADDR:SEC %d,\"%s\""),m_i8820Mode,m_i8820Mode,strCMuModeStr);
       if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	   strCmd.Format(_T("0;SYST:REM:ADDR:SEC? %d"));
       if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	return DEVICE_SUCCESS;
}
int CFuncGSMTest_8820::IGSMTestSetPCL(int iPCL)
{
	CString strCmd;
	int iDeviceErr;
	strCmd.Format("MSPWR %d",iPCL);
	DEVICE_WRITE(strCmd);

    return DEVICE_SUCCESS;
}
int CFuncGSMTest_8820::IGSMTestSetBSLev(double dLev)
{
     CString strCmd;
   int iDeviceErr;
   strCmd.Format(_T("%d;CONFigure:BSSignal:CSWitched:TCH:LEVel:UTIMeslot %f;*OPC?"),m_i8820Mode,dLev);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    
	return DEVICE_SUCCESS;
}

int CFuncGSMTest_8820::IGSMTestSetCH(int iBCCH,int iTCCH)
{
     CString strCmd;
    int iDeviceErr;

	strCmd.Format(_T("%d;CONFigure:BSSignal:CCH:TX:CHANnel %d; :CONFigure:BSSignal:CSWitched:TCH:CHANnel %d;*OPC?"),m_i8820Mode,iBCCH,iTCCH);
   if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    

	return DEVICE_SUCCESS;
}
int CFuncGSMTest_8820::IGSMTestProceMTC()
{
  
    CString strCmd;
    int iDeviceErr;
	strCmd.Format(_T("%d;PROCedure:SIGNalling:ACTion MTC;*OPC?"),m_i8820Mode);
     if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
     return DEVICE_SUCCESS; 

}
int  CFuncGSMTest_8820::IGSMTestProceActOnOff(bool bOn)
{
    CString strCmd;
    int iDeviceErr;
	CString strSub;
	bOn?strSub=_T("SON"):strSub=_T("SOFF");
	strCmd.Format(_T("%d;PROCedure:SIGNalling:CSWitched:ACTion %s;*OPC?"),m_i8820Mode,strSub);
    if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
   return DEVICE_SUCCESS;
}
int CFuncGSMTest_8820::IGSMTestQueryCallState(CString & strState)
{
    CString strCmd;
    int iDeviceErr;
	strCmd.Format(_T("%d;SIGNalling:STATe?"),m_i8820Mode);
    if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

   strState=Device_GetReadBuf();
   return DEVICE_SUCCESS;
}

int CFuncGSMTest_8820::IGSMTestConfigGSMTest()
{
  CString strCmd;
    int iDeviceErr;
	strCmd.Format(_T("%d;CONFigure:NETWork:CSWitched:SMODe:TRAFfic FRV1;*OPC?"),m_i8820Mode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
   
    strCmd.Format(_T("%d;CONFigure:BSSignal:CSWitched:TCH:SSLot:TIMeslot 2;:CONFigure:NETWork:NSUPport GSM;*OPC?"),m_i8820Mode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

    strCmd.Format(_T("%d;CONFigure:MSSignal:TCH:TADVance 0;*OPC?"),m_i8820Mode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

   
    strCmd.Format(_T("%d;CONFigure:MSSignal:CSWitched:TCH:SSLot:LOOP C; :CONFigure:BSSignal:CCH:TX:MODE BATC;*OPC?"),m_i8820Mode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    strCmd.Format(_T("%d;CONFigure:NETWork:CSWitched:SMODe:SCHannel NONE"),m_i8820Mode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

     strCmd.Format(_T(" %d;CONFigure:NETWork:IDENtity:LAC 0001; :PROCedure:SIGNalling:CSWitched:ACTion SOFF;*OPC?"),m_i8820Mode);
   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    return DEVICE_SUCCESS;
}
int CFuncGSMTest_8820::IGSMTestSetBitStream(BitDataType eType)
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
	strCmd.Format(_T("%d;CONFigure:NETWork:CSWitched:SMODe:BITStream %s;*OPC?"),m_i8820Mode,strType);

   if((iDeviceErr=Device_Query(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

   return DEVICE_SUCCESS;

}
int CFuncGSMTest_8820::IGSMTestSetInputLevel(double dMax,bool bAuto)
{
	 CString strCmd;
    int iDeviceErr;
	if(bAuto)
	{
		strCmd.Format(_T("%d;LEVel:MODE AUTomatic;:LEVel:MAXimum %4.1f"),m_i8820Mode,dMax);
	}
	else
	{
        strCmd.Format(_T("%d;LEVel:MODE MAN;:LEVel:MAXimum %4.1f"),m_i8820Mode,dMax); 
	}
  
   if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
    
  return DEVICE_SUCCESS;
}


int CFuncGSMTest_8820::IGSMTestSetScreen(int iScreenOFF)
{
	CString strSecAddr;
	CString strCmd;
	CString strReadBuf;
	int iDeviceErr;
	
	if (iScreenOFF)
	{
		strCmd=_T("SCREEN OFF");
		DEVICE_WRITE(strCmd);
		
		strCmd=_T("MEASMODE FAST");
		DEVICE_WRITE(strCmd);
	}
	else
	{
		strCmd=_T("SCREEN ON");
		DEVICE_WRITE(strCmd);

		strCmd=_T("MEASMODE NORM");
		DEVICE_WRITE(strCmd);
	}

	strCmd=_T("TEMP_MEAS OFF;VSTIME_MEAS OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("MOD_MEAS OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("ORFSSW_MEAS OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("ORFSMD_MEAS OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("ILVLCTRL PCL");
	DEVICE_WRITE(strCmd);

	strCmd=_T("MEASTRG TS");
	DEVICE_WRITE(strCmd);

	strCmd=_T("LVL ON;*OPC?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();

	return DEVICE_SUCCESS;	
}

int CFuncGSMTest_8820::IGSMTestSetTCH(int iChan, int  iPCL)
{
	CString strCmd;
	int iDeviceErr;
	strCmd.Format("CHAN %d",iChan);
	DEVICE_WRITE(strCmd);

	strCmd.Format("MSPWR %d",iPCL);
	DEVICE_WRITE(strCmd);

	return DEVICE_SUCCESS;
}

int CFuncGSMTest_8820::IGSMTestHandOver(int iBand,int iChannel,int iPCL,int iFreqMode,int iSlotNum)
{
	CString strCmd;
	int iDeviceErr;

	if (iBand!=PHONE_MODE_GSM_1900)
	{
		strCmd=_T("SYSCMB DCS1800");
		DEVICE_WRITE(strCmd);
	}
	else
	{
		strCmd=_T("SYSCMB PCS1900");
		DEVICE_WRITE(strCmd);
	}

	strCmd=_T("OLVL -60;*OPC?");
	DEVICE_WRITE(strCmd);

	strCmd.Format("CTRLCH %d;*OPC?",iChannel);
	DEVICE_WRITE(strCmd);

	strCmd.Format("CHAN %d;*OPC?",iChannel);
	DEVICE_WRITE(strCmd);

	strCmd=_T("ILVLCTRL PCL");
	DEVICE_WRITE(strCmd);

	strCmd=_T("ILVLCTRL_REF TCH");
	DEVICE_WRITE(strCmd);

	if(iFreqMode==0)
	{
		strCmd.Format("MSPWR %d;*OPC?",iPCL);
		DEVICE_WRITE(strCmd);
		strCmd.Format("SLTNUM %d",iSlotNum);
		DEVICE_WRITE(strCmd);
	}
	else if(iFreqMode==1)
	{
		strCmd.Format("MSPWR %d;*OPC?",iPCL);
		DEVICE_WRITE(strCmd);

		strCmd.Format("MSPWR_2ND %d;*OPC?",iPCL);
		DEVICE_WRITE(strCmd);
	}

	strCmd=_T("LVL ON;*OPC?");
	DEVICE_WRITE(strCmd);
	Sleep(500);   //changed by yu at 20141030

	return DEVICE_SUCCESS;
}

int CFuncGSMTest_8820::IGSMTestStartTxMeasurment(int BurstQty,int loopi,CStringVtr & strRes,CString strTestItem,int iEdge)
{

	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	int imstat;
	int iTryTimes=150;

	if (iEdge==0)
	{
		strCmd=_T("PWR_MEAS ON;MOD_MEAS ON;TEMP_MEAS ON;BER_MEAS OFF;ORFSMD_MEAS ON;ORFSSW_MEAS ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("MOD_COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("PWR_COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("ORFSMD_COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("ORFSSW_COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("PWR_TEMPSTD");
		DEVICE_WRITE(strCmd);

		strCmd=_T("SWP");
		DEVICE_WRITE(strCmd);		
		do 
		{
			strCmd=_T("MSTAT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			imstat=CStr::StrToInt(strReadBuf);
			Sleep(100);
			iTryTimes--;   
		}while( imstat!=0 && iTryTimes>0);
		if (iTryTimes==0)
		{
			return DEVICE_QUERY_FAIL;
		}

	
		if (strTestItem.Find("A1")!=-1)
		{
			strCmd=_T("AVG_TXPWR?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("B1")!=-1)
		{
			strCmd=_T("MAX_PPHASEERR?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("C1")!=-1)
		{
			strCmd=_T("AVG_PHASEERR?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("D1")!=-1)
		{
			strCmd=_T("AVG_CARRFERR? HZ");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("E1")!=-1)
		{
			strCmd=_T("AVG_PWRTEMP?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("F1")!=-1)
		{
			Sleep(200);
			strCmd=_T("ORFSSW_JUDGE?");
			DEVICE_QUERY_DELAY(strCmd,300);
			strReadBuf=Device_GetReadBuf();
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("G1")!=-1)
		{
			strReadBuf.Empty();

			strCmd=_T("AVG_LSWPWR? OF1800");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_LSWPWR? OF1200");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_LSWPWR? OF600");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_LSWPWR? OF400");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_USWPWR? OF400");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_USWPWR? OF600");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_USWPWR? OF1200");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_USWPWR? OF1800");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf();

			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("H1")!=-1)
		{
			strCmd=_T("ORFSMD_JUDGE?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("I1")!=-1)
		{
			CString strTemp;
			double dPower30kHz,dLOF1000,dUOF1000,dLOF600,dUOF600,dLOF400,dUOF400,dLOF250,dUOF250,dLOF200,dUOF200,dLOF100,dUOF100;
			strReadBuf.Empty();

			strCmd=_T("AVG_LMODPWR? OF0");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dPower30kHz=CStr::StrToFloat(strTemp);
			//strReadBuf+=strTemp+',';

			strCmd=_T("AVG_LMODPWR? OF1000");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dLOF1000=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				dLOF1000+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dLOF1000);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_LMODPWR? OF600");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dLOF600=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				dLOF600+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dLOF600);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_LMODPWR? OF400");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dLOF400=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				dLOF400+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dLOF400);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_LMODPWR? OF250");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dLOF250=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				//dLOF250+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dLOF250);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_LMODPWR? OF200");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dLOF200=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				//dLOF200+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dLOF200);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_LMODPWR? OF100");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dLOF100=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				//dLOF100+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dLOF100);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_UMODPWR? OF100");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dUOF100=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				//dUOF100+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dUOF100);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_UMODPWR? OF200");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dUOF200=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				//dUOF200+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dUOF200);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_UMODPWR? OF250");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dUOF250=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				//dUOF250+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dUOF250);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_UMODPWR? OF400");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dUOF400=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				dUOF400+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dUOF400);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_UMODPWR? OF600");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dUOF600=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				dUOF600+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dUOF600);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_UMODPWR? OF1000");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dUOF1000=CStr::StrToFloat(strTemp);
			if (loopi==2)
			{
				dUOF1000+=dPower30kHz;
			}
			strTemp=CStr::FloatToStr(dUOF1000);
			strReadBuf+=strTemp;

			strRes.push_back(strReadBuf);
		}
		strCmd=_T("PWR_MEAS OFF;MOD_MEAS OFF;TEMP_MEAS OFF;BER_MEAS OFF;ORFSMD_MEAS OFF;ORFSSW_MEAS OFF");
		DEVICE_WRITE(strCmd);
	}else if (iEdge==1)
	{

		strCmd.Format("MEASOBJ 8PSK");
		DEVICE_WRITE(strCmd);

		strCmd.Format("ILVLCTRL_REF TCH");
		DEVICE_WRITE(strCmd);

		strCmd.Format("PWR_MEAS ON;MOD_MEAS ON;TEMP_MEAS ON;GPRSBER_MEAS OFF;ORFSMD_MEAS ON;ORFSSW_MEAS ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("MOD_COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("PWR_COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("ORFSMD_COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("ORFSSW_COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("PWR_TEMPSTD");
		DEVICE_WRITE(strCmd);		
		
		strCmd.Format("SWP");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("MSTAT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			imstat=CStr::StrToInt(strReadBuf);
			Sleep(100);
			iTryTimes--;   
		}while( imstat!=0 && iTryTimes>0);
		if (iTryTimes==0)
		{
			return DEVICE_QUERY_FAIL;
		}		

		if (strTestItem.Find("A1")!=-1)
		{
			strCmd=_T("AVG_TXPWR?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("B1")!=-1)
		{
			strCmd=_T("MAX_PEVM?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("C1")!=-1)
		{
			strCmd=_T("AVG_EVM?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("D1")!=-1)
		{
			strCmd=_T("EVM95PCT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("E1")!=-1)
		{
			strCmd=_T("AVG_ORGNOFS?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("F1")!=-1)
		{
			strCmd=_T("AVG_CARRFERR? HZ");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("G1")!=-1)
		{
			strCmd=_T("AVG_PWRTEMP?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("H1")!=-1)
		{
			strCmd=_T("ORFSSW_JUDGE?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("I1")!=-1)
		{
			strReadBuf.Empty();

			strCmd=_T("AVG_LSWPWR? OF1800");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_LSWPWR? OF1200");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_LSWPWR? OF600");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_LSWPWR? OF400");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_USWPWR? OF400");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_USWPWR? OF600");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_USWPWR? OF1200");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_USWPWR? OF1800");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf();

			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("J1")!=-1)
		{
			strCmd=_T("ORFSMD_JUDGE?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strRes.push_back(strReadBuf);
		}

		if (strTestItem.Find("K1")!=-1)
		{
			CString strTemp;
			double dPower30kHz,dLOF400,dUOF400;
			strReadBuf.Empty();

			strCmd=_T("AVG_LMODPWR? OF0");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dPower30kHz=CStr::StrToFloat(strTemp);
			//strReadBuf+=strTemp+',';

			strCmd=_T("AVG_LMODPWR? OF1000");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_LMODPWR? OF400");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dLOF400=CStr::StrToFloat(strTemp)+dPower30kHz;
			strTemp=CStr::FloatToStr(dLOF400);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_LMODPWR? OF250");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_LMODPWR? OF200");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_UMODPWR? OF200");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_UMODPWR? OF250");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf()+',';

			strCmd=_T("AVG_UMODPWR? OF400");
			DEVICE_QUERY(strCmd);
			strTemp.Empty();
			strTemp=Device_GetReadBuf();
			dUOF400=CStr::StrToFloat(strTemp)+dPower30kHz;
			strTemp=CStr::FloatToStr(dUOF400);
			strReadBuf+=strTemp+',';

			strCmd=_T("AVG_UMODPWR? OF1000");
			DEVICE_QUERY(strCmd);
			strReadBuf+=Device_GetReadBuf();

			strRes.push_back(strReadBuf);
		}
		strCmd.Format("PWR_MEAS OFF;MOD_MEAS OFF;TEMP_MEAS OFF;GPRSBER_MEAS OFF;ORFSMD_MEAS OFF;ORFSSW_MEAS OFF");
		DEVICE_WRITE(strCmd);



	}


	//MessageBox(NULL,strReadBuf,"123",MB_OK);

	return DEVICE_SUCCESS;
}

int CFuncGSMTest_8820::IGSMTestStartRxLevelMeasurment(double dCellpower)
{
	CString strReadBuf;
	CString strCmd;
	int iRet=0;
	int iDeviceErr;

	strCmd.Format("OLVL %f;*OPC?",dCellpower);
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();
	iRet=CStr::StrToInt(strReadBuf);

	if (!iRet)
	{
		return DEVICE_QUERY_FAIL;
	}

	Sleep(20);

	return DEVICE_SUCCESS;
}

int CFuncGSMTest_8820::IGSMTestStartRxBerMeasurment(int BurstQty,double dCellpower,double &dSebr,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	int iRet=0,iNodata=0,iRetryTimes=3;

	if (strTestItem.Find("X1")!=-1)
	{
		strCmd.Format("OLVL %f;*OPC?",(dCellpower+5));
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();

		Sleep(200);
		strCmd=_T("BER_MEASINPUT RF");
		DEVICE_WRITE(strCmd);
		strCmd=_T("LBTYPE FAST");

		DEVICE_WRITE(strCmd);
		strCmd.Format("BER_SAMPLE FAST,%d",BurstQty);
		DEVICE_WRITE(strCmd);
		strCmd.Format("MEASSTOP");
		DEVICE_WRITE(strCmd);
		strCmd=_T("BER_MEAS ON");
		DEVICE_WRITE(strCmd);
		strCmd=_T("ILVLCTRL_REF TCH");
		DEVICE_WRITE(strCmd);
		strCmd=_T("LVL ON;*OPC?");
		DEVICE_WRITE(strCmd);
		
		strCmd.Format("OLVL %f",dCellpower);
		DEVICE_WRITE(strCmd);

/*
		strCmd=_T("DLSLTLVL 0,0");
		DEVICE_WRITE(strCmd);

		strCmd=_T("DLSLTLVL 2,-25");
		DEVICE_WRITE(strCmd);

		strCmd=_T("VARDLSLT ON");
		DEVICE_WRITE(strCmd);*/

		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();

		Sleep(20);
		/*strCmd=_T("SNGLS");
		DEVICE_WRITE(strCmd);*/

		do 
		{
			strCmd=_T("SWP");
			DEVICE_WRITE(strCmd);

			strCmd=_T("MSTAT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			iRet=CStr::StrToInt(strReadBuf);

			if (iRet)
			{
				Sleep(200);
				iNodata=1;
			}
			else
			{
				strCmd=_T("LOOPBACK ON");
				DEVICE_WRITE(strCmd);
				iNodata=0;
				strCmd=_T("BER? FAST");
				DEVICE_QUERY(strCmd);
				strReadBuf=Device_GetReadBuf();
			}

		} while (((iNodata==1)||(CStr::StrToFloat(strReadBuf)>=2.4))&&(iRetryTimes-->0));				

		if(iNodata==1)
		{
			return DEVICE_QUERY_FAIL;
		}
		dSebr=CStr::StrToFloat(strReadBuf);

		strCmd=_T("BER_MEAS OFF");
		DEVICE_WRITE(strCmd);


		strCmd=_T("VARDLSLT OFF");
		DEVICE_WRITE(strCmd);

		strCmd=_T("OLVL -75;*OPC?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
	}
	
	return DEVICE_SUCCESS;
}

int  CFuncGSMTest_8820::IGSMTestSetLoss(int iGSMBand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;

	strCmd.Format("DELLOSSTBL"); 
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


	switch(iGSMBand)
	{
	case GSM_850_BAND_ID:
			strCmd.Format("LOSSTBLVAL 869.2MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 824.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 881.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 836.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 893.8MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 848.8MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case GSM_EGSM_BAND_ID:
			strCmd.Format("LOSSTBLVAL 925.2MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 880.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 942.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 897.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 959.8MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 914.8MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case GSM_DCS_BAND_ID:
			strCmd.Format("LOSSTBLVAL 1805.2MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1710.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1842.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1747.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1879.8MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1784.8MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case GSM_PCS_BAND_ID:
			strCmd.Format("LOSSTBLVAL 1930.2MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1850.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1960.0MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1880.0MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1989.8MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1909.8MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	default:
		return DEVICE_WRITE_FAIL;
	}

	return DEVICE_SUCCESS;
}