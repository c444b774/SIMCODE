// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimRFCaltestUI.h"
#include "BaseConfigPage.h"
#include "SimRFDlg.h"
#include  "PasswordDlg.h"
#include  "ItemDetail.h"

// CBaseConfigPage dialog


CBaseConfigPage::CBaseConfigPage(CWnd* pParent /*=NULL*/)
	: CPageInterface(CBaseConfigPage::IDD)
{

}

CBaseConfigPage::CBaseConfigPage(const CString & strPageName):CPageInterface(strPageName)
{

}

CBaseConfigPage::~CBaseConfigPage()
{
}

void CBaseConfigPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLALL, m_listProcessAll);
	DDX_Control(pDX, IDC_PLEN, m_listProcessEnable);
}


BEGIN_MESSAGE_MAP(CBaseConfigPage, CDialog)
	ON_BN_CLICKED(IDOK, &CBaseConfigPage::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CBaseConfigPage::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBaseConfigPage::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CBaseConfigPage::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CBaseConfigPage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CBaseConfigPage::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &CBaseConfigPage::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CBaseConfigPage::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CBaseConfigPage::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CBaseConfigPage::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, &CBaseConfigPage::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON10, &CBaseConfigPage::OnBnClickedButton10)
	ON_BN_CLICKED(IDSHOWDETAIL, &CBaseConfigPage::OnBnClickedShowdetail)

END_MESSAGE_MAP()


// CBaseConfigPage message handlers

void CBaseConfigPage::OnBnClickedOk()
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
	
     CString strDllPathName;
	 CString strDllLossFileName;
	 char szTemp[1024];
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
	
     
	::GetModuleFileName(NULL, szTemp, _MAX_PATH);

	  
	  strDllPathName.Format("%s",szTemp);
     strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));

	strDllPathName=strDllPathName+_T("\\SystemConfig\\SystemSetup.ini");
	
	if(fopen(strDllPathName,"r")==NULL)
	{
        CString strTemp=strDllPathName+_T("  not exist");
		AfxMessageBox(strTemp);
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

    GetDlgItemText(IDC_LOOPCOUNT,strTemp);
	 
   ::WritePrivateProfileString(_T("Settings"),_T("LoopCount"),strTemp,strDllPathName);

    GetDlgItemText(IDC_WAITCOM,strTemp);
	strTemp=strTemp.Left(strTemp.GetLength()-2);
   ::WritePrivateProfileString(_T("Settings"),_T("PhoneOpenPortRetryTime"),strTemp,strDllPathName);

      GetDlgItemText(IDC_TESTSET,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("TesterDeviceCommon"),strTemp,strDllPathName);

    GetDlgItemText(IDC_TESTSET1,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("TesterDevice1"),strTemp,strDllPathName);

      GetDlgItemText(IDC_PLY,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("PowerSupplyCommon"),strTemp,strDllPathName);

    GetDlgItemText(IDC_PLY1,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("PowerSupply1"),strTemp,strDllPathName);


      GetDlgItemText(IDC_FREQMEAS,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("FreqMeasDevice"),strTemp,strDllPathName);

    GetDlgItemText(IDC_MULMEAS,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("MulMeasDevice"),strTemp,strDllPathName);


      GetDlgItemText(IDC_GPIBADDR,strTemp);
   
    ::GetPrivateProfileString(_T("Settings"),_T("Device_Addr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    CString str=_tKeyValue;  
	int iIndex=str.Find("::");
	CString str1=str.Left(iIndex+2);
	int iIndex2=str.Find("::",iIndex+1);
	CString str2=NULL;
	
	if (iIndex2>-1)
	{
		iIndex=str.GetLength() - str.Find("::",iIndex+1);
		str2=str.Right(iIndex);
	}

	
    str=str1+strTemp+str2;
   ::WritePrivateProfileString(_T("Settings"),_T("Device_Addr"),str,strDllPathName);

     GetDlgItemText(IDC_GPIBADDR1,strTemp);
   
    ::GetPrivateProfileString(_T("Settings"),_T("Device_Addr1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    str=_tKeyValue;   
	iIndex=str.Find("::");
	str=str.Left(iIndex+2);
    str+=strTemp;
   ::WritePrivateProfileString(_T("Settings"),_T("Device_Addr1"),str,strDllPathName);

      GetDlgItemText(IDC_GPIBADDRPLY,strTemp);
   
    ::GetPrivateProfileString(_T("Settings"),_T("Device_AddrPly"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    str=_tKeyValue;   
	iIndex=str.Find("::");
	str=str.Left(iIndex+2);
    str+=strTemp;
   ::WritePrivateProfileString(_T("Settings"),_T("Device_AddrPly"),str,strDllPathName);

     GetDlgItemText(IDC_GPIBADDRPLY1,strTemp);
   
    ::GetPrivateProfileString(_T("Settings"),_T("Device_AddrPly1"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    str=_tKeyValue;   
	iIndex=str.Find("::");
	str=str.Left(iIndex+2);
    str+=strTemp;
   ::WritePrivateProfileString(_T("Settings"),_T("Device_AddrPly1"),str,strDllPathName);


     GetDlgItemText(IDC_FREQADDR,strTemp);
   
    ::GetPrivateProfileString(_T("Settings"),_T("FreqMeasAddr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
     str=_tKeyValue;   
    iIndex=str.Find("::");
	str=str.Left(iIndex+2);
    str+=strTemp;
   ::WritePrivateProfileString(_T("Settings"),_T("FreqMeasAddr"),str,strDllPathName);

    GetDlgItemText(IDC_MULMEASADDR,strTemp);
   
    ::GetPrivateProfileString(_T("Settings"),_T("MulMeasAddr"),NULL,_tKeyValue,sizeof(_tKeyValue),strDllPathName);
    str=_tKeyValue;   
	 iIndex=str.Find("::");
	str=str.Left(iIndex+2);
    str+=strTemp;
   ::WritePrivateProfileString(_T("Settings"),_T("MulMeasAddr"),str,strDllPathName);


     GetDlgItemText(IDC_PLYPORT,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("PowerSupplyPort"),strTemp,strDllPathName);

      GetDlgItemText(IDC_PLYPORT1,strTemp);
   
   ::WritePrivateProfileString(_T("Settings"),_T("PowerSupply1Port"),strTemp,strDllPathName);



    
   int iCheck=((CButton*)GetDlgItem(IDC_SFCTRL))->GetCheck();
   ::WritePrivateProfileString(_T("Settings"),_T("IsDoSF"),CStr::IntToStr(iCheck),strDllPathName);

      iCheck=((CButton*)GetDlgItem(IDC_DB))->GetCheck();
   ::WritePrivateProfileString(_T("Settings"),_T("IsDoDB"),CStr::IntToStr(iCheck),strDllPathName);
    
   iCheck=((CButton*)GetDlgItem(IDC_STOPFAIL))->GetCheck();

   ::WritePrivateProfileString(_T("Settings"),_T("StopWhenFail"),CStr::IntToStr(iCheck),strDllPathName);

    iCheck=((CButton*)GetDlgItem(IDC_RUNSN))->GetCheck();

   ::WritePrivateProfileString(_T("Settings"),_T("RunAfterSN"),CStr::IntToStr(iCheck),strDllPathName);

   
   
       
		  theApp.m_vProcessListEnable.clear();
		  for(int i=0;i<m_listProcessEnable.GetCount();++i)
		  {
			  m_listProcessEnable.GetText(i,strTemp);
			  theApp.m_vProcessListEnable.push_back(strTemp);
		  }
     if(m_bChangeProcess)
     theApp.UpdateXMLProcessList();

	 theApp.ParseSystemIni();
	 theApp.MainPageLoadIniUpdateUI();

	 LRESULT lr;
	((CTabCtrl*)GetParent())->SetCurSel(0);
	 ((CSimRFDlg*)AfxGetMainWnd())->OnTcnSelchangeTab4(0,&lr);
     
}

void CBaseConfigPage::OnBnClickedButton1()
{ 
	CString strPath;
	CString strDllPathName;
	char initialdir[MAX_PATH];
	::GetModuleFileName(NULL,initialdir,MAX_PATH);	
	strDllPathName.Format("%s",initialdir);
	strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')))+"\\SetupINI\\Conductor";
	
  CFileDialog dlgSeq(true,"*.ini",NULL,0 ,"INI/XML Files (*.ini;*.xml)|*.xml|");
  dlgSeq.m_pOFN->lpstrInitialDir=strDllPathName;
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

void CBaseConfigPage::OnBnClickedButton2()
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
  strSelectDir.TrimRight('\\');
  SetDlgItemText(IDC_LOGPATH,strSelectDir);
}
void CBaseConfigPage::Refresh()
{
  theApp.ParseSystemIni();
     CString strTemp;
	CString strDeviceAddr;
	CStringStringMapItr itrLossFind;
	int iIndex;

    m_bChangeProcess=false;

	
	iIndex=((CComboBox*)GetDlgItem(IDC_TESTSET))->FindString(0,theApp.m_pConfigSetting->strTestDevceName);

	((CComboBox*)GetDlgItem(IDC_TESTSET))->SetCurSel(iIndex);


     iIndex=((CComboBox*)GetDlgItem(IDC_TESTSET1))->FindString(0,theApp.m_pConfigSetting->strTestDevceName1);
     ((CComboBox*)GetDlgItem(IDC_TESTSET1))->SetCurSel(iIndex);

	 iIndex=((CComboBox*)GetDlgItem(IDC_PLY))->FindString(0,theApp.m_pConfigSetting->strPowerSupplyName);

	((CComboBox*)GetDlgItem(IDC_PLY))->SetCurSel(iIndex);

	 iIndex=((CComboBox*)GetDlgItem(IDC_PLY1))->FindString(0,theApp.m_pConfigSetting->strPowerSupplyName1);

	((CComboBox*)GetDlgItem(IDC_PLY1))->SetCurSel(iIndex);

	 iIndex=((CComboBox*)GetDlgItem(IDC_FREQMEAS))->FindString(0,theApp.m_pConfigSetting->strFreqMeasName);

	((CComboBox*)GetDlgItem(IDC_FREQMEAS))->SetCurSel(iIndex);

	 iIndex=((CComboBox*)GetDlgItem(IDC_MULMEAS))->FindString(0,theApp.m_pConfigSetting->strMulMeasName);

	((CComboBox*)GetDlgItem(IDC_MULMEAS))->SetCurSel(iIndex);



	
	SetDlgItemText(IDC_FILESEQPATH,theApp.m_strIniPath);
	SetDlgItemText(IDC_LOGPATH,theApp.m_LogPath);
	((CComboBox*)GetDlgItem(IDC_DIAGPORT))->SetCurSel(theApp.m_pConfigSetting->m_PhonePort);
	((CComboBox*)GetDlgItem(IDC_ATPORT))->SetCurSel(theApp.m_pConfigSetting->m_ATPort-1);

	((CComboBox*)GetDlgItem(IDC_PLYPORT))->SetCurSel(theApp.m_pConfigSetting->m_iPlyPort-1);
    ((CComboBox*)GetDlgItem(IDC_PLYPORT1))->SetCurSel(theApp.m_pConfigSetting->m_iPly1Port-1);


	((CComboBox*)GetDlgItem(IDC_WAITCOM))->SetCurSel(theApp.m_pConfigSetting->m_iRetryPhonePortTimes/2-1);
	((CComboBox*)GetDlgItem(IDC_LOOPCOUNT))->SetCurSel(theApp.m_iLoopCount-1);
	 iIndex=theApp.m_pConfigSetting->strGPIBAddr.Find("::");

	strDeviceAddr=theApp.m_pConfigSetting->strGPIBAddr.Mid(iIndex+2);
	((CComboBox*)GetDlgItem(IDC_GPIBADDR))->SetCurSel(atoi(strDeviceAddr)-1);

	strDeviceAddr=theApp.m_pConfigSetting->strGPIBAddr1.Mid(iIndex+2);
	((CComboBox*)GetDlgItem(IDC_GPIBADDR1))->SetCurSel(atoi(strDeviceAddr)-1);

    strDeviceAddr=theApp.m_pConfigSetting->strGPIBAddrPLY.Mid(iIndex+2);
	((CComboBox*)GetDlgItem(IDC_GPIBADDRPLY))->SetCurSel(atoi(strDeviceAddr)-1);

	strDeviceAddr=theApp.m_pConfigSetting->strGPIBAddrPLY1.Mid(iIndex+2);
	((CComboBox*)GetDlgItem(IDC_GPIBADDRPLY1))->SetCurSel(atoi(strDeviceAddr)-1);

	strDeviceAddr=theApp.m_pConfigSetting->strFreqMeasAddr.Mid(iIndex+2);
	((CComboBox*)GetDlgItem(IDC_FREQADDR))->SetCurSel(atoi(strDeviceAddr)-1);

	strDeviceAddr=theApp.m_pConfigSetting->strMulMeasAddr.Mid(iIndex+2);
	((CComboBox*)GetDlgItem(IDC_MULMEASADDR))->SetCurSel(atoi(strDeviceAddr)-1);

    if(theApp.m_bIsDOSF)
		((CButton*)GetDlgItem(IDC_SFCTRL))->SetCheck(1);
	else
        ((CButton*)GetDlgItem(IDC_SFCTRL))->SetCheck(0);

	  if(theApp.m_bIsDataBase)
		((CButton*)GetDlgItem(IDC_DB))->SetCheck(1);
	else
        ((CButton*)GetDlgItem(IDC_DB))->SetCheck(0);

	  if(theApp.m_bStopWhenFail)
		((CButton*)GetDlgItem(IDC_STOPFAIL))->SetCheck(1);
	else
        ((CButton*)GetDlgItem(IDC_STOPFAIL))->SetCheck(0);

	   if(theApp.m_bRunAfterSN)
		((CButton*)GetDlgItem(IDC_RUNSN))->SetCheck(1);
	else
        ((CButton*)GetDlgItem(IDC_RUNSN))->SetCheck(0);

	 

	  
    
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
BOOL CBaseConfigPage::OnInitDialog()
{
	CDialog::OnInitDialog();
	 CString strTemp;
	//Refresh();
	((CComboBox*)GetDlgItem(IDC_LOOPCOUNT))->ResetContent();
    ((CComboBox*)GetDlgItem(IDC_DIAGPORT))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_ATPORT))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_GPIBADDRPLY))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_GPIBADDRPLY1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_GPIBADDR))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_GPIBADDR1))->ResetContent();
    ((CComboBox*)GetDlgItem(IDC_WAITCOM))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_TESTSET))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_TESTSET1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_PLY))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_PLY1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_PLYPORT))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_PLYPORT1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_FREQADDR))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_MULMEASADDR))->ResetContent();
    for(int i=1;i<3;++i)
	{
     strTemp.Format("%d",i);
    ((CComboBox*)GetDlgItem(IDC_PLYPORT))->AddString(strTemp);
	((CComboBox*)GetDlgItem(IDC_PLYPORT1))->AddString(strTemp);
	}
	for(int i=0;i<100;i++)
	{	
		HKEY hKEY;

		LPCTSTR data_Set="HARDWARE\\DEVICEMAP\\SERIALCOMM";
		long ret=::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set,0,KEY_READ,&hKEY);
		if(ret!=ERROR_SUCCESS)
		{
			::RegCloseKey(hKEY);
			break;
		}

		LPBYTE portGet=new BYTE[16];
		DWORD type=REG_SZ;
		DWORD cbData_1=16;

		strTemp.Format("\\Device\\QCUSB_COM%d_1",i);
		ret=::RegQueryValueEx(hKEY,strTemp,NULL,&type,portGet,&cbData_1);
		if(ret==ERROR_SUCCESS)
		{
			strTemp=portGet;
			((CComboBox*)GetDlgItem(IDC_DIAGPORT))->SetCurSel(i);
		}

		strTemp.Format("\\Device\\QCUSB_COM%d_2",i);
		ret=::RegQueryValueEx(hKEY,strTemp,NULL,&type,portGet,&cbData_1);
		if(ret==ERROR_SUCCESS)
		{
			strTemp=portGet;
			((CComboBox*)GetDlgItem(IDC_ATPORT))->SetCurSel(i);
		}
	}
	for(int i=0;i<100;i++)
	{
		strTemp.Format("COM%d",i);
		((CComboBox*)GetDlgItem(IDC_DIAGPORT))->AddString(strTemp);
		
	}
	for(int i=1;i<100;i++)
	{
		strTemp.Format("COM%d",i);
		((CComboBox*)GetDlgItem(IDC_ATPORT))->AddString(strTemp);
		strTemp.Format("%d",i);
		((CComboBox*)GetDlgItem(IDC_GPIBADDR))->AddString(strTemp);
		((CComboBox*)GetDlgItem(IDC_LOOPCOUNT))->AddString(strTemp);
		((CComboBox*)GetDlgItem(IDC_GPIBADDR1))->AddString(strTemp);
		((CComboBox*)GetDlgItem(IDC_GPIBADDRPLY))->AddString(strTemp);
		((CComboBox*)GetDlgItem(IDC_GPIBADDRPLY1))->AddString(strTemp);
		((CComboBox*)GetDlgItem(IDC_FREQADDR))->AddString(strTemp);
		((CComboBox*)GetDlgItem(IDC_MULMEASADDR))->AddString(strTemp);

	}
    
	 for(int i=2;i<100;i+=2)
	{
	strTemp.Format("%d s",i);
	((CComboBox*)GetDlgItem(IDC_WAITCOM))->AddString(strTemp);
	}

	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("dummy");
	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("CMW500");
	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("MT8820");
	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("A8960");
	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("CMU200");
	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("N5182A");
	((CComboBox*)GetDlgItem(IDC_TESTSET))->AddString("SP6010");

    ((CComboBox*)GetDlgItem(IDC_TESTSET1))->AddString("dummy");
	((CComboBox*)GetDlgItem(IDC_TESTSET1))->AddString("CMW500");
	((CComboBox*)GetDlgItem(IDC_TESTSET1))->AddString("MT8820");
	((CComboBox*)GetDlgItem(IDC_TESTSET1))->AddString("A8960");
	((CComboBox*)GetDlgItem(IDC_TESTSET1))->AddString("CMU200");
	((CComboBox*)GetDlgItem(IDC_TESTSET1))->AddString("N5182A");
	((CComboBox*)GetDlgItem(IDC_TESTSET1))->AddString("SP6010");


	((CComboBox*)GetDlgItem(IDC_PLY))->AddString("dummy");
	((CComboBox*)GetDlgItem(IDC_PLY))->AddString("GeneralPly");
	((CComboBox*)GetDlgItem(IDC_PLY))->AddString("Kethely2306");

	((CComboBox*)GetDlgItem(IDC_PLY1))->AddString("dummy");
	((CComboBox*)GetDlgItem(IDC_PLY1))->AddString("GeneralPly");
	((CComboBox*)GetDlgItem(IDC_PLY1))->AddString("Kethely2306");

	((CComboBox*)GetDlgItem(IDC_FREQMEAS))->AddString("Cymometer");
	((CComboBox*)GetDlgItem(IDC_FREQMEAS))->AddString("dummy");

	((CComboBox*)GetDlgItem(IDC_MULMEAS))->AddString("GeneralMul");
	((CComboBox*)GetDlgItem(IDC_MULMEAS))->AddString("dummy");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseConfigPage::OnBnClickedCancel()
{
	LRESULT lr;
	((CTabCtrl*)GetParent())->SetCurSel(0);
	 ((CSimRFDlg*)AfxGetMainWnd())->OnTcnSelchangeTab4(0,&lr);
}

void CBaseConfigPage::OnBnClickedButton3()
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

void CBaseConfigPage::OnBnClickedButton7()
{
	m_bChangeProcess=true;
	int iCurrentIndex=m_listProcessEnable.GetCurSel();
	m_listProcessEnable.DeleteString(iCurrentIndex);
	if(iCurrentIndex!=m_listProcessEnable.GetCount())
	 m_listProcessEnable.SetCurSel(iCurrentIndex);
	else
		m_listProcessEnable.SetCurSel(0);
   
}

void CBaseConfigPage::OnBnClickedButton5()
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

void CBaseConfigPage::OnBnClickedButton6()
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

void CBaseConfigPage::OnBnClickedButton8()
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

void CBaseConfigPage::OnBnClickedButton9()
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

void CBaseConfigPage::OnBnClickedButton4()
{
	m_bChangeProcess=true;
	m_listProcessEnable.ResetContent();
}

void CBaseConfigPage::OnBnClickedButton10()
{
	m_bChangeProcess=false;
	m_listProcessEnable.ResetContent();

    for(CStringItr itrProcessListEN=theApp.m_vProcessListEnable.begin();itrProcessListEN!=theApp.m_vProcessListEnable.end();++itrProcessListEN)
	  {
		  ((CListBox*)GetDlgItem(IDC_PLEN))->AddString(*itrProcessListEN);
	  }

	m_listProcessEnable.SetCurSel(m_listProcessEnable.GetCount()-1);
	
}

void CBaseConfigPage::OnBnClickedShowdetail()
{
	int iCurrIndex=m_listProcessEnable.GetCurSel();
	CString strItemname;
	m_listProcessEnable.GetText(iCurrIndex,strItemname);

    CStringPairVtr mapDetails;
    theApp.GetMapFromNodeName(strItemname,"//Configurations/ProcessObjectSet",mapDetails);
    
   
	CItemDetail dlg;
	dlg.SetDataMap(mapDetails);
    dlg.SetItemString(strItemname);
	dlg.DoModal();


	return;
    
}


