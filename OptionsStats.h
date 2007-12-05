#if !defined(AFX_OPTIONSSTATS_H__5F6FFD2C_E563_4166_8294_A0CBBD17403B__INCLUDED_)
#define AFX_OPTIONSSTATS_H__5F6FFD2C_E563_4166_8294_A0CBBD17403B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsStats.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsStats dialog

//##ModelId=474D303D01B6
class COptionsStats : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsStats)

// Construction
public:
	//##ModelId=474D303D01C7
	COptionsStats();   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsStats)
	enum { IDD = IDD_OPTIONS_STATS };
	//##ModelId=474D303D01D5
	CString	m_eAllCopies;
	//##ModelId=474D303D01D6
	CString	m_eAllPastes;
	//##ModelId=474D303D01E5
	CString	m_eAllDate;
	//##ModelId=474D303D01E6
	CString	m_eTripCopies;
	//##ModelId=474D303D01F5
	CString	m_eTripDate;
	//##ModelId=474D303D01F6
	CString	m_eTripPastes;
	//##ModelId=474D303D0204
	CString	m_eSavedCopies;
	//##ModelId=474D303D0214
	CString	m_eSavedCopyData;
	//##ModelId=474D303D0215
	CString	m_eDatabaseSize;
	//##ModelId=474D303D0224
	CString	m_eClipsSent;
	//##ModelId=474D303D0225
	CString	m_eClipsRecieved;
	//##ModelId=474D303D0233
	CString	m_eLastStarted;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsStats)
	protected:
	//##ModelId=474D303D0243
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	//##ModelId=474D303D0252
	CString m_csTitle;

	// Generated message map functions
	//{{AFX_MSG(COptionsStats)
	//##ModelId=474D303D0262
	virtual BOOL OnInitDialog();
	//##ModelId=474D303D0264
	afx_msg void OnResetCounts();
	//##ModelId=474D303D0273
	afx_msg void OnRemoveAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSSTATS_H__5F6FFD2C_E563_4166_8294_A0CBBD17403B__INCLUDED_)
