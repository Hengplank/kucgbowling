#pragma once


// Translation ��ȭ �����Դϴ�.

class Translation : public CDialog
{
	DECLARE_DYNAMIC(Translation)

public:
	Translation(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Translation();
	float f_transX, f_transY, f_transZ;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_TRAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
