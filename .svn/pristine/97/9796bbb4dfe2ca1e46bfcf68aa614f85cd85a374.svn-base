#ifndef _CDMAXOCAL_H_
#define _CDMAXOCAL_H_
#include "IFHandler.h"
class CCDMAXOCalibration:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CCDMAXOCalibration)
public: 

		CCDMAXOCalibration();
		~CCDMAXOCalibration();
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


    int  m_iFreqOffset;
	int  m_iBand;
	int  m_iXOMode; // 0:cdma  1 wcdma
    int  m_iCHannel;
	int  m_iPaRange;
	int  m_iPDM;

private: 
	bool CCDMAXOCalibrationMainFunc();
	bool CCDMAXOCalibrationDC_CF();
	bool CCDMAXOCalibrationFT();




 
};
#endif