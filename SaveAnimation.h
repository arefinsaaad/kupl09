#pragma once

//##ModelId=474D302602CF
class CSaveAnimation
{
public:
	//##ModelId=474D302602DF
	CSaveAnimation();
	//##ModelId=474D302602E0
	~CSaveAnimation(void);

	//##ModelId=474D302602F0
	void DoAnimation(CRect crStart, CRect crEnd, CWnd *pWnd);
	//##ModelId=474D3026031E
	void GetPercentages(long lMaxDist);
	//##ModelId=474D3026033D
	long GetMaxDistance();
	
	//##ModelId=474D3026034C
	CRect m_crStart;
	//##ModelId=474D3026034D
	CRect m_crEnd;

	//##ModelId=474D3026035C
	double m_dLeftPercent;
	//##ModelId=474D3026037B
	double m_dTopPercent;
	//##ModelId=474D3026037C
	double m_dRightPercent;
	//##ModelId=474D3026038B
	double m_dBottomPercent;

	//##ModelId=474D302603AA
	double m_dSpeed;
};
