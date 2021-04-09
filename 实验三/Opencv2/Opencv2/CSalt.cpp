// CSalt.cpp: 实现文件
//

#include "stdafx.h"
#include "CSalt.h"
#include "afxdialogex.h"
#include "resource.h"

// CSalt 对话框

IMPLEMENT_DYNAMIC(CSalt, CDialogEx)

CSalt::CSalt(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, salt(0)
{

}

CSalt::~CSalt()
{
}

void CSalt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_JIAOYANSLIDER, saltslider);
	DDX_Slider(pDX, IDC_JIAOYANSLIDER, salt);
	DDV_MinMaxInt(pDX, salt, 0, 1000);
	DDX_Control(pDX, IDC_JIAOYANSTATIC, saltstatic);
}


BEGIN_MESSAGE_MAP(CSalt, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_JIAOYANSLIDER, &CSalt::OnNMCustomdrawJiaoyanslider)
END_MESSAGE_MAP()


// CSalt 消息处理程序


void CSalt::OnNMCustomdrawJiaoyanslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	a = 0.001*saltslider.GetPos();
	CString str;
	str.Format(_T("%f"), a);
	GetDlgItem(IDC_JIAOYANSTATIC)->SetWindowText(str);
	UpdateData(FALSE);
	*pResult = 0;
}


BOOL CSalt::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	saltslider.SetRange(0, 1000);
	saltslider.SetPos(20);
	CString str;
	str.Format(_T("%f"), 0.02);
	GetDlgItem(IDC_JIAOYANSTATIC)->SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
