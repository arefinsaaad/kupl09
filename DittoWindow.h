#pragma once

#define BUTTON_CLOSE 1
#define BUTTON_CHEVRON 2
#define BUTTON_MINIMIZE 3
#define BUTTON_MAXIMIZE 4

#define BORDER 2 
#define CAPTION_BORDER 16 

//##ModelId=474D306B008D
class CDittoWindow
{
public:
	//##ModelId=474D306B009D
	CDittoWindow(void);
	//##ModelId=474D306B00AD
	~CDittoWindow(void);

	//##ModelId=474D306B00CC
	void DoNcPaint(CWnd *pWnd);
	//##ModelId=474D306B00DB
	void DrawChevronBtn(CWindowDC &dc);
	//##ModelId=474D306B00EC
	void DrawCloseBtn(CWindowDC &dc);
	//##ModelId=474D306B011B
	void DrawMaximizeBtn(CWindowDC &dc);
	//##ModelId=474D306B0149
	void DrawMinimizeBtn(CWindowDC &dc);

	//##ModelId=474D306B0168
	void DoCreate(CWnd *pWnd);
	//##ModelId=474D306B0187
	void DoNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//##ModelId=474D306B01E5
	UINT DoNcHitTest(CWnd *pWnd, CPoint point);
	//##ModelId=474D306B0204
	void DoSetRegion(CWnd *pWnd);
	//##ModelId=474D306B0233
	long DoNcLButtonUp(CWnd *pWnd, UINT nHitTest, CPoint point);
	//##ModelId=474D306B0253
	void DoNcLButtonDown(CWnd *pWnd, UINT nHitTest, CPoint point);
	//##ModelId=474D306B0264
	void DoNcMouseMove(CWnd *pWnd, UINT nHitTest, CPoint point) ;
	//##ModelId=474D306B0275
	bool DoPreTranslateMessage(MSG* pMsg);
	//##ModelId=474D306B02B0
	void SetCaptionOn(CWnd *pWnd, int nPos, bool bOnstartup);
	//##ModelId=474D306B02CF
	bool SetCaptionColors(COLORREF left, COLORREF right);
	//##ModelId=474D306B02DF
	bool SetCaptionColorActive(bool bActive, bool ConnectedToClipboard);

	//##ModelId=474D306B02EF
	long m_lTopBorder;
	//##ModelId=474D306B030E
	long m_lRightBorder;
	//##ModelId=474D306B033D
	long m_lBottomBorder;
	//##ModelId=474D306B034C
	long m_lLeftBorder;

	//##ModelId=474D306B035C
	bool m_bDrawClose;
	//##ModelId=474D306B038B
	bool m_bDrawChevron;
	//##ModelId=474D306B039B
	bool m_bDrawMaximize;
	//##ModelId=474D306B03AA
	bool m_bDrawMinimize;

	//##ModelId=474D306B03BA
	CRect m_crCloseBT;
	//##ModelId=474D306B03C9
	CRect m_crChevronBT;
	//##ModelId=474D306B03CA
	CRect m_crMaximizeBT;
	//##ModelId=474D306C0020
	CRect m_crMinimizeBT;

	//##ModelId=474D306C0031
	CFont m_VertFont;
	//##ModelId=474D306C0050
	CFont m_HorFont;

	//##ModelId=474D306C008D
	bool m_bMinimized;

	//##ModelId=474D306C00EB
	bool m_bMouseDownOnChevron;
	//##ModelId=474D306C0139
	bool m_bMouseOverChevron;
	//##ModelId=474D306C0178
	bool m_bMouseDownOnClose;
	//##ModelId=474D306C01E5
	bool m_bMouseOverClose;
	//##ModelId=474D306C0204
	bool m_bMouseDownOnCaption;
	//##ModelId=474D306C0233
	bool m_bMouseDownOnMinimize;
	//##ModelId=474D306C0243
	bool m_bMouseOverMinimize;
	//##ModelId=474D306C0252
	bool m_bMouseDownOnMaximize;
	//##ModelId=474D306C0262
	bool m_bMouseOverMaximize;

	//##ModelId=474D306C0272
	COLORREF m_CaptionColorLeft;
	//##ModelId=474D306C02A1
	COLORREF m_CaptionColorRight;
};
