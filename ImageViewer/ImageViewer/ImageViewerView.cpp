
// ImageViewerView.cpp : implementation of the CImageViewerView class
//

#include "framework.h"
#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageViewer.h"
#endif

#include "ImageViewerDoc.h"
#include "ImageViewerView.h"

// CImageViewerView

IMPLEMENT_DYNCREATE(CImageViewerView, CView)

BEGIN_MESSAGE_MAP(CImageViewerView, CView)
	ON_COMMAND(ID_FILE_OPEN, &CImageViewerView::OnOpenFile)
END_MESSAGE_MAP()

// CImageViewerView construction/destruction

CImageViewerView::CImageViewerView() noexcept
{
	// TODO: add construction code here
}

CImageViewerView::~CImageViewerView()
{
}

BOOL CImageViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

Gdiplus::Size GetScaledSize(const Gdiplus::Size& imageSize, const CRect& clientRect)
{
	using namespace Gdiplus;

	if (imageSize.Width <= clientRect.Width() && imageSize.Height <= clientRect.Height())
	{
		return imageSize;
	}

	float nPercentW = (float)clientRect.Width() / imageSize.Width;
	float nPercentH = (float)clientRect.Height() / imageSize.Height;

	float nPercent = (nPercentH < nPercentW) ? nPercentH : nPercentW;

	return { (int)(imageSize.Width * nPercent), (int)(imageSize.Height * nPercent) };
}

Gdiplus::Point GetCentredImageTopLeftPoint(const Gdiplus::Size& imageSize, const CRect& clientRect)
{
	using namespace Gdiplus;
	Point topLeft;

	if (imageSize.Width < clientRect.Width())
	{
		topLeft.X = (clientRect.Width() - imageSize.Width) / 2;
	}
	if (imageSize.Height < clientRect.Height())
	{
		topLeft.Y = (clientRect.Height() - imageSize.Height) / 2;
	}
	return topLeft;
}

void DrawCurrentImage(CImageViewerDoc* pDoc, Gdiplus::Graphics& graphics, const CRect& clientRect)
{
	using namespace Gdiplus;

	auto image = pDoc->GetImage();
	if (!image)
	{
		return;
	}

	Size imageSize{ (int)image->GetWidth(), (int)image->GetHeight() };

	auto scaledImageSize = GetScaledSize(imageSize, clientRect);
	auto topLeftPoint = GetCentredImageTopLeftPoint(scaledImageSize, clientRect);

	graphics.DrawImage(image, Rect{ topLeftPoint, scaledImageSize },
		0, 0, imageSize.Width, imageSize.Height, Unit::UnitPixel);
}

// CImageViewerView drawing

void CImageViewerView::OnDraw(CDC* pDC)
{
	using namespace Gdiplus;

	CImageViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	Graphics graphics(pDC->GetSafeHdc());

	CRect clientRect;
	GetClientRect(&clientRect);

	DrawCurrentImage(pDoc, graphics, clientRect);
}



// CImageViewerView diagnostics

#ifdef _DEBUG
void CImageViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CImageViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void CImageViewerView::OnOpenFile()
{
	using namespace Gdiplus;
	LPCTSTR pszFilter = _T("jpg (*.jpg)|*.jpg|");

	CFileDialog dlgFile(TRUE, _T("jpg"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		pszFilter, AfxGetMainWnd());

	if (dlgFile.DoModal() == IDOK)
	{
		GetDocument()->SetImage(dlgFile.GetPathName());
	}
}

CImageViewerDoc* CImageViewerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageViewerDoc)));
	return (CImageViewerDoc*)m_pDocument;
}
#endif //_DEBUG

// CImageViewerView message handlers
