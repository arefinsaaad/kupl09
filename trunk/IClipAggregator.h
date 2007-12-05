#pragma once

//##ModelId=474D3062009D
class IClipAggregator
{
public:
	//##ModelId=474D306200AD
	virtual bool AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount) = 0;
	//##ModelId=474D306200DB
	virtual HGLOBAL GetHGlobal() = 0;
};
