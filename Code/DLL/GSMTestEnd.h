#ifndef _GSM_TESTEND_H_
#define _GSM_TESTEND_H_
#include "IFHandler.h"

class CGSMTestEnd:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CGSMTestEnd)
public: 

		CGSMTestEnd();
		~CGSMTestEnd();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    //PIFuncGSMTest_Dev m_pFunGSMTestDev;



private: 
	bool CGSMTestEndMainFunc();;
	bool CGSMTestEndFunc();


private:
   

 
};
#endif