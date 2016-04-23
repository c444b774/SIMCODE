#ifndef _6285TXRXCAL_H_
#define _6285TXRXCAL_H_
#include "IFHandler.h"
class CQTR6285TXRXCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CQTR6285TXRXCal)
public: 

		CQTR6285TXRXCal();
		~CQTR6285TXRXCal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	IWCDMACal_Dev* m_pFunWCDMACalDev;

private:
	bool m_bIsUseTXRXCAL;
	bool m_bIsUseSecondSweep;
	int m_iHDET_ADC_Channel;
    int m_iCurrBand;
	int m_iRefCH;
	double m_dDyRange;
    double m_dTXLimPower;
	int m_iTXLimPDMSize;
	int m_iTXLimPDMNum;
	CString m_strCurrBand;
	IntVtr m_vStepSize;
    IntVtr m_vPARange;
	DblVtr m_vTargetPower;
	DblVtr m_vStopPower;
	IntVtr m_vStartPDM;
	IntVtr m_vStopPDM;
    DblVtr m_vExpectPower;

	IntVtr m_vTXCalCHList;
    IntVtr m_vRXCalCHList;
    DblVtr m_vTXCompPower;
    IntVtr m_vTXCompPDM;
	int    m_iCalSecFreqComp;
	IntVtr m_vTXSecCompPDM;
    DblVtr m_vRXOffsetPower;
  
	
    int m_iSecondSweepPDM;
	double m_dSecondExpectedPower;
	CString m_strWaveFile;
	
    DblVtr m_vTXComPowerUpLimit;
    DblVtr m_vTXComPowerLowLimit;
   
	DblVtr m_vRXOffsetUpLimit;
	DblVtr m_vRXOffsetLowLimit;

    DblVtr  m_vCableLoss;
    
	

    QMSL_CDMA_TxLimVsFreq_RefChan_Measurement_struct  m_refChanTxLim;   	
	QMSL_CDMA_TxLin_BetaScaling_struct m_TxLinResForSecFreqComp;

private: 
	bool CQTR6285TXRXCalMainFunc();
	bool CQTR6285TX_LIN_CalFunc();
	bool CQTR6285TX_LIMComPen_CalFunc();
    bool CQTR6285RXCalFunc();
	bool CQTR6285TXRXComposite();

private:

	bool SetWCDMACALLOSS();
	bool CalculateLimPDM(int iExpectPDMNum,double dExpectPower,int iPDMSize,IntVtr & vtrLimPDMList);
	bool GetChannelPower_PDM(int iPARange,int iPDM,double dExpectedPwr,double & dMeasuredPwr);
	bool GetTXLinPowerList(int iPRangeIndex,int iStartPDM,double dExpectedPower,int iPDMNum,int iTimeOut,double dStepPower,double dULMHz,DblVtr & dPowerListResults);
	bool CalculateSecFreqCompPwr(QMSL_CDMA_TxLin_BetaScaling_struct TxLinResForSecFreqComp,IntVtr iEumPDM,DblVtr & vtrPwrList);	




 
};
#endif