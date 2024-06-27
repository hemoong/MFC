// SCREEN_REC.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC.h"
#include "SCREEN_REC.h"
#include "afxdialogex.h"


// SCREEN_REC 대화 상자입니다.

IMPLEMENT_DYNAMIC(SCREEN_REC, CDialogEx)

SCREEN_REC::SCREEN_REC(CWnd* pParent /*=NULL*/)
	: CDialogEx(SCREEN_REC::IDD, pParent)
{
	select = 0;
	count = 0;
}

SCREEN_REC::~SCREEN_REC()
{
}

void SCREEN_REC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SCREEN_REC, CDialogEx)
	ON_BN_CLICKED(IDC_FULLCAPTURE, &SCREEN_REC::OnBnClickedFullcapture)
	ON_BN_CLICKED(IDC_USERDEFINE, &SCREEN_REC::OnBnClickedUserdefine)
	ON_BN_CLICKED(IDC_RECSTART, &SCREEN_REC::OnBnClickedRecstart)
	ON_BN_CLICKED(IDC_RECEND, &SCREEN_REC::OnBnClickedRecend)
	ON_BN_CLICKED(IDCANCEL, &SCREEN_REC::OnBnClickedCancel)
	ON_COMMAND(ID_CAPTURE, &SCREEN_REC::OnCapture)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// SCREEN_REC 메시지 처리기입니다.


void SCREEN_REC::OnBnClickedFullcapture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	select = 1;
	CDialogEx::OnOK();
}


void SCREEN_REC::OnBnClickedUserdefine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	select = 2;
	CDialogEx::OnOK();
}


void SCREEN_REC::OnBnClickedRecstart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	SetTimer(1, 30 , NULL);

}


void SCREEN_REC::OnBnClickedRecend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(1);
	select = 3;
	CDialogEx::OnOK();
}


void SCREEN_REC::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void SCREEN_REC::OnCapture()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void SCREEN_REC::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent ==1){
		CImage capImage;
		CWnd *pDesktopWnd = GetDesktopWindow();
		HDC hDC = NULL;
		int nx =0, ny = 0; 
		nx = GetSystemMetrics(SM_CXSCREEN);
		ny = GetSystemMetrics(SM_CYSCREEN);
		if(!capImage.Create(nx, ny, 32))
			return;
		hDC = capImage.GetDC();
		if(!pDesktopWnd)
			return;
		CWindowDC DeskTopDC(pDesktopWnd);
		BitBlt(hDC, 0,0, nx, ny, DeskTopDC.m_hDC, 0, 0, SRCCOPY);   
		num.Format(_T("%04d.jpg"),count);
		capImage.Save( num , Gdiplus::ImageFormatJPEG);
		capImage.ReleaseDC();
		count++;
	}
	CDialogEx::OnTimer(nIDEvent);
}
