// LWHelperDlg.h : 头文件
// Download by http://www.codefans.net

#pragma once

#define	PLAYTIME 100

typedef struct UIITEM
{
	int x;
	int y;
	int width;
	int height;
	int SrcX;
	int SrcY;
	bool Show;
} UIITEM, *PUIITEM;

typedef struct KUGOUUI
{
	UIITEM main;
	UIITEM left;
	UIITEM top;
	UIITEM right;
	UIITEM bottom;
	int width;
	int height;
	UIITEM Item[5];
} KUGOUUI, *PKUGOUUI;

// CLWHelperDlg 对话框
class CLWHelperDlg : public CDialog
{
// 构造
public:
	CLWHelperDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LWHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected: 
	KUGOUUI m_LWHelper;
	Image * m_pSrcImage;
	bool m_bTracking;
	bool m_Play;
protected:
	void InitUI(void);
	void DrawUI(void);
	void DrawItem(Graphics *g,UIITEM item);
	void PlayMouseOver();
	void PlayMouseOut();
	void ShowItem(bool bShow);
	UIITEM MakeUiItem(int x,int y,int width,int height,int SrcX,int SrcY,bool Show=false);
	void LoadResImage(int nResID,Image * &lpImage);
	void doEvents();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHover(WPARAM   wParam,   LPARAM   lParam) ;
	afx_msg LRESULT OnMouseLeave(WPARAM   wParam,   LPARAM   lParam) ;
  afx_msg void OnDropFiles(HDROP hDropInfo);
};
