// DataBase.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "DataBase.h"

CMyDataBase::CMyDataBase()
{
   m_bIsOpen=false;
   m_strErrorMsg="";

}


CMyDataBase::~CMyDataBase()
{
	if(m_bIsOpen)
	{
         m_db.Close();
		m_bIsOpen = FALSE;
		m_strErrorMsg="";
	}

}
bool CMyDataBase::CloseDataBase()
{

    if(m_bIsOpen)
	{
		m_db.Close();
		m_bIsOpen = FALSE;
		m_strErrorMsg="";
	}

  return true;

}
void CMyDataBase::GetLastErrorMsg(CString & strErrorMsg)
{
    strErrorMsg=m_strErrorMsg; 
}
bool CMyDataBase::OpenDataBase(const CString & strDSN,const CString & strUser,const CString & strPWD)
{
       CString strql;
		strql.Format("DSN=%s;UID=%s;PWD=%s;READONLY=FALSE;",strDSN,strUser,strPWD);
	
		
  if(!m_bIsOpen)
  {
       if(!m_db.OpenEx(strql) )
		{
            m_strErrorMsg="Open Data Base Fail";
			m_bIsOpen = FALSE;
			return FALSE;
		}
  }

  if(!m_db.IsOpen())
  {
       m_strErrorMsg="Open Data Base Success,but DataBase not Open correctly";
			m_bIsOpen = FALSE;
			return FALSE;
  }
  m_bIsOpen=true;
  return true;
}

bool CMyDataBase::InsertRecord(const CString & strTableName,const CString & strItemName,const CString & strItemValue)
{

	if(!m_bIsOpen)
  
	{
		m_strErrorMsg="Data Base not opened!";



			return FALSE;
	}

	 CString strql;
		strql.Format("Insert into %s (%s) values('%s')",strTableName,strItemName,strItemValue);
	

		try
	{
		m_db.ExecuteSQL(strql);
	}
	catch(CException* e)
	{
		TCHAR message[200];
		e->GetErrorMessage(message,200);
		m_strErrorMsg=message;
		e->Delete();
		return FALSE;
	}
    return true;
}
 int CMyDataBase::QuerySingRecord(const CString & strTableName,const CString & strItemName,const CString & strKeyItemName,const CString & strKeyItemValue,CString & strReturnValue,const CString & strOrderName,int iIsAsc)
 {
     if(!m_bIsOpen)
  
	{
		m_strErrorMsg="Data Base not opened!";
	
			return 1;
	}

	 CString strql;
	 CRecordset rs(&m_db);
	 if(iIsAsc)
		strql.Format("select %s from %s where %s = '%s'",strItemName,strTableName,strKeyItemName,strKeyItemValue);
	 else
        strql.Format("select %s from %s where %s = '%s' order by %s desc",strItemName,strTableName,strKeyItemName,strKeyItemValue,strOrderName);

	

	try
	{
		rs.Open(CRecordset::forwardOnly, strql, CRecordset::readOnly);
		if(!rs.IsEOF())
		{
			
			rs.GetFieldValue(strItemName,strReturnValue);
	
			
		}
		else
		{
            m_strErrorMsg.Format("Can not find %s from selected record",strItemName);
			return 2;
		}
		rs.Close();
		
	}
	catch(CException* e)
	{
		TCHAR message[200];
		e->GetErrorMessage(message,200);
		m_strErrorMsg=message;
		e->Delete();
		return 3;
	}
    return 0; 
 }

bool CMyDataBase::UpdateSingRecord(const CString & strTableName,const CString & strItemName,const CString & strItemValue,const CString & strKeyItemName,const CString & strKeyItemValue)
{
   if(!m_bIsOpen)
  
	{
		m_strErrorMsg="Data Base not opened!";
	
			return FALSE;
	}

	/* CString strql;
		strql.Format("Update %s set %s='%s' where %s='%s'",strTableName,strItemName,strItemValue,strKeyItemName,strKeyItemValue);*/
     CString strql;
		strql.Format("Update %s set %s='%s' where %s=",strTableName,strItemName,strItemValue,strKeyItemName);
       strql+=strKeyItemValue;
	

		try
	{
		m_db.ExecuteSQL(strql);
	}
	catch(CException* e)
	{
		TCHAR message[200];
		e->GetErrorMessage(message,200);
		m_strErrorMsg=message;
		e->Delete();
		return FALSE;
	}
    return true;
}



