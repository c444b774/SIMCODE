#ifndef _WCDMA_TESTCALL_H_
#define _WCDMA_TESTCALL_H_
#include "IFHandler.h"

class CWCDMATestStartCall:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CWCDMATestStartCall)
public: 

		CWCDMATestStartCall();
		~CWCDMATestStartCall();
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
	bool CWCDMATestStartCallMainFunc();
	bool CWCDMATestStartCallFunc();
	bool CWCDMATest_NS_StartCallFunc();


private:
   int m_iCallBand;
   CString m_strCallBand;
   int m_iCallULChannel;
   double m_dCallCellPower;
   double m_dCallTargetPower;
   double m_dBERSessionTimeOut;
   double m_dRegistTimeOut;

 
};
#endif