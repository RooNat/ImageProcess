#pragma once


// CLineNum 对话框

class CLineNum : public CDialogEx
{
	DECLARE_DYNAMIC(CLineNum)

public:
	CLineNum(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLineNum();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int Linenum;
	afx_msg void OnBnClickedOk();
};
