// GroupTree.cpp : implementation file
//

#include "stdafx.h"
#include "cp_main.h"
#include "GroupTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupTree

//##ModelId=474D306402C0
CGroupTree::CGroupTree()
{
	m_bHide = true;
	m_lSelectedFolderID = -1;
	m_bSendAllready = false;
}

//##ModelId=474D3065011A
CGroupTree::~CGroupTree()
{
}


BEGIN_MESSAGE_MAP(CGroupTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CGroupTree)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_KILLFOCUS()
	ON_WM_ACTIVATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGroupTree message handlers

//##ModelId=474D3065008D
BOOL CGroupTree::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

//##ModelId=474D3065012A
int CGroupTree::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CImageList iml;
	iml.Create(18, 16, ILC_COLOR8, 0, 1);

	m_bmClosedFolder.LoadBitmap(IDB_CLOSED_FOLDER);
	iml.Add(&m_bmClosedFolder, RGB(255, 0, 0));

	m_bmOpenFolder.LoadBitmap(IDB_OPEN_FOLDER);
	iml.Add(&m_bmOpenFolder, RGB(255, 0, 0));
	

	SetImageList(&iml, TVSIL_NORMAL);
	iml.Detach();
		
	return 0;
}

//##ModelId=474D306402C1
void CGroupTree::FillTree()
{	
	DeleteAllItems();
	m_bSendAllready = false;

	HTREEITEM hItem = InsertItem(_T("Root"), TVI_ROOT);
	SetItemData(hItem, -1);
	SetItemState(hItem, TVIS_EXPANDED, TVIS_EXPANDED);

	if(m_lSelectedFolderID < 0)
		SelectItem(hItem);
	
	FillTree(-1, hItem);
}


//##ModelId=474D3064033D
void CGroupTree::FillTree(long lParentID, HTREEITEM hParent)
{	
	try
	{
		CppSQLite3Query q = theApp.m_db.execQueryEx(_T("SELECT lID, mText FROM Main WHERE bIsGroup = 1 AND lParentID = %d"), lParentID);
			
		if(q.eof() == false)
		{
			HTREEITEM hItem;

			while(!q.eof())
			{
				if(q.getIntField(_T("lID")) == m_lSelectedFolderID)
				{
					hItem = InsertItem(q.getStringField(_T("mText")), 1, 1, hParent);
					SelectItem(hItem);
				}
				else
				{				
					hItem = InsertItem(q.getStringField(_T("mText")), 0, 0, hParent);
				}

				SetItemData(hItem, q.getIntField(_T("lID")));
				
				FillTree(q.getIntField(_T("lID")), hItem);

				q.nextRow();
			}
		}
	}		
	CATCH_SQLITE_EXCEPTION	
}

//##ModelId=474D30650168
void CGroupTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
//	if(m_bHide == true)
//	{	
//		::SendMessage(m_NotificationWnd, NM_GROUP_TREE_MESSAGE, GetItemData(pNMTreeView->itemNew.hItem), 0);
//	}
	
	*pResult = 0;
}

//##ModelId=474D306501F5
void CGroupTree::OnKillFocus(CWnd* pNewWnd) 
{
	CTreeCtrl::OnKillFocus(pNewWnd);
}

//##ModelId=474D30650262
void CGroupTree::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CTreeCtrl::OnActivate(nState, pWndOther, bMinimized);
	
	if(m_bHide)
	{
		if (nState == WA_INACTIVE)
		{		
			SendToParent(-1);
		}
	}
}

//##ModelId=474D306502EF
void CGroupTree::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM hItem =  GetNextItem(TVI_ROOT, TVGN_CARET);
	if(hItem)
		SendToParent(GetItemData(hItem));
			
	*pResult = 1;
}

//##ModelId=474D3064031E
long CGroupTree::GetSelectedTree()
{
	HTREEITEM hItem =  GetNextItem(TVI_ROOT, TVGN_CARET);
	if(hItem)
		return (long)GetItemData(hItem);

	return -1;
}

//##ModelId=474D3065033E
void CGroupTree::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	
	switch(pTVKeyDown->wVKey)
	{
	case VK_RETURN:
	{	
		HTREEITEM hItem =  GetNextItem(TVI_ROOT, TVGN_CARET);
		if(hItem)
			SendToParent(GetItemData(hItem));
		
		break;
	}
	case VK_ESCAPE:
	{	
		SendToParent(-1);
		break;
	}	
	}
	
	*pResult = 1;
}


//##ModelId=474D3064034D
void CGroupTree::SendToParent(long lID)
{
	if(m_bSendAllready == false)
	{
		m_bSendAllready = true;
		::PostMessage(m_NotificationWnd, NM_GROUP_TREE_MESSAGE, lID, 0);
	}
}

//##ModelId=474D3064031F
bool CGroupTree::AddNode(CString csText, long lID)
{
	HTREEITEM hItem;

	HTREEITEM hParent =  GetNextItem(TVI_ROOT, TVGN_CARET);
	if(hParent == NULL)
		return false;
		
	hItem = InsertItem(csText, 1, 1, hParent);
	SelectItem(hItem);

	SetItemData(hItem, lID);

	return true;
}
