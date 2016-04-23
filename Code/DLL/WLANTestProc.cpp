#include "StdAfx.h"
#include "WLANTestProc.h"
RF_IMPLEMENT_DYNCREATE(CWLANTestProc)
CWLANTestProc::CWLANTestProc(void)
{
	m_mapClassFunc[_T("WLANTestCallMainFunc")]=&CWLANTestProc::WLANTestMainFunc;
	m_mapClassFunc[_T("WLANCallossMainFunc")]=&CWLANTestProc::WLANCallossMainFunc;
	m_mapClassFunc[_T("WLANTestTXFunc")]=&CWLANTestProc::WLANTestTXFunc;
    m_mapClassFunc[_T("WLANTestRXFunc")]=&CWLANTestProc::WLANTestRXFunc;
	m_mapClassFunc[_T("WCalLossFunc")]=&CWLANTestProc::WLANTestTXCalLossFunc;
	m_mapClassFunc[_T("WLANTestRmmod")]=&CWLANTestProc::WLANTestRmmod;
	m_mapClassFunc[_T("ADB_Push")]=&CWLANTestProc::ADB_Push;
	m_mapClassFunc[_T("WLANTestDoSelfInit")]=&CWLANTestProc::WLANTestDoSelfInit;
	m_iItemCode=1001;
}
// bool CQualPhone::WLAN_Do_SelfInit()
bool CWLANTestProc::WLANTestDoSelfInit()
{
	 if(!m_pPhone->WLAN_Do_SelfInit())
	   {
			LogTrace(MSG_ERROR,"WLAN_Do_SelfInit Fail");
			return false;
	   }
	 return true;
}
bool CWLANTestProc::WLANTestRmmod()
{
	 if(!m_pPhone->WLAN_Rmmod())
	   {
			LogTrace(MSG_ERROR,"WLAN Load Driver Fail");
			return false;
	   }
	 return true;
}
bool CWLANTestProc::ADB_Push()
{	
	 if(!m_pPhone->Adb_Push(strFilePath,strTargetPath))
	   {
			LogTrace(MSG_ERROR,"WLAN Load Driver Fail");
			return false;
	   }
	 return true;
}
// bool CQualPhone::Adb_Push(CString filePath,CString targetPath)
CWLANTestProc::~CWLANTestProc(void)
{
}
bool CWLANTestProc::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CWLANTestProc::Handle()
{
	 CString strMsg;
	 if(!m_pPhone->SetAtMode(m_iIsUseAT))
   {	
        LogTrace(MSG_ERROR,"Set WLAN AT mode fail");
	    CalFailLog(_T("_"),_T("_"),1002,"Set WLAN AT mode fail");
	    return false;
   }



	 if(m_iIsUseAT)
	 {
		 if(!m_pPhone->OpenATComport(m_iATComport))
	   {
			LogTrace(MSG_ERROR,"Open Comport Fail");
			return false;
	   }
	 }
	 else
	 {
       if(!m_pPhone->WLAN_Driverop())
	   {
			LogTrace(MSG_ERROR,"WLAN Load Driver Fail");
			return false;
	   }
	    Sleep(3000);
	  
	 }

	if(!DoProcess())
	{
         if(m_iIsUseAT)
	 {
		 m_pPhone->CloseATComport();
	  
	 }
	 else
	 {
       if(!m_pPhone->WLAN_Driverop(false))
	   {
			LogTrace(MSG_ERROR,"WLAN UnLoad Driver Fail");
			return false;
	   }
	 }
 
		return false;
	}

	if(m_iIsUseAT)
	 {
		 m_pPhone->CloseATComport();
	  
	 }
	 else
	 {
       if(!m_pPhone->WLAN_Driverop(false))
	   {
			LogTrace(MSG_ERROR,"WLAN UnLoad Driver Fail");
			return false;
	   }
	 }

	return true;
}

 bool CWLANTestProc::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {

	 m_bWLANRXTestFirst=true;

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
		 LogTrace(MSG_FATAL,_T("Not Find FuncLIst"));
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
    
    itrFind=pcSettingMap->find(_T("WLANADDR"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'WLANADDR' from ini file!");
		 return false;
	 }
	 else
	 {
		 strWLANADDR=itrFind->second;
	 }
//needSelfinit
	 itrFind=pcSettingMap->find(_T("SelfInit"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'SelfInit' from ini file! Default is Not use");
		 needSelfinit=0;
	 }
	 else
	 {
		 needSelfinit=CStr::StrToInt(itrFind->second);
	 }
	// CString strFilePath;
	// CString strTargetPath;

	 itrFind=pcSettingMap->find(_T("FilePath"));
	
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"FilePath");
		 strFilePath="";
	 }
	 else
	 {
		 strFilePath=itrFind->second;
	 }

		 itrFind=pcSettingMap->find(_T("TargetFilePath"));
	
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"TargetFilePath");
		 strTargetPath="";
	 }
	 else
	 {
		 strTargetPath=itrFind->second;
	 }

	 itrFind=pcSettingMap->find(_T("IsUseAT"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'IsUseAT' from ini file! Default is Not use");
		 m_iIsUseAT=0;
	 }
	 else
	 {
		 m_iIsUseAT=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("ATDelayRxCMD_ms"));
	   if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'ATDelayRxCMD_ms' from ini file! Default is 7000 ms ");
		 m_iDelayWlanRXcommandAT=7000;
	 }
	 else
	 {
		 m_iDelayWlanRXcommandAT=CStr::StrToInt(itrFind->second);
	 }

	  itrFind=pcSettingMap->find(_T("ADBDelayRxCMD_ms"));
	   if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'ADBDelayRxCMD_ms' from ini file! Default is 3000 ms ");
		 m_iDelayWlanRXcommandADB=3000;
	 }
	 else
	 {
		 m_iDelayWlanRXcommandADB=CStr::StrToInt(itrFind->second); 
	 }

	    itrFind=pcSettingMap->find(_T("ATDelayDeviceON_ms"));
	   if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'ATDelayDeviceON_ms' from ini file! Default is 3000 ms ");
		 m_iDelayDeviceOnAT=3000;
	 }
	 else
	 {
		 m_iDelayDeviceOnAT=CStr::StrToInt(itrFind->second); 
	 }

	    itrFind=pcSettingMap->find(_T("ADBDelayDeviceON_ms"));
	   if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'ADBDelayDeviceON_ms' from ini file! Default is 2000 ms ");
		 m_iDelayDeviceOnADB=2000;
	 }
	 else
	 {
		 m_iDelayDeviceOnADB=CStr::StrToInt(itrFind->second); 
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
   itrFind=pcSettingMap->find(_T("WLANDevicePort"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'WLANDevicePort' from ini file!.default use pre config");
		 //return false;
		 m_iInOutPort=m_piTesterDeviceCurr->m_iInputPort;
	 }
	 else
	 {
		 m_iInOutPort=CStr::StrToInt(itrFind->second);
	 }

      
	 itrFind=pcSettingMap->find(_T("TXPerformaceList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'TXPerformaceList' from ini file!");
		 return false;
	 }
	 else
	 {
		 CStringVtr strTestNameVtr;
		 CStringVtr strTestFlagVtr;
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strTestNameVtr);
         itrFind=pcSettingMap->find(_T("TXPerformaceListBitMask"));
		  if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'TXPerformaceListBitMask' from ini file!");
			 return false;
		 }

         strValue=itrFind->second;
          CStr::ParseString(strValue,_T(","),strTestFlagVtr);

		if(!CStr::MakeVector2Map(strTestNameVtr,strTestFlagVtr,m_str2strTestMap))
		{
            LogTrace(MSG_ERROR,"TXPerformaceList size not equal to TXPerformaceListBitMask size!");
            return false;
		}
         
	 }
    
	 itrFind=pcSettingMap->find(_T("WLANSignalTypeList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'WLANSignalTypeList' from ini file!");
		 return false;
	 }
	 else
	 {
        CStringVtr strSignalTypeList;
        CStringVtr strWaveFileNameList;
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		strSignalTypeList=strVtr;
		CStr::StrVtr2IntVtr(m_striTypeVtr,strVtr);

		 itrFind=pcSettingMap->find(_T("WLANWaveFormNameList"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'WLANWaveFormNameList' from ini file!");
				 return false;
			 }
			 else
			 {
				strValue=itrFind->second;
				CStr::ParseString(strValue,_T(","),strWaveFileNameList);   
			 }

       	if(!CStr::MakeVector2Map(strSignalTypeList,strWaveFileNameList,m_str2strWaveFilenameMap))
		{
            LogTrace(MSG_ERROR,"WLANSignalTypeList size not equal to WLANWaveFormNameList size!");
            return false;
		}
           
	 }



	  itrFind=pcSettingMap->find(_T("WLANChannelList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'WLANChannelList' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		m_strChannelVtr=strVtr;
		CStr::StrVtr2IntVtr(m_iChannelVtr,strVtr);
      
	 }

 
     itrFind=pcSettingMap->find(_T("TXPOWERSpec"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'TXPOWERSpec' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		m_PowerSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
      
	 }

	 m_dMaxLev=m_PowerSpec.GetMax();


	  itrFind=pcSettingMap->find(_T("EVMALLCARRSpec"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'EVMALLCARRSpec' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		m_EVMAllCarrSpec.SetRange(CStr::StrToInt(strVtr[0]),CStr::StrToInt(strVtr[1]));
      
	 }

      itrFind=pcSettingMap->find(_T("CellPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'CellPower' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
		m_dCellPower=CStr::StrToFloat(strValue);
      
	 }
     

     itrFind=pcSettingMap->find(("TargetPower"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'TargetPower' from ini file! Use 16 dBm ");
		 m_iTargetPower=16;

	 }
	 else
	 {
		strValue=itrFind->second;
		m_iTargetPower=CStr::StrToInt(strValue);
      
	 }
       itrFind=pcSettingMap->find(_T("RXFerSpec"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'RXFerSpec' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		m_RXFerSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
      
	 }

	  itrFind=pcSettingMap->find(_T("WLANRXRootWaveFilePath"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'WLANRXRootWaveFilePath' from ini file!");
		 return false;
	 }
	 else
	 {
		m_strWaveFileRootPath=itrFind->second;
  
	 }

	 itrFind=pcSettingMap->find(_T("AdbType"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'AdbType' from ini file! Use 1 ");
		 m_iAdbType=1;

	 }
	 else
	 {
		 strValue=itrFind->second;
		 m_iAdbType=CStr::StrToInt(strValue);
	 }

	
	 if(strMainFun=="WLANCallossMainFunc")
	 {

		  itrFind=pcSettingMap->find(_T("LossPreset"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_WARNING,"Not Find 'LossPreset' from ini file!default is 0");
			  m_dLossPreset=0;
		 }
		 else
		 {
			strValue=itrFind->second;
			m_dLossPreset=CStr::StrToFloat(strValue);
			   
		 }

			 itrFind=pcSettingMap->find(_T("GoldenPowerList"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'GoldenPowerList' from ini file!");
			 return false;
		 }
		 else
		 {
			strValue=itrFind->second;
			CStr::ParseString(strValue,_T(","),strVtr);
			CStr::StrVtr2DblVtr(m_dGoldenpower,strVtr);

			m_dMaxLev=m_dGoldenpower[0]-m_dLossPreset+3;
	      
		 }

          itrFind=pcSettingMap->find(_T("BTChannelList"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'BTChannelList' from ini file!");
			 return false;
		 }
		 else
		 {
			strValue=itrFind->second;
			CStr::ParseString(strValue,_T(","),m_strBTChannelVtr);
	      
		 }

		 
			 CStringVtr strVtrTemp;
		 itrFind=pcSettingMap->find(_T("CalLossSpec"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'CalLossSpec' from ini file!");
			 return false;
		 }
		 else
		 {
			strValue=itrFind->second;
			CStr::ParseString(strValue,_T(","),strVtrTemp);
			m_LossSpec.SetRange(CStr::StrToFloat(strVtrTemp[0]),CStr::StrToFloat(strVtrTemp[1]));
	      
		 }
		
	 }


     
        

	 InitData();
	 return true;
 }
bool CWLANTestProc::WLANCallossMainFunc()
{
  if(!m_pPhone->WLAN_Enable(true,true,m_iAdbType))
   {
        LogTrace(MSG_ERROR,"Init DUT WLAN fail");
	    CalFailLog(_T("_"),_T("_"),1002,"Init DUT WLAN fail");
	    return false;
   }

    if(DEVICE_SUCCESS!=m_pFunWLANTestDev->IWLANTestInit(m_strDeviceAddrCurr,strWLANADDR))
   {
	    LogTrace(MSG_ERROR,"Init WLAN device fail");
	    CalFailLog(_T("_"),_T("_"),1001,"Init WLAN device fail");
	    return false;
	  
   }
	if(DEVICE_SUCCESS!=m_pFunWLANTestDev->IWLANTestSetInOutPort(m_iInOutPort,m_iInOutPort))
   {
	    LogTrace(MSG_ERROR,"Set WLAN Portfail");
	    CalFailLog(_T("_"),_T("_"),1001,"Set WLAN Portfail");
	    return false;
	  
   }

for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}


  return true;
}
 bool CWLANTestProc::WLANTestMainFunc()
 {

	  if(DEVICE_SUCCESS!=m_pFunWLANTestDev->IWLANTestInit(m_strDeviceAddrCurr,strWLANADDR))
   {
	    LogTrace(MSG_ERROR,"Init WLAN device fail");
	    CalFailLog(_T("_"),_T("_"),1001,"Init WLAN device fail");
	    return false;
	  
   }
    
	 if(DEVICE_SUCCESS!=m_pFunWLANTestDev->IWLANTestSetInOutPort(m_iInOutPort,m_iInOutPort))
   {
	    LogTrace(MSG_ERROR,"Set WLAN Portfail");
	    CalFailLog(_T("_"),_T("_"),1001,"Set WLAN Portfail");
	    return false;
	  
   }
	 for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;

		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
		{
			if(fpTestFunc==&CWLANTestProc::WLANTestRXFunc)
			{
				
				m_bWLANRXTestFirst=false;
                if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
					return false;

			}
			else

			return false;
		}
	}


	  
	 return true;

 }
 bool CWLANTestProc::WLANTestRXFunc()
 {
   
      for(IntItr itrType=m_striTypeVtr.begin();itrType!=m_striTypeVtr.end();++itrType)
   {
	    
	   for(IntItr itrCh=m_iChannelVtr.begin();itrCh!=m_iChannelVtr.end();++itrCh)
	   {
		   strCurrCH=CStr::IntToStr(*itrCh);

		   if(!WLANHandover(*itrType,*itrCh,m_iTargetPower,m_dCellPower,false))
		   {
			  if(!m_bWLANRXTestFirst)
			  {
      
				  CalFailLog(strCurrType,strCurrCH,1005," WLAN  Test RX Handover fail");
				  return false;
			  }
		   }

		   if(!WLANTestRxSpec())
		   {
			   return false;
		   }


	   }
   }
    
     
	  if(!WLANEndTest(false))
   {
      LogTrace(MSG_WARNING,"End WLAN RX not successfully!");
   }

	 return true;
 }

 bool CWLANTestProc::WLANTestTXCalLossFunc()
 {
      for(IntItr itrType=m_striTypeVtr.begin();itrType!=m_striTypeVtr.end();++itrType)
   {
	   
	   m_dCalpower.clear();
	   for(IntItr itrCh=m_iChannelVtr.begin();itrCh!=m_iChannelVtr.end();++itrCh)
	   {
		   strCurrCH=CStr::IntToStr(*itrCh);

		   if(!WLANHandover(*itrType,*itrCh,m_iTargetPower,m_dCellPower,true,true))
		   {
      
			  CalFailLog(strCurrType,strCurrCH,1003," WLAN  Test TX Handover fail");
			  return false;
		   }

		   if(!WLANTestTxSpec(*itrType,true))
		   {
			   return false;
		   }


	   }
   }

    if(!WLANEndTest())
   {
      LogTrace(MSG_WARNING,"End WLAN TX not successfully!");
   }

   CStringVtr strVtrLoss;
   CStringVtr strVtrCh;
   DblVtrItr itrMeasPowerItr;
   DblVtrItr itrGoldPowerItr;
   CStringStringMap mapString2String;
 

   for(itrMeasPowerItr=m_dCalpower.begin(),itrGoldPowerItr=m_dGoldenpower.begin();itrMeasPowerItr!=m_dCalpower.end() && itrGoldPowerItr!=m_dGoldenpower.end();++itrMeasPowerItr,++itrGoldPowerItr)
   {
       double dloss=*itrGoldPowerItr-*itrMeasPowerItr;
	
		  if(!m_LossSpec.InRange(dloss))
		   {
			   TestFailLog("_","_",1020,CStr::FloatToStr(m_LossSpec.GetMax()),CStr::FloatToStr(m_LossSpec.GetMin()),CStr::FloatToStr(dloss),"dB","Loss Fail");
			   return false;
		   }
	   strVtrLoss.push_back(CStr::FloatToStr(dloss));
	   TestPassLog("_","_",CStr::FloatToStr(m_LossSpec.GetMax()),CStr::FloatToStr(m_LossSpec.GetMin()),CStr::FloatToStr(dloss),"dB","Loss Pass");

	   
   }

   CStr::MakeVector2Map(m_strChannelVtr,strVtrLoss,mapString2String);
   if(!m_LossFinder.UpdateLossIniFromMap("WLAN",mapString2String))
   {
       CalFailLog(strCurrType,strCurrCH,1003,"Cable loss ini not exist");
			  return false;
   }
   mapString2String.clear();
   CStr::MakeVector2Map(m_strBTChannelVtr,strVtrLoss,mapString2String);
   if(!m_LossFinder.UpdateLossIniFromMap("BT",mapString2String))
   {
     CalFailLog(strCurrType,strCurrCH,1003,"Cable loss ini not exist");
	 return false;
   }
  
	return true;
 
 }
 bool CWLANTestProc::WLANTestTXFunc()
 {
	
	 if(!m_pPhone->WLAN_Enable(true,true,m_iAdbType))
   {
        LogTrace(MSG_ERROR,"Init DUT WLAN fail");
	    CalFailLog(_T("_"),_T("_"),1002,"Init DUT WLAN fail");
	    return false;
   }


   for(IntItr itrType=m_striTypeVtr.begin();itrType!=m_striTypeVtr.end();++itrType)
   {
	   
	 
	   for(IntItr itrCh=m_iChannelVtr.begin();itrCh!=m_iChannelVtr.end();++itrCh)
	   {
		   strCurrCH=CStr::IntToStr(*itrCh);

		   if(!WLANHandover(*itrType,*itrCh,m_iTargetPower,m_dCellPower,true))
		   {
      
			  CalFailLog(strCurrType,strCurrCH,1003," WLAN  Test TX Handover fail");
			  return false;
		   }

		   if(!WLANTestTxSpec(*itrType))
		   {
			   return false;
		   }


	   }
   }

    if(!WLANEndTest())
   {
      LogTrace(MSG_WARNING,"End WLAN TX not successfully!");
   }



   return true;
 }
 bool CWLANTestProc::WLANHandover(int eSigType,int iChannel,int iTargetPower,double dlPower,bool bIsTx,bool bIsCalloss)
 {
   
	CString strSigType;

	int  iFreq;
	double dLoss;
	
        if(iChannel<=13) 
		iFreq=iChannel*5+2407;
		else
        iFreq=2472+(iChannel-13)*12;
	
   dLoss=m_LossFinder.GetWLANLoss(iChannel);
   if(bIsCalloss)
   dLoss=0;
	switch(eSigType)
	{
	    case W802a:
		strSigType="AOFDm";
		strCurrType="WLAN_802.11a_OFDM";
		m_strWavefilePath=m_strWaveFileRootPath+"\\"+m_str2strWaveFilenameMap["1"];
	break;
	   case W802b:
		  strSigType="BDSSs";
		  strCurrType="WLAN_802.11b_DSSS";
		  m_strWavefilePath=m_strWaveFileRootPath+"\\"+m_str2strWaveFilenameMap["2"];
	break;
		case W802g_DSSS:
		strSigType="GDSSs";
		strCurrType="WLAN_802.11a_DSSS";
		m_strWavefilePath=m_strWaveFileRootPath+"\\"+m_str2strWaveFilenameMap["3"];
	break;
		case W802g_OFDM:
		strSigType="GOFDm";
		strCurrType="WLAN_802.11g_OFDM";
		m_strWavefilePath=m_strWaveFileRootPath+"\\"+m_str2strWaveFilenameMap["4"];
	break;
		case W802n:
		strSigType="NOFDm";
		strCurrType="WLAN_802.11n";
		m_strWavefilePath=m_strWaveFileRootPath+"\\"+m_str2strWaveFilenameMap["5"];
     break;

		default:
            
		 strSigType="GOFDm";
			break;


	}
	if(bIsTx)
	{
		 if(!m_pPhone->WLAN_TX_Test(strWLANADDR,iChannel,eSigType,0,0,iTargetPower,54,needSelfinit,m_iAdbType))
		 {
			LogTrace(MSG_ERROR,"DUT handover fail");
			return false;
		 }
		if(m_pFunWLANTestDev->IWLANTestSetTrackingAllOn()!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"IWLANTestSetTrackingAllOn");
		  return false;
		} 
		if(m_pFunWLANTestDev->IWLANTestSetType(strSigType)!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Device set Burst type fail");
		  return false;
		}

		 if(m_pFunWLANTestDev->IWLANTestSetFreq(iFreq,m_dMaxLev,dLoss)!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Device set Burst Frequency  fail");
			return false;
		}
	    if(m_iAdbType==1)
		{
			if(m_pFunWLANTestDev->IWLANTestSetTrigger(-30,15,10)!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Device set Trigger fail");
				return false;
			}
		}
		else 
		{
			if(m_pFunWLANTestDev->IWLANTestSetTrigger(-30,15,50)!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Device set Trigger fail");
				return false;
			}
		}

		  
		 if(m_pFunWLANTestDev->IWLANTestInitMeasure(10)!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Device Measure On fail");
			return false;
		}
	   
		 
		
	}
	else
	{ 
       if(m_pFunWLANTestDev->IWLANTestSetDLType(m_strWavefilePath)!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Device set DL wavefile fail");
		  return false;
		}

	   	 if(m_pFunWLANTestDev->IWLANTestSetDLFreqPower(iFreq,dlPower,dLoss)!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Device set DL frequency dl power  fail");
			return false;
		}

		 if(m_pFunWLANTestDev->IWLANTestSetDLSigOn(false)!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,"Set WLAN signal OFF  fail");
			return false;
			
		 }


		 if(!m_pPhone->WLAN_RXBegin_Test(strWLANADDR,iChannel,eSigType,0,0,iTargetPower,54))
		 {
			LogTrace(MSG_ERROR,"DUT RX handover fail");
			return false;
		 } 

          if(m_iIsUseAT)
			  Sleep(m_iDelayWlanRXcommandAT);
		  else
			  Sleep(m_iDelayWlanRXcommandADB);

	}
   
	 return true;
 }
 bool CWLANTestProc::WLANTestRxSpec()
 {

	CString strItemType;
    int iPreCount=0; 
	int iLastCount=0;
	double dFER;
	int iRXLevLog=m_dCellPower;
	
	strItemType=strCurrType+"RX_"+CStr::IntToStr(iRXLevLog)+"dBm_PER";
	 
	 /*if(!m_iIsUseAT)
	 {
		 if(!m_pPhone->WLAN_RXCount_ValidPackets(iPreCount))
	   {
			LogTrace(MSG_ERROR,"Count WLAN Packets count fail");
			CalFailLog(_T("_"),_T("_"),1002,"Count WLAN Packets count fail");
			return false;
	   }
	 }*/

      if(m_pFunWLANTestDev->IWLANTestSetDLSigOn(true)!=DEVICE_SUCCESS)
	 {
		LogTrace(MSG_ERROR,"Set WLAN signal on  fail");
        return false;
	 }
	  
           if(m_iIsUseAT)
			Sleep(m_iDelayDeviceOnAT);
		   else
		    Sleep(m_iDelayDeviceOnADB);

     if(!m_pPhone->WLAN_RXCount_ValidPackets(iLastCount))
	   {
			LogTrace(MSG_ERROR,"Count WLAN Packets count fail");
			CalFailLog(_T("_"),_T("_"),1002,"Count WLAN Packets count fail");
			return false;
	   }
   
	/*if(!m_iIsUseAT)
	{

    dFER=(double)(1000-(iLastCount-iPreCount))/1000;
    if(dFER<0)
      dFER=0;
	}
	else
	{*/

      dFER=(double)(1000-iLastCount)/1000;

	  if(dFER<0)
		  dFER=0;
	//}

	if(m_RXFerSpec.InRange(dFER))
	{
      TestPassLog(strItemType,strCurrCH,CStr::FloatToStr(m_RXFerSpec.GetMax()),CStr::FloatToStr(m_RXFerSpec.GetMin()),CStr::FloatToStr(dFER),"_","WLAN RX FER pass");
	}
	else
	{
		 if(!m_bWLANRXTestFirst)
		 {
		   TestFailLog(strItemType,strCurrCH,1007,CStr::FloatToStr(m_RXFerSpec.GetMax()),CStr::FloatToStr(m_RXFerSpec.GetMin()),CStr::FloatToStr(dFER),"_","WLAN RX FER fail ");  
		   
		 }
		   return false;
		 
	}


    if(m_pFunWLANTestDev->IWLANTestSetDLSigOn(false)!=DEVICE_SUCCESS)
	 {
		LogTrace(MSG_ERROR,"Set WLAN signal OFF  fail");
        return false;
	 }

	 return true;
 }
 bool CWLANTestProc::WLANTestTxSpec(int eSigType,bool bIsCalLoss)
 {
	 CStringVtr vtrResult;
	 CString strResult;
	 CString strItemType;
	 double dResult;
	 
	 if(m_pFunWLANTestDev->IWLANTestFetchResults(eSigType,vtrResult)!=DEVICE_SUCCESS)
	 {
		LogTrace(MSG_ERROR,"Fetch WLAN result  fail");
        return false;
	 }
	 
	 for(CStringStringMapItr itrTest=m_str2strTestMap.begin();itrTest!=m_str2strTestMap.end();++itrTest)
	 {
		 CString strTestName=itrTest->first;
		 if(itrTest->second=="0")
			 continue;

		  if(bIsCalLoss)
			 {
				strItemType=strCurrType+"TX_PWR";  
                if(vtrResult[3]=="NAV")
				 {
					  CalFailLog(strItemType,strCurrCH,1005,"WLAN TX POWER is NAV");
					  return false;
				 }

				m_dCalpower.push_back(CStr::StrToFloat(vtrResult[3]));

                TestPassLog(strItemType,strCurrCH,"_","_",vtrResult[3],"dBm","WLAN Cal Power pass");
	             
			   return true;
			 }
		  else
		  {
			 if(strTestName=="TXPOWER")
			 {
				
			
					 strItemType=strCurrType+"TX_PWR";
					 if("NAV" == vtrResult[3])
					 {
						  TestFailLog(strItemType,strCurrCH,1005,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),vtrResult[3],"dBm","WLAN Nomial Power Fail");
						 return false;
					 }
		             
					 dResult=CStr::StrToFloat(vtrResult[3]);
					 if(m_PowerSpec.InRange(dResult))
					 {
						 TestPassLog(strItemType,strCurrCH,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),CStr::FloatToStr(dResult),"dBm","WLAN Nomial Power pass");
						
					 }
					 else
					 {
						 TestFailLog(strItemType,strCurrCH,1005,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),CStr::FloatToStr(dResult),"dBm","WLAN Nomial Power Fail");
						 return false;
					 }
				
			 }
				 if(strTestName=="EVMALLCARR")
				 {
					 strItemType=strCurrType+"TX_EVM_ALLCarrier_RMS";
						  if(vtrResult[4]=="NAV")
					 {
						  TestFailLog(strItemType,strCurrCH,1005,CStr::FloatToStr(m_EVMAllCarrSpec.GetMax()),CStr::FloatToStr(m_EVMAllCarrSpec.GetMin()),vtrResult[4],"db","WLAN EVM ALLCARR Fail");
						 return false;
					 }
		             
						dResult=CStr::StrToFloat(vtrResult[4]);
						 if(m_EVMAllCarrSpec.InRange(dResult))
						 {
							 TestPassLog(strItemType,strCurrCH,CStr::FloatToStr(m_EVMAllCarrSpec.GetMax()),CStr::FloatToStr(m_EVMAllCarrSpec.GetMin()),CStr::FloatToStr(dResult),"db","WLAN EVM ALLCARR pass");
							
						 }
						 else
						 {
							 TestFailLog(strItemType,strCurrCH,1006,CStr::FloatToStr(m_EVMAllCarrSpec.GetMax()),CStr::FloatToStr(m_EVMAllCarrSpec.GetMin()),CStr::FloatToStr(dResult),"db","WLAN EVM ALLCARR Fail");
							 return false;
						 }  
				 }
				 
		  }
		 
	 }


   return true;
 }
bool CWLANTestProc::WLANEndTest(bool bIsTx)
{
	  m_pFunWLANTestDev->Deivce_Exit();
	
	   if(!m_pPhone->WLAN_Enable(false,bIsTx,m_iAdbType))
	   {
			LogTrace(MSG_ERROR,"End WLAN fail");
			//CalFailLog(_T("_"),_T("_"),1002,"End WLAN fail");
			return false;
	   }

	   

  return true;
}

 bool CWLANTestProc::InitData()
 {
	 m_pFunWLANTestDev=m_piTesterDeviceCurr->m_piFuncWLANTest;
	 return true;
 }