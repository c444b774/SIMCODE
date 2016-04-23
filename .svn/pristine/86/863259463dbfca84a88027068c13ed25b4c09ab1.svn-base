#include "StdAfx.h"
#include "BBTest.h"
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
	if(!DoProcess())
	{
        
		return false;
	}
	return true;
}

 bool CBTTestProc::InitData(
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
	 itrFind=pcSettingMap->find(_T("FuncLIst"));
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
		m_RMSDEVMSpec.SetRange(CStr::StrToInt(strVtr[0]),CStr::StrToInt(strVtr[1]));
      
	 }

	 InitData();
	 return true;
 }

 bool CBTTestProc::BTTestMainFunc()
 {
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
   if(!m_pPhone->BT_Enable())
   {
        LogTrace(MSG_ERROR,"Init DUT BT fail");
	    CalFailLog(_T("_"),_T("_"),1002,"Init DUT BT fail");
	    return false;
   }
   LogTrace(MSG_MID,"Init DUT BT Pass");

   if(DEVICE_SUCCESS!=m_pFunBTTestDev->IBTTestInit(m_strDeviceAddr,strBTADDR))
   {
	    LogTrace(MSG_ERROR,"Init BT device fail");
	    CalFailLog(_T("_"),_T("_"),1001,"Init BT device fail");
	    return false;
	  
   }
   LogTrace(MSG_MID,"Init TestDevice BT Pass");
   for(IntItr itrType=m_striTypeVtr.begin();itrType!=m_striTypeVtr.end();++itrType)
   {
	   strCurrType=CStr::IntToStr(*itrType);
	 
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
	
	unsigned double iFreq=(iChannel+2402)*1000000;
	switch(eSigType)
	{
	    case 1:
		strBurstType="BR";
		strPacketType="DH1";
	break;
	   case 2:
		    strBurstType="BR";
		strPacketType="DH2";
	break;
		case 3:
			strBurstType="BR";
		strPacketType="DH3";
	break;
		case 4:
			strBurstType="EDR";
		strPacketType="E21P";
	break;
		case 5:
				strBurstType="EDR";
		strPacketType="E23P";
	break;
		case 6:
				strBurstType="EDR";
		strPacketType="E25P";
	break;
		case 7:
				strBurstType="EDR";
		strPacketType="E31P";
	break;
		case 8:
				strBurstType="EDR";
		strPacketType="E33P";
	break;
		case 9:
				strBurstType="EDR";
		strPacketType="E35P";
		break;

		default:
            strBurstType="EDR";
		   strPacketType="E35P";
			break;


	}
    if(m_pFunBTTestDev->IBTTestSetType(strBurstType,strPacketType)!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Device set Burst type fail");
      return false;
	}

	 if(m_pFunBTTestDev->IBTTestSetFreq(iFreq,0,dCableloss)!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Device set Burst Frequency  fail");
        return false;
	}
    
	  if(m_pFunBTTestDev->IBTTestSetTrigger(-30,2)!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Device set Trigger fail");
        return false;
	}
	  
     if(m_pFunBTTestDev->IBTTestInitMeasure(10)!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,"Device Measure On fail");
        return false;
	}
   
	 if(!m_pPhone->BT_TX_Test(iChannel,0,eSigType,0))
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
	 double dResult;
	 
	 if(m_pFunBTTestDev->IBTTestFetchResults(eSigType,vtrResult)!=DEVICE_SUCCESS)
	 {
		LogTrace(MSG_ERROR,"Fetch BT result  fail");
        return false;
	 }
	 for(CStringStringMapItr itrTest=m_str2strTestMap.begin();itrTest!=m_str2strTestMap.end();++itrTest)
	 {
		 CString strTestName=itrTest->first;
		 if(itrTest->second=="0")
			 continue;
		 if(strTestName=="TXPOWER")
		 {
			     if(vtrResult[2]=="INV")
			 {
				   TestFailLog(strCurrType,strCurrCH,1005,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),vtrResult[2],"dBm","BT Nomial Power Fail");
				 return false;
			 }
			 dResult=CStr::StrToFloat(vtrResult[2]);
			 if(m_PowerSpec.InRange(dResult))
			 {
				 TestPassLog(strCurrType,strCurrCH,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),CStr::FloatToStr(dResult),"dBm","BT Nomial Power pass");
				
			 }
			 else
			 {
				 TestFailLog(strCurrType,strCurrCH,1005,CStr::FloatToStr(m_PowerSpec.GetMax()),CStr::FloatToStr(m_PowerSpec.GetMin()),CStr::FloatToStr(dResult),"dBm","BT Nomial Power Fail");
				 return false;
			 }
		 }
		 if(strTestName=="DEVMRMS")
		 {
			    
			     if(vtrResult[12]=="INV")
			 {
				   TestFailLog(strCurrType,strCurrCH,1006,CStr::FloatToStr(m_RMSDEVMSpec.GetMax()),CStr::FloatToStr(m_RMSDEVMSpec.GetMin()),vtrResult[12],"dBm","BT DEVM Fail");
				 return false;
			 }
				dResult=CStr::StrToFloat(vtrResult[12]);
				 if(m_RMSDEVMSpec.InRange(dResult))
				 {
					 TestPassLog(strCurrType,strCurrCH,CStr::FloatToStr(m_RMSDEVMSpec.GetMax()),CStr::FloatToStr(m_RMSDEVMSpec.GetMin()),CStr::FloatToStr(dResult),"","BT DEVM pass");
					
				 }
				 else
				 {
					 TestFailLog(strCurrType,strCurrCH,1006,CStr::FloatToStr(m_RMSDEVMSpec.GetMax()),CStr::FloatToStr(m_RMSDEVMSpec.GetMin()),CStr::FloatToStr(dResult),"","BT DEVM Fail");
					 return false;
				 }  
		 }
		 
	 }


   return true;
 }
bool CBTTestProc::BTEndTest()
{
  return true;
}

 bool CBTTestProc::InitData()
 {
	 m_pFunBTTestDev=m_piTesterDevice->m_piFuncBTTest;
	 return true;
 }