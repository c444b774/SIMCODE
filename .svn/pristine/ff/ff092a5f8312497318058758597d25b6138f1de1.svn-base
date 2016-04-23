#pragma once
#include "FuncDev_8960.h"
#include  "IFuncGSMTest_Dev.h"
class CFunGSMTest_8960: public IFuncGSMTest_Dev,public CFuncDev_8960
{
public:
	CFunGSMTest_8960(void);
	virtual ~CFunGSMTest_8960(void);
    CFunGSMTest_8960(PCTesterDevice pDev);

	int IGSMTestSetLoss(int iGSMBand,const DblVtr & vLossList);
	int IGSMTestSetScreen(int iScreenOFF);
	int IGSMTestInitGSMtest_NSFT(const CString& strAddr,int iFreqMode,int iChan,int iPcl,int iBand);
	int IGSMTestHandOver(int iBand,int iChannel,int iPCL,int iFreqMode=0,int iSlotNum=2);
	int IGSMTestStartTxMeasurment(int BurstQty,int loopi,CStringVtr &strResult,CString strTestItem,int iEdge);
	int IGSMTestStartRxLevelMeasurment(double dCellpower);
	int IGSMTestStartRxBerMeasurment(int BurstQty,double dCellpower,double &dSebr,CString strTestItem);
};
