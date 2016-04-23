#include "stdafx.h"
#include "DBHelper.h"

typedef char* (__stdcall* CheckSNRouting)(char* ServerConn,char* Station,char* SerialCode) ;      //(char* Username,char* password,TUser *tu);  
typedef char* (__stdcall* UpdateSNRouting)(char* ServerConn,char* Station,char* FixtureCode,char* ErrorCode,char* Line,char* SerialCode,char* Creator,int IsPass); 
typedef char* (__stdcall* CheckIMEIRouting)(char* ServerConn,char* Station,char* SerialCode,char* IMEI,char* IMEI2,char* MEID,char* ESN,char* WIFINO,char* BTADDR);
typedef char* (__stdcall* UpdateIMEIRouting)(char* ServerConn,char* Station,char* ErrorCode,char* Line,char* SerialCode,char* IMEI,char* IMEI2,char* MEID,char* ESN,char* WIFINO,char* BTADDR,char* Creator,char* SW,char* PN,int IsPass);

//¶¨Òå
CheckSNRouting m_CheckSNRouting;
UpdateSNRouting m_UpdateSNRouting;
CheckIMEIRouting m_CheckIMEIRouting;
UpdateIMEIRouting m_UpdateIMEIRouting;

CDBHelper::CDBHelper(void)
{
}

CDBHelper::~CDBHelper(void)
{
}

BOOL CDBHelper::DBHelper_Library_DynamicLoad(void)
{
	HINSTANCE hinstLib = LoadLibrary(_T("DBHelper.dll"));	
	if (hinstLib == NULL)
		return FALSE;
	else
	{
		m_CheckSNRouting = (CheckSNRouting)GetProcAddress(hinstLib, "CheckSNRouting");  
		m_UpdateSNRouting = (UpdateSNRouting)GetProcAddress(hinstLib, "UpdateSNRouting");
		m_CheckIMEIRouting = (CheckIMEIRouting)GetProcAddress(hinstLib, "CheckIMEIRouting");
		m_UpdateIMEIRouting = (UpdateIMEIRouting)GetProcAddress(hinstLib, "UpdateIMEIRouting");
	}

	this->ComposeSFC_Character(this->strSFC_ServerConn);
	return TRUE;
}

BOOL CDBHelper::DB_UpdateSNRouting()//char *strStation,char *strSerialCode,char* strFixture,char* strErrorCode,char* strLine,char* strCreator,int IsPass
{
	char retVal[64];

	memset(retVal,0,64);

	try
	{
		strcpy(retVal,m_UpdateSNRouting(
			this->strSFC_ServerConn.GetBuffer(this->strSFC_ServerConn.GetLength()),
			this->strStation.GetBuffer(this->strStation.GetLength()),
			this->strFixture.GetBuffer(this->strFixture.GetLength()),
			this->strErrorCode.GetBuffer(this->strErrorCode.GetLength()),
			this->strLine.GetBuffer(this->strLine.GetLength()),
			this->strBarcode.GetBuffer(this->strBarcode.GetLength()),
			this->strCreator.GetBuffer(this->strCreator.GetLength()),
			this->IsPass)
			);

		if(NULL == strstr("OK",retVal))
		{
			this->strRetVal.Format("%s",retVal);
			throw(0);
		}
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
	
}

BOOL CDBHelper::DB_CheckSNRouting()
{
	char retVal[64];

	memset(retVal,0,64);

	try
	{
		strcpy(retVal,m_CheckSNRouting(this->strSFC_ServerConn.GetBuffer(this->strSFC_ServerConn.GetLength()),(LPSTR)(LPCTSTR)this->strStation,(LPSTR)(LPCTSTR)this->strBarcode));
		if(NULL == strstr("OK",retVal))
		{
			this->strRetVal.Format("%s",retVal);
			throw(0);
		}
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
	
}

void CDBHelper::ComposeSFC_Character(CString &str)
{
	str.Format("Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%s;Data Source=%s",this->strPasswd,this->strUser,this->strDatabase,this->strServer);//CSATS
}

BOOL CDBHelper::DB_CheckIMEIRouting()
{
	char retVal[64];
	
	memset(retVal,0,64);
	
	try
	{
		strcpy(retVal,m_CheckIMEIRouting(this->strSFC_ServerConn.GetBuffer(0),
			(LPSTR)(LPCTSTR)this->strStation,
			(LPSTR)(LPCTSTR)this->strBarcode,
			(LPSTR)(LPCTSTR)this->strImei,
			(LPSTR)(LPCTSTR)this->strImei2,
			(LPSTR)(LPCTSTR)this->strMeid,
			(LPSTR)(LPCTSTR)this->strEsn,
			(LPSTR)(LPCTSTR)this->strWifi,
			(LPSTR)(LPCTSTR)this->strBtaddr));
		if(NULL == strstr("OK",retVal))
		{
			this->strRetVal.Format("%s",retVal);
			throw(0);
		}
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CDBHelper::DB_UpdateIMEIRouting()
{
	char retVal[64];
	
	memset(retVal,0,64);

	try
	{
		strcpy(retVal,m_UpdateIMEIRouting(
			this->strSFC_ServerConn.GetBuffer(0),
			this->strStation.GetBuffer(0),
			this->strErrorCode.GetBuffer(0),
			this->strLine.GetBuffer(0),
			this->strBarcode.GetBuffer(0),
			this->strImei.GetBuffer(0),
			this->strImei2.GetBuffer(0),
			this->strMeid.GetBuffer(0),
			this->strEsn.GetBuffer(0),
			this->strWifi.GetBuffer(0),
			this->strBtaddr.GetBuffer(0),
			this->strCreator.GetBuffer(0),
			this->strSW.GetBuffer(0),
			this->strPN.GetBuffer(0),
			this->IsPass)
			);
		
		if(NULL == strstr("OK",retVal))
		{
			this->strRetVal.Format("%s",retVal);
			throw(0);
		}
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}
