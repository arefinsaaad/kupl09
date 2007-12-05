#if !defined(AFX_WNDEX_H__E14EA019_CE71_469A_AEB4_3D3CB271C531__INCLUDED_)
#define AFX_WNDEX_H__E14EA019_CE71_469A_AEB4_3D3CB271C531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndEx.h : header file
//

#include "DittoWindow.h"

#define	SWAP_MIN_MAX			1
#define FORCE_MIN				2
#define FORCE_MAX				3

//##ModelId=474D307E031E
class CWndEx : public CWnd
{
// Construction
public:
	//##ModelId=474D307E033D
	CWndEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndEx)
	public:
	//##ModelId=474D307E033E
	virtual BOOL Create(const CRect& crStart, CWnd* pParentWnd);
	//##ModelId=474D307E035C
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

public:
	//##ModelId=474D307E037B
	bool SetCaptionColors( COLORREF left, COLORREF right );
	//##ModelId=474D307E038C
	void InvalidateNc();
	//##ModelId=474D307E039B
	void SetCaptionOn(int nPos, bool bOnstartup = false);
	//##ModelId=474D307E03C9
	void SetAutoHide(BOOL bAutoHide);
	//##ModelId=474D307E03D9
	void MinMaxWindow(long lOption = SWAP_MIN_MAX);
	//##ModelId=474D307F0002
	void GetWindowRectEx(LPRECT lpRect);
	//##ModelId=474D307F0010
	bool SetCaptionColorActive(bool bActive, bool ConnectedToClipboard);

protected:
	//##ModelId=474D307F0031
	CDittoWindow m_DittoWindow;
	//##ModelId=474D307F004F
	CRect m_crFullSizeWindow;
	//##ModelId=474D307F005E
	bool m_bMaxSetTimer;

// Implementation
public:
	//##ModelId=474D307F006E
	virtual ~CWndEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndEx)
	//##ModelId=474D307F007E
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D307F008F
	afx_msg void OnNcPaint();
	//##ModelId=474D307F00AD
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//##ModelId=474D307F00CC
	afx_msg UINT OnNcHitTest(CPoint point);
	//##ModelId=474D307F00EB
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//##ModelId=474D307F010B
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	//##ModelId=474D307F0139
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	//##ModelId=474D307F0158
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//##ModelId=474D307F0168
	afx_msg void OnTimer(UINT nIDEvent);
	//##ModelId=474D307F0187
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	//##ModelId=474D307F0199
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//##ModelId=474D307F01C6
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDEX_H__E14EA019_CE71_469A_AEB4_3D3CB271C531__INCLUDED_)
