#include "stdafx.h"
#include "Options.h"
#include "AlphaBlend.h"
#include "Misc.h"
#include "TextConvert.h"
#include "sqlite\CppSQLite3.h"
#include "Path.h"

using namespace nsPath;

UINT WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nValue, LPCTSTR lpFileName)
{
	// Locals
	TCHAR	szBuff[25];

	// Format
	SPRINTF(szBuff, _T("%d"), nValue);

	// Write
	return WritePrivateProfileString(lpAppName, lpKeyName, szBuff, lpFileName);
}

//##ModelId=474D304700AD
long CGetSetOptions::m_nLinesPerRow;
//##ModelId=474D304A03D9
BOOL CGetSetOptions::m_bUseCtrlNumAccel;
//##ModelId=474D304B0233
BOOL CGetSetOptions::m_bAllowDuplicates;
//##ModelId=474D304B033E
BOOL CGetSetOptions::m_bUpdateTimeOnPaste;
//##ModelId=474D304C0149
BOOL CGetSetOptions::m_bSaveMultiPaste;
//##ModelId=474D304C02CF
BOOL CGetSetOptions::m_bShowPersistent;
//##ModelId=474D304C035C
BOOL CGetSetOptions::m_bHistoryStartTop;
//##ModelId=474D304D010A
long CGetSetOptions::m_bDescTextSize;
//##ModelId=474D304D0187
BOOL CGetSetOptions::m_bDescShowLeadingWhiteSpace;
//##ModelId=474D304D0281
BOOL CGetSetOptions::m_bAllwaysShowDescription;
//##ModelId=474D304D034C
long CGetSetOptions::m_bDoubleClickingOnCaptionDoes;
//##ModelId=474D304E004F
BOOL CGetSetOptions::m_bPrompForNewGroupName;
//##ModelId=474D304E010A
BOOL CGetSetOptions::m_bSendPasteOnFirstTenHotKeys;
//##ModelId=474D304E01C7
CSendClients CGetSetOptions::m_SendClients[MAX_SEND_CLIENTS];
//##ModelId=474D304E02B0
long CGetSetOptions::m_lAutoSendClientCount;
//##ModelId=474D304F00BC
CString CGetSetOptions::m_csIPListToPutOnClipboard;
//##ModelId=474D304F0168
BOOL CGetSetOptions::m_bLogSendReceiveErrors;
//##ModelId=474D304F031E
BOOL CGetSetOptions::m_bUseHookDllForFocus;
//##ModelId=474D304F039B
BOOL CGetSetOptions::m_HideDittoOnHotKeyIfAlreadyShown;
//##ModelId=474D3050012A
long CGetSetOptions::m_lPort;
//##ModelId=474D3050033D
BOOL CGetSetOptions::m_bDrawThumbnail;
//##ModelId=474D30510188
CStringA CGetSetOptions::m_csPassword;
//##ModelId=474D30510263
BOOL CGetSetOptions::m_bDrawRTF;
//##ModelId=474D3051037B
BOOL CGetSetOptions::m_bMultiPasteReverse;
//##ModelId=474D3052003F
CString CGetSetOptions::m_csPlaySoundOnCopy;
//##ModelId=474D305403BB
CStringArray CGetSetOptions::m_csNetworkPasswordArray;
//##ModelId=474D3052011B
BOOL CGetSetOptions::m_bSendPasteMessageAfterSelection;
//##ModelId=474D30520204
BOOL CGetSetOptions::m_bFindAsYouType;
//##ModelId=474D305202CF
BOOL CGetSetOptions::m_bEnsureEntireWindowCanBeSeen;
//##ModelId=474D30530011
BOOL CGetSetOptions::m_bShowAllClipsInMainList;
//##ModelId=474D30530168
long CGetSetOptions::m_lMaxClipSizeInBytes;
//##ModelId=474D30530215
DWORD CGetSetOptions::m_dwSaveClipDelay;
//##ModelId=474D3053030E
long CGetSetOptions::m_lProcessDrawClipboardDelay;
//##ModelId=474D3054006E
BOOL CGetSetOptions::m_bEnableDebugLogging;
//##ModelId=474D30540149
BOOL CGetSetOptions::m_bEnsureConnectToClipboard;
//##ModelId=474D3054036C
bool CGetSetOptions::m_bOutputDebugString;
//##ModelId=474D30430252
bool CGetSetOptions::m_bU3 = false;
//##ModelId=474D30430204
bool CGetSetOptions::m_bInConversion = false;
//##ModelId=474D30430158
bool CGetSetOptions::m_bFromIni = false;
//##ModelId=474D304301C6
CString CGetSetOptions::m_csIniFileName;
//##ModelId=474D305500DC
__int64 CGetSetOptions::nLastDbWriteTime = 0;

CGetSetOptions g_Opt;

//##ModelId=474D304300CC
CGetSetOptions::CGetSetOptions()
{
}

//##ModelId=474D3043011A
CGetSetOptions::~CGetSetOptions()
{

}

//##ModelId=474D304302A1
void CGetSetOptions::LoadSettings()
{
	m_csIniFileName = GetIniFileName(false);

	if(m_bU3)
	{
		m_bFromIni = true;
	}
	else
	{
		//First check to see if they have an ini file in my docs&settings - ditto
		if(FileExists(m_csIniFileName))
		{
			m_bFromIni = true;
		}
		else
		{
			//next check if they have an ini file in the application directory
			m_csIniFileName = GetIniFileName(true);
			if(FileExists(m_csIniFileName))
			{
				m_bFromIni = true;
			}
		}
	}

	//first time running set some defaults
	if(GetTotalCopyCount() <= 0)
	{
		SetMaxEntries(500);
		SetCheckForMaxEntries(TRUE);
		SetQuickPastePosition(POS_AT_CARET);
		SetDisableRecieve(TRUE);
	}

	GetSetCurrentDirectory();

	m_nLinesPerRow = GetLinesPerRow();
	m_bUseCtrlNumAccel = GetUseCtrlNumForFirstTenHotKeys();
	m_bAllowDuplicates = GetAllowDuplicates();
	m_bUpdateTimeOnPaste = GetUpdateTimeOnPaste();
	m_bSaveMultiPaste = GetSaveMultiPaste();
	m_bShowPersistent = GetShowPersistent();
	m_bHistoryStartTop = GetHistoryStartTop();
	m_bDescTextSize = GetDescTextSize();
	m_bDescShowLeadingWhiteSpace = GetDescShowLeadingWhiteSpace();
	m_bAllwaysShowDescription = GetAllwaysShowDescription();
	m_bDoubleClickingOnCaptionDoes = GetDoubleClickingOnCaptionDoes();
	m_bPrompForNewGroupName = GetPrompForNewGroupName();
	m_bSendPasteOnFirstTenHotKeys = GetSendPasteOnFirstTenHotKeys();
	m_csIPListToPutOnClipboard = GetListToPutOnClipboard();
	m_bLogSendReceiveErrors = GetLogSendReceiveErrors();
	
	//If running from U3 then we can't use the hook dll because we are unable
	//to delete the hook dll, it's loaded by other processes
	if(m_bU3)
		m_bUseHookDllForFocus = GetProfileLong("UseHookDllForFocus", FALSE);
	else
		m_bUseHookDllForFocus = GetProfileLong("UseHookDllForFocus", TRUE);

	m_HideDittoOnHotKeyIfAlreadyShown = GetHideDittoOnHotKeyIfAlreadyShown();
	m_lPort = GetPort();
	m_bDrawThumbnail = GetDrawThumbnail();
	m_csPassword = GetNetworkPassword();
	m_bDrawRTF = GetDrawRTF();
	m_bMultiPasteReverse = GetMultiPasteReverse();
	m_csPlaySoundOnCopy = GetPlaySoundOnCopy();
	m_bSendPasteMessageAfterSelection = GetSendPasteAfterSelection();
	m_bFindAsYouType = GetFindAsYouType();
	m_bEnsureEntireWindowCanBeSeen = GetEnsureEntireWindowCanBeSeen();
	m_bShowAllClipsInMainList = GetShowAllClipsInMainList();
	m_lMaxClipSizeInBytes = GetMaxClipSizeInBytes();
	m_dwSaveClipDelay = GetSaveClipDelay();
	m_lProcessDrawClipboardDelay = GetProcessDrawClipboardDelay();
	m_bEnableDebugLogging = GetEnableDebugLogging();
	m_bEnsureConnectToClipboard = GetEnsureConnectToClipboard();
	m_bOutputDebugString = false;

	GetExtraNetworkPassword(true);

#ifdef _DEBUG
	m_bUseHookDllForFocus = FALSE;
#endif

	for(int i = 0; i < MAX_SEND_CLIENTS; i++)
	{
		GetSendClients(i);
	}

	GetClientSendCount();


	//If running from a U3 device and no language file as been asigned
	//then use the language defined by the U3 launcher
	if(m_bU3)
	{
		CString csLanguage = GetLanguageFile();
		if(csLanguage.IsEmpty())
		{
			CString csLanguage = GETENV(_T("U3_ENV_LANGUAGE"));
			long lLanguage = ATOI(csLanguage);
			csLanguage.Empty();
			switch(lLanguage)
			{
			case 1036: //French
				csLanguage = _T("Français");
				break;

			case 1040: //Italian
				csLanguage = _T("Italiano");
				break;

			case 1031: //German
				csLanguage = _T("German");
				break;

			case 3082: //German
				csLanguage = _T("Español");
				break;
			}

			if(csLanguage.IsEmpty() == FALSE)
			{
				SetLanguageFile(csLanguage);
			}
		}
	}
}

//##ModelId=474D304303BA
void CGetSetOptions::ConverSettingsToIni()
{
	m_bInConversion = true;

	CSize sz;
	CPoint pt;

	GetQuickPasteSize(sz);
	SetQuickPasteSize(sz);
	
	GetQuickPastePoint(pt);
	SetQuickPastePoint(pt);

	GetEditWndSize(sz);
	SetEditWndSize(sz);

	GetEditWndPoint(pt);
	SetEditWndPoint(pt);

	SetShowIconInSysTray(GetShowIconInSysTray());
	SetRunOnStartUp(GetRunOnStartUp());
	SetEnableTransparency(GetEnableTransparency());
	SetTransparencyPercent(GetTransparencyPercent());
	SetLinesPerRow(GetLinesPerRow());
	SetQuickPastePosition(GetQuickPastePosition());
	SetCopyGap(GetCopyGap());
	SetDBPath(GetDBPath());
	SetCheckForMaxEntries(GetCheckForMaxEntries());
	SetCheckForExpiredEntries(GetCheckForExpiredEntries());
	SetMaxEntries(GetMaxEntries());
	SetExpiredEntries(GetExpiredEntries());
	SetTripCopyCount(GetTripCopyCount());
	SetTripPasteCount(GetTripPasteCount());
	SetTripDate(GetTripDate());
	SetTotalCopyCount(GetTotalCopyCount());
	SetTotalPasteCount(GetTotalPasteCount());
	SetTotalDate(GetTotalDate());
	SetUpdateFilePath(GetUpdateFilePath());
	SetUpdateInstallPath(GetUpdateInstallPath());	
	SetLastUpdate(GetLastUpdate());
	SetCheckForUpdates(GetCheckForUpdates());
	SetUseCtrlNumForFirstTenHotKeys(GetUseCtrlNumForFirstTenHotKeys());
	SetAllowDuplicates(GetAllowDuplicates());
	SetUpdateTimeOnPaste(GetUpdateTimeOnPaste());
	SetSaveMultiPaste(GetSaveMultiPaste());
	SetShowPersistent(GetShowPersistent());
	SetHistoryStartTop(GetHistoryStartTop());
	SetShowTextForFirstTenHotKeys(GetShowTextForFirstTenHotKeys());
	SetMainHWND(GetMainHWND());
	SetCaptionPos(GetCaptionPos());
	SetAutoHide(GetAutoHide());
	SetDescTextSize(GetDescTextSize());
	SetDescShowLeadingWhiteSpace(GetDescShowLeadingWhiteSpace());
	SetAllwaysShowDescription(GetAllwaysShowDescription());
	SetDoubleClickingOnCaptionDoes(GetDoubleClickingOnCaptionDoes());
	SetPrompForNewGroupName(GetPrompForNewGroupName());
	SetSendPasteOnFirstTenHotKeys(GetSendPasteOnFirstTenHotKeys());

	for(int i = 0; i < MAX_SEND_CLIENTS; i++)
	{
		GetSendClients(i);
		SetSendClients(m_SendClients[i], i);
	}

	SetListToPutOnClipboard(GetListToPutOnClipboard());
	SetLogSendReceiveErrors(GetLogSendReceiveErrors());
	SetHideDittoOnHotKeyIfAlreadyShown(GetHideDittoOnHotKeyIfAlreadyShown());
	SetPort(GetPort());
	SetDisableRecieve(GetDisableRecieve());

	LOGFONT font;
	GetFont(font);
	SetFont(font);

	SetDrawThumbnail(GetDrawThumbnail());	

	CStringA PassA = GetNetworkPassword();
	CString PassW = PassA;
	SetNetworkPassword(PassW);

	SetDrawRTF(GetDrawRTF());
	SetMultiPasteReverse(GetMultiPasteReverse());
	SetPlaySoundOnCopy(GetPlaySoundOnCopy());
	SetSendPasteAfterSelection(GetSendPasteAfterSelection());
	SetFindAsYouType(GetFindAsYouType());
	SetEnsureEntireWindowCanBeSeen(GetEnsureEntireWindowCanBeSeen());
	SetShowAllClipsInMainList(GetShowAllClipsInMainList());
	SetExtraNetworkPassword(GetExtraNetworkPassword(false));
	SetMaxClipSizeInBytes(GetMaxClipSizeInBytes());
	SetLanguageFile(GetLanguageFile());
	SetSaveClipDelay(GetSaveClipDelay());
	SetProcessDrawClipboardDelay(GetProcessDrawClipboardDelay());
	SetEnableDebugLogging(GetEnableDebugLogging());
	SetEnsureConnectToClipboard(GetEnsureConnectToClipboard());
	SetPromptWhenDeletingClips(GetPromptWhenDeletingClips());
	SetLastImportDir(GetLastImportDir());
	SetLastExportDir(GetLastExportDir());
	SetUpdateDescWhenSavingClip(GetUpdateDescWhenSavingClip());

	m_bInConversion = false;
}

//##ModelId=474D3043032D
CString CGetSetOptions::GetIniFileName(bool bLocalIniFile)
{
	CString csPath = _T("c:\\program files\\Ditto\\");

	if(m_bU3)
	{
		csPath = CGetSetOptions::GetPath(PATH_INI);
	}
	else
	{	
		if(bLocalIniFile)
		{
			csPath = GetFilePath(GetExeFileName());
		}
		else
		{
			LPMALLOC pMalloc;

			if(SUCCEEDED(::SHGetMalloc(&pMalloc))) 
			{ 
				LPITEMIDLIST pidlPrograms;

				SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidlPrograms);

				TCHAR string[MAX_PATH];
				SHGetPathFromIDList(pidlPrograms, string);

				pMalloc->Free(pidlPrograms);
				pMalloc->Release();

				csPath = string;		
			}
			FIX_CSTRING_PATH(csPath);
			csPath += "Ditto\\";
		}
	}

	if(FileExists(csPath) == FALSE)
		CreateDirectory(csPath, NULL);

	csPath = csPath + "Ditto.Settings";

	return csPath;
}

//##ModelId=474D304402DF
long CGetSetOptions::GetProfileLong(CString csName, long lDefaultValue, CString csNewPath)
{
	if(m_bFromIni && !m_bInConversion)
	{
		CString csApp(_T("Ditto"));

		if(csNewPath.IsEmpty() == FALSE)
		{
			csApp = csNewPath;
		}

		return GetPrivateProfileInt(csApp, csName, lDefaultValue, m_csIniFileName);
	}

	CString csPath(_T(REG_PATH));
	if(csNewPath.IsEmpty() == FALSE)
	{
		csPath += "\\" + csNewPath;
	}

	HKEY hkKey;

	long lResult = RegOpenKeyEx(HKEY_CURRENT_USER, csPath, NULL, KEY_READ, &hkKey);

	if(lResult != ERROR_SUCCESS)
		return lDefaultValue;

	DWORD buffer;
	DWORD len =  sizeof(buffer);
	DWORD type;

	lResult = ::RegQueryValueEx(hkKey, csName, 0, &type, (LPBYTE)&buffer, &len);

	RegCloseKey(hkKey);

	if(lResult == ERROR_SUCCESS)
		return (long)buffer;

	return lDefaultValue;
}

//##ModelId=474D3044035C
CString CGetSetOptions::GetProfileString(CString csName, CString csDefault, CString csNewPath)
{
	if(m_bFromIni && !m_bInConversion)
	{
		CString csApp(_T("Ditto"));

		if(csNewPath.IsEmpty() == FALSE)
		{
			csApp = csNewPath;
		}

		TCHAR cString[MAX_PATH];
		GetPrivateProfileString(csApp, csName, csDefault, cString, sizeof(cString), m_csIniFileName);

		return cString;
	}

	CString csPath(_T(REG_PATH));
	if(csNewPath.IsEmpty() == FALSE)
	{
		csPath += "\\" + csNewPath;
	}

	HKEY hkKey;
	long lResult = RegOpenKeyEx(HKEY_CURRENT_USER, csPath, NULL, KEY_READ, &hkKey);

	TCHAR szString[256];
	ZeroMemory(szString, sizeof(szString));
	DWORD dwBufLen = 256;

	lResult = ::RegQueryValueEx(hkKey , csName, NULL, NULL, (LPBYTE)szString, &dwBufLen);

	RegCloseKey(hkKey);

	if(lResult != ERROR_SUCCESS)
		return csDefault;

	return szString;
}

//##ModelId=474D30440291
BOOL CGetSetOptions::SetProfileLong(CString csName, long lValue)
{
	if(m_bFromIni)
	{
		return WritePrivateProfileInt(_T("Ditto"), csName, lValue, m_csIniFileName);
	}

	HKEY hkKey;
	DWORD dWord;
	long lResult = RegCreateKeyEx(HKEY_CURRENT_USER, _T(REG_PATH), NULL, 
		NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 
		NULL, &hkKey, &dWord);

	if(lResult != ERROR_SUCCESS)
		return FALSE;

	DWORD val = (DWORD)lValue;
	lResult = ::RegSetValueEx(hkKey, csName, 0, REG_DWORD, (LPBYTE)&val, sizeof(DWORD));

	RegCloseKey(hkKey);

	return lResult == ERROR_SUCCESS;
}

//##ModelId=474D3045003F
BOOL CGetSetOptions::SetProfileString(CString csName, CString csValue)
{
	if(m_bFromIni)
	{
		return WritePrivateProfileString(_T("Ditto"), csName, csValue, m_csIniFileName);
	}

	HKEY hkKey;
	DWORD dWord;
	long lResult = RegCreateKeyEx(HKEY_CURRENT_USER, _T(REG_PATH), NULL, 
		NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 
		NULL, &hkKey, &dWord);

	if(lResult != ERROR_SUCCESS)
		return FALSE;

	::RegSetValueEx(hkKey, csName, NULL, REG_SZ,
		(BYTE*)(LPCTSTR)csValue, csValue.GetLength()*sizeof(TCHAR));

	RegCloseKey(hkKey);

	return lResult == ERROR_SUCCESS;
}

//##ModelId=474D3045011A
BOOL CGetSetOptions::SetProfileData(CString csName, LPVOID lpData, DWORD dwLength)
{
	if(m_bFromIni)
	{
		ASSERT(!"SetProfileData not supported in .ini settings");
		return FALSE;
	}

	HKEY hkKey;
	DWORD dWord;
	long lResult = RegCreateKeyEx(HKEY_CURRENT_USER, _T(REG_PATH), NULL, 
		NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 
		NULL, &hkKey, &dWord);

	if(lResult != ERROR_SUCCESS)
		return FALSE;

	::RegSetValueEx(hkKey, csName, NULL, REG_BINARY,
		(BYTE*)lpData, dwLength);

	RegCloseKey(hkKey);

	return lResult == ERROR_SUCCESS;
}

//##ModelId=474D30440262
BOOL CGetSetOptions::GetProfileFont(CString csSection, LOGFONT &font)
{
	font.lfHeight = GetPrivateProfileInt(csSection, _T("Height"), 0, m_csIniFileName);
	font.lfWidth = GetPrivateProfileInt(csSection, _T("Width"), 0, m_csIniFileName);
	font.lfEscapement = GetPrivateProfileInt(csSection, _T("Escapement"), 0, m_csIniFileName);
	font.lfOrientation = GetPrivateProfileInt(csSection, _T("Orientation"), 0, m_csIniFileName);
	font.lfWeight = GetPrivateProfileInt(csSection, _T("Weight"), 0, m_csIniFileName);
	font.lfItalic = GetPrivateProfileInt(csSection, _T("Italic"), 0, m_csIniFileName);
	font.lfUnderline = GetPrivateProfileInt(csSection, _T("Underline"), 0, m_csIniFileName);
	font.lfStrikeOut = GetPrivateProfileInt(csSection, _T("StrikeOut"), 0, m_csIniFileName);
	font.lfCharSet = GetPrivateProfileInt(csSection, _T("CharSet"), 0, m_csIniFileName);
	font.lfOutPrecision = GetPrivateProfileInt(csSection, _T("OutPrecision"), 0, m_csIniFileName);
	font.lfClipPrecision = GetPrivateProfileInt(csSection, _T("ClipPrecision"), 0, m_csIniFileName);
	font.lfQuality = GetPrivateProfileInt(csSection, _T("Quality"), 0, m_csIniFileName);
	font.lfPitchAndFamily = GetPrivateProfileInt(csSection, _T("PitchAndFamily"), 0, m_csIniFileName);
	GetPrivateProfileString(csSection, _T("FaceName"), _T(""), font.lfFaceName, sizeof(font.lfFaceName), m_csIniFileName);

	return TRUE;
}

//##ModelId=474D304401F5
BOOL CGetSetOptions::SetProfileFont(CString csSection, LOGFONT &font)
{
	WritePrivateProfileInt(csSection, _T("Height"), font.lfHeight, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("Width"), font.lfWidth, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("Escapement"), font.lfEscapement, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("Orientation"), font.lfOrientation, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("Weight"), font.lfWeight, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("Italic"), font.lfItalic, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("Underline"), font.lfUnderline, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("StrikeOut"), font.lfStrikeOut, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("CharSet"), font.lfCharSet, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("OutPrecision"), font.lfOutPrecision, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("ClipPrecision"), font.lfClipPrecision, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("Quality"), font.lfQuality, m_csIniFileName);
	WritePrivateProfileInt(csSection, _T("PitchAndFamily"), font.lfPitchAndFamily, m_csIniFileName);
	WritePrivateProfileString(csSection, _T("FaceName"), font.lfFaceName, m_csIniFileName);

	return TRUE;
}

//##ModelId=474D304500DB
LPVOID CGetSetOptions::GetProfileData(CString csName, DWORD &dwLength)
{
	if(m_bFromIni && !m_bInConversion)
	{
		ASSERT(!"GetProfileData not supported in .ini settings");
		return NULL;
	}

	HKEY hkKey;

	long lResult = RegOpenKeyEx(HKEY_CURRENT_USER, _T(REG_PATH),
		NULL, KEY_READ, &hkKey);

	lResult = ::RegQueryValueEx(hkKey , csName, NULL, NULL, NULL, &dwLength);

	if(lResult != ERROR_SUCCESS)
		return NULL;

	LPVOID lpVoid = new BYTE[dwLength];

	lResult = ::RegQueryValueEx(hkKey , csName, NULL, NULL, (LPBYTE)lpVoid, &dwLength);

	RegCloseKey(hkKey);

	if(lResult != ERROR_SUCCESS)
		return NULL;

	return lpVoid;
}

//##ModelId=474D304400AD
BOOL CGetSetOptions::GetShowIconInSysTray() 
{
	return GetProfileLong("ShowIconInSystemTray", TRUE);
}

//##ModelId=474D30440168
BOOL CGetSetOptions::SetShowIconInSysTray(BOOL bShow) 
{
	return SetProfileLong("ShowIconInSystemTray", bShow);
}

//##ModelId=474D304601D5
BOOL CGetSetOptions::SetEnableTransparency(BOOL bCheck)
{
	return SetProfileLong("EnableTransparency", bCheck);
}

//##ModelId=474D30460281
BOOL CGetSetOptions::GetEnableTransparency()
{
	return GetProfileLong("EnableTransparency", FALSE);
}

//##ModelId=474D3046030E
BOOL CGetSetOptions::SetTransparencyPercent(long lPercent)
{
#ifdef AFTER_98
	if(lPercent > OPACITY_MAX)
		lPercent = OPACITY_MAX;
	if(lPercent < 0)
		lPercent = 0;

	return SetProfileLong("TransparencyPercent", lPercent);
#endif
	return FALSE;
}

//##ModelId=474D304603D9
long CGetSetOptions::GetTransparencyPercent()
{
#ifdef AFTER_98
	long lValue = GetProfileLong("TransparencyPercent", 14);

	if(lValue > OPACITY_MAX) lValue = OPACITY_MAX;
	if(lValue < 0) lValue = 0;

	return lValue;
#endif
	return 0;
}

//##ModelId=474D30470139
BOOL CGetSetOptions::SetLinesPerRow(long lLines)
{
	m_nLinesPerRow = lLines;
	return SetProfileLong("LinesPerRow", lLines);
}

//##ModelId=474D304701A7
long CGetSetOptions::GetLinesPerRow()
{
	return GetProfileLong("LinesPerRow", 2);
}

//##ModelId=474D30440197
BOOL CGetSetOptions::GetRunOnStartUp()
{
	HKEY hkRun;

	LONG nResult = RegOpenKeyEx(HKEY_CURRENT_USER,
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
		NULL, KEY_READ, &hkRun);

	if(nResult != ERROR_SUCCESS)
		return FALSE;

	nResult = RegQueryValueEx(hkRun, GetAppName(), NULL, NULL, NULL, NULL);
	RegCloseKey(hkRun);
	return nResult == ERROR_SUCCESS;
}

//##ModelId=474D304401C6
void CGetSetOptions::SetRunOnStartUp(BOOL bRun)
{
	//Can't set auto run when running from U3 device
	if(m_bU3)
		return;

	if(bRun == GetRunOnStartUp())
		return;

	HKEY hkRun;
	LONG nResult = RegOpenKeyEx(HKEY_CURRENT_USER,
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
		NULL, KEY_ALL_ACCESS, &hkRun);

	if(nResult != ERROR_SUCCESS)
		return;

	if(bRun)
	{
		CString sExeName = GetExeFileName();
		::RegSetValueEx(hkRun, GetAppName(), NULL, REG_SZ,
			(BYTE*)(LPCTSTR)sExeName, sExeName.GetLength()*sizeof(TCHAR));
	} 
	else 
	{
		::RegDeleteValue(hkRun, GetAppName());
	}

	::RegCloseKey(hkRun);
}

//##ModelId=474D30440020
CString CGetSetOptions::GetExeFileName()
{
	CString sExeName;
	GetModuleFileName(NULL, sExeName.GetBuffer(_MAX_PATH),_MAX_PATH);
	sExeName.ReleaseBuffer();
	return sExeName;
}

//##ModelId=474D3044003F
CString CGetSetOptions::GetAppName()
{
	return "Ditto";
}

//##ModelId=474D304701D5
BOOL CGetSetOptions::SetQuickPastePosition(long lPosition)
{
	return SetProfileLong("ShowQuickPastePosition", lPosition);
}

//##ModelId=474D30470214
long CGetSetOptions::GetQuickPastePosition()
{
	return GetProfileLong("ShowQuickPastePosition", POS_AT_PREVIOUS);
}

//##ModelId=474D30450197
BOOL CGetSetOptions::SetQuickPasteSize(CSize size)
{
	BOOL bRet = SetProfileLong("QuickPasteCX", size.cx);
	bRet = SetProfileLong("QuickPasteCY", size.cy);

	return bRet;
}
//##ModelId=474D30450252
void CGetSetOptions::GetQuickPasteSize(CSize &size)
{
	size.cx = GetProfileLong("QuickPasteCX", 300);
	size.cy = GetProfileLong("QuickPasteCY", 300);
	if(size.cx <= 0 && size.cy <= 0)
	{
		size.cx = 300;
		size.cy = 300;
	}
}

//##ModelId=474D304502FE
BOOL CGetSetOptions::SetQuickPastePoint(CPoint point)
{
	BOOL bRet = SetProfileLong("QuickPasteX", point.x);
	bRet = SetProfileLong("QuickPasteY", point.y);

	return bRet;
}

//##ModelId=474D304503C9
void CGetSetOptions::GetQuickPastePoint(CPoint &point)
{
	point.x = GetProfileLong("QuickPasteX", 300);
	point.y = GetProfileLong("QuickPasteY", 300);

	if(point.x <= 0 && point.y <= 0)
	{
		point.x = 300;
		point.y = 300;
	}
}

//##ModelId=474D30460030
BOOL CGetSetOptions::SetEditWndSize(CSize size)
{
	BOOL bRet = SetProfileLong("EditWndCX", size.cx);
	bRet = SetProfileLong("EditWndCY", size.cy);

	return bRet;
}

//##ModelId=474D3046007E
void CGetSetOptions::GetEditWndSize(CSize &size)
{
	size.cx = GetProfileLong("EditWndCX", 600);
	size.cy = GetProfileLong("EditWndCY", 600);
	if(size.cx <= 0 && size.cy <= 0)
	{
		size.cx = 600;
		size.cy = 600;
	}
}

//##ModelId=474D3046011A
BOOL CGetSetOptions::SetEditWndPoint(CPoint point)
{
	BOOL bRet = SetProfileLong("EditWndX", point.x);
	bRet = SetProfileLong("EditWndY", point.y);

	return bRet;
}

//##ModelId=474D30460168
void CGetSetOptions::GetEditWndPoint(CPoint &point)
{
	point.x = GetProfileLong("EditWndX", 100);
	point.y = GetProfileLong("EditWndY", 100);

	if(point.x <= 0 && point.y <= 0)
	{
		point.x = 100;
		point.y = 100;
	}
}

//##ModelId=474D30470243
long CGetSetOptions::GetCopyGap()
{
	return GetProfileLong("CopyGap", 150);
}

//##ModelId=474D30470281
void CGetSetOptions::SetCopyGap(long lGap)
{
	SetProfileLong("CopyGap", lGap);
}

//##ModelId=474D304800AD
BOOL CGetSetOptions::SetDBPathOld(CString csPath)
{
	return SetProfileString("DBPath", csPath);
}

//##ModelId=474D30480168
CString CGetSetOptions::GetDBPathOld()
{
	return GetProfileString("DBPath", "");
}

//##ModelId=474D3047030E
BOOL CGetSetOptions::SetDBPath(CString csPath)
{
	return SetProfileString("DBPath3", csPath);
}

//##ModelId=474D30480020
CString CGetSetOptions::GetDBPath()
{
	CString csDBPath;
	if(m_bU3)
	{
		csDBPath = GetProfileString("DBPath3", "");
		if(csDBPath.IsEmpty())
		{
			csDBPath = GetDefaultDBName();
		}

		CPath ExistingPath(csDBPath);
		csDBPath = CGetSetOptions::GetPath(PATH_DATABASE);
		csDBPath += ExistingPath.GetName();
	}
	else
	{
		csDBPath = GetProfileString("DBPath3", "");
	}

	return csDBPath;
}

//##ModelId=474D304801D5
void CGetSetOptions::SetCheckForMaxEntries(BOOL bVal)
{
	SetProfileLong("CheckForMaxEntries", bVal);
}

//##ModelId=474D30480291
BOOL CGetSetOptions::GetCheckForMaxEntries()
{
	BOOL bDefault = FALSE;
	if(m_bU3)
		bDefault = TRUE;

	return GetProfileLong("CheckForMaxEntries", bDefault);
}

//##ModelId=474D304802DF
void CGetSetOptions::SetCheckForExpiredEntries(BOOL bVal)
{
	SetProfileLong("CheckForExpiredEntries", bVal);
}

//##ModelId=474D3048037B
BOOL CGetSetOptions::GetCheckForExpiredEntries()
{
	return GetProfileLong("CheckForExpiredEntries", FALSE);
}

//##ModelId=474D30490020
void CGetSetOptions::SetMaxEntries(long lVal)
{
	SetProfileLong("MaxEntries", lVal);
}

//##ModelId=474D304900CC
long CGetSetOptions::GetMaxEntries()
{
	long lMax = 500;
	if(m_bU3)
		lMax = 75;
	return GetProfileLong("MaxEntries", lMax);
}

//##ModelId=474D30490149
void CGetSetOptions::SetExpiredEntries(long lVal)
{
	SetProfileLong("ExpiredEntries", lVal);
}

//##ModelId=474D304901F5
long CGetSetOptions::GetExpiredEntries()
{
	return GetProfileLong("ExpiredEntries", 5);
}

//##ModelId=474D30490224
void CGetSetOptions::SetTripCopyCount(long lVal)
{
	// negative means a relative offset
	if(lVal < 0)
		lVal = GetTripCopyCount() - lVal; // add the absolute value

	if(GetTripDate() == 0)
		SetTripDate(-1);

	SetProfileLong("TripCopies", lVal);
}

//##ModelId=474D30490272
long CGetSetOptions::GetTripCopyCount()
{
	return GetProfileLong("TripCopies", 0);
}

//##ModelId=474D304902B0
void CGetSetOptions::SetTripPasteCount(long lVal)
{
	// negative means a relative offset
	if(lVal < 0)
		lVal = GetTripPasteCount() - lVal; // add the absolute value

	if(GetTripDate() == 0)
		SetTripDate(-1);

	SetProfileLong("TripPastes", lVal);
}

//##ModelId=474D3049033D
long CGetSetOptions::GetTripPasteCount()
{
	return GetProfileLong("TripPastes", 0);
}

//##ModelId=474D304903AA
void CGetSetOptions::SetTripDate(long lDate)
{
	if(lDate == -1)
		lDate = (long)CTime::GetCurrentTime().GetTime();

	SetProfileLong("TripDate", lDate);
}

//##ModelId=474D304A0030
long CGetSetOptions::GetTripDate()
{
	return GetProfileLong("TripDate", 0);
}

//##ModelId=474D304A007E
void CGetSetOptions::SetTotalCopyCount(long lVal)
{
	// negative means a relative offset
	if(lVal < 0)
		lVal = GetTotalCopyCount() - lVal; // add the absolute value

	if(GetTotalDate() == 0)
		SetTotalDate(-1);

	SetProfileLong("TotalCopies", lVal);
}

//##ModelId=474D304A00BC
long CGetSetOptions::GetTotalCopyCount()
{
	return GetProfileLong("TotalCopies", 0);
}

//##ModelId=474D304A00DB
void CGetSetOptions::SetTotalPasteCount(long lVal)
{
	// negative means a relative offset
	if(lVal < 0)
		lVal = GetTotalPasteCount() - lVal; // add the absolute value

	if(GetTotalDate() == 0)
		SetTotalDate(-1);

	SetProfileLong("TotalPastes", lVal);
}

//##ModelId=474D304A012A
long CGetSetOptions::GetTotalPasteCount()
{
	return GetProfileLong("TotalPastes", 0);
}

//##ModelId=474D304A0168
void CGetSetOptions::SetTotalDate(long lDate)
{
	if(lDate == -1)
		lDate = (long)CTime::GetCurrentTime().GetTime();

	SetProfileLong("TotalDate", lDate);
}

//##ModelId=474D304A01B6
long CGetSetOptions::GetTotalDate()
{
	return GetProfileLong("TotalDate", 0);
}

//##ModelId=474D304A01F5
CString	CGetSetOptions::GetUpdateFilePath()			
{ 
	return GetProfileString("UpdateFilePath", "");	
}
//##ModelId=474D304A0214
BOOL CGetSetOptions::SetUpdateFilePath(CString cs)	
{ 
	return SetProfileString("UpdateFilePath", cs);	
}

//##ModelId=474D304A0262
CString	CGetSetOptions::GetUpdateInstallPath()			
{ 
	return GetProfileString("UpdateInstallPath", "");	
}
//##ModelId=474D304A0272
BOOL CGetSetOptions::SetUpdateInstallPath(CString cs)	
{ 
	return SetProfileString("UpdateInstallPath", cs);	
}

//##ModelId=474D304A02C0
long CGetSetOptions::GetLastUpdate()			
{ 
	return GetProfileLong("LastUpdateDay", 0);		
}
//##ModelId=474D304A02CF
long CGetSetOptions::SetLastUpdate(long lValue)	
{ 
	return SetProfileLong("LastUpdateDay", lValue);	
}

//##ModelId=474D304A032D
BOOL CGetSetOptions::GetCheckForUpdates()				
{ 
	return GetProfileLong("CheckForUpdates", TRUE);	
}
//##ModelId=474D304A036C
BOOL CGetSetOptions::SetCheckForUpdates(BOOL bCheck)	
{ 
	return SetProfileLong("CheckForUpdates", bCheck);	
}

//##ModelId=474D304B00CC
void CGetSetOptions::SetUseCtrlNumForFirstTenHotKeys(BOOL bVal)	
{	
	SetProfileLong("UseCtrlNumForFirstTenHotKeys", bVal);	
	m_bUseCtrlNumAccel = bVal;	
}
//##ModelId=474D304B0197
BOOL CGetSetOptions::GetUseCtrlNumForFirstTenHotKeys()			
{	
	return GetProfileLong("UseCtrlNumForFirstTenHotKeys", 0); 
}

//##ModelId=474D304B02A1
void CGetSetOptions::SetAllowDuplicates(BOOL bVal)	
{	
	SetProfileLong("AllowDuplicates", bVal); 
	m_bAllowDuplicates = bVal; 
}
//##ModelId=474D304B02EF
BOOL CGetSetOptions::GetAllowDuplicates()			
{	
	return GetProfileLong("AllowDuplicates", 0); 
}

//##ModelId=474D304C0030
void CGetSetOptions::SetUpdateTimeOnPaste(BOOL bVal)	
{	
	SetProfileLong("UpdateTimeOnPaste", bVal); 
	m_bUpdateTimeOnPaste = bVal; 
}
//##ModelId=474D304C00AD
BOOL CGetSetOptions::GetUpdateTimeOnPaste()			
{	
	return GetProfileLong("UpdateTimeOnPaste", TRUE); 
}

//##ModelId=474D304C0224
void CGetSetOptions::SetSaveMultiPaste(BOOL bVal)	
{	
	SetProfileLong("SaveMultiPaste", bVal); 
	m_bSaveMultiPaste = bVal; 
}
//##ModelId=474D304C0281
BOOL CGetSetOptions::GetSaveMultiPaste()			
{	
	return GetProfileLong("SaveMultiPaste", 0); 
}

//##ModelId=474D304C031E
void CGetSetOptions::SetShowPersistent(BOOL bVal)	
{	
	SetProfileLong("ShowPersistent", bVal); 
	m_bShowPersistent = bVal; 
}
//##ModelId=474D304C033D
BOOL CGetSetOptions::GetShowPersistent()			
{	
	return GetProfileLong("ShowPersistent", 0); 
}

//##ModelId=474D304D0001
void CGetSetOptions::SetHistoryStartTop(BOOL bVal)	
{	
	SetProfileLong("HistoryStartTop", bVal); 
	m_bHistoryStartTop = bVal; 
}
//##ModelId=474D304D0010
BOOL CGetSetOptions::GetHistoryStartTop()			
{	
	return GetProfileLong("HistoryStartTop", TRUE); 
}

//##ModelId=474D304D0020
void CGetSetOptions::SetShowTextForFirstTenHotKeys(BOOL bVal)	
{	
	SetProfileLong("ShowTextForFirstTenHotKeys", bVal);			
}
//##ModelId=474D304D003F
BOOL CGetSetOptions::GetShowTextForFirstTenHotKeys()			
{	
	return GetProfileLong("ShowTextForFirstTenHotKeys", TRUE);	
}

//##ModelId=474D304D004F
void CGetSetOptions::SetMainHWND(long lhWnd)	
{	
	SetProfileLong("MainhWnd", lhWnd);		
}
//##ModelId=474D304D006E
BOOL CGetSetOptions::GetMainHWND()				
{	
	return GetProfileLong("MainhWnd", 0);	
}

//##ModelId=474D304D007E
void CGetSetOptions::SetCaptionPos(long lPos)	
{	
	SetProfileLong("CaptionPos", lPos);					
}
//##ModelId=474D304D009D
long CGetSetOptions::GetCaptionPos()			
{	
	return GetProfileLong("CaptionPos", CAPTION_RIGHT);	
}

//##ModelId=474D304D00BC
void CGetSetOptions::SetAutoHide(BOOL bAutoHide)
{	
	SetProfileLong("AutoHide", bAutoHide);					
}
//##ModelId=474D304D00DB
BOOL CGetSetOptions::GetAutoHide()				
{	
	return GetProfileLong("AutoHide", FALSE);				
}

//##ModelId=474D304D0168
void CGetSetOptions::SetDescTextSize(long lSize)
{	
	SetProfileLong("DescTextSize", lSize); 
	m_bDescTextSize = lSize; 
}
//##ModelId=474D304D0178
long CGetSetOptions::GetDescTextSize()			
{	
	return GetProfileLong("DescTextSize", 500); 
}

//##ModelId=474D304D01F5
void CGetSetOptions::SetDescShowLeadingWhiteSpace(BOOL bVal)
{ 
	SetProfileLong("DescShowLeadingWhiteSpace", bVal); 
	m_bDescShowLeadingWhiteSpace = bVal; 
}
//##ModelId=474D304D0252
BOOL CGetSetOptions::GetDescShowLeadingWhiteSpace()         
{ 
	return GetProfileLong("DescShowLeadingWhiteSpace", FALSE); 
}

//##ModelId=474D304D02FE
void CGetSetOptions::SetAllwaysShowDescription(long bShow)	
{	
	SetProfileLong("AllwaysShowDescription", bShow); 
	m_bAllwaysShowDescription = bShow; 
}
//##ModelId=474D304D032D
BOOL CGetSetOptions::GetAllwaysShowDescription()			
{	
	return GetProfileLong("AllwaysShowDescription", FALSE); 
}

//##ModelId=474D304E0001
void CGetSetOptions::SetDoubleClickingOnCaptionDoes(long lOption)	
{	
	SetProfileLong("DoubleClickingOnCaptionDoes", lOption); 
	m_bDoubleClickingOnCaptionDoes = lOption; 
}
//##ModelId=474D304E0030
long CGetSetOptions::GetDoubleClickingOnCaptionDoes()				
{	
	return GetProfileLong("DoubleClickingOnCaptionDoes", TOGGLES_ALLWAYS_ON_TOP); 
}

//##ModelId=474D304E00BC
void CGetSetOptions::SetPrompForNewGroupName(BOOL bOption)	
{	
	SetProfileLong("PrompForNewGroupName", bOption); 
	m_bPrompForNewGroupName = bOption; 
}
//##ModelId=474D304E00EB
BOOL CGetSetOptions::GetPrompForNewGroupName()				
{	
	return GetProfileLong("PrompForNewGroupName", TRUE); 
}

//##ModelId=474D304E0178
void CGetSetOptions::SetSendPasteOnFirstTenHotKeys(BOOL bOption)	
{	
	SetProfileLong("SendPasteOnFirstTenHotKeys", bOption); 
	m_bSendPasteOnFirstTenHotKeys = bOption; 
}
//##ModelId=474D304E0197
BOOL CGetSetOptions::GetSendPasteOnFirstTenHotKeys()				
{	
	return GetProfileLong("SendPasteOnFirstTenHotKeys", TRUE); 
}

//##ModelId=474D304E037B
void CGetSetOptions::SetSendClients(CSendClients Client, int nPos)
{
	CString cs;

	cs.Format(_T("sendclient_ip_%d"), nPos);
	SetProfileString(cs, Client.csIP);

	cs.Format(_T("sendclient_autosend_%d"), nPos);
	SetProfileLong(cs, Client.bSendAll);

	cs.Format(_T("sendclient_description_%d"), nPos);
	SetProfileString(cs, Client.csDescription);

	Client.bShownFirstError = m_SendClients[nPos].bShownFirstError;

	m_SendClients[nPos] = Client;
}

//##ModelId=474D304E03D9
CSendClients CGetSetOptions::GetSendClients(int nPos)
{
	CSendClients Client;

	CString cs;

	cs.Format(_T("sendclient_ip_%d"), nPos);
	Client.csIP = GetProfileString(cs, "");

	cs.Format(_T("sendclient_autosend_%d"), nPos);
	Client.bSendAll = GetProfileLong(cs, FALSE);

	cs.Format(_T("sendclient_description_%d"), nPos);
	Client.csDescription = GetProfileString(cs, "");

	m_SendClients[nPos] = Client;

	return Client;
}

//##ModelId=474D304E036C
void CGetSetOptions::GetClientSendCount()
{
	m_lAutoSendClientCount = 0;
	for(int i = 0; i < MAX_SEND_CLIENTS; i++)
	{
		if(m_SendClients[i].csIP.GetLength() > 0)
		{
			if(m_SendClients[i].bSendAll)
				m_lAutoSendClientCount++;
		}
	}
}

//##ModelId=474D304F0139
CString	CGetSetOptions::GetListToPutOnClipboard()			
{ 
	CString cs = GetProfileString("ListToPutOnClipboard", "");
	cs.MakeUpper();
	return cs;
}
//##ModelId=474D304F0158
BOOL CGetSetOptions::SetListToPutOnClipboard(CString cs)	
{ 
	cs.MakeUpper();
	m_csIPListToPutOnClipboard = cs;
	return SetProfileString("ListToPutOnClipboard", cs); 

}

//##ModelId=474D304F02A1
void CGetSetOptions::SetLogSendReceiveErrors(BOOL bOption)
{
	m_bLogSendReceiveErrors = bOption;

	SetProfileLong("LogSendReceiveErrors", bOption);
}

//##ModelId=474D304F02EF
BOOL CGetSetOptions::GetLogSendReceiveErrors()
{
	return GetProfileLong("LogSendReceiveErrors", FALSE);
}

//##ModelId=474D305000AD
BOOL CGetSetOptions::GetHideDittoOnHotKeyIfAlreadyShown()
{
	return GetProfileLong("HideDittoOnHotKeyIfAlreadyShown", TRUE);
}

//##ModelId=474D305000CC
void CGetSetOptions::SetHideDittoOnHotKeyIfAlreadyShown(BOOL bVal)
{
	m_HideDittoOnHotKeyIfAlreadyShown = bVal;

	SetProfileLong("HideDittoOnHotKeyIfAlreadyShown", bVal);
}

//##ModelId=474D30500281
void CGetSetOptions::SetPort(long lPort)
{
	m_lPort = lPort;
	SetProfileLong("SendRecvPort", lPort);
}

//##ModelId=474D30500291
long CGetSetOptions::GetPort()
{
	return GetProfileLong("SendRecvPort", 23443);
}

//##ModelId=474D305002A1
BOOL CGetSetOptions::GetDisableRecieve()
{
	BOOL bDefault = FALSE;
	if(m_bU3)
		bDefault = TRUE;

	return GetProfileLong("DisableRecieve", bDefault);
}

//##ModelId=474D305002B0
void CGetSetOptions::SetDisableRecieve(BOOL bVal)
{
	SetProfileLong("DisableRecieve", bVal);
}

//##ModelId=474D305002C1
BOOL CGetSetOptions::GetFont(LOGFONT &font)
{
	if(m_bFromIni && !m_bInConversion)
	{
		GetProfileFont("DisplayFont", font);

		//Return true if there is a font name
		//other wise load the default font below
		if(font.lfFaceName[0] != 0)
		{
			return TRUE;
		}
	}
	else
	{
		DWORD dwLength = 0;
		#ifdef _UNICODE
			LPVOID lpVoid = GetProfileData("DisplayFont3", dwLength);
		#else
			LPVOID lpVoid = GetProfileData("DisplayFont", dwLength);
		#endif
		if(lpVoid)
		{
			if(sizeof(font) == dwLength)
			{
				memcpy(&font, lpVoid, dwLength);
				delete[] lpVoid;
				lpVoid = NULL;
				return TRUE;
			}
			else
			{
				ASSERT(!"invalid font struct size");
			}

			delete[] lpVoid;
			lpVoid = NULL;
		}
	}

	ZeroMemory(&font, sizeof(font));
	font.lfHeight = -11;
	font.lfWeight = 400;
	font.lfCharSet = 1;
	STRCPY(font.lfFaceName, _T("@Arial Unicode MS"));
	return TRUE;
}

//##ModelId=474D3050031E
void CGetSetOptions::SetFont(LOGFONT &font)
{
	if(m_bFromIni)
	{
		SetProfileFont("DisplayFont", font);
	}
	else
	{
		#ifdef _UNICODE
			CString csParam = "DisplayFont3";
		#else
			CString csParam = "DisplayFont";
		#endif

		SetProfileData(csParam, &font, sizeof(LOGFONT));
	}
}

//##ModelId=474D30510020
void CGetSetOptions::SetDrawThumbnail(long bDraw)
{
	SetProfileLong("DrawThumbnail", bDraw); 
	m_bDrawThumbnail = bDraw;
}

//##ModelId=474D305100CC
BOOL CGetSetOptions::GetDrawThumbnail()
{
	BOOL bDrawThumbnails = TRUE;
	if(g_Opt.m_bU3)
		bDrawThumbnails = FALSE;

	return GetProfileLong("DrawThumbnail", bDrawThumbnails);
}

//##ModelId=474D305300DD
void CGetSetOptions::SetExtraNetworkPassword(CString csPassword)
{
	SetProfileString("NetworkExtraPassword", csPassword);
}

//##ModelId=474D30530149
CString CGetSetOptions::GetExtraNetworkPassword(bool bFillArray)
{
	CString cs = GetProfileString("NetworkExtraPassword", "");

	if(bFillArray)
	{
		m_csNetworkPasswordArray.RemoveAll();

		TCHAR seps[]   = _T(",");
		TCHAR *token;

		TCHAR *pString = cs.GetBuffer(cs.GetLength());

		/* Establish string and get the first token: */
		token = STRTOK(pString, seps);
		while(token != NULL)
		{
			CString cs(token);
			cs.TrimLeft();
			cs.TrimRight();

			m_csNetworkPasswordArray.Add(cs);

			// Get next token
			token = STRTOK(NULL, seps);
		}

		cs.ReleaseBuffer();
	}

	return cs;
}

//##ModelId=474D30510233
void CGetSetOptions::SetNetworkPassword(CString csPassword)
{
	CTextConvert Con;
	Con.ConvertToUTF8(csPassword, m_csPassword);

	SetProfileString("NetworkStringPassword", csPassword);
}

//##ModelId=474D30510253
CStringA CGetSetOptions::GetNetworkPassword()
{
	CString cs = GetProfileString("NetworkStringPassword", "LetMeIn");

	CTextConvert Con;
	CStringA csReturn;
	Con.ConvertToUTF8(cs, csReturn);

	return csReturn;
}

//##ModelId=474D3051031E
void CGetSetOptions::SetDrawRTF(long bDraw)
{
	SetProfileLong("DrawRTF", bDraw); 
	m_bDrawRTF = bDraw;
}

//##ModelId=474D3051036C
BOOL CGetSetOptions::GetDrawRTF()
{
	return GetProfileLong("DrawRTF", FALSE);
}

//##ModelId=474D30520001
void CGetSetOptions::SetMultiPasteReverse(BOOL bVal)
{
	SetProfileLong("MultiPasteReverse", bVal); 
	m_bMultiPasteReverse = bVal;
}

//##ModelId=474D30520020
BOOL CGetSetOptions::GetMultiPasteReverse()
{
	return GetProfileLong("MultiPasteReverse", TRUE); 
}

//##ModelId=474D305200CC
void CGetSetOptions::SetPlaySoundOnCopy(CString cs)
{
	m_csPlaySoundOnCopy = cs;

	SetProfileString("PlaySoundOnCopy", cs);
}

//##ModelId=474D305200EB
CString CGetSetOptions::GetPlaySoundOnCopy()
{
	return GetProfileString("PlaySoundOnCopy", "");
}

//##ModelId=474D305201A7
void CGetSetOptions::SetSendPasteAfterSelection(BOOL bVal)
{
	m_bSendPasteMessageAfterSelection = bVal;

	SetProfileLong("SendPasteMessageAfterSelection", bVal);
}

//##ModelId=474D305201F7
BOOL CGetSetOptions::GetSendPasteAfterSelection()
{
	return GetProfileLong("SendPasteMessageAfterSelection", TRUE);
}

//##ModelId=474D305202A1
void CGetSetOptions::SetFindAsYouType(BOOL bVal)
{
	m_bFindAsYouType = bVal;
	SetProfileLong("FindAsYouType", bVal);
}

//##ModelId=474D305202C0
BOOL CGetSetOptions::GetFindAsYouType()
{
	return GetProfileLong("FindAsYouType", TRUE);
}

//##ModelId=474D305203AA
void CGetSetOptions::SetEnsureEntireWindowCanBeSeen(BOOL bVal)
{
	m_bEnsureEntireWindowCanBeSeen = bVal;
	SetProfileLong("EnsureEntireWindowCanBeSeen", bVal);
}

//##ModelId=474D30530003
BOOL CGetSetOptions::GetEnsureEntireWindowCanBeSeen()
{
	return GetProfileLong("EnsureEntireWindowCanBeSeen", TRUE);
}

//##ModelId=474D305300BC
void CGetSetOptions::SetShowAllClipsInMainList(BOOL bVal)
{
	m_bShowAllClipsInMainList = bVal;
	SetProfileLong("ShowAllClipsInMainList", bVal);
}

//##ModelId=474D305300DB
BOOL CGetSetOptions::GetShowAllClipsInMainList()
{
	return GetProfileLong("ShowAllClipsInMainList", TRUE);
}

//##ModelId=474D305301D5
long CGetSetOptions::GetMaxClipSizeInBytes()
{
	return GetProfileLong("MaxClipSizeInBytes", 0);
}

//##ModelId=474D305301E6
void CGetSetOptions::SetMaxClipSizeInBytes(long lSize)
{
	m_lMaxClipSizeInBytes = lSize;
	SetProfileLong("MaxClipSizeInBytes", lSize);
}

//##ModelId=474D305301F5
CString CGetSetOptions::GetLanguageFile()
{
	return GetProfileString("LanguageFile", "");
}

//##ModelId=474D30530204
void CGetSetOptions::SetLanguageFile(CString csLanguage)
{
	SetProfileString("LanguageFile", csLanguage);
}

//##ModelId=474D30530291
ULONG CGetSetOptions::GetSaveClipDelay()
{
	return (ULONG)GetProfileLong("SaveClipDelay", 500);
}

//##ModelId=474D305302B0
void CGetSetOptions::SetSaveClipDelay(DWORD dwDelay)
{
	m_dwSaveClipDelay = dwDelay;
	SetProfileLong("SaveClipDelay", dwDelay);
}

//##ModelId=474D30540020
long CGetSetOptions::GetProcessDrawClipboardDelay()
{
	return GetProfileLong("ProcessDrawClipboardDelay", 100);
}

//##ModelId=474D30540050
void CGetSetOptions::SetProcessDrawClipboardDelay(long lDelay)
{
	m_lProcessDrawClipboardDelay = lDelay;
	SetProfileLong("ProcessDrawClipboardDelay", lDelay);
}

//##ModelId=474D305400FB
BOOL CGetSetOptions::GetEnableDebugLogging()
{
	return GetProfileLong("EnableDebugLogging", FALSE);
}

//##ModelId=474D3054011B
void CGetSetOptions::SetEnableDebugLogging(BOOL bEnable)
{
	m_bEnableDebugLogging = bEnable;
	SetProfileLong("EnableDebugLogging", bEnable);
}

//##ModelId=474D30540272
BOOL CGetSetOptions::GetEnsureConnectToClipboard()
{
	return GetProfileLong("EnsureConnected", TRUE);
}

//##ModelId=474D30540274
void CGetSetOptions::SetEnsureConnectToClipboard(BOOL bSet)
{
	m_bEnsureConnectToClipboard = bSet;
	SetProfileLong("EnsureConnected", bSet);
}

//##ModelId=474D30540291
BOOL CGetSetOptions::GetPromptWhenDeletingClips()
{
	return GetProfileLong("PromptWhenDeletingClips", TRUE);
}

//##ModelId=474D305402A1
void CGetSetOptions::SetPromptWhenDeletingClips(BOOL bSet)
{
	SetProfileLong("PromptWhenDeletingClips", bSet);
}

//##ModelId=474D305402C0
CString CGetSetOptions::GetLastImportDir()
{
	return GetProfileString("LastImportDir", "");
}

//##ModelId=474D305402C2
void CGetSetOptions::SetLastImportDir(CString csDir)
{
	SetProfileString("LastImportDir", csDir);
}

//##ModelId=474D305402DF
CString CGetSetOptions::GetLastExportDir()
{
	return GetProfileString("LastExportDir", "");
}

//##ModelId=474D305402F0
void CGetSetOptions::SetLastExportDir(CString csDir)
{
	SetProfileString("LastExportDir", csDir);
}

//##ModelId=474D3054033D
BOOL CGetSetOptions::GetUpdateDescWhenSavingClip()
{
	return GetProfileLong("UpdateDescWhenSaving", TRUE);
}

//##ModelId=474D3054035C
void CGetSetOptions::SetUpdateDescWhenSavingClip(BOOL bSet)
{
	SetProfileLong("UpdateDescWhenSaving", bSet);
}

//##ModelId=474D3055007E
CString CGetSetOptions::GetPath(long lPathID)
{
	CString csDir = CGetSetOptions::GetExeFileName();
	csDir = GetFilePath(csDir);
	FIX_CSTRING_PATH(csDir);

	//U3_APP_DATA_PATH    -	<U3_DEVICE_PATH>\System\Apps\{app_unique_id}\Data
	//U3_HOST_EXEC_PATH	  - %APPDATA%\U3\{device_serial_number}\{app_unique_id}\Exec
	//U3_DEVICE_EXEC_PATH -	<U3_DEVICE_PATH>\System\Apps\{app_unique_id}\Exec

	switch(lPathID)
	{
	case PATH_HELP:
		if(m_bU3)
		{
			csDir = GETENV(_T("U3_DEVICE_EXEC_PATH"));
			FIX_CSTRING_PATH(csDir);
		}

		csDir += "Help\\";
		break;
	
	case PATH_LANGUAGE:
		if(m_bU3)
		{
			csDir = GETENV(_T("U3_DEVICE_EXEC_PATH"));
			FIX_CSTRING_PATH(csDir);
		}

		csDir += "language\\";

		break;

	case PATH_REMOTE_FILES:
		if(m_bU3)
		{
			csDir = GETENV(_T("U3_HOST_EXEC_PATH"));
			FIX_CSTRING_PATH(csDir);
		}

		csDir += "ReceivedFiles\\";
		break;

	case PATH_LOG_FILE:
		if(m_bU3)
		{
			csDir = GETENV(_T("U3_HOST_EXEC_PATH"));
			FIX_CSTRING_PATH(csDir);
		}

		break;


	case PATH_UPDATE_FILE:
		//same path as the executable
		break;

	case PATH_DATABASE:
		if(m_bU3)
		{
			csDir = GETENV(_T("U3_APP_DATA_PATH"));
			FIX_CSTRING_PATH(csDir);
		}
		break;


	case PATH_INI:
		if(m_bU3)
		{
			csDir = GETENV(_T("U3_APP_DATA_PATH"));
			FIX_CSTRING_PATH(csDir);
		}
		break;

	case PATH_U3_HWND_INI:
		if(m_bU3)
		{
			csDir = GETENV(_T("U3_HOST_EXEC_PATH"));
			FIX_CSTRING_PATH(csDir);
		}
		break;
	}

	return csDir;
}

//##ModelId=474D3055008F
void CGetSetOptions::WriteU3Hwnd(HWND hWnd)
{
	CString csIniFile = GetPath(PATH_U3_HWND_INI);
	csIniFile += _T("DittohWnd.ini");
	WritePrivateProfileInt(_T("Ditto"), _T("MainhWnd"), (int)hWnd, csIniFile);
}

//##ModelId=474D30550187
long CGetSetOptions::GetDittoRestoreClipboardDelay()
{
	return GetProfileLong("RestoreClipboardDelay", 750);

}
//##ModelId=474D305501A7
void CGetSetOptions::SetDittoRestoreClipboardDelay(long lDelay)
{
	SetProfileLong("RestoreClipboardDelay", lDelay);
}

//##ModelId=474D305501C7
void CGetSetOptions::GetCopyBufferItem(int nPos, CCopyBufferItem &Item)
{
	Item.m_lCopyHotKey = GetProfileLong(StrF(_T("CopyBufferCopyHotKey_%d"), nPos), 0);
	Item.m_lPasteHotKey = GetProfileLong(StrF(_T("CopyBufferPasteHotKey_%d"), nPos), 0);
	Item.m_lCutHotKey = GetProfileLong(StrF(_T("CopyBufferCutHotKey_%d"), nPos), 0);
	Item.m_bPlaySoundOnCopy = GetProfileLong(StrF(_T("CopyBufferPlaySound_%d"), nPos), 0);
}

//##ModelId=474D30550224
void CGetSetOptions::SetCopyBufferItem(int nPos, CCopyBufferItem &Item)
{
	SetProfileLong(StrF(_T("CopyBufferCopyHotKey_%d"), nPos), Item.m_lCopyHotKey);
	SetProfileLong(StrF(_T("CopyBufferPasteHotKey_%d"), nPos), Item.m_lPasteHotKey);
	SetProfileLong(StrF(_T("CopyBufferCutHotKey_%d"), nPos), Item.m_lCutHotKey);
	SetProfileLong(StrF(_T("CopyBufferPlaySound_%d"), nPos), Item.m_bPlaySoundOnCopy);
}

//##ModelId=474D30550244
CString CGetSetOptions::GetMultiPasteSeparator(bool bConvertToLineFeeds)
{
	CString csSep = GetProfileString(_T("MultiPasteSeparator"), _T("[LF]"));
	if(bConvertToLineFeeds)
	{
		CString csLineFeed(_T("\r\n"));
		csSep.Replace(_T("[LF]"), csLineFeed);
		csSep.Replace(_T("[lf]"), csLineFeed);
	}

	return csSep;
}

//##ModelId=474D30550264
void CGetSetOptions::SetMultiPasteSeparator(CString csSep)
{
	SetProfileString(_T("MultiPasteSeparator"), csSep);
}

//##ModelId=474D30550274
BOOL CGetSetOptions::GetSetCurrentDirectory()
{
	BOOL bRet = GetProfileLong(_T("SetCurrentDirectory"), FALSE);
	if(bRet)
	{
		CString csExePath = GetFilePath(GetExeFileName());
		FIX_CSTRING_PATH(csExePath);
		::SetCurrentDirectory(csExePath);
	}

	return bRet;
}

//##ModelId=474D3055035C
bool CGetSetOptions::GetIsPortableDitto()
{
	return GetProfileLong(_T("Portable"), FALSE) == TRUE;
}

//##ModelId=474D30550282
CString CGetSetOptions::GetPasteString(CString csAppName)
{
	CString csString = GetProfileString(csAppName, _T(""), _T("PasteStrings"));
	if(csString.IsEmpty())
		return GetDefaultPasteString();

	return csString;
}

//##ModelId=474D30550291
CString CGetSetOptions::GetDefaultPasteString()
{
	return GetProfileString(_T("DefaultPasteString"), _T("^v"));
}

//##ModelId=474D305502A1
CString CGetSetOptions::GetCopyString(CString csAppName)
{
	CString csString = GetProfileString(csAppName, _T(""), _T("CopyStrings"));
	if(csString.IsEmpty())
		return GetDefaultCopyString();

	return csString;
}

//##ModelId=474D305502FF
CString CGetSetOptions::GetDefaultCopyString()
{
	return GetProfileString(_T("DefaultCopyString"), _T("^c"));
}

//##ModelId=474D3055030E
CString CGetSetOptions::GetCutString(CString csAppName)
{
	CString csString = GetProfileString(csAppName, _T(""), _T("CutStrings"));
	if(csString.IsEmpty())
		return GetDefaultCutString();

	return csString;
}

//##ModelId=474D3055031E
CString CGetSetOptions::GetDefaultCutString()
{
	return GetProfileString(_T("DefaultCutString"), _T("^x"));
}

//##ModelId=474D3055032E
BOOL CGetSetOptions::GetEditWordWrap()
{
	return GetProfileLong(_T("EditWordWrap"), TRUE);
}

//##ModelId=474D3055033E
void CGetSetOptions::SetEditWordWrap(BOOL bSet)
{
	SetProfileLong(_T("EditWordWrap"), bSet);
}

//##ModelId=474D3055034D
bool CGetSetOptions::GetAllowFriends()
{
	return (GetProfileLong("AllowFriends", TRUE) == TRUE);
}
