// CRoberts.cpp: 实现文件
//

#include "stdafx.h"
#include "CRoberts.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CRoberts 对话框
extern Mat myImage;
extern Mat rawImage2;
IMPLEMENT_DYNAMIC(CRoberts, CDialogEx)

CRoberts::CRoberts(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RobertsDIALOG, pParent)
{

}

CRoberts::~CRoberts()
{
}

void CRoberts::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, T);
}


BEGIN_MESSAGE_MAP(CRoberts, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CRoberts::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_PLUSBUTTON, &CRoberts::OnBnClickedPlusbutton)
	ON_BN_CLICKED(IDC_Shang1, &CRoberts::OnBnClickedShang1)
	ON_BN_CLICKED(IDC_Shang2, &CRoberts::OnBnClickedShang2)
END_MESSAGE_MAP()


// CRoberts 消息处理程序


void CRoberts::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
	UpdateData(TRUE);
	int t = T.GetPos();
	view->RobertsMat(t);
	UpdateData(FALSE);
}


void CRoberts::OnBnClickedPlusbutton()
{
	image1 = myImage.clone();
	image2 = rawImage2.clone();
	view->ImageplusSegMat(image1, image2);
	plusimage = myImage.clone();
}



BOOL CRoberts::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	T.SetRange(0, 255);
	T.SetPos(50);
	image3 = rawImage2.clone();
	view->RobertsMat(T.GetPos());
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CRoberts::OnBnClickedShang1()
{
	plusimage = myImage.clone();
	rawImage2 = plusimage.clone();
	view->OnHuffman();
}


void CRoberts::OnBnClickedShang2()
{
	rawImage2 = image3.clone();
	view->OnHuffman();
}
