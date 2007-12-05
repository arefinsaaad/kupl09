#pragma once

#include "EditWnd.h"
#include "ClipIds.h"

#include "DittoWindow.h"

//##ModelId=474D306A012A
class CEditFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CEditFrameWnd)
	//##ModelId=474D306A014A
	CEditFrameWnd();

	//##ModelId=474D306A0168
	bool EditIds(CClipIDs &Ids);
	//##ModelId=474D306A01A7
	void SetNotifyWnd(HWND hWnd)	{ m_hNotifyWnd = hWnd; }
	//##ModelId=474D306A01C7
	bool CloseAll();

protected:
	//##ModelId=474D306A01D5
	virtual ~CEditFrameWnd();

	//##ModelId=474D306A01E6
	CEditWnd m_EditWnd;
	//##ModelId=474D306A01F5
	HWND m_hNotifyWnd;
	//##ModelId=474D306A0225
	CDittoWindow m_DittoWindow;
	//##ModelId=474D306A0229
	CRect m_crIcon;

protected:
	DECLARE_MESSAGE_MAP()

	//##ModelId=474D306A0252
	void MoveControls();

public:
	//##ModelId=474D306A0253
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D306A0264
	afx_msg void OnDestroy();
	//##ModelId=474D306A0273
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=474D306A02A2
	afx_msg void OnDummy();
	//##ModelId=474D306A02C1
	afx_msg void OnNcPaint();
	//##ModelId=474D306A02D0
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//##ModelId=474D306A02E1
	afx_msg UINT OnNcHitTest(CPoint point);
protected:
	//##ModelId=474D306A031E
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	//##ModelId=474D306A033D
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//##ModelId=474D306A034C
	afx_msg void OnClose();
	//##ModelId=474D306A034E
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//##ModelId=474D306A036C
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	//##ModelId=474D306A03BA
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	//##ModelId=474D306A03D9
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//##ModelId=474D306B0001
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
};


