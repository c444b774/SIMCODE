#include "StdAfx.h"
#include "LteTestCall.h"
RF_IMPLEMENT_DYNCREATE(CLteTestCall)

CLteTestCall::CLteTestCall(void)
{
	m_mapClassFunc[_T("LteCallMainFunc")]=&CLteTestCall::LteTestStartCallMainFunc;
	m_mapClassFunc[_T("LteCall")]=&CLteTestCall::LteTestStartCallFunc;

}

CLteTestCall::~CLteTestCall(void)
{
}

bool CLteTestCall::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CLteTestCall::Handle()
{
	if(!DoProcess())
	{
		m_pFuncLteTestDev->Deivce_Exit();
		//****************************
		m_pPhone->LTE_NS_IDLE();
		m_pPhone->LTE_NS_STOP();
		return false;
	}
	return true;
}

bool CLteTestCall::LteTestStartCallMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CLteTestCall:: LteTestStartCallFunc()
{

	int iErrorcode;
	int iDLChannel=CLTEBandInfo::GetDLChannel(m_iBand,m_iULChannel);
	//ÐèÒªÐÞ¸Ä
	int iconfig=2;
	if (m_strTesterDevice=="CMW500")
	{
		iconfig=1;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteInitSet(m_strDeviceAddr,m_strWaveFile,m_strLTEMode))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Init Lte Test Dev Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Init Lte Test Dev Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteHandOver(m_iBand,m_iULChannel))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Lte Test Dev HandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Lte Test Dev HandOver Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteConfigWaveForm(50,0,6))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Lte Test Dev ConfigWaveForm Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Lte Test Dev ConfigWaveForm Fail!"))
			return false;
	}
	
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-50,23,2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Lte Test Dev SetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Lte Test Dev SetPower Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->OpenComport(m_iComport))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Phone Open Comport Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone Set FTM Mode Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Phone Set FTM Mode Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->TDLTE_Cal_Setup(m_iBand-1,iDLChannel,iconfig))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone StartCall Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Phone StartCall Fail!"))
			return false;
	}	 
	

	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_WAVEFORM(1,0,0,50,6))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->LTE_NS_IS_CONNECTED())!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strBand),_T("-"),iErrorcode,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
			return false;
	}
	
	


	CalPassLog(_T(m_strBand),_T(CStr::IntToStr(m_iULChannel)),_T("Lte StartCall Pass"))
		return true;
}
bool CLteTestCall::InitData(
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
		m_iBand=CStr::StrToInt(itrFind->second);
		m_strBand.Format("B%d",m_iBand);

	}

	itrFind=pcSettingMap->find(_T("CALLChannel"));

	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'CALLChannel' from ini file!");
		return false;

	}
	else
	{
		m_iULChannel=CStr::StrToInt(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("CellPower"));
	
	itrFind=pcSettingMap->find(_T("LTEMode"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'LTEMode' from ini file!");
		return false;

	}
	else
	{
		m_strLTEMode=itrFind->second;
		//m_iLTEMode=CStr::StrToInt(itrFind->second);
		//m_strLTEMode.Format("%d",m_iLTEMode);

	}
	itrFind=pcSettingMap->find(_T("WaveFile"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'WaveFile' from ini file!");
		m_strWaveFile="D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\library1\\LTE_ProductionTest_1_v01.wv";

	}
	else
	{
		m_strWaveFile=itrFind->second;
		//m_iLTEMode=CStr::StrToInt(itrFind->second);
		//m_strLTEMode.Format("%d",m_iLTEMode);

	}

	InitData();
	return true;
}

bool CLteTestCall::InitData()
{
	m_pFuncLteTestDev=m_piTesterDevice->m_piFuncWCDMATest;

	return true;
}