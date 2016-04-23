#pragma once
#include  "IFuncDev.h"

class IFuncWLANTest_Dev :public virtual IFuncDev
{
public:
	IFuncWLANTest_Dev(void);
	virtual ~IFuncWLANTest_Dev(void);
	IFuncWLANTest_Dev(PCTesterDevice pDev);

	virtual int IWLANTestInit(const CString& strAddr,const CString & strWLANAddr){return DEVICE_SUCCESS;}
	virtual int IWLANTestSetFreq(double AnalyFreq,double dUlPowerMax,double dCableloss){return DEVICE_SUCCESS;}
	virtual int IWLANTestSetType(const CString& iBurstType){return DEVICE_SUCCESS;}
	virtual int IWLANTestSetTrigger(double TriggerLevel,int iTimeout,int evmGap=50){return DEVICE_SUCCESS;}
	virtual int IWLANTestInitMeasure(int iAvgCount){return DEVICE_SUCCESS;}
	virtual int IWLANTestFetchResults(int RateType,CStringVtr & dVtr){return DEVICE_SUCCESS;}
	virtual int IWLANTestModFetchResults(int RateType,double &dPower,double &dEVM,double &FER){return DEVICE_SUCCESS;}

	virtual int IWLANTestSetDLType(const CString& strWavePath){return DEVICE_SUCCESS;}
	virtual int IWLANTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss){return DEVICE_SUCCESS;}
	virtual int IWLANTestSetDLSigOn(bool bIsOn=true){return DEVICE_SUCCESS;}
	virtual int IWLANTestSetTrackingAllOn(void){return DEVICE_SUCCESS;}
	virtual int IWLANTestSetInOutPort(int iInport,int iOutPort){return DEVICE_SUCCESS;}
};
typedef IFuncWLANTest_Dev* PIFuncWLANTest_Dev;
