// QuickPaste.h: interface for the CQuickPaste class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUICKPASTE_H__1B4A98E6_B719_402C_BDD4_7F3F97CD0EB0__INCLUDED_)
#define AFX_QUICKPASTE_H__1B4A98E6_B719_402C_BDD4_7F3F97CD0EB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QPasteWnd.h"

//##ModelId=474D302700EB
class CQuickPaste  
{
public:
	//##ModelId=474D3027012A
	CQuickPaste();
	//##ModelId=474D30270139
	virtual ~CQuickPaste();

	//##ModelId=474D30270149
	void Create(CWnd *pParent);
	//##ModelId=474D30270158
	void ShowQPasteWnd(CWnd *pParent, bool bAtPrevPos, bool bFromKeyboard, BOOL bReFillList);
	//##ModelId=474D30270169
	void HideQPasteWnd();
	//##ModelId=474D30270178
	BOOL CloseQPasteWnd();
	//##ModelId=474D30270187
	BOOL IsWindowVisibleEx();

	//##ModelId=474D30270188
	void UpdateFont()		{ if(m_pwndPaste) m_pwndPaste->UpdateFont();	}

//protected:
	//##ModelId=474D302701A8
	CQPasteWnd *m_pwndPaste;
};

#endif // !defined(AFX_QUICKPASTE_H__1B4A98E6_B719_402C_BDD4_7F3F97CD0EB0__INCLUDED_)
