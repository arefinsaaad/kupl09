#include "stdafx.h"
#include "CP_Main.h"
#include "ClipIds.h"
#include "tinyxml.h"
#include "TextConvert.h"
#include "Clip_ImportExport.h"
#include "CF_HDropAggregator.h"
#include "CF_UnicodeTextAggregator.h"
#include "CF_TextAggregator.h"
#include "richtextaggregator.h"
#include "htmlformataggregator.h"

// allocate an HGLOBAL of the given Format Type representing these Clip IDs.
//##ModelId=474D30750245
HGLOBAL CClipIDs::Render(UINT cfType)
{
	int count = GetSize();
	if(count <= 0)
	{
		return 0;
	}

	if(count == 1)
	{
		return CClip::LoadFormat(ElementAt(0), cfType);
	}

	CStringA SepA = CTextConvert::ConvertToChar(g_Opt.GetMultiPasteSeparator());
	CStringW SepW = CTextConvert::ConvertToUnicode(g_Opt.GetMultiPasteSeparator());

	if(cfType == CF_TEXT)
	{
		CCF_TextAggregator CFText(SepA);
		if(AggregateData(CFText, CF_TEXT, g_Opt.m_bMultiPasteReverse && g_Opt.m_bHistoryStartTop))
		{
			return CFText.GetHGlobal();
		}
	}
	else if(cfType == CF_UNICODETEXT)
	{
		CCF_UnicodeTextAggregator CFUnicodeText(SepW);
		if(AggregateData(CFUnicodeText, CF_UNICODETEXT, g_Opt.m_bMultiPasteReverse && g_Opt.m_bHistoryStartTop))
		{
			return CFUnicodeText.GetHGlobal();
		}
	}
	else if(cfType == CF_HDROP)
	{
		CCF_HDropAggregator HDrop;
		if(AggregateData(HDrop, CF_HDROP, g_Opt.m_bMultiPasteReverse && g_Opt.m_bHistoryStartTop))
		{
			return HDrop.GetHGlobal();
		}
	}
	else if(cfType == theApp.m_HTML_Format)
	{
		CHTMLFormatAggregator Html(SepA);
		if(AggregateData(Html, theApp.m_HTML_Format, g_Opt.m_bMultiPasteReverse && g_Opt.m_bHistoryStartTop))
		{
			return Html.GetHGlobal();
		}
	}
	else if(cfType == theApp.m_RTFFormat)
	{
		CRichTextAggregator RichText(SepA);
		if(AggregateData(RichText, theApp.m_RTFFormat, g_Opt.m_bMultiPasteReverse && g_Opt.m_bHistoryStartTop))
		{
			return RichText.GetHGlobal();
		}
	}
	
	return NULL;
}

//##ModelId=474D30750253
void CClipIDs::GetTypes(CClipTypes& types)
{
	int IDCount = GetSize();
	types.RemoveAll();

	if(IDCount == 1)
	{
		CClip::LoadTypes(ElementAt(0), types);
	}
	else if(IDCount > 1)
	{
		//Add the types that are common accross all paste ids
		long lCount;
		CMap<CLIPFORMAT, CLIPFORMAT, long, long> RenderTypes;

		for(int nIDPos = 0; nIDPos < IDCount; nIDPos++)
		{
			CClipTypes CurrTypes;
			CClip::LoadTypes(ElementAt(nIDPos), CurrTypes);

			int nTypeCount = CurrTypes.GetSize();

			for(int nType = 0; nType < nTypeCount; nType++)
			{	
				lCount = 0;
				if(nIDPos == 0 || RenderTypes.Lookup(CurrTypes[nType], lCount) == TRUE)
				{
					lCount++;
					RenderTypes.SetAt(CurrTypes[nType], lCount);
				}
			}
		}

		CLIPFORMAT Format;
		POSITION pos = RenderTypes.GetStartPosition();
		while(pos)
		{
			RenderTypes.GetNextAssoc(pos, Format, lCount);
			if(lCount == IDCount)
			{
				types.Add(Format);
			}			
		}

		//If there were no common types add the first clip
		if(types.GetSize() <= 0)
		{
			CClip::LoadTypes(ElementAt(0), types);
		}
	}
}

//##ModelId=474D30750272
bool CClipIDs::AggregateData(IClipAggregator &Aggregator, UINT cfType, BOOL bReverse)
{
	CString csSQL;
	LPWSTR Text = NULL;
	int nTextSize = 0;
	int numIDs = GetSize();
	int* pIDs = GetData();
	bool bRet = false;

	try
	{
		int nIndex;
		for(int i=0; i < numIDs; i++)
		{
			nIndex = i;
			if(bReverse)
			{
				nIndex = numIDs - i - 1;
			}

			csSQL.Format(_T("SELECT * FROM Data ")
				_T("INNER JOIN Main ON Main.lID = Data.lParentID ")
				_T("WHERE Data.strClipBoardFormat = '%s' ")
				_T("AND Main.lID = %d"),
				GetFormatName(cfType),
				pIDs[nIndex]);

			CppSQLite3Query q = theApp.m_db.execQuery(csSQL);

			if(q.eof() == false)
			{
				int nDataLen = 0;
				LPVOID pData = (LPVOID)q.getBlobField(_T("ooData"), nDataLen);
				if(pData == NULL)
				{
					continue;
				}

				if(Aggregator.AddClip(pData, nDataLen, i, numIDs))
				{
					bRet = true;
				}
			}
		}
	}
	CATCH_SQLITE_EXCEPTION
		catch(...)
	{

	}

	return bRet;
}

//----------------------------------------------
// ELEMENT (Clip or Group) MANAGEMENT FUNCTIONS
//----------------------------------------------

// returns the address of the given id in this array or NULL.
//##ModelId=474D30750282
long* CClipIDs::FindID(long lID)
{
	int count = GetSize();
	long* pID = (long*) GetData();

	for(int i=0; i < count; i++)
	{
		if(*pID == lID)
		{
			return pID;
		}
		pID++;
	}
	return NULL;
}

// Blindly Moves IDs into the lParentID Group sequentially with the given order
//##ModelId=474D30750292
BOOL CClipIDs::MoveTo(long lParentID, double dFirst, double dIncrement)
{
	try
	{
		int nCount = GetSize();
		for(int i = 0; i < nCount; i++)
		{
			theApp.m_db.execDMLEx(_T("UPDATE Main SET lParentID = %d, ")
									_T("lDontAutoDelete = %d WHERE lID = %d AND lID <> %d;"), 
									lParentID, 
									(long)CTime::GetCurrentTime().GetTime(),
									ElementAt(i),
									lParentID);
		}
	}
	CATCH_SQLITE_EXCEPTION
		
	return (TRUE);
}

// Empties this array and fills it with the elements of the given group ID
//##ModelId=474D307502DF
BOOL CClipIDs::LoadElementsOf(long lGroupID)
{
	SetSize(0);
	
	try
	{
		CppSQLite3Query q = theApp.m_db.execQueryEx(_T("SELECT lID FROM Main WHERE lParentID = %d"), lGroupID);
		while(q.eof() == false)
		{
			Add(q.getIntField(_T("lID")));
			q.nextRow();
		}
	}
	CATCH_SQLITE_EXCEPTION
		
	return GetSize();
}

// Creates copies (duplicates) of all items in this array and assigns the
// lParentID of the copies to the given "lParentID" group.
// - if lParentID <= 0, then the copies have the same parent as the source
// - pCopies is filled with the corresponding duplicate IDs.
// - pAddNewTable and pSeekTable are used for more efficient recursion.
// - the primary overhead for recursion is one ID array per level deep.
//   an alternative design would be to have one CMainTable per level deep,
//   but I thought that might be too costly, so I implemented it this way.

//##ModelId=474D307502E1
BOOL CClipIDs::CopyTo(long lParentID)
{
	int count = GetSize();
	if(count == 0)
		return TRUE;
		
	try
	{
		theApp.m_db.execDML(_T("begin transaction;"));

		for(int i = 0; i < count; i++)
		{
			int nID = ElementAt(i);

			CClip clip;

			if(clip.LoadMainTable(nID))
			{
				if(clip.LoadFormats(nID))
				{
					clip.MakeLatestTime();

					clip.m_lShortCut = 0;
					clip.m_lParent = lParentID;
					clip.m_csQuickPaste = "";

					if(clip.AddToDB(false) == false)
					{
						Log(_T("failed to add copy to database"));
					}
				}
			}
		}

		theApp.m_db.execDML(_T("commit transaction;"));
	}
	CATCH_SQLITE_EXCEPTION
		
	return TRUE;
}

//##ModelId=474D307502F0
BOOL CClipIDs::DeleteIDs()
{
	CPopup status(0, 0, ::GetForegroundWindow());
	bool bAllowShow;
	bAllowShow = IsAppWnd(::GetForegroundWindow());
	
	BOOL bRet = TRUE;
	int count = GetSize();
	
	if(count <= 0)
		return FALSE;

	try
	{
		theApp.m_db.execDML(_T("begin transaction;"));
		for(int i=0; i < count; i++)
		{
			if(bAllowShow)
				status.Show(StrF(_T("Deleting %d out of %d..."), i+1, count));

			if(i && i % 50)
			{
				theApp.m_db.execDML(_T("commit transaction;"));
				theApp.m_db.execDML(_T("begin transaction;"));
			}

			bRet = bRet && DeleteID(ElementAt(i));
		}

		theApp.m_db.execDML(_T("commit transaction;"));
	}
	CATCH_SQLITE_EXCEPTION_AND_RETURN(FALSE)
	
	return bRet;
}

//##ModelId=474D30750300
BOOL CClipIDs::CreateExportSqliteDB(CppSQLite3DB &db)
{
	BOOL bRet = FALSE;
	try
	{
		db.execDML(_T("CREATE TABLE Main(")
			_T("lID INTEGER PRIMARY KEY AUTOINCREMENT, ")
			_T("lVersion INTEGER, ")
			_T("mText TEXT);"));

		db.execDML(_T("CREATE TABLE Data(")
			_T("lID INTEGER PRIMARY KEY AUTOINCREMENT, ")
			_T("lParentID INTEGER, ")
			_T("strClipBoardFormat TEXT, ")
			_T("lOriginalSize INTEGER, ")
			_T("ooData BLOB);"));

		db.execDML(_T("CREATE UNIQUE INDEX Main_ID on Main(lID ASC)"));
		db.execDML(_T("CREATE UNIQUE INDEX Data_ID on Data(lID ASC)"));

		db.execDML(_T("CREATE TRIGGER delete_data_trigger BEFORE DELETE ON Main FOR EACH ROW\n")
			_T("BEGIN\n")
			_T("DELETE FROM Data WHERE lParentID = old.lID;\n")
			_T("END\n"));

		bRet = TRUE;
	}
	CATCH_SQLITE_EXCEPTION_AND_RETURN(FALSE)

	return bRet;
}

//##ModelId=474D307502FE
BOOL CClipIDs::Export(CString csFilePath)
{    
	int count = GetSize();
	if(count == 0)
		return TRUE;

	BOOL bRet = FALSE;

	if(FileExists(csFilePath) && DeleteFile(csFilePath) == FALSE)
	{
		Log(StrF(_T("Export::Error deleting the file %s"), csFilePath));
		return FALSE;
	}

	try
	{		
		CppSQLite3DB db;
		db.open(csFilePath);

		if(CreateExportSqliteDB(db) == FALSE)
			return FALSE;
	
		for(int i = 0; i < count; i++)
		{
			int nID = ElementAt(i);

			CClip_ImportExport clip;
			
			if(clip.LoadMainTable(nID))
			{
				if(clip.LoadFormats(nID))
				{
					clip.ExportToSqliteDB(db);
					bRet = TRUE;
				}
			}
		}

		db.close();
	}
	CATCH_SQLITE_EXCEPTION

	return bRet;
}
