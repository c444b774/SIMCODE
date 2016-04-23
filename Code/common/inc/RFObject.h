
///////////////////////////////////////////////////////////
 
#ifndef __RF_RUNTIME_CLASS_H__
#define __RF_RUNTIME_CLASS_H__
#include "inc\commoninclude.h"

 
class CRFObject;
typedef CRFObject* PCRFObject;
 
class CRFRuntimeClass;
typedef CRFRuntimeClass* PCRFRuntimeClass;
typedef const CRFRuntimeClass* ConstPCRFRuntimeClass;
 
typedef map<CString, PCRFRuntimeClass> CRFRuntimeMap;
 
 
class CRFRuntimeClass {
public:
	typedef PCRFObject (*LPFN_CREATE_OBJECT)();
 
	CRFRuntimeClass(
		const CString&       strClassName,
		LPFN_CREATE_OBJECT  lpfnCreateObject,
		PCRFRuntimeClass    pcNextClass = NULL
		);
 
	//  Summary
	//    Create an object of the class.
	//  Returns
	//    A pointer to the created object is returned if the creation is successful, NULL
	//    \otherwise.
	PCRFObject CreateObject();
	//  Summary
	//    Create an object according to the class name.
	//  Parameters
	//    strClassName :  Class name of the object being created.
	//  Returns
	//    A pointer to the created object is returned if the creation is successful, NULL
	//    \otherwise.
	PCRFObject CreateObject(const CString& strClassName);
 
 
public:
	CString                  m_strClassName;
	LPFN_CREATE_OBJECT      m_lpfnCreateObject;
	PCRFRuntimeClass        m_pcNextClass;      //  Next node
	static PCRFRuntimeClass m_pcFirstClass;     //  First node
 
 
};
 

 
class _RF_INIT_CLASS {
public:
	_RF_INIT_CLASS(PCRFRuntimeClass pcNewClass);
};
 
#define RF_RUNTIME_CLASS(class_name)                                            \
	(&class_name::class##class_name)
 
#define RF_DECLARE_DYNAMIC(class_name)                                          \
	public:                                                                     \
	static CRFRuntimeClass class##class_name;                               \
	static class_name* GetObject(CRFObjectMap& cObjectMap, const CString& strName); \
	virtual PCRFRuntimeClass GetRuntimeClass() const ;                      \
	virtual void Release();													\
	typedef bool (class_name::*FPClassFunc)();								\
	map<CString, FPClassFunc> m_mapClassFunc;										\
	FPClassFunc	m_fpMainFunc;													\
	bool SetMainFunc(const CString& strMainFunc);
 
//Support Selecting Main Function from XML
 
 
#define RF_DECLARE_DYNCREATE(class_name)                                        \
	RF_DECLARE_DYNAMIC(class_name)                                              \
	static PCRFObject CreateObject();                                             \
 
#define _RF_IMPLEMENT_RUNTIME_CLASS(class_name, lpfnCreateObject) \
	static const CString g_str##class_name = _T(#class_name);                       \
	CRFRuntimeClass class_name::class##class_name(                              \
	g_str##class_name,                                                      \
	lpfnCreateObject,                                                      \
	NULL                                                                    \
	);                                                                          \
	static _RF_INIT_CLASS g_init_##class_name(&class_name::class##class_name);  \
	PCRFRuntimeClass class_name::GetRuntimeClass() const                        \
{ return &class_name::class##class_name; }                                  \
	void class_name::Release()                                                  \
{ delete this; }                                                            \
	class_name* class_name::GetObject(CRFObjectMap& cObjectMap, const CString& strName) \
{                                                                           \
	map<CString, PCRFObject>::iterator itr= cObjectMap.find(strName);              \
	return dynamic_cast<class_name*>(itr->second);                       \
}                                                                           \
	bool class_name::SetMainFunc(const CString& strMainFunc){							\
	map<CString, FPClassFunc>::iterator itrMainFunc = m_mapClassFunc.find(strMainFunc);\
	if(itrMainFunc != m_mapClassFunc.end())									\
	{m_fpMainFunc = (*itrMainFunc).second;}						\
	else{return false;}return true;}
 
 
 
#define RF_IMPLEMENT_DYNAMIC(class_name)                       \
	_RF_IMPLEMENT_RUNTIME_CLASS(class_name, NULL)
 
#define RF_IMPLEMENT_DYNCREATE(class_name)                     \
	PCRFObject class_name::CreateObject()                                       \
{ return new class_name; }                                                  \
	_RF_IMPLEMENT_RUNTIME_CLASS(class_name, class_name::CreateObject)
 
 
 
////////////////////////////////////////////////////////////////////////////////
 
 
////////////////////////////////////////////////////////////////////////////////
//  CRFObjectMap
typedef map<CString, PCRFObject> CRFObjectMap;
typedef CRFObjectMap::iterator CRFObjectMapItr;
 
////////////////////////////////////////////////////////////////////////////////
//  CRFObject
class CRFObject {
public:
 
	virtual PCRFRuntimeClass GetRuntimeClass() const ;
 
	virtual void Release() { delete this; }
 
	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) = 0;
 
	virtual bool InitData(
		) = 0;
 
 
public:
	static CRFRuntimeClass classCRFObject; 
 
};
 
#endif//__RF_RUNTIME_CLASS_H__
