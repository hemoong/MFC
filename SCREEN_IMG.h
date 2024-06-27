#pragma once


// SCREEN_IMG 대화 상자입니다.

class SCREEN_IMG : public CDialogEx
{
	DECLARE_DYNAMIC(SCREEN_IMG)

public:
	SCREEN_IMG(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SCREEN_IMG();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
