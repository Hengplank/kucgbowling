#pragma once


// PivotScaling 대화 상자입니다.

class PivotScaling : public CDialog
{
	DECLARE_DYNAMIC(PivotScaling)

public:
	PivotScaling(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~PivotScaling();

	float f_pScaleX, f_pScaleY, f_pScaleZ;
	float f_pPointX, f_pPointY, f_pPointZ;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_PIVOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
