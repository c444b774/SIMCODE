

#ifndef __RF_CAL_TEST_DLL_H__
#define __RF_CAL_TEST_DLL_H__
 
#include "inc\IRFCalTestDLL.h"
#include "CRFCalTestProcessor.h"
 
class CRFCalTestDLL : public IRFCalTestDLL,CRFQualcommCalTestProcessor {
public:
	
 
	virtual bool RF_CALLING_CONVENSION InitData(
		const PCConfigSetting InitConfigData
		);
 
	
	virtual bool RF_CALLING_CONVENSION StartProcess();
 
	virtual void RF_CALLING_CONVENSION AbortProcess();
	virtual bool RF_CALLING_CONVENSION SetLoggerFunc(FPFactoryLog fpFactoryLog,FPTraceLog fpTraceLog,FPCommandLog fpCommandLog,FPFactoryLogEx fpFactoryLogEx);
 
	virtual void RF_CALLING_CONVENSION Free()
	{
		delete this;
	}
 
	
 
 
};
typedef CRFCalTestDLL* PCRFCalTestDLL;
 
#endif  //  __RF_CAL_TEST_DLL_H__
