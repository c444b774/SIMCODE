#pragma once
#include "IFHandler.h"

class CGPSTestProc:public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CGPSTestProc)
public:
	CGPSTestProc(void);
	~CGPSTestProc(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool GPSTestMainFunc();
	bool GPSCalLossMailFunc();
	bool GPSTestRXFunc();
	bool GPSTestGen8();
	bool GPSTestRX_AT();
	bool GPSCalLossFunc();

     
	bool GPSDIAG_Exit();



private:

	 CString m_strWaveFileRootPath;
	 CString m_strWaveFileName;
	 CRangePair<double> m_RXCNOSpec;
	 CRangePair<double> m_FreqOffsetSpec;
	
	 int m_iOutPort;
	 double m_dGPSLoss;
	 bool m_bUseTestSet;
	 double m_dCellPower;
	 double m_dFreqOffset;
	 double m_dGoldenCellPower;
	 double m_dCaLoss;
     double m_dLossStep;
	 double m_dLossInitValue;
	 double m_dMaxLossValue;
	 int    m_iSVID;
	 int    m_iRetryTimes;
	 

private:


protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    PIFuncGPSTest_Dev m_pFunGPSTestDev;
	PIWCDMACal_Dev m_pFuncGPSDev;
    

};
