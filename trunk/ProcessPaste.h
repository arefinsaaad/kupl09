// ProcessPaste.h: interface for the CProcessCopy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSPASTE_H__185CBB6F_4B63_4397_8FF9_E18D777DA506__INCLUDED_)
#define AFX_PROCESSPASTE_H__185CBB6F_4B63_4397_8FF9_E18D777DA506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ArrayEx.h"
#include "Clip.h"
#include "ClipIds.h"
#include "OleClipSource.h"


/*------------------------------------------------------------------*\
	CProcessPaste
\*------------------------------------------------------------------*/
//##ModelId=474D30370291
class CProcessPaste
{
public:
	//##ModelId=474D303702A2
	COleClipSource*	m_pOle;
	//##ModelId=474D303702A6
	bool m_bSendPaste;
	//##ModelId=474D303702B0
	bool m_bActivateTarget;
	//##ModelId=474D303702C0
	bool m_bOnlyPaste_CF_TEXT;
	//##ModelId=474D303702CF
	bool m_bPasteHTMLFormatAs_CF_TEXT;

	//##ModelId=474D303702D0
	CProcessPaste();
	//##ModelId=474D303702DF
	~CProcessPaste();

	//##ModelId=474D303702E0
	CClipIDs& GetClipIDs() { return m_pOle->m_ClipIDs; }

	//##ModelId=474D303702E1
	BOOL DoPaste();
	//##ModelId=474D303702EF
	BOOL DoDrag();

	//##ModelId=474D303702F0
	void MarkAsPasted();
	//##ModelId=474D303702F1
	static UINT MarkAsPastedThread(LPVOID pParam);
};

#endif // !defined(AFX_PROCESSPASTE_H__185CBB6F_4B63_4397_8FF9_E18D777DA506__INCLUDED_)
