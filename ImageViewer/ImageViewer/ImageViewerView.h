
// ImageViewerView.h : interface of the CImageViewerView class
//

#pragma once
#include "CGdiplusInitializer.h"


class CImageViewerView : public CView
{
protected: // create from serialization only
	CImageViewerView() noexcept;
	DECLARE_DYNCREATE(CImageViewerView)

// Attributes
public:
	CImageViewerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CImageViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	//открыть файл должен делать документ, а не view
	afx_msg void OnOpenFile();
};

#ifndef _DEBUG  // debug version in ImageViewerView.cpp
inline CImageViewerDoc* CImageViewerView::GetDocument() const
   { return reinterpret_cast<CImageViewerDoc*>(m_pDocument); }
#endif