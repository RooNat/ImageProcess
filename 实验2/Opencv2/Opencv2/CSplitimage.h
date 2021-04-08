#pragma once
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CSplitimage 对话框

class CSplitimage : public CDialogEx
{
	DECLARE_DYNAMIC(CSplitimage)

public:
	CSplitimage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSplitimage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawImage1slider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawImage2slider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawLightslider(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl alp1;
	CSliderCtrl alp2;
	CSliderCtrl light;
	COpencvMFCView *view;
	Mat image1, image2;
	virtual BOOL OnInitDialog();
	CSliderCtrl Heightslider;
	CSliderCtrl Widthslider;
	CString height;
	CString width;
	afx_msg void OnNMCustomdrawHeightslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawWidthslider(NMHDR *pNMHDR, LRESULT *pResult);
};
