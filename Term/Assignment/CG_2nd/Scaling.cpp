// Scaling.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Scaling.h"


// Scaling ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Scaling, CDialog)

Scaling::Scaling(CWnd* pParent /*=NULL*/)
	: CDialog(Scaling::IDD, pParent)
{
	f_scaleX = f_scaleY = f_scaleZ = 1;
}

Scaling::~Scaling()
{
}

void Scaling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_scaleX);
	DDX_Text(pDX, IDC_EDIT_Y, f_scaleY);
	DDX_Text(pDX, IDC_EDIT_Z, f_scaleZ);
}


BEGIN_MESSAGE_MAP(Scaling, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Scaling::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Scaling::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Scaling �޽��� ó�����Դϴ�.

void Scaling::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void Scaling::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
