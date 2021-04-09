// CValueSet.cpp: 实现文件
//

#include "stdafx.h"
#include "CValueSet.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CValueSet 对话框

IMPLEMENT_DYNAMIC(CValueSet, CDialogEx)

CValueSet::CValueSet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FUDIAODIALOG, pParent)
{

}

CValueSet::~CValueSet()
{
}

void CValueSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, value);
}


BEGIN_MESSAGE_MAP(CValueSet, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CValueSet::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CValueSet 消息处理程序


void CValueSet::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	int T = value.GetPos();
	view->FUDIAO(T);
	UpdateData(FALSE);
	*pResult = 0;
}


BOOL CValueSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	value.SetRange(0, 255);
	value.SetPos(128);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
