// LightColor.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "LightColor.h"


// LightColor ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(LightColor, CDialog)

LightColor::LightColor(CWnd* pParent /*=NULL*/)
	: CDialog(LightColor::IDD, pParent)
{
	f_ambientR = 0.2, f_ambientG = 0.2, f_ambientB = 0.2, f_ambientA = 1.0;
	f_diffuseR = 0.6, f_diffuseG = 0.6, f_diffuseB = 0.6, f_diffuseA = 1.0;
	f_specularR = 1.0, f_specularG = 1.0, f_specularB = 0.5, f_specularA = 1.0;
}

LightColor::~LightColor()
{
}

void LightColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AMBIENT_R, f_ambientR);
	DDX_Text(pDX, IDC_EDIT_AMBIENT_G, f_ambientG);
	DDX_Text(pDX, IDC_EDIT_AMBIENT_B, f_ambientB);
	DDX_Text(pDX, IDC_EDIT_AMBIENT_A, f_ambientA);
	DDX_Text(pDX, IDC_EDIT_DIFFUSE_R, f_diffuseR);
	DDX_Text(pDX, IDC_EDIT_DIFFUSE_G, f_diffuseG);
	DDX_Text(pDX, IDC_EDIT_DIFFUSE_B, f_diffuseB);
	DDX_Text(pDX, IDC_EDIT_DIFFUSE_A, f_diffuseA);
	DDX_Text(pDX, IDC_EDIT_SPECULAR_R, f_specularR);
	DDX_Text(pDX, IDC_EDIT_SPECULAR_G, f_specularG);
	DDX_Text(pDX, IDC_EDIT_SPECULAR_B, f_specularB);
	DDX_Text(pDX, IDC_EDIT_SPECULAR_A, f_specularA);
}


BEGIN_MESSAGE_MAP(LightColor, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &LightColor::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &LightColor::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// LightColor �޽��� ó�����Դϴ�.

void LightColor::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void LightColor::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
