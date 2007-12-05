#if !defined(AFX_NUMBEREDIT_H__C68189CB_8445_4009_8F29_34645AEBD9C5__INCLUDED_)
#define AFX_NUMBEREDIT_H__C68189CB_8445_4009_8F29_34645AEBD9C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumberEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit window

//##ModelId=474D3085031E
class CNumberEdit : public CEdit
{
// Construction
public:
	//##ModelId=474D3085033D
	CNumberEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberEdit)
	//}}AFX_VIRTUAL

public:
	//##ModelId=474D3085033E
	double GetNumberD();
	//##ModelId=474D3085034C
	long GetNumber();
	//##ModelId=474D3085037B
	BOOL SetNumber(long lNumber);
	
	//##ModelId=474D308503AA
	void SetMaxNumber(long lMax)		{ m_dMax = lMax;		}
	//##ModelId=474D308503C9
	long GetMaxNumber()					{ return (long)m_dMax;	}
	
protected:
	//##ModelId=474D308503D9
	BOOL ValidateNumber(double dNumber);

	//##ModelId=474D30860002
	double m_dMax;

// Implementation
public:
	//##ModelId=474D30860010
	virtual ~CNumberEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNumberEdit)
	//##ModelId=474D30860012
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMBEREDIT_H__C68189CB_8445_4009_8F29_34645AEBD9C5__INCLUDED_)
