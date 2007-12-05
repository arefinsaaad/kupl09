// WndEx.cpp : implementation file
//

#include "stdafx.h"
#include "CP_Main.h"
#include "WndEx.h"
#include ".\wndex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndEx

#define CLOSE_WIDTH			12
#define CLOSE_HEIGHT		11
#define CLOSE_BORDER		2
#define TIMER_AUTO_MAX		5
#define TIMER_AUTO_MIN		6

//##ModelId=474D307E033D
CWndEx::CWndEx()
{	
	SetCaptionColorActive(false, theApp.GetConnectCV());
	m_crFullSizeWindow.SetRectEmpty();
}

//##ModelId=474D307F006E
CWndEx::~CWndEx()
{
}

//##ModelId=474D307E038C
void CWndEx::InvalidateNc()
{
	::RedrawWindow( m_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_NOCHILDREN );
}

//##ModelId=474D307F0002
void CWndEx::GetWindowRectEx(LPRECT lpRect)
{
	if(m_DittoWindow.m_bMinimized)
	{
		*lpRect = m_crFullSizeWindow;
		return;
	}
	
	CWnd::GetWindowRect(lpRect);
}

//##ModelId=474D307E037B
bool CWndEx::SetCaptionColors( COLORREF left, COLORREF right )
{
	m_DittoWindow.SetCaptionColors(left, right);
	
	return true;
}

BEGIN_MESSAGE_MAP(CWndEx, CWnd)
//{{AFX_MSG_MAP(CWndEx)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_INITMENUPOPUP() 
//}}AFX_MSG_MAP
ON_WM_SIZE()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndEx message handlers

//##ModelId=474D307E033E
BOOL CWndEx::Create(const CRect& crStart, CWnd* pParentWnd)
{
	WNDCLASS wc;	
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = AfxWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = AfxGetInstanceHandle();
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName =  NULL;
	wc.lpszClassName = _T("QPasteClass");
	
	// Create the QPaste window class
	if (!AfxRegisterClass(&wc))
		return FALSE;
	
	return CWndEx::CreateEx(0, _T("QPasteClass"), _T("Quick Paste"), WS_POPUP,
		crStart, pParentWnd, 0);
}

//##ModelId=474D307F007E
int CWndEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_DittoWindow.DoCreate(this);
	m_DittoWindow.m_bDrawMinimize = false;
	m_DittoWindow.m_bDrawMaximize = false;

	SetAutoHide(CGetSetOptions::GetAutoHide());
	SetCaptionColorActive(false, theApp.GetConnectCV());
	m_DittoWindow.SetCaptionOn(this, CGetSetOptions::GetCaptionPos(), true);
	
	return 0;
}

//##ModelId=474D307F0010
bool CWndEx::SetCaptionColorActive(bool bActive, bool ConnectedToClipboard)
{
	bool bResult;

	if(ConnectedToClipboard == false)
	{
		bResult = SetCaptionColors(RGB(255, 0, 0), RGB(255, 0, 0));
	}
	else
	{
		if(bActive)
			bResult = SetCaptionColors(::GetSysColor(COLOR_ACTIVECAPTION), ::GetSysColor(COLOR_GRADIENTACTIVECAPTION));
		else
			bResult = SetCaptionColors(::GetSysColor(COLOR_INACTIVECAPTION), ::GetSysColor(COLOR_GRADIENTINACTIVECAPTION));
	}

	return bResult;
}

//##ModelId=474D307E03C9
void CWndEx::SetAutoHide(BOOL bAutoHide)
{
	if(bAutoHide)
	{
		SetTimer(TIMER_AUTO_MIN, 500, NULL);
	}
	else
	{
		KillTimer(TIMER_AUTO_MIN);
	}
}

//##ModelId=474D307E039B
void CWndEx::SetCaptionOn(int nPos, bool bOnstartup)
{
	m_DittoWindow.SetCaptionOn(this, nPos, bOnstartup);
}

//##ModelId=474D307F008F
void CWndEx::OnNcPaint()
{
	m_DittoWindow.DoNcPaint(this);
}

//##ModelId=474D307F00AD
void CWndEx::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
	
	m_DittoWindow.DoNcCalcSize(bCalcValidRects, lpncsp);
}

//##ModelId=474D307F00CC
UINT CWndEx::OnNcHitTest(CPoint point) 
{
	UINT Ret = m_DittoWindow.DoNcHitTest(this, point);
	if(Ret == -1)
		return CWnd::OnNcHitTest(point);

	return Ret;
}

//##ModelId=474D307F00EB
void CWndEx::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	m_DittoWindow.DoNcLButtonDown(this, nHitTest, point);

	CWnd::OnNcLButtonDown(nHitTest, point);
}

//##ModelId=474D307F0139
void CWndEx::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	long lRet = m_DittoWindow.DoNcLButtonUp(this, nHitTest, point);
	if(lRet > 0)
	{
		if(lRet == BUTTON_CHEVRON)
		{
			MinMaxWindow();
		}
		return;
	}
	
	CWnd::OnNcLButtonUp(nHitTest, point);
}

//##ModelId=474D307E03D9
void CWndEx::MinMaxWindow(long lOption)
{
	if((m_DittoWindow.m_bMinimized) && (lOption == FORCE_MIN))
		return;
	
	if((m_DittoWindow.m_bMinimized == false) && (lOption == FORCE_MAX))
		return;
	
	if(m_DittoWindow.m_lRightBorder == CAPTION_BORDER)
	{		
		if(m_DittoWindow.m_bMinimized == false)
		{
			GetWindowRect(m_crFullSizeWindow);
			MoveWindow(m_crFullSizeWindow.right - CAPTION_BORDER, 
				m_crFullSizeWindow.top, CAPTION_BORDER, 
				m_crFullSizeWindow.Height());
			m_DittoWindow.m_bMinimized = true;
			OnNcPaint();
		}
		else
		{
			CRect cr;
			GetWindowRect(cr);
			MoveWindow(cr.right - m_crFullSizeWindow.Width(),
				cr.top, m_crFullSizeWindow.Width(), cr.Height());
			
			m_crFullSizeWindow.SetRectEmpty();
			m_DittoWindow.m_bMinimized = false;
			OnNcPaint();
		}
	}
	if(m_DittoWindow.m_lLeftBorder == CAPTION_BORDER)
	{
		if(m_DittoWindow.m_bMinimized == false)
		{
			GetWindowRect(m_crFullSizeWindow);
			MoveWindow(m_crFullSizeWindow.left,
				m_crFullSizeWindow.top, CAPTION_BORDER, 
				m_crFullSizeWindow.Height());
			m_DittoWindow.m_bMinimized = true;
			OnNcPaint();
		}
		else
		{
			CRect cr;
			GetWindowRect(cr);
			MoveWindow(cr.left, cr.top, 
				m_crFullSizeWindow.Width(), cr.Height());
			
			m_crFullSizeWindow.SetRectEmpty();
			m_DittoWindow.m_bMinimized = false;
			OnNcPaint();
		}
	}
	else if(m_DittoWindow.m_lTopBorder == CAPTION_BORDER)
	{
		if(m_DittoWindow.m_bMinimized == false)
		{
			GetWindowRect(m_crFullSizeWindow);
			MoveWindow(m_crFullSizeWindow.left,
				m_crFullSizeWindow.top, 
				m_crFullSizeWindow.Width(), 
				CAPTION_BORDER);
			m_DittoWindow.m_bMinimized = true;
			OnNcPaint();
		}
		else
		{
			CRect cr;
			GetWindowRect(cr);
			MoveWindow(cr.left, cr.top, 
				cr.Width(), m_crFullSizeWindow.Height());
			
			m_crFullSizeWindow.SetRectEmpty();
			m_DittoWindow.m_bMinimized = false;
			OnNcPaint();
		}
	}
	else if(m_DittoWindow.m_lBottomBorder == CAPTION_BORDER)
	{
		if(m_DittoWindow.m_bMinimized == false)
		{
			GetWindowRect(m_crFullSizeWindow);
			MoveWindow(m_crFullSizeWindow.left,
				m_crFullSizeWindow.bottom - CAPTION_BORDER, 
				m_crFullSizeWindow.Width(), 
				CAPTION_BORDER);
			m_DittoWindow.m_bMinimized = true;
			OnNcPaint();
		}
		else
		{
			CRect cr;
			GetWindowRect(cr);
			MoveWindow(cr.left, 
				cr.bottom - m_crFullSizeWindow.Height(), 
				cr.Width(), m_crFullSizeWindow.Height());
			
			m_crFullSizeWindow.SetRectEmpty();
			m_DittoWindow.m_bMinimized = false;
			OnNcPaint();
		}
	}
}

//##ModelId=474D307F010B
void CWndEx::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	m_DittoWindow.DoNcMouseMove(this, nHitTest, point);

	if((m_bMaxSetTimer == false) && m_DittoWindow.m_bMinimized)
	{
		SetTimer(TIMER_AUTO_MAX, 250, NULL);
		m_bMaxSetTimer = true;
	}
	
	CWnd::OnNcMouseMove(nHitTest, point);
}

//##ModelId=474D307E035C
BOOL CWndEx::PreTranslateMessage(MSG* pMsg) 
{
	m_DittoWindow.DoPreTranslateMessage(pMsg);
	
	return CWnd::PreTranslateMessage(pMsg);
}

//##ModelId=474D307F0158
BOOL CWndEx::OnEraseBkgnd(CDC* pDC) 
{
	return CWnd::OnEraseBkgnd(pDC);
}

//##ModelId=474D307F0168
void CWndEx::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == TIMER_AUTO_MAX)
	{
		if(m_DittoWindow.m_bMinimized)
		{
			CPoint cp;
			GetCursorPos(&cp);
			
			UINT nHitTest = OnNcHitTest(cp);
			
			ScreenToClient(&cp);
			
			if(nHitTest == HTCAPTION)
			{
				if(m_DittoWindow.m_crCloseBT.PtInRect(cp) == false)
				{
					if(m_DittoWindow.m_crMinimizeBT.PtInRect(cp) == false)
					{
						MinMaxWindow(FORCE_MAX);
					}
				}
			}
		}
		KillTimer(TIMER_AUTO_MAX);
		m_bMaxSetTimer = false;
	}
	else if(nIDEvent == TIMER_AUTO_MIN)
	{
		if((m_DittoWindow.m_bMinimized == false) && (g_Opt.m_bShowPersistent))
		{
			CPoint cp;
			CRect cr;
			
			GetCursorPos(&cp);
			GetWindowRect(&cr);
			
			if(cr.PtInRect(cp) == false)        
			{
				//theApp.m_bDittoHasFocus is only set when we are using the 
				//hook dll
				if(g_Opt.m_bUseHookDllForFocus)
				{
					if(theApp.m_bDittoHasFocus == false)
					{
						MinMaxWindow(FORCE_MIN);
					}
				}
			}
		}
	}
	
	CWnd::OnTimer(nIDEvent);
}

//##ModelId=474D307F0187
void CWndEx::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CWnd::OnWindowPosChanging(lpwndpos);
	
	if(m_bMaxSetTimer)
	{
		KillTimer(TIMER_AUTO_MAX);
		m_bMaxSetTimer = false;
	}
}


//##ModelId=474D307F01C6
void CWndEx::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	
	m_DittoWindow.DoSetRegion(this);
}


//##ModelId=474D307F0199
void CWndEx::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{
    ASSERT(pPopupMenu != NULL);
    // Check the enabled state of various menu items.
	
    CCmdUI state;
    state.m_pMenu = pPopupMenu;
    ASSERT(state.m_pOther == NULL);
    ASSERT(state.m_pParentMenu == NULL);
	
    // Determine if menu is popup in top-level menu and set m_pOther to
    // it if so (m_pParentMenu == NULL indicates that it is secondary popup).
    HMENU hParentMenu;
    if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
	{
        state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	}
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
    {
        CWnd* pParent = this;
		// Child windows don't have menus--need to go to the top!
        if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
        {
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
        }
    }
	
    state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	state.m_nIndex++)
    {
        state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
        if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.
		
        ASSERT(state.m_pOther == NULL);
        ASSERT(state.m_pMenu != NULL);
        if (state.m_nID == (UINT)-1)
        {
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
        }
        else
        {
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
        }
		
        // Adjust for menu deletions and additions.
        UINT nCount = pPopupMenu->GetMenuItemCount();
        if (nCount < state.m_nIndexMax)
        {
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
        }
        state.m_nIndexMax = nCount;
    }
} 
