#ifndef _RX_DC_AUTO_CAL_H_
#define _RX_DC_AUTO_CAL_H_
#include "IFHandler.h"
class CRxDCAutoCal:public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CRxDCAutoCal)
public: 

		CRxDCAutoCal();
		~CRxDCAutoCal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
//    IWCDMACal_Dev* m_pFunWCDMACalDev;

private:

	int  m_iBand;
	int  m_iDCBandMode; 
	int  m_iDCModeId; //0,	CDMA 1X mode ; 1, WCDMA mode
    int  m_iCHannel;


private: 
	bool CRxDCAutoCalMainFunc();
	bool CRxDCAutoCalFunc();
 
};
#endif