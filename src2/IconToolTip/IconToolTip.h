// IconToolTip.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIconToolTipApp:
// �йش����ʵ�֣������ IconToolTip.cpp
//

class CIconToolTipApp : public CWinApp
{
public:
	ULONG_PTR  m_gdiplusToken;
	
	CIconToolTipApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CIconToolTipApp theApp;