#pragma once
#include "IFHandler.h"
enum BTSigType
{
	DH1=1,
	DH3,
	DH5,
	DH2_1,
	DH2_3,
	DH3_1,	
	DH3_3,
    DH3_5
};

class CBTTestProc:public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CBTTestProc)
public:
	CBTTestProc(void);
	~CBTTestProc(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool BTTestMainFunc();
	bool BTTestTXFunc();



private:
	 CString strCurrCH;
	 CString strCurrType;
     CStringStringMap m_str2strTestMap;

	 CString strBTADDR;
	 IntVtr m_striTypeVtr;//1: DH1 2: DH3 3: DH5 4: 2-DH1 5: 2-DH3 6: 2-DH5 7: 3-DH1 8: 3-DH3 9: 3-DH5
	 IntVtr m_iChannelVtr;

	 int m_iInOutPort;
	 bool m_bFirst;
	 double m_bMaxLev;
	 int m_iIsUseAT;
     CRangePair<double> m_PowerSpec;
     CRangePair<double>  m_RMSDEVMSpec;
private:
	bool BTHandover(int eSigType,int iChannel);
	bool BTTestTxSpec(int eSigType);
	bool BTEndTest();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    PIFuncBTTest_Dev m_pFunBTTestDev;
    

};
