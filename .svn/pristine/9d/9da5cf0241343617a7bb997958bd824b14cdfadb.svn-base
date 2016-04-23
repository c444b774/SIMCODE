
#include "stdafx.h"
#include "CCableLossFinder.h"

 #pragma warning(disable : 4715)
RF_IMPLEMENT_DYNCREATE(CCableLossFinder)
 
PILogger CCableLossFinder::m_piLogger = NULL;

void CCableLossFinder::TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg)
{
	if (m_piLogger)
		m_piLogger->TraceLog(lpszModule, emLevel,lpszFileName, uiLine, lpszMsg);
}

void CCableLossFinder::FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg)
{
	if (m_piLogger)
		m_piLogger->FactoryLog(iProcesCode, strBand, strChannel, iErrorCode, strUL, strDL, strMeasured, strUnit, bPass, strMsg);
}

void CCableLossFinder::CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage)
{
	if (m_piLogger)
	{
		m_piLogger->CommandLog(lpszType, lpszMessage);
	}

}

bool CCableLossFinder::InitData(
	PCStringStrMap     pcSettingMap,
	CRFObjectMap&   cObjectMap
	)
{
	return true;
}
 
bool CCableLossFinder::InitData()
{
	
	return true;
}
 
CString CCableLossFinder::GSMIntToStr(const int iBand)
{
	ASSERT(CGSMBandInfo::CheckVaildBand(iBand));
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			return _T("GSM850");
		case GSM_EGSM_BAND_ID:
			return _T("GSM900");
		case GSM_DCS_BAND_ID:
			return _T("GSM1800");
		case GSM_PCS_BAND_ID:
			return _T("GSM1900");
	}
	ASSERT(0);
	return _T("");
}
CString CCableLossFinder::WirelessGSMIntToStr(const int iBand)
{
	ASSERT(CGSMBandInfo::CheckVaildBand(iBand));
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			return _T("WirelessGSM850");
		case GSM_EGSM_BAND_ID:
			return _T("WirelessGSM900");
		case GSM_DCS_BAND_ID:
			return _T("WirelessGSM1800");
		case GSM_PCS_BAND_ID:
			return _T("WirelessGSM1900");
	}
	ASSERT(0);
	return _T("");
}
CString CCableLossFinder::WirelessWCDMAIntToStr(const int iBand)
{
	ASSERT(CWCDMABandInfo::CheckVaildBand(iBand));
	switch(iBand)
	{
		case WCDMA_850_BAND_ID:
			return _T("WirelessWCDMA850");
		case WCDMA_900_BAND_ID:
			return _T("WirelessWCDMA900");
		case WCDMA_PCS_BAND_ID:
			return _T("WirelessWCDMA2100");
		case WCDMA_IMT_BAND_ID:
			return _T("WirelessWCDMA1900");
		case WCDMA_AWS_BAND_ID:
			return _T("WirelessWCDMA1700");
	}
	ASSERT(0);
	return _T("");
}
CString CCableLossFinder::WCDMAIntToStr(const int iBand)
{
	ASSERT(CWCDMABandInfo::CheckVaildBand(iBand));
	switch(iBand)
	{
		case WCDMA_850_BAND_ID:
			return _T("UMTSBand5");
		case WCDMA_900_BAND_ID:
			return _T("UMTSBand8");
		case WCDMA_AWS_BAND_ID:
			return _T("UMTSBand4");
		case WCDMA_PCS_BAND_ID:
			return _T("UMTSBand2");
		case WCDMA_IMT_BAND_ID:
			return _T("UMTSBand1");
	}
	ASSERT(0);
	return _T("");
}
 

double CCableLossFinder::GetBTLoss(int iChannel)
{
	CStringVtrItr itr;
	bool bFound = false;
	for (itr = m_pvRFCableMapPair->begin(); itr != m_pvRFCableMapPair->end(); ++itr)
	{
		if ( itr->first == _T("BT"))
		{
			bFound = true;
			break;
		}
	}
	if (bFound)
	{
		CStringStringMapItr itrMap;
		for (itrMap = (itr->second).begin(); itrMap != (itr->second).end(); ++itrMap)
		{
			if (itrMap->first == CStr::IntToStr(iChannel))
			{
				return CStr::StrToFloat(itrMap->second);
			}
		}
		
	}
	
	return 0;
}


double CCableLossFinder::GetWLANLoss(int iChannel)
{
	CStringVtrItr itr;
	bool bFound = false;
	for (itr = m_pvRFCableMapPair->begin(); itr != m_pvRFCableMapPair->end(); ++itr)
	{
		if ( itr->first == _T("WLAN"))
		{
			bFound = true;
			break;
		}
	}
	if (bFound)
	{
		CStringStringMapItr itrMap;
		for (itrMap = (itr->second).begin(); itrMap != (itr->second).end(); ++itrMap)
		{
			if (itrMap->first == CStr::IntToStr(iChannel))
			{
				return CStr::StrToFloat(itrMap->second);
			}
		}
		
	}
	
	return 0;
}
bool CCableLossFinder::GetCDMALoss(const CString & iBand,int iChannelTYpe,double & dLoss)
{
    CStringVtrItr itr;
	bool bFoundBand = false;
	bool bFoundChannel=false;
	for (itr = m_pvRFCableMapPair->begin(); itr != m_pvRFCableMapPair->end(); ++itr)
	{
		if ( itr->first==iBand)
		{
			bFoundBand = true;
			break;
		}
	}
	if(!bFoundBand)
		return false;

		CStringStringMapItr itrMap;
		for (itrMap = (itr->second).begin(); itrMap != (itr->second).end(); ++itrMap)
		{
			if (itrMap->first == CStr::IntToStr(iChannelTYpe))
			{
				bFoundChannel=true;
				dLoss=CStr::StrToFloat(itrMap->second);
				break;
			}
		}
		if(!bFoundChannel)
			return false;
	   return true;
}
bool  CCableLossFinder::GetWCDMALoss(const CString & iBand,int iChannelTYpe,double & dLoss)
{
    CStringVtrItr itr;
	bool bFoundBand = false;
	bool bFoundChannel=false;
	for (itr = m_pvRFCableMapPair->begin(); itr != m_pvRFCableMapPair->end(); ++itr)
	{
		if ( itr->first==iBand)
		{
			bFoundBand = true;
			break;
		}
	}
	if(!bFoundBand)
		return false;

		CStringStringMapItr itrMap;
		for (itrMap = (itr->second).begin(); itrMap != (itr->second).end(); ++itrMap)
		{
			if (itrMap->first == CStr::IntToStr(iChannelTYpe))
			{
				bFoundChannel=true;
				dLoss=CStr::StrToFloat(itrMap->second);
				break;
			}
		}
		if(!bFoundChannel)
			return false;
	   return true;
}

bool  CCableLossFinder::GetGSMLoss(const CString & iBand,int iChannelTYpe,double & dLoss)
{
	CStringVtrItr itr;
	bool bFoundBand = false;
	bool bFoundChannel=false;
	for (itr = m_pvRFCableMapPair->begin(); itr != m_pvRFCableMapPair->end(); ++itr)
	{
		if ( itr->first==iBand)
		{
			bFoundBand = true;
			break;
		}
	}
	if(!bFoundBand)
		return false;

	CStringStringMapItr itrMap;
	for (itrMap = (itr->second).begin(); itrMap != (itr->second).end(); ++itrMap)
	{
		if (itrMap->first == CStr::IntToStr(iChannelTYpe))
		{
			bFoundChannel=true;
			dLoss=CStr::StrToFloat(itrMap->second);
			break;
		}
	}
	if(!bFoundChannel)
		return false;
	return true;
}

double CCableLossFinder::GetDTVLoss(int iChannel)
{
  CStringVtrItr itr;
	bool bFound = false;
	for (itr = m_pvRFCableMapPair->begin(); itr != m_pvRFCableMapPair->end(); ++itr)
	{
		if ( itr->first == _T("DTV"))
		{
			bFound = true;
			break;
		}
	}
	if (bFound)
	{
		CStringStringMapItr itrMap;
		for (itrMap = (itr->second).begin(); itrMap != (itr->second).end(); ++itrMap)
		{
			if (itrMap->first == CStr::IntToStr(iChannel))
			{
				return CStr::StrToFloat(itrMap->second);
			}
		}
		
	}
	
	return 0;
}
double CCableLossFinder::GetGPSLoss()
{
	CStringVtrItr itr;
	bool bFound = false;
	for (itr = m_pvRFCableMapPair->begin(); itr != m_pvRFCableMapPair->end(); ++itr)
	{
		if ( itr->first == _T("GPS"))
		{
			bFound = true;
			break;
		}
	}
	if (bFound)
	{
		CStringStringMapItr itrMap;
		for (itrMap = (itr->second).begin(); itrMap != (itr->second).end(); ++itrMap)
		{
			if (itrMap->first == _T("GPSFixFreq"))
			{
				return CStr::StrToFloat(itrMap->second);
			}
		}
		
	}
	
	return 0;
}

 
CString CCableLossFinder::CDMAIntToStr(const int iBand)
{
	ASSERT(CCDMABandInfo::CheckVaildBand(iBand));
	switch(iBand)
	{
		case CDMA_BC0_BAND_ID:
			return _T("CDMA800");
		case CDMA_BC1_BAND_ID:
			return _T("CDMA1900");
	}
	ASSERT(0);
	return _T("");
}

bool CCableLossFinder::UpdateLossIniFromMap(const CString & strSecName,CStringStringMap str2strMapLossCH)
 {
     CString strKeyName;
	 CString strValue;
	 CString strDllPathName;
	 CString strDllLossFileName;
     char szTemp[_MAX_PATH];

	::GetModuleFileName(NULL, szTemp, _MAX_PATH);
	  strDllPathName.Format("%s",szTemp);
     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
	strDllLossFileName=strDllPathName+"\\SystemConfig\\LossConfig.ini";	

	if(fopen(strDllLossFileName,"r")==NULL)
	{
        CString strTemp1=strDllLossFileName+_T("  not exist");

		return false;
	}
	for(CStringStringMapItr itrMap=str2strMapLossCH.begin();itrMap!=str2strMapLossCH.end();++itrMap)
  {
	  strKeyName=itrMap->first;
	  strValue=itrMap->second;
	 
	  ::WritePrivateProfileString(strSecName,strKeyName,strValue,strDllLossFileName);

  }

	 return true;
}

CString CCableLossFinder::GetCurrentXmlToIni(CString strSN)
{
	CString strDllPathName;
	CString strTemp,strTempAim,strTemp1;
	_TCHAR _tKeyName[1000]={0};
	_TCHAR _tKeyValue[1000];
	FILE* fp1;
	CString strPath,strNewPath;
	int iRet;

	::GetModuleFileName(NULL, strDllPathName.GetBuffer(_MAX_PATH), _MAX_PATH);
	strDllPathName.ReleaseBuffer();
	strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));

	strDllPathName=strDllPathName+_T("\\SystemConfig\\SystemSetup.ini");
	if((fp1=fopen(strDllPathName,"r"))==NULL)
	{
		CString strTemp=strDllPathName+_T("  not exist");
		MessageBox(NULL,strTemp,"CurXml",MB_OK);
		return false;
	}

	::GetPrivateProfileString(_T("File Path"),_T("SequencePath"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
	strTemp=_tKeyValue;

	int pos=strTemp.ReverseFind(_T('\\'));
	strTemp=strTemp.Left(pos);
	strPath=strTemp+"\\Calloss.ini";

	::GetPrivateProfileString(_T("Cal Control"),_T("IsToMakeGoldenSample"),NULL,_tKeyValue,sizeof(_tKeyValue),strPath);
	strTempAim.Format("%s",_tKeyValue);
	strNewPath=strPath;
	iRet=CStr::StrToInt(strTempAim);

	int iPos=strPath.ReverseFind(_T('\\'));
	if (!strSN.IsEmpty())
	{
		strNewPath=strPath.Left(iPos)+_T('\\')+strSN+".ini";
	}
	else
		MessageBox(NULL,"SN is empty","Err",MB_OK);

	if(iRet==1)
	{
		strTemp1.Format("To Make Sample:%s!",strSN);
		LogTrace(MSG_LOW,strTemp1);

		::WritePrivateProfileString(_T("Sample"),_T("SN"),strSN,strPath);
		CopyFile(strPath,strNewPath,TRUE);
	}
	else
	{
		strTemp1.Format("ToTestCableLoss Using Sample:%s!",strSN);
		LogTrace(MSG_LOW,strTemp1);

		FILE *fp = fopen(strNewPath, "r") ;
		if(fp != NULL)
		{
			::WritePrivateProfileString(_T("Cal Control"),_T("IsToMakeGoldenSample "),strTempAim,strNewPath);
		}
		else
		{
			fclose(fp);
			return _T("No_GoldenFile");
		}
		fclose(fp);
	}
	fcloseall();
	return strNewPath;
}

//bool CCableLossFinder::ReviseXml(CString strXmlPath,CString strNodeList,CString strKey,CString strValue)
//{
//
//	CString NodeText;
//	XMLNode node;
//
//
//
//	m_pXml.Load("");
//	if(m_pXml.Load(strXmlPath)!=0)
//	{
//		CString strTemp=strXmlPath+_T("   not exist");
//		MessageBox(NULL,strTemp,"CurXml",MB_OK);
//		return false;
//	}
//
//	node=m_pXml.SearchNode("//Configurations/ProcessObjectSet/GNSFTProcessObjects");
//	m_pXml.SetNodeText(node,NodeText);
//	return true;
//}

bool CCableLossFinder::WriteGoldenPowerToIni(CString strBandType,int iBand,DblVtr dVtrGoldenPower,CString strPath)
{
	//CBandInfo.h
	CString strKey="";

	if(strBandType.Find(_T("GSM"))!=-1)
	{
		switch(iBand)
		{
		case GSM_850_BAND_ID:
			strKey=_T("GSM850");
			break;
		case GSM_EGSM_BAND_ID:
			strKey=_T("GSM900");
			break;
		case GSM_DCS_BAND_ID:
			strKey=_T("GSM1800");
			break;
		case GSM_PCS_BAND_ID:
			strKey=_T("GSM1900");
			break;
		default:
			strKey=_T("UnKnown Band");
			break;
		}
	}
	else if (strBandType.Find(_T("WCDMA"))!=-1)
	{
		switch(iBand)
		{
		case WCDMA_850_BAND_ID:
			strKey=_T("W850");
			break;
		case WCDMA_900_BAND_ID:
			strKey=_T("W900");
			break;
		case WCDMA_1500_BAND_ID:
			strKey=_T("W1500");
			break;
		case WCDMA_AWS_BAND_ID:
			strKey=_T("W1700");
			break;
		case WCDMA_PCS_BAND_ID:
			strKey=_T("W1900");
			break;
		case WCDMA_IMT_BAND_ID:
			strKey=_T("W2100");
			break;
		default:
			strKey=_T("UnKnown Band");
			break;
		}	
	}
	else if(strBandType.Find(_T("CDMA"))!=-1)
	{
		switch(iBand)
		{
		case CDMA_BC0_BAND_ID:
			strKey=_T("CDMA800");
			break;
		case CDMA_BC1_BAND_ID:
			strKey=_T("CDMA1900");
			break;
		default:
			strKey=_T("UnKnown Band");
			break;
		}
	}
	else
	{
		strKey=_T("UnKnown Band Type");
		MessageBox(NULL,strKey,"warning",MB_OK);
	}

	CString strTemp,strTempKey;
	int nNumPwr=dVtrGoldenPower.size();
	if (nNumPwr==2)
	{
		for (int i=0;i<2;i++)
		{
			switch(i)
			{
			case 0:
				strTempKey=strKey+"Pow_L";
				break;
			case 1:
				strTempKey=strKey+"Pow_H";
				break;
			default:
				break;
			}

			strTemp.Format("%.2f",dVtrGoldenPower[i]);
			::WritePrivateProfileString(_T("Golden Value"),strTempKey,strTemp,strPath);
		}
	}
	else
	{
		for (int i=0;i<3;i++)
		{
			switch(i)
			{
			case 0:
				strTempKey=strKey+"Pow_L";
				break;
			case 1:
				strTempKey=strKey+"Pow_M";
				break;
			case 2:
				strTempKey=strKey+"Pow_H";
				break;
			default:
				break;
			}

			strTemp.Format("%.2f",dVtrGoldenPower[i]);
			::WritePrivateProfileString(_T("Golden Value"),strTempKey,strTemp,strPath);

		}
	}


	return true;
}

bool CCableLossFinder::GetGoldenPowerFromIni(CString strBandType,int iBand,DblVtr &dVtrGoldenPower,CString strPath)
{
	//CBandInfo.h

	_TCHAR _tKeyValue[1000];
	CString strKey="";
	if(strBandType.Find(_T("GSM"))!=-1)
	{
		switch(iBand)
		{
		case GSM_850_BAND_ID:
			strKey=_T("GSM850");
			break;
		case GSM_EGSM_BAND_ID:
			strKey=_T("GSM900");
			break;
		case GSM_DCS_BAND_ID:
			strKey=_T("GSM1800");
			break;
		case GSM_PCS_BAND_ID:
			strKey=_T("GSM1900");
			break;
		default:
			strKey=_T("UnKnown Band");
			break;
		}
	}
	else if (strBandType.Find(_T("WCDMA"))!=-1)
	{
		switch(iBand)
		{
		case WCDMA_850_BAND_ID:
			strKey=_T("W850");
			break;
		case WCDMA_900_BAND_ID:
			strKey=_T("W900");
			break;
		case WCDMA_1500_BAND_ID:
			strKey=_T("W1500");
			break;
		case WCDMA_AWS_BAND_ID:
			strKey=_T("W1700");
			break;
		case WCDMA_PCS_BAND_ID:
			strKey=_T("W1900");
			break;
		case WCDMA_IMT_BAND_ID:
			strKey=_T("W2100");
			break;
		default:
			strKey=_T("UnKnown Band");
			break;
		}	
	}
	else if(strBandType.Find(_T("CDMA"))!=-1)
	{
		switch(iBand)
		{
		case CDMA_BC0_BAND_ID:
			strKey=_T("CDMA800");
			break;
		case CDMA_BC1_BAND_ID:
			strKey=_T("CDMA1900");
			break;
		default:
			strKey=_T("UnKnown Band");
			break;
		}
	}
	else
	{
		strKey=_T("UnKnown Band Type");
		MessageBox(NULL,strKey,"warning",MB_OK);
	}

	CString strTemp,strTempKey;
	for (int i=0;i<3;i++)
	{
		switch(i)
		{
		case 0:
			strTempKey=strKey+"Pow_L";
			break;
		case 1:
			strTempKey=strKey+"Pow_M";
			break;
		case 2:
			strTempKey=strKey+"Pow_H";
			break;
		default:
			break;
		}
	
		::GetPrivateProfileString(_T("Golden Value"),strTempKey,NULL,_tKeyValue,sizeof(_tKeyValue),strPath);
		strTemp.Format("%s",_tKeyValue);
		dVtrGoldenPower.push_back(CStr::StrToFloat(strTemp));

	}

	return true;
}

int CCableLossFinder::GetPurposeOfLossIni(CString strPath,CString strSN)
{
	_TCHAR _tKeyValue[128];
	CString strKey=_T("IsToMakeGoldenSample"),strTemp="",strNewPath;
	int iRet;

	::GetPrivateProfileString(_T("Cal Control"),strKey,NULL,_tKeyValue,sizeof(_tKeyValue),strPath);
	strTemp.Format("%s",_tKeyValue);
	iRet=CStr::StrToInt(strTemp);

	if(iRet==1)
	{			
		int iPos=strPath.ReverseFind(_T('\\'));
		if (!strSN.IsEmpty())
		{
			strNewPath=strPath.Left(iPos)+_T('\\')+strSN+".ini";
		}
		else
			MessageBox(NULL,"SN is empty","Err",MB_OK);
		

		strKey=_T("SN");
		::WritePrivateProfileString(_T("Sample"),strKey,strSN,strPath);

		CopyFile(strPath,strNewPath,TRUE);
	}

	return iRet;
}

bool CCableLossFinder::CompareSNSameTrue(CString strPath,CString strSN)
{
	_TCHAR _tKeyValue[128];
	CString strKey=_T("SN"),strTemp="",strNewPath;

	::GetPrivateProfileString(_T("Sample"),strKey,NULL,_tKeyValue,sizeof(_tKeyValue),strPath);
	strTemp.Format("%s",_tKeyValue);
	
	if (strSN.IsEmpty()||strSN!=strTemp)
	{
		return false;
	}
	else
		return true;
}

int CCableLossFinder::SetLossIniToMeasLoss(CString strPath)
{
	CString strKey=_T("IsToMakeGoldenSample"),strTemp=_T("0");
	int iRet;

	::WritePrivateProfileString(_T("Cal Control"),strKey,strTemp,strPath);

	iRet=CStr::StrToInt(strTemp);

	return iRet;
}