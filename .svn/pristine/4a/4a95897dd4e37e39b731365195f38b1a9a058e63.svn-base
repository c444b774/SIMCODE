#pragma once
#include "FuncDev_CMW.h"
#include  "IWCDMACal_Dev.h"
class CFunWCDMACal_CMW: public IWCDMACal_Dev,public CFuncDev_CMW
{
public:
	CFunWCDMACal_CMW(void);
	virtual ~CFunWCDMACal_CMW(void);
    CFunWCDMACal_CMW(PCTesterDevice pDev);


	//common

	int SetInput(int iInput);
	int SetOutput(int iOutput);

	//WCDMA CAL
	int IWCDMACalInit(const CString& strAddr);
	int IWCDMACalSetXOSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower);
    int IWCDMACalSetLoss(int iWCDMABand,const DblVtr & vLossList);
	int ILTECalSetLoss(int iBand,const DblVtr & vLossList);
	int IWCDMACalSetChannel(int iBand,int iULChannel);
	int IWCDMACalSetMaxPower(double dMaxPower);
	int IWCDMASetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz);
    int IWCDMAFetchWTDPResults(DblVtr & dvtrResults);
	int IWCDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName);
    int IWCDMAFetchCPRResult(int iMeasCount,double & dCPWR);
	int IDevicesSetIOPort(int iIOPort);
	int IWCDMASetupTXRXComposite(double * dUlFreqMHz,double * dDLFreqMHz,int iNumSteps,double *dRxPowerList,double *dTxMaxLevList);
    int IWCDMAFetchTXRXResults(DblVtr & dvtrResults);
	int IGPSSetLoss(double dLoss);

	int IWCDMAESCalLinearconfig(int Mod,double dBandWidth,int iSegmentTime,DblVtr dvTRxFreq,DblVtr dvTxLvlRef,DblVtr dvRxLvl,int iNumSegment,int iNumSequence);
	// CDMA CAL

	int ICDMACalInit(const CString& strAddr);
	int ICDMACalSetLoss(int iCDMABand,const DblVtr & vLossList);
	int ICDMACalSetNormalSig(double dUlMHz,double iDlMHz,int iFreqOffKhz,double dDlPower,const CString & strWavaFileName);
	int ICDMACalSet_DLPower_On(bool bIsOn);
	int ICDMACalSet_DLPowe(double dDlPower);
	int ICDMACalSetupWTDP(int iCount,int iTimeout,double dStepPower,double dMaxinputPwl,double dULFreqMHz);
	int ICDMAFetchCTDPResults(DblVtr & dvtrResults) sealed;
	int ICDMAFetchCPRResult(int iMeasCount,double & dCPWR);
	int ICDMACalSetMaxPower(double dMaxPower);

};