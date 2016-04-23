#include "StdAfx.h"
#include "FuncWCDMATest_8960.h"

CFuncWCDMATest_8960::CFuncWCDMATest_8960(void)
{
}

CFuncWCDMATest_8960::~CFuncWCDMATest_8960(void)
{
}

CFuncWCDMATest_8960::CFuncWCDMATest_8960(PCTesterDevice pDev):CFuncDev_8960(pDev)
{

}

int CFuncWCDMATest_8960::IWCDMATestInitWCDMAtest(const CString& strAddr)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	if (strRes.Find(_T("WCDMA"))==-1)
	{
		strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME 'WCDMA'");
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYSTEM:APPLICATION:FORMAT:NAME?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if(strRes.Find(_T("WCDMA"))==-1)
		{
			MessageBox(NULL,_T("Tester can NOT fast switch to WCDMA Mode"),_T("WARNING"),MB_OK);
			return DEVICE_NOTIN_FASTSWITCH;
		}
	}
	strCmd=_T("*RST");
	DEVICE_WRITE(strCmd)
		strCmd=_T("RFGENERATOR:OUTPUT:DESTINATION IO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:OPER:MODE OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PAG:SERV RBT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:LOOP:TYPE TYPE1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:DTCHANNEL:DATA PRBS15");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:SERV:RBT:RAB RMC12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:SCODE:PRIMARY 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:UPLINK:DPCHANNEL:SCODE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:UPL:PRAC:SCOD 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:UPL:PRAC:BETA:AUTO OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:UPLINK:DPCHANNEL:MANUAL:DBETA 15");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:RLC:REES OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:MCC:WCDM 1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:MNC:WCDM 1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:LAC:WCDM 30865");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:ATTF:STAT ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PAG:REP:STAT:SEL OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:SRB:CCH:DED:DRAT BPS13600");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CPIC:LEV -3.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CCPC:PRIM:LEV -5.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:DPCH:LEV -10.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:PICH:LEV -8.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:DPCH:RMC12:CCOD CODE9");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:SERV:RBT:RAB RMC12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CCPCHANNEL:SECONDARY:CCODE CODE7");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:AICHANNEL:CCODE CODE10");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PICHANNEL:CCODE CODE16");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:UINT -101");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:UPL:PRAC:PRE:NUMB 4");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:UPL:PRAC:POW:STEP:LEV 3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CVAL -10");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:PCTP 28");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:OPER:MODE FDDT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:UPL:TFCI:CONT:AUTO ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:TFCI '3'");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:SERV:RBT:DTCH:CRC PRES");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WACL:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WBER:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WWQ:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WOBW:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WCP:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WSEM:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL1:POWER:STATE ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	int i=10;
		do 
		{
			DEVICE_QUERY(strCmd)
				Sleep(50);
				strRes=Device_GetReadBuf();
			iRes=CStr::StrToInt(strRes);
		} while (iRes!=1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestSetBand(CString& strBand)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestSetChannel(int iChannel)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("CALL:UPLINK:CHANNEL %d",iChannel);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	int i=10;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestSetPower(const double dCellPower,const double dTargetPower,const int iPowerCtrlBit)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.2f",dCellPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	int i=10;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd.Format("CALL:MS:POWER:TARGET:AMPLITUDE %.2f",dTargetPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPC:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
	switch (iPowerCtrlBit)
	{
	case 0:
		strCmd=_T("CALL:FDDT:CLPC:UPL:MODE DOWN");
		break;
	case 1:
		strCmd=_T("CALL:FDDT:CLPC:UPL:MODE UP");
		break;
	case 2:
		strCmd=_T("CALL:FDDT:CLPC:UPL:MODE UDOWN");
		break;
	default:
		strCmd=_T("CALL:FDDT:CLPC:UPL:MODE ACT");
	}
	DEVICE_WRITE(strCmd)
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestHandOver(int iBand,int iULChannel)
{
	CString strCmd;
	int iDeviceErr,iRes,iSetDLChannel;
	CString strRes;
	iSetDLChannel=CWCDMABandInfo::GetDLChannel(iBand,iULChannel);
	strCmd.Format("CALL:UPLINK:CHANNEL %d",iULChannel);
	DEVICE_WRITE(strCmd)
		strCmd.Format("CALL:CHANNEL %d",iSetDLChannel);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	int i=10;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestMaxPower(int icount,double *dMaxPower)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE UP");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		strCmd=_T("SET:WCP:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WCP:COUN %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:INT:TIME 666.7US");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:TRIG:SOUR ATUO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:FILT ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WCP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("FETCH:WCP:INT?");
	int i=10;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=0&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("FETCH:WCP:POWER:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dMaxPower=CStr::StrToFloat(strRes);
	strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestMinPower(int icount,double *dMinPower)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE -55");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE DOWN");
	DEVICE_WRITE(strCmd)
		Sleep(500);
		strCmd=_T("SET:WCP:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WCP:COUN %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:INT:TIME 666.7US");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:TRIG:SOUR AUTO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:FILT ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WCP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INITIATE:DONE?");
	int i=10;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=0&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("FETCH:WCP:POWER:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dMinPower=CStr::StrToFloat(strRes);
	strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WCP:OFF");
	DEVICE_WRITE(strCmd)
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestPower(int icount,double TargetPower,double *dMeasPower)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestWCDomain(int icount,double dWCDValue[])
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestACLR(int icount,double dACLRValue[])
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE UP");
	DEVICE_WRITE(strCmd)
		Sleep(50);
	strCmd=_T("SET:WACLEAKAGE:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WACLEAKAGE:COUN %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WACL;*OPC");
	DEVICE_WRITE(strCmd)
	int i=50;
	do 
	{
		strCmd=_T("*CLS");
		Sleep(15);
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WACLEAKAGE:AVERAGE:ALL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::StrToDblArr(strRes,dACLRValue,_T(","),4);
	double dBuff;
	dBuff=dACLRValue[0];
	dACLRValue[0]=dACLRValue[2];
	dACLRValue[2]=dACLRValue[1];
	dACLRValue[1]=dBuff;
	strCmd=_T("INIT:WACL:OFF");
	DEVICE_WRITE(strCmd)
		
	strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestOBW(int icount,double *dOBWValue)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE UP");
	DEVICE_WRITE(strCmd)
		Sleep(50);
	strCmd.Format("SET:WOBWIDTH:COUNT:SNUMBER %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WOBWIDTH:PERCENT:TOTAL:POWER 99");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WOBW;*OPC");
	DEVICE_WRITE(strCmd);
	int i=50;
	do 
	{
		strCmd=_T("*CLS");
		Sleep(50);
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WOBWIDTH:BANDWIDTH:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dOBWValue=CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WOBW:OFF");
	DEVICE_WRITE(strCmd)

		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)
	
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestSEMask(int icount,int *iSMASK)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE UP");
	DEVICE_WRITE(strCmd)
		Sleep(50);
	strCmd.Format("SET:WSEMASK:COUNT:SNUMBER %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WSEMASK;*OPC");
	DEVICE_WRITE(strCmd);
	int i=50;
	do 
	{
		strCmd=_T("*CLS");
		Sleep(50);
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WSEMASK:FAIL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	double dRes[2]={1,1};
	*iSMASK=0;
	CStr::StrToDblArr(strRes,dRes,_T(","),2);
	if (dRes[1]<1)
	{
		*iSMASK=1;
	}
	strCmd=_T("INIT:WSEM:OFF");
	DEVICE_WRITE(strCmd)

		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)

	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestBER(int iSample,double dCellPower,double *dBER)
{
	CString strCmd;
	int iDeviceErr,iRes=0;
	CString strRes;
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -100");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE UP");
	DEVICE_WRITE(strCmd)
		Sleep(50);
	strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.2f",dCellPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WBER:TIM 15");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WBERROR:CONTINUOUS OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SETUP:WBERROR:COUNT %d",iSample);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WCP:COUN 20");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:INT:TIME 666.7US");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:TRIG:SOUR AUTO");
	DEVICE_WRITE(strCmd)

		strCmd=_T("SET:WCP:FILT ON");
	DEVICE_WRITE(strCmd)
	//*********************************************Target power Unit=dBm
		strCmd=_T("INIT:WCP;*OPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)

		strCmd=_T("INITIATE:DONE?");
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();
	} while (strRes.Find(_T("WAIT"))> -1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("FETCH:WCP:POWER:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	double dpower=CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WCP:OFF");
	DEVICE_WRITE(strCmd)

		strCmd=_T("INIT:WBER;*OPC");
	DEVICE_WRITE(strCmd)
	i=80;
	do 
	{
		strCmd=_T("*CLS");
		Sleep(50);
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=("FETCH:WBER:INT?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	iRes=CStr::StrToInt(strRes);
	if (iRes!=0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WBERROR:RATIO?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dBER= CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WBER:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75;*OPC");
	DEVICE_WRITE(strCmd)

		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestCPICH_RSCP(double dCellPower,double *iCPICH_RSCP)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestILPC_FailSlot(int *iResultStepE,int *iResultStepF,double * dFailSlotPower_E,double * dFailSlotPower_F,int *iNUM_E,int *iNUM_F)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
    DblVtr dILPC_ABPwrVtr;
     DblVtr dILPC_DeltaPwrVtr;
	 CStringVtr vtrString;
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:MAXimum:POWer:THReshold:TEST:CONTrol:AUTO ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:MAXimum:OUTPut:POWer:TEST:TOLerance 0.7");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:Minimum:POWer:THReshold:TEST:CONTrol:AUTO OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:Minimum:POWer:THReshold:TEST:MANual -49");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:SEGment E");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WILPower");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INITIATE:DONE?");
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WILPower?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	double dRes[2]={1,1};
	CStr::StrToDblArr(strRes,dRes,_T(","),2);
	if (dRes[0]+dRes[1]==0)
	{
		*iResultStepE=1;
	}
	else
	{
		   *iResultStepE=0;
		   dILPC_ABPwrVtr.clear();
		   double dDelta;
		   int iFailSlotsNum=0;
		   int iFailIndex=0;
		   strCmd=_T("FETCh:WILPower:TRACe?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,",",vtrString);
		CStr::StrVtr2DblVtr(dILPC_ABPwrVtr,vtrString);

			for(int i=0;i<dILPC_ABPwrVtr.size() && dILPC_ABPwrVtr[i]>-49;++i)
			{
				 if(dILPC_ABPwrVtr[i]>20)
					 continue;
                 dDelta=dILPC_ABPwrVtr[i]-dILPC_ABPwrVtr[i+1];
				 if(dDelta>1.6 || dDelta<0.4)
				 {
                     if(i-iFailIndex==1)
					 {
						 iFailIndex=i;
						 continue;
					 }
                     iFailSlotsNum+=5;
					 for(int j=0;j<5;++j)
                     dFailSlotPower_E[j]=dILPC_ABPwrVtr[i-1+j];

				 }

                 
               
			}

			*iNUM_E=iFailSlotsNum;
	}

	strCmd=_T("SETup:WILPower:SEGment F");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WILPower");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INITIATE:DONE?");
	i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WILPower?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::StrToDblArr(strRes,dRes,_T(","),2);
	if (dRes[0]+dRes[1]==0)
	{
		*iResultStepF=1;
	}
	else
	{
		   *iResultStepF=0;
		   dILPC_ABPwrVtr.clear();
		   double dDelta;
		   int iFailSlotsNum=0;
		   int iFailIndex=0;
		   strCmd=_T("FETCh:WILPower:TRACe?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		CStr::ParseString(strRes,",",vtrString);
		CStr::StrVtr2DblVtr(dILPC_ABPwrVtr,vtrString);

			for(int i=0;i<dILPC_ABPwrVtr.size() && dILPC_ABPwrVtr[i]<20;++i)
			{
				 if(dILPC_ABPwrVtr[i]<-49)
					 continue;
                 dDelta=dILPC_ABPwrVtr[i+1]-dILPC_ABPwrVtr[i];
				 if(dDelta>1.6 || dDelta<0.4)
				 {
                     if(i-iFailIndex==1)
					 {
						 iFailIndex=i;
						 continue;
					 }
                     iFailSlotsNum+=5;
					 for(int j=0;j<5;++j)
                     dFailSlotPower_F[j]=dILPC_ABPwrVtr[i-1+j];

				 }

                 

			}

			*iNUM_F=iFailSlotsNum;
	}

	return DEVICE_SUCCESS;
    
}
int CFuncWCDMATest_8960::IWCDMATestILPC(int *iResultStepE,int *iResultStepF)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	*iResultStepE=0;
	*iResultStepF=0;
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:MAXimum:POWer:THReshold:TEST:CONTrol:AUTO ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:MAXimum:OUTPut:POWer:TEST:TOLerance 0.7");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:Minimum:POWer:THReshold:TEST:CONTrol:AUTO OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SETup:WILPower:Minimum:POWer:THReshold:TEST:MANual -49");
	DEVICE_WRITE(strCmd)
	int iRetryTime=3;
	do 
	{
		strCmd=_T("SETup:WILPower:SEGment E");
		DEVICE_WRITE(strCmd)
			strCmd=_T("INIT:WILPower");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		int i=50;
		do 
		{
			DEVICE_QUERY(strCmd)
				Sleep(50);
			strRes=Device_GetReadBuf();

		} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
		if (i==0)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("FETCH:WILPower?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		double dRes[2]={1,1};
		CStr::StrToDblArr(strRes,dRes,_T(","),2);
		if (dRes[0]+dRes[1]==0)
		{
			*iResultStepE=1;
		}
	} while (0==*iResultStepE&&0<iRetryTime--);
		

	iRetryTime=3;
	do 
	{
		strCmd=_T("SETup:WILPower:SEGment F");
		DEVICE_WRITE(strCmd)
			strCmd=_T("INIT:WILPower");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		int i=50;
		do 
		{
			DEVICE_QUERY(strCmd)
				Sleep(50);
			strRes=Device_GetReadBuf();

		} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
		if (i==0)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("FETCH:WILPower?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		double dRes[2]={1,1};
		CStr::StrToDblArr(strRes,dRes,_T(","),2);
		if (dRes[0]+dRes[1]==0)
		{
			*iResultStepF=1;
		}
	} while (0==*iResultStepF&&0<iRetryTime--);

	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestSetLoss(int iWCDMABand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	switch(iWCDMABand)
	{
	case 1800:
		strCmd.Format("SYST:CORR:FREQ 1807.6 MHZ,1712.6 MHZ, 1840 MHZ,1745 MHZ, 1877.4 MHZ,1782.4 MHZ");
		DEVICE_WRITE(strCmd)

			strCmd.Format("SYST:CORR:GAIN %f,%f,%f,%f,%f,%f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		break;

			break;
	case 2100:
		strCmd=_T("SYST:CORR:SFR 2112.6 MHZ,1922.6MHZ,2140 MHZ,1950 MHZ,2167.4MHZ,1977.4MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 1900:
		strCmd=_T("SYST:CORR:SFR 1854.2 MHZ,1934.2 MHZ,1880 MHZ,1960 MHZ,1906.6 MHZ,1986.6 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 1500:
		strCmd=_T("SYST:CORR:SFR 1478.4 MHZ,1430.4 MHZ,1486 MHZ,1438 MHZ,1493.4 MHZ,1445.4 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 900:
		strCmd=_T("SYST:CORR:SFR 882.4 MHZ,927.4 MHZ,897.6 MHZ,942.6 MHZ,912.6 MHZ,957.6 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
		DEVICE_WRITE(strCmd)
			break;
	case 850:
		strCmd=_T("SYST:CORR:SFR 871.4 MHZ,826.4 MHZ,880 MHZ,835 MHZ,891.6 MHZ,846.6 MHZ");
		DEVICE_WRITE(strCmd)
			strCmd.Format("SYST:CORR:GAIN %.2f,%.2f,%.2f,%.2f,%.2f,%.2f",-vLossList[0],-vLossList[0],-vLossList[1],-vLossList[1],-vLossList[2],-vLossList[2]);
		DEVICE_WRITE(strCmd)
			strCmd=_T("SYST:CORR:STATE ON");
			break;
	default:
		return DEVICE_WRITE_FAIL;
	}
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestModAnalysis(const int icount,const double dTargetPower,double  *dPowerValue,double dModValue[])
{
	///Error Vector Magnitude  Unit=%
	//Peak Vector Error Unit=%
	///Phase Error Unit=deg
	///Magnitude Error Unit=%
	///Origin Offset Unit=dB
	//IQ Imbalance Unit=%
	///Timing Error Unit=chip
	//DPCCH/DPDCH Power Ratio Unit=dB

	CString strCmd;
	int iDeviceErr;
	CString strRes;
	memset(dModValue,0,8);
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
	strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
	strCmd.Format("CALL:MS:POWER:TARGET:AMPLITUDE %.2f",dTargetPower);
	DEVICE_WRITE(strCmd)
		Sleep(100);
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE UDOWN");
	DEVICE_WRITE(strCmd)
			strCmd=_T("SET:WCP:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WCP:COUN %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:INT:TIME 666.7US");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:TRIG:SOUR AUTO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WWQ:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WWQ:COUN %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:FILT ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WCP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INITIATE:DONE?");
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("FETCH:WCP:POWER:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dPowerValue=CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WCP:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INIT:WWQ");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INITIATE:DONE?");
	i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(15);
		strRes=Device_GetReadBuf();
	
	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WWQUALITY:EVM:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[0]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:PERROR:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[2]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:MERROR:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[3]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:OOFFSET:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[4]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:TERROR:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[6]=CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WWQ:OFF");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8960::IWCDMATestMeasAll(const int icount,const int iSample,double dCellPower,double  *dPowerValue,double dModValue[],	double dACLR[],double *dOBWValue,int *iSMASK,double *dBER,double *dFER)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRes;
	memset(dModValue,0,8);
	strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE UP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE 24");
	DEVICE_WRITE(strCmd)
		Sleep(500);
		strCmd=_T("SET:WACLEAKAGE:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WACLEAKAGE:COUN %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WOBWIDTH:COUNT:SNUMBER %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WOBWIDTH:PERCENT:TOTAL:POWER 99");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WSEMASK:COUNT:SNUMBER %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WBER:TIM 15");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WBERROR:CONTINUOUS OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SETUP:WBERROR:COUNT %d",iSample);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WCP:COUN %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:INT:TIME 666.7US");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:TRIG:SOUR AUTO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WWQ:CONT OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SET:WWQ:COUN %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SET:WCP:FILT ON");
	DEVICE_WRITE(strCmd)
	//*********************************************Target power Unit=dBm
		strCmd=_T("INIT:WCP;*OPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)

		strCmd=_T("INITIATE:DONE?");
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();
	} while (strRes.Find(_T("WAIT"))> -1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	strCmd=_T("FETCH:WCP:POWER:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dPowerValue=CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WCP:OFF");
	DEVICE_WRITE(strCmd)
//****************************************************Mod Analysis
		strCmd=_T("INIT:WWQ;*OPC");
	DEVICE_WRITE(strCmd)
		Sleep(500);
		strCmd=_T("INITIATE:DONE?");
	 i=50;
	 do 
	 {
		 DEVICE_QUERY(strCmd)
			 Sleep(50);
		 strRes=Device_GetReadBuf();

	 } while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WWQUALITY:EVM:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[0]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:PERROR:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[2]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:MERROR:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[3]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:OOFFSET:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[4]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:TERROR:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[6]=CStr::StrToFloat(strRes);
	strCmd=_T("FETCH:WWQUALITY:FERROR:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dFER=CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WWQ:OFF");
	DEVICE_WRITE(strCmd)
	//************************************************************ACLR Test
	strCmd=_T("INIT:WACL;*OPC");
	DEVICE_WRITE(strCmd)
	i=50;
	do 
	{
		strCmd=_T("*CLS");
		Sleep(50);
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		
	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WACLEAKAGE:AVERAGE:ALL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::StrToDblArr(strRes,dACLR,_T(","),4);
	double dBuff;
	dBuff=dACLR[0];
	dACLR[0]=dACLR[2];
	dACLR[2]=dACLR[1];
	dACLR[1]=dBuff;
	strCmd=_T("INIT:WACL:OFF");
	DEVICE_WRITE(strCmd)
	//**************************************************OBW Test unit= MHz
	strCmd=_T("INIT:WOBW;*OPC");
	DEVICE_WRITE(strCmd);
	i=50;
	do 
	{
		strCmd=_T("*CLS");
		Sleep(50);
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WOBWIDTH:BANDWIDTH:AVERAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dOBWValue=CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WOBW:OFF");
	DEVICE_WRITE(strCmd)
	//***************************************************Spectrum Emission Mask Test Pass:1,Fail:0
	strCmd=_T("INIT:WSEMASK;*OPC");
	DEVICE_WRITE(strCmd);
	i=50;
	do 
	{
		strCmd=_T("*CLS");
		Sleep(50);
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WSEMASK:FAIL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	double dRes[2]={1,1};
	*iSMASK=0;
	CStr::StrToDblArr(strRes,dRes,_T(","),2);
	if (dRes[1]<1)
	{
		*iSMASK=1;
	}
	strCmd=_T("INIT:WSEM:OFF");
	DEVICE_WRITE(strCmd)
		strCmd.Format("CALL:CELL:POWER:AMPLITUDE -100;*OPC");
	DEVICE_WRITE(strCmd)
		Sleep(200);

		strCmd.Format("CALL:CELL:POWER:AMPLITUDE %.2f;*OPC",dCellPower);
	DEVICE_WRITE(strCmd)
	Sleep(200);
	//********************************************************BER Test unit= %
	strCmd=_T("INIT:WBER;*OPC");
	DEVICE_WRITE(strCmd)
		i=10;
	do 
	{
		strCmd=_T("*CLS");
		Sleep(500);
		DEVICE_WRITE(strCmd)
			strCmd=_T("INITIATE:DONE?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	} while (strRes.Find(_T("WAIT"))>-1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=("FETCH:WBER:INT?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	iRes=CStr::StrToInt(strRes);
	if (iRes!=0)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("FETCH:WBERROR:RATIO?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dBER= CStr::StrToFloat(strRes);
	strCmd=_T("INIT:WBER:OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:CELL:POWER:AMPLITUDE -75;*OPC");
	DEVICE_WRITE(strCmd)
		Sleep(500);
		strCmd=_T("CALL:FDDT:CLPCONTROL:UPL:MODE ACT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALL:MS:POWER:TARGET:AMPLITUDE -10");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;
}
