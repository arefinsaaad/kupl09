#pragma once
#include "afxcmn.h"


// COptionsCopyBuffers dialog

//##ModelId=474D304000DB
class COptionsCopyBuffers : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsCopyBuffers)

public:
	//##ModelId=474D304000EC
	COptionsCopyBuffers();
	//##ModelId=474D304000FB
	~COptionsCopyBuffers();

// Dialog Data
	enum { IDD = IDD_OPTIONS_COPY_BUFFERS };

protected:
	//##ModelId=474D304000FC
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(COptionsCopyBuffers)
	//##ModelId=474D3040010B
	virtual BOOL OnInitDialog();
	//##ModelId=474D3040011A
	virtual BOOL OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//##ModelId=474D3040012B
	CHotKeyCtrl m_CopyBuffer1;
	//##ModelId=474D3040013A
	CHotKeyCtrl m_PasteBuffer1;
	//##ModelId=474D3040014A
	CHotKeyCtrl m_CutBuffer1;
	//##ModelId=474D30400169
	CHotKeyCtrl m_CopyBuffer2;
	//##ModelId=474D30400179
	CHotKeyCtrl m_PasteBuffer2;
	//##ModelId=474D30400198
	CHotKeyCtrl m_CutBuffer2;
	//##ModelId=474D304001A8
	CHotKeyCtrl m_CopyBuffer3;
	//##ModelId=474D304001C7
	CHotKeyCtrl m_PasteBuffer3;
	//##ModelId=474D304001E6
	CHotKeyCtrl m_CutBuffer3;
};
