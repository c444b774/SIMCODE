#pragma once
#include "IFuncDev.h"
class CFuncDev_8960:public virtual IFuncDev
{
public:
	CFuncDev_8960(void);
	CFuncDev_8960(PCTesterDevice pDev);
	virtual ~CFuncDev_8960(void);
   

};
typedef CFuncDev_8960* PCFuncDev_8960;