#pragma once
#include "MainFrm.h"
#include "Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
// CLineTransDialog 对话框

class CLineTransDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLineTransDialog)

public:
	//class COpencvMFCView;
	CLineTransDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLineTransDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COpencvMFCView *view;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl Minslider;
	CSliderCtrl Maxslider;
	virtual BOOL OnInitDialog();
	int minslider;
	int maxslider;
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	//CString Mintext;
	//CString Maxtext;
};
