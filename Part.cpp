// Part.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC.h"
#include "Part.h"
#include "afxdialogex.h"


// Part ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Part, CDialogEx)

Part::Part(CWnd* pParent /*=NULL*/)
	: CDialogEx(Part::IDD, pParent)
{

}

Part::~Part()
{
}

void Part::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Part, CDialogEx)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &Part::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_FOCUS, &Part::OnBnClickedFocus)
	ON_BN_CLICKED(IDC_BUTTON3, &Part::OnBnClickedButton3)
END_MESSAGE_MAP()


// Part �޽��� ó�����Դϴ�.


BOOL Part::OnInitDialog(){
	CDialogEx::OnInitDialog();
	first = 1;
	part = 0;
	rec = 0;
	return TRUE;
}

void Part::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int temp;
	if(Click == 0){
		if(x1>x2){
			temp = x1;
			x1 = x2;
			x2 = temp;
		}
		if(y1>y2){
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		Click = 1;
		InvalidateRect(NULL);
	}
	if(part == 2 || rec == 1 ){
		x1 = point.x;
		y1 = point.y;
		CDialogEx::OnOK();
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void Part::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(part == 0 ){
		x1 = point.x;
		y1 = point.y;
		Click = 0;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void Part::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(Click == 0){
		x2 = point.x;
		y2 = point.y;
		InvalidateRect(NULL);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void Part::OnPaint()
{

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CPaintDC dc(this);
	CDC memDC;
	CBitmap bitmap;
	HBITMAP hbit;
	BYTE r, g, b;
	
	if(first == 1){
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
		SetWindowPos(&wndTop, 0, 0, nx, ny, SWP_SHOWWINDOW );
		capImage.StretchBlt(dc, 0, 0, nx, ny);
		/*capImage.Save(_T("FULL.jpg"), Gdiplus::ImageFormatJPEG);*/
		//���
		FULL_image.Create(capImage.GetWidth(),capImage.GetHeight() ,32);
		for(int x = 0; x<nx; x++){
			for(int y = 0; y<ny; y++){
				COLORREF *p = (COLORREF*)capImage.GetPixelAddress(x, y);
				r = GetRValue(*p);
				g = GetGValue(*p);
				b = GetBValue(*p);

				BYTE *pixel = (BYTE*)FULL_image.GetPixelAddress(x,y);
				*pixel++ = r;
				*pixel++ = g;
				*pixel = b;
			}
		}
		capImage.ReleaseDC();
		first = 0;


	}
	FULL_image.StretchBlt(dc, 0, 0, 1920, 1080);
	/*Click = 0;*/
	/*memDC.SelectObject(pOldBitmap);*/
	if(Click == 1){
		CBrush brush;
		
		
		
		CPen pen(1,4,RGB(0,0,0));
		// �޸� DC�� ��Ʈ��
		
		brush.CreateStockObject(NULL_BRUSH);
		dc.SelectObject(brush);
		dc.SelectObject(pen);
		dc.Rectangle(x1, y1, x2, y2);
		
		part = 1;
	}
	if(part == 1){
		CImage Part_image;
		Part_image.Create((x2 - x1), (y2 - y1), 24);
		BYTE r, g, b;
		
		for(int x = x1; x<x2; x++){
			for(int y = y1; y<y2; y++){
				COLORREF *p = (COLORREF*)FULL_image.GetPixelAddress(x, y);
				r = GetRValue(*p);
				g = GetGValue(*p);
				b = GetBValue(*p);

				BYTE *pixel = (BYTE*)Part_image.GetPixelAddress((x-x1),(y-y1));
				*pixel++ = r;
				*pixel++ = g;
				*pixel = b;
			}
		}
		SetStretchBltMode(dc,HALFTONE);
		/*SetWindowPos(&wndTop, x1, y1,  (x2-x1) , (y2-y1), SWP_SHOWWINDOW );*/
		Part_image.StretchBlt(dc, x1, y1, (x2-x1), (y2-y1));
		Part_image.Save(_T("Part.jpg"), Gdiplus::ImageFormatJPEG);
		MessageBox(_T("����Ǿ����ϴ�."), _T("save!"),MB_OK);
		CDialogEx::OnOK();
	}
	//else if( part == 2){
	//	CPoint point;
	//	point.x = x1;
	//	point.y = y1;
	//	CWnd* Focus_hWnd = NULL;
	//	RECT rt;
	//	CImage capImage;
	//	HDC hDC = NULL;
	//	Focus_hWnd = WindowFromPoint(point);
	//	if(Focus_hWnd != NULL){
	//		GetWindowRect(&rt);
	//		int nx =0, ny = 0; 
	//		/*nx = rt.top - rt.left;
	//		ny = rt.right - rt.*/
	//		nx = GetSystemMetrics(SM_CXSCREEN);
	//		ny = GetSystemMetrics(SM_CYSCREEN);
	//		if(!capImage.Create(nx, ny, 32))
	//			return;
	//		hDC = capImage.GetDC();
	//		if(!Focus_hWnd)
	//			return;
	//		CWindowDC DeskTopDC(Focus_hWnd);

	//		BitBlt(hDC, 0,0, nx, ny, DeskTopDC.m_hDC, 0, 0, SRCCOPY);   
	//		SetWindowPos(&wndTop, 0, 0, nx, ny, SWP_SHOWWINDOW );
	//		capImage.StretchBlt(dc, 0, 0, nx, ny);
	//	}
	//}
}



void Part::OnSize(UINT nType, int cx, int cy)
{

	CDialogEx::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	int sizeX = GetSystemMetrics(SM_CXSCREEN);
	int sizeY = GetSystemMetrics(SM_CYSCREEN);
}


void Part::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


int Part::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	//CPaintDC dc(this);
	//CDC memDC;
	//CBitmap bitmap;
	//// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	//int cx, cy;
	//	cx = GetSystemMetrics(SM_CXSCREEN);
	//	cy = GetSystemMetrics(SM_CYSCREEN);

	//	CClientDC ScreenDC(GetDesktopWindow());	// ��ũ��DC ����
	//	memDC.CreateCompatibleDC(&ScreenDC);
	//			// ��ũ��DC�� ȣȯ�Ǵ� DC����
	//	bitmap.CreateCompatibleBitmap(&ScreenDC, cx, cy);	// ��ũ��DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	//	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	//		// Bitmap �����͸� �Ѱ���
	//	memDC.StretchBlt(0, 0, cx, cy, &ScreenDC, 0, 0, cx, cy, SRCCOPY);	// ��ũ��DC�� �����ȭ���� memDC�� copy, bitmap���� ��ϵ�
	//	
	//	//���
	//	SetWindowPos(&wndTop, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
	//	dc.BitBlt(0, 0, cx, cy, &memDC, 0, 0, SRCCOPY);	// 0,0 ���� �ػ�ũ����� memDC�� ����Ű�� ������ 0, 0���� �����ؼ� �����
	//	memDC.SelectObject(pOldBitmap);
	return 0;
}


void Part::OnBnClickedFocus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	part = 2;
}


void Part::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	rec = 1;
}
