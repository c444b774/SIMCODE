#pragma once
#include "ifhandler.h"

class CLteTestCall :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CLteTestCall)
public:
	CLteTestCall(void);
	~CLteTestCall(void);
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
	bool LteTestStartCallMainFunc();
	bool LteTestStartCallFunc();

private:
	int m_iBand;
	CString m_strBand;
	int m_iLTEMode;
	CString m_strLTEMode;
	int m_iULChannel;
	bool m_bTddMode;
	CString m_strWaveFile;


};
