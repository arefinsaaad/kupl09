// HyperLink.h : header file
//
//
// HyperLink static control. Will open the default browser with the given URL
// when the user clicks on the link.
//
// Copyright Chris Maunder, 1997
// Feel free to use and distribute. May not be sold for profit. 

#if !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CHyperLink window

//##ModelId=474D30620139
class CHyperLink : public CStatic
{
// Construction/destruction
public:
	//##ModelId=474D30620158
    CHyperLink();
	//##ModelId=474D30620168
    virtual ~CHyperLink();

// Attributes
public:

// Operations
public:

	//##ModelId=474D3062016A
    void SetURL(CString strURL);
	//##ModelId=474D30620179
    CString GetURL() const;

	//##ModelId=474D30620187
    void SetColours(COLORREF crLinkColour, COLORREF crVisitedColour, 
                    COLORREF crHoverColour = -1);
	//##ModelId=474D306201B7
    COLORREF GetLinkColour() const;
	//##ModelId=474D306201C7
    COLORREF GetVisitedColour() const;
	//##ModelId=474D306201D5
    COLORREF GetHoverColour() const;

	//##ModelId=474D306201E6
    void SetVisited(BOOL bVisited = TRUE);
	//##ModelId=474D306201F6
    BOOL GetVisited() const;

	//##ModelId=474D30620204
    void SetLinkCursor(HCURSOR hCursor);
	//##ModelId=474D30620214
    HCURSOR GetLinkCursor() const;

	//##ModelId=474D30620216
    void SetUnderline(BOOL bUnderline = TRUE);
	//##ModelId=474D30620252
    BOOL GetUnderline() const;

	//##ModelId=474D30620272
    void SetAutoSize(BOOL bAutoSize = TRUE);
	//##ModelId=474D306202A1
    BOOL GetAutoSize() const;

	//##ModelId=474D306202C0
	static HINSTANCE GotoURL(LPCTSTR url, int showcmd);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHyperLink)
    public:
	//##ModelId=474D306202EF
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
	//##ModelId=474D306202FE
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=474D3062030E
    void ReportError(int nError);
	//##ModelId=474D3062031F
    static LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	//##ModelId=474D306203C9
    void PositionWindow();
	//##ModelId=474D30630001
    void SetDefaultCursor();

// Protected attributes
protected:
    COLORREF m_crLinkColour, m_crVisitedColour;     // Hyperlink colours
	//##ModelId=474D30630010
    COLORREF m_crHoverColour;                       // Hover colour
	//##ModelId=474D30630020
    BOOL     m_bOverControl;                        // cursor over control?
	//##ModelId=474D30630030
    BOOL     m_bVisited;                            // Has it been visited?
	//##ModelId=474D3063003F
    BOOL     m_bUnderline;                          // underline hyperlink?
	//##ModelId=474D3063006E
    BOOL     m_bAdjustToFit;                        // Adjust window size to fit text?
	//##ModelId=474D306300AD
    CString  m_strURL;                              // hyperlink URL
	//##ModelId=474D306300DC
    CFont    m_Font;                                // Underline font if necessary
	//##ModelId=474D3063012A
    HCURSOR  m_hLinkCursor;                         // Cursor for hyperlink
	//##ModelId=474D30630178
    CToolTipCtrl m_ToolTip;                         // The tooltip

    // Generated message map functions
protected:
    //{{AFX_MSG(CHyperLink)
	//##ModelId=474D306301C6
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//##ModelId=474D30630214
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//##ModelId=474D30630281
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
	//##ModelId=474D306302CF
    afx_msg void OnClicked();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
