#include "StdAfx.h"
#include "N5182A.h"
RF_IMPLEMENT_DYNCREATE(N5182A)
N5182A::N5182A(void)
{ 
  m_piFunc_Dev=(IFunc_Dev*)new CFuncDev_N5182A(dynamic_cast<PCTesterDevice>(this));
  m_piFuncDTVTest=(IFuncDTVTest_Dev*)new CFuncDTV_N5182A(dynamic_cast<PCTesterDevice>(this));

}

N5182A::~N5182A(void)
{
	if(m_piFuncDTVTest)
	{
		delete m_piFuncDTVTest;
		m_piFuncDTVTest=NULL;
	}
}

bool N5182A::InitData(
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

	return true;
}
 
bool N5182A::InitData()
{
	return true;
}
