
// WigglerMfcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WigglerMfc.h"
#include "WigglerMfcDlg.h"
#define _USE_MATH_DEFINES
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>
#include <Windows.h>

// CWigglerMfcDlg dialog

using namespace std;

#define WMU_NOTIFY_CLICK  (WM_USER + 200)
#define SHELL_NOTIFY_ICON_ID 100

vector<POINT> WiggleDeltas;

CWigglerMfcDlg::CWigglerMfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWigglerMfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CWigglerMfcDlg::~CWigglerMfcDlg(void)
{
}


void CWigglerMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWigglerMfcDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CWigglerMfcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWigglerMfcDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWigglerMfcDlg message handlers

BOOL CWigglerMfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	SetUpShellNotifyIcon();

	EXECUTION_STATE state = SetThreadExecutionState(ES_SYSTEM_REQUIRED|ES_DISPLAY_REQUIRED|ES_CONTINUOUS);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWigglerMfcDlg::SetUpShellNotifyIcon()
{
	NOTIFYICONDATA niData;
	ZeroMemory(&niData,sizeof(NOTIFYICONDATA));
     
	niData.cbSize = sizeof(niData);
	niData.hWnd   = this->m_hWnd;
	niData.uID    = SHELL_NOTIFY_ICON_ID;
	niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	niData.uVersion = NOTIFYICON_VERSION_4;
	//u could load ur own icon here
	niData.hIcon  = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
     
	//set the CALLBACK message ID
	niData.uCallbackMessage =  WMU_NOTIFY_CLICK; 
     
	//Adds our App. icon to the taskbar status area
	Shell_NotifyIcon( NIM_ADD, &niData);     
	Shell_NotifyIcon( NIM_SETVERSION, &niData);     
}

void CWigglerMfcDlg::DeleteShellNotifyIcon()
{
	NOTIFYICONDATA niData;
	ZeroMemory(&niData,sizeof(NOTIFYICONDATA));
     
	niData.cbSize = sizeof(niData);
	niData.hWnd   = this->m_hWnd;
	niData.uID    = SHELL_NOTIFY_ICON_ID;
     
	//Adds our App. icon to the taskbar status area
	Shell_NotifyIcon( NIM_DELETE, &niData);     
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWigglerMfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWigglerMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWigglerMfcDlg::OnBnClickedOk()
{
	ShowWindow(SW_HIDE);
}

void CWigglerMfcDlg::OnBnClickedCancel()
{
	if(m_TimerID)
	{
		KillTimer(m_TimerID);
	}

	EXECUTION_STATE state = SetThreadExecutionState(ES_CONTINUOUS);

	OnCancel();
}


void CWigglerMfcDlg::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	// using shared_ptr.  don't need this anymore
	//delete this;
}

void CWigglerMfcDlg::OnCancel()
{
	DeleteShellNotifyIcon();
	DestroyWindow();
}

void CWigglerMfcDlg::OnOk()
{
	OnCancel();
}

LRESULT CWigglerMfcDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message==WMU_NOTIFY_CLICK && LOWORD(lParam) == WM_LBUTTONUP)
	{
		TRACE("Sys tray icon(0x%04x) msg(0x%04x) clicked at %03d, %03d\r\n", HIWORD(lParam), LOWORD(lParam), GET_X_LPARAM(wParam), GET_Y_LPARAM(wParam));
		CRect WindowPos;
		GetWindowRect(&WindowPos);
		WindowPos.MoveToXY(GET_X_LPARAM(wParam)-WindowPos.Width(), GET_Y_LPARAM(wParam)-WindowPos.Height());
		MoveWindow(&WindowPos); 
		ShowWindow(SW_SHOW);
		SetFocus();
	}

	return CDialog::WindowProc(message, wParam, lParam);
}
