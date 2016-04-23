#include "StdAfx.h"
#include "BaseBandTestProc.h"
RF_IMPLEMENT_DYNCREATE(CBaseBandTestProc)

CBaseBandTestProc::CBaseBandTestProc(void)
{
	m_mapClassFunc[_T("CommonTestMainFunc")]=&CBaseBandTestProc::CommonTestMainFunc;
	m_mapClassFunc[_T("ReadSNFunc")]=&CBaseBandTestProc::ReadSNFunc;
	m_mapClassFunc[_T("WriteSNFunc")]=&CBaseBandTestProc::WriteSNFunc;
	m_mapClassFunc[_T("WriteNVFunc")]=&CBaseBandTestProc::CWriteNVFunc;
	m_mapClassFunc[_T("UploadQCN")]=&CBaseBandTestProc::UploadQCN;
	m_mapClassFunc[_T("ReadSNFunc_QRD")]=&CBaseBandTestProc::ReadSN_QRD_Func;
	m_mapClassFunc[_T("WriteSNFunc_QRD")]=&CBaseBandTestProc::WriteSN_QRD_Func;
	m_mapClassFunc[_T("WriteFlagFunc")]=&CBaseBandTestProc::WriteFlag;	
	m_mapClassFunc[_T("CheckFlagFunc")]=&CBaseBandTestProc::CheckFlag;	
    m_mapClassFunc[_T("QRD_FlagOp")]=&CBaseBandTestProc::QRD_FlagOp_Func;	
	m_mapClassFunc[_T("PopMsgFunc")]=&CBaseBandTestProc::PopMsg;
	m_mapClassFunc[_T("SleepFunc")]=&CBaseBandTestProc::SleepFunc;
	m_mapClassFunc[_T("ReloadNV")]=&CBaseBandTestProc::ReloadNV_Func;
	m_mapClassFunc[_T("SetPhoneMode")]=&CBaseBandTestProc::SetPhoneMode;
	m_mapClassFunc[_T("TxLimReviseFunc")]=&CBaseBandTestProc::TxLimReviseFunc;
	m_mapClassFunc[_T("ModeToCDMA")]=&CBaseBandTestProc::ModeToCDMA;
	m_mapClassFunc[_T("ModeToGSMWCDMA")]=&CBaseBandTestProc::ModeToGSMWCDMA;
	m_iItemCode=1003;
}

CBaseBandTestProc::~CBaseBandTestProc(void)
{
}
bool CBaseBandTestProc::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CBaseBandTestProc::Handle()
{
	int iErrorcode;

	if(!DoProcess())
	{
       m_pPhone->CloseComport();;
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


    

	/*if((iErrorcode=m_pPhone->ReloadNV())!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Reload NV Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Reload NV Fail!");
			return false;
	}*/
    
	return true;
}

 bool CBaseBandTestProc::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
     CStringStringMapItr itrFind;
	 CString strValue;
     CString strMainFun;
     CStringVtr strVtr;
     CStringVtr strVtrTemp;

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

		if(strfunc=="ReadSNFunc"  || strfunc=="WriteSNFunc")
		{
							itrFind=pcSettingMap->find(_T("NVID1"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_ERROR,"Not Find 'NVID1' from ini file!");
						 return false;
					 }
					 else
					 {
						 m_iSN_NVID1=atoi(itrFind->second);
					 }

					  itrFind=pcSettingMap->find(_T("NVID2"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_ERROR,"Not Find 'NVID2' from ini file!");
						 return false;
					 }
					 else
					 {
						 m_iSN_NVID2=atoi(itrFind->second);
					 }


					   itrFind=pcSettingMap->find(_T("DelayForNextItemMs"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_WARNING,"Not Find 'DelayForNextItemMs' from ini file!Defalt is 0 ms");
						 m_iDelayForNextItemMs=0;  
					 }
					 else
					 {
						 m_iDelayForNextItemMs=atoi(itrFind->second);
					 }

					 if(strfunc=="WriteSNFunc")
					 {
							  itrFind=pcSettingMap->find(_T("ClearFlagNVID"));
						 if(itrFind==pcSettingMap->end())
						 {
							 LogTrace(MSG_WARNING,"Not Find 'ClearFlagNVID' from ini file!Defalt is 570");
							 m_iFlagNV=570;  
						 }
						 else
						 {
							 m_iFlagNV=atoi(itrFind->second);
						 }

						   itrFind=pcSettingMap->find(_T("IsClearFlagAll"));
						 if(itrFind==pcSettingMap->end())
						 {
							 LogTrace(MSG_WARNING,"Not Find 'IsClearFlagAll' from ini file!Defalt is true");
							 m_bIsClearFlagNV=true;  
						 }
						 else
						 {
							 m_bIsClearFlagNV=CStr::StrToBool(itrFind->second);
						 }

					 }
		}
		else if(strfunc=="ReadSNFunc_QRD" || strfunc=="WriteSNFunc_QRD")
		{
				itrFind=pcSettingMap->find(_T("QRD_NV_ID"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_ERROR,"Not Find 'QRD_NV_ID' from ini file!");
						 return false;
					 }
					 else
					 {
						 m_iSN_NVID_QRD=atoi(itrFind->second);
					 }

					   itrFind=pcSettingMap->find(_T("DelayForNextItemMs"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_WARNING,"Not Find 'DelayForNextItemMs' from ini file!Defalt is 0 ms");
						 m_iDelayForNextItemMs=0;  
					 }
					 else
					 {
						 m_iDelayForNextItemMs=atoi(itrFind->second);
					 }

					 itrFind=pcSettingMap->find(_T("ClearAllFlag"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_WARNING,"Not Find 'ClearAllFlag' from ini file!Defalt is 1");
						 m_iClearAllFlag=1;  
					 }
					 else
					 {
						 m_iClearAllFlag=atoi(itrFind->second);
					 }

					 itrFind=pcSettingMap->find(_T("StationNum"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_WARNING,"Not Find 'StationNum' from ini file!Defalt is 30 ");
						 m_iStationNum=30;  
					 }
					 else
					 {
						 m_iStationNum=atoi(itrFind->second);
					 }

					 itrFind=pcSettingMap->find(_T("FlagNVID"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_WARNING,"Not Find 'FlagNVID' from ini file!Defalt is 2499 ");
						 m_iFlagNVIDforSN=2499;  
					 }
					 else
					 {
						 m_iFlagNVIDforSN=atoi(itrFind->second);
					 }
					 

		}
		else if(strfunc=="PopMsgFunc")
		{
			itrFind=pcSettingMap->find(_T("PopMsg"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_WARNING,"Not Find 'PopMsg' from ini file! default is 请开启另一个手机" );
						 m_strMsg="请开启另一个手机";
					 }
					 else
					 {
						 m_strMsg=itrFind->second;
					 }
          
		}
		else if(strfunc=="SleepFunc")
		{
			itrFind=pcSettingMap->find(_T("SleepSec"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_WARNING,"Not Find 'PopMsg' from ini file! default is 1" );
				m_dSleepSec=1;
			}
			else
			{
				m_dSleepSec=atof(itrFind->second);
			}

		}
		else if (strfunc=="UploadQCN")
		{
			itrFind=pcSettingMap->find(_T("AutoRestore"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_WARNING,"Not Find 'AutoRestore' from ini file! default is 0" );
				m_iQCNAutoRestore=0;
			}
			else
			{
				m_iQCNAutoRestore=atoi(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("SkipReset"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_WARNING,"Not Find 'SkipReset' from ini file! default is 1" );
				m_iQCNSkipReset=1;
			}
			else
			{
				m_iQCNSkipReset=atoi(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("AllowEsnMismatch"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_WARNING,"Not Find 'AllowEsnMismatch' from ini file! default is 1" );
				m_iQCNAllowESNMismatch=1;
			}
			else
			{
				m_iQCNAllowESNMismatch=atoi(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("IgnorePhoneModel"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_WARNING,"Not Find 'IgnorePhoneModel' from ini file! default is 1" );
				m_iQCNIgnorePM=1;
			}
			else
			{
				m_iQCNIgnorePM=atoi(itrFind->second);
			}

		}
		else if(strfunc=="QRD_FlagOp")
		{
			 itrFind=pcSettingMap->find(_T("FlagNVID"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'FlagNVID' from ini file!");
				 return false;
			 }
			 else
			 {
				 m_iFlagNVID=atoi(itrFind->second);
			 }

			  itrFind=pcSettingMap->find(_T("BytePos_QRD"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'BytePos_QRD' from ini file!");
				 return false;
			 }
			 else
			 {
				 m_iBytePosQRD=atoi(itrFind->second);
			 }

			  itrFind=pcSettingMap->find(_T("Flag_Op_type"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'Flag_Op_type' from ini file!");
				 return false;
			 }
			 else
			 {
				 m_iQRD_FlagOp_Enum=atoi(itrFind->second);
			 }
					 


		}
		else if(strfunc=="TxLimReviseFunc")
		{
		}
		else if(strfunc=="ModeToCDMA")
		{
		}
		else if(strfunc=="ModeToGSMWCDMA")
		{
		}
		else if(strfunc=="SetPhoneMode")
		{
		}
		else if(strfunc=="WriteNVFunc")
		{
			itrFind=pcSettingMap->find(_T("QRD_NV_ID"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'QRD_NV_ID' from ini file!");
				return false;
			}
			else
			{
				m_iNV_ID=atoi(itrFind->second);
			}
			itrFind=pcSettingMap->find(_T("NV_Value"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_FATAL,"Not Find 'NV_Value' from ini file!");
				return false;
			}
			else
			{
				strValue=itrFind->second;
				CStr::ParseString(strValue,",",strVtrTemp);
				CStr::StrVtr2IntVtr(m_vNV_Value,strVtrTemp);
			}	
			
		}
     	else
		{
			     itrFind=pcSettingMap->find(_T("FlagNVID"));
				 if(itrFind==pcSettingMap->end())
				 {
					 LogTrace(MSG_ERROR,"Not Find 'FlagNVID' from ini file!");
					 return false;
				 }
				 else
				 {
					 m_iFlagNVID=atoi(itrFind->second);
				 }

		         itrFind=pcSettingMap->find(_T("StationFlag"));
				 if(itrFind==pcSettingMap->end())
				 {
					 LogTrace(MSG_ERROR,"Not Find 'StationFlag' from ini file!");
					 return false;
				 }
				 else
				 {
					 m_iStationFlag=atoi(itrFind->second);
				 }

				   itrFind=pcSettingMap->find(_T("IsSetFlag"));
				 if(itrFind==pcSettingMap->end())
				 {
					 LogTrace(MSG_ERROR,"Not Find 'IsSetFlag' from ini file!");
					 return false;
				 }
				 else
				 {
					 m_iIsSet=atoi(itrFind->second);
				 }			     
        
		}

		
	 }
	   
	 InitData();
	 return true;
 }

 bool CBaseBandTestProc::CommonTestMainFunc()
 {
	 for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	
	 return true;

 }
 bool CBaseBandTestProc::SleepFunc()
 {   
	 CString strMsg;
	 int isleepms=(int)(m_dSleepSec*1000);
	 strMsg.Format("Sleep %0.3f second",m_dSleepSec);
	 CalPassLog(_T("_"),_T("_"),strMsg);
	 LogTrace(MSG_MID,strMsg)
	 Sleep(isleepms);
	 return true;
 }

 bool CBaseBandTestProc::TxLimReviseFunc()
 {
	 int iErrorcode=0;
	 CString strMsg;	 

		 int iNV540[16]={0};
		 unsigned char NVitemValue[32]={0};
		 unsigned char NVitemValueR[32]={0};
		 int CombinedValue=0;
		 if((iErrorcode=m_pPhone->ReadNV(540,NVitemValue,32))!=PHONE_SUCCESS)
		 { 
			 strMsg.Format("Read NV540 Fail!");
			 PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		 }

		 for(int i=0;i<16;i++)
		 {


			 CombinedValue=NVitemValue[2*i]+(NVitemValue[2*i+1]<<8);
			 if(CombinedValue>32767)  CombinedValue=CombinedValue-65536;					
			 iNV540[i]=CombinedValue;
		 }
		 iNV540[0]+=15;
		 iNV540[1]+=15;
		 iNV540[2]+=15;
		 iNV540[3]+=15;
		 iNV540[14]+=9;
		 iNV540[15]+=9;
		 for(int i=0;i<16;i++)
		 {

			 if(iNV540[i]<0)  iNV540[i]=iNV540[i]+65536;	
			 NVitemValueR[2*i]=iNV540[i]&0xFF;
			 NVitemValueR[2*i+1]=(iNV540[i]&0xFF00)>>8;
		 }
		 if((iErrorcode=m_pPhone->WriteNV(540,NVitemValueR,32))!=PHONE_SUCCESS)
		 { 
			 strMsg.Format("write NV540 Fail!");
			 PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		 }	
	
		 if((iErrorcode=m_pPhone->ReadNV(3691,NVitemValue,32))!=PHONE_SUCCESS)
		 { 
			 strMsg.Format("Read NV3691 Fail!");
			 PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		 }
		 for(int i=0;i<16;i++)
		 {


			 CombinedValue=NVitemValue[2*i]+(NVitemValue[2*i+1]<<8);
			 if(CombinedValue>32767)  CombinedValue=CombinedValue-65536;					
			 iNV540[i]=CombinedValue;
		 }
		 iNV540[0]+=9;
		 iNV540[1]+=6;
		 iNV540[14]+=9;
		 iNV540[15]+=15;
		 for(int i=0;i<16;i++)
		 {

			 if(iNV540[i]<0)  iNV540[i]=iNV540[i]+65536;	
			 NVitemValueR[2*i]=iNV540[i]&0xFF;
			 NVitemValueR[2*i+1]=(iNV540[i]&0xFF00)>>8;
		 }
		 if((iErrorcode=m_pPhone->WriteNV(3691,NVitemValueR,32))!=PHONE_SUCCESS)
		 { 
			 strMsg.Format("write NV3691 Fail!");
			 PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		 }
		 return true;

 }

bool CBaseBandTestProc::ModeToCDMA()
{
	char szCmd[1024];
	char szRev[1024]={0};
	bool bret;
	if(!m_pPhone->OpenATComport(m_iATComport))
	{
		LogTrace(MSG_ERROR,"Open Comport Fail");
		return false;
	}	

	bret=m_pPhone->CDMA_GSMWCDMA_Mode_AT(0);
	if(!bret)
		return false;

	bret=m_pPhone->Efssyn_AT();
	if(!bret)
		return false;

	m_pPhone->CloseATComport();		
	
	/*
	int iErrorcode;
	CString strMsg;
    //int NVItemValue=0;
    INT64  NVItemValue=0;

	LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		return false;
	}

	NVItemValue = 11;  //1011
    LogTrace(MSG_MID,_T(" Write NV 1878=11 !"))
	if((iErrorcode=m_pPhone->WriteNV(1878,(unsigned char*)&NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Write NV :%d  Fail!",1878);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

    NVItemValue = 562952183234951; //10 00000000 00000000 10000100 11101000 01000001 10000111
	LogTrace(MSG_MID,_T(" Write NV 1877=562952183234951 !"))
	if((iErrorcode=m_pPhone->WriteNV(1877,(unsigned char*)&NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Write NV :%d  Fail!",1877);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

    NVItemValue = 562952180613127; //10 00000000 00000000 10000100 11000000 01000000 00000111
	LogTrace(MSG_MID,_T(" Write NV 4548=562952180613127 !"))
	if((iErrorcode=m_pPhone->WriteNV(4548,(unsigned char*)&NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Write NV :%d  Fail!",4548);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	/ *
	NVItemValue = 19;//10011
		LogTrace(MSG_MID,_T(" Write NV 10=19 !"))
		if((iErrorcode=m_pPhone->WriteNV(10,(unsigned char*)&NVItemValue,128))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Write NV :%d  Fail!",10);
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}* /
	

	
	LogTrace(MSG_MID,_T(" Write EFS !"))
	if((iErrorcode=m_pPhone->WriteEFS(30000))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone WriteEFS Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone WriteEFS Fail!");
		return false;
	}

	m_pPhone->CloseComport();

	TestPassLog(_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("EndCall Pass"));*/



	return true;
}

bool CBaseBandTestProc::ModeToGSMWCDMA()
{
	char szCmd[1024];
	char szRev[1024]={0};
	bool bret;
	if(!m_pPhone->OpenATComport(m_iATComport))
	{
		LogTrace(MSG_ERROR,"Open Comport Fail");
		return false;
	}	

	bret=m_pPhone->CDMA_GSMWCDMA_Mode_AT(1);
	if(!bret)
		return false;

	bret=m_pPhone->Efssyn_AT();
	if(!bret)
		return false;

	m_pPhone->CloseATComport();		
	
/*	
	int iErrorcode;
	CString strMsg;
	INT64 NVItemValue=0;

	LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		return false;
	}

	NVItemValue = 34; 
	LogTrace(MSG_MID,_T(" Write NV 1878=34 !"))
	if((iErrorcode=m_pPhone->WriteNV(1878,(unsigned char*)&NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Write NV :%d  Fail!",1878);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	NVItemValue = 79691776; 
	LogTrace(MSG_MID,_T(" Write NV 1877=79691776 !"))
	if((iErrorcode=m_pPhone->WriteNV(1877,(unsigned char*)&NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Write NV :%d  Fail!",1877);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	NVItemValue = 0; 
	LogTrace(MSG_MID,_T(" Write NV 4548=0 !"))
	if((iErrorcode=m_pPhone->WriteNV(4548,(unsigned char*)&NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Write NV :%d  Fail!",4548);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	/ *
	NVItemValue = 58;
		LogTrace(MSG_MID,_T(" Write NV 10=58 !"))
		if((iErrorcode=m_pPhone->WriteNV(10,(unsigned char*)&NVItemValue,128))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Write NV :%d  Fail!",10);
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}* /

	LogTrace(MSG_MID,_T(" Write EFS !"))
	if((iErrorcode=m_pPhone->WriteEFS(30000))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone WriteEFS Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone WriteEFS Fail!");
		return false;
	}

	m_pPhone->CloseComport();

	TestPassLog(_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("_"),_T("EndCall Pass"));*/

	return true;
}

 bool CBaseBandTestProc::PopMsg()
 {

	 MessageBox(m_hMsgHandlingWnd,m_strMsg,"PopMSG",MB_OK);
	 return true;
 }
bool CBaseBandTestProc::CheckFlag()
{
    int  iErrorcode;
	unsigned char NVItemValue[128];
	int iBytePos;
	int iBitPos;
	CString strMsg;
	 iBytePos=m_iStationFlag/8;
	 iBitPos=m_iStationFlag%8;
    int iIsPass;

	
    LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}

     if((iErrorcode=m_pPhone->ReadNV(m_iFlagNVID,NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Read NV :%d  Fail!",m_iFlagNVID);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
    
    iIsPass=NVItemValue[iBytePos] & ((1<<iBitPos));

	if(iIsPass)
	{
		strMsg="Check Station "+CStr::IntToStr(m_iStationFlag)+" Flag Pass";
        CalPassLog(_T("_"),_T("_"),strMsg);
		return true;
	}
	else
	{
        strMsg=("Check Station ")+CStr::IntToStr(m_iStationFlag)+" Flag Fail";
        CalFailLog(_T("_"),_T("_"),1211,strMsg); 
		return false;
	}
	
	
}
bool CBaseBandTestProc::WriteFlag() 
{
    int  iErrorcode;
	unsigned char NVItemValue[128];
	int iBytePos;
	int iBitPos;
	CString strMsg;
	 iBytePos=m_iStationFlag/8;
	 iBitPos=m_iStationFlag%8;


	
    LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}

     if((iErrorcode=m_pPhone->ReadNV(m_iFlagNVID,NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Read NV :%d  Fail!",m_iFlagNVID);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	 if(!m_iIsSet)
		  NVItemValue[iBytePos]=NVItemValue[iBytePos]&(~(1<<iBitPos)); 
	 else
          NVItemValue[iBytePos]=NVItemValue[iBytePos] | (1<<iBitPos);

     
	  if((iErrorcode=m_pPhone->WriteNV(m_iFlagNVID,NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Write NV :%d  Fail!",m_iFlagNVID);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	return true;
}
bool CBaseBandTestProc::QRD_FlagOp_Func()
{
    int  iErrorcode;
	unsigned char NVItemValue[128];

	CString strMsg;

	
    LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}

     if((iErrorcode=m_pPhone->ReadNV(m_iFlagNVID,NVItemValue,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Read NV :%d  Fail!",m_iFlagNVID);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	if(m_iQRD_FlagOp_Enum==0) //check
	{
		char uFlag=(char)NVItemValue[m_iBytePosQRD];
		if((uFlag-'P')==0)
		{
		strMsg="Check Station "+CStr::IntToStr(m_iBytePosQRD)+" Flag Pass";
        CalPassLog(_T("_"),_T("_"),strMsg);
		return true;
		}
		else
		{
            strMsg.Format("Check Station %d Fail. Flag=%C",m_iBytePosQRD,uFlag);
	
         CalFailLog(_T("_"),_T("_"),1211,strMsg); 
		 return false;
		}

	}
	else //write
	{
		
		if(m_iQRD_FlagOp_Enum==1) 
         NVItemValue[m_iBytePosQRD]='P';
		else if(m_iQRD_FlagOp_Enum==2)
		 NVItemValue[m_iBytePosQRD]='F';
		else
		 NVItemValue[m_iBytePosQRD]='U';
		 if((iErrorcode=m_pPhone->WriteNV(m_iFlagNVID,NVItemValue,128))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone Write NV :%d  Fail!",m_iFlagNVID);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}

	}
    
     
	 

	return true;
}
bool CBaseBandTestProc::WriteSN_QRD_Func()
{

   int  iErrorcode;
	unsigned char uiData[20]={0};
	unsigned char uiFlag[128]={0};
	char usLabelSN[20]={0};
   CString strMsg;
	LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}

	 strMsg.Format("Writing NV : %d ",m_iSN_NVID_QRD);
	 LogTrace(MSG_MID,strMsg)


	CString strHeader;
	strHeader=m_strSN.Mid(0,m_strSNHeader.GetLength());

	if(strHeader!=m_strSNHeader || m_strSN.GetLength()!=m_iSNLength)
	{
		strMsg.Format("SN Header not correct or length not right . Expected Header :%s  Expected Length :%d",m_strSNHeader,m_iSNLength);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=9999;
			CalFailLog(_T("_"),_T("_"),m_iErrorcode,strMsg);
			return false;
	}
	::SendMessage(m_hMsgHandlingWnd,WM_TRD_CALTEST_UpdateSN_PROC,0,(LPARAM)m_strSN.GetBuffer());


  
	strMsg.Format("Writing SN : %s",m_strSN);
	   LogTrace(MSG_MID,strMsg)

    sprintf(usLabelSN,"%s",m_strSN);
    for(int i=0;i<m_iSNLength;++i)
     uiData[i]=usLabelSN[i];
  
		 if((iErrorcode=m_pPhone->WriteNV(m_iSN_NVID_QRD,uiData,m_iSNLength))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Write NV :%d  Fail!",m_iSN_NVID_QRD);
		LogTrace(MSG_ERROR,strMsg)
	    m_iErrorcode=iErrorcode;
        CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
		 if (m_iClearAllFlag)
		 {
			 for (int iSNum=0;iSNum<m_iStationNum;++iSNum)
			 {
				 uiFlag[iSNum]='U';
			 }
			 if((iErrorcode=m_pPhone->WriteNV(m_iFlagNVIDforSN,uiFlag,128))!=PHONE_SUCCESS)
			 { 
				 strMsg.Format("Phone Write NV :%d  Fail!",m_iFlagNVIDforSN);
				 LogTrace(MSG_ERROR,strMsg)
					 m_iErrorcode=iErrorcode;
				 CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				 return false;
			 }

		 }
    
    m_strSN.Format("%s",uiData);

    
    CalPassLog("_","_","Write SN Pass!");
    
	 strMsg.Format("Waiting for Next item ,delay is %d ms",m_iDelayForNextItemMs);
	  LogTrace(MSG_MID,strMsg)
	Sleep(m_iDelayForNextItemMs);
	return true;     
	
  return true;
}
bool CBaseBandTestProc::ReadSN_QRD_Func()
{
//	CString strIniPath=m_LossFinder.GetCurrentXmlToIni(m_strSN);
//	m_LossFinder.CompareSNSameTrue("C:\\WCDMA_Calloss.ini","000001111122222");
//	m_LossFinder.GetPurposeOfLossIni("C:\\WCDMA_Calloss.ini","");
	int  iErrorcode;
	unsigned char uiData[128]={0};
   CString strMsg;
	LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}

	 strMsg.Format("Reading NV : %d ",m_iSN_NVID_QRD);
	 LogTrace(MSG_MID,strMsg)

   if((iErrorcode=m_pPhone->ReadNV(m_iSN_NVID_QRD,uiData,128))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Read NV :%d  Fail!",m_iSN_NVID_QRD);
		LogTrace(MSG_ERROR,strMsg)
	    m_iErrorcode=iErrorcode;
        CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
    
    m_strSN.Format("%s",uiData);

    ::SendMessage(m_hMsgHandlingWnd,WM_TRD_CALTEST_UpdateSN_PROC,0,(LPARAM)m_strSN.GetBuffer());
    CalPassLog("_","_","Read SN Pass!");
    
	 strMsg.Format("Waiting for Next item ,delay is %d ms",m_iDelayForNextItemMs);
	  LogTrace(MSG_MID,strMsg)
	Sleep(m_iDelayForNextItemMs);
	return true;     
	
  return true;
}
bool CBaseBandTestProc::UploadQCN()
{
	int iErrorcode;
	LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		return false;
	}

	char crPath[1024];
	ZeroMemory(crPath,sizeof(crPath));
	::GetModuleFileName(NULL,crPath,1024);
	*_tcsrchr(crPath,'\\')=0;
	strcat(crPath,"\\QCNFiles\\upload.qcn");
	//m_pPhone->ConfigureCallBacks(NULL,m_pPhone->generalDownloadEvent,NULL);
	if((iErrorcode=m_pPhone->UploadQCNFile(crPath,"000000",m_iQCNAutoRestore,m_iQCNSkipReset,m_iQCNAllowESNMismatch,m_iQCNIgnorePM))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Upload QCN Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Upload QCN Fail!");
		return false;
	}
	 CalPassLog("_","_","Upload QCN Pass!");

	return true;
}

bool CBaseBandTestProc::ReloadNV_Func()
{
	int iErrorcode;
	LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		return false;
	}

	LogTrace(MSG_MID,_T(" ReloadNV!"))
	if((iErrorcode=m_pPhone->ReloadNV())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Reload NV Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Reload NV Fail!");
		return false;
	}

	return true;
}
bool CBaseBandTestProc::SetPhoneMode()
{
	int iErrorcode;
	LogTrace(MSG_MID,_T(" Open Comport....!"))
		if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
		}

		LogTrace(MSG_MID,_T(" SetPhoneMode!"))
			if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
			{
				LogTrace(MSG_ERROR,_T(" SetPhoneMode Fail!"))
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode," SetPhoneMode Fail!");
				return false;
			}
			CalPassLogEx(_T("_"),_T("_")," SetPhoneMode Pass!"," SetPhoneMode")

			return true;
}

bool CBaseBandTestProc::CWriteNVFunc()
{
	int  iErrorcode;	
	unsigned char uiData[128]={0};
	CString strMsg;

	LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		return false;
	}

	for (int i=0;i<m_vNV_Value.size();i++)
	{
        uiData[i]=m_vNV_Value[i];
	}
	if((iErrorcode=m_pPhone->WriteNV(m_iNV_ID,uiData,sizeof(uiData)))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone WriteNV :%d  Fail!",m_iNV_ID);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;

		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
    strMsg.Format("Phone WriteNV :%d  Pass!",m_iNV_ID);	
    CalPassLog(_T("_"),_T("_"),strMsg);

	LogTrace(MSG_MID,_T(" Close Comport....!"))
	m_pPhone->CloseComport();
    
	return true;
}
bool CBaseBandTestProc::WriteSNFunc()
{
	int  iErrorcode;
	unsigned char uiData1[9]={0};
	unsigned char uiData2[9]={0};
    char usLabelSN[20]={0};
   
	CString strMsg;

	CString strHeader;
	strHeader=m_strSN.Mid(0,m_strSNHeader.GetLength());

	if(strHeader!=m_strSNHeader || m_strSN.GetLength()!=m_iSNLength)
	{
		strMsg.Format("SN Header not correct or length not right . Expected Header :%s  Expected Length :%d",m_strSNHeader,m_iSNLength);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=9999;
			CalFailLog(_T("_"),_T("_"),m_iErrorcode,strMsg);
			return false;
	}


    LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}

	

	if(m_bIsClearFlagNV)
	{

		 strMsg.Format("Clearing NV=%d All Flag",m_iFlagNV);
		   LogTrace(MSG_MID,strMsg)
			   unsigned char ucValue[128]={0};

			if((iErrorcode=m_pPhone->WriteNV(m_iFlagNV,ucValue,sizeof(ucValue)))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("Phone WriteNV :%d  Fail!",m_iFlagNV);
			LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;

			CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
			return false;
		}


	}

	strMsg.Format("Writing SN : %s",m_strSN);
	   LogTrace(MSG_MID,strMsg)

   sprintf(usLabelSN,"%s",m_strSN);

   for(int i=0;i<8;++i)
   {
	  uiData1[i]=usLabelSN[i];

   }

     for(int i=0;i<7;++i)
   {
	  uiData2[i]=usLabelSN[i+8];

   }

	 if((iErrorcode=m_pPhone->WriteNV(m_iSN_NVID1,uiData1,8))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone WriteNV :%d  Fail!",m_iSN_NVID1);
		LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;

			    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
	}
	  if((iErrorcode=m_pPhone->WriteNV(m_iSN_NVID2,uiData2,7))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone WriteNV :%d  Fail!",m_iSN_NVID2);
		LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
	}

   
	 strMsg.Format("Waiting for Next item ,delay is %d ms",m_iDelayForNextItemMs);
	   LogTrace(MSG_MID,strMsg)
	Sleep(m_iDelayForNextItemMs);
	return true;
  
}
bool CBaseBandTestProc::ReadSNFunc()
{
	int  iErrorcode;
	unsigned char uiData1[9]={0};
	unsigned char uiData2[9]={0};
	CString strMsg;

    LogTrace(MSG_MID,_T(" Open Comport....!"))
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}
	  //LogTrace(MSG_MID,_T(" EnterFTM Mode....!"))
     /*if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           LogTrace(MSG_ERROR,_T("Phone Enter FTM Mode Fail!"))
				m_iErrorcode=iErrorcode;

			    CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
				return false;
	}
	*/
     
	 strMsg.Format("Reading NV : %d and %d",m_iSN_NVID1,m_iSN_NVID2);
	   LogTrace(MSG_MID,strMsg)
	 if((iErrorcode=m_pPhone->ReadNV(m_iSN_NVID1,uiData1,8))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Read NV :%d  Fail!",m_iSN_NVID1);
		LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;

			    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
	}
	  if((iErrorcode=m_pPhone->ReadNV(m_iSN_NVID2,uiData2,7))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Read NV :%d  Fail!",m_iSN_NVID2);
		LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
	}

    m_strSN.Format("%s%s",uiData1,uiData2);

	::SendMessage(m_hMsgHandlingWnd,WM_TRD_CALTEST_UpdateSN_PROC,0,(LPARAM)m_strSN.GetBuffer());
	 
    CalPassLog("_","_","Read SN Pass!");
    
	 strMsg.Format("Waiting for Next item ,delay is %d ms",m_iDelayForNextItemMs);
	   LogTrace(MSG_MID,strMsg)
	Sleep(m_iDelayForNextItemMs);
	return true;
}


 bool CBaseBandTestProc::InitData()
 {
	
	 return true;
 }