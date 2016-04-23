#pragma once
#include "ifhandler.h"

class CLteTestEnd :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CLteTestEnd)
public:
	CLteTestEnd(void);
	~CLteTestEnd(void);
	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	PIFuncWCDMATest_Dev m_pFuncLteTestDev;



private: 
	bool LteEndCallMainFunc();;
	bool LteEndCall();

	int EndCall();
private:

	bool    m_bEnterOnline;
};
