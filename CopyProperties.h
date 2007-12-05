#include "afxwin.h"
#if !defined(AFX_COPYPROPERTIES_H__129FE1CD_D305_487A_B88C_BB01CD9C1BB7__INCLUDED_)
#define AFX_COPYPROPERTIES_H__129FE1CD_D305_487A_B88C_BB01CD9C1BB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CopyProperties.h : header file
//

#include "GroupCombo.h"
#include "RichEditCtrlEx.h"
#include "DialogResizer.h"
#include "WebBrowser2.h"		// modified by kyo

/////////////////////////////////////////////////////////////////////////////
// CCopyProperties dialog

//##ModelId=474D30730204
class CCopyProperties : public CDialog
{
// Construction
public:
	//##ModelId=474D30730225
	CCopyProperties(long lCopyID, CWnd* pParent = NULL, CClip *pMemoryClip = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCopyProperties)
	enum { IDD = IDD_COPY_PROPERTIES };
	//##ModelId=474D30730253
	CEdit	m_QuickPasteText;
	//##ModelId=474D30730273
	CRichEditCtrlEx	m_RichEdit;
	//##ModelId=474D30730282
	CGroupCombo	m_GroupCombo;
	//##ModelId=474D307302C1
	CHotKeyCtrl	m_HotKey;
	//##ModelId=474D3073030F
	CListBox	m_lCopyData;
	//##ModelId=474D3073038B
	CString	m_eDate;
	//##ModelId=474D307303D9
	BOOL	m_bNeverAutoDelete;

	//##ModelId=474D30740031
	CEdit m_WebPage;	// 익스플로러에서 카피한 데이터에 대한 주소를 받아서 에디터에 표시
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyProperties)
	protected:
	//##ModelId=474D3074006E
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	//##ModelId=474D3074008D
	bool m_bChangedText;
	//##ModelId=474D307400CC
	long m_lGroupChangedTo;
	//##ModelId=474D307400FB
	void SetHideOnKillFocus(bool bVal)	{ m_bHideOnKillFocus = bVal; }
	//##ModelId=474D3074011A
	void SetHandleKillFocus(bool bVal)	{ m_bHandleKillFocus = bVal; }
	//##ModelId=474D30740139
	void SetToTopMost(bool bVal)		{ m_bSetToTopMost = bVal; }

// Implementation
protected:

	//##ModelId=474D30740178
	long m_lCopyID;
	//##ModelId=474D307401A8
	ARRAY m_DeletedData;
	//##ModelId=474D307401E5
	bool m_bDeletedData;
	//##ModelId=474D30740204
	bool m_bHideOnKillFocus;
	//##ModelId=474D30740262
	CDialogResizer m_Resize;
	//##ModelId=474D30740272
	bool m_bInGroup;
	//##ModelId=474D30740281
	bool m_bHandleKillFocus;
	//##ModelId=474D307402A1
	bool m_bSetToTopMost;
	//##ModelId=474D307402C1
	CClip *m_pMemoryClip;

	//##ModelId=474D307402CF
	void LoadDataIntoCClip(CClip &Clip);
	//##ModelId=474D307402EF
	void LoadDataFromCClip(CClip &Clip);

	// Generated message map functions
	//{{AFX_MSG(CCopyProperties)
	//##ModelId=474D3074030E
	virtual BOOL OnInitDialog();
	//##ModelId=474D3074031F
	virtual void OnOK();
	//##ModelId=474D3074037B
	afx_msg void OnDeleteCopyData();
	//##ModelId=474D3074039B
	virtual void OnCancel();
	//##ModelId=474D307403BA
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//##ModelId=474D30750010
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=474D3075003F
	afx_msg void OnBnClickedBtnGoWebaddr();				// modified by kyo
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	// 해당 URL을 이용해 웹 브라우저를 연다.
	//##ModelId=474D3075004F
	bool OpenNewWindow(LPCTSTR pAddress);
	//##ModelId=474D3075007E
	afx_msg void OnBnClickedBtnSaveasTxt();
	//##ModelId=474D3075009E
	afx_msg void OnBnClickedBtnSaveasPdf();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYPROPERTIES_H__129FE1CD_D305_487A_B88C_BB01CD9C1BB7__INCLUDED_)
