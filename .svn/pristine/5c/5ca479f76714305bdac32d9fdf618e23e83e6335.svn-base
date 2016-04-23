#pragma once
#include "stdafx.h"
#include "inc\visa.h"
#include "inc\commoninclude.h"
#include   "inc\ILogger.h"

#define MAX_READLEN  200000


class CVisaInterface
{
public:
	CVisaInterface(void);
	~CVisaInterface(void);
    

public:

	void SetTesterAddr(const CString& strAddr){m_strTesterAddr=strAddr;}
	CString GetTesterAddr(){return m_strTesterAddr;}

	int OpenSession();
	int CheckDeviceLegal();
	void CloseSession();
	int VisaWrite(const CString& strWrite);
	int VisaRead(CString & strRead);
	int VisaQuery(const CString& strQuery,int iDelayMs);
	int VisaQuery_Char(const CString& strQuery,unsigned char* szCharRead,int iDelayMs);
	int VisaClear();
	CString  VisaGetReadBuf();
    
    static PILogger		m_piLogger ;

	inline static void SetLogger(PILogger piLogger){m_piLogger = piLogger;}
	virtual void TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg);
	virtual void FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg);
	virtual void CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage);
private:
	CString m_strTesterAddr;
	 ViSession m_VXIHandle;
	 ViSession m_DefaultHandle;
	 CString m_strReadBuffer;
};
