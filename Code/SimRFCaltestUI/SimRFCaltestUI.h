// SimRFCaltestUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include  "inc\commoninclude.h"
#include "SimpleCriticalSection.h"
#include  <io.h>
#include "shlwapi.h"
#include  "inc\IRFCalTestDLL.h"
#include  "MyMSXML.h"
#include  "inc\DataBaseFuncExports.h"
// CSimRFCaltestUIApp:
// See SimRFCaltestUI.cpp for the implementation of this class


static LPCTSTR MODULENAME = _T("CTTool");
static LPCTSTR DEFAULT_TOOLLOG_FILENAME = _T("CalTestToolLog.csv");
//
void ToolTraceLog(LPCTSTR lpszModule, LPCSTR lpszSrcFile, UINT iSrcLine, EMsgLevel msgLevel, LPCTSTR lpszMsgFormat, ...);
void ToolFactoryLog(INT iProcessCode, LPCTSTR lpszBand, LPCTSTR lpszChannel, INT iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit, BOOL bPass, LPCTSTR lpszMsgFormat, ...);
void ToolFactoryLogEx(INT iProcessCode, LPCTSTR lpszBand, LPCTSTR lpszChannel, INT iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit, BOOL bPass,LPCTSTR lpszItemName, LPCTSTR lpszMsgFormat, ...);
void ToolCommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage);
void ToolDefaultLog(LPCTSTR lpszModule, LPCSTR lpszSrcFile, UINT iSrcLine, LPCTSTR lpszMsgFormat, ...);

// Utility
BOOL ForceCreateDirectory(LPCTSTR lpszDirPath);
 
// append the source file to the destination file
BOOL AppendFiles(LPCTSTR lpszDstFilePath, LPCTSTR lpszSrcFilePath);
 
class CSimRFCaltestUIApp : public CWinApp
{
public:
	CSimRFCaltestUIApp();

// Overrides
public:
	virtual BOOL InitInstance();
	void UpdateLogFilePath(BOOL bCreateFile=TRUE);
    
	void UpdateTraceLogFilePath(BOOL bCreateFile=TRUE);
	void UpdateFactoryLogFilePath(BOOL bCreateFile=TRUE);
	void UpdateCommandLogFilePath(BOOL bCreateFile=TRUE);
    
    void CreateFactoryLogFileAndCreateDir(LPCTSTR lpszLogFilePath);
	void CreateCommandLogFileAndCreateDir(LPCTSTR lpszLogFilePath);
	void ChangeFactoryLogFilePath(LPCTSTR lpszLogFilePath);
	void ChangeCommandLogFilePath(LPCTSTR lpszLogFilePath);

    //bool LoadConfigDataFromIni(CString strIniFile);
	bool LoadConfigDataFromXML(CString strXMLFile);
	bool LoadCableLossFromIni();
	bool ParseSystemIni();
	bool ParseSFINI();
	bool ParseDBINI();
	bool ConvertToVector(_TCHAR* tCharSrc,vector<CString> & vtrOut);
	bool CheckLossUIShow();
	bool ReleaseResource();

	bool UpdateXMLProcessList();
	bool UpdateXMLloss(const CString & strXMLPath,CStringStringMap mapFreqToLoss,const CString & strTYPE,int bIsUplink=1);
    bool GetMapFromNodeName(const CString & strNodeName,const CString & strNodePath,CStringPairVtr & mapNodeDetails,bool bIsInChildNode=true);
	bool ParseObjectsFromXML(const CString & strNodePath,CCString2StringMap & vtrStringPairRef);
    bool ParseObjectsFromXML_CheckEnable(const CString & strNodePath,const CString & strCheckEnablePath,CCString2StringMap & vtrStringPairRef);
    bool UpdateXMlProcessProject(const CString & strNodeName,const CString & strNodePath,CStringStringMap mapNodeDetails,bool bIsInChildNode=true);
	void MainPageLoadIniUpdateUI();

	//Operation for database

	bool InitDataBase(const CString & strDllPath);
	void ExitDataBase();

	//DataBase Operations

	bool InSertRecord(const CString & strTable,const CString & strItemName,const CString & strItemValue);
    bool UpdateSingRecord(const CString & strTable,const CString & strItemName,const CString & strItemValue,const CString & strKeyName,const CString & strKeyValue);
	int  QuerySingRecord(const CString & strTable,const CString & strItemName,const CString & strKeyName,const CString & strKeyValue,CString & strItemValue,const CString & strOrderName="",int iIsAsc=1);
public:
  CString m_strIniPath;
   CString m_LogPath;
 PCConfigSetting m_pConfigSetting;
 CString m_strSN;

 int m_iKeyID;

 CString strstationName;
 CString strProjectName;
 CString m_strToolVer;
 CMyMSXML m_pRFXML;
 CMyMSXML m_pLossXML;

 CStringVtr m_vProcessList;
 CStringVtr m_vProcessListEnable;


 CWnd* m_pMainPage;
 CWnd* m_pBaseConfigPage;
 CWnd* m_pLossConfigPage;

 bool m_bIsPass;
 bool m_bIsDOSF;
 bool m_bIsDataBase;
 bool m_bIsFirstUpdateXMlLossUL;
 bool m_bIsFirstUpdateXMlLossDL;
 
 bool m_bStopWhenFail;
 bool m_bIsHasFailItem;
 bool m_bIsrunning;
 bool m_bRunAfterSN;
 int  m_bEnableTraceLog;
 int  m_iLoopCount;

  FILE* m_pFactoryLog;
  FILE* m_pCommandLog;
  CString m_strFactoryLogFilePath;
  CString m_strCommandLogFilePath;
  HMODULE m_hRFCalTestDLL;
  HMODULE m_hDataBaseDll;
  PIRFCalTestDLL m_pRFCalTestProcessor;
 

  	 CWinThread *m_pCalTestWinThread;
	 HANDLE m_hCalTestThread;

	 //DataBase Export functions


  pFuncOpenDataBase m_pFuncOpenDatabase;
  pFuncCloseDataBase m_pFuncCloseDataBase;
  pFuncGetLastErrorMsg m_pFuncGetLastErrorMsg;
  pFuncInsertRecord m_pFuncInsertRecord;
  pFuncUpdateSingRecord m_pFuncUpdateSingRecord;
  pFuncQuerySingRecord  m_pFuncQuerySingRecord;



private:
     
     
// Implementation

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CSimRFCaltestUIApp theApp;