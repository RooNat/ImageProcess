// CGenThresHold.cpp: 实现文件
//

#include "stdafx.h"
#include "CGenThresHold.h"
#include "afxdialogex.h"
#include "Resource.h"

// CGenThresHold 对话框

IMPLEMENT_DYNAMIC(CGenThresHold, CDialogEx)

CGenThresHold::CGenThresHold(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GENSegDIALOG, pParent)
	, gen(0)
{

}

CGenThresHold::~CGenThresHold()
{
}

void CGenThresHold::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, gen);
}


BEGIN_MESSAGE_MAP(CGenThresHold, CDialogEx)
END_MESSAGE_MAP()


// CGenThresHold 消息处理程序
