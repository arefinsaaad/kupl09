// OptionFriends.cpp : implementation file
//

#include "stdafx.h"
#include "cp_main.h"
#include "OptionFriends.h"
#include "FriendDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EMPTRY_STRING "----"

/////////////////////////////////////////////////////////////////////////////
// COptionFriends property page

IMPLEMENT_DYNCREATE(COptionFriends, CPropertyPage)

//##ModelId=474D30570168
COptionFriends::COptionFriends() : CPropertyPage(COptionFriends::IDD)
{
	m_csTitle = theApp.m_Language.GetString("FriendsTitle", "Friends");
	m_psp.pszTitle = m_csTitle;
	m_psp.dwFlags |= PSP_USETITLE; 

	//{{AFX_DATA_INIT(COptionFriends)
	m_PlaceOnClipboard = _T("");
	m_csPassword = _T("");
	m_csAdditionalPasswords = _T("");
	//}}AFX_DATA_INIT
}

//##ModelId=474D30570187
COptionFriends::~COptionFriends()
{
}

//##ModelId=474D3057038C
void COptionFriends::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionFriends)
	DDX_Control(pDX, IDC_CHECK_DISABLE_FRIENDS, m_bDisableRecieve);
	DDX_Control(pDX, IDC_CHECK_LOG_SEND_RECIEVE, m_SendRecieve);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT_PLACE_ON_CLIPBOARD, m_PlaceOnClipboard);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_ADDITIONAL, m_csAdditionalPasswords);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionFriends, CPropertyPage)
	//{{AFX_MSG_MAP(COptionFriends)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST, OnKeydownList)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_FRIENDS, OnCheckDisableFriends)
	//}}AFX_MSG_MAP 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionFriends message handlers


//##ModelId=474D30580139
BOOL COptionFriends::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_pParent = (COptionsSheet *)GetParent();
	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	InitListCtrlCols();

	InsertItems();

	m_SendRecieve.SetCheck(CGetSetOptions::GetLogSendReceiveErrors());
	m_bDisableRecieve.SetCheck(CGetSetOptions::GetDisableRecieve());

	m_PlaceOnClipboard = g_Opt.m_csIPListToPutOnClipboard;
	m_csPassword = g_Opt.m_csPassword;
	m_csAdditionalPasswords = CGetSetOptions::GetExtraNetworkPassword(false);

	UpdateData(FALSE);

	theApp.m_Language.UpdateOptionFriends(this);
		
	return FALSE;
}

//##ModelId=474D3057036C
BOOL COptionFriends::OnApply() 
{
	CSendClients client;
	for (int i = 0; i < MAX_SEND_CLIENTS; i++)
	{
		if(m_List.GetItemText(i, 1) == "X")
			client.bSendAll = TRUE;
		else
			client.bSendAll = FALSE;

		client.csIP = m_List.GetItemText(i, 2);
		if(client.csIP == EMPTRY_STRING)
			client.csIP = "";
		
		client.csDescription = m_List.GetItemText(i, 3);
		if(client.csDescription == EMPTRY_STRING)
			client.csDescription = "";

		g_Opt.SetSendClients(client, i);
	}

	CGetSetOptions::SetNetworkPassword(m_csPassword);
	CGetSetOptions::SetLogSendReceiveErrors(m_SendRecieve.GetCheck());

	CGetSetOptions::SetDisableRecieve(m_bDisableRecieve.GetCheck());
	theApp.StartStopServerThread();

	UpdateData();

	g_Opt.SetListToPutOnClipboard(m_PlaceOnClipboard);
	g_Opt.SetNetworkPassword(m_csPassword);
	g_Opt.GetClientSendCount();

	g_Opt.SetExtraNetworkPassword(m_csAdditionalPasswords);
	//get get to refill the array extra passwords
	g_Opt.GetExtraNetworkPassword(true);
	
	return CPropertyPage::OnApply();
}


//##ModelId=474D30580001
void COptionFriends::InitListCtrlCols()
{
	// Insert some columns
	m_List.InsertColumn(0, _T(""), LVCFMT_LEFT, 25);

	m_List.InsertColumn(1, theApp.m_Language.GetString("Send_All_Copies", "Send All Copies"), LVCFMT_LEFT, 90);
	m_List.InsertColumn(2, theApp.m_Language.GetString("IP_Name", "IP/Name"), LVCFMT_LEFT, 135);
	m_List.InsertColumn(3, theApp.m_Language.GetString("Descriptions", "Descriptions"), LVCFMT_LEFT, 157);
}

//##ModelId=474D30580030
void COptionFriends::InsertItems()
{
	// Delete the current contents
	m_List.DeleteAllItems();

	// Use the LV_ITEM structure to insert the items
	LVITEM lvi;
	CString strItem;
	for (int i = 0; i < MAX_SEND_CLIENTS; i++)
	{
		// Insert the first item
		lvi.mask =  LVIF_TEXT;
	
		lvi.iItem = i;

//-------------------------------------------------------------------

		strItem.Format(_T("%d"), i+1);

		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		m_List.InsertItem(&lvi);

//-------------------------------------------------------------------
		if(g_Opt.m_SendClients[i].bSendAll)
			strItem = "X";
		else
			strItem = EMPTRY_STRING;

		m_List.SetItemText(i, 1, strItem);

//-------------------------------------------------------------------

		strItem = g_Opt.m_SendClients[i].csIP;
		if(g_Opt.m_SendClients[i].csIP.GetLength() <= 0)
		{
			strItem = EMPTRY_STRING;
		}

		m_List.SetItemText(i, 2, strItem);

//-------------------------------------------------------------------

		strItem = g_Opt.m_SendClients[i].csDescription;
		if(g_Opt.m_SendClients[i].csDescription.GetLength() <= 0)
		{
			strItem = EMPTRY_STRING;
		}
		
		m_List.SetItemText(i, 3, strItem);
	}
}

//##ModelId=474D30580149
void COptionFriends::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if(pos)
	{
		int nItem = m_List.GetNextSelectedItem(pos);

		EditItem(nItem);
	}
	
	*pResult = 0;
}

//##ModelId=474D3058005E
BOOL COptionFriends::EditItem(int nItem)
{
	CFriendDetails dlg;

	if(m_List.GetItemText(nItem, 1) == "X")
		dlg.m_checkSendAll = TRUE;
	else
		dlg.m_checkSendAll = FALSE;

	dlg.m_csIP = m_List.GetItemText(nItem, 2);
	if(dlg.m_csIP == EMPTRY_STRING)
		dlg.m_csIP = "";
	dlg.m_csDescription = m_List.GetItemText(nItem, 3);
	if(dlg.m_csDescription == EMPTRY_STRING)
		dlg.m_csDescription = "";

	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_checkSendAll)
		{
			m_List.SetItemText(nItem, 1, _T("X"));
		}
		else
			m_List.SetItemText(nItem, 1, _T(""));

		m_List.SetItemText(nItem, 2, dlg.m_csIP);
		m_List.SetItemText(nItem, 3, dlg.m_csDescription);

		return TRUE;
	}

	return FALSE;
}

//##ModelId=474D305801B6
void COptionFriends::OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	switch (pLVKeyDow->wVKey)
	{
	case VK_DELETE:
		{
			POSITION pos = m_List.GetFirstSelectedItemPosition();
			if(pos)
			{
				int nItem = m_List.GetNextSelectedItem(pos);
				m_List.SetItemText(nItem, 1, _T(EMPTRY_STRING));
				m_List.SetItemText(nItem, 2, _T(EMPTRY_STRING));
				m_List.SetItemText(nItem, 3, _T(EMPTRY_STRING));
			}
		}
		break;
	case VK_RETURN:
		{
			POSITION pos = m_List.GetFirstSelectedItemPosition();
			if(pos)
			{
				int nItem = m_List.GetNextSelectedItem(pos);
				EditItem(nItem);
			}
		}
		break;
	}
	
	
	*pResult = 0;
}

//##ModelId=474D30580224
void COptionFriends::OnCheckDisableFriends() 
{
	if(m_bDisableRecieve.GetCheck() == BST_CHECKED)
		GetDlgItem(IDC_EDIT_PLACE_ON_CLIPBOARD)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_EDIT_PLACE_ON_CLIPBOARD)->EnableWindow(TRUE);
}
