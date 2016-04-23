#pragma once
#include  "IFuncDev.h"

class IFuncGPSTest_Dev :public virtual IFuncDev
{
public:
	IFuncGPSTest_Dev(void);
	virtual ~IFuncGPSTest_Dev(void);
	IFuncGPSTest_Dev(PCTesterDevice pDev);

	virtual int IGPSTestInit(const CString& strAddr,const CString& strDlSignal){return DEVICE_SUCCESS;}
	virtual int IGPSTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss){return DEVICE_SUCCESS;}
	virtual int IGPSTestSetInOutPort(int iOutPort){return DEVICE_SUCCESS;}
	virtual int IGPSTestSetOn(bool bIsOn){return DEVICE_SUCCESS;}
};
typedef IFuncGPSTest_Dev* PIFuncGPSTest_Dev;
