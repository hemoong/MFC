#pragma once


// SCREEN_IMG ��ȭ �����Դϴ�.

class SCREEN_IMG : public CDialogEx
{
	DECLARE_DYNAMIC(SCREEN_IMG)

public:
	SCREEN_IMG(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SCREEN_IMG();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnAcnStartAnimate1();
	afx_msg void OnBnClicked2();
	int stop;
	int count;
	int x, y;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
