#ifndef _XOCAL_H_
#define _XOCAL_H_
#include "IFHandler.h"
class CXOCalibration:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CXOCalibration)
public: 

		CXOCalibration();
		~CXOCalibration();
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


    double  m_iFreqOffset;
	int  m_iBand;
	int  m_iXOMode; // FTM_Mode_Id_Enum:0:cdma  1 wcdma ,42: tdscdma
    int  m_iCHannel;
	int  m_iPaRange;
	int  m_iPDM;
	double m_dPowerLevel;
	int m_iLNAState;
	double m_dTempSpan;
	int m_iMinFTSample;
	int m_iMaxFTSample;
	int m_iTxOnTimeMs;
	int m_iSubstageTime;
	int  m_iIsResetFail;
	int m_iTxChanBW;
	int m_iRxChanBW;
	int m_iXTALType;
	bool m_bXO_DC_Coarse;
	bool m_bXO_Collect_Sample;
	bool m_bXO_FT_Curve;

private: 
	bool CXOCalibrationMainFunc();
	bool CXOCalDC_CF();
	bool CXOCalFT();
	bool CXOCal_V3(); 
};
#endif