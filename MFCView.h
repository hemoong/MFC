
// MFCView.h : CMFCView 클래스의 인터페이스
//

#pragma once


class CMFCView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMFCView();
	DECLARE_DYNCREATE(CMFCView)

// 특성입니다.
public:
	 CMFCDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	///*afx_msg void OnMouseNove(UINT nFlags, CPoint point);*/
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int Click, flag;
	afx_msg void OnCapture();
	CWnd m_wndChild;
	CBitmap bitmap;
	void Draw();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int count;
	afx_msg void OnRec();
};

#ifndef _DEBUG  // MFCView.cpp의 디버그 버전
inline CMFCDoc* CMFCView::GetDocument() const
   { return reinterpret_cast<CMFCDoc*>(m_pDocument); }
#endif

