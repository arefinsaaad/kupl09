// NumberEdit.cpp : implementation file
//

#include "stdafx.h"
#include "CP_Main.h"
#include "NumberEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit

//##ModelId=474D3085033D
CNumberEdit::CNumberEdit()
{
	m_dMax = LONG_MAX;
}

//##ModelId=474D30860010
CNumberEdit::~CNumberEdit()
{
}


BEGIN_MESSAGE_MAP(CNumberEdit, CEdit)
	//{{AFX_MSG_MAP(CNumberEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit message handlers

//##ModelId=474D30860012
void CNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//Only allow the number 0 - 9 and a the backspace to go through
	if(((nChar < '0') || (nChar > '9')) && (nChar != VK_BACK))
		return;

	CString csText;
	GetWindowText(csText);

	//Save this if the validate fails then these get set back
	int nStartChar, nEndChar;
	GetSel(nStartChar, nEndChar);

	//Set the new number
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	
	//If its not valid set it back to the old number
	if(!ValidateNumber(GetNumberD()))
	{
		SetWindowText(csText);
		SetSel(nStartChar, nEndChar);
	}
}

//##ModelId=474D308503D9
BOOL CNumberEdit::ValidateNumber(double dNumber)
{
	if(dNumber > m_dMax)
		return FALSE;

	return TRUE;
}

//##ModelId=474D3085034C
long CNumberEdit::GetNumber()
{
	CString csText;
	GetWindowText(csText);
	
	return ATOL(csText);
}

//##ModelId=474D3085033E
double CNumberEdit::GetNumberD()
{
	CString csText;
	GetWindowText(csText);

#ifdef _UNICODE				
	TCHAR *pEnd;
	double d = _tcstod(csText, &pEnd);
#else
	double d = atof(csText);
#endif

	return d;
}

//##ModelId=474D3085037B
BOOL CNumberEdit::SetNumber(long lNumber)
{
	//Check if its a good number
	if(!ValidateNumber(lNumber))
	{
		MessageBeep(0);
		return FALSE;
	}

	//Its good
	CString csText;
	csText.Format(_T("%d"), lNumber);
	SetWindowText(csText);

	return TRUE;
}

