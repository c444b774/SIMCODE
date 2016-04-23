
#ifndef __BAND_INFO__H__
#define __BAND_INFO__H__
 
#include "inc\commoninclude.h"
#include "inc\QLib_Defines.h"
#include "inc\CMU_Defines.h"
 
#define GSM_850_BAND_ID 850
#define GSM_EGSM_BAND_ID 900
#define GSM_DCS_BAND_ID 1800
#define GSM_PCS_BAND_ID 1900
 
#define WCDMA_850_BAND_ID 850
#define WCDMA_900_BAND_ID 900
#define WCDMA_1750_BAND_ID 1750
#define WCDMA_1500_BAND_ID 1500
#define WCDMA_AWS_BAND_ID 1700
#define WCDMA_PCS_BAND_ID 1900
#define WCDMA_IMT_BAND_ID 2100
#define WCDMA_1800_BAND_ID 1800
#define WCDMA_B6_BAND_ID 830
#define WCDMA_B19_BAND_ID 840

#define CDMA_BC0_BAND_ID 800
#define CDMA_BC1_BAND_ID 1900
#define CDMA_BC10_BAND_ID 820

 
enum CHANNEL_TYPE_ENUM{
	TYPE_LOW_CH,
	TYPE_MIDDLE_CH,
	TYPE_HIGH_CH
};

enum PCL_TYPE_ENUM{	
	TYPE_LOW_PCL,	
	TYPE_MIDDLE_PCL,
	TYPE_HIGH_PCL
};
 
 
class CGSMBandInfo
{
public:
	static inline bool CheckVaildBand(const int iBand){
		return (iBand == GSM_850_BAND_ID) || (iBand == GSM_EGSM_BAND_ID) || (iBand == GSM_DCS_BAND_ID) || (iBand == GSM_PCS_BAND_ID);
	}
	static inline bool CheckVaildBand(const CString &strBand){
		return CheckVaildBand(CStr::StrToInt(strBand));
	}
	static bool CheckVaildCH(const int iBand, const int iChannel);
	static inline bool CheckVaildCH(const CString &strBand, const CString &strChannel)
	{
		return CheckVaildCH(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}
	static bool CheckVaildPCL(const int iBand, const int iPcl);
	static inline bool CheckVaildPCL(const CString &strBand, const CString &strPcl)
	{
		return CheckVaildPCL(CStr::StrToInt(strBand), CStr::StrToInt(strPcl));
	}
 
	static double ArfcnToTXHz(const int iBand, const int iArfcnCH);
	static double ArfcnToRXHz(const int iBand, const int iArfcnCH);
	static inline double ArfcnToTXHz(const CString &strBand, const CString &strArfcnCH){
		return ArfcnToTXHz(CStr::StrToInt(strBand), CStr::StrToInt(strArfcnCH));
	}
	static inline double ArfcnToRXHz(const CString &strBand, const CString &strArfcnCH){
		return ArfcnToRXHz(CStr::StrToInt(strBand), CStr::StrToInt(strArfcnCH));
	}
 
	static int GetCMU_SigMode(const int iBand);
	static int GetCMU_NSigMode(const int iBand);
	static FTM_RF_Mode_Enum GetPhoneMode(const int iBand);
	static FTM_GSM_BER_Band_Enum GetPhoneTestMode(const int iBand);
	static int GetChannelType(const int iBand, const int iChannel);
	static int GetPclType(const int iBand, const int iPcl);
 
	static inline int GetCMU_SigMode(const CString& strBand)
	{
		return GetCMU_SigMode(CStr::StrToInt(strBand));
	}
	static inline int GetCMU_NSigMode(const CString& strBand)
	{
		return GetCMU_NSigMode(CStr::StrToInt(strBand));
	}
 
	static inline FTM_RF_Mode_Enum GetPhoneMode(const CString& strBand)
	{
		return GetPhoneMode(CStr::StrToInt(strBand));
	}
	static inline FTM_GSM_BER_Band_Enum GetPhoneTestMode(const CString& strBand)
	{
		return GetPhoneTestMode(CStr::StrToInt(strBand));
	}
 
	static inline int GetChannelType(const CString& strBand, const CString& strChannel)
	{
		return GetChannelType(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}

	static inline int GetPclType(const CString& strBand, const CString& strPcl)
	{
		return GetPclType(CStr::StrToInt(strBand), CStr::StrToInt(strPcl));
	}
 
 
};
 
class CWCDMABandInfo
{
public:
	static inline bool CheckVaildBand(const int iBand){
		return (iBand==WCDMA_B6_BAND_ID)||(iBand==WCDMA_B19_BAND_ID)||(iBand==WCDMA_1800_BAND_ID)||(iBand == WCDMA_850_BAND_ID) || (iBand == WCDMA_900_BAND_ID) || (iBand == WCDMA_AWS_BAND_ID)|| (iBand == WCDMA_PCS_BAND_ID) || (iBand == WCDMA_IMT_BAND_ID);
	}
	static inline bool CheckVaildBand(const CString &strBand){
		return CheckVaildBand(CStr::StrToInt(strBand));
	}
	static bool CheckVaildCH(const int iBand, const int iChannel);
	static inline bool CheckVaildCH(const CString &strBand, const CString &strChannel)
	{
		return CheckVaildCH(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}
	static int GetDLChannel(const int iBand, const int iULChannel);
	static inline int GetDLChannel(const CString& strBand, const CString& strULChannel)
	{
		return GetDLChannel(CStr::StrToInt(strBand), CStr::StrToInt(strULChannel));
	}
	static int GetULChannel(const int iBand, const int iDLChannel);
	static inline int GetULChannel(const CString& strBand, const CString& strDLChannel)
	{
		return GetULChannel(CStr::StrToInt(strBand), CStr::StrToInt(strDLChannel));
	}
	static double ArfcnToHz(const int iBand, const int iArfcnCH,const int isUL=1);
	static inline double ArfcnToHz(const CString &strBand, const CString &strArfcnCH){
		return ArfcnToHz(CStr::StrToInt(strBand), CStr::StrToInt(strArfcnCH));
	}
 
	static int GetCMU_NSigMode(const int iBand);
	static int GetCMU_SigMode(const int iBand);
	static FTM_RF_Mode_Enum GetPhoneMode(const int iBand);	
	static int GetChannelType(const int iBand, const int iChannel);
 
	static inline int GetCMU_NSigMode(const CString& strBand)
	{
		return GetCMU_NSigMode(CStr::StrToInt(strBand));
	}
	static inline int GetCMU_SigMode(const CString& strBand)
	{
		return GetCMU_SigMode(CStr::StrToInt(strBand));
	}
	static inline FTM_RF_Mode_Enum GetPhoneMode(const CString& strBand)
	{
		return GetPhoneMode(CStr::StrToInt(strBand));
	}
	static int GetNVModeID(const int iBand);
	static inline int GetNVModeID(const CString& strBand)
	{
		return GetNVModeID(CStr::StrToInt(strBand));
	}
 
	static inline int GetChannelType(const CString& strBand, const CString& strChannel)
	{
		return GetChannelType(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}
 
};

class CLTEBandInfo
{
public:
	static inline bool CheckVaildBand(const int iBand){
		bool bRet=false;
		if (1<=iBand&&41>=iBand)
		{
			bRet=true;
		}
		return bRet;

	}
	static inline bool CheckVaildBand(const CString &strBand){
		return CheckVaildBand(CStr::StrToInt(strBand));
	}
	static bool CheckVaildCH(const int iBand, const int iChannel);
	static inline bool CheckVaildCH(const CString &strBand, const CString &strChannel)
	{
		return CheckVaildCH(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}
	static int GetDLChannel(const int iBand, const int iULChannel);
	static inline int GetDLChannel(const CString& strBand, const CString& strULChannel)
	{
		return GetDLChannel(CStr::StrToInt(strBand), CStr::StrToInt(strULChannel));
	}
	static int GetULChannel(const int iBand, const int iDLChannel);
	static inline int GetULChannel(const CString& strBand, const CString& strDLChannel)
	{
		return GetULChannel(CStr::StrToInt(strBand), CStr::StrToInt(strDLChannel));
	}
	static double ArfcnToHz(const int iBand, const int iArfcnCH);
	static inline double ArfcnToHz(const CString &strBand, const CString &strArfcnCH){
		return ArfcnToHz(CStr::StrToInt(strBand), CStr::StrToInt(strArfcnCH));
	}

	static int GetCMU_NSigMode(const int iBand);
	static int GetCMU_SigMode(const int iBand);
	static FTM_RF_Mode_Enum GetPhoneMode(const int iBand);
	static int GetChannelType(const int iBand, const int iChannel);

	static inline int GetCMU_NSigMode(const CString& strBand)
	{
		return GetCMU_NSigMode(CStr::StrToInt(strBand));
	}
	static inline int GetCMU_SigMode(const CString& strBand)
	{
		return GetCMU_SigMode(CStr::StrToInt(strBand));
	}
	static inline FTM_RF_Mode_Enum GetPhoneMode(const CString& strBand)
	{
		return GetPhoneMode(CStr::StrToInt(strBand));
	}
	static nv_mode_id_type GetNVModeID(const int iBand);
	static inline nv_mode_id_type GetNVModeID(const CString& strBand)
	{
		return GetNVModeID(CStr::StrToInt(strBand));
	}

	static inline int GetChannelType(const CString& strBand, const CString& strChannel)
	{
		return GetChannelType(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}

};

class CTDSBandInfo
{
public:
	static inline bool CheckVaildBand(const int iBand){
		
		return (iBand == 34) || (iBand == 39) || (iBand == 40);
	}
	static inline bool CheckVaildBand(const CString &strBand){
		return CheckVaildBand(CStr::StrToInt(strBand));
	}
	static bool CheckVaildCH(const int iBand, const int iChannel);
	static inline bool CheckVaildCH(const CString &strBand, const CString &strChannel)
	{
		return CheckVaildCH(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}
	static int GetDLChannel(const int iBand, const int iULChannel);
	static inline int GetDLChannel(const CString& strBand, const CString& strULChannel)
	{
		return GetDLChannel(CStr::StrToInt(strBand), CStr::StrToInt(strULChannel));
	}
	static int GetULChannel(const int iBand, const int iDLChannel);
	static inline int GetULChannel(const CString& strBand, const CString& strDLChannel)
	{
		return GetULChannel(CStr::StrToInt(strBand), CStr::StrToInt(strDLChannel));
	}
	static double ArfcnToHz(const int iBand, const int iArfcnCH);
	static inline double ArfcnToHz(const CString &strBand, const CString &strArfcnCH){
		return ArfcnToHz(CStr::StrToInt(strBand), CStr::StrToInt(strArfcnCH));
	}

	static int GetCMU_NSigMode(const int iBand);
	static int GetCMU_SigMode(const int iBand);
	static FTM_RF_Mode_Enum GetPhoneMode(const int iBand);
	static int GetChannelType(const int iBand, const int iChannel);

	static inline int GetCMU_NSigMode(const CString& strBand)
	{
		return GetCMU_NSigMode(CStr::StrToInt(strBand));
	}
	static inline int GetCMU_SigMode(const CString& strBand)
	{
		return GetCMU_SigMode(CStr::StrToInt(strBand));
	}
	static inline FTM_RF_Mode_Enum GetPhoneMode(const CString& strBand)
	{
		return GetPhoneMode(CStr::StrToInt(strBand));
	}
	static nv_mode_id_type GetNVModeID(const int iBand);
	static inline nv_mode_id_type GetNVModeID(const CString& strBand)
	{
		return GetNVModeID(CStr::StrToInt(strBand));
	}

	static inline int GetChannelType(const CString& strBand, const CString& strChannel)
	{
		return GetChannelType(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}

};



class CCDMABandInfo
{
public:
	static inline bool CheckVaildBand(const int iBand){
		return (iBand == CDMA_BC0_BAND_ID) || (iBand == CDMA_BC1_BAND_ID)||(iBand == CDMA_BC10_BAND_ID);
	}
	static inline bool CheckVaildBand(const CString &strBand){
		return CheckVaildBand(CStr::StrToInt(strBand));
	}
	static bool CheckVaildCH(const int iBand, const int iChannel);
	static inline bool CheckVaildCH(const CString &strBand, const CString &strChannel)
	{
		return CheckVaildCH(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}
	static int GetDLChannel(const int iBand, const int iULChannel);
	static inline int GetDLChannel(const CString& strBand, const CString& strULChannel)
	{
		return GetDLChannel(CStr::StrToInt(strBand), CStr::StrToInt(strULChannel));
	}
	static int GetULChannel(const int iBand, const int iDLChannel);
	static inline int GetULChannel(const CString& strBand, const CString& strDLChannel)
	{
		return GetULChannel(CStr::StrToInt(strBand), CStr::StrToInt(strDLChannel));
	}
	static double ArfcnToHz(const int iBand, const int iArfcnCH, const int iULorDL);
	static inline double ArfcnToHz(const CString &strBand, const CString &strArfcnCH, const CString &strULorDL){
		return ArfcnToHz(CStr::StrToInt(strBand), CStr::StrToInt(strArfcnCH), CStr::StrToInt(strULorDL));
	}
 
	static int GetCMU_NSigMode(const int iBand);
	static int GetCMU_SigMode(const int iBand);
	static FTM_RF_Mode_Enum GetPhoneMode(const int iBand);
	static FTM_CDMA2000_BandClasstype GetPhoneBandClassMode(const int iBand);
	static int GetChannelType(const int iBand, const int iChannel);
 
	static inline int GetCMU_NSigMode(const CString& strBand)
	{
		return GetCMU_NSigMode(CStr::StrToInt(strBand));
	}
	static inline int GetCMU_SigMode(const CString& strBand)
	{
		return GetCMU_SigMode(CStr::StrToInt(strBand));
	}
	static inline FTM_RF_Mode_Enum GetPhoneMode(const CString& strBand)
	{
		return GetPhoneMode(CStr::StrToInt(strBand));
	}

	static nv_mode_id_type GetNVModeID(const int iBand);
	static inline nv_mode_id_type GetNVModeID(const CString& strBand)
	{
		return GetNVModeID(CStr::StrToInt(strBand));
	}

	static inline FTM_CDMA2000_BandClasstype GetPhoneBandClassMode(const CString& strBand)
	{
		return GetPhoneBandClassMode(CStr::StrToInt(strBand));
	}
 
	static inline int GetChannelType(const CString& strBand, const CString& strChannel)
	{
		return GetChannelType(CStr::StrToInt(strBand), CStr::StrToInt(strChannel));
	}
 
};
 

 
#endif //__BAND_INFO__H__
