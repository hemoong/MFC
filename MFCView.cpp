
// MFCView.cpp : CMFCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC.h"
#endif

#include "MFCDoc.h"
#include "MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "SCREEN_REC.h"
#include "SCREEN_IMG.h"
#include "Part.h"
// CMFCView

IMPLEMENT_DYNCREATE(CMFCView, CScrollView)

	BEGIN_MESSAGE_MAP(CMFCView, CScrollView)
		ON_WM_CONTEXTMENU()
		ON_WM_LBUTTONUP()
		ON_WM_LBUTTONDOWN()
		ON_WM_MOUSEMOVE()
		
		ON_COMMAND(ID_CAPTURE, &CMFCView::OnCapture)
		ON_WM_TIMER()
		ON_COMMAND(ID_REC, &CMFCView::OnRec)
	END_MESSAGE_MAP()

// CMFCView 생성/소멸

CMFCView::CMFCView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	count = 0;
}

CMFCView::~CMFCView()
{
}

BOOL CMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCView 그리기

void CMFCView::OnDraw(CDC* pDC)
{
	CMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC = GetDC();
	pDC -> Rectangle(10,10,310,310);
	pDC -> Rectangle(320,10,620,310);
	pDC -> Rectangle(630,10,930,310);
	pDC -> Rectangle(10,320,310,620);
	pDC -> Rectangle(320,320,620,620);
	pDC -> Rectangle(630,320,930,620);	

	pDC->TextOutW(11, 620, _T("0"));
	pDC->TextOutW(11+8+256, 620, _T("255"));

	if(!pDoc -> Main_image.IsNull()&& !pDoc->Main_View_image.IsNull())
	{
		SetStretchBltMode(pDC->m_hDC,COLORONCOLOR);		// 이미지 축소 시 깨짐 현상 방지
		pDoc->Main_View_image.StretchBlt(pDC->m_hDC, 15,15,290,290); 
		if(!pDoc -> Gray_image.IsNull())
		{
			pDoc->Gray_image.StretchBlt(pDC->m_hDC, 325,15,290,290); 
			if(!pDoc -> Histo_image.IsNull()){
				pDoc->Histo_image.StretchBlt(pDC->m_hDC, 15, 325,290,290,  NOTSRCCOPY);
			}
			if(!pDoc -> X_Projection_image.IsNull()){
				pDoc->X_Projection_image.StretchBlt(pDC->m_hDC, 325, 325,290,290, NOTSRCCOPY);
			}
			if(!pDoc -> Y_Projection_image.IsNull()){
				pDoc->Y_Projection_image.StretchBlt(pDC->m_hDC, 635, 15, 290,290, NOTSRCCOPY);
			}
		}
		if(!pDoc -> Binary_image.IsNull()){
			pDoc->Binary_image.StretchBlt(pDC->m_hDC, 325,15,290,290);
			if(!pDoc -> Histo_image.IsNull()){
				pDoc->Histo_image.StretchBlt(pDC->m_hDC, 15, 325,290,290,  NOTSRCCOPY);
			}
			if(!pDoc -> X_Projection_image.IsNull()){
				pDoc->X_Projection_image.StretchBlt(pDC->m_hDC, 325, 325,290,290, NOTSRCCOPY);
			}
			if(!pDoc -> Y_Projection_image.IsNull()){
				pDoc->Y_Projection_image.StretchBlt(pDC->m_hDC, 635, 15, 290,290, NOTSRCCOPY);
			}
			
		}
		if(!pDoc -> Sobel_image.IsNull()){
			pDoc->Sobel_image.StretchBlt(pDC->m_hDC, 325,15,290,290);
			if(!pDoc -> Histo_image.IsNull()){
				pDoc->Histo_image.StretchBlt(pDC->m_hDC, 15, 325,290,290,  NOTSRCCOPY);
				
			}
			if(!pDoc -> X_Projection_image.IsNull()){
				pDoc->X_Projection_image.StretchBlt(pDC->m_hDC, 325, 325,290,290, NOTSRCCOPY);
			}
			if(!pDoc -> Y_Projection_image.IsNull()){
				pDoc->Y_Projection_image.StretchBlt(pDC->m_hDC, 635, 15, 290,290, NOTSRCCOPY);
			}
		}
		if(!pDoc ->HistoG_image.IsNull()){
			pDoc->HistoR_image.StretchBlt(pDC->m_hDC,15, 325,290,290 );
			pDoc->HistoG_image.StretchBlt(pDC->m_hDC, 325, 325,290,290 );
			pDoc->HistoB_image.StretchBlt(pDC->m_hDC,635, 325,290,290 );
		}
		if(!pDoc -> Histo_streching_image.IsNull()){
			pDoc->Streching_image.StretchBlt(pDC->m_hDC, 325,15,290,290);
			pDoc->Histo_streching_image.StretchBlt(pDC->m_hDC, 15, 325,290,290,  NOTSRCCOPY);
		}
		if(!pDoc -> Histo_Flat_image.IsNull()){
				pDoc->Histo_Flat_image.StretchBlt(pDC->m_hDC, 15, 325,290,290,  NOTSRCCOPY);
		}
		if(!pDoc->Zoom_in && !Click){
			CBrush brush;
			brush.CreateStockObject(NULL_BRUSH);   //NULL브러쉬 생성
			pDC->SelectObject(brush);
			pDC->Rectangle(pDoc->Start_x, pDoc->Start_y, pDoc->End_x, pDoc->End_y);
		}
		if(!flag){
			int w = pDoc->End_x -  pDoc->Start_x;
			int h =  pDoc->End_y -  pDoc->Start_y;
			BYTE r, g, b;
			flag = 1;
			pDoc->Find = 0;
			pDoc->Zoom_image.Create(w, h, 24);
		
			for(int x =  pDoc->Start_x; x < pDoc->End_x; x++){
				for(int y =  pDoc->Start_y; y <  pDoc->End_y; y++){
					COLORREF p = pDC->GetPixel(x, y);
					r = GetRValue(p);
					g = GetGValue(p);
					b = GetBValue(p);

					BYTE* pixel = (BYTE*) pDoc->Zoom_image.GetPixelAddress(x-pDoc->Start_x, y-pDoc->Start_y);
					*pixel++ = b;
					*pixel++ = g;
					*pixel = r;
				} 
			} 
			SetStretchBltMode(pDC->m_hDC,HALFTONE);
			pDoc->Zoom_image.StretchBlt(pDC->m_hDC, 635, 325,290,290);
		}
		if(!pDoc->Find_image.IsNull())
			pDoc->Find_image.StretchBlt(pDC->m_hDC, 635, 325,290,290);
		if(!pDoc->Streching_image.IsNull())
			pDoc->Streching_image.StretchBlt(pDC->m_hDC, 325,15,290,290);
		if(!pDoc->Flatt_image.IsNull())
			pDoc->Flatt_image.StretchBlt(pDC->m_hDC, 325,15,290,290);
	}

}

void CMFCView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx /*= sizeTotal.cy*/ = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
} 

void CMFCView::OnLButtonUp(UINT  nFlags , CPoint point)
{
	CMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int temp;
	if(!pDoc->Zoom_in){
		if(pDoc->End_x < pDoc->Start_x){
			temp = pDoc->End_x;
			pDoc->End_x = pDoc->Start_x;
			pDoc->Start_x = temp;
		}
		if(pDoc->End_y < pDoc->Start_y){
			temp = pDoc->End_y;
			pDoc->End_y = pDoc->Start_y;
			pDoc->Start_y = pDoc->End_y;
		}
		Click = 1;
		flag = 0;
		pDoc->Zoom_in = 1;
		InvalidateRect(NULL);
	}
	CView::OnLButtonUp(nFlags, point);
}
void CMFCView::OnLButtonDown(UINT  nFlags , CPoint point)
{
	CMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int temp;
	if(!pDoc->Zoom_in){

		pDoc->Start_x = point.x;
		pDoc->Start_y = point.y;
		Click = 0;
	}
	CView::OnLButtonDown(nFlags, point);
}
void CMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	/*theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);*/
#endif
}


// CMFCView 진단

#ifdef _DEBUG
void CMFCView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCDoc* CMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDoc)));
	return (CMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCView 메시지 처리기


void CMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!Click){
		pDoc->End_x = point.x;
		pDoc->End_y = point.y;
		InvalidateRect(NULL);
	}
	CScrollView::OnMouseMove(nFlags, point);
}


void CMFCView::OnCapture()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다. 
	CDC memDC;
	/*CBitmap bitmap;*/
	SCREEN_REC REC;
	SCREEN_IMG Part_rec;
	Part Part;
	CClientDC dc(this);	
	this->GetDlgItem(IDD_DIALOG5);
	if(REC.DoModal() == IDOK){
		if(REC.select == 1){
			int nx =0, ny = 0; 
			CImage capImage;
			CWnd *pDesktopWnd = GetDesktopWindow();
			HDC hDC = NULL;
			if(!pDesktopWnd)
				return;
			CWindowDC DeskTopDC(pDesktopWnd);
			nx = GetSystemMetrics(SM_CXSCREEN);
			ny = GetSystemMetrics(SM_CYSCREEN);
			if(!capImage.Create(nx, ny, 32))
				return;
			hDC = capImage.GetDC();
			BitBlt(hDC, 0,0, nx, ny, DeskTopDC.m_hDC, 0, 0, SRCCOPY);   
			capImage.StretchBlt(dc, 0, 0, nx, ny);
			capImage.Save(_T("FULL.jpg"), Gdiplus::ImageFormatJPEG);
			capImage.ReleaseDC();
			MessageBox(_T("저장되었습니다."), _T("save!"),MB_OK);
		}
		else if(REC.select == 2){
			if(Part.DoModal() != IDOK){
				/*MessageBox(_T("실패"), _T("s뿌앵!"),MB_OK);*/
			}
			else{
				if(Part.part == 2){
					CPoint Point;
					Point.x = Part.x1;
					Point.y = Part.y1;
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
						
						capImage.StretchBlt(dc, 0, 0, nx, ny);
						capImage.Save(_T("window.jpg"), Gdiplus::ImageFormatJPEG);
						capImage.ReleaseDC();
					}
				}
				//if(Part.rec == 1){
				//	if(Part_rec.DoModal() == IDOK){
				//		/*SetTimer(1, 30, NULL);*/
				//		if(Part_rec.stop == 1){
				//			KillTimer(1);
				//			CString path;
				//			const char* str;

				//			ShellExecute(NULL, _T("open"), _T("cmd.exe"), _T("/C cd C:\\ffmpeg\\ffmpeg-n5.0-latest-win64-gpl-5.0\\ffmpeg-n5.0-latest-win64-gpl-shared-5.0\\bin && ffmpeg -i C:\\MFC\\MFC\\Part_%04d.jpg -vf crop=trunc(iw/2)*2:trunc(ih/2)*2 -vcodec libx264 -r 30 C:\\MFC\\MFC\\Recoding_Part.mp4"),NULL,SW_SHOW);
				//			MessageBox(_T("저장되었습니다."), _T("save!"),MB_OK);

				//			CFileFind pFind;
				//			CString num;
				//			for(int i = 0; i<count; i++){
				//				num.Format(_T("Part_%04d.jpg"),i);
				//				BOOL bRet = pFind.FindFile(num);
				//				if(bRet == TRUE){
				//					DeleteFile(num);
				//				}
				//			}
				//		}
				//	}
				//}
			}
		}
		else if(REC.select == 3){
			CString path;
			const char* str;
		
			ShellExecute(NULL, _T("open"), _T("cmd.exe"), _T("/C cd C:\\ffmpeg\\ffmpeg-n5.0-latest-win64-gpl-5.0\\ffmpeg-n5.0-latest-win64-gpl-shared-5.0\\bin && ffmpeg -i C:\\MFC\\MFC\\%04d.jpg -vf crop=trunc(iw/2)*2:trunc(ih/2)*2 -vcodec libx264 -r 30 C:\\MFC\\MFC\\Recoding.mp4"),NULL,SW_SHOW);
			MessageBox(_T("저장되었습니다."), _T("save!"),MB_OK);

			CFileFind pFind;
			CString num;
			for(int i = 0; i<REC.count; i++){
				num.Format(_T("%04d.jpg"),i);
				BOOL bRet = pFind.FindFile(num);
				if(bRet == TRUE){
					DeleteFile(num);
				}
			}
		}
	}
}



	

void CMFCView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*if(nIDEvent == 1){
		Part Part;
	
	CPoint Point;
		Point.x = Part.x1;
		Point.y = Part.y1;
		HWND Focus_hWnd = NULL;
		CImage capImage;
		HDC hDC = NULL;
		Focus_hWnd =:: WindowFromPoint(Point);
		CWnd *pDesktopWnd ;
		:: GetDesktopWindow();
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
			num.Format(_T("Part_%04d.jpg", count));
			capImage.Save(num, Gdiplus::ImageFormatJPEG);
			capImage.ReleaseDC();
	
		}
		CScrollView::OnTimer(nIDEvent);
	}*/
}

void CMFCView::OnRec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SCREEN_IMG rec;
	if(rec.DoModal() == IDOK){
		CString path;
		const char* str;

		
		//ShellExecute(NULL, _T("open"), _T("cmd.exe"), _T("/C cd C:\\ffmpeg\\ffmpeg-n5.0-latest-win64-gpl-5.0\\ffmpeg-n5.0-latest-win64-gpl-shared-5.0\\bin && ffmpeg -i C:\\MFC\\MFC\\Part_%04d.jpg -vf crop=trunc(iw/2)*2:trunc(ih/2)*2 -vcodec libx264 -r 30 C:\\MFC\\MFC\\Recoding_Part.mp4"),NULL,SW_SHOW);
		MessageBox(_T("저장되었습니다."), _T("save!"),MB_OK);

		CFileFind pFind;
		CString num;
		for(int i = 0; i<rec.count; i++){
			num.Format(_T("Part_%04d.jpg"),i);
			BOOL bRet = pFind.FindFile(num);
			if(bRet == TRUE){
				DeleteFile(num);
			}
		}
	}
}
