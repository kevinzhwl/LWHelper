// LWHelper.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLWHelperApp:
// �йش����ʵ�֣������ LWHelper.cpp
//

class CLWHelperApp : public CWinApp
{
public:
	CLWHelperApp();

// ��д
	public:
	virtual BOOL InitInstance();

public:
	ULONG_PTR m_gdiplusToken;  
// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CLWHelperApp theApp;