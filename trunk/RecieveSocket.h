#pragma once

#include "Winsock2.h"
#include "Encryption.h"
#include "ServerDefines.h"

//##ModelId=474D307D0168
class CRecieveSocket
{
public:
	//##ModelId=474D307D0178
	CRecieveSocket(SOCKET sk = NULL);

	//##ModelId=474D307D0187
	~CRecieveSocket();
	
	//##ModelId=474D307D0188
	LPVOID ReceiveEncryptedData(long lInSize, long &lOutSize);
	//##ModelId=474D307D0198
	BOOL RecieveExactSize(char *pData, long lSize);
	//##ModelId=474D307D01B7
	BOOL RecieveCSendInfo(CSendInfo *pInfo);

	//##ModelId=474D307D01C6
	void FreeDecryptedData();

	//##ModelId=474D307D01C7
	SOCKET	GetSocket()				{ return m_Sock;	}
	//##ModelId=474D307D01D5
	void	SetSocket(SOCKET sock)	{ m_Sock = sock;	}

protected:
	//##ModelId=474D307D01E6
	CEncryption *m_pEncryptor;
	//##ModelId=474D307D01F6
	SOCKET m_Sock;
	//##ModelId=474D307D0204
	UCHAR *m_pDataReturnedFromDecrypt;	
};
