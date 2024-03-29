// SimRFCaltestUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimRFCaltestUI.h"
#include "MainPage.h"
#include "SimRFDlg.h"

const COLORREF MSG_LOW_COLOR     = RGB(0, 0, 0);
const COLORREF MSG_MEDIUM_COLOR	 = RGB(0, 128, 64);
const COLORREF MSG_HIGH_COLOR	 = RGB(64, 0, 128);
const COLORREF MSG_ERROR_COLOR	 = RGB(128, 0, 0);
const COLORREF MSG_FATAL_COLOR	 = RGB(250, 0, 0);
const COLORREF MSG_WARNING_COLOR = RGB(239, 145, 226);
const COLORREF MSG_DROP_COLOR	 = RGB(192, 192, 192);
const COLORREF LIGHT_GRAY_COLOR  = RGB(224, 224, 224);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif






CMainPage::CMainPage(CWnd* pParent /*=NULL*/)
	: CPageInterface(CMainPage::IDD)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pLogFile=NULL;
	
	m_hSFDll=0;
	m_pFnCheckSNRouting=0;
    m_pFnUpdateSNRouting=0;
}
 CMainPage::~CMainPage()
 {
	 if(m_hSFDll!=0)
	 {
		 ::FreeLibrary(m_hSFDll);
		   m_hSFDll=0;

	 }
 }

void CMainPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO1, m_ComProcessLIst);
	DDX_Control(pDX, IDC_LIST1, m_ItemListBox);
	DDX_Control(pDX, IDC_LIST3, m_TraceLogListCtl);
	DDX_Control(pDX, IDC_LIST2, m_FacLogCtl);
	DDX_Control(pDX, IDC_PROGRESS2, m_MainProcessCtrl);
	
}

BEGIN_MESSAGE_MAP(CMainPage, CPageInterface)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRD_CALTEST_FINISH, OnCalTestThreadFinish)
	ON_MESSAGE(WM_TRD_CALTEST_PROGRESS_PROC, OnCalTestThreadProcProgress)
	ON_MESSAGE(WM_TRD_CALTEST_PostFllg_PROC, OnCalTestPostFlagProgress)
	ON_MESSAGE(WM_TRD_CALTEST_UpdateSN_PROC, OnCalTestThreadUpdateSn)
	ON_MESSAGE(WM_UPDATEXMLLOSS, OnUpdateXMLLoss)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainPage::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_STOP, &CSimRFCaltestUIDlg::OnBnClickedStop)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CMainPage::OnLvnItemchangedList3)
	ON_BN_CLICKED(IDC_CONFIG, &CMainPage::OnBnClickedConfig)
	ON_STN_CLICKED(IDC_Title, &CMainPage::OnStnClickedTitle)
	ON_BN_CLICKED(IDC_CHECK1, &CMainPage::OnBnClickedCheck1)
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST2, &CMainPage::OnNMCustomdrawList2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, &CMainPage::OnLvnColumnclickList2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK2, &CMainPage::OnBnClickedCheck2)

	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_SNEDIT, &CMainPage::OnEnChangeSnedit)
END_MESSAGE_MAP()


// CSimRFCaltestUIDlg message handlers

BOOL CMainPage::OnInitDialog()
{
	if (!CPropertyPage::OnInitDialog())
		return FALSE;
	





	
	m_MainProcessCtrl.SetRange(0,10);
	m_MainProcessCtrl.SetStep(1);
	//m_MainProcessCtrl.SetBkColor(RGB(255,255,255));
	m_MainProcessCtrl.SetBarColor(RGB(0,0,255));

	 CBitmap bBitmap;
	 bBitmap.LoadBitmap(IDB_BITMAP1);
     

	 ((CStatic*)GetDlgItem(IDC_PICMAIN))->SetBitmap(static_cast<HBITMAP>(bBitmap.Detach()));
	if(theApp.m_bEnableTraceLog)
	{
     m_TraceLogListCtl.ShowWindow(true);
	 ((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(1);
	 m_MainProcessCtrl.ShowWindow(false);
	 GetDlgItem(IDC_PRONAME)->ShowWindow(false);
	 GetDlgItem(IDC_PICMAIN)->ShowWindow(false);
	 GetDlgItem(IDC_PASSFAILBIG)->ShowWindow(false);
	 GetDlgItem(IDC_LIST2)->ShowWindow(true);
	}
	else
	{
     m_TraceLogListCtl.ShowWindow(false);
	 ((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(0);
	  m_MainProcessCtrl.ShowWindow(true);
	 GetDlgItem(IDC_PRONAME)->ShowWindow(true);
	 GetDlgItem(IDC_PICMAIN)->ShowWindow(true);
	 GetDlgItem(IDC_PASSFAILBIG)->ShowWindow(true);
	 GetDlgItem(IDC_LIST2)->ShowWindow(false);
	

	}
    m_font=new CFont();

	//m_strTitle="SIM_Auto_TESTTOOL V"+theApp.m_strToolVer;
	m_strTitle=theApp.m_pConfigSetting->strProjectName;
	LOGFONT logfont;
	memset(&logfont,0,sizeof(logfont));
	logfont.lfHeight=20;
	logfont.lfWidth=10;
	logfont.lfWeight=700;
	
	m_font->CreateFontIndirect(&logfont);
    

	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
   
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	memset(&logfont,0,sizeof(logfont));
	logfont.lfHeight=150;
	logfont.lfWidth=75;
	logfont.lfWeight=7000;
	fPFFont.CreateFontIndirect(&logfont);

	GetDlgItem(IDC_PASSFAILBIG)->SetFont(&fPFFont);
	GetDlgItem(IDC_Title)->SetFont(m_font);
	GetDlgItem(IDC_SNEDIT)->SetFont(m_font);
	((CEdit*)GetDlgItem(IDC_SNEDIT))->LimitText(18);

	// TODO: Add extra initialization here
	m_iCtlStatus=-1;
	
	theApp.m_pConfigSetting->m_hMessageHandlingWnd=GetSafeHwnd();
	
    int iColsWidth[12] = {72, 50, 60, 50, 37, 50, 50, 70, 35, 36, 45, 100};
	int iColsWidthTrace[6] = {90, 80, 80, 50, 60, 120};
	m_FacLogCtl.InsertColumn(0, _T("ItemCode"), LVCFMT_RIGHT, iColsWidth[1]);
	m_FacLogCtl.InsertColumn(1, _T("Band"), LVCFMT_LEFT, iColsWidth[2]);
	m_FacLogCtl.InsertColumn(2, _T("Channel"), LVCFMT_LEFT, iColsWidth[3]);
	m_FacLogCtl.InsertColumn(3, _T("ErrorCode"), LVCFMT_RIGHT, iColsWidth[4]);
	m_FacLogCtl.InsertColumn(4, _T("UpperBound"), LVCFMT_RIGHT, iColsWidth[5]);
	m_FacLogCtl.InsertColumn(5, _T("LowerBound"), LVCFMT_RIGHT, iColsWidth[6]);
	m_FacLogCtl.InsertColumn(6, _T("EvaluatedValue"), LVCFMT_RIGHT, iColsWidth[7]);
	m_FacLogCtl.InsertColumn(7, _T("Unit"), LVCFMT_RIGHT, iColsWidth[8]);
	m_FacLogCtl.InsertColumn(8, _T("Pass/Fail"), LVCFMT_CENTER, iColsWidth[9]);
	m_FacLogCtl.InsertColumn(10, _T("Message"), LVCFMT_LEFT, iColsWidth[11]);
	m_FacLogCtl.InsertColumn(9, _T("Time"), LVCFMT_LEFT, iColsWidth[0]);
	m_FacLogCtl.SetColumnWidth(10, LVSCW_AUTOSIZE_USEHEADER);
	m_FacLogCtl.SetExtendedStyle(LVS_EX_FULLROWSELECT);


	
 	
	m_TraceLogListCtl.InsertColumn(0, _T("Time"), LVCFMT_LEFT, 1);
	m_TraceLogListCtl.InsertColumn(1, _T("Module"), LVCFMT_LEFT, 1);
	m_TraceLogListCtl.InsertColumn(2, _T("File"), LVCFMT_LEFT, 1);
	m_TraceLogListCtl.InsertColumn(3, _T("Line"), LVCFMT_LEFT, 1);
	m_TraceLogListCtl.InsertColumn(4, _T("Level"), LVCFMT_LEFT, 1);
	m_TraceLogListCtl.InsertColumn(5, _T("Message"), LVCFMT_LEFT, 100);
 
	m_TraceLogListCtl.SetExtendedStyle(LVS_EX_GRIDLINES| LVS_EX_FULLROWSELECT);
		m_TraceLogListCtl.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);

		
		LoadIniAndUpdateUi();

	if(theApp.m_bIsDOSF)
		{
		    if(m_hSFDll==0)
			   {
				   m_hSFDll=::LoadLibrary(theApp.m_pConfigSetting->dbConfig.strSFDllPath);
			   }

          m_pFnCheckSNRouting=(pFnCheckSNRouting)GetProcAddress(m_hSFDll,"CheckSNRouting");
          m_pFnUpdateSNRouting=(pFnUpdateSNRouting)GetProcAddress(m_hSFDll,"UpdateSNRouting"); 
		}


   
	
	m_FacLogCtl.GetWindowRect(&m_rectFacLog);
	GetDlgItem(IDC_BUTTON2)->GetWindowRect(&m_rectButton);
	return false;  // return TRUE  unless you set the focus to a control
}

void CMainPage::LoadIniAndUpdateUi()
{

	CString strTemp;
	CStringVtr strListVtr;
	CStringStringMapItr strstrMapitr;
	strTemp=theApp.strProjectName+"---"+theApp.strstationName;
	SetDlgItemText(IDC_Title,strTemp);
	m_ItemListBox.ResetContent();
	
	strstrMapitr=theApp.m_pConfigSetting->m_MapMainSetting.find("List");
	if(strstrMapitr!=theApp.m_pConfigSetting->m_MapMainSetting.end())
	{

		strTemp=strstrMapitr->second;
		CStr::ParseString(strTemp,_T(","),strListVtr);
		for(CStringItr itrList=strListVtr.begin();itrList!=strListVtr.end();++itrList)
		{
			m_ItemListBox.AddString(*itrList);
		}
		
     m_ItemListBox.SetCurSel(0);
	}

    
}

void CMainPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	
		CDialog::OnSysCommand(nID, lParam);
	
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainPage::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainPage::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMainPage::OnUpdateXMLLoss(WPARAM wParam, LPARAM lParam)
{
  

    s_UpdateXMLLossPara *s_Loss=(s_UpdateXMLLossPara*)lParam;
   
	if(!theApp.UpdateXMLloss(s_Loss->strXmlPath,s_Loss->mapFreq2Loss,s_Loss->strType,s_Loss->iIsUplink))
	{

		  TerminateThread(theApp.m_pCalTestWinThread->m_hThread,3);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
            
	}
	return 0;
}
LRESULT CMainPage::OnCalTestThreadUpdateSn(WPARAM wParam, LPARAM lParam)
{
	char *szSN=(char*)lParam;
	CString strSn=szSN;
	CString  strSequence;
	CString  strKeyID;
	int iQueryResult;
	SetDlgItemText(IDC_SNEDIT,strSn);
	theApp.m_strSN=strSn;
	if(theApp.m_bIsDOSF)
	{
		if(!CheckSF(strSn))
		{
             TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
		}
	}
    
	iQueryResult=theApp.QuerySingRecord("MainFT","sequence","SN",strSn,strSequence,"sequence",0);
	if(iQueryResult==2) //not find record
		strSequence="1";
	else if(iQueryResult==0)
	{
		
		strSequence=CStr::IntToStr(atoi(strSequence)+1);
	}
	else
	{
		   TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
	}
	

	if(!theApp.InSertRecord("MainFT","SN",strSn))
	{ 
		    TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
	}

		iQueryResult=theApp.QuerySingRecord("MainFT","KeyID","SN",strSn,strKeyID,"KeyID",0);
	if(iQueryResult!=0) //error
	{
		    TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
	}
	else
	{
		theApp.m_iKeyID=atoi(strKeyID);
		     
	}

	if(!theApp.UpdateSingRecord("MainFT","sequence",strSequence,"KeyID",strKeyID))
	{ 
		    TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
	}

	if(!theApp.UpdateSingRecord("MainFT","StationName",theApp.strstationName,"KeyID",strKeyID))
	{ 
		    TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
	}

	if(!theApp.UpdateSingRecord("MainFT","ProjectName", theApp.m_pConfigSetting->strProjectName,"KeyID",strKeyID))
	{ 
		    TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
	}

	if(!theApp.UpdateSingRecord("MainFT","Status","U" ,"KeyID",strKeyID))
	{ 
		    TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		    PostMessage(WM_TRD_CALTEST_FINISH);
			return -1;
	}

	return 0;
}
LRESULT CMainPage::OnCalTestPostFlagProgress(WPARAM wParam, LPARAM lParam)
{
    int *iPara=(int*)lParam;
	if(*iPara==1)
    theApp.m_bIsHasFailItem=true;
	else
    theApp.m_bIsHasFailItem=false;
	return 0;
	
}
LRESULT CMainPage::OnCalTestThreadProcProgress(WPARAM wParam, LPARAM lParam)
{
	int *iPara=(int*)lParam;

	
	m_ItemListBox.SetCurSel(*iPara);
	CString strPrcName=theApp.m_vProcessListEnable[*iPara];
	SetDlgItemText(IDC_PRONAME,strPrcName);

	
	return 0;
}
void CMainPage::AddFactoryLogEx(INT iProcessCode, LPCTSTR lpszBand, LPCTSTR lpszChannel, INT iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit, BOOL bPass, LPCTSTR lpszItemName,LPCTSTR lpszMsgFormat, ...)
{


	AddFactoryLog(iProcessCode,lpszBand,lpszChannel,iErrorCode,lpszUL,lpszDL,lpszMeasured,lpszUnit,bPass,lpszMsgFormat);

    CString strTempTable;
	CString strTempItem;
    CString strTableName;
	CString strFiledName;

	CString strCHName;
	CString strPCLName;
	CString strItemCode=CStr::IntToStr(iProcessCode);
	
    CString strFirst=strItemCode.Left(1);
	CString strCH=strItemCode.Mid(2,1);
	CString strPCL=strItemCode.Mid(3,1);

	
 
	if(strFirst=="4")
	{
	strTempTable="GFT_";

	}
	else if(strFirst=="6")
	{
	strTempTable="WFT_";
	}
	else if(strFirst=="9")
	{
     strTempTable="CFT_";
	}
	else
		return;

	
	strTableName=strTempTable+lpszBand;

   	if(theApp.m_bIsDataBase)
	{
		if(strstr(lpszItemName,"BANDHAND"))
		{
			if(!theApp.InSertRecord(strTableName,"KeyID",CStr::IntToStr(theApp.m_iKeyID)))
			{
				
					TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
					PostMessage(WM_TRD_CALTEST_FINISH);
					return;
			}

			if(!theApp.UpdateSingRecord(strTableName,"SN",theApp.m_strSN,"KeyID",CStr::IntToStr(theApp.m_iKeyID)))
			{
				
					TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
					PostMessage(WM_TRD_CALTEST_FINISH);
					return;
			}

			return ;

		}
	}

	if(strCH=="0")
		strCHName="CHLOW_";

	else if(strCH=="1")
	    strCHName="CHMID_";
	else 
		strCHName="CHHIGH_";

	if(strFirst=="4")
	{
		if(strPCL=="2")
			strPCLName="PCLLOW_";
		else if(strPCL=="1")
			strPCLName="PCLMID_";
		else 
			strPCLName="PCLHIGH_";
	}
	else
		strPCLName="";

	
   
	    

    

    strTempItem.Format("%s%s%s",strCHName,strPCLName,lpszItemName);

	if(theApp.m_bIsDataBase)
	{
	
	
			if(!theApp.UpdateSingRecord(strTableName,strTempItem,lpszMeasured,"KeyID",CStr::IntToStr(theApp.m_iKeyID)))
			{
				
					TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
					PostMessage(WM_TRD_CALTEST_FINISH);
					return;
			}
	
	}

    
   
	return ;

}
void CMainPage::AddFactoryLog(INT iProcessCode, LPCTSTR lpszBand, LPCTSTR lpszChannel, INT iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit, BOOL bPass, LPCTSTR lpszMsgFormat, ...)
{
 SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	double durationTime = (double)GetDurationTimeAndUpdateLatestClock()/CLOCKS_PER_SEC;
	CString strCurTime;
	strCurTime.Format(_T("%02d:%02d"), systemTime.wHour, systemTime.wMinute);
    char szMsg[9000];
	va_list args;
	va_start(args, lpszMsgFormat);
	CString strLogMsg;
	_vstprintf(szMsg, lpszMsgFormat, args);
	strLogMsg.Format("%s",szMsg);
	va_end(args);
 
	CString strDurationTime;
	strDurationTime.Format(_T("%.4lf"), durationTime);
 
	CString strProcessCode;
	strProcessCode.Format(_T("%d"), iProcessCode);
 
	CString strErrorCode;
	strErrorCode.Format(_T("%d"), iErrorCode);
   //if(m_FacLogCtl.GetItemCount() > 50)
		//m_FacLogCtl.DeleteItem(0);
	CString strPassFail;
	if (bPass)
		strPassFail = _T("Pass");
	else
		strPassFail = _T("Fail");
	if(!bPass || theApp.m_bEnableTraceLog)
	{
		int iIndex = m_FacLogCtl.GetItemCount();
		m_FacLogCtl.InsertItem(iIndex, strProcessCode);
		m_FacLogCtl.SetItemText(iIndex, 1, lpszBand);
		m_FacLogCtl.SetItemText(iIndex, 2, lpszChannel);
		m_FacLogCtl.SetItemText(iIndex, 3, strErrorCode);
		m_FacLogCtl.SetItemText(iIndex, 4, lpszUL);
		m_FacLogCtl.SetItemText(iIndex, 5, lpszDL);
		m_FacLogCtl.SetItemText(iIndex, 6, lpszMeasured);
		m_FacLogCtl.SetItemText(iIndex, 7, lpszUnit); 
		m_FacLogCtl.SetItemText(iIndex, 8, strPassFail);
		m_FacLogCtl.SetItemText(iIndex, 9, strCurTime);
		m_FacLogCtl.SetItemText(iIndex,10, strLogMsg);
		
 		int nCount = m_FacLogCtl.GetItemCount(); 
		if(nCount %16 == 0) 
			m_FacLogCtl.EnsureVisible(nCount-1,FALSE); 
		m_FacLogCtl.Invalidate(TRUE);
	}
 	
	ASSERT(theApp.m_pFactoryLog != NULL);
	if (theApp.m_pFactoryLog == NULL)
		return;

	_ftprintf(theApp.m_pFactoryLog, _T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n"),
			strCurTime,
			strProcessCode, 
			lpszBand,
			lpszChannel,
			strErrorCode,
			lpszUL,
			lpszDL,
			lpszMeasured,
			lpszUnit,
			strPassFail,
			strDurationTime,
			strLogMsg);

   
    
	fflush(theApp.m_pFactoryLog);
	return ;
}
void CMainPage::PostFinishThread(int iThreadExitCode)
{
	      int dwExitCode=iThreadExitCode;
		  if(dwExitCode==3 || theApp.m_bIsHasFailItem)
			{
				m_FacLogCtl.SetBkColor(BKCOLOR_FAIL);
				m_FacLogCtl.SetTextBkColor(BKCOLOR_FAIL);
				m_FacLogCtl.Invalidate(true);

			    SetDlgItemText(IDC_PASSFAIL,"FAIL");
				SetDlgItemText(IDC_PASSFAILBIG,"FAIL");
				GetDlgItem(IDC_PASSFAIL)->SetFont(m_font);
				ChangeStaticCtlColor(1);
				theApp.m_bIsPass=false;
				
			}
			else if(dwExitCode==0) 
			{
				m_FacLogCtl.SetBkColor(BKCOLOR_SUCCESS);
				m_FacLogCtl.SetTextBkColor(BKCOLOR_SUCCESS);
				m_FacLogCtl.Invalidate(true);
				//AfxMessageBox("PASS!");
				SetDlgItemText(IDC_PASSFAIL,"PASS");
				SetDlgItemText(IDC_PASSFAILBIG,"PASS");
				GetDlgItem(IDC_PASSFAIL)->SetFont(m_font);
				ChangeStaticCtlColor(0);
				theApp.m_bIsPass=true;
				
			}
			else if(dwExitCode==4)
			{
				m_FacLogCtl.SetBkColor(BKCOLOR_STOP);
				m_FacLogCtl.SetTextBkColor(BKCOLOR_STOP);
				m_FacLogCtl.Invalidate(true);
				
                theApp.m_bIsPass=false;
				
			}
			else if(dwExitCode==2)
			{
				m_FacLogCtl.SetBkColor(BKCOLOR_FAIL);
				m_FacLogCtl.SetTextBkColor(BKCOLOR_FAIL);
				m_FacLogCtl.Invalidate(true);
				//AfxMessageBox("FAIL!");
			    SetDlgItemText(IDC_PASSFAIL,"DB_Fail");
				SetDlgItemText(IDC_PASSFAILBIG,"DB_Fail");
				GetDlgItem(IDC_PASSFAIL)->SetFont(m_font);
				ChangeStaticCtlColor(1);
				theApp.m_bIsPass=false;	
			}
			

		 
	      if(theApp.m_bIsDOSF)
				{
					 if(!UpdateSF(theApp.m_strSN,1000,theApp.m_bIsPass))
						{
	
					       m_FacLogCtl.SetBkColor(BKCOLOR_FAIL);
							m_FacLogCtl.SetTextBkColor(BKCOLOR_FAIL);
							m_FacLogCtl.Invalidate(true);
							//AfxMessageBox("FAIL!");
							SetDlgItemText(IDC_PASSFAIL,"DB_Fail");
							SetDlgItemText(IDC_PASSFAILBIG,"DB_Fail");
							GetDlgItem(IDC_PASSFAIL)->SetFont(m_font);
							ChangeStaticCtlColor(1);
							theApp.m_bIsPass=false;	 

					}

				}

		   CString strPassFail;

				strPassFail=(theApp.m_bIsPass?"P":"F");

				if(theApp.m_bIsDataBase)
				{
					if(!theApp.UpdateSingRecord("MainFT","Status", strPassFail,"KeyID",CStr::IntToStr(theApp.m_iKeyID)))
					{ 
							m_FacLogCtl.SetTextBkColor(BKCOLOR_FAIL);
							m_FacLogCtl.Invalidate(true);
							//AfxMessageBox("FAIL!");
							SetDlgItemText(IDC_PASSFAIL,"DB_Fail");
							SetDlgItemText(IDC_PASSFAILBIG,"DB_Fail");
							GetDlgItem(IDC_PASSFAIL)->SetFont(m_font);
							ChangeStaticCtlColor(1);
							theApp.m_bIsPass=false;	 
					}
				}


	     SetDlgItemText(IDC_SNEDIT,"");
		 GetDlgItem(IDC_SNEDIT)->EnableWindow(true);
		 GetDlgItem(IDC_SNEDIT)->SetFocus();

		if(theApp.m_bIsDataBase)
        theApp.ExitDataBase();
        theApp.m_bIsrunning=false;
        theApp.ReleaseResource();
		CloseHandle(theApp.m_hCalTestThread);
        theApp.m_hCalTestThread=0;
}

LRESULT CMainPage::OnCalTestThreadFinish(WPARAM wParam, LPARAM lParam)
{
     
	         KillTimer(2);		 
			 m_MainProcessCtrl.SetPos(0);
			 DWORD dwWaitTime=2000;
			
			 DWORD dwExitCode;
			 CString strStopTime;
			 SYSTEMTIME  s_Tm;
			
			 int dwDureTime=(GetTickCount()-m_dwStartTime)/1000;  
             
             GetDlgItemText(IDC_SNEDIT,theApp.m_strSN);
			 
			if (::WaitForSingleObject(theApp.m_hCalTestThread, dwWaitTime) != WAIT_OBJECT_0)
		{
			   TerminateThread(theApp.m_hCalTestThread,1); 
			  
		}

			SetDlgItemText(IDC_TIMEELP,CStr::IntToStr(dwDureTime));
			GetDlgItem(IDC_TIMEELP)->SetFont(m_font);
			GetExitCodeThread(theApp.m_hCalTestThread, &dwExitCode);

			
		 
			GetDlgItem(IDC_BUTTON2)->SetWindowText("Start");
			AfxGetMainWnd()->GetDlgItem(IDC_TAB4)->EnableWindow(true);

			
		
         

				
			::GetLocalTime(&s_Tm);
				 strStopTime.Format("%d-%d-%d %d:%d:%d",s_Tm.wYear,s_Tm.wMonth,s_Tm.wDay,s_Tm.wHour,s_Tm.wMinute,s_Tm.wSecond);
				 CString strKeyID=CStr::IntToStr(theApp.m_iKeyID);
				
				 if(!theApp.UpdateSingRecord("MainFT","StopDate",strStopTime,"KeyID",strKeyID))
				{ 
					 PostFinishThread(2);
						return -1;
				}

               
       
		PostFinishThread(dwExitCode);

		
    

		theApp.UpdateLogFilePath(false);
	
        
		return 1;

}
void CMainPage::CreateLogFileAndCreateDir(LPCTSTR lpszLogFilePath)
{
	
		m_strLogFilePath = lpszLogFilePath;
		if (m_pLogFile != NULL)
		{
			fclose(m_pLogFile);
			m_pLogFile = NULL;
		}
		
 
		// Make sure first the directory the log file exists in is already created
		CString strLogDirPath = lpszLogFilePath;
		strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
 
		ForceCreateDirectory(strLogDirPath);
 
		// Create log file
		m_pLogFile = _tfopen(m_strLogFilePath, _T("a"));
		ASSERT(m_pLogFile != NULL);
		if (m_pLogFile == NULL) 
		{
			CString strErrMsg;
			strErrMsg.Format(_T("Create log failed - %s"), m_strLogFilePath);
			AfxMessageBox(strErrMsg);
		}
	
}
bool CMainPage::CheckSF(CString  strSN)
{
    char strConn[1024]; 
	char * returnResult; 
	CString strMsg;
	CString strPsd=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strPassword;
	CString strUID=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strUID;
	CString strCataLog=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strCataLog;
	CString strDataSrc=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strServerAddr;
	CString strStationID=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strStationID;
	CString strReturnOK=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strReturnOK;
    if(!m_pFnCheckSNRouting)
	{
		MessageBox("Not Load CheckSNRouting Function");
		return false;
	}
	sprintf(strConn,"Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%s;Data Source=%s",strPsd,strUID,strCataLog,strDataSrc);
	try
	{
		returnResult=m_pFnCheckSNRouting(strConn,(char*)strStationID.GetBuffer(),(char*)strSN.GetBuffer());
		
	}
	catch(...)
	{
       MessageBox("Flow Control server not connected ,check for the LAN connect!");
	   return false;
	}
	strStationID.ReleaseBuffer();
	strSN.ReleaseBuffer();
	if(!strcmp(returnResult,strReturnOK.GetBuffer()))  
	{
      strReturnOK.ReleaseBuffer();
	}
	else
	{
      strMsg.Format("SF Control Fail! ErrorCode=%s",returnResult);
	  MessageBox(strMsg);
	  strReturnOK.ReleaseBuffer();
	  return false;
	}
	

	return true;
}
bool  CMainPage::UpdateSF(CString strSN,int iErrorCode,bool bIsPass)
{
    char strConn[1024]; 
	char * returnResult;
	int iResult;
	CString strMsg;
	CString strPsd=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strPassword;
	CString strUID=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strUID;
	CString strCataLog=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strCataLog;
	CString strDataSrc=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strServerAddr;
	CString strStationID=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strStationID;
	CString strReturnOK=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strReturnOK;
	CString strFixID=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strFixID;
	CString strLineNum=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strLineNum;
	CString strCreator=theApp.m_pConfigSetting->dbConfig.s_SFSystemConfig.strCreator;

	if(bIsPass)
    iResult=0;
	else
    iResult=1;

    if(!m_pFnUpdateSNRouting)
	{
		MessageBox("Not Load UpdateSNRouting Function");
		return false;
	}

   sprintf(strConn,"Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%s;Data Source=%s",strPsd,strUID,strCataLog,strDataSrc);
   returnResult=m_pFnUpdateSNRouting(strConn,(char*)strStationID.GetBuffer(),(char*)strFixID.GetBuffer(),"1008",(char*)strLineNum.GetBuffer(),(char*)strSN.GetBuffer(),(char*)strCreator.GetBuffer(),iResult);
   strStationID.ReleaseBuffer();
	strSN.ReleaseBuffer();
	strFixID.ReleaseBuffer();
	strLineNum.ReleaseBuffer();
	strCreator.ReleaseBuffer();

  if(!strcmp(returnResult,strReturnOK.GetBuffer()))  
	{
      strReturnOK.ReleaseBuffer();
	}
	else
	{
      strMsg.Format("SF Control Fail! ErrorCode=%s",returnResult);
	  MessageBox(strMsg);
	  strReturnOK.ReleaseBuffer();
	  return false;
	}
	
	return true;
}
void CMainPage::ChangeLogFilePath(LPCTSTR lpszLogFilePath)
{
	if (m_strLogFilePath == lpszLogFilePath)
		return;
 
	BOOL bFileOpened = FALSE;
	if (m_pLogFile != NULL) {
		fclose(m_pLogFile);
		bFileOpened = TRUE;
	}
 
	if (_taccess(lpszLogFilePath, 0) == 0) {
		// append
		AppendFiles(lpszLogFilePath, m_strLogFilePath);
	}
	else {
		// copy
		CString strLogDirPath = lpszLogFilePath;
		strLogDirPath = strLogDirPath.Left(strLogDirPath.ReverseFind(_T('\\')));
 
		ForceCreateDirectory(strLogDirPath);
		CopyFile(m_strLogFilePath, lpszLogFilePath, FALSE);
	}
 
	// delete the original file and re-open the new file if necessary
	DeleteFile(m_strLogFilePath);
	m_strLogFilePath = lpszLogFilePath;
 
	if (bFileOpened) {
		m_pLogFile = _tfopen(m_strLogFilePath, _T("a"));
		ASSERT(m_pLogFile != NULL);
		if (m_pLogFile == NULL) {
			CString strErrMsg;
			strErrMsg.Format(_T("Change log file path failed - %s"), m_strLogFilePath);
			AfxMessageBox(strErrMsg);
		}
		fclose(m_pLogFile); 
	}
}
void CMainPage::AddTraceLog(LPCTSTR lpszModule, LPCSTR lpszSrcFile, UINT iSrcLine, EMsgLevel msgLevel, LPCTSTR lpszFormat, ...)
 {
   
   SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	char szMsg[9000];
	CString strCurTime;
	strCurTime.Format(_T("%02d:%02d"), systemTime.wHour, systemTime.wMinute);
    
	USES_CONVERSION;
 
	va_list args;
	va_start(args, lpszFormat);
	CString strLogMsg;
      
	_vstprintf(szMsg, lpszFormat, args);
	strLogMsg.Format("%s",szMsg);
	va_end(args);
    if( theApp.m_bEnableTraceLog)
	{
	   if(m_TraceLogListCtl.GetItemCount()>100)
		 m_TraceLogListCtl.DeleteItem(0);
	}
	
	CString strSrcFile = CA2T(lpszSrcFile);
	CString strSrcLine;
	strSrcLine.Format(_T("%3d"), iSrcLine);
     int iIndex = m_TraceLogListCtl.GetItemCount();
	  if( theApp.m_bEnableTraceLog)
	  {

		m_TraceLogListCtl.InsertItem(iIndex, strCurTime);
		m_TraceLogListCtl.SetItemText(iIndex, 1, lpszModule);
		m_TraceLogListCtl.SetItemText(iIndex, 2, PathFindFileName(strSrcFile));
		m_TraceLogListCtl.SetItemText(iIndex, 3, strSrcLine);
		m_TraceLogListCtl.SetItemText(iIndex, 5, strLogMsg);
	  }
 
	CString strLevel;
	DWORD dwItemData;
	switch(msgLevel) {
		case MSG_LOW:
			strLevel = _T("LOW");
		dwItemData = MSG_LOW_COLOR;
			break;
		case MSG_MID:
			strLevel = _T("MED");
		dwItemData = MSG_MEDIUM_COLOR;
			break;
		case MSG_HIGH:
			strLevel = _T("HIGH");
			dwItemData = MSG_HIGH_COLOR;
			break;
		case MSG_ERROR:
			strLevel = _T("ERROR");
		dwItemData = MSG_ERROR_COLOR;
			break;
		case MSG_FATAL:
			strLevel = _T("FATAL");
		dwItemData = MSG_FATAL_COLOR;
			break;
		case MSG_WARNING:
			strLevel = _T("WARNING");
		dwItemData = MSG_WARNING_COLOR;	
			break;
		default:
			ASSERT(0);
			strLevel = _T("???");
			dwItemData = MSG_DROP_COLOR;
			break;
	}
 

	 CString strPathname;
	 char szPathName[_MAX_PATH];
	  if( theApp.m_bEnableTraceLog)
	  {
		m_TraceLogListCtl.SetItemText(iIndex, 4, strLevel);
		m_TraceLogListCtl.SetItemData(iIndex, dwItemData);
		m_TraceLogListCtl.Invalidate(true);
		m_TraceLogListCtl.EnsureVisible(iIndex, FALSE);
	  }

	::GetModuleFileName(NULL, szPathName, _MAX_PATH);
	
	strPathname.Format("%s",szPathName);
		// Add to log file
		if (m_pLogFile == NULL)
		{
			m_strLogFilePath = strPathname + _T("\\") + DEFAULT_TOOLLOG_FILENAME;
			CreateLogFileAndCreateDir(m_strLogFilePath);
		}
 
		_ftprintf(m_pLogFile, _T("%s,%s,%s,%s,%s,%s\n"),
			strCurTime,
			lpszModule,
			PathFindFileName(strSrcFile),
			strSrcLine,
			strLevel,
			strLogMsg);
 
	
			fflush(m_pLogFile);

 }
void CMainPage::AddCommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage)
{
 

	ASSERT(theApp.m_pCommandLog != NULL);
	if (theApp.m_pCommandLog == NULL)
		return;

	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);

	_ftprintf(theApp.m_pCommandLog, _T("%02d:%02d:%03d\t%s\t%s\n"), systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds, lpszType, lpszMessage);
	fflush(theApp.m_pCommandLog);	
}





void CMainPage::OnBnClickedButton2()
{
	

			::SetTimer(m_hWnd,1,1000,NULL);
			::SetTimer(m_hWnd,2,100,NULL);

			
			char szLastErrorMsg[1024];
			CString strCaption;
			GetDlgItemText(IDC_BUTTON2,strCaption);
			SetDlgItemText(IDC_PASSFAIL,"Testing");
			SetDlgItemText(IDC_PASSFAILBIG,"Testing");
			ChangeStaticCtlColor(2);
			SetDlgItemText(IDC_TIMEELP,"");
			m_ckLatestClock=0;
			m_dwStartTime=GetTickCount();
			m_FacLogCtl.SetBkColor(RGB(255,255,255));
			m_FacLogCtl.SetTextBkColor(RGB(255,255,255));
			theApp.m_bIsHasFailItem=false;


			theApp.m_bIsFirstUpdateXMlLossUL=true;
			theApp.m_bIsFirstUpdateXMlLossDL=true;
			GetDlgItem(IDC_SNEDIT)->EnableWindow(false);
			GetDlgItemText(IDC_SNEDIT,theApp.m_pConfigSetting->strSN);


			if(strCaption==_T("Stop"))
			{
				
			  if(MessageBox("Are you sure you stop the Tool running?",NULL,MB_OKCANCEL)==IDOK)
			  {
				  GetDlgItem(IDC_PASSFAIL)->SetFont(m_font);
				  SetDlgItemText(IDC_PASSFAIL,"Stopped");
				  SetDlgItemText(IDC_PASSFAILBIG,"Stopped");
				  ChangeStaticCtlColor(2);
				  TerminateThread(theApp.m_pCalTestWinThread->m_hThread,4);
				  PostMessage(WM_TRD_CALTEST_FINISH);
			
				  return;
			  }
			}
			else
			{
				theApp.m_bIsrunning=true;
				m_TraceLogListCtl.DeleteAllItems();
			    
				m_FacLogCtl.DeleteAllItems();
				theApp.UpdateLogFilePath();

				if(theApp.m_bIsDataBase)
			{
				if(!theApp.InitDataBase(theApp.m_pConfigSetting->dbConfig.strDBDllPath))
				return;

				if(!theApp.m_pFuncOpenDatabase(theApp.m_pConfigSetting->dbConfig.s_DataBaseConfig.strDSN.GetBuffer(),theApp.m_pConfigSetting->dbConfig.s_DataBaseConfig.strUSER.GetBuffer(),theApp.m_pConfigSetting->dbConfig.s_DataBaseConfig.strPWD.GetBuffer()))

				{
					if(!theApp.m_pFuncGetLastErrorMsg(szLastErrorMsg,1024))
					{
						MessageBox("ErrorMsg Buffer not enough");
						return;
					}
					else
					{
						 MessageBox(szLastErrorMsg);
						 return;
					}
				}

				

				

			}

		   


				GetDlgItem(IDC_BUTTON2)->SetWindowText("Stop");
					

				theApp.m_pCalTestWinThread = AfxBeginThread(CalTestThreadProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
				::DuplicateHandle(GetCurrentProcess(), theApp.m_pCalTestWinThread->m_hThread, GetCurrentProcess(), &theApp.m_hCalTestThread, 0, FALSE, DUPLICATE_SAME_ACCESS);
				theApp.m_pCalTestWinThread->ResumeThread();
			}

}
int CMainPage::CalTestThreadProcImp()
{
         CString strTemp;
		 CString strDllPathName,strDllFileName;
		 char szTemp[_MAX_PATH];
	     int iLoopCount=theApp.m_iLoopCount;
         bool bIsShowLoop=false;
		 if(iLoopCount!=1)
			 bIsShowLoop=true;
		 FILETIME ftCreate, ftAccess, ftWrite;
		 SYSTEMTIME stLocal;
		 DWORD dw;
		 ::GetLocalTime(&stLocal);
		 HANDLE hfile;
		 ::GetModuleFileName(NULL, szTemp, _MAX_PATH);
		 strDllPathName.Format("%s",szTemp);
		 strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));
		 strDllFileName=strDllPathName+"\\SimRFCaltestdll.dll";	
		 hfile=CreateFile(strDllFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
		 if (hfile == INVALID_HANDLE_VALUE) 
		 { 
			 dw=GetLastError();
			
		 }

	
		 // Retrieve the file times for the file.
		 if (!GetFileTime(hfile, &ftCreate, &ftAccess, &ftWrite))
			 return FALSE;

		 CTime time1(ftCreate);
		 CTime time2(ftWrite);
		 CTime time3(stLocal);
		 CTimeSpan ts=time3-time2;
		 CTimeSpan ts1=time3-time1;

	/*	 if (ts1.GetTotalHours()>240||ts1.GetTotalHours()<0)
		 {
			 MessageBox("Load ddl fail!");
			 return FALSE;
		 }
		 else if (ts.GetTotalHours()>480||ts1.GetTotalHours()<0)
		 {
			 MessageBox("Load ddl fail!");
			 return FALSE;
		 }*/
	     
		do{

			    if(bIsShowLoop)
				{
					strTemp.Format("Left LoopCount=%d",iLoopCount);
					SetDlgItemText(IDC_LOOPCOUNTER,strTemp);
				}
			
			/*theApp.m_hRFCalTestDLL=::LoadLibrary(_T("SimRFCaltestdll.dll"));*/
			/*	TCHAR chCurDir[MAX_PATH] = {0};  
				GetCurrentDirectory(MAX_PATH, chCurDir);  
				SetCurrentDirectory(_T("E:\\test\\"));  */
				theApp.m_hRFCalTestDLL = ::LoadLibrary("E:\SIMCOM\SVNSIM\Output\bin\Debug\SimRFCaltestdll.dll");  
			//	SetCurrentDirectory(chCurDir);  

			if(theApp.m_hRFCalTestDLL==0)
			{
				DWORD dwerror=GetLastError();
				MessageBox("Load dll fail!");
				return 1;
			}
		    
			pfCreateRFCALTEST pFunc=(pfCreateRFCALTEST)GetProcAddress(theApp.m_hRFCalTestDLL,_T("CreateRFCALTEST"));
			if(pFunc==NULL)
			{
				MessageBox("Load function fail!");
				return 2;
			}

			if(!pFunc(&theApp.m_pRFCalTestProcessor))
			{
				MessageBox("Create Processor fail");
				return 3;
			}
	   


	
	   
			theApp.m_pRFCalTestProcessor->InitData(theApp.m_pConfigSetting);

			theApp.m_pRFCalTestProcessor->SetLoggerFunc(ToolFactoryLog, ToolTraceLog, ToolCommandLog,ToolFactoryLogEx);

			if(!theApp.m_pRFCalTestProcessor->StartProcess())
			{
				PostMessage(WM_TRD_CALTEST_FINISH);
				return 3;
			}
			theApp.ReleaseResource();
		}while(--iLoopCount>0);

		SetDlgItemText(IDC_LOOPCOUNTER,"");
		PostMessage(WM_TRD_CALTEST_FINISH);
	return 0;

}
 UINT CMainPage::CalTestThreadProc(LPVOID pPara)
 {
   CMainPage* dlg=(CMainPage*)pPara;
   return dlg->CalTestThreadProcImp();

 }



 void CMainPage::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
 {
	 LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	 // TODO: Add your control notification handler code here
	 *pResult = 0;
 }

 void CMainPage::OnBnClickedConfig()
 {
     
	



 }

 void CMainPage::OnStnClickedTitle()
 {
	 // TODO: Add your control notification handler code here
 }




 void CMainPage::OnBnClickedCheck1()
 {
     
	 if(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	 {
		 
		 GetDlgItem(IDC_CHECK2) ->EnableWindow(false);
		  m_MainProcessCtrl.ShowWindow(false);
		   GetDlgItem(IDC_PICMAIN)->ShowWindow(false);
		   GetDlgItem(IDC_PASSFAILBIG)->ShowWindow(false);
		   GetDlgItem(IDC_LIST2)->ShowWindow(true);
		GetDlgItem(IDC_PRONAME)->ShowWindow(false);
        RECT rectFacNew;
		RECT rectButtonNew;
		memcpy(&rectFacNew,&m_rectFacLog,sizeof(rectFacNew));
		memcpy(&rectButtonNew,&m_rectButton,sizeof(rectButtonNew));

		rectFacNew.top=m_rectFacLog.top-300;
		rectFacNew.bottom=m_rectFacLog.bottom-300;
		rectFacNew.left=m_rectFacLog.left-20;
		rectButtonNew.top=m_rectButton.top-300;
		rectButtonNew.bottom=m_rectButton.bottom-320;
		m_FacLogCtl.MoveWindow(&rectFacNew);
		GetDlgItem(IDC_BUTTON2)->MoveWindow(&rectButtonNew); 

		m_TraceLogListCtl.ShowWindow(false);
		m_ItemListBox.ShowWindow(false);
		GetDlgItem(IDC_GROUPTRACE)->ShowWindow(false);
		GetDlgItem(IDC_ITEMLIST)->ShowWindow(false);
		GetDlgItem(IDC_FACLOG)->ShowWindow(false);


		 int iBackSize=0;

		  ::SendMessage(AfxGetMainWnd()->m_hWnd,WM_RFDLG_SIZE,0,(LPARAM)(&iBackSize));
	
	 }
	 else
	 {
		 GetDlgItem(IDC_CHECK2) ->EnableWindow(true);
		  GetDlgItem(IDC_PICMAIN)->ShowWindow(true);
		  GetDlgItem(IDC_PASSFAILBIG)->ShowWindow(true);
		  GetDlgItem(IDC_LIST2)->ShowWindow(false);
        m_TraceLogListCtl.ShowWindow(true);
		m_MainProcessCtrl.ShowWindow(true);
		m_ItemListBox.ShowWindow(true);
		GetDlgItem(IDC_GROUPTRACE)->ShowWindow(true);
		GetDlgItem(IDC_ITEMLIST)->ShowWindow(true);
		GetDlgItem(IDC_FACLOG)->ShowWindow(true);
       //Bug ,But I do not know how to solve
		RECT rectFacNew;
		RECT rectButtonNew;
		memcpy(&rectFacNew,&m_rectFacLog,sizeof(rectFacNew));
		memcpy(&rectButtonNew,&m_rectButton,sizeof(rectButtonNew));
        rectFacNew.top=m_rectFacLog.top-50;
		rectFacNew.bottom=m_rectFacLog.bottom-50;
		m_FacLogCtl.MoveWindow(&rectFacNew);
		rectButtonNew.top=rectButtonNew.top-50;
		rectButtonNew.bottom=rectButtonNew.bottom-50;
		GetDlgItem(IDC_BUTTON2)->MoveWindow(&rectButtonNew); 

		 int iBackSize=1;

		  ::SendMessage(AfxGetMainWnd()->m_hWnd,WM_RFDLG_SIZE,0,(LPARAM)(&iBackSize));
		

	 }
 }

 void CMainPage::OnNMCustomdrawList2(NMHDR *pNMHDR, LRESULT *pResult)
 {
	 NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	 *pResult = CDRF_DODEFAULT;

	 if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )        
	 {        
		 *pResult = CDRF_NOTIFYITEMDRAW;  
	 } 
	 else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	 {
		 // *pResult = CDRF_NOTIFYSUBITEMDRAW;
		 //}
		 //else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
		 //{

		 COLORREF crTextBk;
		 int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);

		 CString strTemp = m_FacLogCtl.GetItemText(nItem,8);
		 strTemp.MakeUpper();
		 if (strTemp.Find("FAIL")!=-1)
		 {
			 crTextBk = BKCOLOR_FAIL;
			 pLVCD->clrTextBk = crTextBk;
		 }else if (strTemp.Find("PASS")!=-1)
		 {
			 crTextBk = BKCOLOR_SUCCESS;
			 pLVCD->clrTextBk = crTextBk;
		 }

		 for(int i=0;i <m_FacLogCtl.GetItemCount();i++) 
			 m_FacLogCtl.SetItemData(i,i);

		 *pResult = CDRF_DODEFAULT;
	 }
 }

 int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)  
 {  
 	 CListCtrl* pListCtrl = (CListCtrl*)lParamSort;

	 CString strItem1 = pListCtrl->GetItemText(lParam1, 8);  
	 CString strItem2 = pListCtrl->GetItemText(lParam2, 8);  

	 return strcmp(strItem2, strItem1);  
 }  

 void CMainPage::OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult)
 {
	 LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	 // TODO: Add your control notification handler code here
	 m_FacLogCtl.SortItems(CompareFunc, LPARAM(&m_FacLogCtl)); 

	 int nCount = m_FacLogCtl.GetItemCount(); 
	 if(nCount > 0) 
		 m_FacLogCtl.EnsureVisible(nCount-1,FALSE); 
	 *pResult = 0;
 }

 HBRUSH CMainPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 {
	 HBRUSH hbr = CPageInterface::OnCtlColor(pDC, pWnd, nCtlColor);

	 // TODO:  Change any attributes of the DC here
	 if(pWnd->GetDlgCtrlID()==IDC_SNEDIT)
		 pWnd->SetFocus();
	if (IDC_PASSFAIL==pWnd->GetDlgCtrlID())
	{
		if (m_iCtlStatus==0)
		{
			pDC->SetTextColor(BKCOLOR_SUCCESS);
		}
		else if (m_iCtlStatus==1)
		{
			pDC->SetTextColor(BKCOLOR_FAIL);
		}
		else if (m_iCtlStatus==2)
		{
			pDC->SetTextColor(BKCOLOR_STOP);
		}
	}
	if (IDC_PASSFAILBIG==pWnd->GetDlgCtrlID())
	{
		if (m_iCtlStatus==0)
		{
			pDC->SetTextColor(BKCOLOR_SUCCESS);
		}
		else if (m_iCtlStatus==1)
		{
			pDC->SetTextColor(BKCOLOR_FAIL);
		}
		else if (m_iCtlStatus==2)
		{
			pDC->SetTextColor(BKCOLOR_STOP);
		}
	}

	 // TODO:  Return a different brush if the default is not desired
	 return hbr;
 }
 void CMainPage::SetBitMapTraceLog(bool bIsShow)
 {
          CClientDC   dc(this);   //   device   context   for   painting   
          CDC   memDC;   
		   CBitmap   mBitmap;   
          mBitmap.LoadBitmap(IDB_BITMAP1); 
          memDC.CreateCompatibleDC(&dc);   
          memDC.SelectObject(mBitmap);   
          CRect   rect,   rectWnd;   
          GetWindowRect(rectWnd);   
          GetClientRect(rect);   
          int   width,height;   
          
          BITMAP   *pBitMap;   
          pBitMap   =   new   BITMAP;     
          mBitmap.GetBitmap(pBitMap);   
          width=pBitMap->bmWidth;   
          height=pBitMap->bmHeight;   
          dc.StretchBlt(rect.left,rect.top,rect.Width(), rect.Height(),&memDC,0,0,width,height,SRCCOPY);  
		  Invalidate();
		  delete pBitMap;
 }
 void CMainPage::ChangeStaticCtlColor(int iStatus)
 {
	 CWnd* pWnd=GetDlgItem(IDC_PASSFAIL);
	 CWnd* pWndbig=GetDlgItem(IDC_PASSFAILBIG);
	 switch(iStatus)
	 {
	 case 0:
		 m_iCtlStatus=0;
		 break;
	 case 1:
		 m_iCtlStatus=1;
		 break;
	 case 2:
		 m_iCtlStatus=2;
		 break;
	 default:
		 m_iCtlStatus=-1;
		 break;
	 }
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pWndbig->Invalidate();
	pWndbig->UpdateWindow();
 }

 void CMainPage::OnBnClickedCheck2()
 {
	   CString strDllPathName;

	   CString strTemp;
	   char szTemp[_MAX_PATH];

	  if(((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
	 {
		 theApp.m_bEnableTraceLog=1;
		
        m_TraceLogListCtl.ShowWindow(true);
		GetDlgItem(IDC_GROUPTRACE)->ShowWindow(true);
		 m_MainProcessCtrl.ShowWindow(false);
		GetDlgItem(IDC_PRONAME)->ShowWindow(false);
		 GetDlgItem(IDC_PICMAIN)->ShowWindow(false);
		 GetDlgItem(IDC_PASSFAILBIG)->ShowWindow(false);
		 GetDlgItem(IDC_LIST2)->ShowWindow(true);
		strTemp.Format("1");
	 }
	  else
	  {
        theApp.m_bEnableTraceLog=0;
		 m_TraceLogListCtl.ShowWindow(false);
		 GetDlgItem(IDC_GROUPTRACE)->ShowWindow(false);
		  m_MainProcessCtrl.ShowWindow(true);
		GetDlgItem(IDC_PRONAME)->ShowWindow(true);
		 GetDlgItem(IDC_PICMAIN)->ShowWindow(true);
		 GetDlgItem(IDC_PASSFAILBIG)->ShowWindow(true);
		 GetDlgItem(IDC_LIST2)->ShowWindow(false);
		 strTemp.Format("0");

	  }

	  ::GetModuleFileName(NULL, szTemp, _MAX_PATH);
	  strDllPathName.Format("%s",szTemp);
      strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')));

	  strDllPathName=strDllPathName+_T("\\SystemConfig\\SystemSetup.ini");

	::WritePrivateProfileString(_T("Settings"),_T("EnableTraceLog"),strTemp,strDllPathName);
	
 }


 void CMainPage::OnTimer(UINT_PTR nIDEvent)
 {
	
    switch(nIDEvent)
	{
	case 1:

		break;
	case 2:
		m_MainProcessCtrl.StepIt();
		break;


	}
	 CPageInterface::OnTimer(nIDEvent);
 }

 void CMainPage::OnEnChangeSnedit()
 {

    CString strMsg;
    CString strText;
	
	CString strTextHeader;
	GetDlgItemText(IDC_SNEDIT,strText);
	strTextHeader=strText.Mid(0,theApp.m_pConfigSetting->m_strSNHeader.GetLength());
	if(strText.GetLength()==theApp.m_pConfigSetting->m_iSNLength)
	{
		if(strTextHeader==theApp.m_pConfigSetting->m_strSNHeader)
		{

			if(theApp.m_bRunAfterSN)
			{
				if(!theApp.m_bIsrunning)
			    OnBnClickedButton2();
			}
		}
		else
		{
			strMsg.Format("SN Header not Correct . right header is %s",theApp.m_pConfigSetting->m_strSNHeader);
           MessageBox(strMsg);
		   SetDlgItemText(IDC_SNEDIT,"");
		   GetDlgItem(IDC_SNEDIT)->SetFocus();
		   TerminateThread(theApp.m_pCalTestWinThread->m_hThread,5);
		   PostMessage(WM_TRD_CALTEST_FINISH);
		   return;
		}
	}
 
	 
 }

 void CMainPage::OnOK()
 {
	 // TODO: Add your specialized code here and/or call the base class

	 //CPageInterface::OnOK();
	 return;
 }
