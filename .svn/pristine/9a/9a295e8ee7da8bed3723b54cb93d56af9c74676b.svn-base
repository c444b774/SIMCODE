#include "StdAfx.h"
#include "WCN3660WlanTest.h"
RF_IMPLEMENT_DYNCREATE(CWCN3660WlanTest)
CWCN3660WlanTest::CWCN3660WlanTest(void)
{
	m_mapClassFunc[_T("WlanTestMainFunc")]=&CWCN3660WlanTest::WlanTestMainFunc;
	m_mapClassFunc[_T("Handover")]=&CWCN3660WlanTest::Handover;
	m_mapClassFunc[_T("TxModTest")]=&CWCN3660WlanTest::TxModTest;
	m_mapClassFunc[_T("RxPER")]=&CWCN3660WlanTest::RxPER;
	m_iItemCode=1001;
}

CWCN3660WlanTest::~CWCN3660WlanTest(void)
{
	
}
bool CWCN3660WlanTest::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}
bool CWCN3660WlanTest::Handle()
{
	if(!DoProcess())
	{
		WlanRelease();
		return false;
	}
	WlanRelease();
	return true;
}
bool CWCN3660WlanTest::InitData(
							  PCStringStrMap     pcSettingMap,
							  CRFObjectMap&   cObjectMap
						   ) 
{

	CStringStringMapItr itrFind;
	CRFObjectMap::iterator itrObjectItr;
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
	

	itrFind=pcSettingMap->find(_T("Channel"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'Channel' from ini file!");
		return false;

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivChannel,strVtr);

	}

	itrFind=pcSettingMap->find(_T("RxCellPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'RxCellPower' from ini file!default -70");
		m_dRxCellPower=-65;

	}
	else
	{
		strValue=itrFind->second;
		m_dRxCellPower=CStr::StrToFloat(strValue);
	}
	itrFind=pcSettingMap->find(_T("WlanLoss"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'WlanLoss' from ini file!default 1.5db");
		m_dLoss=1.5;

	}
	else
	{
		strValue=itrFind->second;
		m_dLoss=CStr::StrToFloat(strValue);
	}
	itrFind=pcSettingMap->find(_T("Standard"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'Standard' from ini file!");
		return false;

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",m_strStandardList);
		
	
	}
	itrFind=pcSettingMap->find(_T("CLPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'CLPower' from ini file!");
		return false;

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dCLPowerList,strVtr);
		
	}

	itrFind=pcSettingMap->find(_T("B_PowerSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'B_PowerSpec' from ini file!Use default 6-15");
		m_BPowerSpec.SetRange(6,15);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_BPowerSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}	

	
	itrFind=pcSettingMap->find(_T("B_FreqErrSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'B_FreqErrSpec' from ini file!Use default -20,20");
		m_BFreqErrSpec.SetRange(-20,20);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_BFreqErrSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("B_EVMSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'B_EVMSpec' from ini file!Use default -100,20");
		m_BEVMSpec.SetRange(-100,20);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_BEVMSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("B_RSSISpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'B_RSSISpec' from ini file!Use default -70,-50");
		m_BRSSISpec.SetRange(-70,-50);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_BRSSISpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("B_PerSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'B_PerSpec' from ini file!Use default 0:10");
		m_BPERSpec.SetRange(0,10);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_BPERSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("G_PowerSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'G_PowerSpec' from ini file!Use default 6-15");
		m_GPowerSpec.SetRange(6,15);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_GPowerSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}	


	itrFind=pcSettingMap->find(_T("G_FreqErrSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'G_FreqErrSpec' from ini file!Use default -20,20");
		m_GFreqErrSpec.SetRange(-20,20);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_GFreqErrSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("G_EVMSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'G_EVMSpec' from ini file!Use default -100,20");
		m_GEVMSpec.SetRange(-100,20);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_GEVMSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("G_RSSISpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'G_RSSISpec' from ini file!Use default -70,-50");
		m_GRSSISpec.SetRange(-70,-50);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_GRSSISpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("G_PerSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'G_PerSpec' from ini file!Use default 0:10");
		m_GPERSpec.SetRange(0,10);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_GPERSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("N_PowerSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'N_PowerSpec' from ini file!Use default 6-15");
		m_NPowerSpec.SetRange(6,15);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_NPowerSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}	


	itrFind=pcSettingMap->find(_T("N_FreqErrSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'N_FreqErrSpec' from ini file!Use default -20,20");
		m_NFreqErrSpec.SetRange(-20,20);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_NFreqErrSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("N_EVMSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'N_EVMSpec' from ini file!Use default -100,20");
		m_NEVMSpec.SetRange(-100,20);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_NEVMSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("N_RSSISpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'N_RSSISpec' from ini file!Use default -70,-50");
		m_NRSSISpec.SetRange(-70,-50);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_NRSSISpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("N_PerSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'N_PerSpec' from ini file!Use default 0:10");
		m_NPERSpec.SetRange(0,10);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_NPERSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}




	InitData();
	return true;
}
bool CWCN3660WlanTest::InitData()
{
	m_pFunWLANTestDev=m_piTesterDevice->m_piFuncWLANTest;
	return true;
}
bool CWCN3660WlanTest::WlanTestMainFunc()
{
	if (!this->WlanInit())
	{
		return false;
	}
	for (int j=0;j<m_strStandardList.size();j++)
	{
		m_strStandard=m_strStandardList[j];
		m_dCLPower=m_dCLPowerList[j];
	

	for (int i=0;i<m_ivChannel.size();i++)
	{

		m_iCurrChannel=m_ivChannel[i];
		for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

		{
			int iRetry=0;			

			FPClassFunc fpTestFunc=*itrFP;
			for (;;)
			{
				if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
				{

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
	}

	return true;
}
bool CWCN3660WlanTest::WlanInit()
{
	int iErrorcode;
	if((iErrorcode=m_pPhone->WLANTestAdbInit())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone WLANTestAdbInit Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("WLAN"),_T("-"),iErrorcode,_T("Phone WLANTestAdbInit Fail!"))
			return false;
	}
	//m_pPhone->ADB_KILL_SERVER();
	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone OpenComport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("WLAN"),_T("-"),iErrorcode,_T("Phone OpenComport Fail!"))
			return false;
	}
	Sleep(1000);
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_START())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone FTM_WCN_GEN6_START Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("WLAN"),_T("-"),iErrorcode,_T("Phone FTM_WCN_GEN6_START Fail!"))
			return false;
	}
	if((iErrorcode=m_pFunWLANTestDev->IWLANTestInit(m_strDeviceAddr,m_strWaveFile))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device Init Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("WLAN"),_T("-"),iErrorcode,_T("Test Device Init Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunWLANTestDev->IWLANTestSetInOutPort(1,1))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device SetInOutPort Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("WLAN"),_T("-"),iErrorcode,_T("Test Device SetInOutPort Fail!"))
			return false;
	}
	
	if((iErrorcode=m_pFunWLANTestDev->IWLANTestSetTrigger(-20,20,50))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device SetTrigger Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("WLAN"),_T("-"),iErrorcode,_T("Test Device SetTrigger Fail!"))
			return false;
	}
	LogTrace(MSG_MID,"Init TestDevice WLAN Pass");

	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_STOP())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone FTM_WCN_GEN6_STOP Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("WLAN"),_T("-"),iErrorcode,_T("Phone FTM_WCN_GEN6_STOP Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_START())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone FTM_WCN_GEN6_START Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("WLAN"),_T("-"),iErrorcode,_T("Phone FTM_WCN_GEN6_START Fail!"))
			return false;
	}
	CalPassLog(_T("WLAN"),_T("-"),_T("WLAN Init PASS"))
		return true;
}
bool CWCN3660WlanTest::Handover()
{
	int iErrorcode,iFailFlag=0;
	double dFreqMHz=2407.0+(m_iCurrChannel*5.0);
	m_strStandard=m_strStandard.MakeUpper();
	if (-1<m_strStandard.Find("B"))
	{
		m_strSigType="BDSSs";
		m_iRate=3;
		m_iPreamble=4;
		m_strWaveFile="D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\WLAN_B_11MBps.wv";
	} 
	else if (-1<m_strStandard.Find("G"))
	{
		m_strSigType="GOFDm";
		m_iRate=14;
		m_iPreamble=0;
		m_strWaveFile="D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\WLAN_AG_54MBps.wv";
	}
	else if (-1<m_strStandard.Find("N"))
	{
		m_strSigType="NOFDm";
		m_iRate=30;
		m_iPreamble=2;
		m_strWaveFile="D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\WLAN_N_MCS7_20MHzBW.wv";
	}
	else
	{
		LogTrace(MSG_FATAL," 'Standard' from ini file is error,shout be 11B,11G,11N");
		return false;

	}

	if((iErrorcode=m_pFunWLANTestDev->IWLANTestSetDLType(m_strWaveFile))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device SetDLType Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T("-"),iErrorcode,_T("Test Device SetDLType Fail!"))
			return false;
	}
	if((iErrorcode=m_pFunWLANTestDev->IWLANTestSetType(m_strSigType))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device SetType Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T("-"),iErrorcode,_T("Test Device SetType Fail!"))
			return false;
	}
	if((iErrorcode=m_pFunWLANTestDev->IWLANTestSetFreq(dFreqMHz,m_dCLPower+3,m_dLoss))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device HandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device HandOver Fail!"))
			return false;
	}
	Sleep(500);
	if((iErrorcode=m_pFunWLANTestDev->IWLANTestSetDLFreqPower(dFreqMHz,m_dRxCellPower,m_dLoss))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device DLHandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device DLHandOver Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_SET_CHANNEL(m_iCurrChannel))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone WLAN TEST FTM_WCN_GEN6_SET_CHANNEL Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone WLANTest FTM_WCN_GEN6_SET_CHANNEL Fail!"))
			return false;
	}
	CalPassLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T("Handover Pass!"))
	return true;

}
bool CWCN3660WlanTest::TxModTest()
{
	int iErrorcode,iFailFlag=0;
	double dPower=0,dEVM=0,dFER=0;
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_ENABLE_TX())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone ENABLE_TX Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone ENABLE_TX Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_SET_FRAME(1000,m_iRate,m_iPreamble))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone SET_FRAME Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone SET_FRAME Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_SET_POWER(m_dCLPower))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone SET_POWER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone SET_POWER Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_TXSTOP())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone SET_POWER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone SET_POWER Fail!"))
			return false;
	}
	
	if((iErrorcode=m_pFunWLANTestDev->IWLANTestInitMeasure(3))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device InitMeasure Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device InitMeasure Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_TXSTART())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone TXSTART Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone TXSTART Fail!"))
			return false;
	}
	Sleep(200);
	if((iErrorcode=m_pFunWLANTestDev->IWLANTestModFetchResults(m_iRate,dPower,dEVM,dFER))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ModFetchResults Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T("-"),iErrorcode,_T("Test Device ModFetchResults Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_TXSTOP())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone TXSTOP Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone TXSTOP Fail!"))
			return false;
	}
	if (3==m_iRate)
	{
		if (m_BPowerSpec.InRange(dPower))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_BPowerSpec.GetMax())),_T(CStr::FloatToStr(m_BPowerSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dbm"),_T("TxPower PASS"),"TxPower")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_BPowerSpec.GetMax())),_T(CStr::FloatToStr(m_BPowerSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dbm"),_T("TxPower FAIL"),"TxPower")
				iFailFlag++;
		}
		if (m_BEVMSpec.InRange(dEVM))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_BEVMSpec.GetMax())),_T(CStr::FloatToStr(m_BEVMSpec.GetMin())),_T(CStr::FloatToStr(dEVM)),_T("%"),_T("EVM PASS"),"EVM")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_BEVMSpec.GetMax())),_T(CStr::FloatToStr(m_BEVMSpec.GetMin())),_T(CStr::FloatToStr(dEVM)),_T("%"),_T("EVM FAIL"),"EVM")
				iFailFlag++;
		}
		if (m_BFreqErrSpec.InRange(dFER))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_BFreqErrSpec.GetMax())),_T(CStr::FloatToStr(m_BFreqErrSpec.GetMin())),_T(CStr::FloatToStr(dFER)),_T("kHz"),_T("FreqErr PASS"),"FreqErr")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_BFreqErrSpec.GetMax())),_T(CStr::FloatToStr(m_BFreqErrSpec.GetMin())),_T(CStr::FloatToStr(dFER)),_T("kHz"),_T("FreqErr FAIL"),"FreqErr")
				iFailFlag++;
		}
	}
	else if (14==m_iRate)
	{
		if (m_GPowerSpec.InRange(dPower))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_GPowerSpec.GetMax())),_T(CStr::FloatToStr(m_GPowerSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dbm"),_T("TxPower PASS"),"TxPower")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_GPowerSpec.GetMax())),_T(CStr::FloatToStr(m_GPowerSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dbm"),_T("TxPower FAIL"),"TxPower")
				iFailFlag++;
		}
		if (m_GEVMSpec.InRange(dEVM))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_GEVMSpec.GetMax())),_T(CStr::FloatToStr(m_GEVMSpec.GetMin())),_T(CStr::FloatToStr(dEVM)),_T("db"),_T("EVM PASS"),"EVM")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_GEVMSpec.GetMax())),_T(CStr::FloatToStr(m_GEVMSpec.GetMin())),_T(CStr::FloatToStr(dEVM)),_T("db"),_T("EVM FAIL"),"EVM")
				iFailFlag++;
		}
		if (m_GFreqErrSpec.InRange(dFER))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_GFreqErrSpec.GetMax())),_T(CStr::FloatToStr(m_GFreqErrSpec.GetMin())),_T(CStr::FloatToStr(dFER)),_T("kHz"),_T("FreqErr PASS"),"FreqErr")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_GFreqErrSpec.GetMax())),_T(CStr::FloatToStr(m_GFreqErrSpec.GetMin())),_T(CStr::FloatToStr(dFER)),_T("kHz"),_T("FreqErr FAIL"),"FreqErr")
				iFailFlag++;
		}
	}
	else if (30==m_iRate)
	{
		if (m_NPowerSpec.InRange(dPower))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_NPowerSpec.GetMax())),_T(CStr::FloatToStr(m_NPowerSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dbm"),_T("TxPower PASS"),"TxPower")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_NPowerSpec.GetMax())),_T(CStr::FloatToStr(m_NPowerSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dbm"),_T("TxPower FAIL"),"TxPower")
				iFailFlag++;
		}
		if (m_NEVMSpec.InRange(dEVM))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_NEVMSpec.GetMax())),_T(CStr::FloatToStr(m_NEVMSpec.GetMin())),_T(CStr::FloatToStr(dEVM)),_T("db"),_T("EVM PASS"),"EVM")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_NEVMSpec.GetMax())),_T(CStr::FloatToStr(m_NEVMSpec.GetMin())),_T(CStr::FloatToStr(dEVM)),_T("db"),_T("EVM FAIL"),"EVM")
				iFailFlag++;
		}
		if (m_NFreqErrSpec.InRange(dFER))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_NFreqErrSpec.GetMax())),_T(CStr::FloatToStr(m_NFreqErrSpec.GetMin())),_T(CStr::FloatToStr(dFER)),_T("kHz"),_T("FreqErr PASS"),"FreqErr")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_NFreqErrSpec.GetMax())),_T(CStr::FloatToStr(m_NFreqErrSpec.GetMin())),_T(CStr::FloatToStr(dFER)),_T("kHz"),_T("FreqErr FAIL"),"FreqErr")
				iFailFlag++;
		}
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;
}
bool CWCN3660WlanTest::RxPER()
{
	int iErrorcode,iFailFlag=0;
	double dPER=0;
	short iRSSI=0;
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_ENABLE_RX())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone ENABLE_RX Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone ENABLE_RX Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_SET_RX_DISABLE(m_iRate))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone ENABLE_RX Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone ENABLE_RX Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunWLANTestDev->IWLANTestSetDLSigOn(true))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device InitMeasure Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device InitMeasure Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_WCN_GEN6_GET_RX_RSSI(&iRSSI))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone GET_RX_RSSI Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone GET_RX_RSSI Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->FTM_WCN_GET_PER(5000,&dPER))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone GET_PER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Phone GET_PER Fail!"))
			return false;
	}
	if(3==m_iRate)
	{
		if (m_BRSSISpec.InRange(iRSSI))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_BRSSISpec.GetMax())),_T(CStr::FloatToStr(m_BRSSISpec.GetMin())),_T(CStr::FloatToStr(iRSSI)),_T("-"),_T("RSSI PASS"),"RSSI")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_BRSSISpec.GetMax())),_T(CStr::FloatToStr(m_BRSSISpec.GetMin())),_T(CStr::FloatToStr(iRSSI)),_T("-"),_T("RSSI FAIL"),"RSSI")
				iFailFlag++;
		}
		if (m_BPERSpec.InRange(dPER))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_BPERSpec.GetMax())),_T(CStr::FloatToStr(m_BPERSpec.GetMin())),_T(CStr::FloatToStr(dPER)),_T("-"),_T("PER PASS"),"PER")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_BPERSpec.GetMax())),_T(CStr::FloatToStr(m_BPERSpec.GetMin())),_T(CStr::FloatToStr(dPER)),_T("-"),_T("PER FAIL"),"PER")
				iFailFlag++;
		}
	}
	if(14==m_iRate)
	{
		if (m_GRSSISpec.InRange(iRSSI))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_GRSSISpec.GetMax())),_T(CStr::FloatToStr(m_GRSSISpec.GetMin())),_T(CStr::FloatToStr(iRSSI)),_T("-"),_T("RSSI PASS"),"RSSI")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_GRSSISpec.GetMax())),_T(CStr::FloatToStr(m_GRSSISpec.GetMin())),_T(CStr::FloatToStr(iRSSI)),_T("-"),_T("RSSI FAIL"),"RSSI")
				iFailFlag++;
		}
		if (m_GPERSpec.InRange(dPER))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_GPERSpec.GetMax())),_T(CStr::FloatToStr(m_GPERSpec.GetMin())),_T(CStr::FloatToStr(dPER)),_T("-"),_T("PER PASS"),"PER")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_GPERSpec.GetMax())),_T(CStr::FloatToStr(m_GPERSpec.GetMin())),_T(CStr::FloatToStr(dPER)),_T("-"),_T("PER FAIL"),"PER")
				iFailFlag++;
		}
	}
	if(30==m_iRate)
	{
		if (m_NRSSISpec.InRange(iRSSI))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_NRSSISpec.GetMax())),_T(CStr::FloatToStr(m_NRSSISpec.GetMin())),_T(CStr::FloatToStr(iRSSI)),_T("-"),_T("RSSI PASS"),"RSSI")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_NRSSISpec.GetMax())),_T(CStr::FloatToStr(m_NRSSISpec.GetMin())),_T(CStr::FloatToStr(iRSSI)),_T("-"),_T("RSSI FAIL"),"RSSI")
				iFailFlag++;
		}
		if (m_NPERSpec.InRange(dPER))
		{
			TestPassLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_NPERSpec.GetMax())),_T(CStr::FloatToStr(m_NPERSpec.GetMin())),_T(CStr::FloatToStr(dPER)),_T("-"),_T("PER PASS"),"PER")

		} 
		else
		{
			TestFailLogEx(m_strStandard,_T(CStr::IntToStr(m_iCurrChannel)),WLAN_Test_BaseItemCode,_T(CStr::FloatToStr(m_NPERSpec.GetMax())),_T(CStr::FloatToStr(m_NPERSpec.GetMin())),_T(CStr::FloatToStr(dPER)),_T("-"),_T("PER FAIL"),"PER")
				iFailFlag++;
		}
	}
	if (iFailFlag>0)
	{
		return false;
	}
	
	
	return true;
}
bool CWCN3660WlanTest::WlanRelease()
{
	m_pFunWLANTestDev->Deivce_Exit();
	m_pPhone->FTM_WCN_GEN6_STOP();
	m_pPhone->WLANTestAdbRelease();
	return true;
}
