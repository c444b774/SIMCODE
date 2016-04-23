#ifndef _INITCDMACALL_H_
#define _INITCDMACALL_H_
#include "IFHandler.h"
class CInitCDMACal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CInitCDMACal)
public: 

		CInitCDMACal();
		~CInitCDMACal();
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
	bool CInitCDMACalMainFunc();
	bool CInitCDMACalFunc();

 
};
#endif
