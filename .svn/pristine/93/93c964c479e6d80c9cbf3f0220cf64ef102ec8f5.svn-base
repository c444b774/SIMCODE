#include "stdafx.h"
#include "QTR8615TThermCal.h"
RF_IMPLEMENT_DYNCREATE(CQTR8615TThermCal)

CQTR8615TThermCal::CQTR8615TThermCal()
{
	m_mapClassFunc[_T("QTR8615TThermCalMainFunc")]=&CQTR8615TThermCal::CQTR8615TThermCalMainFunc;
	m_mapClassFunc[_T("QTR8615TThermCalFunc")]=&CQTR8615TThermCal::CQTR8615TThermCalFunc;


}

CQTR8615TThermCal::~CQTR8615TThermCal()
{
	
}

bool CQTR8615TThermCal::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CQTR8615TThermCal::Handle()
{
	if(!DoProcess())
	{

			m_pPhone->CloseComport();
		return false;
	}

	CalPassLog("_","_","ThermCalibration Cal Pass");

	return true;
}

bool CQTR8615TThermCal::CQTR8615TThermCalMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CQTR8615TThermCal::CQTR8615TThermCalFunc()
{
	  CString strMsg;
      int iErrorcode;

		unsigned long HKADC=0;  
		unsigned char readValues[17]={'\0'}; 
		unsigned long bb[2]={0,0};  
		unsigned short iStatus=0; 
		
		int i=0;
		QMSL_Internal_Thermistor_Cal_Meas_struct Thermistor_Cal_Meas;
		
	   QMSL_Internal_Thermistor_Cal_NV_struct Internal_Thermistor_Cal_NV={0};	
		QMSL_RFCal_WriteToPhone_Status   QMSL_RFCal_WriteToPhone;
		memset(&Thermistor_Cal_Meas,0,sizeof(Thermistor_Cal_Meas));
		Thermistor_Cal_Meas.bFillNVThermBins=m_iIsFillThermBins;
		Thermistor_Cal_Meas.bUseEnhTherm=1;
		Thermistor_Cal_Meas.bUseOffsetsForThermBinNV=m_iIsUseOffsetThermBin;    
		   Thermistor_Cal_Meas.bUseTwoSlopes=1;
		   Thermistor_Cal_Meas.dMaxTempSlope=m_dHotSLope;
		  Thermistor_Cal_Meas.dMinTempSlope=m_dColdSLope;
		  Thermistor_Cal_Meas.dSlope=-2;
		  Thermistor_Cal_Meas.iCalTemp=m_iCalTemp;
		   Thermistor_Cal_Meas.iHKADCAtCalTemp=3;
		    Thermistor_Cal_Meas.iMaxTemp=m_iMaxTemp;
			Thermistor_Cal_Meas.iMinTemp=m_iMinTemp;

	if((iErrorcode=m_pPhone->FTM_SET_MODE_ID(1))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode ID  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	
	if((iErrorcode=m_pPhone->FTM_SET_MODE(PHONE_MODE_WCDMA_IMT))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("Phone Set Mode (Band)  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	if((iErrorcode=m_pPhone->FTM_GET_ENH_THERM(&HKADC))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_GET_ENH_THERM  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	Sleep(100);
		if((iErrorcode=m_pPhone->FTM_GET_ENH_THERM(&HKADC))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_GET_ENH_THERM  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

		
	Sleep(100);
			if((iErrorcode=m_pPhone->FTM_GET_ENH_THERM(&HKADC))!=PHONE_SUCCESS)
	{ 
		strMsg.Format("FTM_GET_ENH_THERM  Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
    Thermistor_Cal_Meas.iEnhThermAtCalTemp=HKADC;  

	if(!m_pPhone->IsPhoneConnected())
	{ 
		strMsg.Format("Phone connected Fail!");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
	if(HKADC<=0 || HKADC>=4096)
	{
      strMsg.Format("ADC Value Fail! Value=%d!",HKADC);
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

	iErrorcode=m_pPhone->RFCAL_Internal_Thermistor_Calibration_Results(&Thermistor_Cal_Meas,&Internal_Thermistor_Cal_NV,1);
	if(iErrorcode!=PHONE_SUCCESS)
	{
       strMsg.Format("RFCAL_Internal_Thermistor_Calibration_Results Fail");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}

    iErrorcode=m_pPhone->RFCAL_NV_Manager_WriteToPhone(&QMSL_RFCal_WriteToPhone);

	if(iErrorcode!=PHONE_SUCCESS)
	{
       strMsg.Format("RFCAL_NV_Manager_WriteToPhone Fail");
		LogTrace(MSG_ERROR,strMsg)
		m_iErrorcode=iErrorcode;
	    CalFailLog(_T("_"),_T("_"),iErrorcode,strMsg);
		return false;
	}
		
	return true;
}

 bool CQTR8615TThermCal::InitData(
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



     
	   itrFind=pcSettingMap->find(_T("ColdSLope"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'ColdSLope' from ini file!.default is -4.4");
		 m_dColdSLope=-4.4;
	 }
	 else
	 {
		 m_dColdSLope=CStr::StrToFloat(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("HotSLope"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'HotSLope' from ini file!.default is -4.6");
		 m_dHotSLope=-4.6;
	 }
	 else
	 {
		 m_dHotSLope=CStr::StrToFloat(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("NormalTemperature"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'NormalTemperature' from ini file!.default is 25");
		 m_iCalTemp=25;
	 }
	 else
	 {
		 m_iCalTemp=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("MaxTemperature"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'm_iMaxTemp' from ini file!.default is 85");
		 m_iMaxTemp=85;
	 }
	 else
	 {
		 m_iMaxTemp=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("MinTemperature"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'MinTemperature' from ini file!.default is -30");
		 m_iMinTemp=-30;
	 }
	 else
	 {
		 m_iMinTemp=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("IsFillNVThermBins"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'IsFillNVThermBins' from ini file!.default is false");
		 m_iIsFillThermBins=0;
	 }
	 else
	 {
		 m_iIsFillThermBins=CStr::StrToInt(itrFind->second);
	 }

	 itrFind=pcSettingMap->find(_T("IsUseOffsetThermBins"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'IsUseOffsetThermBins' from ini file!.default is false");
		 m_iIsUseOffsetThermBin=0;
	 }
	 else
	 {
		 m_iIsUseOffsetThermBin=CStr::StrToInt(itrFind->second);
	 }


    

	 InitData();
	 return true;
 }

 bool CQTR8615TThermCal::InitData()
 {
	
	 return true;
 }