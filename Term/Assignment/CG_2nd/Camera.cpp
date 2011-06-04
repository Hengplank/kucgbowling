// CameraPosition.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Camera.h"


// Camera ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Camera, CDialog)

Camera::Camera(CWnd* pParent /*=NULL*/)
	: CDialog(Camera::IDD, pParent)
{
	f_eyeX = -2; f_eyeY = 0; f_eyeZ = -1;
	f_atX = -1.5; f_atY = 0; f_atZ = -1.5;
	f_upX = 0; f_upY = 1; f_upZ = 0;
}

Camera::~Camera()
{
}

void Camera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POS_X, f_eyeX);
	DDX_Text(pDX, IDC_EDIT_POS_Y, f_eyeY);
	DDX_Text(pDX, IDC_EDIT_POS_Z, f_eyeZ);
	DDX_Text(pDX, IDC_EDIT_FOC_X, f_atX);
	DDX_Text(pDX, IDC_EDIT_FOC_Y, f_atY);
	DDX_Text(pDX, IDC_EDIT_FOC_Z, f_atZ);
	DDX_Text(pDX, IDC_EDIT_UP_X, f_upX);
	DDX_Text(pDX, IDC_EDIT_UP_Y, f_upY);
	DDX_Text(pDX, IDC_EDIT_UP_Z, f_upZ);
}


BEGIN_MESSAGE_MAP(Camera, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Camera::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Camera::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Camera �޽��� ó�����Դϴ�.

void Camera::OnBnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	OnOK();
}

void Camera::OnBnClickedButtonCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
