#pragma once
#include "IFHandler.h"

class CPowerSlyControl:public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CPowerSlyControl)
public:
	CPowerSlyControl(void);
	~CPowerSlyControl(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool CPowerSlyControlMainFunc();

	bool StartPly();
	bool StopPly();
	bool GetCurrent();
     

private:
    double m_dVoltage;
	double m_dCurrentLimit;
	int    m_iCurrentMode;  //1 -> A  0 ->MA

	int m_iSmplInter_ms;
	int m_iMeasCount;
	float m_fCurrentLowLimit;
	float m_fCurrentHiLimit;

    
protected:
	vector<FPClassFunc> m_vFPTestFunc;
	virtual bool DoProcess();
    

};
