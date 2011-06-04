// Frustum.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Frustum.h"


// Frustum ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Frustum, CDialog)

Frustum::Frustum(CWnd* pParent /*=NULL*/)
	: CDialog(Frustum::IDD, pParent)
{
	f_left = f_right = f_bottom = f_top = f_near = f_far = 0;
}

Frustum::~Frustum()
{
}

void Frustum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LEFT, f_left);
	DDX_Text(pDX, IDC_EDIT_RIGHT, f_right);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, f_bottom);
	DDX_Text(pDX, IDC_EDIT_TOP, f_top);
	DDX_Text(pDX, IDC_EDIT_NEAR, f_near);
	DDX_Text(pDX, IDC_EDIT_FAR, f_far);
}


BEGIN_MESSAGE_MAP(Frustum, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Frustum::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Frustum::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Frustum �޽��� ó�����Դϴ�.

void Frustum::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void Frustum::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
