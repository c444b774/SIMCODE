#include "StdAfx.h"
#include "GSM_EDGE_NSFT_EndCall.h"
RF_IMPLEMENT_DYNCREATE(CGSM_EDGE_NSFT_EndCall)
CGSM_EDGE_NSFT_EndCall::CGSM_EDGE_NSFT_EndCall(void)
{
	m_mapClassFunc[_T("GNSFTestEndCallMainFunc")]=&CGSM_EDGE_NSFT_EndCall::GNSFTestEndCallMainFunc;
	m_mapClassFunc[_T("GNSFTestFunc")]=&CGSM_EDGE_NSFT_EndCall::GNSFTestFunc;

}

CGSM_EDGE_NSFT_EndCall::~CGSM_EDGE_NSFT_EndCall(void)
{
}

bool CGSM_EDGE_NSFT_EndCall::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool CGSM_EDGE_NSFT_EndCall::Handle()
{
	if(!DoProcess())
	{
		EndCall();
		return false;
	}
	EndCall();
	return true;
}

bool CGSM_EDGE_NSFT_EndCall::InitData(
							PCStringStrMap     pcSettingMap,
							CRFObjectMap&   cObjectMap
							) 
{
	CStringStringMapItr itrFind;
	CString strValue;
	CString strMainFun;
	CStringVtr strVtr;
	itrFind=pcSettingMap->find(_T("MainFunc"));
	if(itrFind==pcSettingMap->end())
		return false;
	else
	{
		if(!SetMainFunc(itrFind->second))
			return false;
	}
	strMainFun=itrFind->second;
	CString strFuncList;
	itrFind=pcSettingMap->find(_T("List"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,_T("Not Find List"));
		return false;
	}
	strFuncList=itrFind->second;


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

	itrFind=pcSettingMap->find(_T("IsEdge"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_ERROR,"Not Find 'IsEdge' from ini file!");
		return false;
	}
	else
	{
		m_IsEdge=CStr::StrToInt(itrFind->second);
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

bool CGSM_EDGE_NSFT_EndCall::GNSFTestEndCallMainFunc()
{

	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}

	return true;
}
bool CGSM_EDGE_NSFT_EndCall::GNSFTestFunc()
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

	m_IsEdge==0?(m_iItemCode=GSM_GSMTestEnd_BaseItemCode):(m_iItemCode=EDGE_EDGETestEnd_BaseItemCode);

/*
	if ((iErrorcode=EndCall())!=PHONE_SUCCESS)
	{
		TestFailLog("_","_",iErrorcode,"_","_","_","_","EndCall Fail");
	}*/

	TestPassLog(_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("EndCall Pass"));

	return true;
}



bool CGSM_EDGE_NSFT_EndCall::InitData()
{
	m_pFunGSMTestDev=m_piTesterDevice->m_piFuncGSMTest;
	return true;
}

int  CGSM_EDGE_NSFT_EndCall::EndCall()
{
	m_pFunGSMTestDev->Deivce_Exit();
	
	m_pPhone->FTM_GSM_EndCall(m_nEndDelay);

	m_pPhone->CloseComport();

	return PHONE_SUCCESS;
}