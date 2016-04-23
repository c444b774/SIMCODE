#include "StdAfx.h"
#include "GPSTestProc.h"
RF_IMPLEMENT_DYNCREATE(CGPSTestProc)
CGPSTestProc::CGPSTestProc(void)
{
	m_mapClassFunc[_T("GPSTestCallMainFunc")]=&CGPSTestProc::GPSTestMainFunc;
	m_mapClassFunc[_T("GPSCalLossMainFunc")]=&CGPSTestProc::GPSCalLossMailFunc;
    m_mapClassFunc[_T("GPSTestRXFunc")]=&CGPSTestProc::GPSTestRXFunc;
	m_mapClassFunc[_T("GPSTestGen8")]=&CGPSTestProc::GPSTestGen8;
	 m_mapClassFunc[_T("GPSTestRX_AT")]=&CGPSTestProc::GPSTestRX_AT;
    m_mapClassFunc[_T("GPSLossCal")]=&CGPSTestProc::GPSCalLossFunc;
	m_iItemCode=1005;
}

CGPSTestProc::~CGPSTestProc(void)
{
}
bool CGPSTestProc::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGPSTestProc::Handle()
{
	if(!DoProcess())
	{
		GPSDIAG_Exit();

		return false;
	}
	GPSDIAG_Exit();
   
	return true;
}

 bool CGPSTestProc::InitData(
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
	 strMainFun=itrFind->second;
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
	 }
    
     itrFind=pcSettingMap->find(_T("CellPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'CellPower' from ini file!");
		 return false;
	 }
	 else
	 {
		 m_dCellPower=CStr::StrToFloat(itrFind->second);
	 } 
	 itrFind=pcSettingMap->find(_T("GPSLoss"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'GPSLoss' from ini file!");
		 m_dGPSLoss=1;
	 }
	 else
	 {
		 m_dGPSLoss=CStr::StrToFloat(itrFind->second);
	 } 

	 itrFind=pcSettingMap->find(_T("FreqOffsetKHz"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_MID,"Not Find 'FreqOffsetKHz' from ini file! default is 100");
		m_dFreqOffset=100;
	 }
	 else
	 {
		 m_dFreqOffset=CStr::StrToFloat(itrFind->second);
	 } 

	 

		  itrFind=pcSettingMap->find(_T("UseTestSet"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'UseTestSet' from ini file! defalt is use");
		 m_bUseTestSet=true;
	 }
	 else
	 {
		 m_bUseTestSet=CStr::StrToBool(itrFind->second);
	 } 

	 itrFind=pcSettingMap->find(_T("GPSWaveFileRootPath"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'GPSWaveFileRootPath' from ini file!");
		 return false;
	 }
	 else
	 {
		 m_strWaveFileRootPath=itrFind->second;
	 }

	 itrFind=pcSettingMap->find(_T("GPSWaveFileName"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'GPSWaveFileName' from ini file!");
		 return false;
	 }
	 else
	 {
		 m_strWaveFileName=itrFind->second;
	 } 

	  itrFind=pcSettingMap->find(_T("SVID"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'SVID' from ini file! Default is 2");
		 m_iSVID=2;
	 }
	 else
	 {
		 m_iSVID=CStr::StrToInt(itrFind->second);
	 } 
	 

		   itrFind=pcSettingMap->find(_T("RetryTimes"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'RetryTimes' from ini file! Default is 20");
		 m_iRetryTimes=20;
	 }
	 else
	 {
		 m_iRetryTimes=CStr::StrToInt(itrFind->second);
	 } 


	 itrFind=pcSettingMap->find("TestDeviceUse");

	  if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not find TestDeviceUse,use TestDeviceCommon");
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
      
		else if(itrFind->second=="TesterDevice1")
		{
          m_piTesterDeviceCurr=m_piTesterDevice1;
		  m_strTesterDeviceCurr=m_strTesterDevice1;
          m_strDeviceAddrCurr=m_strDeviceAddr1;
		}

		else if(itrFind->second=="TesterDevice2")
		{
          m_piTesterDeviceCurr=m_piTesterDevice2;
		  m_strTesterDeviceCurr=m_strTesterDevice2;
          m_strDeviceAddrCurr=m_strDeviceAddr2;
		}
	 }
      itrFind=pcSettingMap->find(_T("GPSDevicePort"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'GPSDevicePort' from ini file!.default use pre config");
		 //return false;
		 m_iOutPort=m_piTesterDeviceCurr->m_iInputPort;
	 }
	 else
	 {
		 m_iOutPort=CStr::StrToInt(itrFind->second);
	 }

     itrFind=pcSettingMap->find(_T("GPSCNOSpec"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'GPSCNOSpec' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		m_RXCNOSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));  
	 }

	 itrFind=pcSettingMap->find(_T("FreqOffsetSpec"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'FreqOffsetSpec' from ini file!");
		 return false;
	 }
	 else
	 {
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strVtr);
		 m_FreqOffsetSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));  
	 }


	 if(strMainFun=="GPSCalLossMainFunc")
	 {
				  itrFind=pcSettingMap->find(_T("GoldenCellPower"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'GoldenCellPower' from ini file!");
			 return false;
		 }
		 else
		 {
			 m_dGoldenCellPower=CStr::StrToFloat(itrFind->second);
		 }

		  itrFind=pcSettingMap->find(_T("CalLossStepdB"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'CalLossStepdB' from ini file!");
			 return false;
		 }
		 else
		 {
			 m_dLossStep=CStr::StrToFloat(itrFind->second);
		 } 

			itrFind=pcSettingMap->find(_T("StartLossValue"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'StartLossValue' from ini file!");
			 return false;
		 }
		 else
		 {
			 m_dLossInitValue=CStr::StrToFloat(itrFind->second);
		 } 

			 itrFind=pcSettingMap->find(_T("MaxLossValue"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'MaxLossValue' from ini file!");
			 return false;
		 }
		 else
		 {
			 m_dMaxLossValue=CStr::StrToFloat(itrFind->second);
		 } 

	 }
	 InitData();
	 return true;
 }

 bool  CGPSTestProc::GPSCalLossMailFunc()
 {
    	CString strSignal;
        int iErrorcode;
	   CStringVtr strVtrLoss;
	   CStringVtr strVtrCh;
	   CStringStringMap mapString2String;
	if(m_bUseTestSet)
	{
		strSignal=m_strWaveFileRootPath+"\\"+m_strWaveFileName;
		  if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestInit(m_strDeviceAddrCurr,strSignal))
	   {
			LogTrace(MSG_ERROR,"Init GPS device fail");
			CalFailLog(_T("_"),_T("_"),1001,"Init GPS device fail");
			return false;
		  
	   }
	}
  
	 for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
		
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
		{
          
			return false;
		}
		else
		{
			strVtrCh.push_back("GPSFixFreq");
			strVtrLoss.push_back(CStr::FloatToStr(m_dCaLoss));
			CStr::MakeVector2Map(strVtrCh,strVtrLoss,mapString2String);
			 if(!m_LossFinder.UpdateLossIniFromMap("GPS",mapString2String))
		   {
			 CalFailLog("_","_",1003,"Cable loss ini not exist");
			 return false;
		   }
		  
		}
	}

	
	   if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetOn(false))
	   {
			LogTrace(MSG_ERROR,"Set GPS power OFF fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set GPS power OFF fail fail");
			return false;
		  
	   }

	
   if(!m_pPhone->GPS_Enable(false))
   {
        LogTrace(MSG_ERROR,"GPS disEnable fail");
	    CalFailLog(_T("_"),_T("_"),1002,"GPS disEnable fail fail");
	    return false;
   }

   if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
	{           LogTrace(MSG_ERROR,_T("Phone Enter Online Mode Fail!"))
				m_iErrorcode=iErrorcode;

			    CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
				return false;
	}
   
   
   m_pPhone->CloseComport();
   if(m_bUseTestSet)
   m_pFunGPSTestDev->Deivce_Exit();
	 return true; 
 }
 bool CGPSTestProc::GPSDIAG_Exit()
 {
	 int iErrorcode;
	  if(m_bUseTestSet)
	 {
	   if(DEVICE_SUCCESS!=m_pFuncGPSDev->ICDMACalSet_DLPower_On(false))
	   {
			LogTrace(MSG_ERROR,"Set GPS power OFF fail");
			CalFailLog(_T("_"),_T("_"),1001,"Set GPS power OFF fail fail");
			return false;
		  
	   }
	   m_pFuncGPSDev->Deivce_Exit();
	 }
	
   if(!m_pPhone->GPS_Enable(false))
   {
        LogTrace(MSG_ERROR,"GPS disEnable fail");
	    CalFailLog(_T("_"),_T("_"),1002,"GPS disEnable fail fail");
	    return false;
   }

   if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
	{           LogTrace(MSG_ERROR,_T("Phone Enter Online Mode Fail!"))
				m_iErrorcode=iErrorcode;

			    CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
				return false;
	}

   
   m_pPhone->CloseComport();
	 return true;
	

 }
 bool CGPSTestProc::GPSTestMainFunc()
 {
	
    

  
	 for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}

 
	 return true;

 }
 bool CGPSTestProc::GPSCalLossFunc()
 {
   	 CString strItemType;
	 int iCNO;
	 double iCNOResult;
	 word wLogCode=0x1477;
	 int iErrorcode;
	 int iRetryTimes=20;
	 double dCableloss=m_LossFinder.GetGPSLoss();
	 int iRXLevLog=m_dCellPower;
	 CString strMsg;
	 strItemType="GPS_CN0_"+CStr::IntToStr(iRXLevLog)+"dBm";
	
			 if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetInOutPort(m_iOutPort))
		   {
				LogTrace(MSG_ERROR,"Set GPS port fail");
				CalFailLog(_T("_"),_T("_"),1001,"Set GPS port fail");
				return false;
			  
		   }

			if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
				{
						LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
						m_iErrorcode=iErrorcode;
						CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
						return false;
				}

					 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
				{           LogTrace(MSG_ERROR,_T("Phone Enter OnlineMode Fail!"))
							m_iErrorcode=iErrorcode;

							CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
							return false;
				}

					 
					 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
				{           LogTrace(MSG_ERROR,_T("Phone Enter FTM Mode Fail!"))
							m_iErrorcode=iErrorcode;

							CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
							return false;
				}
			      
 
          double dLoss;
		  for(dLoss=m_dLossInitValue;dLoss<m_dMaxLossValue;dLoss+=m_dLossStep)
		  {
			  strMsg.Format("Calculate GPS Loss, time is long ,wait.......");
			  LogTrace(MSG_MID,strMsg);
			  iRetryTimes=2;
			  if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetOn(false))
			   {
					LogTrace(MSG_ERROR,"Set GPS power On fail");
					CalFailLog(_T("_"),_T("_"),1001,"Set GPS power On fail");
					return false;
				  
			   }
		 

				 if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetDLFreqPower(1575.42,m_dGoldenCellPower,dLoss))
			   {
					LogTrace(MSG_ERROR,"Set GPS DL Freq Fail fail");
					CalFailLog(_T("_"),_T("_"),1001,"Set GPS DL Freq  fail");
					return false;
				  
			   }

				  if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetOn(true))
			   {
					LogTrace(MSG_ERROR,"Set GPS power On fail");
					CalFailLog(_T("_"),_T("_"),1001,"Set GPS power On fail");
					return false;
				  
			   }
		 

	 		
				 if(!m_pPhone->GPS_Enable())
			   {
					LogTrace(MSG_ERROR,"GPS Enable fail");
					CalFailLog(_T("_"),_T("_"),1002,"GPS Enablel fail");
					return false;
			   }

				 do{

					if(!m_pPhone->GPS_GetCNO(2,wLogCode,iCNO))
							   {
									LogTrace(MSG_ERROR,"GPS GETCNO fail");
									//CalFailLog(_T("_"),_T("_"),1002,"GPS GETCNO fail");
									continue;
							   }
								iCNOResult=iCNO/100;

						if(m_RXCNOSpec.InRange(iCNOResult))                       
					   {
						  TestPassLog(strItemType,"1575.42 MHZ",CStr::FloatToStr(m_dMaxLossValue),CStr::FloatToStr(m_dLossInitValue),CStr::FloatToStr(dLoss),"_","Loss is Passed");
						  
						  m_dCaLoss=dLoss;
						  return true;
					   }
				  		Sleep(10);
						strMsg.Format("Trying Loss=%.2f  StepSize=%.2f StartLoss=%.2f  MaxLoss=%.2f ",dLoss,m_dLossStep,m_dLossInitValue,m_dMaxLossValue); 
						LogTrace(MSG_MID,strMsg);
				 }while(iRetryTimes-->0);

				  if(!m_pPhone->GPS_Enable(false))
			   {
					LogTrace(MSG_ERROR,"GPS disEnable fail");
					CalFailLog(_T("_"),_T("_"),1002,"GPS disEnable fail fail");
					return false;
			   }
						 
		  }

     
     TestFailLog(strItemType,"1575.42 MHZ",1008,CStr::FloatToStr(m_dMaxLossValue),CStr::FloatToStr(m_dLossInitValue),CStr::FloatToStr(dLoss),"_","Loss Reached Max limit");
	 return false;  
 }
 bool CGPSTestProc::GPSTestRX_AT()
 {

	  CString strItemType;
	 int iCNO;
	 double iCNOResult;
	 word wLogCode=0x1477;
	 int iRetryTimes=m_iRetryTimes;
	 double dCableloss=m_LossFinder.GetGPSLoss();
	 int iRXLevLog=m_dCellPower;
	 strItemType="GPS_CN0_"+CStr::IntToStr(iRXLevLog)+"dBm";
	 if(m_bUseTestSet)
	 {
			 if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetInOutPort(m_iOutPort))
		   {
				LogTrace(MSG_ERROR,"Set GPS port fail");
				CalFailLog(_T("_"),_T("_"),1001,"Set GPS port fail");
				return false;
			  
		   }

			 if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetDLFreqPower(1575.42,m_dCellPower,dCableloss))
		   {
				LogTrace(MSG_ERROR,"Set GPS DL Freq Fail fail");
				CalFailLog(_T("_"),_T("_"),1001,"Set GPS DL Freq  fail");
				return false;
			  
		   }

			  if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetOn(true))
		   {
				LogTrace(MSG_ERROR,"Set GPS power On fail");
				CalFailLog(_T("_"),_T("_"),1001,"Set GPS power On fail");
				return false;
			  
		   }
	 }

	 	if(!m_pPhone->OpenATComport(m_iATComport))
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
	
			CalFailLog(_T("_"),_T("_"),1009," Phone Open Comport Fail!");
			return false;
	}

     
	 	if(!m_pPhone->GPS_StartAT(m_iSVID))
	{
		    LogTrace(MSG_ERROR,_T(" GPS START AT Fail!"))

			CalFailLog(_T("_"),_T("_"),1009," GPS START AT Fail!");
			return false;
	}
		
    do{

		   if(!m_pPhone->GPS_GetCNO_AT(iCNO))
		   {
				LogTrace(MSG_ERROR,"GPS GETCNO fail");
				CalFailLog(_T("_"),_T("_"),1002,"GPS GETCNO fail");
				return false;
		   }
			iCNOResult=iCNO;

	if(m_RXCNOSpec.InRange(iCNOResult))
   {
       TestPassLog(strItemType,"1575.42 MHZ",CStr::FloatToStr(m_RXCNOSpec.GetMax()),CStr::FloatToStr(m_RXCNOSpec.GetMin()),CStr::FloatToStr(iCNOResult),"_","GPS CNO pass");
	   return true;
   }
	Sleep(100);
	 }while(iRetryTimes-->0);
 

	  TestFailLog(strItemType,"1575.42 MHZ",1010,CStr::FloatToStr(m_RXCNOSpec.GetMax()),CStr::FloatToStr(m_RXCNOSpec.GetMin()),CStr::FloatToStr(iCNOResult),"_","GPS CNO pass fail");  
	   return false;


	 return true;
 }
 bool CGPSTestProc::GPSTestRXFunc()
 {
	 CString strSignal;
	 CString strItemType;
	 int iCNO;
	 double iCNOResult;
	 word wLogCode=0x1477;
	 int iErrorcode;
	 int iRetryTimes=20;
	 double dCableloss=m_LossFinder.GetGPSLoss();
	 int iRXLevLog=m_dCellPower;
	 strItemType="GPS_CN0_"+CStr::IntToStr(iRXLevLog)+"dBm";
	 if(m_bUseTestSet)
	 {
		 strSignal=m_strWaveFileRootPath+"\\"+m_strWaveFileName;
		 if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestInit(m_strDeviceAddrCurr,strSignal))
		 {
			 LogTrace(MSG_ERROR,"Init GPS device fail");
			 CalFailLog(_T("_"),_T("_"),1001,"Init GPS device fail");
			 return false;

		 }
			 if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetInOutPort(m_iOutPort))
		   {
				LogTrace(MSG_ERROR,"Set GPS port fail");
				CalFailLog(_T("_"),_T("_"),1001,"Set GPS port fail");
				return false;
			  
		   }

			 if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetDLFreqPower(1575.42,m_dCellPower,dCableloss))
		   {
				LogTrace(MSG_ERROR,"Set GPS DL Freq Fail fail");
				CalFailLog(_T("_"),_T("_"),1001,"Set GPS DL Freq  fail");
				return false;
			  
		   }

			  if(DEVICE_SUCCESS!=m_pFunGPSTestDev->IGPSTestSetOn(true))
		   {
				LogTrace(MSG_ERROR,"Set GPS power On fail");
				CalFailLog(_T("_"),_T("_"),1001,"Set GPS power On fail");
				return false;
			  
		   }
	 }

	 	if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	{
		    LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			m_iErrorcode=iErrorcode;
			CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
			return false;
	}

		 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_ONLINE_F))!=PHONE_SUCCESS)
	{           LogTrace(MSG_ERROR,_T("Phone Enter OnlineMode Fail!"))
				m_iErrorcode=iErrorcode;

			    CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
				return false;
	}

		 if((iErrorcode=m_pPhone->SetPhoneMode(MODE_FTM_F))!=PHONE_SUCCESS)
	{           LogTrace(MSG_ERROR,_T("Phone Enter FTM Mode Fail!"))
				m_iErrorcode=iErrorcode;

			    CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Enter FTM Mode Fail!");
				return false;
	}
      

     if(!m_pPhone->GPS_Enable())
   {
        LogTrace(MSG_ERROR,"GPS Enable fail");
	    CalFailLog(_T("_"),_T("_"),1002,"GPS Enablel fail");
	    return false;
   }

	 do{

				if(!m_pPhone->GPS_GetCNO(m_iSVID,wLogCode,iCNO))
		   {
				LogTrace(MSG_ERROR,"GPS GETCNO fail");
				CalFailLog(_T("_"),_T("_"),1002,"GPS GETCNO fail");
				return false;
		   }
			iCNOResult=iCNO/100;

	if(m_RXCNOSpec.InRange(iCNOResult))
   {
       TestPassLog(strItemType,"1575.42 MHZ",CStr::FloatToStr(m_RXCNOSpec.GetMax()),CStr::FloatToStr(m_RXCNOSpec.GetMin()),CStr::FloatToStr(iCNOResult),"_","GPS CNO pass");
	   if(!GPSDIAG_Exit())
		   return false;
	   return true;
   }
	 }while(iRetryTimes-->0);
 

	  TestFailLog(strItemType,"1575.42 MHZ",1010,CStr::FloatToStr(m_RXCNOSpec.GetMax()),CStr::FloatToStr(m_RXCNOSpec.GetMin()),CStr::FloatToStr(iCNOResult),"_","GPS CNO pass fail");  
	   return false;
 
   
	
 }

 
 bool CGPSTestProc::GPSTestGen8()
 {
	 CString strItemType;
	 int iFailFlag=0;
	 double iCNOResult;
	int iFreqResult;
	 int iErrorcode;
	 strItemType="GPS";
	 if(m_bUseTestSet)
	 {
		 if(DEVICE_SUCCESS!=m_pFuncGPSDev->IWCDMACalInit(m_strDeviceAddrCurr))
		 {
			 LogTrace(MSG_ERROR,"Init GPS Dev fail");
			 CalFailLog(_T("_"),_T("_"),1001,"Init GPS Dev fail");
			 return false;

		 }

		 if(DEVICE_SUCCESS!=m_pFuncGPSDev->IWCDMACalSetXOSig(1575.42,1575.42,m_dFreqOffset,m_dCellPower))
		 {
			 LogTrace(MSG_ERROR,"Set GPS DL Freq Fail fail");
			 CalFailLog(_T("_"),_T("_"),1001,"Set GPS DL Freq  fail");
			 return false;
		 }
		 if(DEVICE_SUCCESS!=m_pFuncGPSDev->IDevicesSetIOPort(m_iOutPort))
		 {
			 LogTrace(MSG_ERROR,"DevicesSetIOPort fail");
			 CalFailLog(_T("_"),_T("_"),1001,"DevicesSetIOPort  fail");
			 return false;
		 }
		 if(DEVICE_SUCCESS!=m_pFuncGPSDev->IGPSSetLoss(m_dGPSLoss))
		 {
			 LogTrace(MSG_ERROR,"GPSSetLoss fail");
			 CalFailLog(_T("_"),_T("_"),1001,"GPSSetLoss  fail");
			 return false;
		 }


	 }
	 if((iErrorcode=m_pPhone->OpenComport(m_iComport,m_iComportRetryTimes))!=PHONE_SUCCESS)
	 {
		 LogTrace(MSG_ERROR,_T(" Phone Open Comport Fail!"))
			 m_iErrorcode=iErrorcode;
		 CalFailLog(_T("_"),_T("_"),iErrorcode," Phone Open Comport Fail!");
		 return false;
	 }
	 if(!m_pPhone->GPS_Enable())
	 {
		 LogTrace(MSG_ERROR,"GPS Enable fail");
		 CalFailLog(_T("_"),_T("_"),1002,"GPS Enablel fail");
		 return false;
	 }
	 TestPassLog(strItemType,"1575.42 MHZ","-","-","-","-","GPS Init pass");


	 if(!m_pPhone->GPS_GEN8_GetCNo(1,&iCNOResult,&iFreqResult))
	 {
		 LogTrace(MSG_ERROR,"GPS GETCNO fail");
		 CalFailLog(_T("_"),_T("_"),1002,"GPS GETCNO fail");
		 return false;
	 }
	 iFreqResult=int (iFreqResult-m_dFreqOffset*1000);


	 if(m_RXCNOSpec.InRange(iCNOResult))
	 {
		 TestPassLog(strItemType,"1575.42 MHZ",CStr::FloatToStr(m_RXCNOSpec.GetMax()),CStr::FloatToStr(m_RXCNOSpec.GetMin()),CStr::FloatToStr(iCNOResult),"db","GPS CNO pass");
		
	 }
	 else
	 {
		 TestFailLog(strItemType,"1575.42 MHZ",1010,CStr::FloatToStr(m_RXCNOSpec.GetMax()),CStr::FloatToStr(m_RXCNOSpec.GetMin()),CStr::FloatToStr(iCNOResult),"db","GPS CNO fail");  
	 iFailFlag++;
	 }
	/* if(m_FreqOffsetSpec.InRange(iFreqResult))
	 {
		 TestPassLog(strItemType,"1575.42 MHZ",CStr::FloatToStr(m_FreqOffsetSpec.GetMax()),CStr::FloatToStr(m_FreqOffsetSpec.GetMin()),CStr::FloatToStr(iFreqResult),"Hz","GPS FreqOffset pass");
		 
	 }
	 else
	 {
		 TestFailLog(strItemType,"1575.42 MHZ",1010,CStr::FloatToStr(m_FreqOffsetSpec.GetMax()),CStr::FloatToStr(m_FreqOffsetSpec.GetMin()),CStr::FloatToStr(iFreqResult),"Hz","GPS FreqOffset fail");  
		 iFailFlag++;
	 }*/
	 if (0<iFailFlag)
	 {
		 return false;
	 }
	 return true;
 }
 bool CGPSTestProc::InitData()
 {
	 if(m_bUseTestSet)
	 {
		m_pFunGPSTestDev=m_piTesterDeviceCurr->m_piFuncGPSTest;
		m_pFuncGPSDev=m_piTesterDeviceCurr->m_piFuncWCDMACal;
	 }
	 
	 return true;
 }