#ifndef _8615TXRXCAL_H_
#define _8615TXRXCAL_H_
#include "IFHandler.h"
class CQTR8615TXRXCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CQTR8615TXRXCal)
public: 

		CQTR8615TXRXCal();
		~CQTR8615TXRXCal();
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


private: 
	bool CQTR8615TXRXCallMainFunc();
	bool CQTR8615TX_LIN_CalFunc();
	bool CQTR8615TX_LIMComPen_CalFunc();
    bool CQTR8615RXCalFunc();
	bool CQTR8615TXRXComposite();

private:

	bool SetWCDMACALLOSS();
	bool CalculateLimPDM(int iExpectPDMNum,double dExpectPower,int iPDMSize,IntVtr & vtrLimPDMList);
	bool GetChannelPower_PDM(int iPARange,int iPDM,double dExpectedPwr,double & dMeasuredPwr);
	bool GetTXLinPowerList(int iPRangeIndex,int iStartPDM,double dExpectedPower,int iPDMNum,int iTimeOut,double dStepPower,double dULMHz,DblVtr & dPowerListResults);
	




 
};
#endif