#pragma once
#include "IClipAggregator.h"

//##ModelId=474D307900FB
class CCF_TextAggregator : public IClipAggregator
{
public:
	//##ModelId=474D30790149
	CCF_TextAggregator(CStringA csSepator);
	//##ModelId=474D30790158
	~CCF_TextAggregator(void);

	//##ModelId=474D30790168
	virtual bool AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount);
	//##ModelId=474D307901B6
	virtual HGLOBAL GetHGlobal();

protected:
	//##ModelId=474D307901C7
	CStringA m_csSeparator;
	//##ModelId=474D307901D6
	CStringA m_csNewText;
};
