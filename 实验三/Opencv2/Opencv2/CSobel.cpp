// CSobel.cpp: 实现文件
//

#include "stdafx.h"
#include "CSobel.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CSobel 对话框
extern Mat myImage;
extern Mat rawImage2;
IMPLEMENT_DYNAMIC(CSobel, CDialogEx)

CSobel::CSobel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SobelDIALOG, pParent)
{

}

CSobel::~CSobel()
{
}

void CSobel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, T);
}


BEGIN_MESSAGE_MAP(CSobel, CDialogEx)
	ON_BN_CLICKED(IDC_PLUSBUTTON, &CSobel::OnBnClickedPlusbutton)
	ON_BN_CLICKED(IDC_Shang1, &CSobel::OnBnClickedShang1)
	ON_BN_CLICKED(IDC_Shang2, &CSobel::OnBnClickedShang2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CSobel::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CSobel 消息处理程序


void CSobel::OnBnClickedPlusbutton()
{
	image1 = myImage.clone();
	image2 = rawImage2.clone();
	view->ImageplusSegMat(image1, image2);
	plusimage = myImage.clone();
}


void CSobel::OnBnClickedShang1()
{
	plusimage = myImage.clone();
	rawImage2 = plusimage.clone();
	view->OnHuffman();
}


void CSobel::OnBnClickedShang2()
{
	rawImage2 = image3.clone();
	view->OnHuffman();
}


void CSobel::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	int t = T.GetPos();
	view->SobelMat(t);
	UpdateData(FALSE);
	*pResult = 0;
}


BOOL CSobel::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	T.SetRange(0, 255);
	T.SetPos(50);
	image3 = rawImage2.clone();
	view->SobelMat(T.GetPos());
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
