#if !defined(AFX_OPTIONSTYPES_H__3E35B866_595F_41CA_8654_E4F8E39B1D81__INCLUDED_)
#define AFX_OPTIONSTYPES_H__3E35B866_595F_41CA_8654_E4F8E39B1D81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsTypes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsTypes dialog

//##ModelId=474D303D00CC
class COptionsTypes : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsTypes)

// Construction
public:
	//##ModelId=474D303D00EB
	COptionsTypes();
	//##ModelId=474D303D00EC
	~COptionsTypes();

// Dialog Data
	//{{AFX_DATA(COptionsTypes)
	enum { IDD = IDD_OPTIONS_TYPES };
	//##ModelId=474D303D00FC
	CListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsTypes)
	public:
	//##ModelId=474D303D010A
	virtual BOOL OnApply();
	protected:
	//##ModelId=474D303D010C
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=474D303D011B
	bool m_bSave;
	//##ModelId=474D303D012A
	CString m_csTitle;
	//##ModelId=474D303D0139
	BOOL TextAllReadyThere(const CString &cs);


	// Generated message map functions
	//{{AFX_MSG(COptionsTypes)
	//##ModelId=474D303D0158
	virtual BOOL OnInitDialog();
	//##ModelId=474D303D0168
	afx_msg void OnDelete();
	//##ModelId=474D303D0187
	afx_msg void OnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSTYPES_H__3E35B866_595F_41CA_8654_E4F8E39B1D81__INCLUDED_)
