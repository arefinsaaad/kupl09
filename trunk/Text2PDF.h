#pragma once


// CText2PDF ��ȭ �����Դϴ�.

//##ModelId=474D301E00DB
class CText2PDF : public CDialog
{
	DECLARE_DYNAMIC(CText2PDF)

public:
	//##ModelId=474D301E00EB
	CText2PDF(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	//##ModelId=474D301E00FB
	virtual ~CText2PDF();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TEXT2PDF_DLG };

protected:
	//##ModelId=474D301E010A
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
