#pragma once


// RandomRotation ��ȭ �����Դϴ�.

class RandomRotation : public CDialog
{
	DECLARE_DYNAMIC(RandomRotation)

public:
	RandomRotation(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~RandomRotation();

	float f_sLineX, f_sLineY, f_sLineZ;
	float f_eLineX, f_eLineY, f_eLineZ;
	float f_rAngle;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_RANDOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
