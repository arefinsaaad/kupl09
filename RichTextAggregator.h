#pragma once
#include "IClipAggregator.h"

//##ModelId=474D302603D9
class CRichTextAggregator : public IClipAggregator
{
public:
	//##ModelId=474D30270002
	CRichTextAggregator(CStringA csSeparator);
	//##ModelId=474D30270010
	~CRichTextAggregator(void);

	//##ModelId=474D30270012
	virtual bool AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount);
	//##ModelId=474D3027003F
	virtual HGLOBAL GetHGlobal();

protected:
	//##ModelId=474D30270050
	CStringA m_csNewText;
	//##ModelId=474D3027008E
	CStringA m_csSeparator;
};
