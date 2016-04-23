#pragma once
#include "IFHandler.h"

class CDTVTestProc:public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CDTVTestProc)
public:
	CDTVTestProc(void);
	~CDTVTestProc(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool DTVTestMainFunc();
	bool DTVTestRXFunc();
	bool DTVTCalLossFunc();
    bool DTVHandover(const CString& strType,int iCHannel,double dlCellPower);
    bool DTVTestRXSpec(int iChannel);


private:

	 CString m_strWaveFileRootPath;
	 CString m_strWaveFileName;
	 CRangePair<double> m_RXBERSpec;
	 CRangePair<double>  m_RXCNSpec;
	 int m_iOutPort;
	 double m_dCellPower;
	 bool m_bIsUseDevice;
	 CString strCurrCH;
	 CString strCurrType;
	 CStringStringMap m_str2strTestMap;

	 double m_dCalLoss;
	 double m_dGoldenCellPower;
	 double m_dInitLoss;
	 double m_dStepSizedB;
	 double m_dMaxLoss;
	 bool m_bIsCalLoss;
private:      
      CStringVtr m_strWaveFileVtr; 
	  IntVtr     m_iChannelVtr;
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    PIFuncDTVTest_Dev m_pFunDTVTestDev;
    

};
