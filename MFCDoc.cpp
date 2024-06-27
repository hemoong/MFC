
// MFCDoc.cpp : CMFCDoc 클래스의 구현
//
#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC.h"
#endif

#include "MFCDoc.h"

#include <propkey.h>
#include <math.h>


#include "Scroll_Thres.h"
#include "Scroll_Bright.h"
//#include "Bar2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCDoc


int His_Gray[256] = {0, }, His_R[256] = {0, }, His_G[256] = {0, }, His_B[256] = {0, }, His_Binary[256] = {0, }, His_Sobel[256] = {0, }, His_Stre[256] = {0, }, His_Fla[256] = {0, }, His_sum[256] = {0, };


IMPLEMENT_DYNCREATE(CMFCDoc, CDocument)
BEGIN_MESSAGE_MAP(CMFCDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CMFCDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, &CMFCDoc::OnFileNew)
	ON_COMMAND(ID_FILE_SAVE, &CMFCDoc::OnFileSave)
	ON_COMMAND(ID_GRAY, &CMFCDoc::Filter_GRAY)
	ON_COMMAND(ID_BINARY, &CMFCDoc::Filter_BINARY)
	ON_COMMAND(ID_SOBEL, &CMFCDoc::Filter_SOBEL)
	ON_COMMAND(ID_THRESHOLD, &CMFCDoc::ControlThreshold)
	ON_COMMAND(ID_BRIGHT, &CMFCDoc::ControlBright)
	ON_COMMAND(ID_HISTOGRAM_RGB, &CMFCDoc::HistogramRGB)
	ON_COMMAND(ID_HISTOGRAMOFF, &CMFCDoc::HistogramOff)
	ON_COMMAND(ID_STRECHING, &CMFCDoc::streching)
	ON_COMMAND(ID_FLATTEN, &CMFCDoc::Flatten)
	ON_COMMAND(ID_ZOOM, &CMFCDoc::OnZoom)
	ON_COMMAND(ID_FIND, &CMFCDoc::OnFind)

END_MESSAGE_MAP()


// CMFCDoc 생성/소멸

CMFCDoc::CMFCDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCDoc::~CMFCDoc()
{
}

BOOL CMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCDoc serialization

void CMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCDoc 진단

#ifdef _DEBUG
void CMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDoc 명령
//여기서 함수 정의
void CMFCDoc:: OnFileOpen(){
	TCHAR Filtering[] = TEXT("비트맵 파일(*.bmp)|*.bmp|Jpg 이미지|*.jpg|Png 이미지|*.png|Raw 이미지|*.raw|");
	CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, Filtering);	//TRUE 읽기, FALSE 저장
	OnFileNew();
	if(IDOK == Dlg.DoModal()){
		
		TCHAR img_path[300];
		lstrcpy(img_path, Dlg.GetPathName());
		switch(Dlg.m_ofn.nFilterIndex){
			default:
				{
					Main_View_image.Load(img_path);
					Main_image.Load(img_path);
					break;
				}
		}
	}
	gray_flag = 0;
	bright_flag = 0;
	UpdateAllViews(NULL);
}
void CMFCDoc:: OnFileNew(){
	if(!Main_image.IsNull()&&!Main_View_image.IsNull()){
		Main_image.Destroy();
		Main_View_image.Destroy();
	}
	if(!Gray_image.IsNull()){
		Gray_image.Destroy();				
	}
	if(!Binary_image.IsNull()){
		Binary_image.Destroy();
	}
	if(!Sobel_image.IsNull()){
		Sobel_image.Destroy();
	}
	if(!Streching_image.IsNull())
		Streching_image.Destroy();
	if(!Flatt_image.IsNull())
		Flatt_image.Destroy();
	if(!Histo_image.IsNull())
		Histo_image.Destroy();
	if(!X_Projection_image.IsNull())
		X_Projection_image.Destroy();
	if(!Y_Projection_image.IsNull())
		Y_Projection_image.Destroy();
	if(!Histo_streching_image.IsNull())
		Histo_streching_image.Destroy();
	if(!Histo_Flat_image.IsNull())
		Histo_Flat_image.Destroy();
	if(!Zoom_image.IsNull())
		Zoom_image.Destroy();
	if(!HistoR_image.IsNull())
		HistogramOff();
	UpdateAllViews(NULL);
}
CImage CMFCDoc::Save_image(){	// 필터가 있다면 필터 이미지를 아니라면 메인 이미지를
		if(!Main_image.IsNull())
		{
			if(!Gray_image.IsNull())
			{
				return Gray_image;
			}
			if(!Binary_image.IsNull())
			{
				return Binary_image;
			}
			if(!Sobel_image.IsNull())
			{
				return Sobel_image;
			}
			if(!Flatt_image.IsNull())
				return Flatt_image;
			if(!Streching_image.IsNull())
				return Streching_image;
			
		}
	}
void CMFCDoc::OnFileSave(){
	TCHAR Filtering[] = TEXT("비트맵 파일(*.bmp)|*.bmp|Jpg 이미지|*.jpg|Png 이미지|*.png|");
		CFileDialog Dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, Filtering);	//TRUE 읽기, FALSE 저장, 읽기 전용파일은 보이지 않음

		if(IDOK == Dlg.DoModal())
		{
			TCHAR img_path[300];
			lstrcpy(img_path, Dlg.GetPathName());	// 파일의 경로를 img_path에 저장

			switch(Dlg.m_ofn.nFilterIndex)
			{
			case 1://bmp
				{
					lstrcat(img_path, TEXT(".bmp"));
					Save_image().Save(img_path, Gdiplus::ImageFormatBMP);
					break;
				}
			case 2://jpg
				{
					lstrcat(img_path, TEXT(".jpg"));
					Save_image().Save(img_path, Gdiplus::ImageFormatJPEG);
					break;
				}
			case 3://png
				{
					lstrcat(img_path, TEXT(".png"));
					Save_image().Save(img_path, Gdiplus::ImageFormatPNG);
					break;
				}
			}
		}
}



void CMFCDoc::SetPixel(int x, int y, BYTE color, CImage * image){

	BYTE *p = (BYTE*)image->GetPixelAddress(x, y);					//포인터 사용하여서 주소 바꿔줌 -> 기존 라이브러리함수 setpixel보다 속도가 빠름
	*p++ = color;
	*p++ = color;
	*p = color;
}


void CMFCDoc::Filter_GRAY(){
	double r, g, b;
	COLORREF* pixel;
	/*COLORREF pixel2;*/
	Threshold = 0;
	gray_flag = 1;


	if(!Main_image.IsNull()){
		if(!Gray_image.IsNull()){
			Gray_image.Destroy();				
		}
		if(!Binary_image.IsNull()){
			Binary_image.Destroy();
		}
		if(!Sobel_image.IsNull()){
			Sobel_image.Destroy();
		}
		if(!Streching_image.IsNull())
		Streching_image.Destroy();
		if(!Flatt_image.IsNull())
			Flatt_image.Destroy();
		if(!Histo_image.IsNull())
			Histo_image.Destroy();
		if(!Histo_streching_image.IsNull())
			Histo_streching_image.Destroy();
		if(!Histo_Flat_image.IsNull())
			Histo_Flat_image.Destroy();
		if(!Histo_image.IsNull()){
			Histo_image.Destroy();
		}
		if(!Histo_streching_image.IsNull()){
			Histo_streching_image.Destroy();
		}

		Gray_image.Create(Main_image.GetWidth(),Main_image.GetHeight(),24);	//생성
		GRAYING = new BYTE*[Main_image.GetHeight()];
		
		for(int i = 0; i < Main_image.GetHeight(); i++)
		{
			GRAYING[i] = new BYTE[Main_image.GetWidth()];		// 메인 이미지 길이의 배열로 재할당
		}

		for(int i = 0; i < Main_image.GetHeight(); i++){ //픽셀값 변환
			for(int j = 0; j < Main_image.GetWidth(); j++){

				pixel = (COLORREF*)Main_View_image.GetPixelAddress(j,i);//주소 얻어옴
				/*pixel2 = *pixel;*/
				r = GetRValue(*pixel)*0.299;
				g = GetGValue(*pixel)*0.587;
				b = GetBValue(*pixel) *0.114;

				/*pixel2 = RGB(r+g+b, r+g+b,r+g+b);*/
				GRAYING[i][j] = r + g + b;										//흑백이미지 만들 때 쓸거
				Threshold += GRAYING[i][j];										//얘도
				/*Gray_image.SetPixel(j, i, pixel2);*/							//되긴 되는데 화질 좋은 것들은 너무 느려서 적용 안댐
				SetPixel(j, i , GRAYING[i][j], &Gray_image);					//그래서 새로 만든 함슈
				
				//히스토그램
				His_Gray[(int)GRAYING[i][j]]++;
				His_R[(int)r]++;
				His_G[(int)g]++;
				His_B[(int)b]++;

			}
		}
		Threshold /= (Main_image.GetHeight()*Main_image.GetWidth());			 //총 픽셀의 수 만큼 나눠 그 지점을 경계값으로 한다..?
		Histogram(His_Gray);
		Projection(1);
		select_filter = 1;
	}

	else{
		MessageBox(NULL, _T("메인 이미지가 없습니다"), _T("Warning !"), MB_ICONERROR);
		return;
	}
	UpdateAllViews(NULL);
}
void CMFCDoc::Filter_BINARY(){
	COLORREF *pixel;
	int r, g, b;
	if(gray_flag ==0){
		Filter_GRAY();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	}
	if(!Main_image.IsNull()){
		if(!Gray_image.IsNull())
		{
			Gray_image.Destroy();												// 그레이 공간 초기화
		}
		if(!Binary_image.IsNull())
		{
			Binary_image.Destroy();												// 이진 공간 초기화
		}
		BINARING = new BYTE*[Main_image.GetHeight()];
		
		for(int i = 0; i < Main_image.GetHeight(); i++)
		{
			BINARING[i] = new BYTE[Main_image.GetWidth()];		// 메인 이미지 길이의 배열로 재할당
		}

		Binary_image.Create(Main_image.GetWidth(),Main_image.GetHeight(),24);	//생성
		for (int i = 0; i < Main_image.GetHeight(); i++){
			for(int j = 0; j < Main_image.GetWidth(); j++){
				if(Threshold > GRAYING[i][j])								 //경계값보다 작으면 검정
					SetPixel(j, i , 0, &Binary_image);
				else														//크면 하양
					SetPixel(j, i , 255, &Binary_image);
			}
		}

		//히스토그램이랑 프로젝션
		for (int i = 0; i < Main_image.GetHeight(); i++){
			for(int j = 0; j < Main_image.GetWidth(); j++){							 
				pixel = (COLORREF*)Binary_image.GetPixelAddress(j, i);
				
				r = GetRValue(*pixel);
				g = GetGValue(*pixel);
				b = GetBValue(*pixel);

				BINARING[i][j] = (r+g+b);
				Threshold_B += BINARING[i][j];
				if(r == 0){
					His_Binary[0]+=1;
					BINARING[i][j] = 0;
				}
				else if(r == 255){
					His_Binary[255]+=1;
					BINARING[i][j] = 255;
				}
			}
		}
		Threshold_B /= (Main_image.GetHeight()*Main_image.GetWidth());
		Histogram(His_Binary);
		Projection(2);
		select_filter = 2;
	}
	else{
		MessageBox(NULL, _T("메인 이미지가 없습니다"), _T("Warning !"), MB_ICONERROR);
		return;
	}
	UpdateAllViews(NULL);


}
void CMFCDoc::Filter_SOBEL(){
	int MaskSobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};				//수평
	int MaskSobelY[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};				//수직

	if(gray_flag == 0){
			Filter_GRAY();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	}


	double Xsum, Ysum;

	if(!Main_image.IsNull()){
		//공간 초기화
		if(!Gray_image.IsNull())
		{
			Gray_image.Destroy();												
		}
		if(!Binary_image.IsNull()){
			Binary_image.Destroy();
		}
		if(!Sobel_image.IsNull()){
			Sobel_image.Destroy();
		}
		
		//끝
		SOBELING = new BYTE*[Main_image.GetHeight()];
		
		for(int i = 0; i < Main_image.GetHeight(); i++)
		{
			SOBELING[i] = new BYTE[Main_image.GetWidth()];		// 메인 이미지 길이의 배열로 재할당
		}
		Sobel_image.Create(Main_image.GetWidth(),Main_image.GetHeight(),24);	//생성

		for (int i = 1; i < Main_image.GetHeight() - 1; i++){ 
			for(int j = 1; j < Main_image.GetWidth() - 1; j++){
				Xsum = 0;
				Ysum = 0;
				for(int k = 0; k < 3; k++){
					for(int m = 0; m < 3; m++){

						Xsum += MaskSobelX[k][m] * GRAYING[i + k -1][j + m - 1];
						Ysum += MaskSobelX[k][m] * GRAYING[i + k -1][j + m - 1];
					}

					if(fabs(Xsum) + fabs(Ysum) > Threshold){
						SetPixel(j, i, 0, &Sobel_image);
						His_Sobel[0] += 1;
						SOBELING[i][j] = 0;
					}
					else{
						SetPixel(j, i, 255, &Sobel_image);
						His_Sobel[255] += 1;
						SOBELING[i][j] = 255;
					}
				}
			}
		}

		Histogram(His_Sobel);
		Projection(3);
		select_filter = 3;
	}
	else{
		MessageBox(NULL, _T("메인 이미지가 없습니다"), _T("Warning !"), MB_ICONERROR);
		return;
	}
	UpdateAllViews(NULL);
}
void CMFCDoc::Histogram(int Histogram[]){ //이미지 밝기 분포
	int Max = Histogram[0];

	if(!Histo_image.IsNull()){
		Histo_image.Destroy();
	}

	for(int i = 0; i < 256; i++){
		if(Max < Histogram[i]){
			Max = Histogram[i];
		}
	}
	if(Max > 1400000)
		Max = 1400000;
	Histo_image.Create(256, Max, 24);

	for(int x = 0; x < 256; x++){
		int y = Max - 1;
		int count = 0;
		while(count  != Histogram[x]){
			SetPixel(x, y, 255, &Histo_image);
			count++;
			y--;
		}
	}

	UpdateAllViews(NULL);

}
void CMFCDoc::Projection(int select){
	/*int *X_projection = {0,};
	int *Y_projection = {0, };*/
	if(!X_Projection_image.IsNull()){
		X_Projection_image.Destroy();
	}
	if(!Y_Projection_image.IsNull()){
		Y_Projection_image.Destroy();
	}
	int x_count = 0, y_count = 0;

		X_Projection_image.Create(Main_image.GetWidth(), Main_image.GetHeight(), 24);
		Y_Projection_image.Create(Main_image.GetWidth(), Main_image.GetHeight(), 24);
	switch(select){
		
	case 1:
		for(int y = 0; y < Main_image.GetHeight(); y++){
			for(int x =0; x < Main_image.GetWidth(); x++){
				if(Threshold < GRAYING[y][x]){
					SetPixel(y_count, y, 0, &Y_Projection_image);
					y_count++;
				}
			}
			for(int i = y_count; i < Main_image.GetWidth(); i++){
				SetPixel(y_count, y, 255, &Y_Projection_image);
				y_count++;
			}
			y_count = 0;

		}

		for(int x =0; x < Main_image.GetWidth(); x++){
			for(int y = 0; y < Main_image.GetHeight(); y++){
				if(Threshold < GRAYING[y][x]){
					SetPixel(x, x_count, 0, &X_Projection_image);
					x_count++;
				}
			}
			for(int i = x_count; i < Main_image.GetHeight(); i++){
				SetPixel(x, x_count, 255, &X_Projection_image);
				x_count++;
			}
			x_count = 0;

		}
		break;

		/////////////////////////////////////////////////////////////////////////////////
		//COLORREF *pixel;
		//int r, g, b;
		//for(int x =0; x < Main_image.GetWidth(); x++){
		//	for(int y = 0; y < Main_image.GetHeight(); y++){
		//		pixel = (COLORREF*)Binary_image.GetPixelAddress(x, y);

		//		r = GetRValue(*pixel);
		//		g = GetGValue(*pixel);
		//		b = GetBValue(*pixel);


		//	}
		//}

	case 2:
		for(int y = 0; y < Main_image.GetHeight(); y++){
			for(int x =0; x < Main_image.GetWidth(); x++){
				if(Threshold < BINARING[y][x]){
					SetPixel(y_count, y, 0, &Y_Projection_image);
					y_count++;
				}
			}
			for(int i = y_count; i < Main_image.GetWidth(); i++){
				SetPixel(y_count, y, 255, &Y_Projection_image);
				y_count++;
			}
			y_count = 0;

		}

		for(int x =0; x < Main_image.GetWidth(); x++){
			for(int y = 0; y < Main_image.GetHeight(); y++){
				if(Threshold < BINARING[y][x]){
					SetPixel(x, x_count, 0, &X_Projection_image);
					x_count++;
				}
			}
			for(int i = x_count; i < Main_image.GetHeight(); i++){
				SetPixel(x, x_count, 255, &X_Projection_image);
				x_count++;
			}
			x_count = 0;
		}
		break;
	case 3:
		for(int y = 0; y < Main_image.GetHeight(); y++){
			for(int x =0; x < Main_image.GetWidth(); x++){
				if(Threshold < SOBELING[y][x]){
					SetPixel(y_count, y, 0, &Y_Projection_image);
					y_count++;
				}
			}
			for(int i = y_count; i < Main_image.GetWidth(); i++){
				SetPixel(y_count, y, 255, &Y_Projection_image);
				y_count++;
			}
			y_count = 0;

		}

		for(int x =0; x < Main_image.GetWidth(); x++){
			for(int y = 0; y < Main_image.GetHeight(); y++){
				if(Threshold < SOBELING[y][x]){
					SetPixel(x, x_count, 0, &X_Projection_image);
					x_count++;
				}
			}
			for(int i = x_count; i < Main_image.GetHeight(); i++){
				SetPixel(x, x_count, 255, &X_Projection_image);
				x_count++;
			}
			x_count = 0;
		}
		break;

	}
	UpdateAllViews(NULL);

}
void CMFCDoc::ControlThreshold(){
	Scroll_Thres TC1;

	
	if(TC1.DoModal() == IDOK && !Main_image.IsNull()){
		Threshold = TC1.value;
		switch(select_filter){
			bright_flag = 0;
		case 2:
			Filter_BINARY();
			break;
		case 3:
			Filter_SOBEL();
			break;
		
		}
	
	}
	UpdateAllViews(NULL); // 뷰 갱신
}
void CMFCDoc::ControlBright(){
	int bright = 0;
	Scroll_Bright TC2;

	
	BYTE r, g, b;

	if(TC2.DoModal() == IDOK && !Main_image.IsNull()){
		bright = TC2.value;
	
		for(int i = 0; i < Main_image.GetHeight(); i++){
			for(int j = 0; j < Main_image.GetWidth(); j++){
				COLORREF *pixel = (COLORREF*)Main_image.GetPixelAddress(j, i);
				b = GetBValue(*pixel);
				g = GetGValue(*pixel);
				r = GetRValue(*pixel);
				if(r  + bright > 255)
					r = 255;
				else if(r + bright < 0)
					r = 0;
				else 
					r = r + bright;
				if(g  + bright > 255)
					g = 255;
				else if(g + bright < 0)
					g = 0;
				else 
					g = g + bright;
				if(b + bright > 255)
					b = 255;
				else if(b + bright < 0)
					b = 0;
				else 
					b = b + bright;
				BYTE *p = (BYTE*)Main_View_image.GetPixelAddress(j, i);

				*p++ = r;
				*p++ = g;
				*p = b;
			}
		
		}
		switch(select_filter){
			bright_flag = 0;
		case 1:
			
			Filter_GRAY();
			break;
		case 2:
			Filter_BINARY();
			break;
		case 3:
			Filter_SOBEL();
			break;
		
		
		}
	
	
	}
	UpdateAllViews(NULL); // 뷰 갱신
}

void CMFCDoc::HistogramRGB(){
	int Max_R = His_R[0];
	int Max_G = His_G[0];
	int Max_B = His_B[0];
	if(!HistoR_image.IsNull()){
		HistoR_image.Destroy();
		HistoG_image.Destroy();
		HistoB_image.Destroy();
	}

	for(int i = 0; i < 256; i++){
		if(Max_R < His_R[i]){
			Max_R = His_R[i];
		}
		if(Max_G < His_G[i]){
			Max_G = His_G[i];
		}
		if(Max_B < His_B[i]){
			Max_B = His_B[i];
		}
	}
	/*if(Max > 1400000)
		Max = 1400000;*/
	HistoR_image.Create(256, Max_R, 24);
	HistoG_image.Create(256, Max_G, 24);
	HistoB_image.Create(256, Max_B, 24);
	for(int x = 0; x < 256; x++){
		int y = Max_R - 1;
		int y_G = Max_G - 1;
		int y_B = Max_B - 1;
		int count = 0;
		while(count  != His_R[x]){
			BYTE *p_r = (BYTE*)(&HistoR_image)->GetPixelAddress(x, y);					
			*p_r++ = 0;
			*p_r++ = 0;
			*p_r = 255;
			count++;
			y--;
		}
		count = 0;
		while(count  != His_G[x]){
			BYTE *p_g = (BYTE*)(&HistoG_image)->GetPixelAddress(x, y_G);					
			*p_g++ = 0;
			*p_g++ = 255;
			*p_g = 0;
			count++;
			y_G--;
		}
		count = 0;
		while(count  != His_B[x]){
			BYTE *p_b = (BYTE*)(&HistoB_image)->GetPixelAddress(x, y_B);					
			*p_b++ = 255;
			*p_b++ = 0;
			*p_b = 0;
			count++;
			y_B--;
		}
	}

	UpdateAllViews(NULL);


}
void CMFCDoc::HistogramOff(){
	if(!HistoR_image.IsNull()){
		HistoR_image.Destroy();
		HistoG_image.Destroy();
		HistoB_image.Destroy();
	}


	UpdateAllViews(NULL);

}

void CMFCDoc::streching(){
	if(Gray_image.IsNull()){
		return;
	}
	if(!Streching_image.IsNull())
		Streching_image.Destroy();
	if(!Flatt_image.IsNull())
		Flatt_image.Destroy();
	if(!Histo_image.IsNull())
		Histo_image.Destroy();
	if(!Histo_streching_image.IsNull())
		Histo_streching_image.Destroy();
	if(!Histo_Flat_image.IsNull())
		Histo_Flat_image.Destroy();
	if(!Histo_image.IsNull()){
		Histo_image.Destroy();
	}
	if(!Histo_streching_image.IsNull()){
		Histo_streching_image.Destroy();
	}

	COLORREF *pixel;
	int r;
	int His_ss[256] = {0,};
	int max = 0;
	int min = 255;

	for(int x = 0; x < Gray_image.GetWidth(); x++){
		for(int y = 0; y < Gray_image.GetHeight(); y++){
			pixel = (COLORREF*)Gray_image.GetPixelAddress(x,y);//주소 얻어옴
				r = GetRValue(*pixel);
				if(max < r)
					max = r;
				if(min > r)
					min = r;
		}
	
	}
	
	Streching_image.Create(Gray_image.GetWidth(), Gray_image.GetHeight(), 24);
	for(int x = 0; x < Gray_image.GetWidth(); x++){
		for(int y = 0; y < Gray_image.GetHeight(); y++){
			
			BYTE *p = (BYTE*)Gray_image.GetPixelAddress(x,y);//주소 얻어옴
			int rgb = (*p - min) * 255 / (max-min);
			BYTE *pixel = (BYTE*)Streching_image.GetPixelAddress(x,y);
			*pixel++ = rgb;
			*pixel++ = rgb;
			*pixel = rgb;
			
			His_ss[rgb]++;
		}
	
	}
	int Max = 0;
	for(int x = 0; x < 256; x++){		
		if(Max < His_ss[x]){
			Max = His_ss[x];
		}
	}
	Histo_streching_image.Create(256,Max,24);

	for(int x = 0; x < 256; x++){		
		int y = Max - 1;
		int count = 0;
		while(count  != His_ss[x]){
			
			BYTE *p = (BYTE*)Histo_streching_image.GetPixelAddress(x,y);
			*p++ = 255;
			*p++ = 255;
			*p = 255;
			count++;
			y--;
		}
	}
	
	UpdateAllViews(NULL);
}



void CMFCDoc::Flatten(){
	if(Gray_image.IsNull()){
		return;
	}
	if(!Streching_image.IsNull())
		Streching_image.Destroy();
	if(!Flatt_image.IsNull())
		Flatt_image.Destroy();
	if(!Histo_image.IsNull())
		Histo_image.Destroy();
	if(!Histo_streching_image.IsNull())
		Histo_streching_image.Destroy();
	if(!Histo_Flat_image.IsNull())
		Histo_Flat_image.Destroy();
	if(!Histo_image.IsNull()){
		Histo_image.Destroy();
	}
	if(!Histo_streching_image.IsNull()){
		Histo_streching_image.Destroy();
	}
	COLORREF *pixel;
	int r;

	for(int y = 0; y < Gray_image.GetHeight(); y++){
		for(int x = 0; x < Gray_image.GetWidth(); x++){
			pixel = (COLORREF*)Gray_image.GetPixelAddress(x,y);//주소 얻어옴
				r = GetRValue(*pixel);
				His_Fla[r]++;
		}
	
	}
	int sum = 0;
	int His_nomal[256] = {0,};
	for(int i = 0; i < 256; i++){
		sum+=His_Fla[i];
		His_nomal[i] = (sum/(double)(Main_image.GetHeight()*Main_image.GetWidth()))*255 + 0.5;
	} 
	int max = 0;
	

	int His_FF[256]={0,};
	Flatt_image.Create(Main_image.GetWidth(), Main_image.GetHeight(), 24);
	for(int y = 0; y < Main_image.GetHeight(); y++){
		for(int x = 0; x < Main_image.GetWidth(); x++){
			COLORREF* pixel = (COLORREF*)Gray_image.GetPixelAddress(x, y);
			r = GetRValue(*pixel);
			BYTE *p = (BYTE*)Flatt_image.GetPixelAddress(x, y);
			*p++ = His_nomal[r];
			*p++ = His_nomal[r];
			*p = His_nomal[r];
			His_FF[His_nomal[r]]++;
		}
	}
	
	max = 0;
	for(int x = 0; x < 256; x++){		
		if(max < His_FF[x]){
			max = His_FF[x];
		}
	}
	Histo_Flat_image.Create(256,max,24);
	for(int x = 0; x < 256; x++){		
		int y = max - 1;
		int count = 0;
		while(count  != His_FF[x]){
			SetPixel(x, y, 255, &Histo_Flat_image);
			count++;
			y--;
		}
	}
	UpdateAllViews(NULL);
}

void CMFCDoc::OnZoom()
{
	if(Main_image.IsNull())
		return;
	if(!Zoom_image.IsNull())
		Zoom_image.Destroy();
	Zoom_in = 0;
}


void CMFCDoc::OnFind()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if(Y_Projection_image.IsNull())
		return;
	Find = 1;
	int max = 0;
	int min = Y_Projection_image.GetHeight();
	int i, j;
	
	int sum;
	COLORREF *pixel;
	for(i = 0; i < Y_Projection_image.GetHeight(); i++){
		sum = 0;
		j = 0;
		while(j !=  Y_Projection_image.GetWidth()){
			pixel = (COLORREF*)Y_Projection_image.GetPixelAddress(i,j);
			if(GetRValue(*pixel) == 255){
				sum++;
				j++;
			}
			else
				j++;

		}
		if(sum>max){
			max = sum;
			Start_y = i;
		}
	}
	Start_y = Start_y - 200;
	max = 0;
	min = 0;
	int aveg = 200;
	for(i = 0; i < X_Projection_image.GetHeight(); i++){
		sum = 0;
		j = 0;
		while(j !=  X_Projection_image.GetWidth()){
			pixel = (COLORREF*)Y_Projection_image.GetPixelAddress(i,j);
			if(GetRValue(*pixel) == 255){
				sum++;
				j++;
			}
			else
				j++;

		}
		if(sum > max){
			max = sum;
			End_x = max - 100;
		}
		if(min < sum){
			min = sum;
		
		}	
		if(min == aveg -10)
			break;
	}
	

	for(i = 0; i < Start_x ; i++){
		sum = 0;
		while(j !=  Y_Projection_image.GetHeight()){
			pixel = (COLORREF*)Y_Projection_image.GetPixelAddress(i,j);
			if(GetRValue(*pixel) == 255){
				sum++;
				j++;
			}
			else
				j++;

		}
		if(sum>max)
			max = sum;
	}
	End_y = Y_Projection_image.GetHeight() - max + 100;
	Start_x = 0;
	/*Start_x = 0;
	Start_y = 360;
	End_x = 200;
	End_y =460;*/
	if(Start_x>End_x){
		int temp;
		temp = Start_x;
		Start_x = End_x;
		End_x = temp;
	}
	if(Start_y>End_y){
		int temp = Start_y;
		Start_y = End_y;
		End_y = temp;
	}
	
	int w = End_x - Start_x;
	int h = End_y - Start_y;
	BYTE r, g, b;

	Find = 0;
	Find_image.Create(w, h, 24);

	for(int x = Start_x; x < End_x; x++){
		for(int y =  Start_y; y < End_y; y++){
			COLORREF *p = (COLORREF*)Main_View_image.GetPixelAddress(x, y);
			r = GetRValue(*p);
			g = GetGValue(*p);
			b = GetBValue(*p);

			BYTE* pixel = (BYTE*)Find_image.GetPixelAddress(x - Start_x, y - Start_y);
			*pixel++ = b;
			*pixel++ = g;
			*pixel = r;
		} 
	}
	UpdateAllViews(NULL);
}
