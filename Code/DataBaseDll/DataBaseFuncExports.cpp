#include "stdafx.h"
#include "DataBaseFuncExports.h"
#include "DataBase.h"

CMyDataBase dbOp;

DB_FUNC_API bool OpenDataBase(char* szDSN,char* szUser,char* szPwd)
{

	CString strDSN=szDSN;
	CString strUser=szUser;
	CString strPwd=szPwd;
   

	if(!dbOp.OpenDataBase(strDSN,strUser,strPwd))
		return false;
	return true;
}


DB_FUNC_API bool CloseDataBase()
{

	if(!dbOp.CloseDataBase())
     return false;
	return true;
}

DB_FUNC_API bool GetLastErrorMsg(char* szMsg,int iBufferLen)
{
    
	CString strMsg;
	dbOp.GetLastErrorMsg(strMsg);
	if(iBufferLen<strMsg.GetLength())
		return false;

	sprintf(szMsg,"%s",strMsg);
	return true;
}

DB_FUNC_API  bool InsertRecord(char* szTable,char* szItemName,char* szItemValue)
{
	CString strTable=szTable;
	CString strItemName=szItemName;
	CString strItemValue=szItemValue;
	if(!dbOp.InsertRecord(strTable,strItemName,strItemValue))
		return false;
	return true;
}

DB_FUNC_API  bool UpdateRecord(char* szTable,char* szItemName,char* szItemValue,char* szKeyName,char* szKeyValue)
{
	CString strTable=szTable;
	CString strItemName=szItemName;
	CString strItemValue=szItemValue;
	CString strKeyName=szKeyName;
	CString strKeyValue=szKeyValue;

	if(!dbOp.UpdateSingRecord(strTable,strItemName,strItemValue,strKeyName,strKeyValue))
	return false;

	return true;
}

DB_FUNC_API  int QuerySingRecord(char* szTable,char* szItemName,char* szKeyName,char* szKeyValue,char* szReturnValue,char* OrderKeyName,int iIsAsc)
{

	
	CString strTable=szTable;
	CString strItemName=szItemName;

	CString strKeyName=szKeyName;
	CString strKeyValue=szKeyValue;

	CString strReturnValue;

	int iRet;
	iRet=dbOp.QuerySingRecord(strTable,strItemName,strKeyName,strKeyValue,strReturnValue,OrderKeyName,iIsAsc);

	if(iRet==0)
		strcpy(szReturnValue,strReturnValue);
		return iRet;
    


}
