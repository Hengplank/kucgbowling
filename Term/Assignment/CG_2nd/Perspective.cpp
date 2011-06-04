// Perspective.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Perspective.h"


// Perspective ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Perspective, CDialog)

Perspective::Perspective(CWnd* pParent /*=NULL*/)
	: CDialog(Perspective::IDD, pParent)
{
	f_fov = f_aspect = f_near = f_far = 0;
}

Perspective::~Perspective()
{
}

void Perspective::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FOV, f_fov);
	DDX_Text(pDX, IDC_EDIT_ASPECT, f_aspect);
	DDX_Text(pDX, IDC_EDIT_NEAR, f_near);
	DDX_Text(pDX, IDC_EDIT_FAR, f_far);
}


BEGIN_MESSAGE_MAP(Perspective, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Perspective::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Perspective::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Perspective �޽��� ó�����Դϴ�.

void Perspective::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void Perspective::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
