#pragma once
#include "ifhandler.h"

class CTDSMeasLoop :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CTDSMeasLoop)
public:
	CTDSMeasLoop(void);
	~CTDSMeasLoop(void);
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
	int  m_iCurrentCH;
	CString m_strTestBand;
	IntVtr m_ivTestChannelList;
	int m_iMeasureCount;
	
	CRangePair<double> m_dMaxPowerLimit;
	CRangePair<double> m_dMinPowerLimit;
	double m_dFERLimit;
	double m_dPCDPLimit;
	double m_dOBWLimit;
	double m_dRhoLimit;		
	double m_dEVMLimit;
	double m_dPVELimit;
	double m_dPERLimit;
	double m_dMagERRLimit;
	double m_dIQOffsetLimit;
	double m_dIQImLimit;
	DblVtr m_dvSEMaskLimit;
	DblVtr m_dvPwrTemLimit;
	DblVtr m_dvACLRLimit;

	double m_dRxCellPower;
	int m_iBERSamples;
	double m_dBERLimit;

	DblVtr m_dvRxPowerList;
	DblVtr m_dvRxLevelHLList;
	DblVtr m_dvRxLevelLLList;
	int m_iRxlevelDelayMs;
	DblVtr  m_vCableLoss;

private: 
	bool TDTestMeasureLoopMainFunc();	
	bool SetTDTestLOSS();
	bool TDHandOver();
	bool TDTestPower();
	bool TDTestFreqErr();
	bool TDTestModAnalysis();
	bool TDTestPeakCDP();
	bool TDTestACLR();
	bool TDTestOBW();
	bool TDTestSEMask();
	bool TDTestPwrTempate();
	bool TDTestRxBER();
	bool TDTestCLPC();
	bool TDTestRxLevel();

};
