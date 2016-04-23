#ifndef _GSM_EDGE_NSFT_ENDCALL_H_
#define _GSM_EDGE_NSFT_ENDCALL_H_
#include "ifhandler.h"

class CGSM_EDGE_NSFT_EndCall :public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CGSM_EDGE_NSFT_EndCall)
public:
	CGSM_EDGE_NSFT_EndCall(void);
	~CGSM_EDGE_NSFT_EndCall(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool GNSFTestEndCallMainFunc();
	bool GNSFTestFunc();

 	int EndCall();
private:
	 int	 m_IsEdge;
	 bool    m_bEnterOnline;
	 int     m_nEndDelay;
	 

private:


protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	PIFuncGSMTest_Dev m_pFunGSMTestDev;
};
#endif