#include "StdAfx.h"
#include "PowerSlyControl.h"
RF_IMPLEMENT_DYNCREATE(CPowerSlyControl)

CPowerSlyControl::CPowerSlyControl(void)
{
	m_mapClassFunc[_T("PlyControlMainFunc")]=&CPowerSlyControl::CPowerSlyControlMainFunc;
	m_mapClassFunc[_T("StartPly")]=&CPowerSlyControl::StartPly;
	m_mapClassFunc[_T("StopPly")]=&CPowerSlyControl::StopPly;	
	m_mapClassFunc[_T("GetCurrent")]=&CPowerSlyControl::GetCurrent;


	m_iItemCode=1004;
}

CPowerSlyControl::~CPowerSlyControl(void)
{
}
bool CPowerSlyControl::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CPowerSlyControl::Handle()
{
	if(!DoProcess())
	{
        
		return false;
	}
	return true;
}
bool CPowerSlyControl::StopPly()
{

	 CString strMsg;
	int iErrorcode;
     if(m_piPowerSlyCurr==NULL)
	 {
		 strMsg.Format("No PowerSupply Selected!");
		 LogTrace(MSG_LOW,_T(strMsg));
		 CalPassLog(_T("_"),_T("_"),_T(strMsg));
		 //MessageBox(m_hMsgHandlingWnd,strMsg,"PopMSG",MB_OK);
		 return true;
	 }

	   if((iErrorcode=m_piPowerSlyCurr->InitDevice(m_strPlyAddrCurr,m_iPlyPortCurr))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Init Powersupply fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Init Powersupply fail");
			return false;
		  
	   }

      
	 if((iErrorcode=m_piPowerSlyCurr->PSSetOuptON(false))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Set Powersupply On fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Powersupply On fail");
			return false;
		  
	   }

	  m_piPowerSlyCurr->PS_Release();
	 return true;
}
bool CPowerSlyControl::GetCurrent()
{
	CString strMsg;
	int iErrorcode;
	float fCurrent=0;
	float fSUMCurrent=0;
	if(m_piPowerSlyCurr==NULL)
	{
		strMsg.Format("No PowerSupply Selected!");
		LogTrace(MSG_LOW,_T(strMsg));
		CalPassLog(_T("_"),_T("_"),_T(strMsg));
		//MessageBox(m_hMsgHandlingWnd,strMsg,"PopMSG",MB_OK);
		return true;
	}

	if((iErrorcode=m_piPowerSlyCurr->InitDevice(m_strPlyAddrCurr,m_iPlyPortCurr))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Init Powersupply fail");
		CalFailLog(_T("_"),_T("_"),iErrorcode,"Init Powersupply fail");
		return false;

	}

	for (int i=0;i<m_iMeasCount;i++)
	{
		if((iErrorcode=m_piPowerSlyCurr->PS_GetCurrent(&fCurrent))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Get PS current fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Get PS current fail");
			return false;

		}
		Sleep(m_iSmplInter_ms);
		fSUMCurrent+=fCurrent;
	}
	fCurrent=fSUMCurrent/m_iMeasCount;

	if (fCurrent>m_fCurrentLowLimit&&fCurrent<m_fCurrentHiLimit)
	{
		TestPassLogEx(_T("-"),_T("-"),_T(CStr::FloatToStr(m_fCurrentHiLimit)),_T(CStr::FloatToStr(m_fCurrentLowLimit)),_T(CStr::FloatToStr(fCurrent)),_T("-"),_T("Current PASS"),"Current")

	}
	else
	{
		TestFailLogEx(_T("-"),_T("-"),0000,_T(CStr::FloatToStr(m_fCurrentHiLimit)),_T(CStr::FloatToStr(m_fCurrentLowLimit)),_T(CStr::FloatToStr(fCurrent)),_T("-"),_T("Current FAIL"),"Current")
		
	}
	
	

	m_piPowerSlyCurr->PS_Release();
	return true;
}
bool CPowerSlyControl::StartPly()
{
	
	CString strMsg;
	int iErrorcode;

	 if(m_piPowerSlyCurr==NULL)
	 {
		 strMsg.Format("No PowerSupply Selected!");
		 LogTrace(MSG_LOW,_T(strMsg));
		 CalPassLog(_T("_"),_T("_"),_T(strMsg));
		 //MessageBox(m_hMsgHandlingWnd,strMsg,"PopMSG",MB_OK);
		 return true;
	 }
     if((iErrorcode=m_piPowerSlyCurr->InitDevice(m_strPlyAddrCurr,m_iPlyPortCurr))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Init Powersupply fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Init Powersupply fail");
			return false;
		  
	   }

	  if((iErrorcode=m_piPowerSlyCurr->PSSetOuptON())!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Set Powersupply On fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Powersupply On fail");
			return false;
		  
	   }
      
	 if((iErrorcode=m_piPowerSlyCurr->PS_SetVoltage(m_dVoltage))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Set Powersupply Voltage fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Powersupply Voltage fail");
			return false;
		  
	   }

	  if((iErrorcode=m_piPowerSlyCurr->PS_SetCurrentLimit(m_dCurrentLimit))!=DEVICE_SUCCESS)
	   {
			LogTrace(MSG_ERROR,"Set Powersupply Current limit fail");
			CalFailLog(_T("_"),_T("_"),iErrorcode,"Set Powersupply Current limit fail");
			return false;
		  
	   }


     m_piPowerSlyCurr->PS_Release();

	 return true;
}

 bool CPowerSlyControl::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
    CStringStringMapItr itrFind;
	CString strValue;
     CString strMainFun;
     CStringVtr strVtr;
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

		if(strfunc=="StartPly")
		{
					  itrFind=pcSettingMap->find(_T("Voltage"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_ERROR,"Not Find 'Voltage' from ini file!");
						 return false;
					 }
					 else
					 {
					 
						 m_dVoltage=CStr::StrToFloat(itrFind->second);
					 }

					  itrFind=pcSettingMap->find(_T("CurrentLimit"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_ERROR,"Not Find 'CurrentLimit' from ini file!");
						 return false;
					 }
					 else
					 {
						 m_dCurrentLimit=CStr::StrToFloat(itrFind->second);
					 }

					   itrFind=pcSettingMap->find(_T("CurrentMode"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_WARNING,"Not Find 'CurrentMode' from ini file!Defalt is A");
						 m_iCurrentMode=0;  
					 }
					 else
					 {
						 m_iCurrentMode=atoi(itrFind->second);
					 }
		}

		if(strfunc=="GetCurrent")
		{
			itrFind=pcSettingMap->find(_T("SmplInter_ms"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'SmplInter_ms' from ini file!");
				return false;
			}
			else
			{

				m_iSmplInter_ms=CStr::StrToInt(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("MeasCount"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'MeasCount' from ini file!");
				return false;
			}
			else
			{
				m_iMeasCount=CStr::StrToInt(itrFind->second);
			}
			itrFind=pcSettingMap->find(_T("CurrentLowLimit"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'CurrentLowLimit' from ini file!");
				return false;
			}
			else
			{
				m_fCurrentLowLimit=CStr::StrToFloat(itrFind->second);
			}
			itrFind=pcSettingMap->find(_T("CurrentHiLimit"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'CurrentHiLimit' from ini file!");
				return false;
			}
			else
			{
				m_fCurrentHiLimit=CStr::StrToFloat(itrFind->second);
			}
			
		}
		
	 }
    
   itrFind=pcSettingMap->find(_T("PowerSlyUse"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not find PowerSlyUse,use PowerSlyUseCommon");
		  
		    m_piPowerSlyCurr=m_piPowerSly;
			m_strPlyNameCurr=m_strPlyName;
			m_strPlyAddrCurr=m_strPlyAddr;
			
			m_iPlyPortCurr=m_iPlyPort;
	 }
	 else
	 {
		 if(itrFind->second=="TesterDeviceCommon")
		 {
			  m_piPowerSlyCurr=m_piPowerSly;
			m_strPlyNameCurr=m_strPlyName;
			
			m_strPlyAddrCurr=m_strPlyAddr;
			m_iPlyPortCurr=m_iPlyPort;
		 }
	 }
	      
  
	 InitData();
	 return true;
 }

 bool CPowerSlyControl::CPowerSlyControlMainFunc()
 {
	 for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	
	 return true;

 }


 bool CPowerSlyControl::InitData()
 {
	
	 return true;
 }