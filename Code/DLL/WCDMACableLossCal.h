#ifndef _WCDMA_CABLELOSSCAL_H_
#define _WCDMA_CABLELOSSCAL_H_
#include "IFHandler.h"

class CWCDMACableLossCal:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CWCDMACableLossCal)
public: 

		CWCDMACableLossCal();
		~CWCDMACableLossCal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    PIFuncWCDMATest_Dev m_pFuncWCDMATestDev;



private: 
	bool CWCDMACableLossCalMainFunc();;
	bool CWCDMACableLossCalFunc();
	bool SetWCDMATestLOSS();
	bool CWCDMATestHandOver(int iBand,int iULChannel);
	bool CWCDMATestMeasureALL(int iBand,int iULChannel);

	bool WMakeGoldenSemple();
	bool WSetCableLoss();
	bool WMeasPower();
	bool ReadGoldenPower();
	bool WriteGoldenPower();

private:
   int m_iTestBand;
   int m_IsToMakeSample;
   int m_IsSaveToIni;
   DblVtr	m_dVtrGoldenPwr;
   DblVtr	m_dVtrMeasPwr;
   DblVtr   m_vCableLoss;
   CStringVtr m_strVtrLossRes;
   CStringVtr m_strVtrChan;
   CString  m_strType;

   CString m_strTestBand;
   IntVtr m_iTestChannelList;
   CStringVtr m_strVtrTestItem;
   int m_iMeasureCount;
   int m_iBERSamples;
   CRangePair<double> m_dMaxPowerLimit;
   CRangePair<double> m_dMinPowerLimit;
   CRangePair<double> m_dMidPowerLimit;
   double m_dMidPowerTarget;
   CRangePair<double> m_dFERLimit;
   CRangePair<double> m_dOBWLimit;
   CRangePair<double> m_dBERLimit;
   double m_dRxCellPower;
   int m_iILPCList[8];
   double m_dACLRLimit[4];
   CRangePair<double> m_dEVMLimit;
   CRangePair<double> m_dTERLimit;
   CRangePair<double> m_dPCDERRLimit;
   CRangePair<double> m_dPVELimit;
   CRangePair<double> m_dPERLimit;
   CRangePair<double> m_dMagERRLimit;
   CRangePair<double> m_dOOLimit;
   CRangePair<double> m_dIQILimit;
   CRangePair<double> m_dDDPRlimit;
   DblVtr m_dRSCP_CellPower;
   DblVtr m_dRSCP_HLimit;
   DblVtr m_dRSCP_LLimit;
};
#endif