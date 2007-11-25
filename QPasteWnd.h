#if !defined(AFX_QPASTEWND_H__65261F0F_FEFD_48CF_A0CD_01D8BFEB353B__INCLUDED_)
#define AFX_QPASTEWND_H__65261F0F_FEFD_48CF_A0CD_01D8BFEB353B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QPasteWnd.h : header file
//

#include "QListCtrl.h"
#include "SearchEditBox.h"
#include "WndEx.h"
#include "GroupStatic.h"
#include "GroupTree.h"
#include "AlphaBlend.h"
#include "Sqlite\CppSQLite3.h"
#include <vector>
#include <afxmt.h>

class CMainTable
{
public:
	CMainTable():
		m_lID(-1),
		m_bDontAutoDelete(false),
		m_bIsGroup(false),
		m_bHasShortCut(false),
		m_bHasParent(false)
	{
	}
	long	m_lID;
	CString m_Desc;
	bool	m_bDontAutoDelete;
	bool	m_bIsGroup;
	bool	m_bHasShortCut;	
	bool	m_bHasParent;
	CString m_QuickPaste;
	CString m_WebAddr;				// added by kyo
};


/////////////////////////////////////////////////////////////////////////////
// CQPasteWnd window

class CQPasteWnd : public CWndEx
{
// Construction
public:
	CQPasteWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQPasteWnd)
	public:
	virtual BOOL Create(const POINT& ptStart, CWnd* pParentWnd);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool Add(const CString &csHeader, const CString &csText, int nID);
	virtual ~CQPasteWnd();

	void UpdateFont();

//protected:
	CQListCtrl		m_lstHeader;

	CAlphaBlend		m_Alpha;
	CFont			m_TitleFont;
	CSearchEditBox	m_Search;
	CFont			m_SearchFont;
	CButton			m_btCancel;
	bool			m_bHideWnd;
	CString			m_strSQLSearch;
	CGroupStatic	m_stGroup;
	CFont			GroupFont;
	CString			m_Title;
	CGroupTree		m_GroupTree;
	CBitmapButton	m_ShowGroupsFolderBottom;
	CBitmapButton	m_ShowGroupsFolderTop;
	CBitmapButton	m_BackButton;
	bool			m_bAllowRepaintImmediately;

	CString			m_SQL;
	CString			m_CountSQL;
	long			m_lRecordCount;
	bool			m_bStopQuery;
	bool			m_bHandleSearchTextChange;
	bool			m_bFoundClipToSetFocusTo;
	long			m_lItemsPerPage;

	std::vector<CMainTable> m_Cache;

	HANDLE m_Events[4];
	HANDLE m_ExitEvent;
	HANDLE m_SearchingEvent;

	CCriticalSection m_CritSection;
	
	void RefreshNc( bool bRepaintImmediately = false );
	void UpdateStatus( bool bRepaintImmediately = false );  // regenerates the status (caption) text
	BOOL FillList(CString csSQLSearch = "");
	BOOL HideQPasteWindow();
	BOOL ShowQPasteWindow(BOOL bFillList = TRUE);
	void MoveControls();

	void DeleteSelectedRows();

	BOOL OpenID(long lID, bool bOnlyLoad_CF_TEXT = false, bool bPasteHTMLAs_CF_TEXT = false);
	BOOL OpenSelection(bool bOnlyLoad_CF_TEXT = false, bool bPasteHTMLAs_CF_TEXT = false);
	BOOL OpenIndex( long nItem );
	BOOL NewGroup( bool bGroupSelection = true );
	// moves the caret to the given ID, selects it, and ensures it is visible.
	long SetListID( long lID );

	CString LoadDescription( int nItem );
	bool SaveDescription( int nItem, CString text );

	//Menu Items
	void SetLinesPerRow(long lLines);
	void SetTransparency(long lPercent);
	void OnUpdateLinesPerRow(CCmdUI* pCmdUI, int nValue);
	void OnUpdateTransparency(CCmdUI* pCmdUI, int nValue);
	void SetMenuChecks(CMenu *pMenu);
	void SetSendToMenu(CMenu *pMenu, int nMenuID, int nArrayPos);

	BOOL SendToFriendbyPos(int nPos);

	bool InsertNextNRecords(int nEnd);
	
	CString GetDisplayText(long lDontAutoDelete, long lShortCut, bool bIsGroup, long lParentID, CString csText);

	void FillMainTable(CMainTable &table, CppSQLite3Query &q);
	void RunThread();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQPasteWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMenuLinesperrow1();
	afx_msg void OnMenuLinesperrow2();
	afx_msg void OnMenuLinesperrow3();
	afx_msg void OnMenuLinesperrow4();
	afx_msg void OnMenuLinesperrow5();
	afx_msg void OnMenuTransparency10();
	afx_msg void OnMenuTransparency15();
	afx_msg void OnMenuTransparency20();
	afx_msg void OnMenuTransparency25();
	afx_msg void OnMenuTransparency30();
	afx_msg void OnMenuTransparency40();
	afx_msg void OnMenuTransparency5();
	afx_msg void OnMenuTransparencyNone();
	afx_msg void OnRclickQuickPaste(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuPositioningAtcaret();
	afx_msg void OnMenuPositioningAtcursor();
	afx_msg void OnMenuPositioningAtpreviousposition();
	afx_msg void OnMenuOptions();
	afx_msg void OnCancelFilter();
	afx_msg void OnMenuExitprogram();
	afx_msg void OnMenuToggleConnectCV();
	afx_msg void OnMenuProperties();
	afx_msg void OnClose();
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFindItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuFirsttenhotkeysUsectrlnum();
	afx_msg void OnMenuFirsttenhotkeysShowhotkeytext();
	afx_msg void OnMenuQuickoptionsAllwaysshowdescription();
	afx_msg void OnMenuQuickoptionsDoubleclickingoncaptionTogglesalwaysontop();
	afx_msg void OnMenuQuickoptionsDoubleclickingoncaptionRollupwindow();
	afx_msg void OnMenuQuickoptionsDoubleclickingoncaptionTogglesshowdescription();
	afx_msg void OnMenuQuickoptionsPromptfornewgroupnames();
	afx_msg void OnShowGroupsBottom();
	afx_msg void OnShowGroupsTop();
	afx_msg void OnMenuViewgroups();
	afx_msg void OnMenuQuickpropertiesSettoneverautodelete();
	afx_msg void OnMenuQuickpropertiesAutodelete();
	afx_msg void OnMenuQuickpropertiesRemovehotkey();
	afx_msg void OnMenuSenttoFriendEight();
	afx_msg void OnMenuSenttoFriendEleven();
	afx_msg void OnMenuSenttoFriendFifteen();
	afx_msg void OnMenuSenttoFriendFive();
	afx_msg void OnMenuSenttoFriendFore();
	afx_msg void OnMenuSenttoFriendForeteen();
	afx_msg void OnMenuSenttoFriendNine();
	afx_msg void OnMenuSenttoFriendSeven();
	afx_msg void OnMenuSenttoFriendSix();
	afx_msg void OnMenuSenttoFriendTen();
	afx_msg void OnMenuSenttoFriendThirteen();
	afx_msg void OnMenuSenttoFriendThree();
	afx_msg void OnMenuSenttoFriendTwelve();
	afx_msg void OnMenuSenttoFriendTwo();
	afx_msg void OnMenuSenttoFriendone();
	afx_msg void OnMenuSenttoPromptforip();
	afx_msg void OnMenuGroupsMovetogroup();
	afx_msg void OnMenuPasteplaintextonly();
	afx_msg void OnMenuHelp();
	afx_msg void OnMenuQuickoptionsFont();
	afx_msg void OnMenuQuickoptionsShowthumbnails();
	afx_msg void OnMenuQuickoptionsDrawrtftext();
	afx_msg void OnMenuQuickoptionsPasteclipafterselection();
	afx_msg void OnSearchEditChange();
	afx_msg void OnMenuQuickoptionsFindasyoutype();
	afx_msg void OnMenuQuickoptionsEnsureentirewindowisvisible();
	afx_msg void OnMenuQuickoptionsShowclipsthatareingroupsinmainlist();
	afx_msg void OnMenuPastehtmlasplaintext();
	afx_msg void OnPromptToDeleteClip();
	afx_msg void OnUpdateMenuNewgroup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuNewgroupselection(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuAllwaysontop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuViewfulldescription(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuViewgroups(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuPasteplaintextonly(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuProperties(CCmdUI* pCmdUI);	
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnListSelect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnListEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSearch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProperties(WPARAM wParam, LPARAM lParam);
	afx_msg void OnGetToolTipText(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnListSelect_DB_ID(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnListSelect_Index(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshView(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGroupTreeMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFillRestOfList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefeshVisibleRows(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetListCount(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnViewcaptionbaronRight();
	afx_msg void OnViewcaptionbaronBottom();
	afx_msg void OnViewcaptionbaronLeft();
	afx_msg void OnViewcaptionbaronTop();
	afx_msg void OnMenuAutohide();
	afx_msg void OnMenuViewfulldescription();
	afx_msg void OnMenuAllwaysontop();
	afx_msg void OnSortAscending();
	afx_msg void OnSortDescending();
	afx_msg void OnMenuNewGroup();
	afx_msg void OnMenuNewGroupSelection();
	afx_msg void OnBackButton();
	afx_msg LRESULT OnUpDown(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnItemDeleted(WPARAM wParam, LPARAM lParam);
	LRESULT OnToolTipWndInactive(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMenuExport();
	afx_msg void OnMenuImport();
	afx_msg void OnQuickpropertiesRemovequickpaste();
	afx_msg void OnMenuEdititem();
	afx_msg void OnMenuNewclip();
	afx_msg void OnUpdateMenuEdititem(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuNewclip(CCmdUI *pCmdUI);
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QPASTEWND_H__65261F0F_FEFD_48CF_A0CD_01D8BFEB353B__INCLUDED_)
