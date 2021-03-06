// NewsBarThread.cpp : implementation file
//

#include "stdafx.h"
#include "Widgie.h"
#include "NewsBarThread.h"
#include "newsflash.h"
#include "utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/** 
 *  CLASS NewsBarThread
 *  Implements a thread for newsbar dialog so that the 
 *  other components of the system do not effect the newsflash
 *  operation. 
 *
 *  The newsflash doesn't effect the operation of other components either
 *  
 *  This have been implemented in order to maintain real-time behaviour
 */


IMPLEMENT_DYNCREATE(NewsBarThread, CWinThread)



NewsBarThread::NewsBarThread()
{
	running = TRUE;
	shuttingDown = FALSE;
}

NewsBarThread::~NewsBarThread()
{
	OutDebugs( "NewsBarThread::~NewsBarThread()" );

	//OutDebugs( "NewsBarThread - Deleting newsbar window" );
	//CNewsBar.Hide();
	//CNewsBar.EndCleanup();
	//CNewsBar.logoDlg.DestroyWindow();
	//CNewsBar.DestroyWindow();
	OutDebugs( "NewsBarThread::~NewsBarThread() Done." );
}

/**
 *  Implements the event handler that is called when an new thread it created
 *
 *  creates a newsbar ans starts it operating.
 *
 *
 */

BOOL NewsBarThread::InitInstance()
{
	OutDebugs( "NewsBarThread::InitInstance() has started..." );

	/* Display the newsbar */	
	CNewsBar.Create(IDD_NEWSFLASH_DIALOG1, NULL);

//	while( (long)pAppData == 0xcdcdcdcd || (long)pAppData == 0 )
//		Sleep( 10 );		// wait a bit.... so parent can set the pAppData. (this is what you call an insurance policy, rather than 'trust')

    /* The give the newsbar a reference to the captions it is to display */
	CNewsBar.BindCaptions(&(*pAppData)->newsflashList);
	CNewsBar.BindSection(lpCRITICAL_SECTION);
    
	CNewsBar.ShowDialog();
	OutDebugs( "NewsBarThread::InitInstance() Completed." );
	return TRUE;
}

int NewsBarThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	OutDebugs("NewsBarThread::ExitInstance");    
	return CWinThread::ExitInstance();
}



#ifndef USE_PEEKMSG
BEGIN_MESSAGE_MAP(NewsBarThread, CWinThread)
	//{{AFX_MSG_MAP(NewsBarThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif


/////////////////////////////////////////////////////////////////////////////
// NewsBarThread message handlers


#ifdef USE_PEEKMSG
int NewsBarThread::Run()
{

	MSG mssg;

	// prime the message structure

	PeekMessage( &mssg, NULL, 0, 0, PM_NOREMOVE);

	// run till completed

	while (mssg.message!=WM_QUIT && running )
	{

		// is there a message to process?

		if (PeekMessage( &mssg, NULL, 0, 0, PM_REMOVE)) {

			// dispatch the message

			TranslateMessage(&mssg);
			DispatchMessage(&mssg);

		} else {

			// ### DO OUR SCROLLER HERE AS OFTEN AS POSSIBLE
			internalTimerProc( 0, 0, (DWORD)&CNewsBar, 0, 0 );
		}
	}
	return 0;
}
#endif


void NewsBarThread::Shutdown()
{
	OutDebugs("NewsBarThread::Shutdown() ...");
	shuttingDown = TRUE;

	if( CFG->cfgShowScrollLogo ) {
		CNewsBar.logoDlg.CloseWindow();
	}
	CNewsBar.EndCleanup();

	OutDebugs("NewsBarThread::Shutdown() ... Done");

	TerminateThread( this->m_hThread, 0 );
	running = FALSE;
}


/** 
 *  Destroys the newBar and the thread
 *
 *  A method that the main thread in the application can use to kill
 *  this thread and the CNewsBar
 *
 */

void NewsBarThread::Die()
{
	OutDebugs( "NewsBarThread - Die" );

//	CNewsBar.CloseWindow();
//	CNewsBar.DestroyWindow();

	//((NewsBarThread *)newsThread)->CNewsBar.DestroyWindow();
	//((NewsBarThread *)newsThread)->Delete();

	//AfxEndThread(1);
	OutDebugs( "NewsBarThread - running = FALSe" );
	running = FALSE;
	PostQuitMessage(0);
	ExitThread(0);
}


/**
 *  Initialised the pointer to newsflash data.
 *
 *  Once a newsflash is started a reference to the main threads newsflash data 
 *  structure is set using this function to ebale data sharing between threads.
 *
 */
void NewsBarThread::setAppData(CWidgieXML* pAppDataRef)
{
    pAppData = &pAppDataRef;
}


/** 
 *  Brings the newBar dialog to the top
 *
 *  A method that the main thread in the application can use to bring the 
 *  newsbar to the top
 *
 */
void NewsBarThread::BringToFront()
{
	OutDebugs( "NewsBarThread - BringToFront" );
    CNewsBar.BringWindowToTop();
	//CNewsBar.ShowLogo();
	CNewsBar.SetFocus();
}


void NewsBarThread::ShowNewsBar()
{
	OutDebugs( "NewsBarThread - ShowNewsBar" );
	CNewsBar.ShowDialog( TRUE );
}
