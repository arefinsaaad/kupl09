#if !defined(AFX_CLIPBOARDVIEWER_H__67418FB6_6048_48FA_86D4_F412CACC41B1__INCLUDED_)
#define AFX_CLIPBOARDVIEWER_H__67418FB6_6048_48FA_86D4_F412CACC41B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define TIMER_ENSURE_VIEWER_IN_CHAIN	6
#define TIMER_DRAW_CLIPBOARD			7
#define TIMER_PING						8

//##ModelId=474D3075033D
class CClipboardViewer : public CWnd
{
// Construction
public:
	//##ModelId=474D3075037C
	CClipboardViewer(CCopyThread* pHandler);
	//##ModelId=474D3075038C
	virtual ~CClipboardViewer();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipboardViewer)
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=474D3075039C
	void Create();

	//##ModelId=474D307503AA
	HWND	m_hNextClipboardViewer;
	//##ModelId=474D307503BA
	bool	m_bCalling_SetClipboardViewer;
	//##ModelId=474D307503C9
	bool	m_bPinging;
	//##ModelId=474D307503D9
	bool	m_bConnect;
	//##ModelId=474D30760030
	bool	m_bIsConnected;

	// m_pHandler->OnClipboardChange is called when the clipboard changes.
	//##ModelId=474D3076005F
	CCopyThread*	m_pHandler;

	//##ModelId=474D3076007E
	void Connect();    // connects as a clipboard viewer
	//##ModelId=474D3076007F
	void Disconnect(bool bSendPing = true); // disconnects as a clipboard viewer

	//##ModelId=474D3076008D
	void SendPing();

	//##ModelId=474D3076008E
	bool GetConnect()				{ return m_bConnect; }
	//##ModelId=474D3076009D
	void SetConnect(bool bConnect);
	//##ModelId=474D3076009F
	void SetEnsureConnectedTimer();

	//##ModelId=474D307600AD
	DWORD m_dwLastCopy;
	//##ModelId=474D307600BC
	bool m_bHandlingClipChange;

	// Generated message map functions
protected:
	//{{AFX_MSG(CClipboardViewer)
	//##ModelId=474D307600CC
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=474D3076010A
	afx_msg void OnDestroy();
	//##ModelId=474D3076011A
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	//##ModelId=474D3076012C
	afx_msg void OnDrawClipboard();
	//##ModelId=474D3076013A
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	//##ModelId=474D30760188
	afx_msg LRESULT OnSetConnect(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPBOARDVIEWER_H__67418FB6_6048_48FA_86D4_F412CACC41B1__INCLUDED_)
