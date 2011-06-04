// AxisRotation.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "AxisRotation.h"


// AxisRotation ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(AxisRotation, CDialog)

AxisRotation::AxisRotation(CWnd* pParent /*=NULL*/)
	: CDialog(AxisRotation::IDD, pParent)
{
	f_aRotateX = f_aRotateY = f_aRotateZ = 0;
}

AxisRotation::~AxisRotation()
{
}

void AxisRotation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_aRotateX);
	DDX_Text(pDX, IDC_EDIT_Y, f_aRotateY);
	DDX_Text(pDX, IDC_EDIT_Z, f_aRotateZ);
}


BEGIN_MESSAGE_MAP(AxisRotation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &AxisRotation::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &AxisRotation::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// AxisRotation �޽��� ó�����Դϴ�.

void AxisRotation::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void AxisRotation::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
