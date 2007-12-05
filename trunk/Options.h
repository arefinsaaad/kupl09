#pragma once

#define MAX_SEND_CLIENTS	15
//##ModelId=474D30400214
class CSendClients
{
public:
	//##ModelId=474D30400233
	CSendClients()
	{
		bSendAll = FALSE;
		bShownFirstError = FALSE;
	}
	//##ModelId=474D30400234
	BOOL bSendAll;
	//##ModelId=474D30400243
	CString csIP;
	//##ModelId=474D30400244
	CString csDescription;
	//##ModelId=474D30400252
	BOOL bShownFirstError;
};

#define MAX_COPY_BUFFER	3
//##ModelId=474D30400281
class CCopyBufferItem
{
public:
	//##ModelId=474D30400291
	CCopyBufferItem()
	{
		m_lCopyHotKey = -1;
		m_lPasteHotKey = -1;
		m_lCutHotKey = -1;
		m_bPlaySoundOnCopy = FALSE;
	}
	//##ModelId=474D30400292
	long m_lCopyHotKey;
	//##ModelId=474D304002A1
	long m_lPasteHotKey;
	//##ModelId=474D304002B0
	long m_lCutHotKey;
	//##ModelId=474D304002C0
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

//##ModelId=474D3043006E
class CGetSetOptions
{
public:
	//##ModelId=474D304300CC
	CGetSetOptions();
	//##ModelId=474D3043011A
	virtual ~CGetSetOptions();

	//##ModelId=474D30430158
	static bool m_bFromIni;
	//##ModelId=474D304301C6
	static CString m_csIniFileName;
	//##ModelId=474D30430204
	static bool m_bInConversion;
	//##ModelId=474D30430252
	static bool m_bU3;

	//##ModelId=474D304302A1
	static void LoadSettings();
	//##ModelId=474D3043032D
	static CString GetIniFileName(bool bLocalIniFile);
	//##ModelId=474D304303BA
	static void ConverSettingsToIni();

	//##ModelId=474D30440020
	static CString GetExeFileName();
	//##ModelId=474D3044003F
	static CString GetAppName();

	//##ModelId=474D304400AD
	static BOOL GetShowIconInSysTray();
	//##ModelId=474D30440168
	static BOOL SetShowIconInSysTray(BOOL bShow);

	//##ModelId=474D30440197
	static BOOL GetRunOnStartUp();
	//##ModelId=474D304401C6
	static void SetRunOnStartUp(BOOL bRun);

	//##ModelId=474D304401F5
	static BOOL SetProfileFont(CString csSection, LOGFONT &font);
	//##ModelId=474D30440262
	static BOOL GetProfileFont(CString csSection, LOGFONT &font);

	//##ModelId=474D30440291
	static BOOL SetProfileLong(CString csName, long lValue);
	//##ModelId=474D304402DF
	static long GetProfileLong(CString csName, long lDefaultValue = -1, CString csNewPath = _T(""));

	//##ModelId=474D3044035C
	static CString GetProfileString(CString csName, CString csDefault, CString csNewPath = _T(""));
	//##ModelId=474D3045003F
	static BOOL	SetProfileString(CString csName, CString csValue);

	//##ModelId=474D304500DB
	static LPVOID GetProfileData(CString csName, DWORD &dwLength);
	//##ModelId=474D3045011A
	static BOOL	SetProfileData(CString csName, LPVOID lpData, DWORD dwLength);

	//##ModelId=474D30450197
	static BOOL SetQuickPasteSize(CSize size);
	//##ModelId=474D30450252
	static void GetQuickPasteSize(CSize &size);

	//##ModelId=474D304502FE
	static BOOL SetQuickPastePoint(CPoint point);
	//##ModelId=474D304503C9
	static void GetQuickPastePoint(CPoint &point);

	//##ModelId=474D30460030
	static BOOL SetEditWndSize(CSize size);
	//##ModelId=474D3046007E
	static void GetEditWndSize(CSize &size);

	//##ModelId=474D3046011A
	static BOOL SetEditWndPoint(CPoint point);
	//##ModelId=474D30460168
	static void GetEditWndPoint(CPoint &point);

	//##ModelId=474D304601D5
	static BOOL SetEnableTransparency(BOOL bCheck);
	//##ModelId=474D30460281
	static BOOL GetEnableTransparency();

	//##ModelId=474D3046030E
	static BOOL SetTransparencyPercent(long lPercent);
	//##ModelId=474D304603D9
	static long GetTransparencyPercent();

	//##ModelId=474D304700AD
	static long m_nLinesPerRow;
	//##ModelId=474D30470139
	static BOOL SetLinesPerRow(long lLines);
	//##ModelId=474D304701A7
	static long GetLinesPerRow();

	//##ModelId=474D304701D5
	static BOOL SetQuickPastePosition(long lPosition);
	//##ModelId=474D30470214
	static long GetQuickPastePosition();

	//##ModelId=474D30470243
	static long GetCopyGap();
	//##ModelId=474D30470281
	static void SetCopyGap(long lGap);

	//##ModelId=474D3047030E
	static BOOL SetDBPath(CString csPath);
	//##ModelId=474D30480020
	static CString GetDBPath();

	//##ModelId=474D304800AD
	static BOOL SetDBPathOld(CString csPath);
	//##ModelId=474D30480168
	static CString GetDBPathOld();

	//##ModelId=474D304801D5
	static void SetCheckForMaxEntries(BOOL bVal);
	//##ModelId=474D30480291
	static BOOL GetCheckForMaxEntries();

	//##ModelId=474D304802DF
	static void SetCheckForExpiredEntries(BOOL bVal);
	//##ModelId=474D3048037B
	static BOOL GetCheckForExpiredEntries();

	//##ModelId=474D30490020
	static void SetMaxEntries(long lVal);
	//##ModelId=474D304900CC
	static long GetMaxEntries();

	//##ModelId=474D30490149
	static void SetExpiredEntries(long lVal);
	//##ModelId=474D304901F5
	static long GetExpiredEntries();

	//##ModelId=474D30490224
	static void SetTripCopyCount(long lVal);
	//##ModelId=474D30490272
	static long GetTripCopyCount();

	//##ModelId=474D304902B0
	static void SetTripPasteCount(long lVal);
	//##ModelId=474D3049033D
	static long GetTripPasteCount();

	//##ModelId=474D304903AA
	static void SetTripDate(long lDate);
	//##ModelId=474D304A0030
	static long GetTripDate();

	//##ModelId=474D304A007E
	static void SetTotalCopyCount(long lVal);
	//##ModelId=474D304A00BC
	static long GetTotalCopyCount();

	//##ModelId=474D304A00DB
	static void SetTotalPasteCount(long lVal);
	//##ModelId=474D304A012A
	static long GetTotalPasteCount();

	//##ModelId=474D304A0168
	static void SetTotalDate(long lDate);
	//##ModelId=474D304A01B6
	static long GetTotalDate();

	//##ModelId=474D304A01F5
	static CString	GetUpdateFilePath();
	//##ModelId=474D304A0214
	static BOOL		SetUpdateFilePath(CString cs);

	//##ModelId=474D304A0262
	static CString	GetUpdateInstallPath();
	//##ModelId=474D304A0272
	static BOOL		SetUpdateInstallPath(CString cs);

	//##ModelId=474D304A02C0
	static long		GetLastUpdate();
	//##ModelId=474D304A02CF
	static long		SetLastUpdate(long lValue);

	//##ModelId=474D304A032D
	static BOOL		GetCheckForUpdates();
	//##ModelId=474D304A036C
	static BOOL		SetCheckForUpdates(BOOL bCheck);

	//##ModelId=474D304A03D9
	static BOOL		m_bUseCtrlNumAccel;
	//##ModelId=474D304B00CC
	static void		SetUseCtrlNumForFirstTenHotKeys(BOOL bVal);
	//##ModelId=474D304B0197
	static BOOL		GetUseCtrlNumForFirstTenHotKeys();

	//##ModelId=474D304B0233
	static BOOL		m_bAllowDuplicates;
	//##ModelId=474D304B02A1
	static void		SetAllowDuplicates(BOOL bVal);
	//##ModelId=474D304B02EF
	static BOOL		GetAllowDuplicates();

	//##ModelId=474D304B033E
	static BOOL		m_bUpdateTimeOnPaste;
	//##ModelId=474D304C0030
	static void		SetUpdateTimeOnPaste(BOOL bVal);
	//##ModelId=474D304C00AD
	static BOOL		GetUpdateTimeOnPaste();

	//##ModelId=474D304C0149
	static BOOL		m_bSaveMultiPaste;
	//##ModelId=474D304C0224
	static void		SetSaveMultiPaste(BOOL bVal);
	//##ModelId=474D304C0281
	static BOOL		GetSaveMultiPaste();

	//##ModelId=474D304C02CF
	static BOOL		m_bShowPersistent;
	//##ModelId=474D304C031E
	static void		SetShowPersistent(BOOL bVal);
	//##ModelId=474D304C033D
	static BOOL		GetShowPersistent();

	//##ModelId=474D304C035C
	static BOOL		m_bHistoryStartTop;
	//##ModelId=474D304D0001
	static void		SetHistoryStartTop(BOOL bVal);
	//##ModelId=474D304D0010
	static BOOL		GetHistoryStartTop();

	//##ModelId=474D304D0020
	static void		SetShowTextForFirstTenHotKeys(BOOL bVal);
	//##ModelId=474D304D003F
	static BOOL		GetShowTextForFirstTenHotKeys();

	//##ModelId=474D304D004F
	static void		SetMainHWND(long lhWnd);
	//##ModelId=474D304D006E
	static BOOL		GetMainHWND();

	//##ModelId=474D304D007E
	static void		SetCaptionPos(long lPos);
	//##ModelId=474D304D009D
	static long		GetCaptionPos();

	//##ModelId=474D304D00BC
	static void		SetAutoHide(BOOL bAutoHide);
	//##ModelId=474D304D00DB
	static BOOL		GetAutoHide();

	//##ModelId=474D304D010A
	static long		m_bDescTextSize;
	//##ModelId=474D304D0168
	static void		SetDescTextSize(long lSize);
	//##ModelId=474D304D0178
	static long		GetDescTextSize();

	//##ModelId=474D304D0187
	static BOOL		m_bDescShowLeadingWhiteSpace;
	//##ModelId=474D304D01F5
	static void		SetDescShowLeadingWhiteSpace(BOOL bVal);
	//##ModelId=474D304D0252
	static BOOL		GetDescShowLeadingWhiteSpace();

	//##ModelId=474D304D0281
	static BOOL		m_bAllwaysShowDescription;
	//##ModelId=474D304D02FE
	static void		SetAllwaysShowDescription(long bShow);
	//##ModelId=474D304D032D
	static BOOL		GetAllwaysShowDescription();

	//##ModelId=474D304D034C
	static long		m_bDoubleClickingOnCaptionDoes;
	//##ModelId=474D304E0001
	static void		SetDoubleClickingOnCaptionDoes(long lOption);
	//##ModelId=474D304E0030
	static long		GetDoubleClickingOnCaptionDoes();

	//##ModelId=474D304E004F
	static BOOL		m_bPrompForNewGroupName;
	//##ModelId=474D304E00BC
	static void		SetPrompForNewGroupName(BOOL bOption);
	//##ModelId=474D304E00EB
	static BOOL		GetPrompForNewGroupName();

	//##ModelId=474D304E010A
	static BOOL		m_bSendPasteOnFirstTenHotKeys;
	//##ModelId=474D304E0178
	static void		SetSendPasteOnFirstTenHotKeys(BOOL bOption);
	//##ModelId=474D304E0197
	static BOOL		GetSendPasteOnFirstTenHotKeys();

	//##ModelId=474D304E01C7
	static CSendClients m_SendClients[MAX_SEND_CLIENTS];
	//##ModelId=474D304E02B0
	static long		m_lAutoSendClientCount;
	//##ModelId=474D304E036C
	static void		GetClientSendCount();
	//##ModelId=474D304E037B
	static void		SetSendClients(CSendClients Client, int nPos);
	//##ModelId=474D304E03D9
	static CSendClients		GetSendClients(int nPos);

	//##ModelId=474D304F00BC
	static CString m_csIPListToPutOnClipboard;
	//##ModelId=474D304F0139
	static CString	GetListToPutOnClipboard();
	//##ModelId=474D304F0158
	static BOOL		SetListToPutOnClipboard(CString cs);

	//##ModelId=474D304F0168
	static BOOL		m_bLogSendReceiveErrors;
	//##ModelId=474D304F02A1
	static void		SetLogSendReceiveErrors(BOOL bOption);
	//##ModelId=474D304F02EF
	static BOOL		GetLogSendReceiveErrors();

	//##ModelId=474D304F031E
	static BOOL		m_bUseHookDllForFocus;

	//##ModelId=474D304F039B
	static BOOL		m_HideDittoOnHotKeyIfAlreadyShown;
	//##ModelId=474D305000AD
	static BOOL		GetHideDittoOnHotKeyIfAlreadyShown();
	//##ModelId=474D305000CC
	static void		SetHideDittoOnHotKeyIfAlreadyShown(BOOL bVal);

	//##ModelId=474D3050012A
	static long		m_lPort;
	//##ModelId=474D30500281
	static void		SetPort(long lPort);
	//##ModelId=474D30500291
	static long		GetPort();

	//##ModelId=474D305002A1
	static BOOL		GetDisableRecieve();
	//##ModelId=474D305002B0
	static void		SetDisableRecieve(BOOL bVal);

	//##ModelId=474D305002C1
	static BOOL		GetFont(LOGFONT &font);
	//##ModelId=474D3050031E
	static void		SetFont(LOGFONT &font);

	//##ModelId=474D3050033D
	static BOOL		m_bDrawThumbnail;
	//##ModelId=474D30510020
	static void		SetDrawThumbnail(long bDraw);
	//##ModelId=474D305100CC
	static BOOL		GetDrawThumbnail();

	//##ModelId=474D30510188
	static CStringA	m_csPassword;
	//##ModelId=474D30510233
	static void		SetNetworkPassword(CString csPassword);
	//##ModelId=474D30510253
	static CStringA	GetNetworkPassword();

	//##ModelId=474D30510263
	static BOOL		m_bDrawRTF;
	//##ModelId=474D3051031E
	static void		SetDrawRTF(long bDraw);
	//##ModelId=474D3051036C
	static BOOL		GetDrawRTF();

	//##ModelId=474D3051037B
	static BOOL		m_bMultiPasteReverse;
	//##ModelId=474D30520001
	static void		SetMultiPasteReverse(BOOL bVal);
	//##ModelId=474D30520020
	static BOOL		GetMultiPasteReverse();

	//##ModelId=474D3052003F
	static CString	m_csPlaySoundOnCopy;
	//##ModelId=474D305200CC
	static void		SetPlaySoundOnCopy(CString cs);
	//##ModelId=474D305200EB
	static CString	GetPlaySoundOnCopy();

	//##ModelId=474D3052011B
	static BOOL		m_bSendPasteMessageAfterSelection;
	//##ModelId=474D305201A7
	static void		SetSendPasteAfterSelection(BOOL bVal);
	//##ModelId=474D305201F7
	static BOOL		GetSendPasteAfterSelection();

	//##ModelId=474D30520204
	static BOOL		m_bFindAsYouType;
	//##ModelId=474D305202A1
	static void		SetFindAsYouType(BOOL bVal);
	//##ModelId=474D305202C0
	static BOOL		GetFindAsYouType();

	//##ModelId=474D305202CF
	static BOOL		m_bEnsureEntireWindowCanBeSeen;
	//##ModelId=474D305203AA
	static void		SetEnsureEntireWindowCanBeSeen(BOOL bVal);
	//##ModelId=474D30530003
	static BOOL		GetEnsureEntireWindowCanBeSeen();

	//##ModelId=474D30530011
	static BOOL		m_bShowAllClipsInMainList;
	//##ModelId=474D305300BC
	static void		SetShowAllClipsInMainList(BOOL bVal);
	//##ModelId=474D305300DB
	static BOOL		GetShowAllClipsInMainList();

	//##ModelId=474D305300DD
	static void		SetExtraNetworkPassword(CString csPassword);
	//##ModelId=474D30530149
	static CString	GetExtraNetworkPassword(bool bFillArray);

	//##ModelId=474D30530168
	static long		m_lMaxClipSizeInBytes;
	//##ModelId=474D305301D5
	static long		GetMaxClipSizeInBytes();
	//##ModelId=474D305301E6
	static void		SetMaxClipSizeInBytes(long lSize);

	//##ModelId=474D305301F5
	static CString	GetLanguageFile();
	//##ModelId=474D30530204
	static void		SetLanguageFile(CString csLanguage);

	//##ModelId=474D30530215
	static DWORD	m_dwSaveClipDelay;
	//##ModelId=474D30530291
	static ULONG	GetSaveClipDelay();
	//##ModelId=474D305302B0
	static void		SetSaveClipDelay(DWORD dwDelay);

	//##ModelId=474D3053030E
	static long		m_lProcessDrawClipboardDelay;
	//##ModelId=474D30540020
	static long		GetProcessDrawClipboardDelay();
	//##ModelId=474D30540050
	static void		SetProcessDrawClipboardDelay(long lDelay);

	//##ModelId=474D3054006E
	static BOOL		m_bEnableDebugLogging;
	//##ModelId=474D305400FB
	static BOOL		GetEnableDebugLogging();
	//##ModelId=474D3054011B
	static void		SetEnableDebugLogging(BOOL bEnable);

	//##ModelId=474D30540149
	static BOOL		m_bEnsureConnectToClipboard;
	//##ModelId=474D30540272
	static BOOL		GetEnsureConnectToClipboard();
	//##ModelId=474D30540274
	static void		SetEnsureConnectToClipboard(BOOL bSet);

	//##ModelId=474D30540291
	static BOOL		GetPromptWhenDeletingClips();
	//##ModelId=474D305402A1
	static void		SetPromptWhenDeletingClips(BOOL bSet);

	//##ModelId=474D305402C0
	static CString	GetLastImportDir();
	//##ModelId=474D305402C2
	static void		SetLastImportDir(CString csDir);

	//##ModelId=474D305402DF
	static CString	GetLastExportDir();
	//##ModelId=474D305402F0
	static void		SetLastExportDir(CString csDir);

	//##ModelId=474D3054033D
	static BOOL		GetUpdateDescWhenSavingClip();
	//##ModelId=474D3054035C
	static void		SetUpdateDescWhenSavingClip(BOOL bSet);

	//##ModelId=474D3054036C
	static bool		m_bOutputDebugString;

	//##ModelId=474D305403BB
	static CStringArray m_csNetworkPasswordArray;

	//##ModelId=474D3055007E
	static CString  GetPath(long lPathID);

	//##ModelId=474D3055008F
	static void		WriteU3Hwnd(HWND hWnd);
	//##ModelId=474D305500DC
	static __int64	nLastDbWriteTime;

	//##ModelId=474D30550187
	static long		GetDittoRestoreClipboardDelay();
	//##ModelId=474D305501A7
	static void		SetDittoRestoreClipboardDelay(long lDelay);

	//##ModelId=474D305501C7
	static void		GetCopyBufferItem(int nPos, CCopyBufferItem &Item);
	//##ModelId=474D30550224
	static void		SetCopyBufferItem(int nPos, CCopyBufferItem &Item);

	//##ModelId=474D30550244
	static CString  GetMultiPasteSeparator(bool bConvertToLineFeeds = true);
	//##ModelId=474D30550264
	static void		SetMultiPasteSeparator(CString csSep);

	//##ModelId=474D30550274
	static BOOL		GetSetCurrentDirectory();

	//##ModelId=474D30550282
	static CString GetPasteString(CString csAppName);
	//##ModelId=474D30550291
	static CString GetDefaultPasteString();

	//##ModelId=474D305502A1
	static CString GetCopyString(CString csAppName);
	//##ModelId=474D305502FF
	static CString GetDefaultCopyString();

	//##ModelId=474D3055030E
	static CString GetCutString(CString csAppName);
	//##ModelId=474D3055031E
	static CString GetDefaultCutString();

	//##ModelId=474D3055032E
	static BOOL	GetEditWordWrap();
	//##ModelId=474D3055033E
	static void	SetEditWordWrap(BOOL bSet);

	//##ModelId=474D3055034D
	static bool GetAllowFriends();

	//##ModelId=474D3055035C
	static bool		GetIsPortableDitto();
};

// global for easy access and for initialization of fast access variables
extern CGetSetOptions g_Opt; 
