// MultiLanguage.h: interface for the CMultiLanguage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTILANGUAGE_H__DA57BA64_C421_4368_9498_1EFCE49A5C52__INCLUDED_)
#define AFX_MULTILANGUAGE_H__DA57BA64_C421_4368_9498_1EFCE49A5C52__INCLUDED_

#include "Tinyxml.h"
#include "tinystr.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=474D3059004F
class CLangItem
{
public:
	//##ModelId=474D3059005E
	CLangItem()
	{
		m_nID = -1;
		m_csEnglishLang = "";
		m_csForeignLang = "";
		m_csID = "";
	}
	//##ModelId=474D3059005F
	int m_nID;
	//##ModelId=474D3059008D
	CString m_csID;
	//##ModelId=474D305900AD
	CString m_csEnglishLang;
	//##ModelId=474D305900AE
	CString m_csForeignLang;
};

//##ModelId=474D305900EB
typedef CArray<CLangItem*, CLangItem*> LANGUAGE_ARRAY;

//##ModelId=474D30590149
typedef CMap<CString, LPCTSTR, CLangItem*, CLangItem*> LANGUAGE_MAP;

//##ModelId=474D305901A7
class CMultiLanguage  
{
public:
	//##ModelId=474D305901D5
	CMultiLanguage();
	//##ModelId=474D305901D6
	virtual ~CMultiLanguage();

	//##ModelId=474D30590204
	bool LoadLanguageFile(CString csFile);

	//##ModelId=474D30590224
	bool UpdateRightClickMenu(CMenu *pMenu);
	//##ModelId=474D30590243
	bool UpdateTrayIconRightClickMenu(CMenu *pMenu);

	//##ModelId=474D30590262
	bool UpdateClipProperties(CWnd *pParent);
	//##ModelId=474D30590272
	bool UpdateOptionGeneral(CWnd *pParent);
	//##ModelId=474D30590282
	bool UpdateOptionSupportedTypes(CWnd *pParent);
	//##ModelId=474D30590292
	bool UpdateOptionShortcuts(CWnd *pParent);
	//##ModelId=474D305902A1
	bool UpdateOptionQuickPaste(CWnd *pParent);
	//##ModelId=474D305902CF
	bool UpdateOptionFriends(CWnd *pParent);
	//##ModelId=474D305902E0
	bool UpdateOptionFriendsDetail(CWnd *pParent);
	//##ModelId=474D305902F0
	bool UpdateOptionStats(CWnd *pParent);
	//##ModelId=474D305902FF
	bool UpdateOptionSupportedTypesAdd(CWnd *pParent);
	//##ModelId=474D3059030F
	bool UpdateMoveToGroups(CWnd *pParent);
	//##ModelId=474D3059031F
	bool UpdateOptionsSheet(CWnd *pParent);

	//##ModelId=474D3059032E
	CString GetString(CString csID, CString csDefault);

	//##ModelId=474D3059034C
	CString GetAuthor()	{ return m_csAuthor;		}
	//##ModelId=474D3059034D
	long	GetVersion(){ return m_lFileVersion;	}
	//##ModelId=474D3059035C
	CString GetNotes()	{ return m_csNotes;			}

	//##ModelId=474D3059035D
	void	SetOnlyGetHeader(bool bVal)	{ m_bOnlyGetHeader = true;	}
	//##ModelId=474D3059039B
	static CMenu* GetMenuPos(CMenu *pMenu, const CString &csLookingForMenuText, int &nMenuPos);

	//##ModelId=474D305903AD
	CString m_csLastError;

protected:
	//##ModelId=474D305903CA
	LANGUAGE_ARRAY m_RightClickMenu;
	//##ModelId=474D305903DA
	LANGUAGE_ARRAY m_TrayIconRightClickMenu;
	//##ModelId=474D305A0011
	LANGUAGE_ARRAY m_ClipProperties;
	//##ModelId=474D305A008E
	LANGUAGE_ARRAY m_OptionsGeneral;
	//##ModelId=474D305A009E
	LANGUAGE_ARRAY m_OptionsSupportedTypes;
	//##ModelId=474D305A00CD
	LANGUAGE_ARRAY m_OptionsShortcuts;
	//##ModelId=474D305A010B
	LANGUAGE_ARRAY m_OptionsQuickPaste;
	//##ModelId=474D305A012B
	LANGUAGE_ARRAY m_OptionsFriends;
	//##ModelId=474D305A014A
	LANGUAGE_ARRAY m_OptionsFriendsDetail;
	//##ModelId=474D305A0169
	LANGUAGE_ARRAY m_OptionsStats;
	//##ModelId=474D305A0188
	LANGUAGE_ARRAY m_OptionsSupportedTypesAdd;
	//##ModelId=474D305A01D6
	LANGUAGE_ARRAY m_MoveToGroups;
	//##ModelId=474D305A0215
	LANGUAGE_ARRAY m_OptionsSheet;

	//##ModelId=474D305A0244
	LANGUAGE_MAP	m_StringMap;

	//##ModelId=474D305A0262
	CString m_csAuthor;
	//##ModelId=474D305A0281
	CString m_csNotes;
	//##ModelId=474D305A02CF
	long	m_lFileVersion;

	//##ModelId=474D305A031E
	bool	m_bOnlyGetHeader;

protected:
	//##ModelId=474D305A034C
	bool LoadSection(TiXmlNode &doc, LANGUAGE_ARRAY &Array, CString csSection);
	//##ModelId=474D305A03C9
	bool LoadStringTableSection(TiXmlNode &doc, LANGUAGE_MAP &Map, CString csSection);

	//##ModelId=474D305B0020
	bool UpdateMenuToLanguage(CMenu *pMenu, LANGUAGE_ARRAY &Array);
	//##ModelId=474D305B007E
	bool UpdateWindowToLanguage(CWnd *pParent, LANGUAGE_ARRAY &Array);


	//##ModelId=474D305B00DB
	void ClearArrays();
	//##ModelId=474D305B00EB
	void ClearArray(LANGUAGE_ARRAY &Array);
	//##ModelId=474D305B00FB
	void ClearMap(LANGUAGE_MAP &Map);
};

#endif // !defined(AFX_MULTILANGUAGE_H__DA57BA64_C421_4368_9498_1EFCE49A5C52__INCLUDED_)
