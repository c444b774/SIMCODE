#include "stdafx.h"
#include "XOCalibration.h"
RF_IMPLEMENT_DYNCREATE(CXOCalibration)

CXOCalibration::CXOCalibration()
{
	m_mapClassFunc[_T("XOCalMainFunc")]=&CXOCalibration::CXOCalibrationMainFunc;
	m_mapClassFunc[_T("XOCalDC_CF")]=&CXOCalibration::CXOCalDC_CF;
	m_mapClassFunc[_T("XOCalFT")]=&CXOCalibration::CXOCalFT;
	m_mapClassFunc[_T("XOCal_V3")]=&CXOCalibration::CXOCal_V3;
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
		
		if(m_iIsResetFail)
		{
			if(m_pPhone->IsPhoneConnected())
			{
				m_pPhone->FTM_SET_TX_ON(false);
				m_pPhone->SetPhoneMode(MODE_ONLINE_F);
				Sleep(1000);
				m_pPhone->SetPhoneMode(MODE_RESET_F);
			}
		}
	       
       m_pPhone->CloseComport();
		m_pFunWCDMACalDev->Deivce_Exit();

		return false;
	}

	//CalPassLog("_","_","XO Cal Pass");

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
		byte iTech=0;
		unsigned short iAGC=0;
		memset(&pFTM_ENH_XO_Cal_Request,0,sizeof(FTM_ENH_XO_Cal_Request));
		switch (m_iXOMode)
		{
			case FTM_MODE_ID_WCDMA:
				iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
				eBandInd=CWCDMABandInfo::GetPhoneMode(m_iBand);
				iTech=1;
				dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,1);
				dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,0);
				break;
			case FTM_MODE_ID_CDMA_1X:
				//iDLChannel=CCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
				eBandInd=CCDMABandInfo::GetPhoneMode(m_iBand);
				iTech=0;
				dUlMHz=CCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,0);
				dDLMhz=CCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,1);
				break;
			case FTM_MODE_ID_TDSCDMA:
				eBandInd=CTDSBandInfo::GetPhoneMode(m_iBand);
				dUlMHz=0.2*m_iCHannel;
				dDLMhz=dUlMHz;
				iTech=4;
				break;
			case FTM_MODE_ID_LTE:
				iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
				eBandInd=CLTEBandInfo::GetPhoneMode(m_iBand);
				iTech=3;			
				dUlMHz=CLTEBandInfo::ArfcnToHz(m_iBand,m_iCHannel);
				dDLMhz=CLTEBandInfo::ArfcnToHz(m_iBand,iDLChannel);		
				break;
			default:
				break;
		}
		 pFTM_ENH_XO_Cal_Request.iMax_ft_samples=m_iMaxFTSample;
		 pFTM_ENH_XO_Cal_Request.iMin_ft_samples=m_iMinFTSample;
		 pFTM_ENH_XO_Cal_Request.iOffset=m_iFreqOffset*1000;
		 pFTM_ENH_XO_Cal_Request.iTechnology=iTech;
		 pFTM_ENH_XO_Cal_Request.iRxFreq=dDLMhz*1000;
		 pFTM_ENH_XO_Cal_Request.iSubstage_Time=m_iSubstageTime;
		 pFTM_ENH_XO_Cal_Request.iTemp_Span=(dword)(m_dTempSpan*1024);
		 pFTM_ENH_XO_Cal_Request.iTimeOut=30000;
		 pFTM_ENH_XO_Cal_Request.iWrite_NV=3;       

		 if((iErrorcode=m_pPhone->FTM_SET_Cal_STATE(1))!=PHONE_SUCCESS)
		 { 
			 strMsg.Format("Set Cal State ON  Fail!");
			 LogTrace(MSG_ERROR,strMsg)
			 m_iErrorcode=iErrorcode;
			 CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
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
		 if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(0))!=PHONE_SUCCESS)
		 { 
			 strMsg.Format("Phone FTM_SET_SECONDARY_CHAIN  Fail!");
			 LogTrace(MSG_ERROR,strMsg)
			 m_iErrorcode=iErrorcode;
			 CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			 return false;
		 }
       
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetXOSig(dUlMHz,dDLMhz,m_iFreqOffset,m_dPowerLevel))
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

		if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_iCHannel))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Set channel %d  Fail!",m_iCHannel);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
	
		if((iErrorcode=m_pPhone->FTM_SET_LNA_RANGE(m_iLNAState))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Set LNA RANGE %d Fail!",m_iLNAState);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}

		if((iErrorcode=m_pPhone->FTM_GET_RX_AGC(&iAGC))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone FTM_GET_RX_AGC %x Fail!",iAGC);
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}

		if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Set TX OFF Fail!");
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
	
		iErrorcode=m_pPhone->FTM_DO_ENH_XO_DC_CAL(&pFTM_ENH_XO_Cal_Request,&pFTM_XO_Cal_Response);

		if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state & 0xff)!=1)
		{ 
			
			strMsg.Format("FTM_DO_ENH_XO_DC_CAL  Fail! reason:%d",pFTM_XO_Cal_Response.tcxomgr_cal_info_pkt.fail_reason);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
	    
		iErrorcode=m_pPhone->FTM_DO_ENH_XO_FT_COLLECT_SAMPLE(&pFTM_ENH_XO_Cal_Request,&pFTM_XO_Cal_Response);
		if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state & 0xff)!=2)
		{ 			
			strMsg.Format("FTM_DO_ENH_XO_FT_COLLECT_SAMPLE  Fail!reason:%d",pFTM_XO_Cal_Response.tcxomgr_cal_info_pkt.fail_reason);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}

		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPower_On(false))
	    {
			LogTrace(MSG_ERROR,"Set device DL OFF fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set device DL OFF fail");
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
		byte iTech=0;
		unsigned short iAGC=0;
		switch (m_iXOMode)
		{
		case FTM_MODE_ID_WCDMA:
			iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CWCDMABandInfo::GetPhoneMode(m_iBand);
			iTech=1;
			dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,1);
			dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,0);
			break;
		case FTM_MODE_ID_CDMA_1X:
			//iDLChannel=CCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CCDMABandInfo::GetPhoneMode(m_iBand);
			iTech=0;
			dUlMHz=CCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,0);
			dDLMhz=CCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,1);
			break;
		case FTM_MODE_ID_TDSCDMA:
			eBandInd=CTDSBandInfo::GetPhoneMode(m_iBand);
			dUlMHz=0.2*m_iCHannel;
			dDLMhz=dUlMHz;
			iTech=4;
			break;
		case FTM_MODE_ID_LTE:
			iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CLTEBandInfo::GetPhoneMode(m_iBand);
			iTech=3;			
			dUlMHz=CLTEBandInfo::ArfcnToHz(m_iBand,m_iCHannel);
			dDLMhz=CLTEBandInfo::ArfcnToHz(m_iBand,iDLChannel);		
			break;
		default:
			break;
		}

		pFTM_ENH_XO_Cal_Request.iMax_ft_samples=m_iMaxFTSample;
		pFTM_ENH_XO_Cal_Request.iMin_ft_samples=m_iMinFTSample;
		pFTM_ENH_XO_Cal_Request.iOffset=m_iFreqOffset*1000;
		pFTM_ENH_XO_Cal_Request.iTechnology=iTech;
		pFTM_ENH_XO_Cal_Request.iRxFreq=dDLMhz*1000;
		pFTM_ENH_XO_Cal_Request.iSubstage_Time=m_iSubstageTime;
		pFTM_ENH_XO_Cal_Request.iTemp_Span=(dword)(m_dTempSpan*1024);
		pFTM_ENH_XO_Cal_Request.iTimeOut=120000;
		pFTM_ENH_XO_Cal_Request.iWrite_NV=3;
 

       
		if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetXOSig(dUlMHz,dDLMhz,m_iFreqOffset,m_dPowerLevel))
	   {
			LogTrace(MSG_ERROR,"Init test device fail");
			CalFailLog(_T("_"),_T("_"),WCDMACAL_SETSIG,"Init test device fail");
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
		strMsg.Format("Phone Set channel %d  Fail!",m_iCHannel);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_LNA_RANGE(m_iLNAState))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set LNA RANGE %d Fail!",m_iLNAState);
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

	if((iErrorcode=m_pPhone->FTM_SET_PA_RANGE(m_iPaRange))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone FTM_SET_PA_RANGE %d  Fail!",m_iPaRange);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_PDM(2,m_iPDM))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone FTM_SET_PDM %d  Fail!",m_iPDM);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	Sleep(m_iTxOnTimeMs);
	

	if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set TX OFF Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	if((iErrorcode=m_pPhone->FTM_GET_RX_AGC(&iAGC))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone FTM_GET_RX_AGC %x Fail!",iAGC);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	
	iErrorcode=m_pPhone->FTM_DO_ENH_XO_FT_CURVE_CAL(&pFTM_ENH_XO_Cal_Request,&pFTM_XO_Cal_Response);

    
	if((iErrorcode!=PHONE_SUCCESS)|| (pFTM_XO_Cal_Response.state & 0xff)!=5)
	{ 
		
		strMsg.Format("FTM_DO_ENH_XO_FT_CURVE_CAL  Fail!reason:%d",pFTM_XO_Cal_Response.tcxomgr_cal_info_pkt.fail_reason);
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

	if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPower_On(false))
   {
		LogTrace(MSG_ERROR,"Set device DL OFF fail");
		CalFailLog(_T("_"),_T("_"),1001,"Set device DL OFF fail");
		return false;
	  
   }
   CalPassLog(CStr::IntToStr(m_iBand),CStr::IntToStr(m_iCHannel),"XO_FTCurveCal Pass");
   return true;
}
bool CXOCalibration::CXOCal_V3()
{	
	CString strMsg;
	int iErrorcode;
	unsigned short iStatus=0; 
	int iDLChannel;
	double dUlMHz;
	double dDLMhz;
	FTM_RF_Mode_Enum eBandInd;
	
	//ftm_xo_cal_parameter_type
	ftm_xo_cal_parameter_type pFTM_XO_Cal_Request;
	FTM_XO_Cal_Response_v2  pFTM_XO_Cal_Response;
	byte iTech=0;
	unsigned short iAGC=0;
	memset(&pFTM_XO_Cal_Request,0,sizeof(ftm_xo_cal_parameter_type));
	memset(&pFTM_XO_Cal_Response,0,sizeof(FTM_XO_Cal_Response_v2));
	switch (m_iXOMode)
	{
		case FTM_MODE_ID_WCDMA:
				iDLChannel=CWCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
				eBandInd=CWCDMABandInfo::GetPhoneMode(m_iBand);
				iTech=1;
				dUlMHz=CWCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,1);
				dDLMhz=CWCDMABandInfo::ArfcnToHz(m_iBand,iDLChannel,0);
				break;
		case FTM_MODE_ID_CDMA_1X:
			//iDLChannel=CCDMABandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CCDMABandInfo::GetPhoneMode(m_iBand);
			iTech=0;
			dUlMHz=CCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,0);
			dDLMhz=CCDMABandInfo::ArfcnToHz(m_iBand,m_iCHannel,1);
			break;
		case FTM_MODE_ID_TDSCDMA:
			eBandInd=CTDSBandInfo::GetPhoneMode(m_iBand);
			dUlMHz=0.2*m_iCHannel;
			dDLMhz=dUlMHz;
			iTech=4;
			break;
		case FTM_MODE_ID_LTE:
			iDLChannel=CLTEBandInfo::GetDLChannel(m_iBand,m_iCHannel);
			eBandInd=CLTEBandInfo::GetPhoneMode(m_iBand);
			iTech=3;			
			dUlMHz=CLTEBandInfo::ArfcnToHz(m_iBand,m_iCHannel);
			dDLMhz=CLTEBandInfo::ArfcnToHz(m_iBand,iDLChannel);		
			break;
		default:
			break;
	}
	pFTM_XO_Cal_Request.max_ft_samples=m_iMaxFTSample;
	pFTM_XO_Cal_Request.min_ft_samples=m_iMinFTSample;
	pFTM_XO_Cal_Request.offset=m_iFreqOffset*1000;
	pFTM_XO_Cal_Request.technology=iTech;
	pFTM_XO_Cal_Request.rx_freq_khz=dDLMhz*1000;
	pFTM_XO_Cal_Request.substage_time=m_iSubstageTime;
	pFTM_XO_Cal_Request.temp_span=(dword)(m_dTempSpan*1024);
	pFTM_XO_Cal_Request.timeout_time=30000;
	pFTM_XO_Cal_Request.update_nv=3; 
    pFTM_XO_Cal_Request.temp_grad_timeout=10;
	pFTM_XO_Cal_Request.xtal=m_iXTALType;  

	if((iErrorcode=m_pPhone->FTM_SET_Cal_STATE(1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Set Cal State ON  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
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
	if(m_iXOMode==FTM_MODE_ID_LTE)
	{
		if((iErrorcode=m_pPhone->FTM_SET_BANDWIDTH(m_iTxChanBW,m_iRxChanBW))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Set TX RX BANDWIDTH  Fail!");
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
	}
	if((iErrorcode=m_pPhone->FTM_SET_SECONDARY_CHAIN(0))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone FTM_SET_SECONDARY_CHAIN  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->IWCDMACalSetXOSig(dUlMHz,dDLMhz,m_iFreqOffset,m_dPowerLevel))
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
	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(m_iXOMode))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode ID  Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_iCHannel))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set channel %d  Fail!",m_iCHannel);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_SET_LNA_RANGE(m_iLNAState))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set LNA RANGE %d Fail!",m_iLNAState);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
    //XO Cal command  1-Coarse Cal   2-Collect samples   3-FT Curve Cal
	unsigned char xo_cal_version = 3;
	if (m_bXO_DC_Coarse==true)
	{
		//Coarse_DC Cal
		iErrorcode=m_pPhone->FTM_XO_CALIBRATION(XO_DC_COARSE_CAL,xo_cal_version,&pFTM_XO_Cal_Request, &pFTM_XO_Cal_Response);	
		if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state & 0xff)!=1)
		{ 
			strMsg.Format("FTM_XO_CALIBRATION  Coarse_DC Cal Fail! reason:%d",pFTM_XO_Cal_Response.tcxomgr_cal_info_pkt.fail_reason);
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
	}
    if (m_bXO_Collect_Sample==true)
    {
		//Collect Samples
		iErrorcode=m_pPhone->FTM_XO_CALIBRATION(XO_COLLECT_SAMPLES,xo_cal_version,&pFTM_XO_Cal_Request, &pFTM_XO_Cal_Response);	
		if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state & 0xff)!=2)
		{ 
			strMsg.Format("FTM_XO_CALIBRATION  Collect Samples Fail! reason:%d",pFTM_XO_Cal_Response.tcxomgr_cal_info_pkt.fail_reason);
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
    }
    if (m_bXO_FT_Curve==true)
    {
		//FT Curve Cal-------fine cal
		iErrorcode=m_pPhone->FTM_XO_CALIBRATION(XO_FT_CURVE_CAL,xo_cal_version,&pFTM_XO_Cal_Request, &pFTM_XO_Cal_Response);	
		if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state & 0xff)!=5)
		{ 
			strMsg.Format("FTM_XO_CALIBRATION FT Curve Cal  Fail! reason:%d",pFTM_XO_Cal_Response.tcxomgr_cal_info_pkt.fail_reason);
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
    }
	if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set TX OFF Fail!");
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	/*
	    if((iErrorcode=m_pPhone->FTM_GET_RX_AGC(&iAGC))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone FTM_GET_RX_AGC %x Fail!",iAGC);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
		if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Set TX OFF Fail!");
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
		iErrorcode=m_pPhone->FTM_DO_ENH_XO_DC_CAL(&pFTM_ENH_XO_Cal_Request,&pFTM_XO_Cal_Response);
		if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state & 0xff)!=1)
		{ 
			strMsg.Format("FTM_DO_ENH_XO_DC_CAL  Fail! reason:%d",pFTM_XO_Cal_Response.tcxomgr_cal_info_pkt.fail_reason);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}
		iErrorcode=m_pPhone->FTM_DO_ENH_XO_FT_COLLECT_SAMPLE(&pFTM_ENH_XO_Cal_Request,&pFTM_XO_Cal_Response);
		if((iErrorcode!=PHONE_SUCCESS) || (pFTM_XO_Cal_Response.state & 0xff)!=2)
		{ 			
			strMsg.Format("FTM_DO_ENH_XO_FT_COLLECT_SAMPLE  Fail!reason:%d",pFTM_XO_Cal_Response.tcxomgr_cal_info_pkt.fail_reason);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}*/
	
	if(DEVICE_SUCCESS!=m_pFunWCDMACalDev->ICDMACalSet_DLPower_On(false))
	{
		LogTrace(MSG_ERROR,"Set device DL OFF fail");
		CalFailLog(_T("_"),_T("_"),1001,"Set device DL OFF fail");
		return false;		  
	}
	CalPassLog(CStr::IntToStr(m_iBand),CStr::IntToStr(m_iCHannel),"XO_CoarseCal Pass");
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
		 m_iXOMode=FTM_MODE_ID_WCDMA;
	 }
	 else
	 {
		 m_iXOMode=CStr::StrToInt(itrFind->second);
		 if (FTM_MODE_ID_WCDMA!=m_iXOMode&&FTM_MODE_ID_CDMA_1X!=m_iXOMode&&FTM_MODE_ID_TDSCDMA!=m_iXOMode)
		 {
			  LogTrace(MSG_WARNING,"'RFMode' supported only can be 0,1,42");
		 }
		 
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
	 itrFind=pcSettingMap->find(_T("PowerLevel"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'PowerLevel' from ini file!.default is -30");
		 m_dPowerLevel=-30;
	 }
	 else
	 {
		 m_dPowerLevel=CStr::StrToFloat(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("LNAState"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'LNAState' from ini file!.default is 2");
		 m_iLNAState=2;
	 }
	 else
	 {
		 m_iLNAState=CStr::StrToInt(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("TempSpan"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TempSpan' from ini file!.default is 0.25");
		 m_dTempSpan=0.25;
	 }
	 else
	 {
		 m_dTempSpan=CStr::StrToFloat(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("MinFTSample"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'MinFTSample' from ini file!.default is 100");
		 m_iMinFTSample=100;
	 }
	 else
	 {
		 m_iMinFTSample=CStr::StrToInt(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("MaxFTSample"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'MaxFTSample' from ini file!.default is 200");
		 m_iMaxFTSample=200;
	 }
	 else
	 {
		 m_iMaxFTSample=CStr::StrToInt(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("SubstageTime"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'SubstageTime' from ini file!.default is 100");
		 m_iSubstageTime=100;
	 }
	 else
	 {
		 m_iSubstageTime=CStr::StrToInt(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("TxOnTimeMs"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TxOnTimeMs' from ini file!.default is 10000");
		 m_iTxOnTimeMs=10000;
	 }
	 else
	 {
		 m_iTxOnTimeMs=CStr::StrToInt(itrFind->second);
	 }
	 
	 itrFind=pcSettingMap->find(_T("IsResetFail"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'IsResetFail' from ini file!.default is 1");
		 m_iIsResetFail=1;
	 }
	 else
	 {
		 m_iIsResetFail=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("TxChanBW"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TxChanBW' from ini file!.default is 1");
		 m_iTxChanBW=3;
	 }
	 else
	 {
		 m_iTxChanBW=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("RxChanBW"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RxChanBW' from ini file!.default is 1");
		 m_iRxChanBW=3;
	 }
	 else
	 {
		 m_iRxChanBW=CStr::StrToInt(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("XTALType"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'XTALType' from ini file!.default is 2");
		 m_iXTALType=2;
	 }
	 else
	 {
		 m_iXTALType=CStr::StrToFloat(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("XO_DC_COARSE_CAL"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'XO_DC_COARSE_CAL' from ini file! defualt is true:");
		 m_bXO_DC_Coarse=true;
	 }
	 else
	 {
		 m_bXO_DC_Coarse=CStr::StrToBool(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("XO_COLLECT_SAMPLES"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'XO_COLLECT_SAMPLES' from ini file! defualt is true:");
		 m_bXO_Collect_Sample=true;
	 }
	 else
	 {
		 m_bXO_Collect_Sample=CStr::StrToBool(itrFind->second);
	 }
	 itrFind=pcSettingMap->find(_T("XO_FT_CURVE_CAL"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'XO_FT_CURVE_CAL' from ini file! defualt is true:");
		 m_bXO_FT_Curve=true;
	 }
	 else
	 {
		 m_bXO_FT_Curve=CStr::StrToBool(itrFind->second);
	 }
	 //,

	 InitData();
	 return true;
 }

 bool CXOCalibration::InitData()
 {
	 m_pFunWCDMACalDev=m_piTesterDevice->m_piFuncWCDMACal;
	 return true;
 }