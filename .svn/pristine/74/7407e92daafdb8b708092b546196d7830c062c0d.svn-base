#include "StdAfx.h"
#include "DTVTestProc.h"
RF_IMPLEMENT_DYNCREATE(CDTVTestProc)
CDTVTestProc::CDTVTestProc(void)
{
	m_mapClassFunc[_T("DTVTestCallMainFunc")]=&CDTVTestProc::DTVTestMainFunc;
    m_mapClassFunc[_T("DTVTestRXFunc")]=&CDTVTestProc::DTVTestRXFunc;
	m_mapClassFunc[_T("DTVCalLossFunc")]=&CDTVTestProc::DTVTCalLossFunc;
	m_iItemCode=1018;
}

CDTVTestProc::~CDTVTestProc(void)
{
}
bool CDTVTestProc::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CDTVTestProc::Handle()
{
	if(!DoProcess())
	{
          m_pFunDTVTestDev->Deivce_Exit();
	     m_pPhone->CloseATComport();
		return false;
	}

	m_pFunDTVTestDev->Deivce_Exit();
	m_pPhone->CloseATComport();
	return true;
}

 bool CDTVTestProc::InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) 
 {
	 m_bIsCalLoss=false;
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
		if(strfunc=="DTVCalLossFunc")
		{
			m_bIsCalLoss=true;
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

		  itrFind=pcSettingMap->find(_T("StartLoss"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'StartLoss' from ini file!");
			 return false;
		 }
		 else
		 {
			 m_dInitLoss=CStr::StrToFloat(itrFind->second);
		 } 

		  itrFind=pcSettingMap->find(_T("StepLossdB"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'StepLossdB' from ini file!");
				 return false;
			 }
			 else
			 {
				 m_dStepSizedB=CStr::StrToFloat(itrFind->second);
			 } 

			  itrFind=pcSettingMap->find(_T("MaxLoss"));
			 if(itrFind==pcSettingMap->end())
			 {
				 LogTrace(MSG_ERROR,"Not Find 'MaxLoss' from ini file!");
				 return false;
			 }
			 else
			 {
				 m_dMaxLoss=CStr::StrToFloat(itrFind->second);
			 } 



		}
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

	 
		  itrFind=pcSettingMap->find(_T("UseTestSet"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'UseTestSet' from ini file! defalt is use");
		 m_bIsUseDevice=true;
	 }
	 else
	 {
		 m_bIsUseDevice=CStr::StrToBool(itrFind->second);
	 } 


	 itrFind=pcSettingMap->find(_T("DTVWaveFileRootPath"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DTVWaveFileRootPath' from ini file!");
		 return false;
	 }
	 else
	 {
		 m_strWaveFileRootPath=itrFind->second;
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

      itrFind=pcSettingMap->find(_T("DTVDevicePort"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_WARNING,"Not Find 'DTVDevicePort' from ini file!.default use pre config");
		 //return false;
		 m_iOutPort=m_piTesterDeviceCurr->m_iInputPort;
	 }
	 else
	 {
		 m_iOutPort=CStr::StrToInt(itrFind->second);
	 }

     itrFind=pcSettingMap->find(_T("DTVBERSpec"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DTVBERSpec' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		m_RXBERSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));  
	 }


	   itrFind=pcSettingMap->find(_T("DTVCNSpec"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DTVCNSpec' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		m_RXCNSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));  
	 }
    

	 
	  itrFind=pcSettingMap->find(_T("DTVChannelList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DTVChannelList' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2IntVtr(m_iChannelVtr,strVtr);
      
	 }
    
     itrFind=pcSettingMap->find(_T("DTVWaveFileList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'DTVWaveFileList' from ini file!");
		 return false;
	 }
	 else
	 {
		strValue=itrFind->second;
        CStr::ParseString(strValue,_T(","),m_strWaveFileVtr);
		
      
	 }
    
	  itrFind=pcSettingMap->find(_T("RXPerformaceList"));
	 if(itrFind==pcSettingMap->end())
	 {
		 LogTrace(MSG_ERROR,"Not Find 'RXPerformaceList' from ini file!");
		 return false;
	 }
	 else
	 {
		 CStringVtr strTestNameVtr;
		 CStringVtr strTestFlagVtr;
		 strValue=itrFind->second;
		 CStr::ParseString(strValue,_T(","),strTestNameVtr);
         itrFind=pcSettingMap->find(_T("RXPerformaceListBitMask"));
		  if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_ERROR,"Not Find 'RXPerformaceListBitMask' from ini file!");
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

	 InitData();
	 return true;
 }

 bool CDTVTestProc::DTVTestMainFunc()
 {

	 if(m_bIsUseDevice)

	 {
			 if(DEVICE_SUCCESS!=m_pFunDTVTestDev->IDTVTestInit(m_strDeviceAddrCurr))
		   {
				LogTrace(MSG_ERROR,"Init DTV device fail");
				CalFailLog(_T("_"),_T("_"),1001,"Init DTV device fail");
				return false;
			  
		   }

			if(DEVICE_SUCCESS!=m_pFunDTVTestDev->IDTVTestSetInOutPort(m_iOutPort))
		   {
				LogTrace(MSG_ERROR,"Set DTV device port fail");
				CalFailLog(_T("_"),_T("_"),1001,"Set DTV device port fail");
				return false;
			  
		   }
	 }

	if(!m_pPhone->OpenATComport(m_iATComport))
	   {
			LogTrace(MSG_ERROR,"Open Comport Fail");
			return false;
	   }
	 for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)
			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
		else 
		{

			  if(m_bIsCalLoss)
			  {
					   CStringVtr strVtrCh;
					   CStringVtr strVtrLoss;
					   CStringStringMap mapString2String;
					   strVtrCh.push_back(CStr::IntToStr(m_iChannelVtr[0]));
					   strVtrLoss.push_back(CStr::FloatToStr(m_dCalLoss));
					   CStr::MakeVector2Map(strVtrCh,strVtrLoss,mapString2String);
					 if(!m_LossFinder.UpdateLossIniFromMap("DTV",mapString2String))
				   {
					 CalFailLog("_","_",1003,"Cable loss ini not exist");
					 return false;
				   }
			  }
		}
	
	}

	 if(m_bIsUseDevice)
	 {

		 if(m_pFunDTVTestDev->IDTVTestSetDLSigOn(false)!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Device set DL ON fail");
				CalFailLog("_","_",1008,"Device set DL ON fail");
			  return false;
			} 
	 

		m_pFunDTVTestDev->Deivce_Exit();
	 }
	m_pPhone->CloseATComport();
	 return true;

 }
bool CDTVTestProc::DTVTestRXSpec(int iChannel)
{
	double CNO;
	double SBER;
	int iRetryTimes=3;
	bool bPass1=false;
	bool bPass2=false;
	CString strItemType;
	CString strItemType1;
	int iRxLevLog=m_dCellPower;
	int bTotalPass=1;
	
	int iTestmask[50]={0};
	if(m_bIsUseDevice)
	{
		 if(m_pFunDTVTestDev->IDTVTestSetDLSigOn(true)!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Device set DL ON fail");
				CalFailLog("_","_",1008,"Device set DL ON fail");
			  return false;
			}
		

		Sleep(1000);
	}
	 do{
				if(!m_pPhone->DTV_GetBerCNO(iChannel,CNO,SBER))
			   {
					LogTrace(MSG_ERROR,"Get CNO and SBER fail");
					CalFailLog("_","_",1008,"Get CNO and SBER fail");
					return false;
			   }

             int iTestItemNum=0;

			 for(CStringStringMapItr itrTest=m_str2strTestMap.begin();itrTest!=m_str2strTestMap.end();++itrTest,++iTestItemNum)
			 {
				 CString strTestName=itrTest->first;
				 if(itrTest->second=="0")
					 continue;
				 if(strTestName=="BER")
				 {
					 strItemType="DTV_"+CStr::IntToStr(iRxLevLog)+"dBm_SBER";
					 if(m_RXBERSpec.InRange(SBER))
					 {
						
						iTestmask[iTestItemNum]=1;
					 }
					 else
					 {
						 iTestmask[iTestItemNum]=0;
						 if(iRetryTimes==1)
						 {
						
							 TestFailLog(strItemType,strCurrCH,1010,CStr::FloatToStr(m_RXBERSpec.GetMax()),CStr::FloatToStr(m_RXBERSpec.GetMin()),CStr::FloatToStr(SBER),"_","DTV BER  fail");  
							 return false;
						 }
					 }
				 }
				 if(strTestName=="CN")
				 {
					    
						strItemType1="DTV_"+CStr::IntToStr(iRxLevLog)+"dBm_CN";
						 if(m_RXCNSpec.InRange(CNO/10))
						 {
							 
							iTestmask[iTestItemNum]=1;
						 }
						 else
						 {
							  iTestmask[iTestItemNum]=0;
					         if(iRetryTimes==1)
							 {
								 TestFailLog(strItemType,strCurrCH,1006,CStr::FloatToStr(m_RXCNSpec.GetMax()),CStr::FloatToStr(m_RXCNSpec.GetMin()),CStr::FloatToStr(CNO/10),"","DVT CN Fail");
								 return false;
							 }
						 }  
				 }


				
				 
			 }

	  for(int i=0;i<iTestItemNum;i++)
	  {
          if(iTestmask[i])
            bTotalPass=1;
		  else
		  {
            bTotalPass=0;
			break;
		  }

	  }

	  if(bTotalPass)
	   {

		   TestPassLog(strItemType,strCurrCH,CStr::FloatToStr(m_RXBERSpec.GetMax()),CStr::FloatToStr(m_RXBERSpec.GetMin()),CStr::FloatToStr(SBER),"_","DTV BER pass");
    
		   TestPassLog(strItemType1,strCurrCH,CStr::FloatToStr(m_RXCNSpec.GetMax()),CStr::FloatToStr(m_RXCNSpec.GetMin()),CStr::FloatToStr(CNO/10),"","DTV CN pass");
		  break;
	   }
			 Sleep(100);
	 }while(iRetryTimes-->0);

	
		return true;

   
}
bool CDTVTestProc::DTVHandover(const CString& strType,int iCHannel,double dlCellPower)
  {
     double dDlFrequency;
	 double dLoss=m_LossFinder.GetDTVLoss(iCHannel);
     
      dDlFrequency=(iCHannel-13)*6+473.143; //MHZ
	  if(m_bIsUseDevice)
	  {
		   if(m_pFunDTVTestDev->IDTVTestSetDLType(strType)!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Device set DL wavefile fail");
			  return false;
			}

	   		 if(m_pFunDTVTestDev->IDTVTestSetDLFreqPower(dDlFrequency,dlCellPower,dLoss)!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Device set DL frequency dl power  fail");
				return false;
			}
	  }


	 return true;


  }
 bool CDTVTestProc::DTVTCalLossFunc()
 {

	  double CNO;
	  double SBER;
	  double dLoss;
	  CString strMsg;
     CString strDlType;
     strDlType=m_strWaveFileRootPath;
	 CString strWaveType=m_strWaveFileVtr[0];
     strDlType+=strWaveType;
	 int iCalChannel=m_iChannelVtr[0];
	 strCurrCH=CStr::IntToStr(iCalChannel);
	 int iRetryTimes;
	  double dDlFrequency;
	  dDlFrequency=(iCalChannel-13)*6+473.143; //MHZ

	     if(m_pFunDTVTestDev->IDTVTestSetDLType(strDlType)!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,"Device set DL wavefile fail");
			  return false;
			}
        
       
		 for(dLoss=m_dInitLoss;dLoss<m_dMaxLoss;dLoss+=m_dStepSizedB)
		 {
			   strMsg.Format("Calculate GPS Loss, time is long ,wait.......");
			   LogTrace(MSG_MID,strMsg);
				   iRetryTimes=2;
				   if(m_pFunDTVTestDev->IDTVTestSetDLSigOn(false)!=DEVICE_SUCCESS)
				{
					LogTrace(MSG_ERROR,"Device set DL ON fail");
					CalFailLog("_","_",1008,"Device set DL ON fail");
				  return false;
				}
				  if(m_pFunDTVTestDev->IDTVTestSetDLFreqPower(dDlFrequency,m_dGoldenCellPower,dLoss)!=DEVICE_SUCCESS)
					{
						LogTrace(MSG_ERROR,"Device set DL frequency dl power  fail");
						return false;
					}

				   if(m_pFunDTVTestDev->IDTVTestSetDLSigOn(true)!=DEVICE_SUCCESS)
				{
					LogTrace(MSG_ERROR,"Device set DL ON fail");
					CalFailLog("_","_",1008,"Device set DL ON fail");
				  return false;
				}
			  do
			  {
				  if(!m_pPhone->DTV_GetBerCNO(iCalChannel,CNO,SBER))
				   {
						LogTrace(MSG_ERROR,"Get CNO and SBER fail");
						CalFailLog("_","_",1008,"Get CNO and SBER fail");
						return false;
				   }

                if(m_RXBERSpec.InRange(SBER))
					 {
					   m_dCalLoss=dLoss;
                       TestPassLog("_",strCurrCH,CStr::FloatToStr(m_dInitLoss),CStr::FloatToStr(m_dMaxLoss),CStr::FloatToStr(dLoss),"dB","DTV Cal loss pass");
                       return true;
					 }

				 strMsg.Format("Trying Loss=%.2f  StepSize=%.2f StartLoss=%.2f  MaxLoss=%.2f ",dLoss,m_dStepSizedB,m_dInitLoss,m_dMaxLoss); 
			     LogTrace(MSG_MID,strMsg);

			  }while(--iRetryTimes);

              
		 }
     
    

     TestFailLog("_",strCurrCH,1100,CStr::FloatToStr(m_dInitLoss),CStr::FloatToStr(m_dMaxLoss),CStr::FloatToStr(dLoss),"dB","DTV Cal reate max limit");
	 return false;
 }
 bool CDTVTestProc::DTVTestRXFunc()
 {
	 CString strDlType;
     strDlType=m_strWaveFileRootPath;
	  for(CStringItr itrType=m_strWaveFileVtr.begin();itrType!=m_strWaveFileVtr.end();++itrType)
   {
	   
	    strDlType+=*itrType;
	   for(IntItr itrCh=m_iChannelVtr.begin();itrCh!=m_iChannelVtr.end();++itrCh)
	   {
		   strCurrCH=CStr::IntToStr(*itrCh);

		   if(!DTVHandover(strDlType,*itrCh,m_dCellPower))
		   {
      
			  CalFailLog(strCurrType,strCurrCH,1200," DTV  Test RX Handover fail");
			  return false;
		   }

		   if(!DTVTestRXSpec(*itrCh))
		   {
			   return false;
		   }


	   }
   }
    
     
	
	
	 return true;
 }

 

 bool CDTVTestProc::InitData()
 {
	 m_pFunDTVTestDev=m_piTesterDeviceCurr->m_piFuncDTVTest;
	 return true;
 }