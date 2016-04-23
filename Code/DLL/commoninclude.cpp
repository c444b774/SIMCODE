#include "stdafx.h"
#include <stdio.h>
#include "inc\commoninclude.h"

bool CStr::ParseString(const CString&	strSource,const CString&	strDelimiter,CStringVtr& vList,bool bClearOldVectr,bool	fAppendDelimiter)
  
  {

	
	 bool fRet = true;
	int stCurrPos = 0;
	int stLastDelimiter=0;
	const int stTotalLen		=strSource.GetLength();
	const int stDelimiterLen	=strSource.GetLength(); 
    if(bClearOldVectr)
	vList.clear();

	for(int iIndex=0;iIndex<stDelimiterLen;++iIndex)
	{
		int iFind=strSource.Find(strDelimiter[iIndex]);
		if(iFind!=-1)
			break;
		if(iIndex==stDelimiterLen-1 && iFind==-1)
		{
			vList.push_back(strSource);
			return true;

		}
	}
	while(stCurrPos < stTotalLen)
	{

		int x = 0;
		for(; x < stDelimiterLen; ++x)
		{
			int stFind = strSource.Find(strDelimiter[x], stCurrPos);

			if(stFind==-1)
			{
				
			}
			else
			{
				stLastDelimiter = stFind;
				int stStrLen=stFind-stCurrPos;
				if(fAppendDelimiter){
					++stStrLen;
				}
				vList.push_back(strSource.Mid(stCurrPos, stStrLen));
				stCurrPos = stFind + 1;
				break;
			}


			
		}
		if(x >= stDelimiterLen)
		{
			
			break;
		}
	}
	if(stLastDelimiter + 1 < stTotalLen){
		vList.push_back(strSource.Mid(stLastDelimiter + 1, stTotalLen - stLastDelimiter - 1));
	}

	return fRet;
	  
  }

bool CStr::MakeVector2Map(const CStringVtr& strkey,const CStringVtr& strValue,CStringStringMap & mapReturn)
{
	if(strkey.size()!=strValue.size())
	{
		return false;
	}
    for(int iIndex=0;iIndex<strkey.size();++iIndex)
	{
      mapReturn.insert(make_pair(strkey[iIndex],strValue[iIndex])); 
	}
	
	return true;
} 

