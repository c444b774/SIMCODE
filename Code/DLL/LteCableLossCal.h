#pragma once
#include "ifhandler.h"

class CLteCableLossCal :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CLteCableLossCal)
public:
	CLteCableLossCal(void);
	~CLteCableLossCal(void);

	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	PIWCDMACal_Dev m_pFuncLteDev;
	PIFuncWCDMATest_Dev m_pFuncLteTestDev;
private:
	bool m_bPowerMeasType;
	int m_iTestBand;
	int m_iNVOffset;
	CString m_strTestBand;
	IntVtr m_ivTestChannelList;
	int m_iMeasureCount;
	CRangePair<double> m_dMaxPowerLimit;
	int m_iPARange;
	int m_iPDM;
	int m_iBias;
	DblVtr m_dvPowerMeas;
	DblVtr m_dvGoldenPower;
	DblVtr  m_vCableLoss;

private: 
	bool LteCableLossMainFunc();	
	bool SetLteLoss();
	bool LteMakeGoldenSemple();
	bool LteSetCableLoss();
	bool LteMeasPower();
	bool LteMeasPowerEx();
	bool ReadGoldenPower();
	bool WriteGoldenPower();
};
