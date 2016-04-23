#ifndef _INTELLC_H_
#define _INTELLC_H_
#include "IFHandler.h"
class CIntelliCeivierCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CIntelliCeivierCal)
public: 

		CIntelliCeivierCal();
		~CIntelliCeivierCal();
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
	int m_iInPortOutPort;
    int m_iRXPath;
	int m_iChannel;
	 DblVtr  m_vCableLoss;
	 int m_iCurrBand;
	 int m_iNVModeID;
	 int m_iPhoneMode;
	 CString m_strCurrBand;
	 double m_dMinRSSI;
	 double m_dDyRange;
	 IntVtr m_ivRxPM;
	 double m_dDVGARXPower;
	 CString m_strWaveFile;

	 int m_iIntelliLNARange;
	 int m_dIntelliFreqOffsetKhz;
	 double m_dIntelliRXLevel;
     vector<CRangePair<int>> m_vrCloseLimit;
     vector<CRangePair<int>> m_vrFarLimit;
	  



private: 
	bool CIntelliCeivierCalMainFunc();
	bool CIntelliCeivierCalFunc();

	bool SetCDMACALLOSS();

 
};
#endif