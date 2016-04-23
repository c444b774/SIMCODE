#include "stdafx.h"
#include "GSMCableLossCal.h"

RF_IMPLEMENT_DYNCREATE(CGSMCableLossCal)

CGSMCableLossCal::CGSMCableLossCal()
{
	m_mapClassFunc[_T("CGSMCableLossCalMainFunc")]=&CGSMCableLossCal::CGSMCableLossCalMainFunc;
	m_mapClassFunc[_T("CGSMCableLossCalFunc")]=&CGSMCableLossCal::CGSMCableLossCalFunc;
	m_mapClassFunc[_T("MakeGoldenSemple")]=&CGSMCableLossCal::GsmMakeGoldenSemple;
	m_mapClassFunc[_T("SetCableLoss")]=&CGSMCableLossCal::GsmSetCableLoss;



	m_intChNum=0;
}

CGSMCableLossCal::~CGSMCableLossCal()
{
	
}

bool CGSMCableLossCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSMCableLossCal::Handle()
{
	if((!DoProcess())||(m_iFailFlag!=0))
		return false;
	return true;
}

bool CGSMCableLossCal::CGSMCableLossCalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CGSMCableLossCal::GsmMakeGoldenSemple()
{
	if (!GsmMeasPower())
	{
		m_iFailFlag++;
		return false;
	}

	m_dVtrGoldenPwr.clear();
	m_dVtrGoldenPwr=m_dVtrMeasPwr;
	if (!WriteGoldenPower())
	{
		CalFailLog(m_strCurrBand,"-",1003,"SetCableLoss Fail");
		m_iFailFlag++;
		return false;
	}	
	return true;
}
bool CGSMCableLossCal::GsmSetCableLoss()
{
	CStringVtr cvChannel;
	CStringVtr cvLoss;
	CStringStringMap mapString2String;

	if (!GsmMeasPower())
	{
		m_iFailFlag++;
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
		dTemp=m_dVtrGoldenPwr[i]-m_dVtrMeasPwr[i]+m_vCableLoss[i];     //
		strTemp.Format("%.2f",dTemp);
		strTemp1.Format("cableloss=%.2f",dTemp);
		TestPassLog(m_strCurrBand,"_","_","_",strTemp,"_",strTemp1);
		cvLoss.push_back(strTemp);
	}


	cvChannel.clear();
	cvChannel.push_back("0");cvChannel.push_back("1");cvChannel.push_back("2");
	CStr::MakeVector2Map(cvChannel,cvLoss,mapString2String);	
	if(!m_LossFinder.UpdateLossIniFromMap(m_strCurrBand,mapString2String))
	{
		CalFailLog("_","_",1003,"Cable loss ini not exist");
		m_iFailFlag++;
		return false;
	}
	CalPassLog(m_strCurrBand,"-","SetCableLoss pass");


	return true;

}
bool CGSMCableLossCal::GsmMeasPower()
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

	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		return false;
	}


	if((iErrorcode=m_pFunGSMTestDev->IGSMTestInitGSMtest_NSFT(m_strDeviceAddr,m_IsEdge,m_iTestChan[0],5,m_iFTMBand))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Init GSM NonSignal Test Fail!"))
			m_iErrorcode=iErrorcode;
		return false;
	}
	if (!SetGSMTestLOSS())
	{
		LogTrace(MSG_ERROR,_T("SetGSMTestLOSS Fail!"))
			//		   m_iErrorcode=iErrorcode;
			return false;
	}

	TestPassLog(m_strCurrBand,CStr::IntToStr(m_iTestChan[0]),"_","_","_","_","InitDevice Pass");

	m_IsEdge==0?(m_iItemCode=GSM_GSMTestCall_BaseItemCode):(m_iItemCode=EDGE_EDGECall_Test_BaseItemCode);

	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Set Phone FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("-"),_T("-"),iErrorcode,_T("Set Phone FTM Mode Fail!"))
			return false;
	}
	if ((iErrorcode=m_pPhone->FTM_GSM_StartCall(0,m_iChainId,m_IsEdge,1000,m_iTestChan[0],m_iFTMBand))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("FTM_GSM_StartCall Fail!"))
			m_iErrorcode=iErrorcode;
		TestFailLog(m_strCurrBand+'-'+CStr::IntToStr(m_iCurrBand),CStr::IntToStr(m_iTestChan[0]),1000,"_","_","_","_","Call Fail");
		return false;
	}
	TestPassLog(m_strCurrBand,CStr::IntToStr(m_iTestChan[0]),"_","_","_","_","Call Pass");
	m_dVtrMeasPwr.clear();
	for (int chIndex=0;chIndex<m_iTestChan.size();chIndex++)  
	{		
			CString str,strPcl,strChan,strTestItem;
			strTestItem.Format("A1");
			strPcl.Format("%d",m_iPCL);
			strChan.Format("%d",m_iTestChan[chIndex]);	
			
			m_IsEdge==0?(m_iItemCode=GSM_HandOver_Device_BaseItemCode):(m_iItemCode=EDGE_HandOver_Device_BaseItemCode);
			if((iErrorcode=m_pFunGSMTestDev->IGSMTestHandOver(CGSMBandInfo::GetPhoneMode(m_iCurrBand),m_iTestChan[chIndex],m_iPCL,m_IsEdge))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,_T("IGSMTestHandOver(Device) Fail!"))
					m_iErrorcode=iErrorcode;
				m_iFailFlag++;
				return false;
			}
			TestPassLog(m_strCurrBand,strChan+'-'+strPcl,"_","_","_","_","Instr handover Pass");

			m_IsEdge==0?(m_iItemCode=GSM_HandOver_Phone_BaseItemCode):(m_iItemCode=EDGE_HandOver_Phone_BaseItemCode);
			if((iErrorcode=m_pPhone->FTM_GSM_BER_Handover(m_iTestChan[chIndex],CGSMBandInfo::GetPhoneTestMode(m_iCurrBand),0,2,FTM_GSM_BER_SPEECH_FULL_RATE,m_iPCL,FTM_GSM_BER_Loopback_Type_C,20,m_IsEdge))!=PHONE_SUCCESS)
			{           
				LogTrace(MSG_ERROR,_T("FTM_GSM_BER_Handover(Handset) Fail!"))
					m_iErrorcode=iErrorcode;
				m_iFailFlag++;
				CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_GSM_BER_Handover Fail!");
				return false;
			}
			TestPassLog(m_strCurrBand,strChan+'-'+strPcl,"_","_","_","_","Handset handover Pass");

			m_iItemCode=GetItemCode(m_IsEdge,m_iCurrBand,m_iTestChan[chIndex],m_iPCL);

			m_strVtrResultTX.clear();
			if (!StartLossMeas(strTestItem))
			{
				TestFailLog(m_strCurrBand,"_",1001,"_","_","_","_","LossMeasurment Fail");
				m_iFailFlag++;
				return false;
			}			
			if (m_IsEdge==0)
			{			
				if (!CheckTXResult(chIndex,strPcl,strChan,strTestItem))
				{
					m_iFailFlag++;
					return false;
				}
			}
			else
			{
				m_iFailFlag++;
				return false;
			}

			double  dReservedTemp;//for .2f use

			dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[0]);
			m_dVtrMeasPwr.push_back(dReservedTemp);		
	}
	m_pFunGSMTestDev->Deivce_Exit();
	m_pPhone->FTM_GSM_EndCall(300);
	m_pPhone->CloseComport();
	return true;
}
bool CGSMCableLossCal::ReadGoldenPower()
{
	int  iErrorcode;
	unsigned char uiData[128]={0},uiFlagData[128]={0};
	CString strMsg;
	LogTrace(MSG_MID,_T(" Open Comport....!"))
		if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
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
			case GSM_EGSM_BAND_ID:
				iNVoffset=6;
				break;
			case GSM_DCS_BAND_ID:
				iNVoffset=12;
				break;
			case GSM_PCS_BAND_ID:
				iNVoffset=18;
				break;
			case GSM_850_BAND_ID:
				iNVoffset=0;
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
				CalPassLog(m_strCurrBand,CStr::IntToStr(i+1),strMsg);
			}
			strMsg.Format("Band%d GoldenPower:%.2f,%.2f,%.2f",m_iCurrBand,m_dVtrGoldenPwr[0],m_dVtrGoldenPwr[1],m_dVtrGoldenPwr[2]);
			LogTrace(MSG_MID,strMsg)


				return true;
}
bool CGSMCableLossCal::WriteGoldenPower()
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
			case GSM_EGSM_BAND_ID:
				iNVoffset=6;
				break;
			case GSM_DCS_BAND_ID:
				iNVoffset=12;
				break;
			case GSM_PCS_BAND_ID:
				iNVoffset=18;
				break;
			case GSM_850_BAND_ID:
				iNVoffset=0;
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
			TestPassLogEx(m_strCurrBand,_T("-"),_T("-"),_T("-"),_T("-"),_T("-"),_T("WriteGoldNV PASS"),"WriteGoldNV")

				return true;

}
bool CGSMCableLossCal::CGSMCableLossCalFunc()
{  
   int iErrorcode;

   CString strIniPath=m_LossFinder.GetCurrentXmlToIni(m_strSN);
   if (strIniPath.Find(_T("No_GoldenFile"))!=-1)
   {
		LogTrace(MSG_ERROR,_T("GET Golden file Fail!"))
			return false;
   }
   m_IsToMakeSample=m_LossFinder.GetPurposeOfLossIni(strIniPath,m_strSN);


   m_IsEdge==0?(m_iItemCode=GSM_SetCableLoss_BaseItemCode):(m_iItemCode=EDGE_SetCableLoss_BaseItemCode);

   if (!SetGSMTestLOSS())
   {
	   LogTrace(MSG_ERROR,_T("SetGSMTestLOSS Fail!"))
//		   m_iErrorcode=iErrorcode;
	   return false;
   }
   TestPassLog(m_strCurrBand,"_","_","_","_","_","Set CableLOSS Pass");

	m_dVtrMeasPwr.clear();
	m_strVtrLossRes.clear();

   int nIndex=0;
   for (int chIndex=0;chIndex<m_intChNum;chIndex++)  
   {		
	   for (int pclIndex=0;pclIndex<m_intCh_PclNum[chIndex];pclIndex++)
	   {
			CString str,strPcl,strChan,strTestItem;
			strTestItem.Format("A1");
			strPcl.Format("%d",m_iTestPcl[nIndex]);
			strChan.Format("%d",m_iTestChan[chIndex]);
			str.Format("%d",nIndex);

			if (m_iTestPcl[nIndex]==-1)
			{
				continue;
			}
			m_IsEdge==0?(m_iItemCode=GSM_HandOver_Device_BaseItemCode):(m_iItemCode=EDGE_HandOver_Device_BaseItemCode);
			if((iErrorcode=m_pFunGSMTestDev->IGSMTestHandOver(CGSMBandInfo::GetPhoneMode(m_iCurrBand),m_iTestChan[chIndex],m_iTestPcl[nIndex],m_IsEdge))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,_T("IGSMTestHandOver(Device) Fail!"))
					m_iErrorcode=iErrorcode;
				m_iFailFlag++;
				return false;
			}
			TestPassLog(m_strCurrBand,CStr::IntToStr(m_iTestChan[chIndex])+'-'+CStr::IntToStr(m_iTestPcl[nIndex]),"_","_","_","_","Instr handover Pass");
			
			m_IsEdge==0?(m_iItemCode=GSM_HandOver_Phone_BaseItemCode):(m_iItemCode=EDGE_HandOver_Phone_BaseItemCode);
			if((iErrorcode=m_pPhone->FTM_GSM_BER_Handover(m_iTestChan[chIndex],CGSMBandInfo::GetPhoneTestMode(m_iCurrBand),0,2,FTM_GSM_BER_SPEECH_FULL_RATE,m_iTestPcl[nIndex],FTM_GSM_BER_Loopback_Type_C,20,m_IsEdge))!=PHONE_SUCCESS)
			{           
				LogTrace(MSG_ERROR,_T("FTM_GSM_BER_Handover(Handset) Fail!"))
					m_iErrorcode=iErrorcode;
				m_iFailFlag++;
				CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_GSM_BER_Handover Fail!");
				return false;
			}
			TestPassLog(m_strCurrBand,CStr::IntToStr(m_iTestChan[chIndex])+'-'+CStr::IntToStr(m_iTestPcl[nIndex]),"_","_","_","_","Handset handover Pass");

			m_iItemCode=GetItemCode(m_IsEdge,m_iCurrBand,m_iTestChan[chIndex],m_iTestPcl[nIndex]);

			m_strVtrResultTX.clear();
			if (!StartLossMeas(strTestItem))
			{
				TestFailLog(m_strCurrBand,"_",nIndex,"_","_","_","_","LossMeasurment Fail");
				m_iFailFlag++;
				return false;
			}			
			if (m_IsEdge==0)
			{			
				if (!CheckTXResult(nIndex,strPcl,strChan,strTestItem))
				{
				m_iFailFlag++;
					return false;
				}
			}
			else
			{
				m_iFailFlag++;
				return false;
			}


			double  dReservedTemp;//for .2f use

			dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[0]);
			m_dVtrMeasPwr.push_back(dReservedTemp);

			nIndex++;
	   }
   }

   if (m_IsToMakeSample==1)
   {
		m_LossFinder.WriteGoldenPowerToIni("GSM",m_iCurrBand,m_dVtrMeasPwr,strIniPath);
   }
   else
   {
	   m_LossFinder.GetGoldenPowerFromIni("GSM",m_iCurrBand,m_dVtrGoldenPwr,strIniPath);

	   double dTemp;
	   CString strTemp,strTemp1;
	   for (int i=0;i<m_dVtrMeasPwr.size();i++)
	   {
		   dTemp=m_dVtrGoldenPwr[i]-m_dVtrMeasPwr[i]+m_vCableLoss[i];
		   strTemp.Format("%.2f",dTemp);
		   strTemp1.Format("Pwr:Gold=%.2f,Meas=%.2f,GoldCable=%.2f",m_dVtrGoldenPwr[i],m_dVtrMeasPwr[i],m_vCableLoss[i]);
		   TestPassLog(m_strCurrBand,"_","_","_",strTemp,"_",strTemp1);
		   m_strVtrLossRes.push_back(strTemp);
	   }

	   CStringStringMap mapString2String;
	   m_strVtrChan.clear();
	   if (m_IsSaveToIni)
	   {
		   m_strVtrChan.push_back("0");m_strVtrChan.push_back("1");m_strVtrChan.push_back("2");
		   CStr::MakeVector2Map(m_strVtrChan,m_strVtrLossRes,mapString2String);
		   if(!m_LossFinder.UpdateLossIniFromMap(m_strCurrBand,mapString2String))
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

		   for (int iChIndex=0;iChIndex<m_intChNum;iChIndex++)
		   {
			   CString strTemp;
			   strTemp.Empty();
			   strTemp.Format("%.1f",CGSMBandInfo::ArfcnToTXHz(m_iCurrBand,m_iTestChan[iChIndex]));
			   m_strVtrChan.push_back(strTemp);
		   }
		   CStr::MakeVector2Map(m_strVtrChan,m_strVtrLossRes,mapString2String);

		   sXmlLoss.mapFreq2Loss=mapString2String;
		   sXmlLoss.iIsUplink=1;

		   SendMessage(m_hMsgHandlingWnd,WM_UPDATEXMLLOSS,0,LPARAM(&sXmlLoss));

		   m_strVtrChan.clear();
		   mapString2String.clear();
		   for (int iChIndex=0;iChIndex<m_intChNum;iChIndex++)
		   {
			   CString strTemp;
			   strTemp.Empty();
			   strTemp.Format("%.1f",CGSMBandInfo::ArfcnToRXHz(m_iCurrBand,m_iTestChan[iChIndex]));
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

 bool CGSMCableLossCal::InitData(
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
		 LogTrace(MSG_FATAL,_T("Not Find TestBand"));
		 return false;
	}
	else
	{
		strValue=itrFind->second;
		if (!strcmp(strValue,"EGSM"))
		{
			m_iCurrBand=GSM_EGSM_BAND_ID;
			m_iFTMBand=FTM_GSM_BER_EGSM_900;
			m_strCurrBand="GSM900";
			m_iPCL=5;

		}
		else if (!strcmp(strValue,"DCS"))
		{
			m_iCurrBand=GSM_DCS_BAND_ID;
			m_iFTMBand=FTM_GSM_BER_DCS_1800;
			m_strCurrBand="GSM1800";
			m_iPCL=0;
		}
		else if (!strcmp(strValue,"PCS"))
		{
			m_iCurrBand=GSM_PCS_BAND_ID;
			m_iFTMBand=FTM_GSM_BER_PCS_1900;
			m_strCurrBand="GSM1900";
			m_iPCL=0;
		}
		else if (!strcmp(strValue,"GSM850"))
		{
			m_iCurrBand=GSM_850_BAND_ID;
			m_iFTMBand=FTM_GSM_BER_CELL_850;
			m_strCurrBand="GSM850";
			m_iPCL=5;
		}
		else
		{
			LogTrace(MSG_FATAL,_T("WrongTestBand"));
			return false;
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
		LogTrace(MSG_FATAL,_T("Not Find IsEdge default false"));
		m_IsEdge=0;
	}
	else
	{
		m_IsEdge=CStr::StrToInt(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("IsSaveToIni"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_LOW,_T("Not Find IsSaveToIni,default true"));
		m_IsSaveToIni=1;
	}
	else
	{
		m_IsSaveToIni=CStr::StrToInt(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("strNodeType"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_LOW,_T("Not Find strNodeType,default GSM"));
		m_strType="GSM";
	}
	else
	{
		m_strType=itrFind->second;
	}

	itrFind=pcSettingMap->find(_T("UseFollowPara"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,_T("Not Find UseFollowPara,default is true"));
		m_bUseCfgPara=true;
	}
	else
	{
		m_bUseCfgPara=CStr::StrToBool(itrFind->second);
	}

	if (m_bUseCfgPara)
	{
		CString strtemp;
		CStringVtr strVtrtemp;
		itrFind=pcSettingMap->find(_T("TestChan"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find TestChan"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			m_strVtrChan=strVtrtemp;
			CStr::StrVtr2IntVtr(m_iTestChan,strVtrtemp);
		}

		int nPcl=1;
		for(IntItr itrChan=m_iTestChan.begin();itrChan!=m_iTestChan.end();++itrChan,++m_intChNum)
		{
			strtemp.Empty();
			strVtrtemp.clear();
			int nTsize;

			strtemp.Format("TestPCL_CH%d",nPcl);
			itrFind=pcSettingMap->find(_T(strtemp));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_FATAL,_T(strtemp));
				return false;
			}
			else
			{
				nTsize=m_iTestPcl.size();
				strtemp=itrFind->second;
				CStr::ParseString(strtemp,_T(","),strVtrtemp);
				CStr::StrVtr2IntVtr(m_iTestPcl,strVtrtemp);
			}
			nPcl++;
			m_intCh_PclNum.push_back(m_iTestPcl.size()-nTsize);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("PwrRangMax"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find PwrRangMax"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrPwrMax,strVtrtemp);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("PwrRangMin"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find PwrRangMin"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrPwrMin,strVtrtemp);
		}

	}
	else
	{
		LogTrace(MSG_FATAL,_T("Pls set UseFollowPara to 1; no Default Value now")); 
		return false;
	}


	InitData();
	return true;
 }

 bool CGSMCableLossCal::InitData()
 {
	 m_pFunGSMTestDev=m_piTesterDevice->m_piFuncGSMTest;
	 m_bIsStopWhileFail=m_bIsStopWhenFail;
	 m_iFailFlag=0;
	 return true;
 }

 bool CGSMCableLossCal::StartLossMeas(CString strTestItem)
 {//TestItem_TX AVG_TXPWR-A;MAX_PPHASEERR-B;AVG_PHASEERR-C;AVG_CARRFERR-D;AVG_PWRTEMP-E;ORFSSW_JUDGE-F;AVG_SWPWR-G;ORFSMD_JUDGE-H;AVG_MODPWR-I;
	 int iErrorcode;

	 if((iErrorcode=m_pFunGSMTestDev->IGSMTestStartTxMeasurment(30,1,m_strVtrResultTX,strTestItem,m_IsEdge)!=DEVICE_SUCCESS))
	 {
		 LogTrace(MSG_ERROR,_T("GSM Test StartLossMeas Test Fail!"))
			 m_iErrorcode=iErrorcode;
		 m_iFailFlag++;
		 return false;
	 }

	 return true;
 }


 bool CGSMCableLossCal::CheckTXResult(int nIndex,CString strPcl,CString strChan,CString strTestItem)
 {
	 CString strReservedTemp;//for .2f use
	 double  dReservedTemp;//for .2f use
	 int nTestSeq=0;
	 if (strTestItem.Find("A1")!=-1)
	 {
		 m_iItemCode+='A';
		 CRangePair<double> PowerSpec;
		 PowerSpec.SetRange(m_dVtrPwrMax[nIndex],m_dVtrPwrMin[nIndex]);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
	 	 if (PowerSpec.InRange(dReservedTemp))
		 {
			 TestPassLog(m_strCurrBand,strChan+'-'+strPcl,CStr::FloatToStr(PowerSpec.GetMax()),CStr::FloatToStr(PowerSpec.GetMin()),strReservedTemp,"dBm","Power Pass");
		 }
		 else
		 {
			 TestFailLog(m_strCurrBand,strChan+'-'+strPcl,nIndex,CStr::FloatToStr(PowerSpec.GetMax()),CStr::FloatToStr(PowerSpec.GetMin()),strReservedTemp,"dBm","Power Fail");
			 
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='A';

		 nTestSeq++;
	 }
 
	 return true;
 }

 bool CGSMCableLossCal::SetGSMTestLOSS()
 {
	 CString strMsg;
	 double dLoss;
	 m_vCableLoss.clear();
	 for(int i=0;i<3;i++)
	 {
		 if(!m_LossFinder.GetGSMLoss(m_strCurrBand,i,dLoss))
		 {
			 strMsg.Format("GSM Get Loss Band=%s ,ChannelType=%d Fail",m_strCurrBand,i);
			 LogTrace(MSG_ERROR,strMsg);
			 CalFailLog(_T("_"),_T("_"),1001,strMsg);
			 m_iFailFlag++;
			 return false;
		 }
		 m_vCableLoss.push_back(dLoss);
	 }



	 if(DEVICE_SUCCESS!=m_pFunGSMTestDev->IGSMTestSetLoss(m_iCurrBand,m_vCableLoss))
	 {
		 LogTrace(MSG_ERROR,"Set Cableloss device fail");
		 CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		 m_iFailFlag++;
		 return false;

	 }

	 return  true;

 }


 int CGSMCableLossCal::GetItemCode(int nMode,int Band,int Channel,int PowerLevel)
 {
	 int nItemCode=400000;
	 nItemCode+=nMode*100000;

	 switch(Band)
	 {
	 case GSM_850_BAND_ID:
			  nItemCode+=1*10000;

		 break;
	 case GSM_EGSM_BAND_ID:
			  nItemCode+=2*10000;
		 break;
	 case GSM_DCS_BAND_ID:
			  nItemCode+=3*10000;
		 break;
	 case GSM_PCS_BAND_ID:
			  nItemCode+=4*10000;
		 break;
	 default:
		 return -1;
	 }

	 nItemCode+=CGSMBandInfo::GetChannelType(Band,Channel)*1000;

	 nItemCode+=CGSMBandInfo::GetPclType(Band,Channel)*100;

	 return nItemCode;
 }
