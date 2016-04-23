
#ifndef __RF_NF_ITEM_H
#define __RF_NF_ITEM_H


#include "inc\commoninclude.h"

#include "inc\ILogger.h"
#include "IPhone.h"




#define NV_WCDMA_FREQ_TABLE_SIZ			16
#define NV_WCDMA_EXP_HDET_VS_AGC_SIZ	16
#define NV_WCDMA_NUM_TX_LINEARIZERS		4
#define ADC_PA_POWER_DETECT				4
#define NV_WCDMA_TX_LIN_MASTER_SIZ		32
#define MAX_WCDMA_TX_AGC_PDM			255	//for RTR6285
#define MIN_WCDMA_TX_AGC_PDM			0 //for RTR6285
#define MIN_WCDMA_TX_POWER				-57 //for RTR6285
#define MIN_WCDMA_TX_POWER_6270			-57.3 //for QSC6270
#define MIN_WCDMA_TX_POWER_8615         -70   //for QTR8615

#define DYNAMIC_RANGE					85.3 //For TX range
#define DYNAMIC_RANGE_8615              102.3 //For QTR8615 TX Range

#define MAX_WCDMA_TX_AGC_PDM_8615		127	//for QTR8615
#define MIN_WCDMA_TX_AGC_PDM_8615   	0   //for QTR8615

#define WCDMA_TX_LIN_R2R3_MASTER_SIZ    80

#define NV_CDMA_FREQ_TABLE_SIZ			16
#define NV_CDMA_COMP_TABLE_SIZ			32
#define NV_CDMA_LIM_FREQ_TABLE_SIZ		16
#define NV_CDMA_EXP_HDET_VS_AGC_SIZ		16
#define NV_CDMA_TX_LIN_MASTER_SIZ		64

/* AMAM Master Table Size */
#define RF_AMAM_MASTER_TBL_SIZ 512 

/* AMPM Master Table Size */
#define RF_AMPM_MASTER_TBL_SIZ 256 
#define NV_DCS_CAL_ARFCN_SIZ   16


typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef signed __int64      INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned __int64    UINT64, *PUINT64;



class CRFNVItems : public CRFObject
{
RF_DECLARE_DYNCREATE(CRFNVItems)
public:
CRFNVItems();
~CRFNVItems(){}
virtual bool Handle(){return true;}
virtual bool InitData(	PCStringStrMap     pcSettingMap,CRFObjectMap&   cObjectMap){return true;}
virtual bool InitData(){return true;}
virtual void TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg);
inline static void SetLogger(PILogger piLogger){m_piLogger = piLogger;}

static PILogger		m_piLogger;
void inline SetPhonePtr(PIPhone pcPhone){m_pcPhone = pcPhone;}

protected:
	virtual bool DoProcess(){return true;}

public:
	void InitVariable();
	void InitCDMAVariable();
	void InitRX_Intelliceiver_Variable();

	virtual bool Write_NV_WCDMA_RX(int iBandID);
	bool Write_NV_WCDMA_RX_Diversity(int iBandID);
	virtual bool Write_NV_WCDMA_TX(int iBandID);
	bool Write_NV_WCDMA_IM2(int iBandID);
	bool Write_NV_WCDMA_IM2_Diversity(int iBandID);

	bool Write_NV_GSM_RX(int iBandID);
	bool Write_NV_GSM_TX(int iBandID);
	bool Write_NV_GSM_TX_V2(IntVtr vChannel,int iBandID);
	bool Write_NV_GSM_KVCO(int iBandID);
	bool Write_NV_GSM_PADAC_Search();

	virtual bool Write_NV_CDMA_RX(int iBandID);
	virtual bool Write_NV_CDMA_RX_Diversity(int iBandID);
	virtual bool Write_NV_CDMA_TX(int iBandID);
	virtual bool Write_NV_CDMA_RXIntelliceiver(int iBandID);


protected:
	//WCDMA IM2
	bool Write_NV_WCDMA_IM2_I_VALUE_I(int iBandID);
	bool Write_NV_WCDMA_IM2_Q_VALUE_I(int iBandID);				
	bool Write_NV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(int iBandID);
	//WCDMA RX
	bool Write_NV_WCDMA_VGA_GAIN_OFFSET_I(int iBandID);
	bool Write_NV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(int iBandID);
	bool Write_NV_WCDMA_LNA_OFFSET_I(int iBandID);
	bool Write_NV_WCDMA_LNA_OFFSET_2_I(int iBandID);
	bool Write_NV_WCDMA_LNA_OFFSET_3_I(int iBandID);
	bool Write_NV_WCDMA_LNA_OFFSET_4_I(int iBandID); 
	bool Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_I(int iBandID);
	bool Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_2_I(int iBandID);
	bool Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_3_I(int iBandID);
	bool Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_4_I(int iBandID); 
	//WCDMA TX
	bool Write_NV_WCDMA_TX_LIN_MASTER_0_I(int iBandID);
	virtual bool Write_NV_WCDMA_TX_LIN_MASTER_0_ENH_I(int iBandID){return false;};
	bool Write_NV_WCDMA_TX_LIN_MASTER_1_I(int iBandID);
	bool Write_NV_WCDMA_TX_LIN_MASTER_2_I(int iBandID);
	bool Write_NV_WCDMA_TX_LIN_MASTER_3_I(int iBandID);
	bool Write_NV_WCDMA_TX_PDM_0_I(int iBandID);
	virtual bool Write_NV_WCDMA_TX_PDM_0_ENH_I(int iBandID){return false;};
	bool Write_NV_WCDMA_TX_PDM_1_I(int iBandID);
	bool Write_NV_WCDMA_TX_PDM_2_I(int iBandID);
	bool Write_NV_WCDMA_TX_PDM_3_I(int iBandID);
	bool Write_NV_WCDMA_TX_COMP_VS_FREQ_0_I(int iBandID);
	bool Write_NV_WCDMA_TX_COMP_VS_FREQ_1_I(int iBandID);
	bool Write_NV_WCDMA_TX_COMP_VS_FREQ_2_I(int iBandID);
	bool Write_NV_WCDMA_TX_COMP_VS_FREQ_3_I(int iBandID);
	bool Write_NV_WCDMA_LIM_VS_FREQ_I(int iBandID);
	bool Write_NV_WCDMA_EXP_HDET_VS_AGC_I(int iBandID);
	virtual bool Write_NV_WCDMA_EXP_HDET_VS_AGC_V2_I(int iBandID){return false;};
	bool Write_NV_WCDMA_HDET_OFF_I(int iBandID);
	virtual bool Write_NV_WCDMA_HDET_OFF_V2_I(int iBandID){return false;};
	bool Write_NV_WCDMA_HDET_SPN_I(int iBandID);
	virtual bool Write_NV_WCDMA_HDET_SPN_V2_I(int iBandID){return false;};
	bool Write_Nv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I(int iBandID);
	//WCDMA RX Diversity
	bool Write_NV_C1_WCDMA_VGA_GAIN_OFFSET_I(int iBandID);
	bool Write_NV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(int iBandID);
	bool Write_NV_C1_WCDMA_LNA_OFFSET_I(int iBandID);
	bool Write_NV_C1_WCDMA_LNA_OFFSET_2_I(int iBandID);
	bool Write_NV_C1_WCDMA_LNA_OFFSET_3_I(int iBandID);
	bool Write_NV_C1_WCDMA_LNA_OFFSET_4_I(int iBandID);
	bool Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I(int iBandID);
	bool Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I(int iBandID);
	bool Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I(int iBandID);
	bool Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I(int iBandID);
	bool Write_NV_C1_WCDMA_IM2_I_VALUE_I(int iBandID);
	bool Write_NV_C1_WCDMA_IM2_Q_VALUE_I(int iBandID);				
	bool Write_NV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(int iBandID);
	//GSM RX
	bool  Write_RX_GAIN_RANGE_1_FREQ_COMP_I(int iBandID);
	bool  Write_RX_GAIN_RANGE_2_FREQ_COMP_I(int iBandID);
	bool  Write_RX_GAIN_RANGE_3_FREQ_COMP_I(int iBandID);
	bool  Write_RX_GAIN_RANGE_4_FREQ_COMP_I(int iBandID);
	bool  Write_RX_GAIN_RANGE_5_FREQ_COMP_I(int iBandID);
	//GSM TX
	bool Write_NV_GSM_AMAM_MASTER_TBL_F1(int iBandID); 
	bool Write_NV_GSM_AMAM_MASTER_TBL_F2(int iBandID); 
	bool Write_NV_GSM_AMAM_MASTER_TBL_F3(int iBandID);
	bool Write_NV_GSM_AMPM_MASTER_TBL_F2(int iBandID); 
	bool Write_NV_GSM_AMPM_MASTER_TBL_F1(int iBandID); 
	bool Write_NV_GSM_AMPM_MASTER_TBL_F3(int iBandID);
	//GSM PA_DAC_Search
	bool Write_NV_VCO_DEFAULT_I();
	bool Write_NV_VCO_SLOPE_I();
	/******************CDMA Write NV Items Operation*********************/

	//CDMA TX
	bool Write_NV_CDMA_TX_LIN_MASTER_0_I(int iBandID);
	bool Write_NV_CDMA_TX_LIN_MASTER_1_I(int iBandID);
	bool Write_NV_CDMA_TX_LIN_MASTER_2_I(int iBandID);
	bool Write_NV_CDMA_TX_LIN_MASTER_3_I(int iBandID);
	bool Write_NV_CDMA_TX_PDM_0_I(int iBandID);
	bool Write_NV_CDMA_TX_PDM_1_I(int iBandID);
	bool Write_NV_CDMA_TX_PDM_2_I(int iBandID);
	bool Write_NV_CDMA_TX_PDM_3_I(int iBandID);
	bool Write_NV_CDMA_TX_COMP_VS_FREQ_0_I(int iBandID);
	bool Write_NV_CDMA_TX_COMP_VS_FREQ_1_I(int iBandID);
	bool Write_NV_CDMA_TX_COMP_VS_FREQ_2_I(int iBandID);
	bool Write_NV_CDMA_TX_COMP_VS_FREQ_3_I(int iBandID);
	bool Write_NV_CDMA_LIM_VS_FREQ_I(int iBandID);
	bool Write_NV_CDMA_EXP_HDET_VS_AGC_I(int iBandID);
	bool Write_NV_CDMA_HDET_OFF_I(int iBandID);
	bool Write_NV_CDMA_HDET_SPN_I(int iBandID);
	bool Write_NV_CDMA_TX_CAL_CHAN_I(int iBandID);
	//CDMA RX
	bool Write_NV_CDMA_VGA_GAIN_OFFSET_I(int iBandID);
	bool Write_NV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(int iBandID);
	bool Write_NV_CDMA_LNA_OFFSET_I(int iBandID);
	bool Write_NV_CDMA_LNA_OFFSET_2_I(int iBandID);
	bool Write_NV_CDMA_LNA_OFFSET_3_I(int iBandID);
	bool Write_NV_CDMA_LNA_OFFSET_4_I(int iBandID); 
	bool Write_NV_CDMA_LNA_OFFSET_VS_FREQ_I(int iBandID);
	bool Write_NV_CDMA_LNA_OFFSET_VS_FREQ_2_I(int iBandID);
	bool Write_NV_CDMA_LNA_OFFSET_VS_FREQ_3_I(int iBandID);
	bool Write_NV_CDMA_LNA_OFFSET_VS_FREQ_4_I(int iBandID);
	bool Write_NV_CDMA_RX_CAL_CHAN_I(int iBandID);
	//CDMA RX Diversity
	bool Write_NV_C1_CDMA_VGA_GAIN_OFFSET_I(int iBandID);
	bool Write_NV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(int iBandID);
	bool Write_NV_C1_CDMA_LNA_OFFSET_I(int iBandID);
	bool Write_NV_C1_CDMA_LNA_OFFSET_2_I(int iBandID);
	bool Write_NV_C1_CDMA_LNA_OFFSET_3_I(int iBandID);
	bool Write_NV_C1_CDMA_LNA_OFFSET_4_I(int iBandID);
	bool Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_I(int iBandID);
	bool Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I(int iBandID);
	bool Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I(int iBandID);
	bool Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I(int iBandID);
	
public:
//WCDMA Rx NV Items
	bool Get_NV_WCDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_WCDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t stSize);

	bool Get_NV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex,  size_t stSize);

	bool Get_NV_WCDMA_IM2_I_VALUE_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_WCDMA_IM2_I_VALUE_I(PBYTE pByte, size_t stSize);

	bool Get_NV_WCDMA_IM2_Q_VALUE_I(PBYTE pByte, size_t& stSize);				
	bool Set_NV_WCDMA_IM2_Q_VALUE_I(PBYTE pByte, size_t stSize);				

	bool Get_NV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(PBYTE pByte, size_t stSize);

	bool Get_NV_WCDMA_LNA_OFFSET_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_WCDMA_LNA_OFFSET_I(PBYTE pByte, size_t stSize);

	bool Get_NV_WCDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_WCDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t stSize);

	bool Get_NV_WCDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_WCDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t stSize);

	bool Get_NV_WCDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t& stSize); 
	bool Set_NV_WCDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t stSize); 

	bool Get_NV_WCDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte,size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte,size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_WCDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t stSize); 

	//WCDMA Tx NV Items
	bool Get_NV_WCDMA_TX_LIN_MASTER_0_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_LIN_MASTER_0_I(PBYTE pByte, size_t stIndex, size_t stSize);

	virtual bool Get_NV_WCDMA_TX_LIN_MASTER_0_ENH_I(PBYTE pByte, size_t stIndex, size_t& stSize){return false;};
	virtual bool Set_NV_WCDMA_TX_LIN_MASTER_0_ENH_I(PBYTE pByte, size_t stIndex, size_t stSize){return false;};

	bool Get_NV_WCDMA_TX_LIN_MASTER_1_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_LIN_MASTER_1_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_TX_LIN_MASTER_2_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_LIN_MASTER_2_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_TX_LIN_MASTER_3_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_LIN_MASTER_3_I(PBYTE pByte, size_t stIndex, size_t stSize);


	bool Get_NV_WCDMA_TX_PDM_0_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_PDM_0_I(PBYTE pByte, size_t stIndex, size_t stSize);

	virtual bool Get_NV_WCDMA_TX_PDM_0_ENH_I(PBYTE pByte, size_t stIndex, size_t& stSize){return false;};
	virtual bool Set_NV_WCDMA_TX_PDM_0_ENH_I(PBYTE pByte, size_t stIndex, size_t stSize){return false;};

	bool Get_NV_WCDMA_TX_PDM_1_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_PDM_1_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_TX_PDM_2_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_PDM_2_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_TX_PDM_3_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_PDM_3_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_TX_COMP_VS_FREQ_0_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_COMP_VS_FREQ_0_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_TX_COMP_VS_FREQ_1_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_COMP_VS_FREQ_1_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_TX_COMP_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_COMP_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_TX_COMP_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_TX_COMP_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_LIM_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_LIM_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_WCDMA_EXP_HDET_VS_AGC_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_WCDMA_EXP_HDET_VS_AGC_I(PBYTE pByte, size_t stIndex, size_t stSize);

	virtual bool Get_NV_WCDMA_EXP_HDET_VS_AGC_V2_I(PBYTE pByte, size_t stIndex, size_t& stSize){return false;};
	virtual bool Set_NV_WCDMA_EXP_HDET_VS_AGC_V2_I(PBYTE pByte, size_t stIndex, size_t stSize){return false;};

	bool Get_NV_WCDMA_HDET_OFF_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_WCDMA_HDET_OFF_I(PBYTE pByte, size_t stSize);

	virtual bool Get_NV_WCDMA_HDET_OFF_V2_I(PBYTE pByte, size_t& stSize){return false;};
	virtual bool Set_NV_WCDMA_HDET_OFF_V2_I(PBYTE pByte, size_t stSize){return false;};

	bool Get_NV_WCDMA_HDET_SPN_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_WCDMA_HDET_SPN_I(PBYTE pByte, size_t stSize);

	virtual bool Get_NV_WCDMA_HDET_SPN_V2_I(PBYTE pByte, size_t& stSize){return false;};
	virtual bool Set_NV_WCDMA_HDET_SPN_V2_I(PBYTE pByte, size_t stSize){return false;};

	bool Get_Nv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_Nv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I(PBYTE pByte, size_t stIndex, size_t stSize); 




	//WCDMA Rx Diversity Path
	bool Get_NV_C1_WCDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_WCDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_WCDMA_LNA_OFFSET_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_WCDMA_LNA_OFFSET_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_WCDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_WCDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_WCDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_WCDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_WCDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_WCDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_WCDMA_IM2_I_VALUE_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_WCDMA_IM2_I_VALUE_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_WCDMA_IM2_Q_VALUE_I(PBYTE pByte, size_t& stSize);				
	bool Set_NV_C1_WCDMA_IM2_Q_VALUE_I(PBYTE pByte, size_t stSize);				

	bool Get_NV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(PBYTE pByte, size_t stSize);


	//GSM RX Compensation NV Items
	
	bool  Get_RX_GAIN_RANGE_1_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool  Set_RX_GAIN_RANGE_1_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool  Get_RX_GAIN_RANGE_2_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool  Set_RX_GAIN_RANGE_2_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool  Get_RX_GAIN_RANGE_3_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool  Set_RX_GAIN_RANGE_3_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool  Get_RX_GAIN_RANGE_4_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool  Set_RX_GAIN_RANGE_4_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize); 

	bool  Get_RX_GAIN_RANGE_5_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool  Set_RX_GAIN_RANGE_5_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize); 


	//GSM Tx Polar NV Items

	bool Get_NV_GSM_AMAM_MASTER_TBL_F1(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_GSM_AMAM_MASTER_TBL_F1(PBYTE pByte, size_t stIndex, size_t stSize); 


	bool Get_NV_GSM_AMAM_MASTER_TBL_F2(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_GSM_AMAM_MASTER_TBL_F2(PBYTE pByte, size_t stIndex, size_t stSize); 
	bool Get_NV_GSM_AMAM_MASTER_TBL_F3(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_GSM_AMAM_MASTER_TBL_F3(PBYTE pByte, size_t stIndex, size_t stSize); 

	bool Get_NV_GSM_AMPM_MASTER_TBL_F1(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_GSM_AMPM_MASTER_TBL_F1(PBYTE pByte, size_t stIndex, size_t stSize); 

	bool Get_NV_GSM_AMPM_MASTER_TBL_F2(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_GSM_AMPM_MASTER_TBL_F2(PBYTE pByte, size_t stIndex, size_t stSize); 

	bool Get_NV_GSM_AMPM_MASTER_TBL_F3(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_GSM_AMPM_MASTER_TBL_F3(PBYTE pByte, size_t stIndex, size_t stSize); 
	//GSM Timing Delay search
	bool Get_GSM_NV_POLAR_PATH_DELAY_I(PBYTE pByte, size_t& stSize);
	bool Set_GSM_NV_POLAR_PATH_DELAY_I(PBYTE pByte, size_t stSize);
	bool Write_GSM_NV_POLAR_PATH_DELAY_I(int iBandID);

	//Therm cal
	bool Get_NV_THERM_MAX(PBYTE pByte, size_t& stSize);
	bool Set_NV_THERM_MAX(PBYTE pByte, size_t stSize);

	bool Get_NV_THERM_MIN(PBYTE pByte, size_t& stSize);
	bool Set_NV_THERM_MIN(PBYTE pByte, size_t stSize);
	bool Write_NV_THERM_MAX_MIN();

	//Enh Therm cal
	virtual bool Get_NV_ENH_THERM_MAX(PBYTE pByte, size_t& stSize){return false;};
	virtual bool Set_NV_ENH_THERM_MAX(PBYTE pByte, size_t stSize){return false;};

	virtual bool Get_NV_ENH_THERM_MIN(PBYTE pByte, size_t& stSize){return false;};
	virtual bool Set_NV_ENH_THERM_MIN(PBYTE pByte, size_t stSize){return false;};
	virtual bool Write_NV_ENH_THERM_MAX_MIN(){return false;};

	//VCO
	bool Get_NV_VCO_DEFAULT_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_VCO_DEFAULT_I(PBYTE pByte, size_t stSize);

	bool Get_NV_VCO_SLOPE_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_VCO_SLOPE_I(PBYTE pByte, size_t stSize);

	//GSM Carrier Suppression
	bool Get_NV_GSM_CARRIER_SUPPRESSION_Idc(PBYTE pByte, size_t& stSize);
	bool Set_NV_GSM_CARRIER_SUPPRESSION_Idc(PBYTE pByte, size_t stSize);

	bool Get_NV_GSM_CARRIER_SUPPRESSION_Qdc(PBYTE pByte, size_t& stSize);
	bool Set_NV_GSM_CARRIER_SUPPRESSION_Qdc(PBYTE pByte, size_t stSize);
	bool Write_NV_GSM_CARRIER_SUPPRESSION_Idc_Qdc(int iBandID);

	// CDMA TX NV Items Operation
	bool Get_NV_CDMA_TX_LIN_MASTER(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_TX_LIN_MASTER(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t stSize);
	bool Set_NV_CDMA_TX_PDM(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_EXP_HDET_VS_AGC_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_EXP_HDET_VS_AGC_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_HDET_OFF_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_CDMA_HDET_OFF_I(PBYTE pByte, size_t stSize);
	
	bool Get_NV_CDMA_HDET_SPN_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_CDMA_HDET_SPN_I(PBYTE pByte, size_t stSize);

	bool Get_NV_CDMA_TX_COMP_VS_FREQ(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_TX_COMP_VS_FREQ(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_LIM_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_LIM_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_TX_CAL_CHAN_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_TX_CAL_CHAN_I(PBYTE pByte, size_t stIndex, size_t stSize);

	//CDMA Rx NV Items
	bool Get_NV_CDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_CDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t stSize);

	bool Get_NV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex,  size_t stSize);

	bool Get_NV_CDMA_LNA_OFFSET_I(int iRxLNARange, PBYTE pByte, size_t& stSize);
	bool Set_NV_CDMA_LNA_OFFSET_I(int iRxLNARange, PBYTE pByte, size_t stSize);

	bool Get_NV_CDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_CDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t stSize);

	bool Get_NV_CDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_CDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t stSize);

	bool Get_NV_CDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t& stSize); 
	bool Set_NV_CDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t stSize); 

	bool Get_NV_CDMA_LNA_OFFSET_VS_FREQ_I(int iRxLNARange, PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_LNA_OFFSET_VS_FREQ_I(int iRxLNARange, PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte,size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte,size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_CDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_INTELLICEIVER_CAL_I(PBYTE pByte, size_t stIndex, size_t& stSize); 
	bool Set_NV_CDMA_INTELLICEIVER_CAL_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_CDMA_RX_CAL_CHAN_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_CDMA_RX_CAL_CHAN_I(PBYTE pByte, size_t stIndex, size_t stSize);

	//CDMA Rx Diversity Path
	bool Get_NV_C1_CDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_CDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_CDMA_LNA_OFFSET_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_CDMA_LNA_OFFSET_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_CDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_CDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_CDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_CDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_CDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t& stSize);
	bool Set_NV_C1_CDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t stSize);

	bool Get_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize);

	bool Get_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t& stSize);
	bool Set_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t stSize);


protected:
	PIPhone m_pcPhone;

	//WCDMA Rx NV Items
	INT16 m_iNV_WCDMA_VGA_GAIN_OFFSET_I;
	INT8 m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[NV_WCDMA_FREQ_TABLE_SIZ];
	UINT8 m_uiNV_WCDMA_IM2_I_VALUE_I;
	UINT8 m_uiNV_WCDMA_IM2_Q_VALUE_I;				
	UINT8 m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I;

	UINT16 m_uiNV_WCDMA_LNA_OFFSET_I;
	UINT16 m_uiNV_WCDMA_LNA_OFFSET_2_I;
	UINT16 m_uiNV_WCDMA_LNA_OFFSET_3_I;
	UINT16 m_uiNV_WCDMA_LNA_OFFSET_4_I; 
	INT8 m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I[NV_WCDMA_FREQ_TABLE_SIZ]; 

	//WCDMA Tx NV Items
	UINT16 m_uiNV_WCDMA_TX_LIN_MASTER_0_I[NV_WCDMA_TX_LIN_MASTER_SIZ];
	UINT16 m_uiNV_WCDMA_TX_LIN_MASTER_1_I[NV_WCDMA_TX_LIN_MASTER_SIZ];
	UINT16 m_uiNV_WCDMA_TX_LIN_MASTER_2_I[NV_WCDMA_TX_LIN_MASTER_SIZ];
	UINT16 m_uiNV_WCDMA_TX_LIN_MASTER_3_I[NV_WCDMA_TX_LIN_MASTER_SIZ];

	UINT16 m_uiNV_WCDMA_TX_PDM_0_I[NV_WCDMA_TX_LIN_MASTER_SIZ];
	UINT16 m_uiNV_WCDMA_TX_PDM_1_I[NV_WCDMA_TX_LIN_MASTER_SIZ];
	UINT16 m_uiNV_WCDMA_TX_PDM_2_I[NV_WCDMA_TX_LIN_MASTER_SIZ];
	UINT16 m_uiNV_WCDMA_TX_PDM_3_I[NV_WCDMA_TX_LIN_MASTER_SIZ];

	INT8 m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I[NV_WCDMA_FREQ_TABLE_SIZ];

	INT16 m_iNV_WCDMA_LIM_VS_FREQ_I[NV_WCDMA_FREQ_TABLE_SIZ];

	UINT8 m_uiNV_WCDMA_EXP_HDET_VS_AGC_I[NV_WCDMA_EXP_HDET_VS_AGC_SIZ];
	UINT8 m_uiNV_WCDMA_HDET_OFF_I;
	UINT8 m_uiNV_WCDMA_HDET_SPN_I;

	INT8 m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I[NV_WCDMA_FREQ_TABLE_SIZ];//new for RTR6285

	//WCDMA Rx Diversity Path
	INT16 m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I;
	INT8 m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[NV_WCDMA_FREQ_TABLE_SIZ];

	UINT16 m_uiNV_C1_WCDMA_LNA_OFFSET_I;
	UINT16 m_uiNV_C1_WCDMA_LNA_OFFSET_2_I;
	UINT16 m_uiNV_C1_WCDMA_LNA_OFFSET_3_I;
	UINT16 m_uiNV_C1_WCDMA_LNA_OFFSET_4_I;
	INT8 m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I[NV_WCDMA_FREQ_TABLE_SIZ];
	INT8 m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I[NV_WCDMA_FREQ_TABLE_SIZ];
	UINT8 m_uiNV_C1_WCDMA_IM2_I_VALUE_I;
	UINT8 m_uiNV_C1_WCDMA_IM2_Q_VALUE_I;				
	UINT8 m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I;



	//RX Compensation NV Items
	INT16  m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP[NV_DCS_CAL_ARFCN_SIZ];
	INT16  m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP[NV_DCS_CAL_ARFCN_SIZ];
	INT16  m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP[NV_DCS_CAL_ARFCN_SIZ];
	INT16  m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP[NV_DCS_CAL_ARFCN_SIZ];
	INT16  m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP[NV_DCS_CAL_ARFCN_SIZ]; 


	//Tx Polar NV Items
	UINT16 m_uiNV_GSM_AMAM_MASTER_TBL_F1[RF_AMAM_MASTER_TBL_SIZ]; 
	UINT16 m_uiNV_GSM_AMAM_MASTER_TBL_F2[RF_AMAM_MASTER_TBL_SIZ]; 
	UINT16 m_uiNV_GSM_AMAM_MASTER_TBL_F3[RF_AMAM_MASTER_TBL_SIZ];

	INT32 m_iNV_GSM_AMPM_MASTER_TBL_F1[RF_AMPM_MASTER_TBL_SIZ];
	INT32 m_iNV_GSM_AMPM_MASTER_TBL_F2[RF_AMPM_MASTER_TBL_SIZ];
	INT32 m_iNV_GSM_AMPM_MASTER_TBL_F3[RF_AMPM_MASTER_TBL_SIZ];


	//Timing Delay search
	UINT16 m_uiNV_GSM_POLAR_PATH_DELAY;

	//Therm cal, first is max
	INT8 m_iNV_THERM_MAX_MIN[2];

	//Pout
	//UINT16 piVgaOut, piDetOut, piStatus;
	//Tx CS NV Items
	UINT16 m_uiNV_IDC_QDC[2];

	//PA_DAC_Search
	UINT16 m_uiNV_VCO_Default;
	UINT16 m_uiNV_VCO_Slope;

	//CDMA Tx NV Items
	INT16 m_iNV_CDMA_TX_LIN_MASTER_0_I[NV_CDMA_TX_LIN_MASTER_SIZ];
	INT16 m_iNV_CDMA_TX_LIN_MASTER_1_I[NV_CDMA_TX_LIN_MASTER_SIZ];
	INT16 m_iNV_CDMA_TX_LIN_MASTER_2_I[NV_CDMA_TX_LIN_MASTER_SIZ];
	INT16 m_iNV_CDMA_TX_LIN_MASTER_3_I[NV_CDMA_TX_LIN_MASTER_SIZ];

	INT16 m_iNV_CDMA_TX_PDM_0_I[NV_CDMA_TX_LIN_MASTER_SIZ];
	INT16 m_iNV_CDMA_TX_PDM_1_I[NV_CDMA_TX_LIN_MASTER_SIZ];
	INT16 m_iNV_CDMA_TX_PDM_2_I[NV_CDMA_TX_LIN_MASTER_SIZ];
	INT16 m_iNV_CDMA_TX_PDM_3_I[NV_CDMA_TX_LIN_MASTER_SIZ];

	UINT8  m_uiNV_CDMA_EXP_HDET_VS_AGC_I[NV_CDMA_EXP_HDET_VS_AGC_SIZ];
	UINT8 m_uiNV_CDMA_HDET_OFF_I;
	UINT8 m_uiNV_CDMA_HDET_SPN_I;

	UINT16 m_uiNV_CDMA_TX_CAL_CHAN[NV_CDMA_FREQ_TABLE_SIZ];

	   /*TX_LIN_VS_TEMP[7:0], TX_SLP_VS_TEMP[15:8], TX_COMP_VS_FREQ[31:16]*/
	INT8 m_iNV_CDMA_TX_COMP_0_I[NV_CDMA_COMP_TABLE_SIZ];
	INT8 m_iNV_CDMA_TX_COMP_1_I[NV_CDMA_COMP_TABLE_SIZ];
	INT8 m_iNV_CDMA_TX_COMP_2_I[NV_CDMA_COMP_TABLE_SIZ];
	INT8 m_iNV_CDMA_TX_COMP_3_I[NV_CDMA_COMP_TABLE_SIZ];

	INT8  m_iNV_CDMA_LIM_VS_FREQ_I[NV_CDMA_LIM_FREQ_TABLE_SIZ];

	//CDMA Rx NV Items
	INT16  m_iNV_CDMA_VGA_GAIN_OFFSET_I;
	INT8   m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[NV_CDMA_FREQ_TABLE_SIZ*3];
	
	INT16  m_iNV_CDMA_LNA_OFFSET_I;
	INT16  m_iNV_CDMA_LNA_OFFSET_2_I;
	INT16  m_iNV_CDMA_LNA_OFFSET_3_I;
	INT16  m_iNV_CDMA_LNA_OFFSET_4_I; 
	INT8   m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I[NV_CDMA_FREQ_TABLE_SIZ*3];
	INT8   m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[NV_CDMA_FREQ_TABLE_SIZ*3];
	INT8   m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[NV_CDMA_FREQ_TABLE_SIZ*3];
	INT8   m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[NV_CDMA_FREQ_TABLE_SIZ*3]; 
	UINT16 m_uiNV_CDMA_INTELLICEIVER_CAL[7];
	UINT16 m_uiNV_CDMA_RX_CAL_CHAN[NV_CDMA_FREQ_TABLE_SIZ];

	//CDMA Rx Diversity Path
	INT16 m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I;
	INT8  m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[NV_CDMA_COMP_TABLE_SIZ];

	INT16 m_iNV_C1_CDMA_LNA_OFFSET_I;
	INT16 m_iNV_C1_CDMA_LNA_OFFSET_2_I;
	INT16 m_iNV_C1_CDMA_LNA_OFFSET_3_I;
	INT16 m_iNV_C1_CDMA_LNA_OFFSET_4_I;
	INT8  m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I[NV_CDMA_COMP_TABLE_SIZ];
	INT8  m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I[NV_CDMA_COMP_TABLE_SIZ];
	INT8  m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I[NV_CDMA_COMP_TABLE_SIZ];
	INT8  m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I[NV_CDMA_COMP_TABLE_SIZ];

};
typedef CRFNVItems* PCRFNVItems;


#endif//__RF_NF_ITEM_H