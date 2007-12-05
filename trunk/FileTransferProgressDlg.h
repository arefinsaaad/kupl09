#if !defined(AFX_FILETRANSFERPROGRESSDLG_H__B7CD7263_7AA2_44C1_BF85_31021FB23D85__INCLUDED_)
#define AFX_FILETRANSFERPROGRESSDLG_H__B7CD7263_7AA2_44C1_BF85_31021FB23D85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileTransferProgressDlg.h : header file
//
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CFileTransferProgressDlg dialog

//##ModelId=474D306602A1
class CFileTransferProgressDlg : public CDialog
{
// Construction
public:
	//##ModelId=474D306602CF
	CFileTransferProgressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileTransferProgressDlg)
	enum { IDD = IDD_DIALOG_REMOTE_FILE };
	//##ModelId=474D3066032E
	CAnimateCtrl	m_FileCopy;
	//##ModelId=474D3066034D
	CButton	m_m_CancelButton;
	//##ModelId=474D3066037C
	CProgressCtrl	m_ProgressSingleFile;
	//##ModelId=474D30670021
	CProgressCtrl	m_ProgressAllFiles;
	//##ModelId=474D3067005F
	CStatic	m_Message;
	//##ModelId=474D306700FC
	CStatic	m_CopyingFile;
	//}}AFX_DATA

	//##ModelId=474D30670149
	void SetMessage(CString &cs);
	//##ModelId=474D30670168
	void SetFileMessage(CString &cs);

	//##ModelId=474D30670197
	void SetNumFiles(int nFiles);
	//##ModelId=474D306701E5
	void StepAllFiles();
	//##ModelId=474D306701F5
	void SetSingleFilePos(int nPos);
	//##ModelId=474D30670224
	void ResetSingleFileProgress();

	//##ModelId=474D30670233
	bool Cancelled()	{ return m_bCancelled; }

	//##ModelId=474D30670262
	void PumpMessages();




// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransferProgressDlg)
	protected:
	//##ModelId=474D30670263
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//##ModelId=474D3067037B
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=474D3067038B
	bool m_bCancelled;

	// Generated message map functions
	//{{AFX_MSG(CFileTransferProgressDlg)
	//##ModelId=474D306703BA
	virtual BOOL OnInitDialog();
	//##ModelId=474D30680001
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSFERPROGRESSDLG_H__B7CD7263_7AA2_44C1_BF85_31021FB23D85__INCLUDED_)
