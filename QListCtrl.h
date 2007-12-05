 #if !defined(AFX_QLISTCTRL_H__30BEB04A_4B97_4943_BB73_C5128E66B4ED__INCLUDED_)
#define AFX_QLISTCTRL_H__30BEB04A_4B97_4943_BB73_C5128E66B4ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QListCtrl.h : header file
//
#include "ArrayEx.h"
#include "ToolTipEx.h"
#include "FormattedTextDraw.h"
#include "sqlite/CppSQLite3.h"

#define NM_SELECT					WM_USER+0x100
#define NM_RIGHT					WM_USER+0x101
#define NM_LEFT						WM_USER+0x102
#define NM_END						WM_USER+0x103
#define NM_DELETE					WM_USER+0x104
#define NM_PROPERTIES				WM_USER+0x105
#define NM_LBUTTONDOWN				WM_USER+0x106
#define NM_GETTOOLTIPTEXT	        WM_USER+0x107
#define NM_SELECT_DB_ID		        WM_USER+0x108
#define NM_SELECT_INDEX		        WM_USER+0x109
#define NM_GROUP_TREE_MESSAGE       WM_USER+0x110
#define CB_SEARCH					WM_USER+0x112
#define CB_UPDOWN					WM_USER+0x113
#define NM_INACTIVE_TOOLTIPWND		WM_USER+0x114
#define NM_FILL_REST_OF_LIST		WM_USER+0x115

#define NM_SET_LIST_COUNT			WM_USER+0x116
#define NM_REFRESH_VISIBLE_ROWS		WM_USER+0x117
#define NM_ITEM_DELETED				WM_USER+0x118

#define COPY_BUFFER_HOT_KEY_1_ID	-100
#define COPY_BUFFER_HOT_KEY_2_ID	-101
#define COPY_BUFFER_HOT_KEY_3_ID	-102


//#define NM_LIST_CUT			        WM_USER+0x111
//#define NM_LIST_COPY		        WM_USER+0x112
//#define NM_LIST_PASTE		        WM_USER+0x113

//##ModelId=474D308202B0
class CQListToolTipText
{
public:
	//##ModelId=474D308202C1
	NMHDR hdr;
	//##ModelId=474D308202D2
	long lItem;
	//##ModelId=474D308202DF
	LPTSTR pszText; 
	//##ModelId=474D308202EF
	int cchTextMax; 
};

//##ModelId=474D3082033D
typedef CMap<long, long, CClipFormat, CClipFormat&> CMapIDtoCF;

//##ModelId=474D3083007E
class CQListCtrl : public CListCtrl
{
// Construction
public:
	//##ModelId=474D3083009E
	CQListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQListCtrl)
	public:
	//##ModelId=474D308300BC
	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
	//##ModelId=474D308300EB
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//##ModelId=474D3083011A
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D30830158
	virtual ~CQListCtrl();

	// The "FirstTen" block is either at the top or the bottom
	//  of the list based upon m_bStartTop.
	//##ModelId=474D30830178
	BOOL	m_bShowTextForFirstTenHotKeys;
	//##ModelId=474D30830187
	BOOL	m_bStartTop;
	// returns the position 1-10 if the index is in the FirstTen block else -1
	//##ModelId=474D30830197
	int GetFirstTenNum( int index );
	// returns the list index corresponding to the given FirstTen position number.
	//##ModelId=474D308301D5
	int GetFirstTenIndex( int num );

	//##ModelId=474D30830204
	void SetNumberOfLinesPerRow(int nLines);
	//##ModelId=474D30830224
	void GetSelectionIndexes(ARRAY &arr);
	//##ModelId=474D30830243
	void GetSelectionItemData(ARRAY &arr);
	//##ModelId=474D30830272
	void RefreshVisibleRows();
	//##ModelId=474D30830281
	void RemoveAllSelection();
	//##ModelId=474D30830291
	BOOL SetSelection(int nRow, BOOL bSelect = TRUE);
	//##ModelId=474D308302CF
	BOOL SetText(int nRow, int nCol, CString cs);
	//##ModelId=474D308302FE
	BOOL SetFormattedText(int nRow, int nCol, LPCTSTR lpszFormat,...);
	//##ModelId=474D3083033D
	BOOL SetCaret(int nRow, BOOL bFocus = TRUE);
	//##ModelId=474D3083036C
	long GetCaret();
	// moves the caret to the given index, selects it, and ensures it is visible.
	//##ModelId=474D3083038B
	BOOL SetListPos(int index);
	//##ModelId=474D308303AA
	bool PutSelectedItemOnDittoCopyBuffer(long lBuffer);

	//##ModelId=474D308303D9
	DWORD GetItemData(int nItem);
	//##ModelId=474D30840002
	void GetToolTipText(int nItem, CString &csText);

	//##ModelId=474D30840012
	void SetShowTextForFirstTenHotKeys(BOOL bVal)	{ m_bShowTextForFirstTenHotKeys = bVal;	}

	//##ModelId=474D3084003F
	void DestroyAndCreateAccelerator(BOOL bCreate, CppSQLite3DB &db);

	//##ModelId=474D3084004F
	void ShowFullDescription(bool bFromAuto = false);
	//##ModelId=474D30840051
	BOOL SetItemCountEx(int iCount, DWORD dwFlags = LVSICF_NOINVALIDATEALL);

	//##ModelId=474D3084009D
	void HidePopup()	{ if(m_pToolTip) m_pToolTip->Hide();	}

	//##ModelId=474D3084009E
	void SetLogFont(LOGFONT &font);

	//##ModelId=474D308400AE
	HWND GetToolTipHWnd();

	//##ModelId=474D308400AF
	BOOL HandleKeyDown(WPARAM wParam, LPARAM lParam);

	//##ModelId=474D308400CC
	BOOL OnItemDeleted(long lID);

protected:
	//##ModelId=474D308400FB
	void SendSelection(int nItem);;
	//##ModelId=474D30840139
	void LoadCopyOrCutToClipboard();
	//##ModelId=474D30840158
	void SendSelection(ARRAY &arrItems);
	//##ModelId=474D30840197
	BOOL GetClipData(int nItem, CClipFormat &Clip);
	//##ModelId=474D308401B6
	BOOL DrawBitMap(int nItem, CRect &crRect, CDC *pDC);
	//##ModelId=474D308401E5
	void LoadDittoCopyBufferHotkeys();

	//##ModelId=474D308401F5
	BOOL DrawText(int nItem, CRect &crRect, CDC *pDC);
		
	//##ModelId=474D30840233
	WCHAR *m_pwchTip;
	//##ModelId=474D30840243
	TCHAR *m_pchTip;

	//##ModelId=474D30840252
	HFONT m_SmallFont;

	//Accelerator
	//##ModelId=474D30840273
	CAccels	m_Accels;

	//##ModelId=474D30840292
	CMapIDtoCF m_ThumbNails;
	//##ModelId=474D308402A2
	CMapIDtoCF m_RTFData;

	//##ModelId=474D308402D0
	CToolTipEx *m_pToolTip;

	//##ModelId=474D308402E0
	CFont m_Font;

	//##ModelId=474D3084032E
	IFormattedTextDraw *m_pFormatter;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CQListCtrl)
	//##ModelId=474D3084034C
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D30850001
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D3085006E
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D308500CC
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=474D3085011A
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//##ModelId=474D30850139
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D30850158
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//##ModelId=474D308501C6
	afx_msg void OnTimer(UINT nIDEvent);
	//##ModelId=474D308501E5
	afx_msg void OnSelectionChange(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D30850205
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//##ModelId=474D30850233
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	//##ModelId=474D30850263
	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	DECLARE_MESSAGE_MAP()
public:
	//##ModelId=474D308502CF
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QLISTCTRL_H__30BEB04A_4B97_4943_BB73_C5128E66B4ED__INCLUDED_)
