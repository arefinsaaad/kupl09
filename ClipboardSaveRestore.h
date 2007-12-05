#pragma once

#include "Clip.h"

//##ModelId=474D307601F5
class CClipboardSaveRestore
{
public:
	//##ModelId=474D30760204
	CClipboardSaveRestore(void);
	//##ModelId=474D30760214
	~CClipboardSaveRestore(void);

	//##ModelId=474D30760216
	bool Save();
	//##ModelId=474D30760217
	bool Restore();
	//##ModelId=474D30760224
	void Clear()	{ m_Clipboard.RemoveAll(); }

	//##ModelId=474D30760226
	CClipFormats m_Clipboard;
};
