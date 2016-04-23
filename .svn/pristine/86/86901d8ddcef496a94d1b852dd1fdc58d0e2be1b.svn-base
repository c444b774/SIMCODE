#pragma once
#include "VisaInterface.h"
#include "CTesterDevice.h"
#include   "inc\ILogger.h"
#pragma warning(disable : 4250)
class IFuncDev
{
public:
	IFuncDev(void);
	IFuncDev(PCTesterDevice pDevice);
	virtual ~IFuncDev(void);

   
public:
	inline int Device_Write(const CString & strWriteCmd)
	{
		
		return m_VisaInterface.VisaWrite(strWriteCmd);
	}

	inline int Device_Read(CString & strRead)
	{
		
		return m_VisaInterface.VisaRead(strRead);
	}


	inline int Device_Query(const CString & strReadCmd,int iDelayMs=0)
	{
	  
		return m_VisaInterface.VisaQuery(strReadCmd,iDelayMs);
	}
	inline int CheckDeviceLegal()
	{
		return m_VisaInterface.CheckDeviceLegal();
	}
    
	

	inline int Device_Query_Char(const CString & strReadCmd,unsigned char* szCharRet,int iDelayMs=0)
	{
		
		return m_VisaInterface.VisaQuery_Char(strReadCmd,szCharRet,iDelayMs);
	}


    

	inline CString Device_GetReadBuf()
	{
	
		return m_VisaInterface.VisaGetReadBuf();
	}
	inline int Device_Clear()
	{
		
		return m_VisaInterface.VisaClear();
	}


public :
	int Device_Init(const CString strDeviceAddr);
	void Deivce_Exit();

	virtual int SetInput(int iInput){return DEVICE_SUCCESS;}
	virtual int SetOutput(int iOutput){return DEVICE_SUCCESS;}
	virtual int SetCableLoss(double dInLoss,double dOutLoss){return DEVICE_SUCCESS;}
	
	 CTesterDevice* m_pTesterDevice;
	static PILogger		m_piLogger ;

	inline static void SetLogger(PILogger piLogger){m_piLogger = piLogger;}
	protected:
	static CVisaInterface m_VisaInterface;

};
