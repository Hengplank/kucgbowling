// RandomRotation.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "RandomRotation.h"


// RandomRotation ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(RandomRotation, CDialog)

RandomRotation::RandomRotation(CWnd* pParent /*=NULL*/)
	: CDialog(RandomRotation::IDD, pParent)
{
	f_sLineX = f_sLineY = f_sLineZ = 0;
	f_eLineX = f_eLineY = f_eLineZ = 0;
	f_rAngle = 0;
}

RandomRotation::~RandomRotation()
{
}

void RandomRotation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, f_sLineX);
	DDX_Text(pDX, IDC_EDIT_Y1, f_sLineY);
	DDX_Text(pDX, IDC_EDIT_Z1, f_sLineZ);
	DDX_Text(pDX, IDC_EDIT_X2, f_eLineX);
	DDX_Text(pDX, IDC_EDIT_Y2, f_eLineY);
	DDX_Text(pDX, IDC_EDIT_Z2, f_eLineZ);
	DDX_Text(pDX, IDC_EDIT_ANGLE, f_rAngle);
}


BEGIN_MESSAGE_MAP(RandomRotation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &RandomRotation::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &RandomRotation::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// RandomRotation �޽��� ó�����Դϴ�.

void RandomRotation::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void RandomRotation::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
