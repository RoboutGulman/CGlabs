
// InitialsView.h : interface of the CInitialsView class
//

#pragma once


class CInitialsView : public CView
{
protected: // create from serialization only
	CInitialsView() noexcept;
	DECLARE_DYNCREATE(CInitialsView)

// Attributes
public:
	CInitialsDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CInitialsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:

private: 
	bool m_drawCircle = false;
	Gdiplus::Point m_curMousePos{};
	std::auto_ptr<Gdiplus::Bitmap> m_pBitmap;
public:
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnOpenFile();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in InitialsView.cpp
inline CInitialsDoc* CInitialsView::GetDocument() const
   { return reinterpret_cast<CInitialsDoc*>(m_pDocument); }
#endif

