#include "StdAfx.h"
#include "SP6010.h"
#include  "FuncDev_SP6010.h"
#include "FuncWCDMATest_SP6010.h"
RF_IMPLEMENT_DYNCREATE(SP6010)
SP6010::SP6010(void)
{ 
	m_piFunc_Dev=(IFunc_Dev*)new CFuncDev_SP6010(dynamic_cast<PCTesterDevice>(this));

	m_piFuncWCDMATest=(IFuncWCDMATest_Dev*)new CFuncWCDMATest_SP6010(dynamic_cast<PCTesterDevice>(this));
	m_bUseFastSwitchApp=true;

}

SP6010::~SP6010(void)
{

	
	if(m_piFuncWCDMATest)
	{
		delete m_piFuncWCDMATest;
		m_piFuncWCDMATest=NULL;
	}


}

bool SP6010::InitData(
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

bool SP6010::InitData()
{
	return true;
}
