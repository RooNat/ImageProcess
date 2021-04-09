// CPriwitt.cpp: 实现文件
//

#include "stdafx.h"
#include "CPriwitt.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CPriwitt 对话框
extern Mat myImage;
extern Mat rawImage2;
IMPLEMENT_DYNAMIC(CPriwitt, CDialogEx)

CPriwitt::CPriwitt(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PriwittDIALOG, pParent)
{

}

CPriwitt::~CPriwitt()
{
}

void CPriwitt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, T);
}


BEGIN_MESSAGE_MAP(CPriwitt, CDialogEx)
	ON_BN_CLICKED(IDC_PLUSBUTTON, &CPriwitt::OnBnClickedPlusbutton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CPriwitt::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_Shang1, &CPriwitt::OnBnClickedShang1)
	ON_BN_CLICKED(IDC_Shang2, &CPriwitt::OnBnClickedShang2)
END_MESSAGE_MAP()


// CPriwitt 消息处理程序


void CPriwitt::OnBnClickedPlusbutton()
{
	image1 = myImage.clone();
	image2 = rawImage2.clone();
	view->ImageplusSegMat(image1, image2);
	plusimage = myImage.clone();
}


void CPriwitt::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	int t = T.GetPos();
	view->PriwittMat(t);
	UpdateData(FALSE);
	*pResult = 0;
}


void CPriwitt::OnBnClickedShang1()
{
	plusimage = myImage.clone();
	rawImage2 = plusimage.clone();
	view->OnHuffman();
}


void CPriwitt::OnBnClickedShang2()
{
	rawImage2 = image3.clone();
	view->OnHuffman();
}


BOOL CPriwitt::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	T.SetRange(0, 255);
	T.SetPos(50);
	image3 = rawImage2.clone();
	view->PriwittMat(T.GetPos());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
