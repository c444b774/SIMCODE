#pragma once
#include "ifhandler.h"

class CEndLTECal :
	public IRFCalProcess
{
		RF_DECLARE_DYNCREATE(CEndLTECal)
public:
	CEndLTECal(void);
	~CEndLTECal(void);
	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	IWCDMACal_Dev* m_pFunLTECalDev;

private:
	bool m_bEnterOnline;

private: 
	bool CEndLTECalMainFunc();
	bool CEndLTECalFunc();

};
