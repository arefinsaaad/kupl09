#include "stdafx.h"
#include ".\cf_textaggregator.h"
#include "Misc.h"

//##ModelId=474D30790149
CCF_TextAggregator::CCF_TextAggregator(CStringA csSepator) :
	m_csSeparator(csSepator)
{
}

//##ModelId=474D30790158
CCF_TextAggregator::~CCF_TextAggregator(void)
{
}

//##ModelId=474D30790168
bool CCF_TextAggregator::AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount)
{
	LPCSTR pText = (LPCSTR)lpData;
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

//##ModelId=474D307901B6
HGLOBAL CCF_TextAggregator::GetHGlobal()
{
	long lLen = m_csNewText.GetLength();
	HGLOBAL hGlobal = NewGlobalP(m_csNewText.GetBuffer(lLen), lLen+sizeof(char));
	m_csNewText.ReleaseBuffer();

	return hGlobal;
}
