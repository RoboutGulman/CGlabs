
// ImageViewerDoc.h : interface of the CImageViewerDoc class
//

#pragma once

class CImageViewerDoc : public CDocument
{
protected: // create from serialization only
	CImageViewerDoc() noexcept;
	DECLARE_DYNCREATE(CImageViewerDoc)

	// Attributes
public:
	// Operations
	Gdiplus::Bitmap* GetImage();
	void SetImage(const CString& path);

public:
	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CImageViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	std::unique_ptr<Gdiplus::Bitmap> m_pImage;

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
