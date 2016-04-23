#ifndef _GSMRXCAL_H_
#define _GSMRXCAL_H_
#include "IFHandler.h"
class CGSMRXCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CGSMRXCal)
public: 

		CGSMRXCal();
		~CGSMRXCal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    IFuncGSMCal_Dev* m_pFunGSMCalDev;

private:
    int m_iBand;
	CString m_strBand;
	IntVtr m_vChannelList;
	int m_iChainId;
    DblVtr m_vRXPower;
	IntVtr m_vBitMask;
	IntVtr m_vRXLimitUp;
    IntVtr m_vRXLimitLow;
	int   m_ucGainRangeCount;
	CString m_strWaveFile;
	DblVtr  m_vCableLoss;
	int m_iPhoneMode;

private: 
	bool CGSMRXCalMainFunc();
	bool GSMRXCalFunc();
	bool GSMRXCalFunc_9x25();
	bool SetGSMCableLoss(); 
};
#endif