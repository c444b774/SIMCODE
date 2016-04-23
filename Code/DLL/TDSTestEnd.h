#pragma once
#include "ifhandler.h"

class CTDSTestEnd :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CTDSTestEnd)
public:
	CTDSTestEnd(void);
	~CTDSTestEnd(void);
	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	PIFuncWCDMATest_Dev m_pFuncTDSTestDev;



private: 
	bool TDEndCallMainFunc();;
	bool TDEndCallFunc();

	int EndCall();
private:

	bool    m_bEnterOnline;
};
