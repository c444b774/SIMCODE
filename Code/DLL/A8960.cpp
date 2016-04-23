#include "StdAfx.h"
#include "A8960.h"
#include  "FuncDev_8960.h"
#include  "FunGSMTest_8960.h"
#include  "FuncGSMCal_8960.h"
#include  "FuncWCDMACal_8960.h"
#include "FuncWCDMATest_8960.h"
#include  "FuncCDMATest_8960.h"
RF_IMPLEMENT_DYNCREATE(A8960)
A8960::A8960(void)
{ 
  m_piFunc_Dev=(IFunc_Dev*)new CFuncDev_8960(dynamic_cast<PCTesterDevice>(this));
  m_piFuncGSMTest=(IFuncGSMTest_Dev*)new CFunGSMTest_8960(dynamic_cast<PCTesterDevice>(this));
  m_piFuncWCDMACal=(IWCDMACal_Dev*)new CFunWCDMACal_8960(dynamic_cast<PCTesterDevice>(this));
  m_piFuncWCDMATest=(IFuncWCDMATest_Dev*)new CFuncWCDMATest_8960(dynamic_cast<PCTesterDevice>(this));
  m_piFuncCDMATest=(IFuncCDMATest_Dev*)new CFuncCDMATest_8960(dynamic_cast<PCTesterDevice>(this));
  m_piFuncGSMCal=(IFuncGSMCal_Dev*)new CFuncGSMCAL_8960(dynamic_cast<PCTesterDevice>(this));
  m_bUseFastSwitchApp=true;
}

A8960::~A8960(void)
{

	if(m_piFuncGSMTest)
	{
		delete m_piFuncGSMTest;
		m_piFuncGSMTest=NULL;
	}

	if(m_piFuncCDMATest)
	{
		delete m_piFuncCDMATest;
		m_piFuncCDMATest=NULL;
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

bool A8960::InitData(
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
 
bool A8960::InitData()
{
	return true;
}
