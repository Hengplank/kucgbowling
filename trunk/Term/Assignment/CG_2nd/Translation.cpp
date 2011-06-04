// Translation.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Translation.h"


// Translation ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Translation, CDialog)

Translation::Translation(CWnd* pParent /*=NULL*/)
	: CDialog(Translation::IDD, pParent)
{
	f_transX = f_transY = f_transZ = 0;
}

Translation::~Translation()
{
}

void Translation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_transX);
	DDX_Text(pDX, IDC_EDIT_Y, f_transY);
	DDX_Text(pDX, IDC_EDIT_Z, f_transZ);
}


BEGIN_MESSAGE_MAP(Translation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Translation::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Translation::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Translation �޽��� ó�����Դϴ�.

void Translation::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void Translation::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
