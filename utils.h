#if !defined(_UTILS_H__)
#define _UTILS_H__

#define TIME_SEPARATOR      ':'
#define DATE_SEPARATOR      '-'



#ifdef __cplusplus
extern "C" {
#endif

unsigned long HashIt(char *string, unsigned short len, unsigned long startingh );

BOOL fileExists( char *localFilename );
long fileSize( char *localFilename );

void TouchFile( CString filename );

char *GetLastErrorString( void );

char *mystrstr(const char * str, const char * pat );
size_t strcpyx( char *s1, char *s2, char brkch, size_t words );
int strcmpd(const char * str1, const char * str2);

void ExtractUserFromURL( char *url, char *server, char *username, char *passwd, char *file );
long ReplaceStr( char *srcstring, char *newstring, const char *key, const char *newkey, short wordflag );


long HexStr2UBYTE( const char *str );
long HexStr2int( const char *str );

long OutDebug( const char *txt );
long OutDebugs( const char *txt, ... );

#ifdef __cplusplus
}
#endif


CString URLGetPort( CString domain, long *port );

unsigned long CHashIt( CString str );
unsigned long CHashFile( CString filename );

CString LoadFileintoCString( CString filename );

int zipUpFileX( CString sourcefile, CString zfilename, CString filename );
long GZipCompressFiles( char *sourcefile  );
int GetDirectoryList( char *szTempFile, CList <CString,CString> &fileList );

CString CryptCString( CString txt, int magickey );

CString GetLastDebugMsg( void );

BOOL FileExists( CString localFilename );

CString DecreaseFilenameVersion( CString filename );

CTime TodaysNewTime( char *todaysTimeStr );

CTime TimeDateToCTime(CString timeString, CString dateString);

CTimeSpan TimeDateToCTimeSpan(CString timeString, int days);

void ExtractDate(CString* dateString, int* pYear, int* pMonth, int* pDay);

void ExtractTime(CString* timeString, int* pHour, int* pMinute, int* pSecond);



#endif //_UTILS_H__