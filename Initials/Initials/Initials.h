
// Initials.h : main header file for the Initials application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h" // main symbols

// CInitialsApp:
// See Initials.cpp for the implementation of this class
//

class CInitialsApp : public CWinApp
{
private:
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
public:
	CInitialsApp() noexcept;

	// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CInitialsApp theApp;
