#ifndef _GSMTXCAL_H_
#define _GSMTXCAL_H_
#include "IFHandler.h"
typedef struct
{
	UINT16 gsm_linear_tx_gain_val;
	UINT16 edge_linear_tx_gain_val; 
	UINT8 charpredist_env_gain[16];
}ftm_gsm_env_gain_nv_data_type;

class CGSMTXCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CGSMTXCal)
public: 

		CGSMTXCal();
		~CGSMTXCal();
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
       int m_iBand;
	   CString m_strBand;
	   IntVtr m_vChannelList;
	   DblVtr  m_vCableLoss;
	   int m_iPhoneMode;
       int m_iChainId;
	   IntVtr m_ivNVMap;
	   IntVtr m_ivPARange;
	   int m_idDAStepDuration;
	   double m_dDATrigPower;
	   int m_iDATrigRGI;
	   int m_iDATrigPA;
	   int m_iDAStartRGI;
	   int m_iDAStopRGI;
	   int m_iDAStepRGI;	 
	   int m_iDAMeasOffset;
	   int m_iDAMeasLength;
	   DblVtr m_dvDATrigeLimit;

		unsigned long m_iDcDuration;
		unsigned long m_iEdgeDuration;
		unsigned char m_iOverRideModemConstants;
		float m_dDigGainUnity;
		float m_dRampUnity;
		float m_dExtensionFloor;
		float m_dDacScale;

		//! Debug Smooothing
		unsigned char m_iOverrideSmooothingDefaults;
		unsigned char m_iEnableAmAmSmoothing;
		float m_dAmAmKnot;
		float m_dAmPmKnot;
		
		int m_iRGIForDist;
		int m_iGainParamNVID;	   
		double m_dPredisRGIPower;




private: 
	bool CGSMTXCalMainFunc();
	bool CGSMTXDACalFunc();
	bool CGSMTXDACalV2Func();
	bool CGSMTXPredistCalV2Func();
	bool CGSMTXPredistCalFunc();
	bool CGSMTXDAAndPredistCalFunc_MDM9x25();

	bool SetGSMCableLoss();

 
};
#endif
