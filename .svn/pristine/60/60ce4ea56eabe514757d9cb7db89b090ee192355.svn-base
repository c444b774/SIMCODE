#include "stdafx.h"
#include "GSM_EDGE_NSFT_Call.h"

RF_IMPLEMENT_DYNCREATE(CGSM_EDGE_NSFT_Call)

CGSM_EDGE_NSFT_Call::CGSM_EDGE_NSFT_Call()
{
	m_mapClassFunc[_T("GSM_NoSignal_TestCallMainFunc")]=&CGSM_EDGE_NSFT_Call::CGSM_EDGE_NSFT_CallMainFunc;
	m_mapClassFunc[_T("GSM_Nosignal_StartcallFunc")]=&CGSM_EDGE_NSFT_Call::CGSM_EDGE_NSFT_CallStartcallFunc;
}

CGSM_EDGE_NSFT_Call::~CGSM_EDGE_NSFT_Call()
{
	
}

bool CGSM_EDGE_NSFT_Call::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSM_EDGE_NSFT_Call::Handle()
{
	if(!DoProcess())
	{
		EndCall(m_IsEdge);
		return false;
	}
	return true;
}

bool CGSM_EDGE_NSFT_Call::CGSM_EDGE_NSFT_CallMainFunc()
{

	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CGSM_EDGE_NSFT_Call::CGSM_EDGE_NSFT_CallStartcallFunc()
{
  
   int iErrorcode;
   double dBSlev=-65;
   CString strMsg;
   double dInLoss=0.7;
   double dOutLoss=0.7;
   double dMaxInput=36;
   CString strState;
   unsigned long iSessionTimout=2000; 

   m_IsEdge==0?(m_iItemCode=GSM_GSMTestInit_BaseItemCode):(m_iItemCode=EDGE_EDGEInit_Test_BaseItemCode);
   
   if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
   {
	   LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
		   m_iErrorcode=iErrorcode;
	   CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
	   return false;
   }


   if((iErrorcode=m_pFunGSMTestDev->IGSMTestInitGSMtest_NSFT(m_strDeviceAddr,m_IsEdge,m_iCallCH,m_iCallPcl,m_iCallBand))!=DEVICE_SUCCESS)
   {
	   LogTrace(MSG_ERROR,_T("Init GSM NonSignal Test Fail!"))
	   m_iErrorcode=iErrorcode;
	   return false;
   }

   if((iErrorcode=m_pFunGSMTestDev->IGSMTestSetScreen(m_IsScreenOff))!=DEVICE_SUCCESS)
   {
	   LogTrace(MSG_ERROR,_T("Init Device Screen Fail!"))
		   m_iErrorcode=iErrorcode;
	   return false;
   }
   TestPassLog(m_strCurrBand,CStr::IntToStr(m_iCallCH),"_","_","_","_","InitDevice Pass");

   m_IsEdge==0?(m_iItemCode=GSM_GSMTestCall_BaseItemCode):(m_iItemCode=EDGE_EDGECall_Test_BaseItemCode);

   if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
   {           
	   LogTrace(MSG_ERROR,_T("Set Phone FTM Mode Fail!"))
		   m_iErrorcode=iErrorcode;
	   CalFailLog(_T("-"),_T("-"),iErrorcode,_T("Set Phone FTM Mode Fail!"))
		   return false;
   }
   if ((iErrorcode=m_pPhone->FTM_GSM_StartCall(m_isPreOnlineToFTM,m_iChainId,m_IsEdge,1000,m_iCallCH,m_iCallBand))!=PHONE_SUCCESS)
   {
	   LogTrace(MSG_ERROR,_T("FTM_GSM_StartCall Fail!"))
		   m_iErrorcode=iErrorcode;
	   TestFailLog(m_strCurrBand+'-'+CStr::IntToStr(m_iCallBand),CStr::IntToStr(m_iCallCH),1000,"_","_","_","_","Call Fail");
	   return false;
   }
   TestPassLog(m_strCurrBand,CStr::IntToStr(m_iCallCH),"_","_","_","_","Call Pass");
     
	return true;
}

 bool CGSM_EDGE_NSFT_Call::InitData(
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

	 itrFind=pcSettingMap->find(_T("TesterDeviceUse"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not find TestDeviceUse,use TesterDeviceCommon");
		 //return false;
		 m_piTesterDeviceCurr=m_piTesterDevice;
		 m_strTesterDeviceCurr=m_strTesterDevice;
		 m_strDeviceAddrCurr=m_strDeviceAddr;
	 }
	 else
	 {
		 if(itrFind->second=="TesterDeviceCommon")
		 {
			 m_piTesterDeviceCurr=m_piTesterDevice;
			 m_strTesterDeviceCurr=m_strTesterDevice;
			 m_strDeviceAddrCurr=m_strDeviceAddr;
		 }
	 }

	 //m_iChainId   
	 itrFind=pcSettingMap->find(_T("ChainId"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'ChainId' from ini file!.defualt is 0");
		 m_iChainId=0;
	 }
	 else
	 {
		 m_iChainId=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("IsEdge"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,_T("Not Find IsEdge"));
		 return false;
	 }
	 m_IsEdge=CStr::StrToInt(itrFind->second);		

	 itrFind=pcSettingMap->find(_T("ScreenOFF"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,_T("Not Find ScreenOFF"));
		 return false;
	 }
	 m_IsScreenOff=CStr::StrToInt(itrFind->second);
	

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
			m_iCallBand=4;
			m_strCurrBand=_T("GSM850");
			break;
	case 900:
			m_iCallBand=1;
			m_strCurrBand=_T("GSM900");
			break;
	case 1800:
			m_iCallBand=3;
			m_strCurrBand=_T("GSM1800");
			break;
	case 1900:
			m_iCallBand=2;
			m_strCurrBand=_T("GSM1900");

			break;
	default:
		 LogTrace(MSG_FATAL,_T("Phone Band not correct "));
		 return false;
	}
   
    itrFind=pcSettingMap->find(_T("CALLChannel"));
    if(itrFind==pcSettingMap->end())
	{
		 LogTrace(MSG_FATAL,_T("Not Find CALLChannel"));
		 return false;
	}
	 
	m_iCallCH=CStr::StrToInt(itrFind->second);

	itrFind=pcSettingMap->find(_T("CALLPcl"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,_T("Not Find CALLPcl,use default 5"));
		m_iCallPcl=5;
	}
	else
		m_iCallPcl=CStr::StrToInt(itrFind->second);

	itrFind=pcSettingMap->find(_T("PreOnlineToFTM"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,_T("Not Find PreOnlineToFTM,Use default 1"));
		m_isPreOnlineToFTM=1;
	}
	else
		m_isPreOnlineToFTM=CStr::StrToInt(itrFind->second);	
 
	 InitData();
	 return true;
 }

 bool CGSM_EDGE_NSFT_Call::InitData()
 {
	 m_pFunGSMTestDev=m_piTesterDevice->m_piFuncGSMTest;
	 return true;
 }

 bool CGSM_EDGE_NSFT_Call::CheckBTflag()
 {

	 TestPassLog("ABCDEFG","1","1","1","1","dBm","Test pass!");

	 return true;
 }

 int  CGSM_EDGE_NSFT_Call::EndCall(int iMode)
 {
	 m_pFunGSMTestDev->Deivce_Exit();
	
	 m_pPhone->CloseComport();

	 return PHONE_SUCCESS;
 }