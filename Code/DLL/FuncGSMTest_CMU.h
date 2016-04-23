#pragma once
#include "FuncDev_CMU.h"
#include  "IFuncGSMTest_Dev.h"
class CFuncGSMTest_CMU:public IFuncGSMTest_Dev,public CFuncDev_CMU
{
public:
	CFuncGSMTest_CMU(void);
	CFuncGSMTest_CMU(PCTesterDevice pDev);
	virtual ~CFuncGSMTest_CMU(void);
    int IGSMTestInitGSMtest(const CString& strAddr);
	int IGSMTestSetPCL(int iPCL);
	int IGSMTestSetBand(int iBand);
	int IGSMTestSetBSLev(double dLev);
	int IGSMTestSetCH(int iBCCH,int iTCCH);
	int IGSMTestSetInputLevel(double dMax,bool bAuto);
	int IGSMTestSetBitStream(BitDataType eType);
	int IGSMTestConfigGSMTest();
	int IGSMTestQueryCallState(CString & strState);
	int IGSMTestProceActOnOff(bool bOn);
	int IGSMTestProceMTC();
	int IGSMTestConfigTestPara();

};
