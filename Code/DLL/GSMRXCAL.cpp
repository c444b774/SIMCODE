#include "stdafx.h"
#include "GSMRXCAL.h"
RF_IMPLEMENT_DYNCREATE(CGSMRXCal)

CGSMRXCal::CGSMRXCal()
{
	m_mapClassFunc[_T("GSMRXCalMainFunc")]=&CGSMRXCal::CGSMRXCalMainFunc;
	m_mapClassFunc[_T("GSMRXCal")]=&CGSMRXCal::GSMRXCalFunc;
	m_mapClassFunc[_T("GSMRXCal_9x25")]=&CGSMRXCal::GSMRXCalFunc_9x25;
}

CGSMRXCal::~CGSMRXCal()
{
	
}

bool CGSMRXCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSMRXCal::Handle()
{
	if(!DoProcess())
	{

		m_pPhone->CloseComport();
		m_pFunGSMCalDev->Deivce_Exit();
		return false;
	}

    
	//CalPassLog("_","_","Init GSM Cal Pass");

	return true;
}

bool CGSMRXCal::CGSMRXCalMainFunc()
{

	 if(!SetGSMCableLoss())
		return false;

/*
	 switch(m_iBand)
	 {
		case 850:
	
			m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);

		 break;
		  case 900:
			 m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);
		 break;
		 case 1800:
			 m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);
	     break;
	    case 1900:
			m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);
		 break;
	 }*/
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}

bool CGSMRXCal::SetGSMCableLoss()
{
   CString strMsg;
     double dLoss;
	m_vCableLoss.clear();
	int iErrorCode;
    for(int i=0;i<3;i++)
	{
      if(!m_LossFinder.GetGSMLoss(m_strBand,i,dLoss))
	  {
		  strMsg.Format("GSM Get Loss Band=%s ,ChannelType=%d Fail",m_strBand,i);
          LogTrace(MSG_ERROR,strMsg);
		  CalFailLog(_T("_"),_T("_"),1001,strMsg);
		  return false;
	  }
	  m_vCableLoss.push_back(dLoss);
	}


      
		if((iErrorCode=m_pFunGSMCalDev->IGSMCalSetLoss(m_iBand,m_vCableLoss))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Set Cableloss device fail");
			CalFailLog(_T("_"),_T("_"),iErrorCode,"Set Cableloss device fail");
			return false;
		  
	   }
        



  return true;
}
bool CGSMRXCal::GSMRXCalFunc()
{

   CString strMsg;
   int  iErrorcode;
  // unsigned char ucMaskBit[5] = {0};
  // unsigned char ucMaskCount=0;
   unsigned char ucToggleRx = 0;   
 //  float fMaskPower[5] = {0.0f};   
   double dDLMhz=0.0;
   double dULMhz=0.0;
   unsigned long aiRSSI_Results[ FTM_GSM_RX_GAIN_RANGE_CAL_NUM_RETURN_VALUES ] = {0};
   unsigned short ChannelList[QMSL_GSM_RX_GAIN_RANGE_CHANNELS]={0};

   QMSL_GSM_Rx_Gain_Range_struct aGSM_Rx_Gain_Range_Result;
   QMSL_GSM_Rx_Gain_Range_NV_struct  aGSM_Rx_Gain_Range_NV;
   QMSL_RFCAL_NV_Item   pGSM_Cal_ARFCN_NV;
	
/*
   ucMaskBit[ucMaskCount]=m_vBitMask[0];
   fMaskPower[ucMaskCount] = m_vRXPower[0];
   ucMaskCount++;

   for(int k=0; k<m_vBitMask.size()-1; k++)
   {
	   if(m_vRXPower[k] == m_vRXPower[k+1])
	   {
		   ucMaskBit[ucMaskCount] += m_vBitMask[k+1];
	   }
	   else
	   {		   
		   ucMaskBit[ucMaskCount] = m_vBitMask[k+1];
		   fMaskPower[ucMaskCount] = m_vRXPower[k+1];
		   ucMaskCount++;
	   }
   }*/

   aGSM_Rx_Gain_Range_Result.iNumRxGainRange=m_vRXPower.size();
   aGSM_Rx_Gain_Range_Result.iNumChannel=m_vChannelList.size();
   for(int i=0;i<m_vRXPower.size();++i)
   {
	    aGSM_Rx_Gain_Range_Result.aiCalibrationPwr[i]=m_vRXPower[i];
   }   

   strMsg.Format("Start RX Calibration Band=%s",m_strBand);
   LogTrace(MSG_MID,strMsg) 

  	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iPhoneMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}  

	if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_TX_ON false Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}  
	if((iErrorcode=m_pPhone->FTM_SET_RX_BURST(0,2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_RX_BURST Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	 if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetWaveForm(m_strWaveFile))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"GSM Cal Set DL POWER fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM Cal Set DL POWER fail");
				return false;
			  
		   }
	for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
	{
		dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
		dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);

		if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"GSM Cal Set Freq fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM Cal Set Freq fail");
			return false;
		  
	   }

		if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_vChannelList[iCHIndex]))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_CHAN Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 


		for(int ucMaskIndex = 0; ucMaskIndex<m_vRXPower.size(); ucMaskIndex++)
		{
           if(iCHIndex == 0 && ucMaskIndex == 0)
			{
				ucToggleRx = 1;
			}
		   else
		    {
				ucToggleRx = 0;		
			}

			 if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetDLPower(m_vRXPower[ucMaskIndex]))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"GSM Cal Set DL POWER fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM Cal Set DL POWER fail");
				return false;			  
		   }
			 Sleep(200);

			 if((iErrorcode=m_pPhone->FTM_RX_GAIN_RANGE_CAL(m_vBitMask[ucMaskIndex],m_ucGainRangeCount,ucToggleRx,aiRSSI_Results))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_RX_GAIN_RANGE_CAL Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}  
			 for (int i=0;i<5;i++)
			 {
				 if ((m_vBitMask[ucMaskIndex]>>i)&0x01)
				 {
					 aGSM_Rx_Gain_Range_Result.aiRSSIValue[i][iCHIndex]=aiRSSI_Results[i];
				 }
			 }
		}       
	}	
	
   if((iErrorcode=m_pPhone->RFCAL_GSM_Rx_Gain_Range_Results(m_iPhoneMode,&aGSM_Rx_Gain_Range_Result,&aGSM_Rx_Gain_Range_NV,1))!=PHONE_SUCCESS)
   { 
	   strMsg.Format("RFCAL_GSM_Rx_Gain_Range_Results Fail!");
	   PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
   } 
   unsigned long iRSSIValue;
   int iOffsetValue;
   int iFailflag=0;
   strMsg.Format("Band%d_GSM Rx FreqComp :",m_iBand);
   LogTrace(MSG_MID,strMsg)
	   strMsg.Format("Channel RxLevel	BitMask	RSSI	Offset	Min Max Result");
   LogTrace(MSG_MID,strMsg)
   for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
   {
		ChannelList[iCHIndex]=m_vChannelList[iCHIndex];
		for(int iGainIndex=0;iGainIndex<m_vBitMask.size();++iGainIndex)
		{
			iOffsetValue=aGSM_Rx_Gain_Range_NV.aiRSSI_NV_Value[iGainIndex][iCHIndex];
			iRSSIValue=aGSM_Rx_Gain_Range_Result.aiRSSIValue[iGainIndex][iCHIndex];
			if(iOffsetValue<m_vRXLimitLow[iGainIndex] || iOffsetValue>m_vRXLimitUp[iGainIndex])
			{
				strMsg.Format("%d	%.2f	%d	%u	%d	%d	%d	Fail",m_vChannelList[iCHIndex],m_vRXPower[iGainIndex],m_vBitMask[iGainIndex],iRSSIValue,iOffsetValue,m_vRXLimitLow[iGainIndex],m_vRXLimitUp[iGainIndex]);
				LogTrace(MSG_ERROR,strMsg)	
				iFailflag++;
			}
			else
			{
				strMsg.Format("%d	%.2f	%d	%u	%d	%d	%d	Pass",m_vChannelList[iCHIndex],m_vRXPower[iGainIndex],m_vBitMask[iGainIndex],iRSSIValue,iOffsetValue,m_vRXLimitLow[iGainIndex],m_vRXLimitUp[iGainIndex]);
				LogTrace(MSG_MID,strMsg)				
			}
	   }
   }
   if (iFailflag>0)
   {
	   CalFailLog(m_strBand,"_",1001,"RxGainOffset is out of range")
		   return false;
   }  
	if((iErrorcode=m_pPhone->RFCAL_GSM_CAL_ARFCN(m_iPhoneMode,ChannelList,m_vChannelList.size(),&pGSM_Cal_ARFCN_NV,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_GSM_CAL_ARFCN Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	} 
	CalPassLog(m_strBand,"_","Rx Calibration Pass");
	return true;
}

bool CGSMRXCal::GSMRXCalFunc_9x25()
{

   CString strMsg;
   int  iErrorcode;
   int iMode_id,iMode_id_ex;
   if (0==m_iChainId)
   {
	   iMode_id=2;
	   iMode_id_ex=17;
   }else
   {
	   iMode_id=49;
	   iMode_id_ex=50;
   }
  // unsigned char ucMaskBit[5] = {0};
  // unsigned char ucMaskCount=0;
   unsigned char ucToggleRx = 0;   
 //  float fMaskPower[5] = {0.0f};   
   double dDLMhz=0.0;
   double dULMhz=0.0;
   unsigned long aiRSSI_Results[ FTM_GSM_RX_GAIN_RANGE_CAL_NUM_RETURN_VALUES ] = {0};
   unsigned short ChannelList[QMSL_GSM_RX_GAIN_RANGE_CHANNELS]={0};

   QMSL_GSM_Rx_Calibration_Params_and_Meas aGSM_Rx_Gain_Range_Result;
   memset(&aGSM_Rx_Gain_Range_Result,0,sizeof(QMSL_GSM_Rx_Calibration_Params_and_Meas));
   //QMSL_GSM_Rx_Gain_Range_struct aGSM_Rx_Gain_Range_Result;
   QMSL_GSM_Rx_Calibration_NV  aGSM_Rx_Gain_Range_NV;
   memset(&aGSM_Rx_Gain_Range_NV,0,sizeof(QMSL_GSM_Rx_Calibration_NV));

	
/*
   ucMaskBit[ucMaskCount]=m_vBitMask[0];
   fMaskPower[ucMaskCount] = m_vRXPower[0];
   ucMaskCount++;

   for(int k=0; k<m_vBitMask.size()-1; k++)
   {
	   if(m_vRXPower[k] == m_vRXPower[k+1])
	   {
		   ucMaskBit[ucMaskCount] += m_vBitMask[k+1];
	   }
	   else
	   {		   
		   ucMaskBit[ucMaskCount] = m_vBitMask[k+1];
		   fMaskPower[ucMaskCount] = m_vRXPower[k+1];
		   ucMaskCount++;
	   }
   }*/
	
   aGSM_Rx_Gain_Range_Result.iNumRxGainRange=m_vRXPower.size();
   aGSM_Rx_Gain_Range_Result.iNumChannel=m_vChannelList.size();
   aGSM_Rx_Gain_Range_Result.iChainId=m_iChainId;
   for(int i=0;i<m_vRXPower.size();++i)
   {
	    aGSM_Rx_Gain_Range_Result.aiCalibrationPwr[i]=m_vRXPower[i];
   }   

   strMsg.Format("Start RX Calibration Band=%s",m_strBand);
   LogTrace(MSG_MID,strMsg) 

  	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	if((iErrorcode=m_pPhone->FTM_SET_MODE(m_iPhoneMode))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	if((iErrorcode=m_pPhone->FTM_SET_TX_ON(false))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_TX_ON false Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		}  
	if((iErrorcode=m_pPhone->FTM_SET_RX_BURST(0,2))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_RX_BURST Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 

	 if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetWaveForm(m_strWaveFile))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"GSM Cal Set DL POWER fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM Cal Set DL POWER fail");
				return false;
			  
		   }
	for(int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
	{
		dDLMhz=CGSMBandInfo::ArfcnToRXHz(m_iBand,m_vChannelList[iCHIndex]); 
		dULMhz=CGSMBandInfo::ArfcnToTXHz(m_iBand,m_vChannelList[iCHIndex]);
		aGSM_Rx_Gain_Range_Result.aiChannelList[iCHIndex]=m_vChannelList[iCHIndex];
		if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetFreq(dDLMhz,dULMhz))!=DEVICE_SUCCESS)
	    {
			LogTrace(MSG_ERROR,"GSM Cal Set Freq fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM Cal Set Freq fail");
			return false;		  
	    }
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		if((iErrorcode=m_pPhone->FTM_SET_CHAN(m_vChannelList[iCHIndex]))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_CHAN Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(iMode_id))!=PHONE_SUCCESS)
		{ 
			strMsg.Format("FTM_SET_MODE_ID Fail!");
			PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
		} 
		for(int ucMaskIndex = 0; ucMaskIndex<m_vRXPower.size(); ucMaskIndex++)
		{
           if(iCHIndex == 0 && ucMaskIndex == 0)
			{
				ucToggleRx = 1;
			}
		    else
		    {
				ucToggleRx = 0;		
			}

		    if((iErrorcode=m_pFunGSMCalDev->IGSMCalSetDLPower(m_vRXPower[ucMaskIndex]))!=DEVICE_SUCCESS)
		    {  
				LogTrace(MSG_ERROR,"GSM Cal Set DL POWER fail");
				CalFailLog(_T("_"),_T("_"),iErrorcode,"GSM Cal Set DL POWER fail");
				return false;			  
		    }
			 Sleep(50);

			if((iErrorcode=m_pPhone->FTM_RX_GAIN_RANGE_CAL(m_vBitMask[ucMaskIndex],m_ucGainRangeCount,ucToggleRx,aiRSSI_Results))!=PHONE_SUCCESS)
			{ 
				strMsg.Format("FTM_RX_GAIN_RANGE_CAL Fail!");
				PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
			}  
			for (int i=0;i<5;i++)
			{
				 if ((m_vBitMask[ucMaskIndex]>>i)&0x01)		// 1 2 4 8 =>>> 0,1,2,3
				 {
					 aGSM_Rx_Gain_Range_Result.aiRSSIValue[i][iCHIndex]=aiRSSI_Results[i];
				 }
			}
		}       
	}	
    //Disable RSSI read
	if((iErrorcode=m_pPhone->FTM_SET_RX_BURST(0,2))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_SET_RX_BURST Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	} 
    //QLIB_GSM_RX_CALIBRATION_GENERATE_NV
	if((iErrorcode=m_pPhone->RFCAL_GSM_RX_CALIBRATION_GENERATE_NV(m_iPhoneMode,&aGSM_Rx_Gain_Range_Result,&aGSM_Rx_Gain_Range_NV,1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("RFCAL_GSM_RX_CALIBRATION_GENERATE_NV Fail!");
		PHONE_CAL_ERR_LOG(strMsg,iErrorcode)
	}
	unsigned long iRSSIValue;
	int iOffsetValue;
	int iFailflag=0;
    int RxGainOffsetStartPos = 0;

	strMsg.Format("Band%d_GSM Rx FreqComp :",m_iBand);
	LogTrace(MSG_MID,strMsg)
	strMsg.Format("Channel RxLevel	BitMask	RSSI	Offset	Min Max Result");
	LogTrace(MSG_MID,strMsg)	
	for (int iGainIndex=0;iGainIndex<m_vBitMask.size();++iGainIndex)
	{
		for (int iCHIndex=0;iCHIndex<m_vChannelList.size();++iCHIndex)
		{
             RxGainOffsetStartPos = 62 + iCHIndex * 2 +  iGainIndex * 32;            
			 iOffsetValue = aGSM_Rx_Gain_Range_NV.nvRev0.aiGSM_Rx_Gain_NV_Value[iGainIndex][iCHIndex];
			 iRSSIValue=aGSM_Rx_Gain_Range_Result.aiRSSIValue[iGainIndex][iCHIndex];
			 if(iOffsetValue<m_vRXLimitLow[iGainIndex] || iOffsetValue>m_vRXLimitUp[iGainIndex])
			 {
				 strMsg.Format("%d	%.2f	%d	%u	%d	%d	%d	Fail",m_vChannelList[iCHIndex],m_vRXPower[iGainIndex],m_vBitMask[iGainIndex],iRSSIValue,iOffsetValue,m_vRXLimitLow[iGainIndex],m_vRXLimitUp[iGainIndex]);
				 LogTrace(MSG_ERROR,strMsg)	
				 iFailflag++;
			 }
			 else
			 {
				 strMsg.Format("%d	%.2f	%d	%u	%d	%d	%d	Pass",m_vChannelList[iCHIndex],m_vRXPower[iGainIndex],m_vBitMask[iGainIndex],iRSSIValue,iOffsetValue,m_vRXLimitLow[iGainIndex],m_vRXLimitUp[iGainIndex]);
				 LogTrace(MSG_MID,strMsg)				
			 }		
		}  
	}
	if (iFailflag>0)
	{
		CalFailLog(m_strBand,"_",1001,"RxGainOffset is out of range")
		return false;
	}  
	CalPassLog(m_strBand,"_","Rx Calibration Pass");
	return true;
}

bool CGSMRXCal::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
	
    CStringStringMapItr itrFind;
	CString strValue;
     CString strMainFun;
	 itrFind=pcSettingMap->find(_T("MainFunc"));
	 if(itrFind==pcSettingMap->end())
		 return false;
	 else
	 {
		 if(!SetMainFunc(itrFind->second))
			 return false;
	 }

	 CString strFuncList;
	 itrFind=pcSettingMap->find(_T("List"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_FATAL,_T("Not Find List"));
		 return false;
	 }
	 strFuncList=itrFind->second;
     CStringVtr strVtr;

	 CStr::ParseString(strFuncList,_T(","),strVtr);
     CString strfunc;
	 m_vFPTestFunc.clear();
	 for(CStringItr itrFunc=strVtr.begin();itrFunc!=strVtr.end();++itrFunc)
	 {
		strfunc=*itrFunc;
		map<CString,FPClassFunc>::iterator itrMap=m_mapClassFunc.find(strfunc);
		if(itrMap==m_mapClassFunc.end())
			return false;
		m_vFPTestFunc.push_back(itrMap->second);
		

	 }
 
    
      itrFind=pcSettingMap->find(_T("TesterDeviceUse"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not find TestDeviceUse,use TesterDeviceCommon");
		 //return false;
		 m_piTesterDeviceCurr=m_piTesterDevice;
		 m_strTesterDeviceCurr=m_strTesterDevice;
		 m_strDeviceAddrCurr=m_strDeviceAddr;
	 }
	 else
	 {
		 if(itrFind->second=="TesterDeviceCommon")
		 {
			 m_piTesterDeviceCurr=m_piTesterDevice;
			 m_strTesterDeviceCurr=m_strTesterDevice;
			 m_strDeviceAddrCurr=m_strDeviceAddr;
		 }
	 }

	  itrFind=pcSettingMap->find(_T("WaveFilePath"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'WaveFilePath' from ini file!.Default is \'D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\gmskdigmod.wv\'");
		 m_strWaveFile="D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\gmskdigmod.wv";
	 }
	 else
	 {
	
		 m_strWaveFile=itrFind->second;
	 }
    

	  itrFind=pcSettingMap->find(_T("RXCalPowerList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'RXCalPowerList' from ini file!.");
		 return false;
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2DblVtr(m_vRXPower,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("ChannelList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'ChannelList' from ini file!.");
		 return false;
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vChannelList,strVtr);
	 }
	 itrFind=pcSettingMap->find(_T("ChainId"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'ChainId' from ini file!.default is 0.");
		 m_iChainId=0;
	 }
	 else
	 {
		 m_iChainId=CStr::StrToInt(itrFind->second);		 
	 }

	 itrFind=pcSettingMap->find(_T("BitMask"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'BitMask' from ini file!.");
		 return false;
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vBitMask,strVtr);
	 }

	  itrFind=pcSettingMap->find(_T("RXLimitUp"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'RXLimitUp' from ini file!.");
		 return false;
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vRXLimitUp,strVtr);
	 }

	 itrFind=pcSettingMap->find(_T("RXLimitLow"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'RXLimitLow' from ini file!.");
		 return false;
	 }
	 else
	 {
		 CStr::ParseString(itrFind->second,",",strVtr);
		 CStr::StrVtr2IntVtr(m_vRXLimitLow,strVtr);
	 }



	  itrFind=pcSettingMap->find(_T("GainRangeCount"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'GainRangeCount' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_ucGainRangeCount=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("Band"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'Band' from ini file!.");
		 return false;
	 }
	 else
	 {
		 m_iBand=CStr::StrToInt(itrFind->second);
		 m_strBand="GSM"+itrFind->second;
		 m_iPhoneMode=CGSMBandInfo::GetPhoneMode(m_iBand);
	 }
    
     
	 InitData();
	 return true;
 }

 bool CGSMRXCal::InitData()
 {
	 m_pFunGSMCalDev=m_piTesterDevice->m_piFuncGSMCal;
	 return true;
 }