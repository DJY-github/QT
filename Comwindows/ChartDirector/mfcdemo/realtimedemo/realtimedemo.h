// realtimedemo.h : main header file for the REALTIMEDEMO application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRealtimedemoApp:
// See realtimedemo.cpp for the implementation of this class
//

class CRealtimedemoApp : public CWinApp
{
public:
	CRealtimedemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRealtimedemoApp theApp;
