// Feel free to use this code in your own applications.
// The Author does not guarantee anything about this code.
// Author : Yves Maurer

// FormattedTextDraw.cpp : Implementation of CFormattedTextDraw
#include "stdafx.h"
#include "FormattedTextDraw.h"

/////////////////////////////////////////////////////////////////////////////
// CallBack functions

DWORD CALLBACK EditStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	PCOOKIE pCookie = (PCOOKIE) dwCookie;

	if(pCookie->dwSize - pCookie->dwCount < (DWORD) cb)
		*pcb = pCookie->dwSize - pCookie->dwCount;
	else
		*pcb = cb;

	CopyMemory(pbBuff, pCookie->bstrText, *pcb);
	pCookie->dwCount += *pcb;

	return 0;	//	callback succeeded - no errors
}

/////////////////////////////////////////////////////////////////////////////
// CFormattedTextDraw

//##ModelId=474D30880032
HRESULT CFormattedTextDraw::get_RTFText(BSTR *pVal)
{
	*pVal = SysAllocStringLen(m_RTFText, SysStringLen(m_RTFText));
	return S_OK;
}

//##ModelId=474D30880040
HRESULT CFormattedTextDraw::put_RTFText(BSTR newVal)
{
	HRESULT hr;
	long    len;
	LRESULT lResult = 0;
	EDITSTREAM editStream;

	if (m_RTFText != NULL)
		SysFreeString(m_RTFText);
	len = SysStringLen(newVal);
	m_RTFText = SysAllocStringLen(newVal, len);

	if (!m_spTextServices) 
		return S_FALSE;

	m_editCookie.bstrText = (BSTR) malloc(len + 1);
	WideCharToMultiByte(CP_ACP, 0, m_RTFText, len, (char *) m_editCookie.bstrText, len, NULL, NULL);
	m_editCookie.dwSize = lstrlenA((LPSTR) m_editCookie.bstrText);
	m_editCookie.dwCount = 0;

	editStream.dwCookie = (DWORD_PTR) &m_editCookie;
	editStream.dwError = 0;
	editStream.pfnCallback = EditStreamInCallback;
	hr = m_spTextServices->TxSendMessage(EM_STREAMIN, (WPARAM)(SF_RTF | SF_UNICODE), (LPARAM)&editStream, &lResult);

	free(m_editCookie.bstrText);

	return S_OK;
}

//##ModelId=474D30880021
HRESULT CFormattedTextDraw::Draw(void *hdcDraw, RECT *prc)
{
	if (!m_spTextServices) 
		return S_FALSE;

	m_spTextServices->TxDraw(
	    DVASPECT_CONTENT,  		// Draw Aspect
		0,						// Lindex
		NULL,					// Info for drawing optimization
		NULL,					// target device information
		(HDC) hdcDraw,				// Draw device HDC
		NULL,			 	   	// Target device HDC
		(RECTL *) prc,			// Bounding client rectangle
		NULL,					// Clipping rectangle for metafiles
		(RECT *) NULL,			// Update rectangle
		NULL, 	   				// Call back function
		NULL,					// Call back parameter
		TXTVIEW_INACTIVE);		// What view of the object could be TXTVIEW_ACTIVE
	return S_OK;
}

//##ModelId=474D30880020
HRESULT CFormattedTextDraw::Create()
{
	return CreateTextServicesObject();
}

//##ModelId=474D308703BA
HRESULT CFormattedTextDraw::get_NaturalWidth(long Height, long *pVal)
{
	long lWidth;
	SIZEL szExtent;
	HDC	hdcDraw;

	if (!m_spTextServices)
		return S_FALSE;

	hdcDraw = GetDC(NULL);
	szExtent.cy = Height;
	szExtent.cx = 10000;
	lWidth = 10000;
	m_spTextServices->TxGetNaturalSize(DVASPECT_CONTENT, 
		hdcDraw, 
		NULL,
		NULL,
		TXTNS_FITTOCONTENT,
		&szExtent,
		&lWidth,
		&Height);

	ReleaseDC(NULL, hdcDraw);
	*pVal = lWidth;
	return S_OK;
}

//##ModelId=474D3087037B
HRESULT CFormattedTextDraw::get_NaturalHeight(long Width, long *pVal)
{
	long lHeight;
	SIZEL szExtent;
	HDC	hdcDraw;

	if (!m_spTextServices)
		return S_FALSE;

	hdcDraw = GetDC(NULL);
	szExtent.cx = Width;
	szExtent.cy = 10000;
	lHeight = 10000;
	m_spTextServices->TxGetNaturalSize(DVASPECT_CONTENT, 
		hdcDraw, 
		NULL,
		NULL,
		TXTNS_FITTOCONTENT,
		&szExtent,
		&Width,
		&lHeight);

	ReleaseDC(NULL, hdcDraw);
	*pVal = lHeight;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITextHost functions
//##ModelId=474D3088007F
HDC CFormattedTextDraw::TxGetDC()
{
	return NULL;
}

//##ModelId=474D3088008D
INT CFormattedTextDraw::TxReleaseDC(HDC hdc)
{
	return 1;
}

//##ModelId=474D3088009D
BOOL CFormattedTextDraw::TxShowScrollBar(INT fnBar, BOOL fShow)
{
	return FALSE;
}

//##ModelId=474D3088010A
BOOL CFormattedTextDraw::TxEnableScrollBar(INT fuSBFlags, INT fuArrowflags)
{
	return FALSE;
}

//##ModelId=474D3088011B
BOOL CFormattedTextDraw::TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw)
{
	return FALSE;
}

//##ModelId=474D30880139
BOOL CFormattedTextDraw::TxSetScrollPos(INT fnBar, INT nPos, BOOL fRedraw)
{
	return FALSE;
}

//##ModelId=474D3088014A
void CFormattedTextDraw::TxInvalidateRect(LPCRECT prc, BOOL fMode)
{
}

//##ModelId=474D30880197
void CFormattedTextDraw::TxViewChange(BOOL fUpdate)
{
}

//##ModelId=474D308801A7
BOOL CFormattedTextDraw::TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight)
{
	return FALSE;
}

//##ModelId=474D308801B6
BOOL CFormattedTextDraw::TxShowCaret(BOOL fShow)
{
	return FALSE;
}

//##ModelId=474D308801C6
BOOL CFormattedTextDraw::TxSetCaretPos(INT x, INT y)
{
	return FALSE;
}

//##ModelId=474D308801D5
BOOL CFormattedTextDraw::TxSetTimer(UINT idTimer, UINT uTimeout)
{
	return FALSE;
}

//##ModelId=474D308801E5
void CFormattedTextDraw::TxKillTimer(UINT idTimer)
{
}

//##ModelId=474D308801F5
void CFormattedTextDraw::TxScrollWindowEx(INT dx, INT dy, LPCRECT lprcScroll, LPCRECT lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate, UINT fuScroll)
{
}

//##ModelId=474D30880252
void CFormattedTextDraw::TxSetCapture(BOOL fCapture)
{
}

//##ModelId=474D30880263
void CFormattedTextDraw::TxSetFocus()
{
}

//##ModelId=474D30880272
void CFormattedTextDraw::TxSetCursor(HCURSOR hcur, BOOL fText)
{
}

//##ModelId=474D308802D0
BOOL CFormattedTextDraw::TxScreenToClient(LPPOINT lppt)
{
	return FALSE;
}

//##ModelId=474D308802E0
BOOL CFormattedTextDraw::TxClientToScreen(LPPOINT lppt)
{
	return FALSE;
}

//##ModelId=474D3088031E
HRESULT	CFormattedTextDraw::TxActivate(LONG * plOldState)
{
	return S_OK;
}

//##ModelId=474D3088033D
HRESULT	CFormattedTextDraw::TxDeactivate(LONG lNewState)
{
	return S_OK;
}

//##ModelId=474D3088035D
HRESULT	CFormattedTextDraw::TxGetClientRect(LPRECT prc)
{
	*prc = m_rcClient;
	return S_OK;
}

//##ModelId=474D3088039B
HRESULT	CFormattedTextDraw::TxGetViewInset(LPRECT prc)
{
	*prc = m_rcViewInset;
	return S_OK;
}

//##ModelId=474D308803BB
HRESULT CFormattedTextDraw::TxGetCharFormat(const CHARFORMATW **ppCF)
{
	*ppCF = m_pCF;
	return S_OK;
}

//##ModelId=474D30890010
HRESULT	CFormattedTextDraw::TxGetParaFormat(const PARAFORMAT **ppPF)
{
	*ppPF = &m_PF;
	return S_OK;
}

//##ModelId=474D30890031
COLORREF CFormattedTextDraw::TxGetSysColor(int nIndex)
{
	return GetSysColor(nIndex);
}

//##ModelId=474D3089006E
HRESULT	CFormattedTextDraw::TxGetBackStyle(TXTBACKSTYLE *pstyle)
{
	*pstyle = TXTBACK_TRANSPARENT;
	return S_OK;
}

//##ModelId=474D3089007F
HRESULT	CFormattedTextDraw::TxGetMaxLength(DWORD *plength)
{
	*plength = m_dwMaxLength;
	return S_OK;
}

//##ModelId=474D3089008D
HRESULT	CFormattedTextDraw::TxGetScrollBars(DWORD *pdwScrollBar)
{
	*pdwScrollBar = m_dwScrollbar;
	return S_OK;
}

//##ModelId=474D3089009E
HRESULT	CFormattedTextDraw::TxGetPasswordChar(TCHAR *pch)
{
	return S_FALSE;
}

//##ModelId=474D308900AD
HRESULT	CFormattedTextDraw::TxGetAcceleratorPos(LONG *pcp)
{
	*pcp = -1;
	return S_OK;
}

//##ModelId=474D308900AF
HRESULT	CFormattedTextDraw::TxGetExtent(LPSIZEL lpExtent)
{
	return E_NOTIMPL;
}

//##ModelId=474D308900BD
HRESULT CFormattedTextDraw::OnTxCharFormatChange(const CHARFORMATW * pcf)
{
	memcpy(m_pCF, pcf, pcf->cbSize);
	return S_OK;
}

//##ModelId=474D308900FC
HRESULT	CFormattedTextDraw::OnTxParaFormatChange(const PARAFORMAT * ppf)
{
	memcpy(&m_PF, ppf, ppf->cbSize);
	return S_OK;
}

//##ModelId=474D3089010B
HRESULT	CFormattedTextDraw::TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits)
{
	*pdwBits = m_dwPropertyBits;
	return S_OK;
}

//##ModelId=474D3089012A
HRESULT	CFormattedTextDraw::TxNotify(DWORD iNotify, void *pv)
{
	return S_OK;
}

//##ModelId=474D3089013A
HIMC CFormattedTextDraw::TxImmGetContext()
{
	return NULL;
}

//##ModelId=474D3089013B
void CFormattedTextDraw::TxImmReleaseContext(HIMC himc)
{
}

//##ModelId=474D3089014A
HRESULT	CFormattedTextDraw::TxGetSelectionBarWidth(LONG *lSelBarWidth)
{
	*lSelBarWidth = 100;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// custom functions

//##ModelId=474D30890158
HRESULT CFormattedTextDraw::CharFormatFromHFONT(CHARFORMAT2W* pCF, HFONT hFont)
// Takes an HFONT and fills in a CHARFORMAT2W structure with the corresponding info
{

	HWND hWnd;
	LOGFONT lf;
	HDC hDC;
	LONG yPixPerInch;

	// Get LOGFONT for default font
	if (!hFont)
		hFont = (HFONT) GetStockObject(SYSTEM_FONT);

	// Get LOGFONT for passed hfont
	if (!GetObject(hFont, sizeof(LOGFONT), &lf))
		return E_FAIL;

	// Set CHARFORMAT structure
	memset(pCF, 0, sizeof(CHARFORMAT2W));
	pCF->cbSize = sizeof(CHARFORMAT2W);

	hWnd = GetDesktopWindow();
	hDC = GetDC(hWnd);
	yPixPerInch = GetDeviceCaps(hDC, LOGPIXELSY);
	pCF->yHeight = -lf.lfHeight * LY_PER_INCH / yPixPerInch;
	ReleaseDC(hWnd, hDC);

	pCF->yOffset = 0;
	pCF->crTextColor = 0;

	pCF->dwEffects = CFM_EFFECTS | CFE_AUTOBACKCOLOR;
	pCF->dwEffects &= ~(CFE_PROTECTED | CFE_LINK | CFE_AUTOCOLOR);

	if(lf.lfWeight < FW_BOLD)
		pCF->dwEffects &= ~CFE_BOLD;

	if(!lf.lfItalic)
		pCF->dwEffects &= ~CFE_ITALIC;

	if(!lf.lfUnderline)
		pCF->dwEffects &= ~CFE_UNDERLINE;

	if(!lf.lfStrikeOut)
		pCF->dwEffects &= ~CFE_STRIKEOUT;

	pCF->dwMask = CFM_ALL | CFM_BACKCOLOR | CFM_STYLE;
	pCF->bCharSet = lf.lfCharSet;
	pCF->bPitchAndFamily = lf.lfPitchAndFamily;

#ifdef UNICODE
	wcscpy(pCF->szFaceName, lf.lfFaceName);
#else
	MultiByteToWideChar(CP_ACP, 0, lf.lfFaceName, LF_FACESIZE, pCF->szFaceName, LF_FACESIZE);
#endif

	return S_OK;
}

//##ModelId=474D3089016A
HRESULT CFormattedTextDraw::InitDefaultCharFormat()
{
	return CharFormatFromHFONT(m_pCF, NULL);
}

//##ModelId=474D3089016B
HRESULT CFormattedTextDraw::InitDefaultParaFormat()
{
	memset(&m_PF, 0, sizeof(PARAFORMAT2));
	m_PF.cbSize = sizeof(PARAFORMAT2);
	m_PF.dwMask = PFM_ALL;
	m_PF.wAlignment = PFA_LEFT;
	m_PF.cTabCount = 1;
	m_PF.rgxTabs[0] = lDefaultTab;
	return S_OK;
}

//##ModelId=474D30890178
HRESULT CFormattedTextDraw::CreateTextServicesObject()
{
	HRESULT hr;
	IUnknown *spUnk;

	hr = CreateTextServices(NULL, static_cast<ITextHost*>(this), &spUnk);
	if (hr == S_OK) {
		hr = spUnk->QueryInterface(IID_ITextServicesEx, (void**)&m_spTextServices);
		hr = spUnk->QueryInterface(IID_ITextDocument, (void**)&m_spTextDocument);
		spUnk->Release();
	}
	return hr;
}

