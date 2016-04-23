#ifndef _8615THERM_H_
#define _8615THERM_H_
#include "IFHandler.h"
class CQTR8615TThermCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CQTR8615TThermCal)
public: 

		CQTR8615TThermCal();
		~CQTR8615TThermCal();
		virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	   virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;

private:

     double m_dColdSLope;  
	 double m_dHotSLope;
	 int    m_iCalTemp;
	 int    m_iMaxTemp;
	 int    m_iMinTemp;
	 int    m_iIsUseOffsetThermBin;
	 int    m_iIsFillThermBins;

private: 
	bool CQTR8615TThermCalMainFunc();
	bool CQTR8615TThermCalFunc();





 
};
#endif