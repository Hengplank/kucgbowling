#pragma once


// PivotScaling ��ȭ �����Դϴ�.

class PivotScaling : public CDialog
{
	DECLARE_DYNAMIC(PivotScaling)

public:
	PivotScaling(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~PivotScaling();

	float f_pScaleX, f_pScaleY, f_pScaleZ;
	float f_pPointX, f_pPointY, f_pPointZ;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_PIVOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
