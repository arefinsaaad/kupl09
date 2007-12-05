#pragma once

#include "Winsock2.h"
#include "Encryption.h"
#include "TextConvert.h"
#include "RecieveSocket.h"
#include "FileSend.h"
#include "ServerDefines.h"


//##ModelId=474D307B030E
class CServer
{
public:
	//##ModelId=474D307B033D
	CServer();
	//##ModelId=474D307B036C
	~CServer();

	//##ModelId=474D307B036D
	void RunThread(SOCKET sock);

protected:
	//##ModelId=474D307B03BA
	void AddRemoteCF_HDROPFormat();

	//##ModelId=474D307B03C9
	void OnStart(CSendInfo &Info);
	//##ModelId=474D307C0002
	void OnDataEnd(CSendInfo &info);
	//##ModelId=474D307C0030
	void OnDataStart(CSendInfo &info);
	//##ModelId=474D307C007E
	void OnEnd(CSendInfo &info);
	//##ModelId=474D307C009D
	void OnExit(CSendInfo &info);
	//##ModelId=474D307C00BC
	void OnRequestFiles(CSendInfo &info);

protected:
	//##ModelId=474D307C00DC
	CClipList *m_pClipList;
	//##ModelId=474D307C00EC
	CClip *m_pClip;
	//##ModelId=474D307C013A
	CTextConvert m_Convert;
	//##ModelId=474D307C0158
	BOOL m_bSetToClipBoard;
	//##ModelId=474D307C01C6
	CString m_csIP;
	//##ModelId=474D307C0214
	CString m_csComputerName;
	//##ModelId=474D307C0272
	CString m_csDesc;
	//##ModelId=474D307C02E0
	CRecieveSocket m_Sock;
	//##ModelId=474D307C031F
	CClipFormat m_cf;
};

UINT  MTServerThread(LPVOID pParam);
UINT  ClientThread(LPVOID pParam);
