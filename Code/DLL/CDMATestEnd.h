#ifndef _CDMA_TESTEND_H_
#define _CDMA_TESTEND_H_
#include "IFHandler.h"

class CCDMATestEnd:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CCDMATestEnd)
public: 

		CCDMATestEnd();
		~CCDMATestEnd();
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
	bool CCDMATestEndMainFunc();
	bool CCDMATestEndFunc();
	bool CCDMATestEndFuncWithOutEFS();
	void EndCall();

private:
   bool m_bEnterOnline;
   int  m_nEndDelay;
 
};
#endif