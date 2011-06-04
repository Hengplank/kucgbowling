// PivotScaling.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "PivotScaling.h"


// PivotScaling ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(PivotScaling, CDialog)

PivotScaling::PivotScaling(CWnd* pParent /*=NULL*/)
	: CDialog(PivotScaling::IDD, pParent)
{
	f_pScaleX = f_pScaleY = f_pScaleZ = 1;
	f_pPointX = f_pPointY = f_pPointZ = 0;
}

PivotScaling::~PivotScaling()
{
}

void PivotScaling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_pScaleX);
	DDX_Text(pDX, IDC_EDIT_Y, f_pScaleY);
	DDX_Text(pDX, IDC_EDIT_Z, f_pScaleZ);
	DDX_Text(pDX, IDC_EDIT_PIVOT_X, f_pPointX);
	DDX_Text(pDX, IDC_EDIT_PIVOT_Y, f_pPointY);
	DDX_Text(pDX, IDC_EDIT_PIVOT_Z, f_pPointZ);
}


BEGIN_MESSAGE_MAP(PivotScaling, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &PivotScaling::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &PivotScaling::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// PivotScaling �޽��� ó�����Դϴ�.

void PivotScaling::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void PivotScaling::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
