
// TrolleybusView.h : interface of the CTrolleybusView class
//

#pragma once
#include "CGdiplusInitializer.h"

class CTrolleybusView : public CView
{
protected: // create from serialization only
	CTrolleybusView();
	DECLARE_DYNCREATE(CTrolleybusView)

// Attributes
public:
	CTrolleybusDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CTrolleybusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	CGdiplusInitializer m_initializer;
};

#ifndef _DEBUG  // debug version in TrolleybusView.cpp
inline CTrolleybusDoc* CTrolleybusView::GetDocument() const
   { return reinterpret_cast<CTrolleybusDoc*>(m_pDocument); }
#endif

