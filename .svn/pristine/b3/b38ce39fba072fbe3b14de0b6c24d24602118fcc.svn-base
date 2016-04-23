#pragma once
 

#include "inc\RFObject.h"
 
 
class ILogger : public CRFObject
{
	RF_DECLARE_DYNAMIC(ILogger);
 
public:
	ILogger(){
 
	}
	virtual ~ILogger(){
 
	}
 
	virtual void TraceLog(LPCTSTR strModule, EMsgLevel msgLevel, LPCSTR strFile, UINT iLine, LPCTSTR strMsg) = 0;
 
	virtual void FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg) = 0;
	virtual void FactoryLogEx(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg,LPCTSTR strItemName) = 0;
 
	virtual void CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage) = 0;
 
	inline void SetFactoryLogger(FPFactoryLog fpFactoryLog){m_fpFactoryLog = fpFactoryLog;}
	inline void SetFactoryLoggerEx(FPFactoryLogEx fpFactoryLog){m_fpFactoryLogEx = fpFactoryLog;}
	inline void SetTraceLogger(FPTraceLog fpTraceLog){m_fpTraceLog = fpTraceLog;}
	inline void SetCommandLogger(FPCommandLog fpCommandLog){m_fpCommandLog = fpCommandLog;}
 
protected:
	FPFactoryLog			m_fpFactoryLog;
	FPTraceLog				m_fpTraceLog;
	FPCommandLog		m_fpCommandLog;
	FPFactoryLogEx          m_fpFactoryLogEx;
 
};
typedef ILogger* PILogger;
 

