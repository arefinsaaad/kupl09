#if !defined(AFX_OPTIONFRIENDS_H__E44847C3_54CA_4053_9647_349405B64DF9__INCLUDED_)
#define AFX_OPTIONFRIENDS_H__E44847C3_54CA_4053_9647_349405B64DF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionFriends.h : header file
//
#include "OptionsSheet.h"

/////////////////////////////////////////////////////////////////////////////
// COptionFriends dialog

//##ModelId=474D30570139
class COptionFriends : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionFriends)

// Construction
public:
	//##ModelId=474D30570168
	COptionFriends();
	//##ModelId=474D30570187
	~COptionFriends();

// Dialog Data
	//{{AFX_DATA(COptionFriends)
	enum { IDD = IDD_OPTIONS_FRIENDS };
	//##ModelId=474D305701B7
	CButton	m_bDisableRecieve;
	//##ModelId=474D30570225
	CButton	m_SendRecieve;
	//##ModelId=474D30570281
	CListCtrl	m_List;
	//##ModelId=474D305702A1
	CString	m_PlaceOnClipboard;
	//##ModelId=474D3057031E
	CString	m_csPassword;
	//##ModelId=474D3057034C
	CString	m_csAdditionalPasswords;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionFriends)
	public:
	//##ModelId=474D3057036C
	virtual BOOL OnApply();
	protected:
	//##ModelId=474D3057038C
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=474D30580001
	void InitListCtrlCols();
	//##ModelId=474D30580030
	void InsertItems();
	//##ModelId=474D3058005E
	BOOL EditItem(int nItem);

	//##ModelId=474D305800AD
	CString m_csTitle;
	//##ModelId=474D305800FC
	COptionsSheet *m_pParent;
	
	// Generated message map functions
	//{{AFX_MSG(COptionFriends)
	//##ModelId=474D30580139
	virtual BOOL OnInitDialog();
	//##ModelId=474D30580149
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D305801B6
	afx_msg void OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=474D30580224
	afx_msg void OnCheckDisableFriends();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONFRIENDS_H__E44847C3_54CA_4053_9647_349405B64DF9__INCLUDED_)
