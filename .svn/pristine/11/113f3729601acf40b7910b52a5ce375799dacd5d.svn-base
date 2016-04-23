#pragma once
#include "ifuncgsmtest_dev.h"
#include  "FuncDev_CMW.h"
class CFunGSMTest_CMW :
	public IFuncGSMTest_Dev,public CFuncDev_CMW
{
public:
	CFunGSMTest_CMW(void);
	~CFunGSMTest_CMW(void);
	CFunGSMTest_CMW(PCTesterDevice pDev);

	int IGSMTestSetLoss(int iGSMBand,const DblVtr & vLossList);
	int IGSMTestSetScreen(int iScreenOFF);
	int IGSMTestInitGSMtest_NSFT(const CString& strAddr,int iFreqMode,int iChan,int iPcl,int iBand);
	int IGSMTestHandOver(int iBand,int iChannel,int iPCL,int iFreqMode=0,int iSlotNum=2);
	int IGSMTestStartTxMeasurment(int BurstQty,int loopi,CStringVtr &strResult,CString strTestItem,int iEdge);
	int IGSMTestStartRxLevelMeasurment(double dCellpower);
	int IGSMTestStartRxBerMeasurment(int BurstQty,double dCellpower,double &dSebr,CString strTestItem);
};
