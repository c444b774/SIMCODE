#ifndef _CMU200_H_
#define  _CMU200_H_
#include "CTesterDevice.h"

class CCMU200:public CTesterDevice
{
	RF_DECLARE_DYNCREATE(CCMU200)

public:
	CCMU200();
	virtual ~CCMU200();

	virtual bool InitData(
		PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
		);
 
	virtual bool InitData();
};

#endif