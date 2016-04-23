
#include "stdafx.h"
#include "CBandInfo.h"
#pragma warning(disable : 4715)
bool CGSMBandInfo::CheckVaildCH(const int iBand, const int iChannel)
{
	if(!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			if (iChannel < 128 || iChannel > 251)
			{return false;}
			else
				return true;
			break;
		case GSM_EGSM_BAND_ID:
			if ((iChannel <= 124 && iChannel >= 0) || (iChannel <= 1023 && iChannel >= 975))
			{return true;}
			else
				return false;
			break;
		case GSM_DCS_BAND_ID:
			if (iChannel < 512 || iChannel > 885)
			{return false;}
			else
				return true;
			break;
		case GSM_PCS_BAND_ID:
			if (iChannel < 512 || iChannel > 810)
			{return false;}
			else
				return true;
		//Have Checked Band, no need default
	}
}

bool CGSMBandInfo::CheckVaildPCL(const int iBand, const int iPcl)
{
	if(!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
	case GSM_850_BAND_ID:
		if (iPcl < 5 || iPcl > 19)
		{return false;}
		else
			return true;
		break;
	case GSM_EGSM_BAND_ID:
		if (iPcl < 5 || iPcl > 19)
		{return false;}
		else
			return true;
		break;
	case GSM_DCS_BAND_ID:
		if (iPcl < 0 || iPcl > 15)
		{return false;}
		else
			return true;
		break;
	case GSM_PCS_BAND_ID:
		if (iPcl < 0 || iPcl > 15)
		{return false;}
		else
			return true;
		//Have Checked Band, no need default
	}
}
 
double CGSMBandInfo::ArfcnToTXHz(const int iBand, const int iArfcnCH)
{
	if(!CheckVaildCH(iBand, iArfcnCH))
		return false;
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			return 824.2+0.2*(iArfcnCH-128);
		case GSM_EGSM_BAND_ID:
			return (iArfcnCH >= 975)?(890 + 0.2 * (iArfcnCH-1024)):(890 + 0.2 * (iArfcnCH));
		case GSM_DCS_BAND_ID:
			return 1710.2 + 0.2 * (iArfcnCH - 512);
		case GSM_PCS_BAND_ID:
			return 1850.2 + 0.2 * (iArfcnCH - 512);
	}
}
double CGSMBandInfo::ArfcnToRXHz(const int iBand, const int iArfcnCH)
{
	if(!CheckVaildCH(iBand, iArfcnCH))
		return false;
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			return 869.2+0.2*(iArfcnCH-128);
		case GSM_EGSM_BAND_ID:
			return (iArfcnCH >= 975)?(935 + 0.2 * (iArfcnCH-1024)):(935 + 0.2 * (iArfcnCH));
		case GSM_DCS_BAND_ID:
			return 1805.2 + 0.2 * (iArfcnCH - 512);
		case GSM_PCS_BAND_ID:
			return 1930.2 + 0.2 * (iArfcnCH - 512);
	}
}
 
int CGSMBandInfo::GetCMU_SigMode(const int iBand){
	if(!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			return _GSM850MS_SIG;
		case GSM_EGSM_BAND_ID:
			return _GSM900MS_SIG;
		case GSM_DCS_BAND_ID:
			return _GSM1800MS_SIG;
		case GSM_PCS_BAND_ID:
			return _GSM1900MS_SIG;
	}
 
}
int CGSMBandInfo::GetCMU_NSigMode(const int iBand){
	if(!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			return _GSM850MS_NSIG;
		case GSM_EGSM_BAND_ID:
			return _GSM900MS_NSIG;
		case GSM_DCS_BAND_ID:
			return _GSM1800MS_NSIG;
		case GSM_PCS_BAND_ID:
			return _GSM1900MS_NSIG;
	}
}
 
 
FTM_RF_Mode_Enum CGSMBandInfo::GetPhoneMode(const int iBand)
{
	CheckVaildBand(iBand);
	
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			return PHONE_MODE_GSM_850;
		case GSM_EGSM_BAND_ID:
			return PHONE_MODE_GSM_900;
		case GSM_DCS_BAND_ID:
			return PHONE_MODE_GSM_1800;
		case GSM_PCS_BAND_ID:
			return PHONE_MODE_GSM_1900;
	}
 
}
FTM_GSM_BER_Band_Enum CGSMBandInfo::GetPhoneTestMode(const int iBand)
{
	CheckVaildBand(iBand);
	
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			return FTM_GSM_BER_CELL_850;
		case GSM_EGSM_BAND_ID:
			return FTM_GSM_BER_EGSM_900;
		case GSM_DCS_BAND_ID:
			return FTM_GSM_BER_DCS_1800;
		case GSM_PCS_BAND_ID:
			return FTM_GSM_BER_PCS_1900;
	}
 
}
int CGSMBandInfo::GetChannelType(const int iBand, const int iChannel)
{
	if(!CheckVaildCH(iBand, iChannel))
		return false;
	switch(iBand)
	{
		case GSM_850_BAND_ID:
			if ( iChannel < 170)
			{ return TYPE_LOW_CH;	}
			else if ( iChannel < 211){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
 
		case GSM_EGSM_BAND_ID:
			if ( iChannel <= 1023 && iChannel >=975)
			{ return TYPE_LOW_CH;	}
			else if ( iChannel <= 62 && iChannel >= 0){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
		case GSM_DCS_BAND_ID:
			if ( iChannel < 637)
			{ return TYPE_LOW_CH;	}
			else if ( iChannel < 762){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
		case GSM_PCS_BAND_ID:
			if ( iChannel < 612)
			{ return TYPE_LOW_CH;	}
			else if ( iChannel < 711){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
	}
 
}

int CGSMBandInfo::GetPclType(const int iBand, const int iPcl)
{
	if(!CheckVaildPCL(iBand, iPcl))
		return false;
	switch(iBand)
	{
	case GSM_850_BAND_ID:
		if ( iPcl > 13)
		{ return TYPE_LOW_PCL;	}
		else if ( iPcl < 9){
			return TYPE_HIGH_PCL;
		}else{
			return TYPE_MIDDLE_PCL;
		}

	case GSM_EGSM_BAND_ID:
		if ( iPcl > 13)
		{ return TYPE_LOW_PCL;	}
		else if ( iPcl < 9){
			return TYPE_HIGH_PCL;
		}else{
			return TYPE_MIDDLE_PCL;
		}

	case GSM_DCS_BAND_ID:
		if ( iPcl > 11)
		{ return TYPE_LOW_PCL;	}
		else if ( iPcl < 7){
			return TYPE_HIGH_PCL;
		}else{
			return TYPE_MIDDLE_PCL;
		}

	case GSM_PCS_BAND_ID:
		if ( iPcl > 11)
		{ return TYPE_LOW_PCL;	}
		else if ( iPcl < 7){
			return TYPE_HIGH_PCL;
		}else{
			return TYPE_MIDDLE_PCL;
		}
	}

}
 
 
bool CWCDMABandInfo::CheckVaildCH(const int iBand, const int iChannel)
{
	if(!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
	case WCDMA_B6_BAND_ID:
		if ((iChannel <= 4413 && iChannel >= 4387) || (iChannel <= 4188 && iChannel >= 4163)||iChannel==1037||iChannel==1062||iChannel==812||iChannel==837)
		{return true;}
		else
			return false;
		break;
	case WCDMA_B19_BAND_ID:
		if ((iChannel <= 363 && iChannel >= 312) || (iChannel <= 763 && iChannel >= 712)||iChannel==387||iChannel==412||iChannel==437||iChannel==787||iChannel==812||iChannel==837)
		{return true;}
		else
			return false;
		break;
	case WCDMA_1800_BAND_ID:
		if ((iChannel <= 1288 && iChannel >= 937) || (iChannel <= 1513 && iChannel >= 1162))
		{return true;}
		else
			return false;
		break;
		
		case WCDMA_850_BAND_ID:
			if ((iChannel <= 4233 && iChannel >= 4132) || (iChannel <= 4458 && iChannel >= 4357)|| (iChannel==1007) || (iChannel==1012) || (iChannel==1032) || (iChannel==1037)||
				(iChannel==1062) || (iChannel==1087) || (iChannel==782) || (iChannel==787) || (iChannel==807) || (iChannel==812)||
				(iChannel==837) || (iChannel==862))
			{return true;}
			else
				return false;
			break;
		case WCDMA_900_BAND_ID:
			if ((iChannel <= 2863 && iChannel >= 2712) || (iChannel <= 3088 && iChannel >= 2937))
			{return true;}
			else
				return false;
			break;
		case WCDMA_1500_BAND_ID:
			if ((iChannel <= 3562 && iChannel >= 3487) || (iChannel <= 3787 && iChannel >= 3712))
			{return true;
			} 
			else
			{return false;
			}
			break;
		case WCDMA_AWS_BAND_ID:
			if ((iChannel <= 1513 && iChannel >= 1312) || (iChannel <= 1738 && iChannel >= 1537))
			{return true;}
			else
				return false;
			break;
		case WCDMA_PCS_BAND_ID:
			if ((iChannel <= 9538 && iChannel >= 9262) || (iChannel <= 9938 && iChannel >= 9662) || (iChannel==412) || (iChannel==437) || (iChannel==462) || (iChannel==487)||
				(iChannel==512) || (iChannel==537) || (iChannel==562) || (iChannel==587)||
				(iChannel==612) || (iChannel==637) || (iChannel==662) || (iChannel==687) || (iChannel== 12) || (iChannel== 37) || (iChannel== 62) || (iChannel== 87)||
				(iChannel==112) || (iChannel==137) || (iChannel==162) || (iChannel==187)||
				(iChannel==212) || (iChannel==237) || (iChannel==262) || (iChannel==287))
			{return true;}
			else
				return false;
			break;
		case WCDMA_IMT_BAND_ID:
			if ((iChannel <= 9888 && iChannel >= 9612) || (iChannel <= 10838 && iChannel >= 10562))
			{return true;}
			else
				return false;
			break;
		case WCDMA_1750_BAND_ID:
			if ((iChannel <= 8912 && iChannel >= 8762) || (iChannel <= 9387 && iChannel >= 9237))
			{return true;}
			else
				return false;
			break;
			//Have Checked Band, no need default
	}
}
 
 
int CWCDMABandInfo::GetDLChannel(const int iBand, const int iULChannel)
{
	if(!CheckVaildCH(iBand, iULChannel))
		return false;
	switch(iBand)
	{
	case WCDMA_B6_BAND_ID:
		return iULChannel+225;
	case WCDMA_B19_BAND_ID:
		return iULChannel+400;
		case WCDMA_1800_BAND_ID:
			return iULChannel+225;
		case WCDMA_850_BAND_ID:
			return iULChannel + 225;
		case WCDMA_900_BAND_ID:
			return iULChannel + 225;
		case WCDMA_1500_BAND_ID:
			return iULChannel + 225;
		case WCDMA_AWS_BAND_ID:
			return iULChannel + 225;
		case WCDMA_PCS_BAND_ID:
			return iULChannel + 400;
		case WCDMA_IMT_BAND_ID:
			return iULChannel + 950;
		case WCDMA_1750_BAND_ID:
			return iULChannel + 475;
	}
 
	
	return 0;
}
int CWCDMABandInfo::GetULChannel(const int iBand, const int iDLChannel)
{
	if(!CheckVaildCH(iBand, iDLChannel))
		return false;
	switch(iBand)
	{
	case WCDMA_B6_BAND_ID:
		return iDLChannel-225;
	case WCDMA_B19_BAND_ID:
		return iDLChannel-400;
	case WCDMA_1800_BAND_ID:
		return iDLChannel - 225;
	case WCDMA_850_BAND_ID:
		return iDLChannel - 225;
	case WCDMA_900_BAND_ID:
		return iDLChannel - 225;
	case WCDMA_1500_BAND_ID:
		return iDLChannel - 225;
	case WCDMA_AWS_BAND_ID:
		return iDLChannel - 225;
	case WCDMA_PCS_BAND_ID:
		return iDLChannel - 400;
	case WCDMA_IMT_BAND_ID:
		return iDLChannel - 950;
	case WCDMA_1750_BAND_ID:
		return iDLChannel - 475;
	}
}
 
double CWCDMABandInfo::ArfcnToHz(const int iBand, const int iArfcnCH,const int isUL)
{
	if(!CheckVaildCH(iBand, iArfcnCH))
		return false;
	switch(iBand)
	{
	case WCDMA_B6_BAND_ID:
		if (1==isUL)
		{
			if (iArfcnCH==812)
			{
				return 832.5;
			}
			else if (iArfcnCH==837)
			{
				return 837.5;
			}
			else
			{
				return 832.4+0.2*(iArfcnCH-4162);
			}		
		} 
		else
		{
			if (iArfcnCH==1037)
			{
				return 877.5;
			}
			else if (iArfcnCH==1162)
			{
				return 882.5;
			}
			else
			{
				return 877.4+0.2*(iArfcnCH-4387);
			}
		}
	case WCDMA_B19_BAND_ID:
		if (iArfcnCH<712)
		{
			if (iArfcnCH==387)
			{
				return 832.5;
			}
			else if (iArfcnCH==412)
			{
				return 837.5;
			}
			else if (iArfcnCH==437)
			{
				return 842.5;
			}
			else
			{
				return 832.4+0.2*(iArfcnCH-312);
			}		
		} 
		else
		{
			if (iArfcnCH==787)
			{
				return 877.5;
			}
			else if (iArfcnCH==812)
			{
				return 882.5;
			}
			else if (iArfcnCH==837)
			{
				return 887.5;
			}
			else
			{
				return 877.4+0.2*(iArfcnCH-712);
			}
		}
	case WCDMA_1800_BAND_ID:
		if (1==isUL)
		{
			return 1712.4+0.2 * (iArfcnCH-937);
		}else{
			return 1807.4 + 0.2 * (iArfcnCH-1162);
		}
		case WCDMA_850_BAND_ID:
			if (iArfcnCH>=4132)
			{
				return 0.2 * (iArfcnCH);
			}else{
				return 670.1 + 0.2 * (iArfcnCH);
			}
 
		case WCDMA_900_BAND_ID:
			return 0.2 * (iArfcnCH) + 340;
		case WCDMA_1500_BAND_ID:
			if (iArfcnCH>=3712)
			{return 733+0.2*(iArfcnCH);
			} 
			else
			{return 736+0.2*(iArfcnCH);
			}
			return 733+0.2*(iArfcnCH);
		case WCDMA_AWS_BAND_ID:  /* ignore additional channels that are not in CalChannelList */
			if (iArfcnCH <= 1513 && iArfcnCH >= 1312)
			{
				return 1450 + 0.2 * (iArfcnCH);
			}else{ /* DL --> 1537 to 1738 */
				return 1805 + 0.2 * (iArfcnCH);
			}

		case WCDMA_PCS_BAND_ID:
			if (iArfcnCH>=9262)
			{
				return 0.2 * (iArfcnCH);
			}else{
				return 1850.1 + 0.2 * (iArfcnCH);
			}
 
		case WCDMA_IMT_BAND_ID:
			return 0.2 * (iArfcnCH);
		case WCDMA_1750_BAND_ID:
			return 0.2 * (iArfcnCH);
	}
 
	
	return 0; 
}
 
int CWCDMABandInfo::GetCMU_NSigMode(const int iBand)
{
	return _WCDMA19UEFDD_NSIG;
}
FTM_RF_Mode_Enum CWCDMABandInfo::GetPhoneMode(const int iBand)
{
	CheckVaildBand(iBand);
		
	switch(iBand)
	{
	case WCDMA_1800_BAND_ID:
		return PHONE_MODE_WCDMA_1800;
		case WCDMA_850_BAND_ID:
			return PHONE_MODE_WCDMA_800;
		case WCDMA_900_BAND_ID:
			return PHONE_MODE_WCDMA_BC8;
		case WCDMA_1500_BAND_ID:
			return PHONE_MODE_WCDMA_1500;
		case WCDMA_AWS_BAND_ID:
			return PHONE_MODE_WCDMA_BC4;
		case WCDMA_PCS_BAND_ID:
			return PHONE_MODE_WCDMA_1900B;
		case WCDMA_IMT_BAND_ID:
			return PHONE_MODE_WCDMA_IMT;
		case WCDMA_1750_BAND_ID:
			return PHONE_MODE_WCDMA_BC9;
	}
}

int  CWCDMABandInfo::GetNVModeID(const int iBand)
{
	CheckVaildBand(iBand);

	switch(iBand)
	{
	case WCDMA_1800_BAND_ID:
		return NV_MODE_WCDMA_1800;
	case WCDMA_850_BAND_ID:
		return NV_MODE_WCDMA_800;
	case WCDMA_900_BAND_ID:
		return NV_MODE_WCDMA_BC8;
	case WCDMA_1500_BAND_ID:
		return NV_MODE_WCDMA_1500;
	case WCDMA_AWS_BAND_ID:
		return NV_MODE_WCDMA_BC4;
	case WCDMA_PCS_BAND_ID:
		return NV_MODE_WCDMA_1900B;
	case WCDMA_IMT_BAND_ID:
		return NV_MODE_WCDMA_IMT;
	case WCDMA_1750_BAND_ID:
		return PHONE_MODE_WCDMA_BC9;
	}
}
int CWCDMABandInfo::GetCMU_SigMode(const int iBand)
{
	return _WCDMA19UEFDD_SIG;
}
 
 
//Have to consider 850 1900 some unique band
int CWCDMABandInfo::GetChannelType(const int iBand, const int iChannel)
{
	CheckVaildCH(iBand, iChannel);
		
	switch(iBand)
	{
		case WCDMA_850_BAND_ID:
			if ( iChannel < 4166 || (iChannel < 4391 && iChannel >= 4357))
			{ return TYPE_LOW_CH;	}
			else if (( iChannel >= 4166 && iChannel< 4199 ) || ( iChannel >= 4391 && iChannel < 4424)){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
		case WCDMA_900_BAND_ID:
			if ( iChannel < 2762 || (iChannel < 2987 && iChannel >= 2937))
			{ return TYPE_LOW_CH;	}
			else if (( iChannel >= 2762 && iChannel< 2813 ) || ( iChannel >= 2987 && iChannel < 3038)){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
		case WCDMA_1500_BAND_ID:
			if( iChannel< 3512||(iChannel< 3737&&iChannel>=3712))
			{
				return TYPE_LOW_CH;
			}
			else if((iChannel >=3512&&iChannel<3537)||(iChannel>=3737&&iChannel<3762))
			{
				return TYPE_MIDDLE_CH;
			}
			else
			{
				return TYPE_HIGH_CH;
			}
		case WCDMA_AWS_BAND_ID:
			if ( iChannel < 1379 || (iChannel < 1604 && iChannel >= 1537))
			{ return TYPE_LOW_CH;	}
			else if (( iChannel >= 1379 && iChannel< 1443 ) || ( iChannel >= 1604 && iChannel < 1668)){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
		case WCDMA_PCS_BAND_ID:
			if ( iChannel < 9355 || (iChannel < 9755 && iChannel >= 9662))
			{ return TYPE_LOW_CH;	}
			else if (( iChannel >= 9355 && iChannel< 9445 ) || ( iChannel >= 9755 && iChannel < 9845)){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
		case WCDMA_IMT_BAND_ID:
			if ( iChannel < 9704 || (iChannel < 10654 && iChannel >= 10562))
			{ return TYPE_LOW_CH;	}
			else if (( iChannel >= 9704 && iChannel< 9796 ) || ( iChannel >= 10654 && iChannel < 10746)){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
		case WCDMA_1750_BAND_ID:
			if ( iChannel < 8812 || (iChannel < 9287 && iChannel >= 9237))
			{ return TYPE_LOW_CH;	}
			else if (( iChannel >= 8812 && iChannel< 8862 ) || ( iChannel >= 9287 && iChannel < 9337)){
				return TYPE_MIDDLE_CH;
			}else{
				return TYPE_HIGH_CH;
			}
			
	}
 

}
//TD Band Info

FTM_RF_Mode_Enum CTDSBandInfo::GetPhoneMode(const int iBand)
{
	if (!CheckVaildBand(iBand))
		return PHONE_MODE_MAX;


	switch(iBand)
	{
	case 34:
		return PHONE_MODE_TDSCDMA_B34;
	case 39:
		return PHONE_MODE_TDSCDMA_B39;
	case 40:
		return PHONE_MODE_TDSCDMA_B40;
	
	}
	
}

nv_mode_id_type CTDSBandInfo::GetNVModeID(const int iBand)
{
	if (!CheckVaildBand(iBand))
		return NV_MODE_MAX;


	switch(iBand)
	{
	case 34:
		return NV_MODE_TDSCDMA_B34;
	case 39:
		return NV_MODE_TDSCDMA_B39;
	case 40:
		return NV_MODE_TDSCDMA_B40;

	}

}
bool CTDSBandInfo::CheckVaildCH(const int iBand, const int iChannel)
{
	if (!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
	case 34:
		if (iChannel <= 10125 && iChannel >= 10050){
			return true;}
		else
			return false;
		break;
	case 39:
		if (iChannel <= 9600 && iChannel >= 9400){
			return true;}
		else
			return false;
		break;
	case 40:
		if (iChannel <= 12000 && iChannel >= 11500){
			return true;}
		else
			return false;
		break;
	}
}
int CTDSBandInfo::GetDLChannel(const int iBand, const int iULChannel)
{
	if (!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
	case 34:
		return iULChannel;
	case 39:
		return iULChannel;
	case 40:
		return iULChannel;

	}
}
int CTDSBandInfo::GetULChannel(const int iBand, const int iDLChannel)
{
	if (!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
	case 34:
		return iDLChannel;
	case 39:
		return iDLChannel;
	case 40:
		return iDLChannel;

	}

}
double CTDSBandInfo::ArfcnToHz(const int iBand, const int iArfcnCH)
{
	return iArfcnCH*0.2;
}
//LTE Band Info

FTM_RF_Mode_Enum CLTEBandInfo::GetPhoneMode(const int iBand)
{
	if (!CheckVaildBand(iBand))
		return PHONE_MODE_MAX;
	

	switch(iBand)
	{
	case 1:
		return PHONE_MODE_LTE_B1;
	case 2:
		return PHONE_MODE_LTE_B2;
	case 3:
		return PHONE_MODE_LTE_B3;
	case 4:
		return PHONE_MODE_LTE_B4;
	case 5:
		return PHONE_MODE_LTE_B5;
	case 6:
		return PHONE_MODE_LTE_B6;
	case 7:
		return PHONE_MODE_LTE_B7;
	case 8:
		return PHONE_MODE_LTE_B8;
	case 9:
		return PHONE_MODE_LTE_B9;
	case 10:
		return PHONE_MODE_LTE_B10;
	case 11:
		return PHONE_MODE_LTE_B11;
	case 12:
		return PHONE_MODE_LTE_B12;
	case 13:
		return PHONE_MODE_LTE_B13;
	case 14:
		return PHONE_MODE_LTE_B14;
	case 15:
		return PHONE_MODE_LTE_B15;
	case 16:
		return PHONE_MODE_LTE_B16;
	case 17:
		return PHONE_MODE_LTE_B17;
	case 18:
		return PHONE_MODE_LTE_B18;
	case 19:
		return PHONE_MODE_LTE_B19;
	case 20:
		return PHONE_MODE_LTE_B20;	
	case 21:
		return PHONE_MODE_LTE_B21;
	case 22:
		return PHONE_MODE_LTE_B22;
	case 23:
		return PHONE_MODE_LTE_B23;
	case 24:
		return PHONE_MODE_LTE_B24;
	case 25:
		return PHONE_MODE_LTE_B25;
	case 26:
		return PHONE_MODE_LTE_B26;
	case 27:
		return PHONE_MODE_LTE_B27;
	case 28:
		return PHONE_MODE_LTE_B28;
	case 29:
		return PHONE_MODE_LTE_B29;
	case 30:
		return PHONE_MODE_LTE_B30;	
	case 31:
		return PHONE_MODE_LTE_B31;
	case 32:
		return PHONE_MODE_LTE_B32;
	case 33:
		return PHONE_MODE_LTE_B33;
	case 34:
		return PHONE_MODE_LTE_B34;
	case 35:
		return PHONE_MODE_LTE_B35;
	case 36:
		return PHONE_MODE_LTE_B36;
	case 37:
		return PHONE_MODE_LTE_B37;
	case 38:
		return PHONE_MODE_LTE_B38;
	case 39:
		return PHONE_MODE_LTE_B39;
	case 40:
		return PHONE_MODE_LTE_B40;
	case 41:
		return PHONE_MODE_LTE_B41;

	}

}
nv_mode_id_type CLTEBandInfo::GetNVModeID(const int iBand)
{
	if (!CheckVaildBand(iBand))
		return NV_MODE_MAX;


	switch(iBand)
	{
	case 1:
		return NV_MODE_LTE_B1;
	case 2:
		return NV_MODE_LTE_B2;
	case 3:
		return NV_MODE_LTE_B3;
	case 4:
		return NV_MODE_LTE_B4;
	case 5:
		return NV_MODE_LTE_B5;
	case 6:
		return NV_MODE_LTE_B6;
	case 7:
		return NV_MODE_LTE_B7;
	case 8:
		return NV_MODE_LTE_B8;
	case 9:
		return NV_MODE_LTE_B9;
	case 10:
		return NV_MODE_LTE_B10;
	case 11:
		return NV_MODE_LTE_B11;
	case 12:
		return NV_MODE_LTE_B12;
	case 13:
		return NV_MODE_LTE_B13;
	case 14:
		return NV_MODE_LTE_B14;
	case 15:
		return NV_MODE_LTE_B15;
	case 16:
		return NV_MODE_LTE_B16;
	case 17:
		return NV_MODE_LTE_B17;
	case 18:
		return NV_MODE_LTE_B18;
	case 19:
		return NV_MODE_LTE_B19;
	case 20:
		return NV_MODE_LTE_B20;	
	case 21:
		return NV_MODE_LTE_B21;
	case 22:
		return NV_MODE_LTE_B22;
	case 23:
		return NV_MODE_LTE_B23;
	case 24:
		return NV_MODE_LTE_B24;
	case 25:
		return NV_MODE_LTE_B25;
	case 26:
		return NV_MODE_LTE_B26;
	case 27:
		return NV_MODE_LTE_B27;
	case 28:
		return NV_MODE_LTE_B28;
	case 29:
		return NV_MODE_LTE_B29;
	case 30:
		return NV_MODE_LTE_B30;	
	case 31:
		return NV_MODE_LTE_B31;
	case 32:
		return NV_MODE_LTE_B32;
	case 33:
		return NV_MODE_LTE_B33;
	case 34:
		return NV_MODE_LTE_B34;
	case 35:
		return NV_MODE_LTE_B35;
	case 36:
		return NV_MODE_LTE_B36;
	case 37:
		return NV_MODE_LTE_B37;
	case 38:
		return NV_MODE_LTE_B38;
	case 39:
		return NV_MODE_LTE_B39;
	case 40:
		return NV_MODE_LTE_B40;
	case 41:
		return NV_MODE_LTE_B41;

	}

}

bool CLTEBandInfo::CheckVaildCH(const int iBand, const int iChannel)
{
	if(!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
	case 1:
		if ((iChannel <= 599 && iChannel >= 0) || (iChannel <= 18599 && iChannel >= 18000)){
			return true;}
		else
			return false;
		break;
	case 2:
		if ((iChannel <= 1199 && iChannel >= 600) || (iChannel <= 19199 && iChannel >= 18600)){
			return true;}
		else
			return false;
		break;
	case 3:
		if ((iChannel <= 1949 && iChannel >= 1200) || (iChannel <= 19949 && iChannel >= 19200)){
			return true;}
		else
			return false;
		break;
	case 4:
		if ((iChannel <= 2399 && iChannel >= 1950) || (iChannel <= 20399 && iChannel >= 19950)){
			return true;}
		else
			return false;
		break;
	case 5:
		if ((iChannel <= 2649 && iChannel >= 2400) || (iChannel <= 20649 && iChannel >= 20400)){
			return true;}
		else
			return false;
		break;
	case 7:
		if ((iChannel <= 3499 && iChannel >= 2750) || (iChannel <= 21449 && iChannel >= 20750)){
			return true;}
		else
			return false;
		break;
	case 8:
		if ((iChannel <= 3799 && iChannel >= 3450) || (iChannel <= 21799 && iChannel >= 21450)){
			return true;}
		else
			return false;
		break;
	case 12:
		if ((iChannel <= 5179 && iChannel >= 5000) || (iChannel <= 23179 && iChannel >= 23000)){
			return true;}
		else
			return false;
		break;
	case 14:
		if ((iChannel <= 5379 && iChannel >= 5280) || (iChannel <= 23379 && iChannel >= 23280)){
			return true;}
		else
			return false;
		break;
	
	case 17:
		if ((iChannel <= 5849 && iChannel >= 5730) || (iChannel <= 23849 && iChannel >= 23730)){
			return true;}
		else
			return false;
		break;
	case 19:
		if ((iChannel <= 6149 && iChannel >= 6000) || (iChannel <= 24149 && iChannel >= 24000)){
			return true;}
		else
			return false;
		break;
	case 20:
		if ((iChannel <= 6449 && iChannel >= 6150) || (iChannel <= 24449 && iChannel >= 24150)){
			return true;}
		else
			return false;
		break;
	case 21:
		if ((iChannel <= 6599 && iChannel >= 6450) || (iChannel <= 24599 && iChannel >= 24450)){
			return true;}
		else
			return false;
		break;
	
	case 25:
		if ((iChannel <= 26689 && iChannel >= 26040) || (iChannel <= 8689 && iChannel >= 8040)){
			return true;}
		else
			return false;
		break;
	case 26:
		if ((iChannel <= 27039 && iChannel >= 26690) || (iChannel <= 9039 && iChannel >= 8690)){
			return true;}
		else
			return false;
		break;
	case 28:
		if ((iChannel <= 9659 && iChannel >= 9210) || (iChannel <= 27659 && iChannel >= 27210)){
			return true;}
		else
			return false;
		break;
	case 34:
		if (iChannel <= 36394 && iChannel >= 36200) {
			return true;}
		else
			return false;
		break;
	case 38:
		if (iChannel <= 38294 && iChannel >= 37750){
			return true;}
		else
			return false;
		break;
	case 39:
		if (iChannel <= 38649 && iChannel >= 38250) {
			return true;}
		else
			return false;
		break;
	case 40:
		if (iChannel <= 39649 && iChannel >= 38650){
			return true;}
		else
			return false;
	case 41:
		if (iChannel <= 41589 && iChannel >= 39650){
			return true;}
		else
			return false;
		break;
	}

}

double CLTEBandInfo::ArfcnToHz(const int iBand, const int iArfcnCH)
{
	if(!CheckVaildCH(iBand, iArfcnCH))
		return false;

	switch(iBand)
	{
	case 1:
		if (iArfcnCH<=599)
		{
			return 2110.0 + 0.1 * (iArfcnCH);
		}else{
			return 1920.0 + 0.1 * (iArfcnCH - 18000);
		}
		break;
	case 2:
		if (iArfcnCH<=1199)
		{
			return 1930.0 + 0.1 * (iArfcnCH - 600);
		}else{
			return 1850.0 + 0.1 * (iArfcnCH - 18600);
		}
		break;
	case 3:
		if (iArfcnCH<=1949)
		{
			return 1805.0 + 0.1 * (iArfcnCH-1200);
		}else{
			return 1710.0 + 0.1 * (iArfcnCH - 19200);
		}
		break;
	case 4:
		if (iArfcnCH<=2399)
		{
			return 2110.0 + 0.1 * (iArfcnCH - 1950);
		}else{
			return 1710.0 + 0.1 * (iArfcnCH - 19950);
		}
		break;
	case 5:		
		if (iArfcnCH<=2649)
		{
			return 869.0 + 0.1 * (iArfcnCH - 2400);
		}else{
			return 824.0 + 0.1 * (iArfcnCH - 20400);
		}
		break;
	case 7:		
		if (iArfcnCH<=3449)
		{
			return 2620.0 + 0.1 * (iArfcnCH - 2750);
		}else{
			return 2500.0 + 0.1 * (iArfcnCH - 20750);
		}
		break;
	case 8:
		if (iArfcnCH<=3799)
		{
			return 925.0 + 0.1 * (iArfcnCH - 3450);
		}else{
			return 880.0 + 0.1 * (iArfcnCH - 21450);
		}
		break;
	case 12:
		if (iArfcnCH<=5179)
		{
			return 728.0 + 0.1 * (iArfcnCH - 5000);
		}else{
			return 698.0 + 0.1 * (iArfcnCH - 23000);
		}
		break;
	case 14:
		if (iArfcnCH<=5379)
		{
			return 758.0 + 0.1 * (iArfcnCH - 5280);
		}else{
			return 788.0 + 0.1 * (iArfcnCH - 23280);
		}
		break;
	case 17:
		if (iArfcnCH<=5849)
		{
			return 734.0 + 0.1 * (iArfcnCH - 5730);
		}else{
			return 704.0 + 0.1 * (iArfcnCH - 23730);
		}
		break;
	case 19:
		if (iArfcnCH<=6149)
		{
			return 875.0 + 0.1 * (iArfcnCH - 6000);
		}else{
			return 830.0 + 0.1 * (iArfcnCH - 24000);
		}
		break;
	case 20:
		if (iArfcnCH<=6449)
		{
			return 791.0 + 0.1 * (iArfcnCH - 6150);
		}else{
			return 832.0 + 0.1 * (iArfcnCH - 24150);
		}
		break;
	case 21:
		if (iArfcnCH<=6599)
		{
			return 1495.9 + 0.1 * (iArfcnCH - 6450);
		}else{
			return  1447.9+ 0.1 * (iArfcnCH - 24450);
		}
		break;
	case 25:
		if (iArfcnCH<=8689)
		{
			return 1930.0 + 0.1 * (iArfcnCH - 8040);
		}else{
			return 1850.0 + 0.1 * (iArfcnCH - 26040);
		}
		break;
	case 26:
		if (iArfcnCH<=9039)
		{
			return 859.0 + 0.1 * (iArfcnCH - 8690);
		}else{
			return 814.0 + 0.1 * (iArfcnCH - 26690);
		}
		break;
	case 28:
		if (iArfcnCH<=9659)
		{
			return 758.0 + 0.1 * (iArfcnCH - 9210);
		}else{
			return 703.0 + 0.1 * (iArfcnCH - 27210);
		}
		break;
	case 34:		
		return 2010.0 + 0.1 * (iArfcnCH - 36200);
		break;
	case 38:
		return 2570.0 + 0.1 * (iArfcnCH - 37750);		
		break;
	case 39:		
		return 1880.0 + 0.1 * (iArfcnCH - 38250);
		break;
	case 40:
		return 2300.0 + 0.1 * (iArfcnCH - 38650);	
		break;
	case 41:
		return 2496.0 + 0.1 * (iArfcnCH - 39650);

	}

	return 0; 

}
int CLTEBandInfo::GetULChannel(const int iBand, const int iDLChannel)
{
	if(!CheckVaildCH(iBand,iDLChannel))
		return false;

	switch(iBand)
	{
	case 1:
		return iDLChannel+18000;
	case 2:
		return iDLChannel+18000;
	case 3:
		return iDLChannel+18000;
	case 4:
		return iDLChannel+18000;
	case 5:
		return iDLChannel+18000;
	case 7:
		return iDLChannel+18000;
	case 8:
		return iDLChannel+18000;
	case 12:
		return iDLChannel+18000;
	case 14:
		return iDLChannel+18000;
	case 17:
		return iDLChannel+18000;
	case 19:
		return iDLChannel+18000;
	case 20:
		return iDLChannel+18000;
	case 21:
		return iDLChannel+18000;
	case 25:
		return iDLChannel+18000;
	case 26:
		return iDLChannel+18000;
	case 28:
		return iDLChannel+18000;
	case 34:
		return iDLChannel;
	case 38:
		return iDLChannel;
	case 39:
		return iDLChannel;
	case 40:
		return iDLChannel;
	case 41:
		return iDLChannel;
	default:
		return false;
	}

}
int CLTEBandInfo::GetDLChannel(const int iBand, const int iULChannel)
{
	if(!CheckVaildCH(iBand,iULChannel))
		return false;

	switch(iBand)
	{
	case 1:
		return iULChannel-18000;
	case 2:
		return iULChannel-18000;
	case 3:
		return iULChannel-18000;
	case 4:
		return iULChannel-18000;
	case 5:
		return iULChannel-18000;
	case 7:
		return iULChannel-18000;
	case 8:
		return iULChannel-18000;
	case 12:
		return iULChannel-18000;
	case 14:
		return iULChannel-18000;
	case 17:
		return iULChannel-18000;
	case 19:
		return iULChannel-18000;
	case 20:
		return iULChannel-18000;
	case 21:
		return iULChannel-18000;
	case 25:
		return iULChannel-18000;
	case 26:
		return iULChannel-18000;
	case 28:
		return iULChannel-18000;
	case 34:
		return iULChannel;
	case 38:
		return iULChannel;
	case 39:
		return iULChannel;
	case 40:
		return iULChannel;
	case 41:
		return iULChannel;
	default:
		return false;
	}

}

//CDMA Band Info
FTM_RF_Mode_Enum CCDMABandInfo::GetPhoneMode(const int iBand)
{
	if(!CheckVaildBand(iBand))
		return PHONE_MODE_MAX;
	
	switch(iBand)
	{
		case CDMA_BC0_BAND_ID:
			return PHONE_MODE_CDMA_800;
		case CDMA_BC1_BAND_ID:
			return PHONE_MODE_CDMA_1900;
		case CDMA_BC10_BAND_ID:
			return PHONE_MODE_CDMA_800_SEC;
	}
}
nv_mode_id_type CCDMABandInfo::GetNVModeID(const int iBand)
{
	if(!CheckVaildBand(iBand))
		return NV_MODE_MAX;

	switch(iBand)
	{
	case CDMA_BC0_BAND_ID:
		return NV_MODE_BC0;
	case CDMA_BC1_BAND_ID:
		return NV_MODE_BC1;
	case CDMA_BC10_BAND_ID:
		return NV_MODE_BC10;
	}

}

FTM_CDMA2000_BandClasstype CCDMABandInfo::GetPhoneBandClassMode(const int iBand)
{
	CheckVaildBand(iBand);

	switch(iBand)
	{
	case CDMA_BC0_BAND_ID:
		return FTM_CDMA2000_BAND_BC0;
	case CDMA_BC1_BAND_ID:
		return FTM_CDMA2000_BAND_BC1;
	case CDMA_BC10_BAND_ID:
		return FTM_CDMA2000_BAND_BC10;
	}
}

bool CCDMABandInfo::CheckVaildCH(const int iBand, const int iChannel)
{
	if(!CheckVaildBand(iBand))
		return false;
	switch(iBand)
	{
		case CDMA_BC0_BAND_ID:
			if ((iChannel <= 799 && iChannel >= 1) || (iChannel <= 1023 && iChannel >= 991)){
				return true;}
			else
				return false;
			break;
		case CDMA_BC1_BAND_ID:
			if ((iChannel <= 1199 && iChannel >= 0) )
			{return true;}
			else
				return false;
			break;
		case CDMA_BC10_BAND_ID:
			if ((iChannel <= 919 && iChannel >= 0) )
			{return true;}
			else
				return false;
			break;
	}
}

double CCDMABandInfo::ArfcnToHz(const int iBand, const int iArfcnCH, const int iULorDL) //UL:0, DL:1
{
	CheckVaildCH(iBand, iArfcnCH);
		
	switch(iBand)
	{
		case CDMA_BC0_BAND_ID:
			if (iArfcnCH<=799)
			{
				return 825.0 + 0.03 * (iArfcnCH) + iULorDL*45;
			}else{
				return 825.0 + 0.03 * (iArfcnCH - 1023) + iULorDL*45;
			}
			break;
		case CDMA_BC1_BAND_ID:		
			return 1850.0 + 0.05 * (iArfcnCH) + iULorDL*80;
			break;
		case CDMA_BC10_BAND_ID:		
			return 806.0 + 0.025 * (iArfcnCH) + iULorDL*45;
			break;
	}
 
	return 0; 
}

int CCDMABandInfo::GetChannelType(const int iBand, const int iChannel)
{
	CheckVaildCH(iBand, iChannel);
		
	switch(iBand)
	{
	case CDMA_BC0_BAND_ID:  // 1~799  991~1023
		if ((iChannel <= 1023 && iChannel >= 991) || ( iChannel >= 1 && iChannel< 200 )){ 
			return TYPE_LOW_CH;	
		}else if (( iChannel >= 200 && iChannel< 500 )){
			return TYPE_MIDDLE_CH;
		}else{
			return TYPE_HIGH_CH;
		}
	case CDMA_BC1_BAND_ID:  //0~1199
		if ( (iChannel < 300 && iChannel >= 0))
		{ return TYPE_LOW_CH;	}
		else if (( iChannel >= 300 && iChannel< 800 )){
			return TYPE_MIDDLE_CH;
		}else{
			return TYPE_HIGH_CH;
		}
	case CDMA_BC10_BAND_ID:  //0~1199
		if ( (iChannel < 300 && iChannel >= 0))
		{ return TYPE_LOW_CH;	}
		else if (( iChannel >= 300 && iChannel< 600 )){
			return TYPE_MIDDLE_CH;
		}else{
			return TYPE_HIGH_CH;
		}
	}
	
}

int CCDMABandInfo::GetDLChannel(const int iBand, const int iULChannel)
{
	(CheckVaildCH(iBand, iULChannel));
	return iULChannel;
}
int CCDMABandInfo::GetULChannel(const int iBand, const int iDLChannel)
{
	(CheckVaildCH(iBand, iDLChannel));
	return iDLChannel;
	
}
 
