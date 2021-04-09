#pragma once


// CHuffman 对话框

class CHuffman : public CDialogEx
{
	DECLARE_DYNAMIC(CHuffman)

public:
	CHuffman(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHuffman();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Huffman };
#endif
public:
	int nColorNum; //灰度级（256）
	double *dProba;  //灰度值出现的概率
	CString *m_strCode; //哈夫曼编码表

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstTable;
	//CString m_dEntropy; //信息熵
	//CString m_dCodLength; //平均码字长
	//CString m_dRatio; //编码效率
	double m_dEntropy; //信息熵
	double m_dCodLength; //平均码字长
	double m_dRatio; //编码效率
	virtual BOOL OnInitDialog();
	double m_Cratio;
};
