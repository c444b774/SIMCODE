
#include "stdafx.h"
#include "IPhone.h"


PILogger IPhone::m_piLogger = NULL;
CSerComInterface IPhone::m_SerialInterface;

void IPhone::TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg)
{
	if (m_piLogger)
		m_piLogger->TraceLog(lpszModule, emLevel,lpszFileName, uiLine, lpszMsg);
}


void IPhone::FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg)
{
	if (m_piLogger)
		m_piLogger->FactoryLog(iProcesCode, strBand, strChannel, iErrorCode, strUL, strDL, strMeasured, strUnit, bPass, strMsg);
}

void IPhone::CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage)
{
	if (m_piLogger)
	{
		m_piLogger->CommandLog(lpszType, lpszMessage);
	}

}
