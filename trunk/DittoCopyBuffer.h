#pragma once

#include "ClipboardSaveRestore.h"
#include "afxmt.h"

//##ModelId=474D306D0187
class CClipboardSaveRestoreCopyBuffer : public CClipboardSaveRestore
{
public:
	//##ModelId=474D306D01A7
	CClipboardSaveRestoreCopyBuffer()
	{
		m_lRestoreDelay = 0;
	}
	//##ModelId=474D306D01D5
	long m_lRestoreDelay;
};

//##ModelId=474D306D0243
class CDittoCopyBuffer
{
public:
	//##ModelId=474D306D0272
	CDittoCopyBuffer();
	//##ModelId=474D306D0273
	~CDittoCopyBuffer(void);

	//##ModelId=474D306D02B0
	bool Active()	{ return m_bActive; }
	//##ModelId=474D306D02C0
	bool StartCopy(long lCopyBuffer, bool bCut = false);
	//##ModelId=474D306D02CF
	bool EndCopy(long lID);
	//##ModelId=474D306D02D1
	bool PastCopyBuffer(long lCopyBuffer);

	//##ModelId=474D306D02E0
	static bool PutClipOnDittoCopyBuffer(long lClipId, long lBuffer);
	//##ModelId=474D306D02F0
	static UINT DelayRestoreClipboard(LPVOID pParam);
	//##ModelId=474D306D032F
	static UINT StartCopyTimer(LPVOID pParam);

protected:
	//##ModelId=474D306D033F
	void EndRestoreThread();

protected:
	//##ModelId=474D306D034C
	long m_lCurrentDittoBuffer;
	//##ModelId=474D306D039C
	CClipboardSaveRestore m_SavedClipboard;
	//##ModelId=474D306D03AA
	bool m_bActive;
	//##ModelId=474D306D03BA
	DWORD m_dwLastPaste;
	//##ModelId=474D306E0011
	CEvent m_ActiveTimer;
	//##ModelId=474D306E0040
	CEvent m_RestoreTimer;
	//##ModelId=474D306E009E
	CEvent m_Pasting;
	//##ModelId=474D306E00DC
	CClipboardSaveRestoreCopyBuffer *m_pClipboard;
};
