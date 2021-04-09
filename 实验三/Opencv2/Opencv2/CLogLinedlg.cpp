// CLogLinedlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CLogLinedlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

// CLogLinedlg 对话框

IMPLEMENT_DYNAMIC(CLogLinedlg, CDialogEx)

CLogLinedlg::CLogLinedlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, aslider(0)
	, bslider(0)
	, cslider(0)
{

}

CLogLinedlg::~CLogLinedlg()
{
}

void CLogLinedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_A_SLIDER, Aslider1);
	DDX_Control(pDX, IDC_B_SLIDER, Bslider1);
	DDX_Control(pDX, IDC_C_SLIDER, Cslider1);
	DDX_Slider(pDX, IDC_A_SLIDER, aslider);
	DDV_MinMaxInt(pDX, aslider, 0, 255);
	DDX_Slider(pDX, IDC_B_SLIDER, bslider);
	DDV_MinMaxInt(pDX, bslider, 0, 800);
	DDX_Slider(pDX, IDC_C_SLIDER, cslider);
	DDV_MinMaxInt(pDX, cslider, 0, 200);
	DDX_Control(pDX, IDC_PICTURESTATIC, Picture);
	DDX_Control(pDX, IDC_ASTATIC, Atext);
	DDX_Control(pDX, IDC_BSTATIC, Btext);
	DDX_Control(pDX, IDC_CSTATIC, Ctext);
}


BEGIN_MESSAGE_MAP(CLogLinedlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_A_SLIDER, &CLogLinedlg::OnNMCustomdrawASlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_B_SLIDER, &CLogLinedlg::OnNMCustomdrawBSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_C_SLIDER, &CLogLinedlg::OnNMCustomdrawCSlider)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLogLinedlg 消息处理程序


BOOL CLogLinedlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Aslider1.SetRange(0, 255);
	Bslider1.SetRange(0, 800);
	Cslider1.SetRange(0, 200);
	Aslider1.SetPos(50);
	Bslider1.SetPos(80);
	Cslider1.SetPos(105);
	//DrawAxes();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLogLinedlg::DrawAxes()
{
	int x = rect.right - rect.left;
	int y = rect.bottom - rect.top;

	pDC->MoveTo(40, y - 150);
	pDC->LineTo(x - 20, y - 150);
	pDC->LineTo(x - 25, y - 145);
	pDC->MoveTo(x - 20, y - 150);
	pDC->LineTo(x - 25, y - 155);

	pDC->MoveTo(40, y - 40);
	pDC->LineTo(40, 20);
	pDC->LineTo(35, 25);
	pDC->MoveTo(40, 20);
	pDC->LineTo(45, 25);

	//// X-axis paint
	for (int i = 40; i < x - 40; i += 5)
	{
		pDC->MoveTo(i, y - 150);
		pDC->LineTo(i, y - 145);
		if (!((i - 40) % 50))
		{
			pDC->LineTo(i, y - 140);
			//CString str;
			//str.Format(_T("%d"), (i - 40) * 4);
			//pDC->SetTextColor(RGB(255, 0, 0));
			//pDC->TextOut(i - 5, y - 25, str);
		}
	}

	// Y-axis paint
	int k = 0;
	for (int i = y - 40; i > 40; i -= 5)
	{
		pDC->MoveTo(40, i);
		pDC->LineTo(35, i);
		if (!(k % 5))
		{
			pDC->LineTo(30, i);
			//CString str;
			//str.Format(_T("%d"), k);
			//pDC->SetTextColor(RGB(255, 0, 0));
			//pDC->TextOut(15, i - 8, str);
		}
		k++;
	}
	pDC->SetTextColor(RGB(0, 0, 255));
	pDC->TextOut(50, 60, _T("T(x,y)"));
	pDC->TextOut(x - 50, y - 170, _T("f(x,y)"));
}

void CLogLinedlg::OnNMCustomdrawASlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	a = Aslider1.GetPos();
	CString str1,str2,str3;
	str1.Format(_T("%f"), a);
	GetDlgItem(IDC_ASTATIC)->SetWindowText(str1);
	b = Bslider1.GetPos()*0.01;
	str2.Format(_T("%f"), b);
	GetDlgItem(IDC_BSTATIC)->SetWindowText(str2);
	c = Cslider1.GetPos()*0.01;
	str3.Format(_T("%f"), c);
	GetDlgItem(IDC_CSTATIC)->SetWindowText(str3);
	view->LogLineTransMat(a, b, c);
	UpdateData(FALSE);
	InvalidateRect(rect);
	UpdateWindow();
	*pResult = 0;
}


void CLogLinedlg::OnNMCustomdrawBSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	a = Aslider1.GetPos();
	CString str1, str2, str3;
	str1.Format(_T("%f"), a);
	GetDlgItem(IDC_ASTATIC)->SetWindowText(str1);
	b = Bslider1.GetPos()*0.01;
	str2.Format(_T("%f"), b);
	GetDlgItem(IDC_BSTATIC)->SetWindowText(str2);
	c = Cslider1.GetPos()*0.01;
	str3.Format(_T("%f"), c);
	GetDlgItem(IDC_CSTATIC)->SetWindowText(str3);
	view->LogLineTransMat(a, b, c);
	UpdateData(FALSE);
	InvalidateRect(rect);
	UpdateWindow();
	*pResult = 0;
}


void CLogLinedlg::OnNMCustomdrawCSlider(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	a = Aslider1.GetPos();
	CString str1, str2, str3;
	str1.Format(_T("%f"), a);
	GetDlgItem(IDC_ASTATIC)->SetWindowText(str1);
	b = Bslider1.GetPos()*0.01;
	str2.Format(_T("%f"), b);
	GetDlgItem(IDC_BSTATIC)->SetWindowText(str2);
	c = Cslider1.GetPos()*0.01;
	str3.Format(_T("%f"), c);
	GetDlgItem(IDC_CSTATIC)->SetWindowText(str3);
	view->LogLineTransMat(a, b, c);
	UpdateData(FALSE);
	//CWnd* pWnd = GetDlgItem(IDC_PICTURESTATIC);
	//pWnd->GetWindowRect(&rect);//得到控件客户端区域坐标
	//pwnd->GetClientRect(&rect);//得到控件客户端区域坐标
	//pWnd->ClientToScreen(rect);//将区域坐标由 控件客户区转成对话框区
	//pWnd->GetWindowRect(&rect); //直接得到控件的对话框区坐标

	//this->ScreenToClient(rect); //将区域坐标由 对话框区转成对话框客户区坐标
	InvalidateRect(rect);
	UpdateWindow();
	*pResult = 0;
}


void CLogLinedlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	pwnd = GetDlgItem(IDC_PICTURESTATIC);
	pDC = pwnd->GetDC();
	//pwnd->GetWindowRect(&rect);
	pwnd->GetClientRect(&rect);
	//pDC->FillSolidRect(&rect, RGB(255, 255, 255));
	DrawAxes();
	int s, t;
	int x = rect.right - rect.left;
	int y = rect.bottom - rect.top;
	a = Aslider1.GetPos();
	b = Bslider1.GetPos()*0.01;
	c = Cslider1.GetPos()*0.01;
	pDC->MoveTo(40, y - 150);
	for (int i = 0;i < 256;i++)
	{
		s = (double)log(i + 1) / (b*log(c)) + a + 0.5;
		pDC->LineTo(40+i, y - 150 - s);
	}
}
