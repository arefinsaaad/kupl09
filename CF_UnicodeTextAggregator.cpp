#include "stdafx.h"
#include ".\cf_unicodetextaggregator.h"
#include "Misc.h"

//##ModelId=474D3079003F
CCF_UnicodeTextAggregator::CCF_UnicodeTextAggregator(CStringW csSeparator) :
	m_csSeparator(csSeparator)
{
}

//##ModelId=474D30790041
CCF_UnicodeTextAggregator::~CCF_UnicodeTextAggregator(void)
{
}

//##ModelId=474D3079007E
bool CCF_UnicodeTextAggregator::AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount)
{
	LPCWSTR pText = (LPCWSTR)lpData;
	if(pText == NULL)
	{
		return false;
	}

	//Ensure it's null terminated
	if(pText[nDataSize-1] != '\0')
	{
		int len = 0;
		for(len = 0; len < nDataSize && pText[len] != '\0'; len++ )
		{
		}
		// if it is not null terminated, skip this item
		if(len >= nDataSize)
			return false;
	}

	m_csNewText += pText;
	
	if(nPos != nCount-1)
	{
		m_csNewText += m_csSeparator;
	}

	return true;
}

//##ModelId=474D30790090
HGLOBAL CCF_UnicodeTextAggregator::GetHGlobal()
{
	long lLen = m_csNewText.GetLength() * sizeof(wchar_t);
	HGLOBAL hGlobal = NewGlobalP(m_csNewText.GetBuffer(lLen), lLen+sizeof(wchar_t));
	m_csNewText.ReleaseBuffer();

	return hGlobal;
}
