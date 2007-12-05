#if !defined(AFX_AUTORICHEDITCTRL_H__C26D1E0E_DD32_11D2_B39F_000092914562__INCLUDED_)
#define AFX_AUTORICHEDITCTRL_H__C26D1E0E_DD32_11D2_B39F_000092914562__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoRichEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEx window

BOOL PASCAL AfxInitRichEditEx();

//##ModelId=474D308003C9
class _AFX_RICHEDITEX_STATE
{
public:
	//##ModelId=474D30810030
    _AFX_RICHEDITEX_STATE()
	{
		m_hInstRichEdit20 = NULL;
	}
	//##ModelId=474D3081003F
    virtual ~_AFX_RICHEDITEX_STATE()
	{
		if(m_hInstRichEdit20 != NULL)
		{
			::FreeLibrary(m_hInstRichEdit20);
		}
    }

	//##ModelId=474D30810041
    HINSTANCE m_hInstRichEdit20;
};

//##ModelId=474D3081009D
class CRichEditCtrlEx : public CRichEditCtrl
{
// Construction
public:
	//##ModelId=474D308100AE
	CRichEditCtrlEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRichEditCtrlEx)
	public:
	//##ModelId=474D308100BC
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D3081010A
	long GetSelectionFontSize();
	//##ModelId=474D3081010B
	CString GetSelectionFontName();
	//##ModelId=474D3081012B
	CStringArray m_saFontList;
	//##ModelId=474D30810139
	void GetSystemFonts(CStringArray &saFontList);
	//##ModelId=474D3081014A
	void SetFontSize(int nPointSize);
	//##ModelId=474D30810159
	void SetFontName(CString sFontName);
	//##ModelId=474D30810197
	void SelectColor();
	//##ModelId=474D308101B6
	bool ParagraphIsBulleted();
	//##ModelId=474D308101B7
	void SetParagraphBulleted();
	
	//##ModelId=474D308101D5
	PARAFORMAT GetParagraphFormat();
	
	//##ModelId=474D308101E5
	bool ParagraphIsRight();
	//##ModelId=474D308101F5
	bool ParagraphIsLeft();
	//##ModelId=474D30810204
	bool ParagraphIsCentered();
	
	//##ModelId=474D30810224
	void SetParagraphRight();
	//##ModelId=474D30810243
	void SetParagraphLeft();
	//##ModelId=474D30810262
	void SetParagraphCenter();
	
	//##ModelId=474D30810281
	CHARFORMAT GetCharFormat(DWORD dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE);
	
	//##ModelId=474D308102B0
	bool SelectionIsBold();
	//##ModelId=474D308102EF
	bool SelectionIsItalic();
	//##ModelId=474D3081031E
	bool SelectionIsUnderlined();

	//##ModelId=474D3081033D
	void SetSelectionBold();
	//##ModelId=474D3081036C
	void SetSelectionItalic();
	//##ModelId=474D3081038B
	void SetSelectionUnderlined();

	//##ModelId=474D308103AA
	void SetRTF(CStringA sRTF);
	//##ModelId=474D30820020
	void SetRTF(const char *pRTF);
	//##ModelId=474D30820040
	CString GetRTF();

	//##ModelId=474D308200BC
	void SetText(CString sText);
	//##ModelId=474D308200DB
	CString GetText();

	//##ModelId=474D308200EB
	virtual ~CRichEditCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRichEditCtrlEx)
	//##ModelId=474D3082010A
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	//##ModelId=474D3082012B
		void SetCharStyle(int MASK, int STYLE, int nStart, int nEnd);
	//##ModelId=474D308201A7
		static DWORD CALLBACK CBStreamIn(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	//##ModelId=474D308201F6
		static DWORD CALLBACK CBStreamOut(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb);
	//##ModelId=474D30820244
		static BOOL CALLBACK CBEnumFonts(LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTORICHEDITCTRL_H__C26D1E0E_DD32_11D2_B39F_000092914562__INCLUDED_)
