// Client.h: interface for the CClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENT_H__E9B55197_85B2_4ABF_92FF_E6301F346404__INCLUDED_)
#define AFX_CLIENT_H__E9B55197_85B2_4ABF_92FF_E6301F346404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Server.h"
#include "Encryption.h"
#include "SendSocket.h"

//##ModelId=474D307E0149
class CSendToFriendInfo
{
public:
	//##ModelId=474D307E0168
	CSendToFriendInfo()
	{
		m_pPopup = NULL;
		m_lPos = -1;
		m_pClipList = NULL;
		m_pPopup = NULL;
	}
	//##ModelId=474D307E0169
	~CSendToFriendInfo()
	{
		if(m_pClipList)
		{
			delete m_pClipList;
			m_pClipList = NULL;
		}
	}

	//##ModelId=474D307E0179
	CClipList *m_pClipList;
	//##ModelId=474D307E0187
	long m_lPos;
	//##ModelId=474D307E0188
	CString m_csIP;
	//##ModelId=474D307E01A8
	CPopup *m_pPopup;
	//##ModelId=474D307E01B6
	CString m_csErrorText;
};

//##ModelId=474D307E01E5
class CClient  
{
public:
	//##ModelId=474D307E0224
	CClient();
	//##ModelId=474D307E0233
	virtual ~CClient();

	//##ModelId=474D307E0235
	BOOL SendItem(CClip *pClip);
	
	//##ModelId=474D307E0253
	BOOL OpenConnection(const TCHAR* servername);
	//##ModelId=474D307E0272
	BOOL CloseConnection();

	//##ModelId=474D307E0273
	HGLOBAL RequestCopiedFiles(CClipFormat &HDropFormat, CString csIP, CString csComputerName);

protected:
	//##ModelId=474D307E02A1
	SOCKET m_Connection;

	//##ModelId=474D307E02B1
	CSendSocket m_SendSocket;

	//##ModelId=474D307E02C0
	BOOL SendClipFormat(CClipFormat* pCF);
	
protected:
	
};

BOOL SendToFriend(CSendToFriendInfo &Info);

UINT  SendClientThread(LPVOID pParam);

#endif // !defined(AFX_CLIENT_H__E9B55197_85B2_4ABF_92FF_E6301F346404__INCLUDED_)
