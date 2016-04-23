#include "stdafx.h"
#include "GSM_TestCall.h"

RF_IMPLEMENT_DYNCREATE(CGSM_TestCall)

CGSM_TestCall::CGSM_TestCall()
{
	m_mapClassFunc[_T("GSM_TestCallMainFunc")]=&CGSM_TestCall::CGSM_TestCallMainFunc;
	m_mapClassFunc[_T("GSM_StartcallFunc")]=&CGSM_TestCall::CGSM_TestCallFunc;
	m_mapClassFunc[_T("GSM_Nosignal_StartcallFunc")]=&CGSM_TestCall::CGSM_NS_TestCallFunc;
}

CGSM_TestCall::~CGSM_TestCall()
{
	
}

bool CGSM_TestCall::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSM_TestCall::Handle()
{
	if(!DoProcess())
		return false;
	return true;
}

bool CGSM_TestCall::CGSM_TestCallMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CGSM_TestCall::CGSM_TestCallFunc()
{
	return true;
}
bool CGSM_TestCall::CGSM_NS_TestCallFunc()
{
  
   int iErrorcode;
   double dBSlev=-65;
   CString strMsg;
   double dInLoss=0.7;
   double dOutLoss=0.7;
   double dMaxInput=36;
   CString strState;
   unsigned long iSessionTimout=2000;
   


   if((iErrorcode=m_pFunGSMTestDev->IGSMTestInitGSMtest(m_strDeviceAddr))!=DEVICE_SUCCESS)
   {
      LogTrace(MSG_ERROR,_T("Init GSM Test Fail!"))
	   m_iErrorcode=iErrorcode;
	   return false;
   }
   if((iErrorcode=m_pFunGSMTestDev->IGSMTestSetBand(m_iCallBand))!=DEVICE_SUCCESS)
   {
	    LogTrace(MSG_ERROR,_T("GSM Test Set Band Fail!"))
	   m_iErrorcode=iErrorcode;
	   return false;
   }
    if((iErrorcode=m_pFunGSMTestDev->IGSMTestSetBSLev(dBSlev))!=DEVICE_SUCCESS)
	{
		  LogTrace(MSG_ERROR,_T("GSM Test Set BS Level Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}

	if((iErrorcode=m_pFunGSMTestDev->IGSMTestSetCH(m_iCallBCH,m_iCallTCH))!=DEVICE_SUCCESS)
	{
		  LogTrace(MSG_ERROR,_T("GSM Test Set BS BCCH and TCCH Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
     
	if((iErrorcode=m_pFunGSMTestDev->SetCableLoss(dInLoss,dOutLoss))!=DEVICE_SUCCESS)
	{
		 LogTrace(MSG_ERROR,_T("GSM Test Set cable loss Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
    if((iErrorcode=m_pFunGSMTestDev->IGSMTestSetPCL(m_iCallPCL))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test Set PCL Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}

	 if((iErrorcode=m_pFunGSMTestDev->IGSMTestSetInputLevel(dMaxInput,true))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test Set max input Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}

     if((iErrorcode=m_pFunGSMTestDev->IGSMTestSetBitStream(ECHO))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test Set data bit stream Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}

    if((iErrorcode=m_pFunGSMTestDev->IGSMTestConfigGSMTest())!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test config GSM TEST stream Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
    
     if((iErrorcode=m_pFunGSMTestDev->IGSMTestQueryCallState(strState))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test Query State Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
       if((iErrorcode=m_pFunGSMTestDev->IGSMTestProceActOnOff())!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test Proceed action on  Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
    


    
	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		        LogTrace(MSG_ERROR,_T("GSM Test Phone Open Comport Fail!"))
				m_iErrorcode=iErrorcode;
				return false;
	}
     if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{            LogTrace(MSG_ERROR,_T("GSM Test Phone Set Mode Fail!"))
				m_iErrorcode=iErrorcode;
				return false;
	}

    
       m_pPhone->FTM_GSM_BER_StopSession();
	if((iErrorcode=m_pPhone->FTM_GSM_BER_StartSession(iSessionTimout))!=PHONE_SUCCESS)
	{
		 LogTrace(MSG_ERROR,_T("Phone Start session fail"))
				m_iErrorcode=iErrorcode;
				return false;
	}
      
   

     if((iErrorcode=m_pPhone->FTM_GSM_BER_AssignBCCH((unsigned short)m_iCallBCH,(unsigned char)m_iPhoneTestBand))!=PHONE_SUCCESS)
	{
		 LogTrace(MSG_ERROR,_T("Phone Assign BCCH fail"))
				m_iErrorcode=iErrorcode;
				return false;
	}
	 strState.Empty();
    if((iErrorcode=m_pFunGSMTestDev->IGSMTestQueryCallState(strState))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test Query State  Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
     
	
    strMsg+_T("After call FTM_GSM_BER_AssignBCCH ,the Call state queried from testset is ") +strState ;

	LogTrace(MSG_MID,strMsg);

     if((iErrorcode=m_pFunGSMTestDev->IGSMTestProceMTC())!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test Proceed MTC Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
    bool bRet;
       if((iErrorcode=m_pPhone->FTM_GSM_BER_Handover(m_iCallTCH,m_iPhoneTestBand,0,2,FTM_GSM_BER_SPEECH_FULL_RATE,m_iCallPCL,3,20,bRet))!=PHONE_SUCCESS )
	{
		
		 LogTrace(MSG_ERROR,_T("Phone BER Handover fail"))
				m_iErrorcode=iErrorcode;
				return false;
	}
	   
    
     strState.Empty();
    if((iErrorcode=m_pFunGSMTestDev->IGSMTestQueryCallState(strState))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSM Test Query State  Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
     

	
    strMsg=_T("After call FTM_GSM_BER_Handover ,the Call state queried from testset is ") +strState ;


      if((iErrorcode=m_pFunGSMTestDev->IGSMTestConfigTestPara())!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("GSMTest Config parameter   Fail!"))
		m_iErrorcode=iErrorcode;
	   return false;
	}
     
	return true;
}

 bool CGSM_TestCall::InitData(
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
    itrFind=pcSettingMap->find(_T("CallBand"));
    if(itrFind==pcSettingMap->end())
	{
		 LogTrace(MSG_FATAL,_T("Not Find CallBand"));
		 return false;
	}
    
	 
	m_iCallBand=CStr::StrToInt(itrFind->second);
    switch(m_iCallBand)
	{
	case 850:
			m_iPhoneTestBand=4;
			m_strCurrentBand=_T("GSM850");
			break;
	case 900:
			m_iPhoneTestBand=1;
			m_strCurrentBand=_T("GSM900");
			break;
	case 1800:
			m_iPhoneTestBand=3;
			m_strCurrentBand=_T("GSM1800");
			break;
	case 1900:
			m_iPhoneTestBand=2;
			m_strCurrentBand=_T("GSM1900");

			break;
	default:
		 LogTrace(MSG_FATAL,_T("Phone Band not correct "));
		 return false;
	}
   
    itrFind=pcSettingMap->find(_T("TCH"));
    if(itrFind==pcSettingMap->end())
	{
		 LogTrace(MSG_FATAL,_T("Not Find TCH"));
		 return false;
	}

	 
	m_iCallTCH=CStr::StrToInt(itrFind->second);

	itrFind=pcSettingMap->find(_T("BCH"));
    if(itrFind==pcSettingMap->end())
	{
		 LogTrace(MSG_FATAL,_T("Not Find BCH"));
		 return false;
	}

	 
	m_iCallBCH=CStr::StrToInt(itrFind->second);

	itrFind=pcSettingMap->find(_T("PCL"));
    if(itrFind==pcSettingMap->end())
	{
		 LogTrace(MSG_FATAL,_T("Not Find PCL"));
		 return false;
	}

	 
	m_iCallPCL=CStr::StrToInt(itrFind->second);




	 InitData();
	 return true;
 }

 bool CGSM_TestCall::InitData()
 {
	 m_pFunGSMTestDev=m_piTesterDevice->m_piFuncGSMTest;
	 return true;
 }