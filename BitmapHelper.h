// BitmapHelper.h: interface for the CBitmapHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPHELPER_H__641D941B_5487_4F85_BFC1_012F2083A8B6__INCLUDED_)
#define AFX_BITMAPHELPER_H__641D941B_5487_4F85_BFC1_012F2083A8B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))

//##ModelId=474D3079031E
class CBitmapHelper  
{
public:
	//##ModelId=474D3079034C
	CBitmapHelper();
	//##ModelId=474D3079034D
	virtual ~CBitmapHelper();

	//##ModelId=474D3079034F
	static int		GetCBitmapWidth(const CBitmap & cbm);
	//##ModelId=474D3079036C
	static int		GetCBitmapHeight(const CBitmap & cbm);
	//##ModelId=474D307903AA
	static BOOL		GetCBitmap(void	*pClip2, CDC *pDC, CBitmap *pBitMap, int nMaxHeight);
	//##ModelId=474D307A0010
	static HANDLE	hBitmapToDIB(HBITMAP hBitmap, DWORD dwCompression, HPALETTE hPal);
	//##ModelId=474D307A0030
	static WORD		PaletteSize(LPSTR lpDIB);
	//##ModelId=474D307A0033
	static WORD		DIBNumColors(LPSTR lpDIB);
	//##ModelId=474D307A007E
	static bool		DrawDIB(CDC *pDC, HANDLE hData, int nLeft, int nRight, int &nWidth);

};

#endif // !defined(AFX_BITMAPHELPER_H__641D941B_5487_4F85_BFC1_012F2083A8B6__INCLUDED_)
