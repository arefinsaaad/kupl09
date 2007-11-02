#pragma once

#include "RecieveSocket.h"
#include "FileTransferProgressDlg.h"

#define USER_CANCELED -2

class CFileRecieve
{
public:
	CFileRecieve();
	virtual ~CFileRecieve();

	long RecieveFiles(SOCKET sock, CString csIP, CFileTransferProgressDlg *pProgress);
	HGLOBAL CreateCF_HDROPBuffer();
	void AddFile(CString csFile)	{ m_RecievedFiles.Add(csFile); }

protected:
	long RecieveFileData(ULONG lFileSize, CString csFileName);

protected:
	CRecieveSocket m_Sock;
	CString m_csRecievingFromIP;
	CStringArray m_RecievedFiles;
	CFileTransferProgressDlg *m_pProgress;
};
