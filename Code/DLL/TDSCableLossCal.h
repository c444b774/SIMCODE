#pragma once
#include "ifhandler.h"

class CTDSCableLossCal :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CTDSCableLossCal)
public:
	CTDSCableLossCal(void);
	~CTDSCableLossCal(void);
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
	int m_iTestBand;
	CString m_strTestBand;
	IntVtr m_ivTestChannelList;
	int m_iMeasureCount;
	CRangePair<double> m_dMaxPowerLimit;
	DblVtr m_dvPowerMeas;
	DblVtr m_dvGoldenPower;
	DblVtr  m_vCableLoss;

private: 
	bool TdCableLossMainFunc();	
	bool SetTdLoss();
	bool TdMakeGoldenSemple();
	bool TdSetCableLoss();
	bool TdMeasPower();
	bool ReadGoldenPower();
	bool WriteGoldenPower();

};
