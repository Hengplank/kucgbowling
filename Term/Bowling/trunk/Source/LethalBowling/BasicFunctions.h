
// BasicFunctions.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "BasicFunctionsDlg.h"


// CBasicFunctionsApp:
// �� Ŭ������ ������ ���ؼ��� BasicFunctions.cpp�� �����Ͻʽÿ�.
//

class CBasicFunctionsApp : public CWinApp
{
public:
	CBasicFunctionsApp();
    ~CBasicFunctionsApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
    virtual BOOL OnIdle(LONG lCount);

private:
    CBasicFunctionsDlg* mainDialog_;
};

extern CBasicFunctionsApp theApp;