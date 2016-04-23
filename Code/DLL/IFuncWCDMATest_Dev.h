#pragma once
#include  "IFuncDev.h"

class IFuncWCDMATest_Dev:public virtual IFuncDev
{
public:
	IFuncWCDMATest_Dev(void);
	virtual ~IFuncWCDMATest_Dev(void);
	IFuncWCDMATest_Dev(PCTesterDevice pDev);
	//WCDMA TEST interface
public:

	virtual int IWCDMATestInitWCDMAtest(const CString& strAddr){return DEVICE_SUCCESS;}
	virtual int IWCDMATestSetChannel(int iChannel){return DEVICE_SUCCESS;}
	virtual int IWCDMATestSetBand(CString& strBand){return DEVICE_SUCCESS;}	
	virtual int IWCDMATestSetPower(const double dCellPower,const double dTargetPower,const int iPowerCtrlBit){return DEVICE_SUCCESS;}
	virtual int IWCDMATestHandOver(int iBand,int iULChannel){return DEVICE_SUCCESS;}
	virtual int IWCDMATestMaxPower(int icount,double *dMaxPower){return DEVICE_SUCCESS;}
	virtual int IWCDMATestMinPower(int icount,double *dMinPower){return DEVICE_SUCCESS;}
	virtual int IWCDMATestPower(int icount,double TargetPower,double *dMeasPower){return DEVICE_SUCCESS;}
	virtual int IWCDMATestWCDomain(int icount,double dWCDValue[]){return DEVICE_SUCCESS;}
	virtual int IWCDMATestACLR(int icount,double dACLRValue[]){return DEVICE_SUCCESS;}
	virtual int IWCDMATestOBW(int icount,double *dOBWValue){return DEVICE_SUCCESS;}
	virtual int IWCDMATestSEMask(int icount,int *iSMASK){return DEVICE_SUCCESS;}
	virtual int IWCDMATestBER(int iSample,double dCellPower,double *dBER){return DEVICE_SUCCESS;}
	virtual int IWCDMATestCPICH_RSCP(double dCellPower,double *iCPICH_RSCP){return DEVICE_SUCCESS;}
	virtual int IWCDMATestILPC(int *iResultStepE,int *iResultStepF){return DEVICE_SUCCESS;}
    virtual int IWCDMATestILPC_FailSlot(int *iResultStepE,int *iResultStepF,double * dFailSlotPower_E,double * dFailSlotPower_F,int *iNUM_E,int *iNUM_F){return DEVICE_SUCCESS;}
	virtual int IWCDMATestSetLoss(int iWCDMABand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
	virtual int IWCDMATestModAnalysis(const int icount,const double dTargetPower,double  *dPowerValue,double dModValue[]){return DEVICE_SUCCESS;}
	virtual int IWCDMATestMeasAll(const int icount,const int iSample,double dCellPower,double  *dPowerValue,double dModValue[],	double dACLR[],double *dOBWValue,int *iSMASK,double *dBER,double *dFER){return DEVICE_SUCCESS;}

public:

	virtual int ITDSCDMAInitSet(const CString& strAddr){return DEVICE_SUCCESS;}
	virtual int ITDSCDMASetChannel(int iChannel){return DEVICE_SUCCESS;}
	virtual int ITDSCDMASetBand(CString& strBand){return DEVICE_SUCCESS;}	
	virtual int ITDSCDMASetPower(const double dCellPower,const double dTargetPower,const int iPowerCtrlBit=2){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAHandOver(int iBand,int iULChannel){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAMaxPower(const int icount,double *dMaxPower){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAMinPower(const int icount,double *dMinPower){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAPower(const int icount,double TargetPower,double *dMeasPower){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAFreqErr(const int icount,double dCellPower,double *dFER){return DEVICE_SUCCESS;}
	virtual int ITDSCDMACLPC(const int icount,bool *bResult){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAACLR(const int icount,double dACLRValue[]){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAOBW(const int icount,double *dOBWValue){return DEVICE_SUCCESS;}
	virtual int ITDSCDMASEMask(const int icount,int *isPass,double dSEMask[]){return DEVICE_SUCCESS;}
	virtual int ITDSCDMABER(const int iSample,double dCellPower,double *dBER){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAPwrTemplate(const int icount,double dPTValue[]){return DEVICE_SUCCESS;}		
	virtual int ITDSCDMAModAnalysis(const int icount,double *dRho,double *dEVM,double *dPVE,double *dPhaseErr,double *dMagErr,double *dOgnOfst,double *dIQI){return DEVICE_SUCCESS;}
	virtual int ITDSCDMAPeakCDP(const int icount,double *dPCDErr){return DEVICE_SUCCESS;}
	virtual int ITDSCDMASetLoss(int iBand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
public:
	virtual int ILteInitSet(const CString& strAddr,const CString strWaveForm,const CString strLTEMode){return DEVICE_SUCCESS;}
	virtual int ILteHandOver(int iBand,int iULChannel){return DEVICE_SUCCESS;}
	//iTPC::0-ALLM1,1,ALL1,2-AUTO
	virtual int ILteSetPower(double dCellPower,double dTargetPower,int iTPC){return DEVICE_SUCCESS;}
	virtual int ILteMeasConfig(bool bIsTDD,int iBan){return DEVICE_SUCCESS;}
	virtual int ILteConfigWaveForm(int iNumRB,int iStartRB,int iMCS){return DEVICE_SUCCESS;}
	virtual int ILteTestPower(const int icount,double *dPower){return DEVICE_SUCCESS;}
	virtual int ILteConfiguredPower(const int icount,const double dMaxulpower,double *dPower){return DEVICE_SUCCESS;}
	virtual int ILteTxQual(const int icount,double *dEVM,double *dFERPPM,double *dOgnOfst,double *dSptrFlat,double *dInbEm){return DEVICE_SUCCESS;}
	virtual int ILteSEMask(const int icount,int *isPass,double dSEMask[]){return DEVICE_SUCCESS;}
	virtual int ILteACLR(const int icount,int *isPass,double dACLRValue[]){return DEVICE_SUCCESS;}
	virtual int ILteOBW(const int icount,double *dOBW){return DEVICE_SUCCESS;}
	virtual int ILteSetLoss(int iBand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
};
typedef IFuncWCDMATest_Dev* PIFuncWCDMATest_Dev;
