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

#include "stdafx.h"
#include "RFCalTestDLL.h"
 
 

bool RF_CALLING_CONVENSION CRFCalTestDLL::InitData(
	const PCConfigSetting InitConfigData
	)
{

	return CRFQualcommCalTestProcessor::InitData(InitConfigData);
}
 

 
bool RF_CALLING_CONVENSION CRFCalTestDLL::StartProcess()
{
	return 	CRFQualcommCalTestProcessor::Handle();
}
 
void RF_CALLING_CONVENSION CRFCalTestDLL::AbortProcess()
{
	return 	CRFQualcommCalTestProcessor::Abort();
}

bool RF_CALLING_CONVENSION CRFCalTestDLL::SetLoggerFunc(FPFactoryLog fpFactoryLog,
	FPTraceLog fpTraceLog,
	FPCommandLog fpCommandLog,FPFactoryLogEx fpFactoryLogEx)
{
	return CRFQualcommCalTestProcessor::SetLoggerFunction(fpFactoryLog,fpTraceLog,fpCommandLog,fpFactoryLogEx);
}