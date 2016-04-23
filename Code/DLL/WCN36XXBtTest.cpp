#include "StdAfx.h"
#include "WCN36XXBtTest.h"
RF_IMPLEMENT_DYNCREATE(CWCN36XXBtTest)
CWCN36XXBtTest::CWCN36XXBtTest(void)
{
	m_mapClassFunc[_T("BTTestMainFunc")]=&CWCN36XXBtTest::BTTestMainFunc;
	m_mapClassFunc[_T("Handover")]=&CWCN36XXBtTest::Handover;
	m_mapClassFunc[_T("TxOutputPower")]=&CWCN36XXBtTest::TxOutputPower;
	m_mapClassFunc[_T("GFSKMod")]=&CWCN36XXBtTest::GFSKMod;
	m_mapClassFunc[_T("CarrierFreqDrift")]=&CWCN36XXBtTest::CarrierFreqDrift;
	m_mapClassFunc[_T("ICFT")]=&CWCN36XXBtTest::ICFT;
	m_mapClassFunc[_T("EDRMod")]=&CWCN36XXBtTest::EDRMod;
	m_mapClassFunc[_T("RxBer")]=&CWCN36XXBtTest::RxBer;
	m_iItemCode=1001;
}

CWCN36XXBtTest::~CWCN36XXBtTest(void)
{
}
bool CWCN36XXBtTest::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}
bool CWCN36XXBtTest::Handle()
{
	if(!DoProcess())
	{
		BTRelease(); 
		return false;
	}
	BTRelease();
	return true;
}
bool CWCN36XXBtTest::InitData(
						   PCStringStrMap     pcSettingMap,
						   CRFObjectMap&   cObjectMap
						   ) 
{

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
	itrFind=pcSettingMap->find(_T("WaveFile"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'WaveFile' from ini file!default ''");
		m_strWaveFile="D:\\Rohde-Schwarz\\CMW\\Data\\waveform\\BT_DH1_BD359CBD359C.wv";

	}
	else
	{
		m_strWaveFile=itrFind->second;		
	}

	itrFind=pcSettingMap->find(_T("BTAddr"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'BTAddr' from ini file!default ''");
		m_strBTAddr="BD359CBD359C";
		aBTAddr[0]=0xBD;
		aBTAddr[1]=0x35;
		aBTAddr[2]=0x9C;
		aBTAddr[3]=0xBD;
		aBTAddr[4]=0x35;
		aBTAddr[5]=0x9C;

	}
	else
	{
		m_strBTAddr=itrFind->second;	
		aBTAddr[0]=0xBD;
		aBTAddr[1]=0x35;
		aBTAddr[2]=0x9C;
		aBTAddr[3]=0xBD;
		aBTAddr[4]=0x35;
		aBTAddr[5]=0x9C;
	}

	itrFind=pcSettingMap->find(_T("Channel"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'Channel' from ini file!");
		return false;

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivChannel,strVtr);

	}

	itrFind=pcSettingMap->find(_T("RxCellPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'RxCellPower' from ini file!default -70");
		m_dRxCellPower=-70;

	}
	else
	{
		strValue=itrFind->second;
		m_dRxCellPower=CStr::StrToFloat(strValue);
	}
	itrFind=pcSettingMap->find(_T("BTLoss"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'BTLoss' from ini file!default 1.5db");
		m_dLoss=1.5;

	}
	else
	{
		strValue=itrFind->second;
		m_dLoss=CStr::StrToFloat(strValue);
	}
	itrFind=pcSettingMap->find(_T("PowerSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'PowerSpec' from ini file!Use default 6-15");
		m_PowerSpec.SetRange(6,15);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_PowerSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("DeltaF1Spec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'DeltaF1Spec' from ini file!Use default 140-175");
		m_DeltaF1Spec.SetRange(140,175);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_DeltaF1Spec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("m_DeltaF2Spec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'm_DeltaF2Spec' from ini file!Use default 115-300");
		m_DeltaF2Spec.SetRange(115,300);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_DeltaF2Spec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("CFDSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'CFDSpec' from ini file!Use default -40:40");
		m_CFDSpec.SetRange(-40,40);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_CFDSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("ICFTSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'ICFTSpec' from ini file!Use default -75:75");
		m_ICFTSpec.SetRange(-75,75);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_ICFTSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("RMSDEVMSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'RMSDEVMSpec' from ini file!Use default 0:0.13");
		m_RMSDEVMSpec.SetRange(0,0.13);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_RMSDEVMSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("PeakDEVMSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'PeakDEVMSpec' from ini file!Use default 0:0.25");
		m_PeakDEVMSpec.SetRange(0,0.25);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_PeakDEVMSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("BerSpec"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'BerSpec' from ini file!Use default 0:0.1");
		m_BerSpec.SetRange(0,0.1);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_BerSpec.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}




	InitData();
	return true;
}
bool CWCN36XXBtTest::InitData()
{
	m_pFunBTTestDev=m_piTesterDevice->m_piFuncBTTest;
	return true;
}
bool CWCN36XXBtTest::BTTestMainFunc()
{
	if (!this->BTInit())
	{
		return false;
	}
	
	for (int i=0;i<m_ivChannel.size();i++)
	{
		m_iCurrChannel=m_ivChannel[i];
		for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

		{
			int iRetry=0;			

			FPClassFunc fpTestFunc=*itrFP;
			for (;;)
			{
				if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
				{
				
				}
				else
				{
					break;
				}
				if (iRetry++>1)
				{
					return false;
				}
			}


		}

	}

	return true;
}

bool CWCN36XXBtTest::Handover()
{
	int iErrorcode,iFailFlag=0;
	
	if((iErrorcode=m_pFunBTTestDev->IBTTestSetChannel(m_iCurrChannel))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device HandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device HandOver Fail!"))
			return false;
	}
	return true;
}
bool CWCN36XXBtTest::BTInit()
{
	int iErrorcode;

	if((iErrorcode=m_pFunBTTestDev->IBTTestInitEx(m_strDeviceAddr,m_strWaveFile,m_strBTAddr))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device Init Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Test Device Init Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunBTTestDev->IBTTestSetLoss(m_dLoss))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device SetLoss Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Test Device SetLoss Fail!"))
			return false;
	}
	if((iErrorcode=m_pFunBTTestDev->IBTTestSetInOutPort(1,1))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device SetInOutPort Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Test Device SetInOutPort Fail!"))
			return false;
	}
	LogTrace(MSG_MID,"Init TestDevice BT Pass");
	if((iErrorcode=m_pPhone->BTTestAdbInit())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone BTTestAdbInit Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Phone BTTestAdbInit Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->BTTestFTMInit())!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone BTTestFTMInit Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Phone BTTestFTMInit Fail!"))
			return false;
	}
	CalPassLog(_T("BT"),_T("-"),_T("BT Init PASS"))
	return true;


}
bool CWCN36XXBtTest::TxOutputPower()
{
	int iErrorcode,iFailFlag=0;
	double dPower=0;
	if((iErrorcode=m_pPhone->BTTestTxBurst(m_iCurrChannel,PSEUDO_RANDOM,BT_DH5,0,9,aBTAddr,0))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone BTTestTxBurst Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Phone BTTestTxBurst Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunBTTestDev->IBTTestPowerMeas(12,10,1,5,&dPower))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IBTTestPowerMeas Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device IBTTestPowerMeas Fail!"))
			return false;
	}
	if (m_PowerSpec.InRange(dPower))
	{
		TestPassLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_PowerSpec.GetMax())),_T(CStr::FloatToStr(m_PowerSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dBm"),_T("TxPower PASS"),"TxPower")

	} 
	else
	{
		TestFailLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_PowerSpec.GetMax())),_T(CStr::FloatToStr(m_PowerSpec.GetMin())),_T(CStr::FloatToStr(dPower)),_T("dBm"),_T("TxPower FAIL"),"TxPower")
		return false;
	}
	return true;

}

bool CWCN36XXBtTest::GFSKMod()
{
	int iErrorcode,iFailFlag=0;
	double dDeltaF1=0,dDeltaF2=0;
	

	if((iErrorcode=m_pPhone->BTTestTxBurst(m_iCurrChannel,ALTERNATING_NIBBLE,BT_DH5,0,6,aBTAddr,0))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone BTTestTxBurst Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Phone BTTestTxBurst Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunBTTestDev->IBTTestModMeas(12,10,1,&dDeltaF1))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IBTTestModMeas Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device IBTTestModMeas Fail!"))
			return false;
	}
	if (m_DeltaF1Spec.InRange(dDeltaF1))
	{
		TestPassLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_DeltaF1Spec.GetMax())),_T(CStr::FloatToStr(m_DeltaF1Spec.GetMin())),_T(CStr::FloatToStr(dDeltaF1)),_T("kHz"),_T("GFSK Mod DeltaF1 PASS"),"GFSK Mod DeltaF1")

	} 
	else
	{
		TestFailLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_DeltaF1Spec.GetMax())),_T(CStr::FloatToStr(m_DeltaF1Spec.GetMin())),_T(CStr::FloatToStr(dDeltaF1)),_T("kHz"),_T("GFSK Mod DeltaF1 FAIL"),"GFSK Mod DeltaF1")
		iFailFlag++;
	}

	if((iErrorcode=m_pPhone->BTTestTxBurst(m_iCurrChannel,ALTERNATING_BIT,BT_DH5,0,6,aBTAddr,0))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone BTTestTxBurst Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Phone BTTestTxBurst Fail!"))
			return false;
	}
	Sleep(300);

	if((iErrorcode=m_pFunBTTestDev->IBTTestModMeas(12,10,2,&dDeltaF2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IBTTestModMeas Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device IBTTestModMeas Fail!"))
			return false;
	}
	if (m_DeltaF2Spec.InRange(dDeltaF2))
	{
		TestPassLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_DeltaF2Spec.GetMax())),_T(CStr::FloatToStr(m_DeltaF2Spec.GetMin())),_T(CStr::FloatToStr(dDeltaF2)),_T("kHz"),_T("GFSK Mod DeltaF2 PASS"),"GFSK Mod DeltaF2")

	} 
	else
	{
		TestFailLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_DeltaF2Spec.GetMax())),_T(CStr::FloatToStr(m_DeltaF2Spec.GetMin())),_T(CStr::FloatToStr(dDeltaF2)),_T("kHz"),_T("GFSK Mod DeltaF2 FAIL"),"GFSK Mod DeltaF2")
		iFailFlag++;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;
}
bool CWCN36XXBtTest::CarrierFreqDrift()
{
	int iErrorcode,iFailFlag=0;
	double dDeltaF1=0;


	if((iErrorcode=m_pPhone->BTTestTxBurst(m_iCurrChannel,ALTERNATING_BIT,BT_DH5,0,9,aBTAddr,0))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone BTTestTxBurst Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Phone BTTestTxBurst Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunBTTestDev->IBTTestCFDMeas(12,10,&dDeltaF1))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IBTTestModMeas Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device IBTTestModMeas Fail!"))
			return false;
	}
	if (m_CFDSpec.InRange(dDeltaF1))
	{
		TestPassLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_CFDSpec.GetMax())),_T(CStr::FloatToStr(m_CFDSpec.GetMin())),_T(CStr::FloatToStr(dDeltaF1)),_T("kHz"),_T("carrier freq drift PASS"),"CFD")

	} 
	else
	{
		TestFailLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_CFDSpec.GetMax())),_T(CStr::FloatToStr(m_CFDSpec.GetMin())),_T(CStr::FloatToStr(dDeltaF1)),_T("kHz"),_T("carrier freq drift FAIL"),"CFD")
			return false;
	}
	return true;

}
bool CWCN36XXBtTest::ICFT()
{
	int iErrorcode,iFailFlag=0;
	double dICFTkHz=0;


	if((iErrorcode=m_pPhone->BTTestTxBurst(m_iCurrChannel,PSEUDO_RANDOM,BT_DH1,0,9,aBTAddr,0))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone BTTestTxBurst Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Phone BTTestTxBurst Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunBTTestDev->IBTTestICFTMeas(12,10,&dICFTkHz))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IBTTestICFTMeas Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device IBTTestICFTMeas Fail!"))
			return false;
	}
	if (m_ICFTSpec.InRange(dICFTkHz))
	{
		TestPassLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_ICFTSpec.GetMax())),_T(CStr::FloatToStr(m_ICFTSpec.GetMin())),_T(CStr::FloatToStr(dICFTkHz)),_T("kHz"),_T("Inital carrier freq tol PASS"),"ICFT")

	} 
	else
	{
		TestFailLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_ICFTSpec.GetMax())),_T(CStr::FloatToStr(m_ICFTSpec.GetMin())),_T(CStr::FloatToStr(dICFTkHz)),_T("kHz"),_T("Inital carrier freq tol FAIL"),"ICFT")
			return false;
	}
	return true;

}
bool CWCN36XXBtTest::EDRMod()
{
	int iErrorcode,iFailFlag=0;
	double dECVM_RMS=0,dEVM_PEAK=0;


	if((iErrorcode=m_pPhone->BTTestTxBurst(m_iCurrChannel,PSEUDO_RANDOM,BT_3_DH1,0,9,aBTAddr,0))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Phone BTTestTxBurst Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T("-"),iErrorcode,_T("Phone BTTestTxBurst Fail!"))
			return false;
	}

	if((iErrorcode=m_pFunBTTestDev->IBTTestEDRModMeas(12,10,3,&dECVM_RMS,&dEVM_PEAK))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device IBTTestEDRModMeas Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),iErrorcode,_T("Test Device IBTTestEDRModMeas Fail!"))
			return false;
	}
	if (m_RMSDEVMSpec.InRange(dECVM_RMS))
	{
		TestPassLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_RMSDEVMSpec.GetMax())),_T(CStr::FloatToStr(m_RMSDEVMSpec.GetMin())),_T(CStr::FloatToStr(dECVM_RMS)),_T("-"),_T("EDR RMS DEVM PASS"),"EDR RMS DEVM")

	} 
	else
	{
		TestFailLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_RMSDEVMSpec.GetMax())),_T(CStr::FloatToStr(m_RMSDEVMSpec.GetMin())),_T(CStr::FloatToStr(dECVM_RMS)),_T("-"),_T("EDR RMS DEVM FAIL"),"EDR RMS DEVM")
		iFailFlag++;
	}

	if (m_PeakDEVMSpec.InRange(dEVM_PEAK))
	{
		TestPassLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),_T(CStr::FloatToStr(m_PeakDEVMSpec.GetMax())),_T(CStr::FloatToStr(m_PeakDEVMSpec.GetMin())),_T(CStr::FloatToStr(dEVM_PEAK)),_T("-"),_T("EDR PEAK DEVM PASS"),"EDR PEAK DEVM")

	} 
	else
	{
		TestFailLogEx(_T("BT"),_T(CStr::IntToStr(m_iCurrChannel)),WCDMATEST_FER_OUTOFRANGE,_T(CStr::FloatToStr(m_PeakDEVMSpec.GetMax())),_T(CStr::FloatToStr(m_PeakDEVMSpec.GetMin())),_T(CStr::FloatToStr(dEVM_PEAK)),_T("-"),_T("EDR PEAK DEVM FAIL"),"EDR PEAK DEVM")
		iFailFlag++;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CWCN36XXBtTest::RxBer()
{
	return true;
}
bool CWCN36XXBtTest::BTRelease()
{
	m_pPhone->BTTestReset();
	m_pFunBTTestDev->Deivce_Exit();
	m_pPhone->ADB_KILL_SERVER();
	return true;
}