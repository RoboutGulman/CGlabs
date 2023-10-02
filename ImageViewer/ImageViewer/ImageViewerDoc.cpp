
// ImageViewerDoc.cpp : implementation of the CImageViewerDoc class
//

#include "framework.h"
#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageViewer.h"
#endif

#include "ImageViewerDoc.h"

#include <propkey.h>

// CImageViewerDoc

IMPLEMENT_DYNCREATE(CImageViewerDoc, CDocument)
BEGIN_MESSAGE_MAP(CImageViewerDoc, CDocument)
END_MESSAGE_MAP()

// CImageViewerDoc construction/destruction

CImageViewerDoc::CImageViewerDoc() noexcept
{
	// TODO: add one-time construction code here
}

CImageViewerDoc::~CImageViewerDoc()
{
}

Gdiplus::Bitmap* CImageViewerDoc::GetImage()
{
	return m_pImage.get();
}

void CImageViewerDoc::SetImage(const CString& path)
{
	//в релизной конфигурации программа должна запускаться
	using namespace Gdiplus;
	Image img(path);
	if (img.GetLastStatus() != Ok)
	{
		throw std::runtime_error("Failed to open image");
	}

	// создаем Bitmap необходимых размеров
	m_pImage = std::make_unique<Bitmap>(img.GetWidth(), img.GetHeight());

	// рисуем в Bitmap содержимое img
	Graphics g(m_pImage.get());
	g.DrawImage(&img, 0, 0);
	UpdateAllViews(NULL);
}

BOOL CImageViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CImageViewerDoc serialization

void CImageViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CImageViewerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CImageViewerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageViewerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageViewerDoc diagnostics

#ifdef _DEBUG
void CImageViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CImageViewerDoc commands
