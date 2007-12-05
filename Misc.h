
#if !defined(AFX_CP_GUI_GLOBALS__FBCDED09_A6F2_47EB_873F_50A746EBC86B__INCLUDED_)
#define AFX_CP_GUI_H__FBCDED09_A6F2_47EB_873F_50A746EBC86B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ArrayEx.h"
#include <vector>

#define ONE_MINUTE				60000
#define ONE_HOUR				3600000
#define ONE_DAY					86400000

#define DELETE_PTR(ptr) {  if(ptr) {delete ptr; ptr = NULL;}  }

#define CATCH_SQLITE_EXCEPTION		\
	catch (CppSQLite3Exception& e)	\
    {								\
		Log(StrF(_T("SQLITE Exception %d - %s"), e.errorCode(), e.errorMessage()));	\
		ASSERT(FALSE);				\
    }								\

#define CATCH_SQLITE_EXCEPTION_AND_RETURN(bRet)		\
	catch (CppSQLite3Exception& e)	\
    {								\
		Log(StrF(_T("SQLITE Exception %d - %s"), e.errorCode(), e.errorMessage()));	\
		ASSERT(FALSE);				\
		return bRet;				\
    }								\
	
#define	FIX_PATH(strPath) \
{ \
	if (strPath[strlen(strPath)-1] != '\\' && strPath[strlen(strPath)-1] != '/') \
	strcat(strPath, "\\"); \
}

#define	FIX_CSTRING_PATH(csPath) \
{ \
	if(csPath.IsEmpty() == FALSE && csPath.GetAt(csPath.GetLength()-1) != '\\' && csPath.GetAt(csPath.GetLength()-1) != '/') \
	csPath += "\\"; \
}

#include "DatabaseUtilities.h"

CString GetIPAddress();
CString GetComputerName();

#define FUNC		__FUNCTION__
#define FUNCSIG		__FUNCSIG__
void AppendToFile(const TCHAR* fn, const TCHAR *msg);
#define Log(msg) log(msg, false, __FILE__, __LINE__)
void log(const TCHAR* msg, bool bFromSendRecieve = false, CString csFile = _T(""), long lLine = -1);
CString GetErrorString(int err);

#define LogSendRecieveInfo(cs) logsendrecieveinfo(cs, __FILE__, __LINE__)
void logsendrecieveinfo(CString cs, CString csFile = _T(""), long lLine = -1);

// Utility Functions
CString StrF(const TCHAR * pszFormat, ...);
// called after determining that the preceding character is a backslash
BYTE GetEscapeChar( BYTE ch );
CString RemoveEscapes( const TCHAR* str );

CString GetWndText( HWND hWnd );
// returns true if the given window is owned by this process
bool IsAppWnd( HWND hWnd );
// returns the current Focus window even if it is not owned by our thread.
CPoint GetFocusedCaretPos();

// Global Memory Helper Functions
BOOL IsValid( HGLOBAL hGlobal );
void CopyToGlobalHP( HGLOBAL hDest, LPVOID pBuf, ULONG ulBufLen );
void CopyToGlobalHH( HGLOBAL hDest, HGLOBAL hSource, ULONG ulBufLen );
HGLOBAL NewGlobalP( LPVOID pBuf, UINT nLen );
HGLOBAL NewGlobalH( HGLOBAL hSource, UINT nLen );
HGLOBAL NewGlobal(UINT nLen);
int CompareGlobalHP( HGLOBAL hLeft, LPVOID pBuf, ULONG ulBufLen );
int CompareGlobalHH( HGLOBAL hLeft, HGLOBAL hRight, ULONG ulBufLen );

BOOL EncryptString(CString &csString, UCHAR*& pOutput, int &nLenOutput);
BOOL DecryptString(UCHAR *pData, int nLenIn, UCHAR*& pOutput, int &nLenOutput);

int GetScreenWidth();
int GetScreenHeight();
void GetMonitorRect(int iMonitor, LPRECT lpDestRect);
int GetMonitorFromRect(LPRECT lpMonitorRect);

CLIPFORMAT GetFormatID(LPCTSTR cbName);
CString GetFormatName(CLIPFORMAT cbType);
BOOL PreTranslateGuiDll(MSG *pMsg);

CString GetFilePath(CString csFullPath);
CString GetFileName(CString csFileName);

BOOL EnsureWindowVisible(CRect *pcrRect);

__int64 GetLastWriteTime(const CString &csFile);
CString GetProcessName(HWND hWnd);

//Message to the main window to show icon or not
#define WM_SHOW_TRAY_ICON		WM_USER + 200
#define WM_SETCONNECT			WM_USER + 201
#define WM_CV_IS_CONNECTED		WM_USER + 202
#define WM_COPYPROPERTIES		WM_USER + 203
#define WM_CLOSE_APP			WM_USER + 204
#define WM_REFRESH_VIEW			WM_USER + 205
#define WM_CLIPBOARD_COPIED		WM_USER + 206
#define WM_ADD_TO_DATABASE_FROM_SOCKET		WM_USER + 207
#define WM_SEND_RECIEVE_ERROR	WM_USER + 208
#define WM_FOCUS_CHANGED		WM_USER + 209
#define WM_CV_GETCONNECT		WM_USER + 211
#define WM_EDIT_WND_CLOSING		WM_USER	+ 212
#define WM_SET_CONNECTED		WM_USER	+ 213
//defined in tray icon #define WM_CUSTOMIZE_TRAY_MENU	WM_USER + 211



/*------------------------------------------------------------------*\
	CHotKey - a single system-wide hotkey
\*------------------------------------------------------------------*/

//##ModelId=474D305B02B0
class CHotKey
{
public:
	//##ModelId=474D305B02CF
	CString	m_Name;
	//##ModelId=474D305B02EF
	ATOM	m_Atom;
	//##ModelId=474D305B02FE
	DWORD	m_Key; //704 is ctrl-tilda
	//##ModelId=474D305B030E
	bool	m_bIsRegistered;
	//##ModelId=474D305B031E
	bool	m_bUnRegisterOnShowDitto;
	
	//##ModelId=474D305B032D
	CHotKey( CString name, DWORD defKey = 0, bool bUnregOnShowDitto = false );
	//##ModelId=474D305B033D
	~CHotKey();

	//##ModelId=474D305B033E
	bool	IsRegistered() { return m_bIsRegistered; }
	//##ModelId=474D305B034C
	CString GetName()      { return m_Name; }
	//##ModelId=474D305B034D
	DWORD   GetKey()       { return m_Key; }

	//##ModelId=474D305B035C
	void SetKey( DWORD key, bool bSave = false );
	// profile
	//##ModelId=474D305B037B
	void LoadKey();
	//##ModelId=474D305B038B
	bool SaveKey();

	//##ModelId=474D305B038C
	void CopyFromCtrl(CHotKeyCtrl& ctrl, HWND hParent, int nWindowsCBID);
	//##ModelId=474D305B03AA
	void CopyToCtrl(CHotKeyCtrl& ctrl, HWND hParent, int nWindowsCBID);

//	CString GetKeyAsText();
//	void SetKeyFromText( CString text );

	//##ModelId=474D305B03DA
	static BOOL ValidateHotKey(DWORD dwHotKey);
	//##ModelId=474D305C0002
	static UINT GetModifier(DWORD dwHotKey);
	//##ModelId=474D305C0012
	UINT GetModifier() { return GetModifier(m_Key); }

	//##ModelId=474D305C0020
	bool Register();
	//##ModelId=474D305C0021
	bool Unregister(bool bOnShowingDitto = false);
};


/*------------------------------------------------------------------*\
	CHotKeys - Manages system-wide hotkeys
\*------------------------------------------------------------------*/

//##ModelId=474D305C006E
class CHotKeys : public CArray<CHotKey*,CHotKey*>
{
public:
	//##ModelId=474D305D0021
	HWND	m_hWnd;

	//##ModelId=474D305D0030
	CHotKeys();
	//##ModelId=474D305D0031
	~CHotKeys();

	//##ModelId=474D305D003F
	void Init( HWND hWnd ) { m_hWnd = hWnd; }

	//##ModelId=474D305D0041
	int Find( CHotKey* pHotKey );
	//##ModelId=474D305D0050
	bool Remove( CHotKey* pHotKey ); // pHotKey is NOT deleted.

	// profile load / save
	//##ModelId=474D305D005E
	void LoadAllKeys();
	//##ModelId=474D305D005F
	void SaveAllKeys();

	//##ModelId=474D305D0060
	void RegisterAll(bool bMsgOnError = false);
	//##ModelId=474D305D006F
	void UnregisterAll(bool bMsgOnError = false, bool bOnShowDitto = false);

	//##ModelId=474D305D0080
	void GetKeys( ARRAY& keys );
	//##ModelId=474D305D00FB
	void SetKeys( ARRAY& keys, bool bSave = false ); // caution! this alters hotkeys based upon corresponding indexes

	//##ModelId=474D305D010A
	static bool FindFirstConflict( ARRAY& keys, int* pX = NULL, int* pY = NULL );
	// if true, pX and pY (if valid) are set to the index of the conflicting hotkeys.
	//##ModelId=474D305D012A
	bool FindFirstConflict( int* pX = NULL, int* pY = NULL );
};

extern CHotKeys g_HotKeys;

/*------------------------------------------------------------------*\
	CAccel - an Accelerator (in-app hotkey)

    - the win32 CreateAcceleratorTable using ACCEL was insufficient
    because it only allowed a WORD for the cmd associated with it.
\*------------------------------------------------------------------*/

#define ACCEL_VKEY(key)			LOBYTE(key)
#define ACCEL_MOD(key)			HIBYTE(key)
#define ACCEL_MAKEKEY(vkey,mod) ((mod << 8) | vkey)

//##ModelId=474D305D01A7
class CAccel
{
public:
	//##ModelId=474D305D01C6
	DWORD	Key; // directly uses the CHotKeyCtrl format
	//##ModelId=474D305D01D5
	DWORD	Cmd;
	//##ModelId=474D305D01D6
	CAccel( DWORD key=0, DWORD cmd=0 ) { Key = key;  Cmd = cmd; } 
};

/*------------------------------------------------------------------*\
	CAccels - Manages a set of CAccel
\*------------------------------------------------------------------*/
//##ModelId=474D305D0214
class CAccels
{
public:
	//##ModelId=474D305D0224
	CAccels();

	//##ModelId=474D305D0292
	CMap<DWORD, DWORD, DWORD, DWORD> m_Map;

	//##ModelId=474D305D02A1
	void AddAccel( CAccel& a );

	// handles a key's first WM_KEYDOWN or WM_SYSKEYDOWN message.
	// it uses GetKeyState to test for modifiers.
	// returns a pointer to the internal CAccel if it matches the given key or NULL
	//##ModelId=474D305D02B0
	bool OnMsg( MSG* pMsg , DWORD &dID );
};

// returns a BYTE representing the current GetKeyState modifiers:
//  HOTKEYF_SHIFT, HOTKEYF_CONTROL, HOTKEYF_ALT
BYTE GetKeyStateModifiers();

/*------------------------------------------------------------------*\
	CTokenizer - Tokenizes a string using given delimiters
\*------------------------------------------------------------------*/
// Based upon:
// Date:        Monday, October 22, 2001
// Autor:       Eduardo Velasquez
// Description: Tokenizer class for CStrings. Works like strtok.
///////////////

#if !defined(_BITSET_)
#	include <bitset>
#endif // !defined(_BITSET_)

//##ModelId=474D305D038B
class CTokenizer
{
public:
	//##ModelId=474D305D039B
	CString m_cs;
	//##ModelId=474D305E0070
	CArrayEx<TCHAR> m_delim;
	//##ModelId=474D305E008D
	int m_nCurPos;

	//##ModelId=474D305E00AD
	CTokenizer(const CString& cs, const CString& csDelim);
	//##ModelId=474D305E00BD
	void SetDelimiters(const CString& csDelim);

	//##ModelId=474D305E00EB
	bool Next(CString& cs);
	//##ModelId=474D305E010B
	CString	Tail();
};


/*------------------------------------------------------------------*\
	Global ToolTip Manual Control Functions
\*------------------------------------------------------------------*/

void InitToolInfo( TOOLINFO& ti ); // initializes toolinfo with uid 0

/*------------------------------------------------------------------*\
	CPopup - a tooltip that pops up manually (when Show is called).
	- technique learned from codeproject "ToolTipZen" by "Zarembo Maxim"
\*------------------------------------------------------------------*/

//##ModelId=474D305E0197
class CPopup
{
public:
	//##ModelId=474D305E01B6
	bool m_bOwnTT;

	//##ModelId=474D305E01C6
	HWND m_hTTWnd; // handle to the ToolTip control
	//##ModelId=474D305E01D6
	TOOLINFO m_TI; // struct specifying info about tool in ToolTip control

	//##ModelId=474D305E01E5
	bool m_bIsShowing;

	//##ModelId=474D305E01F5
	bool m_bTop;  // true if m_Pos.x is the top, false if the bottom
	//##ModelId=474D305E0204
	bool m_bLeft; // true if m_Pos.y is the left, false if the right
	//##ModelId=474D305E0214
	bool m_bCenterY; // true if m_Pos is the y center, false if corner
	//##ModelId=474D305E0215
	bool m_bCenterX; // true if m_Pos is the x center, false if corner
	//##ModelId=474D305E0224
	HWND m_hWndPosRelativeTo;
	//##ModelId=474D305E0233
	CPoint m_Pos;

	//##ModelId=474D305E0243
	int m_ScreenMaxX;
	//##ModelId=474D305E0244
	int m_ScreenMaxY;

	//##ModelId=474D305E0252
	HWND m_hWndInsertAfter;

	//##ModelId=474D305E0262
	bool m_bAllowShow; // used by SafeShow to determine whether to show or not

	//##ModelId=474D305E0272
	CString m_csToolTipText;

	//##ModelId=474D305E0281
	CPopup();
	//##ModelId=474D305E0282
	CPopup( int x, int y, HWND hWndPosRelativeTo = NULL, HWND hWndInsertAfter = HWND_TOP );
	//##ModelId=474D305E02A1
	~CPopup();

	//##ModelId=474D305E02A2
	void Init();
	//##ModelId=474D305E02B0
	void SetTTWnd( HWND hTTWnd = NULL, TOOLINFO* pTI = NULL );
	//##ModelId=474D305E02C2
	void CreateToolTip();

	//##ModelId=474D305E02CF
	void SetTimeout( int timeout );

	//##ModelId=474D305E02DF
	void AdjustPos( CPoint& pos );
	//##ModelId=474D305E02EF
	void SetPos( CPoint& pos );
	//##ModelId=474D305E02FF
	void SetPosInfo( bool bTop, bool bCenterY, bool bLeft, bool bCenterX );

	//##ModelId=474D305E031F
	void SendToolTipText( CString text );

	//##ModelId=474D305E032E
	void Show( CString text, CPoint pos, bool bAdjustPos = true );
	//##ModelId=474D305E035C
	void Show( CString text );
	//##ModelId=474D305E035E
	void AllowShow( CString text ); // only shows if m_bAllowShow is true

	//##ModelId=474D305E037B
	void Hide();
};

/*------------------------------------------------------------------*\
	ID based Globals
\*------------------------------------------------------------------*/
long NewGroupID(long lParentID = 0, CString text = "");
BOOL DeleteID(long lID);
BOOL DeleteAllIDs();
BOOL DeleteFormats(long lDataID, ARRAY& formatIDs);

__inline BOOL FileExists(LPCTSTR pszFile)
{ 
	return (GetFileAttributes(pszFile) != 0xffffffff); 
}


#endif // !defined(AFX_CP_GUI_GLOBALS__FBCDED09_A6F2_47EB_873F_50A746EBC86B__INCLUDED_)
