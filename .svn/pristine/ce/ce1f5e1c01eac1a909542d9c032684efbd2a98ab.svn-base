

#include  "stdafx.h"
#include "CRFCalTestProcessor.h"
#include "inc\CUILog.h"



 
 
CRFQualcommCalTestProcessor::CRFQualcommCalTestProcessor() 
{
  //  m_bIsStopWhenFail=1;
	m_bIsRandomCH=false;
	
}
 
 
CRFQualcommCalTestProcessor::~CRFQualcommCalTestProcessor()
{
	CRFObjectMap::iterator itrMap;
    PCRFObject pRFObject=NULL;
	for(itrMap=m_cObjectMap.begin();itrMap!=m_cObjectMap.end();++itrMap)
	{
		pRFObject=itrMap->second;
		if(pRFObject)
		{
		pRFObject->Release();
		pRFObject=NULL;
		}
	}

	if(m_piLogger){
		delete m_piLogger;
		m_piLogger = NULL;
	}
}
 
bool CRFQualcommCalTestProcessor::InitData(
		PCStringStrMap pcSettingMap,
		CRFObjectMap&   cObjectMap
		)
{
	return true;
}
 
bool CRFQualcommCalTestProcessor::InitData()
{
	return true;
}

 
bool CRFQualcommCalTestProcessor::InitData(
		 PCConfigSetting InitConfigData
	)
{
	
  m_pMapConfigSetting=InitConfigData;

  m_hMsgHandlingWnd=m_pMapConfigSetting->m_hMessageHandlingWnd;
  m_LossFinder.SetConfigSetting(m_pMapConfigSetting);

  return true;	

}
 


 
bool CRFQualcommCalTestProcessor::ApplyHanderList()
{
    int  iIndex=0;
	int  iIsFail=0;
	
    VtrPairStringHandlerItr itrHandle;
	CStringPairVtrItr       itrRunFailList;
    CStringVtr                  vtrFailRunList;
	for(itrHandle=m_pHanderListName.begin();itrHandle!=m_pHanderListName.end();++itrHandle)
	{
		PIRFHandler pHandle=itrHandle->second;
		CString HandleName=itrHandle->first;
	    CString strFailRunList=pHandle->m_strFailRunList;
	   
		::SendMessage(m_hMsgHandlingWnd,WM_TRD_CALTEST_PROGRESS_PROC,0,(LPARAM)&iIndex);
        iIndex++;
		if(!pHandle->Handle())
		{
			if(m_bIsStopWhenFail)
			{
                if(strFailRunList!="")
				{
				    CStr::ParseString(strFailRunList,",",vtrFailRunList);
					for(int i=0;i<vtrFailRunList.size();++i)
					{
						for(int j=0;j<m_pHanderListName.size();++j)
						{
							if(m_pHanderListName[j].first==vtrFailRunList[i])
							{
								pHandle=m_pHanderListName[j].second;
								pHandle->Handle();
								::SendMessage(m_hMsgHandlingWnd,WM_TRD_CALTEST_PROGRESS_PROC,0,(LPARAM)&j);

							}
						}
					

					}

				}
				--iIndex;
			   ::SendMessage(m_hMsgHandlingWnd,WM_TRD_CALTEST_PROGRESS_PROC,0,(LPARAM)&iIndex);
				return false;
			}
			else
			{
			iIsFail=1;
           ::SendMessage(m_hMsgHandlingWnd,WM_TRD_CALTEST_PostFllg_PROC,0,(LPARAM)&iIsFail);
			}
		}
	}
	return true;

}
bool CRFQualcommCalTestProcessor::SetLoggerFunction(
		FPFactoryLog fpFactoryLog,
		FPTraceLog fpTraceLog,
		FPCommandLog fpCommandLog,
		FPFactoryLogEx fpFactoryLogEx
		)
{
	if(!m_piLogger){
		m_piLogger = new CUILogger;
		m_piLogger->SetFactoryLogger(fpFactoryLog);
		m_piLogger->SetFactoryLoggerEx(fpFactoryLogEx);
		m_piLogger->SetTraceLogger(fpTraceLog);
		m_piLogger->SetCommandLogger(fpCommandLog);
	}
	return true;
	
}
bool CRFQualcommCalTestProcessor::Handle()
{
   
	 if(!ParseConfigData())
		return false;
     if(!CreateObjects())
		 return false;
	 if(!ApplyHanderList())
		 return false;
	return true;
 
}
bool  CRFQualcommCalTestProcessor::ParseConfigData()
{
    bool bFoundProc=false;
	bool bFoundPre=false;
	bool bFoundPreconfig=false;
	m_pProcessList.clear();
	CCString2StringMap::iterator itr2Map;
	CStringStringMapItr itrMap;
	CStringStringMap map2String;
	CStringPairVtrItr itrPair;
    vector<CString> vtrTemp;
	
    CTesterDevice::SetLogger(m_piLogger);
	IPhone::SetLogger(m_piLogger);
	CVisaInterface::SetLogger(m_piLogger);
	IFuncDev::SetLogger(m_piLogger);
	CSerComInterface::SetLogger(m_piLogger);
	CCableLossFinder::SetLogger(m_piLogger);
	//first lookup for preobjets list and process list
	CStringStringMapItr itrapFind;
    CString2StringPairMapItr itrMapMapFind;
	itrapFind=m_pMapConfigSetting->m_MapMainSetting.find(_T("List"));
	if(itrapFind==m_pMapConfigSetting->m_MapMainSetting.end())
		return false;
    m_pProcessList.clear();
	CStr::ParseString(itrapFind->second,",",m_pProcessList);

    itrapFind=m_pMapConfigSetting->m_MapMainSetting.find(_T("RunListFail"));
	if(itrapFind==m_pMapConfigSetting->m_MapMainSetting.end())
		return false;
 
	CStr::ParseString(itrapFind->second,"$",vtrTemp);

    for(int i=0;i<m_pProcessList.size();++i)
	{
		m_pProcessListRunFail.push_back(make_pair(m_pProcessList[i],vtrTemp[i])); 
	}



    m_pPreObjectList=m_pMapConfigSetting->m_MapPairPreConfig;
    m_pProcessObjectList=m_pMapConfigSetting->m_MapConfigSetting;
    m_pMainSetting=m_pMapConfigSetting->m_MapMainSetting;

	m_strDeviceAddr=m_pMapConfigSetting->strGPIBAddr;
	m_strDeviceAddr1=m_pMapConfigSetting->strGPIBAddr1;
	m_strDeviceAddr2=m_pMapConfigSetting->strGPIBAddr2;

	m_strPlyAddr=m_pMapConfigSetting->strGPIBAddrPLY;
    m_strPlyAddr1=m_pMapConfigSetting->strGPIBAddrPLY1;
	m_strFreqMeasAddr=m_pMapConfigSetting->strFreqMeasAddr;
	m_strMultiMeasAddr=m_pMapConfigSetting->strMulMeasAddr;
    m_iPlyPort=m_pMapConfigSetting->m_iPlyPort;
    m_iPly1Port=m_pMapConfigSetting->m_iPly1Port;
    m_iComport=m_pMapConfigSetting->m_PhonePort;
	m_iATComport=m_pMapConfigSetting->m_ATPort;
	m_iComportRetryTimes=m_pMapConfigSetting->m_iRetryPhonePortTimes;
	m_bIsStopWhenFail=m_pMapConfigSetting->m_bStopWhenFail;
    m_strSN=m_pMapConfigSetting->strSN;
	m_strSNHeader=m_pMapConfigSetting->m_strSNHeader;
	m_iSNLength=m_pMapConfigSetting->m_iSNLength;
	return true;
}

bool CRFQualcommCalTestProcessor::CreateObjects()
{
	CString strMsg;
   PCRFRuntimeClass pcObjectFactory = RF_RUNTIME_CLASS(CRFObject);
   CString strClassName;
   CString strObjectName;

   PCRFObject pObject=NULL;
  
   CStringStringMapItr itrMap; 
   CStrStrPair strMapPair;
   CStringStringMap strstrMap;
   CStringStringMapItr itrMainSettingItr;
   CRFObjectMap::iterator itrObject;
   
 
   for(int  i=0;i<m_pPreObjectList.size();i++)
	{
		  strMapPair=m_pPreObjectList[i]; 
		  strClassName=strMapPair.first;
		  strstrMap=strMapPair.second;
		  itrMap=strstrMap.find(_T("Name"));
		  if(itrMap==strstrMap.end())
		  {

               strMsg = _T("Failed to get field 'ObjectName' for class :") + strClassName ;
               LogTrace(MSG_ERROR,strMsg)
			   return false;
		  }
		
		  strObjectName=itrMap->second;
		  itrObject=m_cObjectMap.find(strObjectName);
           strMsg=_T("Create Object '") + strObjectName+_T(" ' for Class '") + strClassName +_T(" '");
				LogTrace(MSG_MID,strMsg)
				if(itrObject==m_cObjectMap.end())
				{
					if(!(pObject=pcObjectFactory->CreateObject(strClassName)))
					{
						strMsg = _T("Failed to create object:") + strClassName + _T("; spell-check class name");
                         LogTrace(MSG_ERROR,strMsg)
						return false;
					}
					if(!pObject->InitData(&strstrMap,m_cObjectMap))
					{
						strMsg = _T("Failed to initialize object:") + strClassName + _T("; spell-check class name");
						LogTrace(MSG_ERROR,strMsg)
						return false;
						
					}
		              m_cObjectMap.insert(make_pair(strObjectName,pObject));
                  }
	
		}
   //  Init mainSetting Data
        CRFObjectMap::iterator itrObjectMap;
        itrMainSettingItr=m_pMainSetting.find("Phone");
		itrObjectMap=m_cObjectMap.find(itrMainSettingItr->second);
		if(itrObjectMap==m_cObjectMap.end())
		{
              strMsg = _T("Failed to Find Phone Object from ObjectLists:");
						LogTrace(MSG_ERROR,strMsg)
						return false;
		}
		m_pPhone=dynamic_cast<PIPhone>(itrObjectMap->second);
   	   
		itrMainSettingItr=m_pMainSetting.find("TesterDeviceCommon");

		if(itrMainSettingItr==m_pMainSetting.end())
			{
				 strMsg = _T("Failed to Find TesterDeviceCommon  Object from ObjectLists");
							LogTrace(MSG_WARNING,strMsg)
								return false;
			}
		
             if(!itrMainSettingItr->second.CompareNoCase("dummy"))
			{
				m_strTesterDevice="dummy";
				m_piTesterDevice=NULL;
			}
			 else
			 {
				itrObjectMap=m_cObjectMap.find(itrMainSettingItr->second);
			    
				if(itrObjectMap==m_cObjectMap.end())
				{
                   strMsg = _T("Failed to Find TesterDeviceCommon  Object from ObjectLists");
							LogTrace(MSG_WARNING,strMsg)
							return false;
								
				}
				else
				{
					m_piTesterDevice=dynamic_cast<PCTesterDevice>(itrObjectMap->second);
					m_strTesterDevice=itrObjectMap->first;
				}
			}
		
	

		

		   itrMainSettingItr=m_pMainSetting.find("TesterDevice1");
		
	        if(itrMainSettingItr==m_pMainSetting.end())
			{
				 strMsg = _T("Failed to Find TesterDevice1  Object from ObjectLists");
							LogTrace(MSG_WARNING,strMsg)
			}
			else
			{
				  itrObjectMap=m_cObjectMap.find(itrMainSettingItr->second);
			       if(!itrMainSettingItr->second.CompareNoCase("dummy"))
						{
							m_strTesterDevice1="dummy";
							m_piTesterDevice1=NULL;
						}
				   else
				   {
	
						if(itrObjectMap==m_cObjectMap.end())
						{
							  strMsg = _T("Failed to Find TesterDevice1 Object from ObjectLists");
										LogTrace(MSG_WARNING,strMsg)
						}
						else
						{
							
				
							m_piTesterDevice1=dynamic_cast<PCTesterDevice>(itrObjectMap->second);
							 
							m_strTesterDevice1=itrObjectMap->first;

						}
				   }
			}
	
		
         
		itrMainSettingItr=m_pMainSetting.find("TesterDevice2");
	    if(itrMainSettingItr==m_pMainSetting.end())
		{
                  strMsg = _T("Failed to Find TesterDevice2  Object from ObjectLists");
						LogTrace(MSG_WARNING,strMsg)
		}
		else
		{
			itrObjectMap=m_cObjectMap.find(itrMainSettingItr->second);
		    	if(!itrMainSettingItr->second.CompareNoCase("dummy"))
					{
						m_strTesterDevice2="dummy";
						m_piTesterDevice2=NULL;
					}
				else
				{
			if(itrObjectMap==m_cObjectMap.end())
			{
				  strMsg = _T("Failed to Find TesterDevice2  Object from ObjectLists");
							LogTrace(MSG_WARNING,strMsg)
			}
			else
			{
			
								  
                		m_piTesterDevice2=dynamic_cast<PCTesterDevice>(itrObjectMap->second);
						m_strTesterDevice2=itrObjectMap->first;
	
			}
				}
		}


    

		itrMainSettingItr=m_pMainSetting.find("MulMeasDevice");
	    if(itrMainSettingItr==m_pMainSetting.end())
		{
                  strMsg = _T("Failed to Find MultiMeas  Object from ObjectLists");
						LogTrace(MSG_WARNING,strMsg)
		}
		else
		{
			itrObjectMap=m_cObjectMap.find(itrMainSettingItr->second);
		    	if(!itrMainSettingItr->second.CompareNoCase("dummy"))
					{
						m_strMultiMeasDevice="dummy";
						m_piMultiMeasDevice=NULL;
					}
				else
				{
			if(itrObjectMap==m_cObjectMap.end())
			{
				  strMsg = _T("Failed to Find MultiMeas  Object from ObjectLists");
							LogTrace(MSG_WARNING,strMsg)
			}
			else
			{
			
								  
                		m_piMultiMeasDevice=dynamic_cast<PCGenMulMeter>(itrObjectMap->second);
						m_strMultiMeasDevice=itrObjectMap->first;
	
			}
				}
		}


			itrMainSettingItr=m_pMainSetting.find("FreqMeasDevice");
	    if(itrMainSettingItr==m_pMainSetting.end())
		{
                  strMsg = _T("Failed to Find FreqMeas  Object from ObjectLists");
						LogTrace(MSG_WARNING,strMsg)
		}
		else
		{
			itrObjectMap=m_cObjectMap.find(itrMainSettingItr->second);
		    	if(!itrMainSettingItr->second.CompareNoCase("dummy"))
					{
						m_strFreqMeasDevice="dummy";
						m_piFreqMeasDevice=NULL;
					}
				else
				{
			if(itrObjectMap==m_cObjectMap.end())
			{
				  strMsg = _T("Failed to Find FreqMeas  Object from ObjectLists");
							LogTrace(MSG_WARNING,strMsg)
			}
			else
			{
			              
								  
                		m_piFreqMeasDevice=dynamic_cast<PCGenFreqMeas>(itrObjectMap->second);
						m_strFreqMeasDevice=itrObjectMap->first;
	
			}
				}
		}



	

        itrMainSettingItr=m_pMainSetting.find("PowerSupplyCommon");
        if(itrMainSettingItr==m_pMainSetting.end())
			{
				 strMsg = _T("Failed to Find PowerSupplyCommon  Object from ObjectLists");
							LogTrace(MSG_WARNING,strMsg)
			}
		else
		{
			itrObjectMap=m_cObjectMap.find(itrMainSettingItr->second);
			if(!itrMainSettingItr->second.CompareNoCase("dummy"))
				{
					m_strPlyName="dummy";
				    m_piPowerSly=NULL;
				}
			else
				{
			      if(itrObjectMap==m_cObjectMap.end())
					{
						  strMsg = _T("Failed to Find PowerSupplyCommon  Object from ObjectLists");
									LogTrace(MSG_WARNING,strMsg)
					}
					else
					{
						
					
                    
						m_piPowerSly=dynamic_cast<PCPowerSupply>(itrObjectMap->second);
						
						m_strPlyName=itrObjectMap->first;
					
					}
				}
			}
	

	

       
		     itrMainSettingItr=m_pMainSetting.find("PowerSupply1");
		     if(itrMainSettingItr==m_pMainSetting.end())
			{
				 strMsg = _T("Failed to Find PowerSupply1  Object from ObjectLists");
							LogTrace(MSG_WARNING,strMsg)
			}
			 else
			 {
		
	
					itrObjectMap=m_cObjectMap.find(itrMainSettingItr->second);
		
					if(itrObjectMap==m_cObjectMap.end())
					{
						  strMsg = _T("Failed to Find PowerSupply1  Object from ObjectLists");
									LogTrace(MSG_WARNING,strMsg)
					}
					else
					{
						if(itrMainSettingItr->second.CompareNoCase("dummy")==0)
						{
				         
						   m_strPlyName1=itrMainSettingItr->second;
						   m_piPowerSly1=NULL;
						}
						else
						{
							m_piPowerSly1=dynamic_cast<PCPowerSupply>(itrObjectMap->second);
				
							m_strPlyName1=itrObjectMap->first;
						}
					}

			}


	//Init Process Objects

		for(int  i=0;i<m_pProcessObjectList.size();i++)
	{
		  strMapPair=m_pProcessObjectList[i];    	
		  strClassName=strMapPair.first;
		  strstrMap=strMapPair.second;
		  itrMap=strstrMap.find(_T("Name"));
		  if(itrMap==strstrMap.end())
		  {

               strMsg = _T("Failed to get field 'ObjectName' for class :") + strClassName ;
               LogTrace(MSG_ERROR,strMsg)
			   return false;
		  }
		
		  strObjectName=itrMap->second;
		  itrObject=m_cObjectMap.find(strObjectName);
           strMsg=_T("Create Object '") + strObjectName+_T(" ' for Class '") + strClassName +_T(" '");
				LogTrace(MSG_MID,strMsg)
				if(itrObject==m_cObjectMap.end())
				{
					if(!(pObject=pcObjectFactory->CreateObject(strClassName)))
					{
						strMsg = _T("Failed to create object:") + strClassName + _T("; spell-check class name");
                         LogTrace(MSG_ERROR,strMsg)
						return false;
					}
					if(!pObject->InitData(&strstrMap,m_cObjectMap))
					{
						strMsg = _T("Failed to initialize object:") + strClassName + _T("; spell-check class name");
						LogTrace(MSG_ERROR,strMsg)
						return false;
						
					}
		              m_cObjectMap.insert(make_pair(strObjectName,pObject));
					 
                  }
	
		}

	//Insert RF handler list
		for(CStringItr itrProcess=m_pProcessList.begin();itrProcess!=m_pProcessList.end();++itrProcess)
		{
			  itrObject=m_cObjectMap.find(*itrProcess);
				if(itrObject==m_cObjectMap.end())
				{
					strMsg = _T("Failed to Find ObjectName:") + *itrProcess + _T("From Object Map");
						LogTrace(MSG_ERROR,strMsg)
						return false;
				}
		 pObject=itrObject->second; 
		  //m_pHanderList.push_back(dynamic_cast<PIRFHandler>(pObject));

		  m_pHanderListName.push_back(make_pair(*itrProcess,dynamic_cast<PIRFHandler>(pObject)));
		}
   
	return true;
}
 
void CRFQualcommCalTestProcessor::Abort()
{

}
 
bool CRFQualcommCalTestProcessor::DoProcess()
{   
	return true;
}


 
 

 
 

 

 
