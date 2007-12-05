// FormatSQL.h: interface for the CFormatSQL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMATSQL_H__3D7AC79C_FDD8_4948_B7CD_601FB513F208__INCLUDED_)
#define AFX_FORMATSQL_H__3D7AC79C_FDD8_4948_B7CD_601FB513F208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=474D306601A7
class CFormatSQL  
{
public:
	//##ModelId=474D306601C6
	CFormatSQL();
	//##ModelId=474D306601D5
	virtual ~CFormatSQL();

	//##ModelId=474D306601D7
	void Parse(CString cs);

	//##ModelId=474D306601E6
	CString GetSQLString()				{ return m_csWhere; }
	//##ModelId=474D306601F5
	void	SetVariable(CString cs)		{ m_csVariable = cs;}

protected:
	//##ModelId=474D306601F7
	CString m_csWhere;
	//##ModelId=474D30660204
	CString m_csVariable;
	//##ModelId=474D30660262
	enum eSpecialTypes{eINVALID, eNOT, eAND, eOR};
	

	//##ModelId=474D30660214
	bool AddToSQL(CString cs, eSpecialTypes &eNOTValue, eSpecialTypes &eORValue);
	//##ModelId=474D30660234
	CFormatSQL::eSpecialTypes ConvetToKey(CString cs);
	//##ModelId=474D30660244
	CString GetKeyWordString(eSpecialTypes eKeyWord);
};

#endif // !defined(AFX_FORMATSQL_H__3D7AC79C_FDD8_4948_B7CD_601FB513F208__INCLUDED_)
