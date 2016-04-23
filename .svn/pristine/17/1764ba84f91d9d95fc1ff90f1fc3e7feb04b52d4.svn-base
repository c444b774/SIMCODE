#ifndef _CDMA_MEASLOOP_H_
#define _CDMA_MEASLOOP_H_
#include "IFHandler.h"

class CCDMATestMeasureLoop:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CCDMATestMeasureLoop)
public: 

		CCDMATestMeasureLoop();
		~CCDMATestMeasureLoop();
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
	bool CCDMATestMeasureLoopMainFunc();	
	bool CDMATestHandOver();
	bool CDMATestMaxPower();
	bool CDMATestMinPower();
	bool CDMATestWFQ();
	bool CDMATestACPR();
	bool CDMATestTROLPC();
	bool CDMATestRx();

	void EndCall();

private:
	bool	m_bIsStopWhileFail;
	int		m_iFailFlag;

	int		m_iCurrBand;
    CString m_strCurBand;
	IntVtr m_ivTestChannelList;
	int m_iCurrentCH;
   	DblVtr  m_vCableLoss;

	bool	m_bUseCfgPara;

	IntVtr	m_iTestChan;

	int		m_iBurstQty;	
	DblVtr	m_dVtrRxLevPwrLev;
	int		m_iDelayForRxlev;
	//Test limit
	double m_dRxSenLim;
	DblVtr	m_dVtrRHOLim;
	DblVtr	m_dVtrFERLim;
	DblVtr	m_dVtrTimeLim;
	DblVtr	m_dVtrFeedLim;
	DblVtr	m_dVtrPhaseLim;
	DblVtr	m_dVtrMagLim;
	DblVtr	m_dVtrEVMLim;
	DblVtr	m_dVtrMaxPwrLim;
	DblVtr	m_dVtrMinPwrLim;
	DblVtr	m_dVtrADJLim;
	DblVtr	m_dVtrALTLim;
	DblVtr	m_dVtrBerLim;
	DblVtr	m_dVtrSerLim;
	DblVtr	m_dVtrRxLevLimMax;
	DblVtr	m_dVtrRxLevLimMin;

	

private:
	bool SetCDMATestLOSS();
	int	 GetItemCode(int nMode,int Band,int Channel);
};
#endif