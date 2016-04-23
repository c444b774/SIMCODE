#ifndef _CDMATXRXCAL_H_
#define _CDMATXRXCAL_H_
#include "IFHandler.h"
class CCDMATXRXCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CCDMATXRXCal)
public: 

		CCDMATXRXCal();
		~CCDMATXRXCal();
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



    QMSL_CDMA_TxLimVsFreq_RefChan_Measurement_struct  m_refChanTxLim;   	

   

private: 
	bool CCDMATXRXCalMainFunc();
	bool CCDMATXRXCalTX_LIN_CalFunc();
	bool CCDMATXRXCalTX_LIMComPen_CalFunc();
    bool CCDMATXRXCalRXCalFunc();

	
private:

	bool SetCDMACALLOSS();
	bool CalculateLimPDM(int iExpectPDMNum,double dExpectPower,int iPDMSize,IntVtr & vtrLimPDMList);
	bool GetChannelPower_PDM(int iPARange,int iPDM,double dExpectedPwr,double & dMeasuredPwr);

	




 
};
#endif