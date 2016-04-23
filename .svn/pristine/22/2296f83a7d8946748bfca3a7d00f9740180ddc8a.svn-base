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
 *   Copyright (C) 2009 Simcom Corporation
 *   All Rights Reserved.
 *
 ***************************************************************************/
/* *** <<< DO NOT MODIFY OR REMOVE THIS LINE - END >>> *** */

#include "stdafx.h"
#include "CRFNVItem.h"
 
#pragma warning( disable : 4244 )

RF_IMPLEMENT_DYNCREATE(CRFNVItems)
PILogger CRFNVItems::m_piLogger = NULL;
 
 
CRFNVItems::CRFNVItems()
{
	SetLogger(m_pcPhone->m_piLogger);
	InitVariable();
}
 
 
void CRFNVItems::TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg)
{
	if (m_piLogger)
		m_piLogger->TraceLog(lpszModule, emLevel,lpszFileName, uiLine, lpszMsg);
}
 
bool CRFNVItems::Write_NV_WCDMA_RX(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_WCDMA_VGA_GAIN_OFFSET_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LNA_OFFSET_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LNA_OFFSET_2_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LNA_OFFSET_3_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LNA_OFFSET_4_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_2_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_3_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_4_I(iBandID)){return bRet;}
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_RX_Diversity(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_C1_WCDMA_VGA_GAIN_OFFSET_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_LNA_OFFSET_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_LNA_OFFSET_2_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_LNA_OFFSET_3_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_LNA_OFFSET_4_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I(iBandID)){return bRet;}
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_TX(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_WCDMA_TX_LIN_MASTER_0_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_LIN_MASTER_1_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_LIN_MASTER_2_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_LIN_MASTER_3_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_PDM_0_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_PDM_1_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_PDM_2_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_PDM_3_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_COMP_VS_FREQ_0_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_COMP_VS_FREQ_1_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_COMP_VS_FREQ_2_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_TX_COMP_VS_FREQ_3_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_LIM_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_EXP_HDET_VS_AGC_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_HDET_OFF_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_HDET_SPN_I(iBandID)){return bRet;}
	if(!Write_Nv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I(iBandID)){return bRet;}
	return true;
 
}
 
bool CRFNVItems::Write_NV_WCDMA_IM2(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_WCDMA_IM2_I_VALUE_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_IM2_Q_VALUE_I(iBandID)){return bRet;}
	if(!Write_NV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(iBandID)){return bRet;}
	return true;
 
}
 
bool CRFNVItems::Write_NV_WCDMA_IM2_Diversity(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_C1_WCDMA_IM2_I_VALUE_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_IM2_Q_VALUE_I(iBandID)){return bRet;}
	if(!Write_NV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(iBandID)){return bRet;}
	return true;
 
}
bool CRFNVItems::Write_NV_GSM_RX(int iBandID)
{
	bool bRet = false;
	if(!Write_RX_GAIN_RANGE_1_FREQ_COMP_I(iBandID)){return bRet;}
	if(!Write_RX_GAIN_RANGE_2_FREQ_COMP_I(iBandID)){return bRet;}
	if(!Write_RX_GAIN_RANGE_3_FREQ_COMP_I(iBandID)){return bRet;}
	if(!Write_RX_GAIN_RANGE_4_FREQ_COMP_I(iBandID)){return bRet;}
	if(!Write_RX_GAIN_RANGE_5_FREQ_COMP_I(iBandID)){return bRet;}
	return true;
 
}
bool CRFNVItems::Write_NV_GSM_TX(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_GSM_AMAM_MASTER_TBL_F1(iBandID)){return bRet;}
	if(!Write_NV_GSM_AMAM_MASTER_TBL_F2(iBandID)){return bRet;}
	if(!Write_NV_GSM_AMPM_MASTER_TBL_F1(iBandID)){return bRet;}
	if(!Write_NV_GSM_AMPM_MASTER_TBL_F2(iBandID)){return bRet;}
 
	return true;
 
}
bool CRFNVItems::Write_NV_GSM_TX_V2(IntVtr vChannel,int iBandID)
{
	bool bRet = false;
	for(int i=0;i<vChannel.size();i++)
	{
		if(vChannel[i]==-1)
			continue;
	switch(i)
	{
	case 0:
		if(!Write_NV_GSM_AMAM_MASTER_TBL_F1(iBandID)){return bRet;}
		if(!Write_NV_GSM_AMPM_MASTER_TBL_F1(iBandID)){return bRet;}
		break;
	case 1:
		if(!Write_NV_GSM_AMAM_MASTER_TBL_F2(iBandID)){return bRet;}
	    if(!Write_NV_GSM_AMPM_MASTER_TBL_F2(iBandID)){return bRet;}
		break;

	case 2:
		if(!Write_NV_GSM_AMAM_MASTER_TBL_F3(iBandID)){return bRet;}
	    if(!Write_NV_GSM_AMPM_MASTER_TBL_F3(iBandID)){return bRet;}
		break;
	default: 
		
		return false;
	}
	

	}
 
	return true;
 
}
bool CRFNVItems::Write_NV_GSM_KVCO(int iBandID)
{
	bool bRet = false;
 
	return true;
 
}
bool CRFNVItems::Write_NV_GSM_PADAC_Search()
{
	bool bRet = false;
	if(!Write_NV_VCO_DEFAULT_I()){return bRet;}
	if(!Write_NV_VCO_SLOPE_I()){return bRet;}
 
	return true;
 
}
bool CRFNVItems::Get_NV_WCDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_VGA_GAIN_OFFSET_I);
	memcpy(pByte, &m_iNV_WCDMA_VGA_GAIN_OFFSET_I, stSize);
	return true;
}
 
bool CRFNVItems::Set_NV_WCDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_WCDMA_VGA_GAIN_OFFSET_I));
	memcpy(&m_iNV_WCDMA_VGA_GAIN_OFFSET_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_VGA_GAIN_OFFSET_I(int iBandID)
{
	DWORD dwNVItemID_DVGA_Offset = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
		case WCDMA_IMT_BAND_ID:
			dwNVItemID_DVGA_Offset = NV_WCDMA_VGA_GAIN_OFFSET_I;
			break;
		case WCDMA_PCS_BAND_ID:
			dwNVItemID_DVGA_Offset = NV_WCDMA_1900_VGA_GAIN_OFFSET_I;
				break;
		case WCDMA_AWS_BAND_ID:
			dwNVItemID_DVGA_Offset = NV_WCDMA_BC4_VGA_GAIN_OFFSET_I;
				break;
		case WCDMA_850_BAND_ID:
			dwNVItemID_DVGA_Offset = NV_WCDMA_800_VGA_GAIN_OFFSET_I;
				break;
		case WCDMA_900_BAND_ID:
			dwNVItemID_DVGA_Offset = NV_WCDMA_900_VGA_GAIN_OFFSET_I;
				break;
		default:
			ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_DVGA_Offset, (unsigned char* )&m_iNV_WCDMA_VGA_GAIN_OFFSET_I, sizeof(m_iNV_WCDMA_VGA_GAIN_OFFSET_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex,  size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(int iBandID)
{
	DWORD dwNVItemID_DVGA_Offset = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_WCDMA_1900_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_WCDMA_BC4_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_WCDMA_800_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_WCDMA_900_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_DVGA_Offset, (unsigned char* )&m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I, sizeof(m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_IM2_I_VALUE_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_IM2_I_VALUE_I);
	memcpy(pByte, &m_uiNV_WCDMA_IM2_I_VALUE_I, stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_IM2_I_VALUE_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_IM2_I_VALUE_I));
	memcpy(&m_uiNV_WCDMA_IM2_I_VALUE_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_IM2_I_VALUE_I(int iBandID)
{
	DWORD dwNV_WCDMA_IM2_I_VALUE_I = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_WCDMA_IM2_I_VALUE_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_WCDMA_1900_IM2_I_VALUE_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_WCDMA_BC4_IM2_I_VALUE_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_WCDMA_800_IM2_I_VALUE_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_WCDMA_900_IM2_I_VALUE_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_IM2_I_VALUE_I, (unsigned char* )&m_uiNV_WCDMA_IM2_I_VALUE_I, sizeof(m_uiNV_WCDMA_IM2_I_VALUE_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
 
}
 
bool CRFNVItems::Get_NV_WCDMA_IM2_Q_VALUE_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_IM2_Q_VALUE_I);
	memcpy(pByte, &m_uiNV_WCDMA_IM2_Q_VALUE_I, stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_IM2_Q_VALUE_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_IM2_Q_VALUE_I));
	memcpy(&m_uiNV_WCDMA_IM2_Q_VALUE_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_IM2_Q_VALUE_I(int iBandID)
{
	DWORD dwNV_WCDMA_IM2_Q_VALUE_I = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_WCDMA_IM2_Q_VALUE_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_WCDMA_1900_IM2_Q_VALUE_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_WCDMA_BC4_IM2_Q_VALUE_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_WCDMA_800_IM2_Q_VALUE_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_WCDMA_900_IM2_Q_VALUE_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_IM2_Q_VALUE_I, (unsigned char* )&m_uiNV_WCDMA_IM2_Q_VALUE_I, sizeof(m_uiNV_WCDMA_IM2_Q_VALUE_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
 
}
 
 
bool CRFNVItems::Get_NV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I);
	memcpy(pByte, &m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I));
	memcpy(&m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(int iBandID)
{
	DWORD dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_WCDMA_1900_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_WCDMA_BC4_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_WCDMA_800_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_WCDMA_900_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, (unsigned char* )&m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, sizeof(m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
 
}
 
 
bool CRFNVItems::Get_NV_WCDMA_LNA_OFFSET_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_LNA_OFFSET_I);
	memcpy(pByte, &m_uiNV_WCDMA_LNA_OFFSET_I, stSize);
	return true;
}
 
bool CRFNVItems::Set_NV_WCDMA_LNA_OFFSET_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_LNA_OFFSET_I));
	memcpy(&m_uiNV_WCDMA_LNA_OFFSET_I, pByte, stSize);
	return true;
}
 
bool CRFNVItems::Write_NV_WCDMA_LNA_OFFSET_I(int iBandID)
{
	DWORD dwNV_WCDMA_LNA_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET= NV_WCDMA_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_1900_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_BC4_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_800_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_900_LNA_RANGE_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_LNA_OFFSET, (unsigned char* )&m_uiNV_WCDMA_LNA_OFFSET_I, sizeof(m_uiNV_WCDMA_LNA_OFFSET_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
 
}
 
bool CRFNVItems::Get_NV_WCDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_LNA_OFFSET_2_I);
	memcpy(pByte, &m_uiNV_WCDMA_LNA_OFFSET_2_I, stSize);
	return true;
 
}
 
bool CRFNVItems::Set_NV_WCDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_LNA_OFFSET_2_I));
	memcpy(&m_uiNV_WCDMA_LNA_OFFSET_2_I, pByte, stSize);
	return true;
}
 
bool CRFNVItems::Write_NV_WCDMA_LNA_OFFSET_2_I(int iBandID)
{
	DWORD dwNV_WCDMA_LNA_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET= NV_WCDMA_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_1900_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_BC4_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_800_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_900_LNA_RANGE_OFFSET_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_LNA_OFFSET, (unsigned char* )&m_uiNV_WCDMA_LNA_OFFSET_2_I, sizeof(m_uiNV_WCDMA_LNA_OFFSET_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_LNA_OFFSET_3_I);
	memcpy(pByte, &m_uiNV_WCDMA_LNA_OFFSET_3_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_LNA_OFFSET_3_I));
	memcpy(&m_uiNV_WCDMA_LNA_OFFSET_3_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_LNA_OFFSET_3_I(int iBandID)
{
	DWORD dwNV_WCDMA_LNA_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET= NV_WCDMA_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_1900_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_BC4_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_800_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_900_LNA_RANGE_OFFSET_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_LNA_OFFSET, (unsigned char* )&m_uiNV_WCDMA_LNA_OFFSET_3_I, sizeof(m_uiNV_WCDMA_LNA_OFFSET_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_LNA_OFFSET_4_I);
	memcpy(pByte, &m_uiNV_WCDMA_LNA_OFFSET_4_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_LNA_OFFSET_4_I));
	memcpy(&m_uiNV_WCDMA_LNA_OFFSET_4_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_LNA_OFFSET_4_I(int iBandID)
{
	DWORD dwNV_WCDMA_LNA_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET= NV_WCDMA_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_1900_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_BC4_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_800_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_LNA_OFFSET = NV_WCDMA_900_LNA_RANGE_OFFSET_4_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_LNA_OFFSET, (unsigned char* )&m_uiNV_WCDMA_LNA_OFFSET_4_I, sizeof(m_uiNV_WCDMA_LNA_OFFSET_4_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_I(int iBandID)
{
	DWORD dwNVItemID_LNA_Offset = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_LNA_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_1900_LNA_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_BC4_LNA_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_800_LNA_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_900_LNA_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LNA_Offset, (unsigned char* )&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I, sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte,size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte,size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_2_I(int iBandID)
{
	DWORD dwNVItemID_LNA_Offset = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_LNA_OFFSET_VS_FREQ_2_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_1900_LNA_OFFSET_VS_FREQ_2_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_BC4_LNA_OFFSET_VS_FREQ_2_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_800_LNA_OFFSET_VS_FREQ_2_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_900_LNA_OFFSET_VS_FREQ_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LNA_Offset, (unsigned char* )&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I, sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_3_I(int iBandID)
{
	DWORD dwNVItemID_LNA_Offset = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_LNA_OFFSET_VS_FREQ_3_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_1900_LNA_OFFSET_VS_FREQ_3_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_BC4_LNA_OFFSET_VS_FREQ_3_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_800_LNA_OFFSET_VS_FREQ_3_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_900_LNA_OFFSET_VS_FREQ_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LNA_Offset, (unsigned char* )&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I, sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_LNA_OFFSET_VS_FREQ_4_I(int iBandID)
{
	DWORD dwNVItemID_LNA_Offset = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_LNA_OFFSET_VS_FREQ_4_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_1900_LNA_OFFSET_VS_FREQ_4_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_BC4_LNA_OFFSET_VS_FREQ_4_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_800_LNA_OFFSET_VS_FREQ_4_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LNA_Offset = NV_WCDMA_900_LNA_OFFSET_VS_FREQ_4_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LNA_Offset, (unsigned char* )&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I, sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
 
bool CRFNVItems::Get_NV_WCDMA_TX_LIN_MASTER_0_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_0_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_TX_LIN_MASTER_0_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_TX_LIN_MASTER_0_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_0_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_TX_LIN_MASTER_0_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_LIN_MASTER_0_I(int iBandID)
{
	DWORD dwNVItemID_LIN_MASTER = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_TX_LIN_MASTER_0_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_1900_TX_LIN_MASTER_0_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_BC4_TX_LIN_MASTER_0_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_800_TX_LIN_MASTER_0_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_900_TX_LIN_MASTER_0_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIN_MASTER, (unsigned char* )&m_uiNV_WCDMA_TX_LIN_MASTER_0_I, sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_0_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_TX_LIN_MASTER_1_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_1_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_TX_LIN_MASTER_1_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_TX_LIN_MASTER_1_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_1_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_TX_LIN_MASTER_1_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_LIN_MASTER_1_I(int iBandID)
{
	DWORD dwNVItemID_LIN_MASTER = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_TX_LIN_MASTER_1_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_1900_TX_LIN_MASTER_1_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_BC4_TX_LIN_MASTER_1_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_800_TX_LIN_MASTER_1_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_900_TX_LIN_MASTER_1_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIN_MASTER, (unsigned char* )&m_uiNV_WCDMA_TX_LIN_MASTER_1_I, sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_1_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_TX_LIN_MASTER_2_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_2_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_TX_LIN_MASTER_2_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_TX_LIN_MASTER_2_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_2_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_TX_LIN_MASTER_2_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_LIN_MASTER_2_I(int iBandID)
{
	DWORD dwNVItemID_LIN_MASTER = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_TX_LIN_MASTER_2_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_1900_TX_LIN_MASTER_2_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_BC4_TX_LIN_MASTER_2_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_800_TX_LIN_MASTER_2_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_900_TX_LIN_MASTER_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIN_MASTER, (unsigned char* )&m_uiNV_WCDMA_TX_LIN_MASTER_2_I, sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_TX_LIN_MASTER_3_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_3_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_TX_LIN_MASTER_3_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_TX_LIN_MASTER_3_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_3_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_TX_LIN_MASTER_3_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_LIN_MASTER_3_I(int iBandID)
{
	DWORD dwNVItemID_LIN_MASTER = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_TX_LIN_MASTER_3_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_1900_TX_LIN_MASTER_3_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_BC4_TX_LIN_MASTER_3_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_800_TX_LIN_MASTER_3_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_WCDMA_900_TX_LIN_MASTER_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIN_MASTER, (unsigned char* )&m_uiNV_WCDMA_TX_LIN_MASTER_3_I, sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_TX_PDM_0_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_TX_PDM_0_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_TX_PDM_0_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_TX_PDM_0_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_TX_PDM_0_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_TX_PDM_0_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_PDM_0_I(int iBandID)
{
	DWORD dwNVItemID_TX_PDM = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_TX_PDM_LIN_0_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_1900_TX_PDM_LIN_0_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_BC4_TX_PDM_LIN_0_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_800_TX_PDM_LIN_0_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_900_TX_PDM_LIN_0_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_PDM, (unsigned char* )&m_uiNV_WCDMA_TX_PDM_0_I, sizeof(m_uiNV_WCDMA_TX_PDM_0_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_TX_PDM_1_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_TX_PDM_1_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_TX_PDM_1_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_TX_PDM_1_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_TX_PDM_1_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_TX_PDM_1_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_PDM_1_I(int iBandID)
{
	DWORD dwNVItemID_TX_PDM = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_TX_PDM_LIN_1_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_1900_TX_PDM_LIN_1_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_BC4_TX_PDM_LIN_1_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_800_TX_PDM_LIN_1_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_900_TX_PDM_LIN_1_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_PDM, (unsigned char* )&m_uiNV_WCDMA_TX_PDM_1_I, sizeof(m_uiNV_WCDMA_TX_PDM_1_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_TX_PDM_2_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_TX_PDM_2_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_TX_PDM_2_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_TX_PDM_2_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_TX_PDM_2_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_TX_PDM_2_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_PDM_2_I(int iBandID)
{
	DWORD dwNVItemID_TX_PDM = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_TX_PDM_LIN_2_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_1900_TX_PDM_LIN_2_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_BC4_TX_PDM_LIN_2_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_800_TX_PDM_LIN_2_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_900_TX_PDM_LIN_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_PDM, (unsigned char* )&m_uiNV_WCDMA_TX_PDM_2_I, sizeof(m_uiNV_WCDMA_TX_PDM_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_TX_PDM_3_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_TX_PDM_3_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_TX_PDM_3_I[stIndex], stSize);
	return true;
 
}
 
bool CRFNVItems::Set_NV_WCDMA_TX_PDM_3_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_TX_PDM_3_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_TX_PDM_3_I[stIndex], pByte, stSize);
	return true;
 
}
 
bool CRFNVItems::Write_NV_WCDMA_TX_PDM_3_I(int iBandID)
{
	DWORD dwNVItemID_TX_PDM = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_TX_PDM_LIN_3_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_1900_TX_PDM_LIN_3_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_BC4_TX_PDM_LIN_3_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_800_TX_PDM_LIN_3_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_PDM = NV_WCDMA_900_TX_PDM_LIN_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_PDM, (unsigned char* )&m_uiNV_WCDMA_TX_PDM_3_I, sizeof(m_uiNV_WCDMA_TX_PDM_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_TX_COMP_VS_FREQ_0_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I[stIndex], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_WCDMA_TX_COMP_VS_FREQ_0_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_COMP_VS_FREQ_0_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP= 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_TX_COMP_VS_FREQ_0_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_1900_TX_COMP_VS_FREQ_0_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_BC4_TX_COMP_VS_FREQ_0_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_800_TX_COMP_VS_FREQ_0_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_900_TX_COMP_VS_FREQ_0_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP, (unsigned char* )&m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I, sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_TX_COMP_VS_FREQ_1_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_TX_COMP_VS_FREQ_1_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_COMP_VS_FREQ_1_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_TX_COMP_VS_FREQ_1_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_1900_TX_COMP_VS_FREQ_1_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_BC4_TX_COMP_VS_FREQ_1_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_800_TX_COMP_VS_FREQ_1_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_900_TX_COMP_VS_FREQ_1_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP, (unsigned char* )&m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I, sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_TX_COMP_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_TX_COMP_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_COMP_VS_FREQ_2_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_TX_COMP_VS_FREQ_2_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_1900_TX_COMP_VS_FREQ_2_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_BC4_TX_COMP_VS_FREQ_2_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_800_TX_COMP_VS_FREQ_2_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_900_TX_COMP_VS_FREQ_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP, (unsigned char* )&m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I, sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_TX_COMP_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_TX_COMP_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_TX_COMP_VS_FREQ_3_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_TX_COMP_VS_FREQ_3_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_1900_TX_COMP_VS_FREQ_3_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_BC4_TX_COMP_VS_FREQ_3_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_800_TX_COMP_VS_FREQ_3_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_COMP = NV_WCDMA_900_TX_COMP_VS_FREQ_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP, (unsigned char* )&m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I, sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_LIM_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_WCDMA_LIM_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_WCDMA_LIM_VS_FREQ_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_LIM_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_WCDMA_LIM_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_WCDMA_LIM_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_LIM_VS_FREQ_I(int iBandID)
{
	DWORD dwNVItemID_LIM_FREQ = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_LIM_FREQ = NV_WCDMA_TX_LIM_VS_FREQ_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_LIM_FREQ = NV_WCDMA_1900_TX_LIM_VS_FREQ_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_LIM_FREQ = NV_WCDMA_BC4_TX_LIM_VS_FREQ_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_LIM_FREQ = NV_WCDMA_800_TX_LIM_VS_FREQ_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_LIM_FREQ = NV_WCDMA_900_TX_LIM_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIM_FREQ, (unsigned char* )&m_iNV_WCDMA_LIM_VS_FREQ_I, sizeof(m_iNV_WCDMA_LIM_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_WCDMA_EXP_HDET_VS_AGC_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_EXP_HDET_VS_AGC_I[stIndex]);
	memcpy(pByte, &m_uiNV_WCDMA_EXP_HDET_VS_AGC_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_WCDMA_EXP_HDET_VS_AGC_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_WCDMA_EXP_HDET_VS_AGC_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_WCDMA_EXP_HDET_VS_AGC_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_WCDMA_EXP_HDET_VS_AGC_I(int iBandID)
{
	DWORD dwNVItemID_HDET_AGC = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_HDET_AGC = NV_WCDMA_EXP_HDET_VS_AGC_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_HDET_AGC = NV_WCDMA_1900_EXP_HDET_VS_AGC_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_HDET_AGC = NV_WCDMA_BC4_EXP_HDET_VS_AGC_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_HDET_AGC = NV_WCDMA_800_EXP_HDET_VS_AGC_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_HDET_AGC = NV_WCDMA_900_EXP_HDET_VS_AGC_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_HDET_AGC, (unsigned char* )&m_uiNV_WCDMA_EXP_HDET_VS_AGC_I, sizeof(m_uiNV_WCDMA_EXP_HDET_VS_AGC_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_HDET_OFF_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_HDET_OFF_I);
	memcpy(pByte, &m_uiNV_WCDMA_HDET_OFF_I, stSize);
	return true;
}
 
bool CRFNVItems::Set_NV_WCDMA_HDET_OFF_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_HDET_OFF_I));
	memcpy(&m_uiNV_WCDMA_HDET_OFF_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_HDET_OFF_I(int iBandID)
{
	DWORD dwNV_WCDMA_HDET_OFF = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_HDET_OFF= NV_WCDMA_HDET_OFF_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_HDET_OFF = NV_WCDMA_1900_HDET_OFF_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_HDET_OFF = NV_WCDMA_BC4_HDET_OFF_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_HDET_OFF = NV_WCDMA_800_HDET_OFF_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_HDET_OFF = NV_WCDMA_900_HDET_OFF_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_HDET_OFF, (unsigned char* )&m_uiNV_WCDMA_HDET_OFF_I, sizeof(m_uiNV_WCDMA_HDET_OFF_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_WCDMA_HDET_SPN_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_WCDMA_HDET_SPN_I);
	memcpy(pByte, &m_uiNV_WCDMA_HDET_SPN_I, stSize);
	return true;
}
 
bool CRFNVItems::Set_NV_WCDMA_HDET_SPN_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_WCDMA_HDET_SPN_I));
	memcpy(&m_uiNV_WCDMA_HDET_SPN_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_WCDMA_HDET_SPN_I(int iBandID)
{
	DWORD dwNV_WCDMA_HDET_SPN = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_HDET_SPN= NV_WCDMA_HDET_SPN_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_HDET_SPN = NV_WCDMA_1900_HDET_SPN_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNV_WCDMA_HDET_SPN = NV_WCDMA_BC4_HDET_SPN_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_HDET_SPN = NV_WCDMA_800_HDET_SPN_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_HDET_SPN = NV_WCDMA_900_HDET_SPN_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_HDET_SPN, (unsigned char* )&m_uiNV_WCDMA_HDET_SPN_I, sizeof(m_uiNV_WCDMA_HDET_SPN_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_Nv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I[stIndex]);
	memcpy(pByte, &m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_Nv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I[stIndex], pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_Nv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP_FREQ_SECONDARY = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNVItemID_TX_COMP_FREQ_SECONDARY = NV_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNVItemID_TX_COMP_FREQ_SECONDARY = NV_WCDMA_1900_TX_COMP_VS_FREQ_0_SECONDARY_I;
		break;
	case WCDMA_AWS_BAND_ID:
		dwNVItemID_TX_COMP_FREQ_SECONDARY = NV_WCDMA_BC4_TX_COMP_VS_FREQ_0_SECONDARY_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNVItemID_TX_COMP_FREQ_SECONDARY = NV_WCDMA_800_TX_COMP_VS_FREQ_0_SECONDARY_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNVItemID_TX_COMP_FREQ_SECONDARY = NV_WCDMA_900_TX_COMP_VS_FREQ_0_SECONDARY_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP_FREQ_SECONDARY, (unsigned char* )&m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I, sizeof(m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
 
//WCDMA Rx Diversity Path
bool CRFNVItems::Get_NV_C1_WCDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I);
	memcpy(pByte, &m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I, stSize);
	return true;
}
 
bool CRFNVItems::Set_NV_C1_WCDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t stSize)
{
	stSize = sizeof(m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I);
	memcpy(pByte, &m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I, stSize);
	return true;
}
 
bool CRFNVItems::Write_NV_C1_WCDMA_VGA_GAIN_OFFSET_I(int iBandID)
{
	DWORD dwNV_C1_VGA_GAIN_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET= NV_C1_WCDMA_2100_VGA_GAIN_OFFSET_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET = NV_C1_WCDMA_1900_VGA_GAIN_OFFSET_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET = NV_C1_WCDMA_800_VGA_GAIN_OFFSET_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET = NV_C1_WCDMA_900_VGA_GAIN_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_VGA_GAIN_OFFSET, (unsigned char* )&m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I, sizeof(m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex], stSize);
	return true;
}
 
bool CRFNVItems::Set_NV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
}
 
bool CRFNVItems::Write_NV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I(int iBandID)
{
	DWORD dwNV_C1_VGA_GAIN_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET= NV_C1_WCDMA_2100_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET = NV_C1_WCDMA_1900_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET = NV_C1_WCDMA_800_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET = NV_C1_WCDMA_900_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_VGA_GAIN_OFFSET, (unsigned char* )&m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I, sizeof(m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_WCDMA_LNA_OFFSET_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_I);
	memcpy(pByte, &m_uiNV_C1_WCDMA_LNA_OFFSET_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_WCDMA_LNA_OFFSET_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_I));
	memcpy(&m_uiNV_C1_WCDMA_LNA_OFFSET_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_LNA_OFFSET_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_LNA_OFFSET= NV_C1_WCDMA_2100_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_1900_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_800_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_900_LNA_RANGE_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET, (unsigned char* )&m_uiNV_C1_WCDMA_LNA_OFFSET_I, sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_C1_WCDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_2_I);
	memcpy(pByte, &m_uiNV_C1_WCDMA_LNA_OFFSET_2_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_WCDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_2_I));
	memcpy(&m_uiNV_C1_WCDMA_LNA_OFFSET_2_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_LNA_OFFSET_2_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_LNA_OFFSET= NV_C1_WCDMA_2100_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_1900_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_800_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_900_LNA_RANGE_OFFSET_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET, (unsigned char* )&m_uiNV_C1_WCDMA_LNA_OFFSET_2_I, sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_WCDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_3_I);
	memcpy(pByte, &m_uiNV_C1_WCDMA_LNA_OFFSET_3_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_WCDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_3_I));
	memcpy(&m_uiNV_C1_WCDMA_LNA_OFFSET_3_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_LNA_OFFSET_3_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_LNA_OFFSET= NV_C1_WCDMA_2100_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_1900_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_800_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_900_LNA_RANGE_OFFSET_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET, (unsigned char* )&m_uiNV_C1_WCDMA_LNA_OFFSET_3_I, sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_C1_WCDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_4_I);
	memcpy(pByte, &m_uiNV_C1_WCDMA_LNA_OFFSET_4_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_WCDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_4_I));
	memcpy(&m_uiNV_C1_WCDMA_LNA_OFFSET_4_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_LNA_OFFSET_4_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_LNA_OFFSET= NV_C1_WCDMA_2100_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_1900_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_800_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_WCDMA_900_LNA_RANGE_OFFSET_4_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET, (unsigned char* )&m_uiNV_C1_WCDMA_LNA_OFFSET_4_I, sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_4_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET_VS_FREQ = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ= NV_C1_WCDMA_2100_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_1900_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_800_LNA_RANGE_OFFSET_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_900_LNA_RANGE_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET_VS_FREQ, (unsigned char* )&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I, sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET_VS_FREQ = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ= NV_C1_WCDMA_2100_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_1900_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_800_LNA_RANGE_OFFSET_2_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_900_LNA_RANGE_OFFSET_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET_VS_FREQ, (unsigned char* )&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I, sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET_VS_FREQ = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ= NV_C1_WCDMA_2100_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_1900_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_800_LNA_RANGE_OFFSET_3_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_900_LNA_RANGE_OFFSET_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET_VS_FREQ, (unsigned char* )&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I, sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET_VS_FREQ = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ= NV_C1_WCDMA_2100_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_1900_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_800_LNA_RANGE_OFFSET_4_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_WCDMA_900_LNA_RANGE_OFFSET_4_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET_VS_FREQ, (unsigned char* )&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I, sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_WCDMA_IM2_I_VALUE_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_C1_WCDMA_IM2_I_VALUE_I);
	memcpy(pByte, &m_uiNV_C1_WCDMA_IM2_I_VALUE_I, stSize);
	return true;
 
}
 
bool CRFNVItems::Set_NV_C1_WCDMA_IM2_I_VALUE_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_C1_WCDMA_IM2_I_VALUE_I));
	memcpy(&m_uiNV_C1_WCDMA_IM2_I_VALUE_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_IM2_I_VALUE_I(int iBandID)
{
	DWORD dwNV_WCDMA_IM2_I_VALUE_I = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_C1_WCDMA_2100_IM2_I_VALUE_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_C1_WCDMA_1900_IM2_I_VALUE_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_C1_WCDMA_800_IM2_I_VALUE_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_IM2_I_VALUE_I = NV_C1_WCDMA_900_IM2_I_VALUE_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_IM2_I_VALUE_I, (unsigned char* )&m_uiNV_C1_WCDMA_IM2_I_VALUE_I, sizeof(m_uiNV_C1_WCDMA_IM2_I_VALUE_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
 
}
 
bool CRFNVItems::Get_NV_C1_WCDMA_IM2_Q_VALUE_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_C1_WCDMA_IM2_Q_VALUE_I);
	memcpy(pByte, &m_uiNV_C1_WCDMA_IM2_Q_VALUE_I, stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_C1_WCDMA_IM2_Q_VALUE_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_C1_WCDMA_IM2_Q_VALUE_I));
	memcpy(&m_uiNV_C1_WCDMA_IM2_Q_VALUE_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_IM2_Q_VALUE_I(int iBandID)
{
	DWORD dwNV_WCDMA_IM2_Q_VALUE_I = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_C1_WCDMA_2100_IM2_Q_VALUE_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_C1_WCDMA_1900_IM2_Q_VALUE_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_C1_WCDMA_800_IM2_Q_VALUE_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_IM2_Q_VALUE_I = NV_C1_WCDMA_900_IM2_Q_VALUE_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_IM2_Q_VALUE_I, (unsigned char* )&m_uiNV_C1_WCDMA_IM2_Q_VALUE_I, sizeof(m_uiNV_C1_WCDMA_IM2_Q_VALUE_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
 
}
bool CRFNVItems::Get_NV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I);
	memcpy(pByte, &m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I));
	memcpy(&m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I(int iBandID)
{
	DWORD dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case WCDMA_IMT_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_C1_WCDMA_2100_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	case WCDMA_PCS_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_C1_WCDMA_1900_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	case WCDMA_850_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_C1_WCDMA_800_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	case WCDMA_900_BAND_ID:
		dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I = NV_C1_WCDMA_900_IM2_TRANSCONDUCTOR_VALUE_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, (unsigned char* )&m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, sizeof(m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
 
}
 
 
bool CRFNVItems:: Get_RX_GAIN_RANGE_1_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP[stIndex]);
	memcpy(pByte, &m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP[stIndex], stSize);
	return true;
}
bool CRFNVItems:: Set_RX_GAIN_RANGE_1_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems:: Write_RX_GAIN_RANGE_1_FREQ_COMP_I(int iBandID)
{
	DWORD dwNV_GSM_RX_GAIN_RANGE = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE= NV_DCS_RX_GAIN_RANGE_1_FREQ_COMP_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_1900_RX_GAIN_RANGE_1_FREQ_COMP_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_850_RX_GAIN_RANGE_1_FREQ_COMP_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_RX_GAIN_RANGE_1_FREQ_COMP_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_RX_GAIN_RANGE, (unsigned char* )&m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP, sizeof(m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems:: Get_RX_GAIN_RANGE_2_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP[stIndex]);
	memcpy(pByte, &m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP[stIndex], stSize);
	return true;
}
bool CRFNVItems:: Set_RX_GAIN_RANGE_2_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems:: Write_RX_GAIN_RANGE_2_FREQ_COMP_I(int iBandID)
{
	DWORD dwNV_GSM_RX_GAIN_RANGE = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE= NV_DCS_RX_GAIN_RANGE_2_FREQ_COMP_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_1900_RX_GAIN_RANGE_2_FREQ_COMP_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_850_RX_GAIN_RANGE_2_FREQ_COMP_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_RX_GAIN_RANGE_2_FREQ_COMP_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_RX_GAIN_RANGE, (unsigned char* )&m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP, sizeof(m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems:: Get_RX_GAIN_RANGE_3_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP[stIndex]);
	memcpy(pByte, &m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP[stIndex], stSize);
	return true;
}
bool CRFNVItems:: Set_RX_GAIN_RANGE_3_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems:: Write_RX_GAIN_RANGE_3_FREQ_COMP_I(int iBandID)
{
	DWORD dwNV_GSM_RX_GAIN_RANGE = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE= NV_DCS_RX_GAIN_RANGE_3_FREQ_COMP_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_1900_RX_GAIN_RANGE_3_FREQ_COMP_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_850_RX_GAIN_RANGE_3_FREQ_COMP_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_RX_GAIN_RANGE_3_FREQ_COMP_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_RX_GAIN_RANGE, (unsigned char* )&m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP, sizeof(m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems:: Get_RX_GAIN_RANGE_4_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP[stIndex]);
	memcpy(pByte, &m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP[stIndex], stSize);
	return true;
}
bool CRFNVItems:: Set_RX_GAIN_RANGE_4_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems:: Write_RX_GAIN_RANGE_4_FREQ_COMP_I(int iBandID)
{
	DWORD dwNV_GSM_RX_GAIN_RANGE = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE= NV_DCS_RX_GAIN_RANGE_4_FREQ_COMP_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_1900_RX_GAIN_RANGE_4_FREQ_COMP_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_850_RX_GAIN_RANGE_4_FREQ_COMP_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_RX_GAIN_RANGE_4_FREQ_COMP_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_RX_GAIN_RANGE, (unsigned char* )&m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP, sizeof(m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems:: Get_RX_GAIN_RANGE_5_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP[stIndex]);
	memcpy(pByte, &m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP[stIndex], stSize);
	return true;
}
bool CRFNVItems:: Set_RX_GAIN_RANGE_5_FREQ_COMP_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems:: Write_RX_GAIN_RANGE_5_FREQ_COMP_I(int iBandID)
{
	DWORD dwNV_GSM_RX_GAIN_RANGE = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE= NV_DCS_RX_GAIN_RANGE_5_FREQ_COMP_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_1900_RX_GAIN_RANGE_5_FREQ_COMP_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_850_RX_GAIN_RANGE_5_FREQ_COMP_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_RX_GAIN_RANGE = NV_GSM_RX_GAIN_RANGE_5_FREQ_COMP_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_RX_GAIN_RANGE, (unsigned char* )&m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP, sizeof(m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
bool CRFNVItems::Get_NV_GSM_AMAM_MASTER_TBL_F1(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F1[stIndex]);
	memcpy(pByte, &m_uiNV_GSM_AMAM_MASTER_TBL_F1[stIndex], stSize);
	return true;
}
bool CRFNVItems::Get_NV_GSM_AMAM_MASTER_TBL_F3(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F3[stIndex]);
	memcpy(pByte, &m_uiNV_GSM_AMAM_MASTER_TBL_F3[stIndex], stSize);
	return true;
}

bool CRFNVItems::Set_NV_GSM_AMAM_MASTER_TBL_F1(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F1[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_GSM_AMAM_MASTER_TBL_F1[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Set_NV_GSM_AMAM_MASTER_TBL_F3(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F3[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_GSM_AMAM_MASTER_TBL_F3[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_GSM_AMAM_MASTER_TBL_F1(int iBandID)
{
	DWORD dwNV_GSM_AMAM_MASTER_TBL = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL= NV_DCS_AMAM_MASTER_TBL_SEG1_F1_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_1900_AMAM_MASTER_TBL_SEG1_F1_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_850_AMAM_MASTER_TBL_SEG1__F1_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_AMAM_MASTER_TBL_SEG1_F1_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	for( int i = 0 ; i < 8 ; i++){
		if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_AMAM_MASTER_TBL + i, (unsigned char* )&m_uiNV_GSM_AMAM_MASTER_TBL_F1 + i * 64 *sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F1[0]), sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F1[0])*64, &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
		{
			return false;
		}
	}
	return true;
}
 
bool CRFNVItems::Get_NV_GSM_AMAM_MASTER_TBL_F2(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F2[stIndex]);
	memcpy(pByte, &m_uiNV_GSM_AMAM_MASTER_TBL_F2[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_GSM_AMAM_MASTER_TBL_F2(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F2[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_GSM_AMAM_MASTER_TBL_F2[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_GSM_AMAM_MASTER_TBL_F2(int iBandID)
{
	DWORD dwNV_GSM_AMAM_MASTER_TBL = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL= NV_DCS_AMAM_MASTER_TBL_SEG1_F2_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_1900_AMAM_MASTER_TBL_SEG1_F2_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_850_AMAM_MASTER_TBL_SEG1__F2_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_AMAM_MASTER_TBL_SEG1_F2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	for( int i = 0 ; i < 8 ; i++){
		if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_AMAM_MASTER_TBL + i, (unsigned char* )&m_uiNV_GSM_AMAM_MASTER_TBL_F2 + i * 64 *sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F2[0]), sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F2[0])*64, &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
		{
			return false;
		}
	}
	return true;
}
bool CRFNVItems::Write_NV_GSM_AMAM_MASTER_TBL_F3(int iBandID)
{
	DWORD dwNV_GSM_AMAM_MASTER_TBL = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL= NV_DCS_AMAM_MASTER_TBL_SEG1_F3_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_1900_AMAM_MASTER_TBL_SEG1_F3_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_850_AMAM_MASTER_TBL_SEG1__F3_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_AMAM_MASTER_TBL = NV_GSM_AMAM_MASTER_TBL_SEG1_F3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	for( int i = 0 ; i < 8 ; i++){
		if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_AMAM_MASTER_TBL + i, (unsigned char* )&m_uiNV_GSM_AMAM_MASTER_TBL_F3 + i * 64 *sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F3[0]), sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F3[0])*64, &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
		{
			return false;
		}
	}
	return true;
}
bool CRFNVItems::Get_NV_GSM_AMPM_MASTER_TBL_F1(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F1[stIndex]);
	memcpy(pByte, &m_iNV_GSM_AMPM_MASTER_TBL_F1[stIndex], stSize);
	return true;
}
bool CRFNVItems::Get_NV_GSM_AMPM_MASTER_TBL_F3(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F3[stIndex]);
	memcpy(pByte, &m_iNV_GSM_AMPM_MASTER_TBL_F3[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_GSM_AMPM_MASTER_TBL_F1(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F1[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_GSM_AMPM_MASTER_TBL_F1[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Set_NV_GSM_AMPM_MASTER_TBL_F3(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F3[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_GSM_AMPM_MASTER_TBL_F3[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_GSM_AMPM_MASTER_TBL_F1(int iBandID)
{
	DWORD dwNV_GSM_AMPM_MASTER_TBL = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL= NV_DCS_AMPM_MASTER_TBL_SEG1_F1_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_1900_AMPM_MASTER_TBL_SEG1_F1_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_850_AMPM_MASTER_TBL_SEG1__F1_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_AMPM_MASTER_TBL_SEG1_F1_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	for( int i = 0 ; i < 8 ; i++){
		if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_AMPM_MASTER_TBL + i, (unsigned char* )&m_iNV_GSM_AMPM_MASTER_TBL_F1 + i * 32 *sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F1[0]), sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F1[0])*32, &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
		{
			return false;
		}
	}
	return true;
}
bool CRFNVItems::Get_NV_GSM_AMPM_MASTER_TBL_F2(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F2[stIndex]);
	memcpy(pByte, &m_iNV_GSM_AMPM_MASTER_TBL_F2[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_GSM_AMPM_MASTER_TBL_F2(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F2[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_GSM_AMPM_MASTER_TBL_F2[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_GSM_AMPM_MASTER_TBL_F2(int iBandID)
{
	DWORD dwNV_GSM_AMPM_MASTER_TBL = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL= NV_DCS_AMPM_MASTER_TBL_SEG1_F2_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_1900_AMPM_MASTER_TBL_SEG1_F2_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_850_AMPM_MASTER_TBL_SEG1__F2_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_AMPM_MASTER_TBL_SEG1_F2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	for( int i = 0 ; i < 8 ; i++){
		if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_AMPM_MASTER_TBL + i, (unsigned char* )&m_iNV_GSM_AMPM_MASTER_TBL_F2 + i * 32 *sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F2[0]), sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F2[0])*32, &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
		{
			return false;
		}
	}
	return true;
}
bool CRFNVItems::Write_NV_GSM_AMPM_MASTER_TBL_F3(int iBandID)
{
	DWORD dwNV_GSM_AMPM_MASTER_TBL = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL= NV_DCS_AMPM_MASTER_TBL_SEG1_F3_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_1900_AMPM_MASTER_TBL_SEG1_F3_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_850_AMPM_MASTER_TBL_SEG1__F3_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_AMPM_MASTER_TBL = NV_GSM_AMPM_MASTER_TBL_SEG1_F3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	for( int i = 0 ; i < 8 ; i++){
		if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_AMPM_MASTER_TBL + i, (unsigned char* )&m_iNV_GSM_AMPM_MASTER_TBL_F3 + i * 32 *sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F3[0]), sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F3[0])*32, &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
		{
			return false;
		}
	}
	return true;
}
//GSM Timing Delay search
bool CRFNVItems::Get_GSM_NV_POLAR_PATH_DELAY_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_GSM_POLAR_PATH_DELAY);
	memcpy(pByte, &m_uiNV_GSM_POLAR_PATH_DELAY, stSize);
	return true;
 
}
bool CRFNVItems::Set_GSM_NV_POLAR_PATH_DELAY_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_GSM_POLAR_PATH_DELAY));
	memcpy(&m_uiNV_GSM_POLAR_PATH_DELAY, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_GSM_NV_POLAR_PATH_DELAY_I(int iBandID)
{
	DWORD dwNV_GSM_POLAR_PATH_DELAY = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_POLAR_PATH_DELAY= NV_DCS_POLAR_PATH_DELAY_I;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_POLAR_PATH_DELAY = NV_GSM_1900_POLAR_PATH_DELAY_I;
		break;
	case GSM_850_BAND_ID:
		dwNV_GSM_POLAR_PATH_DELAY = NV_850_POLAR_PATH_DELAY_I;
		break;
	case GSM_EGSM_BAND_ID:
		dwNV_GSM_POLAR_PATH_DELAY = NV_GSM_POLAR_PATH_DELAY_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_POLAR_PATH_DELAY, (unsigned char* )&m_uiNV_GSM_POLAR_PATH_DELAY, sizeof(m_uiNV_GSM_POLAR_PATH_DELAY), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
//Therm cal
bool CRFNVItems::Get_NV_THERM_MAX(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_THERM_MAX_MIN[0]);
	memcpy(pByte, &m_iNV_THERM_MAX_MIN[0], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_THERM_MAX(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_THERM_MAX_MIN[0]));
	memcpy(&m_iNV_THERM_MAX_MIN[0], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_THERM_MAX_MIN()
{
	DWORD dwNV_THERM_MAX_MIN = NV_THERM_I;
	WORD wStatus = 0;
 
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_THERM_MAX_MIN, (unsigned char* )&m_iNV_THERM_MAX_MIN, sizeof(m_iNV_THERM_MAX_MIN), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
 
bool CRFNVItems::Get_NV_THERM_MIN(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_THERM_MAX_MIN[1]);
	memcpy(pByte, &m_iNV_THERM_MAX_MIN[1], stSize);
	return true;
 
}
 
bool CRFNVItems::Set_NV_THERM_MIN(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_THERM_MAX_MIN[1]));
	memcpy(&m_iNV_THERM_MAX_MIN[1], pByte, stSize);
	return true;
}
 
//GSM Carrier Suppression
bool CRFNVItems::Get_NV_GSM_CARRIER_SUPPRESSION_Idc(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_IDC_QDC[1]);
	memcpy(pByte, &m_uiNV_IDC_QDC[1], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_GSM_CARRIER_SUPPRESSION_Idc(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_IDC_QDC[1]));
	memcpy(&m_uiNV_IDC_QDC[1], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_GSM_CARRIER_SUPPRESSION_Idc_Qdc(int iBandID)
{
	DWORD dwNV_GSM_CARRIER_SUPPRESSION = 0;
	WORD wStatus = 0;
 
	switch(iBandID)
	{
	case GSM_DCS_BAND_ID:
		dwNV_GSM_CARRIER_SUPPRESSION= NV_GSM_DCS_CARRIER_SUPPRESSION;
		break;
	case GSM_PCS_BAND_ID:
		dwNV_GSM_CARRIER_SUPPRESSION = NV_GSM_1900_CARRIER_SUPPRESSION;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_GSM_CARRIER_SUPPRESSION, (unsigned char* )&m_uiNV_IDC_QDC, sizeof(m_uiNV_IDC_QDC), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_GSM_CARRIER_SUPPRESSION_Qdc(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_IDC_QDC[0]);
	memcpy(pByte, &m_uiNV_IDC_QDC[0], stSize);
	return true;
 
}
bool CRFNVItems::Set_NV_GSM_CARRIER_SUPPRESSION_Qdc(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_IDC_QDC[0]));
	memcpy(&m_uiNV_IDC_QDC[0], pByte, stSize);
	return true;
}
 
 
//PA_DAC_Search
bool CRFNVItems::Get_NV_VCO_DEFAULT_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_VCO_Default);
	memcpy(pByte, &m_uiNV_VCO_Default, stSize);
	return true;
}
bool CRFNVItems::Set_NV_VCO_DEFAULT_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_VCO_Default));
	memcpy(&m_uiNV_VCO_Default, pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_VCO_DEFAULT_I()
{
	WORD wStatus = 0;
 
	if(m_pcPhone->WriteRFNVItemInBatchMode(NV_VCO_DEFAULT_I, (unsigned char* )&m_uiNV_VCO_Default, sizeof(m_uiNV_VCO_Default), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_VCO_SLOPE_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_VCO_Slope);
	memcpy(pByte, &m_uiNV_VCO_Slope, stSize);
	return true;
}
bool CRFNVItems::Set_NV_VCO_SLOPE_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_VCO_Slope));
	memcpy(&m_uiNV_VCO_Slope, pByte, stSize);
	return true;
 
}
bool CRFNVItems::Write_NV_VCO_SLOPE_I()
{
	WORD wStatus = 0;
 
	if(m_pcPhone->WriteRFNVItemInBatchMode(NV_VCO_SLOPE_I, (unsigned char* )&m_uiNV_VCO_Slope, sizeof(m_uiNV_VCO_Slope), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
 
 
void CRFNVItems::InitVariable()
{
	const int iInitNum = 0;
	//WCDMA Rx NV Items
	memset(&m_iNV_WCDMA_VGA_GAIN_OFFSET_I, iInitNum, sizeof(m_iNV_WCDMA_VGA_GAIN_OFFSET_I));
	memset(&m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I, iInitNum, sizeof(m_iNV_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I));
	memset(&m_uiNV_WCDMA_IM2_I_VALUE_I, iInitNum, sizeof(m_uiNV_WCDMA_IM2_I_VALUE_I));
	memset(&m_uiNV_WCDMA_IM2_Q_VALUE_I, iInitNum, sizeof(m_uiNV_WCDMA_IM2_Q_VALUE_I));
	memset(&m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, iInitNum, sizeof(m_uiNV_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I));
 
	memset(&m_uiNV_WCDMA_LNA_OFFSET_I, iInitNum, sizeof(m_uiNV_WCDMA_LNA_OFFSET_I));
	memset(&m_uiNV_WCDMA_LNA_OFFSET_2_I, iInitNum, sizeof(m_uiNV_WCDMA_LNA_OFFSET_2_I));
	memset(&m_uiNV_WCDMA_LNA_OFFSET_3_I, iInitNum, sizeof(m_uiNV_WCDMA_LNA_OFFSET_3_I));
	memset(&m_uiNV_WCDMA_LNA_OFFSET_4_I, iInitNum, sizeof(m_uiNV_WCDMA_LNA_OFFSET_4_I));
	memset(&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I, iInitNum, sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_I));
	memset(&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I, iInitNum, sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_2_I));
	memset(&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I, iInitNum, sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_3_I));
	memset(&m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I,iInitNum, sizeof(m_iNV_WCDMA_LNA_OFFSET_VS_FREQ_4_I));
 
	//WCDMA Tx NV Items
	memset(&m_uiNV_WCDMA_TX_LIN_MASTER_0_I, iInitNum, sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_0_I));
	memset(&m_uiNV_WCDMA_TX_LIN_MASTER_1_I, iInitNum, sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_1_I));
	memset(&m_uiNV_WCDMA_TX_LIN_MASTER_2_I, iInitNum, sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_2_I));
	memset(&m_uiNV_WCDMA_TX_LIN_MASTER_3_I, iInitNum, sizeof(m_uiNV_WCDMA_TX_LIN_MASTER_3_I));
 
	memset(&m_uiNV_WCDMA_TX_PDM_0_I, iInitNum, sizeof(m_uiNV_WCDMA_TX_PDM_0_I));
	memset(&m_uiNV_WCDMA_TX_PDM_1_I, iInitNum, sizeof(m_uiNV_WCDMA_TX_PDM_1_I));
	memset(&m_uiNV_WCDMA_TX_PDM_2_I, iInitNum, sizeof(m_uiNV_WCDMA_TX_PDM_2_I));
	memset(&m_uiNV_WCDMA_TX_PDM_3_I, iInitNum, sizeof(m_uiNV_WCDMA_TX_PDM_3_I));
 
	memset(&m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I, iInitNum, sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_0_I));
	memset(&m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I, iInitNum, sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_1_I));
	memset(&m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I, iInitNum, sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_2_I));
	memset(&m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I, iInitNum, sizeof(m_iNV_WCDMA_TX_COMP_VS_FREQ_3_I));
 
	memset(&m_iNV_WCDMA_LIM_VS_FREQ_I, iInitNum, sizeof(m_iNV_WCDMA_LIM_VS_FREQ_I));
 
	memset(&m_uiNV_WCDMA_EXP_HDET_VS_AGC_I, iInitNum, sizeof(m_uiNV_WCDMA_EXP_HDET_VS_AGC_I));
	memset(&m_uiNV_WCDMA_HDET_OFF_I, iInitNum, sizeof(m_uiNV_WCDMA_HDET_OFF_I));
	memset(&m_uiNV_WCDMA_HDET_OFF_I, iInitNum, sizeof(m_uiNV_WCDMA_HDET_OFF_I));
 
	memset(&m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I, iInitNum, sizeof(m_iNv_WCDMA_TX_COMP_VS_FREQ_0_SECONDARY_I));
 
	//WCDMA Rx Diversity Path
	memset(&m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I, iInitNum, sizeof(m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_I));
	memset(&m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I, iInitNum, sizeof(m_iNV_C1_WCDMA_VGA_GAIN_OFFSET_VS_FREQ_I));
 
	memset(&m_uiNV_C1_WCDMA_LNA_OFFSET_I, iInitNum, sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_I));
	memset(&m_uiNV_C1_WCDMA_LNA_OFFSET_2_I, iInitNum, sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_2_I));
	memset(&m_uiNV_C1_WCDMA_LNA_OFFSET_3_I, iInitNum, sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_3_I));
	memset(&m_uiNV_C1_WCDMA_LNA_OFFSET_4_I, iInitNum, sizeof(m_uiNV_C1_WCDMA_LNA_OFFSET_4_I));
	memset(&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I, iInitNum, sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_I));
	memset(&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I, iInitNum, sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_2_I));
	memset(&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I, iInitNum, sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_3_I));
	memset(&m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I, iInitNum, sizeof(m_iNV_C1_WCDMA_LNA_OFFSET_VS_FREQ_4_I));
	memset(&m_uiNV_C1_WCDMA_IM2_I_VALUE_I, iInitNum, sizeof(m_uiNV_C1_WCDMA_IM2_I_VALUE_I));
	memset(&m_uiNV_C1_WCDMA_IM2_Q_VALUE_I, iInitNum, sizeof(m_uiNV_C1_WCDMA_IM2_Q_VALUE_I));
	memset(&m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I, iInitNum, sizeof(m_uiNV_C1_WCDMA_IM2_TRANSCONDUCTOR_VALUE_I));
 
 
 
	//RX Compensation NV Items
	memset(&m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP, iInitNum, sizeof(m_iNV_GSM_RX_GAIN_RANGE_1_FREQ_COMP));
	memset(&m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP, iInitNum, sizeof(m_iNV_GSM_RX_GAIN_RANGE_2_FREQ_COMP));
	memset(&m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP, iInitNum, sizeof(m_iNV_GSM_RX_GAIN_RANGE_3_FREQ_COMP));
	memset(&m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP, iInitNum, sizeof(m_iNV_GSM_RX_GAIN_RANGE_4_FREQ_COMP));
	memset(&m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP, iInitNum, sizeof(m_iNV_GSM_RX_GAIN_RANGE_5_FREQ_COMP));
 
 
	//Tx Polar NV Items
	memset(&m_uiNV_GSM_AMAM_MASTER_TBL_F1, iInitNum, sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F1));
	memset(&m_uiNV_GSM_AMAM_MASTER_TBL_F2, iInitNum, sizeof(m_uiNV_GSM_AMAM_MASTER_TBL_F2));
 
	memset(&m_iNV_GSM_AMPM_MASTER_TBL_F1, iInitNum, sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F1));
	memset(&m_iNV_GSM_AMPM_MASTER_TBL_F2, iInitNum, sizeof(m_iNV_GSM_AMPM_MASTER_TBL_F2));
 
	//Timing Delay search
	memset(&m_uiNV_GSM_POLAR_PATH_DELAY, iInitNum, sizeof(m_uiNV_GSM_POLAR_PATH_DELAY));
 
	//Therm cal, first is max
	memset(&m_iNV_THERM_MAX_MIN, iInitNum, sizeof(m_iNV_THERM_MAX_MIN));
 
	//Tx CS NV Items
	memset(&m_uiNV_IDC_QDC, iInitNum, sizeof(m_uiNV_IDC_QDC));
 
	//PA_DAC_Search
	memset(&m_uiNV_VCO_Default, iInitNum, sizeof(m_uiNV_VCO_Default));
	memset(&m_uiNV_VCO_Default, iInitNum, sizeof(m_uiNV_VCO_Default));
 
}

void CRFNVItems::InitCDMAVariable() // Not include Rx intelliceiver NV
{
	const int iInitNum = 0;

	//CDMA Tx NV Items
	memset(&m_iNV_CDMA_TX_LIN_MASTER_0_I, iInitNum, sizeof(m_iNV_CDMA_TX_LIN_MASTER_0_I));
	memset(&m_iNV_CDMA_TX_LIN_MASTER_1_I, iInitNum, sizeof(m_iNV_CDMA_TX_LIN_MASTER_1_I));
	memset(&m_iNV_CDMA_TX_LIN_MASTER_2_I, iInitNum, sizeof(m_iNV_CDMA_TX_LIN_MASTER_2_I));
	memset(&m_iNV_CDMA_TX_LIN_MASTER_3_I, iInitNum, sizeof(m_iNV_CDMA_TX_LIN_MASTER_3_I));

	memset(&m_iNV_CDMA_TX_PDM_0_I, iInitNum, sizeof(m_iNV_CDMA_TX_PDM_0_I));
	memset(&m_iNV_CDMA_TX_PDM_1_I, iInitNum, sizeof(m_iNV_CDMA_TX_PDM_1_I));
	memset(&m_iNV_CDMA_TX_PDM_2_I, iInitNum, sizeof(m_iNV_CDMA_TX_PDM_2_I));
	memset(&m_iNV_CDMA_TX_PDM_3_I, iInitNum, sizeof(m_iNV_CDMA_TX_PDM_3_I));

	memset(&m_uiNV_CDMA_EXP_HDET_VS_AGC_I, iInitNum, sizeof(m_uiNV_CDMA_EXP_HDET_VS_AGC_I));
	memset(&m_uiNV_CDMA_HDET_OFF_I, iInitNum, sizeof(m_uiNV_CDMA_HDET_OFF_I));
	memset(&m_uiNV_CDMA_HDET_SPN_I, iInitNum, sizeof(m_uiNV_CDMA_HDET_SPN_I));

	memset(&m_iNV_CDMA_TX_COMP_0_I, iInitNum, sizeof(m_iNV_CDMA_TX_COMP_0_I));
	memset(&m_iNV_CDMA_TX_COMP_1_I, iInitNum, sizeof(m_iNV_CDMA_TX_COMP_1_I));
	memset(&m_iNV_CDMA_TX_COMP_2_I, iInitNum, sizeof(m_iNV_CDMA_TX_COMP_2_I));
	memset(&m_iNV_CDMA_TX_COMP_3_I, iInitNum, sizeof(m_iNV_CDMA_TX_COMP_3_I));

	memset(&m_iNV_CDMA_LIM_VS_FREQ_I, iInitNum, sizeof(m_iNV_CDMA_LIM_VS_FREQ_I));

	memset(&m_uiNV_CDMA_TX_CAL_CHAN, iInitNum, sizeof(m_uiNV_CDMA_TX_CAL_CHAN));

	//CDMA Rx NV Items
	memset(&m_iNV_CDMA_VGA_GAIN_OFFSET_I, iInitNum, sizeof(m_iNV_CDMA_VGA_GAIN_OFFSET_I));
	memset(&m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I, iInitNum, sizeof(m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I));

	memset(&m_iNV_CDMA_LNA_OFFSET_I, iInitNum, sizeof(m_iNV_CDMA_LNA_OFFSET_I));
	memset(&m_iNV_CDMA_LNA_OFFSET_2_I, iInitNum, sizeof(m_iNV_CDMA_LNA_OFFSET_2_I));
	memset(&m_iNV_CDMA_LNA_OFFSET_3_I, iInitNum, sizeof(m_iNV_CDMA_LNA_OFFSET_3_I));
	memset(&m_iNV_CDMA_LNA_OFFSET_4_I, iInitNum, sizeof(m_iNV_CDMA_LNA_OFFSET_4_I));

	memset(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I, iInitNum, sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I));
	memset(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I, iInitNum, sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I));
	memset(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I, iInitNum, sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I));
	memset(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I, iInitNum, sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I));

	memset(&m_uiNV_CDMA_RX_CAL_CHAN, iInitNum, sizeof(m_uiNV_CDMA_RX_CAL_CHAN));

	//CDMA Rx Diversity Path
	memset(&m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I, iInitNum, sizeof(m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I));
	memset(&m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I, iInitNum, sizeof(m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I));

	memset(&m_iNV_C1_CDMA_LNA_OFFSET_I, iInitNum, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_I));
	memset(&m_iNV_C1_CDMA_LNA_OFFSET_2_I, iInitNum, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_2_I));
	memset(&m_iNV_C1_CDMA_LNA_OFFSET_3_I, iInitNum, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_3_I));
	memset(&m_iNV_C1_CDMA_LNA_OFFSET_4_I, iInitNum, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_4_I));

	memset(&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I, iInitNum, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I));
	memset(&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I, iInitNum, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I));
	memset(&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I, iInitNum, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I));
	memset(&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I, iInitNum, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I));

	//Re-initial TX PDM and LIN
	m_iNV_CDMA_TX_LIN_MASTER_0_I[0] = -32768;
	m_iNV_CDMA_TX_LIN_MASTER_1_I[0] = -32768;
	m_iNV_CDMA_TX_LIN_MASTER_2_I[0] = -32768;
	m_iNV_CDMA_TX_LIN_MASTER_3_I[0] = -32768;

	m_iNV_CDMA_TX_PDM_0_I[0] = 32767;
	m_iNV_CDMA_TX_PDM_1_I[0] = 32767;
	m_iNV_CDMA_TX_PDM_2_I[0] = 32767;
	m_iNV_CDMA_TX_PDM_3_I[0] = 32767;
}
void CRFNVItems::InitRX_Intelliceiver_Variable()
{
	const int iInitNum = 0;

	memset(&m_uiNV_CDMA_INTELLICEIVER_CAL, iInitNum, sizeof(m_uiNV_CDMA_INTELLICEIVER_CAL));
}

// CDMA NV Items Operation
bool CRFNVItems::Set_NV_CDMA_TX_LIN_MASTER(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	switch(iPARangeNVIndex)
	{
	case 0:
		memcpy(&m_iNV_CDMA_TX_LIN_MASTER_0_I[stIndex], pByte, stSize);
		break;
	case 1:
		memcpy(&m_iNV_CDMA_TX_LIN_MASTER_1_I[stIndex], pByte, stSize);
		break;
	case 2:
		memcpy(&m_iNV_CDMA_TX_LIN_MASTER_2_I[stIndex], pByte, stSize);
		break;
	case 3:
		memcpy(&m_iNV_CDMA_TX_LIN_MASTER_3_I[stIndex], pByte, stSize);
		break;
	}
	return true;

}

bool CRFNVItems::Get_NV_CDMA_TX_LIN_MASTER(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t& stSize)
{
	switch(iPARangeNVIndex)
	{
	case 0:
		stSize = sizeof(m_iNV_CDMA_TX_LIN_MASTER_0_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_TX_LIN_MASTER_0_I[stIndex], stSize);
		break;
	case 1:
		stSize = sizeof(m_iNV_CDMA_TX_LIN_MASTER_1_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_TX_LIN_MASTER_1_I[stIndex], stSize);
		break;
	case 2:
		stSize = sizeof(m_iNV_CDMA_TX_LIN_MASTER_2_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_TX_LIN_MASTER_2_I[stIndex], stSize);
		break;
	case 3:
		stSize = sizeof(m_iNV_CDMA_TX_LIN_MASTER_3_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_TX_LIN_MASTER_3_I[stIndex], stSize);
		break;
	}
	return true;
}

bool CRFNVItems::Set_NV_CDMA_TX_PDM(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	switch(iPARangeNVIndex)
	{
	case 0:
		memcpy(&m_iNV_CDMA_TX_PDM_0_I[stIndex], pByte, stSize);
		break;
	case 1:
		memcpy(&m_iNV_CDMA_TX_PDM_1_I[stIndex], pByte, stSize);
		break;
	case 2:
		memcpy(&m_iNV_CDMA_TX_PDM_2_I[stIndex], pByte, stSize);
		break;
	case 3:
		memcpy(&m_iNV_CDMA_TX_PDM_3_I[stIndex], pByte, stSize);
		break;
	}
	return true;

}

bool CRFNVItems::Write_NV_CDMA_TX_LIN_MASTER_0_I(int iBandID)
{
	DWORD dwNVItemID_LIN_MASTER = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_BC0_TX_LIN_0_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_BC1_TX_LIN_0_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIN_MASTER, (unsigned char* )&m_iNV_CDMA_TX_LIN_MASTER_0_I, sizeof(m_iNV_CDMA_TX_LIN_MASTER_0_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_LIN_MASTER_1_I(int iBandID)
{
	DWORD dwNVItemID_LIN_MASTER = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_BC0_TX_LIN_1_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_BC1_TX_LIN_1_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIN_MASTER, (unsigned char* )&m_iNV_CDMA_TX_LIN_MASTER_1_I, sizeof(m_iNV_CDMA_TX_LIN_MASTER_1_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_LIN_MASTER_2_I(int iBandID)
{
	DWORD dwNVItemID_LIN_MASTER = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_BC0_TX_LIN_2_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_BC1_TX_LIN_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIN_MASTER, (unsigned char* )&m_iNV_CDMA_TX_LIN_MASTER_2_I, sizeof(m_iNV_CDMA_TX_LIN_MASTER_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_LIN_MASTER_3_I(int iBandID)
{
	DWORD dwNVItemID_LIN_MASTER = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_BC0_TX_LIN_3_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LIN_MASTER = NV_BC1_TX_LIN_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIN_MASTER, (unsigned char* )&m_iNV_CDMA_TX_LIN_MASTER_3_I, sizeof(m_iNV_CDMA_TX_LIN_MASTER_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Write_NV_CDMA_TX_PDM_0_I(int iBandID)
{
	DWORD dwNVItemID_TX_PDM = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_TX_PDM = NV_BC0_TX_PDM_0_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_TX_PDM = NV_BC1_TX_PDM_0_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_PDM, (unsigned char* )&m_iNV_CDMA_TX_PDM_0_I, sizeof(m_iNV_CDMA_TX_PDM_0_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_PDM_1_I(int iBandID)
{
	DWORD dwNVItemID_TX_PDM = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_TX_PDM = NV_BC0_TX_PDM_1_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_TX_PDM = NV_BC1_TX_PDM_1_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_PDM, (unsigned char* )&m_iNV_CDMA_TX_PDM_1_I, sizeof(m_iNV_CDMA_TX_PDM_1_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_PDM_2_I(int iBandID)
{
	DWORD dwNVItemID_TX_PDM = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_TX_PDM = NV_BC0_TX_PDM_2_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_TX_PDM = NV_BC1_TX_PDM_2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_PDM, (unsigned char* )&m_iNV_CDMA_TX_PDM_2_I, sizeof(m_iNV_CDMA_TX_PDM_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_PDM_3_I(int iBandID)
{
	DWORD dwNVItemID_TX_PDM = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_TX_PDM = NV_BC0_TX_PDM_3_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_TX_PDM = NV_BC1_TX_PDM_3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_PDM, (unsigned char* )&m_iNV_CDMA_TX_PDM_3_I, sizeof(m_iNV_CDMA_TX_PDM_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_CDMA_HDET_OFF_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_CDMA_HDET_OFF_I);
	memcpy(pByte, &m_uiNV_CDMA_HDET_OFF_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_HDET_OFF_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_CDMA_HDET_OFF_I));
	memcpy(&m_uiNV_CDMA_HDET_OFF_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_HDET_OFF_I(int iBandID)
{
	DWORD dwNV_CDMA_HDET_OFF = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_CDMA_HDET_OFF = NV_BC0_HDET_OFF_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_CDMA_HDET_OFF = NV_BC1_HDET_OFF_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_CDMA_HDET_OFF, (unsigned char* )&m_uiNV_CDMA_HDET_OFF_I, sizeof(m_uiNV_CDMA_HDET_OFF_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_HDET_SPN_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_uiNV_CDMA_HDET_SPN_I);
	memcpy(pByte, &m_uiNV_CDMA_HDET_SPN_I, stSize);
	return true;
}

bool CRFNVItems::Set_NV_CDMA_HDET_SPN_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_uiNV_CDMA_HDET_SPN_I));
	memcpy(&m_uiNV_CDMA_HDET_SPN_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_HDET_SPN_I(int iBandID)
{
	DWORD dwNV_CDMA_HDET_SPN = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_CDMA_HDET_SPN = NV_BC0_HDET_SPN_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_CDMA_HDET_SPN = NV_BC1_HDET_SPN_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_CDMA_HDET_SPN, (unsigned char* )&m_uiNV_CDMA_HDET_SPN_I, sizeof(m_uiNV_CDMA_HDET_SPN_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_EXP_HDET_VS_AGC_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_CDMA_EXP_HDET_VS_AGC_I[stIndex]);
	memcpy(pByte, &m_uiNV_CDMA_EXP_HDET_VS_AGC_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_EXP_HDET_VS_AGC_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_CDMA_EXP_HDET_VS_AGC_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_CDMA_EXP_HDET_VS_AGC_I[stIndex], pByte, stSize);
	return true;

}
bool CRFNVItems::Write_NV_CDMA_EXP_HDET_VS_AGC_I(int iBandID)
{
	DWORD dwNVItemID_HDET_AGC = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_HDET_AGC = NV_BC0_EXP_HDET_VS_AGC_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_HDET_AGC = NV_BC1_EXP_HDET_VS_AGC_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_HDET_AGC, (unsigned char* )&m_uiNV_CDMA_EXP_HDET_VS_AGC_I, sizeof(m_uiNV_CDMA_EXP_HDET_VS_AGC_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_TX_COMP_VS_FREQ(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t& stSize)
{
	switch(iPARangeNVIndex)
	{
	case 0:
		stSize = sizeof(m_iNV_CDMA_TX_COMP_0_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_TX_COMP_0_I[stIndex], stSize);
		break;
	case 1:
		stSize = sizeof(m_iNV_CDMA_TX_COMP_1_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_TX_COMP_1_I[stIndex], stSize);
		break;
	case 2:
		stSize = sizeof(m_iNV_CDMA_TX_COMP_2_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_TX_COMP_2_I[stIndex], stSize);
		break;
	case 3:
		stSize = sizeof(m_iNV_CDMA_TX_COMP_3_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_TX_COMP_3_I[stIndex], stSize);
		break;
	}
	return true;
}
bool CRFNVItems::Set_NV_CDMA_TX_COMP_VS_FREQ(int iPARangeNVIndex, PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	switch(iPARangeNVIndex)
	{
	case 0:
		stTemp %= sizeof(m_iNV_CDMA_TX_COMP_0_I[0]);
		ASSERT(stTemp == 0);
		memcpy(&m_iNV_CDMA_TX_COMP_0_I[stIndex], pByte, stSize);
		break;
	case 1:
		stTemp %= sizeof(m_iNV_CDMA_TX_COMP_1_I[0]);
		ASSERT(stTemp == 0);
		memcpy(&m_iNV_CDMA_TX_COMP_1_I[stIndex], pByte, stSize);
		break;
	case 2:
		stTemp %= sizeof(m_iNV_CDMA_TX_COMP_2_I[0]);
		ASSERT(stTemp == 0);
		memcpy(&m_iNV_CDMA_TX_COMP_2_I[stIndex], pByte, stSize);
		break;
	case 3:
		stTemp %= sizeof(m_iNV_CDMA_TX_COMP_3_I[0]);
		ASSERT(stTemp == 0);
		memcpy(&m_iNV_CDMA_TX_COMP_3_I[stIndex], pByte, stSize);
		break;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_LIM_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_LIM_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_CDMA_LIM_VS_FREQ_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_LIM_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_CDMA_LIM_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_CDMA_LIM_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_COMP_VS_FREQ_0_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP= 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_TX_COMP = NV_BC0_TX_COMP0_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_TX_COMP = NV_BC1_TX_COMP0_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP, (unsigned char* )&m_iNV_CDMA_TX_COMP_0_I, sizeof(m_iNV_CDMA_TX_COMP_0_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_COMP_VS_FREQ_1_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP= 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_TX_COMP = NV_BC0_TX_COMP1_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_TX_COMP = NV_BC1_TX_COMP1_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP, (unsigned char* )&m_iNV_CDMA_TX_COMP_1_I, sizeof(m_iNV_CDMA_TX_COMP_1_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_COMP_VS_FREQ_2_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP= 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_TX_COMP = NV_BC0_TX_COMP2_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_TX_COMP = NV_BC1_TX_COMP2_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP, (unsigned char* )&m_iNV_CDMA_TX_COMP_2_I, sizeof(m_iNV_CDMA_TX_COMP_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX_COMP_VS_FREQ_3_I(int iBandID)
{
	DWORD dwNVItemID_TX_COMP= 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_TX_COMP = NV_BC0_TX_COMP3_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_TX_COMP = NV_BC1_TX_COMP3_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_TX_COMP, (unsigned char* )&m_iNV_CDMA_TX_COMP_3_I, sizeof(m_iNV_CDMA_TX_COMP_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_LIM_VS_FREQ_I(int iBandID)
{
	DWORD dwNVItemID_LIM_FREQ = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LIM_FREQ = NV_BC0_TX_LIM_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LIM_FREQ = NV_BC1_TX_LIM_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LIM_FREQ, (unsigned char* )&m_iNV_CDMA_LIM_VS_FREQ_I, sizeof(m_iNV_CDMA_LIM_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

//CDMA RX Primary path
bool CRFNVItems::Get_NV_CDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_VGA_GAIN_OFFSET_I);
	memcpy(pByte, &m_iNV_CDMA_VGA_GAIN_OFFSET_I, stSize);
	return true;
}

bool CRFNVItems::Set_NV_CDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_CDMA_VGA_GAIN_OFFSET_I));
	memcpy(&m_iNV_CDMA_VGA_GAIN_OFFSET_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_VGA_GAIN_OFFSET_I(int iBandID)
{
	DWORD dwNVItemID_DVGA_Offset = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_C0_BC0_VGA_GAIN_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_C0_BC1_VGA_GAIN_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_DVGA_Offset, (unsigned char* )&m_iNV_CDMA_VGA_GAIN_OFFSET_I, sizeof(m_iNV_CDMA_VGA_GAIN_OFFSET_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex,  size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(int iBandID)
{
	DWORD dwNVItemID_DVGA_Offset = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_C0_BC0_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_DVGA_Offset = NV_C0_BC1_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_DVGA_Offset, (unsigned char* )&m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I, sizeof(m_iNV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_LNA_OFFSET_I(int iRxLNARange, PBYTE pByte, size_t& stSize)
{
	switch(iRxLNARange)
	{
	case 0:
		stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_I);
		memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_I, stSize);
		break;
	case 1:
		stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_2_I);
		memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_2_I, stSize);
		break;
	case 2:
		stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_3_I);
		memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_3_I, stSize);
		break;
	case 3:
		stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_4_I);
		memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_4_I, stSize);
		break;
	}
	return true;
}

bool CRFNVItems::Set_NV_CDMA_LNA_OFFSET_I(int iRxLNARange, PBYTE pByte, size_t stSize)
{
	switch(iRxLNARange)
	{
	case 0:
		ASSERT(stSize == sizeof(m_iNV_CDMA_LNA_OFFSET_I));
		memcpy(&m_iNV_CDMA_LNA_OFFSET_I, pByte, stSize);
		break;
	case 1:
		ASSERT(stSize == sizeof(m_iNV_CDMA_LNA_OFFSET_2_I));
		memcpy(&m_iNV_CDMA_LNA_OFFSET_2_I, pByte, stSize);
		break;
	case 2:
		ASSERT(stSize == sizeof(m_iNV_CDMA_LNA_OFFSET_3_I));
		memcpy(&m_iNV_CDMA_LNA_OFFSET_3_I, pByte, stSize);
		break;
	case 3:
		ASSERT(stSize == sizeof(m_iNV_CDMA_LNA_OFFSET_4_I));
		memcpy(&m_iNV_CDMA_LNA_OFFSET_4_I, pByte, stSize);
		break;
	}
	return true;
}

bool CRFNVItems::Write_NV_CDMA_LNA_OFFSET_I(int iBandID)
{
	DWORD dwNV_CDMA_LNA_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_CDMA_LNA_OFFSET= NV_C0_BC0_LNA_1_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_CDMA_LNA_OFFSET = NV_C0_BC1_LNA_1_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_CDMA_LNA_OFFSET, (unsigned char* )&m_iNV_CDMA_LNA_OFFSET_I, sizeof(m_iNV_CDMA_LNA_OFFSET_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;

}

bool CRFNVItems::Get_NV_CDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_2_I);
	memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_2_I, stSize);
	return true;

}

bool CRFNVItems::Set_NV_CDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_CDMA_LNA_OFFSET_2_I));
	memcpy(&m_iNV_CDMA_LNA_OFFSET_2_I, pByte, stSize);
	return true;
}

bool CRFNVItems::Write_NV_CDMA_LNA_OFFSET_2_I(int iBandID)
{
	DWORD dwNV_CDMA_LNA_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_CDMA_LNA_OFFSET= NV_C0_BC0_LNA_2_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_CDMA_LNA_OFFSET = NV_C0_BC1_LNA_2_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_CDMA_LNA_OFFSET, (unsigned char* )&m_iNV_CDMA_LNA_OFFSET_2_I, sizeof(m_iNV_CDMA_LNA_OFFSET_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_CDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_3_I);
	memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_3_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_CDMA_LNA_OFFSET_3_I));
	memcpy(&m_iNV_CDMA_LNA_OFFSET_3_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_LNA_OFFSET_3_I(int iBandID)
{
	DWORD dwNV_CDMA_LNA_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_CDMA_LNA_OFFSET= NV_C0_BC0_LNA_3_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_CDMA_LNA_OFFSET = NV_C0_BC1_LNA_3_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_CDMA_LNA_OFFSET, (unsigned char* )&m_iNV_CDMA_LNA_OFFSET_3_I, sizeof(m_iNV_CDMA_LNA_OFFSET_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_CDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_4_I);
	memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_4_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_CDMA_LNA_OFFSET_4_I));
	memcpy(&m_iNV_CDMA_LNA_OFFSET_4_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_LNA_OFFSET_4_I(int iBandID)
{
	DWORD dwNV_CDMA_LNA_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_CDMA_LNA_OFFSET= NV_C0_BC0_LNA_4_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_CDMA_LNA_OFFSET = NV_C0_BC1_LNA_4_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_CDMA_LNA_OFFSET, (unsigned char* )&m_iNV_CDMA_LNA_OFFSET_4_I, sizeof(m_iNV_CDMA_LNA_OFFSET_4_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_LNA_OFFSET_VS_FREQ_I(int iRxLNARange, PBYTE pByte, size_t stIndex, size_t& stSize)
{
	switch(iRxLNARange)
	{
	case 0:	
		stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I[stIndex], stSize);
		break;
	case 1:
		stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], stSize);
		break;
	case 2:
		stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], stSize);
		break;
	case 3:
		stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex]);
		memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], stSize);
		break;
	}
	return true;
}
bool CRFNVItems::Set_NV_CDMA_LNA_OFFSET_VS_FREQ_I(int iRxLNARange, PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	
	switch(iRxLNARange)
	{
	case 0:	
		stTemp %= sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I[0]);
		ASSERT(stTemp == 0);
		memcpy(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I[stIndex], pByte, stSize);
		break;
	case 1:
		stTemp %= sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[0]);
		ASSERT(stTemp == 0);
		memcpy(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], pByte, stSize);
		break;
	case 2:
		stTemp %= sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[0]);
		ASSERT(stTemp == 0);
		memcpy(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], pByte, stSize);
		break;
	case 3:
		stTemp %= sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[0]);
		ASSERT(stTemp == 0);
		memcpy(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], pByte, stSize);
		break;
	}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_LNA_OFFSET_VS_FREQ_I(int iBandID)
{
	DWORD dwNVItemID_LNA_Offset = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LNA_Offset = NV_C0_BC0_LNA_1_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LNA_Offset = NV_C0_BC1_LNA_1_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LNA_Offset, (unsigned char* )&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I, sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte,size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex]);
	memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte,size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_LNA_OFFSET_VS_FREQ_2_I(int iBandID)
{
	DWORD dwNVItemID_LNA_Offset = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LNA_Offset = NV_C0_BC0_LNA_2_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LNA_Offset = NV_C0_BC1_LNA_2_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LNA_Offset, (unsigned char* )&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I, sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex]);
	memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], stSize);
	return true;

}
bool CRFNVItems::Set_NV_CDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_LNA_OFFSET_VS_FREQ_3_I(int iBandID)
{
	DWORD dwNVItemID_LNA_Offset = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LNA_Offset = NV_C0_BC0_LNA_3_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LNA_Offset = NV_C0_BC1_LNA_3_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LNA_Offset, (unsigned char* )&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I, sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex]);
	memcpy(pByte, &m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], stSize);
	return true;

}
bool CRFNVItems::Set_NV_CDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], pByte, stSize);
	return true;

}
bool CRFNVItems::Write_NV_CDMA_LNA_OFFSET_VS_FREQ_4_I(int iBandID)
{
	DWORD dwNVItemID_LNA_Offset = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_LNA_Offset = NV_C0_BC0_LNA_4_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_LNA_Offset = NV_C0_BC1_LNA_4_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_LNA_Offset, (unsigned char* )&m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I, sizeof(m_iNV_CDMA_LNA_OFFSET_VS_FREQ_4_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
//CDMA Rx Diversity Path
bool CRFNVItems::Get_NV_C1_CDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I);
	memcpy(pByte, &m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I, stSize);
	return true;
}

bool CRFNVItems::Set_NV_C1_CDMA_VGA_GAIN_OFFSET_I(PBYTE pByte, size_t stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I);
	memcpy(pByte, &m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I, stSize);
	return true;
}

bool CRFNVItems::Write_NV_C1_CDMA_VGA_GAIN_OFFSET_I(int iBandID)
{
	DWORD dwNV_C1_VGA_GAIN_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET= NV_C1_BC0_VGA_GAIN_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET = NV_C1_BC1_VGA_GAIN_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_VGA_GAIN_OFFSET, (unsigned char* )&m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I, sizeof(m_iNV_C1_CDMA_VGA_GAIN_OFFSET_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex], stSize);
	return true;
}

bool CRFNVItems::Set_NV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
}

bool CRFNVItems::Write_NV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(int iBandID)
{
	DWORD dwNV_C1_VGA_GAIN_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET= NV_C1_BC0_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_VGA_GAIN_OFFSET = NV_C1_BC1_VGA_GAIN_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_VGA_GAIN_OFFSET, (unsigned char* )&m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I, sizeof(m_iNV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_CDMA_LNA_OFFSET_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_LNA_OFFSET_I);
	memcpy(pByte, &m_iNV_C1_CDMA_LNA_OFFSET_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_CDMA_LNA_OFFSET_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_C1_CDMA_LNA_OFFSET_I));
	memcpy(&m_iNV_C1_CDMA_LNA_OFFSET_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_CDMA_LNA_OFFSET_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_LNA_OFFSET= NV_C1_BC0_LNA_1_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_BC1_LNA_1_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET, (unsigned char* )&m_iNV_C1_CDMA_LNA_OFFSET_I, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_C1_CDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_LNA_OFFSET_2_I);
	memcpy(pByte, &m_iNV_C1_CDMA_LNA_OFFSET_2_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_CDMA_LNA_OFFSET_2_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_C1_CDMA_LNA_OFFSET_2_I));
	memcpy(&m_iNV_C1_CDMA_LNA_OFFSET_2_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_CDMA_LNA_OFFSET_2_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_LNA_OFFSET= NV_C1_BC0_LNA_2_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_BC1_LNA_2_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET, (unsigned char* )&m_iNV_C1_CDMA_LNA_OFFSET_2_I, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_CDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_LNA_OFFSET_3_I);
	memcpy(pByte, &m_iNV_C1_CDMA_LNA_OFFSET_3_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_CDMA_LNA_OFFSET_3_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_C1_CDMA_LNA_OFFSET_3_I));
	memcpy(&m_iNV_C1_CDMA_LNA_OFFSET_3_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_CDMA_LNA_OFFSET_3_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_LNA_OFFSET= NV_C1_BC0_LNA_3_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_BC1_LNA_3_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET, (unsigned char* )&m_iNV_C1_CDMA_LNA_OFFSET_3_I, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_C1_CDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_LNA_OFFSET_4_I);
	memcpy(pByte, &m_iNV_C1_CDMA_LNA_OFFSET_4_I, stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_CDMA_LNA_OFFSET_4_I(PBYTE pByte, size_t stSize)
{
	ASSERT(stSize == sizeof(m_iNV_C1_CDMA_LNA_OFFSET_4_I));
	memcpy(&m_iNV_C1_CDMA_LNA_OFFSET_4_I, pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_CDMA_LNA_OFFSET_4_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_LNA_OFFSET= NV_C1_BC0_LNA_4_OFFSET_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_LNA_OFFSET = NV_C1_BC1_LNA_4_OFFSET_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET, (unsigned char* )&m_iNV_C1_CDMA_LNA_OFFSET_4_I, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_4_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET_VS_FREQ = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ= NV_C1_BC0_LNA_1_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_BC1_LNA_1_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET_VS_FREQ, (unsigned char* )&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET_VS_FREQ = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ= NV_C1_BC0_LNA_2_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_BC1_LNA_2_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET_VS_FREQ, (unsigned char* )&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET_VS_FREQ = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ= NV_C1_BC0_LNA_3_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_BC1_LNA_3_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET_VS_FREQ, (unsigned char* )&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}
bool CRFNVItems::Get_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex]);
	memcpy(pByte, &m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I(int iBandID)
{
	DWORD dwNV_C1_LNA_OFFSET_VS_FREQ = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ= NV_C1_BC0_LNA_4_OFFSET_VS_FREQ_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNV_C1_LNA_OFFSET_VS_FREQ = NV_C1_BC1_LNA_4_OFFSET_VS_FREQ_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNV_C1_LNA_OFFSET_VS_FREQ, (unsigned char* )&m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I, sizeof(m_iNV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_INTELLICEIVER_CAL_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_CDMA_INTELLICEIVER_CAL[stIndex]);
	memcpy(pByte, &m_uiNV_CDMA_INTELLICEIVER_CAL[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_INTELLICEIVER_CAL_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_CDMA_INTELLICEIVER_CAL[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_CDMA_INTELLICEIVER_CAL[stIndex], pByte, stSize);
	return true;
}
bool CRFNVItems::Write_NV_CDMA_RXIntelliceiver(int iBandID)
{
	DWORD dwNVItemID_RX_Intelliceiver = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID_RX_Intelliceiver = NV_C0_BC0_INTELLICEIVER_CAL_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID_RX_Intelliceiver = NV_C0_BC1_INTELLICEIVER_CAL_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID_RX_Intelliceiver, (unsigned char* )&m_uiNV_CDMA_INTELLICEIVER_CAL, sizeof(m_uiNV_CDMA_INTELLICEIVER_CAL), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_TX_CAL_CHAN_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_CDMA_TX_CAL_CHAN[stIndex]);
	memcpy(pByte, &m_uiNV_CDMA_TX_CAL_CHAN[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_TX_CAL_CHAN_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_CDMA_TX_CAL_CHAN[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_CDMA_TX_CAL_CHAN[stIndex], pByte, stSize);
	return true;

}
bool CRFNVItems::Write_NV_CDMA_TX_CAL_CHAN_I(int iBandID)
{
	DWORD dwNVItemID = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID = NV_C0_BC0_TX_CAL_CHAN_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID = NV_C0_BC1_TX_CAL_CHAN_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID, (unsigned char* )&m_uiNV_CDMA_TX_CAL_CHAN, sizeof(m_uiNV_CDMA_TX_CAL_CHAN), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Get_NV_CDMA_RX_CAL_CHAN_I(PBYTE pByte, size_t stIndex, size_t& stSize)
{
	stSize = sizeof(m_uiNV_CDMA_RX_CAL_CHAN[stIndex]);
	memcpy(pByte, &m_uiNV_CDMA_RX_CAL_CHAN[stIndex], stSize);
	return true;
}
bool CRFNVItems::Set_NV_CDMA_RX_CAL_CHAN_I(PBYTE pByte, size_t stIndex, size_t stSize)
{
	size_t stTemp = stSize;
	stTemp %= sizeof(m_uiNV_CDMA_RX_CAL_CHAN[0]);
	ASSERT(stTemp == 0);
	memcpy(&m_uiNV_CDMA_RX_CAL_CHAN[stIndex], pByte, stSize);
	return true;

}
bool CRFNVItems::Write_NV_CDMA_RX_CAL_CHAN_I(int iBandID)
{
	DWORD dwNVItemID = 0;
	WORD wStatus = 0;

	switch(iBandID)
	{
	case CDMA_BC0_BAND_ID:
		dwNVItemID = NV_C0_BC0_RX_CAL_CHAN_I;
		break;
	case CDMA_BC1_BAND_ID:
		dwNVItemID = NV_C0_BC1_RX_CAL_CHAN_I;
		break;
	default:
		ASSERT_MSG(false, _T("Wrong Band ID"))
	}
	if(m_pcPhone->WriteRFNVItemInBatchMode(dwNVItemID, (unsigned char* )&m_uiNV_CDMA_RX_CAL_CHAN, sizeof(m_uiNV_CDMA_RX_CAL_CHAN), &wStatus)!=QLIB_FUNCTION_SUCCESSFUL)
	{
		return false;
	}
	return true;
}

bool CRFNVItems::Write_NV_CDMA_RX(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_CDMA_VGA_GAIN_OFFSET_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LNA_OFFSET_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LNA_OFFSET_2_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LNA_OFFSET_3_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LNA_OFFSET_4_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LNA_OFFSET_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LNA_OFFSET_VS_FREQ_2_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LNA_OFFSET_VS_FREQ_3_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LNA_OFFSET_VS_FREQ_4_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_RX_CAL_CHAN_I(iBandID)){return bRet;}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_RX_Diversity(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_C1_CDMA_VGA_GAIN_OFFSET_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_VGA_GAIN_OFFSET_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_LNA_OFFSET_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_LNA_OFFSET_2_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_LNA_OFFSET_3_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_LNA_OFFSET_4_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_2_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_3_I(iBandID)){return bRet;}
	if(!Write_NV_C1_CDMA_LNA_OFFSET_VS_FREQ_4_I(iBandID)){return bRet;}
	return true;
}
bool CRFNVItems::Write_NV_CDMA_TX(int iBandID)
{
	bool bRet = false;
	if(!Write_NV_CDMA_TX_LIN_MASTER_0_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_LIN_MASTER_1_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_LIN_MASTER_2_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_LIN_MASTER_3_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_PDM_0_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_PDM_1_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_PDM_2_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_PDM_3_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_COMP_VS_FREQ_0_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_COMP_VS_FREQ_1_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_COMP_VS_FREQ_2_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_COMP_VS_FREQ_3_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_LIM_VS_FREQ_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_EXP_HDET_VS_AGC_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_HDET_OFF_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_HDET_SPN_I(iBandID)){return bRet;}
	if(!Write_NV_CDMA_TX_CAL_CHAN_I(iBandID)){return bRet;}
	return true;

}



