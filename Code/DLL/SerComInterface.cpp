#include "StdAfx.h"
#include "SerComInterface.h"
PILogger		CSerComInterface::m_piLogger=NULL;
CSerComInterface::CSerComInterface(void)
{
}

CSerComInterface::~CSerComInterface(void)
{
}


void CSerComInterface::TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg)
{
	if (m_piLogger)
		m_piLogger->TraceLog(lpszModule, emLevel,lpszFileName, uiLine, lpszMsg);
}
 
 
void CSerComInterface::FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg)
{
	if (m_piLogger)
		m_piLogger->FactoryLog(iProcesCode, strBand, strChannel, iErrorCode, strUL, strDL, strMeasured, strUnit, bPass, strMsg);
}
 
void CSerComInterface::CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage)
{
	if (m_piLogger)
	{
		m_piLogger->CommandLog(lpszType, lpszMessage);
	}
 
}
bool CSerComInterface::OpenComport(int port)
{
	char pcComPort[10];

	sprintf(pcComPort,"\\\\.\\COM%d",port);
	if(hCom!=NULL)
	{
		CloseCom();
	}
	hCom = CreateFile(pcComPort,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if(hCom==INVALID_HANDLE_VALUE)
	{
		CString tmpstr;
		tmpstr.Format("Open Comport<%d> Fail!",port);
		//AfxMessageBox(tmpstr);

		return false;
	}

	COMMTIMEOUTS CommTimeouts;
	CommTimeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeouts.ReadTotalTimeoutConstant = 20;
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	CommTimeouts.WriteTotalTimeoutConstant = 2000;
	CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	if(!SetCommTimeouts(hCom,&CommTimeouts))
	{
		CString tmpstr;
		tmpstr.Format("Set Comport<%d> Timeout Fail!",port);
		

		return false;
	}

	DCB dcb;
	BOOL bSuccess = GetCommState(hCom,&dcb);
	if(bSuccess)
	{
		dcb.BaudRate = CBR_115200;
		dcb.ByteSize = 8;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		bSuccess = SetCommState(hCom,&dcb);
		if(!bSuccess)
		{
			CString tmpstr;
			tmpstr.Format("Set Comport<%d> State Fail!",port);
			

			return false;
		}
	}
	else
	{
		CString tmpstr;
		tmpstr.Format("Get Comport<%d> State Fail!",port);
		
		
		return false;
	}

	if(!SetupComm(hCom,8192,8192))
	{
		CString tmpstr;
		tmpstr.Format("Setup Comport<%d> Buffer fail!",port);
	

		return false;
	}

	return true;
}

BOOL CSerComInterface::AT_SendCmd(char *strSend, char *strRecv,int iDelayMs)
{
	char tmpSend[1024],tmpRecv[1024];
	DWORD len;
	CString strMsg;

	if(strSend!=NULL)
	{
		strcpy(tmpSend,strSend);
		strcat(tmpSend,"\r");
		strMsg=tmpSend;
		LogATSendCommand(tmpSend)
		if(!WriteCom(tmpSend,strlen(tmpSend)))
		{
			
			return FALSE;
		}
	}

	Sleep(iDelayMs);

	if(strRecv!=NULL)
	{

		if(!ReadCom(tmpRecv,&len))
		{
			
			return FALSE;
		}

		//strMsg=tmpRecv;
		//LogATReceiveCommand(strMsg)
		if(strstr(tmpRecv,"ERROR"))
		{
			//AfxMessageBox("AT ERROR returned!");
			return FALSE;
		}
	    

		
		CString tmpstr;
		tmpstr = _T(tmpRecv);
		tmpstr.GetBufferSetLength(len);
		tmpstr.TrimLeft(tmpSend);
		tmpstr.TrimLeft("\r\n");
		tmpstr.TrimRight("\r\n");
		tmpstr.TrimRight("OK");
		tmpstr.TrimRight("\r\n");
		strcpy(strRecv,tmpstr);
		strMsg=tmpstr;
		LogATReceiveCommand(strMsg)
	}

	return TRUE;
}


BOOL CSerComInterface::AT_Init()
{
	char tmpstr[50];
	DWORD len;

	if(!WriteCom("AT\r",strlen("AT\r")))
	{
		
		return FALSE;
	}

	Sleep(100);

	if(!ReadCom(tmpstr,&len))
	{
		
		return FALSE;
	}

	if(!strstr(tmpstr,"OK"))
	{
		//AfxMessageBox("AT Connect Fail!");
		return FALSE;
	}

	return TRUE;
}


BOOL CSerComInterface::ADB_SendCmd(CString stringSend,CString& strReceived,bool bIsReturn,int iTimeWaitms)
{
    SECURITY_ATTRIBUTES sa = {0};   
	HANDLE hRead = NULL, hWrite = NULL;   

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);   
	sa.lpSecurityDescriptor = NULL;   
	sa.bInheritHandle = TRUE;   
	if (!CreatePipe(&hRead, &hWrite, &sa,0))   
	{   
		return FALSE;   
	}   

	STARTUPINFO si = {0};   
	PROCESS_INFORMATION pi = {0};   
	si.cb = sizeof(STARTUPINFO);   
	GetStartupInfo(&si);
	si.hStdError = hWrite;   
	si.hStdOutput = hWrite;   
	si.wShowWindow = SW_HIDE;   
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;   
    CString strCmd=_T("cmd.exe /c ");
    strCmd+=stringSend;
	LogADBSendCommand(strCmd);
	if (!CreateProcess(NULL, (LPSTR)strCmd.GetBuffer() ,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))   
	{   
		return FALSE;
	}   
	CloseHandle(hWrite);
	char buffer[10000] = {0};   
	DWORD bytesRead = 0;    
	Sleep(iTimeWaitms);
	ZeroMemory(buffer, 30);
	if(bIsReturn)
	{
	if ( !ReadFile(hRead, buffer,10000, &bytesRead, NULL) )
	{
		
				CloseHandle(pi.hThread);
	           CloseHandle(pi.hProcess);
		    return FALSE;
		}
	}
	
	Sleep(200);
		 
	strReceived.Format(_T("%s"),buffer);
   LogADBReceiveCommand(strReceived)
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return TRUE;  
}
BOOL CSerComInterface::ADB_SendCmdEx(CString stringSend,CString& strReceived,bool bIsReturn,int iTimeWaitms)
{
	SECURITY_ATTRIBUTES sa = {0};   
	HANDLE hRead = NULL, hWrite = NULL;   

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);   
	sa.lpSecurityDescriptor = NULL;   
	sa.bInheritHandle = TRUE;   
	if (!CreatePipe(&hRead, &hWrite, &sa,0))   
	{   
		return FALSE;   
	}   

	STARTUPINFO si = {0};   
	PROCESS_INFORMATION pi = {0};   
	si.cb = sizeof(STARTUPINFO);   
	GetStartupInfo(&si);
	si.hStdError = hWrite;   
	si.hStdOutput = hWrite;   
	si.wShowWindow = SW_HIDE;   
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;   
	CString strCmd=_T("adb ");
	strCmd+=stringSend;
	LogADBSendCommand(strCmd);
	char cmdline[200];
	sprintf(cmdline,"%s",strCmd.GetBuffer(strCmd.GetLength()));
	strCmd.ReleaseBuffer();
	if (!CreateProcess(NULL, (LPSTR)strCmd.GetBuffer() ,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))   
	{   
		DWORD dww=GetLastError();
		return FALSE;
	}  
	CloseHandle(hWrite);
	char buffer[10000] = {0};   
	DWORD bytesRead = 0;    
	Sleep(iTimeWaitms);
	ZeroMemory(buffer, 30);
	if(bIsReturn)
	{
	if ( !ReadFile(hRead, buffer,10000, &bytesRead, NULL) )
	{
		
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			return FALSE;
		}
	}

	Sleep(200);

	strReceived.Format(_T("%s"),buffer);
	LogADBReceiveCommand(strReceived)
		CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return TRUE;  
}

BOOL CSerComInterface::WriteCom(LPCVOID pBuff, DWORD len)
{
	DWORD errorType=0;
	DWORD numBytesWritten;
	OVERLAPPED osWrite;
	osWrite.Offset = 0;
	osWrite.OffsetHigh = 0;
	osWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	DWORD       dwErrorFlags;
    COMSTAT     ComStat ;
//	char dbgMsg[100];
	BOOL retCode=TRUE;

	if( hCom == INVALID_HANDLE_VALUE)
	{
//		OutputDebugString("Write com when invalid handle\n");
		return FALSE;
	}
	if (WriteFile(hCom, pBuff,len, &numBytesWritten, &osWrite) == 0)
    {
		//some error is occured
        errorType = GetLastError();
        if (errorType == ERROR_IO_PENDING)
        {
            (void) WaitForSingleObject(osWrite.hEvent, INFINITE);
            (void) ResetEvent(osWrite.hEvent);
//			OutputDebugString("Write com succes\n");
			retCode = TRUE;
        }
        else
        {
//            sprintf(dbgMsg, "I/O error on serial port %d \n", errorType);
//            OutputDebugString(dbgMsg);
            ClearCommError( hCom, &dwErrorFlags, &ComStat ) ;
            retCode = FALSE;
        }
    }
	CloseHandle(osWrite.hEvent);

	return retCode;
}

BOOL CSerComInterface::SendFrame(unsigned char *pData, int nLength)
{
	PurgeComm(hCom,PURGE_TXCLEAR |PURGE_RXCLEAR);

	int i = 0;
	unsigned char data[200];
	while(nLength>0)
	{
		if(*pData==0x7e||*pData==0x7d)
		{
			data[i++] = 0x7d;
			data[i++] = *pData^0x20;
		}
		else 
		{
			data[i++] = *pData;
		}
		
		pData++;
		nLength--;
	}
	data[i++] = 0x7e;

	if(!WriteCom(data, i))
		return FALSE;

	return TRUE;
}

BOOL CSerComInterface::ReadCom(LPVOID pBuff,DWORD* len)
{
	DWORD nBytesRead;
	BOOL status;

	OVERLAPPED osRead;
	osRead.Offset = 0;
	osRead.OffsetHigh = 0;
	osRead.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	if( hCom == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	if(ReadFile(hCom,pBuff,200,&nBytesRead,&osRead)==0)
	{
		DWORD errorType = GetLastError();
		if (errorType == ERROR_IO_PENDING)
		{
			if( !GetOverlappedResult( hCom,&osRead, &nBytesRead, TRUE ))
			{
				errorType = GetLastError();
				status = FALSE;  
			}
			status = TRUE;
		}
		else
		{
			status = FALSE;
			nBytesRead = 0 ;
		}
	}
	else
	{
		status = TRUE;
	}
	*len = nBytesRead;

	CloseHandle(osRead.hEvent);
	return status;
}

BOOL CSerComInterface::ReceiveFrame(unsigned char *pData)
{
	int read_bytes = 0;
	int n = 0;
	unsigned char read_buf[200];
	DWORD len = 0;

	int flag = ReadCom(read_buf,&len);
	if(!flag)
	{
		return FALSE;
	}

	while((read_bytes<136) && (len>0))
	{
		if(read_buf[read_bytes]==0x7e)
		{
			pData[n++] = read_buf[read_bytes];
			//read_bytes++;
			break;
		}
		else if(read_buf[read_bytes]==0x7d)
		{
			read_bytes++;
			pData[n] = read_buf[read_bytes]^0x20;
		}
		else
		{
			pData[n] = read_buf[read_bytes];
		}
		read_bytes++;
		n++;
		len--;
	}

	return TRUE;
}
BOOL CSerComInterface::AT_SendCmdService(char *strSend, char *strSearch, char *strRecv)
{
	char tmpSend[1024]={0,},tmpRecv[1024]={0,};
	DWORD len;
	
	strcpy(tmpSend,strSend);
	strcat(tmpSend,"\r");
	

	if(!WriteCom(tmpSend,strlen(tmpSend)))
	{
		
		return FALSE;
	}
	
	Sleep(200);

	
	if(!ReadCom(tmpRecv,&len))
	{
		
		return FALSE;
	}
	
	if(strstr(tmpRecv,"ERROR"))
	{
	
		return FALSE;
	}

	int trial = 0;
	while(!strstr(tmpRecv,strSearch))
	{
		Sleep(200);
		if(!ReadCom(tmpRecv,&len))
		{
			
			return FALSE;
		}
		if(trial>20)
		{
			
			return FALSE;
		}
		trial++;
	}

	CString tmpstr;
	tmpstr = _T(tmpRecv);
	int pos = tmpstr.Find(strSearch,0);
	tmpstr.Delete(0,pos+strlen(strSearch));
	tmpstr.TrimRight(" ");
	tmpstr.TrimRight("\r\n");
	strcpy(strRecv,tmpstr);
	
	return TRUE;
}


void CSerComInterface::CloseCom()
{
	CloseHandle(hCom);
	hCom = NULL;
}
BOOL CSerComInterface::CmdPipeInit()
{	
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	int bytes_write=0;
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	if(IsCmdPipeOpen)
		return 0;

	hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	osReader.hEvent   =   CreateEvent(NULL,   TRUE,   FALSE,   NULL); 

	if(!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
	{
		return FALSE;
	}
	if(!SetHandleInformation(hChildStdoutRd, HANDLE_FLAG_INHERIT, 0))
		return FALSE;

	if(!CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0 ))
		return FALSE;
	if(!SetHandleInformation(hChildStdinWr, HANDLE_FLAG_INHERIT, 0))
		return FALSE;

	memset(&piProcInfo, 0,sizeof(PROCESS_INFORMATION));

	memset(&siStartInfo, 0,sizeof(STARTUPINFO) );

	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = hChildStdoutWr;
	siStartInfo.hStdOutput = hChildStdoutWr;
	siStartInfo.hStdInput = hChildStdinRd;
	siStartInfo.dwFlags |= STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	siStartInfo.wShowWindow = SW_HIDE;
	if(!CreateProcess(NULL,"cmd",NULL,NULL,TRUE,0,NULL,NULL,&siStartInfo,&piProcInfo))
		return FALSE;										

	//if(enterADB()==-1)return -1;

	//if(enterBT_Testmode()==-1)return;  
	IsCmdPipeOpen=TRUE;
	return TRUE;
}
BOOL CSerComInterface::CmdPipeRelease()
{
	if (IsCmdPipeOpen==TRUE)
	{
		PipeWriteAndWait("taskkill /f /im cmd.exe\n","TO",4);

		IsCmdPipeOpen=FALSE;
	}
	return TRUE;
}
BOOL CSerComInterface::GetCmdPipeStatus()
{
	return IsCmdPipeOpen;
}
BOOL CSerComInterface::CmdPipeWrite(char* writebuff)
{
	DWORD bytes_write;
	LogADBSendCommand(writebuff)
	if(!WriteFile(hChildStdinWr, writebuff, strlen(writebuff), &bytes_write, NULL))
		return FALSE;
	else return TRUE;
}
BOOL CSerComInterface::CmdPipeRead(char* readbuff)
{
	DWORD bytes_read=0;
	BOOL DRT=ReadFile(hChildStdoutRd, readbuff, 2048, &bytes_read, &osReader);
	LogADBReceiveCommand(readbuff)
	if(bytes_read==0||TRUE!=DRT)return FALSE;
	return TRUE;

}
BOOL CSerComInterface::CmdPipeReadLine(char* readbuff,int recurvTime)
{
	int index=0,i;
	DWORD bytes_read=0;
	char temp[4096]={0};
	DWORD DRT=PeekNamedPipe(hChildStdoutRd, temp, 4096, &bytes_read, NULL, NULL);   
	if(bytes_read==0)
	{
		for(i=0;i<recurvTime;i++)
		{

			Sleep(500);
			memset(temp,0,sizeof(temp));
			DRT=PeekNamedPipe(hChildStdoutRd, temp, 4096, &bytes_read, NULL, NULL);   
			if(bytes_read!=0) break;
		}
		if(i==recurvTime) return FALSE;
	}
	index = strcspn(temp,"\n");       
	DRT=ReadFile(hChildStdoutRd, readbuff, index+1, &bytes_read, &osReader);
	LogADBReceiveCommand(readbuff);
	if(bytes_read==0)return FALSE;
	return TRUE;
}
BOOL CSerComInterface::FlushPipe()
{
	DWORD bytes_read=0;
	DWORD i=0;
	int index=0;
	char temp[4096]={0};
	char readbuff[4096]={0};
	PeekNamedPipe(hChildStdoutRd, temp, 4096, &bytes_read, NULL, NULL);    
	if( bytes_read)
		return ReadFile(hChildStdoutRd, readbuff, bytes_read, &i, &osReader);
	return TRUE;
}
BOOL CSerComInterface::PipeWriteAndWait(char * inputStr,char* waitStr,int recurvetime)
{
	DWORD bytes_write=0;
	char readbuf[2048];
	FlushPipe();
	LogADBSendCommand(inputStr);
	BOOL BRT=WriteFile(hChildStdinWr, inputStr, strlen(inputStr), &bytes_write, NULL);   
	if(strcmp(waitStr,"NULL")==0)return TRUE;
	while(1)
	{
		memset(readbuf,0,sizeof(readbuf));
		if(CmdPipeReadLine(readbuf,recurvetime)==FALSE)return FALSE;	
		LogADBReceiveCommand(readbuf);
		printf("%s",readbuf);
		if(strstr(readbuf,waitStr)!=NULL)
			return TRUE;
	}
}