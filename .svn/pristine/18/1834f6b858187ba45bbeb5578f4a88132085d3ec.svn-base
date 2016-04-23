
#ifndef _IFHANDLER_
#define  _IFHANDLER_
 

#include   "inc\RFObject.h"
#include   "CTesterDevice.h"
#include   "PowerSupply.h"
#include   "GeneralMulMeter.h"
#include   "GeneralFreMeas.h"
#include   "IPhone.h"
#include   "IFuncGSMTest_Dev.h"
#include   "IFuncBTTest_Dev.h"
#include   "IFuncWLANTest_Dev.h"
#include   "IFuncGPSTest_Dev.h"
#include   "IFuncDTVTest_Dev.h"
#include   "IWCDMACal_Dev.h"
#include   "IFuncWCDMATest_Dev.h"
#include   "IFuncCDMATest_Dev.h"
#include   "IFuncGSMCal_Dev.h"

#include   "inc\CCableLossFinder.h"
#include   "..\SimRFCaltestUI\toolmsgdef.h"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
 
class IRFHandler : public CRFObject
{
RF_DECLARE_DYNAMIC(IRFHandler)
 
public:
 
	IRFHandler(){
	m_strFailRunList="";	
   
	}
	virtual ~IRFHandler(){
 
	}
	virtual bool Handle() = 0;
    
	CString m_strFailRunList;
	
 
protected:
	virtual bool DoProcess() = 0;
 
	virtual void TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg);
 
	virtual void FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg);
 
	virtual void FactoryLogEx(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg,LPCTSTR strItemName);
	virtual void CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage);
 
  
 

protected:
	static PCTesterDevice m_piTesterDevice;
	static PCTesterDevice m_piTesterDevice1;
	static PCTesterDevice m_piTesterDevice2;

	static PCGenFreqMeas  m_piFreqMeasDevice;
	static PCGenMulMeter  m_piMultiMeasDevice;

	 static PCPowerSupply  m_piPowerSly;
     static PCPowerSupply  m_piPowerSly1;

     PCTesterDevice m_piTesterDeviceCurr;
     PCPowerSupply  m_piPowerSlyCurr;

	static CString m_strTesterDevice;
	static CString m_strTesterDevice1;
	static CString m_strTesterDevice2;

	static CString m_strFreqMeasDevice;
	static CString m_strMultiMeasDevice;

	static CString m_strPlyName;
    static CString m_strPlyName1;

	CString m_strTesterDeviceCurr;
    CString m_strPlyNameCurr;


	static PIPhone m_pPhone;
    static PILogger m_piLogger; 
    static HWND m_hMsgHandlingWnd;
	static CString m_strDeviceAddr;
	static CString m_strDeviceAddr1;
	static CString m_strDeviceAddr2;

	static CString m_strFreqMeasAddr;
    static CString m_strMultiMeasAddr;

	static CString m_strPlyAddr;
	static CString m_strPlyAddr1;
	static int m_iPlyPort;
    static int m_iPly1Port;

	CString m_strDeviceAddrCurr;
	CString m_strPlyAddrCurr;

    int m_iPlyPortCurr;

	static CCableLossFinder m_LossFinder;
	static int  m_iComport;
	static int  m_iATComport;
	static int  m_iComportRetryTimes;
    
	int m_iItemCode;
    static bool m_bIsStopWhenFail;
	static CString m_strSN;
    static CString m_strSNHeader;
	static int m_iSNLength;

    
	
	bool m_bIsRandomCH;

protected:
	int m_iErrorcode;
	
};
typedef IRFHandler* PIRFHandler;
typedef vector<PIRFHandler> RFHandlerVtr;
typedef RFHandlerVtr::iterator	RFHandlerVtrItr;
typedef pair<CString,PIRFHandler> PairStringHandler;
typedef vector<PairStringHandler> VtrPairStringHandler;
typedef vector<PairStringHandler>::iterator VtrPairStringHandlerItr;
class IRFCalProcess : public IRFHandler
{

 RF_DECLARE_DYNAMIC(IRFCalProcess)
public:
	IRFCalProcess(){
 
	}
	virtual ~IRFCalProcess(){
 
	}
	virtual bool Handle() = 0;
 
	virtual bool InitData() = 0;
 
protected:
	virtual bool DoProcess() = 0;
 
 
};
typedef IRFCalProcess* PIRFCal;
 

 
class IRFTestProcess : public IRFHandler
{

  RF_DECLARE_DYNAMIC(IRFTestProcess)
public:
	IRFTestProcess(){
 
	}
	virtual ~IRFTestProcess(){
 
	}
	virtual bool InitData() =0;
	virtual bool Handle() =0;
 
protected:
	virtual bool DoProcess() =0;
	

};
typedef IRFTestProcess* PIRFTest;
 

#endif 