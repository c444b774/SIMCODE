#pragma once
#include "IFuncDev.h"
class CFuncDev_8820:public virtual IFuncDev
{
public:
	CFuncDev_8820(void);
	CFuncDev_8820(PCTesterDevice pDev);
	virtual ~CFuncDev_8820(void);

public:
	int SetInput(int iInput);
	int SetOutput(int iOutput);
	int SetCableLoss(double dInLoss,double dOutLoss);
protected:
	int  OpenSecAddr(const CString & strPriAddr,int iSecAddr);
	
protected:
	CString m_iPrimaryAddr;
    int  m_i8820Mode;
	double m_dFerMHz; 
    
    
};
typedef CFuncDev_8820* PCFuncDev_8820;  
