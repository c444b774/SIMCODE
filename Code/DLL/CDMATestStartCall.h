#ifndef _CDMA_TESTCALL_H_
#define _CDMA_TESTCALL_H_
#include "IFHandler.h"

class CCDMATestStartCall:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CCDMATestStartCall)
public: 

		CCDMATestStartCall();
		~CCDMATestStartCall();
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
	bool CCDMATestStartCallMainFunc();
	bool CCDMATest_NS_StartCallFunc();


private:
   int m_iCallBand;
   int m_isPreOnlineToFTM;
   CString m_strCallBand;
   int m_iCallULChannel;
   int m_iRadioConfig;
   double m_dCallCellPower;
   double m_dCallTargetPower;
   double m_dBERSessionTimeOut;
   double m_dRegistTimeOut;
   CString m_strWavefile;//strWavefile for CMW USE
   int m_iFailFlag;
};
#endif