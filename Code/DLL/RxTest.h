#pragma once
#include "ifhandler.h"

class CRxTest :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CRxTest)
public:
	CRxTest(void);
	~CRxTest(void);
	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	IWCDMACal_Dev* m_pFunCalDev;

private:
	IntVtr m_ivTestChannelList;
	//
	int m_iFTMMode;
	int m_iMainFTMMode;
	int m_bEnableSecChain;
	int m_iCurrentCH;
	int m_iTestBand;
	int m_iRFmode;
	CString m_strTestBand;
	int m_iMode_ID;
	int m_iLNARange;
	int m_iOutPort;
	float m_fCellPower;
	CRangePair<double> m_dAGCLimit;

private: 
	bool RxTestMainFunc();
	bool RxTestFunc();
	bool SetRxTestLoss();
	bool EndTest();
};
