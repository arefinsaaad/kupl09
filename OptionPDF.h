#pragma once


// COptionPDF ��ȭ �����Դϴ�.

//##ModelId=474D3056036C
class COptionPDF : public CDialog
{
	DECLARE_DYNAMIC(COptionPDF)

public:
	//##ModelId=474D305603AB
	COptionPDF(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	//##ModelId=474D30570020
	virtual ~COptionPDF();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OPTIONS_PDF };

protected:
	//##ModelId=474D30570022
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
