#pragma once


// CGenThresHold 对话框

class CGenThresHold : public CDialogEx
{
	DECLARE_DYNAMIC(CGenThresHold)

public:
	CGenThresHold(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGenThresHold();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GENSegDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int gen;
};
