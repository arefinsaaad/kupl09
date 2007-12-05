#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=474D3037005E
class CProgressWnd : public CWnd
{
// Construction/Destruction
public:
	//##ModelId=474D3037006F
    CProgressWnd();
	//##ModelId=474D3037007E
    CProgressWnd(CWnd* pParent, LPCTSTR pszTitle, BOOL bSmooth = FALSE);
	//##ModelId=474D3037008D
    virtual ~CProgressWnd();

	//##ModelId=474D3037008F
    BOOL Create(CWnd* pParent, LPCTSTR pszTitle, BOOL bSmooth = FALSE);
	//##ModelId=474D303700AD
    BOOL GoModal(LPCTSTR pszTitle =_T("Progress"), BOOL bSmooth = FALSE);

protected:
	//##ModelId=474D303700BC
    void CommonConstruct();

// Operations
public:
	//##ModelId=474D303700CC
    void SetRange(int nLower, int nUpper, int nStep = 1);
                                                    // Set range and step size
	//##ModelId=474D303700FB
    int OffsetPos(int nPos);                        // Same as CProgressCtrl
	//##ModelId=474D3037010A
    int StepIt();                                   //    "
	//##ModelId=474D3037011A
    int SetStep(int nStep);                         //    "
	//##ModelId=474D3037012A
    int SetPos(int nPos);                           //    "

	//##ModelId=474D30370139
    void SetText(LPCTSTR fmt, ...);                 // Set text in text area

	//##ModelId=474D3037014A
    void Clear();                                   // Clear text, reset bar
	//##ModelId=474D30370158
    void Hide();                                    // Hide window
	//##ModelId=474D30370168
    void Show();                                    // Show window
	//##ModelId=474D30370178
	void HideCancel();
	//##ModelId=474D30370179
	void ShowCancel();
	//##ModelId=474D30370187
	int	 GetPos() const		{ return m_nPrevPos;	}

	//##ModelId=474D30370189
    BOOL Cancelled() { return m_bCancelled; }       // Was "Cancel" hit?

	//##ModelId=474D30370197
	void SetWindowSize(int nNumTextLines, int nWindowWidth = 390);

	//##ModelId=474D303701A7
    void PeekAndPump(BOOL bCancelOnESCkey = TRUE);  // Message pumping for modal operation   

	//##ModelId=474D303701A9
	void SetTitleText(CString csTitle);
    
// Implementation
protected:
	//##ModelId=474D303701B7
    void GetPreviousSettings();
	//##ModelId=474D303701B8
    void SaveCurrentSettings();

protected:
	//##ModelId=474D303701C6
    BOOL m_bCancelled;
	//##ModelId=474D303701D5
    BOOL m_bModal;
	//##ModelId=474D303701D6
    BOOL m_bPersistantPosition;
    int  m_nPrevPos, m_nPrevPercent;
	//##ModelId=474D303701E5
    int  m_nStep;
    int  m_nMaxValue, m_nMinValue;
	//##ModelId=474D303701F5
    int  m_nNumTextLines;

	//##ModelId=474D30370205
    CStatic       m_Text;
	//##ModelId=474D30370215
    CProgressCtrl m_wndProgress;
	//##ModelId=474D30370234
    CButton       m_CancelButton;
    CString       m_strTitle,
                  m_strCancelLabel;
	//##ModelId=474D30370244
    CFont         m_font;


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CProgressWnd)
	public:
	//##ModelId=474D30370252
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
    //{{AFX_MSG(CProgressWnd)
	//##ModelId=474D30370262
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	//##ModelId=474D30370272
    afx_msg void OnCancel();
    DECLARE_MESSAGE_MAP()
};
