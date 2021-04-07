
// Opencv_MFCView.cpp: COpencvMFCView 类的实现
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Opencv_MFC.h"
#endif

#include "Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define pi 3.1415926535
 Mat myImage;
 Mat Image;
 Mat rawImage;
// COpencvMFCView
 

IMPLEMENT_DYNCREATE(COpencvMFCView, CView)

BEGIN_MESSAGE_MAP(COpencvMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpencvMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Fourier, &COpencvMFCView::OnFourier)
	ON_COMMAND(ID_FourierTran, &COpencvMFCView::OnFouriertran)
	ON_COMMAND(ID_Dct, &COpencvMFCView::OnDct)
	ON_COMMAND(ID_Wal, &COpencvMFCView::OnWal)
	ON_COMMAND(ID_InverseDct, &COpencvMFCView::OnInversedct)
END_MESSAGE_MAP()

// COpencvMFCView 构造/析构

COpencvMFCView::COpencvMFCView() noexcept
{
	// TODO: 在此处添加构造代码

}

COpencvMFCView::~COpencvMFCView()
{
}

BOOL COpencvMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COpencvMFCView 绘图
void COpencvMFCView::OnDraw(CDC* pDC)
{
	COpencvMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码 
	if (pDoc->rawImage.empty())
		return;
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸
	CRect rect;
	//GetDlgItem(IDC_STATIC_Pic)->GetClientRect(&rect);
	//Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	//resize(myImage, imagedst, Size(rect.Width(), rect.Height()));
	//imshow("view", myImage);
	CImage cimage;
	MatToCimage(myImage, cimage); //将Mat类转化为CImage类用作显示，该函数的定义在Image.cpp中
	cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());
	// TODO: 在此处为本机数据添加绘制代码
}


// COpencvMFCView 打印


void COpencvMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpencvMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpencvMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COpencvMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void COpencvMFCView::MatToCimage(Mat & mat, CImage & cImage)      //将Mat图像转化为Cimage
{
	//图像宽
	int width = mat.cols;
	//图像高
	int height = mat.rows;
	//图像通道数
	int channels = mat.channels();
	cImage.Destroy();

	//创建一个CImage类型的图片对象
	if (4 == channels)
		cImage.Create(width, height, 8 * channels, 1); //PNG图片格式带alpha通道 Create创建一个CImage位图，并将其附加到之前构造的CImage对象
	else                //Create的第三个参数 位图中每个像素的比特数。通常是4、8、16、24或32。对于单色位图或遮罩可以为1。
		cImage.Create(width, height, 8 * channels);
	uchar* ps;
	//获取CImage的像素存贮区的指针
	uchar* pimg = (uchar*)cImage.GetBits(); 
	//每行的字节数,注意这个返回值有正有负
	int step = cImage.GetPitch();
	// 如果是1个通道的图像(灰度图像) DIB格式才需要对调色板设置  
	// CImage中内置了调色板，我们要对他进行赋值：
	if (1 == channels)
	{
		RGBQUAD* ColorTable;
		int MaxColors = 256;
		//这里可以通过CI.GetMaxColorTableEntries()得到大小(如果你是CI.Load读入图像的话)  
		ColorTable = new RGBQUAD[MaxColors];
		cImage.GetColorTable(0, MaxColors, ColorTable);//这里是取得指针  
		for (int i = 0; i < MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;
			//BYTE和uchar一回事，但MFC中都用它  
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}
		cImage.SetColorTable(0, MaxColors, ColorTable);
		delete[]ColorTable;
	}

	for (int i = 0; i < height; i++)
	{
		ps = mat.ptr<uchar>(i); //指向了Mat图像第i行的首地址
		for (int j = 0; j < width; j++)
		{
			if (1 == channels)
			{
				*(pimg + i * step + j) = ps[j];
			}
			else if (3 == channels)
			{
				*(pimg + i * step + j * 3) = ps[j * 3];
				*(pimg + i * step + j * 3 + 1) = ps[j * 3 + 1];
				*(pimg + i * step + j * 3 + 2) = ps[j * 3 + 2];
			}
			else if (4 == channels)
			{
				*(pimg + i * step + j * 4) = ps[j * 4];
				*(pimg + i * step + j * 4 + 1) = ps[j * 4 + 1];
				*(pimg + i * step + j * 4 + 2) = ps[j * 4 + 2];
				*(pimg + i * step + j * 4 + 3) = ps[j * 4 + 3];
			}
		}
	}
}

void COpencvMFCView::ForierMat(Mat image)
{
	COpencvMFCDoc* pDoc = GetDocument();
	SetCursor(LoadCursor(NULL, IDC_WAIT));//光标显示为处理状态
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;	
	uchar *lpSrcStartBits;	//指向源像素的指针
	lpSrcStartBits = image.ptr<uchar>(0);			// 找到图像像素起始位置	
	lSrcWidth =image.cols;					// 获取图像的宽度		
	lSrcHeight = image.rows;					// 获取图像的高度		
	lSrcLineBytes = image.step;		// 计算图像每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////		
	double dTmp;// 临时变量
	long	wid = 1, hei = 1;// 进行付立叶变换的宽度和高度，初始化为1		
	int		widpor = 0, heiPor = 0;//2的幂数	
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	long i;                 //行循环变量
	long j;                 //列循环变量	
	while (wid < lSrcWidth)// 计算进行付立叶变换的宽度和高度（2的整数次方）  把宽度和高度变换成2的整数次幂的形式
	{             //lSrcWidth为图片真正的宽度
		wid *= 2;
		widpor++;    //记录幂指数
	}
	while (hei < lSrcHeight)
	{
		hei *= 2;
		heiPor++;  //记录高的幂指数
	}
	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*wid * hei];  // 分配内存，存放空域的值   自定义的结构 专门用来存放空域的值
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*wid * hei];    //存放频域的值
	// 初始化
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData
	// 有一部分数据需要补0
	for (i = 0; i < hei; i++)         //将多余部分补0
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = 0;    //复数的实部，可理解为颜色值（在空域部分），多出的部分补0.
			pTd[i*wid + j].im = 0;    //复数的虚部
		}
	}
	for (i = 0; i < lSrcHeight; i++) 
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrcUnChr = lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			pTd[i*wid + j].re = *lpSrcUnChr;
			pTd[i*wid + j].im = 0;
		}
	}
	Fourier(pTd, lSrcWidth, lSrcHeight, pFd); //蝶形的算法。pfd是时域的值，这句执行完之后pfd是有值的。pfd要保存下来进行逆变换，转换回ptd应该接近于0

	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			dTmp = pFd[i * wid + j].re* pFd[i * wid + j].re
				+ pFd[i * wid + j].im* pFd[i * wid + j].im;
			dTmp = sqrt(dTmp);   //转换成频谱
			// 为了显示，需要对幅度的大小进行伸缩
			dTmp /= 100;//若是一片白或者一片黑，那么是数值太大，可以除大一点
			// 限制图像数据的大小
			lpSrcStartBits[i*lSrcLineBytes + j] = (unsigned char)(int)dTmp;
		}
	}
	// 为了在屏幕上显示，我们把幅度值大的部分用黑色显示
	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrcStartBits[i*lSrcLineBytes + j] = 255 - lpSrcStartBits[i*lSrcLineBytes + j];
		}
	}
		CplexNum *pCTmp, *pCTmp2;
		pFdt = new CplexNum[sizeof(CplexNum)*wid * hei];  //进行赋值以及图像空域值和时域值的保存
		pTdt = new CplexNum[sizeof(CplexNum)*wid * hei];
		for (i = 0; i < hei; i++)
		{
			for (j = 0; j < wid; j++)
			{
				pCTmp = &pFd[wid * i + j];
				pFdt[wid * i + j].re = pCTmp->re;
				pFdt[wid * i + j].im = pCTmp->im;
				pCTmp2 = &pTd[wid * i + j];
				pTdt[wid * i + j].re = pCTmp2->re;
				pTdt[wid * i + j].im = pCTmp2->im;
			}
		}
	delete pTd;// 释放内存
	delete pFd;
}

void COpencvMFCView::ForierMatRGB(Mat image, int c)
{
	COpencvMFCDoc* pDoc = GetDocument();
	SetCursor(LoadCursor(NULL, IDC_WAIT));//光标显示为处理状态
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	uchar *lpSrcStartBits;	//指向源像素的指针
	lpSrcStartBits = image.ptr<uchar>(0);			// 找到图像像素起始位置	
	lSrcWidth = image.cols;					// 获取图像的宽度		
	lSrcHeight = image.rows;					// 获取图像的高度		
	lSrcLineBytes = image.step;		// 计算图像每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////		
	double dTmp;// 临时变量
	long	wid = 1, hei = 1;// 进行付立叶变换的宽度和高度，初始化为1		
	int		widpor = 0, heiPor = 0;//2的幂数	
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	long i;                 //行循环变量
	long j;                 //列循环变量	
	while (wid < lSrcWidth)// 计算进行付立叶变换的宽度和高度（2的整数次方）  把宽度和高度变换成2的整数次幂的形式
	{             //lSrcWidth为图片真正的宽度
		wid *= 2;
		widpor++;    //记录幂指数
	}
	while (hei < lSrcHeight)
	{
		hei *= 2;
		heiPor++;  //记录高的幂指数
	}
	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*wid * hei];  // 分配内存，存放空域的值   自定义的结构 专门用来存放空域的值
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*wid * hei];    //存放频域的值
	// 初始化
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData
	// 有一部分数据需要补0
	for (i = 0; i < hei; i++)         //将多余部分补0
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = 0;    //复数的实部，可理解为颜色值（在空域部分），多出的部分补0.
			pTd[i*wid + j].im = 0;    //复数的虚部
		}
	}
	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrcUnChr = lpSrcStartBits + lSrcLineBytes * i + j;
			pTd[i*wid + j].re = *lpSrcUnChr;
			pTd[i*wid + j].im = 0;
		}
	}
	Fourier(pTd, lSrcWidth, lSrcHeight, pFd); //蝶形的算法。pfd是时域的值，这句执行完之后pfd是有值的。pfd要保存下来进行逆变换，转换回ptd应该接近于0

	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			dTmp = pFd[i * wid + j].re* pFd[i * wid + j].re
				+ pFd[i * wid + j].im* pFd[i * wid + j].im;
			dTmp = sqrt(dTmp);   //转换成频谱
			// 为了显示，需要对幅度的大小进行伸缩
			dTmp /= 100;//若是一片白或者一片黑，那么是数值太大，可以除大一点
			// 限制图像数据的大小
			lpSrcStartBits[i*lSrcLineBytes + j] = (unsigned char)(int)dTmp;
		}
	}
	// 为了在屏幕上显示，我们把幅度值大的部分用黑色显示
	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrcStartBits[i*lSrcLineBytes + j] = 255 - lpSrcStartBits[i*lSrcLineBytes + j];
			//lpSrcStartBits[i*lSrcLineBytes + j] = lpSrcStartBits[i*lSrcLineBytes + j];   
		}
	}
	if (c == 1)   //分别对BGR三个通道的值进行保存
	{
		CplexNum *pCTmp, *pCTmp2;
		pFdtB = new CplexNum[sizeof(CplexNum)*wid * hei];
		pTdtB = new CplexNum[sizeof(CplexNum)*wid * hei];
		for (i = 0; i < hei; i++)
		{
			for (j = 0; j < wid; j++)
			{
				pCTmp = &pFd[wid * i + j];
				pFdtB[wid * i + j].re = pCTmp->re;
				pFdtB[wid * i + j].im = pCTmp->im;
				pCTmp2 = &pTd[wid * i + j];
				pTdtB[wid * i + j].re = pCTmp2->re;
				pTdtB[wid * i + j].im = pCTmp2->im;
			}
		}
	}
	else if (c == 2)
	{
		CplexNum *pCTmp, *pCTmp2;
		pFdtG = new CplexNum[sizeof(CplexNum)*wid * hei];
		pTdtG = new CplexNum[sizeof(CplexNum)*wid * hei];
		for (i = 0; i < hei; i++)
		{
			for (j = 0; j < wid; j++)
			{
				pCTmp = &pFd[wid * i + j];
				pFdtG[wid * i + j].re = pCTmp->re;
				pFdtG[wid * i + j].im = pCTmp->im;
				pCTmp2 = &pTd[wid * i + j];
				pTdtG[wid * i + j].re = pCTmp2->re;
				pTdtG[wid * i + j].im = pCTmp2->im;
				//= complex<double>( pCTmp->real() , -pCTmp->imag() );
			}
		}

	}
	else
	{
		CplexNum *pCTmp, *pCTmp2;
		pFdtR = new CplexNum[sizeof(CplexNum)*wid * hei];
		pTdtR = new CplexNum[sizeof(CplexNum)*wid * hei];
		for (i = 0; i < hei; i++)
		{
			for (j = 0; j < wid; j++)
			{
				pCTmp = &pFd[wid * i + j];
				pFdtR[wid * i + j].re = pCTmp->re;
				pFdtR[wid * i + j].im = pCTmp->im;
				pCTmp2 = &pTd[wid * i + j];
				pTdtR[wid * i + j].re = pCTmp2->re;
				pTdtR[wid * i + j].im = pCTmp2->im;
				//= complex<double>( pCTmp->real() , -pCTmp->imag() );
			}
		}
	}
	
	delete pTd;// 释放内存
	delete pFd;
}


void COpencvMFCView::Fourier(CplexNum * pTd, int lWidth, int lHeight, CplexNum * pFd)
{
	//传入空域值，真实宽，高，获取频域值
	// 循环控制变量
	int	j;
	int	i;
	// 进行傅立叶变换的宽度和高度，（2的整数次幂）
	// 图像的宽度和高度不一定为2的整数次幂
	int		wid = 1;
	int 	hei = 1;
	int		widpor = 0, heiPor = 0;//2的幂数

	while (wid < lWidth)// 计算进行付立叶变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}
	while (hei < lHeight)
	{
		hei *= 2;
		heiPor++;
	}
	for (i = 0; i < hei; i++)
	{
		// x方向进行快速傅立叶变换
		FastFourierTran(&pTd[wid * i], &pFd[wid * i], widpor); //指针指向单行头部
	}
	// pFd中目前存储了pTd经过行变换的结果
	// 为了直接利用FastFourierTran，需要把pFd的二维数据转置，再一次利用FastFourierTran进行
	// 傅立叶行变换（实际上相当于对列进行傅立叶变换）
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[hei * j + i] = pFd[wid * i + j];
		}
	}

	for (j = 0; j < wid; j++)
	{
		// 对x方向进行快速傅立叶变换，实际上相当于对原来的图像数据进行列方向的
		// 傅立叶变换
		FastFourierTran(&pTd[j * hei], &pFd[j * hei], heiPor);
	}

	// pFd中目前存储了pTd经过二维傅立叶变换的结果，但是为了方便列方向
	// 的傅立叶变换，对其进行了转置，现在把结果转置回来
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[wid * i + j] = pFd[hei * j + i];
		}
	}

	memcpy(pTd, pFd, sizeof(CplexNum) * hei * wid);
}

void COpencvMFCView::FastFourierTran(CplexNum * pTd, CplexNum * pFd, int power)
{
	long i;                 //行循环变量
	long j;                 //列循环变量

	long	dotCount;// 付立叶变换点数  	
	int		k;// 循环变量		
	int		bfsize, p;// 中间变量	
	double	angle;// 角度	
	CplexNum *pWn, *temReg1, *temReg2, *temReg;

	dotCount = 1 << power;// 计算付立叶变换点数		
	pWn = new CplexNum[sizeof(CplexNum)*dotCount / 2];// 分配运算所需存储器
	temReg1 = new CplexNum[sizeof(CplexNum)*dotCount];
	temReg2 = new CplexNum[sizeof(CplexNum)*dotCount];
	for (i = 0; i < dotCount / 2; i++)// 计算加权系数
	{
		angle = -i * pi * 2 / dotCount;
		pWn[i].re = cos(angle);
		pWn[i].im = sin(angle);
	}
	memcpy(temReg1, pTd, sizeof(CplexNum)*dotCount);// 将时域点写入temReg1		
	for (k = 0; k < power; k++)// 采用蝶形算法进行快速付立叶变换
	{
		for (j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (power - k);
			for (i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				temReg2[i + p] = Add(temReg1[i + p], temReg1[i + p + bfsize / 2]);
				temReg2[i + p + bfsize / 2] = Mul(Sub(temReg1[i + p], temReg1[i + p + bfsize / 2]),
					pWn[i*(1 << k)]);
			}
		}
		temReg = temReg1;
		temReg1 = temReg2;
		temReg2 = temReg;
	}
	for (j = 0; j < dotCount; j++)// 重新排序
	{
		p = 0;
		for (i = 0; i < power; i++)
		{
			if (j&(1 << i))
			{
				p += 1 << (power - i - 1);
			}
		}
		pFd[j] = temReg1[p];
	}
	delete pWn;// 释放内存
	delete temReg1;
	delete temReg2;
}

void COpencvMFCView::InverFastFourierTran(CplexNum * pFd, CplexNum * pTd, int power)
{
	LONG	dotCount;			// 付立叶变换点数	
	int		i;				// 循环变量
	CplexNum *pX;
	dotCount = 1 << power;		// 计算付立叶变换点数		
	pX = new CplexNum[sizeof(CplexNum)*dotCount];// 分配运算所需存储器		
	memcpy(pX, pFd, sizeof(CplexNum)*dotCount);// 将频域点写入X		
	for (i = 0; i < dotCount; i++)// 求共轭
	{
		pX[i].re = pX[i].re;
		pX[i].im = -pX[i].im;
	}
	FastFourierTran(pX, pTd, power);// 调用快速付立叶变换		
	for (i = 0; i < dotCount; i++)// 求时域点的共轭
	{
		pTd[i].re = pTd[i].re / dotCount;
		pTd[i].im = -pTd[i].im / dotCount;

	}
	delete pX;				// 释放内存
}

void COpencvMFCView::InverseFourier(CplexNum * pFd, CplexNum * pTd, int lWidth, int lHeight)
{
	// 循环控制变量
	int	j;
	int	i;
	// 进行傅立叶变换的宽度和高度，（2的整数次幂）
	// 图像的宽度和高度不一定为2的整数次幂
	int		wid = 1;
	int 	hei = 1;
	int		widpor = 0, heiPor = 0;//2的幂数

	while (wid < lWidth)// 计算进行付立叶变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}
	while (hei < lHeight)
	{
		hei *= 2;
		heiPor++;
	}
	// 分配工作需要的内存空间
	CplexNum *pCWork = new CplexNum[sizeof(CplexNum)*wid * hei];

	//临时变量
	CplexNum *pCTmp;

	// 为了利用傅立叶正变换,可以把傅立叶频域的数据取共轭
	// 然后直接利用正变换，输出结果就是傅立叶反变换结果的共轭
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pCTmp = &pFd[wid * i + j];
			pCWork[wid * i + j].re = pCTmp->re;
			pCWork[wid * i + j].im = -pCTmp->im;
			//= complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// 调用傅立叶正变换
	Fourier(pCWork, lWidth, lHeight, pTd);

	// 求时域点的共轭，求得最终结果
	// 根据傅立叶变换原理，利用这样的方法求得的结果和实际的时域数据
	// 相差一个系数
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pCTmp = &pTd[wid * i + j];
			pTd[wid * i + j].re = pCTmp->re / (wid*hei);
			pTd[wid * i + j].im = -pCTmp->im / (wid*hei);

		}
	}
	delete pCWork;
}

void COpencvMFCView::InverseFourierMat(Mat image)
{
	COpencvMFCDoc* pDoc = GetDocument();
	SetCursor(LoadCursor(NULL, IDC_WAIT));//光标显示为处理状态
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	//LPSTR	lpSrcDib;		//指向源图像的指针	
	uchar *lpSrcStartBits;	//指向源像素的指针
	lpSrcStartBits = image.ptr<uchar>(0);			// 找到图像像素起始位置	
	lSrcWidth = image.cols;					// 获取图像的宽度		
	lSrcHeight = image.rows;					// 获取图像的高度		
	lSrcLineBytes = image.step;		// 计算图像每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////		
	double dTmp;// 临时变量
	long	wid = 1, hei = 1;// 进行付立叶变换的宽度和高度，初始化为1		
	int		widpor = 0, heiPor = 0;//2的幂数	
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	long i;                 //行循环变量
	long j;                 //列循环变量	
	while (wid < lSrcWidth)// 计算进行付立叶变换的宽度和高度（2的整数次方）  把宽度和高度变换成2的整数次幂的形式
	{             //lSrcWidth为图片真正的宽度
		wid *= 2;
		widpor++;    //记录幂指数
	}
	while (hei < lSrcHeight)
	{
		hei *= 2;
		heiPor++;  //记录高的幂指数
	}
	
	// 初始化
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData
	// 有一部分数据需要补0
	InverseFourier(pFdt, pTdt,lSrcWidth,lSrcHeight); //蝶形的算法。pfd是时域的值，这句执行完之后pfd是有值的。pfd要保存下来进行逆变换，转换回ptd应该接近于0

	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth ;j++)
		{
			dTmp = pTdt[i * wid + j].re* pTdt[i * wid + j].re
				+ pTdt[i * wid + j].im* pTdt[i * wid + j].im;  //直接这样实现图像是倒着的
			dTmp = sqrt(dTmp);   //转换成频谱

			// 为了显示，需要对幅度的大小进行伸缩
			//dTmp /= 100;//若是一片白或者一片黑，那么是数值太大，可以除大一点
			// 限制图像数据的大小
//			dTmp = min(dTmp, 255) ;
			lpSrcStartBits[lSrcLineBytes * (lSrcHeight - 1 - i) + j] = (unsigned char)(int)dTmp;
		}
	}
	// 为了在屏幕上显示，我们把幅度值大的部分用黑色显示
	delete pTdt;// 释放内存
	delete pFdt;
}

void COpencvMFCView::InverseFourierMatRGB(Mat image, CplexNum * pFd, CplexNum * pNd)
{
	COpencvMFCDoc* pDoc = GetDocument();
	SetCursor(LoadCursor(NULL, IDC_WAIT));//光标显示为处理状态
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	//LPSTR	lpSrcDib;		//指向源图像的指针	
	uchar *lpSrcStartBits;	//指向源像素的指针
	lpSrcStartBits = image.ptr<uchar>(0);			// 找到图像像素起始位置	
	lSrcWidth = image.cols;					// 获取图像的宽度		
	lSrcHeight = image.rows;					// 获取图像的高度		
	lSrcLineBytes = image.step;		// 计算图像每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////		
	double dTmp;// 临时变量
	long	wid = 1, hei = 1;// 进行付立叶变换的宽度和高度，初始化为1		
	int		widpor = 0, heiPor = 0;//2的幂数	
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	long i;                 //行循环变量
	long j;                 //列循环变量	
	while (wid < lSrcWidth)// 计算进行付立叶变换的宽度和高度（2的整数次方）  把宽度和高度变换成2的整数次幂的形式
	{             //lSrcWidth为图片真正的宽度
		wid *= 2;
		widpor++;    //记录幂指数
	}
	while (hei < lSrcHeight)
	{
		hei *= 2;
		heiPor++;  //记录高的幂指数https://github.com/
	}
	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*wid * hei];
	// 初始化
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData
	// 有一部分数据需要补0
	InverseFourier(pFd, pTd, lSrcWidth, lSrcHeight); //蝶形的算法。pfd是时域的值，这句执行完之后pfd是有值的。pfd要保存下来进行逆变换，转换回ptd应该接近于0

	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			dTmp = pTd[i * wid + j].re* pTd[i * wid + j].re
				+ pTd[i * wid + j].im* pTd[i * wid + j].im;  //直接这样实现图像是倒着的
			dTmp = sqrt(dTmp);   //转换成频谱

			// 为了显示，需要对幅度的大小进行伸缩
			//dTmp /= 100;//若是一片白或者一片黑，那么是数值太大，可以除大一点
			// 限制图像数据的大小
//			dTmp = min(dTmp, 255) ;
			lpSrcStartBits[lSrcLineBytes * i + j] = (unsigned char)(int)dTmp;
		}
	}
	// 为了在屏幕上显示，我们把幅度值大的部分用黑色显示
	delete pTd;// 释放内存
	delete pFd;
}

BOOL COpencvMFCView::CosTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes,int m)
{
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	long i;                 //行循环变量
	long j;                 //列循环变量 			
	long	wid = 1, hei = 1;// 进行付立叶变换的宽度和高度，初始化为1
	double	dTemp;// 中间变量	
	int		widpor = 0, heiPor = 0;//2的幂数

	while (wid < lWidth)// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}
	while (hei < lHeight)
	{
		hei *= 2;
		heiPor++;
	}
	lpSrcUnChr = new uchar[lLineBytes*wid+hei];
	double *pTd = new double[wid * hei];// 分配内存
	double *pFd = new double[wid * hei];
	for (i = 0; i < hei; i++)         //将多余部分补0 很重要！！！！！！
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j] = 0;
		}
	}
	for (i = 0; i < lHeight; i++)// 行
	{
		for (j = 0; j < lWidth; j++)// 列
		{
			// 指向第i行，第j个像素的指针
			lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * i + j; //?从哪开始读
			//lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight-1-i) + j; //?从哪开始读
			pTd[j + i * wid] = *(lpSrcUnChr);// 给时域赋值
		}
	}
	for (i = 0; i < hei; i++)
	{
		DisFCosTran(&pTd[wid * i], &pFd[wid * i], widpor);// 对y方向进行离散余弦变换
	}
	for (i = 0; i < hei; i++)// 保存计算结果
	{
		for (j = 0; j < wid; j++)
		{
			pTd[j * hei + i] = pFd[j + wid * i];
		}
	}
	for (j = 0; j < wid; j++)
	{
		DisFCosTran(&pTd[j * hei], &pFd[j * hei], heiPor);// 对x方向进行离散余弦变换
	}
	for (i = 0; i < lHeight; i++)// 行
	{
		for (j = 0; j < lWidth; j++)// 列
		{
			dTemp = fabs(pFd[i*wid + j]);// 计算频谱


			if (dTemp > 255)// 是否超过255,超过的，直接设置为255
			{
				dTemp = 255;
			}
			//lpSrcStartBits[lLineBytes*i + j] = (BYTE)dTemp;
			// 指向DIB第y行，第x个像素的指针
			//lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j; //这样图像是倒着的
			lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * i + j; //这样图像是正着的
			*(lpSrcUnChr) = (BYTE)(dTemp);// 更新源图像
		}
	}
	if (m == 0)
	{
		pTdD = new double[wid * hei];
		pFdD = new double[wid * hei];
		for (i = 0;i < hei;i++)
			for (j = 0;j < wid;j++)
			{
				pTdD[wid*i + j] = pTd[wid*i + j];
				pFdD[wid*i + j] = pFd[wid*i + j];

			}
	}
	else if (m == 1)
	{
		pTdDB = new double[wid * hei];
		pFdDB = new double[wid * hei];
		for (i = 0;i < hei;i++)
			for (j = 0;j < wid;j++)
			{
				pTdDB[wid*i + j] = pTd[wid*i + j];
				pFdDB[wid*i + j] = pFd[wid*i + j];

			}
	}
	else if (m == 2)
	{
		pTdDG = new double[wid * hei];
		pFdDG = new double[wid * hei];
		for (i = 0;i < hei;i++)
			for (j = 0;j < wid;j++)
			{
				pTdDG[wid*i + j] = pTd[wid*i + j];
				pFdDG[wid*i + j] = pFd[wid*i + j];

			}
	}
	else
	{
		pTdDR = new double[wid * hei];
		pFdDR = new double[wid * hei];
		for (i = 0;i < hei;i++)
			for (j = 0;j < wid;j++)
			{
				pTdDR[wid*i + j] = pTd[wid*i + j];
				pFdDR[wid*i + j] = pFd[wid*i + j];

			}
	}
	
	//delete pTd;// 释放内存
	//delete pFd;
	return TRUE;
}

BOOL COpencvMFCView::InvestCosTran(uchar * lpSrcStartBits, long lWidth, long lHeight, long lLineBytes, double *pTd,double *pFd)
{
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	long i;                 //行循环变量
	long j;                 //列循环变量 			
	long	wid = 1, hei = 1;// 进行付立叶变换的宽度和高度，初始化为1
	double	dTemp;// 中间变量	
	int		widpor = 0, heiPor = 0;//2的幂数

	while (wid < lWidth)// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}
	while (hei < lHeight)
	{
		hei *= 2;
		heiPor++;
	}
	for (i = 0; i < hei; i++)
	{
		InverseDisFCosTran(&pTd[wid * i], &pFd[wid * i], widpor);// 对y方向进行离散余弦变换
	}
	
	for (i = 0; i < hei; i++)// 保存计算结果
	{
		for (j = 0; j < wid; j++)
		{
			pFd[j * hei + i] = pTd[j + wid * i];
		}
	}
	
	for (j = 0; j < wid; j++)
	{
		InverseDisFCosTran(&pTd[j * hei], &pFd[j * hei], heiPor);// 对x方向进行离散余弦变换
	}
	
	for (i = 0; i < lHeight; i++)// 行
	{
		for (j = 0; j < lWidth; j++)// 列
		{
			dTemp = fabs(pTd[i*wid + j]);// 计算频谱
			if (dTemp > 255)// 是否超过255,超过的，直接设置为255
			{
				dTemp =255;
			}
			// 指向DIB第y行，第x个像素的指针
			lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * i + j; 
			//lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight-1-i) + j; //这样图像是倒着的
			//lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * j + i; //这样图像是正着的
			*(lpSrcUnChr) = (BYTE)(dTemp);// 更新源图像
		}
	}
	delete pTd;// 释放内存
	delete pFd;
	return TRUE;
}

void COpencvMFCView::DisFCosTran(double * pTd, double * pFd, int power)
{
	long i;                 //行循环变量				
	long	dotCount;// 离散余弦变换点数			
	double	dTemp;// 临时变量	
	CplexNum *temReg;
	dotCount = 1 << power;// 计算离散余弦变换点数		
	temReg = new CplexNum[sizeof(CplexNum) *dotCount * 2];// 分配内存		
	memset(temReg, 0, sizeof(CplexNum) * dotCount * 2);// 赋为0		
	for (i = 0;i < dotCount;i++)// 将时域点写入数组temReg
	{
		temReg[i].re = pTd[i];
		temReg[i].im = 0;
	}
	FastFourierTran(temReg, temReg, power + 1);// 调用快速付立叶变换		
	dTemp = 1 / sqrt((double)dotCount);// 调整系数		
	pFd[0] = temReg[0].re*dTemp;// 求pFd[0]	
	dTemp *= sqrt(2.0f);
	for (i = 1; i < dotCount; i++)// 求pFd[u]	
	{
		pFd[i] = (temReg[i].re* cos(i*pi / (dotCount * 2)) + temReg[i].im* sin(i*pi / (dotCount * 2))) * dTemp;
	}
	delete temReg;// 释放内存
	
}

void COpencvMFCView::InverseDisFCosTran(double * pTd, double * pFd, int power)
{
	long i;                 //行循环变量				
	long	dotCount;// 离散余弦变换点数			
	double	dTemp;// 临时变量	
	CplexNum *temReg;
	dotCount = 1 << power;// 计算离散余弦变换点数		
	temReg = new CplexNum[sizeof(CplexNum) *dotCount * 2];// 分配内存		
	memset(temReg, 0, sizeof(CplexNum) * dotCount * 2);// 赋为0		
	for (i = 0;i < dotCount;i++)// 将时域点写入数组temReg
	{
		temReg[i].re = pFd[i];
		temReg[i].im = 0;
	}
	FastFourierTran(temReg, temReg, power + 1);// 调用快速付立叶变换		
	dTemp = 1 / sqrt((double)dotCount);// 调整系数		
	pTd[0] = temReg[0].re*dTemp;// 求pFd[0]	
	dTemp *= sqrt(2.0f);
	for (i = 1; i < dotCount; i++)// 求pFd[u]	
	{
		pTd[i] = (temReg[i].re* cos(i*pi / (dotCount * 2)) + temReg[i].im* sin(i*pi / (dotCount * 2))) * dTemp;
	}
	delete temReg;// 释放内存
}

void COpencvMFCView::DctMat(Mat image)
{
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	//LPSTR	lpSrcDib;		//指向源图像的指针	
	uchar *lpSrcStartBits;	//指向源像素的指针
	//lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpSrcStartBits = image.ptr<uchar>(0);			// 找到DIB图像像素起始位置	
	lSrcWidth = image.cols;					// 获取图像的宽度		
	lSrcHeight = image.rows;					// 获取图像的高度		
	lSrcLineBytes = image.step;		// 计算图像每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if (CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes,0))
	{
		CImage cimage;
		MatToCimage(image, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
}

void COpencvMFCView::DctMatRGB(Mat image, int m)
{
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	//LPSTR	lpSrcDib;		//指向源图像的指针	
	uchar *lpSrcStartBits;	//指向源像素的指针
	//lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpSrcStartBits = image.ptr<uchar>(0);			// 找到DIB图像像素起始位置	
	lSrcWidth = image.cols;					// 获取图像的宽度		
	lSrcHeight = image.rows;					// 获取图像的高度		
	lSrcLineBytes = image.step;		// 计算图像每行的字节数
	if (m == 1)
	{
		BOOL a1=CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes,1);
	}
	else if (m == 2)
	{
		BOOL a2=CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes,2);
	}
	else if (m == 3)
	{
		BOOL a3=CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes,3);
	}
	

}

void COpencvMFCView::InverDctMat(Mat image)
{
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	//LPSTR	lpSrcDib;		//指向源图像的指针	
	uchar *lpSrcStartBits;	//指向源像素的指针
	lpSrcStartBits = Image.ptr<uchar>(0);			// 找到DIB图像像素起始位置	
	lSrcWidth = Image.cols;					// 获取图像的宽度		
	lSrcHeight = Image.rows;					// 获取图像的高度		
	lSrcLineBytes = Image.step;		// 计算图像每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if (InvestCosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, pTdD, pFdD))
	{
		CImage cimage;
		MatToCimage(Image, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
}

void COpencvMFCView::InverDctMatRGB(Mat image, double * pFd, double * pTd)
{
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	//LPSTR	lpSrcDib;		//指向源图像的指针	
	uchar *lpSrcStartBits;	//指向源像素的指针
	//lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpSrcStartBits = image.ptr<uchar>(0);			// 找到DIB图像像素起始位置	
	lSrcWidth = image.cols;					// 获取图像的宽度		
	lSrcHeight = image.rows;					// 获取图像的高度		
	lSrcLineBytes = image.step;		// 计算图像每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	InvestCosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, pTd, pFd);
}

void COpencvMFCView::Walshei_Har(double * pTd, double * pFd, int power)
{
	long	dotCount;// 沃尔什-哈达玛变换点数		
	int		i, j, k;// 循环变量	
	int		bfsize, p;// 中间变量	
	double *temReg1, *temReg2, *temReg;
	dotCount = 1 << power;// 计算快速沃尔什变换点数		
	temReg1 = new double[dotCount];// 分配运算所需的数组
	temReg2 = new double[dotCount];
	memcpy(temReg1, pTd, sizeof(double) * dotCount);// 将时域点写入数组temReg1		
	for (k = 0; k < power; k++)// 蝶形运算
	{
		for (j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (power - k);
			for (i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				temReg2[i + p] = temReg1[i + p] + temReg1[i + p + bfsize / 2];
				temReg2[i + p + bfsize / 2] = temReg1[i + p] - temReg1[i + p + bfsize / 2];
			}
		}
		temReg = temReg1;// 互换temReg1和temReg2  
		temReg1 = temReg2;
		temReg2 = temReg;
	}
	for (j = 0; j < dotCount; j++)// 调整系数
	{
		p = 0;
		for (i = 0; i < power; i++)
		{
			if (j & (1 << i))
			{
				p += 1 << (power - i - 1);
			}
		}
		pFd[j] = temReg1[p] / dotCount;
	}
	delete temReg1;// 释放内存
	delete temReg2;
}

BOOL COpencvMFCView::Walsh_HarTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//指向像素的指针	
	long i;                 //行循环变量
	long j;                 //列循环变量		

	long	wid = 1, hei = 1;// 进行付立叶变换的宽度和高度，初始化为1
	double	dTemp;// 中间变量	
	int		widpor = 0, heiPor = 0;//2的幂数

	while (wid < lWidth)// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}
	while (hei < lHeight)
	{
		hei *= 2;
		heiPor++;
	}
	lpSrcUnChr = new uchar[lLineBytes*wid + hei];
	double *pTd = new double[wid * hei];// 分配内存
	double *pFd = new double[wid * hei];
	for (i = 0; i < hei; i++)         //将多余部分补0 很重要！！！！！！
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j] = 0;
		}
	}
	for (i = 0; i < lHeight; i++)// 行
	{

		for (j = 0; j < lWidth; j++)// 列
		{
			// 指向DIB第i行，第j个像素的指针
			lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;
			pTd[j + i * wid] = *(lpSrcUnChr);// 给时域赋值
		}
	}
	for (i = 0; i < hei; i++)
	{
		Walshei_Har(pTd + wid * i, pFd + wid * i, widpor);// 对y方向进行沃尔什-哈达玛变换
	}
	for (i = 0; i < hei; i++)// 保存计算结果
	{
		for (j = 0; j < wid; j++)
		{
			pTd[j * hei + i] = pFd[j + wid * i];
		}
	}
	for (j = 0; j < wid; j++)
	{
		Walshei_Har(pTd + j * hei, pFd + j * hei, heiPor);// 对x方向进行沃尔什-哈达玛变换
	}
	for (i = 0; i < lHeight; i++)// 行
	{
		for (j = 0; j < lWidth; j++)// 列
		{
			dTemp = fabs(pFd[i*wid + j] * 1000);// 计算频谱						
			if (dTemp > 255)// 对于超过255的，直接设置为255
			{
				dTemp = 255;
			}
			// 指向DIB第i行，第j个像素的指针
			//lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;
			lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * i + j;
			*(lpSrcUnChr) = (BYTE)(dTemp);// 更新源图像
		}
	}
	delete pTd;//释放内存
	delete pFd;
	return TRUE;
}

void COpencvMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpencvMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpencvMFCView 诊断

#ifdef _DEBUG
void COpencvMFCView::AssertValid() const
{
	CView::AssertValid();
}

void COpencvMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpencvMFCDoc* COpencvMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpencvMFCDoc)));
	return (COpencvMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COpencvMFCView 消息处理程序


void COpencvMFCView::OnFourier()
{
	if (myImage.channels() == 1)
	{
		ForierMat(myImage);
		CImage cimage;
		MatToCimage(myImage, cimage); //将Mat类转化为CImage类用作显示，该函数的定义在Image.cpp中
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
	else if (myImage.channels() == 3)
	{
		Mat aChannels[3];
		//利用数组分离
		split(myImage, aChannels);
		ForierMatRGB(aChannels[0],1);
		ForierMatRGB(aChannels[1],2);
		ForierMatRGB(aChannels[2],3);
		merge(aChannels, 3, myImage);
		CImage cimage;
		MatToCimage(myImage, cimage); //将Mat类转化为CImage类用作显示，该函数的定义在Image.cpp中
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
	
}



void COpencvMFCView::OnFouriertran()
{
	// TODO: 在此添加命令处理程序代码
	if (myImage.channels() == 1)
	{
		InverseFourierMat(myImage);       //逆转换
		CImage cimage;
		MatToCimage(myImage, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
	else if (myImage.channels() == 3)
	{
		Mat aChannels[3];
		//利用数组分离
		split(myImage, aChannels);
		InverseFourierMatRGB(aChannels[0], pFdtB, pTdtB);
		InverseFourierMatRGB(aChannels[1], pFdtG, pTdtG);     
		InverseFourierMatRGB(aChannels[2], pFdtR, pTdtR);
		merge(aChannels, 3, myImage);
		CImage cimage;
		MatToCimage(myImage, cimage); //将Mat类转化为CImage类用作显示，该函数的定义在Image.cpp中
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());

	}
}


void COpencvMFCView::OnDct()
{
	Image = myImage.clone();
	if (Image.channels() == 1)
	{
		DctMat(Image);
	}
	else if (Image.channels() == 3)
	{
		Mat aChannels[3];
		//利用数组分离
		split(Image, aChannels);
		DctMatRGB(aChannels[0], 1);
		DctMatRGB(aChannels[1], 2);
		DctMatRGB(aChannels[2], 3);
		merge(aChannels, 3, Image);
		CImage cimage;
		MatToCimage(Image, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
}


void COpencvMFCView::OnWal()
{
	// TODO: 在此添加命令处理程序代码
	Mat Image2;
	Image2 = myImage.clone();
	SetCursor(LoadCursor(NULL, IDC_WAIT));//光标显示为处理状态
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	//LPSTR	lpSrcDib;		//指向源图像的指针	
	uchar *lpSrcStartBits;	//指向源像素的指针
	//lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpSrcStartBits = Image2.ptr<uchar>(0);			// 找到DIB图像像素起始位置	
	lSrcWidth = Image2.cols;					// 获取图像的宽度		
	lSrcHeight = Image2.rows;					// 获取图像的高度		
	lSrcLineBytes = Image2.step;		// 计算图像每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if (Walsh_HarTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes))
	{
		CImage cimage;
		MatToCimage(Image2, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
}


void COpencvMFCView::OnInversedct()
{
	// TODO: 在此添加命令处理程序代码
	//SetCursor(LoadCursor(NULL, IDC_WAIT));//光标显示为处理状态
	////////////////////////////////////////////////////////////////////////////////////////////////	
	if (Image.channels() == 1)
	{
		InverDctMat(Image);
	}
	else if (Image.channels() == 3)
	{
		Mat aChannels[3];
		//利用数组分离
		split(Image, aChannels);
		InverDctMatRGB(aChannels[0], pFdDB, pTdDB);
		InverDctMatRGB(aChannels[1], pFdDG, pTdDG);
		InverDctMatRGB(aChannels[2], pFdDR, pTdDR);
		merge(aChannels, 3, Image);
		CImage cimage;
		MatToCimage(Image, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
}
