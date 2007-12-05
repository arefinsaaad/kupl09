#pragma once


// CText2PDF 대화 상자입니다.

//##ModelId=474D301E00DB
class CText2PDF : public CDialog
{
	DECLARE_DYNAMIC(CText2PDF)

public:
	//##ModelId=474D301E00EB
	CText2PDF(CWnd* pParent = NULL);   // 표준 생성자입니다.
	//##ModelId=474D301E00FB
	virtual ~CText2PDF();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEXT2PDF_DLG };

protected:
	//##ModelId=474D301E010A
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
