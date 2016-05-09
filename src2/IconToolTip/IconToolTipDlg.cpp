// IconToolTipDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IconToolTip.h"
#include "IconToolTipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIconToolTipDlg �Ի���




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


// CIconToolTipDlg ��Ϣ�������

BOOL CIconToolTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_EditBox1.SetWindowText(_T("����վ"));
	m_EditBox2.SetWindowText(_T("�������Ѿ�ɾ�����ļ����ļ���"));

	int x=8;
	int y=220;
	m_LinkStatic.CreateEx(0,_T("SysLink")
		,_T("�������:��ѧ�� <a href=\"http://www.it608.com/\">CSDN����</a> <a href=\"http://t.qq.com/dengxuebin\">��Ѷ΢��</a>")
		,WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,CRect(x,y,x+300,y+40),this,IDC_SYSLINK1);
	HFONT hFont=(HFONT)GetStockObject(DEFAULT_GUI_FONT); 
	m_LinkStatic.SendMessage(WM_SETFONT,(WPARAM)hFont);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CIconToolTipDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	PNMLINK pNMLink = (PNMLINK) pNMHDR;
	ShellExecuteW(NULL, L"open", pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL); 
	*pResult = 0;
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIconToolTipDlg::OnPaint()
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
HCURSOR CIconToolTipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIconToolTipDlg::OnBnClickedButton1()
{
	if(::IsWindow(m_TipWindow.m_hWnd)){//���֮ǰ�Ѿ���������ʾ����
		m_TipWindow.DestroyWindow();//������ʾ����
	}
	//===================================
	CString strIconName,StrTipText;
	m_EditBox1.GetWindowText(strIconName);
	m_EditBox2.GetWindowText(StrTipText);
	CRect IconRect;
	HWND hDeskListView;
	BOOL bRet=GetIconRect(strIconName,&IconRect,hDeskListView);
	if(!bRet){
		AfxMessageBox(_T("û�ҵ�ָ��������ͼ��"));
		return;
	}else{
		//CString str;
		//str.Format(_T("����ͼ��λ��: Left=%d Top=%d w=%d h=%d"),IconRect.left,IconRect.top,IconRect.Width(),IconRect.Height());
		//AfxMessageBox(str);
	}
	//===================================
	m_TipWindow.ShowDesktop();//��ʾ����
	m_TipWindow.Create(hDeskListView,IconRect,StrTipText);
}
//==ȡ����ͼ��λ��=======================
BOOL CIconToolTipDlg::GetIconRect(CString strIconName,LPRECT lpRect,HWND &hDeskListView)
{
	
	HWND hDeskWnd=NULL;//������SysListView32�Ĵ��ھ��
	HWND hWnd=::FindWindow(_T("WorkerW"),NULL);//�ȵ�WIN7ϵͳ����
	while(hWnd){
		HWND hShellView=::FindWindowEx(hWnd,NULL,_T("SHELLDLL_DefView"),NULL);
		if(hShellView){
			hDeskWnd=::FindWindowEx(hShellView,NULL,_T("SysListView32"),NULL);
			break;
		}
		hWnd=::GetWindow(hWnd,GW_HWNDNEXT);
	}
	if(!hDeskWnd){//���û�ҵ����ٰ�XP��ʽ����
		hWnd=::FindWindow(_T("Progman"),_T("Program Manager"));
		if(hWnd){
			hWnd=::FindWindowEx(hWnd,NULL,_T("SHELLDLL_DefView"),NULL);
			hDeskWnd=::FindWindowEx(hWnd,NULL,_T("SysListView32"),NULL);
		}
	}
	if(!hDeskWnd){
		MessageBox(_T("�������洰�ھ��ʧ��"));
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
	//�����ⲿ��������ͼ��
	DWORD PID=0;
	GetWindowThreadProcessId(hDeskWnd,&PID);
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,false,PID);
	if(!hProcess){
		TRACE(_T("��ȡ���̾������ʧ��hWnd=%dPID=%d"),hDeskWnd,PID);
	}else{
		LVITEMA* pLVITEM=(LVITEMA*)VirtualAllocEx(hProcess,NULL,sizeof(LVITEM),MEM_COMMIT,PAGE_READWRITE);
		char* pszText=(char*)VirtualAllocEx(hProcess,NULL,512,MEM_COMMIT,PAGE_READWRITE);
		RECT* pItemRc=(RECT*)VirtualAllocEx(hProcess,NULL,sizeof(RECT),MEM_COMMIT,PAGE_READWRITE);
		RECT rc;
		if(!pItemRc || !pLVITEM){
			TRACE(_T("�޷������ڴ棡"));
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
				//�����úõĽṹ����Ŀ�����
				WriteProcessMemory(hProcess,pLVITEM,&LVITEM,sizeof(LVITEM),NULL);
				//����LVM_GETITEM��Ϣ
				BOOL r=(BOOL)::SendMessage(hDeskWnd,LVM_GETITEMTEXTA,iItem,(LPARAM)pLVITEM);
				//��ȡpszText
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
			VirtualFreeEx(hProcess,pItemRc,0,MEM_RELEASE);//�ͷ��ڴ�
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
	//�����ⲿ��������ͼ��
	DWORD PID=0;
	GetWindowThreadProcessId(hDeskWnd,&PID);
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,false,PID);
	if(!hProcess){
		TRACE(_T("��ȡ���̾������ʧ��hWnd=%dPID=%d"),hDeskWnd,PID);
	}else{
		LVITEM64A* pLVITEM=(LVITEM64A*)VirtualAllocEx(hProcess,NULL,sizeof(LVITEM64A),MEM_COMMIT,PAGE_READWRITE);
		char* pszText=(char*)VirtualAllocEx(hProcess,NULL,512,MEM_COMMIT,PAGE_READWRITE);
		RECT* pItemRc=(RECT*)VirtualAllocEx(hProcess,NULL,sizeof(RECT),MEM_COMMIT,PAGE_READWRITE);
		RECT rc;
		if(!pItemRc || !pLVITEM){
			TRACE(_T("�޷������ڴ棡"));
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
				//�����úõĽṹ����Ŀ�����
				WriteProcessMemory(hProcess,pLVITEM,&LVITEM,sizeof(LVITEM),NULL);
				//����LVM_GETITEM��Ϣ
				BOOL r=(BOOL)::SendMessage(hDeskWnd,LVM_GETITEMTEXTA,iItem,(LPARAM)pLVITEM);
				//��ȡpszText
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
			VirtualFreeEx(hProcess,pItemRc,0,MEM_RELEASE);//�ͷ��ڴ�
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
		// 32 λ����ϵͳ
		//_tprintf(_T("is 32 bit OS\r\n"));
	}
	return bRetVal;
}