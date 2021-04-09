// CLineNum.cpp: 实现文件
//

#include "stdafx.h"
#include "CLineNum.h"
#include "afxdialogex.h"
#include"Resource.h"


// CLineNum 对话框

IMPLEMENT_DYNAMIC(CLineNum, CDialogEx)

CLineNum::CLineNum(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, Linenum(0)
{

}

CLineNum::~CLineNum()
{
}

void CLineNum::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMEDIT, Linenum);
	DDV_MinMaxInt(pDX, Linenum, 1, 255);
}


BEGIN_MESSAGE_MAP(CLineNum, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLineNum::OnBnClickedOk)
END_MESSAGE_MAP()


// CLineNum 消息处理程序


void CLineNum::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
