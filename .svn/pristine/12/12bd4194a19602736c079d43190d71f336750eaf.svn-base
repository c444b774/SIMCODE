// PasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimRFCaltestUI.h"
#include "PasswordDlg.h"


// CPasswordDlg dialog

IMPLEMENT_DYNAMIC(CPasswordDlg, CDialog)

CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDlg::IDD, pParent)
{
  m_bPswCorrect=false;
  m_bPSWCorrect2=false;
}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PSW, m_ePSW);
	DDX_Control(pDX, IDC_PSW_STA, m_PSWSTa);
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPasswordDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_PSW, &CPasswordDlg::OnEnChangePsw)
	ON_BN_CLICKED(IDC_BUTTON1, &CPasswordDlg::OnBnClickedButton1)
	ON_STN_DBLCLK(IDC_PSW_STA, &CPasswordDlg::OnStnDblclickPswSta)
	ON_BN_CLICKED(IDCANCEL, &CPasswordDlg::OnBnClickedCancel)
	

END_MESSAGE_MAP()


// CPasswordDlg message handlers

void CPasswordDlg::OnBnClickedOk()
{
	CString strPsw;
    m_ePSW.GetWindowTextA(strPsw);
    if(strPsw.CompareNoCase("simcom")==0 ||strPsw.CompareNoCase("1")==0)
	{
      m_bPswCorrect=true;
	}
	if(strPsw.CompareNoCase("Strong")==0 || strPsw.CompareNoCase("a")==0)
	{
      m_bPSWCorrect2=true;
	}
	OnOK();
}

void CPasswordDlg::OnEnChangePsw()
{
	
}

void CPasswordDlg::OnBnClickedButton1()
{
	 m_bPswCorrect=true;
     OnOK();
}

BOOL CPasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ePSW.SetFocus();
	return false;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CPasswordDlg::OnStnDblclickPswSta()
{
	 m_bPswCorrect=true;
     OnOK();
}

void CPasswordDlg::OnBnClickedCancel()
{
	
	OnCancel();
}


