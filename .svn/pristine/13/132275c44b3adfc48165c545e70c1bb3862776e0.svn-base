#ifndef _CDMA_CABLELOSSCAL_H_
#define _CDMA_CABLELOSSCAL_H_
#include "IFHandler.h"

class CCDMACableLossCal:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CCDMACableLossCal)
public: 

		CCDMACableLossCal();
		~CCDMACableLossCal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    PIFuncCDMATest_Dev m_pFunCDMATestDev;



private: 
	bool CCDMACableLossCalMainFunc();
	bool CCDMACableLossCalFunc();
	bool StartLossMeas(int iTestChan,CString strTestItem);
	bool CheckTXResult(int nIndex,int iChan,CString strTestItem);
	bool CDMAMakeGoldenSemple();
	bool CDMASetCableLoss();
	bool CDMAMeasPower();
	bool ReadGoldenPower();
	bool WriteGoldenPower();

	void EndCall();

private:
	bool	m_bIsStopWhileFail;
	int		m_iFailFlag;
	int		m_IsToMakeSample;
	int		m_IsSaveToIni;
	CString m_strType;

	CStringVtr	m_strVtrLossRes;
	CStringVtr m_strVtrChan;
	DblVtr	m_dVtrGoldenPwr;
	DblVtr	m_dVtrMeasPwr;

	int		m_iCurrBand;
    CString m_strCurBand;
   	DblVtr  m_vCableLoss;
	int		m_CableLossMeasureCount;
	bool	m_bUseCfgPara;

	IntVtr	m_iTestChan;

	int		m_iBurstQty;
	//Test limit
	DblVtr	m_dVtrMaxPwrLim;
	DblVtr	m_dVtrMinPwrLim;
	DblVtr	m_dVtrPwrLevel;


    CStringVtr m_strVtrTestItem;
    CStringVtr m_strVtrTXResult;
	int		m_nEndDelay;

private:
	bool SetCDMATestLOSS();
	int	 GetItemCode(int nMode,int Band,int Channel,int PowerLevel);
};
#endif