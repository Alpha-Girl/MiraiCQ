// MiraiQQ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMiraiQQApp:
// �йش����ʵ�֣������ MiraiQQ.cpp
//

class CMiraiQQApp : public CWinApp
{
public:
	CMiraiQQApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMiraiQQApp theApp;