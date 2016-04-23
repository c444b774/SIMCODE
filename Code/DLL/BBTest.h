#pragma once
#include "IFHandler.h"


class CBBTestProc:public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CBBTestProc)
public:
	CBBTestProc(void);
	~CBBTestProc(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool BBTestMainFunc();



private:

protected: 
	virtual bool DoProcess();
};
