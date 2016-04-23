/* *** <<< DO NOT MODIFY OR REMOVE THIS LINE - BEGIN >>> *** */
/***************************************************************************
 *
 *   This is a part of the Simcom RF Calibration and Test library.
 *
 *   This document contains propriety information, and except with written
 *   permission of Simcom Corp., such information shall not be 
 *   published, or disclosed to others, or used for any purpose, and the   
 *   document shall not be duplicated in whole or in part.  
 *
 *   Copyright (C) 2010 Simcom Corporation
 *   All Rights Reserved.
 *
 ***************************************************************************/
/***************************************************************************
************************Item Code Define Rule********************************
Item Code(6 bytes):
2G Calibration Item Code = 2(1) + Band(1) + Channel(1) + PowerLevel(1) + Item Number(2)
3G Calibration Item Code = 3 + Band + Channel + PowerLevel + Item Number
2G GSM Test Item Code = 4 + Band + Channel + PowerLevel + Item Number
2G EDGE Test Item Code = 5 + Band + Channel + PowerLevel + Item Number
3G Test Item Code = 6 + Band + Channel + PowerLevel + Item Number
Antenna Test Item Code = 7 + Band + Channel + PowerLevel + Item Number
Base Band = 1 + 0 + 0 +  Item Number£¨3bytes£©

Band Definition: 
GSM:   1: 850    2: 900   3: 1800   4: 1900   5: 850/900   6: 1800/1900
EDGE: 1: 850    2: 900   3: 1800    4: 1900
WCDMA:  1: 850   2: 900   3: 1700   4: 1900   5: 2100
CDMA:	1:800	2:1900	

Channel Definition:  
 1: Low Channel   2: Middle Channel   3: High Channel
 
Power Level Definition:
 1: Low Power Level   2: Middle Power Level 	3:High Power Level 
***************************************************************************/
/* *** <<< DO NOT MODIFY OR REMOVE THIS LINE - END >>> *** */
#ifndef _BaseItemCode_H
#define _BaseItemCode_H
//-------------------------------------------------------------------------------------------------
//	2G Calibration BaseItemCode
//------------------------------------------------------------------------------------------------- 
#define GSM_CalGSMInit_BaseItemCode                                      200000
#define GSM_PA_DAC_Search_Calibration_BaseItemCode                       200001              
#define GSM_KVCO_Calibration_BaseItemCode                                200002
#define GSM_CS_Calibration_BaseItemcode                                  200003
#define GSM_Polar_Calibration_BaseItemCode                               200004
#define GSM_RxFreqCompensation_Calibration_BaseItemCode                  200005
#define GSM_TimeDelay_Calibration_BaseItemCode                           200006
#define GSM_AFCPhasing_Calibration_BaseItemCode                          200007
#define GSM_TxRxPhasing_Calibration_BaseItemCode                         200008
#define GSM_PrePhasingTask_Calibration_BaseItemCode                      200009
#define GSM_PostPhasingTask_Calibration_BaseItemCode                     200010
#define GSM_CS_Idc_Calibration_BaseItemCode                              200011
#define GSM_CS_Qdc_Calibration_BaseItemCode                              200012
#define GSM_CalGSMEnd_BaseItemCode                                       200099

//-------------------------------------------------------------------------------------------------
//	2G Test BaseItemCode
//------------------------------------------------------------------------------------------------- 
#define GSM_GSMTestInit_BaseItemCode                                     400000
#define GSM_GSMTestCall_BaseItemCode                                     400001
#define GSM_MaxPower_Test_BaseItemCode                                   400002
#define GSM_Burst_Test_BaseItemCode                                      400003
#define GSM_PeakPhase_Test_BaseItemCode                                  400004
#define GSM_RmsPhase_Test_BaseItemCode                                   400005
#define GSM_FrequencyError_Test_BaseItemCode                             400006
#define GSM_Swit_ORFS_Test_BaseItemCode                                  400007
#define GSM_MOD_ORFS_Test_BaseItemCode                                   400008
#define GSM_RXLev_Test_BaseItemCode                                      400009
#define GSM_TxCurrent_Test_BaseItemCode                                  400010
#define GSM_RXBER_Test_BaseItemCode                                      400011
#define GSM_GSMTestOpenPort_BaseItemCode                                 400090
#define GSM_SetCableLoss_BaseItemCode                                    400096
#define GSM_HandOver_Device_BaseItemCode                                 400097
#define GSM_HandOver_Phone_BaseItemCode                                  400098
#define GSM_GSMTestEnd_BaseItemCode                                      400099

//-------------------------------------------------------------------------------------------------
//	EDGE Test BaseItemCode
//------------------------------------------------------------------------------------------------- 
#define EDGE_EDGEInit_Test_BaseItemCode                                  500000
#define EDGE_EDGECall_Test_BaseItemCode                                  500001
#define EDGE_MaxPower_Test_BaseItemCode                                  500002
#define EDGE_EDGEEVMRMS_Test_BaseItemCode                                500003
#define EDGE_EDGEEVM95_Test_BaseItemCode                                 500004
#define EDGE_FrequencyError_Test_BaseItemCode                            500005
#define EDGE_EDGEORFSSWITCH_Test_BaseItemCode                            500006
#define EDGE_EDGEORFSMOD_Test_BaseItemCode                               500007
#define EDGE_Burst_Test_BaseItemCode                                     500008
#define EDGE_EDGEPeakEVM_Test_BaseItemCode                               500009
#define EDGE_SetCableLoss_BaseItemCode                                   500096
#define EDGE_HandOver_Device_BaseItemCode                                500097
#define EDGE_HandOver_Phone_BaseItemCode                                 500098
#define EDGE_EDGETestEnd_BaseItemCode                                    500099

//-------------------------------------------------------------------------------------------------
//	3G Calibration BaseItemCode
//------------------------------------------------------------------------------------------------- 
#define WCDMA_InitWCDMACal_BaseItemCode                                    300000
#define WCDMA_Therm_Calibration_BaseItemCode                               300001
#define WCDMA_DoDC_Calibration_BaseItemCode                                300002
#define WCDMA_WCDMATXLin_Calibration_BaseItemCode                          300003
#define WCDMA_WCDMATXRXAlign_Calibration_BaseItemCode                      300004
#define WCDMA_EndWCDMACal_BaseItemCode                                     300099
#define WCDMA_FTMPOWER_BaseItemCode										   300005
//-------------------------------------------------------------------------------------------------
//	3G Test BaseItemCode
//------------------------------------------------------------------------------------------------- 
#define WCDMA_InitWCDMATest_BaseItemCode                                   600000
#define WCDMA_WCDMATestCall_BaseItemCode                                   600001
#define WCDMA_MaxPower_Test_BaseItemCode                                   600002
#define WCDMA_MinPower_Test_BaseItemCode                                   600003
#define WCDMA_EVMRMSAvg_Test_BaseItemCode                                  600004
#define WCDMA_FrequencyError_Test_BaseItemCode                             600005
#define WCDMA_TransTimeError_Test_BaseItemCode                             600006
#define WCDMA_EMASK_Test_BaseItemCode                                      600007
#define WCDMA_OccupiedBandWidth_Test_BaseItemCode                          600010
#define WCDMA_BER_Test_BaseItemCode                                        600011
#define WCDMA_RxLevel_Test_BaseItemCode                                    600012

#define WCDMA_ILPC_E_Test_BaseItemCode                                     600014
#define WCDMA_ILPC_F_Test_BaseItemCode                                     600015

#define WCDMA_ACLR_N10_Test_BaseItemCode                                   600020
#define WCDMA_ACLR_N5_Test_BaseItemCode                                    600021
#define WCDMA_ACLR_P5_Test_BaseItemCode                                    600022
#define WCDMA_ACLR_P10_Test_BaseItemCode                                   600023

#define WCDMA_TxCurrent_Test_BaseItemCode                                  600091
#define WCDMA_SetCableLoss_BaseItemCode                                    600096
#define WCDMA_Call_HandOver_Device_BaseItemCode                            600097
#define WCDMA_Call_HandOver_Phone_BaseItemCode                             600098
#define WCDMA_EndWCDMATest_BaseItemCode                                    600099

//-------------------------------------------------------------------------------------------------
//	WireLess Test BaseItemCode
//------------------------------------------------------------------------------------------------- 
#define WireLess_InitGSMTest_BaseItemCode                               700000
#define WireLess_GSMStartCall_BaseItemCode                              700001

#define WireLess_InitWCDMATest_BaseItemCode                             700050
#define WireLess_WCDMAStartCall_BaseItemCode                            700051

#define WireLess_GSM_MaxPower_Test_BaseItemCode                         700002
#define WireLess_WCDMA_MaxPower_Test_BaseItemCode                       700052

#define WireLess_GSM_RxLevel_Test_BaseItemCode                          700003
#define WireLess_WCDMA_RxLevel_Test_BaseItemCode                        700053

#define WireLess_GSM850_MeasureLoop_Test_BaseItemCode                   700048
#define WireLess_WCDMA850_MeasureLoop_Test_BaseItemCode                 700098

#define WireLess_EndGSMTest_BaseItemCode                                700049
#define WireLess_EndWCDMATest_BaseItemCode                              700099

//-------------------------------------------------------------------------------------------------
//	CDMA Test BaseItemCode
//------------------------------------------------------------------------------------------------- 
#define CDMA_Init_Test_BaseItemCode										 900000
#define CDMA_TestTestCall_BaseItemCode                                  900001
#define CDMA_Init_Device_BaseItemCode									 900002
#define CDMA_Init_Phone_BaseItemCode									 900003
#define CDMA_MaxPower_Test_BaseItemCode                                  900004
#define CDMA_SetCableLoss_BaseItemCode                                   900096
#define CDMA_Call_HandOver_Device_BaseItemCode                           900097
#define CDMA_Call_HandOver_Phone_BaseItemCode                            900098
#define CDMA_CDMATestEnd_BaseItemCode                                    900099



//-------------------------------------------------------------------------------------------------
//	Misc BaseItemCode
//------------------------------------------------------------------------------------------------- 
#define BT_Test_BaseItemCode                                            100001
#define WLAN_Test_BaseItemCode                                          100002
#define FM_Test_BaseItemCode                                            100003
#define GPS_Test_BaseItemCode                                           100004

#define StartPowersupply_BaseItemCode                                   100011
#define StopPowersupply_BaseItemCode                                    100012

#define LeakageCurrent_BaseItemCode                                     100021
#define StandbyCurrent_BaseItemCode                                     100022
#define MobileOnCurrent_BaseItemCode                                    100023
#define LEDCurrent_Test_BaseItemCode                                    100024

#define WritePicasso_BaseItemCode                                       100031
#define ReadPicasso_BaseItemCode                                        100032
#define ComparePiasscoNumber_BaseItemCode                               100033
#define WriteMobileID_BaseItemCode                                      100034
#define ReadMobileID_BaseItemCode                                       100035          
#define WriteSWHWVersion_BaseItemCode                                   100036
#define WriteVersion_BaseItemCode                                       100037
#define CheckVersion_BaseItemCode                                       100038
#define HWSWVersionCheck_BaseItemCode                                   100039
#define Write2GStationInfo_BaseItemCode                                 100040
#define Check2GStationInfo_BaseItemCode                                 100041
#define Write3GStationInfo_BaseItemCode                                 100042
#define Check3GStationInfo_BaseItemCode                                 100043
#define WriteAttenaStationInfo_BaseItemCode                             100044
#define CheckAttenaAtationInfo_BaseItemCode                             100045
#define CheckPicassoMobileID_BaseItemCode                               100046
#define CheckHWID_BaseItemCode											100047
#define CheckPicassoInSMTSys_BaseItemCode                               100048
#define CheckSWVersionMT_BaseItemCode									100049

#define StopCoinCharge_BaseItemCode                                     100061
#define StartCoinCharge_BaseItemCode                                    100062
#define USBChargeStart_BaseItemCode                                     100063
#define USBChargeStop_BaseItemCode                                      100064
#define CoinCellVoltage_BaseItemCode                                    100065
#define BatteryVoltage_BaseItemCode                                     100066
#define BatteryDetectSwitch_BaseItemCode                                100067
#define BatteryTemperature_Test_BaseItemCode                            100068
#define USBIsCharging_BaseItemcode                                      100069
#define USBChargeCurrent_BaseItemcode                                   100070

#define WriteQfuse_BaseItemCode                                         100081
#define CheckQfuse_BaseItemCode                                         100082
#define LeopardCheckQfuse_BaseItemCode									100083
#define LeopardWriteQfuse_BaseItemCode									100084


#define IsPhoneConnected_BaseItemCode                                   100091
#define EnterFTM_BaseItemCode                                           100092
#define EnterOnline_BaseItemCode                                        100093
#define ResetHandSet_BaseItemCode                                       100094
#define SetOnlineMode_BaseItemCode                                      100095
#define EnterPowerOffMode_BaseItemCode                                  100096
#define CheckAndChangeMode_BaseItemCode									100097

#define SimCardExistence_BaseItemCode                                   100101
#define GsernsorEpassid_BaseItemCode                                    100102
#define BoardID_BaseItemCode                                            100103
#define SDCard_Test_BaseItemCode                                        100104
#define LED_Test_BaseItemCode                                           100105
#define GsernsorXYZ_BaseItemCode                                        100106
#define GsernsorOn_BaseItemCode                                         100107
#define GsernsorOff_BaseItemCode                                        100108
#define SetRTC_BaseItemCode                                             100109
#define BackupNV_BaseItemCode                                           100110
#define LeopardGSensorTest_BaseItemCode									100111
#define ECompass_BaseItemCode											100112
#define GaugeICIDTest_BaseItemCode										100113
#define LeopardSDCardSize_BaseItemCode									100114
#define LeopardSDCardStatus_BaseItemCode								100115
#define WriteOneNV_BaseItemCode											100116
#define WriteEFSFile_BaseItemCode										100117


#define RFConnector_BaseItemCode                                        100120 
#define GSensorTestGetID_BaseItemCode                                   100121
#define GSensorTestIDFunc_BaseItemCode                                  100122
#define StartMotoUSB_BaseItemCode                                       100123
#define StopMotoUSB_BaseItemCode                                        100124
#define SaveHOB_BaseItemCode                                            100125
#define TrackID_BaseItemCode                                            100126
#define WriteFlashID_BaseItemCode                                       100127
#define ReadFlashID_BaseItemCode                                        100128
#define CheckFlashID_BaseItemCode                                       100129
#define WriteFactoryInfo2G_BaseItemCode                                 100130
#define CheckFactoryInfo2G_BaseItemCode                                 100131
#define WriteFactoryInfo3G_BaseItemCode                                 100132
#define CheckFactoryInfo3G_BaseItemCode                                 100133
#define CheckFactoryInfoCIT_BaseItemCode                                100134
#define WriteFactoryInfoWireless_BaseItemCode                           100135
#define WritePCBID_BaseItemCode                                         100136
#define CheckPCBID_BaseItemCode                                         100137
#define WriteSMTTime_BaseItemCode                                       100138
#define WriteServiceByte_BaseItemCode                                   100139
#define WriteTransceiverNum_BaseItemCode                                100140
#define ResetProcessInfo_BaseItemCode									100141

#define AudioLoopBackTestStart_BaseItemCode                             100143
#define AudioLoopBackTestStop_BaseItemCode                              100144
#define LEDTestStart_BaseItemCode                                       100145
#define LEDTestStop_BaseItemCode                                        100146
#define GPIOTest_BaseItemCode                                           100147
#define UARTTest_BaseItemCode                                           100148
#define SIMTest_BaseItemCode                                            100149

#define PopUSB_BaseItemCode												100150
#define PushUSB_BaseItemCode                                            100151
#endif