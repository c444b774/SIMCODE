

#ifndef __UI_LOG_H__
#define __UI_LOG_H__
#include "ILogger.h"
 
 
 
class CUILogger : public ILogger
{
RF_DECLARE_DYNCREATE(CUILogger)
 
public:
 
 
bool InitData(
		PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
		);
 
	bool InitData();
 
	virtual void TraceLog(LPCTSTR strModule, EMsgLevel msgLevel, LPCSTR strFile, UINT iLine, LPCTSTR strMsg);
 
	virtual void FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg);
	virtual void FactoryLogEx(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg,LPCTSTR strItemName);
 
	virtual void CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage);
 
};
 
typedef CUILogger* PCUILogger;
 
 
 
 
 
 
#endif//__UI_LOG_H__
