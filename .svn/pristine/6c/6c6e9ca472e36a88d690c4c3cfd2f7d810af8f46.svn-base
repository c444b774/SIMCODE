#ifndef _6285THERM_H_
#define _6285THERM_H_
#include "IFHandler.h"
class CRTR6285TThermCal:public IRFCalProcess

{
	RF_DECLARE_DYNCREATE(CRTR6285TThermCal)
public: 

		CRTR6285TThermCal();
		~CRTR6285TThermCal();
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

	 int	m_iIsUseTwoSlope;
     double m_dColdSLope;  
	 double m_dHotSLope;
	 int    m_iCalTemp;
	 int    m_iMaxTemp;
	 int    m_iMinTemp;
	 int    m_iIsUseOffsetThermBin;
	 int    m_iIsFillThermBins;
	 double m_dSlope;

private: 
	bool CRTR6285TThermCalMainFunc();
	bool CRTR6285TThermCalFunc();





 
};
#endif