#ifndef _GSM_EDGE_NSFT_CALL_H_
#define _GSM_EDGE_NSFT_CALL_H_
#include "IFHandler.h"

class CGSM_EDGE_NSFT_Call:public IRFTestProcess

{
	RF_DECLARE_DYNCREATE(CGSM_EDGE_NSFT_Call)
public: 

		CGSM_EDGE_NSFT_Call();
		~CGSM_EDGE_NSFT_Call();
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
	bool CGSM_EDGE_NSFT_CallMainFunc();
	bool CGSM_EDGE_NSFT_CallStartcallFunc();


private:
	int m_IsEdge;
	int m_IsScreenOff;
	int m_iChainId;
	int m_iCallBand;
	int m_iCallCH;
	int m_iCallPcl;
	bool bIsCheckBTflag;
	int m_isPreOnlineToFTM;
	//for log 
	CString m_strCurrBand;
	

private:
	bool CheckBTflag();
 	int EndCall(int iMode);
};
#endif