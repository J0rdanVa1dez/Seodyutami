
// dyutaker.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CdyutakerApp:
// �� Ŭ������ ������ ���ؼ��� dyutaker.cpp�� �����Ͻʽÿ�.
//

class CdyutakerApp : public CWinApp
{
public:
	CdyutakerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CdyutakerApp theApp;