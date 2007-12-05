#if !defined(AFX_GROUPTREE_H__A1F01358_5440_45A8_B402_3F32F46FCAA5__INCLUDED_)
#define AFX_GROUPTREE_H__A1F01358_5440_45A8_B402_3F32F46FCAA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupTree window

//##ModelId=474D30640281
class CGroupTree : public CTreeCtrl
{
// Construction
public:
	//##ModelId=474D306402C0
	CGroupTree();

// Attributes
public:

// Operations
public:
	//##ModelId=474D306402C1
	void FillTree();
	//##ModelId=474D306402CF
	void SetNotificationWndEx(HWND hWnd)	{ m_NotificationWnd = hWnd;	}
	//##ModelId=474D306402FE
	bool m_bHide;
	//##ModelId=474D3064030E
	long m_lSelectedFolderID;
	//##ModelId=474D3064031E
	long GetSelectedTree();
	//##ModelId=474D3064031F
	bool AddNode(CString csText, long lID);

protected:
	//##ModelId=474D3064033D
	void FillTree(long lParentID, HTREEITEM hParent);
	//##ModelId=474D3064034D
	void SendToParent(long lID);

	//##ModelId=474D3064037B
	HWND m_NotificationWnd;
	//##ModelId=474D3064039C
	CBitmap m_bmOpenFolder;
	//##ModelId=474D30650021
	CBitmap m_bmClosedFolder;
	//##ModelId=474D3065006E
	bool m_bSendAllready;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupTree)
	public:
	//##ModelId=474D3065008D
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D3065011A
	virtual ~CGroupTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGroupTree)
	//##ModelId=474D3065012A
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D30650168
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D306501F5
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//##ModelId=474D30650262
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//##ModelId=474D306502EF
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D3065033E
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGroupTree)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPTREE_H__A1F01358_5440_45A8_B402_3F32F46FCAA5__INCLUDED_)
