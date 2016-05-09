#pragma once


// CToolTipEx

class CToolTipEx : public CWnd
{
	DECLARE_DYNAMIC(CToolTipEx)

public:
	CToolTipEx();
	virtual ~CToolTipEx();
public:
	CRect m_BtnRect;
public:
	BOOL Create(HWND hDeskListView,CRect IconRect,CString StrTipText);
	void LoadResImage(int nResID,Image * &lpImage);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void ShowDesktop(void);
};


