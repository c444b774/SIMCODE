#include "stdafx.h"
#include "GSM_EDGE_NSFT_MeasLoop.h"

RF_IMPLEMENT_DYNCREATE(CGSM_EDGE_NSFT_MeasLoop)

CGSM_EDGE_NSFT_MeasLoop::CGSM_EDGE_NSFT_MeasLoop()
{
	m_mapClassFunc[_T("GSM_NoSignal_TestMainFunc")]=&CGSM_EDGE_NSFT_MeasLoop::CGSM_EDGE_NSFT_MeasLoopMainFunc;
	m_mapClassFunc[_T("GSM_NoSignal_TestFunc")]=&CGSM_EDGE_NSFT_MeasLoop::CGSM_EDGE_NSFT_MeasLoopFunc;


	m_intChNum=0;
}

CGSM_EDGE_NSFT_MeasLoop::~CGSM_EDGE_NSFT_MeasLoop()
{
	
}

bool CGSM_EDGE_NSFT_MeasLoop::DoProcess()
{
	 return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CGSM_EDGE_NSFT_MeasLoop::Handle()
{
	if((!DoProcess())||(m_iFailFlag!=0))
	{
		m_pFunGSMTestDev->Deivce_Exit();

		m_pPhone->FTM_GSM_EndCall(300);

		m_pPhone->CloseComport();
		return false;
	}
	return true;
}

bool CGSM_EDGE_NSFT_MeasLoop::CGSM_EDGE_NSFT_MeasLoopMainFunc()
{
	for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)			
	{
		FPClassFunc fpTestFunc=*itrFP;
		if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
			return false;
	}
	return true;
}
bool CGSM_EDGE_NSFT_MeasLoop::CGSM_EDGE_NSFT_MeasLoopFunc()
{  
   int iErrorcode;

   m_IsEdge==0?(m_iItemCode=GSM_SetCableLoss_BaseItemCode):(m_iItemCode=EDGE_SetCableLoss_BaseItemCode);

   if (!SetGSMTestLOSS())
   {
	   LogTrace(MSG_ERROR,_T("SetGSMTestLOSS Fail!"))
//		   m_iErrorcode=iErrorcode;
	   return false;
   }
   TestPassLog(m_strCurrBand,"_","_","_","_","_","Set CableLOSS Pass");
   TestPassLogEx(m_strCurrBand,"_","_","_","_","_","HandOver to Band","BANDHAND");

   int nIndex=0;
   for (int chIndex=0;chIndex<m_intChNum;chIndex++)  
   {		
	   for (int pclIndex=0;pclIndex<m_intCh_PclNum[chIndex];pclIndex++)
	   {
			CString str,strPcl,strChan,strTestItem;
			strTestItem.Format("%s",m_strVtrTestItem[nIndex]);
			strPcl.Format("%d",m_iTestPcl[nIndex]);
			strChan.Format("%d",m_iTestChan[chIndex]);
			str.Format("%d",nIndex);

			if (m_iTestPcl[nIndex]==-1)
			{
				continue;
			}
			m_IsEdge==0?(m_iItemCode=GSM_HandOver_Device_BaseItemCode):(m_iItemCode=EDGE_HandOver_Device_BaseItemCode);
			if((iErrorcode=m_pFunGSMTestDev->IGSMTestHandOver(CGSMBandInfo::GetPhoneMode(m_iCurrBand),m_iTestChan[chIndex],m_iTestPcl[nIndex],m_IsEdge))!=DEVICE_SUCCESS)
			{
				LogTrace(MSG_ERROR,_T("IGSMTestHandOver(Device) Fail!"))
					m_iErrorcode=iErrorcode;
				m_iFailFlag++;
				return false;
			}
			TestPassLog(m_strCurrBand,CStr::IntToStr(m_iTestChan[chIndex])+'-'+CStr::IntToStr(m_iTestPcl[nIndex]),"_","_","_","_","Instr handover Pass");
			
			m_IsEdge==0?(m_iItemCode=GSM_HandOver_Phone_BaseItemCode):(m_iItemCode=EDGE_HandOver_Phone_BaseItemCode);
			if((iErrorcode=m_pPhone->FTM_GSM_BER_Handover(m_iTestChan[chIndex],CGSMBandInfo::GetPhoneTestMode(m_iCurrBand),0,2,FTM_GSM_BER_SPEECH_FULL_RATE,m_iTestPcl[nIndex],FTM_GSM_BER_Loopback_Type_C,20,m_IsEdge))!=PHONE_SUCCESS)
			{           
				LogTrace(MSG_ERROR,_T("FTM_GSM_BER_Handover(Handset) Fail!"))
					m_iErrorcode=iErrorcode;
				m_iFailFlag++;
				CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_GSM_BER_Handover Fail!");
				return false;
			}
			TestPassLog(m_strCurrBand,CStr::IntToStr(m_iTestChan[chIndex])+'-'+CStr::IntToStr(m_iTestPcl[nIndex]),"_","_","_","_","Handset handover Pass");


			m_iItemCode=GetItemCode(m_IsEdge,m_iCurrBand,m_iTestChan[chIndex],m_iTestPcl[nIndex]);

			m_strVtrResultTX.clear();
			if (!StartTxMeasurment(strTestItem))
			{
				TestFailLog(m_strCurrBand,"_",nIndex,"_","_","_","_","TxMeasurment Fail");
				m_iFailFlag++;
				return false;
			}			
			if (m_IsEdge==0)
			{			
				if (!CheckTXResult(nIndex,strPcl,strChan,strTestItem))
				{
				m_iFailFlag++;
					return false;
				}
			}else if (m_IsEdge==1)
			{
				if (!CheckTXResultEdge(nIndex,strPcl,strChan,strTestItem))
				{
				m_iFailFlag++;
					return false;
				}
			}
			else
			{
				m_iFailFlag++;
				return false;
			}

			if (!StartRxLevelMeasurment(strTestItem))
			{
				m_iFailFlag++;
				return false;
			}
			Sleep(200);
			if (!CheckRXLevelResult(nIndex,strPcl,strChan,strTestItem))
			{
				m_iFailFlag++;
				return false;
			}

			if (!StartRxBerMeasurment(strTestItem))
			{
				m_iFailFlag++;
				return false;
			}
			if (!CheckRXBerResult(nIndex,strPcl,strChan,strTestItem))
			{
				m_iFailFlag++;
				return false;
			}

			nIndex++;
	   }
   }

	return true;
}

 bool CGSM_EDGE_NSFT_MeasLoop::InitData(
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

    itrFind=pcSettingMap->find(_T("TestBand"));
    if(itrFind==pcSettingMap->end())
	{
		 LogTrace(MSG_FATAL,_T("Not Find TestBand"));
		 return false;
	}
	else
	{
		strValue=itrFind->second;
		if (!strcmp(strValue,"EGSM"))
		{
			m_iCurrBand=GSM_EGSM_BAND_ID;
			m_strCurrBand="GSM900";
		}
		else if (!strcmp(strValue,"DCS"))
		{
			m_iCurrBand=GSM_DCS_BAND_ID;
			m_strCurrBand="GSM1800";
		}
		else if (!strcmp(strValue,"PCS"))
		{
			m_iCurrBand=GSM_PCS_BAND_ID;
			m_strCurrBand="GSM1900";
		}
		else if (!strcmp(strValue,"GSM850"))
		{
			m_iCurrBand=GSM_850_BAND_ID;
			m_strCurrBand="GSM850";
		}
		else
		{
			LogTrace(MSG_FATAL,_T("WrongTestBand"));
			return false;
		}		
	}

	itrFind=pcSettingMap->find(_T("IsEdge"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,_T("Not Find IsEdge"));
		return false;
	}
	else
	{
		m_IsEdge=CStr::StrToInt(itrFind->second);
	}

	itrFind=pcSettingMap->find(_T("UseFollowPara"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,_T("Not Find UseFollowPara"));
		return false;
	}
	else
	{
		m_bUseCfgPara=CStr::StrToBool(itrFind->second);
	}

	if (m_bUseCfgPara)
	{
		CString strtemp;
		CStringVtr strVtrtemp;
		itrFind=pcSettingMap->find(_T("TestChan"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find TestChan"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2IntVtr(m_iTestChan,strVtrtemp);
		}

		int nPcl=1;
		for(IntItr itrChan=m_iTestChan.begin();itrChan!=m_iTestChan.end();++itrChan,++m_intChNum)
		{
			strtemp.Empty();
			strVtrtemp.clear();
			int nTsize;

			strtemp.Format("TestPCL_CH%d",nPcl);
			itrFind=pcSettingMap->find(_T(strtemp));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_FATAL,_T(strtemp));
				return false;
			}
			else
			{
				nTsize=m_iTestPcl.size();
				strtemp=itrFind->second;
				CStr::ParseString(strtemp,_T(","),strVtrtemp);
				CStr::StrVtr2IntVtr(m_iTestPcl,strVtrtemp);
			}
			nPcl++;
			m_intCh_PclNum.push_back(m_iTestPcl.size()-nTsize);
		}

		for(int i=1;i<=m_intChNum;i++)
		{
			for (int j=1;j<=m_intCh_PclNum[i-1];j++ )
			{
				strtemp.Empty();
				strVtrtemp.clear();

				strtemp.Format("TestItem_CH%d_PCL%d",i,j);
				itrFind=pcSettingMap->find(_T(strtemp));
				if(itrFind==pcSettingMap->end())
				{
					LogTrace(MSG_FATAL,_T(strtemp));
					return false;
				}
				else
				{
					strtemp=itrFind->second;
					m_strVtrTestItem.push_back(strtemp);
				}
			}

		}


		itrFind=pcSettingMap->find(_T("RxLevel"));
		if (itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find RxLevel"));
			return false;
		}
		else
		{
			m_iRxlevel=CStr::StrToInt(itrFind->second);
		}

		itrFind=pcSettingMap->find(_T("EGSMCallCurrentLimit"));
		if (itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find EGSMCallCurrentLimit"));
			return false;
		}
		else
		{
			m_iCallCurrLim=CStr::StrToInt(itrFind->second);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("PwrRangMax"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find PwrRangMax"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrPwrMax,strVtrtemp);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("PwrRangMin"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find PwrRangMin"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrPwrMin,strVtrtemp);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("SwiMHz"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find SwiMHz"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2IntVtr(m_iVtrSwiHz,strVtrtemp);
		}
		
		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("SwiLimHighPcl"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find SwiLimHighPcl"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrSwiHighPcl,strVtrtemp);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("SwiLimLowPcl"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find SwiLimLowPcl"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrSwiLowPcl,strVtrtemp);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("ModMHz"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find ModMHz"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2IntVtr(m_iVtrModHz,strVtrtemp);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("ModLimHighPcl"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find ModLimHighPcl"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrModHighPcl,strVtrtemp);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("ModLimLowPcl"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find ModLimLowPcl"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrModLowPcl,strVtrtemp);
		}

		itrFind=pcSettingMap->find(_T("PhaseErrAvg"));
		if (itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find PhaseErrAvg"));
			return false;
		}
		else
		{
			m_dPhaseErrAvg=CStr::StrToFloat(itrFind->second);
		}

		itrFind=pcSettingMap->find(_T("PhaseErrMax"));
		if (itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find PhaseErrMax"));
			return false;
		}
		else
		{
			m_dPhaseErrMax=CStr::StrToFloat(itrFind->second);
		}

		itrFind=pcSettingMap->find(_T("FreqErr"));
		if (itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find FreqErr"));
			return false;
		}
		else
		{
			m_dFreqErr=CStr::StrToFloat(itrFind->second);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("RxLevelRang"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find RxLevelRang"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrRxLevel,strVtrtemp);
		}

		strtemp.Empty();
		strVtrtemp.clear();
		itrFind=pcSettingMap->find(_T("RxBerRang"));
		if(itrFind==pcSettingMap->end())
		{
			LogTrace(MSG_FATAL,_T("Not Find RxBerRang"));
			return false;
		}
		else
		{
			strtemp=itrFind->second;
			CStr::ParseString(strtemp,_T(","),strVtrtemp);
			CStr::StrVtr2DblVtr(m_dVtrRxBer,strVtrtemp);
		}

		//EDGE only as follow
		if (m_IsEdge==1)
		{
			itrFind=pcSettingMap->find(_T("EVMRMS"));
			if (itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_FATAL,_T("Not Find EVMRMS"));
				return false;
			}
			else
			{
				m_dEvmRms=CStr::StrToFloat(itrFind->second);
			}

			itrFind=pcSettingMap->find(_T("EVMPeak"));
			if (itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_FATAL,_T("Not Find EVMPeak"));
				return false;
			}
			else
			{
				m_dEvmPeak=CStr::StrToFloat(itrFind->second);
			}

			strtemp.Empty();
			strVtrtemp.clear();
			itrFind=pcSettingMap->find(_T("EVM95P"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_FATAL,_T("Not Find EVM95P"));
				return false;
			}
			else
			{
				strtemp=itrFind->second;
				CStr::ParseString(strtemp,_T(","),strVtrtemp);
				CStr::StrVtr2DblVtr(m_dVtrEvm95P,strVtrtemp);
			}

			strtemp.Empty();
			strVtrtemp.clear();
			itrFind=pcSettingMap->find(_T("ORGNOFS"));
			if(itrFind==pcSettingMap->end())
			{
				LogTrace(MSG_FATAL,_T("Not Find ORGNOFS"));
				return false;
			}
			else
			{
				strtemp=itrFind->second;
				CStr::ParseString(strtemp,_T(","),strVtrtemp);
				CStr::StrVtr2DblVtr(m_dVtrORGNOFS,strVtrtemp);
			}
		}
	}
	else
	{
		LogTrace(MSG_FATAL,_T("Pls set UseFollowPara to 1; no Default Value now")); 
		return false;
	}


	   
		 itrFind=pcSettingMap->find(_T("FailRunList"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_WARNING,_T("Not Find FailRunList,default is """));
			 m_strFailRunList="";
		 }
		 else
		 {
			 m_strFailRunList=itrFind->second;
	
		 }

		  itrFind=pcSettingMap->find(_T("IsRandomChannel"));
		 if(itrFind==pcSettingMap->end())
		 {
			 LogTrace(MSG_WARNING,_T("Not Find IsRandomChannel,default is false"));
			 m_bIsRandomCH=false;
		 }
		 else
		 {
			 m_bIsRandomCH=CStr::StrToBool(itrFind->second);
	
		 }

		if(m_bIsRandomCH)
		{
		     srand(GetTickCount()%3); 
		     int iRandCh=m_iTestChan[rand()];
			 m_iTestChan.clear();
			 m_iTestChan.push_back(iRandCh);

		 }




	InitData();
	return true;
 }

 bool CGSM_EDGE_NSFT_MeasLoop::InitData()
 {
	 m_pFunGSMTestDev=m_piTesterDevice->m_piFuncGSMTest;
	 m_bIsStopWhileFail=m_bIsStopWhenFail;
	 m_iFailFlag=0;
	 return true;
 }

 bool CGSM_EDGE_NSFT_MeasLoop::StartTxMeasurment(CString strTestItem)
 {//TestItem_TX AVG_TXPWR-A;MAX_PPHASEERR-B;AVG_PHASEERR-C;AVG_CARRFERR-D;AVG_PWRTEMP-E;ORFSSW_JUDGE-F;AVG_SWPWR-G;ORFSMD_JUDGE-H;AVG_MODPWR-I;
	 int iErrorcode;

	 if((iErrorcode=m_pFunGSMTestDev->IGSMTestStartTxMeasurment(10,1,m_strVtrResultTX,strTestItem,m_IsEdge)!=DEVICE_SUCCESS))
	 {
		 LogTrace(MSG_ERROR,_T("GSM Test StartTxMeasurment Test Fail!"))
			 m_iErrorcode=iErrorcode;
		 m_iFailFlag++;
		 return false;
	 }

	 return true;
 }


 bool CGSM_EDGE_NSFT_MeasLoop::CheckTXResult(int nIndex,CString strPcl,CString strChan,CString strTestItem)
 {
	 CString strReservedTemp;//for .2f use
	 double  dReservedTemp;//for .2f use
	 int nTestSeq=0;
	 if (strTestItem.Find("A1")!=-1)
	 {
		 m_iItemCode+='A';
		 CRangePair<double> PowerSpec;
		 PowerSpec.SetRange(m_dVtrPwrMax[nIndex],m_dVtrPwrMin[nIndex]);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
	 	 if (PowerSpec.InRange(dReservedTemp))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,CStr::FloatToStr(PowerSpec.GetMax()),CStr::FloatToStr(PowerSpec.GetMin()),strReservedTemp,"dBm","Power Pass","Power");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,CStr::FloatToStr(PowerSpec.GetMax()),CStr::FloatToStr(PowerSpec.GetMin()),strReservedTemp,"dBm","Power Fail","Power");
			 
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='A';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("B1")!=-1)
	 {
		 m_iItemCode+='B';
		 CRangePair<double> PhasePeakSpec;
		 PhasePeakSpec.SetRange(m_dPhaseErrMax,-m_dPhaseErrMax);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
		 if (PhasePeakSpec.InRange(dReservedTemp))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,CStr::FloatToStr(PhasePeakSpec.GetMax()),CStr::FloatToStr(PhasePeakSpec.GetMin()),strReservedTemp,"_","PhaseErrMax Pass","PER_Peak");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,CStr::FloatToStr(PhasePeakSpec.GetMax()),CStr::FloatToStr(PhasePeakSpec.GetMin()),strReservedTemp,"_","PhaseErrMax Fail","PER_Peak");
			 
			 m_iFailFlag++;
		 		 if (m_bIsStopWhileFail)
		 		 {
		 			 return false;
		 		 }
		 }
		 m_iItemCode-='B';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("C1")!=-1)
	 {
		 m_iItemCode+='C';
		 CRangePair<double> PhaseErrAvgSpec;
		 PhaseErrAvgSpec.SetRange(m_dPhaseErrAvg,0);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
		 if (PhaseErrAvgSpec.InRange(dReservedTemp))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,CStr::FloatToStr(PhaseErrAvgSpec.GetMax()),CStr::FloatToStr(PhaseErrAvgSpec.GetMin()),strReservedTemp,"_","PhaseErrAvg Pass","PER_Avg");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,CStr::FloatToStr(PhaseErrAvgSpec.GetMax()),CStr::FloatToStr(PhaseErrAvgSpec.GetMin()),strReservedTemp,"_","PhaseErrAvg Fail","PER_Avg");
			 m_iFailFlag++;

		 		 if (m_bIsStopWhileFail)
		 		 {
		 			 return false;
		 		 }
		 }
		 m_iItemCode-='C';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("D1")!=-1)
	 {
		 m_iItemCode+='D';
		 CRangePair<double> FreqErrSpec;
		 FreqErrSpec.SetRange(m_dFreqErr,-m_dFreqErr);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
		 if (FreqErrSpec.InRange(dReservedTemp))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,CStr::FloatToStr(FreqErrSpec.GetMax()),CStr::FloatToStr(FreqErrSpec.GetMin()),strReservedTemp,"_","FreqErr Pass","FER");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,CStr::FloatToStr(FreqErrSpec.GetMax()),CStr::FloatToStr(FreqErrSpec.GetMin()),strReservedTemp,"_","FreqErr Fail","FER");
			 m_iFailFlag++;
		 		 if (m_bIsStopWhileFail)
		 		 {
		 			 return false;
		 		 }
		 }
		 m_iItemCode-='D';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("E1")!=-1)
	 {
		 m_iItemCode+='E';
		 if ((!strncmp(m_strVtrResultTX[nTestSeq],"PASS",4))||(CStr::StrToFloat(m_strVtrResultTX[nTestSeq])==0))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,"_","_","1","_","PVT Pass","PVT");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,"_","_","0","_","PVT Fail","PVT");
			 m_iFailFlag++;

		 		 if (m_bIsStopWhileFail)
		 		 {
		 			 return false;
		 		 }
		 }
		 m_iItemCode-='E';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("F1")!=-1)
	 {
		 m_iItemCode+='F';
		 if ((!strncmp(m_strVtrResultTX[nTestSeq],"PASS",4))||(CStr::StrToFloat(m_strVtrResultTX[nTestSeq])==0))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,"_","_","1","_","ORFS_Swi Pass","ORFS_Swi");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,"_","_","0","_","ORFS_Swi Fail","ORFS_Swi");
			 m_iFailFlag++;

		 		 if (m_bIsStopWhileFail)
		 		 {
		 			 return false;
		 		 }
		 }
		 m_iItemCode-='F';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("G1")!=-1)
	 {
		 m_iItemCode+='G';
		 CStringVtr strVtrtemp;
		 DblVtr		dResult;
		 CStr::ParseString(m_strVtrResultTX[nTestSeq],_T(","),strVtrtemp);
		 CStr::StrVtr2DblVtr(dResult,strVtrtemp);

		 for (int i=0;i<8;i++)
		 {
			 CRangePair<double> SwiSpec;
			 if (CStr::StrToInt(strPcl)<7)
			 {
				 SwiSpec.SetRange(m_dVtrSwiHighPcl[i],-999);
			 }
			 else
				 SwiSpec.SetRange(m_dVtrSwiLowPcl[i],-999);
			
			 CString strtempSwi;
			 if (i<m_iVtrSwiHz.size()/2)
			 {
				strtempSwi.Format("Swi_N%d",m_iVtrSwiHz[i]);
			 }
			 else
			 {
				strtempSwi.Format("Swi_P%d",m_iVtrSwiHz[i]);
			 }


			 if (SwiSpec.InRange(dResult[i]))
			 {
				 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,CStr::FloatToStr(SwiSpec.GetMax()),CStr::FloatToStr(SwiSpec.GetMin()),CStr::FloatToStr(dResult[i]),"_",strtempSwi+" Pass",strtempSwi);
			 }
			 else
			 {
				 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,CStr::FloatToStr(SwiSpec.GetMax()),CStr::FloatToStr(SwiSpec.GetMin()),CStr::FloatToStr(dResult[i]),"_",strtempSwi+" Fail",strtempSwi);
				 m_iFailFlag++;

			 		 if (m_bIsStopWhileFail)
			 		 {
			 			 return false;
			 		 }
			 }
		 }
		 m_iItemCode-='G';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("H1")!=-1)
	 {
		 m_iItemCode+='H';
		 if ((!strncmp(m_strVtrResultTX[nTestSeq],"PASS",4))||(CStr::StrToFloat(m_strVtrResultTX[nTestSeq])==0))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,"_","_","1","_","ORFS_Mod Pass","ORFS_Mod");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,"_","_","0","_","ORFS_Mod Fail","ORFS_Mod");
			 m_iFailFlag++;

		 		 if (m_bIsStopWhileFail)
		 		 {
		 			 return false;
		 		 }
		 }
		 m_iItemCode-='H';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("I1")!=-1)
	 {
		 m_iItemCode+='I';
		 CStringVtr strVtrtemp;
		 DblVtr		dResult;
		 CStr::ParseString(m_strVtrResultTX[nTestSeq],_T(","),strVtrtemp);
		 CStr::StrVtr2DblVtr(dResult,strVtrtemp);

		 for (int i=0;i<12;i++)
		 {
			 CRangePair<double> SwiSpec;
			 if (CStr::StrToInt(strPcl)<7)
			 {
				 SwiSpec.SetRange(m_dVtrModHighPcl[i],-999);
			 }
			 else
				 SwiSpec.SetRange(m_dVtrModLowPcl[i],-999);

			 CString strtempMod;
			 if (i<m_iVtrModHz.size()/2)
			 {
				 strtempMod.Format("Mod_N%d",m_iVtrModHz[i]);
			 }
			 else
			 {
				 strtempMod.Format("Mod_P%d",m_iVtrModHz[i]);
			 }

			 if (SwiSpec.InRange(dResult[i]))
			 {
				 TestPassLogEx(m_strCurrBand,strChan+'-'+strPcl,CStr::FloatToStr(SwiSpec.GetMax()),CStr::FloatToStr(SwiSpec.GetMin()),CStr::FloatToStr(dResult[i]),"_",strtempMod+" Pass",strtempMod);
			 }
			 else
			 {
				 TestFailLogEx(m_strCurrBand,strChan+'-'+strPcl,nIndex,CStr::FloatToStr(SwiSpec.GetMax()),CStr::FloatToStr(SwiSpec.GetMin()),CStr::FloatToStr(dResult[i]),"_",strtempMod+" Fail",strtempMod);
				 m_iFailFlag++;

			 		 if (m_bIsStopWhileFail)
			 		 {
			 			 return false;
			 		 }
			 }
		 }
		 m_iItemCode-='I';

		 nTestSeq++;
	 }
 
	 return true;
 }

 bool CGSM_EDGE_NSFT_MeasLoop::StartRxLevelMeasurment(CString strTestItem)
 {
	 int iErrorcode;

	 if((iErrorcode=m_pFunGSMTestDev->IGSMTestStartRxLevelMeasurment(-80.5)!=DEVICE_SUCCESS))
	 {
		 LogTrace(MSG_ERROR,_T("GSM Rx Level Measurement Fail!"))
			 m_iErrorcode=iErrorcode;
		 m_iFailFlag++;
		 return false;
	 }

	 return true;
 }

 bool CGSM_EDGE_NSFT_MeasLoop::StartRxBerMeasurment(CString strTestItem)
 {
	 int iErrorcode;

	 if((iErrorcode=m_pFunGSMTestDev->IGSMTestStartRxBerMeasurment(10000,m_iRxlevel,m_dRxSEBR,strTestItem)!=DEVICE_SUCCESS))
	 {
		 LogTrace(MSG_ERROR,_T("GSM Rx BER Measurement Fail!"))
			 m_iErrorcode=iErrorcode;
		 m_iFailFlag++;
		 return false;
	 }

	 return true;
 }

 bool CGSM_EDGE_NSFT_MeasLoop::CheckRXLevelResult(int nIndex,CString strBand,CString strChan,CString strTestItem)
 {
	 int iErrorcode;
	int iRxLevel=0;
	 if (strTestItem.Find("R1")!=-1)
	 {
		 m_iItemCode+='R';
		 if((iErrorcode=m_pPhone->FTM_GSM_BER_GetRxMetrics(iRxLevel,50)!=PHONE_SUCCESS))
		 {           
			 LogTrace(MSG_ERROR,_T("FTM_GSM_BER_GetRxMetrics Fail!"))
				 m_iErrorcode=iErrorcode;
			 m_iFailFlag++;
			 CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_GSM_BER_GetRxMetrics Fail!");
			 return false;
		 }

		 CRangePair<double> RxLevelSpec;
		 RxLevelSpec.SetRange(m_dVtrRxLevel[0],m_dVtrRxLevel[1]);
		 if (RxLevelSpec.InRange(iRxLevel))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(RxLevelSpec.GetMax()),CStr::FloatToStr(RxLevelSpec.GetMin()),CStr::FloatToStr(iRxLevel),"_","RxLevel Pass","RxLevel");
		 }
		 else
		 {		 
			 if((iErrorcode=m_pPhone->FTM_GSM_BER_GetRxMetrics(iRxLevel,50)!=PHONE_SUCCESS))
			 {           
				 LogTrace(MSG_ERROR,_T("FTM_GSM_BER_GetRxMetrics Fail!"))
					 m_iErrorcode=iErrorcode;
				 m_iFailFlag++;
				 CalFailLog(_T("_"),_T("_"),iErrorcode,"FTM_GSM_BER_GetRxMetrics Fail!");
				 return false;
			 }

			 if (RxLevelSpec.InRange(iRxLevel))
			 {
				 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(RxLevelSpec.GetMax()),CStr::FloatToStr(RxLevelSpec.GetMin()),CStr::FloatToStr(iRxLevel),"_","RxLevel Pass","RxLevel");
			 }
			 else
			 {
				TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(RxLevelSpec.GetMax()),CStr::FloatToStr(RxLevelSpec.GetMin()),CStr::FloatToStr(iRxLevel),"_","RxLevel Fail","RxLevel");
				m_iFailFlag++;
		 		 if (m_bIsStopWhileFail)
		 		 {
		 			 return false;
		 		 }
			 }
		 }
		 m_iItemCode-='R';
	 }
	 
	 return true;
 }

 bool CGSM_EDGE_NSFT_MeasLoop::CheckRXBerResult(int nIndex,CString strBand,CString strChan,CString strTestItem)
 {
//	 int iErrorcode;

	 if (strTestItem.Find("X1")!=-1)
	 {
		 m_iItemCode+='X';
		 CRangePair<double> RxBerSpec;
		 RxBerSpec.SetRange(m_dVtrRxBer[0],m_dVtrRxBer[1]);
		 if (RxBerSpec.InRange(m_dRxSEBR/100))
		 {
		 	TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(RxBerSpec.GetMax()*100),CStr::FloatToStr(RxBerSpec.GetMin()*100),CStr::FloatToStr(m_dRxSEBR),"_","RxBer Pass","RxBer");
		 }
		 else
		 {
			TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(RxBerSpec.GetMax()*100),CStr::FloatToStr(RxBerSpec.GetMin()*100),CStr::FloatToStr(m_dRxSEBR),"_","RxBer Fail","RxBer");
			 m_iFailFlag++;
			if (m_bIsStopWhileFail)
			{
				 return false;
			}
		 }
		 m_iItemCode-='X';
	 }



	 return true;
 }

 bool CGSM_EDGE_NSFT_MeasLoop::CheckTXResultEdge(int nIndex,CString strBand,CString strChan,CString strTestItem)
 {
	 int nTestSeq=0;
	 CString strReservedTemp;//for .2f use
	 double  dReservedTemp;//for .2f use

	 if (strTestItem.Find("A1")!=-1)
	 {
		 m_iItemCode+='A';
		 CRangePair<double> PowerSpec;
		 PowerSpec.SetRange(m_dVtrPwrMax[nIndex],m_dVtrPwrMin[nIndex]);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
		 if (PowerSpec.InRange(dReservedTemp))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(PowerSpec.GetMax()),CStr::FloatToStr(PowerSpec.GetMin()),strReservedTemp,"dBm","Power Pass","Power");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(PowerSpec.GetMax()),CStr::FloatToStr(PowerSpec.GetMin()),strReservedTemp,"dBm","Power Fail","Power");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='A';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("B1")!=-1)
	 {
		 m_iItemCode+='B';
		 CRangePair<double> EvmPeakSpec;
		 EvmPeakSpec.SetRange(m_dEvmPeak,-m_dEvmPeak);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
		 if (EvmPeakSpec.InRange(dReservedTemp))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(EvmPeakSpec.GetMax()),CStr::FloatToStr(EvmPeakSpec.GetMin()),strReservedTemp,"_","EvmPeak Pass","EvmPeak");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(EvmPeakSpec.GetMax()),CStr::FloatToStr(EvmPeakSpec.GetMin()),strReservedTemp,"_","EvmPeak Fail","EvmPeak");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='B';

		 nTestSeq++;
	 }


	 if (strTestItem.Find("C1")!=-1)
	 {
		 m_iItemCode+='C';
		 CRangePair<double> EvmRMSSpec;
		 EvmRMSSpec.SetRange(m_dEvmRms,0);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
		 if (EvmRMSSpec.InRange(dReservedTemp))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(EvmRMSSpec.GetMax()),CStr::FloatToStr(EvmRMSSpec.GetMin()),strReservedTemp,"_","EvmRMS Pass","EvmRMS");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(EvmRMSSpec.GetMax()),CStr::FloatToStr(EvmRMSSpec.GetMin()),strReservedTemp,"_","EvmRMS Fail","EvmRMS");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='C';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("D1")!=-1)
	 {
		 m_iItemCode+='D';
		 CRangePair<double> Evm95PctSpec;
		 Evm95PctSpec.SetRange(m_dVtrEvm95P[0],m_dVtrEvm95P[1]);

		 dReservedTemp=CStr::StrToFloat(m_strVtrResultTX[nTestSeq]);
		 strReservedTemp.Format("%.2f",dReservedTemp);
		 if (Evm95PctSpec.InRange(dReservedTemp))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(Evm95PctSpec.GetMax()),CStr::FloatToStr(Evm95PctSpec.GetMin()),strReservedTemp,"_","Evm95P Pass","Evm95P");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(Evm95PctSpec.GetMax()),CStr::FloatToStr(Evm95PctSpec.GetMin()),strReservedTemp,"_","Evm95P Fail","Evm95P");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='D';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("E1")!=-1)
	 {
		 m_iItemCode+='E';
		 CRangePair<double> ORGNOFSSpec;
		 ORGNOFSSpec.SetRange(m_dVtrORGNOFS[0],m_dVtrORGNOFS[1]);

		 if (ORGNOFSSpec.InRange(CStr::StrToFloat(m_strVtrResultTX[nTestSeq])))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(ORGNOFSSpec.GetMax()),CStr::FloatToStr(ORGNOFSSpec.GetMin()),m_strVtrResultTX[nTestSeq],"_","ORGNOFS Pass","OrigOFS");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(ORGNOFSSpec.GetMax()),CStr::FloatToStr(ORGNOFSSpec.GetMin()),m_strVtrResultTX[nTestSeq],"_","ORGNOFS Fail","OrigOFS");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='E';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("F1")!=-1)
	 {
		 m_iItemCode+='F';
		 CRangePair<double> FreqErrSpec;
		 FreqErrSpec.SetRange(m_dFreqErr,-m_dFreqErr);

		 if (FreqErrSpec.InRange(CStr::StrToFloat(m_strVtrResultTX[nTestSeq])))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(FreqErrSpec.GetMax()),CStr::FloatToStr(FreqErrSpec.GetMin()),m_strVtrResultTX[nTestSeq],"_","FreqErr Pass","FER");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(FreqErrSpec.GetMax()),CStr::FloatToStr(FreqErrSpec.GetMin()),m_strVtrResultTX[nTestSeq],"_","FreqErr Fail","FER");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='F';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("G1")!=-1)
	 {
		 m_iItemCode+='G';
		 if ((!strncmp(m_strVtrResultTX[nTestSeq],"PASS",4))||(CStr::StrToFloat(m_strVtrResultTX[nTestSeq])==0))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,"_","_","1","_","PVT Pass","PVT");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,"_","_","0","_","PVT Fail","PVT");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='G';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("H1")!=-1)
	 {
		 m_iItemCode+='H';
		 if ((!strncmp(m_strVtrResultTX[nTestSeq],"PASS",4))||(CStr::StrToFloat(m_strVtrResultTX[nTestSeq])==0))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,"_","_","1","_","ORFS_Swi Pass","ORFS_Swi");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,"_","_","0","_","ORFS_Swi Fail","ORFS_Swi");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='H';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("I1")!=-1)
	 {
		 m_iItemCode+='I';
		 CStringVtr strVtrtemp;
		 DblVtr		dResult;
		 CStr::ParseString(m_strVtrResultTX[nTestSeq],_T(","),strVtrtemp);
		 CStr::StrVtr2DblVtr(dResult,strVtrtemp);

		 for (int i=0;i<8;i++)
		 {
			 CRangePair<double> SwiSpec;
			 if (CStr::StrToInt(strBand)<7)
			 {
				 SwiSpec.SetRange(m_dVtrSwiHighPcl[i],-999);
			 }
			 else
				 SwiSpec.SetRange(m_dVtrSwiLowPcl[i],-999);

			 CString strtempSwi;
			 if (i<m_iVtrSwiHz.size()/2)
			 {
				 strtempSwi.Format("Swi_N%d",m_iVtrSwiHz[i]);
			 }
			 else
			 {
				 strtempSwi.Format("Swi_P%d",m_iVtrSwiHz[i]);
			 }

			 if (SwiSpec.InRange(dResult[i]))
			 {
				 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(SwiSpec.GetMax()),CStr::FloatToStr(SwiSpec.GetMin()),CStr::FloatToStr(dResult[i]),"_",strtempSwi+" Pass",strtempSwi);
			 }
			 else
			 {
				 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(SwiSpec.GetMax()),CStr::FloatToStr(SwiSpec.GetMin()),CStr::FloatToStr(dResult[i]),"_",strtempSwi+" Fail",strtempSwi);
				 m_iFailFlag++;
				 if (m_bIsStopWhileFail)
				 {
					 return false;
				 }
			 }
		 }
		 m_iItemCode-='I';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("J1")!=-1)
	 {
		 m_iItemCode+='J';
		 if ((!strncmp(m_strVtrResultTX[nTestSeq],"PASS",4))||(CStr::StrToFloat(m_strVtrResultTX[nTestSeq])==0))
		 {
			 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,"_","_","1","_","ORFS_Mod Pass","ORFS_Mod");
		 }
		 else
		 {
			 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,"_","_","0","_","ORFS_Mod Fail","ORFS_Mod");
			 m_iFailFlag++;
			 if (m_bIsStopWhileFail)
			 {
				 return false;
			 }
		 }
		 m_iItemCode-='J';

		 nTestSeq++;
	 }

	 if (strTestItem.Find("K1")!=-1)
	 {
		 m_iItemCode+='K';
		 CStringVtr strVtrtemp;
		 DblVtr		dResult;
		 CStr::ParseString(m_strVtrResultTX[nTestSeq],_T(","),strVtrtemp);
		 CStr::StrVtr2DblVtr(dResult,strVtrtemp);

		 for (int i=0;i<8;i++)
		 {
			 CRangePair<double> SwiSpec;
			 if (CStr::StrToInt(strBand)<7)
			 {
				 SwiSpec.SetRange(m_dVtrModHighPcl[i],-999);
			 }
			 else
				 SwiSpec.SetRange(m_dVtrModLowPcl[i],-999);

			 CString strtempMod;
			 if (i<m_iVtrSwiHz.size()/2)
			 {
				 strtempMod.Format("Mod_N%d",m_iVtrModHz[i]);
			 }
			 else
			 {
				 strtempMod.Format("Mod_P%d",m_iVtrModHz[i]);
			 }

			 if (SwiSpec.InRange(dResult[i]))
			 {
				 TestPassLogEx(m_strCurrBand,strChan+'-'+strBand,CStr::FloatToStr(SwiSpec.GetMax()),CStr::FloatToStr(SwiSpec.GetMin()),CStr::FloatToStr(dResult[i]),"_",strtempMod+" Pass",strtempMod);
			 }
			 else
			 {
				 TestFailLogEx(m_strCurrBand,strChan+'-'+strBand,nIndex,CStr::FloatToStr(SwiSpec.GetMax()),CStr::FloatToStr(SwiSpec.GetMin()),CStr::FloatToStr(dResult[i]),"_",strtempMod+" Fail",strtempMod);
				 m_iFailFlag++;
				 if (m_bIsStopWhileFail)
				 {
					 return false;
				 }
			 }
		 }
		 m_iItemCode-='K';

		 nTestSeq++;
	 }

	 return true;
 }

 bool CGSM_EDGE_NSFT_MeasLoop::SetGSMTestLOSS()
 {
	 CString strMsg;
	 double dLoss;
	 m_vCableLoss.clear();
	 for(int i=0;i<3;i++)
	 {
		 if(!m_LossFinder.GetGSMLoss(m_strCurrBand,i,dLoss))
		 {
			 strMsg.Format("GSM Get Loss Band=%s ,ChannelType=%d Fail",m_strCurrBand,i);
			 LogTrace(MSG_ERROR,strMsg);
			 CalFailLog(_T("_"),_T("_"),1001,strMsg);
			 m_iFailFlag++;
			 return false;
		 }
		 m_vCableLoss.push_back(dLoss);
	 }



	 if(DEVICE_SUCCESS!=m_pFunGSMTestDev->IGSMTestSetLoss(m_iCurrBand,m_vCableLoss))
	 {
		 LogTrace(MSG_ERROR,"Set Cableloss device fail");
		 CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		 m_iFailFlag++;
		 return false;

	 }

	 return  true;

 }


 int CGSM_EDGE_NSFT_MeasLoop::GetItemCode(int nMode,int Band,int Channel,int PowerLevel)
 {
	 int nItemCode=400000;
	 nItemCode+=nMode*100000;

	 switch(Band)
	 {
	 case GSM_850_BAND_ID:
			  nItemCode+=1*10000;

		 break;
	 case GSM_EGSM_BAND_ID:
			  nItemCode+=2*10000;
		 break;
	 case GSM_DCS_BAND_ID:
			  nItemCode+=3*10000;
		 break;
	 case GSM_PCS_BAND_ID:
			  nItemCode+=4*10000;
		 break;
	 default:
		 return -1;
	 }

	 nItemCode+=CGSMBandInfo::GetChannelType(Band,Channel)*1000;

	 nItemCode+=CGSMBandInfo::GetPclType(Band,PowerLevel)*100;

	 return nItemCode;
 }
