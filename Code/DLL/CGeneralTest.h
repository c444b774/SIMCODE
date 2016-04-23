#pragma once
#include "IFHandler.h"

class CGeneralTest:public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CGeneralTest)
public:
	CGeneralTest(void);
	~CGeneralTest(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool CGeneralTestlMainFunc();
	bool C32KRTCTestFunc();
	bool CBackBattFunc();
	bool COffCurrFunc();
	bool CCharCurrFunc();

private:

    int m_i32KAvgCount;
	int m_iBackAvgCount;
	int m_i32KRetryTimes;
	int m_iBackRetryTimes;
	int m_iCurrRetryTimes;
	CRangePair<float> m_r32KFreqLimit;
    CRangePair<float> m_rBackCharLimit;
	CRangePair<float> m_rBackDisCharLimit;
	CRangePair<float> m_rOffCurrentLimit;
	int m_iOffCurrentAvgCount;
    int m_iCharAvgCount;
	float m_fTargetVol;
	int m_iBackupWaitTime;
	CRangePair<float> m_rCharCurrentLimit;
	float m_fPSOffset;
	float m_fBattVol;

protected:
	vector<FPClassFunc> m_vFPTestFunc;
	virtual bool DoProcess();
    

};