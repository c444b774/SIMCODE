#pragma once
#include "FuncDev_CMU.h"
#include  "IFuncCDMATest_Dev.h"
class CFuncCDMATest_CMU: public IFuncCDMATest_Dev,public CFuncDev_CMU
{
public:
	CFuncCDMATest_CMU(void);
	CFuncCDMATest_CMU(PCTesterDevice pDev);
	virtual ~CFuncCDMATest_CMU(void);


	int ICDMATestInitCDMANStest(const CString& strAddr,const CString strWavefile);//strWavefile for CMW USE
	int ICDMATestHandover(const int iBand,const int iChannel);
	int ICDMATestSetESN(const CString& strESN);
	//int ICDMATestWFQ(const double d_CellPower,double  d_Result[]);

	int ICDMATestHandoverCall(const int iBand,const int iChannel,const double dCellPwr,const double dFchLev);
	int ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartRXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem);
	int ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem,int powercnt);
	//int ICDMATestStartWFQMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	//int ICDMATestStartMaxPwrMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	//int ICDMATestStartACPRMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	//int ICDMATestStartMinPwrMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	//int ICDMATestStartRxSenPreMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartRxLevelMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem,int iIndex);
	int ICDMATestSetLoss(int iCDMABand,const DblVtr & vLossList);
	int ICDMATestEndCall();
};