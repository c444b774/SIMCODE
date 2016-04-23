#include "StdAfx.h"
#include "FuncCDMATest_CMW.h"

CFuncCDMATest_CMW::CFuncCDMATest_CMW(void)
{
}

CFuncCDMATest_CMW::~CFuncCDMATest_CMW(void)
{
}
CFuncCDMATest_CMW::CFuncCDMATest_CMW(PCTesterDevice pDev):CFuncDev_CMW(pDev)
{

}

int CFuncCDMATest_CMW::ICDMATestInitCDMANStest(const CString& strAddr,const CString strWavefile)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRty=15;


	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

	strCmd.Format(_T("*RST"));
	DEVICE_WRITE(strCmd);

	strCmd.Format(_T("*OPC?"));
	DEVICE_QUERY_DELAY(strCmd,50);

	strCmd.Format(_T("*CLS"));
	DEVICE_WRITE(strCmd);

	//*********************************For GPRF Generator

	strCmd.Format(_T("ROUT:GPRF:GEN:RFS:CONN RF1C"));
	DEVICE_WRITE(strCmd);

	strCmd.Format(_T("SOUR:GPRF:GEN:LIST OFF"));
	DEVICE_WRITE(strCmd);

	strCmd.Format(_T("SOUR:GPRF:GEN:BBM ARB"));
	DEVICE_WRITE(strCmd);

	//strCmd.Format(_T("SOUR:GPRF:GEN:ARB:FILE 'D:\Rohde-Schwarz\CMW\Data\waveform\c2k_ch387_hold_up_down_up.wv'"));
	strCmd.Format("SOUR:GPRF:GEN:ARB:FILE '%s'",strWavefile);
	DEVICE_WRITE(strCmd);

	strCmd.Format(_T("TRIG:GPRF:GEN:ARB:SEGM:MODE CSE"));
	DEVICE_WRITE(strCmd);

	strCmd.Format(_T("SOUR:GPRF:GEN:ARB:MSEG:NAME?"));
	DEVICE_QUERY(strCmd);

	strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -55.00");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SOUR:GPRF:GEN:STAT ON");
	DEVICE_WRITE(strCmd);

	do 
	{
		strCmd.Format("SOUR:GPRF:GEN:STAT?");
		DEVICE_QUERY(strCmd);
		Sleep(500);
		strRes=Device_GetReadBuf();
		if(strRes.Find(_T("ON"))!=-1)
		{
			break;
		}
	} while (iRty-->0);

	if(strRes.Find(_T("ON"))==-1)
	{
		return DEVICE_FINDRES_FAIL;
	}

	//********************************************For CDMA Measure


	strCmd.Format("CONF:CDMA:MEAS:MEV:SCO:MOD 5");
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONF:CDMA:MEAS:MEV:SCO:SPEC 10");
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONF:CDMA:MEAS:RCON R12Q");
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONF:CDMA:MEAS:RFS:UMAR 9.00");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SYST:ERR?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	if (strRes.Find("0")==-1)
	{
		MessageBoxA(NULL,strRes,"warning",MB_OK);
	}
		
	return DEVICE_SUCCESS;
}
int CFuncCDMATest_CMW::ICDMATestHandover(const int iBand,const int iChannel)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	double dDlMHz;


	dDlMHz=CCDMABandInfo::ArfcnToHz(iBand,iChannel,1);
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SOUR:GPRF:GEN:RFS:FREQ %.3fMHz",dDlMHz);
	DEVICE_WRITE(strCmd);

	switch(iBand)
	{
	case CDMA_BC0_BAND_ID:
		strCmd=_T("CONF:CDMA:MEAS:RFS:BCL USC");
		break;
	case CDMA_BC1_BAND_ID:
		strCmd=_T("CONF:CDMA:MEAS:RFS:BCL USPC");
		break;
	}
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONF:CDMA:MEAS:RFS:CHAN %d",iChannel);
	DEVICE_WRITE(strCmd);

	strCmd.Format("SYST:ERR?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	if (strRes.Find("0")==-1)
	{
		MessageBoxA(NULL,strRes,"warning",MB_OK);
	}


	return DEVICE_SUCCESS;
}
int CFuncCDMATest_CMW::ICDMATestSetESN(const CString& strESN){return DEVICE_SUCCESS;}
int CFuncCDMATest_CMW::ICDMATestWFQ(const double d_CellPower,double d_Result[]){return DEVICE_SUCCESS;}

int CFuncCDMATest_CMW::ICDMATestHandoverCall(const int iBand,const int iChannel,const double dCellPwr,const double dFchLev)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	double dDlMHz;


	dDlMHz=CCDMABandInfo::ArfcnToHz(iBand,iChannel,1);

	strCmd.Format("SOUR:GPRF:GEN:RFS:FREQ %.3fMHz",dDlMHz);
	DEVICE_WRITE(strCmd);

	strCmd.Format("SOUR:GPRF:GEN:RFS:LEV %.2f",dCellPwr);
	DEVICE_WRITE(strCmd);


	switch(iBand)
	{
	case CDMA_BC0_BAND_ID:
		strCmd=_T("CONF:CDMA:MEAS:RFS:BCL USC");
		break;
	case CDMA_BC1_BAND_ID:
		strCmd=_T("CONF:CDMA:MEAS:RFS:BCL USPC");
		break;
	}
	DEVICE_WRITE(strCmd);

	strCmd.Format("CONF:CDMA:MEAS:RFS:CHAN %d",iChannel);
	DEVICE_WRITE(strCmd);


	strCmd.Format("SYST:ERR?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	if (strRes.Find("0")==-1)
	{
		MessageBoxA(NULL,strRes,"warning",MB_OK);
	}

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_CMW::ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem,int powercnt)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;
	CStringVtr strVtrTemp;
	CString strTemp;

	strCmd.Format("*CLS");
	DEVICE_WRITE(strCmd);

	if ((strTestItem.Find("A1")!=-1)||(strTestItem.Find("B1")!=-1)||(strTestItem.Find("C1")!=-1)||(strTestItem.Find("D1")!=-1)||
		(strTestItem.Find("E1")!=-1)||(strTestItem.Find("F1")!=-1)||(strTestItem.Find("G1")!=-1))//wfq@-75dBm test
	{
		//A d_Result[0]=Carrier feedthrough
		//B d_Result[1]=EVM
		//C d_Result[2]=Frequency error
		//D d_Result[3]=Magnitude error
		//E d_Result[4]=Phase error
		//F d_Result[5]=Rho
		//G d_Result[6]=Time error
		//# ##############################################################################
		//#  Multi-evaluation measurement for TX (modulation quality)
		//# ##############################################################################
		strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 1");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -104.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONF:CDMA:MEAS:RFS:ENP 25.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);
		Sleep(100);

		strCmd.Format("CONF:CDMA:MEAS:MEV:RES:ALL ON,ON,ON,OFF,OFF,OFF,OFF,ON,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:CDMA:MEAS:MEV:SOUR 'GPRF Gen1: Waveform Marker 2'");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);

		strCmd.Format("INIT:CDMA:MEAS:MEV;*OPC?");
		DEVICE_QUERY(strCmd);

		do 
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:STAT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")!=-1)
			{
				break;
			}
			Sleep(50);
		} while (iRetryTimes-->0);

		strCmd.Format("FETC:CDMA:MEAS:MEV:MOD:AVER?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();

		strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		//strCmd.Format("CALC:CDMA:MEAS:MEV:MOD:AVER?");
		//DEVICE_QUERY(strCmd);
		//strReadBuf=Device_GetReadBuf();

		if (strTestItem.Find("A1")!=-1)//A: Carrier feedthrough
		{
			strVtrResult.push_back(strVtrTemp[7]);
		}

		if (strTestItem.Find("B1")!=-1)//B: EVM AVG
		{
			strVtrResult.push_back(strVtrTemp[1]);
		}

		if (strTestItem.Find("C1")!=-1)//C: Frequency error
		{
			strVtrResult.push_back(strVtrTemp[9]);
		}

		if (strTestItem.Find("D1")!=-1)//D: Magnitude error
		{
			strVtrResult.push_back(strVtrTemp[3]);
		}

		if (strTestItem.Find("E1")!=-1)//E: Phase error
		{
			strVtrResult.push_back(strVtrTemp[5]);
		}

		if (strTestItem.Find("F1")!=-1)//F: Rho
		{
			strVtrResult.push_back(strVtrTemp[13]);
		}

		if (strTestItem.Find("F1")!=-1)//G: Time error
		{
			strVtrResult.push_back(strVtrTemp[10]);
		}


	}

	if((strTestItem.Find("H1")!=-1)||(strTestItem.Find("I1")!=-1))//MAX POWER & ACPR
	{
		strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 1");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC");
		DEVICE_WRITE(strCmd);

				
		//# ##############################################################################
		//#  Multi-evaluation measurement for TX (power and ACP)
		//# ##############################################################################
		strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -104.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONF:CDMA:MEAS:RFS:ENP 25.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);
		Sleep(100);
		if (iBand==CDMA_BC0_BAND_ID)
		{
			strCmd.Format("CONF:CDMA:MEAS:MEV:ACP:FOFF 0.885,1.98,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);
		}
		else if (iBand==CDMA_BC1_BAND_ID)
		{
			strCmd.Format("CONF:CDMA:MEAS:MEV:ACP:FOFF 1.25,1.98,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);
		}
		else
		{
			MessageBoxA(NULL,"Do NOT supported Band","warning",MB_OK);
			return CDMACAL_SETCH;
		}
		

		strCmd.Format("CONF:CDMA:MEAS:MEV:RES OFF,OFF,OFF,ON,OFF,OFF,ON,OFF,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:CDMA:MEAS:MEV:SOUR 'Free Run'");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);

		strCmd.Format("INIT:CDMA:MEAS:MEV;*OPC?");
		DEVICE_QUERY(strCmd);

		do 
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:STAT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")!=-1)
			{
				break;
			}
			Sleep(50);
		} while (iRetryTimes-->0);

		if (strTestItem.Find("H1")!=-1)//max pwr (channel pwr)
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:MOD:AVER?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();

			strVtrTemp.clear();
			CStr::ParseString(strReadBuf,",",strVtrTemp);
			strVtrResult.push_back(strVtrTemp[12]+','+strVtrTemp[11]);
		}

		if (strTestItem.Find("I1")!=-1)//ACPR
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:TRAC:ACP:AVER?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();

			strVtrTemp.clear();
			CStr::ParseString(strReadBuf,",",strVtrTemp);
			strTemp.Format("0,0,%s,%s,%s,%s",strVtrTemp[10],strVtrTemp[12],strVtrTemp[9],strVtrTemp[13]);//0,0 to fit check result in meascpp
			strVtrResult.push_back(strTemp);
		}

		//strCmd.Format("CALC:CDMA:MEAS:MEV:TRAC:ACP:AVER?");
		//DEVICE_QUERY(strCmd);
		//strReadBuf=Device_GetReadBuf();
	}

	if(strTestItem.Find("J1")!=-1)//Min power
	{
		//# ##############################################################################
		//#  Multi-evaluation measurement for TX (min. power)
		//#  switch to segment #2 for min. power measurement
		//# ##############################################################################
		strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -10.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 2");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC;*OPC?");
		DEVICE_QUERY(strCmd);

		strCmd.Format("CONF:CDMA:MEAS:MEV:RES OFF,OFF,OFF,OFF,OFF,OFF,ON,OFF,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:CDMA:MEAS:MEV:SOUR 'Free Run'");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONF:CDMA:MEAS:RFS:ENP -50.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);

		Sleep(200);
		strCmd.Format("INIT:CDMA:MEAS:MEV;*OPC?");
		DEVICE_QUERY(strCmd);
		do 
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:STAT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")!=-1)
			{
				break;
			}
			Sleep(50);
		} while (iRetryTimes-->0);
		strCmd.Format("FETC:CDMA:MEAS:MEV:MOD:AVER?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();

		strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		if (strVtrTemp[0]!="0")
		{
			strCmd.Format("CONF:CDMA:MEAS:RFS:ENP -35.00");
			DEVICE_WRITE(strCmd);

			strCmd.Format("*OPC?");
			DEVICE_QUERY(strCmd);

			Sleep(200);
			strCmd.Format("INIT:CDMA:MEAS:MEV;*OPC?");
			DEVICE_QUERY(strCmd);
			do 
			{
				strCmd.Format("FETC:CDMA:MEAS:MEV:STAT?");
				DEVICE_QUERY(strCmd);
				strReadBuf=Device_GetReadBuf();
				if (strReadBuf.Find("RDY")!=-1)
				{
					break;
				}
				Sleep(50);
			} while (iRetryTimes-->0);
			strCmd.Format("FETC:CDMA:MEAS:MEV:MOD:AVER?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();

			strVtrTemp.clear();
			CStr::ParseString(strReadBuf,",",strVtrTemp);

		}
		strVtrResult.push_back(strVtrTemp[12]+','+strVtrTemp[11]);

		//strCmd.Format("CALC:CDMA:MEAS:MEV:MOD:AVER?");
		//DEVICE_QUERY(strCmd);
		//strReadBuf=Device_GetReadBuf();

	}
	strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 0");
	DEVICE_WRITE(strCmd);

	strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -55.00");
	DEVICE_WRITE(strCmd);

	strCmd.Format("*OPC?");
	DEVICE_QUERY(strCmd);
	Sleep(100);

	strCmd.Format("SYST:ERR?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();
	if (strReadBuf.Find("0")==-1)
	{
		MessageBoxA(NULL,strReadBuf,"warning",MB_OK);
	}

	return DEVICE_SUCCESS;
}


int CFuncCDMATest_CMW::ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;
	CStringVtr strVtrTemp;
	CString strTemp;
	double dTargetPower;

	strCmd.Format("*CLS");
	DEVICE_WRITE(strCmd);

	if ((strTestItem.Find("A1")!=-1)||(strTestItem.Find("B1")!=-1)||(strTestItem.Find("C1")!=-1)||(strTestItem.Find("D1")!=-1)||
		(strTestItem.Find("E1")!=-1)||(strTestItem.Find("F1")!=-1)||(strTestItem.Find("G1")!=-1))//wfq@-75dBm test
	{
		//A d_Result[0]=Carrier feedthrough
		//B d_Result[1]=EVM
		//C d_Result[2]=Frequency error
		//D d_Result[3]=Magnitude error
		//E d_Result[4]=Phase error
		//F d_Result[5]=Rho
		//G d_Result[6]=Time error
		//# ##############################################################################
		//#  Multi-evaluation measurement for TX (modulation quality)
		//# ##############################################################################
		strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 1");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -101.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONF:CDMA:MEAS:RFS:ENP 25.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);
		Sleep(100);

		strCmd.Format("CONF:CDMA:MEAS:MEV:RES:ALL ON,ON,ON,OFF,OFF,OFF,OFF,ON,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:CDMA:MEAS:MEV:SOUR 'GPRF Gen1: Waveform Marker 2'");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);

		strCmd.Format("INIT:CDMA:MEAS:MEV;*OPC?");
		DEVICE_QUERY(strCmd);

		do 
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:STAT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")!=-1)
			{
				break;
			}
			Sleep(50);
		} while (iRetryTimes-->0);

		strCmd.Format("FETC:CDMA:MEAS:MEV:MOD:AVER?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();

		strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		//strCmd.Format("CALC:CDMA:MEAS:MEV:MOD:AVER?");
		//DEVICE_QUERY(strCmd);
		//strReadBuf=Device_GetReadBuf();

		if (strTestItem.Find("A1")!=-1)//A: Carrier feedthrough
		{
			strVtrResult.push_back(strVtrTemp[7]);
		}

		if (strTestItem.Find("B1")!=-1)//B: EVM AVG
		{
			strVtrResult.push_back(strVtrTemp[1]);
		}

		if (strTestItem.Find("C1")!=-1)//C: Frequency error
		{
			strVtrResult.push_back(strVtrTemp[9]);
		}

		if (strTestItem.Find("D1")!=-1)//D: Magnitude error
		{
			strVtrResult.push_back(strVtrTemp[3]);
		}

		if (strTestItem.Find("E1")!=-1)//E: Phase error
		{
			strVtrResult.push_back(strVtrTemp[5]);
		}

		if (strTestItem.Find("F1")!=-1)//F: Rho
		{
			strVtrResult.push_back(strVtrTemp[13]);
		}

		if (strTestItem.Find("F1")!=-1)//G: Time error
		{
			strVtrResult.push_back(strVtrTemp[10]);
		}


	}

	if((strTestItem.Find("H1")!=-1)||(strTestItem.Find("I1")!=-1))//MAX POWER & ACPR
	{
		strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 1");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC");
		DEVICE_WRITE(strCmd);

		//# ##############################################################################
		//#  Multi-evaluation measurement for TX (power and ACP)
		//# ##############################################################################
		strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -104.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONF:CDMA:MEAS:RFS:ENP 25.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);

		Sleep(100);

		strCmd.Format("CONF:CDMA:MEAS:MEV:ACP:FOFF 1.23,2.46,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CONF:CDMA:MEAS:MEV:RES OFF,OFF,OFF,ON,OFF,OFF,ON,OFF,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:CDMA:MEAS:MEV:SOUR 'Free Run'");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);

		strCmd.Format("INIT:CDMA:MEAS:MEV;*OPC?");
		DEVICE_QUERY(strCmd);

		do 
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:STAT?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")!=-1)
			{
				break;
			}
			Sleep(50);
		} while (iRetryTimes-->0);

		if (strTestItem.Find("H1")!=-1)//max pwr (channel pwr)
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:MOD:AVER?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();

			strVtrTemp.clear();
			CStr::ParseString(strReadBuf,",",strVtrTemp);
			strVtrResult.push_back(strVtrTemp[12]+','+strVtrTemp[11]);
		}

		if (strTestItem.Find("I1")!=-1)//ACPR
		{
			strCmd.Format("FETC:CDMA:MEAS:MEV:TRAC:ACP:AVER?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();

			strVtrTemp.clear();
			CStr::ParseString(strReadBuf,",",strVtrTemp);
			strTemp.Format("0,0,%s,%s,%s,%s",strVtrTemp[10],strVtrTemp[12],strVtrTemp[9],strVtrTemp[13]);//0,0 to fit check result in meascpp
			strVtrResult.push_back(strTemp);
		}

		//strCmd.Format("CALC:CDMA:MEAS:MEV:TRAC:ACP:AVER?");
		//DEVICE_QUERY(strCmd);
		//strReadBuf=Device_GetReadBuf();
	}

	if(strTestItem.Find("J1")!=-1)//Min power
	{
		//# ##############################################################################
		//#  Multi-evaluation measurement for TX (min. power)
		//#  switch to segment #2 for min. power measurement
		//# ##############################################################################
		strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -10.00");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 2");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC;*OPC?");
		DEVICE_QUERY(strCmd);

		strCmd.Format("CONF:CDMA:MEAS:MEV:RES OFF,OFF,OFF,OFF,OFF,OFF,ON,OFF,OFF,OFF,OFF,OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("TRIG:CDMA:MEAS:MEV:SOUR 'Free Run'");
		DEVICE_WRITE(strCmd);

		strCmd.Format("*OPC?");
		DEVICE_QUERY(strCmd);

		Sleep(200);

		dTargetPower=-50;
		do
		{
			strCmd.Format("CONF:CDMA:MEAS:RFS:ENP %.2f",dTargetPower);
			DEVICE_WRITE(strCmd);
			strCmd.Format("INIT:CDMA:MEAS:MEV;*OPC?");
			DEVICE_QUERY(strCmd);
			do 
			{
				strCmd.Format("FETC:CDMA:MEAS:MEV:STAT?");
				DEVICE_QUERY(strCmd);
				strReadBuf=Device_GetReadBuf();
				if (strReadBuf.Find("RDY")!=-1)
				{
					break;
				}
				Sleep(50);
			} while (iRetryTimes-->0);
			strCmd.Format("FETC:CDMA:MEAS:MEV:MOD:AVER?");
			DEVICE_QUERY(strCmd);
			strReadBuf=Device_GetReadBuf();

			strVtrTemp.clear();
			CStr::ParseString(strReadBuf,",",strVtrTemp);
			if (strVtrTemp[0]=="3")
			{
				dTargetPower=dTargetPower+5;
			}
			else if (strVtrTemp[0]=="4")
			{
				dTargetPower=dTargetPower-5;
			}

			
		}while(strVtrTemp[0]!="0" && --iTimeout>0);
		if (strVtrTemp[0]=="0")
		{
			strVtrResult.push_back(strVtrTemp[12]+','+strVtrTemp[11]);
		}
		
		strVtrResult.push_back(strVtrTemp[12]+','+strVtrTemp[11]);

		//strCmd.Format("CALC:CDMA:MEAS:MEV:MOD:AVER?");
		//DEVICE_QUERY(strCmd);
		//strReadBuf=Device_GetReadBuf();

	}
	strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 0");
	DEVICE_WRITE(strCmd);

	strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -55.00");
	DEVICE_WRITE(strCmd);

	strCmd.Format("*OPC?");
	DEVICE_QUERY(strCmd);
	Sleep(100);

	strCmd.Format("SYST:ERR?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();
	if (strReadBuf.Find("0")==-1)
	{
		MessageBoxA(NULL,strReadBuf,"warning",MB_OK);
	}

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_CMW::ICDMATestStartRXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	//# switch to segment #3 for receiver sensitivity measurement
	strCmd.Format("SOUR:GPRF:GEN:RFS:LEV -106.50");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SOUR:GPRF:GEN:ARB:SEGM:NEXT 3");
	DEVICE_WRITE(strCmd);

	strCmd.Format("TRIG:GPRF:GEN:ARB:SEGM:MAN:EXEC;*OPC?");
	DEVICE_QUERY(strCmd);

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_CMW::ICDMATestStartRxLevelMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem,int iIndex)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;

	strCmd.Format("SOUR:GPRF:GEN:RFS:LEV %.2f;*OPC?",d_CellPower[iIndex]);
	DEVICE_QUERY(strCmd);

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_CMW::ICDMATestSetLoss(int iCDMABand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;

	strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:DELete \'mytable\'");
	DEVICE_WRITE(strCmd)

	strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:CREate \'mytable\'");
	DEVICE_WRITE(strCmd)

	switch(iCDMABand)
	{
		case 800:
			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 824.7MHZ ,%.2f ,869.7MHZ,%.2f",vLossList[0],vLossList[0]);
			DEVICE_WRITE(strCmd)

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 836.52MHZ ,%.2f ,881.52MHZ,%.2f",vLossList[1],vLossList[1]);
			DEVICE_WRITE(strCmd)

			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 848.31MHZ ,%.2f ,893.31MHZ,%.2f",vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 1900:
			strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1851.25MHZ ,%.2f ,1931.25MHZ,%.2f",vLossList[0],vLossList[0]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1878.15MHZ ,%.2f ,1958.15MHZ,%.2f",vLossList[1],vLossList[1]);
			DEVICE_WRITE(strCmd)

				strCmd.Format("CONFigure:BASE:FDCorrection:CTABle:ADD \'mytable\', 1908.75MHZ ,%.2f ,1988.75MHZ,%.2f",vLossList[2],vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;

		default:
			return DEVICE_WRITE_FAIL;
	}

	strCmd.Format("CONF:CDMA:MEAS:RFS:EATT 0.0");
	DEVICE_WRITE(strCmd)

	strCmd.Format("CONFigure:FDCorrection:ACTivate RF1C, \'mytable\',RX");
	DEVICE_WRITE(strCmd)
	strCmd.Format("CONFigure:FDCorrection:ACTivate RF1C, \'mytable\',TX");
	DEVICE_WRITE(strCmd)

	strCmd.Format("SOUR:GPRF:GEN:RFS:EATT 0.0");
	DEVICE_WRITE(strCmd)

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_CMW::ICDMATestEndCall()
{
	return DEVICE_SUCCESS;
}

 