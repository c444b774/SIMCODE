#ifndef _WCDMACALV3Selfcal_H_
#define _WCDMACALV3Selfcal_H_
#include "IFHandler.h"

class CWCDMA_V3_SelfCal :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CWCDMA_V3_SelfCal)
public:
	CWCDMA_V3_SelfCal(void);
	~CWCDMA_V3_SelfCal(void);
	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	IWCDMACal_Dev* m_pFunWCDMACalDev;
private:
	bool m_bWriteEFS;
	USHORT m_DelaymsBeforeSelfCal;
	short m_iCalType;
private:
	bool CWCDMA_V3_SelfCal_MainFunc();
	bool CWCDMA_V3_CAL_Self_Cal();

};
#endif
