#pragma once
#include "stdafx.h"
#include "inc\commoninclude.h"
#include   "inc\ILogger.h"
class CSerComInterface
{
public:
	CSerComInterface(void);
	~CSerComInterface(void);

    BOOL AT_SendCmd(char *strSend, char *strRecv,int iDelayMs=200);
	BOOL AT_Init();
	BOOL SendFrame (unsigned char *pData, int nLength);
	BOOL ReceiveFrame(unsigned char *pData);
	BOOL ADB_SendCmd(CString stringSend,CString& strReceived,bool bIsReturn=true,int iTimeWaitms=200);
	BOOL ADB_SendCmdEx(CString stringSend,CString& strReceived,bool bIsReturn=true,int iTimeWaitms=200);
	BOOL AT_SendCmdService(char *strSend, char *strSearch, char *strRecv);
	BOOL CmdPipeInit();
	BOOL CmdPipeRelease();
	BOOL PipeWriteAndWait(char * inputStr,char* waitStr,int recurvetime);
	BOOL GetCmdPipeStatus();
	BOOL FlushPipe();
	BOOL CmdPipeReadLine(char* readbuff,int recurvTime);
	BOOL CmdPipeWrite(char* writebuff);
	BOOL CmdPipeRead(char* readbuff);
	 static PILogger		m_piLogger ;

    inline static void SetLogger(PILogger piLogger){m_piLogger = piLogger;}

	virtual void TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg);
	virtual void FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg);
	virtual void CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage);
private:
	HANDLE hCom;
    BOOL ReadCom(LPVOID pBuff,DWORD* len);
	BOOL WriteCom(LPCVOID pBuff,DWORD len);
	
	BOOL IsCmdPipeOpen;
	HANDLE hSaveStdout;
	HANDLE hChildStdoutRd;
	HANDLE hChildStdoutWr;
	HANDLE hChildStdinRd;
	HANDLE hChildStdinWr; 
	OVERLAPPED osReader;
public:
	void CloseCom();
	bool OpenComport(int port);
	


	
};
