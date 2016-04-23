#pragma once
#include "IFHandler.h"

class CBaseBandTestProc:public IRFTestProcess
{
	RF_DECLARE_DYNCREATE(CBaseBandTestProc)
public:
	CBaseBandTestProc(void);
	~CBaseBandTestProc(void);

	virtual bool Handle();

       virtual bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		) ;
	 virtual bool InitData();

private: 
	bool CommonTestMainFunc();

	bool ReadSNFunc();
	bool WriteSNFunc();
	bool CWriteNVFunc();
	bool UploadQCN();
	bool ReadSN_QRD_Func();
	bool ReloadNV_Func();
	bool SetPhoneMode();
	bool WriteSN_QRD_Func();
	bool WriteFlag();
	bool CheckFlag();
	bool QRD_FlagOp_Func();
	bool PopMsg();
	bool SleepFunc();
	bool TxLimReviseFunc();
	bool ModeToCDMA();
	bool ModeToGSMWCDMA();

private:
	int m_iQCNAutoRestore;
	int m_iQCNSkipReset;
	int m_iQCNAllowESNMismatch;
	int m_iQCNIgnorePM;
	int m_iSN_NVID1;
	int m_iSN_NVID2;
	int m_iSN_NVID_QRD;
	int m_iFlagNVID;
	int m_iBytePosQRD;
	int m_iStationFlag;
	int m_iIsSet;
	int m_iDelayForNextItemMs;
	int m_iFlagNVIDforSN;
	int m_iClearAllFlag;
	int m_iStationNum;
	int m_iQRD_FlagOp_Enum;  //0 check  1 write  2 clear 
	bool m_bIsClearFlagNV;
	int m_iNV_ID;
	IntVtr m_vNV_Value; 
	int m_iFlagNV;
	CString m_strMsg;
	double m_dSleepSec;
	

    
protected:
	vector<FPClassFunc> m_vFPTestFunc;
	virtual bool DoProcess();
    

};
