#pragma once
#define EDIT_ID 10000
#define EDIT_ID2 20000
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
// CLinePointset 对话框

class CLinePointset : public CDialogEx
{
	DECLARE_DYNAMIC(CLinePointset)

public:
	CLinePointset(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLinePointset();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int Linenum;
	BYTE s[256], t[256];
	CPtrArray p_MyStatics;
	CPtrArray p_ss, p_ts;
	CPtrArray p_sMyEdits;
	CPtrArray p_tMyEdits;
	COpencvMFCView *view;

	afx_msg void OnBnClickedButton1();
};
