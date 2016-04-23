#pragma once
#include "ifhandler.h"

class CEndTDSCal :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CEndTDSCal)
public:
	CEndTDSCal(void);
	~CEndTDSCal(void);
	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	IWCDMACal_Dev* m_pFunTDSCalDev;

private:
	bool m_bEnterOnline;

private: 
	bool CEndTDSCalMainFunc();
	bool CEndTDSCalFunc();
};
