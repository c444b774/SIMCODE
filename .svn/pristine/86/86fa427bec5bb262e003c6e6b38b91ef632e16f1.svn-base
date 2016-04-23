#ifndef _GSMTXCAL_H_
#define _GSMTXCAL_H_
#include "IFHandler.h"
class CGSMTXCal6285:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CGSMTXCal6285)
public: 

		CGSMTXCal6285();
		~CGSMTXCal6285();
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

		int startDac;
		int stopDac;
	   int m_pathDelayStart;
	   int m_iRGIForDist;
       int m_iListSize;
	   int m_iRangeNum;
	   int m_iSegmentTime;
       int m_iMeasLength;
	   int m_iGainParamNVID;
		double dNVMaxPower;// this should from xml
		double dNVMinPower;// this should from xml
		double dSmoothingWindowSize;// this should from xml
		
		int iFreqnecyLocation;// 
	   double m_dDATrigPower;
	   double m_dPredisRGIPower;
		typedef	struct _timeDelay
		{
			short piDelay;
			double modP400;
			double modN400;
		}timeDelay;



private: 
	bool CGSMTXCalMainFunc6285();
	bool CGSMTXCSCalFunc6285();
	bool CGSMTXPolarCalFunc6285();
	bool CGSMTXDelayCalFunc6285();
	bool SetGSMCableLoss();

 
};
#endif
