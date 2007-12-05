#if !defined(AFX_OPTIONSKEYBOARD_H__3E1A060F_019B_4117_8C53_15326D1ABFAE__INCLUDED_)
#define AFX_OPTIONSKEYBOARD_H__3E1A060F_019B_4117_8C53_15326D1ABFAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsKeyBoard.h : header file
//
#include "stdafx.h"
#include "CP_Main.h"
#include "OptionsSheet.h"
#include "afxwin.h"
#include "HyperLink.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsKeyBoard dialog

//##ModelId=474D303E0262
class COptionsKeyBoard : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsKeyBoard)

// Construction
public:
	//##ModelId=474D303E0281
	COptionsKeyBoard();
	//##ModelId=474D303E0282
	~COptionsKeyBoard();

// Dialog Data
	//{{AFX_DATA(COptionsKeyBoard)
	enum { IDD = IDD_OPTIONS_KEYSTROKES };
	//##ModelId=474D303E0292
	CHotKeyCtrl	m_NamedPaste;
	//##ModelId=474D303E02C1
	CButton	m_btSendPaste;
	//##ModelId=474D303E02E0
	CHotKeyCtrl	m_Nine;
	//##ModelId=474D303E02F0
	CHotKeyCtrl	m_Eight;
	//##ModelId=474D303E030F
	CHotKeyCtrl	m_Seven;
	//##ModelId=474D303E031F
	CHotKeyCtrl	m_Six;
	//##ModelId=474D303E033E
	CHotKeyCtrl	m_Five;
	//##ModelId=474D303E034D
	CHotKeyCtrl	m_Four;
	//##ModelId=474D303E036D
	CHotKeyCtrl	m_Three;
	//##ModelId=474D303E037C
	CHotKeyCtrl	m_Two;
	//##ModelId=474D303E039C
	CHotKeyCtrl	m_Ten;
	//##ModelId=474D303E03BB
	CHotKeyCtrl	m_One;
	//##ModelId=474D303E03DA
	CHotKeyCtrl	m_NamedCopy;
	//##ModelId=474D303F0002
	CHotKeyCtrl	m_HotKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsKeyBoard)
	public:
	//##ModelId=474D303F0020
	virtual LRESULT OnWizardNext();
	//##ModelId=474D303F0022
	virtual BOOL OnWizardFinish();
	//##ModelId=474D303F0031
	virtual BOOL OnApply();
	//##ModelId=474D303F0033
	virtual void OnCancel();
	protected:
	//##ModelId=474D303F0040
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	BOOL RegisterHotKey(WORD wHotKey);
//	BOOL ValidateHotKey(WORD wHotKey);

	//##ModelId=474D303F005F
	COptionsSheet *m_pParent;
	//##ModelId=474D303F007E
	CString m_csTitle;

	// Generated message map functions
	//{{AFX_MSG(COptionsKeyBoard)
	//##ModelId=474D303F009D
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//##ModelId=474D303F00AE
	CHyperLink m_CustomeKeysHelp;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSKEYBOARD_H__3E1A060F_019B_4117_8C53_15326D1ABFAE__INCLUDED_)
