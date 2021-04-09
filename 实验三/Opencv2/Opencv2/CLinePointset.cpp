// CLinePointset.cpp: 实现文件
//
//分段线性增强
#include "stdafx.h"
#include "CLinePointset.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
#include "Resource.h"


// CLinePointset 对话框

IMPLEMENT_DYNAMIC(CLinePointset, CDialogEx)

CLinePointset::CLinePointset(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CLinePointset::~CLinePointset()
{
	int n = p_MyStatics.GetSize();
	for (int i = 0;i < n;i++)
	{
		CStatic* pStatic = (CStatic*)p_MyStatics.GetAt(i);
		//	pStatic->DestroyWindow();
		if (pStatic != NULL)
			delete pStatic;
		p_MyStatics[i] = NULL;
	}
	p_MyStatics.RemoveAll();
	n = p_sMyEdits.GetSize();
	for (int i = 0;i < n;i++)
	{
		CEdit* pEdit = (CEdit*)p_sMyEdits.GetAt(i);
		//pEdit->DestroyWindow();
		if (pEdit != NULL)
			delete pEdit;
		p_sMyEdits[i] = NULL;
	}
	p_sMyEdits.RemoveAll();
	n= p_tMyEdits.GetSize();
	for (int i = 0;i < n;i++)
	{
		CEdit* pEdit = (CEdit*)p_tMyEdits.GetAt(i);
		//pEdit->DestroyWindow();
		if (pEdit != NULL)
			delete pEdit;
		p_tMyEdits[i] = NULL;
	}
	p_tMyEdits.RemoveAll();
	n = p_ss.GetSize();
	for (int i = 0;i < n;i++)
	{
		CStatic* pStatic = (CStatic*)p_ss.GetAt(i);
		//	pStatic->DestroyWindow();
		if (pStatic != NULL)
			delete pStatic;
		p_ss[i] = NULL;
	}
	p_ss.RemoveAll();
	n = p_ts.GetSize();
	for (int i = 0;i < n;i++)
	{
		CStatic* pStatic = (CStatic*)p_ts.GetAt(i);
		//	pStatic->DestroyWindow();
		if (pStatic != NULL)
			delete pStatic;
		p_ts[i] = NULL;
	}
	p_ts.RemoveAll();
}

void CLinePointset::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLinePointset, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLinePointset::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLinePointset 消息处理程序


BOOL CLinePointset::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		// TODO: 在此添加控件通知处理程序代码
	CString m_staticCaption;
	CString m_s, m_t;
	CRect rect, rect2;
	GetClientRect(&rect);
	GetDlgItem(IDC_BUTTON1)->GetWindowRect(&rect2);
	ScreenToClient(&rect2);

	int m_counts = Linenum;
	int perWidth = rect.Width() / 6;
	int perHeight = rect2.top / (m_counts);
	CStatic *p_MyStatic;
	CStatic *p_s, *p_t;
	CEdit *p_sMyEdit;
	CEdit *p_tMyEdit;

	for (int i = 1;i < m_counts;i++)
	{
		p_MyStatic = new CStatic();
		p_s = new CStatic();
		p_t = new CStatic();
		p_sMyEdit = new CEdit();
		p_tMyEdit = new CEdit();
		m_staticCaption.Format(_T("第%d个分段点:"), i );
		p_MyStatic->Create(m_staticCaption, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, i*perHeight + 5, perWidth, 
			(i+1)*perHeight), this);
		m_s.Format(_T("s[%d]的值:"), i );
		p_s->Create(m_s, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(perWidth, i*perHeight + 5, perWidth * 2, 
			(i + 1)*perHeight), this);
		p_sMyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(perWidth*2, i*perHeight + 5, perWidth * 3,
			(i + 1)*perHeight), this, EDIT_ID + i);
		m_t.Format(_T("t[%d]的值:"), i);
		p_t->Create(m_t, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(perWidth*3, i*perHeight + 5, perWidth * 4, 
			(i + 1)*perHeight), this);
		p_tMyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(perWidth * 4, i*perHeight + 5, perWidth * 5, 
			(i + 1)*perHeight ), this, EDIT_ID2 + i);
		//p_MyEdit->SetWindowText(m_staticCaption);
		if (p_MyStatic != NULL)
		{
			p_MyStatics.Add((void*)p_MyStatic);
		}
		if (p_s != NULL)
		{
			p_ss.Add((void*)p_s);
		}
		if (p_t != NULL)
		{
			p_ts.Add((void*)p_t);
		}
		if (p_sMyEdit != NULL)
		{
			p_sMyEdits.Add((void*)p_sMyEdit);
		}
		if (p_tMyEdit != NULL)
		{
			p_tMyEdits.Add((void*)p_tMyEdit);
		}
	}

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLinePointset::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 1;i < Linenum;i++)
	{
		CEdit *s1, *t1;
		s1= (CEdit*)GetDlgItem(EDIT_ID + i);
		t1= (CEdit*)GetDlgItem(EDIT_ID2 + i);
		CString str1, str2;
		s1->GetWindowText(str1);
		t1->GetWindowText(str2);
		s[i] = _ttoi(str1);
		t[i]=  _ttoi(str2);
	}
	s[0] = 0;t[0] = 0;
	s[Linenum] = 255;t[Linenum] = 255;
	view->SegLineTransMat(Linenum, s, t);
}
