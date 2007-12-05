#pragma once

#include "ClipIds.h"

/*------------------------------------------------------------------*\
	COleClipSource
\*------------------------------------------------------------------*/
//##ModelId=474D305802A1
class COleClipSource : public COleDataSource
{
	//DECLARE_DYNAMIC(COleClipSource)

public:
	//##ModelId=474D305802E0
	CClipIDs	m_ClipIDs;
	//##ModelId=474D305802EF
	bool		m_bLoadedFormats;
	//##ModelId=474D3058030E
	bool		m_bOnlyPaste_CF_TEXT;
	//##ModelId=474D3058032D
	bool		m_bPasteHTMLFormatAs_CF_TEXT;

	//##ModelId=474D3058034C
	COleClipSource();
	//##ModelId=474D3058035C
	virtual ~COleClipSource();

	//##ModelId=474D3058036D
	BOOL DoDelayRender();
	//##ModelId=474D3058036E
	BOOL DoImmediateRender();
	//##ModelId=474D3058038B
	long PutFormatOnClipboard(CClipFormats *pFormats, bool bPasteHTMLFormatAs_CF_TEXT);

public:
	//##ModelId=474D305803BB
	virtual BOOL OnRenderGlobalData(LPFORMATETC lpFormatEtc, HGLOBAL* phGlobal);

protected:
	//##ModelId=474D305803DA
	CClipFormats m_DelayRenderedFormats;
};
