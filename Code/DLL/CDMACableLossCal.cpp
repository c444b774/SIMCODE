#include "stdafx.h"
#include "CDMACableLossCal.h"

RF_IMPLEMENT_DYNCREATE(CCDMACableLossCal)

CCDMACableLossCal::CCDMACableLossCal()
{
	m_mapClassFunc[_T("CDMAMeasMainFunc")]=&CCDMACableLossCal::CCDMACableLossCalMainFunc;
	m_mapClassFunc[_T("CDMAMeasLoop")]=&CCDMACableLossCal::CCDMACableLossCalFunc;
	m_mapClassFunc[_T("MakeGoldenSemple")]=&CCDMACableLossCal::CDMAMakeGoldenSemple;
	m_mapClassFunc[_T("SetCableLoss")]=&CCDMACableLossCal::CDMASetCableLoss;

}

CCDMACableLossCal::~CCDMACableLossCal()
{
	
}

bool CCDMACableLossCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CCDMACableLossCal::Handle()
{
	if((!DoProcess())||(m_iFailFlag!=0))
	{
		m_pPhone->FTM_CDMA2000_EndCall(300);
      return false;
	}
		
	return true;
}

bool CCDMACableLossCal::CCDMACableLossCalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CCDMACableLossCal::CDMAMakeGoldenSemple()
{
	if (!CDMAMeasPower())
	{
		return false;
	}

	m_dVtrGoldenPwr.clear();
	m_dVtrGoldenPwr=m_dVtrMeasPwr;
	if (!WriteGoldenPower())
	{
		CalFailLog(m_strCurBand,"-",1003,"SetCableLoss Fail");
		m_iFailFlag++;
		return false;
	}	
	return true;
}

bool CCDMACableLossCal::CDMASetCableLoss()
{
	CStringVtr cvChannel;
	CStringVtr cvLoss;
	CStringStringMap mapString2String;

	if (!CDMAMeasPower())
	{
		return false;
	}
	if (!ReadGoldenPower())
	{
		m_iFailFlag++;
		return true;
	}
	double dTemp;
	CString strTemp,strTemp1;
	for (int i=0;i<3;i++)
	{
		dTemp=m_dVtrGoldenPwr[i]-m_dVtrMeasPwr[i]+m_vCableLoss[i];
		strTemp.Format("%.2f",dTemp);
		strTemp1.Format("cableloss=%.2f",dTemp);
		TestPassLog(m_strCurBand,"_","_","_",strTemp,"_",strTemp1);
		cvLoss.push_back(strTemp);
	}


	cvChannel.clear();
	cvChannel.push_back("0");cvChannel.push_back("1");cvChannel.push_back("2");
	CStr::MakeVector2Map(cvChannel,cvLoss,mapString2String);	
	if(!m_LossFinder.UpdateLossIniFromMap("CDMA"+m_strCurBand,mapString2String))
	{
		CalFailLog("_","_",1003,"Cable loss ini not exist");
		m_iFailFlag++;
		return false;
	}
	CalPassLog(m_strCurBand,"-","SetCableLoss pass");
	return true;
}

bool CCDMACableLossCal::CDMAMeasPower()
{
	int iDLChannel,iULChannel;
	int iErrorcode;
	CString strMsg,strESN;
	iULChannel=m_iTestChan[0];
	iDLChannel=CCDMABandInfo::GetDLChannel(m_iCurrBand,iULChannel);

	m_iItemCode=CDMA_TestTestCall_BaseItemCode;
	m_pPhone->CloseComport();
	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		m_iFailFlag++;
		return false;
	}

	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("CDMA Test Phone Set FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCurBand),_T("-"),iErrorcode,_T("CDMA Test Phone Set FTM Mode Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunCDMATestDev->ICDMATestInitCDMANStest(m_strDeviceAddr,""))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("CDMA NonSignaling Test InitDev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),m_iErrorcode,_T("InitDev Fail!"))
			m_iFailFlag++;
		return false;
	}
	CalPassLog(_T("-"),_T("-"),_T("InitDev Pass!"))
		if (!SetCDMATestLOSS())
		{
			LogTrace(MSG_ERROR,_T("SetCDMATestLOSS Fail!"))
				CalFailLog(_T("_"),_T("_"),LOSS_SET_FAIL,"SetCDMATestLOSS Fail!");
			//		   m_iErrorcode=iErrorcode;
			m_iFailFlag++;
			return false;
		}

		iErrorcode=m_pPhone->DIAG_READ_ESN_F(strESN);
	iErrorcode=m_pFunCDMATestDev->ICDMATestSetESN(strESN);
	if(iErrorcode!=DEVICE_SUCCESS)
	{
		strMsg.Format("DevSetESN Fail,ESN:%s",strESN);
		LogTrace(MSG_ERROR,strMsg)
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("DevSetESN Fail!"))
			return false;
	}
	for (int chIndex=0;chIndex<m_iTestChan.size();chIndex++)  
	{

		if((iErrorcode=m_pFunCDMATestDev->ICDMATestHandover(m_iCurrBand,m_iTestChan[chIndex]))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("ICDMATestHandOver(Device) Fail!"))
				m_iErrorcode=iErrorcode;
			m_iFailFlag++;
			return false;
		}

		CString strESN,strMsg;
		iErrorcode=m_pPhone->DIAG_READ_ESN_F(strESN);
		iErrorcode=m_pFunCDMATestDev->ICDMATestSetESN(strESN);
		if(iErrorcode!=DEVICE_SUCCESS)
		{
			strMsg.Format("DevSetESN Fail,ESN:%s",strESN);
			LogTrace(MSG_ERROR,strMsg)
				m_iErrorcode=iErrorcode;
			CalFailLog(_T("-"),_T("-"),iErrorcode,_T("DevSetESN Fail!"))
				return false;
		}

		m_iItemCode=CDMA_Call_HandOver_Phone_BaseItemCode;
		if((iErrorcode=m_pPhone->FTM_CDMA_BER_Handover(1,0,m_iCurrBand,m_iTestChan[chIndex],0,FTM_CDMA2000_NS_RC_1))!=PHONE_SUCCESS)
		{           
			LogTrace(MSG_ERROR,_T("FTM_CDMA_HandoverCall(Handset) Fail!"))
				m_iErrorcode=iErrorcode;

			CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA_HandoverCall Fail!");
			m_iFailFlag++;
			return false;
		}

		if (m_strTesterDevice=="CMW500")
		{
			if((iErrorcode=m_pPhone->FTM_CDMA_2000_HardHandOff(m_iCurrBand,m_iTestChan[chIndex]))!=PHONE_SUCCESS)
			{           
				LogTrace(MSG_ERROR,_T("FTM_CDMA_2000_HardHandOff(Handset) Fail!"))
					m_iErrorcode=iErrorcode;

				CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA_2000_HardHandOff Fail!");
				m_iFailFlag++;
				return false;
			}

		}
		double dPower=0;
		if((iErrorcode=m_pFunCDMATestDev->ICDMATestMaxPower(m_iBurstQty,&dPower))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("ICDMATestMaxPower Test Fail!"))
				m_iErrorcode=iErrorcode;
			m_iFailFlag++;
			return false;
		}
		CRangePair<double> MaxPwrSpec;
		MaxPwrSpec.SetRange(m_dVtrMaxPwrLim[0],m_dVtrMaxPwrLim[1]);
		if (MaxPwrSpec.InRange(dPower))
		{
			TestPassLogEx(m_strCurBand,_T(CStr::IntToStr(m_iTestChan[chIndex])),_T(CStr::FloatToStr(MaxPwrSpec.GetMax())),_T(CStr::FloatToStr(MaxPwrSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dBm"),_T("MaxPower PASS"),"MaxPower")

		}
		else
		{
			TestFailLogEx(m_strCurBand,_T(CStr::IntToStr(m_iTestChan[chIndex])),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(MaxPwrSpec.GetMax())),_T(CStr::FloatToStr(MaxPwrSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dBm"),_T("MaxPower FAIL"),"MaxPower")
				return false;
		}
		m_dVtrMeasPwr.push_back(dPower);
	}
	m_pFunCDMATestDev->Deivce_Exit();
//****************************
	m_pPhone->FTM_CDMA2000_EndCall(300);

	m_pPhone->CloseComport();
	return true;
}
bool CCDMACableLossCal::WriteGoldenPower()
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
			switch (m_iCurrBand)
			{
			case CDMA_BC0_BAND_ID:
				iNVoffset=24;
				break;
			case CDMA_BC1_BAND_ID:
				iNVoffset=30;
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
			TestPassLogEx(m_strCurBand,_T("-"),_T("-"),_T("-"),_T("-"),_T("-"),_T("WriteGoldNV PASS"),"WriteGoldNV")

	return true;
}
bool CCDMACableLossCal::ReadGoldenPower()
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
			switch (m_iCurrBand)
			{
			case CDMA_BC0_BAND_ID:
				iNVoffset=24;
				break;
			case CDMA_BC1_BAND_ID:
				iNVoffset=30;
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
				CalPassLog(m_strCurBand,CStr::IntToStr(i+1),strMsg);
			}
			strMsg.Format("Band%d GoldenPower:%.2f,%.2f,%.2f",m_iCurrBand,m_dVtrGoldenPwr[0],m_dVtrGoldenPwr[1],m_dVtrGoldenPwr[2]);
			LogTrace(MSG_MID,strMsg)


				return true;
	
}
bool CCDMACableLossCal::CCDMACableLossCalFunc()
{
	int iErrorcode;
	bool bRet=false;

	CString strIniPath=m_LossFinder.GetCurrentXmlToIni(m_strSN);
	if (strIniPath.Find(_T("No_GoldenFile"))!=-1)
	{
		LogTrace(MSG_ERROR,_T("GET Golden file Fail!"))
			return false;
	}
	m_IsToMakeSample=m_LossFinder.GetPurposeOfLossIni(strIniPath,m_strSN);

	m_iItemCode=CDMA_SetCableLoss_BaseItemCode;
	if (!SetCDMATestLOSS())
	{
		LogTrace(MSG_ERROR,_T("SetCDMATestLOSS Fail!"))
		CalFailLog(_T("_"),_T("_"),LOSS_SET_FAIL,"SetCDMATestLOSS Fail!");
			//		   m_iErrorcode=iErrorcode;
		m_iFailFlag++;
			return false;
	}
	TestPassLog(m_strCurBand,"_","_","_","_","_","Set CableLOSS Pass");

	m_dVtrMeasPwr.clear();
	m_strVtrLossRes.clear();

	int nIndex=0;
	for (int chIndex=0;chIndex<m_iTestChan.size();chIndex++)  
	{
		CString str,strChan,strTestItem;
		strTestItem.Format("H1");
		strChan.Format("%d",m_iTestChan[chIndex]);
		str.Format("%d",nIndex);

		m_iItemCode=CDMA_Call_HandOver_Device_BaseItemCode;
		if((iErrorcode=m_pFunCDMATestDev->ICDMATestHandover(m_iCurrBand,m_iTestChan[chIndex]))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("ICDMATestHandOver(Device) Fail!"))
				m_iErrorcode=iErrorcode;
			m_iFailFlag++;
			return false;
		}
		TestPassLog(m_strCurBand,CStr::IntToStr(m_iTestChan[chIndex]),"_","_","_","_","Instr handover Pass");

		m_iItemCode=CDMA_Call_HandOver_Phone_BaseItemCode;
		if((iErrorcode=m_pPhone->FTM_CDMA_BER_Handover(1,0,m_iCurrBand,m_iTestChan[chIndex],0,FTM_CDMA2000_NS_RC_1))!=PHONE_SUCCESS)
		{           
			LogTrace(MSG_ERROR,_T("FTM_CDMA_HandoverCall(Handset) Fail!"))
				m_iErrorcode=iErrorcode;

			CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA_HandoverCall Fail!");
			m_iFailFlag++;
			return false;
		}
		if (m_strTesterDevice=="CMW500")
		{
			if((iErrorcode=m_pPhone->FTM_CDMA_2000_HardHandOff(m_iCurrBand,m_iTestChan[chIndex]))!=PHONE_SUCCESS)
			{           
				LogTrace(MSG_ERROR,_T("FTM_CDMA_2000_HardHandOff(Handset) Fail!"))
					m_iErrorcode=iErrorcode;

				CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_CDMA_2000_HardHandOff Fail!");
				m_iFailFlag++;
				return false;
			}

		}
		TestPassLog(m_strCurBand,CStr::IntToStr(m_iTestChan[chIndex]),"_","_","_","_","Handset handover Pass");

		m_strVtrTXResult.clear();
		bRet=StartLossMeas(m_iTestChan[chIndex],strTestItem);
		if (!bRet)
		{
			TestFailLog(m_strCurBand,CStr::IntToStr(m_iTestChan[chIndex]),10000,"_","_","_","_","StartTXMeasurment Fail");
			m_iFailFlag++;
			return false;
		}
		bRet=CheckTXResult(nIndex,m_iTestChan[chIndex],strTestItem);
		if (!bRet)
		{
			m_iFailFlag++;
			return false;
		}

		//EndCall();

		CStringVtr strVtrTemp;
		CStr::ParseString(m_strVtrTXResult[0],",",strVtrTemp);

		m_dVtrMeasPwr.push_back(CStr::StrToFloat(strVtrTemp[1]));

		nIndex++;		
	}

	if (m_IsToMakeSample==1)
	{
		m_LossFinder.WriteGoldenPowerToIni("CDMA",m_iCurrBand,m_dVtrMeasPwr,strIniPath);
	}
	else
	{
		m_LossFinder.GetGoldenPowerFromIni("CDMA",m_iCurrBand,m_dVtrGoldenPwr,strIniPath);

		double dTemp;
		CString strTemp,strTemp1;
		for (int i=0;i<m_dVtrMeasPwr.size();i++)
		{
			dTemp=m_dVtrGoldenPwr[i]-m_dVtrMeasPwr[i]+m_vCableLoss[i];
			strTemp.Format("%.2f",dTemp);
			strTemp1.Format("Pwr:Gold=%.2f,Meas=%.2f,GoldCable=%.2f",m_dVtrGoldenPwr[i],m_dVtrMeasPwr[i],m_vCableLoss[i]);
			TestPassLog(m_strCurBand,"_","_","_",strTemp,"_",strTemp1);
			m_strVtrLossRes.push_back(strTemp);
		}

		CStringStringMap mapString2String;
		m_strVtrChan.clear();

		if (m_IsSaveToIni)
		{
			m_strVtrChan.push_back("0");m_strVtrChan.push_back("1");m_strVtrChan.push_back("2");
			CStr::MakeVector2Map(m_strVtrChan,m_strVtrLossRes,mapString2String);
			if(!m_LossFinder.UpdateLossIniFromMap("CDMA"+m_strCurBand,mapString2String))
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

			for (int iChIndex=0;iChIndex<m_iTestChan.size();iChIndex++)
			{
				CString strTemp;
				strTemp.Empty();
				strTemp.Format("%.4f",CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_iTestChan[iChIndex],0));
				m_strVtrChan.push_back(strTemp);
			}
			CStr::MakeVector2Map(m_strVtrChan,m_strVtrLossRes,mapString2String);

			sXmlLoss.mapFreq2Loss=mapString2String;
			sXmlLoss.iIsUplink=1;

			SendMessage(m_hMsgHandlingWnd,WM_UPDATEXMLLOSS,0,LPARAM(&sXmlLoss));

			m_strVtrChan.clear();
			mapString2String.clear();
			for (int iChIndex=0;iChIndex<m_iTestChan.size();iChIndex++)
			{
				CString strTemp;
				strTemp.Empty();
				strTemp.Format("%.4f",CCDMABandInfo::ArfcnToHz(m_iCurrBand,m_iTestChan[iChIndex],1));
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


 bool CCDMACableLossCal::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
    CStringStringMapItr itrFind;
	CString strValue,strTemp;
    CString strMainFun;
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
		 LogTrace(MSG_WARNING,"Not Find 'TestBand' from ini file!");
		 return false;
		 
	 }
	 else
	 {
		 strValue=itrFind->second;
		 if (!strcmp(strValue,"800"))
		 {
			 m_strCurBand=_T("800");
			 m_iCurrBand=CDMA_BC0_BAND_ID;
		 }
		 else if(!strcmp(strValue,"1900"))
		 {
			 m_strCurBand=_T("1900");
			 m_iCurrBand=CDMA_BC1_BAND_ID;
		 }
		 if (m_iCurrBand!=CDMA_BC0_BAND_ID && m_iCurrBand!=CDMA_BC1_BAND_ID)
		 {
			 strTemp.Format("Band=%s,not support yet",strValue);
			 LogTrace(MSG_ERROR,_T(strTemp));
				 return false;
		 }
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
		 LogTrace(MSG_LOW,_T("Not Find strNodeType,default CDMA"));
		 m_strType="CDMA";
	 }
	 else
	 {
		 m_strType=itrFind->second;
	 }

	 itrFind=pcSettingMap->find(_T("UseFollowPara"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,_T("Not Find UseFollowPara Default ture"));
		m_bUseCfgPara=true;
	 }
	 else
	 {
		 m_bUseCfgPara=CStr::StrToBool(itrFind->second);
	 }


	 if (m_bUseCfgPara)
	 {
		 itrFind=pcSettingMap->find(_T("TestChan"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find TestChan"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2IntVtr(m_iTestChan,strVtrTemp);
		 }
//m_CableLossMeasureCount
		  strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("CableLossMeasureCount"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find CableLossMeasureCount,default 100"));
			 m_CableLossMeasureCount=100;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 m_CableLossMeasureCount = CStr::StrToInt(strTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("CellPwr"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find CellPwr,default -75"));
			 m_dVtrPwrLevel.push_back(-75);
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrPwrLevel,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("MaxPower"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_FATAL,_T("Not Find MaxPower"));
			 return false;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 CStr::ParseString(strTemp,_T(","),strVtrTemp);
			 CStr::StrVtr2DblVtr(m_dVtrMaxPwrLim,strVtrTemp);
		 }

		 strTemp.Empty();
		 strVtrTemp.clear();
		 itrFind=pcSettingMap->find(_T("iPwrCount"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_LOW,_T("Not Find iPwrCount"));
			 m_iBurstQty=20;
		 }
		 else
		 {
			 strTemp=itrFind->second;
			 m_iBurstQty=CStr::StrToInt(strTemp);
		 }
	 }
	 else
	 {
		 LogTrace(MSG_FATAL,_T("Pls set UseFollowPara to 1; no Default Value now")); 
		 return false;
	 }

	 strTemp.Empty();
	 strVtrTemp.clear();
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


	 InitData();
	 return true;
 }

 bool CCDMACableLossCal::InitData()
 {
	 m_pFunCDMATestDev=m_piTesterDevice->m_piFuncCDMATest;
	 m_bIsStopWhileFail=m_bIsStopWhenFail;
	 m_iFailFlag=0;
	 return true;
 }

 bool CCDMACableLossCal::SetCDMATestLOSS()
 {
	 CString strMsg;
	 double dLoss;
	 m_vCableLoss.clear();
	 for(int i=0;i<3;i++)
	 {
		 if(!m_LossFinder.GetCDMALoss("CDMA"+m_strCurBand,i,dLoss))
		 {
			 strMsg.Format("CDMA Get Loss Band=CDMA%s ,ChannelType=%d Fail",m_strCurBand,i);
			 LogTrace(MSG_ERROR,strMsg);
			 CalFailLog(_T("_"),_T("_"),1001,strMsg);
			 m_iFailFlag++;
			 return false;
		 }
		 m_vCableLoss.push_back(dLoss);
	 }

	 if(DEVICE_SUCCESS!=m_pFunCDMATestDev->ICDMATestSetLoss(m_iCurrBand,m_vCableLoss))
	 {
		 LogTrace(MSG_ERROR,"Set Cableloss device fail");
		 CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		 m_iFailFlag++;
		 return false;

	 }

	 return  true;

 }

 int CCDMACableLossCal::GetItemCode(int nMode,int Band,int Channel,int PowerLevel)
 {
	 int nItemCode=CDMA_Init_Test_BaseItemCode;
	 nItemCode+=nMode*100000;

	 switch(Band)
	 {
	 case CDMA_BC0_BAND_ID:
		 nItemCode+=1*10000;
		 break;
	 case CDMA_BC1_BAND_ID:
		 nItemCode+=2*10000;
		 break;

	 default:
		 return -1;
	 }

	 nItemCode+=CGSMBandInfo::GetChannelType(Band,Channel)*1000;

	 nItemCode+=CGSMBandInfo::GetPclType(Band,Channel)*100;

	 return nItemCode;
 }

  bool CCDMACableLossCal::StartLossMeas(int iTestChan,CString strTestItem)
  {
	  int iErrorcode;

	  if((iErrorcode=m_pFunCDMATestDev->ICDMATestStartTXMeasurment(m_iCurrBand,iTestChan,m_dVtrPwrLevel,m_iBurstQty,m_strVtrTXResult,strTestItem,m_CableLossMeasureCount))!=DEVICE_SUCCESS)
	  {
		  LogTrace(MSG_ERROR,_T("CDMA Test StartMeasurment Test Fail!"))
			  m_iErrorcode=iErrorcode;
		  m_iFailFlag++;
		  return false;
	  }

	  return true;

  }

  bool CCDMACableLossCal::CheckTXResult(int nIndex,int iChan,CString strTestItem)
  {
	  int nTestSeq=0;

	  if (strTestItem.Find("H1")!=-1)//H MAX POWER
	  {
		  m_iItemCode+='H';
		  CRangePair<double> MaxPwrSpec;
		  MaxPwrSpec.SetRange(m_dVtrMaxPwrLim[0],m_dVtrMaxPwrLim[1]);

		  CStringVtr strVtrTemp;
		  CStr::ParseString(m_strVtrTXResult[nTestSeq],",",strVtrTemp);

		  if (MaxPwrSpec.InRange(CStr::StrToFloat(strVtrTemp[1])))
		  {
			  TestPassLog(m_strCurBand,CStr::IntToStr(iChan),CStr::FloatToStr(MaxPwrSpec.GetMax()),CStr::FloatToStr(MaxPwrSpec.GetMin()),strVtrTemp[1],"dBm","MaxPower Pass");
		  }
		  else
		  {
			  TestFailLog(m_strCurBand,CStr::IntToStr(iChan),nIndex,CStr::FloatToStr(MaxPwrSpec.GetMax()),CStr::FloatToStr(MaxPwrSpec.GetMin()),strVtrTemp[1],"dBm","MaxPower Fail");
			  m_iFailFlag++;
			  if (m_bIsStopWhileFail)
			  {
				  return false;
			  }
		  }
		  m_iItemCode-='H';

		  nTestSeq++;
	  }

	  return true;
  }


  void CCDMACableLossCal::EndCall()
  {
	  m_iItemCode=CDMA_Call_HandOver_Device_BaseItemCode;
	  m_pFunCDMATestDev->ICDMATestEndCall();
	
	  m_pPhone->FTM_CDMA2000_EndCall(m_nEndDelay);

	  TestPassLog("_","_","_","_","_","_","Instr handover Pass");
  }