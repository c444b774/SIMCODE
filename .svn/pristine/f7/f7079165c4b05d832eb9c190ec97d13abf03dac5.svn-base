#include "StdAfx.h"
#include "MT8820.h"



RF_IMPLEMENT_DYNCREATE(MT8820)
MT8820::MT8820(void)
{ 
  m_piFunc_Dev=(IFunc_Dev*)new CFuncDev_8820(dynamic_cast<PCTesterDevice>(this));
  m_piFuncGSMTest=(IFuncGSMTest_Dev*)new CFuncGSMTest_8820(dynamic_cast<PCTesterDevice>(this));
  m_piFuncWCDMACal=(IWCDMACal_Dev* )new  CFuncWCDMACAL_8820(dynamic_cast<PCTesterDevice>(this));
  m_piFuncWCDMATest=(IFuncWCDMATest_Dev*)new CFuncWCDMATest_8820(dynamic_cast<PCTesterDevice>(this));
  m_piFuncGSMCal=(IFuncGSMCal_Dev*)new CFuncGSMCAL_8820(dynamic_cast<PCTesterDevice>(this));

}

MT8820::~MT8820(void)
{
	if(m_piFuncGSMTest)
	{
		delete m_piFuncGSMTest;
		m_piFuncGSMTest=NULL;
	}

	if(m_piFuncWCDMACal)
	{
		delete m_piFuncWCDMACal;
		m_piFuncWCDMACal=NULL;
	}

		if(m_piFuncWCDMATest)
	{
		delete m_piFuncWCDMATest;
		m_piFuncWCDMATest=NULL;
	}

	   if(m_piFuncGSMCal)
	{
		delete m_piFuncGSMCal;
		m_piFuncGSMCal=NULL;
	}
}

bool MT8820::InitData(
		PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
		)

{
	CStringStringMapItr itrFind;
	
	itrFind=pcSettingMap->find(_T("RFin"));
	if(itrFind==pcSettingMap->end())
		return false;
	
	m_iInputPort=CStr::StrToInt(itrFind->second);

   itrFind=pcSettingMap->find(_T("RFout"));
	if(itrFind==pcSettingMap->end())
		return false;
	
	m_iOutputPort=CStr::StrToInt(itrFind->second);

   
   itrFind=pcSettingMap->find(_T("ScreenOff"));
	if(itrFind==pcSettingMap->end())
		return false;
	
	m_bIsScreenOff=CStr::StrToBool(itrFind->second);

	return true;
}
 
bool MT8820::InitData()
{
	return true;
}
