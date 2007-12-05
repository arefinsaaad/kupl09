#if !defined(AFX_CARRAYEX_H__BE2C5983_CE26_11D3_BAE6_0000C0D475E2__INCLUDED_)
#define AFX_CARRAYEX_H__BE2C5983_CE26_11D3_BAE6_0000C0D475E2__INCLUDED_

//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

#include <afxtempl.h>


//##ModelId=474D3089039B
template <class TYPE> class CArrayEx : public CArray<TYPE,TYPE>
{
public:
	//##ModelId=474D308A00FE
	inline const TYPE&	operator[](int nIndex) const
	{
		ASSERT(0 <= nIndex && nIndex < GetSize());
		return (GetData()[nIndex]);
	};

	//##ModelId=474D308A0149
	inline const TYPE&	GetAt(int nIndex) const
	{
		ASSERT(0 <= nIndex && nIndex < GetSize());
		return (GetData()[nIndex]);
	};

	//##ModelId=474D308A0159
	inline TYPE& operator[](int nIndex)
	{
		ASSERT(0 <= nIndex && nIndex < GetSize());
		return (GetData()[nIndex]);
	};

	//##ModelId=474D308A0168
	void SortAscending()
	{
		qsort(GetData(), GetSize(), sizeof(TYPE), CArrayEx::CompareAscending);
	}

	//##ModelId=474D308A0169
	void SortDescending()
	{
		qsort(GetData(), GetSize(), sizeof(TYPE), CArrayEx::CompareDescending);
	}
	
	//##ModelId=474D308A0178
	static int CompareAscending(const void * p1, const void * p2)
	{	
		return *(TYPE *)p1 - *(TYPE *)p2;
	}

	//##ModelId=474D308A01B6
	static int CompareDescending(const void * p1, const void * p2)
	{	
		return *(TYPE *)p2 - *(TYPE *)p1;
	}
	
	//##ModelId=474D308A01C7
	BOOL Find(TYPE type)
	{
		LPVOID lpVoid = NULL;
		lpVoid = bsearch(&type, GetData(), GetSize(), sizeof(TYPE), CArrayEx::CompareAscending);

		if(lpVoid)
			return TRUE;
		
		return FALSE;
	}
};

//##ModelId=474D308A0214
typedef CArrayEx<int>				ARRAY;

#endif // !defined(AFX_OCARRAY_H__BE2C5983_CE26_11D3_BAE6_0000C0D475E2__INCLUDED_)
