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
	//��Ҫ���ݵ���Ϣ;
	CString strStation;
	CString strBarcode;
	CString strImei;
	CString strImei2;
	CString strMeid;
	CString strEsn;
	CString strWifi;
	CString strBtaddr;
	CString strFixture;//��Ҫ�����ļ�
	CString strErrorCode;
	CString strLine;//��Ҫ�����ļ�
	CString strCreator;//��Ҫ�����ļ�
	CString strSW;//��Ҫ�����ļ�
	CString strPN;//��Ҫ�����ļ�
	CString strRetVal;
	int IsPass;
public:
	//�����ַ���
	CString strServer;
	CString strDatabase;
	CString strUser;
	CString strPasswd;
};