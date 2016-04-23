#include "StdAfx.h"
#include "GeneralFreMeas.h"
 

RF_IMPLEMENT_DYNCREATE(CGenFreqMeas)
 
CGenFreqMeas::CGenFreqMeas()
{
}
CGenFreqMeas::~CGenFreqMeas()
{
   	 GenFreqMeas_Release();
}

int CGenFreqMeas::InitDevice(const CString & strAddr, int iPort)
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

int CGenFreqMeas::MeasureFreq(double & dFreq,int iAvgCount)
{

  int iDeviceErr;
	CString strCmd;
	CString strRes;
    double dSumFreq=0;
	double dAvgFreq=0;
	double dMeasValue;
	

	for(int i=0;i<iAvgCount;++i)
	{
		strCmd.Format("INIT");
		DEVICE_WRITE(strCmd)
        strCmd.Format("FETCH:FREQUENCY?");
	    DEVICE_QUERY(strCmd)
		strRes=Device_GetReadBuf();
		dMeasValue=CStr::StrToFloat(strRes);
		
		dSumFreq+=dMeasValue;
	}
    dAvgFreq=(double)dSumFreq/(double)iAvgCount;
    dFreq=dAvgFreq;
return DEVICE_SUCCESS;
}
int	CGenFreqMeas::GenFreqMeas_Release()
{
    Device_Clear(); 
	Deivce_Exit();

	return DEVICE_SUCCESS;
}