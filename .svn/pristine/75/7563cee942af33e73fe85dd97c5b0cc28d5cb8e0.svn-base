#ifndef _GSM_EDGE_CABLELOSSCAL_H_
#define _GSM_EDGE_CABLELOSSCAL_H_
#include "IFHandler.h"
class CGSMCableLossCal:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CGSMCableLossCal)
public: 

		CGSMCableLossCal();
		~CGSMCableLossCal();
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
	bool CGSMCableLossCalMainFunc();
	bool CGSMCableLossCalFunc();

	bool SetGSMTestLOSS();
	bool StartLossMeas(CString strTestItem);
	bool CheckTXResult(int nIndex,CString strBand,CString strChan,CString strTestItem);
	bool ReadGoldenPower();
	bool WriteGoldenPower();
	bool GsmMakeGoldenSemple();
	bool GsmSetCableLoss();
	bool GsmMeasPower();


	int	 GetItemCode(int nMode,int Band,int Channel,int PowerLevel);

private:

	//for test use
	int		m_IsEdge;
	int     m_iChainId;
	int		m_IsSaveToIni;
	int		m_IsToMakeSample;
	bool	m_bIsStopWhileFail;
	int		m_iFailFlag;
	CString m_strType;

	int		m_iCurrBand;
	int m_iFTMBand;
	CString m_strCurrBand;

	bool	m_bUseCfgPara;
	DblVtr  m_vCableLoss;
	CStringVtr	m_strVtrLossRes;

	CStringVtr m_strVtrChan;
	IntVtr	m_iTestChan;
	int m_iPCL;
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
	DblVtr	m_dVtrGoldenPwr;
	DblVtr	m_dVtrMeasPwr;

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