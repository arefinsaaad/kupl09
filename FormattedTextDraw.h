// Feel free to use this code in your own applications.
// The Author does not guarantee anything about this code.
// Author : Yves Maurer

// FormattedTextDraw.h : Declaration of the CFormattedTextDraw

#ifndef __FORMATTEDTEXTDRAW_H_
#define __FORMATTEDTEXTDRAW_H_

#include "resource.h"       // main symbols

// be sure to link this project with riched20.lib
#include <richedit.h>
#include <textserv.h>

#ifndef LY_PER_INCH
#define LY_PER_INCH   1440
#define HOST_BORDER 0
#endif

//##ModelId=474D308700BC
typedef struct tagCOOKIE
{
	BSTR	bstrText;
	DWORD	dwSize;
	DWORD	dwCount;
} COOKIE, *PCOOKIE;

// These definitions might give you problems.  If they do, open your
// textserv.h and comment the following lines out. They are right at the top
// EXTERN_C const IID IID_ITextServices;
// EXTERN_C const IID IID_ITextHost;

const IID IID_ITextServicesEx = { // 8d33f740-cf58-11ce-a89d-00aa006cadc5
    0x8d33f740,
    0xcf58,
    0x11ce,
    {0xa8, 0x9d, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5}
 };

//const IID IID_ITextHosts = { // c5bdd8d0-d26e-11ce-a89e-00aa006cadc5
//    0xc5bdd8d0,
//    0xd26e,
//    0x11ce,
//    {0xa8, 0x9e, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5}
//  };

/////////////////////////////////////////////////////////////////////////////
// IFormatttedTextDraw
interface IFormattedTextDraw
{
public:
	virtual ~IFormattedTextDraw() {};
	virtual HRESULT get_NaturalHeight(long Width, /*[out, retval]*/ long *pVal) = 0;
	virtual HRESULT get_NaturalWidth(long Height, /*[out, retval]*/ long *pVal) = 0;
	virtual HRESULT Create() = 0;
	virtual HRESULT Draw(void *hdcDraw, RECT *prc) = 0;
	virtual HRESULT get_RTFText(/*[out, retval]*/ BSTR *pVal) = 0;
	virtual HRESULT put_RTFText(/*[in]*/ BSTR newVal) = 0;

// COM-like functions
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// CFormattedTextDraw
//##ModelId=474D308702FE
class CFormattedTextDraw : 
	public ITextHost,
	public IFormattedTextDraw
{
public:
	//##ModelId=474D3087031E
	CFormattedTextDraw()
	{
		HDC hdcScreen;

		m_RTFText = NULL;

		hdcScreen = GetDC(NULL);
		nPixelsPerInchX = GetDeviceCaps(hdcScreen, LOGPIXELSX);
		nPixelsPerInchY = GetDeviceCaps(hdcScreen, LOGPIXELSY);
		ReleaseDC(NULL, hdcScreen);

		SetRectEmpty(&m_rcClient);
		SetRectEmpty(&m_rcViewInset);

		m_pCF = (CHARFORMAT2W*) malloc(sizeof(CHARFORMAT2W));

		InitDefaultCharFormat();
		InitDefaultParaFormat();
		m_spTextServices = NULL;
		m_spTextDocument = NULL;

		m_dwPropertyBits = TXTBIT_RICHTEXT | TXTBIT_MULTILINE | TXTBIT_WORDWRAP | TXTBIT_USECURRENTBKG;
		m_dwScrollbar = 0;
		m_dwMaxLength = INFINITE;
	}

	//##ModelId=474D3087031F
	~CFormattedTextDraw()
	{
		if (m_RTFText != NULL)
			SysFreeString(m_RTFText);

		free(m_pCF);
		if (m_spTextServices != NULL)
			m_spTextServices->Release();
		if (m_spTextDocument != NULL)
			m_spTextDocument->Release();
	}

// Minimal COM functionality
	//##ModelId=474D30870320
    HRESULT STDMETHODCALLTYPE QueryInterface( 
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		*ppvObject = NULL;
		return S_FALSE;
	}
    
	//##ModelId=474D3087035E
    ULONG STDMETHODCALLTYPE AddRef(void)
	{
		return 0;
	}
    
	//##ModelId=474D3087036C
    ULONG STDMETHODCALLTYPE Release(void)
	{
		return 0;
	}

// IFormattedTextDraw
public:
	//##ModelId=474D3087037B
	HRESULT get_NaturalHeight(long Width, /*[out, retval]*/ long *pVal);
	//##ModelId=474D308703BA
	HRESULT get_NaturalWidth(long Height, /*[out, retval]*/ long *pVal);
	//##ModelId=474D30880020
	HRESULT Create();
	//##ModelId=474D30880021
	HRESULT Draw(void *hdcDraw, RECT *prc);
	//##ModelId=474D30880032
	HRESULT get_RTFText(/*[out, retval]*/ BSTR *pVal);
	//##ModelId=474D30880040
	HRESULT put_RTFText(/*[in]*/ BSTR newVal);

// ITextHost
	//##ModelId=474D3088007F
	HDC TxGetDC();
	//##ModelId=474D3088008D
	INT TxReleaseDC(HDC hdc);
	//##ModelId=474D3088009D
	BOOL TxShowScrollBar(INT fnBar, BOOL fShow);
	//##ModelId=474D3088010A
	BOOL TxEnableScrollBar(INT fuSBFlags, INT fuArrowflags);
	//##ModelId=474D3088011B
	BOOL TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw);
	//##ModelId=474D30880139
	BOOL TxSetScrollPos(INT fnBar, INT nPos, BOOL fRedraw);
	//##ModelId=474D3088014A
	void TxInvalidateRect(LPCRECT prc, BOOL fMode);
	//##ModelId=474D30880197
	void TxViewChange(BOOL fUpdate);
	//##ModelId=474D308801A7
	BOOL TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight);
	//##ModelId=474D308801B6
	BOOL TxShowCaret(BOOL fShow);
	//##ModelId=474D308801C6
	BOOL TxSetCaretPos(INT x, INT y);
	//##ModelId=474D308801D5
	BOOL TxSetTimer(UINT idTimer, UINT uTimeout);
	//##ModelId=474D308801E5
	void TxKillTimer(UINT idTimer);
	//##ModelId=474D308801F5
	void TxScrollWindowEx(INT dx, INT dy, LPCRECT lprcScroll, LPCRECT lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate, UINT fuScroll);
	//##ModelId=474D30880252
	void TxSetCapture(BOOL fCapture);
	//##ModelId=474D30880263
	void TxSetFocus();
	//##ModelId=474D30880272
	void TxSetCursor(HCURSOR hcur, BOOL fText);
	//##ModelId=474D308802D0
	BOOL TxScreenToClient(LPPOINT lppt);
	//##ModelId=474D308802E0
	BOOL TxClientToScreen(LPPOINT lppt);
	//##ModelId=474D3088031E
	HRESULT	TxActivate(LONG * plOldState);
	//##ModelId=474D3088033D
	HRESULT	TxDeactivate(LONG lNewState);
	//##ModelId=474D3088035D
	HRESULT	TxGetClientRect(LPRECT prc);
	//##ModelId=474D3088039B
	HRESULT	TxGetViewInset(LPRECT prc);
	//##ModelId=474D308803BB
	HRESULT TxGetCharFormat(const CHARFORMATW **ppCF);
	//##ModelId=474D30890010
	HRESULT	TxGetParaFormat(const PARAFORMAT **ppPF);
	//##ModelId=474D30890031
	COLORREF TxGetSysColor(int nIndex);
	//##ModelId=474D3089006E
	HRESULT	TxGetBackStyle(TXTBACKSTYLE *pstyle);
	//##ModelId=474D3089007F
	HRESULT	TxGetMaxLength(DWORD *plength);
	//##ModelId=474D3089008D
	HRESULT	TxGetScrollBars(DWORD *pdwScrollBar);
	//##ModelId=474D3089009E
	HRESULT	TxGetPasswordChar(TCHAR *pch);
	//##ModelId=474D308900AD
	HRESULT	TxGetAcceleratorPos(LONG *pcp);
	//##ModelId=474D308900AF
	HRESULT	TxGetExtent(LPSIZEL lpExtent);
	//##ModelId=474D308900BD
	HRESULT OnTxCharFormatChange(const CHARFORMATW * pcf);
	//##ModelId=474D308900FC
	HRESULT	OnTxParaFormatChange(const PARAFORMAT * ppf);
	//##ModelId=474D3089010B
	HRESULT	TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits);
	//##ModelId=474D3089012A
	HRESULT	TxNotify(DWORD iNotify, void *pv);
	//##ModelId=474D3089013A
	HIMC TxImmGetContext();
	//##ModelId=474D3089013B
	void TxImmReleaseContext(HIMC himc);
	//##ModelId=474D3089014A
	HRESULT	TxGetSelectionBarWidth(LONG *lSelBarWidth);

// Custom functions
	//##ModelId=474D30890158
	HRESULT CharFormatFromHFONT(CHARFORMAT2W* pCF, HFONT hFont);
	//##ModelId=474D3089016A
	HRESULT InitDefaultCharFormat();
	//##ModelId=474D3089016B
	HRESULT InitDefaultParaFormat();
	//##ModelId=474D30890178
	HRESULT CreateTextServicesObject();

// Variables
	//##ModelId=474D308901C7
	RECT			m_rcClient;			// Client Rect
	//##ModelId=474D308901D6
	RECT			m_rcViewInset;		// view rect inset
	//##ModelId=474D308901F6
	SIZEL			m_sizelExtent;		// Extent array

	//##ModelId=474D308901FA
	int				nPixelsPerInchX;    // Pixels per logical inch along width
	//##ModelId=474D30890243
	int				nPixelsPerInchY;    // Pixels per logical inch along height

	//##ModelId=474D30890282
	CHARFORMAT2W	*m_pCF;
	//##ModelId=474D30890292
	PARAFORMAT2		m_PF;
	//##ModelId=474D308902A1
	DWORD			m_dwScrollbar;		// Scroll bar style
	//##ModelId=474D308902B0
	DWORD			m_dwPropertyBits;	// Property bits
	//##ModelId=474D308902C0
	DWORD			m_dwMaxLength;
	//##ModelId=474D308902FF
	COOKIE			m_editCookie;

	//##ModelId=474D3089031F
	ITextServices	*m_spTextServices;
	//##ModelId=474D3089033E
	ITextDocument	*m_spTextDocument;
	//##ModelId=474D3089037C
	BSTR			m_RTFText;
};

#endif //__FORMATTEDTEXTDRAW_H_
