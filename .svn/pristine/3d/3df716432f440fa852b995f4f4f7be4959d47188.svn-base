#pragma once
#include "FuncDev_8820.h"
#include  "IWCDMACal_Dev.h"
class CFuncWCDMACAL_8820: public IWCDMACal_Dev,public CFuncDev_8820
{
public:
	CFuncWCDMACAL_8820(void);
	CFuncWCDMACAL_8820(PCTesterDevice pDev);
	virtual ~CFuncWCDMACAL_8820(void);

	 int IWCDMACalInit(const CString& strAddr);
	 int IWCDMACalSetXOSig(double dUlMHz,double dDlMHz,int iFreqOffKhz,double dDlPower);
	 int IWCDMACalSetLoss(int iWCDMABand,const DblVtr & vLossList);
	 int ILTECalSetLoss(int iBand,const DblVtr & vLossList);
	 int IWCDMACalSetChannel(int iBand,int iULChannel);
	 int IWCDMACalSetMaxPower(double dMaxPower);
	 int IWCDMASetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz);
	 int IWCDMAFetchWTDPResults(DblVtr & dvtrResults);
	 int IWCDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName);
     int IWCDMASetupTXRXComposite(double * dUlFreqMHz,double * dDLFreqMHz,int iNumSteps,double *dRxPowerList,double *dTxMaxLevList);
	 int IWCDMAFetchTXRXResults(DblVtr & dvtrResults);
     int IWCDMAFetchCPRResult(int iMeasCount,double & dCPWR);
	 int IWCDMAESCalLinearconfig(int Mod,double dBandWidth,int iSegmentTime,DblVtr dvTRxFreq,DblVtr dvTxLvlRef,DblVtr dvRxLvl,int iNumSegment,int iNumSequence);

	 int IDevicesSetIOPort(int iIOPort);
	 int IGPSSetLoss(double dLoss);
	 int ICDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName);
	 int ICDMACalSet_DLPower_On(bool bIsOn=true);
	 int ICDMACalSet_DLPowe(double dDlPower);
	 int ICDMAFetchCPRResult(int iMeasCount,double & dCPWR);
	 int ICDMACalSetMaxPower(double dMaxPower);
	 
	
    

};
