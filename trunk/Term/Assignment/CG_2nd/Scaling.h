#pragma once


// Scaling ��ȭ �����Դϴ�.

class Scaling : public CDialog
{
	DECLARE_DYNAMIC(Scaling)

public:
	Scaling(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Scaling();
	float f_scaleX, f_scaleY, f_scaleZ;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_SCALE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
