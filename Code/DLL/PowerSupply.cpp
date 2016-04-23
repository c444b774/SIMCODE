
#include "StdAfx.h"
#include "PowerSupply.h"
 

RF_IMPLEMENT_DYNCREATE(CPowerSupply)
 
CPowerSupply::CPowerSupply()
{
}
CPowerSupply::~CPowerSupply()
{
   	 PS_Release();
}

int CPowerSupply::InitDevice(const CString & strAddr, int iPort)
{   

	int iDeviceErr;
	CString strCmd;
    strCmd.Format(_T("%s::%s"),strAddr,"INSTR");
	if((iDeviceErr=Device_Init(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
  
    m_iPort = iPort;
	return DEVICE_SUCCESS;
	
}

int CPowerSupply::SetCurrRangeMax_Min(bool bIsMax)
{
	int iDeviceErr;
	CString strCmd;
     if(bIsMax)
	   strCmd.Format("SENSe:CURRent:RANGe MAX");
	 else
	   strCmd.Format("SENSe:CURRent:RANGe MIN");

	DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;
}

int CPowerSupply::PS_SetVoltage(float fVoltage)
{
	int iDeviceErr;
	CString strCmd;
    strCmd.Format("VOLT %f",fVoltage);
	DEVICE_WRITE(strCmd)
    return DEVICE_SUCCESS;	
}
 
int	CPowerSupply::PS_SetCurrentLimit(float fCurrent)
{
	int iDeviceErr;
	CString strCmd;
    strCmd.Format("CURR  %f",fCurrent);
	DEVICE_WRITE(strCmd)
	 return DEVICE_SUCCESS;
} 
 
int CPowerSupply::PS_GetCurrent(float* fCurrent)
{

    int iDeviceErr;
	CString strCmd;
	CString strRes;
    strCmd.Format("MEAS:CURR?");
	DEVICE_QUERY(strCmd)
    strRes=Device_GetReadBuf();
	*fCurrent=CStr::StrToFloat(strRes);

	return DEVICE_SUCCESS;
} 
 
int	CPowerSupply::PS_Release()
{
    Device_Clear(); 
	Deivce_Exit();

	return DEVICE_SUCCESS;
}
 
int CPowerSupply::PSSetOuptON(bool bIsOn)
{
    int iDeviceErr;
    CString strCmd;
    if(bIsOn)
    strCmd.Format("OUTP ON");
	else
    strCmd.Format("OUTP OFF");
	DEVICE_WRITE(strCmd)
	return DEVICE_SUCCESS;
}
 

