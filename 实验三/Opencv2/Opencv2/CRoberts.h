#pragma once
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CRoberts 对话框

class CRoberts : public CDialogEx
{
	DECLARE_DYNAMIC(CRoberts)

public:
	CRoberts(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRoberts();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RobertsDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl T;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPlusbutton();
	virtual BOOL OnInitDialog();
	COpencvMFCView *view;
	Mat plusimage;
	Mat image1;
	Mat image2;
	Mat image3;
	afx_msg void OnBnClickedShang1();
	afx_msg void OnBnClickedShang2();
};
