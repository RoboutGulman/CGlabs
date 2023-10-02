
// ImageViewer.h : main header file for the ImageViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "CGdiplusInitializer.h"

// CImageViewerApp:
// See ImageViewer.cpp for the implementation of this class
//

class CImageViewerApp : public CWinApp
{
public:
	CImageViewerApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	CGdiplusInitializer m_initializer;
};

extern CImageViewerApp theApp;
