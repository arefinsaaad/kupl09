#if !defined(AFX_COPYTHREAD_H__C6766F04_0111_4314_986A_A0E02FF3B322__INCLUDED_)
#define AFX_COPYTHREAD_H__C6766F04_0111_4314_986A_A0E02FF3B322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClipboardViewer.h"

//##ModelId=474D307200DB
struct CCopyConfig
{
public:
	// WM_CLIPBOARD_COPIED is sent to this window when a copy is made.
	//##ModelId=474D3072010A
	HWND        m_hClipHandler;
	// true to use PostMessage (asynchronous)
	// false to use SendMessage (synchronous)
	//##ModelId=474D3072011A
	bool        m_bAsyncCopy;
	// true to create a copy of the clipboard contents when it changes
	// false to ignore changes in the clipboard
	//##ModelId=474D30720149
	bool        m_bCopyOnChange;
	// the supported types which are copied from the clipboard when it changes.
	//##ModelId=474D30720169
	CClipTypes* m_pSupportedTypes; // ONLY accessed from CopyThread

	//##ModelId=474D30720187
	CCopyConfig( HWND hClipHandler = NULL,
	             bool bAsyncCopy = false,
				 bool bCopyOnChange = false,
				 CClipTypes* pSupportedTypes = NULL )
	{
		m_hClipHandler = hClipHandler;
		m_bAsyncCopy = bAsyncCopy;
		m_bCopyOnChange = bCopyOnChange;
		m_pSupportedTypes = pSupportedTypes;
	}

	//##ModelId=474D30720252
	void DeleteTypes()
	{
		if( m_pSupportedTypes )
		{
			delete m_pSupportedTypes;
			m_pSupportedTypes = NULL;
		}
	}
};

//##ModelId=474D307202B0
class CCopyThread : public CWinThread
{
	DECLARE_DYNCREATE(CCopyThread)
public:
	//##ModelId=474D307202DF
	CCopyThread();
	//##ModelId=474D307202E0
	virtual ~CCopyThread();

// Attributes
public:

// Operations
public:

	//##ModelId=474D307202E2
	bool m_bQuit;

	// critical section is held whenever shared data is changed 
	//##ModelId=474D307202FE
	CRITICAL_SECTION		m_CS;
	//##ModelId=474D3072031E
	void Hold()		{ ::EnterCriticalSection(&m_CS); }
	//##ModelId=474D3072031F
	void Release()	{ ::LeaveCriticalSection(&m_CS); }

// CopyThread Local (accessed from this CopyThread)
	// window owned by this thread which handles clipboard viewer messages
	//##ModelId=474D3072035D
	CClipboardViewer*   m_pClipboardViewer; // permanent during lifetime of thread
	//##ModelId=474D3072036D
	CCopyConfig         m_LocalConfig;

	// Called within Copy Thread:
	//##ModelId=474D3072037B
	void OnClipboardChange(); // called by ClipboardViewer
	//##ModelId=474D3072038B
	void SyncConfig(); // safely syncs m_LocalConfig with m_SharedConfig
	//##ModelId=474D3072038C
	void AddToClips( CClip* pClip ); // after this, pClip is owned by m_pClips

// Shared (use thread-safe access functions below)
	//##ModelId=474D307203AA
	CCopyConfig         m_SharedConfig; 
	//##ModelId=474D307203BA
	bool                m_bConfigChanged; // true if m_SharedConfig was changed.
	//##ModelId=474D30730002
	CClipList*          m_pClips; // snapshots of the clipboard when it changed.

	// Called within Main thread:
	//##ModelId=474D30730020
	bool IsClipboardViewerConnected();
	//##ModelId=474D3073003F
	bool GetConnectCV();
	//##ModelId=474D3073004F
	void SetConnectCV( bool bConnect );

	//##ModelId=474D3073007E
	CClipList* GetClips(); // caller owns the returned CClipList
	//##ModelId=474D3073008D
	void SetSupportedTypes( CClipTypes* pTypes ); // CopyThread will own pTypes
	//##ModelId=474D3073009D
	HWND SetClipHandler( HWND hWnd ); // returns previous value
	//##ModelId=474D307300AD
	HWND GetClipHandler();
	//##ModelId=474D307300CC
	bool SetCopyOnChange( bool bVal ); // returns previous value
	//##ModelId=474D307300DC
	bool GetCopyOnChange();
	//##ModelId=474D307300EB
	bool SetAsyncCopy( bool bVal ); // returns previous value
	//##ModelId=474D307300FB
	bool GetAsyncCopy();

// Main thread
	//##ModelId=474D307300FC
	void Init( CCopyConfig cfg );
	//##ModelId=474D3073010A
	bool Quit();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyThread)
	public:
	//##ModelId=474D3073010B
	virtual BOOL InitInstance();
	//##ModelId=474D3073012A
	virtual int ExitInstance();
	//}}AFX_VIRTUAL


	// Generated message map functions
	//{{AFX_MSG(CCopyThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYTHREAD_H__C6766F04_0111_4314_986A_A0E02FF3B322__INCLUDED_)
