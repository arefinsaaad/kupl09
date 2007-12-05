// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__147283E8_5032_4C0A_9828_1CC59DECFD62__INCLUDED_)
#define AFX_MAINFRM_H__147283E8_5032_4C0A_9828_1CC59DECFD62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SystemTray.h"
#include "QuickPaste.h"
#include "ToolTipEx.h"
#include "EditFrameWnd.h"


#define CLOSE_WINDOW_TIMER				1	
#define HIDE_ICON_TIMER					2
#define REMOVE_OLD_ENTRIES_TIMER		3
#define CHECK_FOR_UPDATE				4
#define CLOSE_APP						5
#define STOP_MONITORING_KEYBOARD_TIMER	7
#define STOP_LOOKING_FOR_KEYBOARD		8
#define REMOVE_OLD_REMOTE_COPIES		9
#define END_DITTO_BUFFER_CLIPBOARD_TIMER	10

//##ModelId=474D305F00CC
class CMainFrame : public CFrameWnd
{
public:
	//##ModelId=474D305F00EB
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

	//##ModelId=474D305F010A
	BOOL ResetKillDBTimer();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	//##ModelId=474D305F011A
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D305F0168
	virtual ~CMainFrame();
#ifdef _DEBUG
	//##ModelId=474D305F0197
	virtual void AssertValid() const;
	//##ModelId=474D305F01B6
	virtual void Dump(CDumpContext& dc) const;
#endif

	//##ModelId=474D305F01E6
	CQuickPaste QuickPaste;
	//##ModelId=474D305F0253
	CSystemTray m_TrayIcon;
	//##ModelId=474D305F0281
	ULONG m_ulCopyGap;
	//##ModelId=474D305F02CF
	CString m_csKeyboardPaste;
	//##ModelId=474D305F02FF
	CToolTipEx *m_pTypingToolTip;
	//##ModelId=474D305F031E
	CString csTypeToolTipTitle;
	//##ModelId=474D305F034C
	CPoint m_ToolTipPoint;
	//##ModelId=474D305F037C
	CAlphaBlend m_Transparency;

	//##ModelId=474D305F03AA
	void DoDittoCopyBufferPaste(int nCopyBuffer);
	//##ModelId=474D305F03C9
	void DoFirstTenPositionsPaste(int nPos);
	//##ModelId=474D3060005E
	void StopLookingForKeystrokes(bool bInitAppVaribles);
	//##ModelId=474D3060007E
	bool PasteQuickPasteEntry(CString csQuickPaste);
	//##ModelId=474D306000AD
	bool SaveQuickPasteEntry(CString csQuickPaste, CClipList *pClipList);
	//##ModelId=474D306000CC
	void ShowErrorMessage(CString csTitle, CString csMessage);
	//##ModelId=474D306000DC
	bool CloseAllOpenDialogs();

	//##ModelId=474D306000EB
	static void DeleteOldRemoteCopies(CString csDir);
	//##ModelId=474D3060010A
	static UINT RemoteOldRemoteFilesThread(LPVOID pParam);

	//##ModelId=474D3060011A
	void ShowEditWnd(CClipIDs &Ids);
	//##ModelId=474D3060012B
	CEditFrameWnd *m_pEditFrameWnd;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	//##ModelId=474D30600139
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D306001A7
	afx_msg void OnFirstOption();
	//##ModelId=474D306001C6
	afx_msg void OnFirstExit();
	//##ModelId=474D306001F5
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	//##ModelId=474D30600243
	afx_msg void OnDrawClipboard();
	//##ModelId=474D30600262
	afx_msg void OnTimer(UINT nIDEvent);
	//##ModelId=474D306002A1
	afx_msg void OnFirstShowquickpaste();
	//##ModelId=474D306002B0
	afx_msg void OnFirstToggleConnectCV();
	//##ModelId=474D306002CF
	afx_msg void OnUpdateFirstToggleConnectCV(CCmdUI* pCmdUI);
	//##ModelId=474D306002EF
	afx_msg void OnFirstHelp();
	//}}AFX_MSG
	//##ModelId=474D306002FF
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D3060035C
	afx_msg LRESULT OnShowTrayIcon(WPARAM wParam, LPARAM lParam);
//	afx_msg LRESULT OnGetIsTopView(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D3060039B
	afx_msg LRESULT OnCopyProperties(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D306003D9
	afx_msg LRESULT OnShutDown(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30610010
	afx_msg LRESULT OnClipboardCopied(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D3061004F
	afx_msg LRESULT OnAddToDatabaseFromSocket(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D3061006E
	afx_msg LRESULT OnErrorOnSendRecieve(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D3061009D
	afx_msg LRESULT OnFocusChanged(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D306100BC
	afx_msg LRESULT OnCustomizeTrayMenu(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D306100EC
	afx_msg LRESULT OnKeyBoardChanged(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D3061011A
	afx_msg LRESULT OnEditWndClose(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30610149
	afx_msg LRESULT OnSetConnected(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	//##ModelId=474D30610168
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//##ModelId=474D306101E5
	afx_msg void OnClose();
	//##ModelId=474D30610214
	afx_msg void OnFirstImport();
	//##ModelId=474D30610216
	afx_msg void OnDestroy();
	//##ModelId=474D30610225
	afx_msg void OnFirstNewclip();
};

//##ModelId=474D30610252
class CShowMainFrame
{
public:
	//##ModelId=474D30610262
	CShowMainFrame();
	//##ModelId=474D30610291
	~CShowMainFrame();
	//##ModelId=474D306102B0
	static bool m_bShowingMainFrame;
	//##ModelId=474D306102DF
	bool m_bHideMainFrameOnExit;
	//##ModelId=474D306102EF
	HWND m_hWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__147283E8_5032_4C0A_9828_1CC59DECFD62__INCLUDED_)
