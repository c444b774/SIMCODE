#pragma once
#include "ifhandler.h"

class CWCN3660WlanTest :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CWCN3660WlanTest)
public:
	CWCN3660WlanTest(void);
	~CWCN3660WlanTest(void);
	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	PIFuncWLANTest_Dev m_pFunWLANTestDev;

private: 
	bool WlanTestMainFunc();
	bool Handover();
	bool TxModTest();
	bool RxPER();
	bool WlanInit();
	bool WlanRelease();
private:
	IntVtr m_ivChannel;
	int m_iCurrChannel;
	double m_dRxCellPower;
	double m_dLoss;
	CString m_strWaveFile;
	CStringVtr m_strStandardList;
	CString m_strStandard;
	CString m_strSigType;
	int m_iRate;
	int m_iPreamble;
	double m_dCLPower;
	DblVtr m_dCLPowerList;
	CRangePair<double> m_BPowerSpec;
	CRangePair<double>  m_BEVMSpec;
	CRangePair<double>  m_BFreqErrSpec;
	CRangePair<double>  m_BRSSISpec;
	CRangePair<double>  m_BPERSpec;

	CRangePair<double> m_GPowerSpec;
	CRangePair<double>  m_GEVMSpec;
	CRangePair<double>  m_GFreqErrSpec;
	CRangePair<double>  m_GRSSISpec;
	CRangePair<double>  m_GPERSpec;

	CRangePair<double> m_NPowerSpec;
	CRangePair<double>  m_NEVMSpec;
	CRangePair<double>  m_NFreqErrSpec;
	CRangePair<double>  m_NRSSISpec;
	CRangePair<double>  m_NPERSpec;
};
