#ifndef _TESTER_DEVICE_H
#define _TESTER_DEVICE_H

#include "inc\RFObject.h"
#include "inc\CBandInfo.h"
#include   "inc\ILogger.h"
class IFunc_Dev;
class IFuncGSMTest_Dev;
class IFuncBTTest_Dev;
class IFuncWLANTest_Dev;
class IFuncGPSTest_Dev;
class IFuncDTVTest_Dev;
class IWCDMACal_Dev;
class IFuncWCDMATest_Dev;
class IFuncCDMATest_Dev;
class IFuncGSMCal_Dev;


class CTesterDevice : public CRFObject
{
 
 RF_DECLARE_DYNCREATE(CTesterDevice)
public:
	CTesterDevice():m_bInternalReference(true){}
	virtual ~CTesterDevice(){}
 
	virtual bool InitData(
		PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
		){return true;};
 
	virtual bool InitData(){return true;}
 
	inline static void SetLogger(PILogger piLogger){m_piLogger = piLogger;}
 
public:
	IFunc_Dev*				m_piFunc_Dev;
	IFuncGSMTest_Dev*		m_piFuncGSMTest;
    IFuncBTTest_Dev*        m_piFuncBTTest;
	IFuncWLANTest_Dev*      m_piFuncWLANTest;
    IFuncGPSTest_Dev*       m_piFuncGPSTest;
	IFuncDTVTest_Dev*       m_piFuncDTVTest;
	IWCDMACal_Dev*          m_piFuncWCDMACal;
    IFuncWCDMATest_Dev*     m_piFuncWCDMATest; 
	IFuncCDMATest_Dev*      m_piFuncCDMATest;
    IFuncGSMCal_Dev*        m_piFuncGSMCal;

    static PILogger			m_piLogger;
	int m_iInputPort;
	int m_iOutputPort;

	int m_iChannelPort;
	bool m_bIsCommandRX1CMW;
	bool m_bUseFastSwitchApp;
	bool m_bIsScreenOff;
    
 
	bool m_bInternalReference;

 
};
typedef CTesterDevice* PCTesterDevice;



#endif