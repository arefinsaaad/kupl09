#ifndef _CRC32DYNAMIC_H_
#define _CRC32DYNAMIC_H_

//##ModelId=474D306E0272
class CCrc32Dynamic
{
public:
	//##ModelId=474D306E0291
	CCrc32Dynamic();
	//##ModelId=474D306E0292
	virtual ~CCrc32Dynamic();

	//##ModelId=474D306E0294
	DWORD GenerateCrc32(const LPBYTE lpbArray, DWORD dSize, DWORD &dwCrc32);

protected:
	//##ModelId=474D306E02B0
	inline void CalcCrc32(const BYTE byte, DWORD &dwCrc32) const;
	
	//##ModelId=474D306E02C0
	void Init();
	//##ModelId=474D306E02CF
	void Free();

	//##ModelId=474D306E02D0
	DWORD *m_pdwCrc32Table;
};

#endif
