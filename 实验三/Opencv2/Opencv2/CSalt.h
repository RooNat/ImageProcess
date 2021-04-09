#pragma once


// CSalt 对话框

class CSalt : public CDialogEx
{
	DECLARE_DYNAMIC(CSalt)

public:
	CSalt(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSalt();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl saltslider;
	float a;
	int salt;
	afx_msg void OnNMCustomdrawJiaoyanslider(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CStatic saltstatic;
};
