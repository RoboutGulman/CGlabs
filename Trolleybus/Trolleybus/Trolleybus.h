
// Trolleybus.h : main header file for the Trolleybus application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTrolleybusApp:
// See Trolleybus.cpp for the implementation of this class
//

class CTrolleybusApp : public CWinApp
{
public:
	CTrolleybusApp() noexcept;

// Overrides
public:
	virtual BOOL InitInstance();
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTrolleybusApp theApp;
