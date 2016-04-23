#pragma once
#include "FuncDev_8960.h"
#include  "IFuncWCDMATest_Dev.h"
class CFuncWCDMATest_8960: public IFuncWCDMATest_Dev,public CFuncDev_8960
{
public:
	CFuncWCDMATest_8960(void);
	CFuncWCDMATest_8960(PCTesterDevice pDev);
	virtual ~CFuncWCDMATest_8960(void);

	int IWCDMATestInitWCDMAtest(const CString& strAddr);
	int IWCDMATestSetBand(CString& strBand);
	int IWCDMATestSetChannel(int iChannel);
	int IWCDMATestSetPower(const double dCellPower,const double dTargetPower,const int iPowerCtrlBit);
	int IWCDMATestHandOver(int iBand,int iULChannel);
	int IWCDMATestMaxPower(int icount,double *dMaxPower);
	int IWCDMATestMinPower(int icount,double *dMinPower);
	int IWCDMATestPower(int icount,double TargetPower,double *dMeasPower);
	int IWCDMATestWCDomain(int icount,double dWCDValue[]);
	int IWCDMATestACLR(int icount,double dACLRValue[]);
	int IWCDMATestOBW(int icount,double *dOBWValue);
	int IWCDMATestSEMask(int icount,int *iSMASK);
	int IWCDMATestBER(int iSample,double dCellPower,double *dBER);
	int IWCDMATestCPICH_RSCP(double dCellPower,double *iCPICH_RSCP);
	int IWCDMATestILPC(int *iResultStepE,int *iResultStepF);
	int IWCDMATestILPC_FailSlot(int *iResultStepE,int *iResultStepF,double * dFailSlotPower_E,double * dFailSlotPower_F,int *iNUM_E,int *iNUM_F);
	int IWCDMATestSetLoss(int iWCDMABand,const DblVtr & vLossList);	
	int IWCDMATestModAnalysis(const int icount,const double dTargetPower,double  *dPowerValue,double dModValue[]);
	int IWCDMATestMeasAll(const int icount,const int iSample,double dCellPower,double  *dPowerValue,double dModValue[],	double dACLR[],double *dOBWValue,int *iSMASK,double *dBER,double *dFER);
};