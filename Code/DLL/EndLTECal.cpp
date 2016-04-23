#include "StdAfx.h"
#include "EndLTECal.h"
RF_IMPLEMENT_DYNCREATE(CEndLTECal)

CEndLTECal::CEndLTECal(void)
{
	m_mapClassFunc[_T("EndLTECalMainFunc")]=&CEndLTECal::CEndLTECalMainFunc;
	m_mapClassFunc[_T("EndLTECalFunc")]=&CEndLTECal::CEndLTECalFunc;
}

CEndLTECal::~CEndLTECal(void)
{
}

bool CEndLTECal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CEndLTECal::Handle()
{
	if(!DoProcess())
	{

		return false;
	}

	CalPassLog("_","_","End LTE Cal Pass");

	return true;
}

bool CEndLTECal::CEndLTECalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CEndLTECal::CEndLTECalFunc()
{
  
    CString strMsg;
    int iErrorcode;
	QMSL_RFCal_WriteToPhone_Status   QMSL_RFCal_WriteToPhone;
	unsigned char NVItemValue[128]={0};
  //  LogTrace(MSG_MID,_T(" ReloadNV!"))
		
	iErrorcode=m_pPhone->RFCAL_NV_Manager_WriteToPhone(&QMSL_RFCal_WriteToPhone);

	if(iErrorcode!=PHONE_SUCCESS)
	{
       strMsg.Format("RFCAL_NV_Manager_WriteToPhone Fail");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	strMsg.Format("RFCAL_NV_Manager_WriteToPhone:");
	LogTrace(MSG_MID,strMsg)
		for (int i=0;i<QMSL_RFCal_WriteToPhone.iNumOfItemsInCache;i++)
		{
			strMsg.Format("%d_%s",QMSL_RFCal_WriteToPhone.aNVItemStatus[i].iNVenum,QMSL_RFCal_WriteToPhone.aNVItemStatus[i].sNVName);
			LogTrace(MSG_MID,strMsg)
		}

	
   
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
	}


		LogTrace(MSG_MID,_T(" Write EFS !"))
		if((iErrorcode=m_pPhone->WriteEFS(30000))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" Phone WriteEFS Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone WriteEFS Fail!");
			return false;
		}

	

    

/*
	if((iErrorcode=m_pPhone->ReloadNV())!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Reload NV Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Reload NV Fail!");
			return false;
	}*/
     
   m_pPhone->CloseComport();
   m_pFunLTECalDev->Deivce_Exit();
    
	return true;
}

 bool CEndLTECal::InitData(
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

 bool CEndLTECal::InitData()
 {
	 m_pFunLTECalDev=m_piTesterDevice->m_piFuncWCDMACal;
	 return true;
 }
