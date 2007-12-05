// OptionPDF.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CP_Main.h"
#include "OptionPDF.h"


// COptionPDF 대화 상자입니다.

IMPLEMENT_DYNAMIC(COptionPDF, CDialog)
//##ModelId=474D305603AB
COptionPDF::COptionPDF(CWnd* pParent /*=NULL*/)
	: CDialog(COptionPDF::IDD, pParent)
{
}

//##ModelId=474D30570020
COptionPDF::~COptionPDF()
{
}

//##ModelId=474D30570022
void COptionPDF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COptionPDF, CDialog)
END_MESSAGE_MAP()


// COptionPDF 메시지 처리기입니다.
