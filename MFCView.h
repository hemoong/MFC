
// MFCView.h : CMFCView Ŭ������ �������̽�
//

#pragma once


class CMFCView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMFCView();
	DECLARE_DYNCREATE(CMFCView)

// Ư���Դϴ�.
public:
	 CMFCDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // MFCView.cpp�� ����� ����
inline CMFCDoc* CMFCView::GetDocument() const
   { return reinterpret_cast<CMFCDoc*>(m_pDocument); }
#endif

