#pragma once


// AxisRotation ��ȭ �����Դϴ�.

class AxisRotation : public CDialog
{
	DECLARE_DYNAMIC(AxisRotation)

public:
	AxisRotation(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~AxisRotation();

	float f_aRotateX, f_aRotateY, f_aRotateZ;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_AXIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
