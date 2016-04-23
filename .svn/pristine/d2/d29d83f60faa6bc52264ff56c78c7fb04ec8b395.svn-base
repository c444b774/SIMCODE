#pragma once
#include "FuncDev_8820.h"
#include  "IFuncGSMTest_Dev.h"
class CFuncGSMTest_8820: public IFuncGSMTest_Dev,public CFuncDev_8820
{
public:
	CFuncGSMTest_8820(void);
	CFuncGSMTest_8820(PCTesterDevice pDev);
	virtual ~CFuncGSMTest_8820(void);
	
    int IGSMTestInitGSMtest(const CString& strAddr,int iMode);
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

	int IGSMTestSetLoss(int iGSMBand,const DblVtr & vLossList);
	int IGSMTestSetScreen(int iScreenOFF);
	int IGSMTestInitGSMtest_NSFT(const CString& strAddr,int iFreqMode,int iChan,int iPcl,int iBand);
	int IGSMTestSetTCH(int iChan, int  iPCL);
	int IGSMTestHandOver(int iBand,int iChannel,int iPCL,int iFreqMode=0,int iSlotNum=2);
	int IGSMTestStartTxMeasurment(int BurstQty,int loopi,CStringVtr & strRes,CString strTestItem,int iEdge);
	int IGSMTestStartRxLevelMeasurment(double dCellpower);
	int IGSMTestStartRxBerMeasurment(int BurstQty,double dCellpower,double &dSebr,CString strTestItem);

private:
	CStringVtr strResult;
};


