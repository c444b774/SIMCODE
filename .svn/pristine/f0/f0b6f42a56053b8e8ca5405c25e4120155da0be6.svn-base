#pragma once
#include "FuncDev_CMW.h"
#include "IFuncGPSTest_Dev.h"


class CFuncGPS_CMW:public IFuncGPSTest_Dev,public CFuncDev_CMW
{
public:
	CFuncGPS_CMW(void);
	virtual ~CFuncGPS_CMW(void);
	CFuncGPS_CMW(PCTesterDevice pDev);

     int IGPSTestInit(const CString& strAddr,const CString& strDlSignal);
	int IGPSTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss);
     int IGPSTestSetOn(bool bIsOn);
	 int IGPSTestSetInOutPort(int iOutPort);
};
