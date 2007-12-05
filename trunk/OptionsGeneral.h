#if !defined(AFX_OPTIONSGENERAL_H__A13ABBF6_7636_4426_9A31_0189D4CA8F2F__INCLUDED_)
#define AFX_OPTIONSGENERAL_H__A13ABBF6_7636_4426_9A31_0189D4CA8F2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsGeneral.h : header file
//
#include "stdafx.h"
#include "CP_Main.h"
#include "OptionsSheet.h"
#include "NumberEdit.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsGeneral dialog

//##ModelId=474D303F00FB
class COptionsGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsGeneral)

// Construction
public:
	//##ModelId=474D303F011A
	COptionsGeneral();
	//##ModelId=474D303F011B
	~COptionsGeneral();

// Dialog Data
	//{{AFX_DATA(COptionsGeneral)
	enum { IDD = IDD_OPTIONS_GENERAL };
	//##ModelId=474D303F012B
	CButton	m_EnsureConnected;
	//##ModelId=474D303F014A
	CNumberEdit	m_SaveDelay;
	//##ModelId=474D303F014F
	CComboBox	m_cbLanguage;
	//##ModelId=474D303F0169
	CEdit	m_MaxClipSize;
	//##ModelId=474D303F0179
	CButton	m_btSendPasteMessage;
	//##ModelId=474D303F0198
	CButton	m_btHideDittoOnHotKey;
	//##ModelId=474D303F01A8
	CNumberEdit	m_DescTextSize;
	//##ModelId=474D303F01C6
	CButton	m_btGetPath;
	//##ModelId=474D303F01D6
	CEdit	m_ePath;
	//##ModelId=474D303F01F6
	CButton	m_btSetDatabasePath;
	//##ModelId=474D303F0205
	CButton	m_btCheckForUpdates;
	//##ModelId=474D303F0225
	CNumberEdit	m_eExpireAfter;
	//##ModelId=474D303F0244
	CNumberEdit	m_eMaxSavedCopies;
	//##ModelId=474D303F0263
	CButton	m_btMaximumCheck;
	//##ModelId=474D303F02A2
	CButton	m_btExpire;
	//##ModelId=474D303F02D0
	CButton		m_btShowIconInSysTray;
	//##ModelId=474D303F02F0
	CButton		m_btRunOnStartup;
	//##ModelId=474D303F031F
	CButton m_btAllowDuplicates;
	//##ModelId=474D303F033E
	CButton m_btUpdateTimeOnPaste;
	//##ModelId=474D303F035D
	CButton m_btSaveMultiPaste;
	//##ModelId=474D303F037B
	CString	m_csPlaySound;
	//##ModelId=474D303F039C
	CEdit m_ClipSeparator;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsGeneral)
	public:
	//##ModelId=474D303F03BA
	virtual BOOL OnSetActive();
	protected:
	//##ModelId=474D303F03C9
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//##ModelId=474D30400001
	virtual BOOL OnApply();
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	//##ModelId=474D30400011
	COptionsSheet *m_pParent;

	//##ModelId=474D30400030
	CString m_csTitle;

	//##ModelId=474D3040005E
	void FillLanguages();

	// Generated message map functions
	//{{AFX_MSG(COptionsGeneral)
	//##ModelId=474D3040005F
	virtual BOOL OnInitDialog();
	//##ModelId=474D3040006F
	afx_msg void OnBtCompactAndRepair();
	//##ModelId=474D3040007F
	afx_msg void OnCheckForUpdates();
	//##ModelId=474D3040008D
	afx_msg void OnSetDbPath();
	//##ModelId=474D3040009D
	afx_msg void OnGetPath();
	//##ModelId=474D3040009F
	afx_msg void OnSelectSound();
	//##ModelId=474D304000AE
	afx_msg void OnButtonPlay();
	//##ModelId=474D304000BD
	afx_msg void OnButtonAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSGENERAL_H__A13ABBF6_7636_4426_9A31_0189D4CA8F2F__INCLUDED_)
