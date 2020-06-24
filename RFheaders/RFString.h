/************************************************************************/
/* RFString.h                                                           */
/* Native C++ string operation library                                  */
/*                                                                      */
/* (C) 2012, RIFTEK LLC.                                                */
/*                                                                      */
/* Version: 0.1.0.0 May.31.2012                                         */
/*                                                                      */
/* Change history:                                                      */
/* May.31.2012 Version 0.1.0.0                                          */
/* * Initial version                                                    */
/*                                                                      */
/************************************************************************/

#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

//#pragma warning (disable:4996)

#ifdef __BORLANDC__
	#define _strlwr strlwr
	#define _strupr strupr
#endif

#ifdef __linux__
char *_strlwr(char*);
char *_strupr(char*);
#endif

typedef struct _RFStringList
{
	size_t uLength;
	char *szString;
	struct _RFStringList *pNext;
} RFStringList;

/*! \class RFString
 * \brief Class for operating strings using native C++
 * \details Implements a set of methods to manipulate text strings
 */
class RFString
{
public:
	RFString(void);
	explicit RFString(const char *szString);
	~RFString(void);

	/*! \fn void SetBuffer(char *szBuffer)
	 * \brief Copy value of szBuffer char array to internal buffer
	 * \details Function copies a value of zero-terminated char array to the internal buffer of RFString
	 * Next line to detailed info
	 * \param szBuffer source char array
	 * \return void : n/a
	 */
	inline void SetBuffer(char *szBuffer) {m_szBuffer = szBuffer; m_uBufferLength=strlen(szBuffer);}
	inline char *GetBuffer(void) {return m_szBuffer;}
	inline int toInt(void) {return atoi(m_szBuffer);}
	inline double toFloat(void) {return atof(m_szBuffer);}
	inline char *toLowercase(void) {return _strlwr(m_szBuffer);}
	inline char *toUppercase(void) {return _strupr(m_szBuffer);}
	inline size_t GetBufferLength(void) {return m_uBufferLength;}
	inline int GetSubstringCount(void) {return m_iSubstrings;}
	void SetBuffer(const char *szBuffer);
	int Split(const char *szDelimiter, bool bCaseSensetive = true);
	int Split(const char cDelimiter);
	int Find(const char *szStringToFind, bool bCaseSensetive = true);
	int Find(const char *szStringToFind, size_t uPos = 0, bool bCaseSensetive = true);
	bool Equal(const char *szStringToMatch, bool bCaseSensetive = true);
	int Member(const char *szSubstring, bool bCaseSensetive = true);
	RFString *GetNthSubstring(int iIndex);
	inline RFString *LeftStr(size_t uChars) {return MidStr(0, uChars);}
	inline RFString *RightStr(size_t uChars) {return MidStr(m_uBufferLength-(uChars+1), uChars);}
	RFString *MidStr(size_t uStart, size_t uLength);
	int Replace(const char cFind, const char cReplace);

	void operator=(const char* szString) {SetBuffer(szString);}
	bool operator==(RFString& s) {return (Equal((const char*)s.GetBuffer()));}
	bool operator==(const char* szString) {return (Equal(szString));}

private:
	size_t m_uBufferLength;
	char *m_szBuffer;
	RFStringList *m_pSubstrings;
	int m_iSubstrings;
	RFStringList *m_pCursor;
	bool m_bPrivateBuffer;

	void init();
	int AddSubstring(size_t uStart, size_t uEnd);
	void EmptyStringList(void);
	char *allocStr(size_t size);
	int internalFind(const char *szStringToFind, bool bCaseSensetive, bool bInternalCall);
	int internalFind(const char *szStringToFind, size_t uPos, bool bCaseSensetive, bool bInternalCall);
};

#if defined(__cplusplus)
}
#endif

