#if !defined(AFX_MOVETOGROUPDLG_H__0F42AFA2_0097_489B_B014_3815E7327940__INCLUDED_)
#define AFX_MOVETOGROUPDLG_H__0F42AFA2_0097_489B_B014_3815E7327940__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoveToGroupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoveToGroupDlg dialog

//##ModelId=474D305B0158
class CMoveToGroupDlg : public CDialog
{
// Construction
public:
	//##ModelId=474D305B0169
	CMoveToGroupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMoveToGroupDlg)
	enum { IDD = IDD_MOVE_TO_GROUP };
	//##ModelId=474D305B01A8
	CGroupTree	m_Tree;
	//}}AFX_DATA

	//##ModelId=474D305B01B6
	int GetSelectedGroup()				{ return m_nSelectedGroup; }
	//##ModelId=474D305B01B7
	void SetSlectedGroup(int nGroup)	{ m_nSelectedGroup = nGroup; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoveToGroupDlg)
	protected:
	//##ModelId=474D305B01C7
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	//##ModelId=474D305B01D6
	int m_nSelectedGroup;

	// Generated message map functions
	//{{AFX_MSG(CMoveToGroupDlg)
	//##ModelId=474D305B0214
	virtual BOOL OnInitDialog();
	//##ModelId=474D305B0224
	virtual void OnOK();
	//##ModelId=474D305B0233
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=474D305B0252
	afx_msg void OnButtonNewGroup();
	//}}AFX_MSG
	//##ModelId=474D305B0262
	LRESULT OnTreeSelect(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVETOGROUPDLG_H__0F42AFA2_0097_489B_B014_3815E7327940__INCLUDED_)
