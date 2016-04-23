#pragma once
#include "ifhandler.h"

class CWCN36XXBtTest :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CWCN36XXBtTest)
public:
	CWCN36XXBtTest(void);
	~CWCN36XXBtTest(void);
	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	PIFuncBTTest_Dev m_pFunBTTestDev;

private: 
	bool BTTestMainFunc();
	bool Handover();
	bool TxOutputPower();
	bool GFSKMod();
	bool CarrierFreqDrift();
	bool ICFT();
	bool EDRMod();
	bool RxBer();
	bool BTInit();
	bool BTRelease();



private:
	IntVtr m_ivChannel;
	int m_iCurrChannel;
	double m_dRxCellPower;
	double m_dLoss;
	CString m_strWaveFile;
	CString m_strBTAddr;
	unsigned char aBTAddr[6];
	CRangePair<double> m_PowerSpec;
	CRangePair<double>  m_DeltaF1Spec;
	CRangePair<double>  m_DeltaF2Spec;
	CRangePair<double>  m_CFDSpec;
	CRangePair<double>  m_ICFTSpec;
	CRangePair<double>  m_RMSDEVMSpec;
	CRangePair<double>  m_PeakDEVMSpec;
	CRangePair<double>  m_BerSpec;

	
};
