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

#ifndef __I_RF_CAL_TEST_DLL_H__
#define __I_RF_CAL_TEST_DLL_H__

#include "commoninclude.h"
 
#define RF_CALLING_CONVENSION       __stdcall
 
//  Summary
//    This is the interface for a simple RF Cal and Test system.
class IRFCalTestDLL {
public:
	
	virtual bool RF_CALLING_CONVENSION InitData(
		  const PCConfigSetting InitConfigData
		) = 0;
 

 
	virtual bool RF_CALLING_CONVENSION StartProcess()= 0;
 
	
 
	virtual void RF_CALLING_CONVENSION Free() = 0;

	virtual bool RF_CALLING_CONVENSION SetLoggerFunc(FPFactoryLog fpFactoryLog,FPTraceLog fpTraceLog,FPCommandLog fpCommandLog,FPFactoryLogEx fpFactoryLogEx)=0;
 
	
};
typedef IRFCalTestDLL* PIRFCalTestDLL;
typedef PIRFCalTestDLL* PPIRFCalTestDLL;
 
typedef bool (RF_CALLING_CONVENSION *LPFN_CREATE_RFCALPROCESSOR)(PPIRFCalTestDLL);
 
 
#endif  //  __I_RF_CAL_TEST_DLL_H__
