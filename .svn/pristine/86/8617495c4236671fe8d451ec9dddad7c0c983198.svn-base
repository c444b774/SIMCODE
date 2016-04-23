#include "StdAfx.h"
#include "TDSCableLossCal.h"
RF_IMPLEMENT_DYNCREATE(CTDSCableLossCal)

CTDSCableLossCal::CTDSCableLossCal(void)
{
	m_mapClassFunc[_T("TdCableLossMainFunc")]=&CTDSCableLossCal::TdCableLossMainFunc;
	m_mapClassFunc[_T("TdMakeGoldenSemple")]=&CTDSCableLossCal::TdMakeGoldenSemple;
	m_mapClassFunc[_T("TdSetCableLoss")]=&CTDSCableLossCal::TdSetCableLoss;
	
}

CTDSCableLossCal::~CTDSCableLossCal(void)
{
}

bool CTDSCableLossCal::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}
bool  CTDSCableLossCal::Handle()
{
	if(!DoProcess())
	{
		m_pPhone->FTM_TDSCDMA_EndCall();
		return false;
	}	

	return true;
}
bool CTDSCableLossCal::TdCableLossMainFunc()
{
	
	
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

	{

		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}

	return true;
}

bool CTDSCableLossCal::TdMakeGoldenSemple()
{
	
	if (!TdMeasPower())
	{
		return false;
	}

	m_dvGoldenPower.clear();
	m_dvGoldenPower=m_dvPowerMeas;
	if (!WriteGoldenPower())
	{
		CalFailLog(m_strTestBand,"-",1003,"SetCableLoss Fail");
		return false;
	}	
	return true;
}
bool CTDSCableLossCal::TdSetCableLoss()
{
	CStringVtr cvChannel;
	CStringVtr cvLoss;
	CStringStringMap mapString2String;

	if (!TdMeasPower())
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
		dTemp=m_dvGoldenPower[i]-m_dvPowerMeas[i]+m_vCableLoss[i];
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
bool CTDSCableLossCal::TdMeasPower()
{
	int iErrorcode;
	m_dvPowerMeas.clear();

	int iCallChannel=m_ivTestChannelList[0];
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAInitSet(m_strDeviceAddr))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Init TDSCDMA Test Dev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Init TDSCDMA Test Dev Fail!"))
			return false;
	}

	if (!SetTdLoss())
		return false;

	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAHandOver(m_iTestBand,iCallChannel))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Dev set channel Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Dev set channel Fail!"))
			return false;
	}

	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMASetPower(-75,-10))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Dev set power Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Dev set channel Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("TDSCDMA Test Phone Open Comport Fail!"))
			return false;
	}



	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone Set FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("TDSCDMA Test Phone Set FTM Mode Fail!"))
			return false;
	}
	m_pPhone->FTM_SET_MODE_ID(FTM_MODE_ID_TDSCDMA);
	int iStartSessiontime=2;
	do 
	{
		
		iErrorcode=(m_pPhone->FTM_TDSCDMA_BER_StartSession(10000));

	} while (iErrorcode!=PHONE_SUCCESS&&iStartSessiontime-->0);
	if(iErrorcode!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone BER_StartSession Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("TDSCDMA Test Phone BER_StartSession Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_TDSCDMA_BER_AcquirePilot(iCallChannel))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone BER_AcquirePilot Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T(CStr::IntToStr(iCallChannel)),iErrorcode,_T("TDSCDMA Test Phone BER_AcquirePilot Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_TDSCDMA_BER_SetupRMC_DCH(FTM_TDSCDMA_BER_RMC_TYPE_12_2_SC,4,2,-10,1))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone BER_SetupRMC_DCH Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T(CStr::IntToStr(iCallChannel)),iErrorcode,_T("TDSCDMA Test Phone BER_SetupRMC_DCH Fail!"))
			return false;
	}

	for (int i=0;i<m_ivTestChannelList.size();i++)
	{
		int iCurrChannel=m_ivTestChannelList[i];
		if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAHandOver(m_iTestBand,iCurrChannel))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device HandOver Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),iErrorcode,_T("Test Device HandOver Fail!"))
				return false;
		}

		if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMASetPower(-65,0,2))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device HandOver Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),iErrorcode,_T("Test Device HandOver Fail!"))
				return false;
		}

		m_iItemCode=WCDMA_Call_HandOver_Phone_BaseItemCode;
		if((iErrorcode=m_pPhone->FTM_TDSCDMA_BER_Handover(0,4,2,24,1,iCurrChannel))!=PHONE_SUCCESS)
		{           
			LogTrace(MSG_ERROR,_T("Phone FTM_TDSCDMA_BER_Handover fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),iErrorcode,_T("Phone FTM_TDSCDMA_BER_Handover fail!"))
				return false;
		}

		if(!m_pPhone->IsPhoneConnected())
		{           
			LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),iErrorcode,_T("Phone Disconnected!"))
				return false;
		}
		double dPowerMeasured;
		if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAMaxPower(m_iMeasureCount,&dPowerMeasured))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ITDSCDMAMaxPower Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),iErrorcode,_T("Test Device ITDSCDMAMaxPower Fail!"))
				return false;
		}
		if (m_dMaxPowerLimit.InRange(dPowerMeasured))
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower PASS"),"MaxPower")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(iCurrChannel)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower FAIL"),"MaxPower")
				return false;
		}
		m_dvPowerMeas.push_back(dPowerMeasured);
	}
	m_pFuncTDSTestDev->Deivce_Exit();
//****************************
	m_pPhone->FTM_TDSCDMA_EndCall();

	m_pPhone->CloseComport();
	return true;
}
bool CTDSCableLossCal::ReadGoldenPower()
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
	case 34:
		iNVoffset=66;
		break;
	case 39:
		iNVoffset=60;
		break;
	case 40:
		iNVoffset=72;
		break;
	default:
		strMsg=_T("unkown band!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
		CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;

	}
	m_dvGoldenPower.clear();
	for (int i=0;i<3;i++)
	{
		dGoldenPower=(double)uiData[iNVoffset+2*i]+(double)uiData[iNVoffset+2*i+1]/100.0;
		m_dvGoldenPower.push_back(dGoldenPower);
		strMsg.Format("GoldenPower:%.2f",dGoldenPower);
		CalPassLog(m_strTestBand,CStr::IntToStr(i+1),strMsg);
	}
	strMsg.Format("Band%d GoldenPower:%.2f,%.2f,%.2f",m_iTestBand,m_dvGoldenPower[0],m_dvGoldenPower[1],m_dvGoldenPower[2]);
	LogTrace(MSG_MID,strMsg)
		

	return true;

}

bool CTDSCableLossCal::WriteGoldenPower()
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
	case 34:
		iNVoffset=66;
		break;
	case 39:
		iNVoffset=60;
		break;
	case 40:
		iNVoffset=72;
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
		double dGoldenPower=m_dvGoldenPower[i];
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



bool CTDSCableLossCal::InitData(
							PCStringStrMap     pcSettingMap,
							CRFObjectMap&   cObjectMap
							) 
{
	CStringStringMapItr itrFind;
	CString strValue;
	CString strMainFun;
	CStringVtr strVtr;
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
	}

	itrFind=pcSettingMap->find(_T("TestBand"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TestBand' from ini file! ");
		return false;

	}
	else
	{
		m_iTestBand=CStr::StrToInt(itrFind->second);
		m_strTestBand.Format("B%d",m_iTestBand);
	}

	itrFind=pcSettingMap->find(_T("TestChannelList"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TestChannelList' from ini file!");
		return false;

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivTestChannelList,strVtr);

	}
	itrFind=pcSettingMap->find(_T("MeasureCount"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'MeasureCount' from ini file! defult is 10 ");
		m_iMeasureCount=10;

	}
	else
	{
		m_iMeasureCount=CStr::StrToInt(itrFind->second);

	}
	itrFind=pcSettingMap->find(_T("MaxPowerLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'MaxPowerLimit' from ini file!Use default 18-25");
		m_dMaxPowerLimit.SetRange(18,25);
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

bool CTDSCableLossCal::InitData()
{
	m_pFuncTDSTestDev=m_piTesterDevice->m_piFuncWCDMATest;
	return true;
}
bool CTDSCableLossCal::SetTdLoss()
{
	CString strMsg;
	double dLoss;
	m_vCableLoss.clear();
	for(int i=0;i<3;i++)
	{
		if(!m_LossFinder.GetWCDMALoss(m_strTestBand,i,dLoss))
		{
			strMsg.Format("Get Loss Band=%s ,ChannelType=%d Fail",m_strTestBand,i);
			LogTrace(MSG_ERROR,strMsg);
			CalFailLog(_T("_"),_T("_"),1001,strMsg);
			return false;
		}
		m_vCableLoss.push_back(dLoss);
	}

	if(DEVICE_SUCCESS!=m_pFuncTDSTestDev->ITDSCDMASetLoss(m_iTestBand,m_vCableLoss))
	{
		LogTrace(MSG_ERROR,"Set Cableloss device fail");
		CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		return false;

	}

	return  true;
}
