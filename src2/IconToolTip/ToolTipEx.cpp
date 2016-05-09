// ToolTipEx.cpp : 实现文件
//

#include "stdafx.h"
#include "IconToolTip.h"
#include "ToolTipEx.h"


// CToolTipEx

IMPLEMENT_DYNAMIC(CToolTipEx, CWnd)

CToolTipEx::CToolTipEx()
{

}

CToolTipEx::~CToolTipEx()
{
}


BEGIN_MESSAGE_MAP(CToolTipEx, CWnd)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CToolTipEx 消息处理程序

BOOL CToolTipEx::Create(HWND hDeskListView,CRect IconRect,CString StrTipText)
{
	int nWidth=210;//初始宽度
	int nHeight=65;//初始高度
	int x=IconRect.right;
	int y=IconRect.top+(IconRect.Height()-nHeight)/2;
	if(!CWnd::CreateEx(WS_EX_TOOLWINDOW|WS_EX_LAYERED,_T("Static"),StrTipText,WS_POPUP|SS_NOTIFY,CRect(x,y,x+nWidth,y+nHeight),CWnd::FromHandle(hDeskListView),0)){
		return FALSE;
	}
	//========================
	HDC hDC=::GetDC(m_hWnd);
	HFONT hFont=(HFONT)GetStockObject(DEFAULT_GUI_FONT);
	HFONT hOldFont=(HFONT)::SelectObject(hDC,hFont);
	CRect rc(0,0,500,nHeight);
	DrawText(hDC,StrTipText,-1,&rc,DT_SINGLELINE|DT_CALCRECT);
	::SelectObject(hDC,hOldFont);
	if(rc.Width()+60>nWidth){
		nWidth=rc.Width()+60;
		if(nWidth>500)nWidth=500;
		SetWindowPos(NULL,0,0,nWidth,nHeight,SWP_NOZORDER|SWP_NOMOVE);
	}
	m_BtnRect=CRect(nWidth-102,nHeight-28,nWidth-41,nHeight-7);
	//========================
	HDC hMemDC=::CreateCompatibleDC(hDC);
	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biBitCount = 32;
	bitmapinfo.bmiHeader.biHeight = nHeight;
	bitmapinfo.bmiHeader.biWidth = nWidth;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biCompression=BI_RGB;
	bitmapinfo.bmiHeader.biXPelsPerMeter=0;
	bitmapinfo.bmiHeader.biYPelsPerMeter=0;
	bitmapinfo.bmiHeader.biClrUsed=0;
	bitmapinfo.bmiHeader.biClrImportant=0;
	bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth * bitmapinfo.bmiHeader.biHeight * bitmapinfo.bmiHeader.biBitCount / 8;
	HBITMAP hBitmap=CreateDIBSection (hMemDC,&bitmapinfo, 0,NULL, 0, 0);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject (hMemDC,hBitmap);
	//========================
	Image* pImage;
	LoadResImage(IDR_PNG1,pImage);
	Graphics g(hMemDC);
	int nSrcW=210;//PNG图片的宽、高
	int nSrcH=65;
	g.DrawImage(pImage,RectF(0,0,50,nHeight),0,0,50,nSrcH,UnitPixel,NULL,NULL,NULL);
	g.DrawImage(pImage,RectF(50,0,nWidth-50-120,nHeight),50,0,nSrcW-50-120,nSrcH,UnitPixel,NULL,NULL,NULL);
	g.DrawImage(pImage,RectF(nWidth-120,0,120,nHeight),nSrcW-120,0,120,nSrcH,UnitPixel,NULL,NULL,NULL);
	delete pImage;
	//========================
	LOGFONT lf;
	GetObject(hFont,sizeof(LOGFONT),&lf);
	Font Font(lf.lfFaceName,12,FontStyleRegular,UnitPixel);
	StringFormat Format;
	Format.SetAlignment(StringAlignmentCenter) ;
	Format.SetLineAlignment(StringAlignmentCenter);
	SolidBrush Brush(Color(254,0,0,0));
	g.DrawString(StrTipText,-1,&Font,RectF(25,10,nWidth-50,22),&Format,&Brush);
	g.DrawString(_T("我知道了"),-1,&Font,RectF(m_BtnRect.left,m_BtnRect.top,60,21),&Format,&Brush);
	//========================
	CPoint DestPt(0,0);
	CSize psize(nWidth,nHeight);
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;
	::UpdateLayeredWindow(m_hWnd,hDC,NULL,&psize,hMemDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);
	//释放资源/===============
	::SelectObject (hMemDC,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(m_hWnd,hDC);	
	//========================
	ShowWindow(SW_SHOW);
	return TRUE;
}
void CToolTipEx::LoadResImage(int nResID,Image * &lpImage)
{
	HMODULE hModule=AfxGetInstanceHandle();
	HRSRC hRsrc = ::FindResource (hModule,MAKEINTRESOURCE(nResID),_T("PNG")); // type 
	if (!hRsrc) 
		return; 
	// load resource into memory 
	DWORD len = SizeofResource(hModule, hRsrc); 
	BYTE* lpRsrc = (BYTE*)LoadResource(hModule, hRsrc); 
	if (!lpRsrc) 
		return; 
	// Allocate global memory on which to create stream 
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len); 
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem); 
	memcpy(pmem,lpRsrc,len); 
	IStream* pstm; 
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm); 
	// load from stream 
	lpImage=Gdiplus::Image::FromStream(pstm); 
	// free/release stuff 
	GlobalUnlock(m_hMem); 
	pstm->Release(); 
	FreeResource(lpRsrc);
}
void CToolTipEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);
	if(m_BtnRect.PtInRect(point)){
		PostMessage(WM_CLOSE);
	}
}

void CToolTipEx::ShowDesktop(void)
{
	CoInitialize(0);
	IShellDispatch4 * pdisp=NULL;
	CoCreateInstance(CLSID_Shell,NULL,CLSCTX_ALL,__uuidof(IShellDispatch4),(void **)&pdisp);
	if(pdisp){
		pdisp->ToggleDesktop();//这句是用来切换桌面的
		pdisp->Release();
	}
}
