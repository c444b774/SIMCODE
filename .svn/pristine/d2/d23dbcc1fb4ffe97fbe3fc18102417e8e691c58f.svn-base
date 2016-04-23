#ifndef _ENDCDMACALL_H_
#define _ENDCDMACALL_H_
#include "IFHandler.h"
class CEndCDMACal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CEndCDMACal)
public: 

		CEndCDMACal();
		~CEndCDMACal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
    IWCDMACal_Dev* m_pFunWCDMACalDev;

private:
	bool m_bEnterOnline;
	bool m_bIsEFS;



private: 
	bool CEndCDMACalMainFunc();
	bool CEndCDMACalFunc();




 
};
#endif
