#include "stdafx.h"
#include "KVCOCal.h"
RF_IMPLEMENT_DYNCREATE(CKVCOCal)

CKVCOCal::CKVCOCal()
{
	m_mapClassFunc[_T("KVCOCalMainFunc")]=&CKVCOCal::CKVCOCalMainFunc;
	m_mapClassFunc[_T("CKVCOCal_V2")]=&CKVCOCal::CKVCOCal_V2;
	m_mapClassFunc[_T("KVCOCal_850")]=&CKVCOCal::CKVCOCalFunc_850;
	m_mapClassFunc[_T("KVCOCal_900")]=&CKVCOCal::CKVCOCalFunc_900;
	m_mapClassFunc[_T("KVCOCal_1800")]=&CKVCOCal::CKVCOCalFunc_1800;
	m_mapClassFunc[_T("KVCOCal_1900")]=&CKVCOCal::CKVCOCalFunc_1900;


}

CKVCOCal::~CKVCOCal()
{
	
}

bool CKVCOCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CKVCOCal::Handle()
{
	if(!DoProcess())
	{
        m_pPhone->CloseComport();
		return false;
	}



	return true;
}

bool CKVCOCal::CKVCOCalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CKVCOCal::CKVCOCalBandSelect(int iBand)
{
	 
    unsigned short piLowChanKvco=0,piHighChanKvco=0; 
	unsigned char ret=0;
	IntVtr vChannelList;
    CString strMsg;
    int iErrorcode;
    int iPhoneMode; 
	CString strBand;
	switch(iBand)
	{
	    case 850:
			iPhoneMode=CGSMBandInfo::GetPhoneMode(850);
			vChannelList=m_vChannelList_850;
			strBand="GSM850";
		break;
		case 900:
			iPhoneMode=CGSMBandInfo::GetPhoneMode(900);
			vChannelList=m_vChannelList_900;
			strBand="GSM900";
		break;
		case 1800:
			iPhoneMode=CGSMBandInfo::GetPhoneMode(1800);
			vChannelList=m_vChannelList_1800;
			strBand="GSM1800";
		break;
		case 1900:
			iPhoneMode=CGSMBandInfo::GetPhoneMode(1900);
			vChannelList=m_vChannelList_1900;
			strBand="GSM1900";
		break;
		default:
		strMsg.Format("Band not correct");
		CalFailLog("_","_",9999,strMsg);
		 return false;


		 
	}

	strMsg.Format("Start KVCO Calibration: Band=GSM%d.....",iBand);
	LogTrace(MSG_MID,strMsg)
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}

		if((iErrorcode=m_pPhone->FTM_SET_MODE(iPhoneMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}
    
		if((iErrorcode=m_pPhone->FTM_GSM_DO_TX_KV_CAL(vChannelList[0],vChannelList[1],&piLowChanKvco,&piHighChanKvco))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_GSM_DO_TX_KV_CAL Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}

		strMsg.Format("KVCO Result :HighKVCO=%d LowKVCO=%d",piLowChanKvco,piHighChanKvco);
        LogTrace(MSG_MID,strMsg)

	   if(piLowChanKvco>=0 && piHighChanKvco>=0)
	   {
			strMsg.Format("KVCO Band=%s Pass",strBand);
			CalPassLog(strBand,"_",strMsg)
	   }
	   else
	   {
		   
		   strMsg.Format("KVCO Band=%s Fail",strBand);
		   CalFailLog(strBand,"_",KVCOFAIL,strMsg);
		   return false;
	   }
       

	return true;
}
bool CKVCOCal::CKVCOCalFunc_850()
{
	 	 		
	return CKVCOCalBandSelect(850);
}
bool CKVCOCal::CKVCOCalFunc_900()
{
	 	 		
	return CKVCOCalBandSelect(900);
}
bool CKVCOCal::CKVCOCalFunc_1800()
{
	 	 		
	return CKVCOCalBandSelect(1800);
}
bool CKVCOCal::CKVCOCalFunc_1900()
{
	 	 		
	return CKVCOCalBandSelect(1900);
}
bool CKVCOCal::CKVCOCal_V2()
{
	CString strMsg;
	int iResult=0,iKvcoRetry=0;
	int iErrorcode;
	unsigned short usRFmodelist[4];
	unsigned short usChannellist[8];
	for (int i=0;i<m_ivRFmodeList.size();i++)
	{
		usRFmodelist[i]=m_ivRFmodeList[i];
		usChannellist[2*i]=m_ivChannelList[2*i];
		usChannellist[2*i+1]=m_ivChannelList[2*i+1];
	}
	
	strMsg.Format("Start KVCO Calibration:");
	LogTrace(MSG_MID,strMsg)

		do 
		{
			iResult=0;
			if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_SET_MODE ID Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}	
			if((iErrorcode=m_pPhone->FTM_GSM_DO_TX_KV_CAL_V2(m_ivRFmodeList.size(),m_iNumTxCycles,m_iNumMeas,usRFmodelist,usChannellist))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_GSM_DO_TX_KV_CAL_V2 Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}

			strMsg.Format("KVCO Result:");
			LogTrace(MSG_MID,strMsg)
				strMsg.Format("Channel	KVCO	min	max	result");
			LogTrace(MSG_MID,strMsg)
				for (int i=0;i<m_ivChannelList.size();i++)
				{
					if (usChannellist[i]<m_ivKVCOmaxLimit[i]&&usChannellist[i]>m_ivKVCOminLimit[i])
					{
						strMsg.Format("%d	%d	%d	%d	Pass",m_ivChannelList[i],usChannellist[i],m_ivKVCOminLimit[i],m_ivKVCOmaxLimit[i]);
						LogTrace(MSG_MID,strMsg)

					}
					else
					{
						strMsg.Format("%d	%d	%d	%d	Fail",m_ivChannelList[i],usChannellist[i],m_ivKVCOminLimit[i],m_ivKVCOmaxLimit[i]);
						LogTrace(MSG_MID,strMsg)
							iResult++;

					}
				}
		} while (iResult>0&&iKvcoRetry++<5);
		
		if (iResult>0)
		{
			strMsg.Format("KVCO_V2 Fail");
			CalFailLog("_","_",iErrorcode,strMsg)
				return false;

			
		}
		strMsg.Format("KVCO_V2 Pass");
		CalPassLog("_","_",strMsg)
			return true;

}

 bool CKVCOCal::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
	 bool bIsCal850=false;
	 bool bIsCal900=false;
	 bool bIsCal1800=false;
	 bool bIsCal1900=false;
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
		if(strfunc=="KVCOCal_850")
		bIsCal850=true;
		else if(strfunc=="KVCOCal_900")
		bIsCal900=true;
		else if(strfunc=="KVCOCal_1800")
		bIsCal1800=true;
		else if(strfunc=="KVCOCal_1900")
		bIsCal1900=true;

	 }


      if(bIsCal850)
	  {
		   itrFind=pcSettingMap->find(_T("ChannelList_850"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'ChannelList_850' from ini file!.");
			 return false;
		 }
		 else
		 {
			 CStr::ParseString(itrFind->second,",",strVtr);
			 CStr::StrVtr2IntVtr(m_vChannelList_850,strVtr);
		 }


	  }
	  if(bIsCal900)
	  {
		   itrFind=pcSettingMap->find(_T("ChannelList_900"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'ChannelList_900' from ini file!.");
			 return false;
		 }
		 else
		 {
			 CStr::ParseString(itrFind->second,",",strVtr);
			 CStr::StrVtr2IntVtr(m_vChannelList_900,strVtr);
		 }

	  }
	  if(bIsCal1800)
	  {
		   itrFind=pcSettingMap->find(_T("ChannelList_1800"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'ChannelList_1800' from ini file!.");
			 return false;
		 }
		 else
		 {
			 CStr::ParseString(itrFind->second,",",strVtr);
			 CStr::StrVtr2IntVtr(m_vChannelList_1800,strVtr);
		 }

	  }
	  if(bIsCal1900)
	  {
         itrFind=pcSettingMap->find(_T("ChannelList_1900"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'ChannelList_1900' from ini file!.");
			 return false;
		 }
		 else
		 {
			 CStr::ParseString(itrFind->second,",",strVtr);
			 CStr::StrVtr2IntVtr(m_vChannelList_1900,strVtr);
		 }

	  }

	  itrFind=pcSettingMap->find(_T("RFmodeList"));
	  if(itrFind==pcSettingMap->end())
	  {
		  LogTrace(MSG_MID,"Not Find 'RFmodeList' from ini file!.default :18,10,11,12");
		  strValue="18,10,11,12";
		  CStr::ParseString(strValue,",",strVtr);
		  CStr::StrVtr2IntVtr(m_ivRFmodeList,strVtr);
	  }
	  else
	  {
		  CStr::ParseString(itrFind->second,",",strVtr);
		  CStr::StrVtr2IntVtr(m_ivRFmodeList,strVtr);
	  }

	  itrFind=pcSettingMap->find(_T("ChannelListAll"));
	  if(itrFind==pcSettingMap->end())
	  {
		  LogTrace(MSG_MID,"Not Find 'ChannelListAll' from ini file!.default :128,251,975,124,512,885,512,810");
		  strValue="128,251,975,124,512,885,512,810";
		  CStr::ParseString(strValue,",",strVtr);
		  CStr::StrVtr2IntVtr(m_ivChannelList,strVtr);
	  }
	  else
	  {
		  CStr::ParseString(itrFind->second,",",strVtr);
		  CStr::StrVtr2IntVtr(m_ivChannelList,strVtr);
	  }
	  itrFind=pcSettingMap->find(_T("KVCOmaxLimit"));
	  if(itrFind==pcSettingMap->end())
	  {
		  LogTrace(MSG_MID,"Not Find 'KVCOmaxLimit' from ini file!.default :3000,3000,3000,3000,3000,3000,3000,3000");
		  strValue="3000,3000,3000,3000,3000,3000,3000,3000";
		  CStr::ParseString(strValue,",",strVtr);
		  CStr::StrVtr2IntVtr(m_ivKVCOmaxLimit,strVtr);
	  }
	  else
	  {
		  CStr::ParseString(itrFind->second,",",strVtr);
		  CStr::StrVtr2IntVtr(m_ivKVCOmaxLimit,strVtr);
	  }
	  itrFind=pcSettingMap->find(_T("KVCOminLimit"));
	  if(itrFind==pcSettingMap->end())
	  {
		  LogTrace(MSG_MID,"Not Find 'KVCOminLimit' from ini file!.default :500,500,500,500,500,500,500,500");
		  strValue="500,500,500,500,500,500,500,500";
		  CStr::ParseString(strValue,",",strVtr);
		  CStr::StrVtr2IntVtr(m_ivKVCOminLimit,strVtr);
	  }
	  else
	  {
		  CStr::ParseString(itrFind->second,",",strVtr);
		  CStr::StrVtr2IntVtr(m_ivKVCOminLimit,strVtr);
	  }

	  itrFind=pcSettingMap->find(_T("NumTxCycles"));
	  if(itrFind==pcSettingMap->end())
	  {
		  LogTrace(MSG_MID,"Not Find 'NumTxCycles' from ini file!.default :1");
		  m_iNumTxCycles=1;
	  }
	  else
	  {		  
		  m_iNumTxCycles=CStr::StrToInt(itrFind->second);
	  }

	  itrFind=pcSettingMap->find(_T("NumMeas"));
	  if(itrFind==pcSettingMap->end())
	  {
		  LogTrace(MSG_MID,"Not Find 'NumMeas' from ini file!.default :1");
		  m_iNumMeas=1;
	  }
	  else
	  {		  
		  m_iNumMeas=CStr::StrToInt(itrFind->second);
	  }
	  
     
	  
	

   
	 InitData();
	 return true;
 }

 bool CKVCOCal::InitData()
 {
	
	 return true;
 }