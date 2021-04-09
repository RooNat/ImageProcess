#pragma once


// CAirth 对话框

class CAirth : public CDialogEx
{
	DECLARE_DYNAMIC(CAirth)

public:
	CAirth(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAirth();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AirthDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedencode();
	afx_msg void OnBnClickeddecode();
	CEdit m_ConAirthSer;
	CString m_AirthOutput;
	CString m_AirthDecode;
	CString m_ArithSerial;
	CButton m_coding;
	CButton m_decoding;
};
