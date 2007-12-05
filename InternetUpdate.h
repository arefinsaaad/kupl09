// InternetUpdate.h: interface for the CInternetUpdate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERNETUPDATE_H__0ED6CFE4_1E10_4D32_93A1_1C5CC1FDA3D2__INCLUDED_)
#define AFX_INTERNETUPDATE_H__0ED6CFE4_1E10_4D32_93A1_1C5CC1FDA3D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=474D3061034C
class CInternetUpdate  
{
public:
	//##ModelId=474D3061037B
	CInternetUpdate();
	//##ModelId=474D3061037C
	virtual ~CInternetUpdate();

	//##ModelId=474D3061038C
	BOOL CheckForUpdate(HWND hParent, BOOL bCheckForPrevUpdate, BOOL bShowNoUpdatesDlg);

	//##ModelId=474D306103BA
	long GetRunningVersion();
	//##ModelId=474D306103BB
	long GetUpdateVersion();

	//##ModelId=474D306103C9
	CString GetVersionString(long lVersion);
	//##ModelId=474D30620001
	CString DownloadUpdate();
	
protected:
	//##ModelId=474D30620010
	long m_lRunningVersion;
	//##ModelId=474D30620020
	long m_lUpdateVersion;
	//##ModelId=474D3062006E
	HWND m_hParent;
	//##ModelId=474D3062006F
	BOOL m_bShowMessages;

	//##ModelId=474D3062007E
	BOOL RemoveOldUpdateFile();

};

#endif // !defined(AFX_INTERNETUPDATE_H__0ED6CFE4_1E10_4D32_93A1_1C5CC1FDA3D2__INCLUDED_)
