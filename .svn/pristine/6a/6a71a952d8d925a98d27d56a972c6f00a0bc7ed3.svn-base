#pragma once
#include "FuncDev_SP6010.h"
#include  "IFuncWCDMATest_Dev.h"
class CFuncWCDMATest_SP6010: public IFuncWCDMATest_Dev,public CFuncDev_SP6010
{
public:
	CFuncWCDMATest_SP6010(void);
	CFuncWCDMATest_SP6010(PCTesterDevice pDev);
	virtual ~CFuncWCDMATest_SP6010(void);

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


};
