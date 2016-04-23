#pragma once
#include "ifhandler.h"

class CDualCarrier :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CDualCarrier)
public:
	CDualCarrier(void);
	~CDualCarrier(void);
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

	int  m_iBand;
	int m_iRFMode;
	int m_iNVMode;
	int  m_iCHannel;
	int m_iRxPath;
	int m_iFTM_MODE_ID;
	IntVtr m_ivRxAction;
	DblVtr m_dvExpectedPower;
	IntVtr m_ivRxMaxLimits;
	IntVtr m_ivRxMinLimits;

private: 
		bool CDualCarrierMainFunc();
		bool CDualCarrierFunc();
		bool CDualCarrierFastFunc();

};
