#include "StdAfx.h"
#include "FuncWCDMATest_SP6010.h"

CFuncWCDMATest_SP6010::CFuncWCDMATest_SP6010(void)
{
}

CFuncWCDMATest_SP6010::~CFuncWCDMATest_SP6010(void)
{
}

CFuncWCDMATest_SP6010::CFuncWCDMATest_SP6010(PCTesterDevice pDev):CFuncDev_SP6010(pDev)
{

}
int CFuncWCDMATest_SP6010::ITDSCDMAInitSet(const CString& strAddr)
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
int CFuncWCDMATest_SP6010::ITDSCDMAACLR(const int icount,double dACLRValue[])
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMABER(const int iSample,double dCellPower,double *dBER)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMACLPC(const int icount,bool *bResult)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMAFreqErr(const int icount,double dCellPower,double *dFER)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMAHandOver(int iBand,int iULChannel)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMAMaxPower(const int icount,double *dMaxPower)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMAMinPower(const int icount,double *dMinPower)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMAModAnalysis(const int icount,double *dRho,double *dEVM,double *dPVE,double *dPhaseErr,double *dMagErr,double *dOgnOfst,double *dIQI)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMAOBW(const int icount,double *dOBWValue)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMAPeakCDP(const int icount,double *dPCDErr)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMAPwrTemplate(const int icount,double dPTValue[])
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMASEMask(const int icount,int *isPass,double dSEMask[])
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMASetLoss(int iBand,const DblVtr & vLossList)
{
	return DEVICE_SUCCESS;
}
int CFuncWCDMATest_SP6010::ITDSCDMASetPower(const double dCellPower,const double dTargetPower,const int iPowerCtrlBit)
{
	return DEVICE_SUCCESS;
}