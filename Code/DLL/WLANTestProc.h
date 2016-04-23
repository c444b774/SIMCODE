#pragma once
#include "IFHandler.h"
enum WLANSigType
{
	W802a=1,
	W802b,
	W802g_DSSS,
	W802g_OFDM,
	W802n
};

class CWLANTestProc:public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CWLANTestProc)
public:
	CWLANTestProc(void);
	~CWLANTestProc(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool WLANCallossMainFunc();
	bool WLANTestMainFunc();
	bool WLANTestTXFunc();
	bool WLANTestRXFunc();
	bool WLANTestTXCalLossFunc();



private:
	 CString strCurrCH;
	 CString strCurrType;
     CStringStringMap m_str2strTestMap;
	 CStringStringMap m_str2strWaveFilenameMap;

     int m_iIsUseAT;
	 int m_iAdbType;

	 int m_iDelayWlanRXcommandAT ;
	 int m_iDelayWlanRXcommandADB;
	 int m_iDelayDeviceOnAT;
	  int m_iDelayDeviceOnADB;
	 CString strWLANADDR;
	 CString strFilePath;
	 CString strTargetPath;
	 IntVtr m_striTypeVtr; //0: 80211a 1: 80211b 2:80211g (DSSS) 3: 80211g (OFDM) 4 :80211n 
	 IntVtr     m_iChannelVtr;
     CStringVtr m_strChannelVtr;
      CStringVtr m_strBTChannelVtr;
	 DblVtr  m_dCalpower;
	 DblVtr  m_dGoldenpower;
	 double m_dCellPower;
	 double m_dLossPreset;
	 CString m_strWavefilePath;
	 int needSelfinit;
	 CString m_strWaveFileRootPath;

     int m_iInOutPort;
	 double m_dMaxLev;
	 int m_iTargetPower;
	 bool m_bWLANRXTestFirst;
     CRangePair<double> m_PowerSpec;
	 CRangePair<double> m_LossSpec;
     CRangePair<int>  m_EVMAllCarrSpec;
	 CRangePair<double> m_RXFerSpec;

	 
private:
	bool WLANHandover(int eSigType,int iChannel,int iTargetPower=16,double dlPower=0,bool bIsTx=true,bool bIsCalloss=false);
    
	bool WLANTestTxSpec(int eSigType,bool bIsCalLoss=false);
	bool WLANTestRxSpec();
	bool WLANEndTest(bool bIsTx=true);
	bool WLANTestRmmod();
	bool ADB_Push();
	bool WLANTestDoSelfInit();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    PIFuncWLANTest_Dev m_pFunWLANTestDev;
    

};
