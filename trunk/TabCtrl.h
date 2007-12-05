#pragma once

#include <afxtempl.h>

#define SHEET_CLASSNAME		_T("_TabCtrlClass_")
#define SHEET_CLASSTYLE		(CS_DBLCLKS)

// Sheet styles
#define SCS_SHEET			0x0000
#define SCS_TAB				0x0001
#define SCS_TOP				0x0002
#define SCS_BOTTOM			0x0004
#define SCS_BOLD			0x0008
#define SCS_BORDER			0x0010

#define SN_SETACTIVETAB		WM_APP + 1122

//##ModelId=474D301E0139
typedef struct tagNMTABCHANGE{
    NMHDR hdr;
    long lOldTab;
    long lNewTab;
	long lOldItemData;
	long lNewItemData;
} NMTABCHANGE, FAR *LPNMTABCHANGE;

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlEx window

//##ModelId=474D301E0252
class CTabCtrlEx : public CWnd
{
// Construction
public:
	//##ModelId=474D301E0263
	CTabCtrlEx();

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabCtrlEx)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D301E0281
	virtual ~CTabCtrlEx();

	// Create the sheet control
	//##ModelId=474D301E0291
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// Add a new window to the sheet. Returns the index of the new tab, -1 on error
	//##ModelId=474D301E02DF
	bool AddItem(const CString& csTabTitle, CWnd* pTabWnd);

	// Insert a new window in the sheet. Returns the index of the new tab, -1 on error
	//##ModelId=474D301E02FE
	bool InsertItem(int nTab, const CString& csTabTitle, CWnd* pTabWnd);
	
	//Replaces the window in nTab position -- Calls HideWindow for the old and ShowWindow for the new
	//##ModelId=474D301E032D
	bool ReplaceItem(int nTab, const CString &csTabTitle, CWnd* pTabWnd);

	// Delete a tab in the sheet
	//##ModelId=474D301E035C
	bool DeleteItem(int nTab);

	// Delete all tabs in the sheet
	//##ModelId=474D301E039B
	bool DeleteAllItems();
	
	// Get/Set the tab title
	//##ModelId=474D301E03BA
	CString GetTabTitle(int nTab);
	//##ModelId=474D301E03D9
	bool SetTabTitle(int nTab, const CString& csTabTitle);

	// Get the active sheet
	//##ModelId=474D301F0010
	int GetActiveTab();

	// Get the number of tabs
	//##ModelId=474D301F0030
	int GetTabCount();

	// Set the active tab and make the tab title visible
	//##ModelId=474D301F003F
	void SetActiveTab(int nTab, bool bNotify = true);

	//##ModelId=474D301F005E
	bool SetTabItemData(int nTab, long lItemData);
	//##ModelId=474D301F007E
	long GetTabItemData(int nTab);

	// Make a tab title visible
	//##ModelId=474D301F008D
	void MakeTabVisible(int nTab);
	
	// Set the tab height
	//##ModelId=474D301F009E
	void SetTabHeight(int nTabHeight);

	// Relay keyboard events for the sheet to process,
	// returns TRUE if the message was processed, DO NOT process this message
	// return FALSE if the message was not processed
	//##ModelId=474D301F00BC
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Underline a tab title, use color -1 to remove underline
	//##ModelId=474D301F00CC
	void UnderlineTabTitle(int nTab, COLORREF clr);

	//##ModelId=474D301F00DB
	void SetFocusToNewlySelectedTab(bool bVal)	{ m_bSetFocusToNewlySelectedTab = bVal;	}
	//##ModelId=474D301F00EC
	bool GetFocusToNewlySelectedTab()			{ return m_bSetFocusToNewlySelectedTab;	}

	//##ModelId=474D301F00FB
	void SetTabColors(COLORREF Selected, COLORREF NonSelected)	{ m_SelectedColor = Selected; m_NonSelectedColor = NonSelected;}

protected:
	//##ModelId=474D3021011A
	class CTab
	{
	public:
		//##ModelId=474D30210139
		CTab()
		{
			lItemData = -1;
		}
		//##ModelId=474D3021013A
		CString csTitle;
		//##ModelId=474D3021014A
		CWnd* pWnd;
		//##ModelId=474D30210159
		long lWidth;
		//##ModelId=474D30210168
		COLORREF clrUnderline;
		//##ModelId=474D30210178
		long lItemData;
	};

	//##ModelId=474D30210187
	typedef enum {ArrowLeft, ArrowRight} ButtonStyle;
	//##ModelId=474D30210197
	typedef enum {BtnDown, BtnUp/*, BtnHover*/} ButtonState;
		

protected:
	//##ModelId=474D301F010A
	short m_nStyle;
	//##ModelId=474D301F0234
	CArray <CTab, CTab&> m_Tabs;
	//##ModelId=474D301F0243
	int m_nActiveTab;
	//##ModelId=474D301F0252
	int m_nTabHeight;
	//##ModelId=474D301F0263
	CBrush m_brSelectedTab;
	//##ModelId=474D301F0282
	CBrush m_brNonSelectedTab;
	//##ModelId=474D301F02A2
	CPen m_penGray;
	//##ModelId=474D301F02B1
	CPen m_penBlack;
	CFont *m_pFntText, *m_pFntBoldText;
	//##ModelId=474D301F02D0
	ButtonState m_btnState[2];
	//##ModelId=474D301F02DF
	bool m_bBtnEnabled[2];
	//##ModelId=474D301F02EF
	int m_nLeftShifted;
	//##ModelId=474D301F02FE
	int m_nPrevWidth;
	//##ModelId=474D301F031E
	bool m_bSetFocusToNewlySelectedTab;
	//##ModelId=474D301F034C
	COLORREF m_SelectedColor;
	//##ModelId=474D301F036C
	COLORREF m_NonSelectedColor;

	
protected:
	//##ModelId=474D30200010
	int GetTextWidth(const CString& csText);
	//##ModelId=474D3020003F
	int GetDisplayWidth();
	//##ModelId=474D3020006E
	int GetTabsWidth();
	//##ModelId=474D3020007E
	int GetSpinnerWidth();
	
	//##ModelId=474D3020008D
	void GetFullRect(CRect& rcTab);
	//##ModelId=474D302000AD
	void GetTabListRect(CRect& rcTab);
	//##ModelId=474D302000DB
	void GetTabRect(int nTab, CRect& rcTab);
	//##ModelId=474D302000FB
	void GetSpinnerRect(CRect& rcButton);
	//##ModelId=474D3020011A
	void GetButtonRect(int nBtn, CRect& rcBtn);

	//##ModelId=474D30200139
	void EnableSpinners();
	//##ModelId=474D30200149
	void DrawTabs(CDC *pDC);
	//##ModelId=474D30200168
	void DrawBar(CDC* pDC);
	//##ModelId=474D30200178
	void DrawTab(int nTab, CDC *pDC, CRect& rcTab);
	//##ModelId=474D30200198
	void DrawTabEx(int nTab, CDC *pDC, CRect& rcTab);
	//##ModelId=474D302001F5
	void DrawSpinner(CDC *pDC);
	//##ModelId=474D30200214
	void DrawButton(CDC *pDC, CRect& rcBtn, ButtonState btnState, ButtonStyle btnStyle, bool bEnable);
	//##ModelId=474D30200252
	void ScrollTab(CPoint point);
	
	//##ModelId=474D30200262
	void ActivateTab(int nTab, bool bNotify, bool bOnSize = false);
	//##ModelId=474D30200291
	void ResizeTabWindow(int nOldTab, int nNewTab, bool bNotify, bool bOnSize);
	//##ModelId=474D302002C0
	void SwitchTabs(bool bNext = true);
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CTabCtrlEx)
	//##ModelId=474D302002CF
	afx_msg void OnPaint();
	//##ModelId=474D302002DF
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D3020030E
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//##ModelId=474D3020033D
	afx_msg void OnTimer(UINT nIDEvent);
	//##ModelId=474D3020034C
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//##ModelId=474D3020036C
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//##ModelId=474D3020038C
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=474D302003BA
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
