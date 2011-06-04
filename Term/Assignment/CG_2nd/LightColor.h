#pragma once


// LightColor ��ȭ �����Դϴ�.

class LightColor : public CDialog
{
	DECLARE_DYNAMIC(LightColor)

public:
	LightColor(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~LightColor();

	float f_ambientR, f_ambientG, f_ambientB, f_ambientA;
	float f_diffuseR, f_diffuseG, f_diffuseB, f_diffuseA;
	float f_specularR, f_specularG, f_specularB, f_specularA;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LIGHT_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
