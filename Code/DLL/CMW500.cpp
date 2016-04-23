#include "StdAfx.h"
#include "CMW500.h"
RF_IMPLEMENT_DYNCREATE(CCMW500)
CCMW500::CCMW500(void)
{
	m_piFunc_Dev=(IFunc_Dev*)new CFuncDev_CMW(dynamic_cast<PCTesterDevice>(this));
	m_piFuncBTTest=(IFuncBTTest_Dev*)new CFuncBT_CMW(dynamic_cast<PCTesterDevice>(this)); 
    m_piFuncWLANTest=(IFuncWLANTest_Dev*)new CFuncWLAN_CMW(dynamic_cast<PCTesterDevice>(this)); 
	m_piFuncGPSTest=(IFuncGPSTest_Dev*)new CFuncGPS_CMW(dynamic_cast<PCTesterDevice>(this)); 
	m_piFuncCDMATest=(IFuncCDMATest_Dev*)new CFuncCDMATest_CMW(dynamic_cast<PCTesterDevice>(this));
	m_piFuncWCDMACal=(IWCDMACal_Dev*)new CFunWCDMACal_CMW(dynamic_cast<PCTesterDevice>(this));
    m_piFuncGSMCal=(IFuncGSMCal_Dev*)new CFunGSMCal_CMW(dynamic_cast<PCTesterDevice>(this));
	m_piFuncWCDMATest=(IFuncWCDMATest_Dev*)new CFuncWCDMATest_CMW(dynamic_cast<PCTesterDevice>(this));
	m_piFuncGSMTest=(IFuncGSMTest_Dev*)new CFunGSMTest_CMW(dynamic_cast<PCTesterDevice>(this));
}

CCMW500::~CCMW500(void)
{



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
	if(m_piFuncGSMTest)
	{
		delete m_piFuncGSMTest;
		m_piFuncGSMTest=NULL;
	}
	   if(m_piFuncGSMCal)
	{
		delete m_piFuncGSMCal;
		m_piFuncGSMCal=NULL;
	}

	    if(m_piFuncBTTest)
	{
		delete m_piFuncBTTest;
		m_piFuncBTTest=NULL;
	}

		 if(m_piFuncWLANTest)
	{
		delete m_piFuncWLANTest;
		m_piFuncWLANTest=NULL;
	}

		  if(m_piFuncGPSTest)
	{
		delete m_piFuncGPSTest;
		m_piFuncGPSTest=NULL;
	}
}
bool CCMW500::InitData(
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

	itrFind=pcSettingMap->find(_T("RFChannel"));
	if(itrFind==pcSettingMap->end())
		return false;

	
    m_iChannelPort=CStr::StrToInt(itrFind->second);

	itrFind=pcSettingMap->find(_T("IsRX1"));
	if(itrFind==pcSettingMap->end())
	{
		m_bIsCommandRX1CMW=1;
	}
	else
	{
		m_bIsCommandRX1CMW=CStr::StrToBool(itrFind->second);
	}
    
   
	return true;
}
 
bool CCMW500::InitData()
{
	return true;
}
