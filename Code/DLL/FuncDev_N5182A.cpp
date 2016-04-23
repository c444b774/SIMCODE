
#include "StdAfx.h"
#include "FuncDev_N5182A.h"

CFuncDev_N5182A::CFuncDev_N5182A(void)
{
}

CFuncDev_N5182A::~CFuncDev_N5182A(void)
{
}
CFuncDev_N5182A::CFuncDev_N5182A(PCTesterDevice pDev):IFuncDev(pDev)
{
  m_pTesterDevice=pDev;
}

