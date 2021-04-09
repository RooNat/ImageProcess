#pragma once
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CLogLinedlg 对话框

class CLogLinedlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogLinedlg)

public:
	CLogLinedlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLogLinedlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl Aslider1;
	CSliderCtrl Bslider1;
	CSliderCtrl Cslider1;
	int aslider;
	int bslider;
	int cslider;
	CStatic Picture;
	COpencvMFCView *view;
	virtual BOOL OnInitDialog();
	CStatic Atext;
	CStatic Btext;
	CStatic Ctext;
	CRect  rect;
	CDC * pDC;
	CWnd * pwnd;
	void DrawAxes();
	double a=50, b=0.8, c=1.05;
	afx_msg void OnNMCustomdrawASlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawBSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawCSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
};
