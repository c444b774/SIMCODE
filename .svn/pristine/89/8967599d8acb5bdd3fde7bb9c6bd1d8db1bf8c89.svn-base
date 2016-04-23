#pragma once
#include "IFuncDev.h"

class CFuncDev_CMU:public virtual IFuncDev
{
public:
	CFuncDev_CMU(void);
	CFuncDev_CMU(PCTesterDevice pDev);
	virtual ~CFuncDev_CMU(void);

public:
	int SetInput(int iInput);
	int SetOutput(int iOutput);
	int SetCableLoss(double dInLoss,double dOutLoss);
protected:
	int  OpenSecAddr(const CString & strPriAddr,int iSecAddr);
	
protected:
	CString m_iPrimaryAddr;
    int  m_iCMUMode;
    
};
typedef CFuncDev_CMU* PCFuncDev_CMU;
