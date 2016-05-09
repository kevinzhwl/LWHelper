// IconToolTipDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IconToolTip.h"
#include "IconToolTipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIconToolTipDlg 对话框




CIconToolTipDlg::CIconToolTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIconToolTipDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIconToolTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT1,m_EditBox1);
	DDX_Control(pDX,IDC_EDIT2,m_EditBox2);
}

BEGIN_MESSAGE_MAP(CIconToolTipDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CIconToolTipDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CIconToolTipDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()


// CIconToolTipDlg 消息处理程序

BOOL CIconToolTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_EditBox1.SetWindowText(_T("回收站"));
	m_EditBox2.SetWindowText(_T("包含您已经删除的文件和文件夹"));

	int x=8;
	int y=220;
	m_LinkStatic.CreateEx(0,_T("SysLink")
		,_T("设计制作:邓学彬 <a href=\"http://www.it608.com/\">CSDN博客</a> <a href=\"http://t.qq.com/dengxuebin\">腾讯微博</a>")
		,WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,CRect(x,y,x+300,y+40),this,IDC_SYSLINK1);
	HFONT hFont=(HFONT)GetStockObject(DEFAULT_GUI_FONT); 
	m_LinkStatic.SendMessage(WM_SETFONT,(WPARAM)hFont);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CIconToolTipDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	PNMLINK pNMLink = (PNMLINK) pNMHDR;
	ShellExecuteW(NULL, L"open", pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL); 
	*pResult = 0;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIconToolTipDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CIconToolTipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIconToolTipDlg::OnBnClickedButton1()
{
	if(::IsWindow(m_TipWindow.m_hWnd)){//如果之前已经创建了提示窗口
		m_TipWindow.DestroyWindow();//销毁提示窗口
	}
	//===================================
	CString strIconName,StrTipText;
	m_EditBox1.GetWindowText(strIconName);
	m_EditBox2.GetWindowText(StrTipText);
	CRect IconRect;
	HWND hDeskListView;
	BOOL bRet=GetIconRect(strIconName,&IconRect,hDeskListView);
	if(!bRet){
		AfxMessageBox(_T("没找到指定的桌面图标"));
		return;
	}else{
		//CString str;
		//str.Format(_T("桌面图标位置: Left=%d Top=%d w=%d h=%d"),IconRect.left,IconRect.top,IconRect.Width(),IconRect.Height());
		//AfxMessageBox(str);
	}
	//===================================
	m_TipWindow.ShowDesktop();//显示桌面
	m_TipWindow.Create(hDeskListView,IconRect,StrTipText);
}
//==取桌面图标位置=======================
BOOL CIconToolTipDlg::GetIconRect(CString strIconName,LPRECT lpRect,HWND &hDeskListView)
{
	
	HWND hDeskWnd=NULL;//桌面上SysListView32的窗口句柄
	HWND hWnd=::FindWindow(_T("WorkerW"),NULL);//先当WIN7系统查找
	while(hWnd){
		HWND hShellView=::FindWindowEx(hWnd,NULL,_T("SHELLDLL_DefView"),NULL);
		if(hShellView){
			hDeskWnd=::FindWindowEx(hShellView,NULL,_T("SysListView32"),NULL);
			break;
		}
		hWnd=::GetWindow(hWnd,GW_HWNDNEXT);
	}
	if(!hDeskWnd){//如果没找到，再按XP方式查找
		hWnd=::FindWindow(_T("Progman"),_T("Program Manager"));
		if(hWnd){
			hWnd=::FindWindowEx(hWnd,NULL,_T("SHELLDLL_DefView"),NULL);
			hDeskWnd=::FindWindowEx(hWnd,NULL,_T("SysListView32"),NULL);
		}
	}
	if(!hDeskWnd){
		MessageBox(_T("查找桌面窗口句柄失败"));
		return FALSE;
	}
	hDeskListView=hDeskWnd;
	BOOL bRet=FALSE;
	if(Is64Bit_OS()){
		//AfxMessageBox(_T("x64"));
		bRet=GetIconRect64(hDeskWnd,strIconName,lpRect);
	}else{
		bRet=GetIconRect(hDeskWnd,strIconName,lpRect);
	}
	if(bRet){
		CPoint pt(lpRect->left,lpRect->top);
		::ClientToScreen(hDeskWnd,&pt);
		OffsetRect(lpRect,pt.x-lpRect->left,pt.y-lpRect->top);
	}
	return bRet;
}
BOOL CIconToolTipDlg::GetIconRect(HWND hDeskWnd,CString strIconName,LPRECT lpRect)
{
	BOOL bRet=FALSE;
	//-----------------------------
	//遍历外部进程所有图标
	DWORD PID=0;
	GetWindowThreadProcessId(hDeskWnd,&PID);
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,false,PID);
	if(!hProcess){
		TRACE(_T("获取进程句柄操作失败hWnd=%dPID=%d"),hDeskWnd,PID);
	}else{
		LVITEMA* pLVITEM=(LVITEMA*)VirtualAllocEx(hProcess,NULL,sizeof(LVITEM),MEM_COMMIT,PAGE_READWRITE);
		char* pszText=(char*)VirtualAllocEx(hProcess,NULL,512,MEM_COMMIT,PAGE_READWRITE);
		RECT* pItemRc=(RECT*)VirtualAllocEx(hProcess,NULL,sizeof(RECT),MEM_COMMIT,PAGE_READWRITE);
		RECT rc;
		if(!pItemRc || !pLVITEM){
			TRACE(_T("无法分配内存！"));
		}else{
			LVITEMA LVITEM;
			LVITEM.mask=LVIF_TEXT;
			LVITEM.cchTextMax=512;
			LVITEM.pszText=pszText;
			char ItemBuf[512];
			int nCount=::SendMessage(hDeskWnd,LVM_GETITEMCOUNT,0,0);
			for(int iItem=0;iItem<nCount;iItem++){
				LVITEM.iItem=iItem;
				LVITEM.iSubItem=0;
				//将设置好的结构插入目标进程
				WriteProcessMemory(hProcess,pLVITEM,&LVITEM,sizeof(LVITEM),NULL);
				//发送LVM_GETITEM消息
				BOOL r=(BOOL)::SendMessage(hDeskWnd,LVM_GETITEMTEXTA,iItem,(LPARAM)pLVITEM);
				//获取pszText
				ReadProcessMemory(hProcess,pszText,ItemBuf,512,NULL);
				CString str=CString(ItemBuf);
				//AfxMessageBox(str);
				if(str==strIconName){				
					::SendMessage (hDeskWnd,LVM_GETITEMRECT,iItem,(LPARAM)pItemRc);
					ReadProcessMemory(hProcess,pItemRc,&rc,sizeof(RECT),NULL);
					memcpy(lpRect,&rc,sizeof(RECT));
					bRet=TRUE;
					break;
				}

			}
			VirtualFreeEx(hProcess,pLVITEM,0,MEM_RELEASE);
			VirtualFreeEx(hProcess,pszText,0,MEM_RELEASE);
			VirtualFreeEx(hProcess,pItemRc,0,MEM_RELEASE);//释放内存
		}
		CloseHandle(hProcess);
	}
	//-----------------------------
	return bRet;
}
BOOL CIconToolTipDlg::GetIconRect64(HWND hDeskWnd,CString strIconName,LPRECT lpRect)
{
	BOOL bRet=FALSE;
	//-----------------------------
	//遍历外部进程所有图标
	DWORD PID=0;
	GetWindowThreadProcessId(hDeskWnd,&PID);
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,false,PID);
	if(!hProcess){
		TRACE(_T("获取进程句柄操作失败hWnd=%dPID=%d"),hDeskWnd,PID);
	}else{
		LVITEM64A* pLVITEM=(LVITEM64A*)VirtualAllocEx(hProcess,NULL,sizeof(LVITEM64A),MEM_COMMIT,PAGE_READWRITE);
		char* pszText=(char*)VirtualAllocEx(hProcess,NULL,512,MEM_COMMIT,PAGE_READWRITE);
		RECT* pItemRc=(RECT*)VirtualAllocEx(hProcess,NULL,sizeof(RECT),MEM_COMMIT,PAGE_READWRITE);
		RECT rc;
		if(!pItemRc || !pLVITEM){
			TRACE(_T("无法分配内存！"));
		}else{
			LVITEM64A LVITEM;
			LVITEM.mask=LVIF_TEXT;
			LVITEM.cchTextMax=512;
			LVITEM.pszText=(INT64)pszText;
			char ItemBuf[512];
			int nCount=::SendMessage(hDeskWnd,LVM_GETITEMCOUNT,0,0);
			for(int iItem=0;iItem<nCount;iItem++){
				LVITEM.iItem=iItem;
				LVITEM.iSubItem=0;
				//将设置好的结构插入目标进程
				WriteProcessMemory(hProcess,pLVITEM,&LVITEM,sizeof(LVITEM),NULL);
				//发送LVM_GETITEM消息
				BOOL r=(BOOL)::SendMessage(hDeskWnd,LVM_GETITEMTEXTA,iItem,(LPARAM)pLVITEM);
				//获取pszText
				ReadProcessMemory(hProcess,pszText,ItemBuf,512,NULL);
				CString str=CString(ItemBuf);
				//AfxMessageBox(str);
				if(str==strIconName){				
					::SendMessage (hDeskWnd,LVM_GETITEMRECT,iItem,(LPARAM)pItemRc);
					ReadProcessMemory(hProcess,pItemRc,&rc,sizeof(RECT),NULL);
					memcpy(lpRect,&rc,sizeof(RECT));
					bRet=TRUE;
					break;
				}

			}
			VirtualFreeEx(hProcess,pLVITEM,0,MEM_RELEASE);
			VirtualFreeEx(hProcess,pszText,0,MEM_RELEASE);
			VirtualFreeEx(hProcess,pItemRc,0,MEM_RELEASE);//释放内存
		}
		CloseHandle(hProcess);
	}
	//-----------------------------
	return bRet;
}

BOOL Is64Bit_OS()
{
	BOOL bRetVal = FALSE;
	SYSTEM_INFO si = { 0 };
	LPFN_PGNSI pGNSI = (LPFN_PGNSI) GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "GetNativeSystemInfo");
	if (pGNSI == NULL)
	{
		return FALSE;
	}
	pGNSI(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || 
	si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
	{
		bRetVal = TRUE;
	}
	else
	{
		// 32 位操作系统
		//_tprintf(_T("is 32 bit OS\r\n"));
	}
	return bRetVal;
}