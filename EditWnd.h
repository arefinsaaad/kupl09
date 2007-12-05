#pragma once

#include "DittoRulerRichEditCtrl.h"
#include "TabCtrl.h"
#include "ClipIds.h"

//##ModelId=474D306800CC
class CEditWnd : public CWnd
{
	DECLARE_DYNAMIC(CEditWnd)

public:
	//##ModelId=474D3068011A
	CEditWnd();
	//##ModelId=474D3068012A
	virtual ~CEditWnd();

	//##ModelId=474D30680139
	bool EditIds(CClipIDs &Ids);
	//##ModelId=474D3068014A
	bool CloseEdits(bool bPrompt);

protected:
	DECLARE_MESSAGE_MAP()

	//##ModelId=474D30680198
	CTabCtrlEx m_Tabs;
	//##ModelId=474D30680244
	CToolBar m_ToolBar;
	//##ModelId=474D306802FF
	CToolTipCtrl m_ToolTip;
	//##ModelId=474D3068039C
	std::vector<CDittoRulerRichEditCtrl*> m_Edits;
	//##ModelId=474D306803DA
	CButton m_cbUpdateDescription;
	//##ModelId=474D3069005F
	CFont m_Font;
	//##ModelId=474D306900EB
	long m_lLastSaveID;

protected:
	//##ModelId=474D3069012A
	void MoveControls();
	//##ModelId=474D30690168
	long IsIDAlreadyInEdit(long lID, bool bSetFocus);
	//##ModelId=474D30690204
	bool AddItem(long lID);
	//##ModelId=474D30690252
	bool DoSave();
	//##ModelId=474D30690262
	bool DoSaveItem(long lIndex);

public:
	//##ModelId=474D306902CF
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D3069039B
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=474D306903D9
	afx_msg void OnSave();
	//##ModelId=474D306A0001
	afx_msg void OnDestroy();
	//##ModelId=474D306A0020
	afx_msg void OnSaveAll();
	//##ModelId=474D306A003F
	afx_msg void OnClose();
	//##ModelId=474D306A0041
	afx_msg void OnNew();
	//##ModelId=474D306A007E
	afx_msg void OnSaveCloseClipboard();
	//##ModelId=474D306A009D
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//##ModelId=474D306A00AD
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


