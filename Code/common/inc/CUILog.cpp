

#include "stdafx.h"
#include "CUILog.h"
 
 
RF_IMPLEMENT_DYNCREATE(CUILogger)
 
 
bool CUILogger::InitData(
					PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
					  )
{
	return true;
}
 
bool CUILogger::InitData()
{
 
	return true;
}
 
void CUILogger::TraceLog(LPCTSTR strModule, EMsgLevel msgLevel, LPCSTR strFile, UINT iLine, LPCTSTR strMsg)
{
	if (m_fpTraceLog)
		m_fpTraceLog(strModule, strFile, iLine, msgLevel, strMsg);
}
 
void CUILogger::FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg)
{
	if (m_fpFactoryLog)
		m_fpFactoryLog(iProcesCode, strBand, strChannel, iErrorCode, strUL, strDL, strMeasured, strUnit, bPass, strMsg);
}

void CUILogger::FactoryLogEx(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg,LPCTSTR strItemName)
{
	if (m_fpFactoryLogEx)
		m_fpFactoryLogEx(iProcesCode, strBand, strChannel, iErrorCode, strUL, strDL, strMeasured, strUnit, bPass, strItemName,strMsg);
}
 
void CUILogger::CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage)
{
	if (m_fpCommandLog)
		m_fpCommandLog(lpszType, lpszMessage);
}
