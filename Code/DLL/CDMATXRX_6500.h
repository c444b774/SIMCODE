#ifndef _CDMATXRX_6500_H_
#define _CDMATXRX_6500_H_
#include "IFHandler.h"
class CCDMATXRX_6500:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CCDMATXRX_6500)
public: 

		CCDMATXRX_6500();
		~CCDMATXRX_6500();
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
	int m_iRXPath;
	int m_iCDMAIDMode;
	int m_iHDET_ADC_Channel;
    int m_iCurrBand;
	int m_iNVModeID;
	int m_iRefCH;
	double m_dDyRange;
    double m_dTXLimPower;
	int m_iTXLimPDMSize;
	int m_iTXLimPDMNum;

	CString m_strWaveFile;
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

     
    DblVtr m_vTXComPowerUpLimit;
    DblVtr m_vTXComPowerLowLimit;
   
	DblVtr m_vRXOffsetUpLimit;
	DblVtr m_vRXOffsetLowLimit;

    DblVtr  m_vCableLoss;
	double  m_dDeltaLimit;


   
	double  m_dDeviceDynRange;
    IntVtr  m_vSecSweepStopPDMList;

    QMSL_CDMA_TxLimVsFreq_RefChan_Measurement_struct  m_refChanTxLim;   	

   

private: 
	bool CCDMATXRX_6500MainFunc();
	bool CCDMATXRX_6500TX_LIN_CalFunc();
	bool CCDMATXRX_6500TX_LIMComPen_CalFunc();
    bool CCDMATXRX_6500RXCalFunc();
	bool C6500TXRXComposite();

	
private:

	bool SetCDMACALLOSS();
	bool CalculateLimPDM(int iExpectPDMNum,double dExpectPower,int iPDMSize,IntVtr & vtrLimPDMList);
	bool GetChannelPower_PDM(int iPARange,int iPDM,double dExpectedPwr,double & dMeasuredPwr);
	bool GetTXLinPowerList(int iPRangeIndex,int iStartPDM,double dExpectedPower,int iPDMNum,int iTimeOut,double dStepPower,double dULMHz,DblVtr & dPowerListResults);

	




 
};
#endif