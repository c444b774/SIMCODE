#pragma once
#include  "IFuncDev.h"

class IWCDMACal_Dev :public virtual IFuncDev
{
public:
	IWCDMACal_Dev(void);
	virtual ~IWCDMACal_Dev(void);
	IWCDMACal_Dev(PCTesterDevice pDev);

    //WCDMA operations
	virtual int IWCDMACalInit(const CString& strAddr){return DEVICE_SUCCESS;}
	virtual int IWCDMACalSetXOSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower){return DEVICE_SUCCESS;}
    virtual int IWCDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName=""){return DEVICE_SUCCESS;}
	virtual int IWCDMACalSetLoss(int iWCDMABand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
	virtual int ILTECalSetLoss(int iBand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
	virtual int IWCDMACalSetChannel(int iBand,int iULChannel){return DEVICE_SUCCESS;}
	virtual int IWCDMACalSetMaxPower(double dMaxPower){return DEVICE_SUCCESS;}
	virtual int IWCDMASetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz){return DEVICE_SUCCESS;}
    virtual int IWCDMAFetchWTDPResults(DblVtr & dvtrResults){return DEVICE_SUCCESS;} 
    virtual int IWCDMAFetchCPRResult(int iMeasCount,double & dCPWR){return DEVICE_SUCCESS;} 
	virtual int IWCDMAESCalLinearconfig(int iMod,double dBandWidth,int iSegmentTime,DblVtr dvTRxFreq,DblVtr dvTxLvlRef,DblVtr dvRxLvl,int iNumSegment,int iNumSequence){return DEVICE_SUCCESS;}
	virtual int IDevicesSetIOPort(int iIOPort){return DEVICE_SUCCESS;}
	virtual int IGPSSetLoss(double dLoss){return DEVICE_SUCCESS;}
	virtual int IWCDMASetupTXRXComposite(double * dUlFreqMHz,double * dDLFreqMHz,int iNumSteps,double *dRxPowerList,double *dTxMaxLevList){return DEVICE_SUCCESS;} 
    virtual int IWCDMAFetchTXRXResults(DblVtr & dvtrResults){return DEVICE_SUCCESS;} 
	//CDMA operations
    virtual int ICDMACalInit(const CString& strAddr){return DEVICE_SUCCESS;}
    virtual int ICDMACalSetLoss(int iCDMABand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
	virtual int ICDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName=""){return DEVICE_SUCCESS;}
	virtual int ICDMACalSet_DLPower_On(bool bIsOn=true){return DEVICE_SUCCESS;}
	virtual int ICDMACalSetupWTDP(int Count,int iTimeout,double dStepPower,double dMaxinputPwl=0,double dULFreqMHz=0){return DEVICE_SUCCESS;}
	virtual int ICDMAFetchCTDPResults(DblVtr & dvtrResults){return DEVICE_SUCCESS;} 
	virtual int ICDMAFetchCPRResult(int iMeasCount,double & dCPWR){return DEVICE_SUCCESS;} 
	virtual int ICDMACalSet_DLPowe(double dDlPower){return DEVICE_SUCCESS;}
    virtual int ICDMACalSetMaxPower(double dMaxPower){return DEVICE_SUCCESS;}
	virtual int ICDMACalSetBand(int iCDMABand){return DEVICE_SUCCESS;}
};
typedef IWCDMACal_Dev* PIWCDMACal_Dev;