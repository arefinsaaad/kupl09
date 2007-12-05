#pragma once

//##ModelId=474D301E005E
class CTextConvert
{
public:

	//##ModelId=474D301E006E
	CTextConvert();
	//##ModelId=474D301E006F
	~CTextConvert();

	//##ModelId=474D301E007E
	static bool ConvertFromUTF8(const CStringA &src, CString &dest);
	//##ModelId=474D301E008D
	static bool ConvertToUTF8(const CString &src, CStringA &dest);

	//##ModelId=474D301E009D
	static CStringA UnicodeStringToMultiByte(const CStringW &srcString);
	//##ModelId=474D301E00AD
	static CStringW MultiByteToUnicodeString(const CStringA &srcString);

	//##ModelId=474D301E00BC
	static CStringA ConvertToChar(const CString &src);
	//##ModelId=474D301E00BF
	static CStringW ConvertToUnicode(const CString &src);

protected:
};
