
// BasicFunctions.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "BasicFunctions.h"
#include "BasicFunctionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBasicFunctionsApp

BEGIN_MESSAGE_MAP(CBasicFunctionsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBasicFunctionsApp ����

CBasicFunctionsApp::CBasicFunctionsApp()
    : mainDialog_(nullptr)
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

CBasicFunctionsApp::~CBasicFunctionsApp()
{
    if(mainDialog_ != nullptr)
    {
        delete mainDialog_;
    }
}

// ������ CBasicFunctionsApp ��ü�Դϴ�.

CBasicFunctionsApp theApp;


// CBasicFunctionsApp �ʱ�ȭ

BOOL CBasicFunctionsApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

    mainDialog_ = new CBasicFunctionsDlg();
	m_pMainWnd = mainDialog_;

    mainDialog_->Create(IDD_BASICFUNCTIONS_DIALOG);
    mainDialog_->ShowWindow(SW_SHOW);

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return TRUE;
}



BOOL CBasicFunctionsApp::OnIdle(LONG lCount)
{
    mainDialog_->UpdateAndDraw();

    //return CWinApp::OnIdle(lCount);
    return TRUE;
}
