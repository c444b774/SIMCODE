#include "stdafx.h"
#include "CWCDMATestEnd.h"

RF_IMPLEMENT_DYNCREATE(CWCDMATestEnd)

CWCDMATestEnd::CWCDMATestEnd()
{
	m_mapClassFunc[_T("WCDMAEndCallMainFunc")]=&CWCDMATestEnd::CWCDMATestEndMainFunc;
	m_mapClassFunc[_T("WCDMAEndCall")]=&CWCDMATestEnd::CWCDMATestEndFunc;
}

CWCDMATestEnd::~CWCDMATestEnd()
{
	
}

bool CWCDMATestEnd::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CWCDMATestEnd::Handle()
{
	if(!DoProcess())
	{
		EndCall();
      return false;
	}
	EndCall();	
	return true;
}

bool CWCDMATestEnd::CWCDMATestEndMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CWCDMATestEnd::CWCDMATestEndFunc()
{
	int iErrorcode;
	CString strMsg;
	unsigned char NVItemValue[128]={0};

	if(m_bEnterOnline)
	{
		LogTrace(MSG_MID,_T(" Write NV 453=0 !"))
			if((iErrorcode=m_pPhone->WriteNV(453,NVItemValue,128))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("Phone Write NV :%d  Fail!",453);
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}

		
			LogTrace(MSG_MID,_T(" Write EFS !"))
				if((iErrorcode=m_pPhone->WriteEFS(30000))!=PHONE_SUCCESS)
				{
					LogTrace(MSG_ERROR,_T(" Phone WriteEFS Fail!"))
						m_iErrorcode=iErrorcode;
					CalFailLog(_T("_"),_T("_"),iErrorcode," Phone WriteEFS Fail!");
					return false;
				}
			
	}

	//m_pFuncWCDMATestDev->Deivce_Exit();

	//m_pPhone->CloseComport();

	TestPassLog(_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("EndCall Pass"));
  
     
	return true;
}

 bool CWCDMATestEnd::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
    CStringStringMapItr itrFind;
	CString strValue;
     CString strMainFun;
	 itrFind=pcSettingMap->find(_T("MainFunc"));
	 if(itrFind==pcSettingMap->end())
		 return false;
	 else
	 {
		 if(!SetMainFunc(itrFind->second))
			 return false;
	 }

	 CString strFuncList;
	 itrFind=pcSettingMap->find(_T("List"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,_T("Not Find List"));
		 return false;
	 }
	 strFuncList=itrFind->second;
     CStringVtr strVtr;

	 CStr::ParseString(strFuncList,_T(","),strVtr);
     CString strfunc;
	 m_vFPTestFunc.clear();
	 for(CStringItr itrFunc=strVtr.begin();itrFunc!=strVtr.end();++itrFunc)
	 {
		strfunc=*itrFunc;
		map<CString,FPClassFunc>::iterator itrMap=m_mapClassFunc.find(strfunc);
		if(itrMap==m_mapClassFunc.end())
			return false;
		m_vFPTestFunc.push_back(itrMap->second);
	 }
   
	 itrFind=pcSettingMap->find(_T("EnterOnline"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'EnterOnline' from ini file!.default is true");
		 m_bEnterOnline=true;
	 }
	 else
	 {
		 m_bEnterOnline=CStr::StrToBool(itrFind->second);
	 }

	
	  
	 InitData();
	 return true;
 }

 bool CWCDMATestEnd::InitData()
 {
	 m_pFuncWCDMATestDev=m_piTesterDevice->m_piFuncWCDMATest;
	 return true;
 }

 int  CWCDMATestEnd::EndCall()
 {
	 m_pFuncWCDMATestDev->Deivce_Exit();

	 m_pPhone->FTM_WCDMA_EndCall();

	 m_pPhone->CloseComport();

	 return PHONE_SUCCESS;
 }