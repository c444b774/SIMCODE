/* *** <<< DO NOT MODIFY OR REMOVE THIS LINE - BEGIN >>> *** */
/***************************************************************************
 *
 *   This is a part of the Simcom RF Calibration and Test library.
 *
 *   This document contains propriety information, and except with written
 *   permission of Simcom Corp., such information shall not be 
 *   published, or disclosed to others, or used for any purpose, and the   
 *   document shall not be duplicated in whole or in part.  
 *
 *   Copyright (C) 2009 Simcom Corporation
 *   All Rights Reserved.
 *
 ***************************************************************************/
/* *** <<< DO NOT MODIFY OR REMOVE THIS LINE - END >>> *** */

#ifndef __RF_CAL_TEST_PROCESSOR__
#define __RF_CAL_TEST_PROCESSOR__
 

#include "inc\commoninclude.h"
#include "IFHandler.h"


  
class CRFQualcommCalTestProcessor:public IRFHandler
{

 
 
public:
	CRFQualcommCalTestProcessor();
	virtual ~CRFQualcommCalTestProcessor();
 
	bool InitData(
		PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
		);
 
	bool InitData();

	bool InitData(
	PCConfigSetting InitConfigData

		);
 

 

    bool SetLoggerFunction(
		FPFactoryLog fpFactoryLog,
		FPTraceLog fpTraceLog,
		FPCommandLog fpCommandLog,
		FPFactoryLogEx fpFactoryLogEx
		);
	bool Handle();
 
	void Abort();
	
 
	
	
protected:
	virtual bool DoProcess();
	bool ParseConfigData();
	bool CreateObjects();
	bool ApplyHanderList();
 
protected:

	PCConfigSetting		m_pMapConfigSetting;
	vector<CString> m_pProcessList;
	CStringPairVtr  m_pProcessListRunFail;
	CCString2StringMap m_pPreObjectList;
	CCString2StringMap  m_pProcessObjectList;
    CStringStringMap    m_pMainSetting;
	//RFHandlerVtr    m_pHanderList;
	VtrPairStringHandler  m_pHanderListName;


	
	map<CString,CString> m_pPreObject2ClassName;
	map<CString,CString> m_pProcessObject2ClassName;
	CRFObjectMap		m_cObjectMap;
	
	
 
 
};
 
typedef CRFQualcommCalTestProcessor* PCRFCalTestProcessor;
 

#endif