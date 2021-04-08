// CtemplateDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "CtemplateDialog.h"
#include "afxdialogex.h"
#include "Resource.h"

// CtemplateDialog 对话框

IMPLEMENT_DYNAMIC(CtemplateDialog, CDialogEx)

CtemplateDialog::CtemplateDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
	, template1(_T(""))
{

}

CtemplateDialog::~CtemplateDialog()
{
}

void CtemplateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, templateBox);
	DDX_CBString(pDX, IDC_COMBO1, template1);
}


BEGIN_MESSAGE_MAP(CtemplateDialog, CDialogEx)
END_MESSAGE_MAP()


// CtemplateDialog 消息处理程序
