#include "StdAfx.h"
#include "IFuncDev.h"
CVisaInterface IFuncDev::m_VisaInterface;
PILogger	IFuncDev::	m_piLogger=NULL;
IFuncDev::IFuncDev(void)
{
}
IFuncDev::IFuncDev(PCTesterDevice pDevice)
{

}
IFuncDev::~IFuncDev(void)
{
}

int IFuncDev::Device_Init(const CString strDeviceAddr)
{

	m_VisaInterface.SetTesterAddr(strDeviceAddr);
	if (DEVICE_SUCCESS!=m_VisaInterface.OpenSession())
	{
		return DEVICE_FINDRES_FAIL;
	}
	return m_VisaInterface.CheckDeviceLegal();
	//return DEVICE_SUCCESS;
	
}
void IFuncDev::Deivce_Exit()
{

	return m_VisaInterface.CloseSession();

}


