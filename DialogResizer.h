// DialogResizer.h: interface for the CDialogResizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGRESIZER_H__DA9AF3FF_C6CC_4D70_965A_4216A0EC9E75__INCLUDED_)
#define AFX_DIALOGRESIZER_H__DA9AF3FF_C6CC_4D70_965A_4216A0EC9E75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

#define DR_MoveLeft			 1
#define DR_MoveTop			 2
#define DR_SizeWidth		 4
#define DR_SizeHeight		 8

//##ModelId=474D306E0139
class CDialogResizer  
{
public:
	//##ModelId=474D306E0168
	CDialogResizer();
	//##ModelId=474D306E0178
	virtual ~CDialogResizer();

protected:
	//##ModelId=474D306E0243
	class CDR_Data
	{
	public:
		//##ModelId=474D306E0252
		CDR_Data()
		{			
			m_nFlags = 0;
		}
		//##ModelId=474D306E0253
		HWND m_hWnd;
		//##ModelId=474D306E0262
		int m_nFlags;
	};

public:
	//##ModelId=474D306E017A
	void MoveControls(CSize csNewSize);

	//##ModelId=474D306E01A7
	void AddControl(int nControlID, int nFlags);
	//##ModelId=474D306E01B7
	void AddControl(HWND hWnd, int nFlags);

	//##ModelId=474D306E01D6
	void SetParent(HWND hWndParent);

protected:

	//##ModelId=474D306E01F6
	CArray< CDR_Data, CDR_Data > m_Controls;
	//##ModelId=474D306E0214
	CSize m_DlgSize;
	//##ModelId=474D306E0224
	HWND m_hWndParent;

protected:
};

#endif // !defined(AFX_DIALOGRESIZER_H__DA9AF3FF_C6CC_4D70_965A_4216A0EC9E75__INCLUDED_)
