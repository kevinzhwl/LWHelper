// IconToolTipDlg.h : ͷ�ļ�
//

#pragma once

#include "ToolTipEx.h"

typedef void (WINAPI *LPFN_PGNSI)(LPSYSTEM_INFO);

typedef struct tagLVITEM64A
{
	UINT mask;
	int iItem;
	int iSubItem;
	UINT state;
	UINT stateMask;
	INT64 pszText;
	int cchTextMax;
	int iImage;
	LPARAM lParam;
#if (_WIN32_IE >= 0x0300)
	int iIndent;
#endif
#if (_WIN32_WINNT >= 0x501)
	int iGroupId;
	UINT cColumns; // tile view columns
	PUINT puColumns;
#endif
} LVITEM64A, *LPLVITEM64A;

// CIconToolTipDlg �Ի���
class CIconToolTipDlg : public CDialog
{
// ����
public:
	CIconToolTipDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ICONTOOLTIP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CEdit m_EditBox1;
	CEdit m_EditBox2;
	CStatic m_LinkStatic;
	CToolTipEx m_TipWindow;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL GetIconRect(CString strIconName,LPRECT lpRect,HWND &hDeskListView);
	BOOL GetIconRect(HWND hDeskWnd,CString strIconName,LPRECT lpRect);
	BOOL GetIconRect64(HWND hDeskWnd,CString strIconName,LPRECT lpRect);
};
BOOL Is64Bit_OS();