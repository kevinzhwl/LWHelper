// LWHelperDlg.h : ͷ�ļ�
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

// CLWHelperDlg �Ի���
class CLWHelperDlg : public CDialog
{
// ����
public:
	CLWHelperDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LWHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
