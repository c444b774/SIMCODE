#pragma once
#include "ifhandler.h"
#define MAX_RGI_STEPS 128


typedef struct
{
	//! Storage for Tx power (dBm) for each Tx gain state.
	double adPower[ MAX_PA_STATES ][ MAX_RGI_STEPS ];

	//! Storage for Tx	RGIs for each gain state.
	int aiRGI[ MAX_PA_STATES ][ MAX_RGI_STEPS ];

	//! Storage for HDET values to be used to generate HDET vs AGC table.
	unsigned short aiHDET[ MAX_PA_STATES ][ MAX_RGI_STEPS ];

	//! Storage for LPM HDET values to be used to generate LPM HDET vs AGC table. Used for LTE BC13 only.
	unsigned short aiHDETLPM[ MAX_PA_STATES ][ MAX_RGI_STEPS ];

	unsigned short aiTxPurpose[ MAX_PA_STATES];

	double aiBias[MAX_PA_STATES][MAX_RGI_STEPS];

	double adMaxPower[ MAX_PA_STATES ];

	double adMinPower[ MAX_PA_STATES ];

	//! Number of Tx gain states for which Tx power vs PDM was measured.
	unsigned short iNumPAStates;

	//! Number of Tx power vs PDM values measured for each gain state
	unsigned short aiNumTxRGI[ MAX_PA_STATES ];

	int aiPAState[MAX_PA_STATES];



} TxlinStruct;

typedef struct
{
	word opcode;
	byte paState;
	byte rgi;
	dword paBias;
	byte numHdetAvg;
	byte numLpmHdetAvg;
	word rxActions;
	word expRxAGC;
	word txPurpose;

}TRx_Request;

class CESCalTDS :
	public IRFCalProcess
{
	RF_DECLARE_DYNCREATE(CESCalTDS)
public:
	CESCalTDS(void);
	~CESCalTDS(void);

	virtual bool Handle();

	virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	virtual bool InitData();
protected: 
	virtual bool DoProcess();
	vector<FPClassFunc> m_vFPTestFunc;
	IWCDMACal_Dev* m_pFunTDSCalDev;

private:
	bool m_bEnterOnline;
	int m_iBand;
	int m_iRFmode;
	int m_iNVModeID;
	int m_iTxLinChannel;
	int m_iUpperBoundChan;
	IntVtr m_vRGIStep;
	IntVtr m_vPAState;
	DblVtr m_vStartPower;
	DblVtr m_vStopPower;
	IntVtr m_vStartRGI;
	IntVtr m_vStopRGI;
	DblVtr m_vExpectPower;
	IntVtr m_vRFDevices;
	int m_iTxPurpose;
	int m_iTxWaveform;
	IntVtr m_iHDETSample;
	IntVtr m_iLPMHDETSample;
	bool m_bAPTenabled;
	IntVtr m_iPABiasValue;
	CString m_strBiasIniname;

	TxlinStruct myTxLinStruct;

	IntVtr m_ivChannellist;
	IntVtr m_ivTxFreqPAState;
	DblVtr m_dvTxFreqPower;
	DblVtr m_dvTFPLimitMin;
	DblVtr m_dvTFPLimitMax;
	IntVtr m_ivLNAOffsetMin;
	IntVtr m_ivLNAOffsetMax;
	IntVtr m_ivFreqHDETSample;
	IntVtr m_ivFreqLPMHDETSample;
	IntVtr m_ivFreqTxPurpose;
	IntVtr m_ivRxPM;
	IntVtr m_ivRxAction;
	DblVtr m_dvRxPower;
	int m_iRXPath;
	FTM_Cal_Sweep_Request tx_rx_Sweep[200];
	FTM_Cal_Sweep_Response tx_rx_Response[200];
	FTM_Cal_Sweep_Request tx_Sweep[1024];
	FTM_Cal_Sweep_Response sweep_resp[1024];
	unsigned short inumTxlin;
	unsigned short inumTRxFreq;
	int aiRGI[7];
	double aiBias[7];
private: 
	bool SetTDSCalLoss();
	bool ESCalTDSMainFunc();
	bool TxLinearizerFunc();
	bool TxRxFreqCompFunc();
	bool TxLinOldFunc();
	bool TxFreqCompFunc();
	bool RxFreqCompFunc();
	bool GenerateAndWriteNV();
	bool ArrangeMyTxLinStruct(TxlinStruct *txlinstruct);
	bool GetPowerVsBiasXml(CString xmlpath,int rf_mode,int device,int channel,int paState,double* pwrlist,int* biaslist,int* biasNum );
	bool GetPowerVsBiasIni(CString Inipath,int rf_mode,int device,int channel,int paState,double* pwrlist,dword* biaslist,int* biasNum );
	bool GetTxFreqRGI(IntVtr ivPAState,DblVtr dvPower,int * aiRGIList,double * aiBiasList);

};
