#include "StdAfx.h"
#include "FuncDev_CMU.h"

  
CFuncDev_CMU::CFuncDev_CMU(void)
{
}

CFuncDev_CMU::CFuncDev_CMU(PCTesterDevice pDev):IFuncDev(pDev)
{
 m_pTesterDevice=pDev;
}
CFuncDev_CMU::~CFuncDev_CMU(void)
{
}

int  CFuncDev_CMU::OpenSecAddr(const CString & strPriAddr,int iSecAddr)
{

    CString strSecAddr;
	int iDeviceErr;
	strSecAddr.Format(_T("%s::%d"),strPriAddr,iSecAddr);
	 if((iDeviceErr=Device_Init(strSecAddr))!=DEVICE_SUCCESS)
		return iDeviceErr;
	 return DEVICE_SUCCESS;
}
int CFuncDev_CMU::SetInput(int iInput)

{
   CString strCmd;
   int iDeviceErr;
   

    strCmd.Format("1;INP RF%d",iInput);
	DEVICE_WRITE(strCmd)

   
 return DEVICE_SUCCESS;
}
int CFuncDev_CMU::SetOutput(int iOutput)
{
	CString strCmd;
	int iDeviceErr;
    strCmd.Format("1;OUTP RF%d",iOutput);
	DEVICE_WRITE(strCmd)
    return  DEVICE_SUCCESS;
}
int CFuncDev_CMU::SetCableLoss(double dInLoss,double dOutLoss)
{
	CString strCmd;
	int iDeviceErr;
	
    strCmd.Format(_T("%d;SOUR:CORR:LOSS:OUTPUT%d %8.3f"),m_iCMUMode,m_pTesterDevice->m_iOutputPort,dOutLoss);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
	 strCmd.Format(_T("%d;SOUR:CORR:LOSS:INPUT%d %8.3f"),m_iCMUMode,m_pTesterDevice->m_iInputPort,dInLoss);
     if((iDeviceErr=Device_Write(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;

    return  DEVICE_SUCCESS;
}
