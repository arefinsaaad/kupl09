#if !defined(AFX_ABOUT_H__02A95202_4AEF_4854_9DC0_161326D7B914__INCLUDED_)
#define AFX_ABOUT_H__02A95202_4AEF_4854_9DC0_161326D7B914__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// About.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog

#include "hyperlink.h"

//##ModelId=474D307B012A
class CAbout : public CPropertyPage
{
	DECLARE_DYNCREATE(CAbout)

// Construction
public:
	//##ModelId=474D307B0158
	CAbout();
	//##ModelId=474D307B0159
	~CAbout();

// Dialog Data
	//{{AFX_DATA(CAbout)
	enum { IDD = IDD_ABOUT };
	//##ModelId=474D307B01A8
	CHyperLink	m_Link;
	//##ModelId=474D307B01B7
	CHyperLink	m_HyperLink;
	//##ModelId=474D307B01D6
	CListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAbout)
	protected:
	//##ModelId=474D307B0214
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	//##ModelId=474D307B0233
	CString m_csTitle;

	// Generated message map functions
	//{{AFX_MSG(CAbout)
	//##ModelId=474D307B02A1
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUT_H__02A95202_4AEF_4854_9DC0_161326D7B914__INCLUDED_)
