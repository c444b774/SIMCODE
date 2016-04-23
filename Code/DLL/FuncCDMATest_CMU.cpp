#include "StdAfx.h"
#include "FuncCDMATest_CMU.h"

CFuncCDMATest_CMU::CFuncCDMATest_CMU(void)
{
}

CFuncCDMATest_CMU::~CFuncCDMATest_CMU(void)
{
}

CFuncCDMATest_CMU::CFuncCDMATest_CMU(PCTesterDevice pDev):CFuncDev_CMU(pDev)
{

}
int CFuncCDMATest_CMU::ICDMATestInitCDMANStest(const CString& strAddr,const CString strWavefile)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;


	if((iDeviceErr=Device_Init(strAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;

/*
	strCmd.Format(_T("%s::%s"),strAddr,"0::INSTR");
	if((iDeviceErr=Device_Init(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;*/

	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd)
		strCmd=_T("0;SYST:REM:ADDR:SEC? 1");
	DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
	if (strRes.Find("CDMA2KCellMS_NSig")==-1)
	{
		strCmd=_T("0;SYST:REM:ADDR:SEC 1,NONE");
		DEVICE_WRITE(strCmd)
		strCmd=_T("0;SYST:REM:ADDR:SEC 1,\"CDMA2KCellMS_NSig\"");
		DEVICE_WRITE(strCmd)
			strCmd=_T("0;SYST:REM:ADDR:SEC? 1");
		DEVICE_QUERY(strCmd)
			strRes=Device_GetReadBuf();
		if (strRes.Find("CDMA2KCellMS_NSig")==-1)
		{
			MessageBox(NULL,_T("Device fast switch CDMA2KCellMS_NSig fail!"),_T("WARNING"),MB_OK);
			return DEVICE_WRITE_FAIL;
		}


	}
	strCmd=_T("0;SYST:RES:CURR;*OPC?");
	DEVICE_QUERY(strCmd)


	if(m_pTesterDevice->m_bIsScreenOff)
	{
		strCmd=_T("0;DISPLAY OFF");
		DEVICE_WRITE(strCmd)

	}
	strCmd=_T("1;OUTP RF2");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;INP RF2");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;TRIGger:SOURce INTernal");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOUR:RFG:PREV 6");
	DEVICE_WRITE(strCmd)
		
		return DEVICE_SUCCESS;

}
int CFuncCDMATest_CMU::ICDMATestHandover(const int iBand,const int iChannel)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("0;SYST:REM:ADDR:SEC 1,NONE");
	DEVICE_WRITE(strCmd)
	switch(iBand)
	{
	case CDMA_BC0_BAND_ID:
		strCmd=_T("0;SYST:REM:ADDR:SEC 1,\"CDMA2KCellMS_NSig\"");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONF:NETW:STAN USC");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)

		break;
	case CDMA_BC1_BAND_ID:
		strCmd=_T("0;SYST:REM:ADDR:SEC 1,\"CDMA2KPCSMS_NSig\"");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONF:NETW:STAN NAPC;*OPC?");
		DEVICE_QUERY(strCmd)
		break;
	}
	strCmd=_T("1;TRIGger:SOURce INTernal");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOUR:RFG:PREV 6");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:RC 1");
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;SOUR:RFG:FREQ:UNIT CH");
	DEVICE_WRITE(strCmd)
		strCmd.Format("1;SOUR:RFG:FREQ %d",iChannel);
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;RFAN:FREQ:UNIT CH");
	DEVICE_WRITE(strCmd)
		strCmd.Format("1;RFAN:FREQ %d",iChannel);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)

		strCmd=_T("1;SOURce:RFG:POWER:CDMA -65");
	DEVICE_WRITE(strCmd)
		Sleep(30);
	strCmd=_T("1;INIT:RFG");
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;SOURce:RFGenerator:FRATe:FFCH FULL");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:LEVel:FPICh -7");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:LEVel:FPCH -12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:CHANnel:FFCH 10");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:LEVel:FFCH -15.6");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:LEVel:FSYNc -16");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:PROPerty:PNOFfset 12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:SID 331");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:NID 1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:PCBits AUTO");
	DEVICE_WRITE(strCmd)

		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)

		strCmd=_T("1;LEVel:MAXimum 28");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		strCmd=_T("1;LEVel:MODE AUT");
	DEVICE_WRITE(strCmd)
	
		strCmd=_T("1;ABORt:MODulation:OVERview");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;ABORt:CDPower:CHPW");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;ABORt:NPOWer");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;ABORt:SPECtrum:ACP");
	DEVICE_WRITE(strCmd)
	
		return DEVICE_SUCCESS;

}
int CFuncCDMATest_CMU::ICDMATestHandoverCall(const int iBand,const int iChannel,const double dCellPwr,const double dFchLev)
{

	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd=_T("0;SYST:REM:ADDR:SEC 1,NONE");
	DEVICE_WRITE(strCmd)
		switch(iBand)
	{
		case CDMA_BC0_BAND_ID:
			strCmd=_T("0;SYST:REM:ADDR:SEC 1,\"CDMA2KCellMS_NSig\"");
			DEVICE_WRITE(strCmd)
				strCmd=_T("1;CONF:NETW:STAN USC;*OPC?");
			DEVICE_QUERY(strCmd)

				break;
		case CDMA_BC1_BAND_ID:
			strCmd=_T("0;SYST:REM:ADDR:SEC 1,\"CDMA2KPCSMS_NSig\"");
			DEVICE_WRITE(strCmd)
				strCmd=_T("1;CONF:NETW:STAN NAPC;*OPC?");
			DEVICE_QUERY(strCmd)
				break;
	}
	strCmd=_T("1;TRIGger:SOURce INTernal");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOUR:RFG:PREV 6");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:RC 1");
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;SOUR:RFG:FREQ:UNIT CH");
	DEVICE_WRITE(strCmd)
		strCmd.Format("1;SOUR:RFG:FREQ %d",iChannel);
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;RFAN:FREQ:UNIT CH");
	DEVICE_WRITE(strCmd)
		strCmd.Format("1;RFAN:FREQ %d",iChannel);
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)

		strCmd=_T("1;SOURce:RFG:POWER:CDMA -65");
	DEVICE_WRITE(strCmd)
		Sleep(30);
	strCmd=_T("1;INIT:RFG");
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;SOURce:RFGenerator:FRATe:FFCH FULL");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:LEVel:FPICh -7");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:LEVel:FPCH -12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:CHANnel:FFCH 10");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:LEVel:FFCH -15.6");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:LEVel:FSYNc -16");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:PROPerty:PNOFfset 12");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:SID 331");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:NID 1");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:PCBits AUTO");
	DEVICE_WRITE(strCmd)

		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)

		strCmd=_T("1;LEVel:MAXimum 28");
	DEVICE_WRITE(strCmd)
		strCmd=_T("*OPC?");
	DEVICE_QUERY(strCmd)
		strCmd=_T("1;LEVel:MODE AUT");
	DEVICE_WRITE(strCmd)

		strCmd=_T("1;ABORt:MODulation:OVERview");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;ABORt:CDPower:CHPW");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;ABORt:NPOWer");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;ABORt:SPECtrum:ACP");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;
}
int CFuncCDMATest_CMU::ICDMATestSetESN(const CString& strESN)
{
	CString strCmd;
	CString strRes;
	int iDeviceErr;
	strCmd.Format("1;SOURce:RFGenerator:ESN \"%s\"",strESN);
	DEVICE_WRITE(strCmd)
		return DEVICE_SUCCESS;
}
int CFuncCDMATest_CMU::ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	CStringVtr strVtrTemp;
	CString strTemp;
	int iCountPwr=4,iPwrSel=30;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);
	if ((strTestItem.Find("A1")!=-1)||(strTestItem.Find("B1")!=-1)||(strTestItem.Find("C1")!=-1)||(strTestItem.Find("D1")!=-1)||
		(strTestItem.Find("E1")!=-1)||(strTestItem.Find("F1")!=-1)||(strTestItem.Find("G1")!=-1))//wfq@-75dBm test
	{
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -75");
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
		strCmd=_T("1;LEVel:MAXimum 28");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:PCBits AUP");
		DEVICE_WRITE(strCmd);
		strCmd.Format("1;CONFigure:CDPower:CHPW:CONTrol SCAL,%d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd);
		strCmd.Format("1;CONFigure:MODulation:OVERview:CONTrol %d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;INITiate:MODulation:OVERview");
		DEVICE_WRITE(strCmd)
			iRetryTimes=50;
		do 
		{
			strCmd=_T("1;FETCh:MODulation:OVERview:STATus?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("RDY")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("1;FETCh:MODulation:OVERview?");
		DEVICE_QUERY(strCmd)
		strReadBuf=Device_GetReadBuf();
		strCmd=_T("1;ABORt:MODulation:OVERview");
		DEVICE_WRITE(strCmd)

		strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		if (strTestItem.Find("A1")!=-1)//A: Carrier feedthrough
		{
			strVtrResult.push_back(strVtrTemp[19]);
		}

		if (strTestItem.Find("B1")!=-1)//B: EVM AVG
		{
			strVtrResult.push_back(strVtrTemp[4]);
		}

		if (strTestItem.Find("C1")!=-1)//C: Frequency error
		{
			strVtrResult.push_back(strVtrTemp[25]);
		}

		if (strTestItem.Find("D1")!=-1)//D: Magnitude error
		{
			strVtrResult.push_back(strVtrTemp[10]);
		}

		if (strTestItem.Find("E1")!=-1)//E: Phase error
		{
			strVtrResult.push_back(strVtrTemp[16]);
		}

		if (strTestItem.Find("F1")!=-1)//F: Rho
		{
			strVtrResult.push_back(strVtrTemp[31]);
		}

		if (strTestItem.Find("F1")!=-1)//G: Time error
		{
			strVtrResult.push_back(strVtrTemp[28]);
		}


	}
	if(strTestItem.Find("H1")!=-1)//MAX POWER
	{
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -101");
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;LEVel:MAXimum 28");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd=_T("1;SOURce:RFGenerator:PCBits AUP");
		DEVICE_WRITE(strCmd)
			strCmd.Format("1;CONFigure:NPOWer:CONTrol %d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;INITiate:NPOWer");
		DEVICE_WRITE(strCmd)
			iRetryTimes=50;
		do 
		{
			strCmd=_T("1;FETCh:NPOWer:STATus?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("RDY")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		iRetryTimes=50;
		do 
		{
			strCmd=_T("1;STATus:OPERation:SYMBolic?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("NONE")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("NONE")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("1;FETCh:NPOWer?");
		DEVICE_QUERY(strCmd)
		strReadBuf=Device_GetReadBuf();
		strCmd=_T("1;ABORt:NPOWer");
		DEVICE_WRITE(strCmd)

			strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		strVtrResult.push_back(strVtrTemp[3]+','+strVtrTemp[0]);


	}
	if (strTestItem.Find("I1")!=-1)//ACPR
	{
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -101");
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;LEVel:MAXimum 28");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd=_T("1;SOURce:RFGenerator:PCBits AUP");						
		DEVICE_WRITE(strCmd)
			strCmd.Format("1;CONFigure:SPECtrum:ACP:CONTrol %d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;INITiate:SPECtrum:ACP");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:CONTrol:FOFFset:ACP1 ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:CONTrol:FOFFset:ACP2 ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:CONTrol:FOFFset:ACP3 ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:CONTrol:FOFFset:ACP4 ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:LIMit:ACP1 OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:LIMit:ACP2 OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:LIMit:ACP3 OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:LIMit:ACP4 OFF");
		DEVICE_WRITE(strCmd)
			iRetryTimes=50;
		do 
		{
			strCmd=_T("1;FETCh:SPECtrum:ACP:STATus?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("RDY")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("1;FETCh:SPECtrum:ACP?");
		DEVICE_QUERY(strCmd)
			strReadBuf=Device_GetReadBuf();
		strCmd=_T("1;ABORt:NPOWer");
		DEVICE_WRITE(strCmd)
			strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		strTemp.Format("0,0,%s,%s,%s,%s",strVtrTemp[10],strVtrTemp[13],strVtrTemp[8],strVtrTemp[15]);//(0,0,low adj,up adj,low alt,up alt) to fit check result in meascpp
		strVtrResult.push_back(strTemp);

	}
	if(strTestItem.Find("J1")!=-1)//Min power
	{

			strCmd=_T("1;SOURce:RFGenerator:LEVel:FFCH -7.4");
		DEVICE_WRITE(strCmd)
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -20");
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;LEVel:MAXimum -33;*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd=_T("1;SOURce:RFGenerator:PCBits ADOW");
		DEVICE_WRITE(strCmd)
			Sleep(500);
			strCmd.Format("1;CONFigure:NPOWer:CONTrol %d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;INITiate:NPOWer");
		DEVICE_WRITE(strCmd)
			iRetryTimes=50;
		do 
		{
			strCmd=_T("1;FETCh:NPOWer:STATus?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("RDY")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		iRetryTimes=50;
		do 
		{
			strCmd=_T("1;STATus:OPERation:SYMBolic?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("NONE")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("NONE")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("1;FETCh:NPOWer?");
		DEVICE_QUERY(strCmd)
			strReadBuf=Device_GetReadBuf();
		strCmd=_T("1;ABORt:NPOWer");
		DEVICE_WRITE(strCmd)

			strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		strVtrResult.push_back(strVtrTemp[3]+','+strVtrTemp[0]);
	}
	strCmd=_T("1;SOURce:RFGenerator:LEVel:FFCH -15.6");
	DEVICE_WRITE(strCmd)
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -65");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;LEVel:MODE AUT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:PCBits AUTO");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;
}
int CFuncCDMATest_CMU::ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem,int powercnt)
{
	CString strReadBuf;
	CString strCmd;
	int iDeviceErr;
	CString strCellPower;
	int iRetryTimes=50;
	int iTimeout=10;
	CStringVtr strVtrTemp;
	CString strTemp;
	int iCountPwr=4,iPwrSel=30;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);
	if ((strTestItem.Find("A1")!=-1)||(strTestItem.Find("B1")!=-1)||(strTestItem.Find("C1")!=-1)||(strTestItem.Find("D1")!=-1)||
		(strTestItem.Find("E1")!=-1)||(strTestItem.Find("F1")!=-1)||(strTestItem.Find("G1")!=-1))//wfq@-75dBm test
	{
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -75");
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;LEVel:MAXimum 28");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd=_T("1;SOURce:RFGenerator:PCBits AUP");
		DEVICE_WRITE(strCmd);
		strCmd.Format("1;CONFigure:CDPower:CHPW:CONTrol SCAL,%d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd);
		strCmd.Format("1;CONFigure:MODulation:OVERview:CONTrol %d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;INITiate:MODulation:OVERview");
		DEVICE_WRITE(strCmd)
			iRetryTimes=50;
		do 
		{
			strCmd=_T("1;FETCh:MODulation:OVERview:STATus?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("RDY")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("1;FETCh:MODulation:OVERview?");
		DEVICE_QUERY(strCmd)
			strReadBuf=Device_GetReadBuf();
		strCmd=_T("1;ABORt:MODulation:OVERview");
		DEVICE_WRITE(strCmd)

			strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		if (strTestItem.Find("A1")!=-1)//A: Carrier feedthrough
		{
			strVtrResult.push_back(strVtrTemp[19]);
		}

		if (strTestItem.Find("B1")!=-1)//B: EVM AVG
		{
			strVtrResult.push_back(strVtrTemp[4]);
		}

		if (strTestItem.Find("C1")!=-1)//C: Frequency error
		{
			strVtrResult.push_back(strVtrTemp[25]);
		}

		if (strTestItem.Find("D1")!=-1)//D: Magnitude error
		{
			strVtrResult.push_back(strVtrTemp[10]);
		}

		if (strTestItem.Find("E1")!=-1)//E: Phase error
		{
			strVtrResult.push_back(strVtrTemp[16]);
		}

		if (strTestItem.Find("F1")!=-1)//F: Rho
		{
			strVtrResult.push_back(strVtrTemp[31]);
		}

		if (strTestItem.Find("F1")!=-1)//G: Time error
		{
			strVtrResult.push_back(strVtrTemp[28]);
		}


	}
	if(strTestItem.Find("H1")!=-1)//MAX POWER
	{
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -101");
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;LEVel:MAXimum 28");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd=_T("1;SOURce:RFGenerator:PCBits AUP");
		DEVICE_WRITE(strCmd)
			strCmd.Format("1;CONFigure:NPOWer:CONTrol %d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;INITiate:NPOWer");
		DEVICE_WRITE(strCmd)
			iRetryTimes=50;
		do 
		{
			strCmd=_T("1;FETCh:NPOWer:STATus?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("RDY")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		iRetryTimes=50;
		do 
		{
			strCmd=_T("1;STATus:OPERation:SYMBolic?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("NONE")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("NONE")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("1;FETCh:NPOWer?");
		DEVICE_QUERY(strCmd)
			strReadBuf=Device_GetReadBuf();
		strCmd=_T("1;ABORt:NPOWer");
		DEVICE_WRITE(strCmd)

			strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		strVtrResult.push_back(strVtrTemp[3]+','+strVtrTemp[0]);


	}
	if (strTestItem.Find("I1")!=-1)//ACPR
	{
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -101");
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;LEVel:MAXimum 28");
		DEVICE_WRITE(strCmd)
			strCmd=_T("*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd=_T("1;SOURce:RFGenerator:PCBits AUP");						
		DEVICE_WRITE(strCmd)
			strCmd.Format("1;CONFigure:SPECtrum:ACP:CONTrol %d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;INITiate:SPECtrum:ACP");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:CONTrol:FOFFset:ACP1 ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:CONTrol:FOFFset:ACP2 ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:CONTrol:FOFFset:ACP3 ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:CONTrol:FOFFset:ACP4 ON");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:LIMit:ACP1 OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:LIMit:ACP2 OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:LIMit:ACP3 OFF");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;CONFigure:SPECtrum:ACP:LIMit:ACP4 OFF");
		DEVICE_WRITE(strCmd)
			iRetryTimes=50;
		do 
		{
			strCmd=_T("1;FETCh:SPECtrum:ACP:STATus?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("RDY")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("1;FETCh:SPECtrum:ACP?");
		DEVICE_QUERY(strCmd)
			strReadBuf=Device_GetReadBuf();
		strCmd=_T("1;ABORt:NPOWer");
		DEVICE_WRITE(strCmd)
			strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		strTemp.Format("0,0,%s,%s,%s,%s",strVtrTemp[10],strVtrTemp[13],strVtrTemp[8],strVtrTemp[15]);//(0,0,low adj,up adj,low alt,up alt) to fit check result in meascpp
		strVtrResult.push_back(strTemp);

	}
	if(strTestItem.Find("J1")!=-1)//Min power
	{

		strCmd=_T("1;SOURce:RFGenerator:LEVel:FFCH -7.4");
		DEVICE_WRITE(strCmd)
			strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -20");
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;LEVel:MAXimum -33;*OPC?");
		DEVICE_QUERY(strCmd)
			strCmd=_T("1;SOURce:RFGenerator:PCBits ADOW");
		DEVICE_WRITE(strCmd)
			Sleep(500);
		strCmd.Format("1;CONFigure:NPOWer:CONTrol %d,SING,NONE,NONE",BurstQty);
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;INITiate:NPOWer");
		DEVICE_WRITE(strCmd)
			iRetryTimes=50;
		do 
		{
			strCmd=_T("1;FETCh:NPOWer:STATus?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("RDY")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("RDY")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		iRetryTimes=50;
		do 
		{
			strCmd=_T("1;STATus:OPERation:SYMBolic?");
			DEVICE_QUERY(strCmd)
				strReadBuf=Device_GetReadBuf();
			if (strReadBuf.Find("NONE")>-1)
			{
				break;
			}
			Sleep(100);

		} while (--iRetryTimes>0);
		if(strReadBuf.Find("NONE")==-1)
		{
			return DEVICE_QUERY_FAIL;
		}
		strCmd=_T("1;FETCh:NPOWer?");
		DEVICE_QUERY(strCmd)
			strReadBuf=Device_GetReadBuf();
		strCmd=_T("1;ABORt:NPOWer");
		DEVICE_WRITE(strCmd)

			strVtrTemp.clear();
		CStr::ParseString(strReadBuf,",",strVtrTemp);
		strVtrResult.push_back(strVtrTemp[3]+','+strVtrTemp[0]);
	}
	strCmd=_T("1;SOURce:RFGenerator:LEVel:FFCH -15.6");
	DEVICE_WRITE(strCmd)
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA -65");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;LEVel:MODE AUT");
	DEVICE_WRITE(strCmd)
		strCmd=_T("1;SOURce:RFGenerator:PCBits AUTO");
	DEVICE_WRITE(strCmd)

		return DEVICE_SUCCESS;

}

int CFuncCDMATest_CMU::ICDMATestStartRXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem)
{
	CString strCmd;
	int iDeviceErr;
	int iRetryTimes=30;

	if(strTestItem.Find("R1")!=-1)//RXSensitivityPrediction
	{
		
		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA %.2f",d_CellPower[3]);
		DEVICE_WRITE(strCmd);
		strCmd=_T("1;LEVel:MODE MANual");
		DEVICE_WRITE(strCmd)
			strCmd=_T("1;LEVel:MAXimum 28;*OPC?");
		DEVICE_QUERY(strCmd)

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
int CFuncCDMATest_CMU::ICDMATestStartRxLevelMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem,int iIndex)
{
	
	CString strCmd;
	int iDeviceErr;
	int iRetryTimes=30;


		strCmd.Format("1;SOURce:RFGenerator:POWer:CDMA %.2f",d_CellPower[iIndex]);
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
int CFuncCDMATest_CMU::ICDMATestEndCall()
{
	int iDeviceErr;
	CString strCmd;
	strCmd=_T("*CLS");
	DEVICE_WRITE(strCmd);
	return DEVICE_SUCCESS;
}
int CFuncCDMATest_CMU::ICDMATestSetLoss(int iCDMABand,const DblVtr & vLossList)
{
	CString strCmd;
	int iDeviceErr;
	CString strRes;
	//double dLossAverage;
			strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:ENABle ON");
	DEVICE_WRITE(strCmd)
		switch(iCDMABand)
	{
		case 800:
			strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE1 824.85 MHZ,OFF,%f,OFF,OFF",vLossList[0]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE2 869.85 MHZ,OFF,%f,OFF,OFF",vLossList[0]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE3 835.74 MHZ,OFF,%f,OFF,OFF",vLossList[1]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE4 880.74 MHZ,OFF,%f,OFF,OFF",vLossList[1]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE5 848.22 MHZ,OFF,%f,OFF,OFF",vLossList[2]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE6 893.22 MHZ,OFF,%f,OFF,OFF",vLossList[2]);
			DEVICE_WRITE(strCmd)

				break;
		case 1900:
			strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE1 1851.25 MHZ,OFF,%f,OFF,OFF",vLossList[0]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE2 1931.25 MHZ,OFF,%f,OFF,OFF",vLossList[0]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE3 1878.15 MHZ,OFF,%f,OFF,OFF",vLossList[1]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE4 1958.15 MHZ,OFF,%f,OFF,OFF",vLossList[1]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE5 1908.75 MHZ,OFF,%f,OFF,OFF",vLossList[2]);
			DEVICE_WRITE(strCmd)
				strCmd.Format("0;CONFigure:USER:CORRection:LOSS:TABLe:LINE6 1988.75 MHZ,OFF,%f,OFF,OFF",vLossList[2]);
			DEVICE_WRITE(strCmd)
				break;

		default:
			return DEVICE_WRITE_FAIL;
	}


	return DEVICE_SUCCESS;
}

