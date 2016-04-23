#include "StdAfx.h"
#include "CGeneralTest.h"
RF_IMPLEMENT_DYNCREATE(CGeneralTest)

CGeneralTest::CGeneralTest(void)
{

	m_mapClassFunc[_T("GeTestMainFunc")]=&CGeneralTest::CGeneralTestlMainFunc;
	m_mapClassFunc[_T("32KTest")]=&CGeneralTest::C32KRTCTestFunc;
	m_mapClassFunc[_T("BackBattTest")]=&CGeneralTest::CBackBattFunc;	
	m_mapClassFunc[_T("OffCurrTest")]=&CGeneralTest::COffCurrFunc;
	m_mapClassFunc[_T("CharCurrTest")]=&CGeneralTest::CCharCurrFunc;

	m_iItemCode=1005;
}

CGeneralTest::~CGeneralTest(void)
{
}
bool CGeneralTest::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGeneralTest::Handle()
{
	if(!DoProcess())
	{
		
        
		return false;
	}
	return true;
}

 bool CGeneralTest::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
    CStringStringMapItr itrFind;
	CString strValue;
     CString strMainFun;
     CStringVtr strVtr;
	 CStringVtr strVtrFuncList;
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
    

	 CStr::ParseString(strFuncList,_T(","),strVtrFuncList);
     CString strfunc;
	 m_vFPTestFunc.clear();

	 for(CStringItr itrFunc=strVtrFuncList.begin();itrFunc!=strVtrFuncList.end();++itrFunc)
	 {
		strfunc=*itrFunc;
		map<CString,FPClassFunc>::iterator itrMap=m_mapClassFunc.find(strfunc);
		if(itrMap==m_mapClassFunc.end())
			return false;
		m_vFPTestFunc.push_back(itrMap->second);

		if(strfunc=="32KTest")
		{

                    itrFind=pcSettingMap->find(_T("C32KAvgCount"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_ERROR,"Not Find 'C32KAvgCount' from ini file!");
						 return false;
					 }
					 else
					 {
					 
						 m_i32KAvgCount=CStr::StrToInt(itrFind->second);
					 }

					   itrFind=pcSettingMap->find(_T("C32KFreqLimit"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_ERROR,"Not Find 'C32KFreqLimit' from ini file!");
						 return false;
					 }
					 else
					 {
					 
						 strValue=itrFind->second;
						 CStr::ParseString(strValue,",",strVtr);
						 m_r32KFreqLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
					 }

					   itrFind=pcSettingMap->find(_T("C32KRetryTimes"));
					 if(itrFind==pcSettingMap->end())
					 {
						 LogTrace(MSG_ERROR,"Not Find 'C32KRetryTimes' from ini file!");
						 return false;
					 }
					 else
					 {
					 
						m_i32KRetryTimes=CStr::StrToInt(itrFind->second);
					 }
					 

					 
		}
		else if(strfunc=="BackBattTest")
		{

			  itrFind=pcSettingMap->find(_T("BackAvgCount"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'BackAvgCount' from ini file!");
				 return false;
			 }
			 else
			 {
			 
				 m_iBackAvgCount=CStr::StrToInt(itrFind->second);
			 }

			 itrFind=pcSettingMap->find(_T("TargetVol"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'TargetVol' from ini file!");
				 return false;
			 }
			 else
			 {

				 m_fTargetVol=CStr::StrToFloat(itrFind->second);
			 }

			 itrFind=pcSettingMap->find(_T("BackRetryTimes"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'BackRetryTimes' from ini file!");
				 return false;
			 }
			 else
			 {

				 m_iBackRetryTimes=CStr::StrToInt(itrFind->second);
			 }

			 itrFind=pcSettingMap->find(_T("BackupWaitTime"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'BackupWaitTime' from ini file!");
				 return false;
			 }
			 else
			 {

				 m_iBackupWaitTime=CStr::StrToInt(itrFind->second);
			 }

            itrFind=pcSettingMap->find(_T("BackCharLimit"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'BackCharLimit' from ini file!");
				 return false;
			 }
			 else
			 {
			 
				 strValue=itrFind->second;
				 CStr::ParseString(strValue,",",strVtr);
				 m_rBackCharLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
			 }
			 itrFind=pcSettingMap->find(_T("BackDisCharLimit"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'BackDisCharLimit' from ini file!");
				 return false;
			 }
			 else
			 {

				 strValue=itrFind->second;
				 CStr::ParseString(strValue,",",strVtr);
				 m_rBackDisCharLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
			 }
		}
		else if(strfunc=="OffCurrTest")
		{

			itrFind=pcSettingMap->find(_T("OffCurrentAvgCount"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'OffCurrentAvgCount' from ini file!");
				return false;
			}
			else
			{

				m_iOffCurrentAvgCount=CStr::StrToInt(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("CurrRetryTimes"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'CurrRetryTimes' from ini file!");
				return false;
			}
			else
			{

				m_iCurrRetryTimes=CStr::StrToInt(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("OffCurrentLimit"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'OffCurrentLimit' from ini file!");
				return false;
			}
			else
			{

				strValue=itrFind->second;
				CStr::ParseString(strValue,",",strVtr);
				m_rOffCurrentLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
			}
		}
		else if(strfunc=="CharCurrTest")
		{

			itrFind=pcSettingMap->find(_T("CharAvgCount"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'CharAvgCount' from ini file!");
				return false;
			}
			else
			{

				m_iCharAvgCount=CStr::StrToInt(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("CurrRetryTimes"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'CurrRetryTimes' from ini file!");
				return false;
			}
			else
			{

				m_iCurrRetryTimes=CStr::StrToInt(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("CharCurrentLimit"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_ERROR,"Not Find 'CharCurrentLimit' from ini file!");
				return false;
			}
			else
			{

				strValue=itrFind->second;
				CStr::ParseString(strValue,",",strVtr);
				m_rCharCurrentLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
			}
		}

		
	 }
      
  
	      
  
	 InitData();
	 return true;
 }
 bool CGeneralTest::C32KRTCTestFunc()
 {

     CString strMsg;
	 int iErrorCode;
	 double dFreq;
     strMsg.Format("Start 32KRCT testing....");
	 LogTrace(MSG_MID,strMsg)

		 
		 if(!m_piFreqMeasDevice)
		 {
           strMsg="Freq Measure device not selected.";
		   LogTrace(MSG_WARNING,strMsg)
		   return false;
		 }

	
		  if((iErrorCode=m_piFreqMeasDevice->InitDevice(m_strFreqMeasAddr,0))!=DEVICE_SUCCESS)
		   {
				LogTrace(MSG_ERROR,"Init FreqMeasDevice fail");
				CalFailLog(_T("_"),_T("_"),iErrorCode,"Init FreqMeasDevice fail");
				return false;
			  
		   }
	
	    Sleep(2000);

	
		  do
		  {

				  if((iErrorCode=m_piFreqMeasDevice->MeasureFreq(dFreq,m_i32KAvgCount))!=DEVICE_SUCCESS)
				   {
						LogTrace(MSG_ERROR," MeasureFreq fail");
						CalFailLog(_T("_"),_T("_"),iErrorCode," MeasureFreq fail");
						m_piFreqMeasDevice->GenFreqMeas_Release();
						return false;
					  
				   }

				  if(m_r32KFreqLimit.InRange(dFreq))
				  {
					   strMsg.Format("32K RCT Test Pass");
					   TestPassLog("_","_",CStr::FloatToStr(m_r32KFreqLimit.GetMax()),CStr::FloatToStr(m_r32KFreqLimit.GetMin()),CStr::FloatToStr(dFreq),"HZ",strMsg)
					   m_piFreqMeasDevice->GenFreqMeas_Release();
						   return true;
				  }
		  Sleep(100);

		  }while(--m_i32KRetryTimes>0);

		  if(m_i32KRetryTimes==0)
		  {
			   strMsg.Format("32K RCT Test Fail");
			   TestFailLog("_","_",2000,CStr::FloatToStr(m_r32KFreqLimit.GetMax()),CStr::FloatToStr(m_r32KFreqLimit.GetMin()),CStr::FloatToStr(dFreq),"HZ",strMsg)
			   m_piFreqMeasDevice->GenFreqMeas_Release();
				   return false;
		  }
	
	 return true;
 }
bool CGeneralTest::CBackBattFunc()
{
	CString strMsg;
	int iErrorCode;
	double dMeasVol;
	int iFailflag=0;
	int iRetrytime=m_iCurrRetryTimes;
	strMsg.Format("Start Backup Battery testing....");
	LogTrace(MSG_MID,strMsg)


	if(!m_piMultiMeasDevice)
	{
		strMsg="Multi Measure device not selected.";
		LogTrace(MSG_WARNING,strMsg)
		return false;
	}
	if(!m_piPowerSly)
	{
		strMsg="Power Supply device not selected.";
		LogTrace(MSG_WARNING,strMsg)
			return false;
	}

	if((iErrorCode=m_piMultiMeasDevice->InitDevice(m_strMultiMeasDevice,0))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Init MultiMeasDevice fail");
		CalFailLog(_T("_"),_T("_"),iErrorCode,"Init MultiMeasDevice fail");
		return false;
	}
	if((iErrorCode=m_piPowerSly->InitDevice(m_strPlyAddr,m_iPlyPort))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Init Power Supply Device fail");
		CalFailLog(_T("_"),_T("_"),iErrorCode,"Init PS Device fail");
		m_piMultiMeasDevice->Release();
		m_piPowerSly->Release();
		return false;
	}
	CalPassLog(_T("_"),_T("_"),"Init Devices fail")

	if((iErrorCode=m_piPowerSly->PS_SetVoltage(4.0))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Set PS Voltage to 4.0 fail");
		CalFailLog(_T("_"),_T("_"),iErrorCode,"Set PS Voltage to 4.0 fail");
		m_piMultiMeasDevice->Release();
		m_piPowerSly->Release();
		return false;
	}
	//**************************************************************************Backup Battery charge test
	if((iErrorCode=m_piPowerSly->PSSetOuptON(true))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Turn On PS fail");
		CalFailLog(_T("_"),_T("_"),iErrorCode,"Turn On PS fail");
		m_piMultiMeasDevice->Release();
		m_piPowerSly->Release();
		return false;
	}
	do 
	{
		if((iErrorCode=m_piMultiMeasDevice->MeasureVoltage(dMeasVol,5))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Measure Voltage fail");
			CalFailLog(_T("_"),_T("_"),iErrorCode,"Measure Voltage fail");
			m_piMultiMeasDevice->Release();
			m_piPowerSly->Release();
			return false;
		}
		if(m_rBackDisCharLimit.InRange(m_fBattVol))
		{
			strMsg.Format("Backup Battery Char Test Pass");
			TestPassLog("_","_",CStr::FloatToStr(m_rBackCharLimit.GetMax()),CStr::FloatToStr(m_rBackCharLimit.GetMin()),CStr::FloatToStr(dMeasVol),"mV",strMsg)
			break;
		}

	} while (--iRetrytime>0);
	if(m_iBackRetryTimes==0)
	{
		strMsg.Format("Backup Battery Char Test Fail");
		TestFailLog("_","_",iErrorCode,CStr::FloatToStr(m_rBackCharLimit.GetMax()),CStr::FloatToStr(m_rBackCharLimit.GetMin()),CStr::FloatToStr(dMeasVol),"mV",strMsg)
			iFailflag++;
	}
	if (iFailflag>0&&m_bIsStopWhenFail)
	{
		m_piMultiMeasDevice->Release();
		m_piPowerSly->Release();
		return false;
	}
	//****************************************************************************** Wait Backup Battery Voltage  
	iRetrytime=m_iBackupWaitTime;
	do 
	{
		if((iErrorCode=m_piMultiMeasDevice->MeasureVoltage(dMeasVol,5))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Measure Voltage fail");
			CalFailLog(_T("_"),_T("_"),iErrorCode,"Measure Voltage fail");
			m_piMultiMeasDevice->Release();
			m_piPowerSly->Release();
			return false;
		}
		strMsg.Format("Backup Battery Voltage is %.2f,Target Voltage is %.2f",dMeasVol,m_fTargetVol);
		LogTrace(MSG_WARNING,strMsg);
		if(dMeasVol<m_fTargetVol)
		{
			break;
		}
		Sleep(200);

	} while (--iRetrytime>0);
	//***************************************************************************Backup Battery discharge test

	if((iErrorCode=m_piPowerSly->PSSetOuptON(false))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Turn Off PS fail");
		CalFailLog(_T("_"),_T("_"),iErrorCode,"Turn Off PS fail");
		m_piMultiMeasDevice->Release();
		m_piPowerSly->Release();
		return false;
	}
	iRetrytime=m_iCurrRetryTimes;
	do 
	{
		if((iErrorCode=m_piMultiMeasDevice->MeasureVoltage(dMeasVol,5))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Measure Voltage fail");
			CalFailLog(_T("_"),_T("_"),iErrorCode,"Measure Voltage fail");
			m_piMultiMeasDevice->Release();
			m_piPowerSly->Release();
			return false;
		}
		if(m_rBackDisCharLimit.InRange(dMeasVol))
		{
			strMsg.Format("Backup Battery DisChar Test Pass");
			TestPassLog("_","_",CStr::FloatToStr(m_rBackDisCharLimit.GetMax()),CStr::FloatToStr(m_rBackDisCharLimit.GetMin()),CStr::FloatToStr(dMeasVol),"mV",strMsg)
				break;
		}

	} while (--iRetrytime>0);
	if(iRetrytime==0)
	{
		strMsg.Format("Backup Battery DisChar Test Fail");
		TestFailLog("_","_",iErrorCode,CStr::FloatToStr(m_rBackDisCharLimit.GetMax()),CStr::FloatToStr(m_rBackDisCharLimit.GetMin()),CStr::FloatToStr(dMeasVol),"mV",strMsg)
			iFailflag++;
	}
	if (iFailflag>0&&m_bIsStopWhenFail)
	{
		m_piMultiMeasDevice->Release();
		m_piPowerSly->Release();
		return false;
	}
	m_piMultiMeasDevice->Release();
	m_piPowerSly->Release();

	return true;
}
bool CGeneralTest::COffCurrFunc()
{
	CString strMsg;
	int iErrorCode;
	float dMeasCurr;
	int iFailflag=0;
	int iRetrytime=m_iCurrRetryTimes;
	strMsg=_T("Start Power Off Current testing....");
	LogTrace(MSG_MID,strMsg)

	if(!m_piPowerSly)
	{
		strMsg="Power Supply device not selected.";
		LogTrace(MSG_WARNING,strMsg)
			return false;
	}

	if((iErrorCode=m_piPowerSly->InitDevice(m_strPlyAddr,m_iPlyPort))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Init Power Supply Device fail");
		CalFailLog(_T("_"),_T("_"),iErrorCode,"Init PS Device fail");
		m_piPowerSly->Release();
		return false;
	}
	if((iErrorCode=m_piPowerSly->PSSetOuptON(false))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Turn Off PS fail");
		CalFailLog(_T("_"),_T("_"),iErrorCode,"Turn Off PS fail");
		m_piPowerSly->Release();
		return false;
	}
	CalPassLog(_T("_"),_T("_"),"Turn Off PS Pass");
	do 
	{
		if((iErrorCode=m_piPowerSly->PS_GetCurrent(&dMeasCurr))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Measure PS Current fail");
			CalFailLog(_T("_"),_T("_"),iErrorCode,"Measure PS Current fail");
			m_piPowerSly->Release();
			return false;
		}
		if(m_rOffCurrentLimit.InRange(dMeasCurr))
		{
			strMsg.Format("Power Off Current Test Pass");
			TestPassLog("_","_",CStr::FloatToStr(m_rOffCurrentLimit.GetMax()),CStr::FloatToStr(m_rOffCurrentLimit.GetMin()),CStr::FloatToStr(dMeasCurr),"mA",strMsg)
				break;
		}
		Sleep(100);
	} while (--iRetrytime>0);
	if(iRetrytime==0)
	{
		strMsg.Format("Power off current Test Fail");
		TestFailLog("_","_",iErrorCode,CStr::FloatToStr(m_rOffCurrentLimit.GetMax()),CStr::FloatToStr(m_rOffCurrentLimit.GetMin()),CStr::FloatToStr(dMeasCurr),"mA",strMsg)
			iFailflag++;
	}
	if (iFailflag>0&&m_bIsStopWhenFail)
	{
		m_piPowerSly->Release();
		return false;
	}
	m_piPowerSly->Release();
	return true;
}
bool CGeneralTest::CCharCurrFunc()
{
	CString strMsg;
	int iErrorCode;
	float dMeasCurr;
	int iFailflag=0;
	int iRetrytime=m_iCurrRetryTimes;
	strMsg=_T("Start Charger Current testing....");
	LogTrace(MSG_MID,strMsg)

		if(!m_piPowerSly)
		{
			strMsg="Power Supply device not selected.";
			LogTrace(MSG_WARNING,strMsg)
				return false;
		}

		if((iErrorCode=m_piPowerSly->InitDevice(m_strPlyAddr,m_iPlyPort))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Init Power Supply Device fail");
			CalFailLog(_T("_"),_T("_"),iErrorCode,"Init PS Device fail");
			m_piPowerSly->Release();
			return false;
		}
		if((iErrorCode=m_piPowerSly->PS_SetVoltage(3.7))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"PS Set Voltage to 3.7 fail");
			CalFailLog(_T("_"),_T("_"),iErrorCode,"PS Set Voltage to 3.7 fail");
			m_piPowerSly->Release();
			return false;
		}
		if((iErrorCode=m_piPowerSly->PSSetOuptON(false))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Turn Off PS fail");
			CalFailLog(_T("_"),_T("_"),iErrorCode,"Turn Off PS fail");
			m_piPowerSly->Release();
			return false;
		}
		CalPassLog(_T("_"),_T("_"),"PS Set Voltage to 3.7 Pass");
		MessageBox(NULL,_T("please plugin the USB cable"),_T("Warning"),MB_OK);
		do 
		{
			if((iErrorCode=m_piPowerSly->PS_GetCurrent( &dMeasCurr))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Measure PS Current fail");
				CalFailLog(_T("_"),_T("_"),iErrorCode,"Measure PS Current fail");
				m_piPowerSly->Release();
				return false;
			}
			if(m_rCharCurrentLimit.InRange(dMeasCurr))
			{
				strMsg.Format("Charge Current Test Pass");
				TestPassLog("_","_",CStr::FloatToStr(m_rCharCurrentLimit.GetMax()),CStr::FloatToStr(m_rCharCurrentLimit.GetMin()),CStr::FloatToStr(dMeasCurr),"mA",strMsg)
					break;
			}
			Sleep(100);
		} while (--iRetrytime>0);
		if(iRetrytime==0)
		{
			strMsg.Format("Charge current Test Fail");
			TestFailLog("_","_",iErrorCode,CStr::FloatToStr(m_rCharCurrentLimit.GetMax()),CStr::FloatToStr(m_rCharCurrentLimit.GetMin()),CStr::FloatToStr(dMeasCurr),"mA",strMsg)
				iFailflag++;
		}
		if (iFailflag>0&&m_bIsStopWhenFail)
		{
			m_piPowerSly->Release();
			return false;
		}
		m_piPowerSly->Release();
		return true;
	return true;
}
 bool CGeneralTest::CGeneralTestlMainFunc()
 {
	 for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	
	 return true;

 }


 bool CGeneralTest::InitData()
 {
	
	 return true;
 }