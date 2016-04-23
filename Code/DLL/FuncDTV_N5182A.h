#pragma once
#include "FuncDev_N5182A.h"
#include "IFuncDTVTest_Dev.h"


class CFuncDTV_N5182A:public IFuncDTVTest_Dev,public CFuncDev_N5182A
{
public:
	CFuncDTV_N5182A(void);
	virtual ~CFuncDTV_N5182A(void);
	CFuncDTV_N5182A(PCTesterDevice pDev);

     int IDTVTestInit(const CString& strAddr);
	 int IDTVTestSetDLType(const CString& strWavePath);
	 int IDTVTestSetDLFreqPower(double DLFreq,double DlPower,double dCableloss);
	 int IDTVTestSetDLSigOn(bool bIsOn);
	 int IDTVTestSetInOutPort(int iInport,int iOutPort);
};
