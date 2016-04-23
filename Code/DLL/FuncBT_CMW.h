#pragma once
#include "FuncDev_CMW.h"
#include "IFuncBTTest_Dev.h"


class CFuncBT_CMW:public IFuncBTTest_Dev,public CFuncDev_CMW
{
public:
	CFuncBT_CMW(void);
	virtual ~CFuncBT_CMW(void);
	CFuncBT_CMW(PCTesterDevice pDev);

    int IBTTestInit(const CString& strAddr,const CString & strBTAddr);
	 int IBTTestSetFreq(double AnalyFreq,double dUlPowerMax,double dLoss);
	 int IBTTestSetType(const CString& iBurstType,const CString& iPacketType);
	 int IBTTestSetBitPattern(const CString& iBitPattern);
	 int IBTTestSetTrigger(double TriggerLevel,int iTimeout);
	 int IBTTestInitMeasure(int iAvgCount);
	 int IBTTestFetchResults(int RateType,CStringVtr & dVtr);

	 int IBTTestSetInOutPort(int iInPort,int iOutPort);
	
	 int IBTTestInitEx(const CString& strAddr,const CString strWaveForm,const CString & strBTAddr);
	 int IBTTestSetChannel(int iChannel);
	 int IBTTestSetLoss(double dLoss);
	 int IBTTestPowerMeas(double dExpPower,int iMeasCount,int iBTType,int iDH,double* dPower);
	 int IBTTestModMeas(double dExpPower,int iMeasCount,int iFreqType,double* dDeltaF);
	 int IBTTestCFDMeas(double dExpPower,int iMeasCount,double* dCFD);
	 int IBTTestICFTMeas(double dExpPower,int iMeasCount,double* dICFTkHz);
	 int IBTTestEDRModMeas(double dExpPower,int iMeasCount,int iBTType,double* dEVM_RMS,double* dEVM_PEAK);
	 int IBTTestSetCellPower(double dPower);
};
