// CRegiongrow.cpp: 实现文件
//

#include "stdafx.h"
#include "CRegiongrow.h"
#include "afxdialogex.h"
#include "Resource.h"

// CRegiongrow 对话框

IMPLEMENT_DYNAMIC(CRegiongrow, CDialogEx)

CRegiongrow::CRegiongrow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG14, pParent)
	, T(0)
{

}

CRegiongrow::~CRegiongrow()
{
}

void CRegiongrow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER1, T);
	DDV_MinMaxInt(pDX, T, 0, 255);
}


BEGIN_MESSAGE_MAP(CRegiongrow, CDialogEx)
END_MESSAGE_MAP()


// CRegiongrow 消息处理程序
