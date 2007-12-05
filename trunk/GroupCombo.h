#if !defined(AFX_GROUPCOMBO_H__42D00360_95BE_49B5_AA39_E3B37CFCFF5B__INCLUDED_)
#define AFX_GROUPCOMBO_H__42D00360_95BE_49B5_AA39_E3B37CFCFF5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupCombo window

//##ModelId=474D3066009D
class CGroupCombo : public CComboBox
{
// Construction
public:
	//##ModelId=474D306600AE
	CGroupCombo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupCombo)
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D306600AF
	virtual ~CGroupCombo();

	//##ModelId=474D306600BD
	void FillCombo();
	//##ModelId=474D306600CC
	void FillCombo(long lParentID, long lSpaces);
	//##ModelId=474D306600DD
	BOOL SetCurSelOnItemData(long lItemData);
	//##ModelId=474D306600EC
	int GetItemDataFromCursel();

	//##ModelId=474D306600FB
	long m_lSkipGroupID;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGroupCombo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPCOMBO_H__42D00360_95BE_49B5_AA39_E3B37CFCFF5B__INCLUDED_)
