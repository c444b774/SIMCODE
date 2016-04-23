// SimRFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimRFCaltestUI.h"
#include "SimRFDlg.h"
#include "MainPage.h"
#include "BaseConfigPage.h"
#include "LossConfigPage.h"


// CSimRFDlg dialog

IMPLEMENT_DYNAMIC(CSimRFDlg, CDialog)

CSimRFDlg::CSimRFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimRFDlg::IDD, pParent)
{

}

CSimRFDlg::~CSimRFDlg()
{
	for (int i = 0; i < m_PageArray.GetSize(); i++)	
	{
		CPageInterface* pPage = m_PageArray.GetAt(i);

		if (pPage != NULL)
			delete pPage;
	}


	m_PageArray.RemoveAll();
}

void CSimRFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB4, m_pagelistctrl);
}


BEGIN_MESSAGE_MAP(CSimRFDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB4, &CSimRFDlg::OnTcnSelchangeTab4)
	ON_WM_SIZE()
	ON_MESSAGE(WM_RFDLG_SIZE, OnMainDlgSize)
END_MESSAGE_MAP()


// CSimRFDlg message handlers
LRESULT CSimRFDlg::OnMainDlgSize(WPARAM wParam, LPARAM lParam)
{
  int iIsBackSize=*((int *)lParam);
  if(iIsBackSize)
	  ReSizeMainWnd(true);
  else
      ReSizeMainWnd(false);
  return 1;
}
void CSimRFDlg::OnTcnSelchangeTab4(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(	theApp.m_bIsrunning)
		return;
	CString strPageName;
	for (int iPageIdx = 0; iPageIdx < m_PageArray.GetSize(); iPageIdx++) {
		ASSERT(m_PageArray[iPageIdx] != NULL);
		if (m_PageArray[iPageIdx] == NULL)
			continue;
 
		if (iPageIdx == m_pagelistctrl.GetCurSel()) {
			
           
			m_PageArray[iPageIdx]->GetPageName(strPageName); 
		
			 m_PageArray[iPageIdx]->ShowWindow(SW_SHOW);
			 m_PageArray[iPageIdx]->Refresh(); // to sync with xml data
			
		}
		else
			m_PageArray[iPageIdx]->ShowWindow(SW_HIDE);
	}
	
	*pResult = 0;
}
void CSimRFDlg::ReSizeMainWnd(bool IsBack)
{
	if(!IsBack)
	{
		int iX=m_RectRFDlg.left;
		int iY=m_RectRFDlg.top;
		int iHeight=m_RectRFDlg.bottom-m_RectRFDlg.top;
		int iWidth=m_RectRFDlg.right-m_RectRFDlg.left;
		iHeight-=300;
		iWidth-=30;

		MoveWindow(iX,iY,iWidth,iHeight);
	}
	else
	{
	    MoveWindow(&m_RectRFDlg);
	}
}
BOOL CSimRFDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString strTitle;
    
	CMainPage* pMainPage=new CMainPage();

	pMainPage->Create(CMainPage::IDD,&m_pagelistctrl);
	m_pagelistctrl.InsertItem(m_pagelistctrl.GetItemCount(),"MainTest");
    m_PageArray.Add(pMainPage);
    ((CSimRFCaltestUIApp*)AfxGetApp())->m_pMainPage=pMainPage;

    CBaseConfigPage* pBaseConfigPage=new CBaseConfigPage("BaseConfig");
	pBaseConfigPage->Create(CBaseConfigPage::IDD,&m_pagelistctrl);
    m_pagelistctrl.InsertItem(m_pagelistctrl.GetItemCount(),"BaseConfig");
    m_PageArray.Add(pBaseConfigPage);
	((CSimRFCaltestUIApp*)AfxGetApp())->m_pBaseConfigPage=pBaseConfigPage;

    CLossConfigPage* pLossConfigPage=new CLossConfigPage();
	pLossConfigPage->Create(CLossConfigPage::IDD,&m_pagelistctrl);
    m_pagelistctrl.InsertItem(m_pagelistctrl.GetItemCount(),"LossConfig");
    m_PageArray.Add(pLossConfigPage);
	((CSimRFCaltestUIApp*)AfxGetApp())->m_pLossConfigPage=pLossConfigPage;

	strTitle.Format("SimcomTestTool V%s     CopyRight: Author  QQ:19719817  Mail:zhuang.wang@sim.com",theApp.m_strToolVer);
	SetWindowText(strTitle);
	CRect rect;
	m_pagelistctrl.GetClientRect(&rect);
	m_pagelistctrl.AdjustRect(FALSE, &rect);
	for (int i = 0; i < m_PageArray.GetSize(); i++)
		m_PageArray.GetAt(i)->MoveWindow(rect);
 
	m_pagelistctrl.SetCurSel(0);

	LRESULT lr;
	OnTcnSelchangeTab4(0, &lr);
	GetWindowRect(&m_RectRFDlg);


	return true;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSimRFDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);


	// TODO: Add your message handler code here
}

void CSimRFDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialog::OnOK();

}

void CSimRFDlg::OnCancel()
{
	if(theApp.m_hCalTestThread)
	{
	 int iSelID=AfxMessageBox("Are you sure to exit the TOOL ?",MB_OKCANCEL,0);

		
		if(iSelID==IDCANCEL)
				return ;
	}
    
	CDialog::OnCancel();
}
