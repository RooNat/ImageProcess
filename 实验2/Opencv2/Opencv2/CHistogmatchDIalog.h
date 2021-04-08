#pragma once
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CHistogmatchDIalog 对话框

class CHistogmatchDIalog : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogmatchDIalog)

public:
	float pu[256];
	float fPro[256];
	float fProT[256];
	int T[256], nk[256], H[256];
	CHistogmatchDIalog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHistogmatchDIalog();
	//COpencvMFCView *view;
	//Mat FIleimage;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreatepicture();
	
	
	CStatic hrect;
};
