#include "StdAfx.h"
#include "FunGSMTest_CMW.h"

CFunGSMTest_CMW::CFunGSMTest_CMW(void)
{
}

CFunGSMTest_CMW::~CFunGSMTest_CMW(void)
{
}
CFunGSMTest_CMW::CFunGSMTest_CMW(PCTesterDevice pDev):CFuncDev_CMW(pDev)
{

}
int CFunGSMTest_CMW::IGSMTestInitGSMtest_NSFT(const CString& strAddr,int iFreqMode,int iChan,int iPcl,int iBand)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;
	double DLFreq=0;
	double ULFreq=0;
	double ExpectPower=0;


	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

	strCmd=_T("SYSTEM:RESET \"GSM Sig\";*OPC?");
	DEVICE_QUERY(strCmd)

		strCmd=_T("ROUTe:GPRF:GENerator:SCENario:SALone RFAC, TX1;*OPC?");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ROUTe:GSM:MEASurement:SCENario:SALone RFAC, RX1;*OPC?");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SYSTem:BASE:REFerence:FREQuency:SOURce INTernal;*OPC?");
	DEVICE_WRITE(strCmd)
		//GPRF GEN setup
		strCmd=_T("SOURCe:GPRF:GEN:STAT OFF;*OPC?");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ABORT:GSM:MEAS:MEValuation");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SOURce:GPRF:GEN:BBMode ARB");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SOURce:GPRF:GEN:ARB:FILE \'D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\library1\\loopC_1040.wv\'");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SOURce:GPRF:GEN:ARB:FILE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	if (-1==strRes.Find("loopC"))
	{
		MessageBox(NULL,_T("waveform open failed"),_T("WARNING"),MB_OK);
		return DEVICE_WRITE_FAIL;
	}
		strCmd=_T("SOURce:GPRF:GEN:ARB:REPetition CONTinuous");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TRIGger:GPRF:GEN:ARB:RETRigger ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TRIGger:GPRF:GEN:ARB:AUTostart ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TRIGger:GPRF:GEN:ARB:SEGMents:MODE CSEamless");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SOURce:GPRF:GEN:LIST OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SOURce:GPRF:GEN:STATe ON;*OPC?");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SOURce:GPRF:GEN:STATe?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	if (-1==strRes.Find("ON"))
	{
		MessageBox(NULL,_T("GPRF ON failed"),_T("WARNING"),MB_OK);
		return DEVICE_WRITE_FAIL;
	}
	//meas setup
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:TSEQuence TSC0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:PCLMode PCL");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:PCL 5,5,5,5,5,5,5,5");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:RFSettings:UMARgin 5;*OPC?");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:RFSettings:ENPower 33;*OPC?");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SOURce:GPRF:GENerator:RFSettings:LEVel -60;*OPC?");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ABORt:GSM:MEAS:MEValuation");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:RESult:ALL OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:TOUT 10");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:REPetition SINGleshot");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:MOEXception OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:FCRange WIDE");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:HDALevel -50");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:NBQSearch OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:ABSearch OFF");
	DEVICE_WRITE(strCmd)

		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:VAMos:TSCSet 1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:LIST OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:RPMode AVERage");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:FILTer:PVTime G05M");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:MODulation:DECode GTBits");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:MVIew GMSK,OFF,OFF,OFF,OFF,OFF,OFF,OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONFigure:GSM:MEAS:MEValuation:MSLots 0,1,0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TRIGger:GSM:MEAS:MEValuation:SOURce 'POWER'");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TRIGger:GSM:MEAS:MEValuation:SLOPe REDGe");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TRIGger:GSM:MEAS:MEValuation:THReshold -20");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TRIGger:GSM:MEAS:MEValuation:TOUT 5");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TRIGger:GSM:MEAS:MEValuation:MGAP 0");
	DEVICE_WRITE(strCmd)
	

	if (iBand==FTM_GSM_BER_PCS_1900)
	{
		DLFreq=CGSMBandInfo::ArfcnToRXHz(GSM_PCS_BAND_ID,iChan);
		ULFreq=CGSMBandInfo::ArfcnToTXHz(GSM_PCS_BAND_ID,iChan);
		ExpectPower= 30.0- 2*iPcl;
	}
	else if(iBand==FTM_GSM_BER_DCS_1800)
	{
		DLFreq=CGSMBandInfo::ArfcnToRXHz(GSM_DCS_BAND_ID,iChan);
		ULFreq=CGSMBandInfo::ArfcnToTXHz(GSM_DCS_BAND_ID,iChan);
		ExpectPower= 30.0- 2*iPcl;
	}
	else if (iBand==FTM_GSM_BER_CELL_850)
	{
		DLFreq=CGSMBandInfo::ArfcnToRXHz(GSM_850_BAND_ID,iChan);
		ULFreq=CGSMBandInfo::ArfcnToTXHz(GSM_850_BAND_ID,iChan);
		ExpectPower= 43.0- 2*iPcl;
	}
	else if (iBand == FTM_GSM_BER_EGSM_900)
	{
		DLFreq=CGSMBandInfo::ArfcnToRXHz(GSM_EGSM_BAND_ID,iChan);
		ULFreq=CGSMBandInfo::ArfcnToTXHz(GSM_EGSM_BAND_ID,iChan);
		ExpectPower= 43.0- 2*iPcl;
	}
	else
	{
		return DEVICE_WRITE_FAIL;
	}
	strCmd.Format("SOURce:GPRF:GENerator:RFSettings:LEVel -60;*OPC?");
	DEVICE_QUERY(strCmd)
		strCmd.Format("SOURce:GPRF:GENerator:RFSettings:FREQuency %.2fMHz;*OPC?",DLFreq);
	DEVICE_QUERY(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:RFSettings:FREQuency %.2f MHz;*OPC?",ULFreq);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:PCLMode PCL");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:PCL %d,%d,%d,%d,%d,%d,%d,%d",iPcl,iPcl,iPcl,iPcl,iPcl,iPcl,iPcl,iPcl);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:RFSettings:UMARgin 5;*OPC?");
	DEVICE_QUERY(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:RFSettings:ENPower %.2f;*OPC?",ExpectPower);
	DEVICE_QUERY(strCmd)
		strCmd.Format("SOURce:GPRF:GEN:STATe?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	if (-1<strRes.Find("ON"))
	{
		return DEVICE_SUCCESS;
	}

		return DEVICE_SUCCESS;
}
int CFunGSMTest_CMW::IGSMTestSetLoss(int iGSMBand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;

	strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:DELete \'mytable\'");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:CREate \'mytable\'");
	DEVICE_WRITE(strCmd)



		switch(iGSMBand)
	{
		case 850:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 824.2 MHZ ,%.2f ,836.6 MHZ,%.2f,848.8 MHZ,%.2f",vLossList[0],vLossList[1],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 900:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 880.2 MHZ ,%.2f ,902.4 MHZ,%.2f,914.8 MHZ,%.2f",vLossList[0],vLossList[1],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		case 1800:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1710.2 MHZ ,%.2f ,1747.4 MHZ,%.2f,1784.8 MHZ,%.2f",vLossList[0],vLossList[1],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		case 1900:

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1850.2 MHZ ,%.2f ,1880 MHZ,%.2f,1909.8 MHZ,%.2f",vLossList[0],vLossList[1],vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		default:
			return DEVICE_WRITE_FAIL;
	}

	strCmd.Format("CONFigure:GPRF:MEAS%d:RFSettings:EATTenuation 0.0");
	DEVICE_WRITE(strCmd)

		strCmd.Format("SOURce:GPRF:GEN%d:RFSettings:EATTenuation 0.0");
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:FDCorrection:ACTivate RFAC,\'mytable\',TX");
	DEVICE_WRITE(strCmd)

		strCmd.Format("CONFigure:FDCorrection:ACTivate RFAC,\'mytable\',RX");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;
	return DEVICE_SUCCESS;
}
int CFunGSMTest_CMW::IGSMTestSetScreen(int iScreenOFF)
{
	return DEVICE_SUCCESS;
}
int CFunGSMTest_CMW::IGSMTestHandOver(int iBand,int iChannel,int iPCL,int iFreqMode/* =0 */,int iSlotNum/* =2 */)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;
	double DLFreq=0;
	double ULFreq=0;
	double ExpectPower=0;

	if (0==iFreqMode)
	{
		if (iBand==PHONE_MODE_GSM_1900)
		{
			DLFreq=CGSMBandInfo::ArfcnToRXHz(GSM_PCS_BAND_ID,iChannel);
			ULFreq=CGSMBandInfo::ArfcnToTXHz(GSM_PCS_BAND_ID,iChannel);
			ExpectPower= 30.0- 2*iPCL;
		}
		else if(iBand==PHONE_MODE_GSM_1800)
		{
			DLFreq=CGSMBandInfo::ArfcnToRXHz(GSM_DCS_BAND_ID,iChannel);
			ULFreq=CGSMBandInfo::ArfcnToTXHz(GSM_DCS_BAND_ID,iChannel);
			ExpectPower= 30.0- 2*iPCL;
		}
		else if (iBand==PHONE_MODE_GSM_850)
		{
			DLFreq=CGSMBandInfo::ArfcnToRXHz(GSM_850_BAND_ID,iChannel);
			ULFreq=CGSMBandInfo::ArfcnToTXHz(GSM_850_BAND_ID,iChannel);
			ExpectPower= 43.0- 2*iPCL;
		}
		else if (iBand == PHONE_MODE_GSM_900)
		{
			DLFreq=CGSMBandInfo::ArfcnToRXHz(GSM_EGSM_BAND_ID,iChannel);
			ULFreq=CGSMBandInfo::ArfcnToTXHz(GSM_EGSM_BAND_ID,iChannel);
			ExpectPower= 43.0- 2*iPCL;
		}
		else
		{
			return DEVICE_WRITE_FAIL;
		}
		strCmd.Format("SOURce:GPRF:GENerator:RFSettings:LEVel -60;*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd.Format("SOURce:GPRF:GENerator:RFSettings:FREQuency %.2fMHz;*OPC?",DLFreq);
		DEVICE_QUERY(strCmd)
			strCmd.Format("CONFigure:GSM:MEAS:RFSettings:FREQuency %.2f MHz;*OPC?",ULFreq);
		DEVICE_WRITE(strCmd)
			strCmd.Format("CONFigure:GSM:MEAS:MEValuation:PCLMode PCL");
		DEVICE_WRITE(strCmd)
			strCmd.Format("CONFigure:GSM:MEAS:MEValuation:MSLots 0,%d,0",iSlotNum);
		DEVICE_WRITE(strCmd)
			strCmd.Format("CONFigure:GSM:MEAS:MEValuation:PCL %d,%d,%d,%d,%d,%d,%d,%d",iPCL,iPCL,iPCL,iPCL,iPCL,iPCL,iPCL,iPCL);
		DEVICE_WRITE(strCmd)
			strCmd.Format("CONFigure:GSM:MEAS:RFSettings:UMARgin 5;*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd.Format("CONFigure:GSM:MEAS:RFSettings:ENPower %.2f;*OPC?",ExpectPower);
		DEVICE_QUERY(strCmd)
			strCmd.Format("SOURce:GPRF:GEN:STATe?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (-1<strRes.Find("ON"))
		{
			return DEVICE_SUCCESS;
		}

	}

	return DEVICE_WRITE_FAIL;
}
int CFunGSMTest_CMW::IGSMTestStartTxMeasurment(int BurstQty,int loopi,CStringVtr &strResult,CString strTestItem,int iEdge)
{
	CString strCmd;
	int iDeviceErr,iQueryTimes=50;
	CString strRes;
	CStringVtr strvRes;
	DblVtr dvStr;
	int iRes=0;
	CString strtemp;
	CStringVtr strVtrtemp;
	strtemp.Empty();
	strVtrtemp.clear();

	strCmd.Format("CONFigure:GSM:MEAS:MEValuation:RESult:PERRor ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:RESult:EVM ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:RESult:MERRor ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:SCOunt:MODulation %d",BurstQty);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:RESult:PVTime ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:SCOunt:PVTime %d",BurstQty);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:RESult:MSCalar ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:SCOunt:MODulation %d",BurstQty);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:RESult:SSFRequency ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:SCOunt:SSWitching %d",BurstQty);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:SSWitching:OFRequence 0.4e+6,0.6e+6,1.2e+6,1.8e+6,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:RESult:SMFRequency ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:SCOunt:SMODulation %d",BurstQty);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:SMODulation:OFRequence 0.1e+6,0.2e+6,0.25e+6,0.4e+6,0.6e+6,1e+6,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF");
	DEVICE_WRITE(strCmd)

		strCmd=_T("INITiate:GSM:MEAS:MEValuation");
	DEVICE_WRITE(strCmd);
	strCmd=_T("FETCh:GSM:MEAS:MEValuation:STATe?");
	do
	{
		Sleep(50);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("RDY"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("RDY"))
	{
		return DEVICE_FINDRES_FAIL;
	}

	if (strTestItem.Find("A1")!=-1)
	{
		strVtrtemp.clear();
		strCmd=_T("FETCh:GSM:MEAS:MEValuation:PVTime:ALL?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		strRes.Replace("\r","");
		strRes.Replace("\n","");
		CStr::ParseString(strRes,_T(","),strVtrtemp);
		if (strVtrtemp[2].Find(_T("NCAP"))>-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strResult.push_back(strVtrtemp[2]);
	}
	if ((strTestItem.Find("B1")!=-1)||(strTestItem.Find("C1")!=-1)||(strTestItem.Find("D1")!=-1))
	{
		strVtrtemp.clear();
		strCmd=_T("FETCh:GSM:MEAS:MEValuation:MODulation:MAXimum?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		strRes.Replace("\r","");
		strRes.Replace("\n","");
		CStr::ParseString(strRes,_T(","),strVtrtemp);

		if(strTestItem.Find("B1")!=-1)
		{
			//MAX_PPHASEERR?");				
			strResult.push_back(strVtrtemp[7]);
		}
		
		strVtrtemp.clear();
		strCmd=_T("FETCh:GSM:MEAS:MEValuation:MODulation:AVERage?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		strRes.Replace("\r","");
		strRes.Replace("\n","");
		CStr::ParseString(strRes,_T(","),strVtrtemp);

		if (strTestItem.Find("C1")!=-1)
		{
			//AVG_PHASEERR?");
			strResult.push_back(strVtrtemp[6]);
		}
		if (strTestItem.Find("D1")!=-1)
		{
			//AVG_CARRFERR? HZ");
			strResult.push_back(strVtrtemp[10]);
		}

		
	}
	if (strTestItem.Find("E1")!=-1)
	{
		strVtrtemp.clear();
		strCmd=_T("FETCh:GSM:MEAS:MEValuation:PVTime:ALL?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		strRes.Replace("\r","");
		strRes.Replace("\n","");
		CStr::ParseString(strRes,_T(","),strVtrtemp);
		if (strVtrtemp[1].Find(_T("NCAP"))>-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		double dOutTol=CStr::StrToFloat(strVtrtemp[1]);
		if(dOutTol>0)
		{strResult.push_back("FAIL");

		}
		else{strResult.push_back("PASS");}
		
	}
	if (strTestItem.Find("F1")!=-1)
	{		
		strCmd=_T("FETCh:GSM:MEAS:MEValuation:SSWitching?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,_T(","),strVtrtemp);
		if (strVtrtemp[1].Find(_T("NCAP"))>-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		double dOutTol=CStr::StrToFloat(strVtrtemp[1]);
		if(dOutTol>0)
		{strResult.push_back("FAIL");

		}
		else{strResult.push_back("PASS");}
	}

	if (strTestItem.Find("G1")!=-1)
	{
		strtemp.Empty();

		strCmd=_T("FETCh:GSM:MEAS:MEValuation:SSWitching:FREQuency?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,",",strVtrtemp);
		strtemp=strVtrtemp[17]+","+strVtrtemp[18]+","+strVtrtemp[19]+","+strVtrtemp[20]+","+strVtrtemp[22]+","+strVtrtemp[23]+","+strVtrtemp[24]+","+strVtrtemp[25];
		strResult.push_back(strtemp);
	}
	if (strTestItem.Find("H1")!=-1)
	{		
		strCmd=_T("FETCh:GSM:MEAS:MEValuation:SMODulation?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,_T(","),strVtrtemp);
		if (strVtrtemp[1].Find(_T("NCAP"))>-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		double dOutTol=CStr::StrToFloat(strVtrtemp[1]);
		if(dOutTol>0)
		{strResult.push_back("FAIL");

		}
		else{strResult.push_back("PASS");}
	}

	if (strTestItem.Find("I1")!=-1)
	{
		strtemp.Empty();

		strCmd=_T("FETCh:GSM:MEAS:MEValuation:SMODulation:FREQuency?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,",",strVtrtemp);
		strtemp=strVtrtemp[15]+","+strVtrtemp[16]+","+strVtrtemp[17]+","+strVtrtemp[18]+","+strVtrtemp[19]+","+strVtrtemp[20]+","+strVtrtemp[22]+","+strVtrtemp[23]+","+strVtrtemp[24]+","+strVtrtemp[25]+","+strVtrtemp[26]+","+strVtrtemp[27];
		strResult.push_back(strtemp);
	}
	

	return DEVICE_SUCCESS;
}
int CFunGSMTest_CMW::IGSMTestStartRxLevelMeasurment(double dCellpower)
{
	CString strReadBuf;
	CString strCmd;
	int iRet=0;
	int iDeviceErr;

	strCmd.Format("SOURce:GPRF:GENerator:RFSettings:LEVel %.2f;*OPC?",dCellpower);
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
int CFunGSMTest_CMW::IGSMTestStartRxBerMeasurment(int BurstQty,double dCellpower,double &dSebr,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	CStringVtr strVtr;
	int iRet=0,iTryTimes=30;
	int iDeviceErr;
	if (strTestItem.Find("X1")!=-1)
	{
		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:RESult:BER ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:BER:TST 30");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:BER:TRUN 30");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONFigure:GSM:MEAS:MEValuation:SCOunt:BER %d", BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("SOURce:GPRF:GENerator:RFSettings:LEVel %f;*OPC?",dCellpower);
		DEVICE_WRITE(strCmd);

		Sleep(200);

		strCmd=_T("INITiate:GSM:MEAS:MEValuation");
		DEVICE_WRITE(strCmd);
		strCmd=_T("FETCh:GSM:MEAS:MEValuation:STATe?");
		do
		{
			Sleep(150);
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();

		}while((0!=strReadBuf.Find("RDY"))&&(0<iTryTimes--));
		if (0!=strReadBuf.Find("RDY"))
		{
			return DEVICE_FINDRES_FAIL;
		}


		strCmd=_T("FETCh:GSM:MEAS:MEValuation:BER?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		CStr::ParseString(strReadBuf,",",strVtr);

		dSebr=CStr::StrToFloat(strVtr[1]);
	}

	return DEVICE_SUCCESS;
}