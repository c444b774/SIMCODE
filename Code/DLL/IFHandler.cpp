
#include "stdafx.h"
#include "IFHandler.h"

RF_IMPLEMENT_DYNAMIC(IRFHandler)
 
RF_IMPLEMENT_DYNAMIC(IRFCalProcess)
 
RF_IMPLEMENT_DYNAMIC(IRFTestProcess)


PCTesterDevice IRFHandler::m_piTesterDevice=NULL;
PCTesterDevice IRFHandler::m_piTesterDevice1=NULL;
PCTesterDevice IRFHandler::m_piTesterDevice2=NULL;

PCPowerSupply IRFHandler::m_piPowerSly=NULL;
PCPowerSupply IRFHandler::m_piPowerSly1=NULL;
PCGenFreqMeas  IRFHandler::m_piFreqMeasDevice=NULL;
PCGenMulMeter  IRFHandler::m_piMultiMeasDevice=NULL;

CString IRFHandler::m_strSN;
CString IRFHandler::m_strSNHeader;
int IRFHandler::m_iSNLength;


//PCTesterDevice IRFHandler::m_piTesterDeviceCurr=NULL;
PIPhone IRFHandler::m_pPhone=NULL;
CString IRFHandler::m_strTesterDevice=_T("");
CString IRFHandler::m_strTesterDevice1=_T("");
CString IRFHandler::m_strTesterDevice2=_T("");
CString IRFHandler::m_strPlyName=_T("");
CString IRFHandler::m_strPlyName1=_T("");

CString  IRFHandler::m_strFreqMeasDevice=_T("");
CString  IRFHandler::m_strMultiMeasDevice=_T("");
//CString IRFHandler::m_strTesterDeviceCurr=_T("");
CString IRFHandler:: m_strDeviceAddr;
CString IRFHandler:: m_strDeviceAddr1;
CString IRFHandler:: m_strDeviceAddr2;
CString IRFHandler:: m_strPlyAddr;
CString IRFHandler:: m_strPlyAddr1;

CString IRFHandler::m_strFreqMeasAddr;
CString IRFHandler::m_strMultiMeasAddr;
int IRFHandler::m_iPlyPort;
int IRFHandler::m_iPly1Port;
int IRFHandler::  m_iComport;
int IRFHandler::  m_iATComport;
int IRFHandler:: m_iComportRetryTimes;
PILogger IRFHandler::m_piLogger=NULL;
HWND IRFHandler::m_hMsgHandlingWnd = NULL;
CCableLossFinder IRFHandler::m_LossFinder;
bool IRFHandler::m_bIsStopWhenFail=true;
void IRFHandler::TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg)
{
  if (m_piLogger)
		m_piLogger->TraceLog(lpszModule, emLevel,lpszFileName, uiLine, lpszMsg);
}
 
void IRFHandler::FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg)
{
 if (m_piLogger)
		m_piLogger->FactoryLog(iProcesCode, strBand, strChannel, iErrorCode, strUL, strDL, strMeasured, strUnit, bPass, strMsg);
}

void IRFHandler::FactoryLogEx(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg,LPCTSTR strItemName)
{
 if (m_piLogger)
		m_piLogger->FactoryLogEx(iProcesCode, strBand, strChannel, iErrorCode, strUL, strDL, strMeasured, strUnit, bPass, strMsg,strItemName);
}
 
void IRFHandler::CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage)
{
  if (m_piLogger)
	{
		m_piLogger->CommandLog(lpszType, lpszMessage);
	}
}
