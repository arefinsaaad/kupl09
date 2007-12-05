#pragma once

//##ModelId=474D307A03D9
typedef BOOL (*PLUGIN_CONVERT_DATABASE)(const char *, const char *);

//##ModelId=474D307B006E
class CAccessToSqlite
{
public:
	//##ModelId=474D307B009D
	CAccessToSqlite(void);

	//##ModelId=474D307B00AD
	BOOL ConvertDatabase(const TCHAR *pNewDatabase, const TCHAR *pOldDatabase);
public:
	//##ModelId=474D307B00EB
	~CAccessToSqlite(void);
};
