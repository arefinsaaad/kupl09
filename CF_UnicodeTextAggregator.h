#pragma once
#include "IClipAggregator.h"

//##ModelId=474D30790020
class CCF_UnicodeTextAggregator : public IClipAggregator
{
public:
	//##ModelId=474D3079003F
	CCF_UnicodeTextAggregator(CStringW csSeparator);
	//##ModelId=474D30790041
	~CCF_UnicodeTextAggregator(void);

	//##ModelId=474D3079007E
	virtual bool AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount);
	//##ModelId=474D30790090
	virtual HGLOBAL GetHGlobal();

protected:
	//##ModelId=474D3079009F
	CStringW m_csSeparator;
	//##ModelId=474D307900AE
	CStringW m_csNewText;
};
