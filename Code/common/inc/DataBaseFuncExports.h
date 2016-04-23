#ifdef DATABASE_FUNC_EXPORTS

#define DB_FUNC_API extern "C" __declspec(dllexport)
#else
#define DB_FUNC_API extern "C" __declspec(dllimport)
#endif

typedef bool (*pFuncOpenDataBase)(char*,char*,char*);
DB_FUNC_API bool OpenDataBase(char* szDSN,char* szUser,char* szPwd);

typedef bool (*pFuncCloseDataBase)();
DB_FUNC_API bool CloseDataBase();

typedef bool (*pFuncGetLastErrorMsg)(char*,int);
DB_FUNC_API  bool GetLastErrorMsg(char* szMsg,int iBufferLen);


typedef bool (*pFuncInsertRecord)(char*,char*,char*);
DB_FUNC_API  bool InsertRecord(char* szTable,char* szItemName,char* szItemValue);

typedef bool (*pFuncUpdateSingRecord)(char*,char*,char*,char*,char*);
DB_FUNC_API  bool UpdateRecord(char* szTable,char* szItemName,char* szItemValue,char* szKeyName,char* szKeyValue);

//return value: 1 -> Database not opened    2-> no record  3 -> default error   0->success   

typedef int (*pFuncQuerySingRecord)(char*,char*,char*,char*,char*,char*,int);
DB_FUNC_API  int QuerySingRecord(char* szTable,char* szItemName,char* szKeyName,char* szKeyValue,char* szReturnValue,char* OrderKeyName,int iIsAsc);
