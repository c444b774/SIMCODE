#include <afxdb.h>   

#ifdef DATABASE_CLASS_EXPORTS

#define DB_CLASS_API __declspec(dllexport)
#else
#define DB_CLASS_API __declspec(dllimport)
#endif



class  DB_CLASS_API CMyDataBase {
public:
	CMyDataBase(void);
    virtual ~CMyDataBase();

	bool OpenDataBase(const CString & strDSN,const CString & strUser,const CString & strPWD);
	bool CloseDataBase();
	
    bool InsertRecord(const CString & strTableName,const CString & strItemName,const CString & strItemValue);
	bool UpdateSingRecord(const CString & strTableName,const CString & strItemName,const CString & strItemValue,const CString & strKeyItemName,const CString & strKeyItemValue);
    int QuerySingRecord(const CString & strTableName,const CString & strItemName,const CString & strKeyItemName,const CString & strKeyItemValue,CString & strReturnValue,const CString & strOrderName,int iIsAsc);
	
	void GetLastErrorMsg(CString & strErrorMsg);
private:
	CDatabase m_db;
	bool      m_bIsOpen;
	CString m_strErrorMsg;


};


