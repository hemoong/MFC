#pragma once

#include "SCREEN_IMG.h"
// SCREEN_REC ��ȭ �����Դϴ�.

class SCREEN_REC : public CDialogEx
{
	DECLARE_DYNAMIC(SCREEN_REC)

public:
	SCREEN_REC(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SCREEN_REC();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
