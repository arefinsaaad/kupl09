#pragma once
#include "clip.h"

//##ModelId=474D30760243
class CClip_ImportExport :	public CClip
{
public:
	//##ModelId=474D30760262
	CClip_ImportExport(void);
	//##ModelId=474D30760264
	~CClip_ImportExport(void);

	//##ModelId=474D30760272
	bool ExportToSqliteDB(CppSQLite3DB &m_db);
	//##ModelId=474D307602CF
	bool ImportFromSqliteDB(CppSQLite3DB &db, bool bAddToDB, bool bPutOnClipboard);
	
	//##ModelId=474D307602FE
	long m_lImportCount;

protected:
	//##ModelId=474D307602FF
	bool ImportFromSqliteV1(CppSQLite3DB &db, CppSQLite3Query &qMain);
	//##ModelId=474D3076032D
	bool Append_CF_TEXT_AND_CF_UNICODETEXT(CStringA &csCF_TEXT, CStringW &csCF_UNICODETEXT);

	//##ModelId=474D3076033E
	bool PlaceFormatsOnclipboard();
	//##ModelId=474D3076034C
	bool PlaceCF_TEXT_AND_CF_UNICODETEXT_OnClipboard(CStringA &csCF_TEXT, CStringW &csCF_UNICODETEXT);
};
