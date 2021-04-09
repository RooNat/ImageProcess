// CTransDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CTransDlg.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
// CTransDlg

IMPLEMENT_DYNCREATE(CTransDlg, CFormView)

CTransDlg::CTransDlg()
	:CFormView(IDD_DIALOG10)
{

}

CTransDlg::~CTransDlg()
{
}

BEGIN_MESSAGE_MAP(CTransDlg, CFormView)
	/*ON_NOTIFY(NM_CUSTOMDRAW, IDC_XSLIDER, &CTransDlg::OnNMCustomdrawXslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_YSLIDER, &CTransDlg::OnNMCustomdrawYslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ANGSLIDER, &CTransDlg::OnNMCustomdrawAngslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ALLSLIDER, &CTransDlg::OnNMCustomdrawAllslider)
	ON_BN_CLICKED(IDC_ZOOMBUTTON, &CTransDlg::OnBnClickedZoombutton)
	ON_BN_CLICKED(IDC_ConverBUTTON, &CTransDlg::OnBnClickedConverbutton)
	ON_BN_CLICKED(IDC_InverBUTTON, &CTransDlg::OnBnClickedInverbutton)*/
END_MESSAGE_MAP()


// CTransDlg 绘图

void CTransDlg::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CTransDlg 诊断

#ifdef _DEBUG
void CTransDlg::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CTransDlg::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTransDlg 消息处理程序


void CTransDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_XSLIDER, xslider);
	DDX_Slider(pDX, IDC_XSLIDER, xslidernum);
	DDV_MinMaxInt(pDX, xslidernum, 0, 1000);
	DDX_Control(pDX, IDC_YSLIDER, yslider);
	DDX_Slider(pDX, IDC_YSLIDER, yslidernum);
	DDV_MinMaxInt(pDX, yslidernum, 0, 1000);
	DDX_Control(pDX, IDC_ANGSLIDER, angslider);
	DDX_Slider(pDX, IDC_ANGSLIDER, angslidernum);
	DDV_MinMaxInt(pDX, angslidernum, 0, 360);
	DDX_Control(pDX, IDC_ALLSLIDER, allslider);
	DDX_Slider(pDX, IDC_ALLSLIDER, allslidernum);
	DDV_MinMaxInt(pDX, allslidernum, 10, 200);
	DDX_Control(pDX, IDC_HeightEDIT, heightedit);
	DDX_Control(pDX, IDC_WidthEDIT, widthedit);
	DDX_Text(pDX, IDC_ZOOMSTATIC, zoomstatic);
	DDX_Text(pDX, IDC_HeightEDIT, height);
	DDX_Text(pDX, IDC_WidthEDIT, width);

	CFormView::DoDataExchange(pDX);
}


//void CTransDlg::OnNMCustomdrawXslider(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	UpdateData(TRUE);
//	int x, y;
//	x = xslider.GetPos();
//	y = yslider.GetPos();
//	view->TransMat(x, y);
//	UpdateData(FALSE);
//	*pResult = 0;
//}
//
//
//void CTransDlg::OnNMCustomdrawYslider(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	UpdateData(TRUE);
//	int x, y;
//	x = xslider.GetPos();
//	y = yslider.GetPos();
//	view->TransMat(x, y);
//	UpdateData(FALSE);
//	*pResult = 0;
//}
//
//
//void CTransDlg::OnNMCustomdrawAngslider(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	UpdateData(TRUE);
//	double degree;
//	degree = (double)angslider.GetPos();
//	view->RotateMat(degree);
//	UpdateData(FALSE);
//	*pResult = 0;
//}
//
//
//void CTransDlg::OnNMCustomdrawAllslider(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	double k;
//	k = allslider.GetPos() * 0.01;
//	CString str;
//	str.Format(_T("%f"), k);
//	GetDlgItem(IDC_ZOOMSTATIC)->SetWindowText(str);
//	view->ZoomMat(k);
//	*pResult = 0;
//	*pResult = 0;
//}
//
//
//void CTransDlg::OnBnClickedZoombutton()
//{
//	UpdateData(TRUE);
//	int Height, Width;
//	Width = _ttoi(width);
//	Height = _ttoi(height);
//	view->ZoomMat(Width, Height);
//	UpdateData(FALSE);
//}
//
//
//void CTransDlg::OnBnClickedConverbutton()
//{
//	UpdateData(TRUE);
//	view->ConvertMat();
//	UpdateData(FALSE);
//}
//
//
//void CTransDlg::OnBnClickedInverbutton()
//{
//	UpdateData(TRUE);
//	view->InversionMat();
//	UpdateData(FALSE);
//}


void CTransDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	xslider.SetRange(0, 1000);
	yslider.SetRange(0, 1000);
	angslider.SetRange(0, 360);
	allslider.SetRange(10, 200);
	// TODO: 在此添加专用代码和/或调用基类
}
