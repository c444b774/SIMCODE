#pragma once
#include "CTesterDevice.h"
#include  "FuncDev_8820.h"
#include  "FuncGSMTest_8820.h"
#include   "FuncWCDMACAL_8820.h"
#include   "FuncWCDMATest_8820.h"
#include    "FuncGSMCal_8820.h"
class MT8820:public CTesterDevice
{
	RF_DECLARE_DYNCREATE(MT8820)
public:
	MT8820(void);
	virtual ~MT8820(void);

		virtual bool InitData(
		PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
		);
 
	virtual bool InitData();


};
