#include "StdAfx.h"
#include "TDSTestCall.h"

RF_IMPLEMENT_DYNCREATE(CTDSTestCall)
CTDSTestCall::CTDSTestCall(void)
{
	m_mapClassFunc[_T("TDSCallMainFunc")]=&CTDSTestCall::CTDSTestStartCallMainFunc;
	m_mapClassFunc[_T("TDSCall")]=&CTDSTestCall::CTDSTestStartCallFunc;
	m_mapClassFunc[_T("TDS_NS_Call")]=&CTDSTestCall::CTDSTest_NS_StartCallFunc;
}

CTDSTestCall::~CTDSTestCall(void)
{
}

bool CTDSTestCall::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CTDSTestCall::Handle()
{
	if(!DoProcess())
	{
		return false;
	}

	return true;
}

bool CTDSTestCall::CTDSTestStartCallMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CTDSTestCall:: CTDSTest_NS_StartCallFunc()
{
	unsigned char ucTFCIConfig[4]={0,1,2,3};

	if(m_strTesterDevice=="A8960")
	{
		ucTFCIConfig[1]=2;
		ucTFCIConfig[2]=1;
	}
	int iErrorcode;
	//需要修改
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAInitSet(m_strDeviceAddr))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Init TDSCDMA Test Dev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCallBand),_T("-"),iErrorcode,_T("Init TDSCDMA Test Dev Fail!"))
			return false;
	}
	//需要修改
	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMAHandOver(m_iCallBand,m_iCallULChannel))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Dev set channel Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCallBand),_T("-"),iErrorcode,_T("Dev set channel Fail!"))
			return false;
	}

	if((iErrorcode=m_pFuncTDSTestDev->ITDSCDMASetPower(m_dCallCellPower,m_dCallTargetPower))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Dev set power Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCallBand),_T("-"),iErrorcode,_T("Dev set channel Fail!"))
			return false;
	}
	Sleep(400);
	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCallBand),_T("-"),iErrorcode,_T("TDSCDMA Test Phone Open Comport Fail!"))
			return false;
	}



	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone Set FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCallBand),_T("-"),iErrorcode,_T("TDSCDMA Test Phone Set FTM Mode Fail!"))
			return false;
	}
	m_pPhone->FTM_SET_MODE_ID(FTM_MODE_ID_TDSCDMA);
	int iStartSessiontime=2;
	do 
	{
		
		/*if (m_strTesterDevice=="A8960")
		{
			m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_DL_TFCS_CONFIG,ucTFCIConfig);
			m_pPhone->FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(FTM_WCDMA_BER_UL_TFCS_CONFIG,ucTFCIConfig);

		}*/
		iErrorcode=(m_pPhone->FTM_TDSCDMA_BER_StartSession(m_dBERSessionTimeOut));

	} while (iErrorcode!=PHONE_SUCCESS&&iStartSessiontime-->0);
	if(iErrorcode!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone BER_StartSession Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCallBand),_T("-"),iErrorcode,_T("TDSCDMA Test Phone BER_StartSession Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_TDSCDMA_BER_AcquirePilot(m_iCallULChannel))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone BER_AcquirePilot Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCallBand),_T(CStr::IntToStr(m_iCallULChannel)),iErrorcode,_T("TDSCDMA Test Phone BER_AcquirePilot Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->FTM_TDSCDMA_BER_SetupRMC_DCH(FTM_TDSCDMA_BER_RMC_TYPE_12_2_SC,4,2,m_dCallTargetPower,1))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("TDSCDMA Test Phone BER_SetupRMC_DCH Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strCallBand),_T(CStr::IntToStr(m_iCallULChannel)),iErrorcode,_T("TDSCDMA Test Phone BER_SetupRMC_DCH Fail!"))
			return false;
	}

	/*if((iErrorcode=m_pPhone->DIAG_CHANGE_RX_DIVERSITY(5,1))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("DIAG_CHANGE_RX_DIVERSITY"))if((iErrorcode=m_pFuncTDSTestDev->IWCDMATestHandOver(m_iCallBand,m_iCallULChannel))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Dev set channel Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(_T(m_strCallBand),_T("-"),iErrorcode,_T("Dev set channel Fail!"))
				return false;
		}
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strCallBand,_T(CStr::IntToStr(m_iCallULChannel)),iErrorcode,_T("DIAG_CHANGE_RX_DIVERSITY"))
			return false;
	}*/

	CalPassLog(_T(m_strCallBand),_T(CStr::IntToStr(m_iCallULChannel)),_T("TDSCDMA_NS StartCall Pass"))
		return true;
}
bool CTDSTestCall::CTDSTestStartCallFunc()
{
	return true;
}

bool CTDSTestCall::InitData(
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


	itrFind=pcSettingMap->find(_T("CALLBand"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'CALLBand' from ini file!");
		return false;

	}
	else
	{
		m_iCallBand=CStr::StrToInt(itrFind->second);
		m_strCallBand.Format("B%d",m_iCallBand);

	}

	itrFind=pcSettingMap->find(_T("CALLChannel"));

	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'CALLChannel' from ini file!");
		return false;

	}
	else
	{
		m_iCallULChannel=CStr::StrToInt(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("CellPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'CellPower' from ini file,Use default -75 dBm!");
		m_dCallCellPower=-75;

	}
	else
	{
		m_dCallCellPower=CStr::StrToFloat(itrFind->second);

	}
	itrFind=pcSettingMap->find(_T("TargetPower"));

	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'TargetPower' from ini file,Use default -10 dBm!");
		m_dCallTargetPower=-10;

	}
	else
	{
		m_dCallTargetPower=CStr::StrToFloat(itrFind->second);

	}
	itrFind=pcSettingMap->find(_T("BERSessionTimeOut"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'BERSessionTimeOut' from ini file!Use default 2000 ms");
		m_dBERSessionTimeOut=2000;

	}
	else
	{
		m_dBERSessionTimeOut=CStr::StrToFloat(itrFind->second);

	}

	itrFind=pcSettingMap->find(_T("RegistTimeOut"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RegistTimeOut' from ini file,Use default 30 ms!");
		m_dRegistTimeOut=30;

	}
	else
	{
		m_dRegistTimeOut=CStr::StrToFloat(itrFind->second);

	}


	InitData();
	return true;
}

bool CTDSTestCall::InitData()
{
	m_pFuncTDSTestDev=m_piTesterDevice->m_piFuncWCDMATest;

	return true;
}