#include "StdAfx.h"
#include "LteMeasLoop.h"
RF_IMPLEMENT_DYNCREATE(CLteMeasLoop)

CLteMeasLoop::CLteMeasLoop(void)
{
	m_mapClassFunc[_T("LteTestMainFunc")]=&CLteMeasLoop::LteTestMainFunc;
	m_mapClassFunc[_T("LteHandOver")]=&CLteMeasLoop::LteHandOver;
	m_mapClassFunc[_T("LteACLR")]=&CLteMeasLoop::LteACLR;
	m_mapClassFunc[_T("LteMaxPower")]=&CLteMeasLoop::LteMaxPower;
	m_mapClassFunc[_T("ConfiguredTxPower")]=&CLteMeasLoop::LteConfiguredTxPower;
	m_mapClassFunc[_T("LteMinPower")]=&CLteMeasLoop::LteMinPower;
	m_mapClassFunc[_T("LteTxQual")]=&CLteMeasLoop::LteTxQual;
	m_mapClassFunc[_T("LteSEMask")]=&CLteMeasLoop::LteSEMask;
	m_mapClassFunc[_T("LteOBW")]=&CLteMeasLoop::LteOBW;
	m_mapClassFunc[_T("LteBlockErr")]=&CLteMeasLoop::LteBlockErr;
}

CLteMeasLoop::~CLteMeasLoop(void)
{
}

bool CLteMeasLoop::DoProcess()
{
	return CALL_MEMBER_FN(*this, m_fpMainFunc)();
}

bool  CLteMeasLoop::Handle()
{
	if(!DoProcess())
	{
		m_pFuncLteTestDev->Deivce_Exit();
//****************************
	m_pPhone->LTE_NS_IDLE();

	m_pPhone->LTE_NS_STOP();
		return false;
	}

	return true;
}
bool CLteMeasLoop::LteTestMainFunc()
{
	if (!SetLteTestLoss())
		return false;
	for (int i=0;i<m_ivTestChannelList.size();i++)
	{
		m_iCurrentCH=m_ivTestChannelList[i];
		for (vector<FPClassFunc>::iterator itrFP = m_vFPTestFunc.begin();itrFP != m_vFPTestFunc.end(); ++itrFP)

		{
			int iRetry=0;			

			FPClassFunc fpTestFunc=*itrFP;
			for (;;)
			{
				if(CALL_MEMBER_FN(*this,fpTestFunc)()!=true)
				{
					this->LteHandOver();
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
bool CLteMeasLoop::LteConfiguredTxPower()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_MaxPower_Test_BaseItemCode;
	double dPowerMeasured=0;
	double dTxError=0;
	double adMaxUlPwr[3]={-10,10,15};
	CString strMsg;
	for (int i=0;i<3;i++)
	{
		if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,adMaxUlPwr[i]+10,2))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
				return false;
		}

		if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,10*adMaxUlPwr[i]))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
				return false;
		}
		if((iErrorcode=m_pFuncLteTestDev->ILteConfiguredPower(m_iMeasureCount,adMaxUlPwr[i],&dPowerMeasured))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteTestPower Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteTestPower Fail!"))
				return false;
		}
		dTxError=dPowerMeasured-adMaxUlPwr[i];
		strMsg.Format(" at %.0f dBm",adMaxUlPwr[i]);
		if (m_dTxErrorLimit.InRange(dTxError))
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dTxErrorLimit.GetMax())),_T(CStr::FloatToStr(m_dTxErrorLimit.GetMin())),_T(CStr::FloatToStr(dTxError)),_T("dB"),_T("ConfiguredPower PASS")+strMsg,"ConfiguredPower")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_TARGETPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dTxErrorLimit.GetMax())),_T(CStr::FloatToStr(m_dTxErrorLimit.GetMin())),_T(CStr::FloatToStr(dTxError)),_T("dB"),_T("ConfiguredPower FAIL")+strMsg,"ConfiguredPower")
				iFailFlag++;
		}

		if(!m_pPhone->IsPhoneConnected())
		{           
			LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
				return false;
		}
	}	
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CLteMeasLoop::LteMinPower()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_MinPower_Test_BaseItemCode;
	double dPowerMeasured=0;
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,-44,0))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,-500))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteTestPower(m_iMeasureCount,&dPowerMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteTestPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteTestPower Fail!"))
			return false;
	}
	if (m_dMinPowerLimit.InRange(dPowerMeasured))
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MinPower PASS"),"MinPower")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MINPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMinPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMinPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MinPower FAIL"),"MinPower")
			iFailFlag++;
	}
	
	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CLteMeasLoop::LteMaxPower()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_MaxPower_Test_BaseItemCode;
	double dPowerMeasured=0;
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,28,1))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,280))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteTestPower(m_iMeasureCount,&dPowerMeasured))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteTestPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteTestPower Fail!"))
			return false;
	}
	if (m_dMaxPowerLimit.InRange(dPowerMeasured))
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower PASS"),"MaxPower")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_MAXPOWER_OUTOFRANGE,_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMax())),_T(CStr::FloatToStr(m_dMaxPowerLimit.GetMin())),_T(CStr::FloatToStr(dPowerMeasured)),_T("dBm"),_T("MaxPower FAIL"),"MaxPower")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CLteMeasLoop::LteTxQual()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_EVMRMSAvg_Test_BaseItemCode;
	double dEVM=0,dFER=0,dOrgOfst=0,dSptrFlat=0,dInbEm=0;
	CString strMsg;
	for (int i=0;i<m_dvTxQualPowerList.size();i++)
	{
		if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,m_dvTxQualPowerList[i]+3,2))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
				return false;
		}

		if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,10*m_dvTxQualPowerList[i]))!=PHONE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
				return false;
		}
		Sleep(500);
		if((iErrorcode=m_pFuncLteTestDev->ILteTxQual(m_iMeasureCount,&dEVM,&dFER,&dOrgOfst,&dSptrFlat,&dInbEm))!=DEVICE_SUCCESS)
		{
			LogTrace(MSG_ERROR,_T("Test Device ILteTxQual Fail!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteTxQual Fail!"))
				return false;
		}
		strMsg.Format(" at %.1fdBm",m_dvTxQualPowerList[i]);
		if (dEVM<=m_dEVMLimit[i])
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("-999"),_T(CStr::FloatToStr(m_dEVMLimit[i])),_T(CStr::FloatToStr(dEVM)),_T("-"),_T("EVM PASS")+strMsg,"EVM")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_EVM_OUTOFRANGE,_T("-999"),_T(CStr::FloatToStr(m_dEVMLimit[i])),_T(CStr::FloatToStr(dEVM)),_T("-"),_T("EVM FAIL")+strMsg,"EVM")
				iFailFlag++;
		}
		if (dFER<=m_dFERLimit[i])
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("0"),_T(CStr::FloatToStr(m_dFERLimit[i])),_T(CStr::FloatToStr(dFER)),_T("PPM"),_T("FER PASS")+strMsg,"EVM")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_FER_OUTOFRANGE,_T("0"),_T(CStr::FloatToStr(m_dFERLimit[i])),_T(CStr::FloatToStr(dFER)),_T("PPM"),_T("FER FAIL")+strMsg,"FER")
				iFailFlag++;
		}	
		if (dOrgOfst<=m_dOrigOffsetLimit[i])
		{
			TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("-999"),_T(CStr::FloatToStr(m_dOrigOffsetLimit[i])),_T(CStr::FloatToStr(dOrgOfst)),_T("dBc"),_T("Origin Offset PASS")+strMsg,"OriginOffset")

		}
		else
		{
			TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMATEST_ORIGINOFFSET_OUTOFRANGE,_T("-999"),_T(CStr::FloatToStr(m_dOrigOffsetLimit[i])),_T(CStr::FloatToStr(dOrgOfst)),_T("dBc"),_T("Origin Offset FAIL")+strMsg,"OriginOffset")
				iFailFlag++;
		}

		if(!m_pPhone->IsPhoneConnected())
		{           
			LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
				m_iErrorcode=iErrorcode;
			CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
				return false;
		}
	}
	
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CLteMeasLoop::LteSEMask()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_EMASK_Test_BaseItemCode;
	int isPass=1;
	double adSEMask[8]={0};
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,28,2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,250))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteSEMask(m_iMeasureCount,&isPass,adSEMask))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSEMask Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSEMask Fail!"))
			return false;
	}
	isPass=1;
	for (int i=0;i<8;i++)
	{	
		if (adSEMask[i]>m_dvSEMaskLimit[i])
		{
			isPass=0;
		}
	}
	if (isPass)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T(CStr::IntToStr(isPass)),_T("-"),_T("SEMask PASS"),"SEMask")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMA_EMASK_Test_BaseItemCode,_T("1"),_T("1"),_T(CStr::IntToStr(isPass)),_T("-"),_T("SEMask FAIL"),"SEMask")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CLteMeasLoop::LteACLR()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_ACLR_N10_Test_BaseItemCode;
	int isPass=0;
	double adACLR[4]={0};
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,28,2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,250))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteACLR(m_iMeasureCount,&isPass,adACLR))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteACLR Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteACLR Fail!"))
			return false;
	}
	isPass=1;		
	for (int i=0;i<4;i++)
	{		
		if (adACLR[i]>m_dvACLRLimit[i])
		{
			isPass=0;
		}
	}
	if (isPass)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T("1"),_T("1"),_T(CStr::IntToStr(isPass)),_T("-"),_T("ACLR PASS"),"ACLR")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMA_ACLR_N10_Test_BaseItemCode,_T("1"),_T("1"),_T(CStr::IntToStr(isPass)),_T("-"),_T("ACLR FAIL"),"ACLR")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CLteMeasLoop::LteRecall()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_Call_HandOver_Phone_BaseItemCode;

	m_pPhone->LTE_NS_IDLE();

	m_pPhone->LTE_NS_STOP();
	int iconfig=2;
	if (m_strTesterDevice=="CMW500")
	{
		iconfig=1;
	}
	int iDLChannel=CLTEBandInfo::GetDLChannel(m_iTestBand,m_iCurrentCH);
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,23,2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteConfigWaveForm(m_iNumRB,m_iStartRB,m_iMCS))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteConfigWaveForm Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteConfigWaveForm Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteHandOver(m_iTestBand,m_iCurrentCH))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteHandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteHandOver Fail!"))
			return false;
	}	

	if((iErrorcode=m_pPhone->TDLTE_Cal_Setup(m_iTestBand-1,iDLChannel,iconfig))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone StartCall Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone StartCall Fail!"))
			return false;
	}	

	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_WAVEFORM(1,0,m_iStartRB,m_iNumRB,m_iMCS))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->LTE_NS_IS_CONNECTED())!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
			return false;
	}
	return true;

}
bool CLteMeasLoop::LteHandOver()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_Call_HandOver_Phone_BaseItemCode;

	m_pPhone->LTE_NS_IDLE();

	m_pPhone->LTE_NS_STOP();
	int iconfig=2;
	if (m_strTesterDevice=="CMW500")
	{
		iconfig=1;
	}
	int iDLChannel=CLTEBandInfo::GetDLChannel(m_iTestBand,m_iCurrentCH);
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,23,2))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteConfigWaveForm(m_iNumRB,m_iStartRB,m_iMCS))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteConfigWaveForm Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteConfigWaveForm Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteHandOver(m_iTestBand,m_iCurrentCH))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteHandOver Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteHandOver Fail!"))
			return false;
	}	

	if((iErrorcode=m_pPhone->TDLTE_Cal_Setup(m_iTestBand-1,iDLChannel,iconfig))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone StartCall Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone StartCall Fail!"))
			return false;
	}	
	
	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_WAVEFORM(1,0,m_iStartRB,m_iNumRB,m_iMCS))!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone LTE_NS_CONFIG_UL_WAVEFORM Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->LTE_NS_IS_CONNECTED())!=PHONE_SUCCESS)
	{           
		LogTrace(MSG_ERROR,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(_T(m_strTestBand),_T("-"),iErrorcode,_T("Phone LTE_NS_IS_CONNECTED Fail!"))
			return false;
	}
	return true;

}
bool CLteMeasLoop::LteBlockErr()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_BER_Test_BaseItemCode;
	double dBLER=0;
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(m_dRxCellPower,28,1))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,250))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
			return false;
	}
	if((iErrorcode=m_pPhone->LTE_GET_BLER(m_iBLERSamples,&dBLER))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("LTE_GET_BLER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_GET_BLER Fail!"))
			return false;
	}
	if (dBLER<=m_dBLERLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dBLERLimit)),_T("0"),_T(CStr::FloatToStr(dBLER)),_T("%"),_T("BLER PASS"),"BLER")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMA_BER_Test_BaseItemCode,_T(CStr::FloatToStr(m_dBLERLimit)),_T("0"),_T(CStr::FloatToStr(dBLER)),_T("%"),_T("BLER FAIL"),"BLER")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}
bool CLteMeasLoop::LteOBW()
{
	int iErrorcode,iFailFlag=0;;
	m_iItemCode=WCDMA_OccupiedBandWidth_Test_BaseItemCode;
	double dOccBandwith=0;
	if((iErrorcode=m_pFuncLteTestDev->ILteSetPower(-57,28,1))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteSetPower Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteSetPower Fail!"))
			return false;
	}

	if((iErrorcode=m_pPhone->LTE_NS_CONFIG_UL_POWER(0,1,280))!=PHONE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T(" LTE_NS_CONFIG_UL_POWER Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("LTE_NS_CONFIG_UL_POWER Fail!"))
			return false;
	}
	if((iErrorcode=m_pFuncLteTestDev->ILteOBW(m_iMeasureCount,&dOccBandwith))!=DEVICE_SUCCESS)
	{
		LogTrace(MSG_ERROR,_T("Test Device ILteOBW Fail!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Test Device ILteOBW Fail!"))
			return false;
	}
	if (dOccBandwith<=m_dOBWLimit)
	{
		TestPassLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),_T(CStr::FloatToStr(m_dOBWLimit)),_T("0"),_T(CStr::FloatToStr(dOccBandwith)),_T("MHZ"),_T("OBW PASS"),"OBW")

	}
	else
	{
		TestFailLogEx(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),WCDMA_OccupiedBandWidth_Test_BaseItemCode,_T(CStr::FloatToStr(m_dOBWLimit)),_T("0"),_T(CStr::FloatToStr(dOccBandwith)),_T("MHZ"),_T("OBW FAIL"),"OBW")
			iFailFlag++;
	}

	if(!m_pPhone->IsPhoneConnected())
	{           
		LogTrace(MSG_ERROR,_T("Phone Disconnected!"))
			m_iErrorcode=iErrorcode;
		CalFailLog(m_strTestBand,_T(CStr::IntToStr(m_iCurrentCH)),iErrorcode,_T("Phone Disconnected!"))
			return false;
	}
	if (iFailFlag>0)
	{
		return false;
	}
	return true;

}

bool CLteMeasLoop::InitData(
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
	}

	itrFind=pcSettingMap->find(_T("TestBand"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TestBand' from ini file! ");
		return false;

	}
	else
	{
		m_iTestBand=CStr::StrToInt(itrFind->second);
		
	}

	itrFind=pcSettingMap->find(_T("TestChannelList"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TestChannelList' from ini file!");
		return false;

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2IntVtr(m_ivTestChannelList,strVtr);

	}

	itrFind=pcSettingMap->find(_T("NumRB"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'NumRB' from ini file!default 12");
		m_iNumRB=12;

	}
	else
	{
		strValue=itrFind->second;
		m_iNumRB=CStr::StrToInt(strValue);
	}
	
	itrFind=pcSettingMap->find(_T("StartRB"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'StartRB' from ini file!default 0");
		m_iStartRB=0;

	}
	else
	{
		strValue=itrFind->second;
		m_iStartRB=CStr::StrToInt(strValue);
	}
	itrFind=pcSettingMap->find(_T("MCS"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'MCS' from ini file!default 6");
		m_iMCS=6;

	}
	else
	{
		strValue=itrFind->second;
		m_iMCS=CStr::StrToInt(strValue);
	}
	if(m_iMCS>10)
	{
		m_strTestBand.Format("B%d-16QAM",m_iTestBand);
	}else
	{
		m_strTestBand.Format("B%d-QPSK",m_iTestBand);
	}
	
	itrFind=pcSettingMap->find(_T("WaveFile"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'WaveFile' from ini file!default ''");
		m_strWaveFile="D:\\LTE.WV";

	}
	else
	{
		strValue=itrFind->second;
		m_strWaveFile=strValue;
	}
	itrFind=pcSettingMap->find(_T("MeasureCount"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'MeasureCount' from ini file!default 20");
		m_iMeasureCount=20;

	}
	else
	{
		strValue=itrFind->second;
		m_iMeasureCount=CStr::StrToInt(strValue);
	}
	itrFind=pcSettingMap->find(_T("MaxPowerLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'MaxPowerLimit' from ini file!Use default 21-25");
		m_dMaxPowerLimit.SetRange(19.3,25.7);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_dMaxPowerLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("TxErrorLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'TxErrorLimit' from ini file!Use default -5.7,5.7");
		m_dTxErrorLimit.SetRange(-5.7,5.7);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_dTxErrorLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}

	itrFind=pcSettingMap->find(_T("MinPowerLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_FATAL,"Not Find 'MinPowerLimit' from ini file!Use default -70~-50!");
		m_dMinPowerLimit.SetRange(-100,-39);
	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		m_dMinPowerLimit.SetRange(CStr::StrToFloat(strVtr[0]),CStr::StrToFloat(strVtr[1]));
	}
	itrFind=pcSettingMap->find(_T("TxQualPowerList"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'TxQualPowerList' from ini file,Use default 25,-36.8!");
		strValue="25,-36.8";
		CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2DblVtr(m_dvTxQualPowerList,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2DblVtr(m_dvTxQualPowerList,strVtr);
	}

	itrFind=pcSettingMap->find(_T("FERLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'FERLimit' from ini file,Use default 0.1!");
		strValue="0.1,0.1";
		CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2DblVtr(m_dFERLimit,strVtr);		

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2DblVtr(m_dFERLimit,strVtr);
	}

	itrFind=pcSettingMap->find(_T("OBWLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'OBWLimit' from ini file,Use default 10!");
		m_dOBWLimit=10;

	}
	else
	{
		m_dOBWLimit=CStr::StrToFloat(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("EVMLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'EVMLimit' from ini file,Use default 17.5!");
		strValue="17.5,17.5";
		CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2DblVtr(m_dEVMLimit,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2DblVtr(m_dEVMLimit,strVtr);
	}
	itrFind=pcSettingMap->find(_T("OrigOffsetLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'OrigOffsetLimit' from ini file,Use default -24.2!");
		strValue="-24.2,-9.2";
		CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2DblVtr(m_dOrigOffsetLimit,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,_T(","),strVtr);
		CStr::StrVtr2DblVtr(m_dOrigOffsetLimit,strVtr);
	}
	itrFind=pcSettingMap->find(_T("SEMaskLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'SEMaskLimit' from ini file!");
		strValue="-23.5,-11.5,-8.5,-16.5,-16.5,-8.5,-11.5,-23.5";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvSEMaskLimit,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvSEMaskLimit,strVtr);

	}
	itrFind=pcSettingMap->find(_T("ACLRLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_MID,"Not Find 'ACLRLimit' from ini file!");
		strValue="-35.2,-32.2,-32.2,-35.2";
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvACLRLimit,strVtr);

	}
	else
	{
		strValue=itrFind->second;
		CStr::ParseString(strValue,",",strVtr);
		CStr::StrVtr2DblVtr(m_dvACLRLimit,strVtr);

	}
	itrFind=pcSettingMap->find(_T("RxCellPower"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'RxCellPower' from ini file,Use default -96.3!");
		m_dRxCellPower=-96.3;

	}
	else
	{
		m_dRxCellPower=CStr::StrToFloat(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("BLERSamples"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'BLERSamples' from ini file,Use default 500!");
		m_iBLERSamples=500;

	}
	else
	{
		m_iBLERSamples=CStr::StrToInt(itrFind->second);
	}
	itrFind=pcSettingMap->find(_T("BLERLimit"));
	if(itrFind==pcSettingMap->end())
	{
		LogTrace(MSG_WARNING,"Not Find 'BLERLimit' from ini file,Use default 5!");
		m_dBLERLimit=5;

	}
	else
	{
		m_dBLERLimit=CStr::StrToFloat(itrFind->second);
	}

	InitData();
	return true;
}

bool CLteMeasLoop::InitData()
{
	m_pFuncLteTestDev=m_piTesterDevice->m_piFuncWCDMATest;
	return true;
}
bool CLteMeasLoop::SetLteTestLoss()
{
	CString strMsg;
	double dLoss;
	m_vCableLoss.clear();
	CString strCurrBand;
	strCurrBand.Format(_T("B%d"),m_iTestBand);
	for(int i=0;i<3;i++)
	{
		if(!m_LossFinder.GetWCDMALoss(strCurrBand,i,dLoss))
		{
			strMsg.Format("Lte Get Loss Band=%s ,ChannelType=%d Fail",strCurrBand,i);
			LogTrace(MSG_ERROR,strMsg);
			CalFailLog(_T("_"),_T("_"),1001,strMsg);
			return false;
		}
		m_vCableLoss.push_back(dLoss);
	}

	if(DEVICE_SUCCESS!=m_pFuncLteTestDev->ILteSetLoss(m_iTestBand,m_vCableLoss))
	{
		LogTrace(MSG_ERROR,"Set Cableloss device fail");
		CalFailLog(_T("_"),_T("_"),1001,"Set Cableloss device fail");
		return false;

	}

	return  true;
}
