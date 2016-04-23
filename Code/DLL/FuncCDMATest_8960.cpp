#include "StdAfx.h"
#include "FuncCDMATest_8960.h"

CFuncCDMATest_8960::CFuncCDMATest_8960(void)
{
}

CFuncCDMATest_8960::~CFuncCDMATest_8960(void)
{
}

CFuncCDMATest_8960::CFuncCDMATest_8960(PCTesterDevice pDev):CFuncDev_8960(pDev)
{

}
int CFuncCDMATest_8960::ICDMATestInitCDMANStest(const CString& strAddr,const CString strWavefile)//strWavefile for CMW USE
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;	
	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;
	
		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
	DEVICE_QUERY(strCmd)
	strRes=Device_GetReadBuf();
	if (strRes.Find(_T("IS-2000"))==-1)
	{
		strCmd=_T("SYSTEM:APPLICATION:FORMAT 'IS-2000/IS-95/AMPS'");
		DEVICE_WRITE(strCmd)
		strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (strRes.Find(_T("IS-2000"))==-1)
		{
			MessageBox(NULL,_T("Device fast switch IS-2000 fail!"),_T("WARNING"),MB_OK);
			return DEVICE_WRITE_FAIL;
		}
			
	}
	
	int i=5;
	strCmd=_T("*RST");
	DEVICE_WRITE(strCmd)
	

	if(m_pTesterDevice->m_bIsScreenOff)
	{
		strCmd=_T("DISPLAY:MODE FAST");
		DEVICE_WRITE(strCmd)

	}
		strCmd=_T("CALL:CELL:OPERATING:MODE OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("RFGENERATOR:OUTPUT:DESTINATION IO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:PROT PREV6");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:RCONFIG F1R1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:SOPTION SO55");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:POWER:AMPLITUDE -65");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:POWER:STATE ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:TRAF:DRAT FULL");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PILOT:LEVEL -7");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PAG:LEV -12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FCH:LEV -15.6");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:SYNC:LEV -16");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:PNOF 12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:SID 331");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:NID 1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PAG:SCIN 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CLPC:REV:MODE ALT;*OPC?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	DEVICE_WRITE(strCmd)
		/*strCmd=_T("CALL:CELL:CLPC:REV:STEP DB1");
	DEVICE_WRITE(strCmd)*/
	strCmd=_T("CALL:CELL:OPERATING:MODE D2KTEST");
	DEVICE_WRITE(strCmd)
		strCmd=_T("RFANALYZER:MANUAL:POWER:SELECTED 30;*OPC?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:REGISTER:TIMER 29");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:RLGAIN 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:QPCHANNEL:LEVEL:RTPILOT -3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:QPCHANNEL:STATE OFF");
	DEVICE_WRITE(strCmd)
		
	strCmd=_T("*OPC?");
	i=50;
	int iRes;
	do 
	{
		DEVICE_QUERY_DELAY(strCmd,20)
			strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);

		return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestHandover(const int iBand,const int iChannel)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iRes;
	switch(iBand)
	{
	case CDMA_BC0_BAND_ID:
		strCmd=_T("CALL:BAND USC");
		break;
	case CDMA_BC1_BAND_ID:
		strCmd=_T("CALL:BAND USPC");
		break;
	case CDMA_BC10_BAND_ID:
		strCmd=_T("CALL:BAND SEC800");
		break;
	}
	DEVICE_WRITE(strCmd)

		strCmd.Format("CALL:CHAN:SEL %d",iChannel);
	DEVICE_WRITE(strCmd)		
		strCmd=_T("*OPC?");
	int i=50;
	do 
	{
		DEVICE_QUERY_DELAY(strCmd,20)
			strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);

		return DEVICE_SUCCESS;

}
int CFuncCDMATest_8960::ICDMATestSetPower(double dCellPower,double dExpectPower,int iPCB)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iRes;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);


	strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.2f",dCellPower);
	DEVICE_WRITE(strCmd);

	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
	DEVICE_WRITE(strCmd);
	strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %.2f",dExpectPower);
	DEVICE_WRITE(strCmd);
	switch(iPCB)
	{
	case 0:
		strCmd=_T("CALL:CLPC:REV:MODE DOWN");
		break;
	case 1:
		strCmd=_T("CALL:CLPC:REV:MODE UP");
		break;
	default:
		strCmd=_T("CALL:CLPC:REV:MODE ALT");

	}
	DEVICE_WRITE(strCmd);		
		strCmd=_T("*OPC?");
	int i=50;
	do 
	{
		DEVICE_QUERY_DELAY(strCmd,20)
			strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);

	return DEVICE_SUCCESS;
	
}
int CFuncCDMATest_8960::ICDMATestSetESN(const CString& strESN)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd.Format("CALL:D2KT:ESN:HEX \"%s\"",strESN);
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;
}
int CFuncCDMATest_8960::ICDMATestWFQ(int iMeasCount,double* dRho,double* dFer,double* dTer,double* dCFT,double* dPer,double* dMer,double* dEVM)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	int iRetryTimes=50;
	int iTimeout=10;
	
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);
		
		
		strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);
		strCmd=_T("RFANALYZER:MANUAL:POWER:SELECTED 10");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);
		Sleep(50);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("SETUP:WQUALITY:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:WQUALITY:COUNT:NUMBER %d",iMeasCount);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:WQUALITY:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:WQUALITY:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("INITIATE:WQUALITY:ON");
		DEVICE_WRITE(strCmd);		

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(20);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("WQU")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:WQUALITY?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		*dCFT=CStr::StrToFloat(strReadBuf);
		

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:EVM:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		*dEVM=CStr::StrToFloat(strReadBuf);
		

		strCmd=_T("FETCH:WQUALITY:EVM:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:EVM:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FERROR:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		*dFer=CStr::StrToFloat(strReadBuf);

		strCmd=_T("FETCH:WQUALITY:FERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:MERROR:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		*dMer=CStr::StrToFloat(strReadBuf);

		strCmd=_T("FETCH:WQUALITY:MERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:MERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:PERROR:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		*dPer=CStr::StrToFloat(strReadBuf);	

		strCmd=_T("FETCH:WQUALITY:PERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:PERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:RHO:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		*dRho=CStr::StrToFloat(strReadBuf);
		

		strCmd=_T("FETCH:WQUALITY:RHO:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:RHO:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:TERROR:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		*dTer=CStr::StrToFloat(strReadBuf);

		strCmd=_T("FETCH:WQUALITY:TERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:TERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("INITIATE:WQUALITY:OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE -75");
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
	
	return DEVICE_SUCCESS;

}
int CFuncCDMATest_8960::ICDMATestTROLPC(int *iResult)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	int iRetryTimes=50;
	int iTimeout=10;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);
	*iResult=0;

	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -60");
	DEVICE_WRITE(strCmd);
	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:FCH -7.4");
	DEVICE_WRITE(strCmd);
	for (int i=0;i<4;i++)
	{		
		switch(i)
		{
		case 0:
			strCmd=_T("SETUP:TROP:STEP UP20");
			break;
		case 1:
			strCmd=_T("SETUP:TROP:STEP DOWN20");
			break;
		case 2:
			strCmd=_T("SETUP:TROP:STEP DOWN20");
			break;
		case 3:
			strCmd=_T("SETUP:TROP:STEP UP20");
			break;
		}
		DEVICE_WRITE(strCmd);
		strCmd=_T("INITIATE:TROP");
		DEVICE_WRITE(strCmd);
		iRetryTimes=50;
		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(20);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("TROP")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("FETCh:TROP?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		CStringVtr strVtrTemp;
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		*iResult+=CStr::StrToInt(strVtrTemp[1]);

		
		
	}
	strCmd=_T("CALL:FCH -15.6");
	DEVICE_WRITE(strCmd);

	strCmd=_T("INITIATE:TROP:OFF");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;


}
int CFuncCDMATest_8960::ICDMATestMaxPower(int iMeasCount,double *dPower)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	int iRetryTimes=50;
	int iTimeout=10;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);


	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -101");
	DEVICE_WRITE(strCmd);

	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("RFANALYZER:MANUAL:POWER:SELECTED 24");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CLPC:REV:MODE UP");
	DEVICE_WRITE(strCmd);

	strCmd=_T("SETUP:CPOWER:COUNT:STATE ON");
	DEVICE_WRITE(strCmd);
	
	strCmd.Format("SETUP:CPOWER:COUNT:NUMBER %d",iMeasCount);
	DEVICE_WRITE(strCmd);

	strCmd=_T("SETUP:CPOWER:CONTINUOUS OFF");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SETUP:CPOWER:TIMEOUT:STIME %d",iTimeout);
	DEVICE_WRITE(strCmd);	

	do 
	{
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
	} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}

	Sleep(50);//Must have to avoid 8960 response slowly

	strCmd=_T("INITIATE:CPOWER");
	DEVICE_WRITE(strCmd);
	do 
	{
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);
		strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd);		
		Sleep(20);
		strReadBuf=Device_GetReadBuf();
		if(strReadBuf.Find("CPOW")!=-1)
		{
			break;
		}
	} while ( iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("FETCH:CPOWER:ALL?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();
	CStringVtr strVtrTemp;
	CStr::ParseString(strReadBuf,",",strVtrTemp);
	*dPower=CStr::StrToFloat(strVtrTemp[1]);

	strCmd=_T("INITIATE:CPOWER:OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CLPC:REV:MODE ALT");
	DEVICE_WRITE(strCmd);

	do 
	{
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
	} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncCDMATest_8960::ICDMATestMinPower(int iMeasCount,double *dPower)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	int iRetryTimes=50;
	int iTimeout=10;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);


	strCmd=_T("CALL:FCH:LEV -7.4");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -30");
	DEVICE_WRITE(strCmd);

	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("RFANALYZER:MANUAL:POWER:SELECTED -50");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CLPC:REV:MODE DOWN");
	DEVICE_WRITE(strCmd);

	strCmd=_T("SETUP:CPOWER:COUNT:STATE ON");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SETUP:CPOWER:COUNT:NUMBER %d",iMeasCount);
	DEVICE_WRITE(strCmd);

	strCmd=_T("SETUP:CPOWER:CONTINUOUS OFF");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SETUP:CPOWER:TIMEOUT:STIME %d",iTimeout);
	DEVICE_WRITE(strCmd);	

	do 
	{
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
	} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}

	Sleep(100);//Must have to avoid 8960 response slowly

	strCmd=_T("INITIATE:CPOWER");
	DEVICE_WRITE(strCmd);
	do 
	{
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);
		strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd);		
		Sleep(20);
		strReadBuf=Device_GetReadBuf();
		if(strReadBuf.Find("CPOW")!=-1)
		{
			break;
		}
	} while ( iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("FETCH:CPOWER:ALL?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();
	CStringVtr strVtrTemp;
	CStr::ParseString(strReadBuf,",",strVtrTemp);
	*dPower=CStr::StrToFloat(strVtrTemp[1]);

	strCmd=_T("INITIATE:CPOWER:OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CLPC:REV:MODE ALT");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CALL:FCH:LEV -15.6");
	DEVICE_WRITE(strCmd);

	do 
	{
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
	} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncCDMATest_8960::ICDMATestACPR(int iMeasCount,double dACPRValue[],int *iResult)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	int iRetryTimes=50;
	int iTimeout=10;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -101");
	DEVICE_WRITE(strCmd);

	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("RFANALYZER:MANUAL:POWER:SELECTED 24");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CLPC:REV:MODE UP");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SETUP:DAPOWER:COUNT:STATE ON");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SETUP:DAPOWER:COUNT:NUMBER %d",iMeasCount);
	DEVICE_WRITE(strCmd);

	strCmd=_T("SETUP:DAPOWER:CONTINUOUS OFF");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SETUP:DAPOWER:TIMEOUT:STIME %d",iTimeout);
	DEVICE_WRITE(strCmd);

	strCmd=_T("SETUP:CTXSPURIOUS:COUNT:STATE ON");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SETUP:CTXSPURIOUS:COUNT:NUMBER %d",iMeasCount);
	DEVICE_WRITE(strCmd);

	strCmd=_T("SETUP:CTXSPURIOUS:CONTINUOUS OFF");
	DEVICE_WRITE(strCmd);

	strCmd.Format("SETUP:CTXSPURIOUS:TIMEOUT:STIME %d",iTimeout);
	DEVICE_WRITE(strCmd);
	Sleep(50);
	do 
	{
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
	} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}	

	strCmd=_T("INITIATE:CTXSPURIOUS");
	DEVICE_WRITE(strCmd);

	do 
	{
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);
		strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd);		
		Sleep(50);
		strReadBuf=Device_GetReadBuf();
		if(strReadBuf.Find("CTXS")!=-1)
		{
			break;
		}
	} while ( iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("FETCH:CTXSPURIOUS?");
	DEVICE_QUERY(strCmd);
	strReadBuf=Device_GetReadBuf();
	CStringVtr strVtrTemp;
	CStr::ParseString(strReadBuf,",",strVtrTemp);
	*iResult=CStr::StrToInt(strVtrTemp[1]);
	dACPRValue[0]=CStr::StrToFloat(strVtrTemp[2]);
	dACPRValue[1]=CStr::StrToFloat(strVtrTemp[3]);
	dACPRValue[2]=CStr::StrToFloat(strVtrTemp[4]);
	dACPRValue[3]=CStr::StrToFloat(strVtrTemp[5]);

	strCmd=_T("INITIATE:CTXSPURIOUS:OFF");
	DEVICE_WRITE(strCmd);

	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd);

	strCmd=_T("CALL:CLPC:REV:MODE ALT");
	DEVICE_WRITE(strCmd);

	do 
	{
		strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd);
	} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

	if (iRetryTimes==-1)
	{
		return DEVICE_QUERY_FAIL;
	}
	return DEVICE_SUCCESS;

}

int CFuncCDMATest_8960::ICDMATestWFQ(const double d_CellPower,double d_Result[])
{
	//d_Result[0]=Integrity
	//d_Result[1]=Rho
	//d_Result[2]=Frequency error
	//d_Result[3]=Time error
	//d_Result[4]=Carrier feedthrough
	//d_Result[5]=Phase error
	//d_Result[6]=Magnitude error
	//d_Result[7]=EVM
	

	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("INITIATE:WQUALITY:ON");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		int i=3;
		do 
		{
			strCmd=_T("INITiate:Done?");
			DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
			Sleep(20);

		} while (strRes!=_T("NONE")&&i-->0);
	strCmd=_T("FETCh:WQUALITY?");
	DEVICE_QUERY(strCmd)
	strRes=Device_GetReadBuf();
	//CStr::StrToDblArr(strRes,d_Result[],_T(","),8);

	strCmd=_T("INITIATE:WQUALITY:OFF");
	DEVICE_WRITE(strCmd)
	
	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestHandoverCall(const int iBand,const int iChannel,const double dCellPwr,const double dFchLev)
{
	CString strCmd;
	CString strRes,strTemp;
	int iDeviceErr;
	CString strTempHzUL,strTempHzDL;
	
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);

	switch(iBand)
	{
	case CDMA_BC0_BAND_ID:
		strTemp=_T("USC");
		break;
	case CDMA_BC1_BAND_ID:
		strTemp=_T("USPC");
		break;
	case CDMA_BC10_BAND_ID:
		strTemp=_T("SEC800");
		break;
	}

	strCmd=_T("CALL:BAND?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();

	if (strRes.Find(strTemp)==-1)
	{
		ICDMATestHandover(iBand,iChannel);
	}

	strCmd=_T("CALL:CHANNEL?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	if(strRes.Find(CStr::IntToStr(iChannel))==-1)
	{
		Sleep(50);
		strCmd=_T("CALL:CHANNEL?");
		DEVICE_QUERY(strCmd);
		strRes=Device_GetReadBuf();
		if(strRes.Find(CStr::IntToStr(iChannel))==-1)
		{
			strCmd.Format("CALL:CHANNEL:SEL %d",iChannel);
			DEVICE_WRITE(strCmd);

			Sleep(20);
			strCmd=_T("CALL:CHANNEL?");
			DEVICE_QUERY(strCmd);
			strRes=Device_GetReadBuf();
			if(strRes.Find(CStr::IntToStr(iChannel))==-1)
			{
				Sleep(20);
				strCmd=_T("CALL:CHANNEL?");
				DEVICE_QUERY(strCmd);
				strRes=Device_GetReadBuf();
				if(strRes.Find(CStr::IntToStr(iChannel))==-1)
				{
					return DEVICE_QUERY_FAIL;
				}
			}
		}
	}
	strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.2f",dCellPwr);
	DEVICE_WRITE(strCmd);

	if (dFchLev<-0.01)
	{
		strCmd.Format("CALL:FCH:LEV %.1f",dFchLev);
		DEVICE_WRITE(strCmd);

		return DEVICE_SUCCESS;
	}

	


	strCmd=_T("CALL:CELL:POWER:STATE ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:TRAF:DRAT FULL");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PILOT:LEVEL -7");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PAG:LEV -12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FCH:LEV -15.6");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:SYNC:LEV -16");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:PNOF 12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:SID 331");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:NID 1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PAG:SCIN 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CLPC:REV:MODE ALT;*OPC?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	//DEVICE_WRITE(strCmd)
	strCmd=_T("CALL:CLPC:REV:STEP DB1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("RFANALYZER:MANUAL:POWER:SELECTED 30;*OPC?");
	DEVICE_QUERY_DELAY(strCmd,300)
		strRes=Device_GetReadBuf();
	//DEVICE_WRITE(strCmd)
	strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:REGISTER:TIMER 29");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:RLGAIN 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:QPCHANNEL:LEVEL:RTPILOT -3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:QPCHANNEL:STATE OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)


	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;

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
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);

		ICDMATestHandoverCall(iBand,iChan,d_CellPower[0],0);
		//strCellPower.Format("%.2f",d_CellPower[0]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);
		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",25);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE UP");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("SETUP:WQUALITY:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:WQUALITY:COUNT:NUMBER %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:WQUALITY:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:WQUALITY:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("INITIATE:WQUALITY:ON");
		DEVICE_WRITE(strCmd);
		Sleep(1000);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(300);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("WQU")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:WQUALITY?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,300);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("A1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:EVM:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("B1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:EVM:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:EVM:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FERROR:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("C1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:FERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:MERROR:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("D1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:MERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:MERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:PERROR:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("E1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}	

		strCmd=_T("FETCH:WQUALITY:PERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:PERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:RHO:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("F1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:RHO:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:RHO:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:TERROR:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("G1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:TERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:TERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("INITIATE:WQUALITY:OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.1f",d_CellPower[4]);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		//strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		//DEVICE_WRITE(strCmd);

	}

	if(strTestItem.Find("H1")!=-1)//MAX POWER
	{
		ICDMATestHandoverCall(iBand,iChan,d_CellPower[1],0);
		//strCellPower.Format("%.2f",d_CellPower[1]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CPOWER:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		//strCmd.Format("SETUP:CPOWER:COUNT:NUMBER %d",iCountPwr);
		strCmd.Format("SETUP:CPOWER:COUNT:NUMBER 20");
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CPOWER:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CPOWER:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE UP");
		DEVICE_WRITE(strCmd);

		//strCmd=_T("CALL:CONT:DOWN:TIM:ADV 0");
		//DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		Sleep(1000);//Must have to avoid 8960 response slowly

		strCmd=_T("INITIATE:CPOWER");
		DEVICE_WRITE(strCmd);
		Sleep(1000);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(300);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("CPOW")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:CPOWER:ALL?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		strVtrResult.push_back(strReadBuf);

		strCmd=_T("INITIATE:CPOWER:OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.1f",d_CellPower[4]);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		DEVICE_WRITE(strCmd);

	}

	if (strTestItem.Find("I1")!=-1)//ACPR
	{
		ICDMATestHandoverCall(iBand,iChan,d_CellPower[1],0);
		//strCellPower.Format("%.2f",d_CellPower[1]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:DAPOWER:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:DAPOWER:COUNT:NUMBER %d",iCountPwr);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:DAPOWER:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:DAPOWER:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CTXSPURIOUS:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CTXSPURIOUS:COUNT:NUMBER %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CTXSPURIOUS:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CTXSPURIOUS:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("CALL:CLPC:REV:MODE UP");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("INITIATE:CTXSPURIOUS");
		DEVICE_WRITE(strCmd);
		Sleep(1000);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(300);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("CTXS")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:CTXSPURIOUS?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		strVtrResult.push_back(strReadBuf);

		strCmd=_T("INITIATE:CTXSPURIOUS:OFF");
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.1f",d_CellPower[4]);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

	}

	if(strTestItem.Find("J1")!=-1)//Min power
	{
		iPwrSel=-60;

		ICDMATestHandoverCall(iBand,iChan,d_CellPower[2],-7.4);

		strCellPower.Format("%.2f",d_CellPower[2]);
		strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CPOWER:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CPOWER:COUNT:NUMBER %d",iCountPwr);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CPOWER:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CPOWER:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("CALL:CLPC:REV:MODE DOWN");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		Sleep(1000);//Must have to avoid 8960 response slowly

		strCmd=_T("INITIATE:CPOWER");
		DEVICE_WRITE(strCmd);
		//Sleep(1000);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(300);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("CPOW")!=-1)
			{
				break;
			}
		} while (iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:CPOWER:ALL?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		strVtrResult.push_back(strReadBuf);

		strCmd=_T("INITIATE:CPOWER:OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.1f",d_CellPower[4]);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		DEVICE_WRITE(strCmd);

	}

	return DEVICE_SUCCESS;
}
int CFuncCDMATest_8960::ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem,int powercnt)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;

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
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);

		ICDMATestHandoverCall(iBand,iChan,d_CellPower[0],0);
		//strCellPower.Format("%.2f",d_CellPower[0]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);
		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",25);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE UP");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("SETUP:WQUALITY:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:WQUALITY:COUNT:NUMBER %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:WQUALITY:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:WQUALITY:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("INITIATE:WQUALITY:ON");
		DEVICE_WRITE(strCmd);
		Sleep(1000);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(300);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("WQU")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:WQUALITY?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,300);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("A1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:EVM:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("B1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:EVM:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:EVM:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FERROR:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("C1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:FERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:MERROR:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("D1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:MERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:MERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:PERROR:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("E1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}	

		strCmd=_T("FETCH:WQUALITY:PERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:PERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:RHO:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("F1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:RHO:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:RHO:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:TERROR:AVERAGE?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("G1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:TERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:TERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("INITIATE:WQUALITY:OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.1f",d_CellPower[4]);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		//strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		//DEVICE_WRITE(strCmd);

	}

	if(strTestItem.Find("H1")!=-1)//MAX POWER
	{
		ICDMATestHandoverCall(iBand,iChan,d_CellPower[1],0);
		//strCellPower.Format("%.2f",d_CellPower[1]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CPOWER:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CPOWER:COUNT:NUMBER %d",powercnt);
		
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CPOWER:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CPOWER:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE UP");
		DEVICE_WRITE(strCmd);

		//strCmd=_T("CALL:CONT:DOWN:TIM:ADV 0");
		//DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		Sleep(1000);//Must have to avoid 8960 response slowly

		strCmd=_T("INITIATE:CPOWER");
		DEVICE_WRITE(strCmd);
		Sleep(1000);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(300);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("CPOW")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:CPOWER:ALL?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		strVtrResult.push_back(strReadBuf);

		strCmd=_T("INITIATE:CPOWER:OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.1f",d_CellPower[4]);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		DEVICE_WRITE(strCmd);

	}

	if (strTestItem.Find("I1")!=-1)//ACPR
	{
		ICDMATestHandoverCall(iBand,iChan,d_CellPower[1],0);
		//strCellPower.Format("%.2f",d_CellPower[1]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:DAPOWER:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:DAPOWER:COUNT:NUMBER %d",iCountPwr);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:DAPOWER:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:DAPOWER:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CTXSPURIOUS:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CTXSPURIOUS:COUNT:NUMBER %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CTXSPURIOUS:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CTXSPURIOUS:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("CALL:CLPC:REV:MODE UP");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("INITIATE:CTXSPURIOUS");
		DEVICE_WRITE(strCmd);
		Sleep(1000);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(300);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("CTXS")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:CTXSPURIOUS?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		strVtrResult.push_back(strReadBuf);

		strCmd=_T("INITIATE:CTXSPURIOUS:OFF");
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.1f",d_CellPower[4]);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

	}

	if(strTestItem.Find("J1")!=-1)//Min power
	{
		iPwrSel=-60;

		ICDMATestHandoverCall(iBand,iChan,d_CellPower[2],-7.4);

		strCellPower.Format("%.2f",d_CellPower[2]);
		strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CPOWER:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CPOWER:COUNT:NUMBER %d",iCountPwr);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CPOWER:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CPOWER:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("CALL:CLPC:REV:MODE DOWN");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		Sleep(1000);//Must have to avoid 8960 response slowly

		strCmd=_T("INITIATE:CPOWER");
		DEVICE_WRITE(strCmd);
		//Sleep(1000);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(300);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("CPOW")!=-1)
			{
				break;
			}
		} while (iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:CPOWER:ALL?");
		DEVICE_QUERY_DELAY(strCmd,100);
		strReadBuf=Device_GetReadBuf();
		strVtrResult.push_back(strReadBuf);

		strCmd=_T("INITIATE:CPOWER:OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.1f",d_CellPower[4]);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		DEVICE_WRITE(strCmd);

	}

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestStartWFQMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;



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
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd);

		ICDMATestHandoverCall(iBand,iChan,d_CellPower[0],0);
		//strCellPower.Format("%.2f",d_CellPower[0]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		//strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
		//DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE ALT");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("SETUP:WQUALITY:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:WQUALITY:COUNT:NUMBER %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:WQUALITY:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:WQUALITY:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("INITIATE:WQUALITY:ON");
		DEVICE_WRITE(strCmd);
		Sleep(50);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(30);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("WQU")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:WQUALITY?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("A1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FEEDTHROUGH:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:EVM:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("B1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:EVM:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:EVM:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FERROR:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("C1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:FERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:FERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:MERROR:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("D1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:MERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:MERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:PERROR:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("E1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}	

		strCmd=_T("FETCH:WQUALITY:PERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:PERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:RHO:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("F1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:RHO:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:RHO:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:TERROR:AVERAGE?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		if (strTestItem.Find("G1")!=-1)
		{
			strVtrResult.push_back(strReadBuf);
		}

		strCmd=_T("FETCH:WQUALITY:TERROR:MAXIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("FETCH:WQUALITY:TERROR:MINIMUM?");
		DEVICE_QUERY(strCmd);

		strCmd=_T("INITIATE:WQUALITY:OFF");
		DEVICE_WRITE(strCmd);

	}

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestStartMaxPwrMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;

	if(strTestItem.Find("H1")!=-1)//MAX POWER
	{
		ICDMATestHandoverCall(iBand,iChan,d_CellPower[1],0);
		//strCellPower.Format("%.2f",d_CellPower[1]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:DAPOWER:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:DAPOWER:COUNT:NUMBER %d",iCountPwr);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:DAPOWER:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:DAPOWER:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		strCmd=_T("CALL:CLPC:REV:MODE UP");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}


		strCmd=_T("INITIATE:DAPOWER");
		DEVICE_WRITE(strCmd);
		Sleep(50);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(20);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("DAP")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:DAPOWER:ALL?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		strVtrResult.push_back(strReadBuf);

		strCmd=_T("INITIATE:DAPOWER:OFF");
		DEVICE_WRITE(strCmd);
	}

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestStartACPRMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;

	if (strTestItem.Find("I1")!=-1)//ACPR
	{
		ICDMATestHandoverCall(iBand,iChan,d_CellPower[1],0);
		//strCellPower.Format("%.2f",d_CellPower[1]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:DAPOWER:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:DAPOWER:COUNT:NUMBER %d",iCountPwr);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:DAPOWER:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:DAPOWER:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CTXSPURIOUS:COUNT:STATE ON");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CTXSPURIOUS:COUNT:NUMBER %d",BurstQty);
		DEVICE_WRITE(strCmd);

		strCmd=_T("SETUP:CTXSPURIOUS:CONTINUOUS OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("SETUP:CTXSPURIOUS:TIMEOUT:STIME %d",iTimeout);
		DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("CALL:CLPC:REV:MODE UP");
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("INITIATE:CTXSPURIOUS");
		DEVICE_WRITE(strCmd);
		Sleep(50);

		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd);
			strCmd=_T("INITIATE:DONE?");
			DEVICE_QUERY(strCmd);		
			Sleep(20);
			strReadBuf=Device_GetReadBuf();
			if(strReadBuf.Find("CTXS")!=-1)
			{
				break;
			}
		} while ( iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}

		strCmd=_T("FETCH:CTXSPURIOUS?");
		DEVICE_QUERY(strCmd);
		strReadBuf=Device_GetReadBuf();
		strVtrResult.push_back(strReadBuf);

		strCmd=_T("INITIATE:CTXSPURIOUS:OFF");
		DEVICE_WRITE(strCmd);

	}

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestStartMinPwrMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem)
{


	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestStartRxSenPreMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=30;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;

	if(strTestItem.Find("R1")!=-1)//RXSensitivityPrediction
	{
		iPwrSel=31;
		ICDMATestHandoverCall(iBand,iChan,d_CellPower[3],-15.6);

		//strCellPower.Format("%.2f",d_CellPower[3]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
	}

	return DEVICE_SUCCESS;
}


int CFuncCDMATest_8960::ICDMATestStartRXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=30;
	int iTimeout=10;
	int iCountPwr=4,iPwrSel=30;

	if(strTestItem.Find("R1")!=-1)//RXSensitivityPrediction
	{
		iPwrSel=31;
		ICDMATestHandoverCall(iBand,iChan,d_CellPower[3],-15.6);

		//strCellPower.Format("%.2f",d_CellPower[3]);
		//strCmd.Format(_T("CALL:CELL:POWER:AMPLITUDE %s"),strCellPower);
		//DEVICE_WRITE(strCmd);

		strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO OFF");
		DEVICE_WRITE(strCmd);

		strCmd.Format("RFANALYZER:MANUAL:POWER:SELECTED %d",iPwrSel);
		DEVICE_WRITE(strCmd);

		do 
		{
			strCmd=_T("*OPC?");
			DEVICE_QUERY(strCmd);
		} while (iDeviceErr!=DEVICE_SUCCESS && iRetryTimes-->0);

		if (iRetryTimes==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
	}

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestEndCall()
{
	int iDeviceErr;
	CString strCmd;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);

	//strCmd=_T("RFANALYZER:CONTROL:POWER:AUTO ON");
	//DEVICE_WRITE(strCmd);

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestStartRxLevelMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem,int iIndex)
{
//	int iDeviceErr;
	CString strCmd;
	ICDMATestHandoverCall(iBand,iChan,d_CellPower[iIndex],0);

	return DEVICE_SUCCESS;
}

int CFuncCDMATest_8960::ICDMATestSetLoss(int iCDMABand,const DblVtr & vLossList)
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

		switch(iCDMABand)
	{
		case 820:
			strCmd.Format("SYST:CORR:FREQ 824.85 MHZ,869.85 MHZ, 835.74 MHZ,880.74 MHZ, 848.22 MHZ,893.22 MHZ");
			DEVICE_WRITE(strCmd)

				strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 800:
			strCmd.Format("SYST:CORR:FREQ 824.85 MHZ,869.85 MHZ, 835.74 MHZ,880.74 MHZ, 848.22 MHZ,893.22 MHZ");
			DEVICE_WRITE(strCmd)

				strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 1900:
			strCmd.Format("SYST:CORR:FREQ 1851.25 MHZ,1931.25 MHZ, 1878.15 MHZ,1958.15 MHZ, 1908.75 MHZ,1988.75 MHZ");
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
