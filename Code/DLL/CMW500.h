#pragma once
#include "CTesterDevice.h"
#include  "FuncDev_CMW.h"
#include  "FuncBT_CMW.h"
#include  "FuncWLAN_CMW.h"
#include  "FuncGPS_CMW.h"
#include  "FuncCDMATest_CMW.h"
#include  "FuncGSMCal_CMW.h"
#include  "FuncWCDMACal_CMW.h"
#include  "FuncWCDMATest_CMW.h"
#include "FunGSMTest_CMW.h"
class CCMW500:public CTesterDevice
{
	RF_DECLARE_DYNCREATE(CCMW500)
public:
	CCMW500(void);
	~CCMW500(void);

	virtual bool InitData(
		PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
		);
 
	virtual bool InitData();

	
};
