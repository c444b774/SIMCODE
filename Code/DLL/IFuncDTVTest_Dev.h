#pragma once
#include  "IFuncDev.h"

class IFuncDTVTest_Dev :public virtual IFuncDev
{
public:
	IFuncDTVTest_Dev(void);
	virtual ~IFuncDTVTest_Dev(void);
	IFuncDTVTest_Dev(PCTesterDevice pDev);

	virtual int IDTVTestInit(const CString& strAddr){return DEVICE_SUCCESS;}
	 virtual int IDTVTestSetDLType(const CString& strWavePath){return DEVICE_SUCCESS;}
	virtual int IDTVTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss){return DEVICE_SUCCESS;}
	virtual int IDTVTestSetInOutPort(int iOutPort){return DEVICE_SUCCESS;}
	virtual int IDTVTestSetDLSigOn(bool bIsOn){return DEVICE_SUCCESS;}
};
typedef IFuncDTVTest_Dev* PIFuncDTVTest_Dev;
