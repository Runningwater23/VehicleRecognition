
// VihecleRecognitionVS2013.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVihecleRecognitionVS2013App: 
// �йش����ʵ�֣������ VihecleRecognitionVS2013.cpp
//

class CVihecleRecognitionVS2013App : public CWinApp
{
public:
	CVihecleRecognitionVS2013App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVihecleRecognitionVS2013App theApp;