#pragma once


// COptionPDF 대화 상자입니다.

//##ModelId=474D3056036C
class COptionPDF : public CDialog
{
	DECLARE_DYNAMIC(COptionPDF)

public:
	//##ModelId=474D305603AB
	COptionPDF(CWnd* pParent = NULL);   // 표준 생성자입니다.
	//##ModelId=474D30570020
	virtual ~COptionPDF();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OPTIONS_PDF };

protected:
	//##ModelId=474D30570022
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
