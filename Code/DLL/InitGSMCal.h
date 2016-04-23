#ifndef _INITGSMCAL_H_
#define _INITGSMCAL_H_
#include "IFHandler.h"
class CInitCGSMCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CInitCGSMCal)
public: 

		CInitCGSMCal();
		~CInitCGSMCal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    IFuncGSMCal_Dev* m_pFunGSMCalDev;

private:
	int m_iInPortOutPort;
	int m_isPreOnlineToFTM;



private: 
	bool CInitCGSMCalMainFunc();
	bool CInitCGSMCalCalFunc();
	bool CInitCGSMCalCalFunc6285();

 
};
#endif
