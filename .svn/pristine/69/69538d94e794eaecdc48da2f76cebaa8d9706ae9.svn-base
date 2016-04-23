

#pragma once
 
#include "IFuncDev.h"
#include "CTesterDevice.h"


 
 
class CGenMulMeter: public IFuncDev,public CTesterDevice
{
RF_DECLARE_DYNCREATE(CGenMulMeter)
 
public:
	CGenMulMeter();
	~CGenMulMeter();
	virtual int	InitDevice(const CString & strAddr, int iPort = 0);
    virtual int MulMeter_Release();
    virtual int MeasureVoltage(double & dVoltage,int iAvgCount=5);
	virtual bool InitData(PCStringStrMap pcSettingMap,CRFObjectMap&   cObjectMap) { return true; }
 
	virtual bool InitData() { return true;}
    

protected:
	int m_iPort;

 
};
typedef CGenMulMeter* PCGenMulMeter;
