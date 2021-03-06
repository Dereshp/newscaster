// Widgie.h : main header file for the WIDGIE application
//

#if !defined(AFX_WIDGIE_H__31E48102_6B2B_4FFB_BBAE_8A43A3C50426__INCLUDED_)
#define AFX_WIDGIE_H__31E48102_6B2B_4FFB_BBAE_8A43A3C50426__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include <afxstr.h>
#include <atlimage.h> 
#include <afxtempl.h> 

#include "resource.h"		// main symbols
//#include "WidgieDlg.h"

#include "Splash.h"
#include "Picture.h"

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH       256
#endif



#define	CFG						( (CWidgieApp *)AfxGetApp( ) )

#define INI_FILE            	CFG->ini_file
#define ONE_SECOND          	1000
#define DEFAULT_LOOP        	"default_slideshow.xml"     // gotta put this in .ini file

#define	DEFAULT_LOGOFILE		"SplashLogo.jpg"
#define	SCROLLNEWSLOGO_FN		"news_logo_scroll.bmp"
#define	NEWSLOGO_FN				"news_logo.bmp"

#define DEFPATH_CONTENT			"Media\\"
#define DEFPATH_IMAGES			"Images\\"

#define	DEFURL_ARTWORK			"/content/"

// default local filenames
#define	DEFURL_NEWS				"newsflash.xml"
#define	DEFURL_MANIFEST			"manifest.xml"
#define	DEFURL_LOOPSEQ			"slideshow.xml"
#define	DEFURL_CONFIG			"config.xml"

#define	DEFURL_NATIONALNEWS		"http://ticker.seven.com.au/xml/news.xml"
#define	DEFURL_YAHOOTOPNEWS		"http://rss.news.yahoo.com/rss/topstories"
#define	DEFURL_YAHOOUSANEWS		"http://rss.news.yahoo.com/rss/us"
#define	DEFURL_YAHOOWORLDNEWS	"http://rss.news.yahoo.com/rss/world"
#define	DEFURL_BBCWORLDNEWS		"http://news.bbc.co.uk/rss/newsonline_world_edition/front_page/rss091.xml"

#define	XMLFN_NEWS				"/content/config/newsflash.xml"
#define	XMLFN_MANIFEST			"/content/config/manifest.xml"
#define	XMLFN_LOOPSEQ			"/plasmanet/webservices/imageviewer.asmx/GetSlideshow?"
#define	XMLFN_GETIMAGE			"/plasmanet/getimage.aspx"
#define	XMLFN_CONFIG			"/content/config/config.xml"

#define XMLFN_NATIONALNEWS		"sevennews.xml"
#define XMLFN_YAHOOWORLDNEWS	"yahootopnews.xml"
#define XMLFN_BBCWORLDNEWS		"bbcnews.xml"


#define	URL_MDID_GETSLIDESHOW	"/plasmanet/webservices/imageviewer.asmx/GetSlideshow?"
#define	URL_MDID_LOGIN			"/plasmanet/webservices/imageviewer.asmx/Login?"


/* ------------------  .ini default settings ------------------ 

[LOCAL MACHINE]
LocalXML_Dir = Config\
LocalContentDir = Media\

LocalNewsName = newsflash.xml
LocalLoopName = slideshow.xml
LocalManifestName = manifest.xml

RSSNews=1
ShowScrollLogo=0

[SERVER]
IP = 192.168.1.99
Port = 80;
IPandPort =192.168.1.99
ServerContentPath=/content/
ServerImagePath=/mdid2/getimage.aspx
ServerVideoPath=/content/video/
# this is used to log into the MDID system
Username = Client
Userpass = Client
slideshowid = Display_123344			( last 6 digits of MAC )


  ------------------------------------------------------------- */







void PrintDebugText( char *txt, int color=-1 );

/////////////////////////////////////////////////////////////////////////////
// CWidgieApp:
// See Widgie.cpp for the implementation of this class
//
#ifndef SM_CMONITORS
#define	SM_CMONITORS 80
#endif


class CWidgieApp : public CWinApp
{
public:
	CWidgieApp();
    CSplash m_splash;

    /* System Globals */
    CString cfgLanguage;
	CString cfgIniFilename;
	char ini_file[BUFFER_LENGTH];

	int running;


	int	cfgRuns;

    /* Graphics Globals */
    int cfgTop;                 // Top of MCCA screen (y co-ordinate)
    int cfgLeft;                // Left of MCCA screen (x co-ordinate)
    int cfgBottom;              // Bottom of MCCA screen (y co-ordinate)
    int cfgRight;               // Right of MCCA screen (x co-ordinate)
	virtual int cfgWidth()	{ return cfgRight-cfgLeft; };
	virtual int cfgHeight()	{ return cfgBottom-cfgTop; };

    int cfgMeterHeight;         // Height of the Taxi meter used when rendering 
                                // overlaped regions when the newsbar moves away
    
    int cfgBarHeight;           // Height of the news bar 

    int cfgTempBarHeight;       // When a new bar height is received it is stroed here
                                // because the graphics for the newsflash crashes if
                                // cfgBarHeight is modified while the newsflash thread
                                // is oprating. WidgieDlg handles the stopping and
                                // starting of the thread and the copying of this
                                // variable to cfgBarHeight.
                            

    int cfgNewsBarDelay;        // Delay used to animate rising and falling of
                                // newsbar. Delay in between moving the dialog by
                                // 1 pixel.
    
    int cfgNewsInterval;        // time that the newsbar stays hidden after it hides
    int cfgScrollSpeed;         // time interval that news scrolling is updated

    int cfgBackgroundColor;     // The colour to paint the background


	int cfgTextColor;           // newsbar text colour

    CString cfgFontFace;        // newsbar font face any True Type Font will work
		
    int cfgFontHeight;          // height of the newsflash font
		
	int cfgStepSpeed;           // home many pixels to advance the caption when scrolling  (ie its speed)

	BOOL cfgSaveBMPCache;
	BOOL cfgCacheSourceImages;	// cache decompressed source images in ram rather then reloading all the time.

	// ------- NEWS TICKERS
	BOOL cfgUseRSSNews;			// flag to decide if to use the news ticker directly, or not.

	BOOL cfgPreloadAllImages;
	BOOL cfgIgnoreEthernet;		// do use the ethernet as a download medium

	BOOL cfgScreenSaverMode;	// be a screen saver - do not talk to server hosts.
	BOOL cfgImageBlend;			// blend smoothly between two images

	BOOL cfgEnableHttpListen;	// enable the internal http listening server for debug/communications monitoring and media sharing

	BOOL cfgPurgeMissingMedia;	// remove missing media from play list if not found.
	BOOL cfgEnableLogs;			// enable debug/operations logs

	BOOL cfgVideoDownloadAlways;// Always try to download the video, even if it exists, but not if its the same size.
	BOOL cfgImagesDownloadAlways;// Always try to download the video, even if it exists, but not if its the same size.


	CString	cfgConfigVersion;	// version of XML config data being used , to decide if to download a new config.xml or not.
	CString	cfgConfigDate;		// the date of the config file creation on the server


    /* Local Machine paths */  
    CString cfgLocalBaseDir;    // Directory where all directories required
                                // by the MCCA can be found
    
    CString	cfgLocalContentDir;		// Directory relative to cfgLocalBaseDir where all  JPEG and Sockwave content can be found

	CString	cfgLocalImagesDir;		// Directory relative to cfgLocalBaseDir where all applications static default images are kept

    CString cfgLocalXML_Dir;        // Directory relative to cfgLocalBaseDir where   all XML files can be found

    CString	cfg_App_LogoFile;


    CString cfgLocalNewsName;       // name of file containing newsflash XML
    CString cfgLocalLoopName;       // name of file containing Loopsequence XML
    CString cfgLocalManifestName;   // name of file containing manifest XML

	/* Web Server Information */
	CString cfgIPandPort;           // Main Content Server Remote location
	CString cfgOriginalServer;      // Main Content Server Remote location (backup from ini file)
	BOOL	cfgServerIsLocal;		// true if we are located next to the server and dont have to go over the internet to get to it.
	CString cfgLocalName;			// the name of this computer.

	// --- Local Proxy server details
	CString cfgLocalServer;         // Main Content Server Local Master, Empty for the server
	CTime	m_LocalServerFoundTime;
	BOOL	cfgLocalServerReachable;

	/* Server Content paths */
    CString cfgServerContentPath;   // path on server, relative to URL, that contains
                                    // all JPEG and Shockwave Content
    CString cfgServerImagePath;		// URL that calls the cgi to get the image...
    CString cfgServerVideoPath;		// URL that calls the cgi to get the video file...

	CString	cfgServerSubmitURL;		// submitted url to send hit data.
    
	CString	cfgConfigFileName;		// name of file containing config data in XML
    CString cfgNewsFileName;        // name of file containing newsflash XML or  script that returns the file
	CString cfgManifestFileName;    // name of file containing manifest XML or  script that returns the file
	CString cfgLoopsequenceFileName;// name of file containing loopsequence XML or  script that returns the file
	CString	cfgGetImageFileName;	// url that defines how to retrieve and image via an ASP call

	CString	cfgMainLogoFileName;
	CString	cfgNewsLogoFileName;
	CString	cfgScrollLogoFileName;

	CString	cfgUpdateExe;

	int		cfgDefaultPlayLength;

    /* download configuration 
		we have a download interval for *ALL* data, which downloads everything if its a fast net connection, or ONLY
		the XML content if its GPRS modem connection.
		we also have a download interval for NEWS only downloads, which is more frequent than general downloads.
	
	*/
    CString		cfgDownloadIntervalTime;
    int			cfgDownloadIntervalDay;

	// main media times/intervals
	CTime		cfgLastDownloadTime;
    CTimeSpan	cfgDownloadInterval;

	// news download intervals/counters
	CTime		cfgNewsLastDownloadTime;		// last time we got the news.
	CTimeSpan	cfgNewsDownloadInterval;		// probly 3hrs or something.

	// specific news download timers... for "today", if used, += 24hrs
	CTime		cfgNewsNextDownloadTime1;		// last time we got the news.
	CTime		cfgNewsNextDownloadTime2;		// last time we got the news.
	CTime		cfgNewsNextDownloadTime3;		// last time we got the news.
	CString		cfgNewsDownloadTime1;
	CString		cfgNewsDownloadTime2;
	CString		cfgNewsDownloadTime3;

	CList<CString,CString> cfgNewsRSSFeeds;		// a list of rss news feeds definable besides the hardcoded above ones.

	// xml downloa periods...
	CTime		cfgXMLLastDownloadTime;			// last time we got the xml
	CTimeSpan	cfgXMLDownloadInterval;			// probly 12hrs or something.

	// upload intervals/counters
	CTime		cfgLastUploadTime;			// last time we got the news.
	CTimeSpan	cfgUploadInterval;			// 1 week, 24*7 or 1 hour (value is in seconds, 88640=1day)

	CTime		cfgShutDownTime;			// the time when to shut down each day.... be it 6pm or 11pm.

	CString		cfgID;						// our unique id that defines who we are... either generated or static.
	CString		cfgUsername;				// mdid login user name
	CString		cfgUserpass;				// mdid login pass word

	CString		cfgBrightnessDown;
	CString		cfgBrightnessUp;
	int			cfgBrightnessDownValue;
	int			cfgBrightnessUpValue;

	CString		cfgSleepStartTime;			// Time when to stop the animations and put monitor to sleep
	CString		cfgSleepStopTime;			// Time to restart anim and wakeup monitor

	CString		cfgRestartTime;				// restart program at X time "HH:MM"
	BOOL		cfgNoInternet;				// Do not talk to the internet.
	BOOL		cfgShutdownWhenIdle;
	BOOL		cfgRebootWhenIdle;
	BOOL		cfgExitWhenIdle;			// exit app and restart via start.bat
	BOOL		cfgExitAt3am;				// exit app at 3am and restart via start.bat

	BOOL		cfgNeverShutdown;
	BOOL		cfgShutdownActive;

	BOOL		cfgShowScrollLogo;
	BOOL		cfgUse2ndMonitor;			// Use the 2nd monitor to the max

	// ---------------------------------------------------------------------------------------------------------------------


	class CWidgieDlg	*m_mainDlg;
	int			appReturnCode;

	int			m_timetaken_ms;				// time taken for scroller to move

	void		ChangeIVAStatus( int x );
	int			m_ivaStatus;
	int			m_ivaStatusLast;
	int			m_ivaVersion;
	int			m_CallCount;
	int			m_CallBusyCount;
	int			m_CallNoAnswerCount;
	int			m_CallNoDialToneCount;

	// -------- TEMPERATURE DATA
#define	HD_TEMP_COUNT	60
	int			m_tempHD;					// temperature of HD
	int			m_tempHD_average;			// moving average of last hour
	int			m_tempHD_history[HD_TEMP_COUNT];		// 60 items worth (1 every 5mins)

	CString		m_TestingID;				// ID/name of the person testing the hardware.

	BOOL		m_logdebug;					// log all OutDebugs messages to debug.log

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWidgieApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWidgieApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CImage	SplashLogo;
    

public:
	BOOL	CheckLocalServer( void );
	void	DoButtonCommand( unsigned char key );
	int		ChooseAdminMenu(int menuSelected);
	void	SetAppPriority( int pri );
	CString	BuildStatusString();
	int		PrintText(char *text);
	int		PrintTextLarge(char *text);
	void	MuteCheck( int x );
	void	MuteHoldCheck( int secs );
	virtual const char *GetExeName() { return m_pszExeName; }

	BOOL	OpenSplashLogo( void );
	void SaveLoginDetails(void);
};



void RebootNow( void );
void ShutdownNow( void );
void DisplayMessageLine( CString message );
int globalCheckNetConnection(void);
int globalCheckNetAdaptors( CString *netip, CString *netname );
unsigned long HashIt(char *string, unsigned short len);
#define CHashStr( str )	HashIt( str.GetBuffer(0), str.GetLength() )
#include <afxtempl.h>
int ScanSubnetForDisplays( CList <CString,CString> *machinesP );

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIDGIE_H__31E48102_6B2B_4FFB_BBAE_8A43A3C50426__INCLUDED_)
