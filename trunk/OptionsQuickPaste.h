#if !defined(AFX_OPTIONSQUICKPASTE_H__69465009_2717_4BD5_BFFC_8CD537732050__INCLUDED_)
#define AFX_OPTIONSQUICKPASTE_H__69465009_2717_4BD5_BFFC_8CD537732050__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsQuickPaste.h : header file
#include "NumberEdit.h"
#include "OptionsSheet.h"
#include "afxwin.h"
//

/////////////////////////////////////////////////////////////////////////////
// COptionsQuickPaste dialog

//##ModelId=474D303D03D9
class COptionsQuickPaste : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsQuickPaste)

// Construction
public:
	//##ModelId=474D303E0002
	COptionsQuickPaste();
	//##ModelId=474D303E0003
	~COptionsQuickPaste();

// Dialog Data
	//{{AFX_DATA(COptionsQuickPaste)
	enum { IDD = IDD_OPTIONS_QUICK_PASTE };
	//##ModelId=474D303E0011
	CButton	m_EnsureEntireWindowVisible;
	//##ModelId=474D303E0021
	CButton	m_ShowAllInMainList;
	//##ModelId=474D303E0040
	CButton	m_FindAsYouType;
	//##ModelId=474D303E0050
	CButton	m_btDrawRTF;
	//##ModelId=474D303E005F
	CButton	m_btShowThumbnails;
	//##ModelId=474D303E007F
	CButton	m_btDefaultButton;
	//##ModelId=474D303E008E
	CButton	m_btFont;
	//##ModelId=474D303E00AE
	CButton	m_btShowText;
	//##ModelId=474D303E00BD
	CNumberEdit	m_eLinesPerRow;
	//##ModelId=474D303E00DC
	CNumberEdit	m_eTransparencyPercent;
	//##ModelId=474D303E00EC
	CButton	m_btEnableTransparency;
	//##ModelId=474D303E010B
	CButton	m_btUseCtrlNum;
	//##ModelId=474D303E012B
	CButton m_btHistoryStartTop;
	//##ModelId=474D303E013A
	CButton m_btDescShowLeadingWhiteSpace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsQuickPaste)
	public:
	//##ModelId=474D303E0158
	virtual BOOL OnApply();
	protected:
	//##ModelId=474D303E0168
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	//##ModelId=474D303E0188
	COptionsSheet *m_pParent;

	//##ModelId=474D303E01A8
	CFont m_Font;
	//##ModelId=474D303E01C7
	LOGFONT m_LogFont;
	//##ModelId=474D303E01D5
	CString m_csTitle;


// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsQuickPaste)
	//##ModelId=474D303E01F5
	virtual BOOL OnInitDialog();
	//##ModelId=474D303E0204
	afx_msg void OnButtonFont();
	//##ModelId=474D303E0214
	afx_msg void OnButtonDefaultFault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//##ModelId=474D303E0225
	CButton m_PromptForDelete;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSQUICKPASTE_H__69465009_2717_4BD5_BFFC_8CD537732050__INCLUDED_)
