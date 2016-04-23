#ifndef _WCDMA_MEASLOOP_H_
#define _WCDMA_MEASLOOP_H_
#include "IFHandler.h"
#include "WCDMATestCall.h"
class CWCDMATestMeasureLoop:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CWCDMATestMeasureLoop)
public: 

		CWCDMATestMeasureLoop();
		~CWCDMATestMeasureLoop();
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
	bool CWCDMATestMeasureLoopMainFunc();
	bool WcdmaReCall();
	bool SetWCDMATestLOSS();
	bool CWCDMATestHandOver();
	bool CWCDMATestMinPower();
	bool CWCDMATestModAnalysis();
	bool CWCDMATestMeasureALL(int iBand,int iULChannel,CString strTestItem);
	bool CWCDMATestILPC();
	bool CWCDMATestRSCP();
	bool CWCDMANSTestRX();
	bool CWCDMATestMaxPower();
    bool CWCDMATestACLR();
    bool CWCDMATestOBW();
    bool CWCDMATestBER();
    bool CWCDMATestSEMask();

	bool CWCDMATestReTestILPC(int iResult_E,int iResult_F,double * dFailSLots_E,double * dFailSlots_F,int iFailSlotNum_E,int iFailSlotNum_F);

	bool CWCDMATestReCALL();
private:
   int m_iTestBand;
   int  m_iIsReFineILPC;
   
   int  m_iCurrentCH;
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
  // double m_dACLRLimit[4];
   DblVtr m_dvACLRLimit;
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
   
   int m_iRXScaleFactor;
   double m_dMinRXPower;
   IntVtr  m_vFALLRISE_NVID;
   IntVtr  m_vCompenNV_ID;
   int m_iIs6285Plat;

   CWCDMATestStartCall * m_pReStartCall;
   




   //Error Vector Magnitude  Unit=%
   //Peak Vector Error Unit=%
   //Phase Error Unit=deg
   //Magnitude Error Unit=%
   //Origin Offset Unit=dB
   //IQ Imbalance Unit=%
   //Timing Error Unit=chip
   //DPCCH/DPDCH Power Ratio Unit=dB

   DblVtr  m_vCableLoss;
	int	 GetItemCode(int nMode,int Band,int Channel);
 
};
#endif