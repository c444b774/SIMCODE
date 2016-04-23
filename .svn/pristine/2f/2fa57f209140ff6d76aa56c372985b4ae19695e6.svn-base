#pragma once
#include "FuncDev_CMW.h"
#include "IFuncCDMATest_Dev.h"


class CFuncCDMATest_CMW:public IFuncCDMATest_Dev,public CFuncDev_CMW
{
public:
	CFuncCDMATest_CMW(void);
	virtual ~CFuncCDMATest_CMW(void);
	CFuncCDMATest_CMW(PCTesterDevice pDev);

	int ICDMATestInitCDMANStest(const CString& strAddr,const CString strWavefile);
	int ICDMATestHandover(const int iBand,const int iChannel);
	int ICDMATestSetESN(const CString& strESN);
	int ICDMATestWFQ(const double d_CellPower,double d_Result[]);

	int ICDMATestHandoverCall(const int iBand,const int iChannel,const double dCellPwr,const double dFchLev);
	int ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem,int powercnt);
	int ICDMATestStartRXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem);
	int ICDMATestStartRxLevelMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem,int iIndex);
	int ICDMATestSetLoss(int iCDMABand,const DblVtr & vLossList);
	int ICDMATestEndCall();

};
