#pragma once
#include "ifhandler.h"

class CTDSTestCall :
	public IRFCalProcess
{
		RF_DECLARE_DYNCREATE(CTDSTestCall)
public:
	CTDSTestCall(void);
	~CTDSTestCall(void);
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
	bool CTDSTestStartCallMainFunc();
	bool CTDSTestStartCallFunc();
	bool CTDSTest_NS_StartCallFunc();


private:
	int m_iCallBand;
	CString m_strCallBand;
	int m_iCallULChannel;
	double m_dCallCellPower;
	double m_dCallTargetPower;
	double m_dBERSessionTimeOut;
	double m_dRegistTimeOut;
};
