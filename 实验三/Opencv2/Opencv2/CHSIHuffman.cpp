// CHSIHuffman.cpp: 实现文件
//

#include "stdafx.h"
#include "CHSIHuffman.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <math.h>

// CHSIHuffman 对话框

IMPLEMENT_DYNAMIC(CHSIHuffman, CDialogEx)

CHSIHuffman::CHSIHuffman(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HSI_Huffman, pParent)
	/*, m_dHsiEntropy(_T(""))
	, m_HsiCodelength(_T(""))
	, m_HsiRadio(_T(""))*/
	/*, m_Cratio(_T(""))*/
{
	m_dHsiEntropy = 0.0;
	m_HsiCodelength = 0.0;
	m_dHsiEntropy = 0.0;
	m_Cratio = 0.0;
}

CHSIHuffman::~CHSIHuffman()
{
}

void CHSIHuffman::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_HSI_Table, m_lst_hsi_table);
	DDX_Text(pDX, IDC_ShangHSIEDIT, m_dHsiEntropy);
	DDX_Text(pDX, IDC_AverageHSIEDIT, m_HsiCodelength);
	DDX_Text(pDX, IDC_EncodevHSIEDIT, m_HsiRadio);
	DDX_Text(pDX, IDC_CRatio_EDIT, m_Cratio);
}


BEGIN_MESSAGE_MAP(CHSIHuffman, CDialogEx)
END_MESSAGE_MAP()


// CHSIHuffman 消息处理程序


BOOL CHSIHuffman::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LONG	i;
	LONG	j;
	LONG	k;
	
	// 中间变量
	double	dT;

	// 字符串变量
	CString	str2View;

	// 控件ListCtrl的ITEM
	LV_ITEM lvItem;

	// 保存控件ListCtrl中添加的ITEM编号
	int		nItem2View;

	// 保存计算中间结果的数组
	double *	dTemp;

	// 数组用来存放灰度值和其位置之间的映射
	int	*	n4Turn;

	m_dHsiEntropy = 0.0;  //信息熵
	m_HsiCodelength = 0.0; //平均码字长

	// 分配内存
	m_strCode = new CString[nColorNum]; //哈夫曼编码表
	n4Turn = new int[nColorNum]; //灰度值和其位置之间的映射
	dTemp = new double[nColorNum]; //保存计算中间结果的数组

	// 令dTemp赋值
	// 开始的灰度值按灰度值大小排列相同
	for (i = 0; i < nColorNum; i++)
	{
		dTemp[i] = dProba[i];
		n4Turn[i] = i;
	}

	// 用冒泡法对进行灰度值出现的概率排序
	// 同时改变灰度值位置的映射关系
	for (j = 0; j < nColorNum - 1; j++)
	{
		for (i = 0; i < nColorNum - j - 1; i++)
		{
			if (dTemp[i] > dTemp[i + 1])
			{
				dT = dTemp[i];
				dTemp[i] = dTemp[i + 1];
				dTemp[i + 1] = dT;

				// 将i和i+1灰度的位置值互换
				for (k = 0; k < nColorNum; k++)
				{
					if (n4Turn[k] == i)
						n4Turn[k] = i + 1;
					else if (n4Turn[k] == i + 1)
						n4Turn[k] = i;
				}
			}
		}
	}

	/*******************************************************
	计算哈夫曼编码表
	*******************************************************/

	// 从概率大于0处开始编码
	for (i = 0; i < nColorNum - 1; i++)
	{
		if (dTemp[i] > 0)
			break;
	}

	for (; i < nColorNum - 1; i++)
	{
		// 更新m_strCode
		for (k = 0; k < nColorNum; k++)
		{
			// 灰度值是否i
			if (n4Turn[k] == i)
			{
				// 灰度值较小的码字加1
				m_strCode[k] = L"1" + m_strCode[k];
			}
			else if (n4Turn[k] == i + 1)
			{
				// 灰度值较小的码字加0
				m_strCode[k] = L"0" + m_strCode[k];
			}
		}
		// 概率最小的两个概率相加，保存在dTemp[i + 1]中
		dTemp[i + 1] += dTemp[i];

		// 改变映射关系
		for (k = 0; k < nColorNum; k++)
		{
			// 将位置为i的灰度值i改为灰度值i+1
			if (n4Turn[k] == i)
				n4Turn[k] = i + 1;
		}

		// 重新排序
		for (j = i + 1; j < nColorNum - 1; j++)
		{
			if (dTemp[j] > dTemp[j + 1])
			{
				// 互换
				dT = dTemp[j];
				dTemp[j] = dTemp[j + 1];
				dTemp[j + 1] = dT;

				// // 将i和i+1灰度的位置值互换
				for (k = 0; k < nColorNum; k++)
				{
					if (n4Turn[k] == j)
						n4Turn[k] = j + 1;
					else if (n4Turn[k] == j + 1)
						n4Turn[k] = j;
				}
			}
			else
				// 退出循环
				break;
		}
	}

	// 计算图像熵
	for (i = 0; i < nColorNum; i++)
	{
		if (dProba[i] > 0)
		{
			// 计算图像熵
			m_dHsiEntropy -= dProba[i] * log(dProba[i]) / log(2.0);
		}
	}

	// 计算平均码字长度
	for (i = 0; i < nColorNum; i++)
	{
		// 累加
		m_HsiCodelength += dProba[i] * m_strCode[i].GetLength();
	}

	m_Cratio = 1 - m_HsiCodelength / 8;

	// 计算编码效率
	m_HsiRadio = m_dHsiEntropy / m_HsiCodelength; //信息熵/码字长

	// 保存变动
	UpdateData(FALSE);

	/*************************************************
	输出计算结果
	*************************************************/

	// 设置CListCtrl控件样式
	m_lst_hsi_table.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	// 给List控件添加Header
	m_lst_hsi_table.InsertColumn(0, L"灰度值", LVCFMT_LEFT, 60, 0);
	m_lst_hsi_table.InsertColumn(1, L"概率值", LVCFMT_LEFT, 78, 0);
	m_lst_hsi_table.InsertColumn(2, L"哈夫曼编码", LVCFMT_LEFT, 110, 1);
	m_lst_hsi_table.InsertColumn(3, L"码字长度", LVCFMT_LEFT, 78, 2);

	// 设置样式为文本
	lvItem.mask = LVIF_TEXT;

	// 添加显示
	for (i = 0; i < nColorNum; i++)
	{
		// 第一列显示
		lvItem.iItem = m_lst_hsi_table.GetItemCount();
		str2View.Format(_T("%u"), i);
		lvItem.iSubItem = 0;
		lvItem.pszText = (LPTSTR)(LPCTSTR)str2View;
		nItem2View = m_lst_hsi_table.InsertItem(&lvItem);

		// 其它列显示
		lvItem.iItem = nItem2View;

		// 添加灰度值的概率值
		lvItem.iSubItem = 1;
		str2View.Format(_T("%f"), dProba[i]);
		lvItem.pszText = (LPTSTR)(LPCTSTR)str2View;
		m_lst_hsi_table.SetItem(&lvItem);

		// 添加哈夫曼编码
		lvItem.iSubItem = 2;
		lvItem.pszText = (LPTSTR)(LPCTSTR)m_strCode[i];
		m_lst_hsi_table.SetItem(&lvItem);

		// 添加码字长度
		lvItem.iSubItem = 3;
		str2View.Format(_T("%u"), m_strCode[i].GetLength());
		lvItem.pszText = (LPTSTR)(LPCTSTR)str2View;
		m_lst_hsi_table.SetItem(&lvItem);
	}

	//  内存释放
	delete n4Turn;
	delete dTemp;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
