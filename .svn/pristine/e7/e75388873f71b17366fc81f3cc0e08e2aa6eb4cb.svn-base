#include "stdafx.h"
#include "RxDCAutoCal.h"
RF_IMPLEMENT_DYNCREATE(CRxDCAutoCal)

CRxDCAutoCal::CRxDCAutoCal()
{
	m_mapClassFunc[_T("RxDCAutoCalMainFunc")]=&CRxDCAutoCal::CRxDCAutoCalMainFunc;
	m_mapClassFunc[_T("RxDCAutoCalFunc")]=&CRxDCAutoCal::CRxDCAutoCalFunc;

}

CRxDCAutoCal::~CRxDCAutoCal()
{
	
}

bool CRxDCAutoCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CRxDCAutoCal::Handle()
{
	if(!DoProcess())
	{
		m_pPhone->FTM_SET_TX_ON(false);
       m_pPhone->CloseComport();

		return false;
	}

	return true;
}

bool CRxDCAutoCal::CRxDCAutoCalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CRxDCAutoCal::CRxDCAutoCalFunc()
{
      CString strMsg;
      int iErrorcode;
	QMSL_RFCal_WriteToPhone_Status   QMSL_RFCal_WriteToPhone;
        
	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iDCModeId))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode ID  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	
	if((iErrorcode=m_pPhone->FTM_SET_MODE(CWCDMABandInfo::GetPhoneMode(m_iBand)))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode (Band)  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iDCModeId))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode ID  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_iCHannel))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode (Band)  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iDCModeId))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode ID  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_DO_DC_CAL())!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Do Dc Cal  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	iErrorcode=m_pPhone->RFCAL_NV_Manager_WriteToPhone(&QMSL_RFCal_WriteToPhone);

	if(iErrorcode!=PHONE_SUCCESS)
	{
		strMsg.Format("RFCAL_NV_Manager_WriteToPhone Fail");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	strMsg.Format("Band %d RxDC_Cal:Pass",m_iBand);
	CalPassLog("_","_",strMsg);
	
	return true;
}


 bool CRxDCAutoCal::InitData(
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
     
	 itrFind=pcSettingMap->find(_T("RFMode"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RFMode' from ini file!.default is 1 (WCDMA)");
		 m_iDCModeId=1;
	 }
	 else
	 {
		 m_iDCModeId=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("Band"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'Band' from ini file!.default is 2100");
		 m_iBand=2100;
	 }
	 else
	 {
		 m_iBand=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("Channel"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'Channel' from ini file!.default is 9750");
		 m_iCHannel=9750;
	 }
	 else
	 {
		 m_iCHannel=CStr::StrToInt(itrFind->second);
	 }



	 InitData();
	 return true;
 }

 bool CRxDCAutoCal::InitData()
 {
//	 m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	 return true;
 }