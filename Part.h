#pragma once


// Part ��ȭ �����Դϴ�.

class Part : public CDialogEx
{
	DECLARE_DYNAMIC(Part)

public:
	Part(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Part();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	int x1, y1, x2, y2;
	int Click;
	int first;
	int part;
	virtual BOOL OnInitDialog();
	CImage FULL_image;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedFocus();
	afx_msg void OnBnClickedButton3();
	int rec;
};
