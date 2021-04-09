#pragma once
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CGateGredDialog 对话框

class CGateGredDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CGateGredDialog)

public:
	CGateGredDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGateGredDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG12 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl Gateslider;
	afx_msg void OnNMCustomdrawGateslider(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	COpencvMFCView *view;
};
