#pragma once


// CHSIHuffman 对话框

class CHSIHuffman : public CDialogEx
{
	DECLARE_DYNAMIC(CHSIHuffman)

public:
	CHSIHuffman(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHSIHuffman();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HSI_Huffman };
#endif
public:
	int nColorNum;
	double *dProba;
	CString *m_strCode;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lst_hsi_table;
	double m_dHsiEntropy;
	double m_HsiCodelength;
	double m_HsiRadio;
	virtual BOOL OnInitDialog();
	double m_Cratio;
};
