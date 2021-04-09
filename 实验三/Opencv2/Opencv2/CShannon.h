#pragma once


// CShannon 对话框

class CShannon : public CDialogEx
{
	DECLARE_DYNAMIC(CShannon)

public:
	CShannon(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShannon();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ShannonDIALOG };
#endif
public:
	// 灰度级别数目
	int m_nColorNum;

	// 各个灰度值出现频率
	double *	m_dProba;

	// 香农－弗诺编码表
	CString	* m_strCode;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstTable;
	double m_dEntropy;
	double m_dAvgCodelen;
	double m_dEfficiency;
	double m_Cratio;
	virtual BOOL OnInitDialog();
};
