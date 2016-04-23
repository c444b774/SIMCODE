#include "stdafx.h"
#include "FuncCDMATest_CMU.h"
#include "CMU200.h"
#include  "FuncDev_CMU.h"
#include  "FuncGSMTest_CMU.h"
#include "FuncWCDMACal_CMU.h"

RF_IMPLEMENT_DYNCREATE(CCMU200)
CCMU200::CCMU200()
{
  m_piFunc_Dev=(IFunc_Dev*)new CFuncDev_CMU(dynamic_cast<PCTesterDevice>(this));
  m_piFuncGSMTest=(PIFuncGSMTest_Dev)new CFuncGSMTest_CMU(dynamic_cast<PCTesterDevice>(this));
  m_piFuncCDMATest=(IFuncCDMATest_Dev*)new CFuncCDMATest_CMU(dynamic_cast<PCTesterDevice>(this));
  m_piFuncWCDMACal=(IWCDMACal_Dev* )new CFuncWCDMACAL_CMU(dynamic_cast<PCTesterDevice>(this));

}
CCMU200::~CCMU200()
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

		

	
}

bool CCMU200::InitData(
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
	{
		 m_bIsScreenOff=false;
	}
	else

	m_bIsScreenOff=CStr::StrToBool(itrFind->second);

	return true;
}
 
bool CCMU200::InitData()
{
	return true;
}