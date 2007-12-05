// FormatSQL.cpp: implementation of the CFormatSQL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cp_main.h"
#include "FormatSQL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=474D306601C6
CFormatSQL::CFormatSQL()
{

}

//##ModelId=474D306601D5
CFormatSQL::~CFormatSQL()
{

}

//##ModelId=474D306601D7
void CFormatSQL::Parse(CString cs)
{
	//Replace all single ' with a double '
	cs.Replace(_T("'"), _T("''"));
	//Replace all "|" with a space
	cs.Replace(_T("|"), _T(" "));

	cs.Replace(_T("["), _T(" "));
	cs.Replace(_T("]"), _T(" "));

	cs.Replace(_T("*"), _T("%"));

	int nLength = cs.GetLength();

	CString csCurrentWord;
	bool bInQuotes = false;
	eSpecialTypes eNotValue = eINVALID;
	eSpecialTypes eOrValue = eAND;

	for(int i = 0; i < nLength; i++)
	{
		switch(cs[i])
		{
		case '"':
			bInQuotes = !bInQuotes;
			break;
		case ' ':
			if(bInQuotes == false)
			{
				eSpecialTypes sp = ConvetToKey(csCurrentWord);
				switch(sp)
				{
				case eNOT:
					eNotValue = sp;
					break;
				case eOR:
				case eAND:
					eOrValue = sp;
					break;
				default:
					AddToSQL(csCurrentWord, eNotValue, eOrValue);
				}
				csCurrentWord = "";
			}
			else
			{
				csCurrentWord += cs[i];
			}
			break;
		default:
			csCurrentWord += cs[i];
		}
	}

	if(csCurrentWord.GetLength() > 0)
		AddToSQL(csCurrentWord, eNotValue, eOrValue);
}

//##ModelId=474D30660234
CFormatSQL::eSpecialTypes CFormatSQL::ConvetToKey(CString cs)
{
	cs.MakeUpper();

	if(cs == "NOT" || 
		cs == "!")
	{
		return eNOT;
	}
	else if(cs == "OR")
	{
		return eOR;
	}
	else if(cs == "AND")
	{
		return eAND;
	}

	return eINVALID;
}

//##ModelId=474D30660244
CString CFormatSQL::GetKeyWordString(eSpecialTypes eKeyWord)
{
	switch(eKeyWord)
	{
	case eNOT:
		return " NOT ";
	case eAND:
		return " AND ";
	case eOR:
		return " OR ";
	case eINVALID:
		return " ";
	}

	return " ";
}

//##ModelId=474D30660214
bool CFormatSQL::AddToSQL(CString cs, eSpecialTypes &eNOTValue, eSpecialTypes &eORValue)
{
	CString csThisSQL;
	cs.TrimLeft();
	cs.TrimRight();

	if(cs.Find(_T("%")) < 0 && cs.Find(_T("?")) < 0)
	{
		csThisSQL.Format(_T("%s%sLIKE \'%%%s%%\'"), m_csVariable, GetKeyWordString(eNOTValue), cs);
	}
	else
	{
		csThisSQL.Format(_T("%s%sLIKE \'%s%%\'"), m_csVariable, GetKeyWordString(eNOTValue), cs);
	}

	if(m_csWhere.GetLength() > 0)
	{
		m_csWhere += GetKeyWordString(eORValue) + csThisSQL;
	}
	else
	{
		m_csWhere = csThisSQL;
	}

	eNOTValue = eINVALID;
	eORValue = eAND;

	return true;
}
