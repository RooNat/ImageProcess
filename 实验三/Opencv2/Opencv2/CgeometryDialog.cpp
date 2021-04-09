// CgeometryDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "CgeometryDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
// CgeometryDialog 对话框

IMPLEMENT_DYNAMIC(CgeometryDialog, CDialogEx)

CgeometryDialog::CgeometryDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG10,pParent)
	, xslidernum(0)
	, yslidernum(0)
	, angslidernum(0)
	, allslidernum(0)
	, zoomstatic(_T(""))
	, height(_T(""))
	, width(_T(""))
{
	
}

CgeometryDialog::~CgeometryDialog()
{
}

void CgeometryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
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
}


BEGIN_MESSAGE_MAP(CgeometryDialog, CDialogEx)
	ON_BN_CLICKED(IDC_ZOOMBUTTON, &CgeometryDialog::OnBnClickedZoombutton)
	ON_BN_CLICKED(IDC_ConverBUTTON, &CgeometryDialog::OnBnClickedConverbutton)
	ON_BN_CLICKED(IDC_InverBUTTON, &CgeometryDialog::OnBnClickedInverbutton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_XSLIDER, &CgeometryDialog::OnNMCustomdrawXslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_YSLIDER, &CgeometryDialog::OnNMCustomdrawYslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ANGSLIDER, &CgeometryDialog::OnNMCustomdrawAngslider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ALLSLIDER, &CgeometryDialog::OnNMCustomdrawAllslider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_XSLIDER, &CgeometryDialog::OnNMReleasedcaptureXslider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_YSLIDER, &CgeometryDialog::OnNMReleasedcaptureYslider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ANGSLIDER, &CgeometryDialog::OnNMReleasedcaptureAngslider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ALLSLIDER, &CgeometryDialog::OnNMReleasedcaptureAllslider)
END_MESSAGE_MAP()


// CgeometryDialog 消息处理程序


void CgeometryDialog::OnBnClickedZoombutton()
{
	UpdateData(TRUE);
	int Height, Width;
	Width = _ttoi(width);
	Height = _ttoi(height);
	view->ZoomMat(Width, Height);
	UpdateData(FALSE);
}


void CgeometryDialog::OnBnClickedConverbutton()
{
	UpdateData(TRUE);
	view->ConvertMat();
	UpdateData(FALSE);
}


void CgeometryDialog::OnBnClickedInverbutton()
{
	UpdateData(TRUE);
	view->InversionMat();
	UpdateData(FALSE);
}


void CgeometryDialog::OnNMCustomdrawXslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	*pResult = 0;
	
}


void CgeometryDialog::OnNMCustomdrawYslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	*pResult = 0;
	
}


void CgeometryDialog::OnNMCustomdrawAngslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	*pResult = 0;
	
}


void CgeometryDialog::OnNMCustomdrawAllslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//UpdateData(TRUE);
	
	//UpdateData(FALSE);
	*pResult = 0;
	
}


BOOL CgeometryDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	xslider.SetRange(0, 1000);
	yslider.SetRange(0, 1000);
	angslider.SetRange(0, 360);
	allslider.SetRange(10, 200);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CgeometryDialog::OnNMReleasedcaptureXslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	int x, y;
	x = xslider.GetPos();
	y = yslider.GetPos();
	view->TransMat(x, y);
	UpdateData(FALSE);
	*pResult = 0;
}


void CgeometryDialog::OnNMReleasedcaptureYslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	int x, y;
	x = xslider.GetPos();
	y = yslider.GetPos();
	view->TransMat(x, y);
	UpdateData(FALSE);
	*pResult = 0;
}


void CgeometryDialog::OnNMReleasedcaptureAngslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	double degree;
	degree = (double)angslider.GetPos();
	view->RotateMat(degree);
	UpdateData(FALSE);
	*pResult = 0;
}


void CgeometryDialog::OnNMReleasedcaptureAllslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	double k;
	k = allslider.GetPos() * 0.01;
	CString str;
	str.Format(_T("%f"), k);
	GetDlgItem(IDC_ZOOMSTATIC)->SetWindowText(str);
	view->ZoomMat(k);
	*pResult = 0;
}
