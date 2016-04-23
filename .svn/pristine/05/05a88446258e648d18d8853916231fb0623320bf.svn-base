#include "stdafx.h"
#include "inc\RFObject.h"
 
////////////////////////////////////////////////////////////////////////////////
//  CRFRuntimeClass
PCRFRuntimeClass CRFRuntimeClass::m_pcFirstClass = NULL;
 
CRFRuntimeClass::CRFRuntimeClass(
								 const CString&       strClassName,
								 LPFN_CREATE_OBJECT  lpfnCreateObject,
								 PCRFRuntimeClass    pcNextClass
								 ) :
m_strClassName(strClassName),
m_lpfnCreateObject(lpfnCreateObject),
m_pcNextClass(pcNextClass)
{
}
 
 
PCRFObject CRFRuntimeClass::CreateObject()
{
	PCRFObject pcObject = NULL;
 
	if (m_lpfnCreateObject) {
		pcObject = (*m_lpfnCreateObject)();
	} else {
		
	}
 
	return pcObject;
}
 
PCRFObject CRFRuntimeClass::CreateObject(const CString& strClassName)
{
	PCRFRuntimeClass pcCurrClass = m_pcFirstClass;
	while (pcCurrClass) {
		if (strClassName == pcCurrClass->m_strClassName)
		{ 
			return pcCurrClass->CreateObject(); 
		}
		pcCurrClass = pcCurrClass->m_pcNextClass;
	}
	return NULL;
}
 
 
 
 

_RF_INIT_CLASS::_RF_INIT_CLASS(PCRFRuntimeClass pcNewClass)
{
	pcNewClass->m_pcNextClass = CRFRuntimeClass::m_pcFirstClass;
	CRFRuntimeClass::m_pcFirstClass = pcNewClass;
 
}
 
 
 
 
////////////////////////////////////////////////////////////////////////////////
//  CRFObject
 
static const CString g_strCRFObject = _T("CRFObject");
CRFRuntimeClass CRFObject::classCRFObject(g_strCRFObject, NULL);
static _RF_INIT_CLASS g_init_CRFObject(&CRFObject::classCRFObject);
 
PCRFRuntimeClass CRFObject::GetRuntimeClass() const
{
	return &CRFObject::classCRFObject;
}
 
 
 
