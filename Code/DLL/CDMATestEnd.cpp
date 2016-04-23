#include "stdafx.h"
#include "CDMATestEnd.h"

RF_IMPLEMENT_DYNCREATE(CCDMATestEnd)

CCDMATestEnd::CCDMATestEnd()
{
	m_mapClassFunc[_T("CDMAEndCallMainFunc")]=&CCDMATestEnd::CCDMATestEndMainFunc;
	m_mapClassFunc[_T("CDMAEndCall")]=&CCDMATestEnd::CCDMATestEndFunc;
	m_mapClassFunc[_T("CDMAEndCallWithOutEFS")]=&CCDMATestEnd::CCDMATestEndFuncWithOutEFS;
}

CCDMATestEnd::~CCDMATestEnd()
{
	
}

bool CCDMATestEnd::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CCDMATestEnd::Handle()
{
	if(!DoProcess())
	{
	  EndCall();
      return false;
	}
	EndCall();	
	return true;
}

bool CCDMATestEnd::CCDMATestEndMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CCDMATestEnd::CCDMATestEndFuncWithOutEFS()
{
	CString strMsg;
	int iErrorcode;

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
	}

		m_pPhone->CloseComport();
		m_pFunCDMATestDev->Deivce_Exit();

		TestPassLog(_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("EndCall Pass"));


		return true;
}
bool CCDMATestEnd::CCDMATestEndFunc()
{
	CString strMsg;
	int iErrorcode;

	unsigned char NVItemValue[128]={0};
	if((iErrorcode=m_pPhone->FTM_CDMA2000_CMD_RELEASE())!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("FTM_CDMA2000_CMD_RELEASE() Fail!"))
			m_iErrorcode=iErrorcode;

		CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA2000_CMD_RELEASE() Fail!");
		return false;
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

			LogTrace(MSG_MID,_T(" Write EFS !"))
				if((iErrorcode=m_pPhone->WriteEFS(30000))!=PHONE_SUCCESS)
				{
					LogTrace(MSG_ERROR,_T(" Phone WriteEFS Fail!"))
						m_iErrorcode=iErrorcode;
					CalFailLog(_T("_"),_T("_"),iErrorcode," Phone WriteEFS Fail!");
					return false;
				}
	}
		

		


		return true;
}

 bool CCDMATestEnd::InitData(
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

	 itrFind=pcSettingMap->find(_T("EndDelay"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'EndDelay' from ini file!.default is 3000");
		 m_nEndDelay=3000;
	 }
	 else
	 {
		 m_nEndDelay=CStr::StrToInt(itrFind->second);
	 }
	  
	 InitData();
	 return true;
 }

 bool CCDMATestEnd::InitData()
 {
	 m_pFunCDMATestDev=m_piTesterDevice->m_piFuncCDMATest;
	 return true;
 }

 void CCDMATestEnd::EndCall()
 {
	 m_iItemCode=CDMA_CDMATestEnd_BaseItemCode;
	 m_pFunCDMATestDev->ICDMATestEndCall();

	 m_pPhone->FTM_CDMA2000_EndCall(m_nEndDelay);
	 m_pPhone->CloseComport();
	 m_pFunCDMATestDev->Deivce_Exit();

	 TestPassLog("_","_","_","_","_","_","EndCall Pass");
 }