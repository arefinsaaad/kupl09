// ==================================================================
// 
//  Path.h   
//  
//  Created:       03.03.2005
//
//  Copyright (C) Peter Hauptmann
//              
// ------------------------------------------------------------------
// 
/// \page pgDisclaimer Copyright & Disclaimer
/// 
/// Copyright (C) 2004-2005 Peter Hauptmann
///     all rights reserved
/// more info: http://www.codeproject.com/phShellPath.asp
/// Please contact the author with improvements / modifications.
/// 
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted under the following conditions: 
///     - Redistribution of source must retain the copyright above, 
///       and the disclaimer below.
///     - Modifications to the source should be marked clearly, to be 
///       distinguishable from the original sources.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
/// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
/// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
/// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
/// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
/// SUCH DAMAGE.
/// 


#ifndef FILE_PH_PATH_H_200506202_INCLUDED_
#define FILE_PH_PATH_H_200506202_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


#include <comdef.h> // for _bstr_t extractor only, can be removed if you don't need CPath::GetBStr()
#include "shlwapi.h"


#pragma once





/// The nsPath namespace contains the CPath class and global helper functions.
namespace nsPath
{

// ---------------- DECLARATIONS --------------------------------------------

    // ----- CString Helpers ---------
void  Trim(CString & s);                    
TCHAR GetFirstChar(CString const & s);      ///< returns the first char of the string, or 0 if the string length is 0.
TCHAR GetLastChar(CString const & s);       ///< returns the last char of the string, or 0 if the string length is 0.


TCHAR GetDriveLetter(TCHAR ch);
TCHAR GetDriveLetter(LPCTSTR s);

CString QuoteSpaces(CString const & str);


// ==================================================================
//  ERootType
// ------------------------------------------------------------------
/// 
/// Recognized root types for a path. 
/// see nsPath::GetRootType "GetRootType" for more.
/// 
/// \c len refers to the rootLen parameter optionally returned by \c GetRootType.
/// 
//##ModelId=474D3039039B
enum ERootType
{
	//##ModelId=474D303903BB
   rtNoRoot       =  0,    ///< no, or unknown root (\c len = 0)
	//##ModelId=474D303903C9
   rtDriveRoot    =  1,    ///< a drive specification with backslash ("C:\", \c len = 3)
	//##ModelId=474D303903D9
   rtDriveCur     =  2,    ///< a drive specification without backslash ("C:", \c len = 2)
//   rtPathRoot     =  3,    ///< a path root, i.e. staring with a single backslash (nyi, \c len = 1)
	//##ModelId=474D303A0001
   rtLongPath     =  4,    ///< a UNC long path specification (e.g. "\\?\C:\", \c len is length of path root + 4),  no distinction for "root / current" is made
	//##ModelId=474D303A0002
   rtServerOnly   =  5,    ///< a server only specification (e.g. "\\fileserv" or "\\fileserv\", \c len is the string length)
	//##ModelId=474D303A0010
   rtServerShare  =  6,    ///< server + share specification ("\\server\share", \c len includes the backslash after share if given)
	//##ModelId=474D303A0020
   rtProtocol     =  7,    ///< protocol, ("http://", \c len includes the "://" part)
	//##ModelId=474D303A0030
   rtPseudoProtocol = 8,   ///< pseudo protocol (no slahes) ("mailto:", \c len includes the colon)
	//##ModelId=474D303A003F
   rtServer         = 9,    ///< server with share following (for GetRootType(_,_,greedy=false)
};

ERootType GetRootType(LPCTSTR path, int * pLen, bool greedy = true); 



// ==================================================================
//  nsPath::EPathCleanup
// ------------------------------------------------------------------
/// Flags for nsPath::CPath::Cleanup
///
//##ModelId=474D303A007E
enum EPathCleanup
{
	//##ModelId=474D303A009D
    epcTrim             =   1,      ///< trim outer whitespace
	//##ModelId=474D303A00AD
    epcUnquote          =   2,      ///< remove single or double quotes
	//##ModelId=474D303A00AE
    epcTrimInQuote      =   4,      ///< trim whitespaces inside quotes
	//##ModelId=474D303A00BC
    epcCanonicalize     =   8,      ///< Canonicalize (collapse "\\..\\" and "\\.\\")
	//##ModelId=474D303A00CC
    epcRemoveXXL        =   16,     ///< Remove "\\\\?\\" and "\\\\?\\UNC\\" markers
	//##ModelId=474D303A00DB
    epcSlashToBackslash = 32,   ///< replace forward slashes with backslashes
	//##ModelId=474D303A00EB
    epcMakePretty       =   64,     ///< Windows' idea of a pretty path
	//##ModelId=474D303A00FB
    epcRemoveArgs       =  128,     ///< calls PathRemoveArgs (before trimming/unquoting)
	//##ModelId=474D303A010A
    epcRemoveIconLocation = 256,    ///< Remove Icon location from the path
	//##ModelId=474D303A011A
    epcExpandEnvStrings   = 512,    ///< Expand environment strings

	//##ModelId=474D303A011B
    epc_Default = epcTrim | 
                  epcUnquote | 
                  epcTrimInQuote | 
                  epcCanonicalize | 
                  epcRemoveXXL |
                  epcExpandEnvStrings, ///< default for CTors and Assignment operators
};


// ==================================================================
//  nsPath::EPathPacking
// ------------------------------------------------------------------
/// 
/// Flags for nsPath::CPath::GetStr
/// \note 
/// eppAutoQuote was ignored in Version 1.2 and before. 
/// It is fixed since V.1.3 (August 2005), /// but was removed from 
/// epp_Default for backward compatibility
///
//##ModelId=474D303A0149
enum EPathPacking
{
	//##ModelId=474D303A0159
    eppAutoQuote        =   1,      ///< Quote the path if it contains spaces
	//##ModelId=474D303A0168
    eppAutoXXL          =   2,      ///< If path length is > MAX_PATH, use "\\\\?\\" syntax
	//##ModelId=474D303A0169
    eppBackslashToSlash =   4,      ///< turn backslashes into forward slashes

	//##ModelId=474D303A0178
    epp_Default = eppAutoXXL,       
};




// ==================================================================
//  nsPath::CPath
// ------------------------------------------------------------------
/// 
/// 
///
//##ModelId=474D303B005E
class CPath
{
protected:
	//##ModelId=474D303B006E
    CString     m_path;
	//##ModelId=474D303B007E
    void        CAssign(CString const & src);

public:

    //@{ \name Construction
	//##ModelId=474D303B008E
    CPath()                     {}
	//##ModelId=474D303B008F
    CPath(LPCSTR path);             ///< Assigns \c path. CPath::Clean(epc_Default) is called for cleanup
	//##ModelId=474D303B00BC
    CPath(LPCWSTR path);            ///< Assigns \c path. CPath::Clean(epc_Default) is called for cleanup
	//##ModelId=474D303B00FB
    CPath(CString const & path);    ///< Assigns \c path  CPath::Clean(epc_Default) is called for cleanup
	//##ModelId=474D303B012A
    CPath(CPath const & path);      ///< Assigns \c path to the path. Does \b not modify the assigned path!
	//##ModelId=474D303B0158
    CPath(CString const & path, DWORD cleanup); ///< Assigns \c path, using custom cleanup options (see CPath::Clean)
    //@}


    //@{ \name Assignment
    CPath & operator=(LPCSTR rhs);  ///< Assigns \c path, and calls CPath::Clean(epc_Default)
    CPath & operator=(LPCWSTR rhs); ///< Assigns \c path, and calls CPath::Clean(epc_Default)

    CPath & operator=(CString const & rhs); ///< Assigns \c path, and calls CPath::Clean(epc_Default)
    CPath & operator=(CPath const & rhs);   ///< Assigns \c path Does \b not call CPath::Clean!
	//##ModelId=474D303B0187
    CPath & Assign(CString const & str, DWORD cleanup = epc_Default);
    //@}

    //@{ \name Miscellaneous Query
	//##ModelId=474D303B01C6
    operator LPCTSTR () const   { return m_path.operator LPCTSTR(); } 
	//##ModelId=474D303B01D6
    int      GetLength() const  { return m_path.GetLength(); }  ///< returns the length of the path, in characters
    //@}

    //@{ \name Path concatenation
	//##ModelId=474D303B01D8
    CPath & operator &=(LPCTSTR rhs);   
	//##ModelId=474D303B0204
    CPath & Append(LPCTSTR appendix);
	//##ModelId=474D303B0233
    CPath & AddBackslash();
	//##ModelId=474D303B0262
    CPath & RemoveBackslash();
    //@}

    //@{ \name Splitting into Path Segments
	//##ModelId=474D303B0281
    CString ShellGetRoot() const; 
	//##ModelId=474D303B02B0
    CPath   GetPath(bool includeRoot  = true) const;
	//##ModelId=474D303B02CF
    CString GetName() const;
	//##ModelId=474D303B02EF
    CString GetTitle() const;
	//##ModelId=474D303B030E
    CString GetExtension() const;
	//##ModelId=474D303B033D
    ERootType GetRootType(int * len = 0, bool greedy = true) const;
	//##ModelId=474D303B039B
    CString GetRoot(ERootType * rt = NULL, bool greedy = true) const;
	//##ModelId=474D303B03C9
    CString SplitRoot(ERootType * rt = NULL);
	//##ModelId=474D303C0010
    int     GetDriveNumber();
	//##ModelId=474D303C0020
    TCHAR   GetDriveLetter();
    //@}

    //@{ \name  Add / Modify / Remove parts
	//##ModelId=474D303C0030
    CPath & AddExtension(LPCTSTR extension, int len = -1);
	//##ModelId=474D303C004F
    CPath & RemoveExtension();
	//##ModelId=474D303C006E
    CPath & RenameExtension(LPCTSTR newExt);
	//##ModelId=474D303C008D
    CPath & RemoveFileSpec();
    //@}


    //@{ \name Cleanup
	//##ModelId=474D303C009D
    CPath & Trim();
	//##ModelId=474D303C00EB
    CPath & Unquote();
	//##ModelId=474D303C012A
    CPath & Canonicalize();
	//##ModelId=474D303C0168
    CPath & ShrinkXXLPath();
	//##ModelId=474D303C01A7
    CPath & MakePretty();
	//##ModelId=474D303C01E5
    CPath & Clean(DWORD cleanup = epc_Default);
    //@}


    //@{ \name Extractors (with special "packing")
	//##ModelId=474D303C0233
    CString GetStr(DWORD packing = epp_Default) const;
	//##ModelId=474D303C0291
    _bstr_t GetBStr(DWORD packing = epp_Default) const;
    //@}
    
    //@{ \name Static checking (not accessing file system, see also GetRootType)
	//##ModelId=474D303C02CF
    bool    IsValid() const;

	//##ModelId=474D303C02D1
    bool    IsDot() const;
	//##ModelId=474D303C02E0
    bool    IsDotDot() const;
	//##ModelId=474D303C02E2
    bool    IsDotty() const;    // IsDot || IsDotDot

	//##ModelId=474D303C02FF
    bool    MatchSpec(LPCTSTR spec);
	//##ModelId=474D303C031E
    bool    IsContentType(LPCTSTR contentType)  { return 0 != ::PathIsContentType(m_path, contentType); } ///< compare content type registered for this file, see also MSDN: PathIsContentType
	//##ModelId=474D303C032D
    bool    IsFileSpec()                { return 0 != ::PathIsFileSpec(m_path);         } ///< true if path does not contain backslash, see MSDN: PathIsFileSpec
	//##ModelId=474D303C032E
    bool    IsPrefix(LPCTSTR prefix)    { return 0 != ::PathIsPrefix(m_path, prefix);   } ///< checks if the path starts with a prefix like "C:\\", see MSDN: PathIsPrefix
	//##ModelId=474D303C033D
    bool    IsRelative()                { return 0 != ::PathIsRelative(m_path);         } ///< returns true if the path is relative, see MSDN: PathIsRelative
	//##ModelId=474D303C033E
    bool    IsRoot()                    { return 0 != ::PathIsRoot(m_path);             } ///< returns true if path is a directory root, see MSDN: PathIsRoot
	//##ModelId=474D303C034C
    bool    IsSameRoot(LPCTSTR other)   { return 0 != ::PathIsSameRoot(m_path, other);  } ///< returns true if the path has the same root as \c otherPath, see MSDN: IsSameRoot

	//##ModelId=474D303C034E
    bool    IsUNC()                     { return 0 != ::PathIsUNC(m_path);              } ///< returns true if the path is a UNC specification, see MSDN: PathIsUNC
	//##ModelId=474D303C035C
    bool    IsUNCServer()               { return 0 != ::PathIsUNCServer(m_path);        } ///< returns true if the path is a UNC server specification, see MSDN: PathIsUNCServer
	//##ModelId=474D303C035D
    bool    IsUNCServerShare()          { return 0 != ::PathIsUNCServerShare(m_path);   } ///< returns true if the path is a UNC server + share specification, see MSDN: PathIsUNCServerShare
	//##ModelId=474D303C036C
    bool    IsURL()                     { return 0 != ::PathIsURL(m_path);              } ///< returns true if the path is an URL, see MSDN: PathIsURL

//  bool    IsHTMLFile()                { return 0 != ::PathIsHTMLFile(m_path);         } ///< (missing?) true if content type registered for this file is HTML, see MSDN: PathIsHTMLFile
//  bool    IsLFNFileSpec()             { return 0 != ::PathISLFNFileSpec(m_path);      } ///< (missing?) true if file is not a 8.3 file, see MSDN: PathIsLFNFileSpec
//  bool    IsNetworkPath()             { return 0 != ::PathIsNetworkPath(m_path);      } ///< (missing?) returns true if the path is on a network,  see MSDN: PathIsNetworkPath

    //@}


    //@{ \name Relative Paths
	//##ModelId=474D303C036D
    CPath   GetCommonPrefix(LPCTSTR secondPath);
	//##ModelId=474D303C037B
    CPath   RelativePathTo(LPCTSTR pathTo, bool srcIsDir = true);
	//##ModelId=474D303C039B
    bool    MakeRelative(CPath const & basePath);
	//##ModelId=474D303C03AA
    bool    MakeAbsolute(CPath const & basePath);
    //@}

    //@{ \name Dialog control operations
	//##ModelId=474D303C03BA
    CString GetCompactStr(HDC dc, UINT dx, DWORD eppFlags = 0);
	//##ModelId=474D303C03D9
    CString GetCompactStr(UINT cchMax, DWORD eppFlags = 0, DWORD flags = 0);
	//##ModelId=474D303D0002
    void    SetDlgItem(HWND dlg, UINT dlgCtrlID, DWORD eppFlags = 0);
    //@}


    //@{ \name File System / Environment-Dependent operations
	//##ModelId=474D303D0020
    CPath & SearchAndQualify();
	//##ModelId=474D303D0030
    CPath & FindOnPath(LPCTSTR * additionalDirs = 0);
	//##ModelId=474D303D0032
    bool    Exists() const;
	//##ModelId=474D303D0040
    bool    IsDirectory() const;
	//##ModelId=474D303D004F
    bool    IsSystemFolder(DWORD attrib = FILE_ATTRIBUTE_SYSTEM) const;
	//##ModelId=474D303D005E
    CPath & MakeSystemFolder(bool make = true);
	//##ModelId=474D303D006E
    DWORD   GetAttributes();
	//##ModelId=474D303D006F
    bool    GetAttributes(WIN32_FILE_ATTRIBUTE_DATA & fad);
	//##ModelId=474D303D007E
    CPath & MakeFullPath(); 
	//##ModelId=474D303D007F
    CPath & ExpandEnvStrings();
	//##ModelId=474D303D008D
    bool    EnvUnexpandRoot(LPCTSTR envVar);
	//##ModelId=474D303D009E
    bool    EnvUnexpandDefaultRoots();
	//##ModelId=474D303D00AD
    long    ToRegistry(HKEY baseKey, LPCTSTR subkey, LPCTSTR name, bool replaceEnv = true);
    //@}



    

// TODO: Shell 5.0 support
// V5:    CPath & UnexpandEnvStrings();
// V5:    LPCTSTR FindSuffixArray(LPCTSTR suffixes, int numSuffixes);
// V5:    void    PathUndecorate();
// V5:    CPath PathCreateFromURL(LPCTSTR path, DWORD dwReserved = 0);
// V5:    bool    IsDirectoryEmpty() const;
// might be useful for later extensions: PathGetCharType


};

// creation functions:
CPath SplitArgs(CString const & path_args, CString * args = NULL, DWORD cleanup = epc_Default);
CPath SplitIconLocation(CString const & path_icon, int * pIcon = NULL, DWORD cleanup = epc_Default);
CPath BuildRoot(int driveNumber);
CPath GetModuleFileName(HMODULE module = NULL);
CPath GetCurrentDirectory();
CPath FromRegistry(HKEY baseKey, LPCTSTR subkey, LPCTSTR name);


CString ReplaceInvalid(CString const & str, TCHAR replaceChar = '_');


// concatenation 

inline CPath operator & (CPath const & lhs, LPCTSTR rhs) { CPath ret = lhs; ret &= rhs; return ret; }







// ---------------- INLIME IMPLEMENTATIONS ----------------------------------

// ==============================================
// GetFirstChar
// ----------------------------------------------
/// \return [TCHAR]: the first char of the string, or 0 if the string length is 0.
/// \note The implementation takes care that the string is not copied when there are no spaces.
inline TCHAR GetFirstChar(CString const & s)
{
    if (s.GetLength() == 0)
        return 0;
    else
        return s[0];
}

// ==============================================
// GetLastChar
// ----------------------------------------------
/// \return [TCHAR]: the last character in the string, or 0 if the string length is 0.
/// \par Note
/// \b MBCS: if the string ends with a Multibyte character, this 
/// function returns the lead byte of the multibyte sequence.
inline TCHAR GetLastChar(CString const & s)
{
    LPCTSTR pstr = s;
    LPCTSTR pLastChar = _tcsdec(pstr, pstr + s.GetLength());
    if (pLastChar == NULL)
        return 0;
    else 
        return *pLastChar;
}





} // namespace nsPath




#endif // FILE_PH_PATH_H_200506202_INCLUDED_
