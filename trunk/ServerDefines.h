#pragma once


#define CHUNK_WRITE_SIZE 65536

//##ModelId=474D3024039B
class MyEnums
{
public:
	//##ModelId=474D30250010
	enum eSendType{START, DATA, DATA_START, DATA_END, END, EXIT, REQUEST_FILES};
};

//##ModelId=474D30250030
class CSendInfo
{
public:
	//##ModelId=474D3025005E
	CSendInfo()
	{
		memset(this, 0, sizeof(*this));
		m_nSize = sizeof(CSendInfo);
		m_nVersion = 1;
		m_lParameter1 = -1;
		m_lParameter2 = -1;
	}
	//##ModelId=474D3025005F
	int					m_nSize;
	//##ModelId=474D3025006F
	MyEnums::eSendType	m_Type;
	//##ModelId=474D3025008D
	int					m_nVersion;
	//##ModelId=474D3025008E
	CHAR				m_cIP[20];
	//##ModelId=474D3025009D
	CHAR				m_cComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	//##ModelId=474D302500AD
	CHAR				m_cDesc[250];
	//##ModelId=474D302500BC
	long				m_lParameter1;
	//##ModelId=474D302500CC
	long				m_lParameter2;
	//##ModelId=474D302500DB
	char				m_cExtra[50];
};

//##ModelId=474D302500FB
class CDittoCF_HDROP
{
public:
	//##ModelId=474D3025011A
	CDittoCF_HDROP()
	{
		memset(m_cIP, 0, sizeof(m_cIP));
		memset(m_cComputerName, 0, sizeof(m_cComputerName));
	}
	//##ModelId=474D3025011B
	char m_cIP[25];
	//##ModelId=474D3025012A
	char m_cComputerName[MAX_COMPUTERNAME_LENGTH + 1];
};
