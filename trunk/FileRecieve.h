#pragma once

#include "RecieveSocket.h"
#include "FileTransferProgressDlg.h"

#define USER_CANCELED -2

//##ModelId=474D307E0001
class CFileRecieve
{
public:
	//##ModelId=474D307E0010
	CFileRecieve();
	//##ModelId=474D307E0020
	virtual ~CFileRecieve();

	//##ModelId=474D307E0022
	long RecieveFiles(SOCKET sock, CString csIP, CFileTransferProgressDlg *pProgress);
	//##ModelId=474D307E0032
	HGLOBAL CreateCF_HDROPBuffer();
	//##ModelId=474D307E003F
	void AddFile(CString csFile)	{ m_RecievedFiles.Add(csFile); }

protected:
	//##ModelId=474D307E0041
	long RecieveFileData(ULONG lFileSize, CString csFileName);

protected:
	//##ModelId=474D307E005F
	CRecieveSocket m_Sock;
	//##ModelId=474D307E009D
	CString m_csRecievingFromIP;
	//##ModelId=474D307E00DC
	CStringArray m_RecievedFiles;
	//##ModelId=474D307E010B
	CFileTransferProgressDlg *m_pProgress;
};
