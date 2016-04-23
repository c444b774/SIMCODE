#pragma once
#include  "IFuncDev.h"
class IFuncGSMTest_Dev:public virtual IFuncDev
{
public:
	IFuncGSMTest_Dev(void);
    IFuncGSMTest_Dev(PCTesterDevice pDev);
	virtual ~IFuncGSMTest_Dev(void);

//GSMtest_Interface
public:
	virtual int IGSMTestSetBand(int iBand){return DEVICE_SUCCESS;}
	virtual int IGSMTestSetBSLev(double dLev){return DEVICE_SUCCESS;}
	virtual int IGSMTestSetCH(int iBCCH,int iTCCH){return DEVICE_SUCCESS;}
	virtual int IGSMTestInitGSMtest(const CString& strAddr,int iMode=0){return DEVICE_SUCCESS;}
	virtual int IGSMTestSetPCL(int iPCL){return DEVICE_SUCCESS;}
	virtual int IGSMTestSetInputLevel(double dMax,bool bAuto=false){return DEVICE_SUCCESS;}
	virtual int IGSMTestSetBitStream(BitDataType eType){return DEVICE_SUCCESS;}
	virtual int IGSMTestConfigGSMTest(){return DEVICE_SUCCESS;}
	virtual int IGSMTestQueryCallState(CString & strState){return DEVICE_SUCCESS;}
	virtual int IGSMTestProceActOnOff(bool bOn=true){return DEVICE_SUCCESS;}
	virtual int IGSMTestProceMTC(){return DEVICE_SUCCESS;}
	virtual int IGSMTestConfigTestPara(){return DEVICE_SUCCESS;}
	
	virtual int IGSMTestSetLoss(int iGSMBand,const DblVtr & vLossList){return DEVICE_SUCCESS;}
	virtual int IGSMTestInitGSMtest_NSFT(const CString& strAddr,int iFreqMode,int iChan,int iPcl,int iBand){return DEVICE_SUCCESS;}
	virtual int IGSMTestSetScreen(int iScreenOFF){return DEVICE_SUCCESS;}
	virtual int IGSMTestHandOver(int iBand,int iChannel,int iPCL,int iFreqMode=0,int iSlotNum=2){return DEVICE_SUCCESS;}
	virtual int IGSMTestStartTxMeasurment(int BurstQty,int loopi,CStringVtr &strResult,CString strTestItem,int iEdge){return DEVICE_SUCCESS;}
	virtual int IGSMTestStartRxLevelMeasurment(double dCellpower){return DEVICE_SUCCESS;}
	virtual int IGSMTestStartRxBerMeasurment(int BurstQty,double dCellpower,double &dSebr,CString strTestItem){return DEVICE_SUCCESS;}
};
typedef IFuncGSMTest_Dev* PIFuncGSMTest_Dev;
