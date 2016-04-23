#include "StdAfx.h"
#include "FuncWCDMATest_8820.h"

CFuncWCDMATest_8820::CFuncWCDMATest_8820(void)
{
}

CFuncWCDMATest_8820::~CFuncWCDMATest_8820(void)
{
}

CFuncWCDMATest_8820::CFuncWCDMATest_8820(PCTesterDevice pDev):CFuncDev_8820(pDev)
{

}
int CFuncWCDMATest_8820::IWCDMATestInitWCDMAtest(const CString& strAddr)
{
	CString strCmd;
	int iDeviceErr,iRes;

	CString strRes;

	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;


	 strCmd=_T("BANDCAL;*OPC");
	  DEVICE_WRITE(strCmd)

	  Sleep(100);

	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)

		strCmd=_T("CALLSO");
	DEVICE_WRITE(strCmd)

		strCmd=_T("STDSEL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();

	if(strRes.Find("WCDMA")==-1)
	{
		strCmd=_T("STDSEL WCDMA");
		DEVICE_WRITE(strCmd)

			Sleep(3000);

		strCmd=_T("STDSEL?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

		if(strRes.Find("WCDMA")==-1)
		{
			return  -99; 
		}

	}
	strCmd=_T("*RST;*OPC?");
	DEVICE_QUERY(strCmd)

	strCmd=_T("*CLS;*OPC?");
	DEVICE_QUERY(strCmd)

	if(m_pTesterDevice->m_bIsScreenOff)
	{
		strCmd=_T("SCREEN OFF");
		DEVICE_WRITE(strCmd)

		strCmd=_T("MEASMODE FAST");
		DEVICE_WRITE(strCmd)
	}
	else

	{
		strCmd=_T("SCREEN ON");
		DEVICE_WRITE(strCmd)

		strCmd=_T("MEASMODE NORM");
		DEVICE_WRITE(strCmd)
	}
	strCmd=_T("CALLPROC OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("BANDIND OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("DTCHPAT PN9");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ULCHAN 9750");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TESTMODE OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CHCODING REFMEASCH");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PRISCRCODE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("UNIT IOR");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CPICHPWR -3.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PCCPCH ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PCCPCHPWR -5.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SCH ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SCHPWR -5.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PICH ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PICHPWR -8.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PICHCODE 16");
	DEVICE_WRITE(strCmd)
		strCmd=_T("DDPCH ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("DDPCHPWR -10.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("DDPCHSASSCRCODE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("DDPCHSSCRCODE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("DDPCHSACODE 9");
	DEVICE_WRITE(strCmd)
		strCmd=_T("DDPCHCODE 9");
	DEVICE_WRITE(strCmd)
		strCmd=_T("DDPCHTOFS 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SCCPCH ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SCCPCHPWR -10.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SCCPCHTOFS 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SCCPCHCODE 7");
	DEVICE_WRITE(strCmd)
		strCmd=_T("AICH ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("AICHPWR -8.3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("AICHCODE 10");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PRACHSCRCODE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("UDPCHSCRCODE 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("UDPCHTYPE LONG");
	DEVICE_WRITE(strCmd)
		strCmd=_T("UDPCCHBETAC 8");
	DEVICE_WRITE(strCmd)
		strCmd=_T("UDPDCHBETAD 15");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCALGO 2");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCSTEP 1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ILPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("MCC 001");
	DEVICE_WRITE(strCmd)
		strCmd=_T("MNC 01");
	DEVICE_WRITE(strCmd)
		strCmd=_T("MAXULPWR 33");
	DEVICE_WRITE(strCmd)
		strCmd=_T("INTERFERENCE -101");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PREAMRET 4");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PWROFS 3");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONSTANT -10");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CPICHTXPWR 28");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -65");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ALLMEASITEMS_OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);


		return DEVICE_SUCCESS;


	
}
int CFuncWCDMATest_8820::IWCDMATestSetChannel(int iChannel)
{
	CString strCmd,strRes;
	int iDeviceErr,iRes;
	strCmd.Format("ULCHAN %d;*OPC?",iChannel);
	DEVICE_QUERY(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::IWCDMATestHandOver(int iBand,int iULChannel)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRes;
	double UlFreq=CWCDMABandInfo::ArfcnToHz(iBand,iULChannel,1);
	double DlFreq=CWCDMABandInfo::ArfcnToHz(iBand,CWCDMABandInfo::GetDLChannel(iBand,iULChannel),0);

	strCmd.Format("ULFREQ %0.2fMHz;*OPC?",UlFreq);
	DEVICE_QUERY (strCmd)

		strCmd.Format("DLFREQ %0.2fMHz;*OPC?",DlFreq);
	DEVICE_QUERY(strCmd)
/*
	strCmd.Format("ULCHAN %d",iULChannel);
	DEVICE_WRITE(strCmd)*/
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
		return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8820::ITDSCDMAHandOver(int iBand,int iULChannel)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRes;
	strCmd.Format("MEASSTOP");
	DEVICE_WRITE(strCmd)
		strCmd.Format("ALLMEASITEMS_OFF");
	DEVICE_WRITE(strCmd)
	strCmd.Format("CHAN %d",iULChannel);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMASetPower(const double dCellPower,const double dTargetPower,const int iPowerCtrlBit)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRes;
	strCmd.Format("OLVL %.2f",dCellPower);
	DEVICE_WRITE(strCmd)
		strCmd.Format("ILVL %.2f",dTargetPower);
	DEVICE_WRITE(strCmd)
		switch (iPowerCtrlBit)
	{
		case 0:
			strCmd=_T("TPCPAT ALL0");
			DEVICE_WRITE(strCmd)
				break;
		case 1:
			strCmd=_T("TPCPAT ALL1");
			DEVICE_WRITE(strCmd)
				break;
		case 2:
			strCmd=_T("TPCPAT CLPC");
			DEVICE_WRITE(strCmd)
				break;
		default:
			strCmd=_T("TPCPAT CLPC");
			DEVICE_WRITE(strCmd)
				break;
	}
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8820::IWCDMATestSetBand(CString& strBand)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8820::IWCDMATestMaxPower(int icount,double *dMaxPower)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		int i=50;
	strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<i--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
		strCmd=_T("AVG_FILTPWR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dMaxPower=CStr::StrToFloat(strRes);
	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;	
}
int CFuncWCDMATest_8820::ITDSCDMAMaxPower(int icount,double *dMaxPower)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iQueryTimes=10;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 24");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -65");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		strCmd=_T("MEASOBJ DPCH");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("AVG_POWER?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dMaxPower=CStr::StrToFloat(strRes);
	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;

}

int CFuncWCDMATest_8820::ITDSCDMAMinPower(int icount,double *dMinPower)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iQueryTimes=10;
	double dILVL= -50;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL -50");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -100");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALLDROP OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL0");
	DEVICE_WRITE(strCmd)
		Sleep(100);
		strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (0==strRes.Find("2"))
		{
			dILVL+=10;
			strCmd.Format("ILVL %.2f",dILVL);
			DEVICE_WRITE(strCmd)
				strCmd=_T("SWP");
			DEVICE_WRITE(strCmd)
				strCmd=_T("TXMSTAT?");
		}

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("AVG_POWER?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dMinPower=CStr::StrToFloat(strRes);
	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL -30");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALLDROP ON");
	DEVICE_WRITE(strCmd)		

		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMACLPC(const int icount,bool *bResult)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iQueryTimes=10,iRetryTime=0;	
	strCmd=_T("ILVL 20");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -75");
	DEVICE_WRITE(strCmd)
	strCmd=_T("TESTPRM CALL_CLPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CLPC_MEAS AUTO_BC");
	DEVICE_WRITE(strCmd)
	do 
	{
		iQueryTimes=10;
		*bResult=true;
		strCmd=_T("SWP");
		DEVICE_WRITE(strCmd)
			strCmd=_T("TXMSTAT?");
		do
		{
			Sleep(20);
			DEVICE_QUERY(strCmd)
				strRes=Device_GetReadBuf();

		}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
		if (0!=strRes.Find("0"))
		{
			return DEVICE_FINDRES_FAIL;
		}
		strCmd=_T("CLPC_PASS? B");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (strRes.Find("PASS")==-1)
		{
			*bResult=false;
		}
		strCmd=_T("CLPC_PASS? C");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (strRes.Find("PASS")==-1)
		{
			*bResult=false;
		}
	} while (*bResult==false&&++iRetryTime<3);
		
	
	
	strCmd=_T("TESTPRM NORMAL");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL -30");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALLDROP ON");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMAFreqErr(int icount,double dCellPower,double *dFER)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iQueryTimes=10;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 23");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -90");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		//strCmd=_T("OLVL -104");   
		strCmd.Format("OLVL %.2f",dCellPower);
	DEVICE_WRITE(strCmd)		
		Sleep(100);
	strCmd=_T("FREQ_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("FREQ_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}

		strCmd=_T("AVG_CARRFERR? PPM");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dFER=CStr::StrToFloat(strRes);
	strCmd=_T("FREQ_MEAS OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL -30");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALLDROP ON");
	DEVICE_WRITE(strCmd)		

		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMAPeakCDP(const int icount,double *dPCDErr)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iQueryTimes=10;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 23");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -65");
	DEVICE_WRITE(strCmd)	
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		Sleep(50);
	strCmd=_T("PCDE_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PCDE_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}

	strCmd=_T("AVG_PCDERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dPCDErr=CStr::StrToFloat(strRes);
	strCmd=_T("PCDE_MEAS OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL -30");
	DEVICE_WRITE(strCmd)		

		return DEVICE_SUCCESS;

}
INT CFuncWCDMATest_8820::ITDSCDMAACLR(const int icount,double dACLRValue[])
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iQueryTimes=10;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 24");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -65");
	DEVICE_WRITE(strCmd)		
		Sleep(500);
	strCmd=_T("ADJ_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("ADJ_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}

	strCmd=_T("AVG_MODPWR? LOW16");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dACLRValue[0]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_MODPWR? UP16");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dACLRValue[1]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_MODPWR? LOW32");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dACLRValue[2]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_MODPWR? UP32");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dACLRValue[3]=CStr::StrToFloat(strRes);

	strCmd=_T("ADJ_MEAS OFF");
	DEVICE_WRITE(strCmd)		
		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMAOBW(const int icount,double *dOBWValue)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iQueryTimes=10;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 23");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -65");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		Sleep(50);
	strCmd=_T("OBW_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("OBW_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}

	strCmd=_T("OBW?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dOBWValue=CStr::StrToFloat(strRes)/1000000;

	
	strCmd=_T("OBW_MEAS OFF");
	DEVICE_WRITE(strCmd)	
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;

}
INT CFuncWCDMATest_8820::ITDSCDMASEMask(const int icount,int *isPass,double dSEMask[])
{
	CString strCmd;
	CString strRes;
	DblVtr dvSEMASK;
	CStringVtr strVtr; 
	int iDeviceErr,iQueryTimes=10;
	*isPass=0;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 23");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -65");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		Sleep(50);
	strCmd=_T("SMASK_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SMASK_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}

	strCmd=_T("SMASKPASS?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	if (-1!=strRes.Find("PASS"))
	{
		*isPass=1;
	}
	strCmd=_T("TTL_WORST_SMASK?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	CStr::ParseString(strRes,",",strVtr);
	CStr::StrVtr2DblVtr(dvSEMASK,strVtr);
	dSEMask[0]=-dvSEMASK[0];
	dSEMask[1]=-dvSEMASK[2];
	dSEMask[2]=-dvSEMASK[4];
	dSEMask[3]=-dvSEMASK[6];

	strCmd=_T("SMASK_MEAS OFF");
	DEVICE_WRITE(strCmd)	
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMAPwrTemplate(const int icount,double dPTValue[])
{
	CString strCmd;
	CString strRes;
	DblVtr dvSEMASK;
	CStringVtr strVtr; 
	int iDeviceErr,iQueryTimes=10;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL -30");

	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -90");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		strCmd=_T("OLVL -100");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		Sleep(50);
	strCmd=_T("PWRTEMP_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PWRTEMP_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("AVG_OFFPWRM?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dPTValue[0]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_OFFPWRP?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dPTValue[1]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_M50PWR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dPTValue[2]=CStr::StrToFloat(strRes);

	strCmd=_T("PWRTEMP_MEAS OFF");
	DEVICE_WRITE(strCmd)	
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMABER(const int iSample,double dCellPower,double *dBER)
{
	CString strCmd;
	CString strRes;
	DblVtr dvSEMASK;
	CStringVtr strVtr; 
	int iDeviceErr,iQueryTimes=10;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -100");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 23");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		strCmd.Format("OLVL %.2f",dCellPower);
	DEVICE_WRITE(strCmd)
		
	
		strCmd.Format("BER_SAMPLE %d",iSample);
	DEVICE_WRITE(strCmd)
		strCmd=_T("CONF_MEAS OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("BER_LIMIT 0.1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("RX_TIMEOUT 15");
	DEVICE_WRITE(strCmd)
		strCmd=_T("BER_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("RXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("BER? PER");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dBER=CStr::StrToFloat(strRes);

	

	strCmd=_T("BER_MEAS OFF");
	DEVICE_WRITE(strCmd)	
		strCmd=_T("TPCPAT CLPC");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMAModAnalysis(const int icount,double *dRho,double *dEVM,double *dPVE,double *dPhaseErr,double *dMagErr,double *dOgnOfst,double *dIQI)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iQueryTimes=10;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 19.5");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -65");
	DEVICE_WRITE(strCmd)		
		Sleep(50);
	strCmd=_T("MOD_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("MOD_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}

	strCmd=_T("AVG_EVM?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dEVM=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_PVECTERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dPVE=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_MAGTDERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dMagErr=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_PHASEERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dPhaseErr=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_ORGNOFS?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dOgnOfst=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_IQIMB?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dIQI=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_RHO?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dRho=CStr::StrToFloat(strRes);

	strCmd=_T("MOD_MEAS OFF");
	DEVICE_WRITE(strCmd)		

		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::IWCDMATestMinPower(int icount,double *dMinPower)
{
	CString strCmd;
	CString strRes;
	int iRes;
	int iDeviceErr;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL -55");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL0");
	DEVICE_WRITE(strCmd)
		Sleep(300);
		strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
	
	int i=50;
	do 
	{
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd)
		strCmd=_T("SWP?");
		DEVICE_QUERY(strCmd)
		Sleep(50);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=0&&--i>0);
/*
	i=50;
	do 
	{
			strCmd=_T("TXMSTAT?");
		DEVICE_QUERY(strCmd)
			Sleep(50);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=0&&--i>0);*/
		strCmd=_T("AVG_FILTPWR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dMinPower=CStr::StrToFloat(strRes);
	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 0");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ILPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALT");
	DEVICE_WRITE(strCmd)


		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::IWCDMATestPower(int icount,double TargetPower,double *dMeasPower)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd.Format("ILVL %.2f",TargetPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<i--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
		strCmd=_T("AVG_FILTPWR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dMeasPower=CStr::StrToFloat(strRes);
	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;
}
	/*
		  EVM_max=WCDValue[1];
		  Frequency_error_max=W_CDValue[2];
		  Origin_offset_max=W_CDValue[3];
		  Phase_error_max=W_CDValue[4];
		  Timing_error_max=W_CDValue[5];
		  Mag_error_max=W_CDValue[6];
		  Peak_code_domain_error_max=W_CDValue[7];
*/
int CFuncWCDMATest_8820::IWCDMATestWCDomain(int icount,double dWCDValue[])
{
	/*
		  EVM_max=WCDValue[1];
		  Frequency_error_max=W_CDValue[2];
		  Origin_offset_max=W_CDValue[3];
		  Phase_error_max=W_CDValue[4];
		  Timing_error_max=W_CDValue[5];
		  Mag_error_max=W_CDValue[6];
		  Peak_code_domain_error_max=W_CDValue[7];
*/
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("FREQ_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("FREQ_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("MOD_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("MOD_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("PCDE_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PCDE_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("RCDE_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("RCDE_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<i--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
		strCmd=_T("MAX_CARRFERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dWCDValue[2]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_ORGNOFS?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dWCDValue[3]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_PHASEERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dWCDValue[4]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_TMGERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dWCDValue[5]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_MAGTDERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dWCDValue[6]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_EVM?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dWCDValue[1]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_PCDERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dWCDValue[7]=CStr::StrToFloat(strRes);

	strCmd=_T("ALLMEASITEMS_OFF");
	DEVICE_WRITE(strCmd)
		
		return DEVICE_SUCCESS;

}

int CFuncWCDMATest_8820::IWCDMATestOBW(int icount,double *dOBWValue)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	double dOBW;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OBW_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("OBW_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<i--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
		strCmd=_T("OBW?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dOBW=CStr::StrToFloat(strRes);
	*dOBWValue=dOBW/(1000000);
	strCmd=_T("OBW_MEAS OFF");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::IWCDMATestACLR(int icount,double dACLRValue[])
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	for (int i=0;i<4;i++)
	{
       dACLRValue[i]=0;
	}
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		Sleep(500);
		strCmd=_T("ADJ_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("ADJ_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
	int i=50,iRes=-1;
	do 
	{
		strCmd=_T("*CLS");
		DEVICE_WRITE(strCmd)
			strCmd=_T("SWP?");
		Device_Query(strCmd,15);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=0&&--i>0);
	if (0!=iRes)
	{
		return DEVICE_FINDRES_FAIL;
	}
	
		strCmd=_T("AVG_MODPWR? LOW10");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dACLRValue[0]=CStr::StrToFloat(strRes);		
		
		strCmd=_T("AVG_MODPWR? LOW5");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dACLRValue[1]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_MODPWR? UP5");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dACLRValue[2]=CStr::StrToFloat(strRes);

	strCmd=_T("AVG_MODPWR? UP10");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dACLRValue[3]=CStr::StrToFloat(strRes);

	strCmd=_T("ADJ_MEAS OFF");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;

}

int CFuncWCDMATest_8820::IWCDMATestSEMask(int icount,int *iSMASK)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SMASK_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("SMASK_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_WRITE(strCmd)
		int i=50;
	strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<i--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	strCmd=_T("SMASKPASS?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*iSMASK=0;
	if (strRes.Find(_T("PASS"))>-1)
	{
		*iSMASK=1;
	}
	strCmd=_T("SMASK_MEAS OFF");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::IWCDMATestBER(int iSample,double dCellPower,double *dBER)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -100");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		strCmd.Format("OLVL %0.2f",dCellPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("BER_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("BER_SAMPLE %d",iSample);
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
		int iQueryTimes=50;
		strCmd=_T("RXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (-1<strRes.Find("13"))
		{
			return DEVICE_FINDRES_FAIL;
		}

	}while((0!=strRes.Find("0"))&&(0<iQueryTimes--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
		strCmd=_T("BER?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*dBER=CStr::StrToFloat(strRes);
		strCmd=_T("BER_MEAS OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -75");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::IWCDMATestCPICH_RSCP(double dCellPower,double *iCPICH_RSCP)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr,iRes;
	int iReceiveFlag=0,iTimeOut=0;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		Sleep(500);
		strCmd.Format("OLVL %0.2f",dCellPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		i=50;
		do 
		{
			Sleep(20);
			strRes=Device_GetReadBuf();
			iRes=CStr::StrToInt(strRes);
		} while (iRes!=1&&--i>0);
		strCmd=_T("MEASREP ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALLRFR");
	DEVICE_WRITE(strCmd)
	do 
	{
		Sleep(1000);
		strCmd=_T("CPICH_RSCP? FLAG");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		iReceiveFlag=CStr::StrToInt(strRes);
		iTimeOut++;
	} while ((iReceiveFlag!=1)&&(iTimeOut<6));
	if (iTimeOut==6) return ERR_DEVICE_WCDMATEST_RSCP_NORECEIVES;
	strCmd=_T("CPICH_RSCP?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	*iCPICH_RSCP=CStr::StrToFloat(strRes);
	strCmd=_T("MEASREP OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OLVL -75");
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;
	
}
/*
	ALL	iItem[0]	iILPCRusult[0]
	A	iItem[1]	iILPCRusult[1]
	B	iItem[2]	iILPCRusult[2]
	C	iItem[3]	iILPCRusult[3]
	E	iItem[4]	iILPCRusult[4]
	F	iItem[5]	iILPCRusult[5]
	G	iItem[6]	iILPCRusult[6]
	H	iItem[7]	iILPCRusult[7]
	*/
int CFuncWCDMATest_8820::IWCDMATestILPC(int *iResultStepE,int *iResultStepF)
{
	
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	int iMSTAT=-1,iTimeOut=0;
	*iResultStepE=0;
	*iResultStepF=0;
	strCmd=_T("SCRSEL TDMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ILPC");
	DEVICE_WRITE(strCmd)


		strCmd=_T("TDM_RRC OFF");
	DEVICE_WRITE(strCmd)


		Sleep(50);
		strCmd=_T("MEASOBJ ILPC_AUTO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILPC_MEAS AUTO_EF");
	DEVICE_WRITE(strCmd)
	int iRetryTimes=3;
	do 
	{
		strCmd=_T("SWP");
		DEVICE_WRITE(strCmd)
		do 
		{
			Sleep(50);
			strCmd=_T("MSTAT?");
			DEVICE_QUERY(strCmd)
				strRes=Device_GetReadBuf();
			iMSTAT=CStr::StrToInt(strRes);
			iTimeOut++;
		} while ((iMSTAT!=0)&&(iTimeOut<15));
		//	if (iTimeOut==15) return iMSTAT+1010;
		if (0==*iResultStepE)
		{
			strCmd=_T("ILPC_PASS? E");
			DEVICE_QUERY(strCmd)
				strRes=Device_GetReadBuf();
			if (strRes.Find("PASS")>-1)
			{
				*iResultStepE=1;
			}
		}

		if (0==*iResultStepF)
		{
			strCmd=_T("ILPC_PASS? F");
			DEVICE_QUERY(strCmd)
				strRes=Device_GetReadBuf();
			if (strRes.Find("PASS")>-1)
			{
				*iResultStepF=1;
			}
		}
	} while ((0==*iResultStepE||0==*iResultStepF)&&(0<iRetryTimes--));	
	
		
	return DEVICE_SUCCESS;


}

int CFuncWCDMATest_8820::IWCDMATestILPC_FailSlot(int *iResultStepE,int *iResultStepF,double * dFailSlotPower_E,double * dFailSlotPower_F,int *iNUM_E,int *iNUM_F)
{
	CString strCmd;
	CString strRes;
	CStringVtr strVtrRes;
	int iDeviceErr;
	int iFailSotNumber[10]={0};
	int iNUME=0;
	int iNUMF=0;
	CString strTemp;

	int iMSTAT=-1,iTimeOut=0;

	
		
	strCmd=_T("SCRSEL TDMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 25");
	DEVICE_WRITE(strCmd)
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)

	


		
		strCmd=_T("MEASOBJ ILPC_AUTO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILPC_MEAS AUTO_EF");
	DEVICE_WRITE(strCmd)

	strCmd=_T("TDM_RRC OFF");
	DEVICE_WRITE(strCmd)

		

		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
	do 
	{
		Sleep(50);
		strCmd=_T("MSTAT?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		iMSTAT=CStr::StrToInt(strRes);
		iTimeOut++;
	} while ((iMSTAT!=0)&&(iTimeOut<15));
//	if (iTimeOut==15) return iMSTAT+1010;

		strCmd=_T("ILPC_PASS? E");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (strRes.Find("PASS")>-1)
		{
			*iResultStepE=1;
		}
		else
		{
           *iResultStepE=0;
          
		}
		
     


		strCmd=_T("ILPC_PASS? F");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (strRes.Find("PASS")>-1)
		{
			*iResultStepF=1;
		}
		else
		{
           *iResultStepF=0;
		}

		   strCmd=_T("SLOTLIST ON");
	   DEVICE_WRITE(strCmd)

          strCmd=_T("MKR_ILPC NRM");
	   DEVICE_WRITE(strCmd)

            strCmd=_T("MKRS_ILPC E,1");
	   DEVICE_WRITE(strCmd)

         if(*iResultStepF==0 || *iResultStepE==0)
		 {
			 int iIndex_E=0;
			 int iIndex_F=0;
			  for(int i=0;i<20;++i)
			   {

				   strCmd=_T("FSSEARCH");
				   DEVICE_WRITE(strCmd)

	
				   strCmd=_T("MKRS_ILPC?");
					DEVICE_QUERY(strCmd)
					strRes=Device_GetReadBuf();
					CStr::ParseString(strRes,",",strVtrRes);
					iFailSotNumber[i]=CStr::StrToInt(strVtrRes[1]);
					if(i!=0 && iFailSotNumber[i]==iFailSotNumber[0])
						break;

					if(i!=0 && (abs(iFailSotNumber[i]-iFailSotNumber[i-1])==1))
					{
                          i=i-1;
						  continue;
					}
                     
					 if(strVtrRes[0]=="E")
					 {
						 iNUME+=5;
						 
						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
						dFailSlotPower_E[iIndex_E*5+2]=CStr::StrToFloat(strRes);
                         

						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]-2);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
                        dFailSlotPower_E[iIndex_E*5]=CStr::StrToFloat(strRes);

						strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]-1);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
                        dFailSlotPower_E[iIndex_E*5+1]=CStr::StrToFloat(strRes);


						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]+1);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
						dFailSlotPower_E[iIndex_E*5+3]=CStr::StrToFloat(strRes);

						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]+2);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
						dFailSlotPower_E[iIndex_E*5+4]=CStr::StrToFloat(strRes);

						iIndex_E++;
					 }
					 else if(strVtrRes[0]=="F")
					 {
						 iNUMF+=5;
						 
						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
						dFailSlotPower_F[iIndex_F*5+2]=CStr::StrToFloat(strRes);



						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]-1);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
                        dFailSlotPower_F[iIndex_F*5+1]=CStr::StrToFloat(strRes);

						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]-2);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
                        dFailSlotPower_F[iIndex_F*5]=CStr::StrToFloat(strRes);

						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]+1);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
						dFailSlotPower_F[iIndex_F*5+3]=CStr::StrToFloat(strRes);

						 strCmd.Format("ILPC_PWR? %s,%d",strVtrRes[0],iFailSotNumber[i]+2);
						DEVICE_QUERY(strCmd)
						strRes=Device_GetReadBuf();
						dFailSlotPower_F[iIndex_F*5+4]=CStr::StrToFloat(strRes);

						iIndex_F++;

					 }
				   

			   }
		 }
		


    *iNUM_E=iNUME;
     *iNUM_F=iNUMF;
  return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ITDSCDMASetLoss(int iBand,const DblVtr & vLossList)
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

	strCmd.Format(_T("DLEXTLOSSW COMMON"));
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	strCmd.Format(_T("ULEXTLOSSW COMMON"));
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	strCmd.Format(_T("EXTLOSSW COMMON"));
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	strCmd.Format(_T("EXTLOSSW COMMON"));
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;


	switch(iBand)
	{
	case 1:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1920MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2140MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1950MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2170MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1980MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 2:
		strCmd.Format("LOSSTBLVAL 1930MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1850MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1960MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1990MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1909MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 3:
		strCmd.Format("LOSSTBLVAL 1805MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1711MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1843MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1748MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1785MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 4:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1710MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2132MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1732MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2155MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1755MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 5:
		strCmd.Format("LOSSTBLVAL 869MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 824MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 882MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 837MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 894MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 849MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 7:
		strCmd.Format("LOSSTBLVAL 2620MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2500MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2656MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2536MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2690MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2570MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 8:
		strCmd.Format("LOSSTBLVAL 925MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 880MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 942MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 897MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 960MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 915MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 12:
		strCmd.Format("LOSSTBLVAL 728MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 698MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 737MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 707MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 746MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 716MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 14:
		strCmd.Format("LOSSTBLVAL 758MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 788MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 763MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 793MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 768MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 798MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 17:
		strCmd.Format("LOSSTBLVAL 734MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 704MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 740MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 710MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 746MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 716MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 20:
		strCmd.Format("LOSSTBLVAL 791MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 832MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 806MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 847MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 821MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 862MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 25:
		strCmd.Format("LOSSTBLVAL 1930MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1850MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1950MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1870MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1970MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1890MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 26:
		strCmd.Format("LOSSTBLVAL 859MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 814MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 869MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 824MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 879MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 834MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;	
	
	case 34:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2010MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2117MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2017MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2124MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2024MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 38:
		strCmd.Format("LOSSTBLVAL 2570MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2470MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2595MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2495MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2620MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2520MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 39:
		strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1780MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1900MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1800MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1920MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1820MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 40:
		strCmd.Format("LOSSTBLVAL 2300MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2200MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2350MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2250MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2400MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2290MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;	
	case 41:
		strCmd.Format("LOSSTBLVAL 2496MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2450MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2590MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2550MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2690MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2650MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	default:
		return DEVICE_WRITE_FAIL;
	}

	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ILteSetLoss(int iBand,const DblVtr & vLossList)
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


	strCmd.Format(_T("EXTLOSSW COMMON"));
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;


	switch(iBand)
	{
	case 1:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1920MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2140MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1950MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2170MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1980MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 2:
		strCmd.Format("LOSSTBLVAL 1930MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1850MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1960MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1990MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1909MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 3:
		strCmd.Format("LOSSTBLVAL 1805MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1711MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1843MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1748MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1785MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 4:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1710MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2132MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1732MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2155MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1755MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 5:
		strCmd.Format("LOSSTBLVAL 869MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 824MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 882MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 837MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 894MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 849MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 7:
		strCmd.Format("LOSSTBLVAL 2620MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2500MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2656MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2536MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2690MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2570MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 8:
		strCmd.Format("LOSSTBLVAL 925MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 880MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 942MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 897MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 960MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 915MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 12:
		strCmd.Format("LOSSTBLVAL 728MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 698MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 737MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 707MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 746MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 716MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 14:
		strCmd.Format("LOSSTBLVAL 758MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 788MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 763MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 793MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 768MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 798MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 17:
		strCmd.Format("LOSSTBLVAL 734MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 704MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 740MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 710MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 746MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 716MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 19:
		strCmd.Format("LOSSTBLVAL 830MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 875MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 837MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 882MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 845MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 890MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 20:
		strCmd.Format("LOSSTBLVAL 791MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 832MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 806MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 847MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 821MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 862MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 21:
		strCmd.Format("LOSSTBLVAL 1448MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1496MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1455MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1503MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1463MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1511MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 25:
		strCmd.Format("LOSSTBLVAL 1930MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1850MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1950MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1870MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1970MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1890MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 26:
		strCmd.Format("LOSSTBLVAL 859MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 814MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 869MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 824MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 879MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 834MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;	
	case 28:
		strCmd.Format("LOSSTBLVAL 758MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 703MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 779.5MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 724.5MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 803MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 748MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 34:
		strCmd.Format("LOSSTBLVAL 2110MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2010MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2117MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2017MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2124MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2024MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 38:
		strCmd.Format("LOSSTBLVAL 2570MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2470MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2595MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2495MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2620MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2520MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 39:
		strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1780MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1900MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1800MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1920MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1820MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 40:
		strCmd.Format("LOSSTBLVAL 2300MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2200MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2350MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2250MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2400MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2290MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;	
	case 41:
		strCmd.Format("LOSSTBLVAL 2496MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2450MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2590MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2550MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2690MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 2650MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	default:
		return DEVICE_WRITE_FAIL;
	}

	return DEVICE_SUCCESS;
}
int  CFuncWCDMATest_8820::IWCDMATestSetLoss(int iWCDMABand,const DblVtr & vLossList)
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
	//if (strBuf.Find("8820B")!=-1)
	//{
	//	strCmd.Format(_T("DLEXTLOSSW COMMON"));
	//	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
	//		return iDeviceErr;
	//	strCmd.Format(_T("ULEXTLOSSW COMMON"));
	//	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
	//		return iDeviceErr;
	//}
	//else
	//{
	//	strCmd.Format(_T("EXTLOSSW COMMON"));
	//	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
	//		return iDeviceErr;
	//}

		strCmd.Format(_T("DLEXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
		strCmd.Format(_T("ULEXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

		/*strCmd.Format(_T("EXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;*/


	switch(iWCDMABand)
	{
	case WCDMA_B6_BAND_ID:

		strCmd.Format("LOSSTBLVAL 871.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 826.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 835MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 891.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 846.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case WCDMA_B19_BAND_ID:

		strCmd.Format("LOSSTBLVAL 871.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 826.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 835MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 891.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 846.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 1800:
		strCmd.Format("LOSSTBLVAL 1712.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1807.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1840MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1745MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1877.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1782.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 2100:
		strCmd.Format("LOSSTBLVAL 2112.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1922.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2140MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1950MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 2167.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1977.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 1900:
		strCmd.Format("LOSSTBLVAL 1854.2MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1934.2MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1960MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1906.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1986.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 1500:
		strCmd.Format("LOSSTBLVAL 1478.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1430.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1486MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1438MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 1493.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 1445.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 900:
		strCmd.Format("LOSSTBLVAL 882.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 927.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 897.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 942.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 912.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 957.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	case 850:
		strCmd.Format("LOSSTBLVAL 871.4MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 826.4MHZ,%0.2f,%0.2f,%0.2f",vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0],vLossList[0]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 880MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 835MHZ,%0.2f,%0.2f,%0.2f",vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1],vLossList[1]);
		DEVICE_WRITE(strCmd)
			strCmd.Format("LOSSTBLVAL 891.6MHZ,%0.2f,%0.2f,%0.2f;LOSSTBLVAL 846.6MHZ,%0.2f,%0.2f,%0.2f",vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2],vLossList[2]);
		DEVICE_WRITE(strCmd)
			break;
	default:
		return DEVICE_WRITE_FAIL;
	}

	return DEVICE_SUCCESS;
}

int CFuncWCDMATest_8820::IWCDMATestModAnalysis(const int icount,const double dTargetPower,double  *dPowerValue,double dModValue[])
{
	//Error Vector Magnitude  Unit=%
	//Peak Vector Error Unit=%
	//Phase Error Unit=deg
	//Magnitude Error Unit=%
	//Origin Offset Unit=dB
	//IQ Imbalance Unit=%
	//Timing Error Unit=chip
	//DPCCH/DPDCH Power Ratio Unit=dB

	CString strCmd;
	int iDeviceErr;
	CString strRes;
	int iRes;
	memset(dModValue,0,8);
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
	strCmd.Format("ILVL %.2f",dTargetPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
		strCmd=_T("TPCPAT ILPC");
	DEVICE_WRITE(strCmd)
		Sleep(50);
		strCmd=_T("TPCPAT ALT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("MOD_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd.Format("MOD_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		i=50;
	do 
	{
		Sleep(15);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
	i=50;
	strCmd=_T("TXMSTAT?");
	do
	{
		Sleep(20);
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

	}while((0!=strRes.Find("0"))&&(0<i--));
	if (0!=strRes.Find("0"))
	{
		return DEVICE_FINDRES_FAIL;
	}
	//Target power Unit=dBm
	strCmd=_T("AVG_FILTPWR?");
	DEVICE_QUERY(strCmd)

		strRes=Device_GetReadBuf();
	*dPowerValue=CStr::StrToFloat(strRes);
	//Error Vector Magnitude  Unit=%
	strCmd=_T("AVG_EVM?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[0]=CStr::StrToFloat(strRes);
	//Peak Vector Error Unit=%
	strCmd=_T("AVG_PVECTERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[1]=CStr::StrToFloat(strRes);
	//Phase Error Unit=deg
	strCmd=_T("AVG_PHASEERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[2]=CStr::StrToFloat(strRes);
	//Magnitude Error Unit=%
	strCmd=_T("AVG_MAGTDERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[3]=CStr::StrToFloat(strRes);
	//Origin Offset Unit=dB
	strCmd=_T("AVG_ORGNOFS?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[4]=CStr::StrToFloat(strRes);
	//IQ Imbalance Unit=%
	strCmd=_T("AVG_IQIMB?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[5]=CStr::StrToFloat(strRes);
	//Timing Error Unit=chip
	strCmd=_T("AVG_TMGERR?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[6]=CStr::StrToFloat(strRes);
	//DPCCH/DPDCH Power Ratio Unit=dB
	strCmd=_T("AVG_PWRRATIO?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	dModValue[7]=CStr::StrToFloat(strRes);

	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("MOD_MEAS OFF");
	DEVICE_WRITE(strCmd)
	
	return DEVICE_SUCCESS;	

}

int CFuncWCDMATest_8820::IWCDMATestMeasAll(const int icount,const int iSample,double dCellPower,double  *dPowerValue,double dModValue[],
					  double dACLR[],double *dOBWValue,int *iSMASK,double *dBER,double *dFER)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
	strCmd=_T("ILVL 24");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
		strCmd=_T("TPCPAT ALL1");
	DEVICE_WRITE(strCmd)
		Sleep(500);
		
		
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
		strCmd=_T("MEASMODE NORM");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("MOD_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ADJ_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("OBW_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SMASK_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("BER_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("FREQ_MEAS ON");
	DEVICE_WRITE(strCmd)
		strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd.Format("MOD_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd.Format("ADJ_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd.Format("OBW_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd.Format("SMASK_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd.Format("BER_SAMPLE %d",iSample);
	DEVICE_WRITE(strCmd)
		strCmd.Format("FREQ_AVG %d",icount);
	DEVICE_WRITE(strCmd)
		strCmd=_T("OBW_RATIO 99");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SWP");
	DEVICE_WRITE(strCmd)
//		strCmd=_T("*OPC?");
//	DEVICE_QUERY(strCmd)
		i=10;
		do 
		{
			strCmd=_T("*CLS");
			DEVICE_WRITE(strCmd)
				strCmd=_T("SWP?");
			Device_Query(strCmd,3000);
			strRes=Device_GetReadBuf();
			iRes=CStr::StrToInt(strRes);
		} while (iRes!=0&&--i>0);
		i=50;
		do 
		{
				strCmd=_T("RXMSTAT?");
			DEVICE_QUERY(strCmd)
				Sleep(20);
			strRes=Device_GetReadBuf();
			iRes=CStr::StrToInt(strRes);
		} while (iRes!=0&&--i>0);
		//************************************************Target power Unit=dBm
		strCmd=_T("AVG_FILTPWR?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		*dPowerValue=CStr::StrToFloat(strRes);
		//************************************************Mod Analysis
		//Error Vector Magnitude  Unit=%
		strCmd=_T("AVG_EVM?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dModValue[0]=CStr::StrToFloat(strRes);
		//Peak Vector Error Unit=%
		strCmd=_T("AVG_PVECTERR?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dModValue[1]=CStr::StrToFloat(strRes);
		//Phase Error Unit=deg
		strCmd=_T("AVG_PHASEERR?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dModValue[2]=CStr::StrToFloat(strRes);
		//Magnitude Error Unit=%
		strCmd=_T("AVG_MAGTDERR?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dModValue[3]=CStr::StrToFloat(strRes);
		//Origin Offset Unit=dB
		strCmd=_T("AVG_ORGNOFS?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dModValue[4]=CStr::StrToFloat(strRes);
		//IQ Imbalance Unit=%
		strCmd=_T("AVG_IQIMB?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dModValue[5]=CStr::StrToFloat(strRes);
		//Timing Error Unit=chip
		strCmd=_T("AVG_TMGERR?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dModValue[6]=CStr::StrToFloat(strRes);
		//DPCCH/DPDCH Power Ratio Unit=dB
		strCmd=_T("AVG_PWRRATIO?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dModValue[7]=CStr::StrToFloat(strRes);
		//*************************************************ACLR Test
		strCmd=_T("AVG_MODPWR? LOW10");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dACLR[0]=CStr::StrToFloat(strRes);
		strCmd=_T("AVG_MODPWR? LOW5");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dACLR[1]=CStr::StrToFloat(strRes);
		strCmd=_T("AVG_MODPWR? UP5");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dACLR[2]=CStr::StrToFloat(strRes);
		strCmd=_T("AVG_MODPWR? UP10");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		dACLR[3]=CStr::StrToFloat(strRes);
		//***************************************************OBW Test unit= MHz
		strCmd=_T("OCCBW?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		*dOBWValue=CStr::StrToFloat(strRes);
		*dOBWValue=*dOBWValue/1000000;
		//***************************************************Spectrum Emission Mask Test Pass:1,Fail:0
		strCmd=_T("SMASKPASS?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		*iSMASK=0;
		if (strRes.Find(_T("PASS"))>-1)
		{
			*iSMASK=1;
		}
		//***************************************************BER Test unit= %

		strCmd=_T("OLVL -100");
	DEVICE_WRITE(strCmd)
		Sleep(200);

		strCmd.Format("OLVL %.2f;*OPC",dCellPower);
	DEVICE_WRITE(strCmd)

		Sleep(200);

		strCmd=_T("BER? PER");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		*dBER=CStr::StrToFloat(strRes);
		//***************************************************FER Test unit= Hz

		strCmd.Format("OLVL %0.2f;*OPC",-65.00);
	   DEVICE_WRITE(strCmd)

		strCmd=_T("AVG_CARRFERR?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		*dFER=CStr::StrToFloat(strRes);


		strCmd=_T("PWR_MEAS OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MOD_MEAS OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("ADJ_MEAS OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("OBW_MEAS OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("SMASK_MEAS OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("BER_MEAS OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("FREQ_MEAS OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MEASMODE FAST");
		DEVICE_WRITE(strCmd)

			return DEVICE_SUCCESS;

}
/*PowerCtrlBit : 0 for All Down,1 for All Up,2 for Alternate,3 for Inner Loop Power Ctrl*/
int CFuncWCDMATest_8820::IWCDMATestSetPower(const double dCellPower,const double dTargetPower,const int iPowerCtrlBit)
{

	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("ILVL %.2f",dTargetPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		int i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	strCmd.Format("OLVL %.2f",dCellPower);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
	i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	strCmd=_T("TPCPAT ILPC");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
	i=50;
	do 
	{
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	switch (iPowerCtrlBit)
	{
	case 0:
		strCmd=_T("TPCPAT ALL0");
		DEVICE_WRITE(strCmd)
		break;
	case 1:
		strCmd=_T("TPCPAT ALL1");
		DEVICE_WRITE(strCmd)
			break;
	case 2:
		strCmd=_T("TPCPAT ALT");
		DEVICE_WRITE(strCmd)
			break;
	default:
		strCmd=_T("TPCPAT ILPC");
		DEVICE_WRITE(strCmd)
			break;
	}

	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8820::ITDSCDMAInitSet(const CString& strAddr)
{
	CString strCmd;
	int iDeviceErr,iRes;

	CString strRes;

	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;


	strCmd=_T("BANDCAL");
	DEVICE_WRITE(strCmd)
		Sleep(1000);
	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)

		strCmd=_T("CALLSO");
	DEVICE_WRITE(strCmd)

		strCmd=_T("STDSEL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();

	if(strRes.Find("TDSCDMA")==-1)
	{
		strCmd=_T("STDSEL TDSCDMA");
		DEVICE_WRITE(strCmd)

			Sleep(3000);

		strCmd=_T("STDSEL?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

		if(strRes.Find("TDSCDMA")==-1)
		{
			return  -99; 
		}

	}
	strCmd=_T("*RST");
	DEVICE_WRITE(strCmd)

		strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
	
			strCmd=_T("SCREEN ON");
			DEVICE_WRITE(strCmd)

				strCmd=_T("MEASMODE NORM");
			DEVICE_WRITE(strCmd)
	
		strCmd=_T("CALLPROC OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("TESTMODE MODE1");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MOD ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("CHCODING RMC_SINGLE");
		DEVICE_WRITE(strCmd)
			strCmd=_T("RRCSTATE CELLDCH");
		DEVICE_WRITE(strCmd)			
			strCmd=_T("INTEGRITY ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("AUTHENT_KEYALL 00010203,04050607,08090A0B,0C0D0E0F");
		DEVICE_WRITE(strCmd)
			strCmd=_T("REGMODE COMBINED");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MCC 1");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MNC 01");
		DEVICE_WRITE(strCmd)
			strCmd=_T("UETIM_N313 50");
		DEVICE_WRITE(strCmd)
			strCmd=_T("UETIM_T313 15");
		DEVICE_WRITE(strCmd)
			strCmd=_T("OLVL -65");
		DEVICE_WRITE(strCmd)
			strCmd=_T("TPCPAT CLPC");
		DEVICE_WRITE(strCmd)
			strCmd=_T("CALLDROP ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("ILVL 0");
		DEVICE_WRITE(strCmd)
			strCmd=_T("TPCSTEP 1");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MAXULPWR 24");
		DEVICE_WRITE(strCmd)
			strCmd=_T("PCCPCHPWR 24");
		DEVICE_WRITE(strCmd)
			strCmd=_T("PRXUPCH -100");
		DEVICE_WRITE(strCmd)
			strCmd=_T("PWRRMPSTEP 0");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MAXSYNCTRANS 1");
		DEVICE_WRITE(strCmd)
			strCmd=_T("RABCONNECT ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("DTCHPAT PN9");
		DEVICE_WRITE(strCmd)
			strCmd=_T("SCRCODEID 0");
		DEVICE_WRITE(strCmd)
			strCmd=_T("DWPCHLVL 0");
		DEVICE_WRITE(strCmd)
			strCmd=_T("UDPCHSLOT 2");
		DEVICE_WRITE(strCmd)
			strCmd=_T("PCCPCHLVL 0");
		DEVICE_WRITE(strCmd)
			strCmd=_T("DDPCHLVL 0");
		DEVICE_WRITE(strCmd)
			strCmd=_T("DLPWRCTRL OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("LVL ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MEASSTOP");
		DEVICE_WRITE(strCmd)
			strCmd=_T("ALLMEASITEMS_OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("MEASMODE NORM");
		DEVICE_WRITE(strCmd)
			strCmd=_T("SCRSEL FMEAS");
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
int CFuncWCDMATest_8820::ILteMeasConfig(bool bIsTDD,int iBan)
{
	return DEVICE_SUCCESS;
}

int CFuncWCDMATest_8820::ILteInitSet(const CString& strAddr,const CString strWaveForm,const CString strLTEMode)
{
	CString strCmd;
	int iDeviceErr;

	CString strRes;

	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

	

	strCmd=_T("SCRSEL FMEAS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALLSO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("STDSEL?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();

	if(strRes.Find("LTE")==-1)
	{
		strCmd=_T("STDSEL LTE");
		DEVICE_WRITE(strCmd)

			Sleep(3000);

		strCmd=_T("STDSEL?");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();

		if(strRes.Find("LTE")==-1)
		{
			return  -99; 
		}

	}
	strCmd=_T("PRESET_EXTARB;*OPC?");
	DEVICE_QUERY(strCmd)

		strCmd=_T("BANDCAL;*OPC");
		DEVICE_WRITE(strCmd)


		strCmd=_T("*CLS;*OPC?");
	DEVICE_QUERY(strCmd)

		strCmd=_T("SCREEN ON");
	DEVICE_WRITE(strCmd)
		strCmd=_T("MEASSTOP");
	DEVICE_WRITE(strCmd)		
		strCmd=_T("ALLMEASITEMS_OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("CALLPROC ARB");	
	DEVICE_WRITE(strCmd)
    if (strLTEMode=="FDD")
    {
		strCmd=_T("RFOUT MAIN;*OPC?");
			DEVICE_QUERY(strCmd)
		//DEVICE_WRITE(strCmd)
    }
	if (strLTEMode=="FDD")
	{
		strCmd=_T("FRAMETYPE FDD");
		DEVICE_WRITE(strCmd)
	}

	if (strLTEMode=="TDD")
	{
		strCmd=_T("FRAMETYPE TDD");
		DEVICE_WRITE(strCmd)
	}

		strCmd=_T("TPCPAT AUTO");
	DEVICE_WRITE(strCmd)
		strCmd=_T("ILVL 20");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PACKAGE?");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	if (-1==strRes.Find("PAC1"))
	{
		strCmd=_T("PACKAGE PAC1;*OPC?");
		DEVICE_QUERY(strCmd)
	}
	

		
	
	if (strLTEMode=="FDD")
	{
		strCmd=_T("DLPAT PAT3;*OPC?");
		DEVICE_QUERY(strCmd)
	}
	if (strLTEMode=="TDD")
	{
		strCmd=_T("DLPAT PAT15;*OPC?");
		DEVICE_QUERY(strCmd)
	}

		strCmd=_T("GROUPHOP OFF");
	DEVICE_WRITE(strCmd)
		strCmd=_T("BANDWIDTH 10MHZ");
	DEVICE_WRITE(strCmd)

		strCmd=_T("CHCONFIG PUSCH");
	DEVICE_WRITE(strCmd)
		strCmd=_T("SIB2_NS NS_01");
	DEVICE_WRITE(strCmd)

		strCmd=_T("PWRRMPSTEP DB2");
	DEVICE_WRITE(strCmd)
		strCmd=_T("PRACHID 3");
	DEVICE_WRITE(strCmd)
		
		strCmd=_T("PREAMBLETGT -104");
	DEVICE_WRITE(strCmd)

		strCmd=_T("WINDSIZE SF10");
	DEVICE_WRITE(strCmd)

		strCmd=_T("PREAMBLEMAX N6");
	DEVICE_WRITE(strCmd)

		strCmd=_T("TARGETSTATE 3A");
	DEVICE_WRITE(strCmd)

		strCmd=_T("LOOPBACK OFF");
	DEVICE_WRITE(strCmd)

		strCmd=_T("DTCHPAT MACPAD");
	DEVICE_WRITE(strCmd)

		strCmd=_T("MODIFPERIOD N2");
	DEVICE_WRITE(strCmd)

		strCmd=_T("PCYCLE 32");
	DEVICE_WRITE(strCmd)

		strCmd=_T("RRCUPDATE Paging");
	DEVICE_WRITE(strCmd)
    if (strLTEMode=="TDD")
    {
		strCmd=_T("TDDSSFCONF 4");
		DEVICE_WRITE(strCmd)

			strCmd=_T("TDDULDLCONF 1");
		DEVICE_WRITE(strCmd)
    }

		strCmd=_T("MAXULPWR 30");
	DEVICE_WRITE(strCmd)

		strCmd=_T("LVL ON");
	DEVICE_WRITE(strCmd)

		

	return DEVICE_SUCCESS;
}

int CFuncWCDMATest_8820::ILteHandOver(int iBand,int iULChannel)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	int iDLChannel=CLTEBandInfo::GetDLChannel(iBand,iULChannel);
	strCmd.Format("DLCHAN %d",iDLChannel);
	DEVICE_WRITE(strCmd)
		strCmd.Format("ULCHAN %d",iULChannel);
	DEVICE_WRITE(strCmd)

	strCmd=_T("*OPC?");	
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
		Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8820::ILteSetPower(double dCellPower,double dTargetPower,int iTPC)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("ILVL %.2f",dTargetPower);
	DEVICE_WRITE(strCmd)
		strCmd.Format("OLVL %.2f",dCellPower);
	DEVICE_WRITE(strCmd)
	
	switch (iTPC)
	{
	case 0:
		strCmd=_T("TPCPAT ALLM1");
		DEVICE_WRITE(strCmd)
			break;
	case 1:
		strCmd=_T("TPCPAT ALL1");
		DEVICE_WRITE(strCmd)
			break;
	case 2:
		strCmd=_T("TPCPAT AUTO");
		DEVICE_WRITE(strCmd)
			break;
	default:
		strCmd=_T("TPCPAT AUTO");
		DEVICE_WRITE(strCmd)
			break;
	}

		strCmd=_T("*OPC?");	
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}

	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_8820::ILteConfigWaveForm(int iNumRB,int iStartRB,int iMCS)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("ULRMC_RB %d",iNumRB);
	DEVICE_WRITE(strCmd)
		strCmd.Format("ULRB_START %d",iStartRB);
	DEVICE_WRITE(strCmd)
		strCmd.Format("ULIMCS %d",iMCS);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");	
	int i=50;
	do 
	{
		DEVICE_QUERY(strCmd)
			Sleep(20);
		strRes=Device_GetReadBuf();
		iRes=CStr::StrToInt(strRes);
	} while (iRes!=1&&--i>0);
	if (i==0)
	{
		return DEVICE_QUERY_FAIL;
	}
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ILteConfiguredPower(const int icount,const double dMaxulpower,double *dPower)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd);
	strCmd.Format("MAXULPWR %.0f",dMaxulpower);
	DEVICE_WRITE(strCmd);
	strCmd="SWP";
	DEVICE_WRITE(strCmd);
	strCmd="SWP?";
	int i=50;
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
	strCmd="TXMSTAT?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	iRes=CStr::StrToInt(strRes);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("POWER? AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	*dPower=CStr::StrToFloat(strRes);
	strCmd=_T("MEASSTOP");
	DEVICE_WRITE(strCmd);
	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd);
	strCmd=_T("MAXULPWR 30");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ILteTestPower(const int icount,double *dPower)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("PWR_AVG %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("PWR_MEAS ON");
	DEVICE_WRITE(strCmd);
	strCmd="SWP";
	DEVICE_WRITE(strCmd);
	strCmd="SWP?";
	int i=50;
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
	strCmd="TXMSTAT?";
	DEVICE_QUERY(strCmd)
	strRes=Device_GetReadBuf();
	iRes=CStr::StrToInt(strRes);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("POWER? AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	*dPower=CStr::StrToFloat(strRes);
	strCmd=_T("MEASSTOP");
	DEVICE_WRITE(strCmd);
	strCmd=_T("PWR_MEAS OFF");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

		

}
int CFuncWCDMATest_8820::ILteOBW(const int icount,double *dOBW)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("OBW_AVG %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("OBW_MEAS ON");
	DEVICE_WRITE(strCmd);
	strCmd="SWP";
	DEVICE_WRITE(strCmd);
	strCmd="SWP?";
	int i=50;
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
	strCmd="TXMSTAT?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	iRes=CStr::StrToInt(strRes);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("OBW?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	*dOBW=CStr::StrToFloat(strRes)/1000000;
	strCmd=_T("MEASSTOP");
	DEVICE_WRITE(strCmd);
	strCmd=_T("OBW_MEAS OFF");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ILteTxQual(const int icount,double *dEVM,double *dFERPPM,double *dOgnOfst,double *dSptrFlat,double *dInbEm)
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("MOD_AVG %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("MOD_MEAS ON");
	DEVICE_WRITE(strCmd);
	strCmd="SWP";
	DEVICE_WRITE(strCmd);
	strCmd="SWP?";
	int i=50;
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
	strCmd="TXMSTAT?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	iRes=CStr::StrToInt(strRes);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("EVM? AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	*dEVM=CStr::StrToFloat(strRes);

	strCmd=_T("CARRFERR? PPM,AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	*dFERPPM=abs(CStr::StrToFloat(strRes));

	strCmd=_T("CARRLEAK? AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	*dOgnOfst=CStr::StrToFloat(strRes);	
	*dSptrFlat=0;
	*dInbEm=0;
	strCmd=_T("MEASSTOP");
	DEVICE_WRITE(strCmd);
	strCmd=_T("MOD_MEAS OFF");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ILteSEMask(const int icount,int *isPass,double dSEMask[])
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("SEM_AVG %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("SEM_MEAS ON");
	DEVICE_WRITE(strCmd);
	strCmd="SWP";
	DEVICE_WRITE(strCmd);
	strCmd="SWP?";
	int i=50;
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
	strCmd="TXMSTAT?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	iRes=CStr::StrToInt(strRes);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}
	strCmd=_T("TTL_WORST_SEM_LV?");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	DblVtr dvRes;
	CStringVtr svRes;
	double daSEMaskLimit[8]={-23.5,-11.5,-8.5,-16.5,-16.5,-8.5,-11.5,-23.5};
	*isPass=1;
	CStr::ParseString(strRes,",",svRes)	;
	CStr::StrVtr2DblVtr(dvRes,svRes);
	for (int i=0;i<8;i++)
	{
		dSEMask[i]=dvRes[2*i];
		if (dSEMask[i]>daSEMaskLimit[i])
		{
			*isPass=0;
		}
	}
	strCmd=_T("MEASSTOP");
	DEVICE_WRITE(strCmd);
	strCmd=_T("SEM_MEAS OFF");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}
int CFuncWCDMATest_8820::ILteACLR(const int icount,int *isPass,double dACLRValue[])
{
	CString strCmd;
	int iDeviceErr,iRes;
	CString strRes;
	strCmd.Format("ACLR_AVG %d",icount);
	DEVICE_WRITE(strCmd);
	strCmd=_T("ACLR_MEAS ON");
	DEVICE_WRITE(strCmd);
	strCmd="SWP";
	DEVICE_WRITE(strCmd);
	strCmd="SWP?";
	int i=50;
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
	strCmd="TXMSTAT?";
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	iRes=CStr::StrToInt(strRes);
	if (0!=iRes)
	{
		return DEVICE_QUERY_FAIL;
	}	
	strCmd=_T("MODPWR? LOW2,AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	dACLRValue[0]=CStr::StrToFloat(strRes);

	strCmd=_T("MODPWR? LOW1,AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	dACLRValue[1]=CStr::StrToFloat(strRes);

	strCmd=_T("MODPWR? UP1,AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();
	dACLRValue[2]=CStr::StrToFloat(strRes);

	strCmd=_T("MODPWR? UP2,AVG");
	DEVICE_QUERY(strCmd);
	strRes=Device_GetReadBuf();	
	dACLRValue[3]=CStr::StrToFloat(strRes);	
	*isPass=1;
	double daACLRLimit[4]={-35.2,-32.2,-32.2,-35.2};
	for (int i=0;i<4;i++)
	{		
		if (dACLRValue[i]>daACLRLimit[i])
		{
			*isPass=0;
		}
	}
	strCmd=_T("MEASSTOP");
	DEVICE_WRITE(strCmd);
	strCmd=_T("ACLR_MEAS OFF");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;

}