#pragma once
#include "IClipAggregator.h"
#include "FileRecieve.h"

//##ModelId=474D307901E5
class CCF_HDropAggregator : public IClipAggregator
{
public:
	//##ModelId=474D30790204
	CCF_HDropAggregator(void);
	//##ModelId=474D30790224
	~CCF_HDropAggregator(void);

	//##ModelId=474D30790243
	virtual bool AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount);
	//##ModelId=474D30790262
	virtual HGLOBAL GetHGlobal();

protected:
	//##ModelId=474D30790273
	CFileRecieve m_DropFiles;
};
