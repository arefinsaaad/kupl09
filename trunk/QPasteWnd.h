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

//##ModelId=474D302701E5
class CMainTable
{
public:
	//##ModelId=474D30270204
	CMainTable():
		m_lID(-1),
		m_bDontAutoDelete(false),
		m_bIsGroup(false),
		m_bHasShortCut(false),
		m_bHasParent(false)
	{
	}
	//##ModelId=474D30270205
	long	m_lID;
	//##ModelId=474D30270233
	CString m_Desc;
	//##ModelId=474D30270252
	bool	m_bDontAutoDelete;
	//##ModelId=474D302702A1
	bool	m_bIsGroup;
	//##ModelId=474D302702C0
	bool	m_bHasShortCut;	
	//##ModelId=474D302702DF
	bool	m_bHasParent;
	//##ModelId=474D302702FE
	CString m_QuickPaste;
	//##ModelId=474D3027030E
	CString m_WebAddr;				// added by kyo
};


/////////////////////////////////////////////////////////////////////////////
// CQPasteWnd window

//##ModelId=474D302A02A1
class CQPasteWnd : public CWndEx
{
// Construction
public:
	//##ModelId=474D302A02C0
	CQPasteWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQPasteWnd)
	public:
	//##ModelId=474D302A039B
	virtual BOOL Create(const POINT& ptStart, CWnd* pParentWnd);
	//##ModelId=474D302B004F
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D302B006E
	bool Add(const CString &csHeader, const CString &csText, int nID);
	//##ModelId=474D302B00FB
	virtual ~CQPasteWnd();

	//##ModelId=474D302B01A7
	void UpdateFont();

//protected:
	//##ModelId=474D302B01F6
	CQListCtrl		m_lstHeader;

	//##ModelId=474D302B0215
	CAlphaBlend		m_Alpha;
	//##ModelId=474D302B0234
	CFont			m_TitleFont;
	//##ModelId=474D302B0263
	CSearchEditBox	m_Search;
	//##ModelId=474D302B0282
	CFont			m_SearchFont;
	//##ModelId=474D302B02A2
	CButton			m_btCancel;
	//##ModelId=474D302B02C0
	bool			m_bHideWnd;
	//##ModelId=474D302B02CF
	CString			m_strSQLSearch;
	//##ModelId=474D302B02E0
	CGroupStatic	m_stGroup;
	//##ModelId=474D302B02FF
	CFont			GroupFont;
	//##ModelId=474D302B030E
	CString			m_Title;
	//##ModelId=474D302B032E
	CGroupTree		m_GroupTree;
	//##ModelId=474D302B035D
	CBitmapButton	m_ShowGroupsFolderBottom;
	//##ModelId=474D302B036D
	CBitmapButton	m_ShowGroupsFolderTop;
	//##ModelId=474D302B038C
	CBitmapButton	m_BackButton;
	//##ModelId=474D302B03AA
	bool			m_bAllowRepaintImmediately;

	//##ModelId=474D302B03BA
	CString			m_SQL;
	//##ModelId=474D302B03D9
	CString			m_CountSQL;
	//##ModelId=474D302C0001
	long			m_lRecordCount;
	//##ModelId=474D302C0020
	bool			m_bStopQuery;
	//##ModelId=474D302C0030
	bool			m_bHandleSearchTextChange;
	//##ModelId=474D302C004F
	bool			m_bFoundClipToSetFocusTo;
	//##ModelId=474D302C005E
	long			m_lItemsPerPage;

	//##ModelId=474D302C00AE
	std::vector<CMainTable> m_Cache;

	//##ModelId=474D302C00BC
	HANDLE m_Events[4];
	//##ModelId=474D302C00DB
	HANDLE m_ExitEvent;
	//##ModelId=474D302C00FB
	HANDLE m_SearchingEvent;

	//##ModelId=474D302C010B
	CCriticalSection m_CritSection;
	
	//##ModelId=474D302C012A
	void RefreshNc( bool bRepaintImmediately = false );
	//##ModelId=474D302C01A7
	void UpdateStatus( bool bRepaintImmediately = false );  // regenerates the status (caption) text
	//##ModelId=474D302C0252
	BOOL FillList(CString csSQLSearch = "");
	//##ModelId=474D302C02C0
	BOOL HideQPasteWindow();
	//##ModelId=474D302C033D
	BOOL ShowQPasteWindow(BOOL bFillList = TRUE);
	//##ModelId=474D302D0020
	void MoveControls();

	//##ModelId=474D302D00FB
	void DeleteSelectedRows();

	//##ModelId=474D302D0139
	BOOL OpenID(long lID, bool bOnlyLoad_CF_TEXT = false, bool bPasteHTMLAs_CF_TEXT = false);
	//##ModelId=474D302D01F5
	BOOL OpenSelection(bool bOnlyLoad_CF_TEXT = false, bool bPasteHTMLAs_CF_TEXT = false);
	//##ModelId=474D302D0281
	BOOL OpenIndex( long nItem );
	//##ModelId=474D302D02FE
	BOOL NewGroup( bool bGroupSelection = true );
	// moves the caret to the given ID, selects it, and ensures it is visible.
	//##ModelId=474D302D039B
	long SetListID( long lID );

	//##ModelId=474D302E004F
	CString LoadDescription( int nItem );
	//##ModelId=474D302E008D
	bool SaveDescription( int nItem, CString text );

	//Menu Items
	//##ModelId=474D302E00BC
	void SetLinesPerRow(long lLines);
	//##ModelId=474D302E010A
	void SetTransparency(long lPercent);
	//##ModelId=474D302E0158
	void OnUpdateLinesPerRow(CCmdUI* pCmdUI, int nValue);
	//##ModelId=474D302E0197
	void OnUpdateTransparency(CCmdUI* pCmdUI, int nValue);
	//##ModelId=474D302E01C6
	void SetMenuChecks(CMenu *pMenu);
	//##ModelId=474D302E0224
	void SetSendToMenu(CMenu *pMenu, int nMenuID, int nArrayPos);

	//##ModelId=474D302E0291
	BOOL SendToFriendbyPos(int nPos);

	//##ModelId=474D302E02C0
	bool InsertNextNRecords(int nEnd);
	
	//##ModelId=474D302E02DF
	CString GetDisplayText(long lDontAutoDelete, long lShortCut, bool bIsGroup, long lParentID, CString csText);

	//##ModelId=474D302E034C
	void FillMainTable(CMainTable &table, CppSQLite3Query &q);
	//##ModelId=474D302E037B
	void RunThread();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQPasteWnd)
	//##ModelId=474D302E037C
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D302F004F
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=474D302F0187
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//##ModelId=474D302F0252
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//##ModelId=474D302F02FE
	afx_msg void OnMenuLinesperrow1();
	//##ModelId=474D302F034C
	afx_msg void OnMenuLinesperrow2();
	//##ModelId=474D302F039B
	afx_msg void OnMenuLinesperrow3();
	//##ModelId=474D302F03D9
	afx_msg void OnMenuLinesperrow4();
	//##ModelId=474D3030003F
	afx_msg void OnMenuLinesperrow5();
	//##ModelId=474D303000AD
	afx_msg void OnMenuTransparency10();
	//##ModelId=474D303000FB
	afx_msg void OnMenuTransparency15();
	//##ModelId=474D30300158
	afx_msg void OnMenuTransparency20();
	//##ModelId=474D303001A7
	afx_msg void OnMenuTransparency25();
	//##ModelId=474D30300204
	afx_msg void OnMenuTransparency30();
	//##ModelId=474D30300252
	afx_msg void OnMenuTransparency40();
	//##ModelId=474D30300291
	afx_msg void OnMenuTransparency5();
	//##ModelId=474D303002CF
	afx_msg void OnMenuTransparencyNone();
	//##ModelId=474D3030031E
	afx_msg void OnRclickQuickPaste(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D303003AA
	afx_msg void OnMenuDelete();
	//##ModelId=474D30310010
	afx_msg void OnMenuPositioningAtcaret();
	//##ModelId=474D3031005E
	afx_msg void OnMenuPositioningAtcursor();
	//##ModelId=474D303100BC
	afx_msg void OnMenuPositioningAtpreviousposition();
	//##ModelId=474D3031010A
	afx_msg void OnMenuOptions();
	//##ModelId=474D30310158
	afx_msg void OnCancelFilter();
	//##ModelId=474D30310178
	afx_msg void OnMenuExitprogram();
	//##ModelId=474D303101C6
	afx_msg void OnMenuToggleConnectCV();
	//##ModelId=474D30310204
	afx_msg void OnMenuProperties();
	//##ModelId=474D30310243
	afx_msg void OnClose();
	//##ModelId=474D30310262
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D303102A1
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=474D303102DF
	afx_msg void GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D3031031E
	afx_msg void OnFindItem(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D3031035C
	afx_msg void OnMenuFirsttenhotkeysUsectrlnum();
	//##ModelId=474D3031039B
	afx_msg void OnMenuFirsttenhotkeysShowhotkeytext();
	//##ModelId=474D303103D9
	afx_msg void OnMenuQuickoptionsAllwaysshowdescription();
	//##ModelId=474D30320030
	afx_msg void OnMenuQuickoptionsDoubleclickingoncaptionTogglesalwaysontop();
	//##ModelId=474D3032006E
	afx_msg void OnMenuQuickoptionsDoubleclickingoncaptionRollupwindow();
	//##ModelId=474D303200AD
	afx_msg void OnMenuQuickoptionsDoubleclickingoncaptionTogglesshowdescription();
	//##ModelId=474D303200FB
	afx_msg void OnMenuQuickoptionsPromptfornewgroupnames();
	//##ModelId=474D30320139
	afx_msg void OnShowGroupsBottom();
	//##ModelId=474D30320158
	afx_msg void OnShowGroupsTop();
	//##ModelId=474D30320178
	afx_msg void OnMenuViewgroups();
	//##ModelId=474D303201C6
	afx_msg void OnMenuQuickpropertiesSettoneverautodelete();
	//##ModelId=474D30320204
	afx_msg void OnMenuQuickpropertiesAutodelete();
	//##ModelId=474D30320243
	afx_msg void OnMenuQuickpropertiesRemovehotkey();
	//##ModelId=474D30320281
	afx_msg void OnMenuSenttoFriendEight();
	//##ModelId=474D303202C0
	afx_msg void OnMenuSenttoFriendEleven();
	//##ModelId=474D303202EF
	afx_msg void OnMenuSenttoFriendFifteen();
	//##ModelId=474D3032031E
	afx_msg void OnMenuSenttoFriendFive();
	//##ModelId=474D3032034C
	afx_msg void OnMenuSenttoFriendFore();
	//##ModelId=474D3032038B
	afx_msg void OnMenuSenttoFriendForeteen();
	//##ModelId=474D303203BA
	afx_msg void OnMenuSenttoFriendNine();
	//##ModelId=474D30330010
	afx_msg void OnMenuSenttoFriendSeven();
	//##ModelId=474D3033004F
	afx_msg void OnMenuSenttoFriendSix();
	//##ModelId=474D3033008D
	afx_msg void OnMenuSenttoFriendTen();
	//##ModelId=474D303300CC
	afx_msg void OnMenuSenttoFriendThirteen();
	//##ModelId=474D3033010A
	afx_msg void OnMenuSenttoFriendThree();
	//##ModelId=474D30330149
	afx_msg void OnMenuSenttoFriendTwelve();
	//##ModelId=474D30330178
	afx_msg void OnMenuSenttoFriendTwo();
	//##ModelId=474D303301B6
	afx_msg void OnMenuSenttoFriendone();
	//##ModelId=474D303301E5
	afx_msg void OnMenuSenttoPromptforip();
	//##ModelId=474D30330214
	afx_msg void OnMenuGroupsMovetogroup();
	//##ModelId=474D30330243
	afx_msg void OnMenuPasteplaintextonly();
	//##ModelId=474D30330272
	afx_msg void OnMenuHelp();
	//##ModelId=474D30330291
	afx_msg void OnMenuQuickoptionsFont();
	//##ModelId=474D303302C0
	afx_msg void OnMenuQuickoptionsShowthumbnails();
	//##ModelId=474D303302DF
	afx_msg void OnMenuQuickoptionsDrawrtftext();
	//##ModelId=474D3033030E
	afx_msg void OnMenuQuickoptionsPasteclipafterselection();
	//##ModelId=474D3033032D
	afx_msg void OnSearchEditChange();
	//##ModelId=474D3033034C
	afx_msg void OnMenuQuickoptionsFindasyoutype();
	//##ModelId=474D3033037B
	afx_msg void OnMenuQuickoptionsEnsureentirewindowisvisible();
	//##ModelId=474D303303AA
	afx_msg void OnMenuQuickoptionsShowclipsthatareingroupsinmainlist();
	//##ModelId=474D303303D9
	afx_msg void OnMenuPastehtmlasplaintext();
	//##ModelId=474D30340010
	afx_msg void OnPromptToDeleteClip();
	//##ModelId=474D3034003F
	afx_msg void OnUpdateMenuNewgroup(CCmdUI* pCmdUI);
	//##ModelId=474D3034005E
	afx_msg void OnUpdateMenuNewgroupselection(CCmdUI* pCmdUI);
	//##ModelId=474D3034007E
	afx_msg void OnUpdateMenuAllwaysontop(CCmdUI* pCmdUI);
	//##ModelId=474D3034009D
	afx_msg void OnUpdateMenuViewfulldescription(CCmdUI* pCmdUI);
	//##ModelId=474D303400BC
	afx_msg void OnUpdateMenuViewgroups(CCmdUI* pCmdUI);
	//##ModelId=474D303400DB
	afx_msg void OnUpdateMenuPasteplaintextonly(CCmdUI* pCmdUI);
	//##ModelId=474D3034010A
	afx_msg void OnUpdateMenuDelete(CCmdUI* pCmdUI);
	//##ModelId=474D30340149
	afx_msg void OnUpdateMenuProperties(CCmdUI* pCmdUI);	
	//##ModelId=474D30340178
	afx_msg void OnDestroy();
	//}}AFX_MSG
	//##ModelId=474D3034017A
	afx_msg LRESULT OnListSelect(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30340233
	afx_msg LRESULT OnListEnd(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D303402DF
	afx_msg LRESULT OnSearch(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D3034034C
	afx_msg LRESULT OnDelete(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D303403AA
	afx_msg LRESULT OnProperties(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D303403D9
	afx_msg void OnGetToolTipText(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D30350030
	afx_msg LRESULT OnListSelect_DB_ID(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D303500BC
	afx_msg LRESULT OnListSelect_Index(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30350149
	afx_msg LRESULT OnRefreshView(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30350204
	afx_msg LRESULT OnGroupTreeMessage(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30350243
	afx_msg LRESULT OnFillRestOfList(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30350262
	afx_msg LRESULT OnRefeshVisibleRows(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30350291
	afx_msg LRESULT OnSetListCount(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	//##ModelId=474D303502C0
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	//##ModelId=474D303502EF
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	//##ModelId=474D3035030E
	afx_msg void OnViewcaptionbaronRight();
	//##ModelId=474D3035034C
	afx_msg void OnViewcaptionbaronBottom();
	//##ModelId=474D3035039B
	afx_msg void OnViewcaptionbaronLeft();
	//##ModelId=474D303503D9
	afx_msg void OnViewcaptionbaronTop();
	//##ModelId=474D30360020
	afx_msg void OnMenuAutohide();
	//##ModelId=474D3036005E
	afx_msg void OnMenuViewfulldescription();
	//##ModelId=474D3036009D
	afx_msg void OnMenuAllwaysontop();
	//##ModelId=474D303600EB
	afx_msg void OnSortAscending();
	//##ModelId=474D3036012A
	afx_msg void OnSortDescending();
	//##ModelId=474D30360168
	afx_msg void OnMenuNewGroup();
	//##ModelId=474D303601A7
	afx_msg void OnMenuNewGroupSelection();
	//##ModelId=474D303601E5
	afx_msg void OnBackButton();
	//##ModelId=474D30360204
	afx_msg LRESULT OnUpDown(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30360262
	afx_msg LRESULT OnItemDeleted(WPARAM wParam, LPARAM lParam);
	//##ModelId=474D30360291
	LRESULT OnToolTipWndInactive(WPARAM wParam, LPARAM lParam);
public:
	//##ModelId=474D303602C0
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//##ModelId=474D303602CF
	afx_msg void OnMenuExport();
	//##ModelId=474D303602FE
	afx_msg void OnMenuImport();
	//##ModelId=474D3036032D
	afx_msg void OnQuickpropertiesRemovequickpaste();
	//##ModelId=474D3036036C
	afx_msg void OnMenuEdititem();
	//##ModelId=474D3036038B
	afx_msg void OnMenuNewclip();
	//##ModelId=474D303603BA
	afx_msg void OnUpdateMenuEdititem(CCmdUI *pCmdUI);
	//##ModelId=474D303603C9
	afx_msg void OnUpdateMenuNewclip(CCmdUI *pCmdUI);
	//##ModelId=474D30370001
	afx_msg void OnSaveAsTXTFile();
	//##ModelId=474D30370003
	afx_msg void OnSaveAsPDFFile();
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QPASTEWND_H__65261F0F_FEFD_48CF_A0CD_01D8BFEB353B__INCLUDED_)
