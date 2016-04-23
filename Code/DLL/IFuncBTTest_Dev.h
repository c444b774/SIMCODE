#pragma once
#include  "IFuncDev.h"

class IFuncBTTest_Dev :public virtual IFuncDev
{
public:
	IFuncBTTest_Dev(void);
	virtual ~IFuncBTTest_Dev(void);
	IFuncBTTest_Dev(PCTesterDevice pDev);

	virtual int IBTTestInit(const CString& strAddr,const CString & strBTAddr){return DEVICE_SUCCESS;}
	virtual int IBTTestSetFreq(double AnalyFreq,double dUlPowerMax,double dLoss){return DEVICE_SUCCESS;}
	virtual int IBTTestSetType(const CString& iBurstType,const CString& iPacketType){return DEVICE_SUCCESS;}
	virtual int IBTTestSetBitPattern(const CString& iBitPattern){return DEVICE_SUCCESS;}
	virtual int IBTTestSetTrigger(double TriggerLevel,int iTimeout){return DEVICE_SUCCESS;}
	virtual int IBTTestInitMeasure(int iAvgCount){return DEVICE_SUCCESS;}
	virtual int IBTTestFetchResults(int RateType,CStringVtr & dVtr){return DEVICE_SUCCESS;}

	virtual int IBTTestSetInOutPort(int iInPort,int iOutPort){return DEVICE_SUCCESS;}

	virtual int IBTTestInitEx(const CString& strAddr,const CString strWaveForm,const CString & strBTAddr){return DEVICE_SUCCESS;}
	virtual int IBTTestSetChannel(int iChannel){return DEVICE_SUCCESS;}
	virtual int IBTTestSetLoss(double dLoss){return DEVICE_SUCCESS;}
	virtual int IBTTestPowerMeas(double dExpPower,int iMeasCount,int iBTType,int iDH,double* dPower){return DEVICE_SUCCESS;}
	virtual int IBTTestModMeas(double dExpPower,int iMeasCount,int iFreqType,double* dDeltaF){return DEVICE_SUCCESS;}	
	virtual int IBTTestCFDMeas(double dExpPower,int iMeasCount,double* dCFD){return DEVICE_SUCCESS;}
	virtual int IBTTestICFTMeas(double dExpPower,int iMeasCount,double* dICFTkHz){return DEVICE_SUCCESS;}
	virtual int IBTTestEDRModMeas(double dExpPower,int iMeasCount,int iBTType,double* dEVM_RMS,double* dEVM_PEAK){return DEVICE_SUCCESS;}
	virtual int IBTTestSetCellPower(double dPower){return DEVICE_SUCCESS;}	

};
typedef IFuncBTTest_Dev* PIFuncBTTest_Dev;
