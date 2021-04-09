// CLineTransDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "CLineTransDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
#include "Resource.h"
// CLineTransDialog 对话框

IMPLEMENT_DYNAMIC(CLineTransDialog, CDialogEx)

CLineTransDialog::CLineTransDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, minslider(0)
	, maxslider(0)
{
	
}

CLineTransDialog::~CLineTransDialog()
{
}

void CLineTransDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, Minslider);
	DDX_Control(pDX, IDC_SLIDER2, Maxslider);
	DDX_Slider(pDX, IDC_SLIDER1, minslider);
	DDV_MinMaxInt(pDX, minslider, 0, 255);
	DDX_Slider(pDX, IDC_SLIDER2, maxslider);
	DDV_MinMaxInt(pDX, maxslider, 0, 255);
}


BEGIN_MESSAGE_MAP(CLineTransDialog, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CLineTransDialog::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CLineTransDialog::OnNMCustomdrawSlider2)
END_MESSAGE_MAP()


// CLineTransDialog 消息处理程序


void CLineTransDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	int min = Minslider.GetPos();
	int max = Maxslider.GetPos();
	view->LineTransMat(min, max);
	UpdateData(FALSE);
	*pResult = 0;
}




BOOL CLineTransDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Minslider.SetRange(0, 255); //设置范围
	Maxslider.SetRange(0, 255);
	Minslider.SetPos(100);  //设置当前值
	Maxslider.SetPos(200);
	return TRUE;  
}


void CLineTransDialog::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	int min = Minslider.GetPos();
	/*CString minstr, maxstr;
	minstr.Format(_T('%d'), min);
	Mintext = minstr;*/
	int max = Maxslider.GetPos();
	/*maxstr.Format(_T('%d'), max);
	Maxtext = maxstr;*/
	//COpencvMFCView* m_pView = (COpencvMFCView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	view->LineTransMat(min, max);
	UpdateData(FALSE);
	*pResult = 0;
}
