#include "StdAfx.h"
#include "GeneralMulMeter.h"
 

RF_IMPLEMENT_DYNCREATE(CGenMulMeter)
 
CGenMulMeter::CGenMulMeter()
{
}
CGenMulMeter::~CGenMulMeter()
{
   	 MulMeter_Release();
}

int CGenMulMeter::InitDevice(const CString & strAddr, int iPort)
{   

	int iDeviceErr;
	CString strCmd;
    strCmd.Format(_T("%s::%s"),strAddr,"INSTR");
	if((iDeviceErr=Device_Init(strCmd))!=DEVICE_SUCCESS)
		return iDeviceErr;
  
    m_iPort = iPort;

    strCmd.Format("*RST;*OPC?");
	DEVICE_QUERY(strCmd)

	strCmd.Format("*CLS");
	DEVICE_WRITE(strCmd)
	return DEVICE_SUCCESS;
	
}

int CGenMulMeter::MeasureVoltage(double & dVoltage,int iAvgCount)
{
    int iDeviceErr;
	CString strCmd;
	CString strRes;
    double dSumVol=0;
	double dAvgVol=0;
	double dMeasValue;
	strCmd.Format("MEAS:VOLT:DC?");

	for(int i=0;i<iAvgCount;++i)
	{
		DEVICE_QUERY(strCmd)
			Sleep(20);
		strRes=Device_GetReadBuf();
		dMeasValue=CStr::StrToFloat(strRes);
		dSumVol+=dMeasValue;
	}
   dAvgVol=(double)dSumVol/(double)iAvgCount;
    dVoltage=dAvgVol;
return DEVICE_SUCCESS;
}
int	CGenMulMeter::MulMeter_Release()
{
    Device_Clear(); 
	Deivce_Exit();

	return DEVICE_SUCCESS;
}
 

 