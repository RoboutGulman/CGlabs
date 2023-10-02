
// TrolleybusView.cpp : implementation of the CTrolleybusView class
//

#include "framework.h"
#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Trolleybus.h"
#endif

#include "TrolleybusDoc.h"
#include "TrolleybusView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CGdiplusInitializer.h"

// CTrolleybusView

IMPLEMENT_DYNCREATE(CTrolleybusView, CView)

BEGIN_MESSAGE_MAP(CTrolleybusView, CView)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CTrolleybusView construction/destruction

CTrolleybusView::CTrolleybusView() 
{
	// TODO: add construction code here
}

CTrolleybusView::~CTrolleybusView()
{
}

BOOL CTrolleybusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTrolleybusView drawing

const int BORDER_WIDTH = 2;

void DrawWheel(Gdiplus::Graphics& graphics, const Gdiplus::Point& topLeftP)
{
	using namespace Gdiplus;
	const Size WHEEL_SIZE{ 80, 80 };

	SolidBrush greyBrush(Color(255, 115, 117, 130));
	graphics.FillEllipse(&greyBrush, Rect(topLeftP, WHEEL_SIZE));

	Pen blackPen(Color(255, 0, 0, 0), 10.0);
	graphics.DrawEllipse(&blackPen, Rect(topLeftP, WHEEL_SIZE));
}

const Gdiplus::Size DEFAULT_WINDOW_SIZE{ 120, 80 };

void DrawWindow(Gdiplus::Graphics& graphics, const Gdiplus::Point& topLeftP, const Gdiplus::Size& size = DEFAULT_WINDOW_SIZE)
{
	using namespace Gdiplus;

	SolidBrush whiteBrush(Color(255, 255, 255, 255));
	graphics.FillRectangle(&whiteBrush, Rect(topLeftP, size));

	Pen blackPen(Color(255, 0, 0, 0), BORDER_WIDTH);
	graphics.DrawRectangle(&blackPen, Rect(topLeftP, size));
}

const int DEFAULT_DOOR_SECTION_COUNT = 4;

void DrawDoor(Gdiplus::Graphics& graphics, const Gdiplus::Point& topLeftP, int doorSectionCount = DEFAULT_DOOR_SECTION_COUNT)
{
	using namespace Gdiplus;

	const Size DOOR_SECTION_SIZE{ 30, 180 };
	const Size WINDOW_DOOR_SIZE{ 20, 60 };

	SolidBrush blueBrush(Color(255, 162, 217, 247));
	Pen blackPen(Color(255, 0, 0, 0), BORDER_WIDTH);

	for (int i = 0; i < doorSectionCount; i++)
	{
		const Point currentSectionTopLeft{ topLeftP.X + i * DOOR_SECTION_SIZE.Width, topLeftP.Y };
		graphics.FillRectangle(&blueBrush, Rect(currentSectionTopLeft, DOOR_SECTION_SIZE));
		graphics.DrawRectangle(&blackPen, Rect(currentSectionTopLeft, DOOR_SECTION_SIZE));

		const Point windowTopLeft = currentSectionTopLeft + Point{ 5, 5 };
		DrawWindow(graphics, windowTopLeft, WINDOW_DOOR_SIZE);
	}
}

void DrawTrolleybusBody(Gdiplus::Graphics& graphics, const Gdiplus::Point& topLeftP, const Gdiplus::Size& size)
{
	using namespace Gdiplus;

	// fill background
	SolidBrush solidBrush(Color(255, 130, 142, 220));
	graphics.FillRectangle(&solidBrush, Rect(topLeftP, size));

	// draw border
	Pen blackPen(Color(255, 0, 0, 0), BORDER_WIDTH);
	graphics.DrawRectangle(&blackPen, Rect(topLeftP, size));

	const int WHEEL_Y_COORDINATE = 160;
	const int WHEEL_X_COORDINATES[]{ 230, 730 };

	for (auto x : WHEEL_X_COORDINATES)
	{
		DrawWheel(graphics, topLeftP + Point{ x, WHEEL_Y_COORDINATE });
	}

	const int WINDOW_Y_COORDINATE = 20;
	const int WINDOW_X_COORDINATES[]{ 220, 340, 600, 720 };

	for (auto x : WINDOW_X_COORDINATES)
	{
		DrawWindow(graphics, topLeftP + Point{ x, WINDOW_Y_COORDINATE });
	}

	struct DoorInfo
	{
		int x;
		int sectionCount = DEFAULT_DOOR_SECTION_COUNT;
	};

	const int DOORS_Y_COORDINATE = 30;
	const DoorInfo DOORS_INFO[]{ { 70 }, { 470 }, { 850, 2 } };

	for (auto doorsInfo : DOORS_INFO)
	{
		DrawDoor(graphics, topLeftP + Point{ doorsInfo.x, DOORS_Y_COORDINATE }, doorsInfo.sectionCount);
	}
}

void DrawTrolleybusPantographs(Gdiplus::Graphics& graphics, const Gdiplus::Point& startPoint, int trolleybusWidth, int height)
{
	using namespace Gdiplus;
	const Point END_POINT = startPoint + Point{ trolleybusWidth / 2, height };

	const int PANTOGRAPHS_WIDTH = 5;
	Pen blackPen(Color(255, 0, 0, 0), PANTOGRAPHS_WIDTH);

	graphics.DrawLine(&blackPen, startPoint, END_POINT);
}

void DrawTrolleybus(Gdiplus::Graphics& graphics, const Gdiplus::Point& topLeftP)
{
	using namespace Gdiplus;

	const Size TROLLEYBUS_SIZE{ 1000, 210 };
	const int PANTOGRAPHS_HEIGHT = 200;

	DrawTrolleybusPantographs(graphics, topLeftP, TROLLEYBUS_SIZE.Width, PANTOGRAPHS_HEIGHT);

	DrawTrolleybusBody(graphics, topLeftP + Point{ 0, PANTOGRAPHS_HEIGHT }, TROLLEYBUS_SIZE);
}

void DrawWires(Gdiplus::Graphics& graphics, const Gdiplus::Point& startPoint, int width)
{
	using namespace Gdiplus;

	const int WIRES_WIDTH = 1;
	Pen blackPen(Color(255, 0, 0, 0), WIRES_WIDTH);

	graphics.DrawLine(&blackPen, startPoint, startPoint + Point(width, 0));
}

void CTrolleybusView::OnDraw(CDC* pDC)
{
	// за счёт чего происходит выход из приложения
	// перед выходом выводится сообщение goodbuy, и только при нажатии ОК происходит выход
	using namespace Gdiplus;
	CTrolleybusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	Graphics graphics(pDC->GetSafeHdc());

	const Point TOP_LEFT_POINT{ 100, 100 };
	const int WIRES_WIDTH = 1500;

	DrawWires(graphics, Point(0, TOP_LEFT_POINT.Y), WIRES_WIDTH);

	DrawTrolleybus(graphics, TOP_LEFT_POINT);
}

// CTrolleybusView diagnostics

#ifdef _DEBUG
void CTrolleybusView::AssertValid() const
{
	CView::AssertValid();
}

void CTrolleybusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrolleybusDoc* CTrolleybusView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrolleybusDoc)));
	return (CTrolleybusDoc*)m_pDocument;
}
#endif //_DEBUG

// CTrolleybusView message handlers
