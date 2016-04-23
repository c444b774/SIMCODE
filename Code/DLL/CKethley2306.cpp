
#include "StdAfx.h"
#include "CKethley2306.h"
 

RF_IMPLEMENT_DYNCREATE(CKethley2306)
 
CKethley2306::CKethley2306()
{
}
CKethley2306::~CKethley2306()
{
   	
}

int CKethley2306::InitDevice(const CString & strAddr, int iPort)
{   
	int	 iStatus=DEVICE_SUCCESS;
    int iDeviceErr;
	CString strCmd;
	iStatus = CPowerSupply::InitDevice(strAddr, iPort);
	if(iStatus!=DEVICE_SUCCESS)
	{return iStatus;}

  

	if (iPort == POWER_SUPPLY_OUTPUT1 || iPort ==POWER_SUPPLY_OUTPUT2)
	{
		strCmd.Format("DISPlay:CHAN %d",iPort);

		DEVICE_WRITE(strCmd)
	}else
	{
		iStatus = ERR_POWER_SUPPLY_WRONG_OUTPUT;
		return iStatus;
	}


    
	return DEVICE_SUCCESS;
	
}

int CKethley2306::SetCurrRangeMax_Min(bool bIsMax)
{
	int iDeviceErr;
	CString strCmd;
    int	 iStatus=DEVICE_SUCCESS;
	if(POWER_SUPPLY_OUTPUT1 == m_iPort)

	{
		 if(bIsMax)
	     strCmd.Format("SENSe:CURRent:RANGe MAX");
		 else
		 strCmd.Format("SENSe:CURRent:RANGe MIN");
	} 

	else if(POWER_SUPPLY_OUTPUT2== m_iPort)
	{
		if(bIsMax)
		strCmd.Format("SENSe2:CURRent:RANGe MAX");
		else
		strCmd.Format("SENSe2:CURRent:RANGe MIN");
	}
	else{
		iStatus = ERR_POWER_SUPPLY_WRONG_OUTPUT;
		return iStatus;
	}
   
	DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;
}

int CKethley2306::PS_SetVoltage(float fVoltage)
{
		int iDeviceErr;
	CString strCmd;
    int	 iStatus=DEVICE_SUCCESS;
	if(POWER_SUPPLY_OUTPUT1 == m_iPort)
	     strCmd.Format("VOLT %f",fVoltage);

	else if(POWER_SUPPLY_OUTPUT2== m_iPort)
		strCmd.Format("SOUR2:VOLT %f",fVoltage);
	else{
		iStatus = ERR_POWER_SUPPLY_WRONG_OUTPUT;
		return iStatus;
	}
   
	DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;
}
 
int	CKethley2306::PS_SetCurrentLimit(float fCurrent)
{
	int iDeviceErr;
	CString strCmd;
    int	 iStatus=DEVICE_SUCCESS;
	if(POWER_SUPPLY_OUTPUT1 == m_iPort)
	     strCmd.Format("CURR %f",fCurrent);

	else if(POWER_SUPPLY_OUTPUT2== m_iPort)
		strCmd.Format("SOUR2:CURR %f",fCurrent);
	else{
		iStatus = ERR_POWER_SUPPLY_WRONG_OUTPUT;
		return iStatus;
	}
   
	DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;
} 
 
int CKethley2306::PS_GetCurrent(float*fCurrent)
{

    int iDeviceErr;
	CString strCmd;
	CString strRes;
    int	 iStatus=DEVICE_SUCCESS;
	if(POWER_SUPPLY_OUTPUT1 == m_iPort)
	{
	     strCmd.Format("SENSe:FUNC \"CURR\"");
		 DEVICE_WRITE(strCmd)

		 strCmd.Format("READ?");
		 DEVICE_QUERY(strCmd)
		 strRes=Device_GetReadBuf();
		 *fCurrent=CStr::StrToFloat(strRes);
	}

	else if(POWER_SUPPLY_OUTPUT2== m_iPort)
	{
		strCmd.Format("SENSe2:FUNC \"CURR\"");
		DEVICE_WRITE(strCmd)

		strCmd.Format("READ2?");
		DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
		*fCurrent=CStr::StrToFloat(strRes);

	}
	else{
		iStatus = ERR_POWER_SUPPLY_WRONG_OUTPUT;
		return iStatus;
	}
   
	DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;

	return DEVICE_SUCCESS;
} 
 

 
int CKethley2306::PSSetOuptON(bool bIsOn)
{
    int iDeviceErr;
	CString strCmd;
    int	 iStatus=DEVICE_SUCCESS;
	if(POWER_SUPPLY_OUTPUT1 == m_iPort)

	{
		 if(bIsOn)
	     strCmd.Format("OUTPut ON");
		 else
		 strCmd.Format("OUTPut OFF");
	} 

	else if(POWER_SUPPLY_OUTPUT2== m_iPort)
	{
		if(bIsOn)
		strCmd.Format("OUTPut2 ON");
		else
		strCmd.Format("OUTPut2 OFF");
	}
	else{
		iStatus = ERR_POWER_SUPPLY_WRONG_OUTPUT;
		return iStatus;
	}
   
	DEVICE_WRITE(strCmd)
   return DEVICE_SUCCESS;
}
 