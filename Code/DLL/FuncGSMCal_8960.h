#pragma once
#include "FuncDev_8960.h"
#include  "IFuncGSMCal_Dev.h"
class CFuncGSMCAL_8960: public IFuncGSMCal_Dev,public CFuncDev_8960
{
public:
	CFuncGSMCAL_8960(void);
	CFuncGSMCAL_8960(PCTesterDevice pDev);
	virtual ~CFuncGSMCAL_8960(void);

	int IGSMCalInit(const CString& strAddr);
	int IGSMCalSetLoss(int iGSMBand,const DblVtr & vLossList);
	int IGSMCalSetFreq(double dDLMhz,double dULMhz);
	int IGSMCalSetDLPower(double dDlPower);
	int IGSMCalInitAMAM_AMPM(double dExpectPower,int iStepNum,int iMeasLen,double iStepLen,int iTriggerOffset,const CString & strFilterType="NARR");
    int IGSMCalFetchMAM_AMPM_Results(float *fPower,float *fPhase,float *fFER,int iListNum);
	int IGSMCalInit_IQSample(double dExpectPower,int iSampleCount,int iTriggerDelay,const CString & strFilterType);
	int IGSMCalFetchIQ_Results(unsigned char* uIQData,unsigned char* uPower,unsigned char* uPhse,int iListNum);
	int IGSMCalFetchIQ_Results_V2(float* uPower,float* uPhse,unsigned short *iListNum);
	int IGSMCalSetWaveForm(const CString & strWaveFile);
	int IGSMTestGetAllMod(float * mod);
	int IGSMTestInitTxDelay(double powLevel);
};