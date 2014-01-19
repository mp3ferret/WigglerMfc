
// WigglerMfc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WigglerMfc.h"
#include "WigglerMfcDlg.h"
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWigglerMfcApp

BEGIN_MESSAGE_MAP(CWigglerMfcApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWigglerMfcApp construction

CWigglerMfcApp::CWigglerMfcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CWigglerMfcApp object

CWigglerMfcApp theApp;
std::shared_ptr<CWigglerMfcDlg> pWigglerDlg;
// CWigglerMfcApp initialization

BOOL CWigglerMfcApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	pWigglerDlg = std::shared_ptr<CWigglerMfcDlg>(new CWigglerMfcDlg);
	pWigglerDlg->Create(CWigglerMfcDlg::IDD, CWnd::GetDesktopWindow());
	//pWigglerDlg->ShowWindow(SW_SHOW);
	m_pMainWnd = pWigglerDlg.get();

	return TRUE;
}
