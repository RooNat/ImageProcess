// CLaplacian.cpp: 实现文件
//

#include "stdafx.h"
#include "CLaplacian.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CLaplacian 对话框
extern Mat myImage;
extern Mat rawImage2;
IMPLEMENT_DYNAMIC(CLaplacian, CDialogEx)

CLaplacian::CLaplacian(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LaplacianDIALOG, pParent)
{

}

CLaplacian::~CLaplacian()
{
}

void CLaplacian::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, T);
}


BEGIN_MESSAGE_MAP(CLaplacian, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CLaplacian::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_PLUSBUTTON, &CLaplacian::OnBnClickedPlusbutton)
	ON_BN_CLICKED(IDC_Shang1, &CLaplacian::OnBnClickedShang1)
	ON_BN_CLICKED(IDC_Shang2, &CLaplacian::OnBnClickedShang2)
END_MESSAGE_MAP()


// CLaplacian 消息处理程序


void CLaplacian::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	int t = T.GetPos();
	view->LaplacianMat(t);
	UpdateData(FALSE);
	*pResult = 0;
}


void CLaplacian::OnBnClickedPlusbutton()
{
	image1 = myImage.clone();
	image2 = rawImage2.clone();
	view->ImageplusSegMat(image1, image2);
}


void CLaplacian::OnBnClickedShang1()
{
	plusimage = myImage.clone();
	rawImage2 = plusimage.clone();
	view->OnHuffman();
}


void CLaplacian::OnBnClickedShang2()
{
	rawImage2 = image3.clone();
	view->OnHuffman();
}


BOOL CLaplacian::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	T.SetRange(0, 255);
	T.SetPos(50);
	image3 = rawImage2.clone();
	view->LaplacianMat(T.GetPos());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
