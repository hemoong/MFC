
// MFCDoc.h : CMFCDoc 클래스의 인터페이스
//


#pragma once

  
class CMFCDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCDoc();
	DECLARE_DYNCREATE(CMFCDoc)

// 특성입니다.
public:
	COLORREF* r_pixel;

	CImage Main_image;

	CImage Gray_image;
	CImage Binary_image;
	CImage Sobel_image;

	CImage Main_View_image;
	CImage Streching_image;
	CImage Flatt_image;
	CImage Histo_image;
	CImage X_Projection_image;
	CImage Y_Projection_image;
	CImage Histo_streching_image;
	CImage Histo_Flat_image;
	CImage HistoR_image;
	CImage HistoG_image;
	CImage HistoB_image;
	CImage Zoom_image;
	CImage Find_image;
	
	int gray_flag, bright_flag, select_filter;
	int Threshold, Threshold_B;
	BYTE **GRAYING;
	BYTE **BINARING;
	BYTE **SOBELING;
	/*int His_Gray[256];*/
	BOOL Zoom_in;
	int Find ;
	int Start_x, Start_y, End_x, End_y;
	/*int His_R[256];
	int His_G[256];
	int His_B[256];*/
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void OnFileNew();
	void OnFileSave();
	void OnFileOpen();

	void SetPixel(int, int, BYTE, CImage *);

	void Filter_GRAY();
	void Filter_BINARY();
	void Filter_SOBEL();

	void Histogram(int []);
	void HistogramRGB();
	void HistogramOff();

	void Projection(int);

	void ControlThreshold();
	void ControlBright();

	void streching();
	void Flatten();


	CImage Save_image();
	afx_msg void OnZoom();
	afx_msg void OnFind();
	
};
