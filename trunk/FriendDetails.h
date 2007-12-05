#if !defined(AFX_FRIENDDETAILS_H__EE25569D_E112_4F70_BDB3_6AD778477A73__INCLUDED_)
#define AFX_FRIENDDETAILS_H__EE25569D_E112_4F70_BDB3_6AD778477A73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FriendDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFriendDetails dialog

//##ModelId=474D3066011A
class CFriendDetails : public CDialog
{
// Construction
public:
	//##ModelId=474D30660149
	CFriendDetails(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFriendDetails)
	enum { IDD = IDD_FRIEND_DETAILS };
	//##ModelId=474D3066014B
	BOOL	m_checkSendAll;
	//##ModelId=474D30660158
	CString	m_csDescription;
	//##ModelId=474D30660168
	CString	m_csIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFriendDetails)
	protected:
	//##ModelId=474D30660169
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFriendDetails)
	//##ModelId=474D30660187
	virtual BOOL OnInitDialog();
	//##ModelId=474D30660197
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRIENDDETAILS_H__EE25569D_E112_4F70_BDB3_6AD778477A73__INCLUDED_)
