#pragma once


// Frustum ��ȭ �����Դϴ�.

class Frustum : public CDialog
{
	DECLARE_DYNAMIC(Frustum)

public:
	Frustum(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Frustum();

	float f_left, f_right, f_bottom, f_top, f_near, f_far;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_FRUSTUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
