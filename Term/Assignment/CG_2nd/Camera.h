#pragma once


// Camera ��ȭ �����Դϴ�.

class Camera : public CDialog
{
	DECLARE_DYNAMIC(Camera)

public:
	Camera(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Camera();

	float f_eyeX, f_eyeY, f_eyeZ;
	float f_atX, f_atY, f_atZ;
	float f_upX, f_upY, f_upZ;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_Camera_POS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
