#include "StdAfx.h"
#include "FunGSMTest_8960.h"

CFunGSMTest_8960::CFunGSMTest_8960(void)
{
}

CFunGSMTest_8960::~CFunGSMTest_8960(void)
{
}

CFunGSMTest_8960::CFunGSMTest_8960(PCTesterDevice pDev):CFuncDev_8960(pDev)
{

}

int CFunGSMTest_8960::IGSMTestSetScreen(int iScreenOFF)
{
	CString strCmd;
	int iDeviceErr;

	if (iScreenOFF)
	{
		strCmd=_T("DISPLAY:MODE FAST");
		DEVICE_WRITE(strCmd)
	}

	return DEVICE_SUCCESS;
}

int CFunGSMTest_8960::IGSMTestInitGSMtest_NSFT(const CString& strAddr,int iFreqMode,int iChan,int iPcl,int iBand)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;


	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

	strCmd=_T("*RST;*OPC?");
	DEVICE_QUERY(strCmd)
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
	strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	if (strRes.Find(_T("GSM/GPRS"))==-1)
	{
		strCmd=_T("SYSTEM:APPLICATION:FORMAT 'GSM/GPRS'");
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (strRes.Find(_T("GSM/GPRS"))==-1)
		{
			MessageBox(NULL,_T("Device fast switch GSM/GPRS fail!"),_T("WARNING"),MB_OK);
			return DEVICE_WRITE_FAIL;
		}

	}

	int i=5;
	do 
	{
		strCmd=_T("SYSTEM:PRES2;*OPC?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		Sleep(500);

	} while ((iDeviceErr!=DEVICE_SUCCESS)&&(strRes!=_T("1"))&&i-->0);

	strCmd=_T("RFGENERATOR:OUTPUT:DESTINATION IO");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:OPER:MODE OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:IATT 1");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CELL:BCCode 0");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:BURSt:TYPE TSC0");
	DEVICE_WRITE(strCmd);


	if (iFreqMode==0)//GSM
	{	
		strCmd=_T("CALL:CELL:BCHANNEL:SCELL GSM");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:OPER:MODE GBTTest");
		DEVICE_WRITE(strCmd);

		i=5;
		do 
		{
			strCmd=_T("CALL:OPER:MODE?");
			DEVICE_QUERY(strCmd)
				strRes=Device_GetReadBuf();
			Sleep(100);
		} while ((iDeviceErr!=DEVICE_SUCCESS)&&(strRes!=_T("GBTT"))&&i-->0);

		switch(iBand)
		{
		case FTM_GSM_BER_CELL_850:
			strCmd.Format("CALL:BAND GSM850");
			DEVICE_WRITE(strCmd)
				break;
		case FTM_GSM_BER_EGSM_900:
			strCmd.Format("CALL:BAND EGSM");
			DEVICE_WRITE(strCmd)
				break;
		case FTM_GSM_BER_DCS_1800:
			strCmd.Format("CALL:BINDicator DCS;*OPC?");
			DEVICE_QUERY(strCmd)
				strCmd.Format("CALL:BAND DCS");
			DEVICE_WRITE(strCmd)
				break;
		case FTM_GSM_BER_PCS_1900:
			strCmd.Format("CALL:BINDicator PCS;*OPC?");
			DEVICE_QUERY(strCmd)
				strCmd.Format("CALL:BAND PCS");
			DEVICE_WRITE(strCmd)
				break;
		}

		strCmd.Format("CALL:CELL:BCH %d",iChan);
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:TCHANNEL %d",iChan);
		DEVICE_WRITE(strCmd);

		strCmd=_T("*OPC?");
		DEVICE_QUERY_DELAY(strCmd,100);

		strCmd=_T("CALL:CELL:BA:TABLE:SELECTED");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:MS:TXLEVEL:SELECTED %d",iPcl);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:POWER -60");
		DEVICE_WRITE(strCmd);

		strCmd=_T("*OPC?");
		DEVICE_QUERY_DELAY(strCmd,100);

		strCmd=_T("CALL:TCHANNEL:DOWNLINK:SPEECH PRBS15");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:TCHANNEL:CMODE FRSPEECH");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:TCHANNEL:TSLOT 2");
		DEVICE_WRITE(strCmd);
	}
	else if (iFreqMode==1)//EDGE
	{
		strCmd=_T("CALL:CELL:BCHANNEL:SCELL EGPRS");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:OPER:MODE EBPTest");
		DEVICE_WRITE(strCmd);

		i=5;
		do 
		{
			strCmd=_T("CALL:OPER:MODE?");
			DEVICE_QUERY(strCmd)
				strRes=Device_GetReadBuf();
			Sleep(100);
		} while ((iDeviceErr!=DEVICE_SUCCESS)&&(strRes!=_T("EBPT"))&&i-->0);

		switch(iBand)
		{
		case FTM_GSM_BER_CELL_850:
			strCmd.Format("CALL:BAND GSM850");
			DEVICE_WRITE(strCmd)
				break;
		case FTM_GSM_BER_EGSM_900:
			strCmd.Format("CALL:BAND EGSM");
			DEVICE_WRITE(strCmd)
				break;
		case FTM_GSM_BER_DCS_1800:
			strCmd.Format("CALL:BINDicator DCS;*OPC?");
			DEVICE_QUERY(strCmd)
				strCmd.Format("CALL:BAND DCS");
			DEVICE_WRITE(strCmd)
				break;
		case FTM_GSM_BER_PCS_1900:
			strCmd.Format("CALL:BINDicator PCS;*OPC?");
			DEVICE_QUERY(strCmd)
				strCmd.Format("CALL:BAND PCS");
			DEVICE_WRITE(strCmd)
				break;
		}

		strCmd.Format("CALL:CELL:BCH %d",iChan);
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:TCHANNEL %d",iChan);
		DEVICE_WRITE(strCmd);

		strCmd=_T("*OPC?");
		DEVICE_QUERY_DELAY(strCmd,100);

		strCmd=_T("CALL:CELL:BA:TABLE:SELECTED");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:PDTCH:MS:TXLevel:BURS1 %d",iPcl);
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:MS:TXLEVEL:SELECTED %d",iPcl);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:POWER -60");
		DEVICE_WRITE(strCmd);

		strCmd=_T("*OPC?");
		DEVICE_QUERY_DELAY(strCmd,100);

		strCmd.Format("CALL:PDTCH %d",iChan);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:TCHANNEL:TSLOT 3");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:PDTCH:MCSCheme:EBPTest MCS5P1");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:PDTCH:MCSCheme:EBPTest:BURSt2 ASBURSt1");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:PDTCH:MCSCheme:EBPTest:BURSt3 ASBURSt1");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:PDTCH:MCSCheme:EBPTest:BURSt4 ASBURSt1");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:FUNC:CONN:TYPE SRBL");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:PDTCH:MSL:CONF D2U2");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:FUNCtion:DATA:ETSIA:PDU:COUNt 0");
		DEVICE_WRITE(strCmd);

	}
	else//ERR MODE
	{
		strRes.Format("ERR Mode=%d:1-edge,0-gsm",iFreqMode);
		MessageBox(NULL,strRes,_T("WARNNING"),MB_OK);
		return DEVICE_FINDRES_FAIL;
	}		

	return DEVICE_SUCCESS;
}

int  CFunGSMTest_8960::IGSMTestSetLoss(int iGSMBand,const DblVtr & vLossList)
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

	switch(iGSMBand)
	{
	case GSM_850_BAND_ID:
		strCmd.Format("SYST:CORR:FREQ 824.2 MHZ,862.2 MHZ, 836.6 MHZ,881.6 MHZ, 848.8 MHZ,893.8 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case GSM_EGSM_BAND_ID:
		strCmd.Format("SYST:CORR:FREQ 880.2 MHZ,925.2 MHZ, 897.6 MHZ,942.6 MHZ, 914.8 MHZ,959.8 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case GSM_DCS_BAND_ID:
		strCmd.Format("SYST:CORR:FREQ 1710.2 MHZ,1805.2 MHZ, 1747.4 MHZ,1842.4 MHZ, 1784.8 MHZ,1879.8 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case GSM_PCS_BAND_ID:
		strCmd.Format("SYST:CORR:FREQ 1850.2 MHZ,1930.2 MHZ, 1880.0 MHZ,1960.0 MHZ, 1909.8 MHZ,1989.8 MHZ");
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

int CFunGSMTest_8960::IGSMTestHandOver(int iBand,int iChannel,int iPCL,int iFreqMode,int iSlotNum)
{
	CString strCmd;
	int iDeviceErr;
	int iRtyTime=5;

	CString strRes;

	if(iFreqMode==0)
	{
		switch(iBand)
		{
		case PHONE_MODE_GSM_850:
			strCmd.Format("CALL:TCH:BAND GSM850");
			DEVICE_WRITE(strCmd)
				break;
		case PHONE_MODE_GSM_900:
			strCmd.Format("CALL:TCH:BAND EGSM");
			DEVICE_WRITE(strCmd)
				break;
		case PHONE_MODE_GSM_1800:
			strCmd.Format("CALL:BINDicator DCS;*OPC?");
			DEVICE_QUERY(strCmd)
				strCmd.Format("CALL:TCH:BAND DCS");
			DEVICE_WRITE(strCmd)
				break;
		case PHONE_MODE_GSM_1900:
			strCmd.Format("CALL:BINDicator PCS;*OPC?");
			DEVICE_QUERY(strCmd)
				strCmd.Format("CALL:TCH:BAND PCS");
			DEVICE_WRITE(strCmd)
				break;
		}

		strCmd.Format("CALL:TCH %d",iChannel);
		DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:MS:TXLEVEL:SELECTED %d",iPCL);
		DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:TCH:TSLOT %d",iSlotNum);
		DEVICE_WRITE(strCmd)

	}
	else if(iFreqMode==1)
	{
		switch(iBand)
		{
		case PHONE_MODE_GSM_850:
			strCmd.Format("CALL:PDTCH:BAND GSM850");
			DEVICE_WRITE(strCmd)
				break;
		case PHONE_MODE_GSM_900:
			strCmd.Format("CALL:PDTCH:BAND EGSM");
			DEVICE_WRITE(strCmd)
				break;
		case PHONE_MODE_GSM_1800:
			strCmd.Format("CALL:BINDicator DCS;*OPC?");
			DEVICE_QUERY(strCmd)
				strCmd.Format("CALL:PDTCH:BAND DCS");
			DEVICE_WRITE(strCmd)
				break;
		case PHONE_MODE_GSM_1900:
			strCmd.Format("CALL:BINDicator PCS;*OPC?");
			DEVICE_QUERY(strCmd)
				strCmd.Format("CALL:PDTCH:BAND PCS");
			DEVICE_WRITE(strCmd)
				break;
		}

		strCmd.Format("CALL:PDTCH %d",iChannel);
		DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:MS:TXLEVEL:SELECTED %d",iPCL);
		DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:PDTCH:MCSC:EBPT MCS5P1");
		DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:PDTCH:MCSC:EBPT:BURSt2 ASBURSt1");
		DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:PDTCH:MCSC:EBPT:BURSt3 ASBURSt1");
		DEVICE_WRITE(strCmd)
		
		strCmd.Format("CALL:PDTCH:MCSC:EBPT:BURSt4 ASBURSt1");
		DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:PDTCH:MS:TXL:BURST1 %d",iPCL);
		DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:PDTCH:MS:TXL:BURST2 %d",iPCL);
		DEVICE_WRITE(strCmd)
	}

	strCmd.Format("*OPC?");
	DEVICE_QUERY_DELAY(strCmd,200);

	strCmd.Format("CALL:CELL:POW:STAT ON");
	DEVICE_WRITE(strCmd);

	return DEVICE_SUCCESS;
}

int CFunGSMTest_8960::IGSMTestStartTxMeasurment(int BurstQty,int loopi,CStringVtr &strRes,CString strTestItem,int iEdge)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	int iTryTimes=50;
	CString strtemp;
	CStringVtr strVtrtemp;
	strtemp.Empty();
	strVtrtemp.clear();

	if (iEdge==0)
	{
		strCmd.Format("SETUP:PFERROR:COUNT:SNUM %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:PVTIME:COUNT:SNUM %d",BurstQty);
		DEVICE_WRITE(strCmd);

		//strCmd.Format("SETup:ORFSpectrum:FILTer:TYPe AUTO");
		//DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:ORFSPECTRUM:SWITCHING:COUNT:SNUM %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:ORFSPECTRUM:SWITCHING:FREQ:OFFSET -1800 KHZ, -1200 KHZ, -600 KHZ, -400 KHZ, 400 KHZ, 600KHZ, 1200 KHZ, 1800 KHZ");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:ORFSPECTRUM:MODULATION:COUNT:SNUM %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:ORFSPECTRUM:MODULATION:FREQ:OFFSET -1000KHZ, -600 KHZ, -400 KHZ, -250 KHZ, -200 KHZ, -100 KHZ, 100 KHZ, 200 KHZ, 250 KHZ,400 KHZ, 600KHZ, 1000 KHZ");
		DEVICE_WRITE(strCmd);

		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);		

		strCmd=_T("SETUP:ALL:CONTINUOUS:OFF");
		DEVICE_WRITE(strCmd);

		strCmd=_T("INIT:ORFS;PFER;PVT:ON");
		DEVICE_WRITE(strCmd);

		 
		do 
		{
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			Sleep(50);
			if (iTryTimes==0)
			{
				return DEVICE_QUERY_FAIL;
			}		
		}while( strReadBuf.Find("NONE")==-1 && iTryTimes-->0);

		if (strTestItem.Find("A1")!=-1)
		{
			strVtrtemp.clear();
			strCmd=_T("FETCH:PVT:ALL?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			CStr::ParseString(strReadBuf,_T(","),strVtrtemp);
			if (strVtrtemp[0].Find(_T("0"))==-1)
			{
				return DEVICE_QUERY_FAIL;
			}
			strRes.push_back(strVtrtemp[2]);
		}

		if ((strTestItem.Find("B1")!=-1)||(strTestItem.Find("C1")!=-1)||(strTestItem.Find("D1")!=-1))
		{
			strVtrtemp.clear();
			strCmd=_T("FETCH:PFER?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			CStr::ParseString(strReadBuf,_T(","),strVtrtemp);

			if (strVtrtemp[0].Find(_T("0"))==-1)
			{
				return DEVICE_QUERY_FAIL;
			}

			if(strTestItem.Find("B1")!=-1)
			{
				//MAX_PPHASEERR?");				
				strRes.push_back(strVtrtemp[2]);
			}

			if (strTestItem.Find("C1")!=-1)
			{
				//AVG_PHASEERR?");
				strRes.push_back(strVtrtemp[1]);
			}

			if (strTestItem.Find("D1")!=-1)
			{
				//AVG_CARRFERR? HZ");
				strRes.push_back(strVtrtemp[3]);
			}
		}

		if (strTestItem.Find("E1")!=-1)
		{
			strVtrtemp.clear();
			strCmd=_T("FETCH:PVTIME:MASK:FAIL?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");

			strRes.push_back(strReadBuf);
		}

		if ((strTestItem.Find("F1")!=-1)||(strTestItem.Find("G1")!=-1)||(strTestItem.Find("H1")!=-1)||(strTestItem.Find("I1")!=-1))
		{
			strVtrtemp.clear();
			strCmd=_T("FETC:ORFS:ALL?");
			DEVICE_QUERY_DELAY(strCmd,300);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			CStr::ParseString(strReadBuf,_T(","),strVtrtemp);
			if (strVtrtemp[0].Find(_T("0"))==-1)
			{
				return DEVICE_QUERY_FAIL;
			}

			if (strTestItem.Find("F1")!=-1)
			{
				Sleep(200);
				strCmd=_T("FETCh:ORFSpectrum:SWITChing:LIMit?");
				DEVICE_QUERY_DELAY(strCmd,300);
				strReadBuf=Device_GetReadBuf();
				strRes.push_back(strReadBuf);
			}

			if (strTestItem.Find("G1")!=-1)
			{
				strReadBuf.Empty();
				for(int i=0;i<8;i++)
				{
					strReadBuf+=strVtrtemp[i+2]+',';
				}

				strRes.push_back(strReadBuf);
			}

			if (strTestItem.Find("H1")!=-1)
			{
				strCmd=_T("FETCh:ORFSpectrum:MOD:LIMit?");
				DEVICE_QUERY(strCmd);
				strReadBuf=Device_GetReadBuf();
				strRes.push_back(strReadBuf);
			}

			if (strTestItem.Find("I1")!=-1)
			{
				CString strTemp;
				double dPower30kHz,dLOF1000,dUOF1000,dLOF600,dUOF600,dLOF400,dUOF400,dLOF250,dUOF250,dLOF200,dUOF200,dLOF100,dUOF100;
				strReadBuf.Empty();
				strTemp.Empty();
				for(int i=0;i<13;i++)
				{
					strTemp+=strVtrtemp[i+10]+',';
				}
				strVtrtemp.clear();
				CStr::ParseString(strTemp,_T(","),strVtrtemp);

				//AVG_LMODPWR? OF0");
				dPower30kHz=CStr::StrToFloat(strVtrtemp[0]);

				strTemp.Empty();
				//AVG_LMODPWR? OF1000");
				dLOF1000=CStr::StrToFloat(strVtrtemp[1]);
				if (loopi==2)
				{
					dLOF1000+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dLOF1000);
				strReadBuf+=strTemp+',';

				//AVG_LMODPWR? OF600");
				strTemp.Empty();
				dLOF600=CStr::StrToFloat(strVtrtemp[2]);
				if (loopi==2)
				{
					dLOF600+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dLOF600);
				strReadBuf+=strTemp+',';

				//AVG_LMODPWR? OF400");
				strTemp.Empty();
				dLOF400=CStr::StrToFloat(strVtrtemp[3]);
				if (loopi==2)
				{
					dLOF400+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dLOF400);
				strReadBuf+=strTemp+',';

				//AVG_LMODPWR? OF250");
				strTemp.Empty();
				dLOF250=CStr::StrToFloat(strVtrtemp[4]);
				if (loopi==2)
				{
					//dLOF250+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dLOF250);
				strReadBuf+=strTemp+',';

				//AVG_LMODPWR? OF200");
				strTemp.Empty();
				dLOF200=CStr::StrToFloat(strVtrtemp[5]);
				if (loopi==2)
				{
					//dLOF200+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dLOF200);
				strReadBuf+=strTemp+',';
				

				//AVG_LMODPWR? OF100");
				strTemp.Empty();
				dLOF100=CStr::StrToFloat(strVtrtemp[6]);
				if (loopi==2)
				{
					//dLOF100+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dLOF100);
				strReadBuf+=strTemp+',';

				//AVG_UMODPWR? OF100");
				strTemp.Empty();
				dUOF100=CStr::StrToFloat(strVtrtemp[7]);
				if (loopi==2)
				{
					//dUOF100+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dUOF100);
				strReadBuf+=strTemp+',';

				//AVG_UMODPWR? OF200");
				strTemp.Empty();
				dUOF200=CStr::StrToFloat(strVtrtemp[8]);
				if (loopi==2)
				{
					//dUOF200+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dUOF200);
				strReadBuf+=strTemp+',';

				//AVG_UMODPWR? OF250");
				strTemp.Empty();
				dUOF250=CStr::StrToFloat(strVtrtemp[9]);
				if (loopi==2)
				{
					//dUOF250+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dUOF250);
				strReadBuf+=strTemp+',';

				//AVG_UMODPWR? OF400");
				strTemp.Empty();
				dUOF400=CStr::StrToFloat(strVtrtemp[10]);
				if (loopi==2)
				{
					dUOF400+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dUOF400);
				strReadBuf+=strTemp+',';

				//AVG_UMODPWR? OF600");
				strTemp.Empty();
				dUOF600=CStr::StrToFloat(strVtrtemp[11]);
				if (loopi==2)
				{
					dUOF600+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dUOF600);
				strReadBuf+=strTemp+',';

				//AVG_UMODPWR? OF1000");
				strTemp.Empty();
				dUOF1000=CStr::StrToFloat(strVtrtemp[12]);
				if (loopi==2)
				{
					dUOF1000+=dPower30kHz;
				}
				strTemp=CStr::FloatToStr(dUOF1000);
				strReadBuf+=strTemp;

				strRes.push_back(strReadBuf);
			}		
		}
	}
	else if (iEdge==1)
	{
		strCmd.Format("SETUP:EMAC:COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:PVTIME:COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETup:ORFSpectrum:FILTer:TYPe AUTO");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:ORFSPECTRUM:SWITCHING:COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:ORFSPECTRUM:SWITCHING:FREQ:OFFSET -1800 KHZ, -1200 KHZ, -600 KHZ, -400 KHZ, 400 KHZ, 600KHZ, 1200 KHZ, 1800 KHZ",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:ORFSPECTRUM:MODULATION:COUNT %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:ORFSPECTRUM:MODULATION:FREQ:OFFSET -1000KHZ, -600 KHZ, -400 KHZ, -250 KHZ, -200 KHZ, -100 KHZ, 100 KHZ, 200 KHZ, 250 KHZ,400 KHZ, 600KHZ, 1000 KHZ",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:ALL:CONTINUOUS:OFF");
		DEVICE_WRITE(strCmd);

		strCmd=_T("INIT:ORFS;EMAC;PVT:ON");
		DEVICE_WRITE(strCmd);

		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);

		Sleep(1000); 
		do 
		{
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			Sleep(100);
			if (iTryTimes==0)
			{
				return DEVICE_QUERY_FAIL;
			}		
		}while( strReadBuf.Find("NONE")==-1 && iTryTimes-->0);

		if (strTestItem.Find("A1")!=-1)
		{
			strVtrtemp.clear();
			strCmd=_T("FETCH:PVT:ALL?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			CStr::ParseString(strReadBuf,_T(","),strVtrtemp);
			if (strVtrtemp[0].Find(_T("0"))==-1)
			{
				return DEVICE_QUERY_FAIL;
			}
			strRes.push_back(strVtrtemp[2]);
		}		

		if ((strTestItem.Find("B1")!=-1)||(strTestItem.Find("C1")!=-1)||(strTestItem.Find("D1")!=-1)||(strTestItem.Find("E1")!=-1)||(strTestItem.Find("F1")!=-1))
		{
			strVtrtemp.clear();
			strCmd=_T("FETC:EMAC:ALL?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			CStr::ParseString(strReadBuf,_T(","),strVtrtemp);
			if (strVtrtemp[0].Find(_T("0"))==-1)
			{
				return DEVICE_QUERY_FAIL;
			}

			if (strTestItem.Find("B1")!=-1)
			{
				//_T("MAX_PEVM?");
				strRes.push_back(strVtrtemp[2]);
			}

			if (strTestItem.Find("C1")!=-1)
			{
				//_T("AVG_EVM?");
				strRes.push_back(strVtrtemp[1]);
			}

			if (strTestItem.Find("D1")!=-1)
			{
				//_T("EVM95PCT?");
				strRes.push_back(strVtrtemp[3]);
			}

			if (strTestItem.Find("E1")!=-1)
			{
				//=_T("AVG_ORGNOFS?");
				strRes.push_back(strVtrtemp[5]);
			}

			if (strTestItem.Find("F1")!=-1)
			{
				//_T("AVG_CARRFERR? HZ");
				strRes.push_back(strVtrtemp[4]);
			}
		}

		if (strTestItem.Find("G1")!=-1)
		{
			strVtrtemp.clear();
			strCmd=_T("FETC:PVT:ALL?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			CStr::ParseString(strReadBuf,_T(","),strVtrtemp);
			if (strVtrtemp[0].Find(_T("0"))==-1)
			{
				return DEVICE_QUERY_FAIL;
			}
			strRes.push_back(strVtrtemp[1]);
			//_T("AVG_PWRTEMP?");
		}

		if ((strTestItem.Find("H1")!=-1)||(strTestItem.Find("I1")!=-1)||(strTestItem.Find("J1")!=-1)||(strTestItem.Find("K1")!=-1))
		{
			strVtrtemp.clear();
			strCmd=_T("FETC:ORFS:ALL?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			strReadBuf.Replace("\r","");
			strReadBuf.Replace("\n","");
			CStr::ParseString(strReadBuf,_T(","),strVtrtemp);
			if (strVtrtemp[0].Find(_T("0"))==-1)
			{
				return DEVICE_QUERY_FAIL;
			}

			if (strTestItem.Find("H1")!=-1)
			{
				//_T("ORFSSW_JUDGE?");
				strCmd=_T("FETCh:ORFSpectrum:SWIT:LIMit?");
				DEVICE_QUERY(strCmd);
				strReadBuf=Device_GetReadBuf();
				strRes.push_back(strReadBuf);
			}

			if (strTestItem.Find("I1")!=-1)
			{
				strReadBuf.Empty();

				//_T("AVG_LSWPWR? OF1800");
				strReadBuf+=strVtrtemp[2]+',';

				//_T("AVG_LSWPWR? OF1200");
				strReadBuf+=strVtrtemp[3]+',';

				//_T("AVG_LSWPWR? OF600");
				strReadBuf+=strVtrtemp[4]+',';

				//_T("AVG_LSWPWR? OF400");
				strReadBuf+=strVtrtemp[5]+',';

				//_T("AVG_USWPWR? OF400");
				strReadBuf+=strVtrtemp[6]+',';

				//_T("AVG_USWPWR? OF600");
				strReadBuf+=strVtrtemp[7]+',';

				//_T("AVG_USWPWR? OF1200");
				strReadBuf+=strVtrtemp[8]+',';

				//_T("AVG_USWPWR? OF1800");
				strReadBuf+=strVtrtemp[9];

				strRes.push_back(strReadBuf);
			}

			if (strTestItem.Find("J1")!=-1)
			{
				//_T("ORFSMD_JUDGE?");
				strCmd=_T("FETCh:ORFSpectrum:MOD:LIMit?");
				DEVICE_QUERY(strCmd);
				strReadBuf=Device_GetReadBuf();
				strRes.push_back(strReadBuf);
			}

			if (strTestItem.Find("K1")!=-1)
			{
				CString strTemp;
				double dPower30kHz,dLOF400,dUOF400;
				strReadBuf.Empty();

				//_T("AVG_LMODPWR? OF0");
				strTemp.Empty();
				dPower30kHz=CStr::StrToFloat(strVtrtemp[10]);
				//strReadBuf+=strTemp+',';

				//_T("AVG_LMODPWR? OF1000");
				strReadBuf+=strVtrtemp[11]+',';

				//_T("AVG_LMODPWR? OF400");
				strTemp.Empty();
				strTemp=Device_GetReadBuf();
				dLOF400=CStr::StrToFloat(strVtrtemp[13])+dPower30kHz;
				strTemp=CStr::FloatToStr(dLOF400);
				strReadBuf+=strTemp+',';

				//_T("AVG_LMODPWR? OF250");
				DEVICE_QUERY(strCmd);
				strReadBuf+=strVtrtemp[14]+',';

				//_T("AVG_LMODPWR? OF200");
				strReadBuf+=strVtrtemp[15]+',';

				//_T("AVG_UMODPWR? OF200");
				strReadBuf+=strVtrtemp[18]+',';

				//_T("AVG_UMODPWR? OF250");
				strReadBuf+=strVtrtemp[19]+',';

				//_T("AVG_UMODPWR? OF400");
				strTemp.Empty();
				dUOF400=CStr::StrToFloat(strVtrtemp[20])+dPower30kHz;
				strTemp=CStr::FloatToStr(dUOF400);
				strReadBuf+=strTemp+',';

				//_T("AVG_UMODPWR? OF1000");
				strReadBuf+=strVtrtemp[22];

				strRes.push_back(strReadBuf);
			}
		}




	}


	//MessageBox(NULL,strReadBuf,"123",MB_OK);

	return DEVICE_SUCCESS;
}
int CFunGSMTest_8960::IGSMTestStartRxLevelMeasurment(double dCellpower)
{
	 CString strReadBuf;
	 CString strCmd;
	 int iRet=0;
	 int iDeviceErr;

	 strCmd.Format("CALL:POW %f;*OPC?",dCellpower);
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
int CFunGSMTest_8960::IGSMTestStartRxBerMeasurment(int BurstQty,double dCellpower,double &dSebr,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iRet=0,iTryTimes=10;
	int iDeviceErr;
	if (strTestItem.Find("X1")!=-1)
	{
		strCmd.Format("SETUP:FBERROR:CLSDELAY:STIME 500 MS");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:FBERROR:SLCONTROL ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:FBERROR:LDCONTROL:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:FBERROR:MANUAL:DELAY 1");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:FBERROR:COUNT %d", BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:POW %f",dCellpower);
		DEVICE_WRITE(strCmd);

		strCmd.Format("INIT:FBER:ON");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			Sleep(100);
			if (iTryTimes==0)
			{
				return DEVICE_QUERY_FAIL;
			}		
		}while( strReadBuf.Find("FBER")==-1 && iTryTimes-->0);

		strCmd=_T("FETCh:FBERROR:RATIO?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		
		dSebr=CStr::StrToFloat(strReadBuf);
	}

	return DEVICE_SUCCESS;
}

