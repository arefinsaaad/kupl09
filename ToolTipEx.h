#if !defined(AFX_ToolTipEx_H__5796127D_8817_493F_ACA7_8741A6759DD3__INCLUDED_)
#define AFX_ToolTipEx_H__5796127D_8817_493F_ACA7_8741A6759DD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolTipEx.h : header file
//
#include "RichEditCtrlEx.h"
#include "WndEx.h"
/////////////////////////////////////////////////////////////////////////////
// CToolTipEx window

#define HIDE_WINDOW_TIMER 1

//##ModelId=474D307F0224
class CToolTipEx : public CWnd
{
// Construction
public:
	//##ModelId=474D307F0234
	CToolTipEx();

// Attributes
public:

// Operations
public:
	//##ModelId=474D307F0243
	BOOL OnMsg(MSG* pMsg);
	//##ModelId=474D307F0253
	BOOL Create(CWnd* pParentWnd);
	//##ModelId=474D307F0263
	BOOL Show(CPoint point);
	//##ModelId=474D307F0272
	BOOL Hide();
	//##ModelId=474D307F0291
	void SetToolTipText(const CString &csText);
//	void SetRTFText(const CString &csRTF);
	//##ModelId=474D307F02A1
	void SetRTFText(const char *pRTF);
	//##ModelId=474D307F02A3
	void SetBitmap(CBitmap *pBitmap);
	//##ModelId=474D307F02C0
	void SetNotifyWnd(CWnd *pNotify)		{ m_pNotifyWnd = pNotify;	}
	//##ModelId=474D307F02C2
	void HideWindowInXMilliSeconds(long lms)	{ SetTimer(HIDE_WINDOW_TIMER, lms, NULL); }
	//##ModelId=474D307F02DF
	CRect GetBoundsRect();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipEx)
	protected:
	//##ModelId=474D307F02E0
	virtual void PostNcDestroy();
	//##ModelId=474D307F02EF
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D307F030E
	virtual ~CToolTipEx();
	
protected:
	//##ModelId=474D307F0310
	DWORD m_dwTextStyle;
	//##ModelId=474D307F032D
	CRect m_rectMargin;
	//##ModelId=474D307F033D
	CString m_csText;
	//##ModelId=474D307F034D
	CFont m_Font;
	//##ModelId=474D307F03CA
	CBitmap *m_pBitmap;
	//##ModelId=474D30800030
	CString m_csRTF;

	//##ModelId=474D3080006F
	CRichEditCtrlEx m_RichEdit;

	//##ModelId=474D3080007F
	CWnd *m_pNotifyWnd;

	

protected:
	//##ModelId=474D308000BC
	CString GetFieldFromString(CString ref, int nIndex, TCHAR ch);
	//##ModelId=474D30800149
	BOOL SetLogFont(LPLOGFONT lpLogFont, BOOL bRedraw /*=TRUE*/);
	//##ModelId=474D30800187
	LPLOGFONT GetSystemToolTipFont();
	//##ModelId=474D30800197
	BOOL IsCursorInToolTip();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolTipEx)
	//##ModelId=474D308001B6
	afx_msg void OnPaint();
	//##ModelId=474D308001D5
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=474D30800204
	afx_msg UINT OnNcHitTest(CPoint point);
	//##ModelId=474D30800262
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//##ModelId=474D308002E0
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ToolTipEx_H__5796127D_8817_493F_ACA7_8741A6759DD3__INCLUDED_)
