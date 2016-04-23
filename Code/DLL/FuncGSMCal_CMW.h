#pragma once
#include "FuncDev_CMW.h"
#include  "IFuncGSMCal_Dev.h"
class CFunGSMCal_CMW: public IFuncGSMCal_Dev,public CFuncDev_CMW
{
public:
	CFunGSMCal_CMW(void);
	virtual ~CFunGSMCal_CMW(void);
    CFunGSMCal_CMW(PCTesterDevice pDev);


	//common

	int SetInput(int iInput);
	int SetOutput(int iOutput);

	int IGSMCalInit(const CString& strAddr);
	int IGSMCalSetLoss(int iGSMBand,const DblVtr & vLossList);
	int IGSMCalSetFreq(double dDLMhz,double dULMhz);
	int IGSMCalSetDLPower(double dDlPower);
	int IGSMCalSetWaveForm(const CString & strWaveFile);
	int IGSMCalInitAMAM_AMPM(double dExpectPower,int iStepNum,int iMeasLen,double iStepLen,int iTriggerOffset,const CString & strFilterType="NARR");
    int IGSMCalFetchMAM_AMPM_Results(float *fPower,float *fPhase,float *fFER,int iListNum);
	int IGSMCalInit_IQSample(double dExpectPower,int iSampleCount,int iTriggerDelay,const CString & strFilterType);
	int IGSMCalFetchIQ_Results(unsigned char* uIQData,unsigned char* uPower,unsigned char* uPhse,int iListNum);	

};