
// InitialsView.cpp : implementation of the CInitialsView class
//

#include "framework.h"
#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Initials.h"
#endif

#include "InitialsDoc.h"
#include "InitialsView.h"
#include <stdexcept>

// CInitialsView

IMPLEMENT_DYNCREATE(CInitialsView, CView)

BEGIN_MESSAGE_MAP(CInitialsView, CView)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CInitialsView::OnDrawRectangle)
	ON_COMMAND(ID_DRAW_CIRCLE, &CInitialsView::OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CInitialsView::OnUpdateDrawCircle)
	ON_COMMAND(ID_FILE_OPEN, &CInitialsView::OnOpenFile)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CInitialsView construction/destruction

CInitialsView::CInitialsView() noexcept
{
	using namespace Gdiplus;
	Image img(L"car.jpg");

	if (img.GetLastStatus() != Ok)
	{
		throw std::runtime_error("Failed to open image");
	}

	// создаем Bitmap необходимых размеров
	m_pBitmap = std::auto_ptr<Bitmap>(new Bitmap(
		img.GetWidth(), img.GetHeight()));

	// рисуем в Bitmap содержимое img
	Graphics g(m_pBitmap.get());
	g.DrawImage(&img, 0, 0);
}

CInitialsView::~CInitialsView()
{
}

BOOL CInitialsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CInitialsView drawing

const int LETTER_HEIGHT = 200;
const int LETTER_WIDTH = 100;
const int PEN_WIDTH = 10;

void DrawLetterZ(Gdiplus::Graphics& graphics, const Gdiplus::Point& topLeftP)
{
	using namespace Gdiplus;

	Pen bluePen(Color(255, 0, 0, 255), PEN_WIDTH);
	SolidBrush whiteBrush(Color(255, 255, 255, 255));

	const Size ELLIPSE_SIZE{ LETTER_WIDTH, LETTER_HEIGHT / 2 - PEN_WIDTH };

	graphics.DrawEllipse(&bluePen, Rect{ topLeftP + Point{ 0, PEN_WIDTH }, ELLIPSE_SIZE });
	graphics.DrawEllipse(&bluePen, Rect{ topLeftP + Point{ 0, LETTER_WIDTH }, ELLIPSE_SIZE });
	graphics.FillRectangle(&whiteBrush, Rect{ topLeftP, { LETTER_WIDTH / 2, LETTER_HEIGHT + PEN_WIDTH * 2 } });
}

void DrawLetterA(Gdiplus::Graphics& graphics, const Gdiplus::Point& topLeftP)
{
	using namespace Gdiplus;

	Pen redPen(Color(255, 255, 0, 0), PEN_WIDTH);

	const Point TOP_CENTER_POINT{ LETTER_WIDTH / 2, PEN_WIDTH };

	graphics.DrawLine(&redPen, topLeftP + Point{ PEN_WIDTH, LETTER_HEIGHT }, topLeftP + TOP_CENTER_POINT);
	graphics.DrawLine(&redPen, topLeftP + TOP_CENTER_POINT, topLeftP + Point{ LETTER_WIDTH, LETTER_HEIGHT });
	graphics.DrawLine(&redPen, topLeftP + Point{ LETTER_WIDTH / 4, LETTER_HEIGHT / 2 + PEN_WIDTH }, topLeftP + Point{ LETTER_WIDTH * 3 / 4, LETTER_HEIGHT / 2 + PEN_WIDTH });
}

void DrawLetterYu(Gdiplus::Graphics& graphics, const Gdiplus::Point& topLeftP)
{
	using namespace Gdiplus;

	Pen greenPen(Color(255, 0, 255, 0), PEN_WIDTH);

	graphics.DrawLine(&greenPen, topLeftP + Point{ PEN_WIDTH, PEN_WIDTH }, topLeftP + Point{ PEN_WIDTH, LETTER_HEIGHT });
	graphics.DrawLine(&greenPen, topLeftP + Point{ PEN_WIDTH, LETTER_HEIGHT / 2 + PEN_WIDTH }, topLeftP + Point{ LETTER_WIDTH / 2 + PEN_WIDTH, LETTER_HEIGHT / 2 + PEN_WIDTH });
	graphics.DrawEllipse(&greenPen, Rect(topLeftP + Point{ LETTER_WIDTH / 2 + PEN_WIDTH, PEN_WIDTH }, { LETTER_WIDTH / 2 + PEN_WIDTH, LETTER_HEIGHT - PEN_WIDTH * 2 }));
}

void CInitialsView::OnDraw(CDC* pDC)
{
	// добавить функции минимизации, максимизации окна
	using namespace Gdiplus;
	CInitialsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Graphics graphics(pDC->GetSafeHdc());

	// DrawLetterZ(graphics, Point());
	// DrawLetterA(graphics, { LETTER_WIDTH * 2, 0 });
	// DrawLetterYu(graphics, { LETTER_WIDTH * 4, 0 });

	//
	Pen greenPen(Color(255, 0, 255, 0), PEN_WIDTH);
	/* if (m_drawCircle)
	{
		graphics.DrawEllipse(&greenPen, Rect({ 20, 20 }, { 100, 100 }));
	}

	graphics.DrawImage(m_pBitmap.get(), 20, 20);*/
	graphics.DrawLine(&greenPen, Point{}, m_curMousePos);
	//
}

// CInitialsView diagnostics

#ifdef _DEBUG
void CInitialsView::AssertValid() const
{
	CView::AssertValid();
}

void CInitialsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CInitialsDoc* CInitialsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInitialsDoc)));
	return (CInitialsDoc*)m_pDocument;
}
#endif //_DEBUG

// CInitialsView message handlers

void CInitialsView::OnDrawRectangle()
{
	// TODO: Add your command handler code here
	m_drawCircle = false;
	Invalidate();
	UpdateWindow();
}

void CInitialsView::OnDrawCircle()
{
	// TODO: Add your command handler code here
	m_drawCircle = true;
	Invalidate();
	UpdateWindow();
}

void CInitialsView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_drawCircle);
}

void CInitialsView::OnOpenFile()
{
	using namespace Gdiplus;
	LPCTSTR pszFilter = _T("jpg (*.jpg)|*.jpg|");
	try
	{
		CFileDialog dlgFile(TRUE, _T("jpg"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
			pszFilter, AfxGetMainWnd());

		if (IDOK == dlgFile.DoModal())
		{
			Image img(dlgFile.GetPathName());
			if (img.GetLastStatus() != Ok)
			{
				throw std::runtime_error("Failed to open image");
			}

			// создаем Bitmap необходимых размеров
			m_pBitmap = std::auto_ptr<Bitmap>(new Bitmap(
				img.GetWidth(), img.GetHeight()));

			// рисуем в Bitmap содержимое img
			Graphics g(m_pBitmap.get());
			g.DrawImage(&img, 0, 0);
			Invalidate();
			UpdateWindow();
			/* CStdioFile file(dlgFile.GetPathName(), CFile::modeRead | CFile::typeText);
			bool successful{ false };
			if (dlgFile.GetFileExt() == _T("jpg"))
			{
			}*/
		}
	}
	catch (CFileException* pe)
	{
		TRACE(_T("File could not be opened, cause = %d\n"),
			pe->m_cause);
		pe->Delete();
	}
}

void CInitialsView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_curMousePos = { point.x, point.y };

	CView::OnMouseMove(nFlags, point);
	Invalidate();
	UpdateWindow();
}

void CInitialsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}

void CInitialsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);
}
