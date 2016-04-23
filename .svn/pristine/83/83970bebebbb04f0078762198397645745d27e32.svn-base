#include "StdAfx.h"
#include "VisaInterface.h"
PILogger		CVisaInterface::m_piLogger=NULL;
CVisaInterface::CVisaInterface(void)
{
	 m_strTesterAddr=_T("");
	 m_strReadBuffer=_T("");
	m_VXIHandle=NULL;
	m_DefaultHandle=NULL;

}

CVisaInterface::~CVisaInterface(void)
{
	 m_strTesterAddr=_T("");

	 if(!m_VXIHandle)
	 {
		 viClose(m_VXIHandle);
		 m_VXIHandle=NULL;
	 }
	 if(!m_DefaultHandle)
	 {
		viClose(m_DefaultHandle);
		m_DefaultHandle=NULL;
	 }
}

void CVisaInterface::TraceLog(LPCTSTR lpszModule, EMsgLevel emLevel, LPCSTR lpszFileName, UINT uiLine, LPCTSTR lpszMsg)
{
	if (m_piLogger)
		m_piLogger->TraceLog(lpszModule, emLevel,lpszFileName, uiLine, lpszMsg);
}
 
 
void CVisaInterface::FactoryLog(int iProcesCode, LPCTSTR strBand, LPCTSTR strChannel, int iErrorCode, LPCTSTR strUL, LPCTSTR strDL, LPCTSTR strMeasured, LPCTSTR strUnit, BOOL bPass, LPCTSTR strMsg)
{
	if (m_piLogger)
		m_piLogger->FactoryLog(iProcesCode, strBand, strChannel, iErrorCode, strUL, strDL, strMeasured, strUnit, bPass, strMsg);
}
 
void CVisaInterface::CommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage)
{
	if (m_piLogger)
	{
		m_piLogger->CommandLog(lpszType, lpszMessage);
	}
 
}

void CVisaInterface::CloseSession()
{
	m_strTesterAddr=_T("");

	 if(!m_VXIHandle)
	 {
		 viClose(m_VXIHandle);
		 m_VXIHandle=NULL;
	 }
	 if(!m_DefaultHandle)
	 {
		viClose(m_DefaultHandle);
		m_DefaultHandle=NULL;
	 }
}
int CVisaInterface::VisaWrite(const CString& strWrite)
{
	CString strMsg;

	ViUInt32 iCount=strWrite.GetLength();
	 ViPUInt32 piCount=0;
	 CString strTemp=strWrite;
	 ViPBuf pBuf=(ViPBuf)strTemp.GetBuffer();
     CommandLog(_T("visa_Write:"),strWrite);
	 ViStatus vstatus=viWrite(m_VXIHandle,pBuf,iCount,piCount);
	 
	  if(vstatus<VI_SUCCESS)
	  {
	    strMsg=_T("Write visa command fail!");
        CommandLog(_T("visa_Write:"),strMsg);
		CloseSession();
		return DEVICE_WRITE_FAIL;
	  }
	
    
	return DEVICE_SUCCESS;
}
int CVisaInterface::VisaRead(CString &strRead)
{
	CString strMsg;
	char *szRead=new char[MAX_READLEN];
	ViUInt32 iCount=MAX_READLEN;
	 ViUInt32 iCountReal;
	 int iTimeout=10;
	
     
	 ViStatus vstatus=viRead(m_VXIHandle,(ViPBuf)szRead,iCount,&iCountReal);
	 if (VI_ERROR_TMO==vstatus)
	 {
		 
			 do 
			 {
				 Sleep(500);				
				 vstatus=viRead(m_VXIHandle,(ViPBuf)szRead,iCount,&iCountReal);
				 if (VI_SUCCESS==vstatus)
				 {
					 break;
				 }
			 } while (VI_ERROR_TMO==vstatus&&iTimeout-->0);
	 }
	 
	  if(vstatus<VI_SUCCESS)
	  {
		  strMsg.Format("Read visa command fail! status:%ld",vstatus);
        CommandLog(_T("visa_Read:"),strMsg);
		CloseSession();
		return DEVICE_READ_FAIL;
	  }

	szRead[iCountReal]='\0';
	strRead.Format("%s",szRead);
	delete[] szRead;
    CommandLog(_T("visa_Read:"),strRead);
	return DEVICE_SUCCESS;
}
int CVisaInterface::VisaClear()
{
	CString strMsg;
	 ViStatus vstatus=viClear(m_VXIHandle);
	  if(vstatus<VI_SUCCESS)
	  {
	    strMsg=_T("Clear visa command fail!");
        CommandLog(_T("visa_Clear:"),strMsg);
		CloseSession();
		return DEVICE_READ_FAIL;
	  }
	  return DEVICE_SUCCESS;
}
int CVisaInterface::VisaQuery_Char(const CString& strQuery,unsigned char* szCharRead,int iDelayMs)
{
	Sleep(iDelayMs);
	CString strMsg;
	unsigned char *szRead=(unsigned char*)malloc(MAX_READLEN);
	memset(szRead,0,MAX_READLEN);
    ViUInt32 iCount=MAX_READLEN;
	 ViUInt32 iCountReal;

   if(VisaWrite(strQuery)!=DEVICE_SUCCESS)
	{
			CloseSession();
		return DEVICE_QUERY_FAIL;
	}
	
     
	 ViStatus vstatus=viRead(m_VXIHandle,(ViPBuf)szRead,iCount,&iCountReal);
	 
	  if(vstatus<VI_SUCCESS)
	  {
       strMsg=_T("Read visa command fail!");
        CommandLog(_T("visa_Read:"),strMsg);
		CloseSession();
		return DEVICE_READ_FAIL;
	  }

	szRead[iCountReal]='\0';
	memcpy(szCharRead,szRead,iCountReal);
	free(szRead);

	return DEVICE_SUCCESS;


}
int CVisaInterface::VisaQuery(const CString& strQuery,int iDelayMs)
{
    
	if(VisaWrite(strQuery)!=DEVICE_SUCCESS)
	{
			CloseSession();
		return DEVICE_QUERY_FAIL;
	}
	Sleep(iDelayMs);
	if (VisaRead(m_strReadBuffer)!= DEVICE_SUCCESS)
	{    	CloseSession();
		return DEVICE_QUERY_FAIL;
	}
 
	return DEVICE_SUCCESS;
}

CString  CVisaInterface::VisaGetReadBuf()
{
	return m_strReadBuffer;
}

int CVisaInterface::OpenSession()
{
	CString strMsg;
	if(m_strTesterAddr==_T(""))
		return DEVICE_OPENDEFAULTSESSION_FAIL;
	 ViStatus status=viOpenDefaultRM(&m_DefaultHandle);
	 if(status<VI_SUCCESS)
		{
			CommandLog(_T(",Visa_Init:,"),_T("Open default Session Fail"));
			return DEVICE_OPENDEFAULTSESSION_FAIL;
		
	    }
	 
       status = viOpen (m_DefaultHandle, (ViRsrc)m_strTesterAddr.GetBuffer(),VI_NULL, VI_NULL, &m_VXIHandle);
	   m_strTesterAddr.ReleaseBuffer();
	    if (status < VI_SUCCESS)
		{
			//if can not open , find resource 
			strMsg=_T("Open TesterDeviceAddr :") +m_strTesterAddr +_T(" Fail try to find resource!");
            CommandLog(_T(",Visa_Init:,"),strMsg);
					char instrDescriptor[VI_FIND_BUFLEN];
					ViUInt32 numInstrs;
					ViFindList findList;

				   status = viFindRsrc (m_DefaultHandle, "?*INSTR", &findList, &numInstrs, instrDescriptor);
			   if (status < VI_SUCCESS)
			   {
				       strMsg=_T("Find resource Fail!");
						 CommandLog(_T(",Visa_Init:,"),strMsg);
	    			   viClose(m_DefaultHandle);
						return DEVICE_FINDRES_FAIL;
			   }

			   strMsg=_T("Found resource :") +CString(instrDescriptor)+ _T(" and try to open it!");
			   CommandLog(_T(",Visa_Init:,"),strMsg);
			   status = viOpen (m_DefaultHandle, instrDescriptor, VI_NULL, VI_NULL, &m_VXIHandle);
		    
				
				if(status<VI_SUCCESS)
				{
                      strMsg=_T("Open resource :") +CString(instrDescriptor)+ _T(" Fail !");
					  CommandLog(_T(",Visa_Init:,"),strMsg);
					 viClose(m_DefaultHandle);
					return DEVICE_OPENCURRENTSESSION_FAIL;
				}
				strMsg=_T("Open resource :") +CString(instrDescriptor) +_T(" Successfully!");
                CommandLog(_T(",Visa_Init:,"),strMsg);
		}
		else
		{
			strMsg=_T("Open TesterDeviceAddr :") +m_strTesterAddr +_T(" Successfully!");
            CommandLog(_T(",Visa_Init:,"),strMsg);
		}


		
return DEVICE_SUCCESS;

}
int CVisaInterface::CheckDeviceLegal()
{
	CString strCmd;
	CString strRes,strDevicesSn;
	CStringVtr strVtr;
	CString strAllSn=_T("1201.0002k75-100463-hA,1201.0002k50-143100-nN,1201.0002k50-147577-Kr,1201.0002k50-147583-sG,1201.0002k50-147590-rC,1201.0002k50/102018,1201.0002k50/143100,1201.0002k50/143802,1201.0002k50/103997,1201.0002k50/121560,1201.0002k25/100491,1201.0002k25/100492,1201.0002k25/100493,1201.0002k25/100494,1201.0002k25/100495,1201.0002k25/100496,1201.0002k25/100497,1201.0002k25/100498,1201.0002k25/100499,6200863124,6200863122,6200863123,6200826444,6201341898,6200951803,6201169174,MY50267182,GB45080106,6201010312,GB46490111,MY47510736,GB46040333,GB44200216,GB45080107,GB45080105,MY48365395,MY48365396,0122,6123,130812-tm");
	CStringVtr strVtrAll;
	strVtrAll.clear();
	strVtrAll.push_back(strAllSn);
	strAllSn=_T("6200863122,6201026541,6201060980,6200491551,6200491552,6200491555,6200526403,GB46120198,GB46120191,GB46120207,GB46120201,GB46120204,GB46120208,GB46120205,GB46120202,GB46120199,6200542696,US45450510,MY46080290,MY46080254,MY46080153,MY46080280,MY46080256,MY46080206,MY46080289,MY46080249,MY46080252,MY46080137,GB46320239,GB46320237,GB46320243,GB46320108,GB46320245,GB46320242,GB46320106,GB46320241,GB46320236,GB47390325,GB47470107,GB47400141,GB47390324,GB47400142,GB47400139,GB47470109,GB47470103,GB47400140,GB47470110,GB47390342,MY47510367,MY47510401,MY47510527,MY47510696,MY47510698,MY47510708,MY47510714,MY47510726,MY47510737,MY47510739,MY47510754,MY47510755,MY47510760,MY46160063,MY46160066,MY46160068,MY46160073,MY46160074,MY46160125,MY46160126,MY46160161,MY46160162,6200751958,6200751959,6200751960,6200751961,0803004,0803013,0803015,0803020,0803022,0803026,0803030,MY46160287,MY46160286,MY46160285,6200826427,6200826429,6200826430,6200826438,6200826432,6200826425,6200826426,6200826436,6200826428,6200705041,6200662396,MY46160288,MY46160291,MY46160292");
	strVtrAll.push_back(strAllSn);
	strAllSn=_T("GB46506328,GB46130415,MY47070318,MY47070368,MY50061321,MY47230828,MY48281312,MY50061352,GB46200584,GB45360940, MY48360818,GB47400133,GB47400130,GB47150398,GB47400124,MY48367845,MY46160295,MY45370113,MY46160296,MY46160300,MY46160301,MY46160303,6200757649,6200772656,6200757645,6200772657,MY44450217,MY45230331,MY46080243,MY46080233,MY48367475,MY48367479,MY48367478,MY48367486,MY48367485,MY48367487,MY48367482,MY48367476,6200826440,6200826441,6200826446,6200826445,6200826455,6200826454,MY48367760,MY48367767,MY48367816,MY48367819,MY48367842,MY48367843,MY48367844,MY50266350,MY50266277,MY50266188,MY50266353,MY50266355,MY50266176,MY50266352,MY50266354,MY50266356,MY50266189,MY50266276,MY50266236,MY50266351,6201010301,6201010307,6201010316,6201010319,6201010322,6201010317,6201010321,6200951830,6201060980,6201060984,6201061002");
	strVtrAll.push_back(strAllSn);
	strAllSn=_T("6200837793,6200951823,6201060979,6201060982,6201061003,6201061004,6201074394,6201060872,6201074395,6201060874,6200837790,6201341898,6201010310,6201010324,6201010320,6201010304,6201010315,6201010305,6201010318,6201009893,6201010312,6201010308,6201010311,6201010302,6201010306,6201010314,6201010303,6201010323,6201010313,6201010325,6200985495,6200985509,6200985501,6200985508,6200985496,6200985507,6200985505,6200985494,6200985497,6200985499,6200985493,6200985503,6200985490,6200985502,6200985498,6200985491,6200985506,6200985510,6200985504,6200985492,MY50266412,MY50266428,MY50266427,MY50266415,MY50266418,MY50266419,MY50266411,MY50266406,MY50266404,MY50266426,MY50266430,MY50266408,MY50266410,MY50266401,MY50266421,MY50266413,MY50266414,MY50266420,MY50266402,MY50266372,MY49072056,MY49072045,MY49072046,MY49072002,MY49072020,MY49071963,MY49072061,MY49072063,MY49072055,100491,100492,100493,100494,100495,100497,100498,100499,100496,6200951821 ,6200951832 ,6200837783,6200951826 ,6200951822,6201074425,6201074424,6200960373,6200951872,6200837795,6200951831");
	strVtrAll.push_back(strAllSn);
	strCmd=_T("*IDN?");
	if(VisaWrite(strCmd)!=DEVICE_SUCCESS)
	{
		CloseSession();
		return DEVICE_QUERY_FAIL;
	}
	if (VisaRead(strRes)!= DEVICE_SUCCESS)
	{    	CloseSession();
	return DEVICE_QUERY_FAIL;
	}
	CStr::ParseString(strRes,",",strVtr);
	strDevicesSn=strVtr[2];
	for (int i=0;i<strVtrAll.size();i++)
	{
		strAllSn=strVtrAll[i];
		if (-1<strAllSn.Find(strDevicesSn))
		{
			return DEVICE_SUCCESS;
		}
	}
	
	return DEVICE_FINDRES_FAIL;
}
