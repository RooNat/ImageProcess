// CHistogmatchDIalog.cpp: 实现文件
//

#include "stdafx.h"
#include "CHistogmatchDIalog.h"
#include "opencv2/opencv.hpp"
#include "afxdialogex.h"
#include "Resource.h"
#include "MainFrm.h"
#include"Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
#include <iostream>
using namespace cv;


// CHistogmatchDIalog 对话框

IMPLEMENT_DYNAMIC(CHistogmatchDIalog, CDialogEx)

CHistogmatchDIalog::CHistogmatchDIalog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG9, pParent)
{

}

CHistogmatchDIalog::~CHistogmatchDIalog()
{
}

void CHistogmatchDIalog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HMSTATIC, hrect);
}


BEGIN_MESSAGE_MAP(CHistogmatchDIalog, CDialogEx)
	ON_BN_CLICKED(IDC_Createpicture, &CHistogmatchDIalog::OnBnClickedCreatepicture)
END_MESSAGE_MAP()


// CHistogmatchDIalog 消息处理程序





void CHistogmatchDIalog::OnBnClickedCreatepicture()
{
	CRect rect;
	GetDlgItem(IDC_HMSTATIC)->GetClientRect(&rect);
	int x1, y1, x2, y2;
	x1 = rect.left;
	y1 = rect.top;
	x2 = rect.right;
	y2 = rect.bottom;
	CWnd *pWnd = GetDlgItem(IDC_HMSTATIC);
	CDC *pDC = pWnd->GetDC();
	pDC->Rectangle(x1 + 5, y1 + 5, x2 - 5, y1 + 200);
	pDC->Rectangle(x1 + 5, y1 + 205, x2 - 5, y1 + 405);
	pDC->Rectangle(x1 + 5, y1 + 410, x2 - 5, y1 + 610);
	pDC->MoveTo(x1 + 20, y1 + 20);  //原图坐标轴
	pDC->LineTo(x1 + 20, y1 + 170);
	pDC->LineTo(x2 - 20, y1 + 170);
	pDC->LineTo(x2 - 25, y1 + 165);

	pDC->MoveTo(x2 - 20, y1 + 170);
	pDC->LineTo(x2 - 25, y1 + 175);

	pDC->MoveTo(x1 + 15, y1 + 25);
	pDC->LineTo(x1 + 20, y1 + 20);
	pDC->LineTo(x1 + 25, y1 + 25);

	int i;
	CString str;
	for (i = 0;i <= 5;i++)
	{
		pDC->MoveTo(x1 + 20 + i * 50, y1 + 170);
		pDC->LineTo(x1 + 20 + i * 50, y1 + 175);
		str.Format(_T("%d"), i * 50);
		pDC->SetTextColor(RGB(255, 0, 255));
		pDC->TextOut(x1 + 20 + 48 * i, 177, str);
		pDC->TextOut(x2 - 50, y1 + 20, _T("原图"));
	}
	for (i = 1;i <= 51;i++)
	{
		pDC->MoveTo(x1 + 20 + i * 5, y1 + 170);
		pDC->LineTo(x1 + 20 + i * 5, y1 + 173);
	}
	for (i = 1;i <= 7;i++)
	{
		pDC->MoveTo(x1 + 20, y1 + 170 - i * 20);
		pDC->LineTo(x1 + 15, y1 + 170 - i * 20);
	}
	for (i = 1;i <= 28;i++)
	{
		pDC->MoveTo(x1 + 20, y1 + 170 - i * 5);
		pDC->LineTo(x1 + 17, y1 + 170 - i * 5);
	}


	pDC->MoveTo(x1 + 20, y1 + 20 + 200);  //累计直方图坐标轴
	pDC->LineTo(x1 + 20, y1 + 170 + 200);
	pDC->LineTo(x2 - 20, y1 + 170 + 200);
	pDC->LineTo(x2 - 25, y1 + 165 + 200);

	pDC->MoveTo(x2 - 20, y1 + 170 + 200);
	pDC->LineTo(x2 - 25, y1 + 175 + 200);

	pDC->MoveTo(x1 + 15, y1 + 25 + 200);
	pDC->LineTo(x1 + 20, y1 + 20 + 200);
	pDC->LineTo(x1 + 25, y1 + 25 + 200);


	for (i = 0;i <= 5;i++)
	{
		pDC->MoveTo(x1 + 20 + i * 50, y1 + 170 + 200);
		pDC->LineTo(x1 + 20 + i * 50, y1 + 175 + 200);
		str.Format(_T("%d"), i * 50);
		pDC->SetTextColor(RGB(255, 0, 255));
		pDC->TextOut(x1 + 20 + 48 * i, 177 + 200, str);
		pDC->TextOut(x2 - 110, y1 + 220, _T("规定化模板图"));
	}
	for (i = 1;i <= 51;i++)
	{
		pDC->MoveTo(x1 + 20 + i * 5, y1 + 170 + 200);
		pDC->LineTo(x1 + 20 + i * 5, y1 + 173 + 200);
	}
	for (i = 1;i <= 7;i++)
	{
		pDC->MoveTo(x1 + 20, y1 + 170 - i * 20 + 200);
		pDC->LineTo(x1 + 15, y1 + 170 - i * 20 + 200);
	}
	for (i = 1;i <= 28;i++)
	{
		pDC->MoveTo(x1 + 20, y1 + 170 - i * 5 + 200);
		pDC->LineTo(x1 + 17, y1 + 170 - i * 5 + 200);
	}

	pDC->MoveTo(x1 + 20, y1 + 20 + 200 + 200);  //均衡化后直方图坐标轴
	pDC->LineTo(x1 + 20, y1 + 170 + 200 + 200);
	pDC->LineTo(x2 - 20, y1 + 170 + 200 + 200);
	pDC->LineTo(x2 - 25, y1 + 165 + 200 + 200);

	pDC->MoveTo(x2 - 20, y1 + 170 + 200 + 200);
	pDC->LineTo(x2 - 25, y1 + 175 + 200 + 200);

	pDC->MoveTo(x1 + 15, y1 + 25 + 200 + 200);
	pDC->LineTo(x1 + 20, y1 + 20 + 200 + 200);
	pDC->LineTo(x1 + 25, y1 + 25 + 200 + 200);


	for (i = 0;i <= 5;i++)
	{
		pDC->MoveTo(x1 + 20 + i * 50, y1 + 170 + 200 + 200);
		pDC->LineTo(x1 + 20 + i * 50, y1 + 175 + 200 + 200);
		str.Format(_T("%d"), i * 50);
		pDC->SetTextColor(RGB(255, 0, 255));
		pDC->TextOut(x1 + 20 + 48 * i, 177 + 200 + 200, str);
		pDC->TextOut(x2 - 90, y1 + 420, _T("规定化后"));
	}
	for (i = 1;i <= 51;i++)
	{
		pDC->MoveTo(x1 + 20 + i * 5, y1 + 170 + 200 + 200);
		pDC->LineTo(x1 + 20 + i * 5, y1 + 173 + 200 + 200);
	}
	for (i = 1;i <= 7;i++)
	{
		pDC->MoveTo(x1 + 20, y1 + 170 - i * 20 + 200 + 200);
		pDC->LineTo(x1 + 15, y1 + 170 - i * 20 + 200 + 200);
	}
	for (i = 1;i <= 28;i++)
	{
		pDC->MoveTo(x1 + 20, y1 + 170 - i * 5 + 200 + 200);
		pDC->LineTo(x1 + 17, y1 + 170 - i * 5 + 200 + 200);
	}
	for (i = 0;i <= 255;i++)
	{
		T[i] = (int)(fPro[i] * 140 * 100 + 0.5) / 2;
		if (T[i] > 145)
		{
			T[i] = 145;
		}
		nk[i] = (int)(pu[i] * 140 * 100 + 0.5) / 2;
		if (nk[i] > 145)
		{
			nk[i] = 145;
		}
		H[i] = (int)(fProT[i] * 140 * 100 + 0.5) / 2;
		if (H[i] > 145)
		{
			H[i] = 145;
		}
	}
	for (int i = 0;i <= 255;i++)
	{
		pDC->MoveTo(x1 + 20 + i, y1 + 170);
		pDC->LineTo(x1 + 20 + i, y1 + 170 - T[i]);
		pDC->MoveTo(x1 + 20 + i, y1 + 170 + 200);
		pDC->LineTo(x1 + 20 + i, y1 + 170 + 200 - nk[i]);
		pDC->MoveTo(x1 + 20 + i, y1 + 170 + 400);
		pDC->LineTo(x1 + 20 + i, y1 + 170 + 400 - H[i]);
	}
}
