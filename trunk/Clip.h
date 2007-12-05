// ProcessCopy.h: classes for saving the clipboard to db
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSCOPY_H__185CBB6F_4B63_4397_8FF9_E18D777DA506__INCLUDED_)
#define AFX_PROCESSCOPY_H__185CBB6F_4B63_4397_8FF9_E18D777DA506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxole.h>
#include <afxtempl.h>
#include "tinyxml.h"

class CClip;
class CCopyThread;

//##ModelId=474D3076036C
typedef CArray<CLIPFORMAT, CLIPFORMAT> CClipTypes;

/*----------------------------------------------------------------------------*\
	COleDataObjectEx
\*----------------------------------------------------------------------------*/
//##ModelId=474D307603BA
class COleDataObjectEx : public COleDataObject
{
public:
	// creates global from IStream if necessary
	//##ModelId=474D30770001
	HGLOBAL GetGlobalData(CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtc = NULL);
};

/*----------------------------------------------------------------------------*\
	CClipFormat - holds the data of one clip format.
\*----------------------------------------------------------------------------*/
//##ModelId=474D3077007E
class CClipFormat
{
public:
	//##ModelId=474D3077008E
	CLIPFORMAT	m_cfType;
	//##ModelId=474D3077009D
    HGLOBAL		m_hgData;
	//##ModelId=474D307700AD
	bool		bDeleteData;
	//##ModelId=474D307700AE
	long		m_lDBID;

	//##ModelId=474D307700BC
	CClipFormat(CLIPFORMAT cfType = 0, HGLOBAL hgData = 0, long lDBID = -1);
	//##ModelId=474D307700FB
	~CClipFormat();

	//##ModelId=474D3077010A
	void Clear();
	//##ModelId=474D3077012A
	void Free();
};

/*----------------------------------------------------------------------------*\
	CClipFormats - holds an array of CClipFormat
\*----------------------------------------------------------------------------*/
//##ModelId=474D30770158
class CClipFormats : public CArray<CClipFormat,CClipFormat&>
{
public:
	// returns a pointer to the CClipFormat in this array which matches the given type
	//  or NULL if that type doesn't exist in this array.
	//##ModelId=474D307701C6
	CClipFormat* FindFormat(UINT cfType); 
};


/*----------------------------------------------------------------------------*\
	CClip - holds multiple CClipFormats and clip statistics
	- provides static functions for manipulating a Clip as a single unit.
\*----------------------------------------------------------------------------*/
//##ModelId=474D30770262
class CClip
{
public:
	//##ModelId=474D30770281
	CClip();
	//##ModelId=474D30770291
	~CClip();
	//##ModelId=474D307702C0
	const CClip& operator=(const CClip &clip);

	//##ModelId=474D307702FE
	static DWORD m_LastAddedCRC;
	//##ModelId=474D3077031E
	static long m_LastAddedID;

	//##ModelId=474D3077034C
	long m_ID;
	//##ModelId=474D307703CA
	CClipFormats m_Formats;
	//##ModelId=474D30780001
	CTime m_Time;
	//##ModelId=474D30780020
	ULONG m_lTotalCopySize;
	//##ModelId=474D3078003F
	long m_lParent;
	//##ModelId=474D3078005E
	long m_lDontAutoDelete;
	//##ModelId=474D3078007E
	long m_lShortCut;
	//##ModelId=474D3078008D
	BOOL m_bIsGroup;
	//##ModelId=474D3078008E
	DWORD m_CRC;
	//##ModelId=474D3078009D
	CString m_csQuickPaste;
	//##ModelId=474D307800AD
	CString m_Desc;					// 실제 ctrl+c 한 후에 복사 될 스트링
	//##ModelId=474D307800AE
	CString m_WebAddr;				// 스트링이 카피된 웹페이지 주소

	//##ModelId=474D307800BC
	void Clear();
	//##ModelId=474D307800CC
	void EmptyFormats();
	//##ModelId=474D307800DB
	bool AddFormat(CLIPFORMAT cfType, void* pData, UINT nLen);
	//##ModelId=474D3078010A
	bool LoadFromClipboard(CClipTypes* pClipTypes);
	//##ModelId=474D30780168
	bool SetDescFromText(HGLOBAL hgData);
	//##ModelId=474D30780187
	bool SetDescFromType();
	//##ModelId=474D30780197
	bool AddToDB(bool bCheckForDuplicates = true);
	//##ModelId=474D307801A8
	bool ModifyMainTable();
	//##ModelId=474D307801E5
	bool SaveFromEditWnd(BOOL bUpdateDesc);
	//##ModelId=474D30780204
	void MakeLatestTime();
	//##ModelId=474D30780205
	BOOL LoadMainTable(long lID);
	//##ModelId=474D30780214
	DWORD GenerateCRC();

	// Allocates a Global containing the requested Clip's Format Data
	//##ModelId=474D30780224
	static HGLOBAL LoadFormat(long lID, UINT cfType);
	// Fills "formats" with the Data of all Formats in the db for the given Clip ID
	//##ModelId=474D30780234
	bool LoadFormats(long lID, bool bOnlyLoad_CF_TEXT = false);
	// Fills "types" with all Types in the db for the given Clip ID
	//##ModelId=474D30780262
	static void LoadTypes(long lID, CClipTypes& types);

	
protected:
	//##ModelId=474D30780281
	bool AddToMainTable();
	//##ModelId=474D30780282
	bool AddToDataTable();
	//##ModelId=474D307802A1
	int FindDuplicate();
};


/*----------------------------------------------------------------------------*\
	CClipList
\*----------------------------------------------------------------------------*/

//##ModelId=474D307802CF
class CClipList : public CList<CClip*,CClip*>
{
public:
	//##ModelId=474D3078036C
	~CClipList();
	// returns the number of clips actually saved
	// while this does empty the Format Data, it does not delete the Clips.
	//##ModelId=474D3078039B
	int AddToDB( bool bLatestTime = false, bool bShowStatus = true );

	//##ModelId=474D307803BB
	const CClipList& operator=(const CClipList &cliplist);
};

#endif // !defined(AFX_PROCESSCOPY_H__185CBB6F_4B63_4397_8FF9_E18D777DA506__INCLUDED_)
