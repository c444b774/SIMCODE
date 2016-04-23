#include "stdafx.h"
#include "WCDMACableLossCal.h"

RF_IMPLEMENT_DYNCREATE(CWCDMACableLossCal)

CWCDMACableLossCal::CWCDMACableLossCal()
{
	m_mapClassFunc[_T("CWCDMALossMainFunc")]=&CWCDMACableLossCal::CWCDMACableLossCalMainFunc;
	m_mapClassFunc[_T("CWCDMALossFunc")]=&CWCDMACableLossCal::CWCDMACableLossCalFunc;
	m_mapClassFunc[_T("MakeGoldenSemple")]=&CWCDMACableLossCal::WMakeGoldenSemple;
	m_mapClassFunc[_T("SetCableLoss")]=&CWCDMACableLossCal::WSetCableLoss;
}

CWCDMACableLossCal::~CWCDMACableLossCal()
{
	
}

bool CWCDMACableLossCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CWCDMACableLossCal::Handle()
{
	if(!DoProcess())
	{
      return false;
	}
		
	return true;
}

bool CWCDMACableLossCal::CWCDMACableLossCalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{

		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CWCDMACableLossCal::WMakeGoldenSemple()
{
	if (!WMeasPower())
	{
		return false;
	}

	m_dVtrGoldenPwr.clear();
	m_dVtrGoldenPwr=m_dVtrMeasPwr;
	if (!WriteGoldenPower())
	{
		CalFailLog(m_strTestBand,"-",1003,"SetCableLoss Fail");
		return false;
	}	
	return true;
}
bool CWCDMACableLossCal::WSetCableLoss()
{
	CStringVtr cvChannel;
	CStringVtr cvLoss;
	CStringStringMap mapString2String;

	if (!WMeasPower())
	{
		return false;
	}
	if (!ReadGoldenPower())
	{
		return true;
	}
	double dTemp;
	CString strTemp,strTemp1;
	for (int i=0;i<3;i++)
	{
		dTemp=m_dVtrGoldenPwr[i]-m_dVtrMeasPwr[i]+m_vCableLoss[i];
		strTemp.Format("%.2f",dTemp);
		strTemp1.Format("cableloss=%.2f",dTemp);
		TestPassLog(m_strTestBand,"_","_","_",strTemp,"_",strTemp1);
		cvLoss.push_back(strTemp);
	}


	cvChannel.clear();
	cvChannel.push_back("0");cvChannel.push_back("1");cvChannel.push_back("2");
	CStr::MakeVector2Map(cvChannel,cvLoss,mapString2String);	
	if(!m_LossFinder.UpdateLossIniFromMap(m_strTestBand,mapString2String))
	{
		CalFailLog("_","_",1003,"Cable loss ini not exist");
		return false;
	}
	CalPassLog(m_strTestBand,"-","SetCableLoss pass");
	return true;
}
bool CWCDMACableLossCal::WMeasPower()
{
	unsigned char ucTFCIConfig[4]={0,1,2,3};

	if(m_strTesterDevice=="A8960")
	{
		ucTFCIConfig[1]=2;
		ucTFCIConfig[2]=1;
	}
	int iDLChannel,iULChannel=m_iTestChannelList[0];
	int iErrorcode;
	iDLChannel=CWCDMABandInfo::GetDLChannel(m_iTestBand,iULChannel);


	if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestInitWCDMAtest(m_strDeviceAddr))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Init WCDMA Test Dev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("Init WCDMA Test Dev Fail!"))
			return false;
	}
	if(!SetWCDMATestLOSS())
	{
		LogTrace(MSG_ERROR,_T("SetWCDMATestLOSS Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("SetWCDMATestLOSS Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestHandOver(m_iTestBand,iULChannel))!=DEVICE_SUCCESS)
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
		CalFailLog(_T("-"),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("WCDMA Test Phone BER_AcquirePilot Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCDMA_BER_SetupRMC_DCH(FTM_WCDMA_BER_RMC_Type12_2kpbs,33,0,FTM_WCDMA_BER_PCA_Type_Alg1,FTM_WCDMA_BER_PCA_Size_1dB,0,9))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("WCDMA Test Phone BER_SetupRMC_DCH Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("WCDMA Test Phone BER_SetupRMC_DCH Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCDMA_AGC_START_LOG())!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("FTM_WCDMA_AGC_START_LOG"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("FTM_WCDMA_AGC_START_LOG"))
			return false;
	}
	m_dVtrMeasPwr.clear();

	for (int chIndex=0;chIndex<m_iTestChannelList.size();chIndex++)  
	{
		CString str,strChan;
		strChan.Format("%d",m_iTestChannelList[chIndex]);	
		iErrorcode=CWCDMACableLossCal::CWCDMATestHandOver(m_iTestBand,m_iTestChannelList[chIndex]);
		if (!iErrorcode)
		{
			return false;
		}
		iErrorcode=CWCDMACableLossCal::CWCDMATestMeasureALL(m_iTestBand,m_iTestChannelList[chIndex]);
		if (!iErrorcode)
		{
			return false;
		}		
	}
	m_pFuncWCDMATestDev->Deivce_Exit();
//****************************
	m_pPhone->FTM_WCDMA_EndCall();

	m_pPhone->CloseComport();
	return true;
}
bool CWCDMACableLossCal::WriteGoldenPower()
{
	int  iErrorcode;
	unsigned char uiData[128]={0},uiFlagData[128]={0};
	CString strMsg;

	LogTrace(MSG_MID,_T(" Open Comport....!"))
		if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
		}

		strMsg.Format("Reading NV : %d ",2498);
		LogTrace(MSG_MID,strMsg)

			if((iErrorcode=m_pPhone->ReadNV(2498,uiData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Read NV :2498  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}


			int iNVoffset=0;
			switch (m_iTestBand)
			{
			case WCDMA_IMT_BAND_ID:
				iNVoffset=36;
				break;
			case WCDMA_PCS_BAND_ID:
				iNVoffset=42;
				break;	
			case WCDMA_850_BAND_ID:
				iNVoffset=48;
				break;	
			case WCDMA_900_BAND_ID:
				iNVoffset=54;
				break;	
			default:
				strMsg=_T("unkown band!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;

			}
			for (int i=0;i<3;i++)
			{
				double dGoldenPower=m_dVtrGoldenPwr[i];
				int n1 = (int)dGoldenPower;
				int n2 = (int)(dGoldenPower * 100.0) - n1 * 100;
				uiData[iNVoffset++] = (byte)n1;
				uiData[iNVoffset++] = (byte)n2;		
			}
			SYSTEMTIME st;
			::GetLocalTime(&st);
			uiData[120]=(byte)(st.wYear-2000);
			uiData[121]=(byte)st.wMonth;
			uiData[122]=(byte)st.wDay;
			uiData[123]=(byte)st.wHour;
			uiData[124]=(byte)st.wMinute;
			uiData[125]=(byte)st.wSecond;

			byte CheckSum126 = 0;
			byte CheckSum127 = 0;
			for (int index = 0; index < 63; index++)
			{
				CheckSum126 ^= uiData[2*index];
				CheckSum127 ^= uiData[2 * index+1];
			}
			for (int index=0;index<64;index++)
			{
				CheckSum126 ^= uiFlagData[2*index];
				CheckSum127 ^= uiFlagData[2 * index+1];
			}
			uiData[126] = CheckSum126;
			uiData[127] = CheckSum127;

			if((iErrorcode=m_pPhone->WriteNV(2498,uiData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Write NV :2498  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}
			if((iErrorcode=m_pPhone->WriteNV(2499,uiFlagData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Write NV :2499  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}

			if((iErrorcode=m_pPhone->WriteEFS(3000))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone WriteEFS  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}
			m_pPhone->CloseComport();
			TestPassLogEx(m_strTestBand,_T("-"),_T("-"),_T("-"),_T("-"),_T("-"),_T("WriteGoldNV PASS"),"WriteGoldNV")

				return true;
}
bool CWCDMACableLossCal::ReadGoldenPower()
{
	int  iErrorcode;
	unsigned char uiData[128]={0},uiFlagData[128]={0};
	CString strMsg;
	LogTrace(MSG_MID,_T(" Open Comport....!"))
		if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
		}

		strMsg.Format("Reading NV : %d ",2498);
		LogTrace(MSG_MID,strMsg)

			if((iErrorcode=m_pPhone->ReadNV(2498,uiData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Read NV :2498  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}
			if((iErrorcode=m_pPhone->ReadNV(2499,uiFlagData,128))!=PHONE_SUCCESS)
			{ 
				strMsg=_T("Phone Read NV :2499  Fail!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}
			m_pPhone->CloseComport();

			byte CheckSum126 = 0;
			byte CheckSum127 = 0;
			for (int index = 0; index < 63; index++)
			{
				CheckSum126 ^= uiData[2 * index];
				CheckSum127 ^= uiData[2 * index + 1];
			}
			for (int index=0;index<64;index++)
			{
				CheckSum126 ^= uiFlagData[2*index];
				CheckSum127 ^= uiFlagData[2 * index+1];
			}
			if ((uiData[126] != CheckSum126) || (uiData[127] != CheckSum127))
			{
				strMsg=_T("Golden NV CheckSum is not right!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;
			}

			strMsg.Format("Golden Sample modified time:%d-%d-%d %d:%d:%d",uiData[120],uiData[121],uiData[122],uiData[123],uiData[124],uiData[125]);
			LogTrace(MSG_MID,strMsg)
				double dGoldenPower=0;
			int iNVoffset=0;
			switch (m_iTestBand)
			{
			case WCDMA_IMT_BAND_ID:
				iNVoffset=36;
				break;
			case WCDMA_PCS_BAND_ID:
				iNVoffset=42;
				break;	
			case WCDMA_850_BAND_ID:
				iNVoffset=48;
				break;	
			case WCDMA_900_BAND_ID:
				iNVoffset=54;
				break;	
			default:
				strMsg=_T("unkown band!");
				LogTrace(MSG_ERROR,strMsg)
					m_iErrorcode=iErrorcode;
				CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
				return false;

			}
			m_dVtrGoldenPwr.clear();
			for (int i=0;i<3;i++)
			{
				dGoldenPower=(double)uiData[iNVoffset+2*i]+(double)uiData[iNVoffset+2*i+1]/100.0;
				m_dVtrGoldenPwr.push_back(dGoldenPower);
				strMsg.Format("GoldenPower:%.2f",dGoldenPower);
				CalPassLog(m_strTestBand,CStr::IntToStr(i+1),strMsg);
			}
			strMsg.Format("Band%d GoldenPower:%.2f,%.2f,%.2f",m_iTestBand,m_dVtrGoldenPwr[0],m_dVtrGoldenPwr[1],m_dVtrGoldenPwr[2]);
			LogTrace(MSG_MID,strMsg)


				return true;
}
bool CWCDMACableLossCal::CWCDMACableLossCalFunc()
{
	bool iErrorcode;
	int iFailflag=0;

	CString strIniPath=m_LossFinder.GetCurrentXmlToIni(m_strSN);
	if (strIniPath.Find(_T("No_GoldenFile"))!=-1)
	{
		LogTrace(MSG_ERROR,_T("GET Golden file Fail!"))
			return false;
	}
	m_IsToMakeSample=m_LossFinder.GetPurposeOfLossIni(strIniPath,m_strSN);

	if (!SetWCDMATestLOSS())
	{
		LogTrace(MSG_ERROR,_T("SetWCDMATestLOSS Fail!"))
		TestFailLog(m_strTestBand,"_",LOSS_SET_FAIL,"_","_","_","_","Set CableLOSS Fail");
		return false;
	}

	m_dVtrMeasPwr.clear();
	m_strVtrLossRes.clear();
	int nIndex=0;
	for (int chIndex=0;chIndex<m_iTestChannelList.size();chIndex++)  
	{
		CString str,strChan;
		strChan.Format("%d",m_iTestChannelList[chIndex]);
		str.Format("%d",nIndex);
		iErrorcode=CWCDMACableLossCal::CWCDMATestHandOver(m_iTestBand,m_iTestChannelList[chIndex]);
		if (m_bIsStopWhenFail&&!iErrorcode)
		{
			return false;
		}
		iErrorcode=CWCDMACableLossCal::CWCDMATestMeasureALL(m_iTestBand,m_iTestChannelList[chIndex]);
		if (!iErrorcode)
		{
			if (m_bIsStopWhenFail)
			{
				return false;
			} 
			else
			{
				iFailflag++;
			}
		}		

		nIndex++;
	}
	if (iFailflag>0)
	{
		return false;
	}

	if (m_IsToMakeSample==1)
	{
		m_LossFinder.WriteGoldenPowerToIni("WCDMA",m_iTestBand,m_dVtrMeasPwr,strIniPath);
	}
	else
	{
		m_LossFinder.GetGoldenPowerFromIni("WCDMA",m_iTestBand,m_dVtrGoldenPwr,strIniPath);

		double dTemp;
		CString strTemp,strTemp1;
		for (int i=0;i<m_dVtrMeasPwr.size();i++)
		{
			dTemp=m_dVtrGoldenPwr[i]-m_dVtrMeasPwr[i]+m_vCableLoss[i];
			strTemp.Format("%.2f",dTemp);
			strTemp1.Format("Pwr:Gold=%.2f,Meas=%.2f,GoldCable=%.2f",m_dVtrGoldenPwr[i],m_dVtrMeasPwr[i],m_vCableLoss[i]);
			TestPassLog(m_strTestBand,"_","_","_",strTemp,"_",strTemp1);
			m_strVtrLossRes.push_back(strTemp);
		}

		CStringStringMap mapString2String;
		m_strVtrChan.clear();

		if (m_IsSaveToIni)
		{
			m_strVtrChan.push_back("0");m_strVtrChan.push_back("1");m_strVtrChan.push_back("2");
			CStr::MakeVector2Map(m_strVtrChan,m_strVtrLossRes,mapString2String);
			m_strTestBand.Format("W%d",m_iTestBand);
			if(!m_LossFinder.UpdateLossIniFromMap(m_strTestBand,mapString2String))
			{
				CalFailLog("_","_",1003,"Cable loss ini not exist");
				return false;
			}
		}
		else
		{
			s_UpdateXMLLossPara sXmlLoss;
			sXmlLoss.strXmlPath="C:\\Program Files\\Qualcomm\\QDART\\Databases\\CalDB_NET.xml";
			sXmlLoss.strType=m_strType;

			for (int iChIndex=0;iChIndex<m_iTestChannelList.size();iChIndex++)
			{
				CString strTemp;
				strTemp.Empty();
				strTemp.Format("%.1f",CWCDMABandInfo::ArfcnToHz(m_iTestBand,m_iTestChannelList[iChIndex],1));
				m_strVtrChan.push_back(strTemp);
			}
			CStr::MakeVector2Map(m_strVtrChan,m_strVtrLossRes,mapString2String);

			sXmlLoss.mapFreq2Loss=mapString2String;
			sXmlLoss.iIsUplink=1;

			SendMessage(m_hMsgHandlingWnd,WM_UPDATEXMLLOSS,0,LPARAM(&sXmlLoss));

			m_strVtrChan.clear();
			mapString2String.clear();
			for (int iChIndex=0;iChIndex<m_iTestChannelList.size();iChIndex++)
			{
				CString strTemp;
				strTemp.Empty();
				strTemp.Format("%.1f",CWCDMABandInfo::ArfcnToHz(m_iTestBand,CWCDMABandInfo::GetDLChannel(m_iTestBand,m_iTestChannelList[iChIndex]),0));
				m_strVtrChan.push_back(strTemp);
			}
			CStr::MakeVector2Map(m_strVtrChan,m_strVtrLossRes,mapString2String);

			sXmlLoss.mapFreq2Loss=mapString2String;
			sXmlLoss.iIsUplink=0;

			SendMessage(m_hMsgHandlingWnd,WM_UPDATEXMLLOSS,0,LPARAM(&sXmlLoss));
		}


	}

	return true;

}

 bool CWCDMACableLossCal::InitData(
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

	 itrFind=pcSettingMap->find(_T("IsSaveToIni"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_LOW,"Not Find 'IsSaveToIni' from ini file,use default true");
		 m_IsSaveToIni=1;
	 }
	 else
	 {
		 m_IsSaveToIni=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("strNodeType"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_LOW,_T("Not Find strNodeType,default WCDMA"));
		 m_strType="WCDMA";
	 }
	 else
	 {
		 m_strType=itrFind->second;
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

	 itrFind=pcSettingMap->find(_T("MeasureCount"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'MeasureCount' from ini file,Use default 10 !");
		 m_iMeasureCount=50;

	 }
	 else
	 {
		 m_iMeasureCount=CStr::StrToInt(itrFind->second);
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
	
	 InitData();
	 return true;
 }

 bool CWCDMACableLossCal::InitData()
 {
	 m_pFuncWCDMATestDev=m_piTesterDevice->m_piFuncWCDMATest;
	 return true;
 }
 bool CWCDMACableLossCal::SetWCDMATestLOSS()
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
 bool CWCDMACableLossCal::CWCDMATestHandOver(int iBand,int iULChannel)
 {
	 unsigned char ucTFCIConfig[4]={0,1,2,3};

	 if(m_strTesterDevice=="A8960")
		 ucTFCIConfig[1]=2;
	 ucTFCIConfig[2]=1;

	 int iDLChannel;
	 int iErrorcode;
	 iDLChannel=CWCDMABandInfo::GetDLChannel(iBand,iULChannel);


	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestHandOver(iBand,iULChannel))!=DEVICE_SUCCESS)
	 {
		 LogTrace(MSG_ERROR,_T("WCDMA Test Dev HandOver Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T("-"),_T("-"),iErrorcode,_T("WCDMA Test Dev HandOver Fail!"))
			 return false;
	 }


	 if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(FTM_MODE_ID_WCDMA))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("Set phone FTM_MODE_ID_WCDMA fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("Set phone FTM_MODE_ID_WCDMA fail"))
			 return false;
	 }

	 if((iErrorcode=m_pPhone->FTM_WCDMA_BER_Handover(3,33,0,0,0,0,9,8,15,iDLChannel))!=PHONE_SUCCESS)
	 {           
		 LogTrace(MSG_ERROR,_T("WCDMA Test Phone BER_Handover Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("WCDMA Test Phone BER_Handover Fail!"))
			 return false;
	 }
	 CalPassLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T("WCDMA_NS HandOver Pass"))
		 return true;

 }

 bool CWCDMACableLossCal::CWCDMATestMeasureALL(int iBand,int iULChannel)
 {
	 int iErrorcode;
	 double dMeasPower;
	 CString strMsg;
	 int ifailflag=0;
	 if((iErrorcode=m_pFuncWCDMATestDev->IWCDMATestMaxPower(m_iMeasureCount,&dMeasPower))!=DEVICE_SUCCESS)
	 {
		 LogTrace(MSG_ERROR,_T("WCDMA Test Measure ALL Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),iErrorcode,_T("WCDMA Test Measure ALL Fail!"))
			 return false;
	 }
 
	 if (m_dMaxPowerLimit.InRange(dMeasPower))
	 {
		 TestPassLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dMeasPower)),_T("dBm"),_T("MaxPower PASS "))
	 } 
	 else
	 {
		 ifailflag++;
		 TestFailLog(_T(CStr::IntToStr(iBand)),_T(CStr::IntToStr(iULChannel)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dMeasPower)),_T("dBm"),_T("MaxPower FAIL"))
	 }


	 if (ifailflag>0)
	 {
		 return false;
	 }

	 m_dVtrMeasPwr.push_back(dMeasPower);

	 return true;

 }
