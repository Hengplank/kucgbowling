#pragma once


// Perspective ��ȭ �����Դϴ�.

class Perspective : public CDialog
{
	DECLARE_DYNAMIC(Perspective)

public:
	Perspective(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Perspective();

	float f_fov, f_aspect, f_near, f_far;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_PERSPECTIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
