// SimRFCaltestUIDlg.h : header file
//

#pragma once
#include  "PageInterface.h"

#include "afxwin.h"
#include "afxcmn.h"
// CSimRFCaltestUIDlg dialog
typedef bool (__cdecl *pfCreateRFCALTEST)(PPIRFCalTestDLL);
typedef char* (_stdcall *pFnCheckSNRouting)(char* ServerConn,char* Station,char* SerialCode);
typedef char* (_stdcall *pFnUpdateSNRouting)(char* ServerConn,char* Station,char* FixtureCode,char* ErrorCode,char* Line,char* SerialCode,char* Creator,int IsPass);
class CMainPage : public CPageInterface
{
// Construction
public:
	CMainPage(CWnd* pParent = NULL);	// standard constructor
    ~CMainPage();
// Dialog Data
	enum { IDD = IDD_MAINPAGE };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnCalTestThreadProcProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCalTestPostFlagProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnCalTestThreadUpdateSn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnUpdateXMLLoss(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComProcessLIst;
	
	 CListBox m_ItemListBox;
	
     

    void LoadIniAndUpdateUi();
	void AddFactoryLog(INT iProcessCode, LPCTSTR lpszBand, LPCTSTR lpszChannel, INT iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit, BOOL bPass, LPCTSTR lpszMsgFormat, ...);
	void AddCommandLog(LPCTSTR lpszType, LPCTSTR lpszMessage);
    void AddTraceLog(LPCTSTR lpszModule, LPCSTR lpszSrcFile, UINT iSrcLine, EMsgLevel msgLevel, LPCTSTR lpszFormat, ...);
	void AddFactoryLogEx(INT iProcessCode, LPCTSTR lpszBand, LPCTSTR lpszChannel, INT iErrorCode, LPCTSTR lpszUL, LPCTSTR lpszDL, LPCTSTR lpszMeasured, LPCTSTR lpszUnit, BOOL bPass, LPCTSTR lpszItemName,LPCTSTR lpszMsgFormat, ...);
	void ChangeStaticCtlColor(int iStatus);
    void SetBitMapTraceLog(bool bIsShow=true);
	void CreateLogFileAndCreateDir(LPCTSTR lpszLogFilePath);
	void ChangeLogFilePath(LPCTSTR lpszLogFilePath);
	bool CheckSF(CString  strSN);
	bool UpdateSF(CString  strSN,int iErrorCode,bool bIsPass);
	
	void PostFinishThread(int iThreadExitCode);
private:

	
	inline clock_t GetDurationTimeAndUpdateLatestClock()
	{
	clock_t curClock = clock();
	clock_t duration = curClock - m_ckLatestClock;
	m_ckLatestClock = curClock;
	return duration;
	}
	int CalTestThreadProcImp();
	static UINT CalTestThreadProc(LPVOID pPara);
	

private:
	
	RECT m_rectFacLog;
    RECT m_rectButton;
	CString m_strLogFilePath;
	clock_t m_ckLatestClock;
	FILE* m_pLogFile;
	CFont *m_font;
	CFont fPFFont;
	CString m_strTitle;
	DWORD m_dwStartTime;
	HMODULE m_hSFDll; 
	pFnCheckSNRouting m_pFnCheckSNRouting;
    pFnUpdateSNRouting m_pFnUpdateSNRouting;
   
	int m_iCtlStatus;
	
public:
	afx_msg void OnBnClickedButton2();
	afx_msg LRESULT OnCalTestThreadFinish(WPARAM wParam, LPARAM lParam);
	

	CListCtrl m_TraceLogListCtl;
	CListCtrl m_FacLogCtl;
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedConfig();
	afx_msg void OnStnClickedTitle();

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnNMCustomdrawList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCheck2();
	
	CProgressCtrl m_MainProcessCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_picMain;
	afx_msg void OnEnChangeSnedit();
	virtual void OnOK();
};
