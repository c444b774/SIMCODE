#pragma once
#include "ifhandler.h"

class CInitLTECal :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CInitLTECal)
public:
	CInitLTECal(void);
	~CInitLTECal(void);
	
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
	int m_iInPortOutPort;



private: 
	bool CInitLTECalMainFunc();
	bool CInitLTECalFunc();
};
