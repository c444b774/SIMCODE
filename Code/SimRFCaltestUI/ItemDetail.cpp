// ItemDetail.cpp : implementation file
//

#include "stdafx.h"
#include "SimRFCaltestUI.h"
#include "ItemDetail.h"
#include  "PasswordDlg.h"

// CItemDetail dialog

IMPLEMENT_DYNAMIC(CItemDetail, CDialog)

CItemDetail::CItemDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CItemDetail::IDD, pParent)
{

}

CItemDetail::~CItemDetail()
{
}

void CItemDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CItemDetail, CDialog)
	ON_BN_CLICKED(IDOK, &CItemDetail::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CItemDetail::OnBnClickedCancel)
END_MESSAGE_MAP()


// CItemDetail message handlers

void CItemDetail::OnBnClickedOk()
{
   
      CPasswordDlg dlg;
	 int iRetrunID=dlg.DoModal();
	 if(iRetrunID==IDCANCEL)
		 return;

	 if(!dlg.IsPSWRightEx())
	
	{
       MessageBox("Wrong Password!");
	   return;
	}
	

	char szClassName[256];
	CStringStringMap mapProcessProject;
    CString strKeyName;
	CWnd* pValueWnd;
	HWND  hwnd;
	CString strListValue;
	CString strBitMask;
	int iIsCheck;
	for(CStringWndMapItr itrMap=m_UICtrlistMap.begin();itrMap!=m_UICtrlistMap.end();++itrMap)
	{ 
		strKeyName=itrMap->first;
		pValueWnd=itrMap->second;
		hwnd=pValueWnd->GetSafeHwnd();
		GetClassName(hwnd,szClassName,256);
		CString strClassName=szClassName;
		if(strClassName.CompareNoCase("BUTTON")==0)
		{
			if(strListValue.IsEmpty())
			{
			 strListValue=strKeyName;
			 iIsCheck=((CButton*)pValueWnd)->GetCheck();
			 strBitMask=CStr::IntToStr(iIsCheck);
			}
			else
			{
			  strListValue=strListValue+","+strKeyName;
			 iIsCheck=((CButton*)pValueWnd)->GetCheck();
			 strBitMask=strBitMask+","+CStr::IntToStr(iIsCheck);
			}
		
		
		}
		else
		{
			CString strValue;
			pValueWnd->GetWindowText(strValue);
			mapProcessProject.insert(make_pair(strKeyName,strValue));
		}
	 
	}

	  mapProcessProject.insert(make_pair("List",strListValue));
	  mapProcessProject.insert(make_pair("ListMask",strBitMask));

    theApp.UpdateXMlProcessProject(m_strItemName,"//Configurations/ProcessObjectSet",mapProcessProject);
    
	OnOK();
}

void CItemDetail::OnBnClickedCancel()
{

	
	OnCancel();
}

BOOL CItemDetail::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_ITEMNAME,m_strItemName);
	 CString strValue;
	CString strItem;
	HWND hWnd; 
	CWnd* pWnd;
	RECT rctOld;
	int iYPoint=0;
	int iXPoint=0;
	int iRowNum=0;
	CStringVtr vtrListMask;
  
	m_UICtrlistMap.clear();
	m_StaticList.clear();
	
  
		for(CStringPairVtrItr itrMap=m_MapData.begin();itrMap!=m_MapData.end();++itrMap)
	{
      
		if(iYPoint==18)
		{
           iYPoint=0;
           iXPoint++;
		   //iRowNum++;
		   GetWindowRect(&rctOld);
		   rctOld.right+=280;
		   MoveWindow(&rctOld);

		   
		}
		

		
		    strItem=itrMap->first;
            
		
			hWnd=CreateWindow(TEXT("STATIC"),strItem,WS_CHILD | WS_VISIBLE,20+iXPoint*280,40+iYPoint*30,150,30,m_hWnd,NULL,(HINSTANCE)(UINT64)GetWindowLong(m_hWnd, GWL_HINSTANCE),NULL);
			pWnd=FromHandle(hWnd);
			m_StaticList.push_back(pWnd);

		    strValue=itrMap->second;

			if(strItem=="ListMask")
			{
              CStr::ParseString(strValue,",",vtrListMask);
			  
			}
			else if(strItem=="List")
			{
				CStringVtr vtrlistItem;
				CStringItr itritem;
                CStringItr itrMask;
				CStr::ParseString(strValue,",",vtrlistItem);
			    
				for(itritem=vtrlistItem.begin(),itrMask=vtrListMask.begin();itritem!=vtrlistItem.end() && itrMask!=vtrListMask.end();++itritem,++itrMask)
				{
                   hWnd=CreateWindow(TEXT("BUTTON"),*itritem,WS_CHILD | WS_VISIBLE|BS_AUTOCHECKBOX |BS_MULTILINE,130+280*iXPoint,40+iYPoint*30,150,20,m_hWnd,NULL,(HINSTANCE)(UINT64)GetWindowLong(m_hWnd, GWL_HINSTANCE),NULL);
				   pWnd=FromHandle(hWnd);
				   if(*itrMask=="1")
					   ((CButton*)pWnd)->SetCheck(1);
				   else
					   ((CButton*)pWnd)->SetCheck(0); 
				   m_UICtrlistMap.insert(make_pair(*itritem,pWnd));
				   iYPoint++;
				}
			} 
			else
				 {
					hWnd=CreateWindow(TEXT("EDIT"),strValue,ES_MULTILINE|WS_CHILD | WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL,180+280*iXPoint,40+iYPoint*30,100,20,m_hWnd,NULL,(HINSTANCE)(UINT64)GetWindowLong(m_hWnd, GWL_HINSTANCE),NULL);
					pWnd=FromHandle(hWnd);
					m_UICtrlistMap.insert(make_pair(strItem,pWnd));
					iYPoint++;
				}
		
		

	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
