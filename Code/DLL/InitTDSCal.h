#pragma once
#include "ifhandler.h"

class CInitTDSCal :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CInitTDSCal)
public:
	CInitTDSCal(void);
	~CInitTDSCal(void);
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
	int m_iInPortOutPort;



private: 
	bool CInitTDSCalMainFunc();
	bool CInitTDSCalFunc();
};
