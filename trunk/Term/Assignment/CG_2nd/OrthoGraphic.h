#pragma once


// OrthoGraphic ��ȭ �����Դϴ�.

class OrthoGraphic : public CDialog
{
	DECLARE_DYNAMIC(OrthoGraphic)

public:
	OrthoGraphic(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~OrthoGraphic();

	float f_left, f_right, f_bottom, f_top, f_near, f_far;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_ORTHO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
