// LossConfigPage.cpp : implementation file
//

#include "stdafx.h"
#include "SimRFCaltestUI.h"
#include "LossConfigPage.h"
#include "SimRFDlg.h"
#include  "PasswordDlg.h"

// CLossConfigPage dialog



CLossConfigPage::CLossConfigPage()
	: CPageInterface(CLossConfigPage::IDD)
{

}

CLossConfigPage::~CLossConfigPage()
{
}

void CLossConfigPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLossConfigPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON2, &CLossConfigPage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CLossConfigPage::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLossConfigPage message handlers

void CLossConfigPage::Refresh()
{
	CString strTemp;
	CString strItem;
	HWND hWnd; 
	CWnd* pWnd;
	int iYPoint=0;
	
   theApp.LoadCableLossFromIni();
	m_pMapItemList.clear();
	
	map<CString,CWnd*>::iterator itrWnd;
	for(itrWnd=m_UICtrlListMap.begin();itrWnd!=m_UICtrlListMap.end();++itrWnd)
	{
		pWnd=itrWnd->second;
		pWnd->DestroyWindow();
	}
	m_UICtrlListMap.clear();
	for(CStringVtrItr itrLoss=theApp.m_pConfigSetting->m_MapLossConfig.begin();itrLoss!=theApp.m_pConfigSetting->m_MapLossConfig.end();++itrLoss)
	{
      
	    strItem=itrLoss->first;
		hWnd=CreateWindow(TEXT("STATIC"),strItem,WS_CHILD | WS_VISIBLE,20,60+iYPoint*30,80,60,m_hWnd,NULL,(HINSTANCE)(UINT64)GetWindowLong(m_hWnd, GWL_HINSTANCE),NULL);
		
        int iXpoint=0;
		for(CStringStringMapItr itrLoss2=itrLoss->second.begin();itrLoss2!=itrLoss->second.end() && iXpoint<3;++itrLoss2,++iXpoint)
			{
				 strTemp=itrLoss2->first;
                 hWnd=CreateWindow(TEXT("EDIT"),strTemp,WS_CHILD | WS_VISIBLE |	ES_LEFT	| WS_BORDER,130+200*iXpoint,60+iYPoint*30,40,20,m_hWnd,NULL,(HINSTANCE)(UINT64)GetWindowLong(m_hWnd, GWL_HINSTANCE),NULL);
                 pWnd=FromHandle(hWnd);
                 strTemp.Format("%s_CH%d",strItem,iXpoint+1);
                 m_UICtrlListMap.insert(make_pair(strTemp,pWnd));

				 strTemp=itrLoss2->second;
				 hWnd=CreateWindow(TEXT("EDIT"),strTemp,WS_CHILD | WS_VISIBLE |	ES_LEFT	| WS_BORDER,220+200*iXpoint,60+iYPoint*30,40,20,m_hWnd,NULL,(HINSTANCE)(UINT64)GetWindowLong(m_hWnd, GWL_HINSTANCE),NULL);
				 pWnd=FromHandle(hWnd);
                 strTemp.Format("%s_LOSS%d",strItem,iXpoint+1);
                 m_UICtrlListMap.insert(make_pair(strTemp,pWnd));

                
			}
        
		m_pMapItemList.insert(make_pair(strItem,iXpoint));

		
		iYPoint++;

	}

	return;

}
BOOL CLossConfigPage::OnInitDialog()
{
	CPageInterface::OnInitDialog();
	//Refresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLossConfigPage::OnBnClickedButton2()
{
	LRESULT lr;
	((CTabCtrl*)GetParent())->SetCurSel(0);
	 ((CSimRFDlg*)AfxGetMainWnd())->OnTcnSelchangeTab4(0,&lr);
}

void CLossConfigPage::OnBnClickedButton1()
{ 
	CPasswordDlg dlg;
	int iRetrunID=dlg.DoModal();
	 if(iRetrunID==IDCANCEL)
		 return;


	if(!dlg.IsPSWRgiht())
	
	{
       MessageBox("Wrong Password!");
	   return;
	}
   
    CString strTemp;
	map<CString,CWnd*>::iterator itrMapFindCH;
	map<CString,CWnd*>::iterator itrMapFindLOSS;
	map<CString,int> ::iterator  itrMapItem;
	 CString strCH;
	 CString strLOSS;
	 CString strDllPathName;
	 CString strDllLossFileName;
    char szTemp[1024];


	  ::GetModuleFileName(NULL, szTemp, _MAX_PATH);
	  strDllPathName.Format("%s",szTemp);
     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
	strDllLossFileName=strDllPathName+"\\SystemConfig\\LossConfig.ini";	

	if(fopen(strDllLossFileName,"r")==NULL)
	{
        CString strTemp1=strDllLossFileName+_T("  not exist");
		AfxMessageBox(strTemp1);
		return ;
	}
	for(itrMapItem=m_pMapItemList.begin();itrMapItem!=m_pMapItemList.end();++itrMapItem)
   {
	   for(int i=1;i<itrMapItem->second+1;++i)
	   {
		   strTemp.Format("%s_CH%d",itrMapItem->first,i);
		   itrMapFindCH=m_UICtrlListMap.find(strTemp);
		   if(itrMapFindCH!=m_UICtrlListMap.end())
		   {
			   strTemp.Format("%s_LOSS%d",itrMapItem->first,i);
			 itrMapFindLOSS=m_UICtrlListMap.find(strTemp);

			 if(itrMapFindLOSS!=m_UICtrlListMap.end())

			 {
				
				 itrMapFindCH->second->GetWindowText(strCH);
				 itrMapFindLOSS->second->GetWindowText(strLOSS);

				 ::WritePrivateProfileString(itrMapItem->first,strCH,strLOSS,strDllLossFileName);


			 }

		   }
	   }

   }
   theApp.LoadCableLossFromIni();
   
	LRESULT lr;
	((CTabCtrl*)GetParent())->SetCurSel(0);
	 ((CSimRFDlg*)AfxGetMainWnd())->OnTcnSelchangeTab4(0,&lr);
}
