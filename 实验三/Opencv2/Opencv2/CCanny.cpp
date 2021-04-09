// CCanny.cpp: 实现文件
//

#include "stdafx.h"
#include "CCanny.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CCanny 对话框
extern Mat myImage;
extern Mat rawImage2;
IMPLEMENT_DYNAMIC(CCanny, CDialogEx)

CCanny::CCanny(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CannyDIALOG, pParent)
{

}

CCanny::~CCanny()
{
}

void CCanny::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, sig);
	DDX_Control(pDX, IDC_SLIDER2, rl);
	DDX_Control(pDX, IDC_SLIDER3, rh);
}


BEGIN_MESSAGE_MAP(CCanny, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CCanny::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CCanny::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CCanny::OnNMCustomdrawSlider3)
	ON_BN_CLICKED(IDC_PLUSBUTTON, &CCanny::OnBnClickedPlusbutton)
	ON_BN_CLICKED(IDC_Shang1, &CCanny::OnBnClickedShang1)
	ON_BN_CLICKED(IDC_Shang2, &CCanny::OnBnClickedShang2)
END_MESSAGE_MAP()


// CCanny 消息处理程序


void CCanny::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	double sig1 = sig.GetPos()*0.01;
	double rl1 = rl.GetPos()*0.01;
	double rh1 = rh.GetPos()*0.01;
	view->CannyMat(sig1, rl1, rh1);
	UpdateData(FALSE);
	*pResult = 0;
}


void CCanny::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	double sig1 = sig.GetPos()*0.01;
	double rl1 = rl.GetPos()*0.01;
	double rh1 = rh.GetPos()*0.01;
	view->CannyMat(sig1, rl1, rh1);
	UpdateData(FALSE);
	*pResult = 0;
}


void CCanny::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	double sig1 = sig.GetPos()*0.01;
	double rl1 = rl.GetPos()*0.01;
	double rh1 = rh.GetPos()*0.01;
	view->CannyMat(sig1,rl1,rh1);
	UpdateData(FALSE);
	*pResult = 0;
}


void CCanny::OnBnClickedPlusbutton()
{
	image1 = myImage.clone();
	image2 = rawImage2.clone();
	view->ImageplusSegMat(image1, image2);
	plusimage = myImage.clone();
}


void CCanny::OnBnClickedShang1()
{
	plusimage = myImage.clone();
	rawImage2 = plusimage.clone();
	view->OnHuffman();
}


void CCanny::OnBnClickedShang2()
{
	rawImage2 = image3.clone();
	view->OnHuffman();
}


BOOL CCanny::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	sig.SetRange(0, 100);
	sig.SetPos(40);
	rl.SetRange(0, 100);
	rl.SetPos(40);
	rh.SetRange(0, 100);
	rh.SetPos(70);
	image3 = rawImage2.clone();
	view->CannyMat(sig.GetPos()*0.01, sig.GetPos()*0.01, sig.GetPos()*0.01);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
