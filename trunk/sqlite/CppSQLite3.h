////////////////////////////////////////////////////////////////////////////////
// CppSQLite3 - A C++ wrapper around the SQLite3 embedded database library.
//
// Copyright (c) 2004 Rob Groves. All Rights Reserved. rob.groves@btinternet.com
// 
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without a written
// agreement, is hereby granted, provided that the above copyright notice, 
// this paragraph and the following two paragraphs appear in all copies, 
// modifications, and distributions.
//
// IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
// PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF
// ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS". THE AUTHOR HAS NO OBLIGATION
// TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
// V3.0		03/08/2004	-Initial Version for sqlite3
//
// V3.1		16/09/2004	-Implemented getXXXXField using sqlite3 functions
//						-Added CppSQLiteDB3::tableExists()
////////////////////////////////////////////////////////////////////////////////
#ifndef _CppSQLite3_H_
#define _CppSQLite3_H_

#include "sqlite3.h"
#include <cstdio>
#include <cstring>

#define CPPSQLITE_ERROR 1000

#ifdef _UNICODE
	#define SQLITE3_ERRMSG(mpDB) const TCHAR* szError = (const TCHAR*)sqlite3_errmsg16(mpDB)
#else							
	#define SQLITE3_ERRMSG(mpDB) const TCHAR* szError = sqlite3_errmsg(mpDB)
#endif		

int sqlite3_encode_binary(const unsigned char *in, int n, unsigned char *out);
int sqlite3_decode_binary(const unsigned char *in, unsigned char *out);

//##ModelId=474D306E030E
class CppSQLite3Exception
{
public:

	//##ModelId=474D306E031E
    CppSQLite3Exception(const int nErrCode,
                    TCHAR* szErrMess,
                    bool bDeleteMsg=true);

	//##ModelId=474D306E034C
    CppSQLite3Exception(const CppSQLite3Exception&  e);

	//##ModelId=474D306E036C
    virtual ~CppSQLite3Exception();

	//##ModelId=474D306E038B
    const int errorCode() { return mnErrCode; }

	//##ModelId=474D306E039B
    const TCHAR* errorMessage() { return mpszErrMess; }

	//##ModelId=474D306E039C
    static const TCHAR* errorCodeAsString(int nErrCode);

private:

	//##ModelId=474D306E03C9
    int mnErrCode;
	//##ModelId=474D306E03D9
    TCHAR mpszErrMess[1000];
};

//##ModelId=474D306F009D
class CppSQLite3Query
{
public:

	//##ModelId=474D306F00BC
    CppSQLite3Query();

	//##ModelId=474D306F00DB
    CppSQLite3Query(const CppSQLite3Query& rQuery);

	//##ModelId=474D306F012A
    CppSQLite3Query(sqlite3* pDB,
				sqlite3_stmt* pVM,
                bool bEof,
                bool bOwnVM=true);

	//##ModelId=474D306F0158
    CppSQLite3Query& operator=(const CppSQLite3Query& rQuery);

	//##ModelId=474D306F0178
    virtual ~CppSQLite3Query();

	//##ModelId=474D306F0197
    int numFields();

	//##ModelId=474D306F01B6
    int fieldIndex(const TCHAR* szField);
	//##ModelId=474D306F01D5
    const TCHAR* fieldName(int nCol);

	//##ModelId=474D306F01F5
    const TCHAR* fieldDeclType(int nCol);
	//##ModelId=474D306F0214
    int fieldDataType(int nCol);

	//##ModelId=474D306F0233
    const TCHAR* fieldValue(int nField);
	//##ModelId=474D306F0243
    const TCHAR* fieldValue(const TCHAR* szField);

	//##ModelId=474D306F0272
    int getIntField(int nField, int nNullValue=0);
	//##ModelId=474D306F0291
    int getIntField(const TCHAR* szField, int nNullValue=0);

	//##ModelId=474D306F02FE
    double getFloatField(int nField, double fNullValue=0.0);
	//##ModelId=474D306F031E
    double getFloatField(const TCHAR* szField, double fNullValue=0.0);

	//##ModelId=474D306F033D
    const TCHAR* getStringField(int nField, const TCHAR* szNullValue=_T(""));
	//##ModelId=474D306F036C
    const TCHAR* getStringField(const TCHAR* szField, const TCHAR* szNullValue=_T(""));

	//##ModelId=474D306F039B
    const unsigned char* getBlobField(int nField, int& nLen);
	//##ModelId=474D306F03C9
    const unsigned char* getBlobField(const TCHAR* szField, int& nLen);

	//##ModelId=474D306F03D9
	int getBlobFieldSize(const TCHAR* szField);
	//##ModelId=474D30700030
	int getBlobFieldSize(int nField);

	//##ModelId=474D3070004F
    bool fieldIsNull(int nField);
	//##ModelId=474D3070006E
    bool fieldIsNull(const TCHAR* szField);

	//##ModelId=474D3070008D
    bool eof();

	//##ModelId=474D307000AD
    void nextRow();

	//##ModelId=474D307000BC
    void finalize();

private:

	//##ModelId=474D307000DB
    void checkVM();

	//##ModelId=474D30700169
	sqlite3* mpDB;
	//##ModelId=474D30700188
    sqlite3_stmt* mpVM;
	//##ModelId=474D30700197
    bool mbEof;
	//##ModelId=474D307001B6
    int mnCols;
	//##ModelId=474D307001D5
    bool mbOwnVM;
};

//##ModelId=474D30700272
class CppSQLite3Statement
{
public:

	//##ModelId=474D307002A1
    CppSQLite3Statement();

	//##ModelId=474D307002B0
    CppSQLite3Statement(const CppSQLite3Statement& rStatement);

	//##ModelId=474D307002C0
    CppSQLite3Statement(sqlite3* pDB, sqlite3_stmt* pVM);

	//##ModelId=474D307002EF
    virtual ~CppSQLite3Statement();

	//##ModelId=474D3070030E
    CppSQLite3Statement& operator=(const CppSQLite3Statement& rStatement);

	//##ModelId=474D3070033D
    int execDML();

	//##ModelId=474D3070034C
    CppSQLite3Query execQuery();

	//##ModelId=474D3070036C
    void bind(int nParam, const TCHAR* szValue);
	//##ModelId=474D307003D9
    void bind(int nParam, const int nValue);
	//##ModelId=474D30710020
    void bind(int nParam, const double dwValue);
	//##ModelId=474D3071005E
    void bind(int nParam, const unsigned char* blobValue, int nLen);
	//##ModelId=474D3071009D
    void bindNull(int nParam);

	//##ModelId=474D307100BD
    void reset();

	//##ModelId=474D307100CC
    void finalize();

private:

	//##ModelId=474D307100DB
    void checkDB();
	//##ModelId=474D307100FB
    void checkVM();

	//##ModelId=474D3071010B
    sqlite3* mpDB;
	//##ModelId=474D3071011B
    sqlite3_stmt* mpVM;
};


//##ModelId=474D307101B6
class CppSQLite3DB
{
public:

	//##ModelId=474D307101E5
    CppSQLite3DB();

	//##ModelId=474D307101F5
    virtual ~CppSQLite3DB();

	//##ModelId=474D30710204
    void open(const TCHAR* szFile);

	//##ModelId=474D30710224
    bool close();

	//##ModelId=474D30710243
	bool tableExists(const TCHAR* szTable);

	//##ModelId=474D30710262
	int execDMLEx(LPCTSTR szSQL,...);
	//##ModelId=474D30710292
    int execDML(const TCHAR* szSQL);

	//##ModelId=474D307102B0
	CppSQLite3Query execQueryEx(LPCTSTR szSQL,...);
	//##ModelId=474D307102CF
    CppSQLite3Query execQuery(const TCHAR* szSQL);

	//##ModelId=474D307102EF
	int execScalarEx(LPCTSTR szSQL,...);
	//##ModelId=474D3071030E
    int execScalar(const TCHAR* szSQL);

	//##ModelId=474D3071031E
    CppSQLite3Statement compileStatement(const TCHAR* szSQL);

	//##ModelId=474D3071032D
    sqlite_int64 lastRowId();

	//##ModelId=474D3071035C
    void interrupt() { sqlite3_interrupt(mpDB); }

	//##ModelId=474D3071035D
    void setBusyTimeout(int nMillisecs);

	//##ModelId=474D3071037B
    static const TCHAR* SQLiteVersion() { return _T(SQLITE_VERSION); }

private:

	//##ModelId=474D3071039C
    CppSQLite3DB(const CppSQLite3DB& db);
	//##ModelId=474D307103AA
    CppSQLite3DB& operator=(const CppSQLite3DB& db);

	//##ModelId=474D307103C9
    sqlite3_stmt* compile(const TCHAR* szSQL);

	//##ModelId=474D307103DA
    void checkDB();

	//##ModelId=474D30720002
    sqlite3* mpDB;
	//##ModelId=474D30720020
    int mnBusyTimeoutMs;
};

#endif
