#include "stdafx.h"
#include "CDMAXOCAL.h"
RF_IMPLEMENT_DYNCREATE(CCDMAXOCalibration)

CCDMAXOCalibration::CCDMAXOCalibration()
{
	m_mapClassFunc[_T("CDMAXOCalMainFunc")]=&CXOCalibration::CXOCalibrationMainFunc;
	m_mapClassFunc[_T("CDMAXOCalDC_CF")]=&CXOCalibration::CXOCalDC_CF;
	m_mapClassFunc[_T("CDMAXOCalFT")]=&CXOCalibration::CXOCalFT;

}

CXOCalibration::~CXOCalibration()
{
	
}

bool CXOCalibration::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CXOCalibration::Handle()
{
	if(!DoProcess())
	{

		return false;
	}

	CalPassLog("_","_","XO Cal Pass");

	return true;
}

bool CXOCalibration::CXOCalibrationMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CXOCalibration::CXOCalDC_CF()
{
      CString strMsg;
      int iErrorcode;
    	unsigned short iStatus=0; 
		int iDLChannel;
		double dUlMHz;
		double dDLMhz;
		FTM_RF_Mode_Enum eBandInd;
		FTM_ENH_XO_Cal_Request  pFTM_ENH_XO_Cal_Request;
		FTM_XO_Cal_Response_v2  pFTM_XO_Cal_Response;
		

		 if(m_iXOMode==1)
		{
			iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CWCDMABandInfo::GetPhoneMode(m_iBand);
			dUlMHz=1000*CWCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel);
			dDLMhz=1000*CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel);
  
		}
		else
		{
			iDLChannel=CCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CCDMABandInfo::GetPhoneMode(m_iBand);

			dUlMHz=1000*CCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,0);
			dDLMhz=1000*CCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,1);
		}

		pFTM_ENH_XO_Cal_Request.iMax_ft_samples=100;
		pFTM_ENH_XO_Cal_Request.iMin_ft_samples=5;
		pFTM_ENH_XO_Cal_Request.iOffset=m_iFreqOffset*1000;
		pFTM_ENH_XO_Cal_Request.iTechnology=1;
		pFTM_ENH_XO_Cal_Request.iRxFreq=dDLMhz;
		pFTM_ENH_XO_Cal_Request.iSubstage_Time=200;
		pFTM_ENH_XO_Cal_Request.iTemp_Span=1024;
		pFTM_ENH_XO_Cal_Request.iTimeOut=30000;
		pFTM_ENH_XO_Cal_Request.iWrite_NV=3;
 

       
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetXOSig(dDLMhz,dUlMHz,m_iFreqOffset,-35))
	   {
			LogTrace(MSG_ERROR,"Init test device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Init test device fail");
			return false;
		  
	   }
        
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iXOMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode ID  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	
	if((iErrorcode=m_pPhone->FTM_SET_MODE(eBandInd))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode (Band)  Fail!");
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
	
	iErrorcode=m_pPhone->FTM_DO_ENH_XO_DC_CAL(&pFTM_ENH_XO_Cal_Request,&pFTM_XO_Cal_Response);

	if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state && 0xff)!=1)
	{ 
		
		strMsg.Format("FTM_DO_ENH_XO_DC_CAL  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

    
	iErrorcode=m_pPhone->FTM_DO_ENH_XO_FT_COLLECT_SAMPLE(&pFTM_ENH_XO_Cal_Request,&pFTM_XO_Cal_Response);

	if((iErrorcode!=PHONE_SUCCESS) || ((pFTM_XO_Cal_Response.state && 0xff)!=2))
	{ 
		
		strMsg.Format("FTM_DO_ENH_XO_FT_COLLECT_SAMPLE  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

  


	CalPassLog(CStr::IntToStr(m_iBand),CStr::IntToStr(m_iCHannel),"XO_CoarseCal Pass");



	return true;
}

bool CXOCalibration::CXOCalFT()
{
  
      CString strMsg;
      int iErrorcode;
    	unsigned short iStatus=0; 
		int iDLChannel;
		double dUlMHz;
		double dDLMhz;
		FTM_RF_Mode_Enum eBandInd;
		FTM_ENH_XO_Cal_Request  pFTM_ENH_XO_Cal_Request;
		FTM_XO_Cal_Response_v2  pFTM_XO_Cal_Response;
		

		 if(m_iXOMode==1)
		{
			iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CWCDMABandInfo::GetPhoneMode(m_iBand);
			dUlMHz=1000*CWCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel);
			dDLMhz=1000*CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel);
  
		}
		else
		{
			iDLChannel=CCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CCDMABandInfo::GetPhoneMode(m_iBand);

			dUlMHz=1000*CCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,0);
			dDLMhz=1000*CCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,1);
		}

		pFTM_ENH_XO_Cal_Request.iMax_ft_samples=100;
		pFTM_ENH_XO_Cal_Request.iMin_ft_samples=5;
		pFTM_ENH_XO_Cal_Request.iOffset=m_iFreqOffset*1000;
		pFTM_ENH_XO_Cal_Request.iTechnology=1;
		pFTM_ENH_XO_Cal_Request.iRxFreq=dDLMhz;
		pFTM_ENH_XO_Cal_Request.iSubstage_Time=200;
		pFTM_ENH_XO_Cal_Request.iTemp_Span=1024;
		pFTM_ENH_XO_Cal_Request.iTimeOut=30000;
		pFTM_ENH_XO_Cal_Request.iWrite_NV=3;
 

       
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetXOSig(dDLMhz,dUlMHz,m_iFreqOffset,-35))
	   {
			LogTrace(MSG_ERROR,"Init test device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Init test device fail");
			return false;
		  
	   }
        
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iXOMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode ID  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	
	if((iErrorcode=m_pPhone->FTM_SET_MODE(eBandInd))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode (Band)  Fail!");
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

	if((iErrorcode=m_pPhone->FTM_SET_LNA_RANGE(2))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set LNA RANGE  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	if((iErrorcode=m_pPhone->FTM_SET_TX_ON())!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set TX ON  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_PA_RANGE(3))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone FTM_SET_PA_RANGE 3  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_PDM(2,100))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone FTM_SET_PDM 100  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}



	
	iErrorcode=m_pPhone->FTM_DO_ENH_XO_FT_CURVE_CAL(&pFTM_ENH_XO_Cal_Request,&pFTM_XO_Cal_Response);

    
	if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state && 0xff)!=5)
	{ 
		
		strMsg.Format("FTM_DO_ENH_XO_FT_CURVE_CAL  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set TX OFF  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

    
	if(!m_pPhone->IsPhoneConnected())
	{ 
		strMsg.Format("Phone connected Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	CalPassLog(CStr::IntToStr(m_iBand),CStr::IntToStr(m_iCHannel),"XO_FTCurveCal Pass");


	return true;
}


 bool CXOCalibration::InitData(
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
     
       itrFind=pcSettingMap->find(_T("FreqOffSetKhz"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'FreqOffSetKhz' from ini file!.default is 200");
		 m_iFreqOffset=200;
	 }
	 else
	 {
		 m_iFreqOffset=CStr::StrToInt(itrFind->second);
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

	  itrFind=pcSettingMap->find(_T("RFMode"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RFMode' from ini file!.default is 1 (WCDMA)");
		 m_iXOMode=1;
	 }
	 else
	 {
		 m_iXOMode=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("PARange"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'PARange' from ini file!.default is 3");
		 m_iPaRange=3;
	 }
	 else
	 {
		 m_iPaRange=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("PDM"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'PDM' from ini file!.default is 100");
		 m_iPDM=100;
	 }
	 else
	 {
		 m_iPDM=CStr::StrToInt(itrFind->second);
	 }

	 InitData();
	 return true;
 }

 bool CXOCalibration::InitData()
 {
	 m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	 return true;
 }