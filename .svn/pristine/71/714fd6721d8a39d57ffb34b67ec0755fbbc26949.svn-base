#include "stdafx.h"
#include "CWCDMAMeasLoop.h"


RF_IMPLEMENT_DYNCREATE(CWCDMATestMeasureLoop)

CWCDMATestMeasureLoop::CWCDMATestMeasureLoop()
{
	m_mapClassFunc[_T("WCDMAMeasMainFunc")]=&CWCDMATestMeasureLoop::CWCDMATestMeasureLoopMainFunc;
	m_mapClassFunc[_T("TestHandOver")]=&CWCDMATestMeasureLoop::CWCDMATestHandOver;
	m_mapClassFunc[_T("TestMinPower")]=&CWCDMATestMeasureLoop::CWCDMATestMinPower;
    m_mapClassFunc[_T("TestModAnalysis")]=&CWCDMATestMeasureLoop::CWCDMATestModAnalysis;
    m_mapClassFunc[_T("TestMaxPower")]=&CWCDMATestMeasureLoop::CWCDMATestMaxPower;
    m_mapClassFunc[_T("TestACLR")]=&CWCDMATestMeasureLoop::CWCDMATestACLR;
    m_mapClassFunc[_T("TestOBW")]=&CWCDMATestMeasureLoop::CWCDMATestOBW;
    m_mapClassFunc[_T("TestBER")]=&CWCDMATestMeasureLoop::CWCDMATestBER;
    m_mapClassFunc[_T("TestSEMask")]=&CWCDMATestMeasureLoop::CWCDMATestSEMask;
    m_mapClassFunc[_T("TestILPC")]=&CWCDMATestMeasureLoop::CWCDMATestILPC;



	//m_mapClassFunc[_T("WCDMATestRSCP")]=&CWCDMATestMeasureLoop::CWCDMATestRSCP;
	//m_mapClassFunc[_T("WCDMANSTestRX")]=&CWCDMATestMeasureLoop::CWCDMANSTestRX;
/*
 bool CWCDMATestMeasureLoop::CWCDMATestMeasureALL(int iBand,int iULChannel,CString strTestItem)	
*/	

	m_pReStartCall=NULL;
}

CWCDMATestMeasureLoop::~CWCDMATestMeasureLoop()
{
	
}

bool CWCDMATestMeasureLoop::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CWCDMATestMeasureLoop::Handle()
{
	if(!DoProcess())
	{
		m_pFuncWCDMATestDev->Deivce_Exit();

		m_pPhone->FTM_WCDMA_EndCall();

		m_pPhone->CloseComport();
      return false;
	}
		
	return true;
}

bool CWCDMATestMeasureLoop::CWCDMATestMeasureLoopMainFunc()
{
	if (!SetWCDMATestLOSS())
	return false;
	for (int i=0;i<m_iTestChannelList.size();i++)   
	{
		m_iCurrentCH=m_iTestChannelList[i];
		for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
		{
			int iRetry=0;
			FPClassFunc fpTestFunc=*itrFP;
			for (;;)
			{
				if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
				{
					this->WcdmaReCall();
				}
				else
				{
					break;
				}
				if (iRetry++>1)
				{
					return false;
				}
			}
	
		 }
	}	
	return true;	
}

 bool CWCDMATestMeasureLoop::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
     CStringStringMapItr itrFind;
	 CRFObjectMapItr   itrObjFind;
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
	 itrFind=pcSettingMap->find(_T("IsReFineILPC"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'IsReFineILPC' from ini file! Default is 0");
		 m_iIsReFineILPC=0;
		 
	 }
	 else
	 {
		 m_iIsReFineILPC=CStr::StrToInt(itrFind->second);
	 }
    
	

    itrFind=pcSettingMap->find(_T("RXScaleFactor"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RXScaleFactor' from ini file! Default is 10");
		 m_iRXScaleFactor=10;
		 
	 }
	 else
	 {
		 m_iRXScaleFactor=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("RXMinPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RXMinPower' from ini file! Default is -106");
		 m_dMinRXPower=-106;
		 
	 }
	 else
	 {
		 m_dMinRXPower=CStr::StrToFloat(itrFind->second);
	 }

	   itrFind=pcSettingMap->find(_T("TestBand"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'TestBand' from ini file!");
		 return false;
		 
	 }
	 else
	 {
		 m_iTestBand=CStr::StrToInt(itrFind->second);
		 m_strTestBand="W"+itrFind->second;
	 }
	 itrFind=pcSettingMap->find(_T("ChannelList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'ChannelList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2IntVtr(m_iTestChannelList,strVtr);
	 }	 

/*	 for(int i=1;i<=m_iTestChannelList.size();i++)
	 {
		 strValue.Empty();
		 strVtr.clear();

		 strValue.Format("TestItem_CH%d",i);
		 itrFind=pcSettingMap->find(_T(strValue));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T(strValue));
			 return false;
		 }
		 else
		 {
			 strValue=itrFind->second;
			 m_strVtrTestItem.push_back(strValue);
		 }
	 }
*/
	 itrFind=pcSettingMap->find(_T("MeasureCount"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'MeasureCount' from ini file,Use default 10 !");
		 m_iMeasureCount=10;

	 }
	 else
	 {
		 m_iMeasureCount=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("BERSamples"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'BERSamples' from ini file,Use default 10000!");
		 m_iBERSamples=10000;

	 }
	 else
	 {
		 m_iBERSamples=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("MidPowerTarget"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'MidPowerTarget' from ini file,Use default 10!");
		 m_dMidPowerTarget=10;

	 }
	 else
	 {
		 m_dMidPowerTarget=CStr::StrToFloat(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("MaxPowerLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'MaxPowerLimit' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dMaxPowerLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("MinPowerLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'MinPowerLimit' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dMinPowerLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("MidPowerLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'MidPowerLimit' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dMidPowerLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("FERLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'FERLimit' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dFERLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("OBWLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'OBWLimit' from ini file,Use default 5 MHz!");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dOBWLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("BERLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'BERLimit' from ini file,Use default 0.1 %!");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dBERLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("RxCellPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RxCellPower' from ini file,Use default -106 dBm!");
		 m_dRxCellPower=-106;

	 }
	 else
	 {
		 m_dRxCellPower=CStr::StrToFloat(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("ILPCList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'ILPCList' from ini file,Use default 0,0,0,0,0,0,0,0!");
		 memset(m_iILPCList,0,sizeof(m_iILPCList));
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::StrToIntArr(strValue,m_iILPCList,_T(","),8);

	 }

	 itrFind=pcSettingMap->find(_T("ACLRLimit"));
   if(itrFind==pcSettingMap->end())
	 {
		LogTrace(MSG_FATAL,"Not Find 'ACLRLimit' from ini file! Use default -43,-33,-33,-43 Unit dB value");
		strValue="-33,-33,-43,-43";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvACLRLimit,strVtr);
	 }
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvACLRLimit,strVtr);
	}
	 itrFind=pcSettingMap->find(_T("EVMLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'EVMLimit' from ini file,Use default 17.5 %!");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dEVMLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }
	 itrFind=pcSettingMap->find(_T("PVELimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'PVELimit' from ini file");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dPVELimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("PERLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'PERLimit' from ini file");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dPERLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("MagERRLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'MagERRLimit' from ini file");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dMagERRLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("ORGNOFSLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'ORGNOFSLimit' from ini file");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dOOLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("IQILimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'IQILimit' from ini file");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dIQILimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("DDPRlimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'DDPRlimit' from ini file");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dDDPRlimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("TERLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'TERLimit' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dTERLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("PCDERRLimit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'PCDERRLimit' from ini file,Use default -15 dB!");
		 return false;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_dPCDERRLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	 }

	 itrFind=pcSettingMap->find(_T("RSCPCellPowerList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RSCPCellPowerList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_dRSCP_CellPower,strVtr);
	 }

	 itrFind=pcSettingMap->find(_T("RSCPHighLimitList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RSCPHighLimitList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_dRSCP_HLimit,strVtr);
	 }

	 itrFind=pcSettingMap->find(_T("RSCPLowLimitList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,"Not Find 'RSCPLowLimitList' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,",",strVtr);
		 CStr::StrVtr2DblVtr(m_dRSCP_LLimit,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("FailRunList"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_WARNING,_T("Not Find FailRunList,default is """));
			 m_strFailRunList="";
		 }
		 else
		 {
			 m_strFailRunList=itrFind->second;
	
		 }

	  itrFind=pcSettingMap->find(_T("ReCallObjName"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_WARNING,_T("Not Find ReCallObjName,default is """));
			 return false;
		 }
		 itrObjFind=cObjectMap.find(itrFind->second);
		 if(itrObjFind==cObjectMap.end())
		 {
			 LogTrace(MSG_WARNING,"Not Find 'ReCallObjName' from ini file.default is NULL !");
			 m_pReStartCall=NULL;

		 }
		 else
		 {
			 m_pReStartCall=dynamic_cast<CWCDMATestStartCall *>(itrObjFind->second);
		 }


		 if(m_iIsReFineILPC)
		 {
			 itrFind=pcSettingMap->find(_T("NV_RISE_FALL"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_FATAL,"Not Find 'NV_RISE_FALL' from ini file!");
				 return false;
			 }
			 else
			 {
				 strValue=itrFind->second;
				 CStr::ParseString(strValue,",",strVtr);
				 CStr::StrVtr2IntVtr(m_vFALLRISE_NVID,strVtr);
			 }

			  itrFind=pcSettingMap->find(_T("NV_COMPEN_UP_DOWN_FALL"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_FATAL,"Not Find 'NV_COMPEN_UP_DOWN_FALL' from ini file!");
				 return false;
			 }
			 else
			 {
				 strValue=itrFind->second;
				 CStr::ParseString(strValue,",",strVtr);
				 CStr::StrVtr2IntVtr(m_vCompenNV_ID,strVtr);
			 }

			 itrFind=pcSettingMap->find(_T("IsRTR6285"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_WARNING,"Not Find 'IsRTR6285' from ini file! Default is 1");
				 m_iIs6285Plat=1;
			 }
			 else
			 {
				 m_iIs6285Plat=CStr::StrToInt(itrFind->second);
				 
			 }

		 }
	
	 InitData();
	 return true;
 }

 bool CWCDMATestMeasureLoop::InitData()
 {
	 m_pFuncWCDMATestDev=m_piTesterDevice->m_piFuncWCDMATest;
	 return true;
 }

 bool CWCDMATestMeasureLoop::SetWCDMATestLOSS()
 {
	 CString strMsg;
	 double dLoss;
	 m_vCableLoss.clear();
	 for(int i=0;i<3;i++)
	 {
		 if(!m_LossFinder.GetWCDMALoss(m_strTestBand,i,dLoss))
		 {
			 strMsg.Format("WCDMA Get Loss Band=%s ,ChannelType=%d Fail",m_strTestBand,i);
			 LogTrace(MSG_ERROR,strMsg);
			 CalFailLog(_T("_"),_T("_"),1001,strMsg);
			 return false;
		 }
		 m_vCableLoss.push_back(dLoss);
	 }

	 if(DEVICE_SUCCESS!=m_pFuncWCDMATestDev->IWCDMATestSetLoss(m_iTestBand,m_vCableLoss))
	 {
		 LogTrace(MSG_ERROR,"Set Cableloss device fail");
		 CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		 return false;

	 }

	 return  true;

 }
 bool CWCDMATestMeasureLoop::WcdmaReCall()
 {


	 unsigned char ucTFCIConfig[4]={0,1,2,3};
	 if(m_strTesterDevice=="A8960")
	 {	 ucTFCIConfig[1]=2;
	 ucTFCIConfig[2]=1;
	 }
	 int iErrorcode;
	 int iDLChannel;
	 m_iItemCode=WCDMA_Call_HandOver_Device_BaseItemCode;
	 iDLChannel=CWCDMABandInfo::GetDLChannel(m_iTestBand,m_iCurrentCH);

	
	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestHandOver(m_iTestBand,m_iCurrentCH))!=DEVICE_SUCCESS)	 
	 {
		 LogTrace(MSG_ERROR,_T("WCDMA Test Dev HandOver Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Dev HandOver Fail!"))
			 return false;
	 }
	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestSetPower(-75,0,2))!=DEVICE_SUCCESS)	 
	 {
		 LogTrace(MSG_ERROR,_T("WCDMA Test Dev IWCDMATestSetPower Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Dev IWCDMATestSetPower Fail!"))
			 return false;
	 }

	 m_iItemCode=WCDMA_Call_HandOver_Phone_BaseItemCode;
	 if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(FTM_MODE_ID_WCDMA))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("Set phone FTM_MODE_ID_WCDMA fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Set phone FTM_MODE_ID_WCDMA fail"))
			 return false;
	 }

	 if((iErrorcode=m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_DL_TFCS_CONFIG,ucTFCIConfig))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ DL Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ DL Fail!"))
			 return false;
	 }
	 if((iErrorcode=m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_UL_TFCS_CONFIG,ucTFCIConfig))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ UL Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ UL Fail!"))
			 return false;
	 }

	 if((iErrorcode=m_pPhone->FTM_WCDMA_BER_Handover(3,33,0,0,0,0,9,8,15,iDLChannel))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("WCDMA Test Phone BER_Handover Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Test Phone BER_Handover Fail!"))
			 return false;
	 }
	 if(!m_pPhone->IsPhoneConnected())  
	 {           
		 LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			 return false;
	 }	
	 return true;

 }
  bool CWCDMATestMeasureLoop::CWCDMATestHandOver()
  {
     unsigned char ucTFCIConfig[4]={0,1,2,3};
	 if(m_strTesterDevice=="A8960")
	 {	 ucTFCIConfig[1]=2;
	     ucTFCIConfig[2]=1;
	 }
	 int iErrorcode;
	 int iDLChannel;
	 m_iItemCode=WCDMA_Call_HandOver_Device_BaseItemCode;
	 iDLChannel=CWCDMABandInfo::GetDLChannel(m_iTestBand,m_iCurrentCH);

	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestHandOver(m_iTestBand,m_iCurrentCH))!=DEVICE_SUCCESS)	 
	 {
		 LogTrace(MSG_ERROR,_T("WCDMA Test Dev HandOver Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Dev HandOver Fail!"))
			 return false;
	 }

     m_iItemCode=WCDMA_Call_HandOver_Phone_BaseItemCode;
	 if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(FTM_MODE_ID_WCDMA))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("Set phone FTM_MODE_ID_WCDMA fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Set phone FTM_MODE_ID_WCDMA fail"))
			 return false;
	 }

	 if((iErrorcode=m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_DL_TFCS_CONFIG,ucTFCIConfig))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ DL Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ DL Fail!"))
			 return false;
	 }
	 if((iErrorcode=m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_UL_TFCS_CONFIG,ucTFCIConfig))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ UL Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ UL Fail!"))
			 return false;
	 }

	 if((iErrorcode=m_pPhone->FTM_WCDMA_BER_Handover(3,33,0,0,0,0,9,8,15,iDLChannel))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("WCDMA Test Phone BER_Handover Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Test Phone BER_Handover Fail!"))
			 return false;
	 }
	 CalPassLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("WCDMA_NS HandOver Pass"))

	 return true;
  }

 bool CWCDMATestMeasureLoop::CWCDMATestMinPower()
 {
	 /*
	 A1 MinPower
	 B1 Power at TargetPower
	 C1 Mod at TargetPower
	 D1 MaxPower
	 E1 Mod at MaxPower
	 F1 ADJ at MaxPower
	 G1 OBW at MaxPower
	 H1 SMASK at MaxPower
	 I1 BER at MaxPower
	 J1 FER at MaxPower
	 K1 ILPC
	 */
	 int iErrorcode;
	 double dMeasPower;
	 int iFailFlag=0;
	 m_iItemCode=WCDMA_MinPower_Test_BaseItemCode;
	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestMinPower(m_iMeasureCount,&dMeasPower))!=DEVICE_SUCCESS)
	 {
		 LogTrace(MSG_ERROR,_T("WCDMA Test Measure MinPower Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Test Measure MinPower Fail!"))
			 return false;
	 }

	 if (m_dMinPowerLimit.InRange(dMeasPower))
	 {
		 TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMin())),_T(CStr::FloatToStr(dMeasPower)),_T("dBm"),_T("MinPower PASS"),"MinPower")
	 } 
	 else
	 {
		 iFailFlag++;
		 TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MINPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMinPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMin())),_T(CStr::FloatToStr(dMeasPower)),_T("dBm"),_T("MinPower FAIL"),"MinPower")
	 }

	 if(!m_pPhone->IsPhoneConnected())  
	 {           
		 LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			 return false;
	 }	
	 if (iFailFlag>0)
	 {
		 return false;
	 }
	 
	 return true;

 }
 bool CWCDMATestMeasureLoop::CWCDMATestModAnalysis()
 {
	 /*
	 A1 MinPower
	 B1 Power at TargetPower
	 C1 Mod at TargetPower
	 D1 MaxPower
	 E1 Mod at MaxPower
	 F1 ADJ at MaxPower
	 G1 OBW at MaxPower
	 H1 SMASK at MaxPower
	 I1 BER at MaxPower
	 J1 FER at MaxPower
	 K1 ILPC
	 */
	 //Error Vector Magnitude  Unit=%
	 //Peak Vector Error Unit=%
	 //Phase Error Unit=deg
	 //Magnitude Error Unit=%
	 //Origin Offset Unit=dB
	 //IQ Imbalance Unit=%
	 //Timing Error Unit=chip
	 //DPCCH/DPDCH Power Ratio Unit=dB
	 int iErrorcode;
	 double dMeasPower;
	 double dModValue[8];
	 CString strMsg;
	 int ifailflag=0;
	 m_iItemCode=WCDMA_InitWCDMATest_BaseItemCode;
	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestModAnalysis(m_iMeasureCount,m_dMidPowerTarget,&dMeasPower,dModValue))!=DEVICE_SUCCESS)
	 {
		 LogTrace(MSG_ERROR,_T("WCDMA Test Measure ModAnalysis Fail!"))
		 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Test Measure ModAnalysis Fail!"))
		 return false;
	 }

     m_iItemCode+='C';
	 if (m_dEVMLimit.InRange(dModValue[0]))
	 {
		 strMsg.Format("Error Vector Magnitude PASS at %.2f dbm",m_dMidPowerTarget);
		 TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dEVMLimit.GetMax())),_T(CStr::FloatToStr(m_dEVMLimit.GetMin())),_T(CStr::FloatToStr(dModValue[0])),_T("%"),strMsg,"EVM")
	 } 
	 else
	 {
		 strMsg.Format("Error Vector Magnitude FAIL at %.2f dbm",m_dMidPowerTarget);
		 ifailflag++;
		 TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_EVM_OUTOFRANGE,_T(CStr::FloatToStr(m_dEVMLimit.GetMax())),_T(CStr::FloatToStr(m_dEVMLimit.GetMin())),_T(CStr::FloatToStr(dModValue[0])),_T("%"),strMsg,"EVM")
	 }

	 if (m_dMagERRLimit.InRange(dModValue[3]))
	 {
		 strMsg.Format("Magnitude Error PASS at %.2f dbm",m_dMidPowerTarget);
		 TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMagERRLimit.GetMax())),_T(CStr::FloatToStr(m_dMagERRLimit.GetMin())),_T(CStr::FloatToStr(dModValue[3])),_T("%"),strMsg,"Mag")
	 } 
	 else
	 {
		 strMsg.Format("Magnitude Error Fail at %.2f dbm",m_dMidPowerTarget);
		 ifailflag++;
		 TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MAGTDERR_OUTOFRANGE,_T(CStr::FloatToStr(m_dMagERRLimit.GetMax())),_T(CStr::FloatToStr(m_dMagERRLimit.GetMin())),_T(CStr::FloatToStr(dModValue[3])),_T("%"),strMsg,"Mag")
	 }

	 if (m_dOOLimit.InRange(dModValue[4]))
	 {
		 strMsg.Format("Origin Offset PASS at %.2f dbm",m_dMidPowerTarget);
		 TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dOOLimit.GetMax())),_T(CStr::FloatToStr(m_dOOLimit.GetMin())),_T(CStr::FloatToStr(dModValue[4])),_T("dB"),strMsg,"OFS")
	 } 
	 else
	 {
		 strMsg.Format("Origin Offset Fail at %.2f dbm",m_dMidPowerTarget);
		 ifailflag++;
		 TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ORIGINOFFSET_OUTOFRANGE,_T(CStr::FloatToStr(m_dOOLimit.GetMax())),_T(CStr::FloatToStr(m_dOOLimit.GetMin())),_T(CStr::FloatToStr(dModValue[4])),_T("dB"),strMsg,"OFS")
	 }

	/* if (m_dIQILimit.InRange(dModValue[5]))
	 {
		 strMsg.Format("IQ Imbalance PASS at CellPower %.2f",m_dMidPowerTarget);
		 TestPassLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dIQILimit.GetMax())),_T(CStr::FloatToStr(m_dIQILimit.GetMin())),_T(CStr::FloatToStr(dModValue[5])),_T("%"),strMsg)
	 } 
	 else
	 {
		 strMsg.Format("IQ Imbalance Fail at CellPower %.2f",m_dMidPowerTarget);
		 ifailflag++;
		 TestFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ORIGINOFFSET_OUTOFRANGE,_T(CStr::FloatToStr(m_dIQILimit.GetMax())),_T(CStr::FloatToStr(m_dIQILimit.GetMin())),_T(CStr::FloatToStr(dModValue[5])),_T("%"),strMsg)
	 }*/

	 if (m_dTERLimit.InRange(dModValue[6]))
	 {
		 strMsg.Format("Timing Error PASS at %.2f dbm",m_dMidPowerTarget);
		 TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dTERLimit.GetMax())),_T(CStr::FloatToStr(m_dTERLimit.GetMin())),_T(CStr::FloatToStr(dModValue[6])),_T("chip"),strMsg,"TimeErr")
	 } 
	 else
	 {
		 strMsg.Format("Timing Error Fail at %.2f dbm",m_dMidPowerTarget);
		 ifailflag++;
		 TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_TIMINGERR_OUTOFRANGE,_T(CStr::FloatToStr(m_dTERLimit.GetMax())),_T(CStr::FloatToStr(m_dTERLimit.GetMin())),_T(CStr::FloatToStr(dModValue[6])),_T("chip"),strMsg,"TimeErr")
	 }

	 m_iItemCode-='C';
	/* if (m_dDDPRlimit.InRange(dModValue[7]))
	 {
		 strMsg.Format("DPCCH/DPDCH Power Ratio PASS at CellPower %.2f",m_dMidPowerTarget);
		 TestPassLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dDDPRlimit.GetMax())),_T(CStr::FloatToStr(m_dDDPRlimit.GetMin())),_T(CStr::FloatToStr(dModValue[7])),_T("dB"),strMsg)
	 } 
	 else
	 {
		 strMsg.Format("DPCCH/DPDCH Power Ratio Fail at CellPower %.2f",m_dMidPowerTarget);
		 ifailflag++;
		 TestFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ORIGINOFFSET_OUTOFRANGE,_T(CStr::FloatToStr(m_dDDPRlimit.GetMax())),_T(CStr::FloatToStr(m_dDDPRlimit.GetMin())),_T(CStr::FloatToStr(dModValue[7])),_T("dB"),strMsg)
	 }*/
	 
	 if (ifailflag>0)
	 {
		 return false;
	 }

	 return true;
 }

 bool CWCDMATestMeasureLoop::CWCDMATestMaxPower()
 {
 	 int iErrorcode;
	 double dMeasMaxPower;
	 int iFailFlag=0;
	 m_iItemCode=WCDMA_MaxPower_Test_BaseItemCode;
	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestMaxPower(m_iMeasureCount,&dMeasMaxPower))!=DEVICE_SUCCESS)
	 {
		 LogTrace(MSG_ERROR,_T("IWCDMA Test Measure Max Power Fail!"))
		 m_iErrorcode=iErrorcode;
		 CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("IWCDMA Test Measure MaxPower Fail!"))
			 return false;
	 }

	 if (m_dMaxPowerLimit.InRange(dMeasMaxPower))
	 {
		 TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dMeasMaxPower)),_T("dBm"),_T("MaxPower PASS"),"MaxPower")
	 } 
	 else
	 {
		 iFailFlag++;
		 TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dMeasMaxPower)),_T("dBm"),_T("MaxPower FAIL"),"MaxPower")
	 }

	 if(!m_pPhone->IsPhoneConnected())  
	 {           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
		return false;
	 }	 
	 
	 if (iFailFlag>0)
	 {
		 return false;
	 }	 
	 return true;
 }

 bool CWCDMATestMeasureLoop::CWCDMATestACLR()
 {
    int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_ACLR_N10_Test_BaseItemCode;
	double dACLRMeasured[4];
	if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestACLR(m_iMeasureCount,dACLRMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IWCDMAACLR Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device IWCDMAACLR Fail!"))
			return false;
	}
	for (int i=0;i<4;i++)
	{
		if (dACLRMeasured[i]<m_dvACLRLimit[i])
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dvACLRLimit[i])),_T("-"),_T(CStr::FloatToStr(dACLRMeasured[i])),_T("dBc"),_T("ACLR PASS"),"ACLR")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ACLR_OUTOFRANGE,_T(CStr::FloatToStr(m_dvACLRLimit[i])),_T("-"),_T(CStr::FloatToStr(dACLRMeasured[i])),_T("dBc"),_T("ACLR FAIL"),"ACLR")
				iFailFlag++;
		}
	}
	

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;
 }
 bool CWCDMATestMeasureLoop::CWCDMATestOBW()
 {
    int iErrorcode,iFailFlag=0;
    CString strMsg;
	m_iItemCode=WCDMA_OccupiedBandWidth_Test_BaseItemCode;
	double dOBWMeasured;
	if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestOBW(m_iMeasureCount,&dOBWMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IWCDMAOBW Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device IWCDMAOBW Fail!"))
			return false;
	}

	if (m_dOBWLimit.InRange(dOBWMeasured))
	{
		 strMsg.Format("Occupied BandWidth PASS at MaxPower");
		 TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dOBWLimit.GetMax())),_T(CStr::FloatToStr(m_dOBWLimit.GetMin())),_T(CStr::FloatToStr(dOBWMeasured)),_T("MHz"),strMsg,"OBW")
	 } 
	else
	{
		 strMsg.Format("Occupied BandWidth FAIL at MaxPower");
		 iFailFlag++;
		 TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_OBW_OUTOFRANGE,_T(CStr::FloatToStr(m_dOBWLimit.GetMax())),_T(CStr::FloatToStr(m_dOBWLimit.GetMin())),_T(CStr::FloatToStr(dOBWMeasured)),_T("MHz"),strMsg,"OBW")
	 }

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;
	 
 }
 bool CWCDMATestMeasureLoop::CWCDMATestBER()
 {
    int iErrorcode,iFailFlag=0;
	m_iItemCode=WCDMA_BER_Test_BaseItemCode;
	double dBERMeasured;
	if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestBER(m_iBERSamples,m_dRxCellPower,&dBERMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IWCDMABER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device IWCDMABER Fail!"))
			return false;
	}

	 if (m_dBERLimit.InRange(dBERMeasured))
	 {
		 TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dBERLimit.GetMax())),_T(CStr::FloatToStr(m_dBERLimit.GetMin())),_T(CStr::FloatToStr(dBERMeasured)),_T("%"),_T("Bit Error Rate PASS"),"BER")
	 } 
	 else
	 {
		 iFailFlag++;
		 TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_BER_OUTOFRANGE,_T(CStr::FloatToStr(m_dBERLimit.GetMax())),_T(CStr::FloatToStr(m_dBERLimit.GetMin())),_T(CStr::FloatToStr(dBERMeasured)),_T("%"),_T("Bit Error Rate FAIL"),"BER")
	 }

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

 }
 bool CWCDMATestMeasureLoop::CWCDMATestSEMask()
 {
    int iErrorcode,iFailFlag=0;
	m_iItemCode=WCDMA_EMASK_Test_BaseItemCode;
	int iSMASK;	
	if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestSEMask(m_iMeasureCount,&iSMASK))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IWCDMASEMask Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device IWCDMASEMask Fail!"))
			return false;
	}
	
		if (0!=iSMASK)
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T("1"),_T("-"),_T("SEMASK PASS"),"SEMASK")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_SEMASK_OUTOFRANGE,_T("1"),_T("1"),_T("0"),_T("-"),_T("SEMASK FAIL"),"SEMASK")
				iFailFlag++;
		}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;
 }  
 bool CWCDMATestMeasureLoop::CWCDMATestMeasureALL(int iBand,int iULChannel,CString strTestItem)
 {
	 /*
	 A1 MinPower
	 B1 Power at TargetPower
	 C1 Mod at TargetPower
	 D1 MaxPower
	 E1 Mod at MaxPower
	 F1 ADJ at MaxPower
	 G1 OBW at MaxPower
	 H1 SMASK at MaxPower
	 I1 FER at MaxPower
	 J1 BER at MaxPower
	 K1 ILPC
	 */
	 //Error Vector Magnitude  Unit=%
	 //Peak Vector Error Unit=%
	 //Phase Error Unit=deg
	 //Magnitude Error Unit=%
	 //Origin Offset Unit=dB
	 //IQ Imbalance Unit=%
	 //Timing Error Unit=chip
	 //DPCCH/DPDCH Power Ratio Unit=dB
	 int iErrorcode,iSMASK;
	 double dMeasPower,dOBWValue,dBERValue,dFERValue;
	 double dModValue[8],dACLR[4];
	 CString strMsg;
	 int ifailflag=0;
	 m_iItemCode=WCDMA_InitWCDMATest_BaseItemCode;
	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestMeasAll(m_iMeasureCount,m_iBERSamples,m_dRxCellPower,&dMeasPower,dModValue,dACLR,&dOBWValue,&iSMASK,&dBERValue,&dFERValue))!=DEVICE_SUCCESS)
	 {
		 LogTrace(MSG_ERROR,_T("WCDMA Test Measure ALL Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("WCDMA Test Measure ALL Fail!"))
			 return false;
	 }

	 m_iItemCode=GetItemCode(6,iBand,iULChannel);

	 if (strTestItem.Find(_T("D1"))>-1)
	 {	
		 m_iItemCode+='D';
		 if (m_dMaxPowerLimit.InRange(dMeasPower))
		 {
			 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dMeasPower)),_T("dBm"),_T("MaxPower PASS "),"MaxPower")
		 } 
		 else
		 {
			 ifailflag++;
			 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dMeasPower)),_T("dBm"),_T("MaxPower FAIL"),"MaxPower")
		 }
		 m_iItemCode-='D';
	 }
	 //******Mod Analysis**********************************************************************************************************************

	 if (strTestItem.Find(_T("E1"))>-1)
	 {
			m_iItemCode+='E'; 
			 if (m_dEVMLimit.InRange(dModValue[0]))
			 {
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dEVMLimit.GetMax())),_T(CStr::FloatToStr(m_dEVMLimit.GetMin())),_T(CStr::FloatToStr(dModValue[0])),_T("%"),_T("Error Vector Magnitude PASS at MaxPower"),"EVM")
			 } 
			 else
			 {
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_EVM_OUTOFRANGE,_T(CStr::FloatToStr(m_dEVMLimit.GetMax())),_T(CStr::FloatToStr(m_dEVMLimit.GetMin())),_T(CStr::FloatToStr(dModValue[0])),_T("%"),_T("Error Vector Magnitude FAIL at MaxPower"),"EVM")
			 }

			 /*if (m_dPVELimit.InRange(dModValue[1]))
			 {
				 TestPassLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dPVELimit.GetMax())),_T(CStr::FloatToStr(m_dPVELimit.GetMin())),_T(CStr::FloatToStr(dModValue[1])),_T("%"),_T("Peak Vector Error PASS at MaxPower"))
			 } 
			 else
			 {
				 ifailflag++;
				 TestFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_EVM_OUTOFRANGE,_T(CStr::FloatToStr(m_dPVELimit.GetMax())),_T(CStr::FloatToStr(m_dPVELimit.GetMin())),_T(CStr::FloatToStr(dModValue[1])),_T("%"),_T("Peak Vector Error FAIL at MaxPower"))
			 }*/

			/* if (m_dPERLimit.InRange(dModValue[2]))
			 {
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dPERLimit.GetMax())),_T(CStr::FloatToStr(m_dPERLimit.GetMin())),_T(CStr::FloatToStr(dModValue[2])),_T("deg"),_T("Phase Error PASS at MaxPower"),"PER")
			 } 
			 else
			 {
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_PHASEERR_OUTOFRANGE,_T(CStr::FloatToStr(m_dPERLimit.GetMax())),_T(CStr::FloatToStr(m_dPERLimit.GetMin())),_T(CStr::FloatToStr(dModValue[2])),_T("deg"),_T("Phase Error FAIL at MaxPower"),"PER")
			 }*/

			 if (m_dMagERRLimit.InRange(dModValue[3]))
			 {
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dMagERRLimit.GetMax())),_T(CStr::FloatToStr(m_dMagERRLimit.GetMin())),_T(CStr::FloatToStr(dModValue[3])),_T("%"),_T("Magnitude Error PASS at MaxPower"),"Mag")
			 } 
			 else
			 {
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_MAGTDERR_OUTOFRANGE,_T(CStr::FloatToStr(m_dMagERRLimit.GetMax())),_T(CStr::FloatToStr(m_dMagERRLimit.GetMin())),_T(CStr::FloatToStr(dModValue[3])),_T("%"),_T("Magnitude Error FAIL at MaxPower"),"Mag")
			 }

			 if (m_dOOLimit.InRange(dModValue[4]))
			 {
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dOOLimit.GetMax())),_T(CStr::FloatToStr(m_dOOLimit.GetMin())),_T(CStr::FloatToStr(dModValue[4])),_T("dB"),_T("Origin Offset PASS at MaxPower"),"OFS")
			 } 
			 else
			 {
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ORIGINOFFSET_OUTOFRANGE,_T(CStr::FloatToStr(m_dOOLimit.GetMax())),_T(CStr::FloatToStr(m_dOOLimit.GetMin())),_T(CStr::FloatToStr(dModValue[4])),_T("dB"),_T("Origin Offset FAIL at MaxPower"),"OFS")
			 } 
			/* if (m_dIQILimit.InRange(dModValue[5]))
			 {
				 TestPassLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dIQILimit.GetMax())),_T(CStr::FloatToStr(m_dIQILimit.GetMin())),_T(CStr::FloatToStr(dModValue[5])),_T("%"),_T("IQ Imbalance PASS at MaxPower"))
			 } 
			 else
			 {
				 ifailflag++;
				 TestFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ORIGINOFFSET_OUTOFRANGE,_T(CStr::FloatToStr(m_dIQILimit.GetMax())),_T(CStr::FloatToStr(m_dIQILimit.GetMin())),_T(CStr::FloatToStr(dModValue[5])),_T("%"),_T("IQ Imbalance FAIL at MaxPower"))
			 }*/

			 if (m_dTERLimit.InRange(dModValue[6]))
			 {
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dTERLimit.GetMax())),_T(CStr::FloatToStr(m_dTERLimit.GetMin())),_T(CStr::FloatToStr(dModValue[6])),_T("chip"),_T("Timing Error PASS at MaxPower"),"TimeErr")
			 } 
			 else
			 {
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_TIMINGERR_OUTOFRANGE,_T(CStr::FloatToStr(m_dTERLimit.GetMax())),_T(CStr::FloatToStr(m_dTERLimit.GetMin())),_T(CStr::FloatToStr(dModValue[6])),_T("chip"),_T("Timing Error FAIL at MaxPower"),"TimeErr")
			 }

			/* if (m_dDDPRlimit.InRange(dModValue[7]))
			 {
				 TestPassLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dDDPRlimit.GetMax())),_T(CStr::FloatToStr(m_dDDPRlimit.GetMin())),_T(CStr::FloatToStr(dModValue[7])),_T("dB"),_T("DPCCH/DPDCH Power Ratio PASS at MaxPower"))
			 } 
			 else
			 {
				 ifailflag++;
				 TestFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ORIGINOFFSET_OUTOFRANGE,_T(CStr::FloatToStr(m_dDDPRlimit.GetMax())),_T(CStr::FloatToStr(m_dDDPRlimit.GetMin())),_T(CStr::FloatToStr(dModValue[7])),_T("dB"),_T("DPCCH/DPDCH Power Ratio FAIL at MaxPower"))
			 }*/
			m_iItemCode-='E';
	 }
//********ACLR*********************************************************************************************************************************
/*	 if(strTestItem.Find(_T("F1"))>-1)
	 {

			m_iItemCode+='F';
			 if (dACLR[0]<m_dACLRLimit[0])
			 {
				 strMsg.Format("ACLR -10 PASS at MaxPower");
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dACLRLimit[0])),_T("-9999"),_T(CStr::FloatToStr(dACLR[0])),_T("dB"),strMsg,"ACLR_N10")
			 } 
			 else
			 {
				 strMsg.Format("ACLR -10 FAIL at MaxPower"); 
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ACLR_OUTOFRANGE,_T(CStr::FloatToStr(m_dACLRLimit[0])),_T("-9999"),_T(CStr::FloatToStr(dACLR[0])),_T("dB"),strMsg,"ACLR_N10")
			 }
			 if (dACLR[1]<m_dACLRLimit[1])
			 {
				 strMsg.Format("ACLR -5 PASS at MaxPower");
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dACLRLimit[1])),_T("-9999"),_T(CStr::FloatToStr(dACLR[1])),_T("dB"),strMsg,"ACLR_N5")
			 } 
			 else
			 {
				 strMsg.Format("ACLR -5 FAIL at MaxPower");
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ACLR_OUTOFRANGE,_T(CStr::FloatToStr(m_dACLRLimit[1])),_T("-9999"),_T(CStr::FloatToStr(dACLR[1])),_T("dB"),strMsg,"ACLR_N5")
			 }
			 if (dACLR[2]<m_dACLRLimit[2])
			 {
				 strMsg.Format("ACLR +5 PASS at MaxPower");
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dACLRLimit[2])),_T("-9999"),_T(CStr::FloatToStr(dACLR[2])),_T("dB"),strMsg,"ACLR_P5")
			 } 
			 else
			 {
				 strMsg.Format("ACLR +10 FAIL at MaxPower");
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ACLR_OUTOFRANGE,_T(CStr::FloatToStr(m_dACLRLimit[2])),_T("-9999"),_T(CStr::FloatToStr(dACLR[2])),_T("dB"),strMsg,"ACLR_P5")
			 }
			 if (dACLR[3]<m_dACLRLimit[3])
			 {
				 strMsg.Format("ACLR +10 PASS at MaxPower");
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dACLRLimit[3])),_T("-9999"),_T(CStr::FloatToStr(dACLR[3])),_T("dB"),strMsg,"ACLR_P10")
			 } 
			 else
			 {
				 strMsg.Format("ACLR +10 FAIL at MaxPower");
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_ACLR_OUTOFRANGE,_T(CStr::FloatToStr(m_dACLRLimit[3])),_T("-9999"),_T(CStr::FloatToStr(dACLR[3])),_T("dB"),strMsg,"ACLR_P10")
			 }
			 m_iItemCode-='F';
	 }
*/
	 //****OBW*******************************************************************************************************************
	 if (strTestItem.Find(_T("G1"))>-1)
	 {
			m_iItemCode+='G';
			 if (m_dOBWLimit.InRange(dOBWValue))
			 {
				 strMsg.Format("Occupied BandWidth PASS at MaxPower");
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dOBWLimit.GetMax())),_T(CStr::FloatToStr(m_dOBWLimit.GetMin())),_T(CStr::FloatToStr(dOBWValue)),_T("MHz"),strMsg,"OBW")
			 } 
			 else
			 {
				 strMsg.Format("Occupied BandWidth FAIL at MaxPower");
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_OBW_OUTOFRANGE,_T(CStr::FloatToStr(m_dOBWLimit.GetMax())),_T(CStr::FloatToStr(m_dOBWLimit.GetMin())),_T(CStr::FloatToStr(dOBWValue)),_T("MHz"),strMsg,"OBW")
			 }
			 m_iItemCode-='G';
	 }

	 //****SMASK*******************************************************************************************************************
	 if(strTestItem.Find(_T("H1"))>-1)
	 {
		 m_iItemCode+='H';
			 if (iSMASK==1)
			 {
				 strMsg.Format("SMASK PASS at MaxPower");
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T("1"),_T("1"),_T(CStr::FloatToStr(iSMASK)),_T("-"),strMsg,"SMASK")
			 } 
			 else
			 {
				 strMsg.Format("SMASK FAIL at MaxPower");
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_SEMASK_OUTOFRANGE,_T("1"),_T("1"),_T(CStr::FloatToStr(iSMASK)),_T("-"),strMsg,"SMASK")
			 }
			 m_iItemCode-='H';
	 }

	  //****FER*******************************************************************************************************************
	 if(strTestItem.Find(_T("I1"))>-1)
	 {
		 m_iItemCode+='I';
			 if (m_dFERLimit.InRange(dFERValue))
			 {
				 strMsg.Format("Frequency Error PASS at MaxPower");
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dFERLimit.GetMax())),_T(CStr::FloatToStr(m_dFERLimit.GetMin())),_T(CStr::FloatToStr(dFERValue)),_T("Hz"),strMsg,"FER")
			 } 
			 else
			 {
				 strMsg.Format("Frequency Error FAIL at MaxPower");
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_dFERLimit.GetMax())),_T(CStr::FloatToStr(m_dFERLimit.GetMin())),_T(CStr::FloatToStr(dBERValue)),_T("Hz"),strMsg,"FER")
			 }
			 m_iItemCode-='I';
	 }
	
	  //****BER*******************************************************************************************************************
	 if(strTestItem.Find(_T("J1"))>1)
	 {
		 m_iItemCode+='J';
			 if (m_dBERLimit.InRange(dBERValue))
			 {
				 strMsg.Format("Bit Error Rate PASS at %.2f",m_dRxCellPower);
				 TestPassLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dBERLimit.GetMax())),_T(CStr::FloatToStr(m_dBERLimit.GetMin())),_T(CStr::FloatToStr(dBERValue)),_T("%"),strMsg,"BER")
			 } 
			 else
			 {
				 strMsg.Format("Bit Error Rate FAIL at %.2f",m_dRxCellPower);
				 ifailflag++;
				 TestFailLogEx(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_BER_OUTOFRANGE,_T(CStr::FloatToStr(m_dBERLimit.GetMax())),_T(CStr::FloatToStr(m_dBERLimit.GetMin())),_T(CStr::FloatToStr(dBERValue)),_T("%"),strMsg,"BER")
			 }
			 m_iItemCode-='J';
	 }

	 if (ifailflag>0)
	 {
		 return false;
	 }
	 return true;
 }
  bool CWCDMATestMeasureLoop::CWCDMATestILPC()
  {
		  int iErrorcode;
		  int iResultStepE=0,iResultStepF=0;
		  CString strMsg;
		  int iFailFlag=0;
		  m_iItemCode=WCDMA_InitWCDMATest_BaseItemCode;
		  m_iItemCode+='K';	      
		
		  if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestILPC(&iResultStepE,&iResultStepF))!=DEVICE_SUCCESS)
		  {
			  LogTrace(MSG_ERROR,_T("WCDMA Test Measure ILPC Fail!"))
				  m_iErrorcode=iErrorcode;
			  CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Test Measure ILPC Fail!"))
				  return false;
		  }
		  if (1!=iResultStepE||1!=iResultStepF)
		  {
			  TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ILPC_F_OUTOFRANGE,_T("1"),_T("1"),_T("0"),_T("-"),_T("ILPC Fail"),"ILPC")
			 m_iItemCode-='K';
			  return false;
		  }
		  else
		  {
			  TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T("0"),_T("-"),_T("ILPC Pass"),"ILPC")
			m_iItemCode-='K';
			  return true;

		  }
		  
         /* if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestILPC_FailSlot(&iResultStepE,&iResultStepF,dFailSLots_E,dFailSlots_F,&iNUME,&iNUMF))!=DEVICE_SUCCESS)
		  {
			  LogTrace(MSG_ERROR,_T("WCDMA Test Measure ILPC Fail!"))
				  m_iErrorcode=iErrorcode;
			  CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Test Measure ILPC Fail!"))
				  return false;
		  }

		  if (iResultStepE!=1 || iResultStepF!=1)
		  {
			      if(iResultStepE!=1)
				  {
					  strMsg.Format("ILPC E: FAIL_Range=%d, %d Slots Absolute Power is :",iNUME/5,iNUME);
					  LogTrace(MSG_MID,strMsg)
					  
					  for(int i=0;i<iNUME;++i)
					  {
						  strMsg.Format("SLot Num=%d Power=%.2f",i,dFailSLots_E[i]);
                           LogTrace(MSG_MID,strMsg)
					  }
				  }

				  if(iResultStepF!=1)
				  {
                     strMsg.Format("ILPC F: FAIL_Range=%d, %d Slots Absolute Power is :",iNUMF/5,iNUMF);
					  LogTrace(MSG_MID,strMsg)
					  
					  for(int i=0;i<iNUMF;++i)
					  {
						  strMsg.Format("SLot Num=%d Power=%.2f",i,dFailSlots_F[i]);
                           LogTrace(MSG_MID,strMsg)
					  }
				  }
			       if(m_iIsReFineILPC)
				   {
			  
					  if(!CWCDMATestReTestILPC(iResultStepE,iResultStepF,dFailSLots_E,dFailSlots_F,iNUME,iNUMF))
						  return false;
				   }

				  if(!CWCDMATestReCALL())
				{
					 LogTrace(MSG_ERROR,_T("ILPC ReCall  Fail!"))
						m_iErrorcode=iErrorcode;
						CalFailLog(_T("_"),_T("_"),iErrorcode," ILPC ReCall  Fail!");
						return false;
				}
				  
				if(!CWCDMATestHandOver())
				{
					  LogTrace(MSG_ERROR,_T("ILPC ReHandOver Fail!"))
						m_iErrorcode=iErrorcode;
						CalFailLog(_T("_"),_T("_"),iErrorcode," ILPC ReHandOver  Fail!");
						return false;
				}

				if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestILPC(&iResultStepE,&iResultStepF))!=DEVICE_SUCCESS)
				{
					  LogTrace(MSG_ERROR,_T("WCDMA Test Measure ILPC Fail!"))
						  m_iErrorcode=iErrorcode;
					  CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Test Measure ILPC Fail!"))
						  return false;
				}
			    if (iResultStepE==1)
			    {				  
				     TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T(CStr::IntToStr(iResultStepE)),_T("-"),_T("ILPC Step E Pass"),"ILPC_E")
			    } 
			    else
			    {
				     iFailFlag++;
				     TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ILPC_E_OUTOFRANGE,_T("1"),_T("1"),_T(CStr::IntToStr(iResultStepF)),_T("-"),_T("ILPC Step E Fail"),"ILPC_E")
			    }
			    if (iResultStepF==1)
			    {
				    TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T(CStr::IntToStr(iResultStepF)),_T("-"),_T("ILPC Step F Pass"),"ILPC_F")
			    } 
			    else
			    {
				    iFailFlag++;
				    TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ILPC_F_OUTOFRANGE,_T("1"),_T("1"),_T(CStr::IntToStr(iResultStepF)),_T("-"),_T("ILPC Step F Fail"),"ILPC_F")
			    }
			    m_iItemCode-='K';			
			    if (iFailFlag>0)
			    {
				     return false;
			    }					  
		  } 
		  else
		  {
			    TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T(CStr::IntToStr(iResultStepE)),_T("-"),_T("ILPC Step E Pass"),"ILPC_E")
		      TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T(CStr::IntToStr(iResultStepF)),_T("-"),_T("ILPC Step F Pass"),"ILPC_F")
			    m_iItemCode-='K';
			    return true;
		  }	 */ 
	    return true;
  }

  bool CWCDMATestMeasureLoop::CWCDMATestRSCP()
  {
	  int iErrorcode;
	  CString strMsg;
	  int iFailFlag=0;
	  double dResult;
	  m_iItemCode=WCDMA_InitWCDMATest_BaseItemCode;
	  m_iItemCode+='L';
	  for (int i=0;i<m_dRSCP_CellPower.size();i++)
	  {
		  if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestCPICH_RSCP(m_dRSCP_CellPower[i],&dResult))!=DEVICE_SUCCESS)
		  {
			  LogTrace(MSG_ERROR,_T("WCDMA Test Measure RSCP Fail!"))
				  m_iErrorcode=iErrorcode;
			  CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Test Measure RSCP Fail!"))
				  return false;
		  }
		  strMsg.Format("CPICH_RSCP at %.2fdBm",m_dRSCP_CellPower[i]);
		  if (dResult>=m_dRSCP_LLimit[i]||dResult<=m_dRSCP_HLimit[i])
		  {
			  
			  TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dRSCP_HLimit[i])),_T(CStr::FloatToStr(m_dRSCP_LLimit[i])),_T(CStr::FloatToStr(dResult)),_T("dBm"),strMsg,"RSCP")
		  } 
		  else
		  {
			  iFailFlag++;
			  TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_RSCP_OUTOFRANGE,_T(CStr::FloatToStr(m_dRSCP_HLimit[i])),_T(CStr::FloatToStr(m_dRSCP_LLimit[i])),_T(CStr::FloatToStr(dResult)),_T("dBm"),strMsg,"RSCP")
		  }

	  }
	  m_iItemCode-='L';
	  if (iFailFlag>0)
	  {
		  return false;
	  }
	  return true;

  }
  bool CWCDMATestMeasureLoop::CWCDMATestReCALL()
  {

    if(m_pReStartCall==NULL)
	{
       LogTrace(MSG_ERROR,_T("ReCall Object not passed by"))
		   return false;
	}

     m_pFuncWCDMATestDev->Deivce_Exit();

	 m_pPhone->FTM_WCDMA_EndCall();

	 m_pPhone->CloseComport();


	 if(!m_pReStartCall->Handle())
		return false;

	  
    return true;
  }
  bool CWCDMATestMeasureLoop::CWCDMATestReTestILPC(int iResult_E,int iResult_F,double * dFailSLots_E,double * dFailSlots_F,int iFailSlotNum_E,int iFailSlotNum_F)
  {
	  

	  int iErrorcode;
	  CString strMsg;
	  unsigned short iPowerNV[6];
	  double dPowerCal[6];
	  short    iCompenOldValue[6];
	  unsigned char uiNVValue[128]={0};
      double  dCalFailSLots_E[6];
	  double  dCalFailSlots_F[6];
      bool bIsSwitch_E=false;
      bool bIsSwitch_F=false;
      int  iDiffValue=0;
      int  iFactor;
	  if(m_iIs6285Plat)
         iFactor=12;
	  else
		  iFactor=10;
	  for(int i=0;i<6;++i)
	  {

		   if((iErrorcode=m_pPhone->ReadNV(m_vFALLRISE_NVID[i],(unsigned char*)uiNVValue,128))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Read NV :%d  Fail!",m_vFALLRISE_NVID[i]);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			return false;
		}
        

		iPowerNV[i]=*(unsigned short*)&uiNVValue[0];
		
		    if((iErrorcode=m_pPhone->ReadNV(m_vCompenNV_ID[i],(unsigned char*)&uiNVValue,128))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Read NV :%d  Fail!",m_vCompenNV_ID[i]);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			return false;
		}
			iCompenOldValue[i]=*(short*)&uiNVValue[0];
		if(m_iIs6285Plat)
        dPowerCal[i]=iPowerNV[i]/(1024/85.3)+(85.3/2-57.4);
		else
        dPowerCal[i]=iPowerNV[i]/10+(51.2-70);

		strMsg.Format("RISE_FALL_NVID=%d NVValue=%d Calculate Power=%.2f ",m_vFALLRISE_NVID[i],iPowerNV[i],dPowerCal[i]);
        LogTrace(MSG_LOW,strMsg)

	  }

     
	 
      if(!iResult_E)
	  {
                int iIndexUse;
		       if(dFailSLots_E[4]<dPowerCal[0]) //R1_R0
			   {
				   if(dFailSLots_E[2]>dPowerCal[0])
				   {
                       dCalFailSLots_E[0]=dFailSLots_E[1];
                       dCalFailSLots_E[1]=dFailSLots_E[2];
					   dCalFailSLots_E[2]=dFailSLots_E[3];
				   }
				   else
				   {
					   for(int i=0;i<3;++i)
					   {
						   if(dFailSLots_E[i]>dPowerCal[0] && dFailSLots_E[i+1] <dPowerCal[0])
						   {
								dCalFailSLots_E[0]=dFailSLots_E[i];
								dCalFailSLots_E[1]=dFailSLots_E[i+1];
								dCalFailSLots_E[2]=dFailSLots_E[i+2];
								bIsSwitch_E=true;
								break;

						   }
					   }
				   }
                
                iIndexUse=0;
			   }

			   else if(dFailSLots_E[0]>dPowerCal[2]) //R2_R1
			   {
					 if(dFailSLots_E[2]>dPowerCal[2])
					   {
						   dCalFailSLots_E[0]=dFailSLots_E[1];
						   dCalFailSLots_E[1]=dFailSLots_E[2];
						   dCalFailSLots_E[2]=dFailSLots_E[3];
					   }
					 else
					 {
						 for(int i=0;i<3;++i)
					   {
						   if(dFailSLots_E[i]>dPowerCal[2] && dFailSLots_E[i+1] <dPowerCal[2])
						   {
								dCalFailSLots_E[0]=dFailSLots_E[i];
								dCalFailSLots_E[1]=dFailSLots_E[i+1];
								dCalFailSLots_E[2]=dFailSLots_E[i+2];
								bIsSwitch_E=true;
								break;

						   }
					   }
					 }

                   iIndexUse=2;
			   }
                  if(bIsSwitch_E)
				  {
					  strMsg.Format("ILPC_E Selected Points :");
                      LogTrace(MSG_LOW,strMsg)
                     
						  strMsg.Format("%.2f  %.2f  %.2f ",dCalFailSLots_E[0],dCalFailSLots_E[1],dCalFailSLots_E[2]);
                           LogTrace(MSG_LOW,strMsg)
					
					
                      int iCompenValue=0;
					  double dDistDiff;
					  double dDist=(dCalFailSLots_E[0]-dCalFailSLots_E[2])/2;
					  double dDist2Slots=dCalFailSLots_E[0]-dCalFailSLots_E[1];
					 
					  dDistDiff=dCalFailSLots_E[0]-dCalFailSLots_E[1]-dDist;
					  
                      if(dDistDiff>0)
						  iCompenValue+=iCompenOldValue[iIndexUse]+int(dDistDiff*iFactor+0.5);
					   else
						 iCompenValue+=iCompenOldValue[iIndexUse]+int(dDistDiff*iFactor-0.5); 


					    strMsg.Format("Need Tuned DeltaPower=%.2f  CompenNVID=%d OldCompenNVValue=%d FineTunedNVValue=%d",dDistDiff,m_vCompenNV_ID[iIndexUse],iCompenOldValue[iIndexUse],iCompenValue);
                        LogTrace(MSG_LOW,strMsg)
					   if((iErrorcode=m_pPhone->WriteNV(m_vCompenNV_ID[iIndexUse],(unsigned char*)&iCompenValue,4))!=PHONE_SUCCESS)
						{ 
							strMsg.Format("Phone Read NV :%d  Fail!",m_vCompenNV_ID[iIndexUse]);
							LogTrace(MSG_ERROR,strMsg)
							m_iErrorcode=iErrorcode;
							return false;
						}
					   if(iIndexUse==2)
					   {
							  if((iErrorcode=m_pPhone->WriteNV(m_vCompenNV_ID[iIndexUse+2],(unsigned char*)&iCompenValue,4))!=PHONE_SUCCESS)
							{ 
								strMsg.Format("Phone Read NV :%d  Fail!",m_vCompenNV_ID[iIndexUse+2]);
								LogTrace(MSG_ERROR,strMsg)
								m_iErrorcode=iErrorcode;
								return false;
							}
					   }
				  }
			
               bIsSwitch_E=false;
			   if(iFailSlotNum_E==10)
		      
			   {
						if(dFailSLots_E[9]<dPowerCal[0]) //R1_R0
					   {
						  if(dFailSLots_E[7]>dPowerCal[2])
							   {
								   dCalFailSLots_E[0]=dFailSLots_E[6];
								   dCalFailSLots_E[1]=dFailSLots_E[7];
								   dCalFailSLots_E[2]=dFailSLots_E[8];
							   }
							else
							{
							   for(int i=5;i<9;++i)
							   {
								   if(dFailSLots_E[i]>dPowerCal[0] && dFailSLots_E[i+1] <dPowerCal[0])
								   {
										dCalFailSLots_E[0]=dFailSLots_E[i];
										dCalFailSLots_E[1]=dFailSLots_E[i+1];
										dCalFailSLots_E[2]=dFailSLots_E[i+2];
										bIsSwitch_E=true;
										break;

								   }
								   
							   }
							}

							  if(bIsSwitch_E)
							  {
								iIndexUse=0;
	      
								  strMsg.Format("ILPC_E Selected Points :");
								  LogTrace(MSG_LOW,strMsg)
								
									  strMsg.Format("%.2f  %.2f  %.2f ",dCalFailSLots_E[0],dCalFailSLots_E[1],dCalFailSLots_E[2]);
									   LogTrace(MSG_LOW,strMsg)
								
							  int iCompenValue=0;
							  double dDistDiff;
							  double dDist=(dCalFailSLots_E[0]-dCalFailSLots_E[2])/2;
							  double dDist2Slots=dCalFailSLots_E[0]-dCalFailSLots_E[1];
						 
							  dDistDiff=dCalFailSLots_E[0]-dCalFailSLots_E[1]-dDist;
						 
							
							     if(dDistDiff>0)
								  iCompenValue+=iCompenOldValue[2]+int(dDistDiff*iFactor+0.5);
							   else
								 iCompenValue+=iCompenOldValue[2]+int(dDistDiff*iFactor-0.5); 

							 
							   strMsg.Format("Need Tuned DeltaPower=%.2f  CompenNVID=%d OldCompenNVValue=%d FineTunedNVValue=%d",dDistDiff,m_vCompenNV_ID[iIndexUse],iCompenOldValue[iIndexUse],iCompenValue);
                               LogTrace(MSG_LOW,strMsg)

							   if((iErrorcode=m_pPhone->WriteNV(m_vCompenNV_ID[0],(unsigned char*)&iCompenValue,4))!=PHONE_SUCCESS)
								{ 
									strMsg.Format("Phone Read NV :%d  Fail!",m_vCompenNV_ID[0]);
									LogTrace(MSG_ERROR,strMsg)
									m_iErrorcode=iErrorcode;
									return false;
								}
						   }

			

					   }
                  
			   } 
		    
	  }
	  
	  if(!iResult_F)
	  {

		       int iIndexUse;
		       if(dFailSlots_F[0]<dPowerCal[1]) //R0_R1
			   {
				   if(dFailSlots_F[2]<dPowerCal[1])
				   {
                                dCalFailSlots_F[0]=dFailSlots_F[1];
								dCalFailSlots_F[1]=dFailSlots_F[2];
								dCalFailSlots_F[2]=dFailSlots_F[3];   
				   }
				   else
				   {
						for(int i=0;i<3;++i)
					   {
						   if(dFailSlots_F[i+1]>dPowerCal[1] && dFailSlots_F[i] <dPowerCal[1])
						   {
							   
								dCalFailSlots_F[0]=dFailSlots_F[i];
								dCalFailSlots_F[1]=dFailSlots_F[i+1];
								dCalFailSlots_F[2]=dFailSlots_F[i+2];
								bIsSwitch_F=true;
								break;

						   }
					   }
				   }
                   iIndexUse=1;

			   }
			   else if(dFailSlots_F[4]>dPowerCal[3]) //R1_R2
			   {
				  if(dFailSlots_F[2]<dPowerCal[3])
				   {
                         dCalFailSlots_F[0]=dFailSlots_F[1];
					     dCalFailSlots_F[1]=dFailSlots_F[2];
						 dCalFailSlots_F[2]=dFailSlots_F[3];   
				   }
				  else
				  {
						for(int i=0;i<3;++i)
					   {
						   if(dFailSlots_F[i+1]>dPowerCal[3] && dFailSlots_F[i] <dPowerCal[3])
						   {
								dCalFailSlots_F[0]=dFailSlots_F[i];
								dCalFailSlots_F[1]=dFailSlots_F[i+1];
								dCalFailSlots_F[2]=dFailSlots_F[i+2];
								bIsSwitch_F=true;
								break;

						   }
					   }
				  }
                   iIndexUse=3;
			   }



		       if(bIsSwitch_F)
			   {
				     strMsg.Format("ILPC_F Selected Points :");
                      LogTrace(MSG_LOW,strMsg)
                   
						  strMsg.Format("%.2f  %.2f  %.2f ",dCalFailSlots_F[0],dCalFailSlots_F[1],dCalFailSlots_F[2]);
                           LogTrace(MSG_LOW,strMsg)
					 
					  int iCompenValue=0;
                        double dDistDiff;
					  double dDist=(dCalFailSlots_F[2]-dCalFailSlots_F[0])/2;
					  double dDis2Slots=dCalFailSlots_F[1]-dCalFailSlots_F[0];
					
                      dDistDiff=dDist-dDis2Slots;
					  

					     if(dDistDiff>0)
						  iCompenValue+=iCompenOldValue[iIndexUse]+int(dDistDiff*iFactor+0.5);
					   else
						 iCompenValue+=iCompenOldValue[iIndexUse]+int(dDistDiff*iFactor-0.5); 

					   strMsg.Format("Need Tuned DeltaPower=%.2f  CompenNVID=%d OldCompenNVValue=%d FineTunedNVValue=%d",dDistDiff,m_vCompenNV_ID[iIndexUse],iCompenOldValue[iIndexUse],iCompenValue);
                        LogTrace(MSG_LOW,strMsg)

					   if((iErrorcode=m_pPhone->WriteNV(m_vCompenNV_ID[iIndexUse],(unsigned char*)&iCompenValue,4))!=PHONE_SUCCESS)
						{ 
							strMsg.Format("Phone Read NV :%d  Fail!",m_vCompenNV_ID[iIndexUse]);
							LogTrace(MSG_ERROR,strMsg)
							m_iErrorcode=iErrorcode;
							return false;
						}

					     if(iIndexUse==3)
					   {
							  if((iErrorcode=m_pPhone->WriteNV(m_vCompenNV_ID[iIndexUse+2],(unsigned char*)&iCompenValue,4))!=PHONE_SUCCESS)
							{ 
								strMsg.Format("Phone Read NV :%d  Fail!",m_vCompenNV_ID[iIndexUse+2]);
								LogTrace(MSG_ERROR,strMsg)
								m_iErrorcode=iErrorcode;
								return false;
							}
					   }
			   }
			   bIsSwitch_F=false;
				 
			 
			   if(iFailSlotNum_F==10)
			   {
                   if(dFailSlots_F[9]>dPowerCal[3])
				  {
					   if(dFailSlots_F[7]<dPowerCal[3])
					   {
							 dCalFailSlots_F[0]=dFailSlots_F[6];
							 dCalFailSlots_F[1]=dFailSlots_F[7];
							 dCalFailSlots_F[2]=dFailSlots_F[8];   
					   }
						 else
						 {

							 for(int i=5;i<9;++i)
								   {
									   if(dFailSlots_F[i]<dPowerCal[3] && dFailSlots_F[i+1] >dPowerCal[3])
									   {
											dCalFailSlots_F[0]=dFailSlots_F[i];
											dCalFailSlots_F[1]=dFailSlots_F[i+1];
											dCalFailSlots_F[2]=dFailSlots_F[i+2];
											bIsSwitch_F=true;
											break;

									   }
								   }
						 }

						 if(bIsSwitch_F)
						 {

								  strMsg.Format("ILPC_F Selected Points :");
						  LogTrace(MSG_LOW,strMsg)
						 
							  strMsg.Format("%.2f  %.2f  %.2f ",dCalFailSlots_F[0],dCalFailSlots_F[1],dCalFailSlots_F[2]);
							   LogTrace(MSG_LOW,strMsg)
						 
							 int iCompenValue=0;
								double dDistDiff;
							  double dDist=(dCalFailSlots_F[2]-dCalFailSlots_F[0])/2;
							  double dDis2Slots=dCalFailSlots_F[1]-dCalFailSlots_F[0];
								dDistDiff=dDist-dDis2Slots;

							    if(dDistDiff>0)
							  iCompenValue+=iCompenOldValue[3]+int(dDistDiff*iFactor+0.5);
						   else
							 iCompenValue+=iCompenOldValue[3]+int(dDistDiff*iFactor-0.5); 
							   strMsg.Format("Need Tuned DeltaPower=%.2f  CompenNVID=%d OldCompenNVValue=%d FineTunedNVValue=%d",dDistDiff,m_vCompenNV_ID[iIndexUse],iCompenOldValue[iIndexUse],iCompenValue);
                               LogTrace(MSG_LOW,strMsg)
							   if((iErrorcode=m_pPhone->WriteNV(m_vCompenNV_ID[3],(unsigned char*)&iCompenValue,4))!=PHONE_SUCCESS)
								{ 
									strMsg.Format("Phone Read NV :%d  Fail!",m_vCompenNV_ID[3]);
									LogTrace(MSG_ERROR,strMsg)
									m_iErrorcode=iErrorcode;
									return false;
								}

								if((iErrorcode=m_pPhone->WriteNV(m_vCompenNV_ID[5],(unsigned char*)&iCompenValue,4))!=PHONE_SUCCESS)
								{ 
									strMsg.Format("Phone Read NV :%d  Fail!",m_vCompenNV_ID[5]);
									LogTrace(MSG_ERROR,strMsg)
									m_iErrorcode=iErrorcode;
									return false;
								}
						 }


				  }
			   }


	  }


	    /*LogTrace(MSG_MID,_T(" Write EFS !"))
		if((iErrorcode=m_pPhone->WriteEFS(30000))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone WriteEFS Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone WriteEFS Fail!");
			return false;
	}
    */

/*
	if((iErrorcode=m_pPhone->ReloadNV())!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Reload NV Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Reload NV Fail!");
			return false;
	}*/

   

	  return true;
  }
  bool CWCDMATestMeasureLoop::CWCDMANSTestRX()
  {
	  int iErrorcode;
	  CString strMsg;
	  int iFailFlag=0;
	  double dBER=1,dRXPower=0;
	  m_iItemCode=WCDMA_InitWCDMATest_BaseItemCode;
	  m_iItemCode+='M';
/*
	  if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestSetPower(m_dRxCellPower,25,1))!=DEVICE_SUCCESS)
	  {
		  LogTrace(MSG_ERROR,_T("WCDMA NS Test Set Power Fail!"))
			  m_iErrorcode=iErrorcode;
		  CalFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("SetPower Fail!"))
			  return false;
	  }
	  if((iErrorcode=m_pPhone->FTM_WCDMA_Measure_BER(&dBER))!=PHONE_SUCCESS)
	  {           
		  LogTrace(MSG_ERROR,_T("WCDMA Measure BER Fail!"))
			  m_iErrorcode=iErrorcode;
		   CalFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("WCDMA Measure BER Fail!"))
			  return false;
	  }
	  
	  if (m_dBERLimit.InRange(dBER))
	  {
		  strMsg.Format("BER Pass at %.2f dBm",m_dRxCellPower);
		  TestPassLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dBERLimit.GetMax())),_T(CStr::FloatToStr(m_dBERLimit.GetMin())),_T(CStr::FloatToStr(dBER)),_T("%"),strMsg)
	  } 
	  else
	  {
		  strMsg.Format("BER Fail at %.2f",m_dRxCellPower);
		  iFailFlag++;
		  TestFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_BER_OUTOFRANGE,_T(CStr::FloatToStr(m_dBERLimit.GetMax())),_T(CStr::FloatToStr(m_dBERLimit.GetMin())),_T(CStr::FloatToStr(dBER)),_T("%"),strMsg)
	  }
*/

	  for (int i=0;i<m_dRSCP_CellPower.size();i++)
	  {
		  if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestSetPower(m_dRSCP_CellPower[i],25,1))!=DEVICE_SUCCESS)
		  {
			  LogTrace(MSG_ERROR,_T("WCDMA SetPower Fail! "))
				  m_iErrorcode=iErrorcode;
			  CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA SetPower Fail!"))
				  return false;
		  }
		  Sleep(2000);

		  if((iErrorcode=m_pPhone->FTM_WCDMA_Measure_RXLV(&dRXPower,m_iRXScaleFactor,m_dMinRXPower))!=PHONE_SUCCESS)
		  {           
			  LogTrace(MSG_ERROR,_T("WCDMA Measure RXLV Fail!"))
				  m_iErrorcode=iErrorcode;
			  CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("WCDMA Measure RXLV Fail!"))
				  return false;
		  }
		  strMsg.Format("CPICH_RSCP at %.2fdBm",m_dRSCP_CellPower[i]);
		  if (dRXPower>=m_dRSCP_LLimit[i]&&dRXPower<=m_dRSCP_HLimit[i])
		  {

			  TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dRSCP_HLimit[i])),_T(CStr::FloatToStr(m_dRSCP_LLimit[i])),_T(CStr::FloatToStr(dRXPower)),_T("dBm"),strMsg,"RxPower")
		  } 
		  else
		  {
			  iFailFlag++;
			  TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_RSCP_OUTOFRANGE,_T(CStr::FloatToStr(m_dRSCP_HLimit[i])),_T(CStr::FloatToStr(m_dRSCP_LLimit[i])),_T(CStr::FloatToStr(dRXPower)),_T("dBm"),strMsg,"RxPower")
		  }

	  }
	  m_iItemCode-='M';
	  if (iFailFlag>0)
	  {
		  return false;
	  }
	

	  return true;
  }

  int CWCDMATestMeasureLoop::GetItemCode(int nMode,int Band,int Channel)
  {
	  int nItemCode=WCDMA_InitWCDMATest_BaseItemCode;
	  //nItemCode+=nMode*100000;

	  switch(Band)
	  {
	  case WCDMA_850_BAND_ID:
		  nItemCode+=1*10000;
		  break;
	  case WCDMA_900_BAND_ID:
		  nItemCode+=2*10000;
		  break;
	  case WCDMA_1500_BAND_ID:
		  nItemCode+=3*10000;
		  break;
	  case WCDMA_AWS_BAND_ID:
		  nItemCode+=4*10000;
		  break;
	  case WCDMA_1750_BAND_ID:
		  nItemCode+=5*10000;
		  break;
	  case WCDMA_PCS_BAND_ID:
		  nItemCode+=6*10000;
		  break;
	  case WCDMA_IMT_BAND_ID:
		  nItemCode+=7*10000;
		  break;

	  default:
		  return -1;
	  }

	  nItemCode+=CWCDMABandInfo::GetChannelType(Band,Channel)*1000;


	  return nItemCode;
  }