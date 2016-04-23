#pragma once
#include "PowerSupply.h"
class CKethley2306 : public CPowerSupply
{
	RF_DECLARE_DYNCREATE(CKethley2306)
public:
	CKethley2306(void);
	virtual ~CKethley2306(void);
	 int	InitDevice(const CString & strAddr, int iPort);
     int	PS_SetVoltage(float fVoltage);
     int	PS_SetCurrentLimit(float fCurrent1);
	 int	PS_GetCurrent(float *fCurrent);
     int	PSSetOuptON(bool bIsOn=true);
	 int    SetCurrRangeMax_Min(bool bIsMax);
};