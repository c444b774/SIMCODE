

#pragma once
 
#include "IFuncDev.h"
#include "CTesterDevice.h"


#define POWER_SUPPLY_OUTPUT1	1
#define POWER_SUPPLY_OUTPUT2	2
 
 
class CPowerSupply: public IFuncDev,public CTesterDevice
{
RF_DECLARE_DYNCREATE(CPowerSupply)
 
public:
	CPowerSupply();
	~CPowerSupply();
	virtual int	InitDevice(const CString & strAddr, int iPort = 0);
	virtual int	PS_SetVoltage(float fVoltage);
	virtual int	PS_SetCurrentLimit(float fCurrent1);
	virtual int	PS_GetCurrent(float *fCurrent);
	virtual int	PSSetOuptON(bool bIsOn=true);
	virtual int SetCurrRangeMax_Min(bool bIsMax=true);
    virtual int PS_Release();
 
	virtual bool InitData(PCStringStrMap pcSettingMap,CRFObjectMap&   cObjectMap) { return true; }
 
	virtual bool InitData() { return true;}
    

protected:
	int m_iPort;

 
};
typedef CPowerSupply* PCPowerSupply;
