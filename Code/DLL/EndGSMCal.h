#ifndef _ENDGSMCAL_H_
#define _ENDGSMCAL_H_
#include "IFHandler.h"
class CEndGSMCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CEndGSMCal)
public: 

		CEndGSMCal();
		~CEndGSMCal();
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
	bool m_bEnterOnline;



private: 
	bool CEndGSMCalMainFunc();
	bool CEndGSMCalFunc();
	bool CEndGSMCalFunc6285();



 
};
#endif
