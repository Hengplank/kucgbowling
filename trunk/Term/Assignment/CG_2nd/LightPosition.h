#pragma once


// LightPosition ��ȭ �����Դϴ�.

class LightPosition : public CDialog
{
	DECLARE_DYNAMIC(LightPosition)

public:
	LightPosition(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~LightPosition();

	float f_lightX, f_lightY, f_lightZ, f_isPoint;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LIGHT_POS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
