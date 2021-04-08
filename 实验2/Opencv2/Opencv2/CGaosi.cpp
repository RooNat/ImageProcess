// CGaosi.cpp: 实现文件
//

#include "stdafx.h"
#include "CGaosi.h"
#include "afxdialogex.h"
#include "Resource.h"


// CGaosi 对话框

IMPLEMENT_DYNAMIC(CGaosi, CDialogEx)

CGaosi::CGaosi(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
	, gaosi(0)
{

}

CGaosi::~CGaosi()
{
}

void CGaosi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAOSISLIDER, Gaosislider);
	DDX_Slider(pDX, IDC_GAOSISLIDER, gaosi);
	DDV_MinMaxInt(pDX, gaosi, 1, 256);
}


BEGIN_MESSAGE_MAP(CGaosi, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_GAOSISLIDER, &CGaosi::OnNMCustomdrawGaosislider)
END_MESSAGE_MAP()


// CGaosi 消息处理程序


BOOL CGaosi::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Gaosislider.SetRange(1, 256);
	Gaosislider.SetPos(32);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGaosi::OnNMCustomdrawGaosislider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	*pResult = 0;
}
