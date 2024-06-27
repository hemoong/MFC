// SCREEN_IMG.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC.h"
#include "SCREEN_IMG.h"
#include "afxdialogex.h"
#include "Part.h"


// SCREEN_IMG 대화 상자입니다.

IMPLEMENT_DYNAMIC(SCREEN_IMG, CDialogEx)

SCREEN_IMG::SCREEN_IMG(CWnd* pParent /*=NULL*/)
	: CDialogEx(SCREEN_IMG::IDD, pParent)
{
	stop = 0;
	count = 0;
}

SCREEN_IMG::~SCREEN_IMG()
{
}

void SCREEN_IMG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SCREEN_IMG, CDialogEx)
	
	ON_BN_CLICKED(IDCANCEL, &SCREEN_IMG::OnBnClickedCancel)
	
	ON_BN_CLICKED(2, &SCREEN_IMG::OnBnClicked2)
	ON_BN_CLICKED(IDC_BUTTON1, &SCREEN_IMG::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// SCREEN_IMG 메시지 처리기입니다.





void SCREEN_IMG::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}





void SCREEN_IMG::OnBnClicked2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	stop = 1;
	KillTimer(1);
	CDialogEx::OnOK();
}


void SCREEN_IMG::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Part part;
	if(part.DoModal() == IDOK){
		x = part.x1;
		y = part.y1;
		SetTimer(1, 30, NULL);
	}
}


void SCREEN_IMG::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(nIDEvent == 1){
		CPoint Point;
		Point.x = x;
		Point.y = y;
		HWND Focus_hWnd = NULL;
		CImage capImage;
		HDC hDC = NULL;
		Focus_hWnd =:: WindowFromPoint(Point);
		CWnd *pDesktopWnd = GetDesktopWindow();
		if(!pDesktopWnd)
			return;
		CWindowDC DeskTopDC(pDesktopWnd);
		if(Focus_hWnd != NULL){
			RECT rt;
			::GetWindowRect(Focus_hWnd, &rt);
			int nx =0, ny = 0; 
			nx = rt.right - rt.left;
			ny = rt.bottom - rt.top;

			if(!capImage.Create(nx, ny, 32))
				return;
			hDC = capImage.GetDC();
			if(!Focus_hWnd)
				return;

			::BitBlt(hDC, 0, 0, nx, ny,DeskTopDC.m_hDC, rt.left, rt.top, SRCCOPY);   

			CString num;
			num.Format(_T("Part_%04d.jpg"), count);
			capImage.Save(num, Gdiplus::ImageFormatJPEG);
			capImage.ReleaseDC();
			count++;
		}
	
	}
	CDialogEx::OnTimer(nIDEvent);
}
