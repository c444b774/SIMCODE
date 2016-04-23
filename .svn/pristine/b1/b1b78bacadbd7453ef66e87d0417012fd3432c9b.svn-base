#ifndef _ENDWCDMACALL_H_
#define _ENDWCDMACALL_H_
#include "IFHandler.h"
class CEndWCDMACal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CEndWCDMACal)
public: 

		CEndWCDMACal();
		~CEndWCDMACal();
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
	



private: 
	bool CEndWCDMACalMainFunc();
	bool CEndWCDMACalFunc();




 
};
#endif
