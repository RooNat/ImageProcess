#pragma once


// CHistogramDialog 对话框

class CHistogramDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDialog)

public:
	CHistogramDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHistogramDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic picture;
	CString pixel1;
	CString average1;
	CStatic standard2;
	CString Standard2;
	CString mid2;
	CString average2;
	CString pixel2;
	CString standard1;
	CString mid1;
	int T[256], nk[256], H[256];
	float fPro[256];
	//中间变量
	float temp[256]; //累计密度
	float fProT[256];//均衡化之后灰度分布概率密度变量
	afx_msg void OnPaint();
};
