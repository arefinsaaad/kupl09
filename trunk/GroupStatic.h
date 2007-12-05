#if !defined(AFX_GROUPSTATIC_H__C7039DB6_84EE_4622_8054_6DBA48FA21A9__INCLUDED_)
#define AFX_GROUPSTATIC_H__C7039DB6_84EE_4622_8054_6DBA48FA21A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupStatic window

//##ModelId=474D30860272
class CGroupStatic : public CStatic
{
// Construction
public:
	//##ModelId=474D308602A1
	CGroupStatic();

// Attributes
public:

// Operations
public:

	//##ModelId=474D308602B0
	void SetTextColor( COLORREF color )		{ m_dwTextColor = color;	}
	//##ModelId=474D308602C0
	void SetBkColor( COLORREF color )		{ m_dwBkColor = color;		}
	//##ModelId=474D308602E0
	void SetFont( int nPointSize, LPCTSTR lpszFaceName, CDC* pDC = NULL );
	//##ModelId=474D3086032D
	void SetFont(CFont *pFont)				{ CStatic::SetFont(pFont);		}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupStatic)
	public:
	//##ModelId=474D3086033E
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D3086039C
	virtual ~CGroupStatic();

protected:
	//##ModelId=474D3086039E
	COLORREF m_dwTextColor;
	//##ModelId=474D308603BA
	COLORREF m_dwBkColor;
	//##ModelId=474D308603CA
	CFont*   m_pFont;
	//##ModelId=474D30870002
	CBrush   m_brush;
	//##ModelId=474D3087005E
	CString  m_strBuff;        // Holds the static controls contents before & after the control is displayed


	// Generated message map functions
protected:
	//{{AFX_MSG(CGroupStatic)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPSTATIC_H__C7039DB6_84EE_4622_8054_6DBA48FA21A9__INCLUDED_)
