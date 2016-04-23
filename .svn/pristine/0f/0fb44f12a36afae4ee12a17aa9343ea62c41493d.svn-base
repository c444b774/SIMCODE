// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimRFCaltestUI.h"
//#include  "SimRFCaltestUIDlg.h"
#include "SetupDlg.h"


// CSetupDlg dialog

IMPLEMENT_DYNAMIC(CSetupDlg, CDialog)

CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{

}

CSetupDlg::~CSetupDlg()
{
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLALL, m_listProcessAll);
	DDX_Control(pDX, IDC_PLEN, m_listProcessEnable);
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSetupDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetupDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSetupDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CSetupDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CSetupDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CSetupDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &CSetupDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CSetupDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CSetupDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CSetupDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, &CSetupDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON10, &CSetupDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CSetupDlg message handlers

void CSetupDlg::OnBnClickedOk()
{
   
	
     CString strDllPathName;
	 CString strDllLossFileName;
	_TCHAR _tKeyName[1000]={0};
	_TCHAR _TSectionName[1000]={0};
	_TCHAR _tKeyValue[1000];
	CString strTemp;
	int iCtrlIDIndex=0;
	CString strChannel;
	CString striLoss;
    
	
	 if(m_listProcessEnable.GetCount()==0)
	 {
      AfxMessageBox("ProcesslistEnable can not be NULL");
	  return;
	 }
	
   
	::GetModuleFileName(NULL, strDllPathName.GetBuffer(_MAX_PATH), _MAX_PATH);
	  strDllPathName.ReleaseBuffer();
     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
	strDllLossFileName=strDllPathName+"\\SystemConfig\\LossConfig.ini";	
	strDllPathName=strDllPathName+_T("\\SystemConfig\\SystemSetup.ini");
	
	if(fopen(strDllPathName,"r")==NULL)
	{
        CString strTemp=strDllPathName+_T("  not exist");
		AfxMessageBox(strTemp);
		return ;
	}

	if(fopen(strDllLossFileName,"r")==NULL)
	{
        CString strTemp1=strDllLossFileName+_T("  not exist");
		AfxMessageBox(strTemp1);
		return ;
	}
	GetDlgItemText(IDC_FILESEQPATH,strTemp);
	::WritePrivateProfileString(_T("File Path"),_T("SequencePath"),strTemp,strDllPathName);
    GetDlgItemText(IDC_LOGPATH,strTemp);
   ::WritePrivateProfileString(_T("File Path"),_T("LogPath"),strTemp,strDllPathName);

      GetDlgItemText(IDC_DIAGPORT,strTemp);
	  strTemp=strTemp.Right(strTemp.GetLength()-3);
   ::WritePrivateProfileString(_T("Settings"),_T("PhoneComport"),strTemp,strDllPathName);

      GetDlgItemText(IDC_ATPORT,strTemp);
	  strTemp=strTemp.Right(strTemp.GetLength()-3);
   ::WritePrivateProfileString(_T("Settings"),_T("ATComport"),strTemp,strDllPathName);

    GetDlgItemText(IDC_WAITCOM,strTemp);
	strTemp=strTemp.Left(strTemp.GetLength()-2);
   ::WritePrivateProfileString(_T("Settings"),_T("PhoneOpenPortRetryTime"),strTemp,strDllPathName);

      GetDlgItemText(IDC_TESTSET,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("TesterDeviceCommon"),strTemp,strDllPathName);

    GetDlgItemText(IDC_TESTSET1,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("TesterDevice1"),strTemp,strDllPathName);

      GetDlgItemText(IDC_GPIBADDR,strTemp);
   
    ::GetPrivateProfileString(_T("Settings"),_T("Device_Addr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    CString str=_tKeyValue;   
	int iIndex=str.Find("::");
	str=str.Left(iIndex+2);
    str+=strTemp;
   ::WritePrivateProfileString(_T("Settings"),_T("Device_Addr"),str,strDllPathName);

     GetDlgItemText(IDC_GPIBADDR1,strTemp);
   
    ::GetPrivateProfileString(_T("Settings"),_T("Device_Addr1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    str=_tKeyValue;   
	iIndex=str.Find("::");
	str=str.Left(iIndex+2);
    str+=strTemp;
   ::WritePrivateProfileString(_T("Settings"),_T("Device_Addr1"),str,strDllPathName);
    
   int iCheck=((CButton*)GetDlgItem(IDC_SFCTRL))->GetCheck();
   ::WritePrivateProfileString(_T("Settings"),_T("IsDoSF"),CStr::IntToStr(iCheck),strDllPathName);
    
   iCheck=((CButton*)GetDlgItem(IDC_STOPFAIL))->GetCheck();

   ::WritePrivateProfileString(_T("Settings"),_T("StopWhenFail"),CStr::IntToStr(iCheck),strDllPathName);

    //BT 
    for(int i=0;i<3;i++)
	{
		GetDlgItemText(IDC_BTLOWCH+i,strChannel);
        GetDlgItemText(IDC_BTLOWLOSS+i,striLoss);
        if(strChannel!="" && striLoss!="")
		{
	 
      ::WritePrivateProfileString(_T("BT"),strChannel,striLoss,strDllLossFileName);
		}

	}

	for(int i=0;i<3;i++)
	{
		GetDlgItemText(IDC_WLLOWCH+i,strChannel);
        GetDlgItemText(IDC_WLLOWLOSS+i,striLoss);
        if(strChannel!="" && striLoss!="")
		{
      ::WritePrivateProfileString(_T("WLAN"),strChannel,striLoss,strDllLossFileName);
		}

	}

	for(int i=0;i<3;i++)
	{
		GetDlgItemText(IDC_DTVLOWCH+i,strChannel);
        GetDlgItemText(IDC_DTVLOWLOSS+i,striLoss);
        if(strChannel!="" && striLoss!="")
		{
      ::WritePrivateProfileString(_T("DTV"),strChannel,striLoss,strDllLossFileName);
		}

	}
   
        GetDlgItemText(IDC_GPSLOWCH,strChannel);
        GetDlgItemText(IDC_GPSLOWLOSS,striLoss);
		  if(strChannel!="" && striLoss!="")
		{
		  ::WritePrivateProfileString(_T("GPS"),strChannel,striLoss,strDllLossFileName);
		}
		  theApp.m_vProcessListEnable.clear();
		  for(int i=0;i<m_listProcessEnable.GetCount();++i)
		  {
			  m_listProcessEnable.GetText(i,strTemp);
			  theApp.m_vProcessListEnable.push_back(strTemp);
		  }
     if(m_bChangeProcess)
     theApp.UpdateXMLProcessList();

	 theApp.ParseSystemIni();
	
     CMainPage* pTraceLogWnd = dynamic_cast<CMainPage*>(((CSimRFCaltestUIApp*)AfxGetApp())->m_pMainPage);

	pTraceLogWnd->LoadIniAndUpdateUi();
	OnOK();
}

void CSetupDlg::OnBnClickedButton1()
{ 
	CString strPath;
  CFileDialog dlgSeq(true,"*.ini",NULL,0 ,"INI/XML Files (*.ini;*.xml)|*.xml|");
  if(IDCANCEL==dlgSeq.DoModal())
	  return;

  strPath=dlgSeq.GetPathName();
  SetDlgItemText(IDC_FILESEQPATH,strPath);


  if(!theApp.LoadConfigDataFromXML(strPath))
	{
		//return false;
	}
	
   ((CListBox*)GetDlgItem(IDC_PLALL))->ResetContent();
   ((CListBox*)GetDlgItem(IDC_PLEN))->ResetContent();
	  for(CStringItr itrProcessList=theApp.m_vProcessList.begin();itrProcessList!=theApp.m_vProcessList.end();++itrProcessList)
	  {
		  ((CListBox*)GetDlgItem(IDC_PLALL))->AddString(*itrProcessList);
	  }
	  ((CListBox*)GetDlgItem(IDC_PLALL))->SetCurSel(0);

	   for(CStringItr itrProcessListEN=theApp.m_vProcessListEnable.begin();itrProcessListEN!=theApp.m_vProcessListEnable.end();++itrProcessListEN)
	  {
		  ((CListBox*)GetDlgItem(IDC_PLEN))->AddString(*itrProcessListEN);
	  }
	   ((CListBox*)GetDlgItem(IDC_PLEN))->SetCurSel(((CListBox*)GetDlgItem(IDC_PLEN))->GetCount()-1);
  


	
}

void CSetupDlg::OnBnClickedButton2()
{
	char szBuffer[1024];
	CString strIniDir;
	CString strSelectDir;
	GetCurrentDirectory (1024,szBuffer);
    strIniDir=szBuffer;
  CFolderDlg dlgFolder(TRUE, strIniDir, NULL);
  if(IDCANCEL==dlgFolder.DoModal())
	  return;
  strSelectDir=dlgFolder.GetFolderName();
  SetDlgItemText(IDC_LOGPATH,strSelectDir);
}

BOOL CSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString strTemp;
	CString strDeviceAddr;
	CStringStringMapItr itrLossFind;
	int iIndex;

    m_bChangeProcess=false;
    for(int i=1;i<100;i++)
	{
	strTemp.Format("COM%d",i);
	((CComboBox*)GetDlgItem(IDC_DIAGPORT))->AddString(strTemp);
	((CComboBox*)GetDlgItem(IDC_ATPORT))->AddString(strTemp);
    strTemp.Format("%d",i);
	((CComboBox*)GetDlgItem(IDC_GPIBADDR))->AddString(strTemp);
	((CComboBox*)GetDlgItem(IDC_GPIBADDR1))->AddString(strTemp);
	}
    
	 for(int i=2;i<50;i+=2)
	{
	strTemp.Format("%d s",i);
	((CComboBox*)GetDlgItem(IDC_WAITCOM))->AddString(strTemp);
	}

	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("CMW500");
	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("MT8820");
	((CComboBox*)GetDlgItem(IDC_TESTSET))->SetCurSel(1);

	((CComboBox*)GetDlgItem(IDC_TESTSET1))->AddString("N5182A");
	((CComboBox*)GetDlgItem(IDC_TESTSET1))->SetCurSel(0);
 
	SetDlgItemText(IDC_FILESEQPATH,theApp.m_strIniPath);
	SetDlgItemText(IDC_LOGPATH,theApp.m_LogPath);
	((CComboBox*)GetDlgItem(IDC_DIAGPORT))->SetCurSel(theApp.m_pConfigSetting->m_PhonePort-1);
	((CComboBox*)GetDlgItem(IDC_ATPORT))->SetCurSel(theApp.m_pConfigSetting->m_ATPort-1);
	((CComboBox*)GetDlgItem(IDC_WAITCOM))->SetCurSel(theApp.m_pConfigSetting->m_iRetryPhonePortTimes/2-1);
	iIndex=theApp.m_pConfigSetting->strGPIBAddr.Find("::");

	strDeviceAddr=theApp.m_pConfigSetting->strGPIBAddr.Mid(iIndex+2);
	((CComboBox*)GetDlgItem(IDC_GPIBADDR))->SetCurSel(atoi(strDeviceAddr)-1);

	strDeviceAddr=theApp.m_pConfigSetting->strGPIBAddr1.Mid(iIndex+2);
	((CComboBox*)GetDlgItem(IDC_GPIBADDR1))->SetCurSel(atoi(strDeviceAddr)-1);

    if(theApp.m_bIsDOSF)
		((CButton*)GetDlgItem(IDC_SFCTRL))->SetCheck(1);
	else
        ((CButton*)GetDlgItem(IDC_SFCTRL))->SetCheck(0);

	  if(theApp.m_bStopWhenFail)
		((CButton*)GetDlgItem(IDC_STOPFAIL))->SetCheck(1);
	else
        ((CButton*)GetDlgItem(IDC_STOPFAIL))->SetCheck(0);

	 

	  for(CStringVtrItr itrLoss=theApp.m_pConfigSetting->m_MapLossConfig.begin();itrLoss!=theApp.m_pConfigSetting->m_MapLossConfig.end();++itrLoss)
	{
		if(itrLoss->first=="BT")
		{ 
		    iIndex=0;
			for(CStringStringMapItr itrLoss2=itrLoss->second.begin();itrLoss2!=itrLoss->second.end() && iIndex<3;++itrLoss2,++iIndex)
			{
				SetDlgItemText(IDC_BTLOWCH+iIndex,itrLoss2->first);
				SetDlgItemText(IDC_BTLOWLOSS+iIndex,itrLoss2->second);
                
			}
			
		}

		if(itrLoss->first=="WLAN")
		{ 
		   iIndex=0;
			for(CStringStringMapItr itrLoss3=itrLoss->second.begin();itrLoss3!=itrLoss->second.end() && iIndex<3;++itrLoss3,++iIndex)
			{
				SetDlgItemText(IDC_WLLOWCH+iIndex,itrLoss3->first);
				SetDlgItemText(IDC_WLLOWLOSS+iIndex,itrLoss3->second);
                
			}
			
		}
        if(itrLoss->first=="DTV")
		{ 
		   iIndex=0;
			for(CStringStringMapItr itrLoss4=itrLoss->second.begin();itrLoss4!=itrLoss->second.end() && iIndex<3;++itrLoss4,++iIndex)
			{
				SetDlgItemText(IDC_DTVLOWCH+iIndex,itrLoss4->first);
				SetDlgItemText(IDC_DTVLOWLOSS+iIndex,itrLoss4->second);
                
			}
			
		}

        if(itrLoss->first=="GPS")
		{ 
				CStringStringMapItr itrLoss5=itrLoss->second.begin();
				SetDlgItemText(IDC_GPSLOWCH,itrLoss5->first);
				SetDlgItemText(IDC_GPSLOWLOSS,itrLoss5->second);
          
		}

	}
    
    ((CListBox*)GetDlgItem(IDC_PLALL))->ResetContent();
   ((CListBox*)GetDlgItem(IDC_PLEN))->ResetContent();
	  for(CStringItr itrProcessList=theApp.m_vProcessList.begin();itrProcessList!=theApp.m_vProcessList.end();++itrProcessList)
	  {
		  ((CListBox*)GetDlgItem(IDC_PLALL))->AddString(*itrProcessList);
	  }
	  ((CListBox*)GetDlgItem(IDC_PLALL))->SetCurSel(0);

	   for(CStringItr itrProcessListEN=theApp.m_vProcessListEnable.begin();itrProcessListEN!=theApp.m_vProcessListEnable.end();++itrProcessListEN)
	  {
		  ((CListBox*)GetDlgItem(IDC_PLEN))->AddString(*itrProcessListEN);
	  }
	   ((CListBox*)GetDlgItem(IDC_PLEN))->SetCurSel(((CListBox*)GetDlgItem(IDC_PLEN))->GetCount()-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CSetupDlg::OnBnClickedButton3()
{
	m_bChangeProcess=true;
	CString strLeftString;
	int iRightCurIndex;
	CString strMsg;
	m_listProcessAll.GetText(m_listProcessAll.GetCurSel(),strLeftString);
	if((m_listProcessEnable.FindString(0,strLeftString))!=-1)
	{
		  strMsg.Format("%s has already in right list box. Are you sure duplicate the process?",strLeftString);
		  if(MessageBox(strMsg,"Warning",MB_YESNO)==IDYES)
		  {
			 iRightCurIndex=m_listProcessEnable.GetCurSel();
			m_listProcessEnable.InsertString(iRightCurIndex+1,strLeftString);
			m_listProcessAll.SetCurSel(m_listProcessAll.GetCurSel()+1);
			m_listProcessEnable.SetCurSel(iRightCurIndex+1); 
		  }
	}
	else
	{   
		iRightCurIndex=m_listProcessEnable.GetCurSel();
		m_listProcessEnable.InsertString(iRightCurIndex+1,strLeftString);
		m_listProcessAll.SetCurSel(m_listProcessAll.GetCurSel()+1);
		m_listProcessEnable.SetCurSel(iRightCurIndex+1);
	}
}

void CSetupDlg::OnBnClickedButton7()
{
	m_bChangeProcess=true;
	int iCurrentIndex=m_listProcessEnable.GetCurSel();
	m_listProcessEnable.DeleteString(iCurrentIndex);
	if(iCurrentIndex!=m_listProcessEnable.GetCount())
	 m_listProcessEnable.SetCurSel(iCurrentIndex);
	else
		m_listProcessEnable.SetCurSel(0);
   
}

void CSetupDlg::OnBnClickedButton5()
{
	m_bChangeProcess=true;
	CString strCurr;
	int iCurrentIndex=m_listProcessEnable.GetCurSel();
	if(iCurrentIndex==-1)
		return ;
	m_listProcessEnable.GetText(iCurrentIndex,strCurr);
	if(iCurrentIndex!=0)
	{
	m_listProcessEnable.InsertString(iCurrentIndex-1,strCurr);
	m_listProcessEnable.DeleteString(iCurrentIndex+1);
	m_listProcessEnable.SetCurSel(iCurrentIndex-1);
	}
	



}

void CSetupDlg::OnBnClickedButton6()
{
	m_bChangeProcess=true;
	CString strCurr;
	int iCurrentIndex=m_listProcessEnable.GetCurSel();
	if(iCurrentIndex==-1)
		return ;
    m_listProcessEnable.GetText(iCurrentIndex,strCurr);
   if(iCurrentIndex!=m_listProcessEnable.GetCount()-1)
   {
	 m_listProcessEnable.DeleteString(iCurrentIndex);
     m_listProcessEnable.InsertString(iCurrentIndex+1,strCurr);
	 m_listProcessEnable.SetCurSel(iCurrentIndex+1);
   }

}

void CSetupDlg::OnBnClickedButton8()
{
	m_bChangeProcess=true;
	CString strCurr;
	int iCurrentIndex=m_listProcessEnable.GetCurSel();
	if(iCurrentIndex==-1)
		return ;
	 m_listProcessEnable.GetText(iCurrentIndex,strCurr);
    m_listProcessEnable.DeleteString(iCurrentIndex);
	m_listProcessEnable.InsertString(0,strCurr);
    m_listProcessEnable.SetCurSel(0);
  
}

void CSetupDlg::OnBnClickedButton9()
{
	m_bChangeProcess=true;
	CString strCurr;
	int iCurrentIndex=m_listProcessEnable.GetCurSel();
	if(iCurrentIndex==-1)
		return ;
	 m_listProcessEnable.GetText(iCurrentIndex,strCurr);
    m_listProcessEnable.DeleteString(iCurrentIndex);
	m_listProcessEnable.InsertString(m_listProcessEnable.GetCount(),strCurr);
	m_listProcessEnable.SetCurSel(m_listProcessEnable.GetCount()-1);
}

void CSetupDlg::OnBnClickedButton4()
{
	m_bChangeProcess=true;
	m_listProcessEnable.ResetContent();
}

void CSetupDlg::OnBnClickedButton10()
{
	m_bChangeProcess=false;
	m_listProcessEnable.ResetContent();

    for(CStringItr itrProcessListEN=theApp.m_vProcessListEnable.begin();itrProcessListEN!=theApp.m_vProcessListEnable.end();++itrProcessListEN)
	  {
		  ((CListBox*)GetDlgItem(IDC_PLEN))->AddString(*itrProcessListEN);
	  }

	m_listProcessEnable.SetCurSel(m_listProcessEnable.GetCount()-1);
	
}
