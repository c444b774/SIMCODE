#pragma once
#include "FuncDev_8960.h"
#include  "IFuncCDMATest_Dev.h"
class CFuncCDMATest_8960: public IFuncCDMATest_Dev,public CFuncDev_8960
{
public:
	CFuncCDMATest_8960(void);
	CFuncCDMATest_8960(PCTesterDevice pDev);
	virtual ~CFuncCDMATest_8960(void);

	int ICDMATestInitCDMANStest(const CString& strAddr,const CString strWavefile);//strWavefile for CMW USE
	int ICDMATestHandover(const int iBand,const int iChannel);
	int ICDMATestSetESN(const CString& strESN);
	int ICDMATestWFQ(const double d_CellPower,double  d_Result[]);
	int ICDMATestSetPower(double dCellPower,double dExpectPower,int iPCB);

	int ICDMATestMinPower(int iMeasCount,double *dPower);
	int ICDMATestMaxPower(int iMeasCount,double *dPower);
	int ICDMATestTROLPC(int *iResult);
	int ICDMATestACPR(int iMeasCount,double dACPRValue[],int *iResult);
	int ICDMATestWFQ(int iMeasCount,double* dRho,double* dFer,double* dTer,double* dCFT,double* dPer,double* dMer,double* dEVM);

	int ICDMATestHandoverCall(const int iBand,const int iChannel,const double dCellPwr,const double dFchLev);
	int ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartRXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem);
	int ICDMATestStartWFQMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartMaxPwrMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartACPRMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartMinPwrMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartRxSenPreMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem);
	int ICDMATestStartRxLevelMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem,int iIndex);
	int ICDMATestSetLoss(int iCDMABand,const DblVtr & vLossList);
	int ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem,int powercnt);
	int ICDMATestEndCall();
};
