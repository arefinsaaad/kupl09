// CopyProperties.cpp : implementation file
//

#include "stdafx.h"
#include "cp_main.h"
#include "CopyProperties.h"
#include ".\copyproperties.h"
#include "shellapi.h"
#include "WebBrowser2.h"
#include "Path.h"
#include "pdflib.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyProperties dialog


CCopyProperties::CCopyProperties(long lCopyID, CWnd* pParent, CClip *pMemoryClip)
	: CDialog(CCopyProperties::IDD, pParent)
{
	m_lCopyID = lCopyID;
	m_bDeletedData = false;
	m_bChangedText = false;
	m_bHandleKillFocus = false;
	m_bHideOnKillFocus = false;
	m_bInGroup = false;
	m_lGroupChangedTo = -1;
	m_pMemoryClip = pMemoryClip;
	m_bSetToTopMost = true;

	//{{AFX_DATA_INIT(CCopyProperties)
	m_eDate = _T("");
	m_bNeverAutoDelete = FALSE;
	//}}AFX_DATA_INIT
}


void CCopyProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyProperties)
	DDX_Control(pDX, IDC_EDIT_QUICK_PASTE, m_QuickPasteText);
	DDX_Control(pDX, IDC_RICHEDIT1, m_RichEdit);
	DDX_Control(pDX, IDC_COMBO1, m_GroupCombo);
	DDX_Control(pDX, IDC_HOTKEY, m_HotKey);
	DDX_Control(pDX, IDC_COPY_DATA, m_lCopyData);
	DDX_Text(pDX, IDC_DATE, m_eDate);
	DDX_Check(pDX, IDC_NEVER_AUTO_DELETE, m_bNeverAutoDelete);

	DDX_Control(pDX, IDC_EDIT_WEBPAGE, m_WebPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCopyProperties, CDialog)
	//{{AFX_MSG_MAP(CCopyProperties)
	ON_BN_CLICKED(IDC_DELETE_COPY_DATA, OnDeleteCopyData)
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_GO_WEBADDR, OnBnClickedBtnGoWebaddr)		// modified by kyo
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SAVEAS_TXT, OnBnClickedBtnSaveasTxt)
	ON_BN_CLICKED(IDC_BTN_SAVEAS_PDF, OnBnClickedBtnSaveasPdf)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyProperties message handlers

BOOL CCopyProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_GroupCombo.FillCombo();

	try
	{
		if(m_lCopyID == -1 && m_pMemoryClip != NULL)
		{
			LoadDataFromCClip(*m_pMemoryClip);
		}
		else
		{
			CClip Clip;
			if(Clip.LoadMainTable(m_lCopyID))
			{
				Clip.LoadFormats(m_lCopyID);
				LoadDataFromCClip(Clip);			
			}
		}
	}
	CATCH_SQLITE_EXCEPTION

	UpdateData(FALSE);

	if(m_bSetToTopMost)
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	if(m_lCopyID == -1 && m_pMemoryClip != NULL)
	{
		GetDlgItem(IDOK)->SetFocus();
	}
	else
	{
		m_RichEdit.SetFocus();
	}

	m_Resize.SetParent(m_hWnd);
	m_Resize.AddControl(IDC_RICHEDIT1, DR_SizeHeight | DR_SizeWidth);
	m_Resize.AddControl(IDC_STATIC_FORMATS, DR_MoveTop);
	m_Resize.AddControl(IDC_COPY_DATA, DR_MoveTop | DR_SizeWidth);
	m_Resize.AddControl(IDC_DELETE_COPY_DATA, DR_MoveTop);
	m_Resize.AddControl(IDOK, DR_MoveTop | DR_MoveLeft);
	m_Resize.AddControl(IDCANCEL, DR_MoveTop | DR_MoveLeft);

	theApp.m_Language.UpdateClipProperties(this);

	return FALSE;
}

void CCopyProperties::LoadDataFromCClip(CClip &Clip)
{
	COleDateTime dtTime(Clip.m_Time.GetTime());
	m_eDate = dtTime.Format();
	m_RichEdit.SetText(Clip.m_Desc);
	m_WebPage.SetWindowText(Clip.m_WebAddr);		// modified by kyo

//	MessageBox((LPCTSTR)Clip.m_WebAddr);			// for Test

	if(Clip.m_lDontAutoDelete)
	{
		m_bNeverAutoDelete = TRUE;
	}
	else
	{
		m_bNeverAutoDelete = FALSE;
	}

	m_GroupCombo.SetCurSelOnItemData(Clip.m_lParent);

	if(Clip.m_lParent >= 0)
		m_bInGroup = true;

	m_HotKey.SetHotKey(LOBYTE(Clip.m_lShortCut), HIBYTE(Clip.m_lShortCut));
	m_HotKey.SetRules(HKCOMB_A, 0);

	m_QuickPasteText.SetWindowText(Clip.m_csQuickPaste);

	CString cs;
	CClipFormat* pCF;
	int nCount = Clip.m_Formats.GetSize();
	for(int i = 0; i < nCount; i++)
	{
		pCF = &Clip.m_Formats.GetData()[i];
		if(pCF)
		{
			cs.Format(_T("%s, %d"), GetFormatName(pCF->m_cfType), GlobalSize(pCF->m_hgData));
			int nIndex = m_lCopyData.AddString(cs);
			
			if(m_lCopyID == -1 && pCF->m_lDBID == -1)
				m_lCopyData.SetItemData(nIndex, i);
			else
				m_lCopyData.SetItemData(nIndex, pCF->m_lDBID);
		}
	}
}

void CCopyProperties::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	if (nState == WA_INACTIVE)
	{
		if(m_bHideOnKillFocus)
		{
			if(!m_bHandleKillFocus)
			{
				EndDialog(-1);
				m_bHandleKillFocus = false;
			}
		}
	}
	else if (nState == WA_ACTIVE)
	{
		SetFocus();
		::SetForegroundWindow(m_hWnd);
	}

}
void CCopyProperties::OnOK() 
{
	UpdateData();

	try
	{
		if(m_lCopyID == -1 && m_pMemoryClip != NULL)
		{
			LoadDataIntoCClip(*m_pMemoryClip);

			m_DeletedData.SortDescending();
			int nCount = m_DeletedData.GetSize();
			for(int i = 0; i < nCount; i++)
			{
				m_pMemoryClip->m_Formats.RemoveAt(m_DeletedData[i], 1);
			}
		}
		else
		{
			CClip Clip;
			if(Clip.LoadMainTable(m_lCopyID))
			{
				LoadDataIntoCClip(Clip);

				Clip.ModifyMainTable();
			
				if(m_bDeletedData)
				{
					DeleteFormats(m_lCopyID, m_DeletedData);
				}
			}
		}

		m_bHandleKillFocus = true;
	}
	CATCH_SQLITE_EXCEPTION

	CDialog::OnOK();
}

void CCopyProperties::LoadDataIntoCClip(CClip &Clip)
{
	Clip.m_lShortCut = m_HotKey.GetHotKey();

	//remove any others that have the same hot key
	if(Clip.m_lShortCut > 0)
	{
		theApp.m_db.execDMLEx(_T("UPDATE Main SET lShortCut = 0 where lShortCut = %d AND lID <> %d;"), Clip.m_lShortCut, m_lCopyID);
	}

	Clip.m_Desc = m_RichEdit.GetText();
	Clip.m_Desc.Replace(_T("'"), _T("''"));

	m_QuickPasteText.GetWindowText(Clip.m_csQuickPaste);
	Clip.m_csQuickPaste.MakeUpper();
	Clip.m_csQuickPaste.Replace(_T("'"), _T("''"));

	//remove any other that have the same quick paste text
	if(Clip.m_csQuickPaste.IsEmpty() == FALSE)
	{
		theApp.m_db.execDMLEx(_T("UPDATE Main SET QuickPasteText = '' WHERE QuickPasteText = '%s' AND lID <> %d;"), Clip.m_csQuickPaste, m_lCopyID);
	}

	Clip.m_lParent = m_GroupCombo.GetItemDataFromCursel();

	//If we are going from no group to a group or the
	//don't auto delete check box is checked
	if(m_bInGroup == false && Clip.m_lParent >= 0 || m_bNeverAutoDelete)
	{
		Clip.m_lDontAutoDelete = (long)CTime::GetCurrentTime().GetTime();
	}
	else if(m_bNeverAutoDelete == FALSE)
	{
		Clip.m_lDontAutoDelete = FALSE;
	}
}

void CCopyProperties::OnDeleteCopyData() 
{
	int nCount = m_lCopyData.GetSelCount();
	if(nCount)
	{
		m_bDeletedData = true;

		//Get the selected indexes
		ARRAY items;
		items.SetSize(nCount);
		m_lCopyData.GetSelItems(nCount, items.GetData()); 

		items.SortDescending();

		//Get the selected itemdata
		for(int i = 0; i < nCount; i++)
		{
			m_DeletedData.Add(m_lCopyData.GetItemData(items[i]));
			m_lCopyData.DeleteString(items[i]);
		}		
	}
}

void CCopyProperties::OnCancel() 
{
	m_bHandleKillFocus = true;
		
	CDialog::OnCancel();
}

void CCopyProperties::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	

	m_Resize.MoveControls(CSize(cx, cy));
}

void CCopyProperties::OnBnClickedBtnGoWebaddr()
{
	// TODO: 해당 웹사이트로 이동한다.
	char strAddr[256];						// 스트링 길이 조절에 조금 문제 있음

	int nLength = m_WebPage.GetWindowTextLength() + 1;

	if( nLength <= 0 )
	{
		AfxMessageBox("이동할 URL이 없습니다.");
	}
	else
	{
		m_WebPage.GetWindowText(strAddr,nLength);
		OpenNewWindow(strAddr);
//		ShellExecute( NULL, "open", strAddr, NULL, NULL, SW_SHOWNORMAL); 
	}
}

// 해당 URL을 이용해 웹 브라우저를 연다.
bool CCopyProperties::OpenNewWindow(LPCTSTR pAddress)
{
	IWebBrowser2 *pWebBrowser;
	HRESULT hr;

	// 웹브라우저 객체를 생성한다.
	hr = ::CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (void**)&pWebBrowser);
	if(FAILED(hr) || pWebBrowser == NULL)	return FALSE;

	CString strAddress = pAddress;

	// Navigate()에 필요한 인자들을 초기화한다
	VARIANT vtFlags, vtTarget, vtPostData, vtHeader;
	::VariantInit(&vtFlags);
	::VariantInit(&vtTarget);
	::VariantInit(&vtPostData);
	::VariantInit(&vtHeader);

	// 웹브라우저를 화면에 보이게 한다
	pWebBrowser->put_Visible(VARIANT_TRUE);
	// 사이트를 연다
	hr = pWebBrowser->Navigate(strAddress.AllocSysString(), &vtFlags, &vtTarget, &vtPostData, &vtHeader);

	// 웹브라우저 인터페이스의 참조 횟수를 줄인다
	pWebBrowser->Release();

	return SUCCEEDED(hr);
}

void CCopyProperties::OnBnClickedBtnSaveasTxt()
{

/*	CStdioFile file; // 파일 열기

	CString test = "test";

	file.Open("C:\test.txt", CFile::modeWrite | CFile::modeCreate | CFile::typeText);
	file.WriteString(test + "\r\n"); // 파일에 쓰기/**/
	
	CString strTitle = m_RichEdit.GetText();
	int nLength = strTitle.GetLength();

	OPENFILENAME ofn;      
	TCHAR szFile[400];      

	memset(&szFile, 0, sizeof(szFile));
	memset(&ofn, 0, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter=_T("PDF File (.pdf)\0*.pdf\0\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrDefExt = _T("pdf");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

	if(GetSaveFileName(&ofn)) 
	{
		using namespace nsPath;
		CPath path(ofn.lpstrFile);
		CString csPath = path.GetPath();

		CFile TextFile;

		TextFile.Open(csPath, CFile::modeCreate || CFile::modeWrite); // 파일 만들기
		TextFile.Write("test", 4);
		TextFile.Close(); // 파일 닫기

//		CStdioFile file; // 파일 열기

//		CString test = "test";

//		file.Open("C:\test.txt", CFile::modeWrite | CFile::modeCreate | CFile::typeText);
//		file.WriteString(test + "\r\n"); // 파일에 쓰기

	}/**/
}

void CCopyProperties::OnBnClickedBtnSaveasPdf()
{
	CString strTitle = m_RichEdit.GetText();
	int nLength = strTitle.GetLength();

	OPENFILENAME ofn;      
	TCHAR szFile[400];      

	memset(&szFile, 0, sizeof(szFile));
	memset(&ofn, 0, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter=_T("PDF File (.pdf)\0*.pdf\0\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrDefExt = _T("pdf");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

	if(GetSaveFileName(&ofn)) 
	{
		PDFlib pdf;
		pdf.set_parameter("compatibility", "1.4");	//Compatible for Acrobat 5

		CString	strFileName(ofn.lpstrFile);

		pdf.open(ofn.lpstrFile);

		float width = 595.0;
		float height = 842.0;

		pdf.begin_page(width, height);

		float PageHeight=0.0, PageWidth=0.0;

		//Font will be embedded in PDF
		int font=pdf.findfont("Arial", "winansi", 1);	
		int fontSize = 10;
		pdf.setfont(font, fontSize);		
		
		pdf.set_text_pos(20, 822);

		CString Line, Text;
		Text=strTitle;
		Text.Replace("\r\n","\r");

		float descender=pdf.get_value("descender", font);
		float LineHeight=(1-descender)*fontSize;

		int iWordIndex=0;
		int iProgress=0;
		
		while (!Text.IsEmpty())
		{
			while (PageWidth <= width)
			{
				iWordIndex=Text.Find(' ', iWordIndex);
				
				if (iWordIndex!=-1)
					Line=Text.Left(iWordIndex++);
				else
				{
					Line=Text;
					break;
				}
				
				PageWidth=pdf.stringwidth(Line.GetBuffer(0),
					font, fontSize);
			}

			iWordIndex=Line.Find('\r');
			if (iWordIndex!=-1)		//enter found (carriage return)
			{
				Line=Line.Left(iWordIndex);
				Text=Text.Right(Text.GetLength() - Line.GetLength() - 1);
			}
			else
			{
				iWordIndex=Line.ReverseFind(' ');
				if (iWordIndex!=-1)		//space found
				{
					if (pdf.stringwidth(Line.GetBuffer(0),
								font, fontSize)>width)
					{
						Line=Line.Left(iWordIndex);	//with space character
						Text=Text.Right(Text.GetLength() - iWordIndex);
					}
					else
					{
						Line=Text;
						Text="";
					}
				}
				else
				{
					Text=Text.Right(Text.GetLength() - Line.GetLength());
				}
			}

			iWordIndex=0;
			iProgress+=Line.GetLength();

			pdf.continue_text(Line.GetBuffer(0));
							
			PageWidth=0;
			PageHeight=pdf.get_value("texty",0.0);

			if (PageHeight < 10.0 )
			{
				pdf.end_page();
				pdf.begin_page(width, height);
				pdf.setfont(font, fontSize);
				pdf.set_text_pos(20, 822);			
			}

			Line="";
		}

		pdf.end_page();

//		USES_CONVERSION;
//		LPCSTR sstr= W2CA((LPCWSTR)strTitle);
//		LPCSTR sstr = (LPCSTR)strTitle;
//		pdf.continue_text(sstr);
//		pdf.end_page();
		pdf.close();/**/
	}
}
