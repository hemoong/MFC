#pragma once

#include "SCREEN_IMG.h"
// SCREEN_REC 대화 상자입니다.

class SCREEN_REC : public CDialogEx
{
	DECLARE_DYNAMIC(SCREEN_REC)

public:
	SCREEN_REC(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SCREEN_REC();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int select;
	afx_msg void OnBnClickedFullcapture();
	afx_msg void OnBnClickedUserdefine();
	afx_msg void OnBnClickedRecstart();
	afx_msg void OnBnClickedRecend();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCapture();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString num;
	int count;
};
