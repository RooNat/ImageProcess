// CSplitimage.cpp: 实现文件
//

#include "stdafx.h"
#include "CSplitimage.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
// CSplitimage 对话框

IMPLEMENT_DYNAMIC(CSplitimage, CDialogEx)

CSplitimage::CSplitimage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG11, pParent)
	, height(_T(""))
	, width(_T(""))
{

}

CSplitimage::~CSplitimage()
{
}

void CSplitimage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Image1SLIDER, alp1);
	DDX_Control(pDX, IDC_Image2SLIDER, alp2);
	DDX_Control(pDX, IDC_LightSLIDER, light);
	DDX_Control(pDX, IDC_HeightSLIDER, Heightslider);
	DDX_Control(pDX, IDC_WidthSLIDER, Widthslider);
	DDX_Text(pDX, IDC_heightSTATIC, height);
	DDX_Text(pDX, IDC_widthSTATIC, width);
}


BEGIN_MESSAGE_MAP(CSplitimage, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_Image1SLIDER, &CSplitimage::OnNMCustomdrawImage1slider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_Image2SLIDER, &CSplitimage::OnNMCustomdrawImage2slider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LightSLIDER, &CSplitimage::OnNMCustomdrawLightslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_HeightSLIDER, &CSplitimage::OnNMCustomdrawHeightslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_WidthSLIDER, &CSplitimage::OnNMCustomdrawWidthslider)
END_MESSAGE_MAP()


// CSplitimage 消息处理程序


void CSplitimage::OnNMCustomdrawImage1slider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	double a, b, c, positionx, positiony;
	UpdateData(TRUE);
	a = alp1.GetPos()*0.01;
	b = 1 - a;
	alp2.SetPos(b * 100);
	c = light.GetPos();
	positionx = Widthslider.GetPos()*0.01;
	positiony = Heightslider.GetPos()*0.01;
	height.Format(_T("%f"), positiony);
	width.Format(_T("%f"), positionx);
	view->ImageplusMat(image1, image2, a, b, c, positionx, positiony);
	UpdateData(FALSE);
	*pResult = 0;
}


void CSplitimage::OnNMCustomdrawImage2slider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	double a, b, c, positionx, positiony;
	UpdateData(TRUE);
	b = alp2.GetPos()*0.01;
	a = 1 - b;
	//alp1.SetPos(a*100);
	c = light.GetPos();
	positionx = Widthslider.GetPos()*0.01;
	positiony = Heightslider.GetPos()*0.01;
	height.Format(_T("%f"), positiony);
	width.Format(_T("%f"), positionx);
	view->ImageplusMat(image1, image2, a, b, c, positionx, positiony);
	UpdateData(FALSE);
	*pResult = 0;
}


void CSplitimage::OnNMCustomdrawLightslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	double a, b, c,positionx,positiony;
	UpdateData(TRUE);
	a = alp1.GetPos()*0.01;
	b = alp2.GetPos()*0.01;
	c = light.GetPos();
	positionx = Widthslider.GetPos()*0.01;
	positiony = Heightslider.GetPos()*0.01;
	height.Format(_T("%f"), positiony);
	width.Format(_T("%f"), positionx);
	view->ImageplusMat(image1, image2, a, b, c, positionx, positiony);
	UpdateData(FALSE);
	*pResult = 0;
}


BOOL CSplitimage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	alp1.SetRange(0, 100);
	alp2.SetRange(0, 100);
	light.SetRange(0, 100);
	Heightslider.SetRange(0, 100);
	Widthslider.SetRange(0, 100);
	alp1.SetPos(50);
	alp2.SetPos(50);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSplitimage::OnNMCustomdrawHeightslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	double a, b, c, positionx, positiony;
	UpdateData(TRUE);
	a = alp1.GetPos()*0.01;
	b = 1 - a;
	alp2.SetPos(b * 100);
	c = light.GetPos();
	positionx = Widthslider.GetPos()*0.01;
	positiony = Heightslider.GetPos()*0.01;
	height.Format(_T("%f"), positiony);
	width.Format(_T("%f"), positionx);
	view->ImageplusMat(image1, image2, a, b, c, positionx, positiony);
	UpdateData(FALSE);
	*pResult = 0;
}


void CSplitimage::OnNMCustomdrawWidthslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	double a, b, c, positionx, positiony;
	UpdateData(TRUE);
	a = alp1.GetPos()*0.01;
	b = 1 - a;
	alp2.SetPos(b * 100);
	c = light.GetPos();
	positionx = Widthslider.GetPos()*0.01;
	positiony = Heightslider.GetPos()*0.01;
	height.Format(_T("%f"), positiony);
	width.Format(_T("%f"), positionx);
	view->ImageplusMat(image1, image2, a, b, c, positionx, positiony);
	UpdateData(FALSE);
	*pResult = 0;
}
