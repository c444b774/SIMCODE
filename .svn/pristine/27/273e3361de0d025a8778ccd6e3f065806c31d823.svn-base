#ifndef _GSM_EDGE_NSFT_MEASLOOP_H
#define _GSM_EDGE_NSFT_MEASLOOP_H
#include "IFHandler.h"
class CGSM_EDGE_NSFT_MeasLoop:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CGSM_EDGE_NSFT_MeasLoop)
public: 

		CGSM_EDGE_NSFT_MeasLoop();
		~CGSM_EDGE_NSFT_MeasLoop();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    PIFuncGSMTest_Dev m_pFunGSMTestDev;
	PCConfigSetting		m_Pcfg;


private: 
	bool CGSM_EDGE_NSFT_MeasLoopMainFunc();
	bool CGSM_EDGE_NSFT_MeasLoopFunc();

	bool SetGSMTestLOSS();
	bool StartTxMeasurment(CString strTestItem);
	bool CheckTXResult(int nIndex,CString strBand,CString strChan,CString strTestItem);
	bool CheckTXResultEdge(int nIndex,CString strBand,CString strChan,CString strTestItem);
	bool StartRxLevelMeasurment(CString strTestItem);
	bool CheckRXLevelResult(int nIndex,CString strBand,CString strChan,CString strTestItem);
	bool StartRxBerMeasurment(CString strTestItem);
	bool CheckRXBerResult(int nIndex,CString strBand,CString strChan,CString strTestItem);

	int	 GetItemCode(int nMode,int Band,int Channel,int PowerLevel);

private:

	//for test use
	int		m_IsEdge;
	bool	m_bIsStopWhileFail;
	int		m_iFailFlag;

	int		m_iCurrBand;
	CString m_strCurrBand;

	bool	m_bUseCfgPara;
	DblVtr  m_vCableLoss;

	IntVtr	m_iTestChan;
	int		m_intChNum;

	IntVtr	m_iTestPcl;
	IntVtr	m_intCh_PclNum;

	int		m_chIndex;
	int		m_pclIndex;

	int		m_iRxlevel;
	int		m_iCallCurrLim;

	double	m_dPhaseErrAvg;
	double	m_dPhaseErrMax;
	double	m_dFreqErr;

	DblVtr	m_dVtrPwrMax;
	DblVtr	m_dVtrPwrMin;

	IntVtr	m_iVtrSwiHz;
	DblVtr	m_dVtrSwiHighPcl;
	DblVtr	m_dVtrSwiLowPcl;

	IntVtr	m_iVtrModHz;
	DblVtr	m_dVtrModHighPcl;
	DblVtr	m_dVtrModLowPcl;

	CStringVtr m_strVtrTestItem;
	CStringVtr m_strVtrResultTX;
	CStringVtr m_strVtrResultRX;

	DblVtr	m_dVtrRxLevel;
	DblVtr	m_dVtrRxBer;
	
	unsigned char	m_RxQual_Full;
	unsigned char	m_RxLev_Full;
	double	m_dRxSEBR;
	int		m_iRxLevel;
	//for EDGE
	double	m_dEvmRms;
	double	m_dEvmPeak;
	DblVtr	m_dVtrEvm95P;
	DblVtr	m_dVtrORGNOFS;
	//for log 
	int m_iPhoneTestBand;

 
};


#endif