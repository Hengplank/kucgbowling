// LightPosition.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "LightPosition.h"


// LightPosition ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(LightPosition, CDialog)

LightPosition::LightPosition(CWnd* pParent /*=NULL*/)
	: CDialog(LightPosition::IDD, pParent)
{
	f_lightX = -1.0f;
	f_lightY = 0.0f;
	f_lightZ = -3.0f;
	f_isPoint = 1.0f;
}

LightPosition::~LightPosition()
{
}

void LightPosition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_lightX);
	DDX_Text(pDX, IDC_EDIT_Y, f_lightY);
	DDX_Text(pDX, IDC_EDIT_Z, f_lightZ);
	DDX_Text(pDX, IDC_EDIT_P, f_isPoint);
}


BEGIN_MESSAGE_MAP(LightPosition, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &LightPosition::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &LightPosition::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// LightPosition �޽��� ó�����Դϴ�.

void LightPosition::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void LightPosition::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
