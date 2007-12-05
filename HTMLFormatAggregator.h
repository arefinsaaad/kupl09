#pragma once
#include "IClipAggregator.h"

//##ModelId=474D3063039B
class CHTMLFormatAggregator : public IClipAggregator
{
public:
	//##ModelId=474D306303D9
	CHTMLFormatAggregator(CStringA csSepator);
	//##ModelId=474D30640001
	~CHTMLFormatAggregator(void);

	//##ModelId=474D30640010
	virtual bool AddClip(LPVOID lpData, int nDataSize, int nPos, int nCount);
	//##ModelId=474D3064004F
	virtual HGLOBAL GetHGlobal();

protected:
	//##ModelId=474D3064009D
	CStringA m_csSeparator;
	//##ModelId=474D306400AE
	CStringA m_csNewText;
	//##ModelId=474D306400BD
	CStringA m_csSourceURL;
	//##ModelId=474D306400CD
	CStringA m_csVersion;
};

//##ModelId=474D306400FB
class CHTMFormatStruct
{
public:
	//##ModelId=474D3064011A
	CHTMFormatStruct()
	{
		m_lStartHTML = 0;
		m_lEndHTML = 0;
		m_lStartFragment = 0;
		m_lEndFragment = 0;
	}

	//##ModelId=474D3064011B
	bool GetData(LPCSTR HTML);
	//##ModelId=474D3064012B
	bool Serialize(CStringA &csHTMLFormat);

	//##ModelId=474D3064014A
	const CStringA &GetFragment() { return m_csFragment; }
	//##ModelId=474D30640178
	const CStringA &GetURL()	  { return m_csSourceURL; }
	//##ModelId=474D30640179
	const CStringA &GetVersion()  { return m_csVersion; }

	//##ModelId=474D3064017A
	void SetFragment(const CStringA &cs){ m_csFragment = cs; }
	//##ModelId=474D30640188
	void SetURL(const CStringA &cs)		{ m_csSourceURL = cs; }
	//##ModelId=474D30640198
	void SetVersion(const CStringA &cs)	{ m_csVersion = cs; }

protected:
	//##ModelId=474D306401B7
	CStringA m_csVersion;
	//##ModelId=474D306401C6
	long m_lStartHTML;
	//##ModelId=474D306401D5
	long m_lEndHTML;
	//##ModelId=474D306401E5
	long m_lStartFragment;
	//##ModelId=474D306401F5
	long m_lEndFragment;
	//##ModelId=474D30640205
	CStringA m_csSourceURL;
	//##ModelId=474D30640217
	CStringA m_csFragment;
};
