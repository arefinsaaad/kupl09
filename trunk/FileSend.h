#pragma once

#include "SendSocket.h"

//##ModelId=474D307D0214
class CFileSend  
{
public:
	//##ModelId=474D307D0233
	CFileSend();
	//##ModelId=474D307D0234
	virtual ~CFileSend();

	//##ModelId=474D307D0253
	BOOL SendClientFiles(SOCKET sock, CClipList *pClipList);

protected:
	//##ModelId=474D307D0272
	CClipFormat* GetCF_HDROP_Data(CClipList *pClipList);
	//##ModelId=474D307D02A1
	BOOL SendFile(CString csFile);

protected:
	//##ModelId=474D307D031F
	CSendSocket m_Send;
};
