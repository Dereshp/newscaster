// AVI PlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vfw.h"
#include "Widgie.h"
#include "WidgieDlg.h"
#include "AVI PlayerDlg.h"
#include "playwnd.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAVIPlayerDlg dialog

CAVIPlayerDlg::CAVIPlayerDlg(CWnd* pParent /*=NULL*/) : CDialog(CAVIPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAVIPlayerDlg)
	m_Path = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_MCIVideo = NULL;
	m_playCount = 0;
	dlgVisible = FALSE;
}

void CAVIPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAVIPlayerDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAVIPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CAVIPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	 
	ON_MESSAGE(WM_GRAPHNOTIFY, OnGraphNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVIPlayerDlg message handlers


LRESULT CAVIPlayerDlg::OnGraphNotify( WPARAM wp, LPARAM lp )
{
	HandleGraphEvent();
	return NULL;
}



BOOL CAVIPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	OutDebugs( "CAVIPlayerDlg/OnInitDialog - this wnd = %08lx", this->m_hWnd );

	if( this->m_hWnd )
	{
		//Hide();
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

CAVIPlayerDlg::~CAVIPlayerDlg()
{
	OutDebugs( "CAVIPlayerDlg Deconstructing" );
}


void CAVIPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CAVIPlayerDlg::OnClose()
{
	//OutDebugs( "CAVIPlayerDlg OnClose called" );

	EndVideo();

	CDialog::OnClose();
}


//
//
// ##### ON TIMER
//
//
void CAVIPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// ####################### MCI WINDOW HANDLER
	if( m_MCIVideo )
	{
		// TODO: Add your message handler code here and/or call default
		if( MCIWndGetPosition(m_MCIVideo) >= m_length )
		{
			EndVideo();
		} else 
		if( MCIWndGetPosition(m_MCIVideo) > 1 && dlgVisible == FALSE )
		{
			ShowDialog();
		}
	}
//	((CWidgieDlg *) GetParent())->HideNewsLogo();

	CDialog::OnTimer(nIDEvent);
}



// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAVIPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAVIPlayerDlg::OnQueryDragIcon()
{
	return NULL;//(HCURSOR) m_hIcon;
}



// -------------------------------------------------------------------------------------------------------------------------------------





void CAVIPlayerDlg::ResetTimer()
{
    this->KillTimer(1);
    this->SetTimer(1, 250, NULL);
}


void CAVIPlayerDlg::EndVideo( void ) 
{
	this->KillTimer(1);

	((CWidgieDlg *) GetParent())->StopMoviePlayback();

	moviePlaying = FALSE;

	//Hide();
}


void CAVIPlayerDlg::StartMCIPlay() 
{
	if(m_MCIVideo == NULL)
	{
		m_MCIVideo = MCIWndCreate(this->GetSafeHwnd(),
		  AfxGetInstanceHandle(),
		  WS_CHILD | WS_VISIBLE|MCIWNDF_NOMENU|MCIWNDF_NOPLAYBAR|MCIWNDF_NOTIFYPOS,m_Path);

		if( m_MCIVideo )
		{
			moviePlaying = TRUE;

			RECT rc = { 0,0, 0,0 };
			rc.bottom = CFG->cfgHeight();
			rc.right = CFG->cfgWidth();

			::ShowWindow( m_MCIVideo, SW_SHOW );
			::MoveWindow( m_MCIVideo, 0,0, CFG->cfgWidth(),CFG->cfgHeight(), FALSE );
			::InvalidateRect( m_MCIVideo, &rc, TRUE );
		}
	}
	else
	{
		MCIWndHome(m_MCIVideo);
	}

	m_length = MCIWndGetLength(m_MCIVideo);
	MCIWndPlay(m_MCIVideo);
	m_playCount++;

	::MoveWindow( m_MCIVideo, 1,0, CFG->cfgWidth(),CFG->cfgHeight(), FALSE );
}




void CAVIPlayerDlg::OnPlay() 
{
	m_MCIVideo = NULL;

	moviePlaying = TRUE;
	//StartMCIPlay();

	MoveWindow( -CFG->cfgRight,0, CFG->cfgWidth(),CFG->cfgHeight()-CFG->cfgBarHeight, FALSE );

	StartDirectXPlay( this->m_hWnd, m_Path.GetBuffer(0), CFG->cfgWidth(), CFG->cfgHeight() );

	// TODO: Add your control notification handler code here
	MoveWindow( 0,0, CFG->cfgWidth(),CFG->cfgHeight()-CFG->cfgBarHeight, FALSE );

	ResetTimer();

	dlgVisible = FALSE;
	Pause = FALSE;
}

void CAVIPlayerDlg::OnPause() 
{
	// TODO: Add your control notification handler code here
	if(Pause)
	{
		if( m_MCIVideo )
			MCIWndResume(m_MCIVideo);
		else
			PauseClip();
		Pause = FALSE;
	}
	else
	{
		if( m_MCIVideo )
			MCIWndPause(m_MCIVideo);
		else
			PauseClip();
		Pause = TRUE;
	}
}

void CAVIPlayerDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if( m_MCIVideo )
	{
		MCIWndDestroy(m_MCIVideo);
		OnOK();
	}
	CDialog::OnCancel();
}

void CAVIPlayerDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	if( m_MCIVideo )
	{
		MCIWndStop( m_MCIVideo );
		MCIWndDestroy( m_MCIVideo );
	} else
		CloseClip();
	moviePlaying = FALSE;
}


void CAVIPlayerDlg::Hide() 
{
	//if( dlgVisible )
	{

		MoveWindow( CFG->cfgLeft, CFG->cfgTop-CFG->cfgHeight(), 
					CFG->cfgWidth(), CFG->cfgHeight(), FALSE );
		RECT rc = { 0,0, CFG->cfgWidth(), CFG->cfgHeight() };

		//ShowWindow( SW_HIDE );

		InvalidateRect( &rc, FALSE );

		//ShowWindow( SW_HIDE );

		//((CWidgieDlg *) GetParent())->ShowNewsDialog();

		dlgVisible = FALSE;
	}
}

void CAVIPlayerDlg::ShowDialog() 
{
	dlgVisible = TRUE;
	((CWidgieDlg *) GetParent())->HideNewsLogo();

	MoveWindow( CFG->cfgLeft, CFG->cfgTop, 
				CFG->cfgWidth(), CFG->cfgHeight()-CFG->cfgBarHeight, FALSE );

	RECT rc = { -1,1, CFG->cfgWidth(), CFG->cfgHeight()-CFG->cfgBarHeight };

	ShowWindow( SW_SHOW );

	InvalidateRect( &rc, FALSE );


	((CWidgieDlg *) GetParent())->HideNewsLogo();

	// --------------------- MCI SHOW
	if( m_MCIVideo )
	{
		RECT rc = { 0,0, CFG->cfgWidth(), CFG->cfgHeight() };

		if( m_MCIVideo )
		{
			::BringWindowToTop(m_MCIVideo);
			::MoveWindow( m_MCIVideo, 0,0, CFG->cfgWidth(),CFG->cfgHeight(), FALSE );
			::ShowWindow( m_MCIVideo, SW_SHOW );
			::InvalidateRect( m_MCIVideo, &rc, FALSE );
		}
		MCIWndRealize( m_MCIVideo, FALSE );
	}

}

