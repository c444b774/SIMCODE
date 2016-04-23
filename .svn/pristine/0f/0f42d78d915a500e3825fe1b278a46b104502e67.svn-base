#ifndef _WCDMA_TESTEND_H_
#define _WCDMA_TESTEND_H_
#include "IFHandler.h"

class CWCDMATestEnd:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CWCDMATestEnd)
public: 

		CWCDMATestEnd();
		~CWCDMATestEnd();
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
	bool CWCDMATestEndMainFunc();;
	bool CWCDMATestEndFunc();

    int EndCall();
private:
   
	bool    m_bEnterOnline;
	
 
};
#endif