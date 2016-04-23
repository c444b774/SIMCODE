#pragma once

class CDBHelper
{
public:
	CDBHelper(void);
	~CDBHelper(void);

	BOOL DBHelper_Library_DynamicLoad(void);
	BOOL DB_CheckSNRouting(void);//char *strStation,char *strSerialCode
	BOOL DB_UpdateSNRouting(void);//char *strStation,char *strSerialCode,char* strFixture,char* strErrorCode,char* strLine,char* strCreator,int IsPass
	BOOL DB_CheckIMEIRouting();
	BOOL DB_UpdateIMEIRouting();

private:
	void ComposeSFC_Character(CString &str);

private:
	CString strSFC_ServerConn;
public:
	//需要传递的信息;
	CString strStation;
	CString strBarcode;
	CString strImei;
	CString strImei2;
	CString strMeid;
	CString strEsn;
	CString strWifi;
	CString strBtaddr;
	CString strFixture;//需要配置文件
	CString strErrorCode;
	CString strLine;//需要配置文件
	CString strCreator;//需要配置文件
	CString strSW;//需要配置文件
	CString strPN;//需要配置文件
	CString strRetVal;
	int IsPass;
public:
	//连接字符串
	CString strServer;
	CString strDatabase;
	CString strUser;
	CString strPasswd;
};