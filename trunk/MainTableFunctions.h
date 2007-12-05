// MainTableFunctions.h: interface for the CMainTableFunctions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINTABLEFUNCTIONS_H__3AE1D19B_D68D_48E7_80CA_AB62B0447883__INCLUDED_)
#define AFX_MAINTABLEFUNCTIONS_H__3AE1D19B_D68D_48E7_80CA_AB62B0447883__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=474D305E039B
class CMainTableFunctions  
{
public:
	//##ModelId=474D305E03BA
	CMainTableFunctions();
	//##ModelId=474D305E03C9
	virtual ~CMainTableFunctions();

	//##ModelId=474D305E03CB
	static void LoadAcceleratorKeys(CAccels& accels, CppSQLite3DB &db);
	//##ModelId=474D305E03DC
	static CString GetDisplayText(int nMaxLines, const CString &OrigText);
};

#endif // !defined(AFX_MAINTABLEFUNCTIONS_H__3AE1D19B_D68D_48E7_80CA_AB62B0447883__INCLUDED_)
