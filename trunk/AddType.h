#if !defined(AFX_ADDTYPE_H__783BC68A_076E_41CD_8F88_D8169D90BA55__INCLUDED_)
#define AFX_ADDTYPE_H__783BC68A_076E_41CD_8F88_D8169D90BA55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddType dialog

//##ModelId=474D307A009D
class CAddType : public CDialog
{
// Construction
public:
	//##ModelId=474D307A00EC
	CAddType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddType)
	enum { IDD = IDD_ADD_TYPE };
	//##ModelId=474D307A00FC
	CListBox	m_lbOnClipboard;
	//##ModelId=474D307A013A
	CListBox	m_lbDefaultTypes;
	//##ModelId=474D307A01A7
	CString	m_eCustomType;
	//}}AFX_DATA

	//##ModelId=474D307A01F6
	CStringArray m_csSelectedTypes;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddType)
	protected:
	//##ModelId=474D307A0224
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddType)
	//##ModelId=474D307A0281
	afx_msg void OnAdd1();
	//##ModelId=474D307A02A2
	afx_msg void OnAdd2();
	//##ModelId=474D307A02EF
	afx_msg void OnAdd3();
	//##ModelId=474D307A030E
	virtual BOOL OnInitDialog();
	//##ModelId=474D307A034C
	afx_msg void OnDblclkList1();
	//##ModelId=474D307A039B
	afx_msg void OnDblclkList2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDTYPE_H__783BC68A_076E_41CD_8F88_D8169D90BA55__INCLUDED_)
