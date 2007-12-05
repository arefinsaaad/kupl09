#include "stdafx.h"
#include "AccessToSqlite.h"
#include "Options.h"
#include "Misc.h"
#include "TextConvert.h"


//##ModelId=474D307B00AD
BOOL CAccessToSqlite::ConvertDatabase(const TCHAR *pNewDatabase, const TCHAR *pOldDatabase)
{
	BOOL bRet = FALSE;

	CString csFile = CGetSetOptions::GetExeFileName();
	csFile = GetFilePath(csFile);
	csFile += "AccessToSqlite.dll";

 	HMODULE hModule = LoadLibrary(csFile);
 	PLUGIN_CONVERT_DATABASE Function;
 	if(hModule)
 	{
 		Function = (PLUGIN_CONVERT_DATABASE)GetProcAddress(hModule, "ConvertDatabase");
 
 		if(Function)
 		{
			CStringA csNew = CTextConvert::ConvertToChar(pNewDatabase);
			CStringA csOld = CTextConvert::ConvertToChar(pOldDatabase);

 			bRet = Function(csNew, csOld);
 		}
		else
		{
			MessageBox(NULL, _T("Error loading function from conversion DLL"), _T("Ditto Error"), MB_OK);
		}

		FreeLibrary(hModule);
 	}
	else
	{
		MessageBox(NULL, _T("Error loading conversion DLL"), _T("Ditto Error"), MB_OK);
	}

	return bRet;
}

//##ModelId=474D307B009D
CAccessToSqlite::CAccessToSqlite(void)
{
}

//##ModelId=474D307B00EB
CAccessToSqlite::~CAccessToSqlite(void)
{
}
