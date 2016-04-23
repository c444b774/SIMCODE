#ifndef _GSM_TESTCALL_H_
#define _GSML_TESTCALL_H_
#include "IFHandler.h"

class CGSM_TestCall:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CGSM_TestCall)
public: 

		CGSM_TestCall();
		~CGSM_TestCall();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    PIFuncGSMTest_Dev m_pFunGSMTestDev;



private: 
	bool CGSM_TestCallMainFunc();
	bool CGSM_TestCallFunc();
	bool CGSM_NS_TestCallFunc();


private:
	int m_iCallBand;
	int m_iCallTCH;
	int m_iCallBCH;
	int m_iCallPCL;


	//for log 
	CString m_strCurrentBand;
	int m_iPhoneTestBand;

 
};
#endif