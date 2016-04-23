#pragma once
#include "FuncDev_CMW.h"
#include "IFuncWLANTest_Dev.h"


class CFuncWLAN_CMW:public IFuncWLANTest_Dev,public CFuncDev_CMW
{
public:
	CFuncWLAN_CMW(void);
	virtual ~CFuncWLAN_CMW(void);
	CFuncWLAN_CMW(PCTesterDevice pDev);

     int IWLANTestInit(const CString& strAddr,const CString & strWLANAddr);
	 int IWLANTestSetFreq(double AnalyFreq,double dUlPowerMax,double dCableloss);
	 int IWLANTestSetType(const CString& iBurstType);
	 int IWLANTestSetTrigger(double TriggerLevel,int iTimeout,int evmGap=50);
	 int IWLANTestInitMeasure(int iAvgCount);
	 int IWLANTestFetchResults(int RateType,CStringVtr & dVtr);
	 int IWLANTestModFetchResults(int RateType,double &dPower,double &dEVM,double &FER);
	 int IWLANTestSetTrackingAllOn(void);
	 int IWLANTestSetDLType(const CString& strWavePath);
	 int IWLANTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss);
	 int IWLANTestSetDLSigOn(bool bIsOn);

	 int IWLANTestSetInOutPort(int iInport,int iOutPort);
};
