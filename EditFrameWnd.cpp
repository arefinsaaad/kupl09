// EditFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CP_Main.h"
#include "EditFrameWnd.h"
#include ".\editframewnd.h"


// CEditFrameWnd

IMPLEMENT_DYNCREATE(CEditFrameWnd, CFrameWnd)

//##ModelId=474D306A014A
CEditFrameWnd::CEditFrameWnd()
{
	m_bAutoMenuEnable = FALSE;
}

//##ModelId=474D306A01D5
CEditFrameWnd::~CEditFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CEditFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON_SAVE, OnDummy)
	ON_COMMAND(ID_BUTTON_SAVE_ALL, OnDummy)
	ON_COMMAND(ID_BUTTON_CLOSE, OnDummy)
	ON_COMMAND(ID_BUTTON_NEW, OnDummy)
	ON_COMMAND(ID_BUTTON_SAVE_CLOSE_CLIPBOARD, OnDummy)
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()


// CEditFrameWnd message handlers

//##ModelId=474D306A0253
int CEditFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(WS_CAPTION|WS_BORDER|WS_OVERLAPPED|0x0000C000|WS_THICKFRAME|WS_DLGFRAME|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX, 0, SWP_DRAWFRAME); 
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, 0);
		
	CString csTitle = theApp.m_Language.GetString("Ditto_Edit", "Ditto Edit");
	m_EditWnd.Create(NULL, csTitle, WS_CHILD, CRect(0, 0, 0, 0), this, 100, NULL);
	m_EditWnd.ShowWindow(SW_SHOW);

	MoveControls();   

	m_DittoWindow.DoCreate(this);
	m_DittoWindow.m_bDrawChevron = false;
	m_DittoWindow.SetCaptionColors(::GetSysColor(COLOR_ACTIVECAPTION), ::GetSysColor(COLOR_GRADIENTACTIVECAPTION));
	m_DittoWindow.SetCaptionOn(this, CAPTION_TOP, true);

	m_crIcon.SetRect(-2, -15, 15, 0);

	SetWindowText(_T("Ditto Editor"));

	return 0;
}

//##ModelId=474D306A0264
void CEditFrameWnd::OnDestroy()
{
	CFrameWnd::OnDestroy();

	CRect rect;
	GetWindowRect(&rect);
	CGetSetOptions::SetEditWndSize(rect.Size());
	CGetSetOptions::SetEditWndPoint(rect.TopLeft());

	::SendMessage(m_hNotifyWnd, WM_EDIT_WND_CLOSING, 0, 0);
}

//##ModelId=474D306A0273
void CEditFrameWnd::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	m_DittoWindow.DoSetRegion(this);

	MoveControls();
}

//##ModelId=474D306A0252
void CEditFrameWnd::MoveControls()
{
	if(::IsWindow(m_EditWnd.GetSafeHwnd()))
	{
		CRect cr;
		GetClientRect(cr);
		m_EditWnd.MoveWindow(cr);
	}
}

//##ModelId=474D306A0168
bool CEditFrameWnd::EditIds(CClipIDs &Ids)
{
	return m_EditWnd.EditIds(Ids);
}
//##ModelId=474D306A031E
BOOL CEditFrameWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	if(cs.hMenu!=NULL)  
	{
		::DestroyMenu(cs.hMenu);      // delete menu if loaded
		cs.hMenu = NULL;              // no menu for this window
	}

	WNDCLASS wc;	
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = AfxWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = AfxGetInstanceHandle();
	wc.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName =  NULL;
	wc.lpszClassName = _T("Ditto Edit Wnd");

	// Create the QPaste window class
	if (!AfxRegisterClass(&wc))
		return FALSE;

	cs.lpszClass = wc.lpszClassName;

	return CFrameWnd::PreCreateWindow(cs);
}

//##ModelId=474D306A02A2
void CEditFrameWnd::OnDummy()
{

}


//##ModelId=474D306A033D
void CEditFrameWnd::OnSetFocus(CWnd* pOldWnd)
{
	CFrameWnd::OnSetFocus(pOldWnd);

	m_EditWnd.SetFocus();
}

//##ModelId=474D306A034C
void CEditFrameWnd::OnClose()
{
	if(m_EditWnd.CloseEdits(true) == false)
		return;

	CFrameWnd::OnClose();
}

//##ModelId=474D306A02D0
void CEditFrameWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);

	m_DittoWindow.DoNcCalcSize(bCalcValidRects, lpncsp);
}

//##ModelId=474D306A02C1
void CEditFrameWnd::OnNcPaint()
{
	m_DittoWindow.DoNcPaint(this);	
}

//##ModelId=474D306A02E1
UINT CEditFrameWnd::OnNcHitTest(CPoint point) 
{
	UINT Ret = m_DittoWindow.DoNcHitTest(this, point);
	if(Ret == -1)
		return CWnd::OnNcHitTest(point);

	return Ret;
}
//##ModelId=474D306A034E
void CEditFrameWnd::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	m_DittoWindow.DoNcLButtonDown(this, nHitTest, point);

	CFrameWnd::OnNcLButtonDown(nHitTest, point);
}

//##ModelId=474D306A036C
void CEditFrameWnd::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	if(m_DittoWindow.DoNcLButtonUp(this, nHitTest, point) > 0)
		return;

	CFrameWnd::OnNcLButtonUp(nHitTest, point);
}

//##ModelId=474D306A03BA
void CEditFrameWnd::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	m_DittoWindow.DoNcMouseMove(this, nHitTest, point);

	CFrameWnd::OnNcMouseMove(nHitTest, point);
}

//##ModelId=474D306A03D9
BOOL CEditFrameWnd::PreTranslateMessage(MSG* pMsg)
{
	m_DittoWindow.DoPreTranslateMessage(pMsg);

	return CFrameWnd::PreTranslateMessage(pMsg);
}

//##ModelId=474D306A01C7
bool CEditFrameWnd::CloseAll()
{
	return m_EditWnd.CloseEdits(true);
}
//##ModelId=474D306B0001
void CEditFrameWnd::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	CPoint pt(point);
	ScreenToClient(&pt);
	if(m_crIcon.PtInRect(pt))
	{
		CloseAll();
		OnClose();
		return;
	}

	CFrameWnd::OnNcLButtonDblClk(nHitTest, point);
}
