// CGateGredDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "CGateGredDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
// CGateGredDialog 对话框

IMPLEMENT_DYNAMIC(CGateGredDialog, CDialogEx)

CGateGredDialog::CGateGredDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG12, pParent)
{

}

CGateGredDialog::~CGateGredDialog()
{
}

void CGateGredDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GateSLIDER, Gateslider);
}


BEGIN_MESSAGE_MAP(CGateGredDialog, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_GateSLIDER, &CGateGredDialog::OnNMCustomdrawGateslider)
END_MESSAGE_MAP()


// CGateGredDialog 消息处理程序


void CGateGredDialog::OnNMCustomdrawGateslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	BYTE t = Gateslider.GetPos();
	view->GateGradMat(t);
	UpdateData(FALSE);
	*pResult = 0;
}


BOOL CGateGredDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Gateslider.SetRange(0, 255);
	Gateslider.SetPos(30);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
