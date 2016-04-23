#include "StdAfx.h"
#include "FuncDev_8820.h"

CFuncDev_8820::CFuncDev_8820(void)
{
}

CFuncDev_8820::~CFuncDev_8820(void)
{
}
CFuncDev_8820::CFuncDev_8820(PCTesterDevice pDev)
{
  m_pTesterDevice=pDev;
}
int  CFuncDev_8820::OpenSecAddr(const CString & strPriAddr,int iSecAddr)
{
	CString strSecAddr;
	int iDeviceErr;
	//	strSecAddr.Format(_T("%s::%d"),strPriAddr,iSecAddr);
	strSecAddr.Format(_T("%s::%s"),strPriAddr,"INSTR");
	if((iDeviceErr=Device_Init(strSecAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;
 
   
	 return DEVICE_SUCCESS;
}
int CFuncDev_8820::SetInput(int iInput)

{
 
 return DEVICE_SUCCESS;
}
int CFuncDev_8820::SetOutput(int iOutput)
{

    return  DEVICE_SUCCESS;
}
int CFuncDev_8820::SetCableLoss(double dInLoss,double dOutLoss)
{
	CString strCmd;
	int iDeviceErr;

	CString strBuf;
	strCmd.Format("*IDN?");
	DEVICE_QUERY(strCmd);
	strBuf=Device_GetReadBuf();

		strCmd.Format(_T("DLEXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
		strCmd.Format(_T("ULEXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;

		strCmd.Format(_T("EXTLOSSW COMMON"));
		if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
			return iDeviceErr;
	

	strCmd.Format(_T("LOSSTBLVAL %.2fMHz,%.2f,%.2f,0.0"),m_dFerMHz,dInLoss,dOutLoss);
	if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

	return  DEVICE_SUCCESS;
}



