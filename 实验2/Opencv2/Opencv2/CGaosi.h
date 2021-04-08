#pragma once


// CGaosi 对话框

class CGaosi : public CDialogEx
{
	DECLARE_DYNAMIC(CGaosi)

public:
	CGaosi(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGaosi();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CSliderCtrl Gaosislider;
	int gaosi;
	afx_msg void OnNMCustomdrawGaosislider(NMHDR *pNMHDR, LRESULT *pResult);
};
