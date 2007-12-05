#include "stdafx.h"
#include ".\cf_hdropaggregator.h"

//##ModelId=474D30790204
CCF_HDropAggregator::CCF_HDropAggregator(void)
{
}

//##ModelId=474D30790224
CCF_HDropAggregator::~CCF_HDropAggregator(void)
{
}

//##ModelId=474D30790243
bool CCF_HDropAggregator::AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount)
{
	HDROP drop = (HDROP)GlobalLock((HDROP)lpData);
	int nNumFiles = DragQueryFile(drop, -1, NULL, 0);
	TCHAR file[MAX_PATH];

	for(int nFile = 0; nFile < nNumFiles; nFile++)
	{
		if(DragQueryFile(drop, nFile, file, sizeof(file)) > 0)
		{
			m_DropFiles.AddFile(file);
		}
	}

	return true;
}

//##ModelId=474D30790262
HGLOBAL CCF_HDropAggregator::GetHGlobal()
{
	return m_DropFiles.CreateCF_HDROPBuffer();
}
