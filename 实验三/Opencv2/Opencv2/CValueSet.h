#pragma once
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CValueSet 对话框

class CValueSet : public CDialogEx
{
	DECLARE_DYNAMIC(CValueSet)

public:
	CValueSet(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CValueSet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FUDIAODIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl value;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	COpencvMFCView *view;
	virtual BOOL OnInitDialog();
};
