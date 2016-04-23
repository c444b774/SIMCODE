#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <deque>
#include <queue> 
#include <algorithm>
#include <string>
#include  "ErrorCode.h"
#include  "Enum_File.h"
#include  "BaseItemCode.h"
#include   "math.h"

#pragma warning(disable:4018)
#pragma warning(disable:4819)

using namespace std;
//define for STL
typedef queue<CString> CStringQue;
typedef pair<CString,CString> CStringPair;
typedef vector<CStringPair> CStringPairVtr;
typedef CStringPairVtr::iterator CStringPairVtrItr; 
typedef map<CString,CStringPairVtr> CString2StringPairMap;
typedef CString2StringPairMap::iterator CString2StringPairMapItr;

typedef map<CString,CString> CStringStringMap;
typedef CStringStringMap::iterator CStringStringMapItr;
typedef pair<CString,CStringStringMap> CStrStrPair;
typedef vector<CStrStrPair> CCString2StringMap;
typedef vector<CStrStrPair>::iterator CStringVtrItr;
typedef CCString2StringMap* PCCString2StringMap;
typedef CStringStringMap * PCStringStrMap;
typedef vector<CString> CStringVtr;
typedef vector<CString>::iterator CStringItr;
typedef vector<int>  IntVtr;
typedef vector<int>::iterator IntItr;
typedef map<CString,double> StringDblMap;
typedef vector<double> DblVtr;
typedef DblVtr::iterator DblVtrItr;





class CRFLossConfig
{
public:
	
	
	CCString2StringMap	  vRFCableRXMapPair;
	CCString2StringMap    vRFCableTXMapPair;
	//CCString2StringMap    vCalGSMCableLossPair;
	//CCString2StringMap    vCalWCDMACableLossPair;
};
typedef CRFLossConfig* PCRFLossConfig;
struct SFSystemConfig
{
	CString strIsDo;
	CString strServerAddr;
	CString strPassword;
	CString strUID;
	CString strCataLog;
	CString strReturnOK;
	CString strStationID;
	CString strFixID;
	CString strLineNum;
	CString strCreator;

};
struct DataBaseConfig
{
	CString strDSN;
	CString strUSER;
	CString strPWD;

};
struct s_UpdateXMLLossPara
{
	CString strXmlPath;
    CString  strType;  
    int iIsUplink;
	CStringStringMap mapFreq2Loss;
};
class CDataBaseConfig
{
public:
	CString strSFDllPath;
	CString strDBDllPath;
	SFSystemConfig s_SFSystemConfig;
	DataBaseConfig s_DataBaseConfig;



};
typedef CDataBaseConfig* PCDataBaseConfig;
class CConfigSetting
{
public: 
	CConfigSetting(){}
	virtual ~CConfigSetting(){}
	HWND    m_hMessageHandlingWnd;
	CCString2StringMap  m_MapLossConfig;
    CCString2StringMap m_MapPairPreConfig;
    CCString2StringMap m_MapConfigSetting;
	CStringStringMap m_MapMainSetting;

	int m_PhonePort;
	int m_ATPort;
	int m_iRetryPhonePortTimes; //unit :s
	bool m_bStopWhenFail;
	CString strSN;
	CString m_strSNHeader;
	int m_iSNLength;
	CString strGPIBAddr;
	CString strGPIBAddr1;
	CString strGPIBAddr2;
    CString strGPIBAddrPLY;
	CString strGPIBAddrPLY1;
	CString strFreqMeasAddr;
	CString strMulMeasAddr;
	CString strProjectName;
	CString strTestDevceName;
    CString strTestDevceName1;
	CString strTestDevceName2;
	CString strPowerSupplyName;
    CString strPowerSupplyName1;
    CString strFreqMeasName;
	CString strMulMeasName;

	int m_iPlyPort;
    int m_iPly1Port;

	CDataBaseConfig dbConfig;


};
typedef CConfigSetting* PCConfigSetting;

inline int OutputAssertInfo(
							const _TCHAR* pszExpression,						
							const _TCHAR* pszFileName,						
							int nLineNo,
							FILE* pFile = stderr
							)
{
	return _ftprintf(pFile,
		_T("**********************************************************************************")
		_T("Assertion failed!\n")
		_T("	Expression: %s\n")
		_T("		File: %s\n")
		_T("		Line: %d\n")
		_T("**********************************************************************************"),
		pszExpression, 
		pszFileName,
		nLineNo
		);

}
#ifndef ASSERT
#ifdef _DEBUG
#include <assert.h>
#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)
#define ASSERT(exp)				{if(!(exp)) {OutputAssertInfo(_T(#exp), _T(__FILE__), __LINE__); assert(0);\
	assert(0); } }
#else //!_DEBUG
#define ASSERT(exp) ;
#endif //_DEBUG	
#endif //ASSERT
#ifndef ASSERT_MSG 
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 
#include <assert.h>
#define ASSERT_MSG(exp, err)	{if(!(exp)) {OutputAssertInfo(err, _T(__FILE__), __LINE__); assert(0);\
	assert(0); } }
#else //!_DEBUG
#define ASSERT_MSG(exp, err) ;
#endif //_DEBUG	
#endif //ASSERT_MSG


//define for Data from UI


	


// operation for String 
#pragma warning(disable : 4244)
class CStr{
public:

	
	static CString IntToStr(int nValue)
	{
		
         CString strInt;
		 
		strInt.Format(_T("%d"),nValue);
		return strInt;
	}
	static CString UShortToStr(unsigned short nValue)
	{
	
        CString strUShort;
		strUShort.Format(_T("%hu"),nValue);
		
		return strUShort;
	}
	static CString FloatToStr(double flValue)
	{
	    CString strFloat;
		strFloat.Format(_T("%.4f"),flValue);
		return strFloat;
	}

	static float StrToFloat(const CString& str)
	{
          float dret;
		  dret=atof(str);
		  
		  return dret;
		

	}
	
	static int StrToInt(const CString& str)
	{
        int iRet;
		iRet=atoi(str);
		return iRet;
	}

	

	static bool StrToBool(const CString& str)
	{
		CString strTemp=str;

		if(strTemp.MakeLower()==_T("1") || strTemp.MakeLower()==_T("yes") || strTemp.MakeLower()=="true")
			return true;
		else
			return false;
		
		 	
	}
                                      
	static void StrVtr2IntVtr(IntVtr & intVtrRes,const CStringVtr & strVtr)
	{
      int iIndex;
	  for(iIndex=0;iIndex<strVtr.size();++iIndex)
	  {
		  intVtrRes.push_back(CStr::StrToInt(strVtr[iIndex]));
	  }

	}
                               
	static void StrVtr2DblVtr(DblVtr & dblVtrRes,const CStringVtr & strVtr)
	{
      int iIndex;
	  for(iIndex=0;iIndex<strVtr.size();++iIndex)
	  {
		  dblVtrRes.push_back(atof(strVtr[iIndex]));
	  }

	}
	static bool ParseString(
		const CString&	strSource,
		const CString&	strDelimiter,
		CStringVtr&			vList,
		bool bClearOldVectr=true,
		bool fAppendDelimiter = false
		);
	static bool StrToIntArr(const CString& str,int nValue[],const CString& spliter,int ArrNum)
	{
		int iIndex;
		CString strCurr,strLeft;
		strCurr=str;
		int iCurrStrLen;
		int spliterLen=spliter.GetLength();
		int i;
		for(i=0;i<ArrNum;i++)
		{
			iIndex=strCurr.Find(spliter);
			if (iIndex==-1)
			{
				nValue[i]=atoi(strCurr);
				break;
			}
			else
			{
				strLeft=strCurr.Left(iIndex);
				iCurrStrLen=strCurr.GetLength();
				strCurr=strCurr.Right(iCurrStrLen-iIndex-spliterLen);
				nValue[i]=atoi(strLeft);

			}

		}
		return true;

	}

	static bool StrToDblArr(const CString& str,double nValue[],const CString& spliter,int ArrNum)
	{
		int iIndex;
		CString strCurr,strLeft;
		strCurr=str;
		int spliterLen=spliter.GetLength();
		int iCurrStrLen;
		for(int i=0;i<ArrNum;i++)
		{
			iIndex=strCurr.Find(spliter);
			if (iIndex==-1)
			{
				nValue[i]=atof(strCurr);
				break;
			}
			else
			{
				strLeft=strCurr.Left(iIndex);
				iCurrStrLen=strCurr.GetLength();
				strCurr=strCurr.Right(iCurrStrLen-iIndex-spliterLen);
				nValue[i]=atof(strLeft);

			}

		}
		return true;

	}

	static bool MakeVector2Map(const CStringVtr& strkey,const CStringVtr& strValue,CStringStringMap & mapReturn);



	
};

template<typename T>
class CRangePair
{
public:
	void SetRange(const T& dlFirst, const T& dlSecond)
	{
		if (dlFirst >= dlSecond)
		{
			m_dlMax = dlFirst;
			m_dlMin = dlSecond;
		} else{
			m_dlMax = dlSecond;
			m_dlMin = dlFirst;
		}
	}
	

	bool InRange(T dlValue){
		if (dlValue > m_dlMax || dlValue < m_dlMin)
		{
			return false;
		}
		return true;
	}
	
	inline T GetMax(){return m_dlMax;}
	inline T GetMin(){return m_dlMin;}

private:
	T m_dlMax;
	T m_dlMin;
};

//define for log

enum EMsgLevel
{
	MSG_WARNING,
	MSG_LOW,
	MSG_MID,
	MSG_HIGH,
	MSG_ERROR,
	MSG_FATAL,	
	MSG_LAST = 0xff
};

enum EComType
{
	AT_CMD,
	ADB_CMD
};


typedef void (*FPFactoryLog)(int iProcessCode,LPCTSTR lpszBand,LPCTSTR lpszChannel, int iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit,BOOL bPass, LPCTSTR lpszMsgFormat, ...);
typedef void (*FPFactoryLogEx)(int iProcessCode,LPCTSTR lpszBand,LPCTSTR lpszChannel, int iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit,BOOL bPass, LPCTSTR lpszItemName,LPCTSTR lpszMsgFormat, ...);
typedef void (*FPTraceLog)(LPCTSTR lpszModule, LPCSTR lpszSrcFile, UINT iSrcLine, EMsgLevel msgLevel, LPCTSTR lpszMsgFormat, ...);
typedef void (*FPCommandLog)(LPCTSTR lpszType, LPCTSTR lpszMessage);


#define LogTrace(level, msg)	TraceLog(_T("SimComRFtest"), level, __FILE__, __LINE__, msg);

#define TestPassLog(strBand, strChannel, iUL, iDL, iMea, strUnit, msg)	FactoryLog(m_iItemCode, strBand, strChannel, 0, iUL, iDL, iMea, strUnit,TRUE, msg);
#define TestFailLog(strBand, strChannel, err, iUL, iDL, iMea,  strUnit, msg)	FactoryLog(m_iItemCode, strBand, strChannel, err, iUL, iDL, iMea, strUnit, FALSE, msg);
#define TestPassLogEx(strBand, strChannel, iUL, iDL, iMea, strUnit, msg,ItemName)	FactoryLogEx(m_iItemCode, strBand, strChannel, 0, iUL, iDL, iMea, strUnit,TRUE, msg,ItemName);
#define TestFailLogEx(strBand, strChannel, err, iUL, iDL, iMea, strUnit, msg,ItemName)	FactoryLogEx(m_iItemCode, strBand, strChannel, err, iUL, iDL, iMea, strUnit,FALSE, msg,ItemName);

#define CalPassLog(strBand, strCH, msg)	FactoryLog(m_iItemCode, strBand, strCH, 0, _T("1"), _T("0"), _T("1"), _T("-"), TRUE, msg);
#define CalFailLog(strBand, strCH, err, msg)	FactoryLog(m_iItemCode, strBand, strCH, err, _T("1"), _T("0"), _T("0"), _T("-"), FALSE, msg);
#define CalPassLogEx(strBand, strCH, msg,ItemName)	FactoryLogEx(m_iItemCode, strBand, strCH, 0, _T("1"), _T("0"), _T("1"), _T("-"), TRUE, msg,ItemName);
#define CalFailLogEx(strBand, strCH, err, msg,ItemName)	FactoryLogEx(m_iItemCode, strBand, strCH, err, _T("1"), _T("0"), _T("0"), _T("-"), FALSE, msg,ItemName);

#define LogPhoneStartCommand(msg)	CommandLog(_T(",QMSL_LOG_C_HIGH_LEVEL_START,"), msg);
#define LogPhoneStopCommand(msg)	CommandLog(_T(",QMSL_LOG_C_HIGH_LEVEL_STOP,"), msg);
#define LogADBSendCommand(msg)	       CommandLog(_T(",ADB_Send,"), msg);
#define LogADBReceiveCommand(msg)	       CommandLog(_T(",ADB_Receive,"), msg);

#define LogATSendCommand(msg)	       CommandLog(_T(",AT_Send,"), msg);
#define LogATReceiveCommand(msg)	       CommandLog(_T(",AT_Receive,"), msg);


CONST COLORREF BKCOLOR_SUCCESS = RGB(50, 255, 28);
CONST COLORREF BKCOLOR_FAIL    = RGB(255, 0, 0);
CONST COLORREF BKCOLOR_STOP   = RGB(0, 0, 255);

#define DEVICE_WRITE(str)   if((iDeviceErr=Device_Write(str))!=DEVICE_SUCCESS) \
return iDeviceErr;

#define DEVICE_QUERY(str)      if((iDeviceErr=Device_Query(str,0))!=DEVICE_SUCCESS) \
return iDeviceErr;

#define DEVICE_QUERY_CHAR(str,chRet)      if((iDeviceErr=Device_Query_Char(str,chRet,0))!=DEVICE_SUCCESS) \
return iDeviceErr;

#define DEVICE_QUERY_DELAY(str,delay)   if((iDeviceErr=Device_Query(str,delay))!=DEVICE_SUCCESS) \
return iDeviceErr; 

#define PHONE_CAL_ERR_LOG(str,errcode)   LogTrace(MSG_ERROR,str)\
		m_iErrorcode=errcode;\
	    CalFailLog(_T("_"),_T("_"),errcode,str);\
		return false;
 
