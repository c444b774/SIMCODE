#include "StdAfx.h"
#include "BTTestProc.h"
RF_IMPLEMENT_DYNCREATE(CBTTestProc)
CBTTestProc::CBTTestProc(void)
{
	m_mapClassFunc[_T("BTTestCallMainFunc")]=&CBTTestProc::BTTestMainFunc;
	m_mapClassFunc[_T("BTTestTXFunc")]=&CBTTestProc::BTTestTXFunc;
	m_iItemCode=1001;
	
}

CBTTestProc::~CBTTestProc(void)
{
}
bool CBTTestProc::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CBTTestProc::Handle()
{
	 CString strMsg;
	 if(!m_pPhone->SetAtMode(m_iIsUseAT))
   {
        LogTrace(MSG_ERROR,"Set BT AT mode fail");
	    CalFailLog(_T("_"),_T("_"),1002,"Set BT AT mode fail");
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

	if(!DoProcess())
	{
         if(m_iIsUseAT)
	 {
		 m_pPhone->CloseATComport();
	  
	 }
 
		return false;
	}

	if(m_iIsUseAT)
	 {
		 m_pPhone->CloseATComport();
	  
	 }

	return true;
}

 bool CBTTestProc::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {

	 m_bFirst=true;
    CStringStringMapItr itrFind;
	CRFObjectMap::iterator itrObjectItr;
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
	 }
    
    itrFind=pcSettingMap->find(_T("BTADDR"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'BTADDR' from ini file!");
		 return false;
	 }
	 else
	 {
		 strBTADDR=itrFind->second;
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

    itrFind=pcSettingMap->find(_T("BTDevicePort"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'BTDevicePort' from ini file!.default use pre config");
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
    
	 itrFind=pcSettingMap->find(_T("BTSignalTypeList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'BTSignalTypeList' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2IntVtr(m_striTypeVtr,strVtr);
      
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
        CStr::ParseString(strValue,_T(","),strVtr);
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
	 m_bMaxLev=m_PowerSpec.GetMax();

	  itrFind=pcSettingMap->find(_T("DEVMRMSSpec"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DEVMRMSSpec' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		m_RMSDEVMSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
      
	 }

	 InitData();
	 return true;
 }

 bool CBTTestProc::BTTestMainFunc()
 {

	  if(DEVICE_SUCCESS!=m_pFunBTTestDev->IBTTestInit(m_strDeviceAddrCurr,strBTADDR))
   {
	    LogTrace(MSG_ERROR,"Init BT device fail");
	    CalFailLog(_T("_"),_T("_"),1001,"Init BT device fail");
	    return false;
	  
   }
   LogTrace(MSG_MID,"Init TestDevice BT Pass");
   

	   if(DEVICE_SUCCESS!=m_pFunBTTestDev->IBTTestSetInOutPort(m_iInOutPort,m_iInOutPort))
   {
	    LogTrace(MSG_ERROR,"Set BT port fail");
	    CalFailLog(_T("_"),_T("_"),1001,"Set BT port fail");
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
 bool CBTTestProc::BTTestTXFunc()
 {
	
	 CString strMsg;
	
  /* if(!m_pPhone->BT_Enable())
   {
        LogTrace(MSG_ERROR,"Init DUT BT fail");
	    CalFailLog(_T("_"),_T("_"),1002,"Init DUT BT fail");
	    return false;
   }
   LogTrace(MSG_MID,"Init DUT BT Pass");*/

    
 
   for(IntItr itrType=m_striTypeVtr.begin();itrType!=m_striTypeVtr.end();++itrType)
   {
	 
	 
	   for(IntItr itrCh=m_iChannelVtr.begin();itrCh!=m_iChannelVtr.end();++itrCh)
	   {
		   strCurrCH=CStr::IntToStr(*itrCh);

		   if(!BTHandover(*itrType,*itrCh))
		   {
      
			  CalFailLog(strCurrType,strCurrCH,1003," BT  Test Handover fail");
			  return false;
		   }
		   strMsg.Format("BT Handover :signal type=%s ;Channel=%s Pass",strCurrType,strCurrCH);
		    LogTrace(MSG_MID,strMsg);

		   if(!BTTestTxSpec(*itrType))
		   {
		   LogTrace(MSG_WARNING,"Retry BT Test.....");
		   m_bFirst=false;
		   int iDUTFreq=2402+*itrCh;
		   if(m_pFunBTTestDev->IBTTestInitMeasure(1)!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Device Measure On fail");
				return false;
			}
			if(!m_pPhone->BT_TX_Test(iDUTFreq,0,*itrType,0))
			 {
				LogTrace(MSG_ERROR,"DUT handover fail");
				return false;
			 }
              if(!BTTestTxSpec(*itrType))
			  

			   return false;
		   }


	   }
   }

   if(!BTEndTest())
   {
      LogTrace(MSG_WARNING,"End BT Test not successfully!");
   }

   return true;
 }
 bool CBTTestProc::BTHandover(int eSigType,int iChannel)
 {
    CString strBurstType; 
	CString strPacketType;
	double dCableloss=m_LossFinder.GetBTLoss(iChannel);

	double iFreq=(2402+iChannel)*1000000;
	int iDUTFreq=2402+iChannel;
	switch(eSigType)
	{
	    case 1:
		strBurstType="BR";
		strPacketType="DH1";
		strCurrType="BT_DH1";
	break;
	   case 2:
		    strBurstType="BR";
		strPacketType="DH2";
		strCurrType="BT_DH2";
	break;
		case 3:
			strBurstType="BR";
		strPacketType="DH3";
		strCurrType="BT_DH3";
	break;
		case 4:
			strBurstType="EDR";
		strPacketType="E21P";
		strCurrType="BT_2DH1";
	break;
		case 5:
				strBurstType="EDR";
		strPacketType="E23P";
		strCurrType="BT_2DH3";
	break;
		case 6:
				strBurstType="EDR";
		strPacketType="E25P";
		strCurrType="BT_2DH5";
	break;
		case 7:
				strBurstType="EDR";
		strPacketType="E31P";
		strCurrType="BT_3DH1";
	break;
		case 8:
				strBurstType="EDR";
		strPacketType="E33P";
		strCurrType="BT_3DH3";
	break;
		case 9:
				strBurstType="EDR";
		strPacketType="E35P";
		strCurrType="BT_3DH5";
		break;

		default:
            strBurstType="EDR";
		   strPacketType="E35P";
		   strCurrType="BT_3DH5";

			break;


	}
    if(m_pFunBTTestDev->IBTTestSetType(strBurstType,strPacketType)!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Device set Burst type fail");
      return false;
	}

	 if(m_pFunBTTestDev->IBTTestSetFreq(iFreq,m_bMaxLev,dCableloss)!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Device set Burst Frequency  fail");
        return false;
	}
    
	  if(m_pFunBTTestDev->IBTTestSetTrigger(-25,25000)!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Device set Trigger fail");
        return false;
	}
	  
     if(m_pFunBTTestDev->IBTTestInitMeasure(1)!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Device Measure On fail");
        return false;
	}
   
	 if(!m_pPhone->BT_TX_Test(iDUTFreq,0,eSigType,0))
	 {
		LogTrace(MSG_ERROR,"DUT handover fail");
        return false;
	 }
      
	 return true;
 }
 bool CBTTestProc::BTTestTxSpec(int eSigType)
 {
	 CStringVtr vtrResult;
	 CString strResult;
	 CString strItemType;
	 double dResult;
	 
	 if(m_pFunBTTestDev->IBTTestFetchResults(eSigType,vtrResult)!=DEVICE_SUCCESS)
	 {
		LogTrace(MSG_ERROR,"Fetch BT result  fail");
		if(!m_bFirst)
		CalFailLog("_","_",1100,"Fetch BT result  fail");
        return false;
	 }
	 for(CStringStringMapItr itrTest=m_str2strTestMap.begin();itrTest!=m_str2strTestMap.end();++itrTest)
	 {
		 CString strTestName=itrTest->first;
		 if(itrTest->second=="0")
			 continue;
		 if(strTestName=="TXPOWER")
		 {
			 strItemType=strCurrType+"_TX_PWR";
			     if(vtrResult[2]=="INV")
			 {
				   if(!m_bFirst)
				   TestFailLog(strItemType,strCurrCH,1005,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),vtrResult[2],"dBm","BT Nomial Power Fail");
				 return false;
			 }
			 dResult=CStr::StrToFloat(vtrResult[2]);
			 if(m_PowerSpec.InRange(dResult))
			 {
				 TestPassLog(strItemType,strCurrCH,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),CStr::FloatToStr(dResult),"dBm","BT Nomial Power pass");
				
			 }
			 else
			 {
				 if(!m_bFirst)
				 TestFailLog(strItemType,strCurrCH,1005,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),CStr::FloatToStr(dResult),"dBm","BT Nomial Power Fail");
				 return false;
			 }
		 }
		 if(strTestName=="DEVMRMS")
		 {
			    strItemType=strCurrType+"_TX_DEVM_RMS";
			     if(vtrResult[12]=="INV")
			 {
				   if(!m_bFirst)
				   TestFailLog(strItemType,strCurrCH,1006,CStr::FloatToStr(m_RMSDEVMSpec.GetMax()),CStr::FloatToStr(m_RMSDEVMSpec.GetMin()),vtrResult[12],"","BT DEVM Fail");
				 return false;
			 }
				dResult=CStr::StrToFloat(vtrResult[12]);
				 if(m_RMSDEVMSpec.InRange(dResult))
				 {
					 TestPassLog(strItemType,strCurrCH,CStr::FloatToStr(m_RMSDEVMSpec.GetMax()),CStr::FloatToStr(m_RMSDEVMSpec.GetMin()),CStr::FloatToStr(dResult),"","BT DEVM pass");
					
				 }
				 else
				 {
			         if(!m_bFirst)
					 TestFailLog(strItemType,strCurrCH,1006,CStr::FloatToStr(m_RMSDEVMSpec.GetMax()),CStr::FloatToStr(m_RMSDEVMSpec.GetMin()),CStr::FloatToStr(dResult),"","BT DEVM Fail");
					 return false;
				 }  
		 }
		 
	 }


   return true;
 }
bool CBTTestProc::BTEndTest()
{

	m_pFunBTTestDev->Deivce_Exit();
	
  return true;
}

 bool CBTTestProc::InitData()
 {
	 m_pFunBTTestDev=m_piTesterDeviceCurr->m_piFuncBTTest;
	 return true;
 }