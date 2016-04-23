#include "StdAfx.h"
#include "FuncWCDMATest_CMW.h"

CFuncWCDMATest_CMW::CFuncWCDMATest_CMW(void)
{
}

CFuncWCDMATest_CMW::~CFuncWCDMATest_CMW(void)
{
}
CFuncWCDMATest_CMW::CFuncWCDMATest_CMW(PCTesterDevice pDev):CFuncDev_CMW(pDev)
{

}

int CFuncWCDMATest_CMW::ILteInitSet(const CString& strAddr,const CString strWaveForm,const CString strLTEMode)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRty=150;


	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

	strCmd=_T("*RST");
	DEVICE_WRITE(strCmd);

	strCmd=_T("*OPC?");
	DEVICE_QUERY_DELAY(strCmd,0);
	strCmd=_T("SYSTem:DISPlay:UPDate ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SYSTem:BASE:OPTion:LIST? SWOPtion, VALid");
	DEVICE_QUERY(strCmd);
	strCmd=_T("ROUTe:GPRF:GENerator:SCENario:SALone RFAC, TX1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("ROUTe:GPRF:MEASurement:SCENario:SALone RFAC, RX1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:BBMode ARB");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:REP CONT");
	DEVICE_WRITE(strCmd);
	strCmd.Format("SOURce:GPRF:GENerator:ARB:FILE '%s'",strWaveForm);
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:FILE?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	if (strRes.Find("LTE")==-1)
	{		
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("ROUTe:GPRF:GENerator:RFSettings:CONNector RF1C");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GENerator:STATe ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:STATe?");
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
	
	strCmd=_T("CONFigure:LTE:MEAS:RFSettings:UMARgin 10");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:CBANdwidth B100");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:MODulation:MSCHeme AUTO");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:CPRefix NORmal");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:PRACh:PCINdex 3");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:EVM OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:MERR OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:PERR OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:IEM OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:EVMC OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:IQ OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:ESFL OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:TXM OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:SEM OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:ACLR OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:RBAT OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:PMON OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:BLER OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEAS:MEValuation:RESult:PDYN OFF");
	DEVICE_WRITE(strCmd);
	this->ILteMeasConfig(strLTEMode=="TDD",100);
	
	
	return DEVICE_SUCCESS;

}

int CFuncWCDMATest_CMW::ILteMeasConfig(bool bIsTDD,int iBan)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:REPetition SINGleshot");
	DEVICE_WRITE(strCmd);
	if (bIsTDD)
	{
		strCmd=_T("CONFigure:LTE:MEASurement:DMODe TDD");
	}
	else
	{
		strCmd=_T("CONFigure:LTE:MEASurement:DMODe FDD");

	}	
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:MSUBframes 2, 10, 0");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:SCON NONE ");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:MOEX OFF");
	DEVICE_WRITE(strCmd);
	strCmd.Format("CONFigure:LTE:MEASurement:MEValuation:CBAN B%d",iBan);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONF:LTE:MEAS:MEV:CTYP AUTO");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONF:LTE:MEAS:MEV:RBAL:AUTO ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIG:LTE:MEAS:MEV:SOUR 'GPRF Gen1: Waveform Marker 4'");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::ILteHandOver(int iBand,int iULChannel)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	float dULMHz=0,dDLMHz=0;
	dULMHz=CLTEBandInfo::ArfcnToHz(iBand,iULChannel);
	dDLMHz=CLTEBandInfo::ArfcnToHz(iBand,CLTEBandInfo::GetDLChannel(iBand,iULChannel));
	strCmd.Format("CONFigure:LTE:MEASurement:RFSettings:FREQuency %fMHZ",dULMHz);
	DEVICE_WRITE(strCmd);
	strCmd.Format("SOURce:GPRF:GENerator:RFSettings:FREQuency %fMHZ",dDLMHz);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}

int CFuncWCDMATest_CMW::ILteSetPower(double dCellPower,double dTargetPower,int iTPC)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	strCmd.Format("CONFigure:LTE:MEASurement:RFSettings:ENPower %.2f",dTargetPower);
	DEVICE_WRITE(strCmd);
	strCmd.Format("SOURce:GPRF:GEN:RFSettings:LEVel %.2f",dCellPower);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::ILteConfigWaveForm(int iNumRB,int iStartRB,int iMCS)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::ILteTestPower(const int icount,double *dPower)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	strCmd.Format("CONFigure:LTE:MEASurement:MEValuation:SCOunt:MODulation %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:TXM ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INIT:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd="FETCh:LTE:MEASurement:MEValuation:STATe?";
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();	
		iRes=strRes.Find("RDY");
	} while (iRes!=0&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd="FETCh:LTE:MEASurement:MEValuation:MODulation:AVERage?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	*dPower=CStr::StrToFloat(strvRes[17]);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:TXM OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("STOP:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::ILteTxQual(const int icount,double *dEVM,double *dFERPPM,double *dOgnOfst,double *dSptrFlat,double *dInbEm)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	double dFreqHz=0;
	strCmd=_T("CONFigure:LTE:MEASurement:RFSettings:FREQuency?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dFreqHz=CStr::StrToFloat(strRes);
	strCmd.Format("CONFigure:LTE:MEASurement:MEValuation:SCOunt:MODulation %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:ALL ON,ON,ON,ON,ON,ON,ON,ON,ON,ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:TXM ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INIT:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd="FETCh:LTE:MEASurement:MEValuation:STATe?";
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();	
		iRes=strRes.Find("RDY");
	} while (iRes!=0&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd="FETCh:LTE:MEASurement:MEValuation:MODulation:AVERage?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	*dEVM=CStr::StrToFloat(strvRes[2]);
	*dFERPPM=abs(1000000*CStr::StrToFloat(strvRes[15])/dFreqHz);
	*dOgnOfst=CStr::StrToFloat(strvRes[14]);
	strvRes.clear();
	strCmd="FETCh:LTE:MEAS:MEValuation:IEMission:MARGin:EXTReme?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	*dSptrFlat=CStr::StrToFloat(strvRes[2]);

	strvRes.clear();
	strCmd="FETC:LTE:MEAS:MEV:ESFL:AVER?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	*dInbEm=CStr::StrToFloat(strvRes[1]);

	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:TXM OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("STOP:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::ILteACLR(const int icount,int *isPass,double dACLRValue[])
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	strCmd.Format("CONFigure:LTE:MEASurement:MEValuation:SCOunt:SPECtrum:ACLR %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:ACLR ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INIT:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd="FETCh:LTE:MEASurement:MEValuation:STATe?";
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
	strCmd="FETCh:LTE:MEASurement:MEValuation:ACLR:AVERage?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	dACLRValue[0]=-CStr::StrToFloat(strvRes[1]);
	dACLRValue[1]=-CStr::StrToFloat(strvRes[2]);
	dACLRValue[2]=-CStr::StrToFloat(strvRes[6]);
	dACLRValue[3]=-CStr::StrToFloat(strvRes[7]);
	*isPass=1;
	double daACLRLimit[4]={-35.2,-32.2,-32.2,-35.2};
	for (int i=0;i<4;i++)
	{		
		if (dACLRValue[i]>daACLRLimit[i])
		{
			*isPass=0;
		}
	}
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:ACLR OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("STOP:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_CMW::ILteSEMask(const int icount,int *isPass,double dSEMask[])
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	strCmd.Format("CONFigure:LTE:MEASurement:MEValuation:SCOunt:SPEctrum:SEMask %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:SEMask ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:LIMit:SEMask:LIMit1:CBANdwidth100 ON, 0, 1e+006, -16.5, K030");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:LIMit:SEMask:LIMit2:CBANdwidth100 ON, 1e+006, 5e+006, -8.5, M1");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:LIMit:SEMask:LIMit3:CBANdwidth100 ON, 5e+006, 1e+007, -11.5, M1");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:LIMit:SEMask:LIMit4:CBANdwidth100 ON, 1e+007, 1.5e+007, -23.5, M1");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INIT:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd="FETCh:LTE:MEASurement:MEValuation:STATe?";
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
	strCmd="FETCh:LTE:MEASurement:MEValuation:SEMask:MARGin?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	dSEMask[0]=-23.5-CStr::StrToFloat(strvRes[25]);
	dSEMask[1]=-11.5-CStr::StrToFloat(strvRes[24]);
	dSEMask[2]=-8.5-CStr::StrToFloat(strvRes[23]);
	dSEMask[3]=-16.5-CStr::StrToFloat(strvRes[22]);
	dSEMask[4]=-16.5-CStr::StrToFloat(strvRes[32]);
	dSEMask[5]=-8.5-CStr::StrToFloat(strvRes[33]);
	dSEMask[6]=-11.5-CStr::StrToFloat(strvRes[34]);
	dSEMask[7]=-23.5-CStr::StrToFloat(strvRes[35]);	
	CStringVtr svRes;
	double daSEMaskLimit[8]={-23.5,-11.5,-8.5,-16.5,-16.5,-8.5,-11.5,-23.5};
	*isPass=1;
	if (CStr::StrToFloat(strvRes[1])>0)
	{
		*isPass=0;
	}
/*
	for (int i=0;i<8;i++)
	{
		
		if (dSEMask[i]>daSEMaskLimit[i])
		{
			*isPass=0;
		}
	}*/
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:SEMask OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("STOP:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_CMW::ILteOBW(const int icount,double *dOBW)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	strCmd.Format("CONFigure:LTE:MEASurement:MEValuation:SCOunt:SPEctrum:SEMask %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:SEMask ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INIT:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd="FETCh:LTE:MEASurement:MEValuation:STATe?";
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
	strCmd="FETCh:LTE:MEASurement:MEValuation:SEMask:AVERage?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	*dOBW=CStr::StrToFloat(strvRes[2])/1000000;
	
	strCmd=_T("CONFigure:LTE:MEASurement:MEValuation:RESult:SEMask OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("STOP:LTE:MEASurement:MEValuation");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}


int CFuncWCDMATest_CMW::IWCDMATestInitWCDMAtest(const CString& strAddr)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRty=150;


	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

	strCmd=_T("*RST");
	DEVICE_WRITE(strCmd);

	strCmd=_T("*OPC?");
	DEVICE_QUERY_DELAY(strCmd,0);
	strCmd=_T("SYSTem:DISPlay:UPDate ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SYSTem:BASE:OPTion:LIST? SWOPtion, VALid");
	DEVICE_QUERY(strCmd);
	strCmd=_T("ROUTe:GPRF:GENerator:SCENario:SALone RFAC, TX1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("ROUTe:GPRF:MEASurement:SCENario:SALone RFAC, RX1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:BBMode ARB");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:REP CONT");
	DEVICE_WRITE(strCmd);
	strCmd.Format("SOURce:GPRF:GENerator:ARB:FILE 'D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\library1\\RMC12_2_MultiSegment_0_9_A02.wv'");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:FILE?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	if (strRes.Find("RMC12_2")==-1)
	{		
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("TRIGger:GPRF:GEN:ARB:RETRigger ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:AUTostart ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MODE CSEamless");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:LIST OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:LIMit:RCDerror:EECDp:DPCCh ON, 8, 64");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:LIMit:RCDerror:EECDp:DPDCh ON, 15, 64");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -65;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:UMARgin 10;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("ROUTe:GPRF:GENerator:RFSettings:CONNector RF1C");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GENerator:STATe ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:STATe?");
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


	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);

	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);

	strCmd=_T("ABORt:WCDMa:MEAS:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd=_T("ABORt:WCDMa:MEAS:TPC");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:ALL OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:REPetition SINGleshot");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:TOUT 60");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:MSCount 1");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:SCOunt:MODulation 10");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:SCOunt:SPECtrum 10");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:PSLot 0");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:MOEX OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:UESignal:SFORmat 0");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:UESignal:ULConfig WCDMa");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:UESignal:DPDCh ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOURce 'Free Run (Fast Sync)'");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:MGAP 0");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:LIMit:RCDerror:EECDp:HSDPcch OFF,60,256");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:LIMit:RCDerror:EECDp:EDPCch OFF,30,256");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:LIMit:RCDerror:EECDp:EDPDch2 OFF,168,4");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -55;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:UMARgin 10;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower 24;*OPC?");
	DEVICE_QUERY(strCmd);

	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::IWCDMATestHandOver(int iBand,int iULChannel)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	float dULMHz=0,dDLMHz=0;
	dULMHz=CWCDMABandInfo::ArfcnToHz(iBand,iULChannel,1);
	dDLMHz=CWCDMABandInfo::ArfcnToHz(iBand,CWCDMABandInfo::GetDLChannel(iBand,iULChannel),0);
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -75;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:UMARgin 10;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower 24;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd.Format("CONFigure:WCDMA:MEAS:RFSettings:FREQuency  %.2fMHZ",dULMHz);
	DEVICE_WRITE(strCmd);
	strCmd.Format("SOURce:GPRF:GENerator:RFSettings:FREQuency %.2fMHZ",dDLMHz);
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::IWCDMATestMaxPower(int icount,double *dMaxPower)
{
	CString strCmd;
	int iDeviceErr,iQueryTimes=50;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -75;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower 24;*OPC?");
	DEVICE_QUERY(strCmd);
	Sleep(100);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd.Format("CONFigure:WCDMa:MEAS:MEValuation:SCOunt:MODulation %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:UEPower ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOUR 'GPRF Gen1: Waveform Marker 3'");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INITiate:WCDMa:MEAS:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:STATe?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("RDY"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("RDY"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:TRACe:UEPower:AVERage?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	*dMaxPower=CStr::StrToFloat(strvRes[1]);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:UEPower OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOURce 'Free Run (Fast Sync)'");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::ILteSetLoss(int iBand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;

	strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:DELete \'mytable\'");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:CREate \'mytable\'");
	DEVICE_WRITE(strCmd)



		switch(iBand)
	{
		
		case 1:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2110 MHZ ,%.2f ,2140 MHZ,%.2f,2170 MHZ,%.2f,1920 MHZ,%.2f,1950 MHZ,%.2f,1980 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 2:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1930 MHZ ,%.2f ,1960 MHZ,%.2f,1990 MHZ,%.2f,1850 MHZ,%.2f,1880 MHZ,%.2f,1909 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 3:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1805 MHZ ,%.2f ,1711 MHZ,%.2f,1843 MHZ,%.2f,1748 MHZ,%.2f,1880 MHZ,%.2f,1785 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 4:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2110 MHZ ,%.2f ,1710 MHZ,%.2f,2132 MHZ,%.2f,1732 MHZ,%.2f,2155 MHZ,%.2f,1755 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 5:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 869 MHZ ,%.2f ,824 MHZ,%.2f,882 MHZ,%.2f,837 MHZ,%.2f,894 MHZ,%.2f,849 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 7:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2620 MHZ ,%.2f ,2500 MHZ,%.2f,2656 MHZ,%.2f,2536 MHZ,%.2f,2690 MHZ,%.2f,2570 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 8:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 925 MHZ ,%.2f ,880 MHZ,%.2f,942 MHZ,%.2f,897 MHZ,%.2f,960 MHZ,%.2f,915 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 12:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 728 MHZ ,%.2f ,698 MHZ,%.2f,737 MHZ,%.2f,707 MHZ,%.2f,746 MHZ,%.2f,716 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 14:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 758 MHZ ,%.2f ,788 MHZ,%.2f,763 MHZ,%.2f,793 MHZ,%.2f,768 MHZ,%.2f,798 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 17:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 734 MHZ ,%.2f ,704 MHZ,%.2f,740 MHZ,%.2f,710 MHZ,%.2f,746 MHZ,%.2f,716 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 19:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 830 MHZ ,%.2f ,875 MHZ,%.2f,837 MHZ,%.2f,882 MHZ,%.2f,845 MHZ,%.2f,890 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 20:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 791 MHZ ,%.2f ,832 MHZ,%.2f,806 MHZ,%.2f,847 MHZ,%.2f,821 MHZ,%.2f,862 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 21:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1448 MHZ ,%.2f ,1496 MHZ,%.2f,1455 MHZ,%.2f,1503 MHZ,%.2f,1463 MHZ,%.2f,1511 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 25:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1930 MHZ ,%.2f ,1850 MHZ,%.2f,1950 MHZ,%.2f,1870 MHZ,%.2f,1970 MHZ,%.2f,1890 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 26:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 859 MHZ ,%.2f ,814 MHZ,%.2f,869 MHZ,%.2f,824 MHZ,%.2f,879 MHZ,%.2f,834 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;

		case 34:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2110 MHZ ,%.2f ,2110 MHZ,%.2f,2117 MHZ,%.2f,2117 MHZ,%.2f,2124 MHZ,%.2f,2124 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 38:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2570 MHZ ,%.2f ,2570 MHZ,%.2f,2595 MHZ,%.2f,2595 MHZ,%.2f,2620 MHZ,%.2f,2620 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		case 39:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1880 MHZ ,%.2f ,1880 MHZ,%.2f,1900 MHZ,%.2f,1900 MHZ,%.2f,1920 MHZ,%.2f,1920 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		case 40:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2300 MHZ ,%.2f ,2300 MHZ,%.2f,2350 MHZ,%.2f,2350 MHZ,%.2f,2400 MHZ,%.2f,2400 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;
		case 41:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2496 MHZ ,%.2f ,2450 MHZ,%.2f,2590 MHZ,%.2f,2550 MHZ,%.2f,2690 MHZ,%.2f,2650 MHZ,%.2f",vLossList[0],vLossList[0],vLossList[1],vLossList[1],vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;



		default:
			return DEVICE_WRITE_FAIL;
	}

	strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation 0.0",m_pTesterDevice->m_iChannelPort);
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:FDCorrection:ACTivate RFAC,\'mytable\',TX");
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:FDCorrection:ACTivate RFAC,\'mytable\',RX");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_CMW::IWCDMATestSetLoss(int iWCDMABand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;

	strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:DELete \'mytable\'");
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:CREate \'mytable\'");
	DEVICE_WRITE(strCmd)

		switch(iWCDMABand)
	{
		case 2100:
			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2112.6MHZ ,%.2f ,1922.6MHZ,%.2f",vLossList[0],vLossList[0]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 2140MHZ ,%.2f ,1950MHZ,%.2f",vLossList[1],vLossList[1]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1977.4MHZ ,%.2f ,2167.4MHZ,%.2f",vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 1900:
			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1854.2MHZ ,%.2f ,1931.25MHZ,%.2f",vLossList[0],vLossList[0]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1878.15MHZ ,%.2f ,1958.15MHZ,%.2f",vLossList[1],vLossList[1]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1908.75MHZ ,%.2f ,1988.75MHZ,%.2f",vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 1500:
			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1430.4MHZ ,%.2f ,1478.4MHZ,%.2f",vLossList[0],vLossList[0]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1486MHZ ,%.2f ,1438MHZ,%.2f",vLossList[1],vLossList[1]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1493.4MHZ ,%.2f ,1445.4MHZ,%.2f",vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 900:
			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 927.4MHZ ,%.2f ,882.4MHZ,%.2f",vLossList[0],vLossList[0]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 942.6MHZ ,%.2f ,897.6MHZ,%.2f",vLossList[1],vLossList[1]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 912.6MHZ ,%.2f ,957.6MHZ,%.2f",vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 850:
			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 871.4MHZ ,%.2f ,826.4MHZ,%.2f",vLossList[0],vLossList[0]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 880MHZ ,%.2f ,835MHZ,%.2f",vLossList[1],vLossList[1]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 846.6MHZ ,%.2f ,891.6MHZ,%.2f",vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;		

		default:
			return DEVICE_WRITE_FAIL;
	}

	strCmd.Format("CONF:WCDMA:MEAS:RFS:EATT 0.0");
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:FDCorrection:ACTivate RF1C, \'mytable\',RX");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:FDCorrection:ACTivate RF1C, \'mytable\',TX");
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOUR:GPRF:GEN:RFS:EATT 0.0");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::IWCDMATestMinPower(int icount,double *dMinPower)
{
	CString strCmd;
	int iDeviceErr,iQueryTimes=50;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -85;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 2;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower -55;*OPC?");
	DEVICE_QUERY(strCmd);
	Sleep(100);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd.Format("CONFigure:WCDMa:MEAS:MEValuation:SCOunt:MODulation %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:UEPower ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOUR 'GPRF Gen1: Waveform Marker 3'");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INITiate:WCDMa:MEAS:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:STATe?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("RDY"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("RDY"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:TRACe:UEPower:AVERage?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	*dMinPower=CStr::StrToFloat(strvRes[1]);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower -24;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:UEPower OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOURce 'Free Run (Fast Sync)'");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_CMW::IWCDMATestModAnalysis(const int icount,const double dTargetPower,double *dPowerValue,double dModValue[])
{
	CString strCmd;
	int iDeviceErr,iQueryTimes=50;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	memset(dModValue,0,8);
	int iRes=0;
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -85;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd.Format("CONFigure:WCDMa:MEAS:RFSettings:ENPower %.2f;*OPC?",dTargetPower);
	DEVICE_QUERY(strCmd);
	Sleep(100);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd.Format("CONFigure:WCDMa:MEAS:MEValuation:SCOunt:MODulation %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:UEPower ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:MERROR ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:PERROR ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:CDPOWER ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOUR 'GPRF Gen1: Waveform Marker 3'");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INITiate:WCDMa:MEAS:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:STATe?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("RDY"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("RDY"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:TRACe:UEPower:AVERage?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	//Power  Unit=dbm
	*dPowerValue=CStr::StrToFloat(strvRes[1]);
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:MODulation:AVERage?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	//Error Vector Magnitude  Unit=%
	dModValue[0]=CStr::StrToFloat(strvRes[1]);
	//Peak Vector Error Unit=%
	dModValue[1]=CStr::StrToFloat(strvRes[2]);
	//Phase Error Unit=deg
	dModValue[2]=CStr::StrToFloat(strvRes[5]);
	//Magnitude Error Unit=%
	dModValue[3]=CStr::StrToFloat(strvRes[3]);
	//Origin Offset Unit=dB
	dModValue[4]=CStr::StrToFloat(strvRes[7]);
	//IQ Imbalance Unit=%
	dModValue[5]=CStr::StrToFloat(strvRes[8]);
	//Timing Error Unit=chip
	dModValue[6]=CStr::StrToFloat(strvRes[10]);
	//DPCCH/DPDCH Power Ratio Unit=dB
	dModValue[7]=CStr::StrToFloat(strvRes[2]);

	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower -24;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:UEPower OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOURce 'Free Run (Fast Sync)'");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_CMW::IWCDMATestOBW(int icount,double *dOBWValue)
{

	CString strCmd;
	int iDeviceErr,iQueryTimes=50;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -75;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower 24;*OPC?");
	DEVICE_QUERY(strCmd);
	Sleep(100);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd.Format("CONFigure:WCDMa:MEAS:MEValuation:SCOunt:SPECtrum %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:ACLR ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:EMASk ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOUR 'GPRF Gen1: Waveform Marker 3'");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INITiate:WCDMa:MEAS:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:STATe?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("RDY"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("RDY"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:SPECtrum:AVERage?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	*dOBWValue=CStr::StrToFloat(strvRes[6])/1000000;
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:ACLR OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOURce 'Free Run (Fast Sync)'");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_CMW::IWCDMATestACLR(int icount,double dACLRValue[])
{
	CString strCmd;
	int iDeviceErr,iQueryTimes=50;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	double dCarrierPower=0;
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -75;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower 24;*OPC?");
	DEVICE_QUERY(strCmd);
	Sleep(100);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd.Format("CONFigure:WCDMa:MEAS:MEValuation:SCOunt:SPECtrum %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:ACLR ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOUR 'GPRF Gen1: Waveform Marker 3'");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INITiate:WCDMa:MEAS:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:STATe?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("RDY"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("RDY"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:SPECtrum:AVERage?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	dCarrierPower=CStr::StrToFloat(strvRes[1]);
	dACLRValue[0]=CStr::StrToFloat(strvRes[2])-dCarrierPower;
	dACLRValue[1]=CStr::StrToFloat(strvRes[3])-dCarrierPower;
	dACLRValue[2]=CStr::StrToFloat(strvRes[4])-dCarrierPower;
	dACLRValue[3]=CStr::StrToFloat(strvRes[5])-dCarrierPower;
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:ACLR OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOURce 'Free Run (Fast Sync)'");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_CMW::IWCDMATestSEMask(int icount,int *iSMASK)
{
	CString strCmd;
	int iDeviceErr,iQueryTimes=50;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	*iSMASK=1;
	strCmd=_T("SOURce:GPRF:GEN:RFSettings:LEVel -75;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("SOURce:GPRF:GEN:ARB:SEGMents:NEXT 1;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:RFSettings:ENPower 24;*OPC?");
	DEVICE_QUERY(strCmd);
	Sleep(100);
	strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MANual:EXECute;*OPC?");
	DEVICE_QUERY(strCmd);
	strCmd.Format("CONFigure:WCDMa:MEAS:MEValuation:SCOunt:SPECtrum %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:EMASk ON");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:LIMit:EMASk:RELative -49, -49, -39, -35, -50, -35");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOUR 'GPRF Gen1: Waveform Marker 3'");
	DEVICE_WRITE(strCmd);
	strCmd=_T("INITiate:WCDMa:MEAS:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:STATe?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("RDY"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("RDY"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("FETCh:WCDMa:MEAS:MEValuation:SPECtrum:AVERage?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strvRes);
	iRes=CStr::StrToInt(strvRes[0]);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	for (int i=7;i<15;i++)
	{
		if (CStr::StrToFloat(strvRes[i])>0)
		{
			*iSMASK=0;
		}
	}

	strCmd=_T("CONFigure:WCDMa:MEAS:MEValuation:RESult:EMASk OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("TRIGger:WCDMa:MEAS:MEValuation:SOURce 'Free Run (Fast Sync)'");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::IWCDMATestILPC(int *iResultStepE,int *iResultStepF)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_CMW::IWCDMATestBER(int iSample,double dCellPower,double *dBER)
{
	return DEVICE_SUCCESS;
}