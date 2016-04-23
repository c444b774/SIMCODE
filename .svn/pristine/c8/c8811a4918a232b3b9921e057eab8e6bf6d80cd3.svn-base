#pragma once
#include  "IFuncDev.h"

class IFuncGSMCal_Dev :public virtual IFuncDev
{
public:
	IFuncGSMCal_Dev(void);
	virtual ~IFuncGSMCal_Dev(void);
	IFuncGSMCal_Dev(PCTesterDevice pDev);

    //WCDMA operations
	virtual int IGSMCalInit(const CString& strAddr){return DEVICE_SUCCESS;}
	virtual int IGSMCalSetFreq(double dDLMhz,double dULMhz){return DEVICE_SUCCESS;}
    virtual int IGSMCalSetLoss(int iGSMBand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
	virtual int IGSMCalSetDLPower(double dDlPower){return DEVICE_SUCCESS;} 
	virtual int IGSMCalSetWaveForm(const CString & strWaveFile){return DEVICE_SUCCESS;} 
	virtual int IGSMCalInitAMAM_AMPM(double dExpectPower,int iStepNum,int iMeasLen,double iStepLen,int dTriggerOffset,const CString & strFilterType="NARR"){return DEVICE_SUCCESS;} 
    virtual int IGSMCalFetchMAM_AMPM_Results(float *fPower,float *fPhase,float *fFER,int iListNum){return DEVICE_SUCCESS;} 
    virtual int IGSMCalInit_IQSample(double dExpectPower,int iSampleCount,int iTriggerDelay,const CString & strFilterType="CONT3"){return DEVICE_SUCCESS;} 
    virtual int IGSMCalFetchIQ_Results(unsigned char* uIQData,unsigned char* uPower,unsigned char* uPhse,int iListNum){return DEVICE_SUCCESS;} 
	virtual int IGSMCalFetchIQ_Results_V2(float* fpPower,float* fpPhse,unsigned short *iListNum){return DEVICE_SUCCESS;} 
	virtual int IGSMTestInitTxDelay(double powLevel){return DEVICE_SUCCESS;} 
	virtual int IGSMTestGetAllMod(float * mod){return DEVICE_SUCCESS;}
};
typedef IFuncGSMCal_Dev* PIFuncGSMCal_Dev;