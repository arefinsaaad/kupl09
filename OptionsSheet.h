#if !defined(AFX_OPTIONSSHEET_H__D8A13849_DBC6_4CD6_A981_E572ECDC2E94__INCLUDED_)
#define AFX_OPTIONSSHEET_H__D8A13849_DBC6_4CD6_A981_E572ECDC2E94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

//##ModelId=474D303D0291
class COptionsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(COptionsSheet)

// Construction
public:
	//##ModelId=474D303D02A2
	COptionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsSheet)
	public:
	//##ModelId=474D303D02B2
	virtual int DoModal();
	//##ModelId=474D303D02C0
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D303D02C2
	virtual ~COptionsSheet();

	// Generated message map functions
protected:

	//##ModelId=474D303D02D0
	CPropertyPage *m_pKeyBoardOptions;
	//##ModelId=474D303D02E0
	CPropertyPage *m_pGeneralOptions;
	//##ModelId=474D303D030E
	CPropertyPage *m_pQuickPasteOptions;
	//##ModelId=474D303D031F
	CPropertyPage *m_pUtilites;
	//##ModelId=474D303D033E
	CPropertyPage *m_pStats;
	//##ModelId=474D303D035C
	CPropertyPage *m_pTypes;
	//##ModelId=474D303D036D
	CPropertyPage *m_pAbout;
	//##ModelId=474D303D038C
	CPropertyPage *m_pFriends;
	//##ModelId=474D303D03AB
	CPropertyPage *m_pCopyBuffers;


	//{{AFX_MSG(COptionsSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSSHEET_H__D8A13849_DBC6_4CD6_A981_E572ECDC2E94__INCLUDED_)
