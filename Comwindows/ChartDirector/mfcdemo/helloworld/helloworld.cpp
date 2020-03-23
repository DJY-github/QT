// helloworld.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "helloworld.h"
#include "helloworldDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelloworldApp

BEGIN_MESSAGE_MAP(CHelloworldApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHelloworldApp construction

CHelloworldApp::CHelloworldApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CHelloworldApp object

CHelloworldApp theApp;


// CHelloworldApp initialization

BOOL CHelloworldApp::InitInstance()
{
	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need

	CHelloworldDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
