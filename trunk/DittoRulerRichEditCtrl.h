#pragma once
#include "rulerricheditctrl\rulerricheditctrl.h"

#define SAVED_CLIP_TO_DB	1
#define DIDNT_NEED_TO_SAVE	2
//##ModelId=474D306C032D
class CDittoRulerRichEditCtrl :	public CRulerRichEditCtrl
{
public:
	//##ModelId=474D306C036C
	CDittoRulerRichEditCtrl(void);
	//##ModelId=474D306C038B
	~CDittoRulerRichEditCtrl(void);

	//##ModelId=474D306D0158
	enum eSaveTypes{stNONE = 0x1, stCF_TEXT = 0x2, stCF_UNICODETEXT = 0x4, stRTF = 0x8};

	//##ModelId=474D306C039B
	bool LoadItem(long lID, CString csDesc);
	//##ModelId=474D306D0001
	int SaveToDB(BOOL bUpdateDesc);
	//##ModelId=474D306D0020
	long GetTypeFlags(long lID);
	//##ModelId=474D306D0022
	bool CloseEdit(bool bPrompt, BOOL bUpdateDesc);
	//##ModelId=474D306D005E
	long GetDBID()		{ return m_lID; }
	//##ModelId=474D306D006E
	CString GetDesc()	{ return m_csDescription; }

	//##ModelId=474D306D006F
	void d();
	    
protected:
	//##ModelId=474D306D007E
	long m_lID;
	//##ModelId=474D306D008D
	long m_SaveTypes;
	//##ModelId=474D306D00CC
	CString m_csDescription;

	//##ModelId=474D306D00DB
	bool LoadRTFData(CClip &Clip);
	//##ModelId=474D306D011A
	bool LoadTextData(CClip &Clip);
};
