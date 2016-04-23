
#ifndef __CABLELOSS__H__
#define __CABLELOSS__H__
 
#include "RFObject.h"
#include "CBandInfo.h"
#include   "inc\ILogger.h"
 
class CCableLossFinder : public CRFObject
{
RF_DECLARE_DYNCREATE(CCableLossFinder)
public:
	CCableLossFinder(){	};
	~CCableLossFinder(){};
 
	static PILogger		m_piLogger ;
	bool InitData(
		PCStringStrMap     pcSettingMap,
		CRFObjectMap&   cObjectMap
		);
 
	bool InitData();
 
	void SetConfigSetting(PCConfigSetting pConfigSetting){
		m_pConfigSetting = pConfigSetting;
		m_pvRFCableMapPair= &(m_pConfigSetting->m_MapLossConfig);
	}
	inline static void SetLogger(PILogger piLogger){m_piLogger = piLogger;}

	virtual void TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg);
	virtual void FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg);;
	virtual void CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage);

	CString GSMIntToStr(const int iBand);
	CString WCDMAIntToStr(const int iBand);
	CString WirelessGSMIntToStr(const int iBand);
	CString WirelessWCDMAIntToStr(const int iBand);

	double GetWLANLoss(int iChannel);
	
	double GetBTLoss(int iChannel);

	double GetGPSLoss();

	double GetDTVLoss(int iChannel);

	bool GetWCDMALoss(const CString & iBand,int iChannelTYpe,double & dLoss);

	bool GetCDMALoss(const CString & iBand,int iChannelTYpe,double & dLoss);

	bool GetGSMLoss(const CString & iBand,int iChannelTYpe,double & dLoss);

	CString CDMAIntToStr(const int iBand);

	bool UpdateLossIniFromMap(const CString & strSecName,CStringStringMap str2strMapLossCH);

	CString GetCurrentXmlToIni(CString strSN);

	bool WriteGoldenPowerToIni(CString strBandType,int iBand,DblVtr dVtrGoldenPower,CString strPath);
	bool GetGoldenPowerFromIni(CString strBandType,int iBand,DblVtr &dVtrGoldenPower,CString strPath);

	int GetPurposeOfLossIni(CString strPath,CString strSN);
	bool CompareSNSameTrue(CString strPath,CString strSN);
	int SetLossIniToMeasLoss(CString strPath);
//	bool ReviseXml(CString strXmlPath,CString strNodeList,CString strKey,CString strValue);
private:
	PCConfigSetting		m_pConfigSetting;
	CCString2StringMap*	m_pvRFCableMapPair;

 //public:
 //	CMyMSXML m_pXml;
 
};
typedef CCableLossFinder* PCCableLossFinder;
 
 

 
 
 
 
 
 
#endif //__CABLELOSS__H__
