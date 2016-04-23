

#pragma once
 
#include "IFuncDev.h"
#include "CTesterDevice.h"


 
 
class CGenFreqMeas: public IFuncDev,public CTesterDevice
{
RF_DECLARE_DYNCREATE(CGenFreqMeas)
 
public:
	CGenFreqMeas();
	~CGenFreqMeas();
	virtual int	InitDevice(const CString & strAddr, int iPort = 0);
    virtual int GenFreqMeas_Release();
    virtual int MeasureFreq(double & dFreq,int iAvgCount=5);
	virtual bool InitData(PCStringStrMap pcSettingMap,CRFObjectMap&   cObjectMap) { return true; }
 
	virtual bool InitData() { return true;}
    

protected:
	int m_iPort;

 
};
typedef CGenFreqMeas* PCGenFreqMeas;
