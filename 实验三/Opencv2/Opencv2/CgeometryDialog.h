#pragma once
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CgeometryDialog 对话框

class CgeometryDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CgeometryDialog)

public:
	CgeometryDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CgeometryDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl xslider;
	int xslidernum;
	CSliderCtrl yslider;
	int yslidernum;
	CSliderCtrl angslider;
	int angslidernum;
	CSliderCtrl allslider;
	int allslidernum;
	CEdit heightedit;
	CEdit widthedit;
	afx_msg void OnBnClickedZoombutton();
	afx_msg void OnBnClickedConverbutton();
	afx_msg void OnBnClickedInverbutton();
	afx_msg void OnNMCustomdrawXslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawYslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawAngslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawAllslider(NMHDR *pNMHDR, LRESULT *pResult);
	CString zoomstatic;
	COpencvMFCView *view;
	CString height;
	CString width;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureXslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureYslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureAngslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureAllslider(NMHDR *pNMHDR, LRESULT *pResult);
};
