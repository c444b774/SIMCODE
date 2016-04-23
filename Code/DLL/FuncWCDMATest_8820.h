#pragma once
#include "FuncDev_8820.h"
#include  "IFuncWCDMATest_Dev.h"
class CFuncWCDMATest_8820: public IFuncWCDMATest_Dev,public CFuncDev_8820
{
public:
	CFuncWCDMATest_8820(void);
	CFuncWCDMATest_8820(PCTesterDevice pDev);
	virtual ~CFuncWCDMATest_8820(void);

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
public:
	int ITDSCDMAInitSet(const CString& strAddr);
	int ITDSCDMAHandOver(int iBand,int iULChannel);
	int ITDSCDMASetPower(const double dCellPower,const double dTargetPower,const int iPowerCtrlBit);
	int ITDSCDMAMaxPower(const int icount,double *dMaxPower);
	int ITDSCDMAMinPower(const int icount,double *dMinPower);
	int ITDSCDMAFreqErr(const int icount,double dCellPower,double *dFER);
	int ITDSCDMACLPC(const int icount,bool *bResult);
	int ITDSCDMAModAnalysis(const int icount,double *dRho,double *dEVM,double *dPVE,double *dPhaseErr,double *dMagErr,double *dOgnOfst,double *dIQI);
	int ITDSCDMAPeakCDP(const int icount,double *dPCDErr);
	int ITDSCDMAACLR(const int icount,double dACLRValue[]);
	int ITDSCDMAOBW(const int icount,double *dOBWValue);
	int ITDSCDMASEMask(const int icount,int *isPass,double dSEMask[]);
	int ITDSCDMAPwrTemplate(const int icount,double dPTValue[]);
	int ITDSCDMABER(const int iSample,double dCellPower,double *dBER);
	INT ITDSCDMASetLoss(int iBand,const DblVtr & vLossList);
public:
	int ILteInitSet(const CString& strAddr,const CString strWaveForm,const CString strLTEMode);
	int ILteHandOver(int iBand,int iULChannel);
	int ILteSetPower(double dCellPower,double dTargetPower,int iTPC);
	int ILteMeasConfig(bool bIsTDD,int iBan);
	int ILteConfigWaveForm(int iNumRB,int iStartRB,int iMCS);
	int ILteTestPower(const int icount,double *dPower);
	int ILteConfiguredPower(const int icount,const double dMaxulpower,double *dPower);
	int ILteTxQual(const int icount,double *dEVM,double *dFERPPM,double *dOgnOfst,double *dSptrFlat,double *dInbEm);
	int ILteSEMask(const int icount,int *isPass,double dSEMask[]);
	int ILteACLR(const int icount,int *isPass,double dACLRValue[]);
	int ILteOBW(const int icount,double *dOBW);
	int ILteSetLoss(int iBand,const DblVtr & vLossList);

};
