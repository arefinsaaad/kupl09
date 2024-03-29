// GroupName.cpp : implementation file
//

#include "stdafx.h"
#include "cp_main.h"
#include "GroupName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupName dialog


//##ModelId=474D306503D9
CGroupName::CGroupName(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupName)
	m_csName = _T("");
	//}}AFX_DATA_INIT
}


//##ModelId=474D3066003F
void CGroupName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupName)
	DDX_Text(pDX, IDC_NAME, m_csName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupName, CDialog)
	//{{AFX_MSG_MAP(CGroupName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupName message handlers

//##ModelId=474D3066006F
void CGroupName::OnOK() 
{
	UpdateData(TRUE);
	
	CDialog::OnOK();
}

//##ModelId=474D3066007F
BOOL CGroupName::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CWnd *pWnd = GetDlgItem(IDC_NAME);
	if(pWnd)
		pWnd->SetFocus();
		
	return FALSE;
}
