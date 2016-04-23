// SimRFCaltestUI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SimRFCaltestUI.h"
#include "SimRFDlg.h"
#include  "MainPage.h"

#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimRFCaltestUIApp

static CSimpleCriticalSection g_csTraceLog;
static CSimpleCriticalSection g_csDataLog;
 
void ToolTraceLog(LPCTSTR lpszModule, LPCSTR lpszSrcFile, UINT iSrcLine, EMsgLevel msgLevel, LPCTSTR lpszMsgFormat, ...)
{
	g_csTraceLog.Lock();
 
	va_list args;
	va_start(args, lpszMsgFormat);
	CString strLogMsg;
	_vstprintf(strLogMsg.GetBuffer(9000), lpszMsgFormat, args);
	strLogMsg.ReleaseBuffer();
	va_end(args);
 
	

	CMainPage* pDataWnd = dynamic_cast<CMainPage*>(((CSimRFCaltestUIApp*)AfxGetApp())->m_pMainPage);
		
	pDataWnd->AddTraceLog(lpszModule, lpszSrcFile, iSrcLine, msgLevel, strLogMsg);


	g_csTraceLog.Unlock();
	return;
}


void ToolFactoryLogEx(INT iProcessCode, LPCTSTR lpszBand, LPCTSTR lpszChannel,INT iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit, BOOL bPass, LPCTSTR lpszItemName,LPCTSTR lpszMsgFormat, ...)
{
	g_csDataLog.Lock();
 
		CMainPage* pDataWnd = dynamic_cast<CMainPage*>(((CSimRFCaltestUIApp*)AfxGetApp())->m_pMainPage);
	ASSERT(pDataWnd != NULL);
	if(pDataWnd == NULL) {
		g_csDataLog.Unlock();
		return;
	}
 
	va_list args;
	va_start(args, lpszMsgFormat);
	CString strLogMsg;
	_vstprintf(strLogMsg.GetBuffer(9000), lpszMsgFormat, args);
	strLogMsg.ReleaseBuffer();
	va_end(args);
   

	pDataWnd->AddFactoryLogEx(iProcessCode, lpszBand, lpszChannel, iErrorCode, lpszUL, lpszDL, lpszMeasured, lpszUnit, bPass, lpszItemName,strLogMsg);
 
	g_csDataLog.Unlock();
	return;
}


void ToolFactoryLog(INT iProcessCode, LPCTSTR lpszBand, LPCTSTR lpszChannel,INT iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit, BOOL bPass, LPCTSTR lpszMsgFormat, ...)
{
	g_csDataLog.Lock();
 
		CMainPage* pDataWnd = dynamic_cast<CMainPage*>(((CSimRFCaltestUIApp*)AfxGetApp())->m_pMainPage);
	ASSERT(pDataWnd != NULL);
	if(pDataWnd == NULL) {
		g_csDataLog.Unlock();
		return;
	}
 
	va_list args;
	va_start(args, lpszMsgFormat);
	CString strLogMsg;
	_vstprintf(strLogMsg.GetBuffer(9000), lpszMsgFormat, args);
	strLogMsg.ReleaseBuffer();
	va_end(args);
   

	pDataWnd->AddFactoryLog(iProcessCode, lpszBand, lpszChannel, iErrorCode, lpszUL, lpszDL, lpszMeasured, lpszUnit, bPass, strLogMsg);
 
	g_csDataLog.Unlock();
	return;
}

void ToolCommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage)
{
	g_csDataLog.Lock();
 
		CMainPage* pDataWnd = dynamic_cast<CMainPage*>(((CSimRFCaltestUIApp*)AfxGetApp())->m_pMainPage);
	ASSERT(pDataWnd != NULL);
	if(pDataWnd == NULL) {
		g_csDataLog.Unlock();
		return;
	}
 
	pDataWnd->AddCommandLog(lpszType, lpszMessage);
 
	g_csDataLog.Unlock();
	return;
}

void ToolDefaultLog(LPCTSTR lpszModule, LPCSTR lpszSrcFile, UINT iSrcLine, LPCTSTR lpszMsgFormat, ...)
{
	g_csTraceLog.Lock();
 
	va_list args;
	va_start(args, lpszMsgFormat);
	CString strLogMsg;
	_vstprintf(strLogMsg.GetBuffer(1000), lpszMsgFormat, args);
	strLogMsg.ReleaseBuffer();
	va_end(args);
 
	FILE *pToolLog = _tfopen(DEFAULT_TOOLLOG_FILENAME, _T("a"));
	if (pToolLog == NULL) {
		g_csTraceLog.Unlock();
		return;
	}
 
	USES_CONVERSION;
 
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	CString strCurTime;
	strCurTime.Format(_T("%02d:%02d:%02d.%03d"), systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);
 
	CString strSrcFile = CA2T(lpszSrcFile);
 
	CString strSrcLine;
	strSrcLine.Format(_T("%3d"), iSrcLine);
 
	_ftprintf(pToolLog, _T("%s,%s,%s,%s,%s\n"),
		strCurTime,
		lpszModule,
		PathFindFileName(strSrcFile),
		strSrcLine,
		strLogMsg);
 
	fclose(pToolLog);
 
	g_csTraceLog.Unlock();
	return;
}

BOOL ForceCreateDirectory(LPCTSTR lpszDirPath)
{
	if (lpszDirPath == NULL || lpszDirPath[0] == NULL)
		return TRUE;
 
	// check if the directory already exists
	HANDLE hFileSearch;
	WIN32_FIND_DATA fileInfo;
 
	hFileSearch = FindFirstFile(lpszDirPath, &fileInfo);
	if(fileInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
		FindClose(hFileSearch);
		return TRUE;
	}
	FindClose(hFileSearch);
 
	vector<CString> strArray;
	CString temp;
	CString strDirPath = lpszDirPath;
 
	for (int i = 0; i < strDirPath.GetLength(); i++) {
		if (strDirPath.GetAt(i) != _T('\\'))
			temp += strDirPath.GetAt(i);
		else {
			strArray.push_back(temp);
			temp += _T('\\');
		}
	}
	strArray.push_back(temp);
 
	// Create each level of the Directory Structure
	for (UINT i = 1; i < strArray.size(); i++) {
		int res = CreateDirectory(strArray[i], NULL);
		if (res)
			SetFileAttributes(strArray[i], FILE_ATTRIBUTE_NORMAL);
	}
	strArray.clear();
 
	// Check to see if the Directory was created and it actually is a Directory
	hFileSearch = FindFirstFile(strDirPath, &fileInfo);
	if(fileInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
		//  Directory Exists close file and return
		FindClose(hFileSearch);
		return TRUE;
	}
	else {
		// For Some reason the Function Failed  Return FALSE
		FindClose(hFileSearch);
		return FALSE;
	}
}

BOOL AppendFiles(LPCTSTR lpszDstFilePath, LPCTSTR lpszSrcFilePath)
{
	USES_CONVERSION;
	OFSTRUCT ofStruct = {0};
	ofStruct.cBytes = sizeof(OFSTRUCT);
 
	HANDLE hSrcFile = (HANDLE)OpenFile(CT2A(lpszSrcFilePath), &ofStruct, OF_READ);
 
	if ((HFILE)hSrcFile == HFILE_ERROR)
		return FALSE;
 
	DWORD dwSrcFileSize = GetFileSize(hSrcFile, NULL);
	DWORD dwSrcFileSizeRead;
	BYTE *pSrcFileBuffer = new BYTE[dwSrcFileSize];
	ReadFile(hSrcFile, pSrcFileBuffer, dwSrcFileSize, &dwSrcFileSizeRead, NULL);
	ASSERT(dwSrcFileSize == dwSrcFileSizeRead);
	CloseHandle(hSrcFile);
 
	HANDLE hDstFile = (HANDLE)OpenFile(CT2A(lpszDstFilePath), &ofStruct, OF_READWRITE);
 
	if ((HFILE)hDstFile == HFILE_ERROR) {
		delete []pSrcFileBuffer;
		return FALSE;
	}
 
	SetFilePointer(hDstFile, 0, NULL, FILE_END);
	DWORD dwBufferWritten;
	WriteFile(hDstFile, "\n", 1, &dwBufferWritten, NULL);
	WriteFile(hDstFile, pSrcFileBuffer, dwSrcFileSize, &dwBufferWritten, NULL);
	ASSERT(dwSrcFileSize == dwBufferWritten);
	CloseHandle(hDstFile);
 
	delete []pSrcFileBuffer;
	return TRUE;
}
BEGIN_MESSAGE_MAP(CSimRFCaltestUIApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSimRFCaltestUIApp construction

CSimRFCaltestUIApp::CSimRFCaltestUIApp()
{
	 m_hRFCalTestDLL=NULL;
     m_pRFCalTestProcessor=NULL;
	 m_pMainPage=NULL;
	 m_bEnableTraceLog=1;
	 m_pFuncOpenDatabase=NULL;
     m_pFuncCloseDataBase=NULL;
     m_pFuncGetLastErrorMsg=NULL;
	  m_pFuncInsertRecord=NULL;
     m_pFuncUpdateSingRecord=NULL;
	 m_pFuncQuerySingRecord=NULL;
}


// The one and only CSimRFCaltestUIApp object

CSimRFCaltestUIApp theApp;


// CSimRFCaltestUIApp initialization

BOOL CSimRFCaltestUIApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
    m_pConfigSetting=new CConfigSetting();

	 //if(!ParseSystemIni())
		//return false;
	

	m_bIsrunning=false;
	m_bEnableTraceLog=1;
	/* m_bIsFirstUpdateXMlLossUL=true;
     m_bIsFirstUpdateXMlLossDL=true;
    
    CStringStringMap m_test;
    m_test.insert(make_pair("888","2322")); 
	m_test.insert(make_pair("999","22")); 
    UpdateXMLloss("C:\\Program Files\\Qualcomm\\QDART\\Databases\\CalDB_NET.xml",m_test,0);
	m_test.clear();
    m_test.insert(make_pair("111","333")); 
	m_test.insert(make_pair("222","444"));
	UpdateXMLloss("C:\\Program Files\\Qualcomm\\QDART\\Databases\\CalDB_NET.xml",m_test,0,0);

	m_test.clear();
    m_test.insert(make_pair("555","666")); 
	m_test.insert(make_pair("777","888"));
	UpdateXMLloss("C:\\Program Files\\Qualcomm\\QDART\\Databases\\CalDB_NET.xml",m_test,0,1);

	m_test.clear();
    m_test.insert(make_pair("999","666")); 
	m_test.insert(make_pair("000","888"));
	UpdateXMLloss("C:\\Program Files\\Qualcomm\\QDART\\Databases\\CalDB_NET.xml",m_test,0,0);*/


    ParseSystemIni();
	
	CSimRFDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


void CSimRFCaltestUIApp::UpdateLogFilePath(BOOL bCreateFile)
{
	UpdateTraceLogFilePath(bCreateFile);
	UpdateFactoryLogFilePath(bCreateFile);
	UpdateCommandLogFilePath(bCreateFile);
	
}
void CSimRFCaltestUIApp::UpdateTraceLogFilePath(BOOL bCreateFile)
{
	CMainPage* pTraceLogWnd = dynamic_cast<CMainPage*>(((CSimRFCaltestUIApp*)AfxGetApp())->m_pMainPage);

	
	
     CTime time = CTime::GetCurrentTime();
	CString strLogDirPath;
	//::GetModuleFileName(NULL, strLogDirPath.GetBuffer(_MAX_PATH), _MAX_PATH);
	//strLogDirPath.ReleaseBuffer();
	//strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
    CString strLogFileName;
	strLogFileName.Format(_T("TraceLog_%s_%s.txt"), m_strSN,time.Format(_T("%m%d%H%M%S")));
	strLogDirPath = m_LogPath +_T("\\")+ strProjectName+_T("\\")+strstationName+_T("\\")+time.Format(_T("%Y%m%d")) + _T("\\")  +"TRACELOG\\"+strLogFileName;
 
	if (bCreateFile)
		pTraceLogWnd->CreateLogFileAndCreateDir(strLogDirPath);
	else
	{
		if(m_bIsPass)
		 strLogFileName.Format(_T("P_TraceLog_%s_%s.txt"),m_strSN, time.Format(_T("%m%d%H%M%S")));
		else
         strLogFileName.Format(_T("F_TraceLog_%s_%s.txt"),m_strSN, time.Format(_T("%m%d%H%M%S")));

        strLogDirPath = m_LogPath+_T("\\")+ strProjectName+_T("\\")+strstationName+_T("\\")+ time.Format(_T("%Y%m%d")) + _T("\\")  +"TRACELOG\\"+strLogFileName;
		pTraceLogWnd->ChangeLogFilePath(strLogDirPath);
	}
}
 
 
void CSimRFCaltestUIApp::UpdateFactoryLogFilePath(BOOL bCreateFile)
{
	
		CString strLogDirPath;
		//::GetModuleFileName(NULL, strLogDirPath.GetBuffer(_MAX_PATH), _MAX_PATH);
		//strLogDirPath.ReleaseBuffer();
		//strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
        
	    CTime time = CTime::GetCurrentTime();
	   
	    CString strLogFileName;
	    strLogFileName.Format(_T("FactoryLog_%s_%s.csv"),m_strSN, time.Format(_T("%m%d%H%M%S")));
     
	   strLogDirPath = m_LogPath +_T("\\")+  strProjectName+_T("\\")+strstationName+_T("\\")+time.Format(_T("%Y%m%d")) + _T("\\") +"FACTORYDLOG\\"+ strLogFileName;
 
	if (bCreateFile)
	{
		CreateFactoryLogFileAndCreateDir(strLogDirPath);
		

	}
	else
	{
		if(m_bIsPass)
		 strLogFileName.Format(_T("P_FactoryLog_%s_%s.csv"),m_strSN, time.Format(_T("%m%d%H%M%S")));
		else
         strLogFileName.Format(_T("F_FactoryLog_%s_%s.csv"),m_strSN, time.Format(_T("%m%d%H%M%S")));

        strLogDirPath = m_LogPath +_T("\\")+  strProjectName+_T("\\")+strstationName+_T("\\")+time.Format(_T("%Y%m%d")) + _T("\\") +"FACTORYDLOG\\"+ strLogFileName;
		ChangeFactoryLogFilePath(strLogDirPath);
	}
}


 
void CSimRFCaltestUIApp::UpdateCommandLogFilePath(BOOL bCreateFile)
{	
	    CString strLogDirPath;
		//::GetModuleFileName(NULL, strLogDirPath.GetBuffer(_MAX_PATH), _MAX_PATH);
		//strLogDirPath.ReleaseBuffer();
		//strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
        
	    CTime time = CTime::GetCurrentTime();
	   
	    CString strLogFileName;
	    strLogFileName.Format(_T("CommandLog_%s_%s.txt"),m_strSN, time.Format(_T("%m%d%H%M%S")));
	
	   strLogDirPath = m_LogPath+_T("\\")+  strProjectName+_T("\\")+strstationName+_T("\\")+time.Format(_T("%Y%m%d")) + _T("\\") +"COMMANDLOG\\" +strLogFileName;
 
	if (bCreateFile)
		CreateCommandLogFileAndCreateDir(strLogDirPath);
	else
	{
		if(m_bIsPass)
		 strLogFileName.Format(_T("P_CommandLog_%s_%s.txt"),m_strSN, time.Format(_T("%m%d%H%M%S")));
		else
         strLogFileName.Format(_T("F_CommandLog_%s_%s.txt"),m_strSN, time.Format(_T("%m%d%H%M%S")));

		strLogDirPath = m_LogPath+_T("\\")+  strProjectName+_T("\\")+strstationName+_T("\\")+time.Format(_T("%Y%m%d")) + _T("\\") +"COMMANDLOG\\" +strLogFileName;
		ChangeCommandLogFilePath(strLogDirPath);
	}
}

void CSimRFCaltestUIApp::CreateFactoryLogFileAndCreateDir(LPCTSTR lpszLogFilePath)
{
	
		m_strFactoryLogFilePath = lpszLogFilePath;
 
		// Make sure first the directory the log file exists in is already created
		CString strLogDirPath = lpszLogFilePath;
		strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
 
		ForceCreateDirectory(strLogDirPath);
 
		// Create log file
		m_pFactoryLog = _tfopen(m_strFactoryLogFilePath, _T("a"));
		ASSERT(m_pFactoryLog != NULL);
		if (m_pFactoryLog == NULL)
		{
			CString strErrMsg;
			strErrMsg.Format(_T("Create log failed - %s"), m_strFactoryLogFilePath);
			AfxMessageBox(strErrMsg);
		}

		_ftprintf(m_pFactoryLog, _T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n"),
			"Time",
			"ItemCode", 
			"Band",
			"Channel",
			"ErrorCode",
			"UpperBound",
			"LowerBound",
			"EvaluatedValue",
			"Unit",
			"Pass/Fail",
			"DuringTime",
			"Message");


	fflush(m_pFactoryLog);

	
}
 
void CSimRFCaltestUIApp::CreateCommandLogFileAndCreateDir(LPCTSTR lpszLogFilePath)
{
	
		m_strCommandLogFilePath = lpszLogFilePath;
 
		// Make sure first the directory the log file exists in is already created
		CString strLogDirPath = lpszLogFilePath;
		strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
 
		ForceCreateDirectory(strLogDirPath);
 
		// Create log file
		m_pCommandLog = _tfopen(m_strCommandLogFilePath, _T("a"));
		ASSERT(m_pCommandLog != NULL);
		if (m_pCommandLog == NULL) {
			CString strErrMsg;
			strErrMsg.Format(_T("Create log failed - %s"), m_strCommandLogFilePath);
			AfxMessageBox(strErrMsg);
		}
	
}
 
void CSimRFCaltestUIApp::ChangeFactoryLogFilePath(LPCTSTR lpszLogFilePath)
{
	if (m_strFactoryLogFilePath == lpszLogFilePath)
		return;
 
	bool bFileOpened = false;
	if (m_pFactoryLog != NULL) 
	{
		fclose(m_pFactoryLog);
		bFileOpened = TRUE;
	}
 
	if (_taccess(lpszLogFilePath, 0) == 0)
	{
		// append
		AppendFiles(lpszLogFilePath, m_strFactoryLogFilePath);
	}
	else 
	{
		// copy
		CString strLogDirPath = lpszLogFilePath;
		strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
 
		ForceCreateDirectory(strLogDirPath);
		CopyFile(m_strFactoryLogFilePath, lpszLogFilePath, FALSE);
	}
 
	// delete the original file and re-open the new file if necessary
	DeleteFile(m_strFactoryLogFilePath);
	m_strFactoryLogFilePath = lpszLogFilePath;
 
	if (bFileOpened) 
	{
		m_pFactoryLog = _tfopen(m_strFactoryLogFilePath, _T("a"));
		ASSERT(m_pFactoryLog != NULL);
		if (m_pFactoryLog == NULL) 
		{
			CString strErrMsg;
			strErrMsg.Format(_T("Change log file path failed - %s"), m_strFactoryLogFilePath);
			AfxMessageBox(strErrMsg);
		}

		fclose(m_pFactoryLog);
}
}
 
void CSimRFCaltestUIApp::ChangeCommandLogFilePath(LPCTSTR lpszLogFilePath)
{
	if (m_strCommandLogFilePath == lpszLogFilePath)
		return;
 
	bool bFileOpened = false;
	if (m_pCommandLog != NULL) 
	{
		fclose(m_pCommandLog);
		bFileOpened = TRUE;
	}
 
	if (_taccess(lpszLogFilePath, 0) == 0) 
	{
		// append
		AppendFiles(lpszLogFilePath, m_strCommandLogFilePath);
	}
	else
	{
		// copy
		CString strLogDirPath = lpszLogFilePath;
		strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
 
		ForceCreateDirectory(strLogDirPath);
		CopyFile(m_strCommandLogFilePath, lpszLogFilePath, FALSE);
	}
 
	// delete the original file and re-open the new file if necessary
	DeleteFile(m_strCommandLogFilePath);
	m_strCommandLogFilePath = lpszLogFilePath;
 
	if (bFileOpened)
	{
		m_pCommandLog = _tfopen(m_strCommandLogFilePath, _T("a"));
		ASSERT(m_pCommandLog != NULL);
		if (m_pCommandLog == NULL) 
		{
			CString strErrMsg;
			strErrMsg.Format(_T("Change log file path failed - %s"), m_strCommandLogFilePath);
			AfxMessageBox(strErrMsg);
		}

		fclose(m_pCommandLog);
	}
}
bool  CSimRFCaltestUIApp::ParseDBINI()
{
   CString strDBDllPath;
   CString strDllPathName;
  
   FILE* fp1;
   _TCHAR _tKeyValue[1000];
   char szTemp[_MAX_PATH];
  ::GetModuleFileName(NULL, szTemp, _MAX_PATH);
	  strDllPathName.Format("%s",szTemp);
     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
	
	//strDBDllPath=strDllPathName+"\\DataBase\\DataBase.dll";	
    strDBDllPath="DataBase.dll";
	strDllPathName=strDllPathName+_T("\\DataBase\\SFC_DB_Config.ini");
	if((fp1=fopen(strDllPathName,"r"))==NULL)
	{
        CString strTemp=strDllPathName+_T("  not exist");
		AfxMessageBox(strTemp);
		return false;
	}

	 m_pConfigSetting->dbConfig.strDBDllPath=strDBDllPath;

      ::GetPrivateProfileString(_T("DataBaseSetting"),_T("DSN"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	m_pConfigSetting->dbConfig.s_DataBaseConfig.strDSN=_tKeyValue;

	::GetPrivateProfileString(_T("DataBaseSetting"),_T("USER"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	m_pConfigSetting->dbConfig.s_DataBaseConfig.strUSER=_tKeyValue;

	::GetPrivateProfileString(_T("DataBaseSetting"),_T("PASSWORD"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	 m_pConfigSetting->dbConfig.s_DataBaseConfig.strPWD=_tKeyValue;
	 fclose(fp1);
  return true;
}
bool CSimRFCaltestUIApp::ParseSFINI()
{

  
  
   CString strDllPathName;
   CString strDLLPath;
   FILE* fp1;
   _TCHAR _tKeyValue[1000];

    char szTemp[_MAX_PATH];
  ::GetModuleFileName(NULL, szTemp, _MAX_PATH);
	  strDllPathName.Format("%s",szTemp);

     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
	strDLLPath=strDllPathName+"\\DataBase\\DBHelper.dll";	

	strDllPathName=strDllPathName+_T("\\DataBase\\SFC_DB_Config.ini");
	if((fp1=fopen(strDllPathName,"r"))==NULL)
	{
        CString strTemp=strDllPathName+_T("  not exist");
		AfxMessageBox(strTemp);
		return false;
	}

	m_pConfigSetting->dbConfig.strSFDllPath=strDLLPath;
   
   ::GetPrivateProfileString(_T("SFCSetting"),_T("ServerAddr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strServerAddr=_tKeyValue;

   ::GetPrivateProfileString(_T("SFCSetting"),_T("password"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strPassword=_tKeyValue;

    ::GetPrivateProfileString(_T("SFCSetting"),_T("UID"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strUID=_tKeyValue;

      ::GetPrivateProfileString(_T("SFCSetting"),_T("Catalog"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strCataLog=_tKeyValue;

     ::GetPrivateProfileString(_T("SFCSetting"),_T("Result"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strReturnOK=_tKeyValue;

    ::GetPrivateProfileString(_T("SFCSetting"),_T("StationID"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strStationID=_tKeyValue;

    ::GetPrivateProfileString(_T("SFCSetting"),_T("Fixture"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strFixID=_tKeyValue;

   ::GetPrivateProfileString(_T("SFCSetting"),_T("Line"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strLineNum=_tKeyValue;

    ::GetPrivateProfileString(_T("SFCSetting"),_T("Creator"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_pConfigSetting->dbConfig.s_SFSystemConfig.strCreator=_tKeyValue;

  
fclose(fp1);
   return true;

}
bool CSimRFCaltestUIApp::ParseSystemIni()
{
	 CString strDllPathName;
	 CString strTemp;
	 CString strIsUseDB;
	_TCHAR _tKeyName[1000]={0};
	_TCHAR _TSectionName[1000]={0};
	_TCHAR _tKeyValue[1000];
	FILE* fp1;
    char szTemp[_MAX_PATH];
	::GetModuleFileName(NULL, szTemp, _MAX_PATH);
	strDllPathName.Format("%s",szTemp);
     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
		
	strDllPathName=strDllPathName+_T("\\SystemConfig\\SystemSetup.ini");
	if((fp1=fopen(strDllPathName,"r"))==NULL)
	{
        CString strTemp=strDllPathName+_T("  not exist");
		AfxMessageBox(strTemp);
		return false;
	}
	
   ::GetPrivateProfileString(_T("File Path"),_T("SequencePath"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   m_strIniPath=_tKeyValue;
   int iFindIndex=m_strIniPath.ReverseFind('\\');
   strstationName=m_strIniPath.Right(theApp.m_strIniPath.GetLength()-iFindIndex-1);
   strstationName=strstationName.Left(strstationName.GetLength()-4);

   strProjectName=m_strIniPath.Left(iFindIndex);
   iFindIndex=strProjectName.ReverseFind('\\');
   strProjectName=strProjectName.Right(strProjectName.GetLength()-iFindIndex-1);
   
 

    ::GetPrivateProfileString(_T("File Path"),_T("LogPath"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
     m_LogPath=_tKeyValue;


    ::GetPrivateProfileString(_T("Settings"),_T("Device_Addr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strGPIBAddr=_tKeyValue;

	    ::GetPrivateProfileString(_T("Settings"),_T("Device_Addr1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strGPIBAddr1=_tKeyValue;

	 ::GetPrivateProfileString(_T("Settings"),_T("Device_AddrPly"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strGPIBAddrPLY=_tKeyValue;

	    ::GetPrivateProfileString(_T("Settings"),_T("Device_AddrPly1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strGPIBAddrPLY1=_tKeyValue;

	 ::GetPrivateProfileString(_T("Settings"),_T("PowerSupplyPort"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->m_iPlyPort=atoi(_tKeyValue);

	    ::GetPrivateProfileString(_T("Settings"),_T("PowerSupply1Port"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->m_iPly1Port=atoi(_tKeyValue);

	 ::GetPrivateProfileString(_T("Settings"),_T("FreqMeasAddr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strFreqMeasAddr=_tKeyValue;

	::GetPrivateProfileString(_T("Settings"),_T("MulMeasAddr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strMulMeasAddr=_tKeyValue;

	 ::GetPrivateProfileString(_T("Settings"),_T("PowerSupply1Port"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->m_iPly1Port=atoi(_tKeyValue);

	::GetPrivateProfileString(_T("Settings"),_T("TesterDeviceCommon"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strTestDevceName=_tKeyValue;

	::GetPrivateProfileString(_T("Settings"),_T("TesterDevice1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strTestDevceName1=_tKeyValue;

	::GetPrivateProfileString(_T("Settings"),_T("PowerSupplyCommon"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strPowerSupplyName=_tKeyValue;

	::GetPrivateProfileString(_T("Settings"),_T("PowerSupply1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strPowerSupplyName1=_tKeyValue;

	::GetPrivateProfileString(_T("Settings"),_T("FreqMeasDevice"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strFreqMeasName=_tKeyValue;
    
	::GetPrivateProfileString(_T("Settings"),_T("MulMeasDevice"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strMulMeasName=_tKeyValue;
    
	    //::GetPrivateProfileString(_T("Settings"),_T("Device_Addr2"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   // m_pConfigSetting->strGPIBAddr2=_tKeyValue;

   ::GetPrivateProfileString(_T("Settings"),_T("PhoneComport"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->m_PhonePort=atoi(_tKeyValue);
    
	  ::GetPrivateProfileString(_T("Settings"),_T("LoopCount"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_iLoopCount=atoi(_tKeyValue);
	

	::GetPrivateProfileString(_T("Settings"),_T("ATComport"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->m_ATPort=atoi(_tKeyValue);

   ::GetPrivateProfileString(_T("Settings"),_T("ProjectName"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->strProjectName=_tKeyValue;

    ::GetPrivateProfileString(_T("Settings"),_T("IsDoSF"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    strTemp=_tKeyValue;

	::GetPrivateProfileString(_T("Settings"),_T("IsDoDB"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    strIsUseDB=_tKeyValue;

	

	 ::GetPrivateProfileString(_T("Settings"),_T("ToolVersion"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_strToolVer=_tKeyValue;

	::GetPrivateProfileString(_T("Settings"),_T("EnableTraceLog"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_bEnableTraceLog=atoi(_tKeyValue);
	::GetPrivateProfileString(_T("Settings"),_T("SN_Header"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->m_strSNHeader=_tKeyValue;	

	m_pConfigSetting->m_iSNLength=::GetPrivateProfileInt(_T("Settings"),_T("SN_Length"),15,strDllPathName);

	

	if(strstr(strTemp,"1"))
	{
		m_bIsDOSF=true;
		ParseSFINI();
	}
	else
	{
		m_bIsDOSF=false;
	}

		if(strstr(strIsUseDB,"1"))
	{
		m_bIsDataBase=true;
		ParseDBINI();
	}
	else
	{
		m_bIsDataBase=false;
	}

	 ::GetPrivateProfileString(_T("Settings"),_T("StopWhenFail"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    strTemp=_tKeyValue;

	if(strstr(strTemp,"1"))
	{
		m_bStopWhenFail=true;
	}
	else
	{
		m_bStopWhenFail=false;
	}

	 ::GetPrivateProfileString(_T("Settings"),_T("RunAfterSN"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    strTemp=_tKeyValue;

	if(strstr(strTemp,"1"))
	{
		m_bRunAfterSN=true;
	}
	else
	{
		m_bRunAfterSN=false;
	}


     m_pConfigSetting->m_bStopWhenFail=m_bStopWhenFail;

	 

	::GetPrivateProfileString(_T("Settings"),_T("PhoneOpenPortRetryTime"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    m_pConfigSetting->m_iRetryPhonePortTimes=atoi(_tKeyValue);

    ::GetPrivateProfileString(_T("Settings"),_T("Device_Addr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
   

		
	m_pRFXML.Load("");// not know why now 

    if(m_pRFXML.Load(theApp.m_strIniPath)!=0)
	{
       CString strTemp=theApp.m_strIniPath+_T("   not exist");
		AfxMessageBox(strTemp);
		return false;
	}


     
	CString NodeText;
	XMLNode node;
    ::GetPrivateProfileString(_T("Settings"),_T("TesterDeviceCommon"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	//::WritePrivateProfileString("PreObjects","TesterDeviceCommon",_tKeyValue,theApp.m_strIniPath);
    node=m_pRFXML.SearchNode("//Configurations/MainObject/TesterDeviceCommon");
	NodeText=_tKeyValue;
	m_pRFXML.SetNodeText(node,NodeText);
	::GetPrivateProfileString(_T("Settings"),_T("TesterDevice1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	//::WritePrivateProfileString("PreObjects","TesterDevice1",_tKeyValue,theApp.m_strIniPath);*/
    node=m_pRFXML.SearchNode("//Configurations/MainObject/TesterDevice1");
	NodeText=_tKeyValue;
	m_pRFXML.SetNodeText(node,NodeText);


	 ::GetPrivateProfileString(_T("Settings"),_T("PowerSupplyCommon"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	//::WritePrivateProfileString("PreObjects","TesterDeviceCommon",_tKeyValue,theApp.m_strIniPath);
    node=m_pRFXML.SearchNode("//Configurations/MainObject/PowerSupplyCommon");
	NodeText=_tKeyValue;
	m_pRFXML.SetNodeText(node,NodeText);

	 ::GetPrivateProfileString(_T("Settings"),_T("PowerSupplyPort"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	//::WritePrivateProfileString("PreObjects","TesterDeviceCommon",_tKeyValue,theApp.m_strIniPath);
    node=m_pRFXML.SearchNode("//Configurations/MainObject/PowerSupplyCommonPort");
	NodeText=_tKeyValue;
	m_pRFXML.SetNodeText(node,NodeText);

	::GetPrivateProfileString(_T("Settings"),_T("PowerSupply1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	//::WritePrivateProfileString("PreObjects","TesterDeviceCommon",_tKeyValue,theApp.m_strIniPath);
    node=m_pRFXML.SearchNode("//Configurations/MainObject/PowerSupply1");
	NodeText=_tKeyValue;
	m_pRFXML.SetNodeText(node,NodeText);


	::GetPrivateProfileString(_T("Settings"),_T("PowerSupply1Port"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	//::WritePrivateProfileString("PreObjects","TesterDeviceCommon",_tKeyValue,theApp.m_strIniPath);
    node=m_pRFXML.SearchNode("//Configurations/MainObject/PowerSupply1Port");
	NodeText=_tKeyValue;
	m_pRFXML.SetNodeText(node,NodeText);

	::GetPrivateProfileString(_T("Settings"),_T("FreqMeasDevice"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	//::WritePrivateProfileString("PreObjects","TesterDeviceCommon",_tKeyValue,theApp.m_strIniPath);
    node=m_pRFXML.SearchNode("//Configurations/MainObject/FreqMeasDevice");
	NodeText=_tKeyValue;
	m_pRFXML.SetNodeText(node,NodeText);

    ::GetPrivateProfileString(_T("Settings"),_T("MulMeasDevice"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	//::WritePrivateProfileString("PreObjects","TesterDeviceCommon",_tKeyValue,theApp.m_strIniPath);
    node=m_pRFXML.SearchNode("//Configurations/MainObject/MulMeasDevice");
	NodeText=_tKeyValue;
	m_pRFXML.SetNodeText(node,NodeText);

	m_pRFXML.Save();
	fclose(fp1);
  
   
	if(!LoadCableLossFromIni())
	{

        
		//return false;
	}
	
	if(!theApp.LoadConfigDataFromXML(theApp.m_strIniPath))
	{
		//return false;
	}
	
	


return true;


}

bool CSimRFCaltestUIApp::ConvertToVector(_TCHAR* tCharSrc,vector<CString> & vtrOut)
{
	vtrOut.clear();
	  int iIdex=0;
	  char* _tToken;
	  char* steps=";";

		

		 _tToken=strtok((char*)tCharSrc,steps);
		while(_tToken!=NULL)
		{
	   
			CString strTokenKey=_tToken;
			vtrOut.push_back(strTokenKey);
			_tToken=strtok(NULL,steps);
			
		}
		return true;

}
bool CSimRFCaltestUIApp::ReleaseResource()
{

	 if(m_hCalTestThread)
	 {
	    if(m_pRFCalTestProcessor)
		   {
			  
			   m_pRFCalTestProcessor->Free();
			   m_pRFCalTestProcessor=NULL;
			  
		   }
		   if(m_hRFCalTestDLL)
		   {
			   FreeLibrary(m_hRFCalTestDLL);
			   m_hRFCalTestDLL=NULL;
		   }
	 }

     return true;

}
bool CSimRFCaltestUIApp::LoadCableLossFromIni()
{
    CString strDllPathName;
	CStringStringMap mapKey2Value;
	_TCHAR _tKeyName[1000]={0};
	_TCHAR _TSectionName[1000]={0};
	_TCHAR _tKeyValue[1000];
   	vector<CString> vtrSecnames;
	vector<CString> vtrKeynames;
	vector<CString> vtrValuenames;
	char szTemp[_MAX_PATH];
	::GetModuleFileName(NULL, szTemp, _MAX_PATH);
	  strDllPathName.Format(szTemp);
     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
		
	strDllPathName=strDllPathName+_T("\\SystemConfig\\LossConfig.ini");
	m_pConfigSetting->m_MapLossConfig.clear();
	if(fopen(strDllPathName,"r")==NULL)
	{
        CString strTemp=strDllPathName+_T("  not exist");
		AfxMessageBox(strTemp);
		return false;
	} 
    
	 int iIdex=0;
		 ::GetPrivateProfileSectionNames(_TSectionName,sizeof(_TSectionName),strDllPathName);
		  do
		 {
			 if(_TSectionName[iIdex]==_T('\0'))
				_TSectionName[iIdex]=_T(';');
				iIdex++;
		 }while(!(_TSectionName[iIdex]==_T('\0') && _TSectionName[iIdex+1]==_T('\0')));

		  ConvertToVector(_TSectionName,vtrSecnames);

          vector<CString>::iterator itr1;
		  vector<CString>::iterator itr2;
		  for(itr1=vtrSecnames.begin();itr1!=vtrSecnames.end();++itr1)
		  {
			 memset(_tKeyName,0,sizeof(_tKeyName));
			  CString strSecname=*itr1;
			  ::GetPrivateProfileString(strSecname,NULL,NULL,_tKeyName,sizeof(_tKeyName),strDllPathName);
			  iIdex=0;
			    do
		 {
			 if(_tKeyName[iIdex]==_T('\0'))
				_tKeyName[iIdex]=_T(';');
				iIdex++;
		 }while(!(_tKeyName[iIdex]==_T('\0') && _tKeyName[iIdex+1]==_T('\0')));
			    ConvertToVector(_tKeyName,vtrKeynames);
				mapKey2Value.clear();
		            for(itr2=vtrKeynames.begin();itr2!=vtrKeynames.end();++itr2)
						{
							CString strKeyname=*itr2;
						   
							::GetPrivateProfileString(strSecname,strKeyname,NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
							CString strValue=_tKeyValue;
							
							mapKey2Value.insert(make_pair(strKeyname,strValue));
							
						}
					
					m_pConfigSetting->m_MapLossConfig.push_back(make_pair(strSecname,mapKey2Value));
		 }
	 return true;

}

void CSimRFCaltestUIApp::MainPageLoadIniUpdateUI()
{
	ASSERT(m_pMainPage!=NULL);

    if(m_pMainPage!=NULL)
		((CMainPage*)m_pMainPage)->LoadIniAndUpdateUi();
}

bool CSimRFCaltestUIApp::ParseObjectsFromXML_CheckEnable(const CString & strNodePath,const CString & strCheckEnablePath,CCString2StringMap & vtrStringPairRef)
{
  if(!m_pRFXML.IsLoad())
	{
       AfxMessageBox("XML not load");
		return false;
	}
    XMLNode node=m_pRFXML.SearchNode(strNodePath);
    XMLNodeList nodeList = m_pRFXML.GetChildNodes(node);

    
   for (UINT i = 0; i < m_pRFXML.GetNodeListSize(nodeList); i++)
   {
		XMLNode node = m_pRFXML.GetNodeListItem(nodeList, i);
 
		if (m_pRFXML.GetNodeType(node) != XMLNodeType_Element)
			continue;
		CString strClsName = m_pRFXML.GetNodeAttrValue(node, _T("ClassName"));
		CString strName = m_pRFXML.GetNodeAttrValue(node, _T("Name"));

	    CString strXMLPath;
	   strXMLPath.Format(_T("%s/Item[@Name=\"%s\"]"),strCheckEnablePath,strName);
	   XMLNode nodeEnable = m_pRFXML.SearchNode(strXMLPath);
	   CString strProcessEnabled = m_pRFXML.GetNodeAttrValue(nodeEnable, _T("Enabled"));
       
	    if((strProcessEnabled.CompareNoCase(_T("TRUE")) != 0) && (strProcessEnabled.CompareNoCase(_T("1")) != 0))
		continue;
		CStringStringMap mapAttrList;
  
		mapAttrList.insert(make_pair(_T("Name"),strName));
 
		XMLNodeList nodeChildList = m_pRFXML.GetChildNodes(node);
		for (UINT j = 0; j < m_pRFXML.GetNodeListSize(nodeChildList); j++) {
			XMLNode nodeAttr = m_pRFXML.GetNodeListItem(nodeChildList, j);
 
			if (m_pRFXML.GetNodeType(nodeAttr) != XMLNodeType_Element)
				continue;
           
			CString strAttrName = m_pRFXML.GetNodeName(nodeAttr);
			CString strAttrValue;
 
			if (strAttrName == _T("List")) {
				// Get node items of Enabled=True
				XMLNodeList nodeItemList = m_pRFXML.GetChildNodes(nodeAttr);
 
				for (UINT k = 0; k < m_pRFXML.GetNodeListSize(nodeItemList); k++) {
					XMLNode nodeItem = m_pRFXML.GetNodeListItem(nodeItemList, k);
					CString strEnabled = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Enabled"));
                    CString nodeItemName = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Name"));
					
					if (strEnabled.CompareNoCase(_T("TRUE"))==0 || strEnabled.CompareNoCase(_T("1"))==0)
					{
						
				
						if (strAttrValue.IsEmpty())
							strAttrValue = nodeItemName;
						else
							strAttrValue = strAttrValue + _T(",") + nodeItemName;
					}
				}
			}
			else
				strAttrValue = m_pRFXML.GetNodeText(nodeAttr);
 
		
			mapAttrList.insert(make_pair(strAttrName,strAttrValue));
		}
 
		vtrStringPairRef.push_back(make_pair(strClsName, mapAttrList));
	}

 return true;
}

bool CSimRFCaltestUIApp::UpdateXMlProcessProject(const CString & strNodeName,const CString & strNodePath,CStringStringMap mapNodeDetails,bool bIsInChildNode)
{
   if(!m_pRFXML.IsLoad())
	{
       AfxMessageBox("XML not load");
		return false;
	}
   
   CString strOrgPath=strNodePath;

  if(bIsInChildNode)
{
     XMLNodeList nodeList = m_pRFXML.GetChildNodes(strOrgPath);
	 for (UINT i = 0; i < m_pRFXML.GetNodeListSize(nodeList); i++) 
	{
		
		XMLNode node = m_pRFXML.GetNodeListItem(nodeList, i);
			if (m_pRFXML.GetNodeType(node) != XMLNodeType_Element)
				continue;
		XMLNodeList nodeList2=m_pRFXML.GetChildNodes(node);
		for(UINT j = 0; j< m_pRFXML.GetNodeListSize(nodeList2); j++)
		{
		   XMLNode node2 = m_pRFXML.GetNodeListItem(nodeList2, j);
		   if (m_pRFXML.GetNodeType(node2) != XMLNodeType_Element)
				continue;
		   CString strAttrName = m_pRFXML.GetNodeAttrValue(node2,"Name");
		   if(strAttrName==strNodeName)
		   {
                CStringStringMapItr itrFind;
				CStringStringMapItr itrFind2;
				CStringStringMapItr itrFind3;
				XMLNodeList nodeList3=m_pRFXML.GetChildNodes(node2);

				for(UINT k= 0; k< m_pRFXML.GetNodeListSize(nodeList3); k++)
				{
					 
					 CString strAttrValue;
					 CString strBitMask;
				   XMLNode node3=m_pRFXML.GetNodeListItem(nodeList3, k);
			
                   if (m_pRFXML.GetNodeType(node3) != XMLNodeType_Element)
				continue;

				  CString strAttrName = m_pRFXML.GetNodeName(node3);
				  itrFind=mapNodeDetails.find(strAttrName);
				  if(itrFind==mapNodeDetails.end())
					  continue;
                if (strAttrName == _T("List")) 
				{
					
					XMLNodeList nodeItemList = m_pRFXML.GetChildNodes(node3);
	                itrFind2=mapNodeDetails.find("ListMask");
						if(itrFind2==mapNodeDetails.end())
					    continue;
					CStringVtr vtrBitMask;
					CStringVtr vtrItems;
					CStringStringMap mapItemMask;
					CStr::ParseString(itrFind2->second,",",vtrBitMask);
					CStr::ParseString(itrFind->second,",",vtrItems);
					CStr::MakeVector2Map(vtrItems,vtrBitMask,mapItemMask);
					for (UINT m = 0; m< m_pRFXML.GetNodeListSize(nodeItemList); m++) 
					{
						
						XMLNode nodeItem = m_pRFXML.GetNodeListItem(nodeItemList, m);
						CString nodeItemAttrValue=m_pRFXML.GetNodeAttrValue(nodeItem,"Name");
						itrFind3=mapItemMask.find(nodeItemAttrValue);
						if(itrFind3==mapItemMask.end())
						 m_pRFXML.SetNodeAttrValue(nodeItem,"Enabled","FALSE");
						else
						{
						  if(itrFind3->second=="1")
						 m_pRFXML.SetNodeAttrValue(nodeItem,"Enabled","TRUE");
						 else
                         m_pRFXML.SetNodeAttrValue(nodeItem,"Enabled","FALSE");
						}
						 
               
					
					}
              
					
				}
				else
				{
					strAttrValue =itrFind->second; 
					m_pRFXML.SetNodeText(node3,strAttrValue);
				}

				

				}

		   }
		}
	    
	}
}

  m_pRFXML.Save();
   return true;


}
bool CSimRFCaltestUIApp::GetMapFromNodeName(const CString & strNodeName,const CString & strNodePath,CStringPairVtr & mapNodeDetails,bool bIsInChildNode)
{
    if(!m_pRFXML.IsLoad())
	{
       AfxMessageBox("XML not load");
		return false;
	}

	

   
	CString strOrgPath=strNodePath;

if(bIsInChildNode)
{
     XMLNodeList nodeList = m_pRFXML.GetChildNodes(strOrgPath);
	 for (UINT i = 0; i < m_pRFXML.GetNodeListSize(nodeList); i++) 
	{
		
		XMLNode node = m_pRFXML.GetNodeListItem(nodeList, i);
			if (m_pRFXML.GetNodeType(node) != XMLNodeType_Element)
				continue;
		XMLNodeList nodeList2=m_pRFXML.GetChildNodes(node);
		for(UINT j = 0; j< m_pRFXML.GetNodeListSize(nodeList2); j++)
		{
		   XMLNode node2 = m_pRFXML.GetNodeListItem(nodeList2, j);
		   if (m_pRFXML.GetNodeType(node2) != XMLNodeType_Element)
				continue;
		   CString strAttrName = m_pRFXML.GetNodeAttrValue(node2,"Name");
		   if(strAttrName==strNodeName)
		   {
             
				XMLNodeList nodeList3=m_pRFXML.GetChildNodes(node2);

				for(UINT k= 0; k< m_pRFXML.GetNodeListSize(nodeList3); k++)

				{
				   XMLNode node3=m_pRFXML.GetNodeListItem(nodeList3, k);
			
                   if (m_pRFXML.GetNodeType(node3) != XMLNodeType_Element)
				continue;

				   CString strAttrName = m_pRFXML.GetNodeName(node3);
                   CString strAttrValue;
				   CString strBitMask;
                if (strAttrName == _T("List")) 
				{
				// Get node items of Enabled=True
					
					XMLNodeList nodeItemList = m_pRFXML.GetChildNodes(node3);
	 
					for (UINT m = 0; m< m_pRFXML.GetNodeListSize(nodeItemList); m++) 
					{
						XMLNode nodeItem = m_pRFXML.GetNodeListItem(nodeItemList, m);
						CString strEnabled = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Enabled"));
						CString nodeItemName = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Name"));

						if (strAttrValue.IsEmpty())
							
								strAttrValue = nodeItemName;
								
						else
								strAttrValue = strAttrValue + _T(",") + nodeItemName;	
							
						if (strEnabled.CompareNoCase(_T("TRUE"))==0 || strEnabled.CompareNoCase(_T("1"))==0)
						{
							
							if(strBitMask.IsEmpty())
								strBitMask="1";
							else
                                strBitMask=strBitMask+_T(",")+_T("1");
						}
						else
						{
							if(strBitMask.IsEmpty())
								strBitMask="0";
							else
                                strBitMask=strBitMask+_T(",")+_T("0");
						}
					}
                    mapNodeDetails.push_back(make_pair("ListMask",strBitMask));
					mapNodeDetails.push_back(make_pair(strAttrName,strAttrValue));
					
				}
				else
				{
					strAttrValue = m_pRFXML.GetNodeText(node3);
					mapNodeDetails.push_back(make_pair(strAttrName,strAttrValue));
				}

				

				}

		   }
		}
	    
	}
}

	 return true;

}

bool CSimRFCaltestUIApp::UpdateXMLloss(const CString & strXMLPath,CStringStringMap mapFreqToLoss,const CString & strTYPE,int bIsUplink)
{
  
	CString strMsg;
	CString strTemp;
	CString strType;
	CString strUpDownLink;
	XMLNode node;
	XMLNode nodeItem;
	XMLNodeList nodeList;
	CStringStringMapItr itrMap;
	bool bFindType=false;
	bool bFindUpDownLink=false;
	CString strName;
    m_pLossXML.Load("");// not know why now 

    if(m_pLossXML.Load(strXMLPath)!=0)
	{
        strMsg=strXMLPath+_T("   not exist");
		AfxMessageBox(strMsg);
		return false;
	}

    
	strType=strTYPE;
	
 


	if(bIsUplink)
		strUpDownLink="5";
	else
        strUpDownLink="4";



	CString strNodeName="//CalibrationData";
    node=m_pLossXML.SearchNode(strNodeName);
    nodeList=nodeList = m_pLossXML.GetChildNodes(node);

    int iSize=m_pLossXML.GetNodeListSize(nodeList);

	for(int m=0;m<iSize;++m)
	{
       node = m_pLossXML.GetNodeListItem(nodeList, m);

	  if (m_pLossXML.GetNodeType(node) != XMLNodeType_Element)
			continue;
      strName=m_pLossXML.GetNodeAttrValue(node, _T("name"));
	  if(strName==strType)
	  {
         bFindType=true;
		 break;
	  }

	}

	if(!bFindType)
	{
		strMsg=strType+_T("   not exist");
		AfxMessageBox(strMsg);
		return false;
	}

	nodeList = m_pLossXML.GetChildNodes(node);
	int iNodelistSize=m_pLossXML.GetNodeListSize(nodeList);
	    for(int i=0;i<iNodelistSize;++i)
	{
	     node = m_pLossXML.GetNodeListItem(nodeList, i);
 
		if (m_pLossXML.GetNodeType(node) != XMLNodeType_Element)
			continue;
		strName = m_pLossXML.GetNodeAttrValue(node, _T("number"));
		if(strName==strUpDownLink)
		{
		  
		
		   XMLNodeList nodeListItem = m_pLossXML.GetChildNodes(node);

		   int iNodeItemListSize=m_pLossXML.GetNodeListSize(nodeListItem);

		   if(bIsUplink)
		   {
				if(m_bIsFirstUpdateXMlLossUL) //clear nodes
			   {
				  
					for(int j=iNodeItemListSize-1;j>=0;j--)
					{
						XMLNode XMLNodeDelete=m_pLossXML.GetNodeListItem(nodeListItem,j);
						CString strTemp=m_pLossXML.GetNodeName(XMLNodeDelete);
						CString strAttrTemp=m_pLossXML.GetNodeAttrValue(XMLNodeDelete,"freq");

					
						if(!m_pLossXML.DeleteNode(XMLNodeDelete))
							return false;
					}

					m_bIsFirstUpdateXMlLossUL=false;
					
	                
			   }
		   }
		   else
		   {
			   if(m_bIsFirstUpdateXMlLossDL) //clear nodes
			   {
				  
					for(int j=iNodeItemListSize-1;j>=0;j--)
					{
						XMLNode XMLNodeDelete=m_pLossXML.GetNodeListItem(nodeListItem,j);
						CString strTemp=m_pLossXML.GetNodeName(XMLNodeDelete);
						CString strAttrTemp=m_pLossXML.GetNodeAttrValue(XMLNodeDelete,"freq");

					
						if(!m_pLossXML.DeleteNode(XMLNodeDelete))
							return false;
					}

					m_bIsFirstUpdateXMlLossDL=false;
					
	                
			   }

		   }

            for(itrMap=mapFreqToLoss.begin();itrMap!=mapFreqToLoss.end();++itrMap)
		   {
			   CString strFreq=itrMap->first;
			   CString strLoss=itrMap->second;
			   XMLNode nodeCreated;
                strTemp.Format("CalPoint[@freq=\"%s\" and @loss=\"%s\"]",strFreq,strLoss);
				if(!m_pLossXML.CreateChildNode(node,strTemp,nodeCreated))
					return false;
			  
			}

		  /* for(itrMap=mapFreqToLoss.begin();itrMap!=mapFreqToLoss.end();++itrMap)
		   {
			   CString strFreq=itrMap->first;
			   CString strLoss=itrMap->second;

			   bool bFindFreq=false;
			   for(int j=0;j<iNodeItemListSize;j++)
			   {
				   XMLNode XMLNodeLoss=m_pLossXML.GetNodeListItem(nodeListItem,j);
				  if (m_pLossXML.GetNodeType(XMLNodeLoss) != XMLNodeType_Element)
				continue;
				  CString strFreqXML=m_pLossXML.GetNodeAttrValue(XMLNodeLoss,"freq");
				  if(strFreqXML==strFreq)
				  {
					  m_pLossXML.SetNodeAttrValue(XMLNodeLoss,"loss",strLoss);
					  bFindFreq=true;
					  break;

				  }
	                 
			   }

			   if(!bFindFreq)
			   {
				    strMsg=strFreq+_T("   not exist");
					AfxMessageBox(strMsg);
					return false;
			   }
		   }*/

           bFindUpDownLink=true;
		   break;
           
		}


       
	}

	if(!bFindUpDownLink)
	{
		strMsg=strUpDownLink+_T("   not exist");
		AfxMessageBox(strMsg);
		return false;
	}
	m_pLossXML.Save();
	return true;


}
bool CSimRFCaltestUIApp::UpdateXMLProcessList()
{
    if(!m_pRFXML.IsLoad())
	{
       AfxMessageBox("XML not load");
		return false;
	}
    CString strTemp;
	int iNameIndex=1;

	XMLNode node=m_pRFXML.SearchNode("//Configurations/MainObject/List");
    XMLNode nodeItem;
    XMLNodeList nodeList = m_pRFXML.GetChildNodes(node);
	int iNodelistSize=m_pRFXML.GetNodeListSize(nodeList);

	for (UINT i = 0; i <iNodelistSize; i++) 
	{
	    strTemp.Format("//Configurations/MainObject/List/Item");
		m_pRFXML.DeleteNode(strTemp);
	}

    

	 for(CStringItr itrProcessListEN=m_vProcessListEnable.begin();itrProcessListEN!=m_vProcessListEnable.end();++itrProcessListEN)
	 {
		 strTemp.Format("//Configurations/MainObject/List/Item[@Name=\"%s\" and @Enabled=\"True\"]",*itrProcessListEN);
		m_pRFXML.CreateNode(strTemp,nodeItem);
      

	 }

	m_pRFXML.Save();

 
	return true;

}
bool CSimRFCaltestUIApp::ParseObjectsFromXML(const CString & strNodePath,CCString2StringMap & vtrStringPairRef)
{
	if(!m_pRFXML.IsLoad())
	{
       AfxMessageBox("XML not load");
		return false;
	}
    XMLNode node=m_pRFXML.SearchNode(strNodePath);
    XMLNodeList nodeList = m_pRFXML.GetChildNodes(node);
    
   for (UINT i = 0; i < m_pRFXML.GetNodeListSize(nodeList); i++)
   {
		XMLNode node = m_pRFXML.GetNodeListItem(nodeList, i);
 
		if (m_pRFXML.GetNodeType(node) != XMLNodeType_Element)
			continue;
		CString strClsName = m_pRFXML.GetNodeAttrValue(node, _T("ClassName"));
		CString strName = m_pRFXML.GetNodeAttrValue(node, _T("Name"));

	
		CStringStringMap mapAttrList;
  
		mapAttrList.insert(make_pair(_T("Name"),strName));
 
		XMLNodeList nodeChildList = m_pRFXML.GetChildNodes(node);
		for (UINT j = 0; j < m_pRFXML.GetNodeListSize(nodeChildList); j++) {
			XMLNode nodeAttr = m_pRFXML.GetNodeListItem(nodeChildList, j);
 
			if (m_pRFXML.GetNodeType(nodeAttr) != XMLNodeType_Element)
				continue;
           
			CString strAttrName = m_pRFXML.GetNodeName(nodeAttr);
			CString strAttrValue;
 
			if (strAttrName == _T("List")) {
				// Get node items of Enabled=True
				XMLNodeList nodeItemList = m_pRFXML.GetChildNodes(nodeAttr);
 
				for (UINT k = 0; k < m_pRFXML.GetNodeListSize(nodeItemList); k++) {
					XMLNode nodeItem = m_pRFXML.GetNodeListItem(nodeItemList, k);
					CString strEnabled = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Enabled"));
 
					if (strEnabled.CompareNoCase(_T("TRUE"))==0 || strEnabled.CompareNoCase(_T("1"))==0)
					{
						CString nodeItemName = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Name"));
 
						if (strAttrValue.IsEmpty())
							strAttrValue = nodeItemName;
						else
							strAttrValue = strAttrValue + _T(",") + nodeItemName;
					}
				}
			}
			else
				strAttrValue = m_pRFXML.GetNodeText(nodeAttr);
 
		
			mapAttrList.insert(make_pair(strAttrName,strAttrValue));
		}
 
		vtrStringPairRef.push_back(make_pair(strClsName, mapAttrList));
	}

 return true;

}
bool  CSimRFCaltestUIApp::LoadConfigDataFromXML(CString strXMLFile)
{
    
    m_pRFXML.Load("");// not know why now 
    	m_vProcessList.clear();
	m_vProcessList.clear();
    if(m_pRFXML.Load(strXMLFile)!=0)
	{
       CString strTemp=strXMLFile+_T("   not exist");
		AfxMessageBox(strTemp);
		return false;
	}
	m_vProcessListEnable.clear();
	m_vProcessList.clear();
	m_pConfigSetting->m_MapMainSetting.clear();
	m_pConfigSetting->m_MapPairPreConfig.clear();
	m_pConfigSetting->m_MapConfigSetting.clear();
	// Parse MainSetting
	XMLNode node=m_pRFXML.SearchNode("//Configurations/MainObject");
    XMLNodeList nodeList = m_pRFXML.GetChildNodes(node);

	for (UINT i = 0; i < m_pRFXML.GetNodeListSize(nodeList); i++) 
	{
		XMLNode node = m_pRFXML.GetNodeListItem(nodeList, i);
 
		if (m_pRFXML.GetNodeType(node) != XMLNodeType_Element)
			continue;
 
		CString strName = m_pRFXML.GetNodeName(node);
		
		if (strName == _T("List")) 
		{ 
			XMLNodeList nodeItemList = m_pRFXML.GetChildNodes(node);
			CString strEnabledItems;
			CString strRunListFaillong;
			for (UINT j = 0; j < m_pRFXML.GetNodeListSize(nodeItemList); j++) 
			{
				XMLNode nodeItem = m_pRFXML.GetNodeListItem(nodeItemList, j);
               CString nodeItemName = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Name"));
				//m_vProcessList.push_back(nodeItemName);
				CString strEnabled = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Enabled"));
				CString strRunListFail = m_pRFXML.GetNodeAttrValue(nodeItem, _T("RunListFail"));
				if(strRunListFail=="")
					strRunListFail="NA";
                
				if ((strEnabled.CompareNoCase(_T("TRUE")) == 0) || (strEnabled.CompareNoCase(_T("1")) == 0) )
				{
					 
					m_vProcessListEnable.push_back(nodeItemName);

					if(strRunListFaillong.IsEmpty())
                        strRunListFaillong=strRunListFail;
					else
						strRunListFaillong=strRunListFaillong+"$"+strRunListFail;

					if (strEnabledItems.IsEmpty())
						strEnabledItems = nodeItemName;
					else
						strEnabledItems = strEnabledItems + _T(",") + nodeItemName;
				}
			}
 

			m_pConfigSetting->m_MapMainSetting.insert(make_pair("List",strEnabledItems));
			m_pConfigSetting->m_MapMainSetting.insert(make_pair("RunListFail",strRunListFaillong));
		}

		else if(strName == _T("ALLItems")) 
		{
           XMLNodeList nodeItemList = m_pRFXML.GetChildNodes(node);
			
			for (UINT j = 0; j < m_pRFXML.GetNodeListSize(nodeItemList); j++)
			{
				XMLNode nodeItem = m_pRFXML.GetNodeListItem(nodeItemList, j);
               CString nodeItemName = m_pRFXML.GetNodeAttrValue(nodeItem, _T("Name"));
				m_vProcessList.push_back(nodeItemName);
				
			}
 
		}
	
		else {
			CString strValue = m_pRFXML.GetNodeText(node);
			m_pConfigSetting->m_MapMainSetting.insert(make_pair(strName,strValue));		
                                                                            
		}
	}
    CString strPath = _T("//Configurations/ProcessObjectSet");
	CString strEnablePath=_T("//Configurations/MainObject/List");
	nodeList = m_pRFXML.GetChildNodes(strPath);
	for (UINT i = 0; i < m_pRFXML.GetNodeListSize(nodeList); i++) 
	{
		XMLNode node = m_pRFXML.GetNodeListItem(nodeList, i);
		CString strNodeName = m_pRFXML.GetNodeName(node);
	if(!ParseObjectsFromXML_CheckEnable(strPath+_T("//")+strNodeName, strEnablePath,m_pConfigSetting->m_MapConfigSetting))
	   {
		 return false;
	   }
	}

     strPath = _T("//Configurations/PreObjects");

	if(!ParseObjectsFromXML(strPath, m_pConfigSetting->m_MapPairPreConfig))
	   {
		 return false;
	   }
	
    
	return true;
}
bool CSimRFCaltestUIApp::InSertRecord(const CString & strTable,const CString & strItemName,const CString & strItemValue)
{
  
	

   if(m_bIsDataBase)
	{
		char szErrMsg[1024];
		
         bool bRet;
		char szTable[256];
        char szItemName[256];
 
        char szItemValue[256];
		sprintf(szTable,"%s",strTable);
		sprintf(szItemName,"%s",strItemName);
		sprintf(szItemValue,"%s",strItemValue);
	
		bRet=m_pFuncInsertRecord(szTable,szItemName,szItemValue);

		if(!bRet)
		{
		    if(m_pFuncGetLastErrorMsg(szErrMsg,1024))
				{
					AfxMessageBox(szErrMsg);
				}
				else
				{
				   AfxMessageBox("Query  Fail,but error message not show for not enough room");
				}
			
			return false;

		}
	}


  return true;
}
bool CSimRFCaltestUIApp::UpdateSingRecord(const CString & strTable,const CString & strItemName,const CString & strItemValue,const CString & strKeyName,const CString & strKeyValue)
{


	if(m_bIsDataBase)
	{
		char szErrMsg[1024];
		char szTable[256];
        char szItemName[256];
		char szItemValue[256];
        char szKeyName[256];
        char szKeyValue[256];
		sprintf(szTable,"%s",strTable);
		sprintf(szItemName,"%s",strItemName);
		sprintf(szItemValue,"%s",strItemValue);
		sprintf(szKeyName,"%s",strKeyName);
		sprintf(szKeyValue,"%s",strKeyValue);
		if(!m_pFuncUpdateSingRecord(szTable,szItemName,szItemValue,szKeyName,szKeyValue))

		{

		   if(m_pFuncGetLastErrorMsg(szErrMsg,1024))
				{
					AfxMessageBox(szErrMsg);
				}
				else
				{
				    AfxMessageBox("Query  Fail,but error message not show for not enough room");
				}
			
			return false;

		}
		
	}

	
	return true;
}
int CSimRFCaltestUIApp::QuerySingRecord(const CString & strTable,const CString & strItemName,const CString & strKeyName,const CString & strKeyValue,CString & strItemValue,const CString & strOrderName,int iIsAsc)
{
    
	if(m_bIsDataBase)
	{
		char szErrMsg[1024];
		int iRetResult;

        char szReturnValue[256];
		char szTable[256];
        char szItemName[256];
        char szKeyName[256];
        char szKeyValue[256];
		char szOrderName[256];
		sprintf(szTable,"%s",strTable);
		sprintf(szItemName,"%s",strItemName);
		sprintf(szKeyName,"%s",strKeyName);
		sprintf(szKeyValue,"%s",strKeyValue);
		sprintf(szOrderName,"%s",strOrderName);
		iRetResult=m_pFuncQuerySingRecord(szTable,szItemName,szKeyName,szKeyValue,szReturnValue,szOrderName,iIsAsc);

		if(iRetResult!=0 && iRetResult!=2)
		{

		    if(m_pFuncGetLastErrorMsg(szErrMsg,1024))
				{
					AfxMessageBox(szErrMsg);
				}
				else
				{
				    AfxMessageBox("Query  Fail,but error message not show for not enough room");
				}
			

		}

		strItemValue=szReturnValue;
		return iRetResult;
	}

   
	return 0;
}
void CSimRFCaltestUIApp::ExitDataBase()
{

	if(m_pFuncCloseDataBase)
       m_pFuncCloseDataBase();
	if(m_hDataBaseDll!=NULL)
	{
		::FreeLibrary(m_hDataBaseDll);
        m_hDataBaseDll=NULL;
	}
}
bool CSimRFCaltestUIApp::InitDataBase(const CString & strDllPath)
{


	//m_hDataBaseDll=::LoadLibrary(strDllPath);
    m_hDataBaseDll=::LoadLibrary(strDllPath);
	if(m_hDataBaseDll==0)
	{
		AfxMessageBox("Load DataBase.dll fail!",MB_OK,0);
		return false;
	}
   m_pFuncOpenDatabase=(pFuncOpenDataBase)GetProcAddress(m_hDataBaseDll,"OpenDataBase");
   if(m_pFuncOpenDatabase==NULL)
   { 
        
		AfxMessageBox("Load OpenDataBase fail!",MB_OK,0);
		return false;
   }

   m_pFuncCloseDataBase=(pFuncCloseDataBase)GetProcAddress(m_hDataBaseDll,"CloseDataBase");

    if(m_pFuncCloseDataBase==NULL)
   { 
       
	   AfxMessageBox("Load CloseDataBase fail!",MB_OK,0);
		return false;
   }

   m_pFuncGetLastErrorMsg=(pFuncGetLastErrorMsg)GetProcAddress(m_hDataBaseDll,"GetLastErrorMsg");

   if(m_pFuncGetLastErrorMsg==NULL)
   { 
       
	   AfxMessageBox("Load GetLastErrorMsg fail!",MB_OK,0);
		return false;
   }

     
  

    m_pFuncInsertRecord=(pFuncInsertRecord)GetProcAddress(m_hDataBaseDll,"InsertRecord");

   if(m_pFuncInsertRecord==NULL)
   { 
       
	   AfxMessageBox("Load InsertRecord fail!",MB_OK,0);
		return false;
   }
  ;

    m_pFuncUpdateSingRecord=(pFuncUpdateSingRecord)GetProcAddress(m_hDataBaseDll,"UpdateRecord");

   if(m_pFuncUpdateSingRecord==NULL)
   { 
       
	   AfxMessageBox("Load UpdateRecord fail!",MB_OK,0);
		return false;
   }

    m_pFuncQuerySingRecord=(pFuncQuerySingRecord)GetProcAddress(m_hDataBaseDll,"QuerySingRecord");

   if(m_pFuncQuerySingRecord==NULL)
   { 
       
	   AfxMessageBox("Load QuerySingRecord fail!",MB_OK,0);
		return false;
   }



	
  return true;
}
int CSimRFCaltestUIApp::ExitInstance()
{
	if(m_pConfigSetting)
	{
		delete m_pConfigSetting;
		m_pConfigSetting=NULL;
	}
    if(m_hCalTestThread)
	{
			 
			 DWORD dwWaitTime=2000;
			 
			if (::WaitForSingleObject(m_hCalTestThread, dwWaitTime) != WAIT_OBJECT_0)
		{
			   TerminateThread(m_hCalTestThread,1); 
			  
		}
			 DWORD dwExitCode;
			GetExitCodeThread(m_hCalTestThread, &dwExitCode);
		    if(dwExitCode!=0)
			{
				AfxMessageBox("CalTest Process not success!");
			}

			if(m_pRFCalTestProcessor)
		   {
			 
			   m_pRFCalTestProcessor->Free();
			   m_pRFCalTestProcessor=NULL;
			
		   }
		   if(m_hRFCalTestDLL)
		   {
			   FreeLibrary(m_hRFCalTestDLL);
			   m_hRFCalTestDLL=NULL;
		   }

      if(m_bIsDataBase)
      ExitDataBase();
	}
   
	return CWinApp::ExitInstance();
}
