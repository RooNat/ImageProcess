﻿#pragma once


// CRegiongrow 对话框

class CRegiongrow : public CDialogEx
{
	DECLARE_DYNAMIC(CRegiongrow)

public:
	CRegiongrow(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegiongrow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG14 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int T;
};
