// OrthoGraphic.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "OrthoGraphic.h"


// OrthoGraphic ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(OrthoGraphic, CDialog)

OrthoGraphic::OrthoGraphic(CWnd* pParent /*=NULL*/)
	: CDialog(OrthoGraphic::IDD, pParent)
{
	f_left = f_right = f_bottom = f_top = f_near = f_far = 0;
}

OrthoGraphic::~OrthoGraphic()
{
}

void OrthoGraphic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LEFT, f_left);
	DDX_Text(pDX, IDC_EDIT_RIGHT, f_right);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, f_bottom);
	DDX_Text(pDX, IDC_EDIT_TOP, f_top);
	DDX_Text(pDX, IDC_EDIT_NEAR, f_near);
	DDX_Text(pDX, IDC_EDIT_FAR, f_far);
}


BEGIN_MESSAGE_MAP(OrthoGraphic, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &OrthoGraphic::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &OrthoGraphic::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// OrthoGraphic �޽��� ó�����Դϴ�.

void OrthoGraphic::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void OrthoGraphic::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
