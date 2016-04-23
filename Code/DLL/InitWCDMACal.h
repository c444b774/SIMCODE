#ifndef _INITWCDMACALL_H_
#define _INITWCDMACALL_H_
#include "IFHandler.h"
class CInitWCDMACal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CInitWCDMACal)
public: 

		CInitWCDMACal();
		~CInitWCDMACal();
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
	int m_iInPortOutPort;



private: 
	bool CInitWCDMACalMainFunc();
	bool CInitWCDMACalFunc();




 
};
#endif
