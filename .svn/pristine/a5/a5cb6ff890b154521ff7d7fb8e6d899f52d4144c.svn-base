#pragma once
#include "FuncDev_CMW.h"
#include "ifuncwcdmatest_dev.h"

class CFuncWCDMATest_CMW :
	public IFuncWCDMATest_Dev,public CFuncDev_CMW
{
public:
	CFuncWCDMATest_CMW(void);
	~CFuncWCDMATest_CMW(void);
	CFuncWCDMATest_CMW(PCTesterDevice pDev);
	//lte test
	int ILteInitSet(const CString& strAddr,const CString strWaveForm,const CString strLTEMode);
	int ILteHandOver(int iBand,int iULChannel);
	int ILteSetPower(double dCellPower,double dTargetPower,int iTPC);
	int ILteMeasConfig(bool bIsTDD,int iBan);
	int ILteConfigWaveForm(int iNumRB,int iStartRB,int iMCS);
	int ILteTestPower(const int icount,double *dPower);
	int ILteTxQual(const int icount,double *dEVM,double *dFERPPM,double *dOgnOfst,double *dSptrFlat,double *dInbEm);
	int ILteSEMask(const int icount,int *isPass,double dSEMask[]);
	int ILteACLR(const int icount,int *isPass,double dACLRValue[]);
	int ILteOBW(const int icount,double *dOBW);
	int ILteSetLoss(int iBand,const DblVtr & vLossList);
	// wcdma test
	int IWCDMATestInitWCDMAtest(const CString& strAddr);
	int IWCDMATestHandOver(int iBand,int iULChannel);
	int IWCDMATestMaxPower(int icount,double *dMaxPower);
	int IWCDMATestOBW(int icount,double *dOBWValue);
	int IWCDMATestMinPower(int icount,double *dMinPower);
	int IWCDMATestACLR(int icount,double dACLRValue[]);
	int IWCDMATestSEMask(int icount,int *iSMASK);
	int IWCDMATestILPC(int *iResultStepE,int *iResultStepF);
	int IWCDMATestModAnalysis(const int icount,const double dTargetPower,double *dPowerValue,double dModValue[]);
	int IWCDMATestBER(int iSample,double dCellPower,double *dBER);
	int IWCDMATestSetLoss(int iWCDMABand,const DblVtr & vLossList);
};
