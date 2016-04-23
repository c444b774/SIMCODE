#pragma once
#include  "IFuncDev.h"

class IFuncCDMATest_Dev:public virtual IFuncDev
{
public:
	IFuncCDMATest_Dev(void);
	virtual ~IFuncCDMATest_Dev(void);
	IFuncCDMATest_Dev(PCTesterDevice pDev);
	//CDMA TEST interface
public:

	virtual int ICDMATestInitCDMANStest(const CString& strAddr,const CString strWavefile){return DEVICE_SUCCESS;}//strWavefile for CMW USE
	virtual int ICDMATestHandover(const int iBand,const int iChannel){return DEVICE_SUCCESS;}
	virtual int ICDMATestSetPower(double dCellPower,double dExpectPower,int iPCB){return DEVICE_SUCCESS;}
	virtual int ICDMATestSetESN(const CString& strESN){return DEVICE_SUCCESS;}
	virtual int ICDMATestWFQ(const double d_CellPower,double d_Result[]){return DEVICE_SUCCESS;}

	virtual int ICDMATestHandoverCall(const int iBand,const int iChannel,const double dCellPwr,const double dFchLev){return DEVICE_SUCCESS;}
	virtual int ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem){return DEVICE_SUCCESS;}
	virtual int ICDMATestStartTXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem,int powercnt){return DEVICE_SUCCESS;}
	virtual int ICDMATestStartMinPwrMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,int BurstQty,CStringVtr &strVtrResult,CString strTestItem){return DEVICE_SUCCESS;}
	virtual int ICDMATestMinPower(int iMeasCount,double *dPower){return DEVICE_SUCCESS;}
	virtual int ICDMATestMaxPower(int iMeasCount,double *dPower){return DEVICE_SUCCESS;}
	virtual int ICDMATestTROLPC(int *iResult){return DEVICE_SUCCESS;}
	virtual int ICDMATestACPR(int iMeasCount,double dACPRValue[],int *iResult){return DEVICE_SUCCESS;}
	virtual int ICDMATestWFQ(int iMeasCount,double* dRho,double* dFer,double* dTer,double* dCFT,double* dPer,double* dMer,double* dEVM){return DEVICE_SUCCESS;}
	virtual int ICDMATestStartRXMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem){return DEVICE_SUCCESS;}
	virtual int ICDMATestEndCall(){return DEVICE_SUCCESS;}
	virtual int ICDMATestStartRxLevelMeasurment(const int iBand,const int iChan,const DblVtr d_CellPower,CString strTestItem,int iIndex){return DEVICE_SUCCESS;}
	virtual int ICDMATestSetLoss(int iCDMABand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
};
typedef IFuncCDMATest_Dev* PIFuncCDMATest_Dev;