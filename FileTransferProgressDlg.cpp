// FileTransferProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cp_main.h"
#include "FileTransferProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTransferProgressDlg dialog


//##ModelId=474D306602CF
CFileTransferProgressDlg::CFileTransferProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileTransferProgressDlg::IDD, pParent)
{
	m_bCancelled = false;
}

//##ModelId=474D30670263
void CFileTransferProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileTransferProgressDlg)
	DDX_Control(pDX, IDC_FILE_COPY, m_FileCopy);
	DDX_Control(pDX, IDCANCEL, m_m_CancelButton);
	DDX_Control(pDX, IDC_PROGRESS_FILE, m_ProgressSingleFile);
	DDX_Control(pDX, IDC_PROGRESS_ALL_FILES, m_ProgressAllFiles);
	DDX_Control(pDX, IDC_STATIC_1, m_Message);
	DDX_Control(pDX, IDC_STATIC_2, m_CopyingFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileTransferProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CFileTransferProgressDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTransferProgressDlg message handlers

//##ModelId=474D3067037B
void CFileTransferProgressDlg::PostNcDestroy() 
{
	CDialog::PostNcDestroy();

	delete this;
}

//##ModelId=474D306703BA
BOOL CFileTransferProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_FileCopy.Open(IDR_FILE_COPY);
	m_FileCopy.Play(0, -1, -1);
	
	SetNumFiles(0);

	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);

	return TRUE;
}

//##ModelId=474D30680001
void CFileTransferProgressDlg::OnCancel() 
{
	m_bCancelled = true;
}

//##ModelId=474D30670149
void CFileTransferProgressDlg::SetMessage(CString &cs)
{
	m_Message.SetWindowText(cs);
}

//##ModelId=474D30670168
void CFileTransferProgressDlg::SetFileMessage(CString &cs)
{
	m_CopyingFile.SetWindowText(cs);
}

//##ModelId=474D30670197
void CFileTransferProgressDlg::SetNumFiles(int nFiles)
{
	m_ProgressAllFiles.SetRange32(0, nFiles);
	m_ProgressAllFiles.SetStep(1);
	m_ProgressAllFiles.SetPos(0);

	m_ProgressSingleFile.SetRange32(0, 100);
	m_ProgressSingleFile.SetStep(1);
	m_ProgressSingleFile.SetPos(0);
}

//##ModelId=474D30670224
void CFileTransferProgressDlg::ResetSingleFileProgress()
{
	m_ProgressSingleFile.SetPos(0);
}

//##ModelId=474D306701E5
void CFileTransferProgressDlg::StepAllFiles()
{
	m_ProgressAllFiles.StepIt();
}

//##ModelId=474D306701F5
void CFileTransferProgressDlg::SetSingleFilePos(int nPos)
{
	m_ProgressSingleFile.SetPos(nPos);
}

//##ModelId=474D30670262
void CFileTransferProgressDlg::PumpMessages()
{
	int nLoops = 0;
	MSG msg;
    while(::PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE)) 
    {
        TranslateMessage(&msg);
		DispatchMessage(&msg);

		nLoops++;
		if(nLoops > 100)
			break;
    }
}
