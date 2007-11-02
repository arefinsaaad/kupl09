#pragma once

#define MAX_SEND_CLIENTS	15
class CSendClients
{
public:
	CSendClients()
	{
		bSendAll = FALSE;
		bShownFirstError = FALSE;
	}
	BOOL bSendAll;
	CString csIP;
	CString csDescription;
	BOOL bShownFirstError;
};

#define MAX_COPY_BUFFER	3
class CCopyBufferItem
{
public:
	CCopyBufferItem()
	{
		m_lCopyHotKey = -1;
		m_lPasteHotKey = -1;
		m_lCutHotKey = -1;
		m_bPlaySoundOnCopy = FALSE;
	}
	long m_lCopyHotKey;
	long m_lPasteHotKey;
	long m_lCutHotKey;
	BOOL m_bPlaySoundOnCopy;
};

#define REG_PATH					"Software\\Ditto"

#define POS_AT_CARET	1
#define POS_AT_CURSOR	2
#define POS_AT_PREVIOUS	3

#define CAPTION_RIGHT	1
#define CAPTION_BOTTOM	2
#define CAPTION_LEFT	3
#define CAPTION_TOP		4

#define TOGGLES_ALLWAYS_ON_TOP				1
#define TOGGLES_ALLWAYS_SHOW_DESCRIPTION	2
#define	ROLLES_UP_WINDOW					3

#define PATH_HELP			0
#define PATH_REMOTE_FILES	1
#define PATH_LOG_FILE		2
#define PATH_LANGUAGE		3
#define PATH_UPDATE_FILE	4
#define PATH_DATABASE		5
#define PATH_INI			6
#define PATH_U3_HWND_INI	7

class CGetSetOptions
{
public:
	CGetSetOptions();
	virtual ~CGetSetOptions();

	static bool m_bFromIni;
	static CString m_csIniFileName;
	static bool m_bInConversion;
	static bool m_bU3;

	static void LoadSettings();
	static CString GetIniFileName(bool bLocalIniFile);
	static void ConverSettingsToIni();

	static CString GetExeFileName();
	static CString GetAppName();

	static BOOL GetShowIconInSysTray();
	static BOOL SetShowIconInSysTray(BOOL bShow);

	static BOOL GetRunOnStartUp();
	static void SetRunOnStartUp(BOOL bRun);

	static BOOL SetProfileFont(CString csSection, LOGFONT &font);
	static BOOL GetProfileFont(CString csSection, LOGFONT &font);

	static BOOL SetProfileLong(CString csName, long lValue);
	static long GetProfileLong(CString csName, long lDefaultValue = -1, CString csNewPath = _T(""));

	static CString GetProfileString(CString csName, CString csDefault, CString csNewPath = _T(""));
	static BOOL	SetProfileString(CString csName, CString csValue);

	static LPVOID GetProfileData(CString csName, DWORD &dwLength);
	static BOOL	SetProfileData(CString csName, LPVOID lpData, DWORD dwLength);

	static BOOL SetQuickPasteSize(CSize size);
	static void GetQuickPasteSize(CSize &size);

	static BOOL SetQuickPastePoint(CPoint point);
	static void GetQuickPastePoint(CPoint &point);

	static BOOL SetEditWndSize(CSize size);
	static void GetEditWndSize(CSize &size);

	static BOOL SetEditWndPoint(CPoint point);
	static void GetEditWndPoint(CPoint &point);

	static BOOL SetEnableTransparency(BOOL bCheck);
	static BOOL GetEnableTransparency();

	static BOOL SetTransparencyPercent(long lPercent);
	static long GetTransparencyPercent();

	static long m_nLinesPerRow;
	static BOOL SetLinesPerRow(long lLines);
	static long GetLinesPerRow();

	static BOOL SetQuickPastePosition(long lPosition);
	static long GetQuickPastePosition();

	static long GetCopyGap();
	static void SetCopyGap(long lGap);

	static BOOL SetDBPath(CString csPath);
	static CString GetDBPath();

	static BOOL SetDBPathOld(CString csPath);
	static CString GetDBPathOld();

	static void SetCheckForMaxEntries(BOOL bVal);
	static BOOL GetCheckForMaxEntries();

	static void SetCheckForExpiredEntries(BOOL bVal);
	static BOOL GetCheckForExpiredEntries();

	static void SetMaxEntries(long lVal);
	static long GetMaxEntries();

	static void SetExpiredEntries(long lVal);
	static long GetExpiredEntries();

	static void SetTripCopyCount(long lVal);
	static long GetTripCopyCount();

	static void SetTripPasteCount(long lVal);
	static long GetTripPasteCount();

	static void SetTripDate(long lDate);
	static long GetTripDate();

	static void SetTotalCopyCount(long lVal);
	static long GetTotalCopyCount();

	static void SetTotalPasteCount(long lVal);
	static long GetTotalPasteCount();

	static void SetTotalDate(long lDate);
	static long GetTotalDate();

	static CString	GetUpdateFilePath();
	static BOOL		SetUpdateFilePath(CString cs);

	static CString	GetUpdateInstallPath();
	static BOOL		SetUpdateInstallPath(CString cs);

	static long		GetLastUpdate();
	static long		SetLastUpdate(long lValue);

	static BOOL		GetCheckForUpdates();
	static BOOL		SetCheckForUpdates(BOOL bCheck);

	static BOOL		m_bUseCtrlNumAccel;
	static void		SetUseCtrlNumForFirstTenHotKeys(BOOL bVal);
	static BOOL		GetUseCtrlNumForFirstTenHotKeys();

	static BOOL		m_bAllowDuplicates;
	static void		SetAllowDuplicates(BOOL bVal);
	static BOOL		GetAllowDuplicates();

	static BOOL		m_bUpdateTimeOnPaste;
	static void		SetUpdateTimeOnPaste(BOOL bVal);
	static BOOL		GetUpdateTimeOnPaste();

	static BOOL		m_bSaveMultiPaste;
	static void		SetSaveMultiPaste(BOOL bVal);
	static BOOL		GetSaveMultiPaste();

	static BOOL		m_bShowPersistent;
	static void		SetShowPersistent(BOOL bVal);
	static BOOL		GetShowPersistent();

	static BOOL		m_bHistoryStartTop;
	static void		SetHistoryStartTop(BOOL bVal);
	static BOOL		GetHistoryStartTop();

	static void		SetShowTextForFirstTenHotKeys(BOOL bVal);
	static BOOL		GetShowTextForFirstTenHotKeys();

	static void		SetMainHWND(long lhWnd);
	static BOOL		GetMainHWND();

	static void		SetCaptionPos(long lPos);
	static long		GetCaptionPos();

	static void		SetAutoHide(BOOL bAutoHide);
	static BOOL		GetAutoHide();

	static long		m_bDescTextSize;
	static void		SetDescTextSize(long lSize);
	static long		GetDescTextSize();

	static BOOL		m_bDescShowLeadingWhiteSpace;
	static void		SetDescShowLeadingWhiteSpace(BOOL bVal);
	static BOOL		GetDescShowLeadingWhiteSpace();

	static BOOL		m_bAllwaysShowDescription;
	static void		SetAllwaysShowDescription(long bShow);
	static BOOL		GetAllwaysShowDescription();

	static long		m_bDoubleClickingOnCaptionDoes;
	static void		SetDoubleClickingOnCaptionDoes(long lOption);
	static long		GetDoubleClickingOnCaptionDoes();

	static BOOL		m_bPrompForNewGroupName;
	static void		SetPrompForNewGroupName(BOOL bOption);
	static BOOL		GetPrompForNewGroupName();

	static BOOL		m_bSendPasteOnFirstTenHotKeys;
	static void		SetSendPasteOnFirstTenHotKeys(BOOL bOption);
	static BOOL		GetSendPasteOnFirstTenHotKeys();

	static CSendClients m_SendClients[MAX_SEND_CLIENTS];
	static long		m_lAutoSendClientCount;
	static void		GetClientSendCount();
	static void		SetSendClients(CSendClients Client, int nPos);
	static CSendClients		GetSendClients(int nPos);

	static CString m_csIPListToPutOnClipboard;
	static CString	GetListToPutOnClipboard();
	static BOOL		SetListToPutOnClipboard(CString cs);

	static BOOL		m_bLogSendReceiveErrors;
	static void		SetLogSendReceiveErrors(BOOL bOption);
	static BOOL		GetLogSendReceiveErrors();

	static BOOL		m_bUseHookDllForFocus;

	static BOOL		m_HideDittoOnHotKeyIfAlreadyShown;
	static BOOL		GetHideDittoOnHotKeyIfAlreadyShown();
	static void		SetHideDittoOnHotKeyIfAlreadyShown(BOOL bVal);

	static long		m_lPort;
	static void		SetPort(long lPort);
	static long		GetPort();

	static BOOL		GetDisableRecieve();
	static void		SetDisableRecieve(BOOL bVal);

	static BOOL		GetFont(LOGFONT &font);
	static void		SetFont(LOGFONT &font);

	static BOOL		m_bDrawThumbnail;
	static void		SetDrawThumbnail(long bDraw);
	static BOOL		GetDrawThumbnail();

	static CStringA	m_csPassword;
	static void		SetNetworkPassword(CString csPassword);
	static CStringA	GetNetworkPassword();

	static BOOL		m_bDrawRTF;
	static void		SetDrawRTF(long bDraw);
	static BOOL		GetDrawRTF();

	static BOOL		m_bMultiPasteReverse;
	static void		SetMultiPasteReverse(BOOL bVal);
	static BOOL		GetMultiPasteReverse();

	static CString	m_csPlaySoundOnCopy;
	static void		SetPlaySoundOnCopy(CString cs);
	static CString	GetPlaySoundOnCopy();

	static BOOL		m_bSendPasteMessageAfterSelection;
	static void		SetSendPasteAfterSelection(BOOL bVal);
	static BOOL		GetSendPasteAfterSelection();

	static BOOL		m_bFindAsYouType;
	static void		SetFindAsYouType(BOOL bVal);
	static BOOL		GetFindAsYouType();

	static BOOL		m_bEnsureEntireWindowCanBeSeen;
	static void		SetEnsureEntireWindowCanBeSeen(BOOL bVal);
	static BOOL		GetEnsureEntireWindowCanBeSeen();

	static BOOL		m_bShowAllClipsInMainList;
	static void		SetShowAllClipsInMainList(BOOL bVal);
	static BOOL		GetShowAllClipsInMainList();

	static void		SetExtraNetworkPassword(CString csPassword);
	static CString	GetExtraNetworkPassword(bool bFillArray);

	static long		m_lMaxClipSizeInBytes;
	static long		GetMaxClipSizeInBytes();
	static void		SetMaxClipSizeInBytes(long lSize);

	static CString	GetLanguageFile();
	static void		SetLanguageFile(CString csLanguage);

	static DWORD	m_dwSaveClipDelay;
	static ULONG	GetSaveClipDelay();
	static void		SetSaveClipDelay(DWORD dwDelay);

	static long		m_lProcessDrawClipboardDelay;
	static long		GetProcessDrawClipboardDelay();
	static void		SetProcessDrawClipboardDelay(long lDelay);

	static BOOL		m_bEnableDebugLogging;
	static BOOL		GetEnableDebugLogging();
	static void		SetEnableDebugLogging(BOOL bEnable);

	static BOOL		m_bEnsureConnectToClipboard;
	static BOOL		GetEnsureConnectToClipboard();
	static void		SetEnsureConnectToClipboard(BOOL bSet);

	static BOOL		GetPromptWhenDeletingClips();
	static void		SetPromptWhenDeletingClips(BOOL bSet);

	static CString	GetLastImportDir();
	static void		SetLastImportDir(CString csDir);

	static CString	GetLastExportDir();
	static void		SetLastExportDir(CString csDir);

	static BOOL		GetUpdateDescWhenSavingClip();
	static void		SetUpdateDescWhenSavingClip(BOOL bSet);

	static bool		m_bOutputDebugString;

	static CStringArray m_csNetworkPasswordArray;

	static CString  GetPath(long lPathID);

	static void		WriteU3Hwnd(HWND hWnd);
	static __int64	nLastDbWriteTime;

	static long		GetDittoRestoreClipboardDelay();
	static void		SetDittoRestoreClipboardDelay(long lDelay);

	static void		GetCopyBufferItem(int nPos, CCopyBufferItem &Item);
	static void		SetCopyBufferItem(int nPos, CCopyBufferItem &Item);

	static CString  GetMultiPasteSeparator(bool bConvertToLineFeeds = true);
	static void		SetMultiPasteSeparator(CString csSep);

	static BOOL		GetSetCurrentDirectory();

	static CString GetPasteString(CString csAppName);
	static CString GetDefaultPasteString();

	static CString GetCopyString(CString csAppName);
	static CString GetDefaultCopyString();

	static CString GetCutString(CString csAppName);
	static CString GetDefaultCutString();

	static BOOL	GetEditWordWrap();
	static void	SetEditWordWrap(BOOL bSet);

	static bool GetAllowFriends();

	static bool		GetIsPortableDitto();
};

// global for easy access and for initialization of fast access variables
extern CGetSetOptions g_Opt; 