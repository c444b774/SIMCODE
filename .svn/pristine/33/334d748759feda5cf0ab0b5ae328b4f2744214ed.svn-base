
#ifndef _IPHONE_H
#define _IPHONE_H



#include "inc\RFObject.h"
#include "inc\QLib.h"
#include   "inc\QLib_Defines.h"
#include   "inc\CBandInfo.h"
#include   "inc\ILogger.h"
#include   "SerComInterface.h"

class CRFNVItems;
typedef CRFNVItems* PCRFNVItems;
class IPhone : public CRFObject
{

	
public:

	
   
	IPhone(){};
	virtual ~IPhone(){};

	static PILogger		m_piLogger ;
	static CSerComInterface m_SerialInterface;
	PCRFNVItems m_pcRFNVItems;

	bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) = 0;
 
	virtual bool InitData(
		) = 0;
 
    inline static void SetLogger(PILogger piLogger){m_piLogger = piLogger;}

	virtual void TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg);
	virtual void FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg);;
	virtual void CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage);

	virtual int OpenComport(int iComport,int iRetrytimes=10){return PHONE_SUCCESS;}
	virtual void CloseComport(){}
	virtual int RFCal_LinearInterpolation(double * adRawX,
		int *aiRawY,
		int iNumRawData,
		double* aInputX,
		int* aOutputY,
		int iNumDataPoint,
		int iMinValue,
		int iMaxValue){return PHONE_SUCCESS;};
	virtual int RFCal_LinearInterpolation(double * adRawX,
		double *aiRawY,
		int iNumRawData,
		double* aInputX,
		double* aOutputY,
		int iNumDataPoint,
		double iMinValue,
		double iMaxValue,
		int iNumOfPtsToAverageSlope=3){return PHONE_SUCCESS;};
	virtual int FTM_GENERATE_OPCODE( void *  sweep_req,bool  rfmode_seg,bool  tuning_seg,bool  rx_cfg_seg,bool  rx_meas_seg){return PHONE_SUCCESS;} 
	virtual int FTM_SET_Cal_STATE(unsigned char  icalState){return PHONE_SUCCESS;}
	virtual int FTM_CFG_AND_EXEC_CAL_SWEEP(void* sweep_req, unsigned long num_seg, bool is_Last_Sweep, bool enableDbgMsgs ){return PHONE_SUCCESS;}
	virtual int FTM_GET_CAL_SWEEP_RESULTS_V2(void * sweep_resp, void * sweep_req, unsigned long num_seg, unsigned int * err_code_1, unsigned int * err_code_2 ){return PHONE_SUCCESS;}
	virtual int FTM_DO_SELFCAL(unsigned char iCal_Type){return PHONE_SUCCESS;}
	virtual int FTM_FTM_RFNV_WRITE(unsigned short iRFNV_ID, unsigned char* pData, unsigned short iDataSz, unsigned short* iFTM_Error_Code){return PHONE_SUCCESS;}
	virtual bool  OpenATComport(int iComport){return true;}
	virtual void CloseATComport(){}
	virtual int BTTestAdbInit(){return PHONE_SUCCESS;}
	virtual int BTTestReset(){return PHONE_SUCCESS;}
	virtual int WLANTestAdbInit(){return PHONE_SUCCESS;}
	virtual int WLANTestAdbRelease(){return PHONE_SUCCESS;}
	virtual int ADB_KILL_SERVER(){return PHONE_SUCCESS;}
	virtual int BTTestFTMInit(){return PHONE_SUCCESS;}
	virtual int BTTestTxBurst( unsigned char  ihopChannels,  
		unsigned char  itransmitPattern,  
		unsigned char  ipacketType,  
		unsigned char  idataWhiteningEnable,  
		unsigned char  itransitOutputPower, 
		unsigned char  itragetDeviceAddress[6],  
		unsigned char  ilogicalTransportAddress 
){return PHONE_SUCCESS;}
	virtual int BTTestRxEnable( unsigned char  ihopChannels,  
		unsigned char  itransmitPattern,  
		unsigned char  ipacketType,  
		unsigned char  idataWhiteningEnable,  
		unsigned char  itransitOutputPower, 
		unsigned char  itragetDeviceAddress[6],   
		unsigned char  ilogicalTransportAddress 
		){return PHONE_SUCCESS;}
	virtual bool IsPhoneConnected(){return true;}
	virtual int  SetPhoneMode(mode_enum_type eMode){return PHONE_SUCCESS;}
	virtual int  GetPhoneMode(unsigned long *piPhonemode){return PHONE_SUCCESS;}
	virtual int  WriteNV(int iNVID,unsigned char* uiNVValue,int iLength){return PHONE_SUCCESS;}
	virtual int  ReadNV(int iNVID,unsigned char* uiNVValue,int iLength){return PHONE_SUCCESS;}
	virtual int  ReadEnvGainNV(int iNVID,unsigned char* uiNVValue,unsigned short iLength){return PHONE_SUCCESS;}
	virtual int WriteRFNVItemInBatchMode(unsigned short iItemID, unsigned char* piItemData, int iLength, unsigned short* piStatus){return PHONE_SUCCESS;}

	virtual int  ReloadNV(){return PHONE_SUCCESS;}
	virtual int  WriteEFS(int iTimout){return PHONE_SUCCESS;}
	//for WLAN TEST
	virtual int FTM_WCN_GEN6_START(){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_STOP(){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_SET_CHANNEL(int chan){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_ENABLE_TX(){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_ENABLE_RX(){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_SET_FRAME(int iPayloadSize,int iRate,int iPreamble){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_SET_POWER(double dPower){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_TXSTART(){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_TXSTOP(){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_SET_RX_DISABLE(int iRate){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GEN6_GET_RX_RSSI(short* rssiVals){return PHONE_SUCCESS;}
	virtual int FTM_WCN_GET_PER(unsigned long count,double *dPER){return PHONE_SUCCESS;}

	//for GSM TEST
	virtual int FTM_SET_PA_DAC_INPUT  ( unsigned short  iDACinput){return PHONE_SUCCESS;} 
	virtual int FTM_TX_CS_SWEEP  ( 
  unsigned char  iListSize,  
  short *  aiI_DC_Correction,  
  short *  aiQ_DC_Correction,  
  unsigned short *  aiSegmentLength,  
  unsigned short *  piStatus 
 ) {return PHONE_SUCCESS;}  
	virtual int UploadQCNFile(char* sFileName,char* sSPC,unsigned char bAutoRestor,unsigned char bAutoReset,unsigned char bAllowEsnMismatch,unsigned char bIgnorePhoneMode){return PHONE_SUCCESS;}
	virtual void ConfigureCallBacks (  
		EfsDirCB  pEfsDirCallback,  
		generalSWDownloadCB  pGeneralSwDownloadCB,  
		asyncMessageCB  pAsyncMessageCB 
		){}
	virtual unsigned char generalDownloadEvent(unsigned char* pGeneralSwDownloadEvent_union){return 0;}
	virtual int FTM_GSM_BER_StopSession(){return PHONE_SUCCESS;}
	virtual int FTM_GSM_BER_StartSession(unsigned long iTimeOut_ms){return PHONE_SUCCESS;}
	virtual int FTM_GSM_BER_AssignBCCH(unsigned short iChannel, unsigned char iBand){return PHONE_SUCCESS;}
	virtual int FTM_GSM_BER_Handover(unsigned short iChannel, unsigned char iBand, unsigned char iTSC, unsigned char iSlot, unsigned char iMode, unsigned char iPowerLevel, unsigned char iLoopbackType,int iQueryValidTimes,int iFreqMode){return PHONE_SUCCESS;}
	//for WCDMA TEST
	virtual int FTM_WCDMA_EndCall(){return PHONE_SUCCESS;}	
	virtual int FTM_TDSCDMA_EndCall(){return PHONE_SUCCESS;}	
	virtual int FTM_SECOND_CHAIN_TEST_CALL(unsigned char iMode){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_BER_StopSession(){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_BER_RMC_DCH_TFCS_CONFIG_REQ(unsigned char eTFCS_Select,unsigned char aiTFCS_Config[4]){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_BER_StartSession(unsigned long iTimeOut_ms){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_BER_AcquirePilot(unsigned short  iChannel ){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_BER_Handover  (unsigned char iRMC_Type,unsigned char iUL_MaxTxPwr,unsigned long iUL_DPCH_ScrCode,unsigned char iUL_PCA,unsigned char iUL_TPC_StepSize,unsigned short  iDL_PriCPICH_Scr_Code,unsigned short iDL_ChanCode,unsigned char iBetaC,unsigned char iBetaD,unsigned short iChannel){return PHONE_SUCCESS;} 
	virtual int FTM_WCDMA_Measure_BER(double * dBER){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_Measure_RXLV(double * dRXPower,int iScaleFactor=10,double dMinPower=-106){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_BER_SetupRMC_DCH(unsigned char iRMC_Type,unsigned char iUL_MaxTxPwr,unsigned long iUL_DPCH_ScrCode,unsigned char iUL_PCA,unsigned char iUL_TPC_StepSize,unsigned short iDL_PriCPICH_Scr_Code,unsigned short iDL_ChanCode){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_BER_Handover_V2B(unsigned short iChannel){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_AGC_START_LOG(){return PHONE_SUCCESS;}
	virtual int FTM_WCDMA_AGC_STOP_LOG(){return PHONE_SUCCESS;}
	//FOR TDSCDMA TEST
	virtual int FTM_TDSCDMA_BER_RxLevel(unsigned char iRxChain,float* fRxPower){return PHONE_SUCCESS;}
	virtual int FTM_TDSCDMA_BER_StartSession(unsigned long iTimeOut_ms){return PHONE_SUCCESS;}
	virtual int FTM_TDSCDMA_BER_AcquirePilot(unsigned short  iChannel ){return PHONE_SUCCESS;}
	virtual int FTM_TDSCDMA_BER_SetupRMC_DCH(unsigned char iRMC_Type,unsigned char iDL_Slot,unsigned char iUL_Slot,unsigned char iUL_MaxTxPwr,unsigned char iUL_TPC_StepSize){return PHONE_SUCCESS;}
	virtual int DIAG_CHANGE_RX_DIVERSITY(unsigned char bSysMode, unsigned char bChainSelection){return PHONE_SUCCESS;}
	virtual int FTM_TDSCDMA_BER_Handover(unsigned char iRMC_Type,unsigned char iDL_Slot,unsigned char iUL_Slot,unsigned char iUL_MaxTxPwr,unsigned char iUL_TPC_StepSize,unsigned short  iChannel){return PHONE_SUCCESS;}
	//for CMDA2000 test
	virtual int DIAG_READ_ESN_F(CString &strESN) {return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_NS_Start(unsigned char eDR_Type,unsigned long iBand_Class,unsigned char bEnableDiversityAGCLog){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_NS_Stop(){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_PILOT_ACQ(unsigned long iBand_Class,unsigned short iCDMA_Freq,	unsigned long  iAcq_Mode){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_DEMOD_SYNC(){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_DEMOD_FCH(unsigned long iRadio_Cfg){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_NS_SetSER_RCandRS(unsigned long eCurrentCDMA2000_RC,unsigned long eCurrentCDMA2000_DataRate){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_MOD_FCH(unsigned long iRadio_Cfg){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_FCH_LOOPBACK(){return PHONE_SUCCESS;};
	virtual int FTM_CDMA2000_NS_Get_FCH_SER_FER(unsigned long iMinimumNumSymbols,unsigned long  iMinimumNumFrames,unsigned long *piTotalSymbols,unsigned long *piTotalErrorSymbols,unsigned long *piTotalFrames,unsigned long *piTotalFrameErrors,double *pdSER_Calculated,	double *pdFER_Calculated,unsigned long iTimeOut_ms){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_CMD_RELEASE(){return PHONE_SUCCESS;}
	virtual int FTM_CDMA_BER_Handover(unsigned char eDR_Type,unsigned char bEnableDiversityAGCLog,unsigned long iBand_Class,unsigned short iCDMA_Freq, unsigned long iAcq_Mode,unsigned long iRadio_Cfg){return PHONE_SUCCESS;}
	virtual int FTM_CDMA_2000_HardHandOff(unsigned long iBand_Class,unsigned short iCDMA_Freq){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_NS_GetRXRESULT_BYPHONE(unsigned long iBand_Class,
													unsigned char eDR_Type,
													unsigned char bEnableDiversityAGCLog,
													unsigned long eCurrentCDMA2000_RC,
													unsigned long eCurrentCDMA2000_DataRate,
													unsigned long iMinimumNumSymbols,
													unsigned long iMinimumNumFrames,
													unsigned long &iTotalSymbols,
													unsigned long &iTotalErrorSymbols,
													unsigned long &iTotalFrames,
													unsigned long &iTotalFrameErrors,
													double &dSER_Calculated, 
													double &dFER_Calculated,
													unsigned long iTimeOut_ms){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_EndCall(int nDelay){return PHONE_SUCCESS;}
	virtual int FTM_CDMA2000_NS_GetRxLevel_BYPHONE(unsigned long iBand_Class,unsigned long iChan,double &dRxLevResult,int iDelay){return PHONE_SUCCESS;}
	virtual int FTM_EnterOnlineBeforeFTM_Delay(int IsPreOnlineToFTM,unsigned long iTimeOut_ms){return PHONE_SUCCESS;}

	virtual int RFCAL_GSM_Tx_Polar_Cal_Results(unsigned short iNvModeId,
													void* aGSM_Polar_Cal,
													void *aGSM_Polar_Cal_NV,
													unsigned char bCachedByNVManager){return PHONE_SUCCESS;}
	//for CDMA2000 CAL
	virtual int FTM_SET_RF_POWER_MODE(int iMode){return PHONE_SUCCESS;}
	virtual int FTM_CDMA_API2_CALIBRATE_DVGA(unsigned char iPath,short iInputPower,unsigned char* iCoun,unsigned short* iDVGAarray){return PHONE_SUCCESS;}
	virtual int FTM_CDMA_API2_CALIBRATE_LNA(unsigned char	iPath,short  iInputPower,unsigned char	iLNAstep,unsigned char*	iCount,unsigned short* iLNAarray ){return PHONE_SUCCESS;}
	virtual int FTM_CDMA_API2_CALIBRATE_INTELLICEIVER(unsigned char iPath,short iInputPower,unsigned char* iSizeOfBLOB,unsigned char* iCalibrationBLOC){return PHONE_SUCCESS;}
	virtual int RFCAL_Rx_Intellieceiver_Cal_Results(unsigned short iNvModeId,void* aIntelliceiverValue,void* aIntelliceiver_NV,unsigned char bCachedByNVManager){return PHONE_SUCCESS;}
	virtual int FTM_SET_TX_WAVEFORM(unsigned char iWaveformType , unsigned char iWaveformAttrib){return PHONE_SUCCESS;} 
	// for WCDMA Calibration
	virtual int FTM_DO_DC_CAL(){return PHONE_SUCCESS;}
	virtual int FTM_SET_MODE_ID(int iMODE_ID){return PHONE_SUCCESS;} 
	virtual int FTM_SET_MODE(short iNewMode){return PHONE_SUCCESS; }
	virtual int FTM_LTE_SET_TX_MOD_TYPE(unsigned long iModType){return PHONE_SUCCESS;}
	virtual int FTM_LTE_SET_TX_WAVEFORM  (unsigned char  iTxWaveform,  
		unsigned char  inumRBsPUSCH,  
		unsigned char  inumRBsPUCCH,  
		unsigned char  iPUSCHStartRBIndex 
		){return PHONE_SUCCESS;}

	//for LTE XO Cal
	virtual int FTM_SET_BANDWIDTH(short m_iTxChanBW,short m_iRxChanBW){return PHONE_SUCCESS; }
	virtual int FTM_SET_CHAN(unsigned short uiChannel){return PHONE_SUCCESS; }
    virtual int FTM_SET_LNA_RANGE(int iLNARange){return PHONE_SUCCESS; }
	virtual int FTM_SET_TX_ON(bool bIsOn=true){return PHONE_SUCCESS; }
	virtual int FTM_SET_PA_RANGE(int iPARange){return PHONE_SUCCESS; }
	virtual int FTM_SET_PA_STATE(int iState){return PHONE_SUCCESS; }
	virtual int FTM_SET_PDM(int iPDMType,int iPDMValue){return PHONE_SUCCESS; }
	virtual int FTM_SET_RGI(unsigned short  iTxGainIndex){return PHONE_SUCCESS;}
	virtual int FTM_SET_CALIBRATION_STATE(bool bActivate=true){return PHONE_SUCCESS; }
	virtual int FTM_CDMA_CW_WAVEFORM(unsigned char bSelectCW=0){return PHONE_SUCCESS; }
	virtual int FTM_CONFIGURE_TX_SWEEP_CAL(unsigned short iTimeInterval, unsigned short iNumofHDETReadingsPerStep){return PHONE_SUCCESS; }
    virtual int FTM_SET_TX_SWEEP_STEP_SIZE(unsigned char iStepSize){return PHONE_SUCCESS; }
	virtual int FTM_TX_SWEEP_CAL(unsigned char bOnOff=true){return PHONE_SUCCESS; }
	virtual int FTM_GET_HDET_FROM_TX_SWEEP_CAL(unsigned short iIndex, unsigned short* piHDETvalue ){return PHONE_SUCCESS;}
    virtual int RFCAL_CDMA_TxLinCal_BetaScaling_Results(unsigned short iNvModeId,void* aTx_Measured,void* aTx_Result,unsigned char bCachedByNVManager){return PHONE_SUCCESS; }
    virtual int FTM_SET_SECONDARY_CHAIN(unsigned short iMode){return PHONE_SUCCESS; }
	virtual int FTM_SET_MULTI_CHAN(unsigned short iChannel0,unsigned short iChannel1){return PHONE_SUCCESS;}
	virtual int GET_RX_OFFSET_MULTI_CHAN(unsigned short iSecondaryMode,int iMode_ID,int iRxAction,short iExpectedAGC,short * piRxoffsetValue){return PHONE_SUCCESS;} 
	virtual int FTM_GET_ADC_VAL(unsigned short iADC_type, unsigned short* piADC_value){return PHONE_SUCCESS; }

    virtual int FTM_TX_RX_FREQ_CAL_SWEEP(void* pFTM_Tx_Rx_Freq_Cal_Sweep_Request_Response){return PHONE_SUCCESS; }
    virtual int RFCAL_CDMA_Tx_LinVsFreq_Results(unsigned short iNvModId,
																	void* aTx_Measured_Power,
																	void* aTx_MeasuredChannels,
																	void* aTx_NV_Channels,
																	int	  iNV_Resolution_Type,
																	int   iNV_Tx_Comp_Type,
																	void* aTx_LinVsFreq_NV_Result,
																	unsigned char bWriteNVChList,
																	unsigned char bCachedByNVManager){return PHONE_SUCCESS; }
	virtual int RFCAL_NV_Manager_WriteToPhone(void *pWriteToPhoneStatus,bool bIsShowNVStatus=true){return PHONE_SUCCESS;} 
    virtual int RFCAL_CDMA_Tx_LimVsFreq_Results(unsigned short iNvModeId,
																	double dDesiredMaxPower,
																	void* aTx_LimVsFreqMeasured,
																	void* aTx_MeasuredChannels,
																	void* aTx_NV_Channels,
																	void* aTx_LimVsFreq_NV_Result,
																	unsigned char bCachedByNVManager)
	{return PHONE_SUCCESS; }

virtual int RFCAL_GSM_Tx_Polar_ProcessTxSweep( void *  aGSM_Polar_Cal_Measurement,  
  void *  aGSM_Polar_Cal_Processed 
 ) {return PHONE_SUCCESS; } 
virtual int RFCAL_Complete_TxRxCal(	unsigned short iNvModeId,
								   void* aFTM_Request,
								   void* aFTM_Response,
								   void* aTx_NV_Structure,
								   unsigned short numRecords,
								   void* aTx_Lin_Cal_NV_Info,
								   unsigned short* numLin,
								   unsigned short iNVPath,
								   unsigned char bCachedByNVManager
								   ){return PHONE_SUCCESS;}
    virtual int RFCAL_CDMA_RxCal_Results( unsigned short iNV_Mode_ID,
										  unsigned char iIsIntelliceiver,
										  double dDVGAOffsetScalingFactor,
										  void* aRX_Measured,
										  void* aRX_MeasuredChannels,
										  void* aRX_NV_Channels,
										  void* aRX_DVGA_LNA_Cal_NV,
										  unsigned char bWriteNVChList,
										  unsigned char bCachedByNVManager)
	{return PHONE_SUCCESS; }
	virtual int RFCAL_WCDMA_MultiCarrier_RxCal_Results  (unsigned int  iBand,
		unsigned short  iNV_Mode_ID,  
		unsigned char  iIsIntelliceiver,  
		double  dDVGAOffsetScalingFactor,  
		void *  aRX_Measured,  
		void *  aRX_MeasuredChannels,  
		void *  aRX_NV_Channels,  
		void *  aRX_DVGA_LNA_Cal_NV,  
		unsigned char  bWriteNVChList,  
		unsigned char  bCachedByNVManager 
		)  

	{return PHONE_SUCCESS; }


    virtual int FTM_GET_DVGA_OFFSET(short iExpectedRX_AGC, short* piDVGAoffset){return PHONE_SUCCESS; }
	virtual int FTM_GET_RX_AGC(unsigned short *  piRX_AGC ){return PHONE_SUCCESS;}
	virtual int FTM_GET_LNA_OFFSET(unsigned short iLNAindex ,short iExpectedRX_AGC,short* piLNAoffsetValue){return PHONE_SUCCESS; }
	//XO calibration
	virtual int FTM_DO_ENH_XO_DC_CAL(void * pFTM_ENH_XO_Cal_Request, void *pFTM_XO_Cal_Response){return PHONE_SUCCESS; }
    virtual int FTM_DO_ENH_XO_FT_COLLECT_SAMPLE(void * pFTM_ENH_XO_Cal_Request, void *pFTM_XO_Cal_Response){return PHONE_SUCCESS;}
    virtual int FTM_DO_ENH_XO_FT_CURVE_CAL(void * pFTM_ENH_XO_Cal_Request, void *pFTM_XO_Cal_Response){return PHONE_SUCCESS;}
	virtual int FTM_XO_CALIBRATION(unsigned short xo_cal_command,unsigned char xo_cal_version,void * pFTM_XO_Cal_Request, void *pFTM_XO_Cal_Response){return PHONE_SUCCESS;}	
	// Thermal calibration
	virtual int FTM_GET_THERM(unsigned char* iThermValue ){return PHONE_SUCCESS;}
	virtual int FTM_GET_ENH_THERM(unsigned long* iThermValue ){return PHONE_SUCCESS;}
	virtual int RFCAL_Internal_Thermistor_Calibration_Results(void *pInt_Therm_Cal_Meas,void *pInt_Therm_Cal_NV,unsigned char bCachedByNVManager){return PHONE_SUCCESS;}
	
	//GSM calibration
	virtual int FTM_Init6285(){return PHONE_SUCCESS;}
   virtual int RFCAL_GSM_Tx_Linear_Process_PreDist_Cal_Results(	unsigned short iNvModeId,
													void* aGSM_PreDist_Cal,
													void *aGSM_PreDist_Cal_NV,
													unsigned char bCachedByNVManager){return PHONE_SUCCESS;} 
   
   virtual int RFCal_GSM_Tx_DA_Cal_IQ_Predist_Cal_Generate_NV(unsigned short iNvModeId, unsigned char iChainId,
	   void* aGSM_DA_Cal,
	   void* aGSM_PreDist_Cal,
	   void* aGSM_Tx_Cx_Cal_NV,
	   unsigned char bCachedByNVManager){return PHONE_SUCCESS;}
   virtual int RFCAL_GSM_Tx_Linear_Process_Swapped_PreDist_Cal_Results(	unsigned short iNvModeId,
	   void* aGSM_PreDist_Cal,
	   void *aGSM_PreDist_Cal_NV,
	   unsigned char bCachedByNVManager){return PHONE_SUCCESS;}

   virtual int FTM_TX_CFG2_AMAM_SWEEP(unsigned long iPreDcDuration, unsigned long iEdgeDuration,unsigned long iCalRgi, unsigned long * piDigScale){return PHONE_SUCCESS;}
   virtual int FTM_TX_CFG2_AMAM_SWEEP_V2 (unsigned long  iDcDuration,  
										   unsigned long  iEdgeDuration,  
										   unsigned long  iCalRgi,  
										   unsigned long  iWaveformType,  
										   unsigned long *  piDigScale ){return PHONE_SUCCESS;}
   virtual int FTM_SET_GSM_LINEAR_PA_RANGE(unsigned short iSlotNum,unsigned short iPaRange ){return PHONE_SUCCESS;}
   virtual int FTM_SET_TRANSMIT_BURS( unsigned char iSlotNum, short iDataSource, unsigned char iTSCindex,unsigned long iNumBursts, unsigned char bIsInfiniteDuration ){return PHONE_SUCCESS;}
   virtual int FTM_DA_CAL(	unsigned short iListSize,
				unsigned short*  aiSegLength,
				unsigned char *  aiRgi,
				unsigned char *  aiGsmMode,
				unsigned char *  aiPaRange){return PHONE_SUCCESS;}

   virtual int RFCAL_GSM_Tx_DA_Cal_Results(unsigned short iNvModeId,
													void* aGSM_DA_Cal,
													void *aGSM_DA_Cal_NV,
													unsigned char bCachedByNVManager){return PHONE_SUCCESS;}

   virtual int FTM_GSM_DO_TX_KV_CAL(	unsigned short iLowChan,
										unsigned short iHiChan,
										unsigned short *piLowChanKvco,
										unsigned short *piHiChanKvco){return PHONE_SUCCESS;}
   virtual int FTM_GSM_DO_TX_KV_CAL_V2(	   
	   unsigned short iNumBands,
	   unsigned short iNumTxCycles,
	   unsigned short iNumMeas,
	   unsigned short *piRfModeList,
	   unsigned short *piKvChanCode
	   ){return PHONE_SUCCESS;}
   virtual int TDLTE_Cal_Setup(int iBand,int iChannel,int iconfig){return PHONE_SUCCESS;}
   virtual int LTE_NS_CONFIG_UL_POWER( unsigned char iTxChain,unsigned char iTxPwrCtrlMode,short iTxLevel){return PHONE_SUCCESS;}
   virtual int LTE_NS_CONFIG_UL_WAVEFORM(unsigned char iConfigOverride,
	   unsigned char  iTxChain,  
	   unsigned char  iStartRB,  
	   unsigned char  iNumRB,  
	   unsigned char  iMCS){return PHONE_SUCCESS;}
   virtual int LTE_NS_IS_CONNECTED(){return PHONE_SUCCESS;}
   virtual int LTE_NS_STOP(){return PHONE_SUCCESS;}
   virtual int LTE_NS_IDLE(){return PHONE_SUCCESS;}
   virtual int LTE_GET_BLER(unsigned int iRxSamples,double *dBLER){return PHONE_SUCCESS;}
    virtual int FTM_SET_RX_BURST(unsigned char iSlotNum, short iRxFunction){return PHONE_SUCCESS;}
	virtual int FTM_RX_GAIN_RANGE_CAL(unsigned char iRxRangeBitMask,
			unsigned char iNumAverages,
			unsigned char bToggleRx,
			unsigned long aiRSSI_Result[8]){return PHONE_SUCCESS;}

	 virtual int RFCAL_GSM_Rx_Gain_Range_Results(	unsigned short iNvModeId,
													void* aGSM_Rx_Gain_Range_Result,
													void* aGSM_Rx_Gain_Range_NV,
													unsigned char bCachedByNVManager){return PHONE_SUCCESS;}
	 virtual int RFCAL_GSM_RX_CALIBRATION_GENERATE_NV(	unsigned short iNvModeId,
		 void* aGSM_Rx_Calibration_Params_n_Meas,
		 void* aGSM_Rx_Gain_Range_NV,
		 unsigned char bCachedByNVManager){return PHONE_SUCCESS;}

	virtual int RFCAL_GSM_Carrier_Suppression(unsigned short iNvModeId,short iIdc,short iQdc, void *pGSM_Carrier_Suppression_NV,unsigned char bCatchedByNvManager){return PHONE_SUCCESS;}
	virtual int FTM_GSM_POLAR_TX_SWEEP_CAL  (
  unsigned long  numDac,  
  unsigned long *  dacList,  
  unsigned long *  dacDuration 
 ) {return PHONE_SUCCESS;}  
    virtual int RFCAL_GSM_CAL_ARFCN(	unsigned short iNvModeId,
													unsigned short* aGSM_Cal_ARFCN_List,
													unsigned char iNumOfChannel,
													void * pGSM_Cal_ARFCN_NV,
													unsigned char bCachedByNVManager){return PHONE_SUCCESS;}
	// for BT WLAN
	virtual bool BT_Enable(bool bOn=true){return true;}
	virtual bool BT_TX_Test(int iChannel,int iDataPattern,int iModulationType,int iTxPower){return true;}
	virtual bool BT_RX_Test(){return true;}
    virtual bool SetAtMode(bool IsAtMode=true){return true;}
   
	virtual bool WLAN_Driverop(bool bLoad=true){return true;}
	virtual bool WLAN_Enable(bool bOn=true,bool bIsTx=true,int iAdbType=1){return true;}
	virtual bool WLAN_TX_Test(const CString& strWLANAddr,int iChannel,int iSignalType,int iBurstType,int iBandWidth,int iTxPower,int iRate,int selfinit,int iAdbType=1){return true;}
	virtual bool WLAN_RXBegin_Test(const CString& strWLANAddr,int iChannel,int iSignalType,int iBurstType,int iBandWidth,int iTxPower,int iRate){return true;}
	virtual bool WLAN_RXCount_ValidPackets(int &refCount){return true;}
	virtual bool WLAN_Do_SelfInit(){return true;}
	virtual bool GPS_Enable(bool bIsOn=true){return true;}
	virtual bool GPS_GetCNO(int iSVID,word wLogID,int & iCNO){return true;}
	virtual bool GPS_GEN8_GetCNo(unsigned char iCollectMode,double *  pdCNoDBHz,int *  piFreqInHz){return true;}
	virtual bool GPS_StartAT(int iSVID){return true;}
	virtual bool GPS_GetCNO_AT(int & iCNO){return true;}
	virtual bool CDMA_GSMWCDMA_Mode_AT(int iID){return true;}
	virtual bool Efssyn_AT(){return true;}

	virtual bool DTV_GetBerCNO(int iChannel,double & dCNO,double & SBER){return true;}

	virtual int FTM_GSM_BER_GetRxMetrics(int & iRxlev,int iRetryTimes){return true;}
	virtual int FTM_GSM_StartCall(int isPreOnlineToFTM,int iChainID,int iFreqMode,unsigned long iTimeOut_ms,unsigned short iChannel, unsigned char iBand, unsigned char iTSC=0, unsigned char iSlot=2,unsigned char iMode=0, unsigned char iPowerLevel=2,unsigned char  iLoopbackType=3){return true;}
	virtual int FTM_GSM_EndCall(int nDelay){return PHONE_SUCCESS;}	
	virtual int FTM_EndCall(int iFreqMode){return true;}
	virtual  bool WLAN_Rmmod(){return true;}
	virtual bool Adb_Push(CString filePath,CString targetPath){return true;}
	virtual int FTM_SET_TX_FRAME_MATRIX(unsigned char  iSlotNum,  
  unsigned char  iTurnSlotOn,  
  unsigned short  iPwrLevel,  
  unsigned char  iModScheme ){return true;}
	virtual int FTM_SET_PATH_DELAY( short *  piDelay ){return true;}
	virtual int RFCAL_GSM_Tx_Delay_Cal_Results(unsigned short  iNvModeId,  
  unsigned short  iPolarDelayPathValue,  
  void *  pDelay_Cal_NVItem,  
  unsigned char  bCachedByNVManager 
 )  {return true;}
};


typedef IPhone* PIPhone;
 
#endif 
