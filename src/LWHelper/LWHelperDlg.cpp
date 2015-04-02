// LWHelperDlg.cpp : ʵ���ļ�
// Download by http://www.codefans.net

#include "stdafx.h"
#include "LWHelper.h"
#include "LWHelperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLWHelperDlg �Ի���




CLWHelperDlg::CLWHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLWHelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bTracking=m_Play=false;
}

void CLWHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLWHelperDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
  ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CLWHelperDlg ��Ϣ�������

BOOL CLWHelperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowText(_T("С������"));
	InitUI();
	DrawUI();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLWHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CLWHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLWHelperDlg::InitUI(void)
{
	//����UI������Ŀ������
m_LWHelper.width = 204;
m_LWHelper.height = 209;
m_LWHelper.main = MakeUiItem (48, 48, 106, 106, 0, 0,true);
m_LWHelper.left = MakeUiItem (0, 54, 98, 100, 110, 0);
m_LWHelper.top = MakeUiItem (53, 0, 98, 100, 110, 0);
m_LWHelper.right = MakeUiItem (106, 54, 98, 100, 110, 0);
m_LWHelper.bottom = MakeUiItem (53, 109, 98, 100, 110, 0);
m_LWHelper.Item [0] = MakeUiItem (30, 90, 24, 24, 113, 179);
m_LWHelper.Item [1] = MakeUiItem (91, 24, 24, 24, 113, 154);
m_LWHelper.Item [2] = MakeUiItem (158, 90, 24, 24, 138, 179);
m_LWHelper.Item [3] = MakeUiItem (91, 157, 24, 24, 138, 154);
	//--------------------------
	LoadResImage(IDR_PNG_APPSKIN,m_pSrcImage);//������Դ�е�Ƥ��PNGͼƬ
	ModifyStyleEx(0,WS_EX_LAYERED);
}

void CLWHelperDlg::DrawUI(void)
{
	HDC hDC=::GetDC(m_hWnd);
	HDC hMemDC=::CreateCompatibleDC(hDC);
	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biBitCount = 32;
	bitmapinfo.bmiHeader.biHeight = m_LWHelper.height;
	bitmapinfo.bmiHeader.biWidth = m_LWHelper.width;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biCompression=BI_RGB;
	bitmapinfo.bmiHeader.biXPelsPerMeter=0;
	bitmapinfo.bmiHeader.biYPelsPerMeter=0;
	bitmapinfo.bmiHeader.biClrUsed=0;
	bitmapinfo.bmiHeader.biClrImportant=0;
	bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth * bitmapinfo.bmiHeader.biHeight * bitmapinfo.bmiHeader.biBitCount / 8;
	HBITMAP hBitmap=::CreateDIBSection (hMemDC,&bitmapinfo, 0,NULL, 0, 0);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject (hMemDC,hBitmap);
	Graphics g(hMemDC);
	//������������Ԫ��----------------------
	DrawItem(&g,m_LWHelper.left);
	DrawItem(&g,m_LWHelper.top);
	DrawItem(&g,m_LWHelper.right);
	DrawItem(&g,m_LWHelper.bottom);
	DrawItem(&g,m_LWHelper.main);
	for(int i=0;i<4;i++)
		DrawItem(&g,m_LWHelper.Item[i]);	
	//����͸������-------------------------------------------------
	CPoint DestPt(0,0);
	CSize psize(m_LWHelper.width,m_LWHelper.height);
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;
	::UpdateLayeredWindow(m_hWnd,hDC,NULL,&psize,hMemDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);
	//�ͷ���Դ-------------------------------------------------
	::SelectObject (hMemDC,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(m_hWnd,hDC);
}
void CLWHelperDlg::DrawItem(Graphics *g,UIITEM item)
{
	if(!item.Show)return;
	g->DrawImage(m_pSrcImage,RectF(item.x,item.y,item.width,item.height),item.SrcX,item.SrcY,item.width,item.height,UnitPixel,NULL,NULL,NULL);
}
void CLWHelperDlg::PlayMouseOver()
{
	m_Play=true;
	//--------------------------
	m_LWHelper.main.SrcY=110;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.top.Show=true;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.right.Show=true;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.bottom.Show=true;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.left.Show=true;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	ShowItem(true);
	m_Play=false;
}
void CLWHelperDlg::PlayMouseOut()
{
	m_Play=false;
	ShowItem(false);
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.left.Show=false;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.bottom.Show=false;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.right.Show=false;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.top.Show=false;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_LWHelper.main.SrcY=0;
	DrawUI();
	doEvents();
	//--------------------------	
	m_Play=false;
}
void CLWHelperDlg::ShowItem(bool bShow)
{
	for(int i=0;i<4;i++)
		m_LWHelper.Item[i].Show=bShow;	
	DrawUI();
}
UIITEM CLWHelperDlg::MakeUiItem(int x,int y,int width,int height,int SrcX,int SrcY,bool Show)
{
	UIITEM item;
item.x = x;
item.y = y;
item.width = width;
item.height = height;
item.SrcX = SrcX;
item.SrcY = SrcY;
item.Show = Show;
return item;
}
void CLWHelperDlg::doEvents()
{
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	} 
}
void CLWHelperDlg::LoadResImage(int nResID,Image * &lpImage)
{
	HINSTANCE hIns=AfxGetInstanceHandle();
	HRSRC hRsrc = ::FindResource (hIns,MAKEINTRESOURCE(nResID),_T("PNG")); // type 
	if (!hRsrc) 
		return; 
	// load resource into memory 
	DWORD len = SizeofResource(hIns, hRsrc); 
	BYTE* lpRsrc = (BYTE*)LoadResource(hIns, hRsrc); 
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
void CLWHelperDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags, point);
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 50;
		m_bTracking = (bool)_TrackMouseEvent(&tme);
	}
}
LRESULT CLWHelperDlg::OnMouseHover(WPARAM   wParam,   LPARAM   lParam)
{
	if(!m_Play)PlayMouseOver();
	return 0;
}
LRESULT CLWHelperDlg::OnMouseLeave(WPARAM   wParam,   LPARAM   lParam)
{
	m_bTracking=false;
	if(!m_Play)PlayMouseOut();
	return 0;
}
void CLWHelperDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
	ReleaseCapture ();
	SendMessage (WM_NCLBUTTONDOWN, HTCAPTION, 0);
}




BOOL RenameFolder2(LPCTSTR lpszFromPath,LPCTSTR lpszToPath)
{
  //int nLengthFrm = _tcslen(lpszFromPath);
  TCHAR NewPathFrom[_MAX_PATH] ={0};
  lstrcpy(NewPathFrom,lpszFromPath);
  //PathQuoteSpaces(NewPathFrom);
  int nLengthFrom = _tcslen(NewPathFrom);
  NewPathFrom[nLengthFrom] = _T('\0');
  NewPathFrom[nLengthFrom+1] = _T('\0');

  TCHAR NewPathTo[_MAX_PATH] ={0};
  lstrcpy(NewPathTo,lpszToPath);
  //PathQuoteSpaces(NewPathTo);
  int nLengthTo = _tcslen(NewPathTo);
  NewPathTo[nLengthTo] = _T('\0');
  NewPathTo[nLengthTo+1] = _T('\0');


  SHFILEOPSTRUCT FileOp;
  ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

  FileOp.fFlags = FOF_NOCONFIRMATION ;
  FileOp.hNameMappings = NULL;
  FileOp.hwnd = NULL;
  FileOp.lpszProgressTitle = NULL;
  FileOp.pFrom = NewPathFrom;
  FileOp.pTo = NewPathTo;
  FileOp.wFunc = FO_RENAME;

  int dwRet = SHFileOperation(&FileOp);
  return  dwRet== 0;
}

void CLWHelperDlg::OnDropFiles(HDROP hDropInfo)
{
  // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
  //CButton * check = (CButton*) GetDlgItem(IDC_CHECK_ENC);
  //bool enc = check->GetCheck() == BST_CHECKED;

  int DropCount=DragQueryFile(hDropInfo,-1,NULL,0);//ȡ�ñ��϶��ļ�����Ŀ  
  for(int i=0;i< DropCount;i++)  
  {  
    TCHAR wcStr[MAX_PATH];  
    DragQueryFile(hDropInfo,i,wcStr,MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ��� 

    CString neName = wcStr;
    CString sampx = _T(".xlsx");
    CString samp = _T(".xls");
    CString ext = neName.Right(samp.GetLength());
    
    if( ext.CompareNoCase(samp) == 0 )
    {
      CString reName = neName.Left( neName.GetLength() - samp.GetLength()) + sampx;

      RenameFolder2(neName,reName);

    }
    else
    {
       ext = neName.Right(sampx.GetLength());
       if( ext.CompareNoCase(sampx) == 0 )
      {
        CString reName = neName.Left( neName.GetLength() - sampx.GetLength()) + samp;

        bool b = RenameFolder2(neName,reName);
        DWORD dw = GetLastError();

      }
    }

  }   
  DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ� 

  CDialog::OnDropFiles(hDropInfo);
}

