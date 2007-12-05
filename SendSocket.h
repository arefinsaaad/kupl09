// SendSocket.h: interface for the CSendSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENDSOCKET_H__4A4A5B96_8123_413C_8F86_A2875C9E5E48__INCLUDED_)
#define AFX_SENDSOCKET_H__4A4A5B96_8123_413C_8F86_A2875C9E5E48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Encryption.h"
#include "ServerDefines.h"

//##ModelId=474D307C03AA
class CSendSocket  
{
public:
	//##ModelId=474D307C03C9
	CSendSocket();
	//##ModelId=474D307C03CA
	virtual ~CSendSocket();

	//##ModelId=474D307C03CC
	void SetSocket(SOCKET sock)		{ m_Connection = sock;	}

	//##ModelId=474D307D007F
	CEncryption *m_pEncryptor;

	//##ModelId=474D307D009D
	BOOL SendCSendData(CSendInfo &data, MyEnums::eSendType type);
	//##ModelId=474D307D00CC
	BOOL SendExactSize(char *pData, long lLength, bool bEncrypt);

protected:
	//##ModelId=474D307D00EC
	SOCKET m_Connection;
};

#endif // !defined(AFX_SENDSOCKET_H__4A4A5B96_8123_413C_8F86_A2875C9E5E48__INCLUDED_)
