#ifndef _GSM_MEASLOOP_H_
#define _GSM_MEASLOOP_H_
#include "IFHandler.h"

class CGSMTestMeasureLoop:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CGSMTestMeasureLoop)
public: 

		CGSMTestMeasureLoop();
		~CGSMTestMeasureLoop();
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
	bool CGSMTestMeasureLoopMainFunc();;
	bool CGSMTestMaxPowerFunc();

private:
   CString m_strtestBand;

 
};
#endif