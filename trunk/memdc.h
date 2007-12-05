#ifndef _MEMDC_H_
#define _MEMDC_H_

//////////////////////////////////////////////////
// CMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// This class implements a memory Device Context

//##ModelId=474D3086005F
class CMemDC : public CDC 
{
private:
	//##ModelId=474D308600BD
	CBitmap*	m_bitmap;
	//##ModelId=474D308600DC
	CBitmap*	m_oldBitmap;
	//##ModelId=474D308600FC
	CDC*		m_pDC;
	//##ModelId=474D3086011A
	CRect		m_rcBounds;
public:
	//##ModelId=474D30860187
	CMemDC(CDC* pDC, const CRect& rcBounds) : CDC()
	{
		CreateCompatibleDC(pDC);
		m_bitmap = new CBitmap;
		m_bitmap->CreateCompatibleBitmap(pDC, rcBounds.Width(), rcBounds.Height());
		m_oldBitmap = SelectObject(m_bitmap);
		m_pDC = pDC;
		m_rcBounds = rcBounds;
	}
	//##ModelId=474D308601B6
	~CMemDC() 
	{
		m_pDC->BitBlt(m_rcBounds.left, m_rcBounds.top, m_rcBounds.Width(), m_rcBounds.Height(), 
					this, m_rcBounds.left, m_rcBounds.top, SRCCOPY);
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) 
			delete m_bitmap;
	}
	//##ModelId=474D308601E5
	CMemDC* operator->() 
	{
		return this;
	}
};

#endif
