#pragma once
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CTransDlg 视图

class CTransDlg : public CFormView
{
	DECLARE_DYNCREATE(CTransDlg)

protected:
	CTransDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CTransDlg();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
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
	CString zoomstatic;
	COpencvMFCView *view;
	CString height;
	CString width;
	/*afx_msg void OnNMCustomdrawXslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawYslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawAngslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawAllslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedZoombutton();
	afx_msg void OnBnClickedConverbutton();
	afx_msg void OnBnClickedInverbutton();*/
	virtual void OnInitialUpdate();
};


