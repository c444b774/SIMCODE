#pragma once
#include "ifhandler.h"

class CLteMeasLoop :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CLteMeasLoop)
public:
	CLteMeasLoop(void);
	~CLteMeasLoop(void);
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
	bool LteTestMainFunc();
	bool LteMinPower();
	bool LteMaxPower();
	bool LteConfiguredTxPower();
	bool LteTxQual();
	bool LteSEMask();
	bool LteACLR();
	bool LteOBW();
	bool LteBlockErr();
	bool LteHandOver();
	bool LteRecall();
	bool SetLteTestLoss();


private:
	int m_iTestBand;
	CString m_strTestBand;
	IntVtr m_ivTestChannelList;
	int m_iRetryTime;
	int m_iDLChannel;
	int m_iCurrentCH;
	bool m_bTddMode;
	int m_iNumRB;
	int m_iStartRB;
	int m_iMCS;
	CString m_strWaveFile;
	DblVtr m_vCableLoss;
	int m_iMeasureCount;
	CRangePair<double> m_dMaxPowerLimit;
	CRangePair<double> m_dTxErrorLimit;
	CRangePair<double> m_dMinPowerLimit;
	DblVtr m_dvTxQualPowerList;
	DblVtr m_dFERLimit;
	double m_dOBWLimit;	
	DblVtr m_dEVMLimit;
	DblVtr m_dOrigOffsetLimit;
	DblVtr m_dvSEMaskLimit;
	DblVtr m_dvACLRLimit;

	double m_dRxCellPower;
	int m_iBLERSamples;
	double m_dBLERLimit;
};