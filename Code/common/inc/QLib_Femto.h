/******************************************************************************/
/**
Program: QMSL

	$Id: //depot/HTE/QDART/QMSL/QLib_Femto.h#6 $

\code

	- Defines the "C" interface for all Factory Library functions.

	- Table of contents (text search can be done for the following sections)

			- Femto Diag and FTM
		
	------------------------------------------------------


	----------------------
	General Information
	----------------------

	- All data types used in this interface are ANSI C compatible.

	- All returns that indicate "true if succeed, false if fail" are defined
		as:  1 = true = Success , 0 = false = failure

		Functions that are not entirely upper case do not correspond directly to
		an FTM or diagnostic command.

		For example, QLIB_ConnectServer() is not mapped directly to a diagnostic
		command.


	- Variable Names
		Variable names are prefixed in lower case to indicate the data type.
		The following are defined:

			p = Pointer
			i = Integer type, either char, short, or long
			d = Double or floating point
			e = Enumeration (possibly stored as a short, but representing
			                 a fixed list of possibilities)
			b = unsigned char, 0=false, 1=true

	----------------------
	Related Documents
	----------------------

	- The function name convention used in this document is as follows:

		QLIB_ indicates that this function corresponds to library function
		in the QLib project.

		From there, all diagnostic and FTM functions are named exactly as
		the command identifiers are defined in the QLib_Defines.h.

	- For a list of all document numbers referred to by QMSL, please see following section in the QDART Help file:
		1) QDART -> QDART Related Documents
	or  2) QDART -> QMSL -> Getting Started -> References.


\endcode


	-----------------------
	Version History
	-----------------------

 \b QUALCOMM  \b PROPRIETARY

	This document contains propriety information, and except with written
	permission of Qualcomm INC, such information shall not be
	published, or disclosed to others, or used for any purpose, and the
	document shall not be duplicated in whole or in part.


	Copyright (c) 2004-2008 QUALCOMM Incorporated.
	All Rights Reserved.
	Qualcomm Confidential and Proprietary

\version
Version information is stored in the file "QMSL_Release_Notes.txt"

\note
Compiler:  Microsoft Visual C++ v6.0 SP4
*******************************************************************************/

#if !defined(_QLIB_FEMTO_H)
#define _QLIB_FEMTO_H

#if !defined(_WINDOWS_)
	#include "windows.h"
#endif

/**
	Establish whether the library is being compiled into a DLL (exporting),
	or being included from a client (importing)

	When the DLL is built, then QLIB_EXPORTS should be defined
*/
#ifdef QLIB_EXPORTS
#define QLIB_API __declspec(dllexport)
#else
#define QLIB_API __declspec(dllimport)
#endif

#if defined(QLIB_STATIC)
#undef QLIB_API
#define QLIB_API
//#define QLIB_API __cdecl
#endif


#ifdef __cplusplus
extern "C" {
#endif


	//test function, do not use
	QLIB_API unsigned char QLIB_Femto_Foo(	HANDLE hResourceContext );


	/******************************************************************************/
	/**

	Connect to a Femto unit. This function returns a Handle which must be used with the rest of the Femto API's

	\param qmslFemtoTransportDllName = The name of the dll that implements the Femto Transport layer. Should be "QMSL_Femto_Transport.dll"
	\param resourceId = The IP address of the Femto unit. i.e. "192.168.10.2"
	\param retryTimeoutSec = How long, in seconds, to retry the connection if it fails at first. Useful if you have reset the unit and need to wait for it to initialize.
	\return HANDLE to use for all subsequent QLIB_FEMTO_* calls that require a handle.
	        If NULL, then there was an error initializing the handle. Call QLIB_FEMTO_GetLastError() to return the error description string.

	*******************************************************************************/
	QLIB_API HANDLE QLIB_FEMTO_ConnectServer( char *qmslFemtoTransportDllName, char *resourceId, int retryTimeoutSec);
	
	/******************************************************************************/
	/**

	This function can be called after QLIB_FEMTO_ConnectServer if a NULL Handle was returned.

	\param resourceId = The resource ID that was used in the call to QLIB_FEMTO_ConnectServer() which failed.

	\return a string that contains the error description, which can be used for troubleshooting.
	*******************************************************************************/
	QLIB_API char* QLIB_FEMTO_GetLastError(char *resourceId);

	/******************************************************************************/
	/**

	This function can be called after any QLIB_FEMTO_* function that got a response.

	\return an integer that was the result code returned in the last response
	*******************************************************************************/
	QLIB_API int QLIB_FEMTO_GetLastResultCode(HANDLE h);

	/******************************************************************************/
	/**

	Read an NV item from RAM. Call QLIB_FEMTO_SET_MODE() and QLIB_FEMTO_FTM_LOAD_NV_PARAMS() first.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param nvId = NV Item ID
	\param data = Buffer to contain the data of the NV item
	\param expectedLen = Expected size (in bytes) of the NV item data to read. The data buffer must be at least this size.
	\return true if successful, false if fail.

	*******************************************************************************/
	QLIB_API unsigned char QLIB_FEMTO_NV_Read(HANDLE h, int nvId, unsigned char *data, int expectedLen) ;

	QLIB_API unsigned char QLIB_FEMTO_NV_Read_Ex(HANDLE h, int nvId, int offset, int length, unsigned char* buf);


	/******************************************************************************/
	/**

	Write an NV item to RAM. Call QLIB_FEMTO_SET_MODE() first.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param nvId = NV Item ID
	\param data = Buffer that contains the data of the NV item
	\param dataLen = Size (in bytes) of the NV item data.
	\return true if successful, false if fail.

	*******************************************************************************/
	QLIB_API unsigned char QLIB_FEMTO_NV_Write(HANDLE h, int nvId, unsigned char *data, int datalen) ;

	QLIB_API unsigned char QLIB_FEMTO_NV_Write_Ex(HANDLE h, int nvId, int offset, int length, unsigned char* buf);


	/******************************************************************************/
	/**

	Write the Rx Gain Calibration NV Item.  Call QLIB_FEMTO_SET_MODE() first.

	This function will be called during Rx Gain Calibration.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param path = 1 : rf path RX_1, 2: rf path RX_2
	\param gain = 0: 30dB gain state, 1: 40dB gain state
	\param numMeas = Number of power measurements taken. This must be set to 32.
	\param power = An array of length 32. Each element is the power level in dBm at which the corresponding rssi measurement was taken.
	\param rssi = An array of length 32. Each element is an rssi measurement.
	\return true if successful, false if fail.

	*******************************************************************************/
	QLIB_API unsigned char QLIB_FEMTO_NV_Write_RxGainCal(HANDLE h, int path, int gain, int numMeas, double *pwr, double *rssi) ;


	/******************************************************************************/
	/**

	Write the Rx Frequency Calibration NV Item.  Call QLIB_FEMTO_SET_MODE() first.

	This function will be called during Rx Frequency Calibration.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param path = 1 : rf path RX_1, 2: rf path RX_2
	\param numMeas = Number of channels at which measurements were taken. 
					 This must be set to 16.
    \param chans = An array of the channel numbers. Each element is a channel number where a measurement was taken.
					The length of the array must be 16 elements
	
	\param rssi_sp30to40 = An array of rssi measurements. Each element is an rssi reading at the corresponding channel.
					The measurements must be taken under the conditions for switchpoint from 30dB gain state to 40dB gain state. 
					For example:
					    * Signal Power at the RF input is -50dBm
						* Rx Gain state is 30dBm
					The length of the array must be 16 elements.
	\param rssi_sp40to30 = An array of rssi measurements. Each element is an rssi reading at the corresponding channel.
					The measurements must be taken under the conditions for switchpoint from 40dB gain state to 30dB gain state. 
					For example:
					    * Signal Power at the RF input is -40dBm
						* Rx Gain state is 40dBm
					The length of the array must be 16 elements.
	
	\param reserved = set to NULL
	\return true if successful, false if fail.

	*******************************************************************************/
	QLIB_API unsigned char QLIB_FEMTO_NV_Write_RxFreqCal(HANDLE h, int path, int numMeas, int *chans, int *rssi_sp30to40, int *rssi_sp40to30, int *reserved) ;

	/******************************************************************************/
	/**

	Write the Tx Gain and Frequency Calibration NV Item.  Call QLIB_FEMTO_SET_MODE() first.

	This function will be called during Tx Gain/Frequency Calibration.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param path = RF path constant as defined in QLIB_FEMTO_TXCAL_INIT
	\param numPowerMeas = Number of Tx gain indexes at which measurements were taken. 
    \param powerMeas = An array of the power measurements taken at each gain index	
	\param numChans = The number of channels over which frequency calibration was done. This must be set to 16
	\param freqMeas = The power measurements taken at each channel. This must be an array of 16 elements.
	
	\param reserved = set to NULL
	\return true if successful, false if fail.

	*******************************************************************************/
	QLIB_API unsigned char QLIB_FEMTO_NV_Write_TxCal(HANDLE h, int path, int numPowerMeas, double *powerMeas, int numChans, int *chans, double *freqMeas, int *reserved) ;
	

	/******************************************************************************/
	/**

	Init Femto for Tx Cal

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param txpath = 1 : rf path TX_0 on FTR8700 #1 
					2 : rf path TX_1 on FTR8700 #1 
					3 : rf path TX_0 on FTR8700 #2 
					4 : rf path TX_1 on FTR8700 #2  
	\param mode = One of the mode constants, defined in QLIB_FEMTO_FTM_SET_MODE 
    \param channel = The channel number to initialize to
	\return true if successful, false if fail.

	*******************************************************************************/
	QLIB_API unsigned char QLIB_FEMTO_TXCAL_INIT(HANDLE h, int txpath, int mode, int channel) ;

	/******************************************************************************/
	/**

	Init Femto for Rx Cal

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param rxpath = 11 : rf path RX_0 on FTR8700 #1 
					12 : rf path RX_1 on FTR8700 #1 
					13 : rf path RX_0 on FTR8700 #2 
					14 : rf path RX_1 on FTR8700 #2 
	\param mode = One of the mode constants, defined in QLIB_FEMTO_FTM_SET_MODE 
    \param channel = The channel number to initialize to. Use the Downlink channel number. The corresponding Uplink channel will be inferred.
	\return true if successful, false if fail.

	*******************************************************************************/
	QLIB_API unsigned char QLIB_FEMTO_RXCAL_INIT(HANDLE h, int rxpath, int mode, int channel) ;

	QLIB_API unsigned char QLIB_FEMTO_TXDVT_INIT(HANDLE h,  int txpath, int mode, int channel, int testId) ;
	QLIB_API unsigned char QLIB_FEMTO_RXDVT_INIT(HANDLE h, int txpath, int rxpath, int mode, int channel, int rate) ;


	//////
	//////
	//////

	
	/******************************************************************************/
	/**

	This function provides software with the value of the current mode (technology, band information, etc.)

	This should be the first function called.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param mode =   513 : UMTS Band 1
					514 : UMTS Band 2
					515 : UMTS Band 5
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_MODE(HANDLE h, int mode);

	//rfcalNvSectRead
	// * Set Mode
	/******************************************************************************/
	/**
	This function loads RF calibration data for a given mode from the flash image in RAM into the current calibration data in RAM. 

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param mode = The same mode value set in QLIB_FEMTO_FTM_SET_MODE()
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_LOAD_NV_PARAMS(HANDLE h, int mode);

	//rfcalNvSectProg
	// * Set Mode
	/******************************************************************************/
	/**

	This function saves the updated RF calibration data in RAM to the flash image in RAM, erases
	flash memory, and writes the flash image in RAM to flash memory. It is only performed in
	calibration test mode.
	Input items will be tagged with the given mode value.
	
	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param mode = The same mode value set in QLIB_FEMTO_FTM_SET_MODE()
    \return true if successful, false if fail.

	*******************************************************************************/
    
    QLIB_API unsigned char QLIB_FEMTO_FTM_COMMIT_NV_PARAMS(HANDLE h, int mode);

	//rfcalRfdrvApilnit
	// *Set Mode
	
    /******************************************************************************/
	/**
	This function initializes the chips in the RF Path. 
	It calls the rfdrvApiInit() function described in the RF ISOD 
	(refer to document 80-F9310-1, FSM9xxx Drivers: RF Interface Specification and Operational Description).

	This function provides software with the value of the current mode (technology, band information, etc.)

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param mode = The same mode value set in QLIB_FEMTO_FTM_SET_MODE()
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_RF_INIT(HANDLE h, int mode);

	// linked to RX_GAIN_STATES (0x1F02)
	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_LOAD_RX_GAIN_STATES(HANDLE h);

	//rfcalSetLoFreq
	// cmd id = 101
	// consolidate to one Set LO Freq?
	// * Set mode
	//
    /******************************************************************************/
	/**

	This function tunes the LO for the given rx path to the given frequency.

	You must call SET_MODE before calling this function.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param rxpath = Rx RF path constant as in QLIB_FEMTO_RXCAL_INIT
	\param channel = the channel number to tune to
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_RX_LO_FREQ(HANDLE h, int rxpath, int channel);

	//rfcalSetRxGainState
	// 0 and 1
	//This function sets the analog gain state on the given Rx path.
    /******************************************************************************/
	/**

	This function provides software with the value of the current mode (technology, band information, etc.)

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param rxpath = Rx RF path constant as in QLIB_FEMTO_RXCAL_INIT
	\param rxgain = 0 : 30dB gain state
					1 : 40 dB gain state
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_RX_GAIN_STATE(HANDLE h, int rxpath, int rxgain);

	//This function is superceded by setup calib/dvt funcs and should not be called
    QLIB_API unsigned char QLIB_FEMTO_FTM_RX_ENABLE_RF_PATH(HANDLE h, int rxpath, int dfechain);


    /******************************************************************************/
	/**

	See rfcalReadDigitalPower in App Note

	This function provides software with the value of the current mode (technology, band information, etc.)

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param dfechain =	11 : DFE_RX0
						12 : DFE_RX1
						13 : DFE_RX2
						14 : DFE_RX3
						15 : DFE_RX4
	\param dpvalue = Output param. Will be populated with the digital power value read from the chip
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_READ_DIGITAL_POWER(HANDLE h, int dfechain, int *dpvalue);


	/******************************************************************************/
	/**

	If modem is running, then will get the estimated rssi from modem.
	Otherwise, will read digital power from chip and do a lookup in the calibration table to return estimated rssi.
    
	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param rxpath = Rx RF path constant as in QLIB_FEMTO_RXCAL_INIT
	\param dfeChain = DFE chain constant as in QLIB_FEMTO_FTM_READ_DIGITAL_POWER
	\param value = output param. Will be populated with the estimated value, in units of dBm
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_GET_ESTIMATED_RX_DBM(HANDLE h, int rxpath, int dfeChain, int *value);


	//
    /******************************************************************************/
	/**
	This function tunes the LO for the given path to the given frequency.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param txpath = Tx RF path constant as in QLIB_FEMTO_TXCAL_INIT
	\param channel = channel number in the band that was set with QLIB_FEMTO_FTM_SET_MODE.
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_TX_LO_FREQ(HANDLE h, int txpath, int channel);

	//rfcalSetTxGainState
	//
    /******************************************************************************/
	/**

	This function sets the gain state on the given Tx path.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param txpath = Tx RF path constant as in QLIB_FEMTO_TXCAL_INIT
	\param txGain = Tx analog gain state. 
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_TX_GAIN_STATE(HANDLE h, int txPath, int txGain);


	
    /******************************************************************************/
	/**

	This function loads a pre-defined waveform into DFE waveform memory and transmits it on the given DFE path.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param waveformId = 0 :  no signal generated = 0
						1 : AWGN waveform (C2K = 1.25 MHz, UMTS = 3.84 MHz)
						2 : CW
	\param dfeChain = Tx DFE chain constant
						1 : DFE_TX0
						2 : DFE_TX1
						3 : DFE_TX2
						4 : DFE_TX3
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_TX_WAVEFORM(HANDLE h, int waveformID, int dfeChain);

	//This function is superceded by setup calib/dvt funcs and should not be called
    QLIB_API unsigned char QLIB_FEMTO_FTM_TX_ENABLE_RF_PATH(HANDLE h, int txpath, int dfechain);


    /******************************************************************************/
	/**

	This function reads the power detector value

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param txpath = One of the Tx RF path constants. Will be used to select which FTR8700 is used.
	\param pdet_in = Select which PDET input is selected to read
						1 : PDET_IN_1, First power detector in FTR8700
						2 : PDET_IN_1, First power detector in FTR8700
	\param hdetVal = will be populated with the power detector value read
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_READ_HDET(HANDLE h, int txpath, int pdet_in, int *hdetVal);

	//rfdrvSetTxPower
	/*
	*/
    /******************************************************************************/
	/**

	See rfdrvSetTxPower, rfdrvSetTxPowers in RF ISOD

	This function sets the transmit powers of a single carrier. 
	This is a wrapper for the rfdrvSetTxPowers( ) function where cid2 is implicitly set to 0, and the power is an integer value.
	The function sets the transmit power by adjusting the analog gain of the FTR8700 path and the Tx digital gain corresponding to the Tx RF path named by txpath. 
	The power level dbmTxPower specifies the desired Tx power at the antenna output assuming that the modem feeding that particular chain is transmitting its reference signal.
	
	This function has different input parameters than the rfdrvSetTxPower function in the RF ISOD.
	This function does not use a CID as input, rather it uses a Tx RF path constant to specifiy the RF path.
	This function has the same effect as rfdrvSetTxPower

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param txpath = Tx RF path constant as in QLIB_FEMTO_TXCAL_INIT
	\param dbmTxPower = the target power level, units of dBm
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_TX_POWER(HANDLE h, int txpath, int dbmTxPower);

	//Used in C2K but not UMTS.
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_TX_POWER_MULTICARRIER(HANDLE h, int cid1, int pwr1_dbmTimes1000, int cid2, int pwr2_dbmTimes1000);

	// 
    /******************************************************************************/
	/**

	Set the NCO value of on the given dfeChain

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param dfeChain = One of the Tx or Rx DFE chain constants
						1 : DFE_TX0
						2 : DFE_TX1
						3 : DFE_TX2
						4 : DFE_TX3
						11 : DFE_RX0
						12 : DFE_RX1
						13 : DFE_RX2
						14 : DFE_RX3
						15 : DFE_RX4
	\param hzOffset = The value of the NCO offset to set, in units of Hz
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_NCO(HANDLE h, int dfeChain, int hzOffset);

	/* 
	
	*/
    /******************************************************************************/
	/**

	This function reads the value of the given thermistor

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param thermistorId = One of the thermistor constants:
	\code
	Value         Function                   Source
	0             pmicThermPARead()          External thermistor, intended to be placed near the PA
	1-2           getInternalHdetTemp()      temp sensor in FTR8700 #1 PDET block
	3-4           getInternalHdetTemp()      temp sensor in FTR8700 #2 PDET block
	11-12         getInternalAdcTemp()       temp sensor in FTR8700 #1 HKADC block
	13-14         getInternalAdcTemp()       temp sensor in FTR8700 #2 HKADC block
	\endcode
	\param adcValue = will be populated with the value read
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_GET_THERM_ADC(HANDLE h, int thermistorId, int *adcValue);

	/******************************************************************************/
	/**
	See rfdrvGrfcInit, grfcSet functions in RF ISOD
	
	This function turns GPIO pins on or off

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param regCtl = Selects a GPIO group that has been defined previously. (See rfdrvGrfcInit() function in RF ISOD)
						2: RFCAL_GPIO_GROUP_A
						3: RFCAL_GPIO_GROUP_B
						4: RFCAL_GPIO_GROUP_C
	\param valueMask = values to set on the active pins
	\param enableMask = mask that specifies the active pins
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_WRITE_GPIO(HANDLE h, int regCtl, int valueMask, int enableMask);

	//
    /******************************************************************************/
	/**

	See rfcalSetDigitalGain in App Note

	This function sets the digital gain for the DFE section of the RF path.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param dfeTxChain = One of the Tx DFE chain constants
						1 : DFE_TX0
						2 : DFE_TX1
						3 : DFE_TX2
						4 : DFE_TX3
	\param gainValue = digital gain value, 0x0000 � 0x7fff
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_SET_DIGITAL_GAIN(HANDLE h, int dfeTxChain, int gainValue);

    // Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_SET_DFE_IQ(HANDLE h, int dfeChain, int igain, int qgain, int icrossgain, int qcrossgain);

	//
    /******************************************************************************/
	/**

	See CalibrateRxIQImbalance in App Note

	This function:
		- Runs the algorithm for Rx I/Q imbalance table generation
		- Using a loopback feature, determines the DFE coefficients required to compensate for the amplitude and the phase imbalance in the Rx path
		- Updates RAM

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param rxRfic = Rx RF path constant
		\code
			FTR1#1,Rx Path # 1 = 11
			FTR1#1,Rx Path # 2 = 12
			FTR1#2,Rx Path # 1 = 13
			FTR1#2,Rx Path # 2 = 14
		\endcode
	\param gain = Gain State. 0,1,2
	\param band = band constant
		\code
		Values for Femtocell C2K band class supported:
			BC_0 = 0
			BC_1 = 1
			BC_3 = 3
			BC_4 = 4
			BC_6 = 6
			BC_10 = 10
			BC_14 = 14
			BC_15 = 15
		Values for Femtocell UMTS band supported:
			B_I = 1
			B_II = 2
			B_III = 3
			B_IV = 4
			B_V = 5
			B_VI = 6
			B_VIII = 8
			B_IX = 9
			B_X = 10
			B_XI = 11
		\endcode

	\param channel = Active channel in the given band
	\param channelOffsetHz = Offset in Hz
	\param iGain = output param. Contains the result of calibration.
	\param qGain = output param. Contains the result of calibration.
	\param iCGain = output param. Contains the result of calibration.
	\param qCGain = output param. Contains the result of calibration.
	\param preDbc = output param. Contains the estimated original interference in units of dbc
	\param postDbc = output param. Contains the estimated interference after calibration in units of dbc
	\return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SELF_CAL_RX_IQ_IMB(HANDLE h, int rxRfic, int gain, int band, int channel, int channelOffsetHz, int *iGain, int *qGain, int *iCGain, int *qCGain, int *preDbc, int *postDbc);

    /******************************************************************************/
	/**

	See CalibrateTxIQImbalance in App Note

	This function:
		- Runs the algorithm for Tx I/Q imbalance table generation
		- Using a loopback feature, determines the DFE coefficients required to compensate for the amplitude and the phase imbalance in the Rx path
		- Updates RAM

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param txRfic = Tx RF path constant
		\code
			FTR #1, Tx Path #1 = 1
			FTR #1, Tx Path #2 = 2
			FTR #2, Tx Path #1 = 3
		\endcode
	\param TxGainIndex = The Tx Gain Index, sets the power level
	\param band = band constant
		\code
		Values for Femtocell C2K band class supported:
			BC_0 = 0
			BC_1 = 1
			BC_3 = 3
			BC_4 = 4
			BC_6 = 6
			BC_10 = 10
			BC_14 = 14
			BC_15 = 15
		Values for Femtocell UMTS band supported:
			B_I = 1
			B_II = 2
			B_III = 3
			B_IV = 4
			B_V = 5
			B_VI = 6
			B_VIII = 8
			B_IX = 9
			B_X = 10
			B_XI = 11
		\endcode

	\param channel = Active channel in the given band
	\param channelOffsetHz = Offset in Hz
	\param iGain = output param. Contains the result of calibration.
	\param qGain = output param. Contains the result of calibration.
	\param iCGain = output param. Contains the result of calibration.
	\param qCGain = output param. Contains the result of calibration.
	\param preDbc = output param. Contains the estimated original interference in units of dbc
	\param postDbc = output param. Contains the estimated interference after calibration in units of dbc
	\return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SELF_CAL_TX_IQ_IMB(HANDLE h, int path, int TxGainIndex, int band, int channel, int channelOffsetHz, int *iGain, int *qGain, int *iCGain, int *qCGain, int *preDbc, int *postDbc);


	/******************************************************************************/
	/**

	See CalibrateRxDcocCoarse in App Note

	This function:
		- Readjusts the amplifier/mixer bias voltage in the FTR8700 Rx analog path so as to minimize the DC offset
		- Runs the algorithm for Rx DCOC table generation
		- Updates the Rx DCOC in RAM, for the given rxRfic and rxGain settings
	The function should be invoked one time for each Rx path, Rx specified channel and Rx gain combination.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param rxRfic = Rx RF path constant
		\code
			FTR1#1,Rx Path # 1 = 11
			FTR1#1,Rx Path # 2 = 12
			FTR1#2,Rx Path # 1 = 13
			FTR1#2,Rx Path # 2 = 14
		\endcode
	\param gain = Gain State. 0,1,2
	\param band = band constant
		\code
		Values for Femtocell C2K band class supported:
			BC_0 = 0
			BC_1 = 1
			BC_3 = 3
			BC_4 = 4
			BC_6 = 6
			BC_10 = 10
			BC_14 = 14
			BC_15 = 15
		Values for Femtocell UMTS band supported:
			B_I = 1
			B_II = 2
			B_III = 3
			B_IV = 4
			B_V = 5
			B_VI = 6
			B_VIII = 8
			B_IX = 9
			B_X = 10
			B_XI = 11
		\endcode

	\param channel = Active channel in the given band
	\param reserved = Unused input param. Set to 0.
	\param trimI = output param. Contains the result of calibration.
	\param trimQ = output param. Contains the result of calibration.
	\param null3 = output param. Will be set to 0. This value can be ignored.
	\param null4 = output param. Will be set to 0. This value can be ignored.
	\param null5 = output param. Will be set to 0. This value can be ignored.
	\param null6 = output param. Will be set to 0. This value can be ignored.
	\return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SELF_CAL_RX_DCOC(HANDLE h, int path, int gain, int band, int channel, int reserved, int *trimI, int *trimQ, int *null3, int *null4, int *null5, int *null6);

    /******************************************************************************/
	/**

	See CalibrateTxDcocCoarse in App Note

	This function:
		- Readjusts the amplifier/mixer bias voltages in the FTR8700 Tx analog path so as to minimize the DC offset
		- Runs the algorithm for Tx DCOC table generation
		- Updates the Tx DCOC in RAM, for the given txRfic and txGain settings
	The function should be invoked one time for each Tx path, Tx specified channel and Tx gain combination.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param rxRfic = Rx RF path constant
		\code
			FTR #1, Tx Path #1 = 1
			FTR #1, Tx Path #2 = 2
			FTR #2, Tx Path #1 = 3
		\endcode
	\param TxGainIndex = The Tx Gain Index, sets the power level
	\param band = band constant
		\code
		Values for Femtocell C2K band class supported:
			BC_0 = 0
			BC_1 = 1
			BC_3 = 3
			BC_4 = 4
			BC_6 = 6
			BC_10 = 10
			BC_14 = 14
			BC_15 = 15
		Values for Femtocell UMTS band supported:
			B_I = 1
			B_II = 2
			B_III = 3
			B_IV = 4
			B_V = 5
			B_VI = 6
			B_VIII = 8
			B_IX = 9
			B_X = 10
			B_XI = 11
		\endcode

	\param channel = Active channel in the given band
	\param reserved = Unused input param. Set to 0.
	\param trimIPlus = output param. Contains the result of calibration.
	\param trimIMinus = output param. Contains the result of calibration.
	\param trimQPlus = output param. Contains the result of calibration.
	\param trimQMinus = output param. Contains the result of calibration.
	\param null5 = output param. Will be set to 0. This value can be ignored.
	\param null6 = output param. Will be set to 0. This value can be ignored.
	\return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_SELF_CAL_TX_DCOC(HANDLE h, int path, int TxGainIndex, int band, int channel, int reserved, int *trimIPlus, int *trimIMinus, int *trimQPlus, int *trimQMinus, int *null5, int *null6);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_SELF_CAL_RX_MIXER_IM2(HANDLE h, int path, int rxGainState, int band, int channel, int channelOffsetHz, int *val1, int *val2, int *val3, int *val4, int *val5, int *val6);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RF_CAL_GET_RX_DBC(HANDLE h, int path, int rxGainState, int band, int channel, int channelOffsetHz, int *postDbc);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RF_CAL_GET_TX_DBC(HANDLE h, int path, int txGaindBm, int band, int channel, int channelOffsetHz, int *postdBc);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RF_CAL_SET_RX_DCOC(HANDLE h, int path, int iTrim, int qTrim);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RF_CAL_GET_DCOC_I(HANDLE h, int path, int band, int *iData);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RF_CAL_GET_DCOC_Q(HANDLE h, int path, int band, int *qData);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_GET_SELF_CAL_RX_IQ_IMB (HANDLE h, int path, int rxGainState, int band, int channel, int channelOffsetHz, int *iGain, int *qGain, int *iCGain, int *qCGain, int *val5, int *val6);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_GET_SELF_CAL_TX_IQ_IMB (HANDLE h, int path, int txGaindBm, int band, int channel, int channelOffsetHz, int *iGain, int *qGain, int *iCGain, int *qCGain, int *val5, int *val6);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_ERASE_FLASH(HANDLE h);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_ERASE_CALIBRATION_RAM(HANDLE h);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_SET_RSSI_DURATION(HANDLE h, int dfeRxChain, int duration);

    /******************************************************************************/
	/**

	See rfcalSetInterruptMask in App Note

	Set the mask for the interrupt register on the processor. 
	This can be used to enable or disable jammer control if it has been provisioned.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param mask = 0: Disable Jammer Detect, 1: Enable Jammer Detect
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_SET_INTERRUPT_MASK(HANDLE h, int mask);

	// 
    /******************************************************************************/
	/**

	This function turn Rx automatic gain control (AGC) on or off

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param rxpath = Rx path constant
	\param value = 0: AGC off, 1: AGC on
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_ENABLE_PATH(HANDLE h, int path, int value);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_ENABLE_CHAIN(HANDLE h, int path, int dfeChain, int value);

	// Not recommended for use other than internal testing
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_RESET_FSM_HW(HANDLE h);

	// Used for C2K only
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_1X_ARM_FOR_PP2S(HANDLE h);

    // Used for C2K only
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_1X_START_SECTOR(HANDLE h, int band, int channel, int sectorGain, int sectorChanMask);

    // Used for C2K only
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_1X_CONFIG_CHANS(HANDLE h, int numFwrdChans, int fwrdChanPwr, int needReverse);

    // Used for C2K only
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_1X_GET_CHAN_FER(HANDLE h, int *totBad, int *totFrames);

    // Used for C2K only
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_1X_STOP_SECTOR(HANDLE h);

    // Used for C2K only
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_EVDO_GET_PER(HANDLE h, int *totBad, int *totFrames);

	//Serval
    QLIB_API unsigned char QLIB_FEMTO_FTM_SET_SWITCH_POSITION(HANDLE h, int switchNum, int position);

    /******************************************************************************/
	/**

	This functions arms the PP2S trigger for realignment

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_ARM_FOR_PP2S(HANDLE h);

	/******************************************************************************/
	/**

	This function disarms the PP2S trigger

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_ALIGN_OFF_PP2S(HANDLE h); 

	
	//doDiversity, gain, see mps_tx_test.out
    /******************************************************************************/
	/**

	See the mps_tx_test.out utility

	This function runs the mps_tx_test.out utility to set up the Tx modem signal

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param reserved1 = set to 0
	\param reserved2 = set to 0
	\param testId = test ID as provided by mps_tx_test.out utility
		\code
		Value			Meaning
			1			1a: MPS Test Model 1, 4 DPCHs
			2	        1b: MPS Test Model 1, 8 DPCHs						
			3	         2: MPS Test Model 2
			4	     2dynp: MPS Test Model 2, power control dynamic range step 4)
			5	        3a: MPS Test Model 3, 4 DPCHs
			6	        3b: MPS Test Model 3, 8 DPCHs
			7	         4: MPS Test Model 4
			8	        5a: MPS Test Model 5, 2 HS-PDSCH 6 DPCHs
			9	        5b: MPS Test Model 5, 4 HS-PDSCH 4 DPCHs
			10	        5c: MPS Test Model 5, 4 HS-PDSCH 14 DPCHs
			11	         6: MPS Test Model 6, 4 HS-PDSCH 4 DPCHs
			12			1c: MPS Test Model 1, 16 DPCHs
			13	        3c: MPS Test Model 3, 16 DPCHs
		\endcode
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_START_TX(HANDLE h, int reserved1, int reserved2, int testId);

	//see mps_rx_test.out
    /******************************************************************************/
	/**

	This function runs the mps_rx_test.out utility for use in getting BER statistics

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param reserved1 = set to 0
	\param reserved2 = set to 0
	\param reserved3 = set to 0
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_START_RX(HANDLE h, int reserved1, int reserved2, int reserved3);

    /******************************************************************************/
	/**

	This function stops the Tx or Rx channels set up by QLIB_FEMTO_FTM_DVT_UMTS_START_RX or QLIB_FEMTO_FTM_DVT_UMTS_START_TX

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param stopFwrdChan = 1 to stop the Tx channel, 0 otherwise
	\param stopRvseChan = 1 to stop the Rx channel, 0 otherwise
    \return true if successful, false if fail.
	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_STOP_CHANS(HANDLE h, int stopFwrdChan, int stopRvseChan);

    /******************************************************************************/
	/**

	This function returns the BER statistics. Call QLIB_FEMTO_FTM_DVT_UMTS_START_RX first.

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param totBadBits = output param. total number of bit errors
	\param totBits = output param. total number of bits
    \return true if successful, false if fail.
	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_GET_CHAN_BER(HANDLE h, int *totBadBits, int *totBits);


	// perry
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_ACQUIRE_PILOT(HANDLE h, int rfCard, int freqBand, int channel, int psc);

	/* WCDMA init */

    /******************************************************************************/
	/**

	This function provisions the Tx RF for calibration. Use QLIB_FEMTO_TXCAL_INIT instead.
	
	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param loChannel = channel number in the band to set the LO to
	\param channel = channel number in the band to set the RF signal to 
	\param bandClass = Band class constant as in QLIB_FEMTO_FTM_SELF_CAL_TX_IQ_IMB
	\param hhChain = 0 (TX#0), 1 (TX#1), 2 (TX#2), 3 (TX#3)
	\param dac     = 0 (FTR#0 TX#0), 1  (FTR#0 TX#1), 2 (FTR#1 TX#0)
    \return true if successful, false if fail.
	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_SETUP_CALIB_TX(HANDLE h, int bandClass, int loChannel, int channel, int hhChain, int dac);

	/******************************************************************************/
	/**

	This function provisions the Rx RF for calibration. Use QLIB_FEMTO_RXCAL_INIT instead.
	
	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param loChannel = channel number in the band to set the LO to. Use the Downlink channel number. The corresponding Uplink channel will be inferred.
	\param channel = channel number in the band to set the RF signal to. Use the Downlink channel number. The corresponding Uplink channel will be inferred.
	\param bandClass = Band class constant as in QLIB_FEMTO_FTM_SELF_CAL_TX_IQ_IMB
	\param hhChain = 0 (RX#0),       1  (RX#1),       2 (RX#2),       3 (RX#3)
	\param adc     = 0 (FTR#0 RX#0), 1  (FTR#0 RX#1), 2 (FTR#1 RX#0), 3 (FTR#1 RX#1)
    \return true if successful, false if fail.
	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_SETUP_CALIB_RX(HANDLE h, int bandClass, int loChannel, int channel, int hhChain, int adc);


	/******************************************************************************/
	/**

	This function provisions the Tx and Rx RF for DVT.
	
	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
	\param loChannel = channel number in the band to set the LO to. Use the Downlink channel number.
	\param channel = channel number in the band to set the RF signal to. Use the Downlink channel number.
	\param bandClass = Band class constant as in QLIB_FEMTO_FTM_SELF_CAL_TX_IQ_IMB
	\param hhChain = 0 (TX#0/RX#0),  1  (TX#1/RX#1),  2 (TX#2/RX#2),  3 (TX#3/RX#3)
	\param dac     = 0 (FTR#0 TX#0), 1  (FTR#0 TX#1), 2 (FTR#1 TX#0)
	\param adc     = 0 (FTR#0 RX#0), 1  (FTR#0 RX#1), 2 (FTR#1 RX#0), 3 (FTR#1 RX#1)
    \return true if successful, false if fail.
	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_RFCAL_SETUP_DVT(HANDLE h, int bandClass, int loChannel, int channel, int hhChain, int dac, int adc);

	/*************/



    /******************************************************************************/
	/**

	This function resets the BER counters that are returned during QLIB_FEMTO_FTM_DVT_UMTS_GET_CHAN_BER

	Call this function when you change the scenario and want to recalculate BER

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
    \return true if successful, false if fail.

	*******************************************************************************/
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_RESET_CNTRS(HANDLE h);

	//Not used
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_SW_ANTENNAS(HANDLE h, int card, int freqMhz);

	//Not used
    QLIB_API unsigned char QLIB_FEMTO_FTM_DVT_UMTS_PWR_AMPS(HANDLE h, int mask);

	QLIB_API unsigned char QLIB_FEMTO_FTM_WRITE_HW_REGISTER(HANDLE _h, int chipType, int chipNumber, int block, int address, int value);
    
	QLIB_API unsigned char QLIB_FEMTO_FTM_READ_HW_REGISTER(HANDLE _h, int chipType, int chipNumber, int block, int address, int *value);


	typedef enum {
		FEMTO_CALPROC_DEFAULT = 0,
		FEMTO_CALPROC_v1,
		FEMTO_CALPROC_v2,
		FEMTO_CALPROC_REAC_RX,
		FEMTO_CALPROC_REAC_TX,
		FEMTO_CALPROC_SELF_TX_DCOC,
		FEMTO_CALPROC_SELF_RX_DCOC

	} FemtoCalProcedureId;

	typedef enum {
		FEMTO_MODE_WCDMA_B1 = 513,
		FEMTO_MODE_WCDMA_B2 = 514,
		FEMTO_MODE_WCDMA_B5 = 515,
		FEMTO_MODE_WCDMA_B4 = 517,

	} FemtoModeConstant;

	typedef struct {
		int mode;
		int channelList[16];
		int channelListSize;
		double powerLev40[32];
		int powerLev40Size;
		double powerLev30[32];
		int powerLev30Size;
		double sp_30to40_dbm;
		double sp_40to30_dbm;

		void ( *teFunc_DL_Init ) (); 
		void ( *teFunc_DL_SetChannel ) (); 
		void ( *teFunc_DL_MeasurePower ) (); 

	} FemtoCalProcedure_v1_Params;


	typedef enum {
		FEMTO_TE_ACTION_UL_SET_POWER,
		FEMTO_TE_ACTION_UL_SET_FREQ,
		FEMTO_TE_ACTION_DL_SET_FREQ,
		FEMTO_TE_ACTION_DL_SET_EXP_POWER,
		FEMTO_TE_ACTION_DL_MEAS_POWER
	} Femto_Type_TE_Action;

	typedef void ( *Femto_Func_TE_Action ) (Femto_Type_TE_Action type, void *params);

	typedef enum {
		FEMTO_LOGTYPE_TXCAL_GAIN,
		FEMTO_LOGTYPE_TXCAL_FREQ,
		FEMTO_LOGTYPE_RXCAL_GAIN,
		FEMTO_LOGTYPE_RXCAL_FREQ,
		FEMTO_LOGTYPE_SELFCAL_TXDCOC,
		FEMTO_LOGTYPE_SELFCAL_RXDCOC
	} Femto_LogType;

	typedef void ( *Femto_Func_Log ) (Femto_LogType type, void *params);

	typedef struct {
		int nvpath;
		int mode;
		int channel;
		int gainIndex;
		double power;
		int hdet;
	} Femto_LogType_TxCal;

	typedef struct {
		int nvpath;
		int mode;
		int channel;
		int rxgain;
		double power;
		int rssi;
	} Femto_LogType_RxCal;


	typedef struct {
		int mode;
		int *channelList;
		int channelListSize;
		double* powerLev40;
		int powerLev40Size;
		double* powerLev30;
		int powerLev30Size;
		int numRssiMeas;

		double sp_30to40_dbm;
		double sp_40to30_dbm;

		Femto_Func_TE_Action teFunc;
		Femto_Func_Log logFunc;

	} FemtoCalProcedure_REAC_Rx_Params;

	typedef struct {
		int mode;
		int *channelList;
		int channelListSize;
		int numGainStates;
		int gainIndexToSweep;
		double expectedFirstPowerLevel;
		double expectedGainSweepAvgPowerLevel;

		Femto_Func_TE_Action teFunc;
		Femto_Func_Log logFunc;

	} FemtoCalProcedure_REAC_Tx_Params;

	
	typedef struct {
		int mode;
		int *nvpathList;
		int nvpathListSize;
		int *channelList;
		int channelListSize;
		int *rxGainList;
		int rxGainListSize;
		
		Femto_Func_Log logFunc;

	} FemtoCalProcedure_Self_RxDcoc_Params;

	typedef struct {
		int mode;
		int *nvpathList;
		int nvpathListSize;
		int *channelList;
		int channelListSize;
		int *txGainList;
		int txGainListSize;
		
		Femto_Func_Log logFunc;

	} FemtoCalProcedure_Self_TxDcoc_Params;


	/******************************************************************************/
	/**

	This function runs one of the defined calibration routines

	\param h = Resource context handle that was returned from the call to QLIB_FEMTO_ConnectServer()
    \return true if successful, false if fail.

	*******************************************************************************/
	QLIB_API unsigned char QLIB_FEMTO_DoCalProcedure(HANDLE _h, int calProc, void *calProcParams);
	

	//////
	//////
	//////



#ifdef __cplusplus
}	// extern "C"
#endif


#endif	// defined(_QLIB_H)
