#if !defined(AFX_GROUPNAME_H__C0A39EC3_DC62_43FF_A9BF_9AC3E356C498__INCLUDED_)
#define AFX_GROUPNAME_H__C0A39EC3_DC62_43FF_A9BF_9AC3E356C498__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupName dialog

//##ModelId=474D306503BA
class CGroupName : public CDialog
{
// Construction
public:
	//##ModelId=474D306503D9
	CGroupName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGroupName)
	enum { IDD = IDD_GROUP_NAME };
	//##ModelId=474D30660001
	CString	m_csName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupName)
	protected:
	//##ModelId=474D3066003F
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupName)
	//##ModelId=474D3066006F
	virtual void OnOK();
	//##ModelId=474D3066007F
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPNAME_H__C0A39EC3_DC62_43FF_A9BF_9AC3E356C498__INCLUDED_)
