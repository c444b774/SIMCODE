#include "stdafx.h"
#include "WCDMATestCall.h"

RF_IMPLEMENT_DYNCREATE(CWCDMATestStartCall)

CWCDMATestStartCall::CWCDMATestStartCall()
{
	m_mapClassFunc[_T("WCDMACallMainFunc")]=&CWCDMATestStartCall::CWCDMATestStartCallMainFunc;
	m_mapClassFunc[_T("WCDMACall")]=&CWCDMATestStartCall::CWCDMATestStartCallFunc;
	m_mapClassFunc[_T("WCDMA_NS_Call")]=&CWCDMATestStartCall::CWCDMATest_NS_StartCallFunc;
}

CWCDMATestStartCall::~CWCDMATestStartCall()
{
	
}

bool CWCDMATestStartCall::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CWCDMATestStartCall::Handle()
{
	if(!DoProcess())
	{
      return false;
	}
		
	return true;
}

bool CWCDMATestStartCall::CWCDMATestStartCallMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CWCDMATestStartCall:: CWCDMATest_NS_StartCallFunc()
{
	unsigned char ucTFCIConfig[4]={0,1,2,3};

	if(m_strTesterDevice=="A8960")
	{
         ucTFCIConfig[1]=2;
         ucTFCIConfig[2]=1;
	}
	int iDLChannel;
	int iErrorcode;
	iDLChannel=CWCDMABandInfo::GetDLChannel(m_iCallBand,m_iCallULChannel);

	
	if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestInitWCDMAtest(m_strDeviceAddr))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Init WCDMA Test Dev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("Init WCDMA Test Dev Fail!"))
		return false;
	}
	CString strMsg;
	double dLoss;
	DblVtr vCableLoss;
	vCableLoss.clear();
	CString strCallband;
	strCallband.Format("W%d",m_iCallBand);
	for(int i=0;i<3;i++)
	{
		if(!m_LossFinder.GetWCDMALoss(strCallband,i,dLoss))
		{
			strMsg.Format("WCDMA Get Loss Band=%s ,ChannelType=%d Fail",strCallband,i);
			LogTrace(MSG_ERROR,strMsg);
			CalFailLog(_T("_"),_T("_"),1001,strMsg);
			return false;
		}
		vCableLoss.push_back(dLoss);
	}

	if(DEVICE_SUCCESS!=m_pFuncWCDMATestDev->IWCDMATestSetLoss(m_iCallBand,vCableLoss))
	{
		LogTrace(MSG_ERROR,"Set Cableloss device fail");
		CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		return false;

	}
	if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestHandOver(m_iCallBand,m_iCallULChannel))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Dev set channel Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("Dev set channel Fail!"))
		return false;
	}
	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("WCDMA Test Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Phone Open Comport Fail!"))
		return false;
	}

	

	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("WCDMA Test Phone Set FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Phone Set FTM Mode Fail!"))
		return false;
	}
//	if((iErrorcode=m_pPhone->FTM_WCDMA_BER_StopSession())!=PHONE_SUCCESS)
//	{           
//		LogTrace(MSG_ERROR,_T("WCDMA Test Phone Set FTM Mode Fail!"))
//			m_iErrorcode=iErrorcode;
//		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Phone Set FTM Mode Fail!"))
//			return false;
//	}
	int iStartSessiontime=2;
	do 
	{
		m_pPhone->FTM_SET_MODE_ID(FTM_MODE_ID_WCDMA);
		m_pPhone->FTM_SECOND_CHAIN_TEST_CALL(0);
		if (m_strTesterDevice=="A8960")
		{
				m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_DL_TFCS_CONFIG,ucTFCIConfig);
				m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_UL_TFCS_CONFIG,ucTFCIConfig);

		}
//		m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_DL_TFCS_CONFIG,ucTFCIConfig);
//		m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_UL_TFCS_CONFIG,ucTFCIConfig);
		iErrorcode=(m_pPhone->FTM_WCDMA_BER_StartSession(10000));

	} while (iErrorcode!=PHONE_SUCCESS&&iStartSessiontime-->0);
	if(iErrorcode!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("WCDMA Test Phone BER_StartSession Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Phone BER_StartSession Fail!"))
		return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCDMA_BER_AcquirePilot(iDLChannel))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("WCDMA Test Phone BER_AcquirePilot Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T(CStr::IntToStr(m_iCallULChannel)),iErrorcode,_T("WCDMA Test Phone BER_AcquirePilot Fail!"))
		return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCDMA_BER_SetupRMC_DCH(FTM_WCDMA_BER_RMC_Type12_2kpbs,33,0,FTM_WCDMA_BER_PCA_Type_Alg1,FTM_WCDMA_BER_PCA_Size_1dB,0,9))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("WCDMA Test Phone BER_SetupRMC_DCH Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T(CStr::IntToStr(m_iCallULChannel)),iErrorcode,_T("WCDMA Test Phone BER_SetupRMC_DCH Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCDMA_AGC_START_LOG())!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("FTM_WCDMA_AGC_START_LOG"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T(CStr::IntToStr(m_iCallULChannel)),iErrorcode,_T("FTM_WCDMA_AGC_START_LOG"))
			return false;
	}
	
//	if((iErrorcode=m_pPhone->FTM_WCDMA_BER_Handover(3,33,0,1,0,0,9,8,15,iDLChannel))!=PHONE_SUCCESS)
//	{           
//		LogTrace(MSG_ERROR,_T("WCDMA Test Phone BER_Handover Fail!"))
//			m_iErrorcode=iErrorcode;
//      	CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Phone BER_Handover Fail!"))
//		return false;
//	}
	CalPassLog(_T(CStr::IntToStr(m_iCallBand)),_T(CStr::IntToStr(m_iCallULChannel)),_T("WCDMA_NS StartCall Pass"))
	return true;
}
bool CWCDMATestStartCall::CWCDMATestStartCallFunc()
{
  
  
     
	return true;
}

 bool CWCDMATestStartCall::InitData(
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
   

	   itrFind=pcSettingMap->find(_T("CALLBand"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'CALLBand' from ini file!");
		 return false;
		 
	 }
	 else
	 {
		 m_iCallBand=CStr::StrToInt(itrFind->second);
	 
	 }

	 itrFind=pcSettingMap->find(_T("CALLChannel"));

	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'CALLChannel' from ini file!");
		 return false;

	 }
	 else
	 {
		 m_iCallULChannel=CStr::StrToInt(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("CellPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'CellPower' from ini file,Use default -75 dBm!");
		 m_dCallCellPower=-75;

	 }
	 else
	 {
		 m_dCallCellPower=CStr::StrToFloat(itrFind->second);

	 }
	 itrFind=pcSettingMap->find(_T("TargetPower"));

	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TargetPower' from ini file,Use default -10 dBm!");
		 m_dCallTargetPower=-10;

	 }
	 else
	 {
		 m_dCallTargetPower=CStr::StrToFloat(itrFind->second);

	 }
	 itrFind=pcSettingMap->find(_T("BERSessionTimeOut"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'BERSessionTimeOut' from ini file!Use default 2000 ms");
		 m_dBERSessionTimeOut=2000;

	 }
	 else
	 {
		 m_dBERSessionTimeOut=CStr::StrToFloat(itrFind->second);

	 }

	 itrFind=pcSettingMap->find(_T("RegistTimeOut"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RegistTimeOut' from ini file,Use default 30 ms!");
		 m_dRegistTimeOut=30;

	 }
	 else
	 {
		 m_dRegistTimeOut=CStr::StrToFloat(itrFind->second);

	 }
	 

	 InitData();
	 return true;
 }

 bool CWCDMATestStartCall::InitData()
 {
	 m_pFuncWCDMATestDev=m_piTesterDevice->m_piFuncWCDMATest;
	
	 return true;
 }