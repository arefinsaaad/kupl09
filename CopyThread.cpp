// CopyThread.cpp : implementation file
//

#include "stdafx.h"
#include "cp_main.h"
#include "CopyThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyThread

IMPLEMENT_DYNCREATE(CCopyThread, CWinThread)

//##ModelId=474D307202DF
CCopyThread::CCopyThread():
	m_bQuit(false),
	m_bConfigChanged(false),
	m_pClips(NULL),
	m_pClipboardViewer(NULL)
{
	m_bAutoDelete = false,

	::InitializeCriticalSection(&m_CS);
}

//##ModelId=474D307202E0
CCopyThread::~CCopyThread()
{
	m_LocalConfig.DeleteTypes();
	m_SharedConfig.DeleteTypes();
	DELETE_PTR(m_pClipboardViewer);
	DELETE_PTR(m_pClips);
	::DeleteCriticalSection(&m_CS);
}

//##ModelId=474D3073010B
BOOL CCopyThread::InitInstance()
{
	m_pClipboardViewer = new CClipboardViewer(this);

	// the window is created within this thread and therefore uses its message queue
	m_pClipboardViewer->Create();

	return TRUE;
}

//##ModelId=474D3073012A
int CCopyThread::ExitInstance()
{
	m_pClipboardViewer->Disconnect(false);

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCopyThread, CWinThread)
	//{{AFX_MSG_MAP(CCopyThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyThread message handlers


// Called within Copy Thread:
//##ModelId=474D3072037B
void CCopyThread::OnClipboardChange()
{
	SyncConfig(); // synchronize with the main thread's copy configuration
	
	// if we are told not to copy on change, then we have nothing to do.
	if(!m_LocalConfig.m_bCopyOnChange)
		return;
	
	CClip* pClip = new CClip;

	CClipTypes* pSupportedTypes = m_LocalConfig.m_pSupportedTypes;
	bool bDeleteMemory = false;

	//If we are copying from a Ditto Buffer then save all to the database, so when we paste this it will paste 
	//just like you were using Ctrl-V
	if(theApp.m_CopyBuffer.Active())
	{
		pSupportedTypes = new CClipTypes;
		if(pSupportedTypes)
		{
			bDeleteMemory = true;
			COleDataObject oleData;

			if(oleData.AttachClipboard())
			{
				oleData.BeginEnumFormats();

				FORMATETC format;
				while(oleData.GetNextFormat(&format))
				{
					pSupportedTypes->Add(format.cfFormat);
				}

				oleData.Release();
			}
		}
		else
		{
			pSupportedTypes = m_LocalConfig.m_pSupportedTypes;
		}
	}

	bool bResult = pClip->LoadFromClipboard(pSupportedTypes);

	if(bDeleteMemory)
	{
		delete pSupportedTypes;
		pSupportedTypes = NULL;
	}
	
	if(!bResult)
	{
		delete pClip;
		return; // error
	}
	
	AddToClips(pClip);
	
	if(m_LocalConfig.m_bAsyncCopy)
		::PostMessage(m_LocalConfig.m_hClipHandler, WM_CLIPBOARD_COPIED, (WPARAM)pClip, 0);
	else
		::SendMessage(m_LocalConfig.m_hClipHandler, WM_CLIPBOARD_COPIED, (WPARAM)pClip, 0);
}

//##ModelId=474D3072038B
void CCopyThread::SyncConfig()
{
	// atomic read
	if(m_bConfigChanged)
	{
		CClipTypes* pTypes = NULL;
		Hold();
		
		pTypes = m_LocalConfig.m_pSupportedTypes;
		
		m_LocalConfig = m_SharedConfig;
		
		// NULL means that it shouldn't have been sync'ed
		if( m_SharedConfig.m_pSupportedTypes == NULL )
		{	// let m_LocalConfig keep its types
			m_LocalConfig.m_pSupportedTypes = pTypes; // undo sync
			pTypes = NULL; // nothing to delete
		}
		else
			m_SharedConfig.m_pSupportedTypes = NULL; // now owned by LocalConfig
		
		Release();
		// delete old types
		if( pTypes )
			delete pTypes;
	}
}

//##ModelId=474D3072038C
void CCopyThread::AddToClips(CClip* pClip)
{
	Hold();

	if(!m_pClips)
		m_pClips = new CClipList;

	m_pClips->AddTail(pClip); // m_pClips now owns pClip

	Release();
}

//##ModelId=474D30730020
bool CCopyThread::IsClipboardViewerConnected()
{
	return m_pClipboardViewer->m_bIsConnected;
}

//##ModelId=474D3073003F
bool CCopyThread::GetConnectCV()
{
	return m_pClipboardViewer->GetConnect();
}

//##ModelId=474D3073004F
void CCopyThread::SetConnectCV(bool bConnect)
{
	ASSERT( m_pClipboardViewer && m_pClipboardViewer->m_hWnd );
	::SendMessage( m_pClipboardViewer->m_hWnd, WM_SETCONNECT, bConnect, 0 );
}

//##ModelId=474D3073007E
CClipList* CCopyThread::GetClips()
{
	Hold();
	
	CClipList* pRet = m_pClips;
	m_pClips = NULL;

	Release();
	return pRet;
}

//##ModelId=474D3073008D
void CCopyThread::SetSupportedTypes( CClipTypes* pTypes )
{
	Hold();

	if(m_SharedConfig.m_pSupportedTypes)
	{
		DELETE_PTR(m_SharedConfig.m_pSupportedTypes);
	}

	m_SharedConfig.m_pSupportedTypes = pTypes;
	m_bConfigChanged = true;

	Release();
}

//##ModelId=474D3073009D
HWND CCopyThread::SetClipHandler(HWND hWnd)
{
	Hold();

	HWND hRet = m_SharedConfig.m_hClipHandler;
	m_SharedConfig.m_hClipHandler = hWnd;
	m_bConfigChanged = (hRet != hWnd);

	Release();

	return hRet;
}
//##ModelId=474D307300AD
HWND CCopyThread::GetClipHandler()
{
	Hold();

	HWND hRet = m_SharedConfig.m_hClipHandler;

	Release();

	return hRet;
}
//##ModelId=474D307300CC
bool CCopyThread::SetCopyOnChange(bool bVal)
{
	Hold();

	bool bRet = m_SharedConfig.m_bCopyOnChange;
	m_SharedConfig.m_bCopyOnChange = bVal;
	m_bConfigChanged = (bRet != bVal);

	Release();

	return bRet;
}
//##ModelId=474D307300DC
bool CCopyThread::GetCopyOnChange()
{
	Hold();
	bool bRet = m_SharedConfig.m_bCopyOnChange;
	Release();

	return bRet;
}
//##ModelId=474D307300EB
bool CCopyThread::SetAsyncCopy(bool bVal)
{
	Hold();
	bool bRet = m_SharedConfig.m_bAsyncCopy;
	m_SharedConfig.m_bAsyncCopy = bVal;
	m_bConfigChanged = (bRet != bVal);
	Release();

	return bRet;
}
//##ModelId=474D307300FB
bool CCopyThread::GetAsyncCopy()
{
	Hold();
	bool bRet = m_SharedConfig.m_bAsyncCopy;
	Release();

	return bRet;
}

//##ModelId=474D307300FC
void CCopyThread::Init(CCopyConfig cfg)
{
	ASSERT(m_LocalConfig.m_pSupportedTypes == NULL);
	m_LocalConfig = m_SharedConfig = cfg;
	// let m_LocalConfig own the m_pSupportedTypes
	m_SharedConfig.m_pSupportedTypes = NULL;
}

//##ModelId=474D3073010A
bool CCopyThread::Quit()
{
	m_bQuit = true;
	m_pClipboardViewer->PostMessage( WM_QUIT );
	return CWinThread::PostThreadMessage( WM_QUIT, NULL, NULL ) != FALSE;
}
