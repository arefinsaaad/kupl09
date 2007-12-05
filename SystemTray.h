/////////////////////////////////////////////////////////////////////////////
// SystemTray.h : header file
//
// Written by Chris Maunder (cmaunder@mail.com)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 

#ifndef _INCLUDED_SYSTEMTRAY_H_
#define _INCLUDED_SYSTEMTRAY_H_

#define ASSUME_IE5_OR_ABOVE

#ifdef ASSUME_IE5_OR_ABOVE
#	ifndef _WIN32_IE
#		define _WIN32_IE 0x0500    // enable shell v5 features
#	elif _WIN32_IE < 0x0500
#		undef _WIN32_IE
#		define _WIN32_IE 0x0500    // enable shell v5 features
#	endif
#	ifdef NOTIFYICONDATA_V1_SIZE   // If NOTIFYICONDATA_V1_SIZE, then we can use fun stuff
#		define SYSTEMTRAY_USEW2K
#	endif
#endif

#ifndef NIIF_NONE
#define NIIF_NONE 0
#endif

#define WM_CUSTOMIZE_TRAY_MENU	WM_USER + 211

// #include <afxwin.h>
#include <afxtempl.h>
#include <afxdisp.h>    // COleDateTime

/////////////////////////////////////////////////////////////////////////////
// CSystemTray window

//##ModelId=474D302102EF
class CSystemTray : public CWnd
{
// Construction/destruction
public:
	//##ModelId=474D3021031F
    CSystemTray();
	//##ModelId=474D3021034C
    CSystemTray(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID, 
                BOOL bhidden = FALSE,
                LPCTSTR szBalloonTip = NULL, LPCTSTR szBalloonTitle = NULL, 
                DWORD dwBalloonIcon = NIIF_NONE, UINT uBalloonTimeout = 10);
	//##ModelId=474D302103AA
    virtual ~CSystemTray();

    DECLARE_DYNAMIC(CSystemTray)

// Operations
public:
	//##ModelId=474D302103C9
    BOOL Enabled() { return m_bEnabled; }
	//##ModelId=474D302103CA
    BOOL Visible() { return !m_bHidden; }

    // Create the tray icon
	//##ModelId=474D302103D9
    BOOL Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID,
                BOOL bHidden = FALSE,
                LPCTSTR szBalloonTip = NULL, LPCTSTR szBalloonTitle = NULL, 
                DWORD dwBalloonIcon = NIIF_NONE, UINT uBalloonTimeout = 10);

    // Change or retrieve the Tooltip text
	//##ModelId=474D30220030
    BOOL    SetTooltipText(LPCTSTR pszTooltipText);
	//##ModelId=474D3022003F
    BOOL    SetTooltipText(UINT nID);
	//##ModelId=474D3022005E
    CString GetTooltipText() const;

    // Change or retrieve the icon displayed
	//##ModelId=474D3022006E
    BOOL  SetIcon(HICON hIcon);
	//##ModelId=474D3022007E
    BOOL  SetIcon(LPCTSTR lpszIconName);
	//##ModelId=474D3022009D
    BOOL  SetIcon(UINT nIDResource);
	//##ModelId=474D302200AD
    BOOL  SetStandardIcon(LPCTSTR lpIconName);
	//##ModelId=474D302200CC
    BOOL  SetStandardIcon(UINT nIDResource);
	//##ModelId=474D302200DB
    HICON GetIcon() const;

	//##ModelId=474D302200EB
    void  SetFocus();
	//##ModelId=474D3022010A
    BOOL  HideIcon();
	//##ModelId=474D3022011A
    BOOL  ShowIcon();
	//##ModelId=474D30220139
    BOOL  AddIcon();
	//##ModelId=474D30220158
    BOOL  RemoveIcon();
	//##ModelId=474D30220178
    BOOL  MoveToRight();

	//##ModelId=474D30220197
    BOOL ShowBalloon(LPCTSTR szText, LPCTSTR szTitle = NULL,
                     DWORD dwIcon = NIIF_NONE, UINT uTimeout = 10);

    // For icon animation
	//##ModelId=474D302201C6
    BOOL  SetIconList(UINT uFirstIconID, UINT uLastIconID); 
	//##ModelId=474D302201E5
    BOOL  SetIconList(HICON* pHIconList, UINT nNumIcons); 
	//##ModelId=474D30220204
    BOOL  Animate(UINT nDelayMilliSeconds, int nNumSeconds = -1);
	//##ModelId=474D30220214
    BOOL  StepAnimation();
	//##ModelId=474D30220224
    BOOL  StopAnimation();

    // Change menu default item
	//##ModelId=474D30220233
    void GetMenuDefaultItem(UINT& uItem, BOOL& bByPos);
	//##ModelId=474D30220245
    BOOL SetMenuDefaultItem(UINT uItem, BOOL bByPos);

    // Change or retrieve the window to send notification messages to
	//##ModelId=474D30220262
    BOOL  SetNotificationWnd(CWnd* pNotifyWnd);
	//##ModelId=474D30220272
    CWnd* GetNotificationWnd() const;

    // Change or retrieve the window to send menu commands to
	//##ModelId=474D30220274
    BOOL  SetTargetWnd(CWnd* pTargetWnd);
	//##ModelId=474D30220291
    CWnd* GetTargetWnd() const;

    // Change or retrieve  notification messages sent to the window
	//##ModelId=474D30220293
    BOOL  SetCallbackMessage(UINT uCallbackMessage);
	//##ModelId=474D302202A2
    UINT  GetCallbackMessage() const;

	//##ModelId=474D302202B1
    UINT  GetTimerID() const   { return m_nTimerID; }

	//##ModelId=474D302202C0
	void	SetSingleClickSelect(BOOL bSel)	{ m_bSingleClickSelect = bSel; }
	//##ModelId=474D302202C2
	BOOL	GetSingleClickSelect()			{ return m_bSingleClickSelect;	}
	

// Static functions
public:
	//##ModelId=474D302202CF
    static void MinimiseToTray(CWnd* pWnd);
	//##ModelId=474D302202D2
    static void MaximiseFromTray(CWnd* pWnd);

public:
    // Default handler for tray notification message
	//##ModelId=474D302202E1
    virtual LRESULT OnTrayNotification(WPARAM uID, LPARAM lEvent);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSystemTray)
	protected:
	//##ModelId=474D302202F1
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=474D3022030F
    void Initialise();
	//##ModelId=474D3022033D
    void InstallIconPending();

// Implementation
protected:
	//##ModelId=474D3022034D
    NOTIFYICONDATA  m_tnd;
	//##ModelId=474D3022035C
    BOOL            m_bEnabled;         // does O/S support tray icon?
	//##ModelId=474D3022036C
    BOOL            m_bHidden;          // Has the icon been hidden?
	//##ModelId=474D3022037B
    BOOL            m_bRemoved;         // Has the icon been removed?
	//##ModelId=474D3022038B
    BOOL            m_bShowIconPending; // Show the icon once tha taskbar has been created
	//##ModelId=474D3022039B
    BOOL            m_bWin2K;           // Use new W2K features?
	//##ModelId=474D302203BB
	CWnd*           m_pTargetWnd;       // Window that menu commands are sent

	//##ModelId=474D302203C9
    CArray<HICON, HICON> m_IconList;
	//##ModelId=474D302203D9
    UINT         m_uIDTimer;
	//##ModelId=474D30230001
    int          m_nCurrentIcon;
	//##ModelId=474D30230011
    COleDateTime m_StartTime;
	//##ModelId=474D30230030
    int          m_nAnimationPeriod;
	//##ModelId=474D3023003F
    HICON        m_hSavedIcon;
	//##ModelId=474D3023004F
    UINT         m_DefaultMenuItemID;
	//##ModelId=474D3023005E
    BOOL         m_DefaultMenuItemByPos;
	//##ModelId=474D3023007E
	UINT         m_uCreationFlags;
	//##ModelId=474D3023008D
	BOOL		 m_bSingleClickSelect;
	
// Static data
protected:
	//##ModelId=474D302300AD
    static BOOL RemoveTaskbarIcon(CWnd* pWnd);

	//##ModelId=474D302300CC
    static const UINT m_nTimerID;
	//##ModelId=474D3023010A
    static UINT  m_nMaxTooltipLength;
	//##ModelId=474D30230139
    static const UINT m_nTaskbarCreatedMsg;
	//##ModelId=474D30230169
    static CWnd  m_wndInvisible;
	//##ModelId=474D30230197
	static BOOL	 m_bShowWndAnimation;

	//##ModelId=474D302301C6
    static BOOL GetW2K();
#ifndef _WIN32_WCE
	//##ModelId=474D302301D5
    static void GetTrayWndRect(LPRECT lprect);
	//##ModelId=474D302301E5
    static BOOL GetDoWndAnimation();
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CSystemTray)
	//##ModelId=474D302301E7
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
#ifndef _WIN32_WCE
	//##ModelId=474D30230204
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
#endif
	//##ModelId=474D30230224
    LRESULT OnTaskbarCreated(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
};


#endif

/////////////////////////////////////////////////////////////////////////////
