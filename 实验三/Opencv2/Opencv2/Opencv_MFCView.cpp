
// Opencv_MFCView.cpp: COpencvMFCView 类的实现
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include<vector>
#include <iostream>
#include <math.h>
#include <windows.h>
using namespace std;
using namespace cv;
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Opencv_MFC.h"
#endif

#include "Opencv_MFCDoc.h"
#include "Opencv_MFCView.h"
#include "CLineTransDialog.h"
#include "CLineNum.h"
#include "CLinePointset.h"
#include "CLogLinedlg.h"
#include "CHistogramDialog.h"
#include "CSalt.h"
#include "CGaosi.h"
#include "CtemplateDialog.h"
#include "CHistogmatchDIalog.h"
#include "CgeometryDialog.h"
#include "CSplitimage.h"
#include "CGateGredDialog.h"
#include "CHuffman.h"
#include "CHSIHuffman.h"
#include "CShannon.h"
#include "CAirth.h"
#include "CRoberts.h"
#include "CSobel.h"
#include "CPriwitt.h"
#include "CLaplacian.h"
#include "CCanny.h"
#include "CRegiongrow.h"
#include "CGenThresHold.h"
#include "CValueSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
#endif
#define pi 3.1415926535
Mat myImage;
Mat Image;
//extern Mat rawImage;
Mat myImage2;
// COpencvMFCView
extern Mat rawImage2;
extern Mat reImage;
IMPLEMENT_DYNCREATE(COpencvMFCView, CScrollView)

BEGIN_MESSAGE_MAP(COpencvMFCView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpencvMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Fourier, &COpencvMFCView::OnFourier)
	ON_COMMAND(ID_FourierTran, &COpencvMFCView::OnFouriertran)
	ON_COMMAND(ID_Dct, &COpencvMFCView::OnDct)
	ON_COMMAND(ID_Wal, &COpencvMFCView::OnWal)
	ON_COMMAND(ID_InverseDct, &COpencvMFCView::OnInversedct)
	ON_COMMAND(ID_LinearTransform, &COpencvMFCView::OnLineartransform)
	ON_COMMAND(ID_SegLineTransform, &COpencvMFCView::OnSeglinetransform)
	ON_COMMAND(ID_logLineTrans, &COpencvMFCView::Onloglinetrans)
	ON_COMMAND(ID_HistogramEqual, &COpencvMFCView::OnHistogramequal)
	ON_COMMAND(ID_AverageSmooth, &COpencvMFCView::OnAveragesmooth)
	ON_COMMAND(ID_Salt, &COpencvMFCView::OnSalt)
	ON_COMMAND(ID_Gaosi, &COpencvMFCView::OnGaosi)
	ON_COMMAND(ID_Gaosifiltering, &COpencvMFCView::OnGaosifiltering)
	ON_COMMAND(ID_Mid, &COpencvMFCView::OnMid)
	ON_COMMAND(ID_Pepper, &COpencvMFCView::OnPepper)
	ON_COMMAND(ID_whitesalt, &COpencvMFCView::Onwhitesalt)
	ON_COMMAND(ID_HistogramMatch, &COpencvMFCView::OnHistogrammatch)
	ON_COMMAND(ID_GateGrad, &COpencvMFCView::OnGategrad)
	ON_COMMAND(ID_Laplacian, &COpencvMFCView::OnLaplacian)
	ON_COMMAND(ID_PrefectLowFilter, &COpencvMFCView::OnPrefectlowfilter)
	ON_COMMAND(ID_PrefectHighFilter, &COpencvMFCView::OnPrefecthighfilter)
	ON_COMMAND(ID_Geometry, &COpencvMFCView::OnGeometry)
	ON_COMMAND(ID_ImagePlus, &COpencvMFCView::OnImageplus)
	ON_COMMAND(ID_ImageSub, &COpencvMFCView::OnImagesub)
	ON_COMMAND(ID_Water, &COpencvMFCView::OnWater)
	ON_COMMAND(ID_Frame, &COpencvMFCView::OnFrame)
	ON_COMMAND(ID_Frame2, &COpencvMFCView::OnFrame2)
	ON_COMMAND(ID_Frame3, &COpencvMFCView::OnFrame3)
	ON_COMMAND(ID_Frame4, &COpencvMFCView::OnFrame4)
	ON_COMMAND(ID_Frame5, &COpencvMFCView::OnFrame5)
	ON_COMMAND(ID_HSIhigram, &COpencvMFCView::OnHsihigram)
	ON_COMMAND(ID_ConvertHSI, &COpencvMFCView::OnConverthsi)
	ON_COMMAND(ID_ConvertRGB, &COpencvMFCView::OnConvertrgb)
	ON_COMMAND(ID_Huffman, &COpencvMFCView::OnHuffman)
	ON_COMMAND(ID_HsiHuffman, &COpencvMFCView::OnHsihuffman)
	ON_COMMAND(ID_ShannonFano, &COpencvMFCView::OnShannonfano)
	ON_COMMAND(ID_Airth, &COpencvMFCView::OnAirth)
	ON_COMMAND(ID_Roberts, &COpencvMFCView::OnRoberts)
	ON_COMMAND(ID_Sobel, &COpencvMFCView::OnSobel)
	ON_COMMAND(ID_Canny, &COpencvMFCView::OnCanny)
	ON_COMMAND(ID_Prewitt, &COpencvMFCView::OnPrewitt)
	ON_COMMAND(ID_LaplacianSeg, &COpencvMFCView::OnLaplacianseg)
	ON_COMMAND(ID_Reimage, &COpencvMFCView::OnReimage)
	ON_COMMAND(ID_regionGrow, &COpencvMFCView::Onregiongrow)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_Reload, &COpencvMFCView::OnReload)
	ON_COMMAND(ID_Threshold, &COpencvMFCView::OnThreshold)
	ON_COMMAND(ID_FuDiao, &COpencvMFCView::OnFudiao)
	ON_COMMAND(ID_ColorRegiongrow, &COpencvMFCView::OnColorregiongrow)
	ON_COMMAND(ID_PencilRoberts, &COpencvMFCView::OnPencilroberts)
	ON_COMMAND(ID_PencilSobel, &COpencvMFCView::OnPencilsobel)
	ON_COMMAND(ID_PencilPriwitt, &COpencvMFCView::OnPencilpriwitt)
	ON_COMMAND(ID_FUDIAOlaplacian, &COpencvMFCView::OnFudiaolaplacian)
END_MESSAGE_MAP()

// COpencvMFCView 构造/析构

COpencvMFCView::COpencvMFCView() noexcept
{
	// TODO: 在此处添加构造代码
	CSize size;
	size.cx = size.cy = 1000;
	SetScrollSizes(MM_TEXT, size); //窗口大小初始化

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
	MatToCimage(pDoc->rawImage, cimage); //将Mat类转化为CImage类用作显示，该函数的定义在Image.cpp中
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
	::memcpy(temReg1, pTd, sizeof(CplexNum)*dotCount);// 将时域点写入temReg1		
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
	InverseFourier(pFdt, pTdt, lSrcWidth, lSrcHeight); //蝶形的算法。pfd是时域的值，这句执行完之后pfd是有值的。pfd要保存下来进行逆变换，转换回ptd应该接近于0

	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth;j++)
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

BOOL COpencvMFCView::CosTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes, int m)
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

BOOL COpencvMFCView::InvestCosTran(uchar * lpSrcStartBits, long lWidth, long lHeight, long lLineBytes, double *pTd, double *pFd)
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
				dTemp = 255;
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
	if (CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, 0))
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
		BOOL a1 = CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, 1);
	}
	else if (m == 2)
	{
		BOOL a2 = CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, 2);
	}
	else if (m == 3)
	{
		BOOL a3 = CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, 3);
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


void COpencvMFCView::Linear_Transform(Mat image, BYTE min, BYTE max) //线性增强
{
	LPBYTE	lpSrc;			// 指向原图像的指针	
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;			//循环变量
	BYTE pixel;	//像素值
	LPBYTE lpDIBBits = image.ptr<uchar>(0); //指向源图像起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits == NULL)
	{
		return;
	}
	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0;i < lWidth; i++)
		{
			// 指向原图像倒数第j行，第i个像素的指针			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			// 指向目标图像倒数第j行，第i个像素的指针			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			//取得当前指针处的像素值，注意要转换为BYTE类型
			pixel = (BYTE)*lpSrc;

			//根据公式(5-2)求出目标图像中与当前点对应的像素点的灰度值

			*lpDst = (BYTE)(((float)(max - min) / 255)*pixel + min + 0.5);
		}
	}
	// 复制变换后的图像
	//CDC *pDC = GetDC();
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::Seg_Linear_Transform(Mat image, int x, BYTE s[], BYTE t[])  //分段线性增强
{
	LPBYTE	lpSrc;			// 指向原图像的指针	
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;			//循环变量
	BYTE pixel;	//像素值
	LPBYTE lpDIBBits = image.ptr<uchar>(0); //指向源图像起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits == NULL)
	{
		return;
	}
	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0;i < lWidth; i++)
		{
			// 指向原图像倒数第j行，第i个像素的指针			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			// 指向目标图像倒数第j行，第i个像素的指针			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			//取得当前指针处的像素值，注意要转换为BYTE类型
			pixel = (BYTE)*lpSrc;
			for (int i = 0;i < x;i++)
			{
				if (pixel >= s[i] && pixel <= s[i + 1])
				{
					*lpDst = (BYTE)(((float)(t[i + 1] - t[i]) / (s[i + 1] - s[i]))*(pixel - s[i]) + t[i] + 0.5);
				}
			}
			//if (pixel >= 0 && pixel < gSrc1)
			//{
			//	*lpDst = (BYTE)(((float)gDst1/gSrc1)*pixel + 0.5);
			//}
			//else if (pixel >= gSrc1 && pixel <= gSrc2)
			//{
			//	*lpDst = (BYTE)(((float) (gDst2 - gDst1)/ (gSrc2 - gSrc1))*(pixel-gSrc1) + gDst1 + 0.5);
			//}
			//else if(pixel>gSrc2&&pixel<=255) //如果不是255灰度级如何改呢？
			//{
			//	*lpDst = (BYTE)(((float)(255 - gDst2) / (255 - gSrc2))*(pixel - gSrc2) + gDst2 + 0.5);
			//}

			//*lpDst = (BYTE)(((float)(max - min) / 255)*pixel + min + 0.5);
		}
	}
	// 复制变换后的图像
	//CDC *pDC = GetDC();
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::Log_Transform(Mat image, double a, double b, double c)  //非线性增强
{
	LPBYTE	lpSrc;			// 指向原图像的指针	
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;			//循环变量
	BYTE pixel;	//像素值
	LPBYTE lpDIBBits = image.ptr<uchar>(0); //指向源图像起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits == NULL)
	{
		return;
	}
	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0;i < lWidth; i++)
		{
			// 指向原图像倒数第j行，第i个像素的指针			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			// 指向目标图像倒数第j行，第i个像素的指针			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			//取得当前指针处的像素值，注意要转换为BYTE类型
			pixel = (BYTE)*lpSrc;

			*lpDst = (BYTE)((log((double)(pixel + 1))) / (b*log(c)) + a + 0.5);
		}
	}
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::Histogram_Equalization(Mat image)  //直方图均衡化函数
{
	LPBYTE	lpSrc;			// 指向原图像的指针	
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;			//循环变量
	BYTE pixel;	//像素值
	int nRst[256];  //直方图均衡化之后存放每个灰度级的像素的值

	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits == NULL)
	{
		return;
	}

	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);


	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);

	// 初始化中间变量temp
	memset(temp, 0, sizeof(temp));
	memset(fPro, 0, sizeof(fPro));
	memset(fProT, 0, sizeof(fProT));
	int sum = 0, sum2 = 0;
	// 获取原图像灰度分布的概率密度
	Histogram_Statistic(image, fPro);
	//进行直方图均衡化处理
	for (i = 0;i < 256;i++)
	{
		temp[i] = fPro[i];
	}
	for (i = 1;i < 256;i++)
	{
		temp[i] = temp[i] + temp[i - 1];   //累计概率
	}
	for (i = 0;i < 256;i++)
	{
		nRst[i] = (int)(temp[i] * 255 + 0.5); //四舍五入，计算直方图均衡化后的灰度值
	}
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0;i < lWidth; i++)
		{
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			pixel = (BYTE)*lpSrc;
			sum = sum + pixel;
			*lpDst = (BYTE)nRst[pixel];
		}
	}
	// 复制均衡化处理后的图像到原图像中
	average1 = float(sum) / (lWidth*lHeight);  //平均灰度
	int graysum = 0;
	for (i = 0;i < 256;i++)
	{
		graysum = graysum + gray[i];
		if (graysum >= ((lWidth*lHeight) / 2))
		{
			mid1 = i;           //中值灰度
			break;
		}
	}
	float stannum1 = 0;
	for (i = 0;i < 256;i++)
	{
		stannum1 = stannum1 + (average1 - i)*(average1 - i)*gray[i];
	}
	stan1 = sqrt(stannum1 / (lWidth*lHeight));
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	Histogram_Statistic(image, fProT);
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0;i < lWidth; i++)
		{
			// 指向原图像倒数第j行，第i个像素的指针			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			// 指向目标图像倒数第j行，第i个像素的指针			
			pixel = (BYTE)*lpSrc;
			sum2 = sum2 + pixel;
		}
	}
	average2 = float(sum2) / (lWidth*lHeight);  //平均灰度
	int graysum2 = 0;
	for (i = 0;i < 256;i++)
	{
		graysum2 = graysum2 + gray[i];
		if (graysum2 >= ((lWidth*lHeight) / 2))
		{
			mid2 = i;     //中值灰度
			break;
		}
	}
	float stannum2 = 0;
	for (i = 0;i < 256;i++)
	{
		stannum2 = stannum2 + (average2 - i)*(average2 - i)*gray[i];
	}
	stan2 = sqrt(stannum2 / (lWidth*lHeight));
	//for (int i = 0;i < 256;i++)
	//{
	//	T[i] = (int)(fPro[i] * lWidth * lHeight +0.5);
	//	nk[i] = (int)(temp[i] * lWidth * lHeight + 0.5);
	//	H[i] = (int)(fProT[i] * lWidth * lHeight + 0.5);
	//}
	//释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::SpicedSalt(Mat image, float n)  //椒盐噪声
{
	LONG lWidth, lHeight;
	lWidth = image.cols;
	lHeight = image.rows;
	LONG sum = lWidth * lHeight;
	int saltsum = sum * n;
	for (int i = 0;i < saltsum;i++)
	{
		int pix = rand() % 2;
		int x = (int)(rand()*1.0 / RAND_MAX * (double)(lWidth - 1));
		int y = (int)(rand()*1.0 / RAND_MAX * (double)(lHeight - 1));
		/*int x = (int)rand() % lWidth;
		int y = (int)rand() % lHeight;*/
		if (pix == 0)
		{
			if (image.channels() == 1)
			{
				image.at<uchar>(y, x) = 0;
			}
			else if (image.channels() == 3)
			{
				image.at<Vec3b>(y, x)[0] = 0;
				image.at<Vec3b>(y, x)[1] = 0;
				image.at<Vec3b>(y, x)[2] = 0;
			}
		}
		else
		{
			if (image.channels() == 1)
			{
				image.at<uchar>(y, x) = 255;
			}
			else if (image.channels() == 3)
			{
				image.at<Vec3b>(y, x)[0] = 255;
				image.at<Vec3b>(y, x)[1] = 255;
				image.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}

}

void COpencvMFCView::WhiteSalt(Mat image, float n)  //盐噪声
{
	LONG lWidth, lHeight;
	lWidth = image.cols;
	lHeight = image.rows;
	LONG sum = lWidth * lHeight;
	int saltsum = sum * n;
	for (int i = 0;i < saltsum;i++)
	{
		/*	int x = (int)(rand()*1.0 / RAND_MAX * (double)(lWidth - 1 ));
			int y = (int)(rand()*1.0 / RAND_MAX * (double)(lHeight - 1));*/
		int x = (int)rand() % lWidth;
		int y = (int)rand() % lHeight;
		if (image.channels() == 1)
		{
			image.at<uchar>(y, x) = 255;
		}
		else if (image.channels() == 3)
		{
			image.at<Vec3b>(y, x)[0] = 255;
			image.at<Vec3b>(y, x)[1] = 255;
			image.at<Vec3b>(y, x)[2] = 255;
		}
	}
}

void COpencvMFCView::Pepper(Mat image, float n)  //胡椒噪声
{
	LONG lWidth, lHeight;
	lWidth = image.cols;
	lHeight = image.rows;
	LONG sum = lWidth * lHeight;
	int saltsum = sum * n;
	for (int i = 0;i < saltsum;i++)
	{
		/*	int x = (int)(rand()*1.0 / RAND_MAX * (double)(lWidth - 1 ));
			int y = (int)(rand()*1.0 / RAND_MAX * (double)(lHeight - 1));*/
		int x = (int)rand() % lWidth;
		int y = (int)rand() % lHeight;
		if (image.channels() == 1)
		{
			image.at<uchar>(y, x) = 0;
		}
		else if (image.channels() == 3)
		{
			image.at<Vec3b>(y, x)[0] = 0;
			image.at<Vec3b>(y, x)[1] = 0;
			image.at<Vec3b>(y, x)[2] = 0;
		}
	}
}

void COpencvMFCView::Middle_Smooth(Mat image, int M)  //中值滤波
{
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpSrc;			// 指向缓存图像的指针
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	int i, j, x, y, m;			//循环变量
	int flag = 1;  //循环标志变量
	BYTE  *pixel;
	pixel = new BYTE[M];
	int num = M / 2; //边缘数量
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);

	//中值滤波
	int p, t;
	int h;
	BYTE type;
	for (j = 0; j < lHeight; j++)   //横向一维
	{
		for (i = 0;i < lWidth; i++)
		{
			if (i < M / 2)
			{
				for (p = 0;p < M / 2 - i;p++)
				{
					pixel[p] = 0;
				}
				h = 0;
				for (p = M / 2 - i;p < M;p++)
				{
					lpSrc = (LPBYTE)lpDIBBits + lWidth * j + p;
					pixel[p] = (BYTE)*lpSrc;
					h++;
				}
			}
			else if (i >= lWidth - M / 2)
			{
				h = 0;
				for (p = i - M / 2;p < lWidth - (i - M / 2);p++)
				{
					lpSrc = (LPBYTE)lpDIBBits + lWidth * j + p;
					//取得当前指针处的像素值，注意要转换为BYTE类型
					pixel[h] = (BYTE)*lpSrc;
					h++;
				}
				for (p = lWidth - (i - M / 2);p < M;p++)
				{
					pixel[p] = 255;
				}
			}
			else
			{
				h = 0;
				for (p = i - M / 2;p <= i + M / 2;p++)
				{
					// 指向原图像倒数第j行，第i个像素的指针			
					lpSrc = (LPBYTE)lpDIBBits + lWidth * j + p;
					//取得当前指针处的像素值，注意要转换为BYTE类型
					pixel[h] = (BYTE)*lpSrc;
					h++;
				}
			}
			for (p = 0;p < M;p++)
				for (t = p + 1;t < M;t++)
				{
					if (pixel[t] < pixel[p])
					{
						type = pixel[t];
						pixel[t] = pixel[p];
						pixel[p] = type;
					}
				}
			// 指向目标图像倒数第j行，第i个像素的指针			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			//根据公式(5-2)求出目标图像中与当前点对应的像素点的灰度值
			*lpDst = pixel[M / 2];
		}
	}
	for (j = 0; j < lWidth; j++)   //横向一维
	{
		for (i = 0;i < lHeight; i++)
		{
			if (i == 0)
			{
				for (p = 0;p < M / 2;p++)
				{
					pixel[p] = 0;
				}
				h = i;
				for (p = M / 2;p < M;p++)
				{
					lpSrc = (LPBYTE)lpDIBBits + lHeight * j + h;
					pixel[p] = (BYTE)*lpSrc;
					h++;
				}
			}
			else if (i >= lHeight - M / 2)
			{
				h = 0;
				for (p = i - M / 2;p < lHeight;p++)
				{
					lpSrc = (LPBYTE)lpDIBBits + lHeight * j + p;
					//取得当前指针处的像素值，注意要转换为BYTE类型
					pixel[h] = (BYTE)*lpSrc;
					h++;
				}
				for (p = lHeight - (i - M / 2);p < M;p++)
				{
					pixel[p] = 255;
				}
			}
			else
			{
				h = 0;
				for (p = i - M / 2;p <= i + M / 2;p++)
				{
					// 指向原图像倒数第j行，第i个像素的指针			
					lpSrc = (LPBYTE)lpDIBBits + lHeight * j + p;
					//取得当前指针处的像素值，注意要转换为BYTE类型
					pixel[h] = (BYTE)*lpSrc;
					h++;
				}
			}
			for (p = 0;p < M;p++)
				for (t = p + 1;t < M;t++)
				{
					if (pixel[t] < pixel[p])
					{
						type = pixel[t];
						pixel[t] = pixel[p];
						pixel[p] = type;
					}
				}
			// 指向目标图像倒数第j行，第i个像素的指针			
			lpDst = (LPBYTE)lpNewDIBBits + lHeight * j + i;
			//根据公式(5-2)求出目标图像中与当前点对应的像素点的灰度值
			*lpDst = pixel[M / 2];
		}
	}
	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	//释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::Histogram_Statistic(Mat image, float * probability)  //直方图统计函数  float *probability -灰度分布概率密度
{
	LPBYTE	lpSrc;			// 指向原图像的指针	
	long i, j;			//循环变量	
	BYTE pixel;	//像素值

	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度

	// 灰度计数变量初始化
	memset(gray, 0, sizeof(gray));
	int sum = 0;
	//逐个扫面图像中的像素点,进行灰度计数统计
	for (j = 0;j < lHeight;j++)
		for (i = 0;i < lWidth;i++)
		{
			// 指向原图像倒数第j行，第i个像素的指针			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			// 指向目标图像倒数第j行，第i个像素的指针			
			pixel = (BYTE)*lpSrc;
			if (pixel >= 0 && pixel <= 255)
			{
				gray[pixel]++;  //求各个灰度级的像素个数
			}
		}
	for (i = 0;i < 256;i++)
	{
		probability[i] = ((float)gray[i]) / (lWidth*lHeight);
	}
}

void COpencvMFCView::Histogram_Match(Mat image, BYTE bGray, int * npMap, float * fpPro) //直方图规定化
{
	LPBYTE	lpSrc;			// 指向原图像的指针	
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;			//循环变量
	BYTE pixel;	//像素值

	//原图像灰度分布概率密度变量
	//float fPro[256];
	//中间变量
	//float temp[256];
	float fPro2[256];
	float fpPro2[256];
	//灰度映射表变量
	int nMap[256];

	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);


	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);

	// 获取原图像灰度分布的概率密度
	memset(fPro, 0, sizeof(fPro));
	memset(temp, 0, sizeof(temp));
	memset(fProT, 0, sizeof(fProT));
	Histogram_Statistic(image, fPro);
	memcpy(fPro2, fPro, 256 * 4);
	memcpy(fpPro2, fpPro, 256 * 4);
	// 计算原图像累计直方图
	for (i = 0; i < 256; i++)
	{
		if (i == 0)
		{
			temp[0] = fPro2[0];
		}
		else
		{
			temp[i] = temp[i - 1] + fPro2[i];
		}
		fPro2[i] = temp[i];
	}

	// 计算规定变换后的累计直方图
	for (i = 0; i < 256; i++)
	{
		if (i == 0)
		{
			temp[0] = fpPro2[0];
		}
		else
		{
			temp[i] = temp[i - 1] + fpPro2[i];
		}
		fpPro2[i] = temp[i];
	}

	// 确定映射关系
	for (i = 0; i < 256; i++)
	{
		// 最接近的规定直方图灰度级
		int m = 0;
		// 最小差值
		float min_value = 1.0f;
		// 枚举规定直方图各灰度
		for (j = 0; j < 256; j++)
		{
			// 当前差值
			float now_value = 0.0f;
			//  差值计算
			if (fPro2[i] - fpPro2[j] >= 0.0f)
				now_value = fPro2[i] - fpPro2[j];
			else
				now_value = fpPro2[j] - fPro2[i];
			// 寻找最接近的规定直方图灰度级
			if (now_value < min_value)
			{
				// 最接近的灰度级
				m = j;
				// 最小差值
				min_value = now_value;
			}
		}

		// 建立灰度映射表
		nMap[i] = npMap[m];
	}

	// 对各像素进行直方图规定化映射处理
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth; i++)
		{
			// 指向原图像倒数第j行，第i个像素的指针			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			// 指向目标图像倒数第j行，第i个像素的指针			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			//取得当前指针处的像素值，注意要转换为BYTE类型
			pixel = (BYTE)*lpSrc;
			//对目标图像进行映射处理
			*lpDst = (BYTE)(nMap[pixel]);

		}
	}

	// 复制直方图规定化处理后的图像到原图像中
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	//释放内存
	Histogram_Statistic(image, fProT);
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::Average_Smooth(Mat image, int M)  //均值滤波
{
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpSrc;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j, m, n;			//循环变量
	int sum = 0; //模板中各个元素总和
	BYTE value_average;	//领域加权均值变量
	BYTE pixel;
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);
	int **structureint;
	structureint = new int*[M];
	for (int i = 0;i < M;i++)
	{
		structureint[i] = new int[M];    //开辟动态二维数组structure
		//structure[i] = (double*)malloc(n * sizeof(int));
	}
	for (int i = 0;i < M;i++)
		for (int j = 0;j < M;j++)
		{
			structureint[i][j] = 1;
		}
	int p;
	int t;
	int structuresum = 0;
	//求模板中各元素权值总和
	for (i = 0;i < M;i++)
		for (j = 0;j < M;j++)
		{
			structuresum = structuresum + structureint[i][j];
		}
	for (i = 0;i < lHeight;i++)
		for (j = 0;j < lWidth;j++)
		{
			if (i<M / 2 || i>lHeight - M / 2 || j<M / 2 || j>lWidth - M / 2)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * i + j;
				lpDst = (LPBYTE)lpNewDIBBits + lWidth * i + j;
				*lpDst = (BYTE)*lpSrc;
			}
			else
			{
				sum = 0;
				p = 0;
				for (m = i - M / 2;m <= i + M / 2;m++)
				{
					t = 0;
					for (n = j - M / 2;n <= j + M / 2;n++)
					{
						lpSrc = (LPBYTE)lpDIBBits + lWidth * m + n;
						pixel = (BYTE)*lpSrc;
						sum = sum + pixel * structureint[p][t];
						t++;
					}
					p++;
				}
				lpDst = (LPBYTE)lpNewDIBBits + lWidth * i + j;
				value_average = (float)sum / structuresum + 0.5;
				*lpDst = (BYTE)value_average;
			}
		}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	//释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

double COpencvMFCView::Gaosiset(double mu, double sigma)
{
	static double V1, V2, S;
	static int phase = 0;
	double X;
	double U1, U2;
	if (phase == 0) {
		do {
			U1 = (double)rand() / RAND_MAX;
			U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else {
		X = V2 * sqrt(-2 * log(S) / S);
	}
	phase = 1 - phase;
	return mu + sigma * X;
}

void COpencvMFCView::GaosiNoise(Mat img, double mu, double sigma, int k)  //高斯噪声
{
	Mat outImage;
	outImage.create(img.rows, img.cols, img.type());
	for (int x = 0;x < img.rows;x++) {
		for (int y = 0;y < img.cols;y++) {
			if (img.channels() == 1)
			{
				double temp = img.at<uchar>(x, y)
					+ k * Gaosiset(mu, sigma);
				if (temp > 255)
					temp = 255;
				else if (temp < 0)
					temp = 0;
				outImage.at<uchar>(x, y) = temp;
			}
			else if (img.channels() == 3)
			{
				double temp1 = img.at<Vec3b>(x, y)[0]
					+ k * Gaosiset(mu, sigma);
				double temp2 = img.at<Vec3b>(x, y)[1]
					+ k * Gaosiset(mu, sigma);
				double temp3 = img.at<Vec3b>(x, y)[2]
					+ k * Gaosiset(mu, sigma);
				temp1 = temp1 > 255 ? 255 : temp1;
				temp2 = temp2 > 255 ? 255 : temp2;
				temp3 = temp3 > 255 ? 255 : temp3;
				temp1 = temp1 < 0 ? 0 : temp1;
				temp2 = temp2 < 0 ? 0 : temp2;
				temp3 = temp3 < 0 ? 0 : temp3;
				outImage.at<Vec3b>(x, y)[0] = temp1;
				outImage.at<Vec3b>(x, y)[1] = temp2;
				outImage.at<Vec3b>(x, y)[2] = temp3;
			}
		}
	}
	myImage = outImage.clone();
	CImage cimage2;
	MatToCimage(outImage, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}

void COpencvMFCView::Value_Average_Smooth(Mat image, int **structure, int M)  //高斯滤波（加权均值滤波）
{
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpSrc;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j, m, n;			//循环变量
	int sum = 0; //模板中各个元素总和
	BYTE value_average;	//领域加权均值变量
	BYTE pixel;
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);
	int p;
	int t;
	int structuresum = 0;
	//求模板中各元素权值总和
	for (i = 0;i < M;i++)
		for (j = 0;j < M;j++)
		{
			structuresum = structuresum + structure[i][j];
		}
	for (i = 0;i < lHeight;i++)
		for (j = 0;j < lWidth;j++)
		{
			if (i<M / 2 || i>lHeight - M / 2 || j<M / 2 || j>lWidth - M / 2)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * i + j;
				lpDst = (LPBYTE)lpNewDIBBits + lWidth * i + j;
				*lpDst = (BYTE)*lpSrc;
			}
			else
			{
				sum = 0;
				p = 0;
				for (m = i - M / 2;m <= i + M / 2;m++)
				{
					t = 0;
					for (n = j - M / 2;n <= j + M / 2;n++)
					{
						lpSrc = (LPBYTE)lpDIBBits + lWidth * m + n;
						pixel = (BYTE)*lpSrc;
						sum = sum + pixel * structure[p][t];
						t++;
					}
					p++;
				}
			}

			lpDst = (LPBYTE)lpNewDIBBits + lWidth * i + j;
			value_average = (float)sum / structuresum + 0.5;
			*lpDst = (BYTE)value_average;
		}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	//释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::CreateGauss(double **structure, int M)  //生成高斯模板
{
	LONG i, j;
	int Center;
	double dDisx, dDisy;
	double dValue;
	double sigma;
	//M = 1 + 2 * ceil(3 * sigma);
	sigma = 0.3*((M - 1)*0.5 - 1) + 0.8; //根据模板大小确定标准差
	Center = M / 2;
	for (i = 0;i < M;i++)
		for (j = 0;j < M;j++)
		{
			dDisx = (double)(i - Center);
			dDisy = (double)(j - Center);
			dValue = exp(-(dDisx*dDisx + dDisy * dDisy) / (2 * sigma*sigma)) / (2 * 3.415926*sigma*sigma);
			structure[i][j] = dValue;
		}
	double k = 1 / structure[0][0];
	for (i = 0;i < M;i++)
	{
		for (j = 0;j < M;j++)
		{
			structure[i][j] *= k;
		}
	}
}

void COpencvMFCView::GateGrad(Mat image, BYTE t) //门限梯度锐化
{
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;			//循环变量

	BYTE temp; //暂存双向一次微分结果

	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为0  	
	memset(lpNewDIBBits, (BYTE)0, lWidth * lHeight);

	//逐个扫描图像中的像素点,进行门限梯度锐化处理

	for (j = 1;j < lHeight - 1;j++)
	{
		for (i = 1;i < lWidth - 1;i++)
		{
			//根据双向一次微分公式计算当前像素的灰度值
			temp = (BYTE)sqrt((float)((lpDIBBits[lWidth*j + i] - lpDIBBits[lWidth*j + (i - 1)])*(lpDIBBits[lWidth*j + i] - lpDIBBits[lWidth*j + (i - 1)])
				+ (lpDIBBits[lWidth*j + i] - lpDIBBits[lWidth*(j - 1) + i])*(lpDIBBits[lWidth*j + i] - lpDIBBits[lWidth*(j - 1) + i])));
			if (temp >= t)
			{
				if ((temp + 100) > 255)
					lpNewDIBBits[lWidth*j + i] = 255;
				else
					lpNewDIBBits[lWidth*j + i] = temp + 100;
			}
			if (temp < t)
				lpNewDIBBits[lWidth*j + i] = lpDIBBits[lWidth*j + i];
		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	//释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::Laplacian(Mat image) //拉普拉斯锐化
{
	int tempH;  //模板高度
	int tempW;  //模板宽度
	float tempC;  //模板系数
	int tempMY;   //模板中心元素Y坐标
	int tempMX;   //模板中心元素X坐标
	float Template[9];   //模板数组	

	//设置拉普拉斯模板参数
	tempW = 3;
	tempH = 3;
	tempC = 1.0;
	tempMY = 1;
	tempMX = 1;
	Template[0] = 0.0;
	Template[1] = 1.0;
	Template[2] = 0.0;
	Template[3] = 1.0;
	Template[4] = -4.0;
	Template[5] = 1.0;
	Template[6] = 0.0;
	Template[7] = 1.0;
	Template[8] = 0.0;

	//调用卷积函数
	Convolution(image, tempH, tempW, tempMX, tempMY, Template, tempC);
}

BOOL COpencvMFCView::Convolution(Mat image, int tempH, int tempW, int tempMX, int tempMY, float * fpTempArray, float fCoef)
{
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j, k, l;			//循环变量
	float fResult;    //暂存计算中间结果     

	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度	

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}

	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为0 	
	memset(lpNewDIBBits, (BYTE)0, lWidth * lHeight);

	//逐个扫描图像中的像素点,进行卷积运算

	for (j = tempMY;j < lHeight - tempH + tempMY + 1;j++)
	{
		for (i = tempMX;i < lWidth - tempW + tempMX + 1;i++)
		{
			//计算像素值
			fResult = 0;
			for (k = 0;k < tempH;k++)
				for (l = 0;l < tempW;l++)
					fResult = fResult + lpDIBBits[(j - tempMY + k)*lWidth + (i - tempMX + l)] * fpTempArray[k*tempW + l];
			//乘上系数
			fResult *= fCoef;
			//取绝对值
			fResult = (float)fabs(fResult);
			//判断是否超过255
			if (fResult > 255)
				//若超过255，直接赋值为255
				lpNewDIBBits[j*lWidth + i] = 255;
			else
				//未超过255，赋值为计算结果
				lpNewDIBBits[j*lWidth + i] = (BYTE)(fResult + 0.5);
		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	//释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	return TRUE;
}

void COpencvMFCView::Perfect_Low_Filter(Mat image, int u, int v)  //理想低通滤波
{
	LPBYTE	lpSrc;			// 指向原图像当前点的指针
	long i, j;			//循环变量
	double d0;  //截止频域变量
	double max = 0.0; //归一化因子

	double *t;  //空域数据指针
	double *H;  //传递函数指针

	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度 	

	long lLineBytes = WIDTHBYTES(lWidth * 8);//计算图象每行的字节数
	t = new double[lHeight*lLineBytes * 2 + 1]; //分配空域空间
	H = new double[lHeight*lLineBytes * 2 + 1]; //分配传递函数空间
	d0 = sqrt((float)(u*u + v * v));  //计算截止频率d0

	//给空域赋值，并计算传递函数
	for (j = 0;j < lHeight;j++)
	{
		for (i = 0;i < lLineBytes;i++)
		{
			lpSrc = lpDIBBits + lLineBytes * j + i;//指向第i行第j列象素
			//给空域赋值
			t[(2 * lLineBytes)*j + 2 * i + 1] = *lpSrc;
			t[(2 * lLineBytes)*j + 2 * i + 2] = 0.0;

			//计算传递函数
			if ((sqrt((float)(i*i + j * j))) <= d0)
				H[2 * i + (2 * lLineBytes)*j + 1] = 1.0;
			else
				H[2 * i + (2 * lLineBytes)*j + 1] = 0.0;
			H[2 * i + (2 * lLineBytes)*j + 2] = 0.0;
		}
	}
	//进行傅立叶变换
	fourier(t, lHeight, lLineBytes, 1);

	//傅立叶变换结果与传递函数进行卷积运算
	for (j = 1;j < lHeight*lLineBytes * 2;j += 2)
	{
		t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
		t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
	}
	//进行傅立叶逆变换
	fourier(t, lHeight, lLineBytes, -1);

	//计算归一化因子
	for (j = 0;j < lHeight;j++)
	{
		for (i = 0;i < lLineBytes;i++)
		{
			t[(2 * lLineBytes)*j + 2 * i + 1] = sqrt(t[(2 * lLineBytes)*j + 2 * i + 1] * t[(2 * lLineBytes)*j + 2 * i + 1] + t[(2 * lLineBytes)*j + 2 * i + 2] * t[(2 * lLineBytes)*j + 2 * i + 2]);
			if (max < t[(2 * lLineBytes)*j + 2 * i + 1])
				max = t[(2 * lLineBytes)*j + 2 * i + 1];
		}
	}

	//计算结果图像,并保存到原图像数据区
	for (j = 0;j < lHeight;j++)
	{
		for (i = 0;i < lLineBytes;i++)
		{
			lpSrc = lpDIBBits + lLineBytes * j + i;
			*lpSrc = (BYTE)(t[(2 * lLineBytes)*j + 2 * i + 1] * 255.0 / max);
		}
	}
	//释放内存空间
	delete t;
	delete H;
}

void COpencvMFCView::Perfect_High_Filter(Mat image, int u, int v) //理想高通滤波
{
	LPBYTE	lpSrc;			// 指向原图像当前点的指针
	long i, j;			//循环变量
	double d0;  //截止频域变量
	double max = 0.0; //归一化因子

	double *t;  //空域数据指针
	double *H;  //传递函数指针

	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度 	

	long lLineBytes = WIDTHBYTES(lWidth * 8);//计算图象每行的字节数
	t = new double[lHeight*lLineBytes * 2 + 1]; //分配空域空间
	H = new double[lHeight*lLineBytes * 2 + 1]; //分配传递函数空间
	d0 = sqrt((float)(u*u + v * v));  //计算截止频率d0

	//给空域赋值，并计算传递函数
	for (j = 0;j < lHeight;j++)
	{
		for (i = 0;i < lLineBytes;i++)
		{
			lpSrc = lpDIBBits + lLineBytes * j + i;//指向第i行第j列象素
			//给空域赋值
			t[(2 * lLineBytes)*j + 2 * i + 1] = *lpSrc;
			t[(2 * lLineBytes)*j + 2 * i + 2] = 0.0;

			//计算传递函数
			if ((sqrt((float)(i*i + j * j))) <= d0)
				H[2 * i + (2 * lLineBytes)*j + 1] = 0.0;
			else
				H[2 * i + (2 * lLineBytes)*j + 1] = 1.0;
			H[2 * i + (2 * lLineBytes)*j + 2] = 0.0;
		}
	}
	//进行傅立叶变换
	fourier(t, lHeight, lLineBytes, 1);

	//傅立叶变换结果与传递函数进行卷积运算
	for (j = 1;j < lHeight*lLineBytes * 2;j += 2)
	{
		t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
		t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
	}
	//进行傅立叶逆变换
	fourier(t, lHeight, lLineBytes, -1);

	//计算归一化因子
	for (j = 0;j < lHeight;j++)
	{
		for (i = 0;i < lLineBytes;i++)
		{
			t[(2 * lLineBytes)*j + 2 * i + 1] = sqrt(t[(2 * lLineBytes)*j + 2 * i + 1] * t[(2 * lLineBytes)*j + 2 * i + 1] + t[(2 * lLineBytes)*j + 2 * i + 2] * t[(2 * lLineBytes)*j + 2 * i + 2]);
			if (max < t[(2 * lLineBytes)*j + 2 * i + 1])
				max = t[(2 * lLineBytes)*j + 2 * i + 1];
		}
	}

	//计算结果图像
	for (j = 0;j < lHeight;j++)
	{
		for (i = 0;i < lLineBytes;i++)
		{
			lpSrc = lpDIBBits + lLineBytes * j + i;
			*lpSrc = (BYTE)(t[(2 * lLineBytes)*j + 2 * i + 1] * 255.0 / max);
		}
	}
	//释放内存空间
	delete t;
	delete H;
}

void COpencvMFCView::fourier(double * data, int height, int width, int isign)
{
	int idim;
	unsigned long i1, i2, i3, i2rev, i3rev, ip1, ip2, ip3, ifp1, ifp2;
	unsigned long ibit, k1, k2, n, nprev, nrem, ntot, nn[3];
	double tempi, tempr;
	double theta, wi, wpi, wpr, wr, wtemp;
	ntot = height * width;
	nn[1] = height;
	nn[2] = width;
	nprev = 1;
	for (idim = 2;idim >= 1;idim--)
	{
		n = nn[idim];
		nrem = ntot / (n*nprev);
		ip1 = nprev << 1;
		ip2 = ip1 * n;
		ip3 = ip2 * nrem;
		i2rev = 1;
		for (i2 = 1;i2 <= ip2;i2 += ip1)
		{
			if (i2 < i2rev)
			{
				for (i1 = i2;i1 <= i2 + ip1 - 2;i1 += 2)
				{
					for (i3 = i1;i3 <= ip3;i3 += ip2)
					{
						i3rev = i2rev + i3 - i2;
						SWAP(data[i3], data[i3rev]);
						SWAP(data[i3 + 1], data[i3rev + 1]);
					}
				}
			}
			ibit = ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit)
			{
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1 = ip1;
		while (ifp1 < ip2)
		{
			ifp2 = ifp1 << 1;
			theta = isign * pi * 2 / (ifp2 / ip1);
			wtemp = sin(0.5*theta);
			wpr = -2.0*wtemp*wtemp;
			wpi = sin(theta);
			wr = 1.0;
			wi = 0.0;
			for (i3 = 1;i3 <= ifp1;i3 += ip1)
			{
				for (i1 = i3;i1 <= i3 + ip1 - 2;i1 += 2)
				{
					for (i2 = i1;i2 <= ip3;i2 += ifp2)
					{
						k1 = i2;
						k2 = k1 + ifp1;
						tempr = wr * data[k2] - wi * data[k2 + 1];
						tempi = wr * data[k2 + 1] + wi * data[k2];
						data[k2] = data[k1] - tempr;
						data[k2 + 1] = data[k1 + 1] - tempi;
						data[k1] += tempr;
						data[k1 + 1] += tempi;
					}
				}
				wr = (wtemp = wr)*wpr - wi * wpi + wr;
				wi = wi * wpr + wtemp * wpi + wi;
			}
			ifp1 = ifp2;
		}
		nprev *= n;
	}
}



void COpencvMFCView::Rotate(Mat image, Mat image3, double ang) //旋转
{
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpSrc;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;
	BYTE pixel;
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度
	double degree;
	degree = pi * ang / 180.0;  //旋转角度的转换

	//计算旋转后的图像宽高。以图像中心为原点旋转
	int midx, midy;
	midx = lWidth / 2;
	midy = lHeight / 2;
	int left1x, left1y, left2x, left2y, right1x, right1y, right2x, right2y;
	left1x = -lWidth / 2; //左上
	left1y = lHeight / 2;
	left2x = -lWidth / 2; //左下
	left2y = -lHeight / 2;
	right1x = lWidth / 2;//右上
	right1y = lHeight / 2;
	right2x = lWidth / 2;//右下
	right2y = -lHeight / 2;
	double Tleft1x, Tleft1y, Tleft2x, Tleft2y, Tright1x, Tright1y, Tright2x, Tright2y;
	Tleft1x = left1x * cos(degree) + left1y * sin(degree);
	Tleft1y = -left1x * sin(degree) + left1y * cos(degree);
	Tleft2x = left2x * cos(degree) + left2y * sin(degree);
	Tleft2y = -left2x * sin(degree) + left2y * cos(degree);
	Tright1x = right1x * cos(degree) + right1y * sin(degree);
	Tright1y = -right1x * sin(degree) + right1y * cos(degree);
	Tright2x = right2x * cos(degree) + right2y * sin(degree);
	Tright2y = -right2x * sin(degree) + right2y * cos(degree);
	int desWidth = max(abs(Tright2x - Tleft1x), abs(Tright1x - Tleft2x));
	int desHeight = max(abs(Tright2y - Tleft1y), abs(Tright1y - Tleft2y));
	//分配旋转后图像的缓存

	lpNewDIBBits = image3.ptr<uchar>(0);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)255, desWidth * desHeight); //为新图像分配值
	//通过新图像的坐标，计算对应的原图像的坐标
	for (i = 0; i < desHeight; i++)
	{
		for (j = 0; j < desWidth; j++)
		{
			//转换到以图像为中心的坐标系，并进行逆旋转
			int tX = (j - desWidth / 2)*cos((360 - ang)*pi / 180.0) + (-i + desHeight / 2)*sin((360 - ang)*pi / 180.0);
			int tY = -(j - desWidth / 2)*sin((360 - ang)*pi / 180.0) + (-i + desHeight / 2)*cos((360 - ang)*pi / 180.0);
			//如果这个坐标不在原图像内，则不赋值
			if (tX > lWidth / 2 || tX < -lWidth / 2 || tY > lHeight / 2 || tY < -lHeight / 2)
			{
				continue;
			}
			//再转换到原坐标系下
			int tXN = tX + lWidth / 2;
			int tYN = abs(tY - lHeight / 2);
			if (tYN == lWidth)
			{
				tYN = 0;
			}
			//值拷贝
			lpSrc = (LPBYTE)lpDIBBits + lWidth * tYN + tXN;
			lpDst = (LPBYTE)lpNewDIBBits + desWidth * i + j;
			pixel = (BYTE)*lpSrc;
			*lpDst = pixel;
		}
	}

}

void COpencvMFCView::Zoom(Mat image, Mat Rimage, double m) //图像缩放（以缩放比例为参数）
{
	//使用双线性内插值算法实现缩放
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpSrc;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;
	BYTE pixel;
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度

	//先求缩放后的长宽
	int Rwidth, Rheight;
	Rwidth = (int)(lWidth*m);
	Rheight = (int)(lHeight*m);
	lpNewDIBBits = Rimage.ptr<uchar>(0);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)255, Rwidth * Rheight); //为新图像分配值

	//double h_times = (double)Rheight / (double)lHeight;
	//double w_times = (double)Rwidth / (double)lWidth;
	int  x1, y1, x2, y2;
	BYTE f11, f12, f21, f22;
	double x, y;
	for (int i = 0; i < Rheight; i++)
	{
		for (int j = 0; j < Rwidth; j++)
		{
			x = j / m;
			y = i / m;
			x1 = (x - 1);
			x2 = (x + 1);
			y1 = (y + 1);
			y2 = (y - 1);
			if (x1 >= 0 && x1 < lWidth&&y1 >= 0 && y1 < lHeight)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * y1 + x1;
				f11 = (BYTE)*lpSrc;
			}
			else
			{
				f11 = 0;
			}
			if (x1 >= 0 && x1 < lWidth&&y2 >= 0 && y2 < lHeight)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * y2 + x1;
				f12 = (BYTE)*lpSrc;
			}
			else
			{
				f12 = 0;
			}
			if (x2 >= 0 && x2 < lWidth&&y1 >= 0 && y1 < lHeight)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * y1 + x2;
				f21 = (BYTE)*lpSrc;
			}
			else
			{
				f21 = 0;
			}
			if (x2 >= 0 && x2 < lWidth&&y2 >= 0 && y2 < lHeight)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * y2 + x2;
				f22 = (BYTE)*lpSrc;
			}
			else
			{
				f22 = 0;
			}
			lpDst = (LPBYTE)lpNewDIBBits + Rwidth * i + j;
			*lpDst = (BYTE)(((f11 * (x2 - x) * (y2 - y)) +
				(f21 * (x - x1) * (y2 - y)) +
				(f12 * (x2 - x) * (y - y1)) +
				(f22 * (x - x1) * (y - y1))) / ((x2 - x1) * (y2 - y1)));
		}
	}
}

void COpencvMFCView::Zoom(Mat image, Mat Rimage2, int Rwidth, int Rheight) //图像缩放（以指定缩放的长宽为参数）
{
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpSrc;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;
	BYTE pixel;
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	int lWidth = image.cols;    //获得原图像的宽度
	int lHeight = image.rows;  //获得原图像的高度
	lpNewDIBBits = Rimage2.ptr<uchar>(0);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)255, Rwidth * Rheight); //为新图像分配值
	double h_times = (double)Rheight / (double)lHeight, w_times = (double)Rwidth / (double)lWidth;
	int  x1, y1, x2, y2;
	BYTE f11, f12, f21, f22;
	double x, y;
	for (int i = 0; i < Rheight; i++)
	{
		for (int j = 0; j < Rwidth; j++)
		{
			x = j / w_times;
			y = i / h_times;
			x1 = (x - 1);
			x2 = (x + 1);
			y1 = (y + 1);
			y2 = (y - 1);
			if (x1 >= 0 && x1 < lWidth&&y1 >= 0 && y1 < lHeight)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * y1 + x1;
				f11 = (BYTE)*lpSrc;
			}
			else
			{
				f11 = 0;
			}
			if (x1 >= 0 && x1 < lWidth&&y2 >= 0 && y2 < lHeight)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * y2 + x1;
				f12 = (BYTE)*lpSrc;
			}
			else
			{
				f12 = 0;
			}
			if (x2 >= 0 && x2 < lWidth&&y1 >= 0 && y1 < lHeight)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * y1 + x2;
				f21 = (BYTE)*lpSrc;
			}
			else
			{
				f21 = 0;
			}
			if (x2 >= 0 && x2 < lWidth&&y2 >= 0 && y2 < lHeight)
			{
				lpSrc = (LPBYTE)lpDIBBits + lWidth * y2 + x2;
				f22 = (BYTE)*lpSrc;
			}
			else
			{
				f22 = 0;
			}
			lpDst = (LPBYTE)lpNewDIBBits + Rwidth * i + j;
			*lpDst = (BYTE)(((f11 * (x2 - x) * (y2 - y)) +
				(f21 * (x - x1) * (y2 - y)) +
				(f12 * (x2 - x) * (y - y1)) +
				(f22 * (x - x1) * (y - y1))) / ((x2 - x1) * (y2 - y1)));
		}
	}
	// 复制变换后的图像
	//memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

}

void COpencvMFCView::Convert(Mat image) //图像倒置
{
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpSrc;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;
	BYTE pixel;
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);

	for (j = 0;j < lHeight;j++)
		for (i = 0;i < lWidth;i++)
		{
			lpSrc = (LPBYTE)lpDIBBits + lWidth * (lHeight - 1 - j) + i;
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			pixel = (BYTE)*lpSrc;
			*lpDst = pixel;
		}
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	//释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::Inversion(Mat image) //图像反转
{
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	LPBYTE	lpSrc;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;
	BYTE pixel;
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	lpNewDIBBits = (LPBYTE)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);

	for (j = 0;j < lHeight;j++)
		for (i = 0;i < lWidth;i++)
		{
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + (lWidth - 1 - i);
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			pixel = (BYTE)*lpSrc;
			*lpDst = pixel;
		}
	// 复制处理后的图像到原图像中
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	//释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
}

void COpencvMFCView::Frame(Mat Image3, Mat Miximage, Mat frame1)  //给图像加相框
{
	//Mat Miximage;
	int lHeight = Image3.rows;
	int lWidth = Image3.cols;
	//将相框缩放到与图片一样大
	Mat achannels[3];
	Mat Zoommat[3];
	Mat frame;
	for (int i = 0;i < 3;i++)
	{
		Zoommat[i].create(lHeight, lWidth, CV_8UC1);
	}
	split(frame1, achannels);
	Zoom(achannels[0], Zoommat[0], lWidth, lHeight);
	Zoom(achannels[1], Zoommat[1], lWidth, lHeight);
	Zoom(achannels[2], Zoommat[2], lWidth, lHeight);
	merge(Zoommat, 3, frame);

	Mat miximage[3];
	for (int i = 0;i < 3;i++)
	{
		miximage[i].create(lHeight, lWidth, CV_8UC1);
	}
	Mat achannels2[3];
	split(frame, achannels2);
	if (Image3.channels() == 1)
	{
		Imageplus(Image3, achannels2[0], miximage[0], 1, 1, 0, 0, 0);
		Imageplus(Image3, achannels2[1], miximage[1], 1, 1, 0, 0, 0);
		Imageplus(Image3, achannels2[2], miximage[2], 1, 1, 0, 0, 0);
		merge(miximage, 3, Miximage);
	}
	else if (Image3.channels() == 3)
	{
		Mat achannels1[3];
		split(Image3, achannels1);
		Imageplus(achannels1[0], achannels2[0], miximage[0], 1, 1, 0, 0, 0);
		Imageplus(achannels1[1], achannels2[1], miximage[1], 1, 1, 0, 0, 0);
		Imageplus(achannels1[2], achannels2[2], miximage[2], 1, 1, 0, 0, 0);
		merge(miximage, 3, Miximage);
	}
}

int COpencvMFCView::Threshold(Mat image, int gen)
{
	//图像信息
	int lHeight = image.rows;
	int lWidth = image.cols;
	int lStep = image.step / sizeof(uchar);
	uchar *pData = (uchar*)image.data;
	//int midgray;
	int diff;
	diff = 0;
	int F[256] = { 0 }; //直方图数组
	int Graysum = 0;//灰度值和
	int Pixelsum = 0;//像素数和
	byte pixelbt;//某点的像素值

	uchar T1 = 0; //阀值
	uchar Tnew = 0; //新阀值
	uchar maxgray = 0, mingray = 255;//原图像中的最大灰度值和最小灰度值
	uchar meangray, meangray2;

	for (int i = 0; i < lWidth; i++)
	{
		for (int j = 0; j < lHeight; j++)
		{
			pixelbt = pData[j*lStep + i];
			if (pixelbt < mingray)
				mingray = pixelbt;
			if (pixelbt > maxgray)
				maxgray = pixelbt;
			F[pixelbt]++;
		}
	}

	T1 = 0;
	Tnew = (mingray + maxgray) / 2;//初始阀值(图像的平均灰度)
	diff = maxgray - mingray;

	for (int a = 0; (abs(T1 - Tnew) > 0.5) && a < gen; a++)//迭代中止条件
	{
		T1 = Tnew;
		//小于当前阀值部分的平均灰度值
		for (int i = mingray; i < T1; i++)
		{
			Graysum += F[i] * i;//F[]存储图像信息
			Pixelsum += F[i];
		}

		meangray = (uchar)(Graysum / Pixelsum);
		//大于当前阀值部分的平均灰度值
		Pixelsum = 0;
		Graysum = 0;
		for (int j = T1 + 1; j < maxgray; j++)
		{
			Graysum += F[j] * j;//F[]存储图像信息
			Pixelsum += F[j];
		}

		meangray2 = (uchar)(Graysum / Pixelsum);

		Tnew = (meangray2 + meangray) / 2;        //新阀值
		diff = abs(meangray2 - meangray);
	}

	return T1;
}


void COpencvMFCView::FUDIAO(int value)
{
	Mat Image2 = rawImage2.clone();
	long lHeight = Image2.rows;
	long lWidth = Image2.cols;
	Mat image3;
	image3.create(lHeight, lWidth, Image2.type());
	if (Image2.channels() == 3)
	{
		for (int i = 1;i < lHeight;i++)
			for (int j = 1;j < lWidth;j++)
			{
				image3.at<Vec3b>(i, j)[0] = Image2.at<Vec3b>(i - 1, j - 1)[0] - Image2.at<Vec3b>(i, j)[0] + value;
				image3.at<Vec3b>(i, j)[1] = Image2.at<Vec3b>(i - 1, j - 1)[1] - Image2.at<Vec3b>(i, j)[1] + value;
				image3.at<Vec3b>(i, j)[2] = Image2.at<Vec3b>(i - 1, j - 1)[2] - Image2.at<Vec3b>(i, j)[2] + value;
			}
	}
	else if (Image2.channels() == 1)
	{
		for (int i = 1;i < lHeight;i++)
			for (int j = 1;j < lWidth;j++)
			{
				image3.at<uchar>(i, j) = Image2.at<uchar>(i - 1, j - 1) - Image2.at<uchar>(i, j) + value;
			}
	}
	CImage cimage;
	CDC *pDC = GetDC();
	MatToCimage(image3, cimage);
	cimage.Draw(pDC->GetSafeHdc(), cimage.GetWidth() + 20, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());
}

Mat COpencvMFCView::Histogram_Equalization2(Mat image)
{
	long i, j;			//循环变量
	BYTE pixel;	//像素值
	BYTE pixel1;
	BYTE pixel2;
	Mat achannel[3];
	split(image, achannel);
	int nRst[256];  //直方图均衡化之后存放每个灰度级的像素的值
	LONG lHeight = image.rows;
	LONG lWidth = image.cols;
	Mat image2;
	image2.create(image.rows, image.cols, CV_8UC3);

	// 初始化中间变量temp
	memset(temp, 0, sizeof(temp));
	memset(fPro, 0, sizeof(fPro));
	memset(fProT, 0, sizeof(fProT));
	int sum = 0, sum2 = 0;
	// 获取原图像灰度分布的概率密度
	CDC *pDC = GetDC();
	CImage cimage2;
	MatToCimage(image, cimage2);
	cimage2.Draw(pDC->GetSafeHdc(), (cimage2.GetWidth() + 20), 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
	pDC->TextOut((cimage2.GetWidth() + 20), cimage2.GetHeight() + 5, _T("RGB转HSI"));
	Histogram_Statistic(achannel[2], fPro);

	//进行直方图均衡化处理
	for (i = 0;i < 256;i++)
	{
		temp[i] = fPro[i];
	}
	for (i = 1;i < 256;i++)
	{
		temp[i] = temp[i] + temp[i - 1];   //累计概率
	}
	for (i = 0;i < 256;i++)
	{
		nRst[i] = (int)(temp[i] * 255 + 0.5); //四舍五入，计算直方图均衡化后的灰度值
	}
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0;i < lWidth; i++)
		{

			pixel = image.at<Vec3b>(j, i)[0];
			pixel1 = image.at<Vec3b>(j, i)[1];
			pixel2 = image.at<Vec3b>(j, i)[2];
			//pixel = image.at<Vec3b>(j, i)[0];
			sum = sum + pixel;
			image2.at<Vec3b>(j, i)[0] = pixel;
			image2.at<Vec3b>(j, i)[1] = pixel1;
			image2.at<Vec3b>(j, i)[2] = (BYTE)nRst[pixel2];
		}
	}
	average1 = float(sum) / (lWidth*lHeight);  //平均灰度
	int graysum = 0;
	for (i = 0;i < 256;i++)
	{
		graysum = graysum + gray[i];
		if (graysum >= ((lWidth*lHeight) / 2))
		{
			mid1 = i;           //中值灰度
			break;
		}
	}
	float stannum1 = 0;
	for (i = 0;i < 256;i++)
	{
		stannum1 = stannum1 + (average1 - i)*(average1 - i)*gray[i];
	}
	stan1 = sqrt(stannum1 / (lWidth*lHeight));
	split(image2, achannel);
	Histogram_Statistic(achannel[2], fProT);
	//Histogram_Statistic(achannel[0], fProT);
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0;i < lWidth; i++)
		{
			pixel = image.at<Vec3b>(j, i)[2];
			sum2 = sum2 + pixel;
		}
	}
	average2 = float(sum2) / (lWidth*lHeight);  //平均灰度
	int graysum2 = 0;
	for (i = 0;i < 256;i++)
	{
		graysum2 = graysum2 + gray[i];
		if (graysum2 >= ((lWidth*lHeight) / 2))
		{
			mid2 = i;     //中值灰度
			break;
		}
	}
	float stannum2 = 0;
	for (i = 0;i < 256;i++)
	{
		stannum2 = stannum2 + (average2 - i)*(average2 - i)*gray[i];
	}
	stan2 = sqrt(stannum2 / (lWidth*lHeight));
	return image2;
}

void COpencvMFCView::LineTransMat(BYTE min, BYTE max) //线性增强
{
	Mat Image2 = rawImage2.clone();
	CDC *pDC = GetDC();
	if (Image2.channels() == 1)
	{
		Linear_Transform(Image2, min, max);
	}
	else if (Image2.channels() == 3)
	{
		Mat achannels[3];
		split(Image2, achannels);
		Linear_Transform(achannels[0], min, max);
		Linear_Transform(achannels[1], min, max);
		Linear_Transform(achannels[2], min, max);
		merge(achannels, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}

void COpencvMFCView::SegLineTransMat(int Linenum, BYTE s[], BYTE t[]) //分段线性增强
{
	Mat Image2 = rawImage2.clone();
	CDC *pDC = GetDC();
	if (Linenum > 255)
	{
		MessageBox(_T("段数不能大于255"));
	}
	if (Image2.channels() == 1)
	{
		Seg_Linear_Transform(Image2, Linenum, s, t);
	}
	else if (Image2.channels() == 3)
	{
		Mat achannels[3];
		split(Image2, achannels);
		Seg_Linear_Transform(achannels[0], Linenum, s, t);
		Seg_Linear_Transform(achannels[1], Linenum, s, t);
		Seg_Linear_Transform(achannels[2], Linenum, s, t);
		merge(achannels, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}

void COpencvMFCView::LogLineTransMat(double a, double b, double c)  //非线性增强（对数函数）
{
	Mat Image2 = rawImage2.clone();
	CDC *pDC = GetDC();
	if (Image2.channels() == 1)
	{
		Log_Transform(Image2, a, b, c);
	}
	else if (Image2.channels() == 3)
	{
		Mat achannels[3];
		split(Image2, achannels);
		Log_Transform(achannels[0], a, b, c);
		Log_Transform(achannels[1], a, b, c);
		Log_Transform(achannels[2], a, b, c);
		merge(achannels, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}

void COpencvMFCView::HistogramequalMat()  //直方图均衡化
{
	Mat Image2 = rawImage2.clone();
	CDC *pDC = GetDC();
	if (Image2.channels() == 1)
	{
		Histogram_Equalization(Image2);
		CImage cimage2;
		MatToCimage(Image2, cimage2);
		cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
			0, 0, cimage2.GetWidth(), cimage2.GetHeight());
	}
	else if (Image2.channels() == 3)
	{
		CString str;
		double run_time;
		_LARGE_INTEGER time_start;	//开始时间
		_LARGE_INTEGER time_over;	//结束时间
		double dqFreq;		//计时器频率
		LARGE_INTEGER f;	//计时器频率
		QueryPerformanceFrequency(&f);
		dqFreq = (double)f.QuadPart;
		QueryPerformanceCounter(&time_start);	//计时开始
		Mat achannels[3];
		split(Image2, achannels);
		Histogram_Equalization(achannels[0]);
		Histogram_Equalization(achannels[1]);
		Histogram_Equalization(achannels[2]);
		merge(achannels, 3, Image2);
		QueryPerformanceCounter(&time_over);	//计时结束
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		str.Format(_T("time:%f us"), run_time);//前后之差即程序运行时间
		CImage cimage2;
		MatToCimage(Image2, cimage2);
		cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
			0, 0, cimage2.GetWidth(), cimage2.GetHeight());
		pDC->TextOut(2 * (cimage2.GetWidth() + 20) + 100, cimage2.GetHeight() + 5, str);
	}
	myImage = Image2.clone();

}

void COpencvMFCView::TransMat(int x, int y) //平移
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2.create(rawImage2.rows, rawImage2.cols, rawImage2.type());
	Image2 = rawImage2.clone();
	//Trans(Image2, x, y);
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + x, y, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}

void COpencvMFCView::ZoomMat(double m) //缩放
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	//先求缩放后的长宽
	Mat Image2;
	Image2 = rawImage2.clone();
	LONG lWidth = Image2.cols;    //获得原图像的宽度
	LONG lHeight = Image2.rows;  //获得原图像的高度

	//先求缩放后的长宽
	int Rwidth, Rheight;
	Rwidth = (int)(lWidth*m);
	Rheight = (int)(lHeight*m);
	Mat Rimage2;
	if (Image2.channels() == 1)
	{
		Rimage2.create(Rheight, Rwidth, CV_8UC1);  //创建一个新图像
		Zoom(Image2, Rimage2, m);
	}
	else if (Image2.channels() == 3)
	{
		Mat Zoomimage[3];
		for (int i = 0;i < 3;i++)
		{
			Zoomimage[i].create(Rheight, Rwidth, CV_8UC1);  //创建一个新图像
		}
		Mat achannels[3];
		split(Image2, achannels);
		Zoom(achannels[0], Zoomimage[0], m);
		Zoom(achannels[1], Zoomimage[1], m);
		Zoom(achannels[2], Zoomimage[2], m);
		merge(Zoomimage, 3, Rimage2);
	}
	CImage cimage2, cimage3;
	MatToCimage(Rimage2, cimage2);
	MatToCimage(Image2, cimage3);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = Rimage2.clone();
}

void COpencvMFCView::ZoomMat(int Rwidth, int Rheight) //缩放
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	//先求缩放后的长宽
	Mat Image2;
	Image2 = rawImage2.clone();
	Mat Rimage2;
	if (Image2.channels() == 1)
	{
		Rimage2.create(Rheight, Rwidth, CV_8UC1);  //创建一个新图像
		Zoom(Image2, Rimage2, Rwidth, Rheight);
	}
	else if (Image2.channels() == 3)
	{
		Mat Zoomimage[3];
		for (int i = 0;i < 3;i++)
		{
			Zoomimage[i].create(Rheight, Rwidth, CV_8UC1);  //创建一个新图像
		}
		Mat achannels[3];
		split(Image2, achannels);
		Zoom(achannels[0], Zoomimage[0], Rwidth, Rheight);
		Zoom(achannels[1], Zoomimage[1], Rwidth, Rheight);
		Zoom(achannels[2], Zoomimage[2], Rwidth, Rheight);
		merge(Zoomimage, 3, Rimage2);
	}
	CImage cimage2, cimage3;
	MatToCimage(Rimage2, cimage2);
	MatToCimage(Image2, cimage3);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = Rimage2.clone();
}

void COpencvMFCView::RotateMat(double ang) //旋转
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2 = rawImage2.clone();
	LONG lWidth = Image2.cols;    //获得原图像的宽度
	LONG lHeight = Image2.rows;  //获得原图像的高度
	double degree;
	degree = pi * ang / 180.0;  //旋转角度的转换

	//计算旋转后的图像宽高。以图像中心为原点旋转
	int midx, midy;
	midx = lWidth / 2;
	midy = lHeight / 2;
	int left1x, left1y, left2x, left2y, right1x, right1y, right2x, right2y;
	left1x = -lWidth / 2; //左上
	left1y = lHeight / 2;
	left2x = -lWidth / 2; //左下
	left2y = -lHeight / 2;
	right1x = lWidth / 2;//右上
	right1y = lHeight / 2;
	right2x = lWidth / 2;//右下
	right2y = -lHeight / 2;
	double Tleft1x, Tleft1y, Tleft2x, Tleft2y, Tright1x, Tright1y, Tright2x, Tright2y;
	Tleft1x = left1x * cos(degree) + left1y * sin(degree);
	Tleft1y = -left1x * sin(degree) + left1y * cos(degree);
	Tleft2x = left2x * cos(degree) + left2y * sin(degree);
	Tleft2y = -left2x * sin(degree) + left2y * cos(degree);
	Tright1x = right1x * cos(degree) + right1y * sin(degree);
	Tright1y = -right1x * sin(degree) + right1y * cos(degree);
	Tright2x = right2x * cos(degree) + right2y * sin(degree);
	Tright2y = -right2x * sin(degree) + right2y * cos(degree);
	int desWidth = max(abs(Tright2x - Tleft1x), abs(Tright1x - Tleft2x));
	int desHeight = max(abs(Tright2y - Tleft1y), abs(Tright1y - Tleft2y));
	Mat image3;
	if (Image2.channels() == 1)
	{
		image3.create(desHeight, desWidth, CV_8UC1);
		Rotate(Image2, image3, ang);
	}
	else if (Image2.channels() == 3)
	{
		Mat Rotateimage[3];
		for (int i = 0;i < 3;i++)
		{
			Rotateimage[i].create(desHeight, desWidth, CV_8UC1);
		}
		Mat achannels[3];
		split(Image2, achannels);
		Rotate(achannels[0], Rotateimage[0], ang);
		Rotate(achannels[1], Rotateimage[1], ang);
		Rotate(achannels[2], Rotateimage[2], ang);
		merge(Rotateimage, 3, image3);
	}
	CImage cimage2, cimage3;
	MatToCimage(image3, cimage2);
	MatToCimage(Image2, cimage3);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = image3.clone();
}

void COpencvMFCView::ConvertMat()  //图像倒置
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	CDC *pDC = GetDC();
	CString str;
	Image2 = rawImage2.clone();
	if (Image2.channels() == 1)
	{
		Convert(Image2);
		CImage cimage2;
		MatToCimage(Image2, cimage2);
		cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
			0, 0, cimage2.GetWidth(), cimage2.GetHeight());
	}
	else if (Image2.channels() == 3)
	{
		double run_time;
		_LARGE_INTEGER time_start;	//开始时间
		_LARGE_INTEGER time_over;	//结束时间
		double dqFreq;		//计时器频率
		LARGE_INTEGER f;	//计时器频率
		QueryPerformanceFrequency(&f);
		dqFreq = (double)f.QuadPart;
		QueryPerformanceCounter(&time_start);	//计时开始
		Mat achannels[3];
		split(Image2, achannels);
		Convert(achannels[0]);
		Convert(achannels[1]);
		Convert(achannels[2]);
		merge(achannels, 3, Image2);
		QueryPerformanceCounter(&time_over);	//计时结束
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		str.Format(_T("time:%f us"), run_time);//前后之差即程序运行时间
		CImage cimage2;
		MatToCimage(Image2, cimage2);
		cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
			0, 0, cimage2.GetWidth(), cimage2.GetHeight());
		pDC->TextOut(2 * (cimage2.GetWidth() + 20) + 30, cimage2.GetHeight() + 5, str);
	}
	myImage = Image2.clone();
}

Mat COpencvMFCView::ConvertHSI(Mat image)
{
	long i, j;
	BYTE pixel;
	LPBYTE lpDIBBits = image.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth = image.cols;    //获得原图像的宽度
	LONG lHeight = image.rows;  //获得原图像的高度
	Mat image2;
	image2.create(lHeight, lWidth, image.type());
	for (j = 0;j < lHeight;j++)
		for (i = 0;i < lWidth;i++)
		{
			image2.at<Vec3b>(j, i)[0] = image.at<Vec3b>(lHeight - 1 - j, i)[0];
			image2.at<Vec3b>(j, i)[1] = image.at<Vec3b>(lHeight - 1 - j, i)[1];
			image2.at<Vec3b>(j, i)[2] = image.at<Vec3b>(lHeight - 1 - j, i)[2];
		}
	return image2;
}

void COpencvMFCView::InversionMat() //图像反转
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2 = rawImage2.clone();
	if (Image2.channels() == 1)
	{
		Inversion(Image2);
	}
	else if (Image2.channels() == 3)
	{
		Mat achannels[3];
		split(Image2, achannels);
		Inversion(achannels[0]);
		Inversion(achannels[1]);
		Inversion(achannels[2]);
		merge(achannels, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}

void COpencvMFCView::Imageplus(Mat image1, Mat image2, Mat Miximage, double alp1, double alp2, int light, int positionx, int positiony)  //图像叠加融合
{
	LPBYTE	lpDst;			// 指向缓存图像的指针
	BYTE	lpSrc1;
	BYTE	lpSrc2;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	int i, j;
	BYTE pixel1, pixel2;
	//LPBYTE lpDIBBits1 = image1.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth1 = image1.cols;    //获得原图像的宽度
	LONG lHeight1 = image1.rows;  //获得原图像的高度
	//LPBYTE lpDIBBits2 = image2.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth2 = image2.cols;    //获得原图像的宽度
	LONG lHeight2 = image2.rows;  //获得原图像的高度
	LONG mixwidth, mixheight;
	mixwidth = lWidth1 > lWidth2 ? lWidth1 : lWidth2;
	mixheight = lHeight1 > lHeight2 ? lHeight1 : lHeight2;
	for (j = 0;j < mixheight;j++)
		for (i = 0;i < mixwidth;i++)
		{
			int pixel3;
			lpSrc1 = (BYTE)image1.at<uchar>(j, i);
			pixel1 = lpSrc1;
			if (j<positiony || j>positiony + lHeight2 - 1 || i<positionx || i>positionx + lWidth2 - 1)
			{
				pixel3 = pixel1 * alp1 + light;
				pixel2 = 255;
			}
			else
			{
				lpSrc2 = (BYTE)image2.at<uchar>(j - positiony, i - positionx);
				pixel2 = lpSrc2;
				pixel3 = (pixel1 * alp1 + pixel2 * alp2) + light;
			}
			if (pixel3 > 255)
			{
				pixel3 = pixel2;
			}
			Miximage.at<uchar>(j, i) = pixel3;
		}
}

void COpencvMFCView::Imagesub(Mat image1, Mat image2, Mat Splitimage)  //图像分离
{
	LPBYTE	lpDst;			// 指向缓存图像的指针
	LPBYTE	lpSrc1;
	LPBYTE	lpSrc2;
	LPBYTE	lpNewDIBBits;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits;
	long i, j;
	BYTE pixel1, pixel2;
	LPBYTE lpDIBBits1 = image1.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth1 = image1.cols;    //获得原图像的宽度
	LONG lHeight1 = image1.rows;  //获得原图像的高度
	LPBYTE lpDIBBits2 = image2.ptr<uchar>(0);//找到原图像的起始位置
	LONG lWidth2 = image2.cols;    //获得原图像的宽度
	LONG lHeight2 = image2.rows;  //获得原图像的高度
	LONG mixwidth, mixheight;
	mixwidth = lWidth1 > lWidth2 ? lWidth1 : lWidth2;
	mixheight = lHeight1 > lHeight2 ? lHeight1 : lHeight2;
	//Splitimage.create(mixheight, mixwidth, rawImage2.type());  //创建一个新图像
	lpNewDIBBits = Splitimage.ptr<uchar>(0);
	// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)255, mixwidth * mixheight); //为新图像分配值
	Mat miximage1, miximage2;
	miximage1.create(mixheight, mixwidth, rawImage2.type());  //创建一个新图像
	miximage2.create(mixheight, mixwidth, rawImage2.type());  //创建一个新图像
	LPBYTE lpSrcmix1, lpSrcmix2;
	LPBYTE mixlpDIBBits1 = miximage1.ptr<uchar>(0);
	LPBYTE mixlpDIBBits2 = miximage2.ptr<uchar>(0);
	lpSrcmix1 = (LPBYTE)mixlpDIBBits1;
	lpSrcmix2 = (LPBYTE)mixlpDIBBits2;
	memset(lpSrcmix1, (BYTE)0, mixwidth * mixheight); //为新图像分配值
	memset(lpSrcmix2, (BYTE)0, mixwidth * mixheight); //为新图像分配值
	for (j = 0;j < lHeight1;j++)
		for (i = 0;i < lWidth1;i++)
		{
			lpSrc1 = (LPBYTE)lpDIBBits1 + lWidth1 * j + i;
			lpSrcmix1 = (LPBYTE)mixlpDIBBits1 + mixwidth * j + i;
			*lpSrcmix1 = (BYTE)*lpSrc1;
		}
	for (j = 0;j < lHeight2;j++)
		for (i = 0;i < lWidth2;i++)
		{
			lpSrc2 = (LPBYTE)lpDIBBits2 + lWidth2 * j + i;
			lpSrcmix2 = (LPBYTE)mixlpDIBBits2 + mixwidth * j + i;
			*lpSrcmix2 = (BYTE)*lpSrc2;
		}
	for (j = 0;j < mixheight;j++)
		for (i = 0;i < mixwidth;i++)
		{
			lpSrcmix1 = (LPBYTE)mixlpDIBBits1 + mixwidth * j + i;
			lpSrcmix2 = (LPBYTE)mixlpDIBBits2 + mixwidth * j + i;
			lpDst = (LPBYTE)lpNewDIBBits + mixwidth * j + i;
			pixel1 = (BYTE)*lpSrcmix1;
			pixel2 = (BYTE)*lpSrcmix2;
			int Pixel3;
			Pixel3 = pixel1 * 2 - pixel2;
			if (Pixel3 < 0)
			{
				Pixel3 = 0;
			}
			*lpDst = Pixel3;
		}
	CImage cimage2, cimage3, cimage4;
	MatToCimage(Splitimage, cimage2);
	MatToCimage(image1, cimage3);
	MatToCimage(image2, cimage4);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 5, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = Splitimage.clone();
}

void COpencvMFCView::ImageplusMat(Mat image1, Mat image2, double alp1, double alp2, int light, double positionx, double positiony) //图像融合
{
	Mat Miximage;
	LONG lWidth1 = image1.cols;    //获得原图像的宽度
	LONG lHeight1 = image1.rows;  //获得原图像的高度
	Mat Zoomimage[3];
	Mat achannels11[3];
	CImage cimage2, cimage3, cimage4;
	Mat image3;
	int PX = positionx * lWidth1;
	int PY = positiony * lHeight1;
	int XX = lWidth1 - PX;
	int YY = lHeight1 - PY;
	LONG lWidth2 = image2.cols;    //获得图像2的宽度
	LONG lHeight2 = image2.rows;  //获得图像2的高度
	lWidth2 = (lWidth2 > (lWidth1 - PX)) ? (lWidth1 - PX) : lWidth2;
	lHeight2 = (lHeight2 > (lHeight1 - PY)) ? (lHeight1 - PY) : lHeight2;
	if (image2.channels() == 3)
	{
		for (int i = 0;i < 3;i++)
		{
			Zoomimage[i].create(lHeight2, lWidth2, CV_8UC1);  //创建一个新图像
		}
		split(image2, achannels11);
		Zoom(achannels11[0], Zoomimage[0], lWidth2, lHeight2);
		Zoom(achannels11[1], Zoomimage[1], lWidth2, lHeight2);
		Zoom(achannels11[2], Zoomimage[2], lWidth2, lHeight2);
		merge(Zoomimage, 3, image3);
	}
	else if (image2.channels() == 1)
	{
		image3.create(lHeight2, lWidth2, CV_8UC1);
		Zoom(image2, image3, lWidth2, lHeight2);
	}
	if (image1.channels() == 1)
	{
		if (image3.channels() == 1)
		{
			Miximage.create(lHeight1, lWidth1, CV_8UC1);
			Imageplus(image1, image3, Miximage, alp1, alp2, light, PX, PY);

			MatToCimage(Miximage, cimage2);
			MatToCimage(image1, cimage3);
			MatToCimage(image2, cimage4);
			CDC *pDC = GetDC();
			cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 10, 0, cimage2.GetWidth(), cimage2.GetHeight(),
				0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
			myImage = Miximage.clone();
		}
		else if (image3.channels() == 3)
		{
			Mat miximage[3];
			for (int i = 0;i < 3;i++)
			{
				miximage[i].create(lHeight1, lWidth1, CV_8UC1);
			}
			Mat achannels[3];
			split(image3, achannels);
			Imageplus(image1, achannels[0], miximage[0], alp1, alp2, light, PX, PY);
			Imageplus(image1, achannels[1], miximage[1], alp1, alp2, light, PX, PY);
			Imageplus(image1, achannels[2], miximage[2], alp1, alp2, light, PX, PY);
			merge(miximage, 3, Miximage);
			MatToCimage(Miximage, cimage2);
			MatToCimage(image1, cimage3);
			MatToCimage(image2, cimage4);
			CDC *pDC = GetDC();
			cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 10, 0, cimage2.GetWidth(), cimage2.GetHeight(),
				0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
			myImage = Miximage.clone();
		}
	}
	else if (image1.channels() == 3)
	{
		if (image3.channels() == 1)
		{
			Mat miximage[3];
			for (int i = 0;i < 3;i++)
			{
				miximage[i].create(lHeight1, lWidth1, CV_8UC1);
			}
			Mat achannels[3];
			split(image1, achannels);
			Imageplus(achannels[0], image3, miximage[0], alp1, alp2, light, PX, PY);
			Imageplus(achannels[1], image3, miximage[1], alp1, alp2, light, PX, PY);
			Imageplus(achannels[2], image3, miximage[2], alp1, alp2, light, PX, PY);
			merge(miximage, 3, Miximage);
			MatToCimage(Miximage, cimage2);
			MatToCimage(image1, cimage3);
			MatToCimage(image2, cimage4);
			CDC *pDC = GetDC();
			cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 10, 0, cimage2.GetWidth(), cimage2.GetHeight(),
				0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
			myImage = Miximage.clone();
		}
		else if (image3.channels() == 3)
		{
			Mat miximage[3];
			for (int i = 0;i < 3;i++)
			{
				miximage[i].create(lHeight1, lWidth1, CV_8UC1);
			}
			Mat achannels1[3];
			Mat achannels2[3];
			split(image1, achannels1);
			split(image3, achannels2);
			Imageplus(achannels1[0], achannels2[0], miximage[0], alp1, alp2, light, PX, PY);
			Imageplus(achannels1[1], achannels2[1], miximage[1], alp1, alp2, light, PX, PY);
			Imageplus(achannels1[2], achannels2[2], miximage[2], alp1, alp2, light, PX, PY);
			merge(miximage, 3, Miximage);
			//CImage cimage2, cimage3, cimage4;
			MatToCimage(Miximage, cimage2);
			MatToCimage(image1, cimage3);
			MatToCimage(image2, cimage4);
			CDC *pDC = GetDC();
			cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 10, 0, cimage2.GetWidth(), cimage2.GetHeight(),
				0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
			myImage = Miximage.clone();
		}
	}
}

void COpencvMFCView::ImagesubMat(Mat image1, Mat image2)     //图像分离
{
	Mat Splitimage;
	LONG lWidth1 = image1.cols;    //获得原图像的宽度
	LONG lHeight1 = image1.rows;  //获得原图像的高度
	LONG lWidth2 = image2.cols;    //获得原图像的宽度
	LONG lHeight2 = image2.rows;  //获得原图像的高度
	LONG mixwidth, mixheight;
	mixwidth = lWidth1 > lWidth2 ? lWidth1 : lWidth2;
	mixheight = lHeight1 > lHeight2 ? lHeight1 : lHeight2;
	if (image1.channels() == 1)
	{
		if (image2.channels() == 1)
		{
			Splitimage.create(mixheight, mixwidth, CV_8UC1);
			Imagesub(image1, image2, Splitimage);
			CImage cimage2, cimage3, cimage4;
			MatToCimage(Splitimage, cimage2);
			MatToCimage(image1, cimage3);
			MatToCimage(image2, cimage4);
			CDC *pDC = GetDC();
			cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 10, 0, cimage2.GetWidth(), cimage2.GetHeight(),
				0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
			myImage = Splitimage.clone();
		}
		else if (image2.channels() == 3)
		{
			Mat miximage[3];
			for (int i = 0;i < 3;i++)
			{
				miximage[i].create(mixheight, mixwidth, CV_8UC1);
			}
			Mat achannels[3];
			split(image2, achannels);
			Imagesub(image1, achannels[0], miximage[0]);
			Imagesub(image1, achannels[1], miximage[1]);
			Imagesub(image1, achannels[2], miximage[2]);
			merge(miximage, 3, Splitimage);
			CImage cimage2, cimage3, cimage4;
			MatToCimage(Splitimage, cimage2);
			MatToCimage(image1, cimage3);
			MatToCimage(image2, cimage4);
			CDC *pDC = GetDC();
			cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 10, 0, cimage2.GetWidth(), cimage2.GetHeight(),
				0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
			myImage = Splitimage.clone();
		}
	}
	else if (image1.channels() == 3)
	{
		if (image2.channels() == 1)
		{
			Mat miximage[3];
			for (int i = 0;i < 3;i++)
			{
				miximage[i].create(mixheight, mixwidth, CV_8UC1);
			}
			Mat achannels[3];
			split(image1, achannels);
			Imagesub(achannels[0], image2, miximage[0]);
			Imagesub(achannels[1], image2, miximage[1]);
			Imagesub(achannels[2], image2, miximage[2]);
			merge(miximage, 3, Splitimage);
			CImage cimage2, cimage3, cimage4;
			MatToCimage(Splitimage, cimage2);
			MatToCimage(image1, cimage3);
			MatToCimage(image2, cimage4);
			CDC *pDC = GetDC();
			cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 10, 0, cimage2.GetWidth(), cimage2.GetHeight(),
				0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
			myImage = Splitimage.clone();
		}
		else if (image2.channels() == 3)
		{
			Mat miximage[3];
			for (int i = 0;i < 3;i++)
			{
				miximage[i].create(mixheight, mixwidth, CV_8UC1);
			}
			Mat achannels1[3];
			Mat achannels2[3];
			split(image1, achannels1);
			split(image2, achannels2);
			Imagesub(achannels1[0], achannels2[0], miximage[0]);
			Imagesub(achannels1[1], achannels2[1], miximage[1]);
			Imagesub(achannels1[2], achannels2[2], miximage[2]);
			merge(miximage, 3, Splitimage);
			CImage cimage2, cimage3, cimage4;
			MatToCimage(Splitimage, cimage2);
			MatToCimage(image1, cimage3);
			MatToCimage(image2, cimage4);
			CDC *pDC = GetDC();
			cimage2.Draw(pDC->GetSafeHdc(), cimage3.GetWidth() + cimage4.GetWidth() + 10, 0, cimage2.GetWidth(), cimage2.GetHeight(),
				0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
			myImage = Splitimage.clone();
		}
	}
}

Mat COpencvMFCView::ImageplusSeg(Mat image1, Mat image2)
{
	Mat image3;
	LONG lHeight = image1.rows;
	LONG lWidth = image1.cols;
	image3.create(lHeight, lWidth, image1.type());
	for(int i=0;i<lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			if (image1.at<uchar>(i, j) == 255)
			{
				image3.at<uchar>(i, j) = image2.at<uchar>(i, j);
			}
			else
			{
				image3.at<uchar>(i, j) = 0;
			}
		}
	//myImage = image3.clone();
	return image3;
}

void COpencvMFCView::ImageplusSegMat(Mat image1, Mat image2)
{
	if (image2.channels() == 1)
	{
		myImage =ImageplusSeg(image1, image2);
	}
	else if (image2.channels() == 3)
	{
		Mat achannels[3];
		Mat achannels2[3];
		Mat mImage[3];
		split(image1, achannels);
		split(image2, achannels2);
		mImage[0] = ImageplusSeg(achannels[0], achannels2[0]);
		mImage[1] = ImageplusSeg(achannels[1], achannels2[1]);
		mImage[2] = ImageplusSeg(achannels[2], achannels2[2]);
		merge(mImage, 3, myImage);
	}
	myImage = myImage.clone();
	CImage cimage2;
	MatToCimage(myImage, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), 2*cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}

void COpencvMFCView::GateGradMat(BYTE t)
{
	Mat Image2;
	Image2.create(rawImage2.rows, rawImage2.cols, rawImage2.type());
	Image2 = rawImage2.clone();
	if (Image2.channels() == 1)
	{
		GateGrad(Image2, t);
	}
	else if (Image2.channels() == 3)
	{
		Mat channel[3];
		split(Image2, channel);
		GateGrad(channel[0], t);
		GateGrad(channel[1], t);
		GateGrad(channel[2], t);
		merge(channel, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}

void COpencvMFCView::Roberts(Mat image, double * kG)
{
	double x;
	double y;
	LONG lWidth;
	LONG lHeight;
	int left1, left2, right1, right2;
	lWidth = image.cols;
	lHeight = image.rows;
	double temp;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			kG[i*lWidth + j] = 0;
		}
	for (int i = 0;i < lHeight - 1;i++)
		for (int j = 0;j < lWidth - 1;j++)
		{
			left1 = image.at<uchar>(i, j);
			right1 = image.at<uchar>(i + 1, j + 1);
			x = left1 - right1;
			left2 = image.at<uchar>(i + 1, j);
			right2 = image.at<uchar>(i, j + 1);
			y = right2 - left2;
			temp = sqrt(x*x + y * y) + 0.5;  //欧氏距离
			if (temp > 255)
			{
				temp = 255;
			}
			kG[i*lWidth + j] = temp;
		}
}

void COpencvMFCView::RobertsMat(int T)
{
	int x;
	int y;
	LONG lHeight;
	LONG lWidth;
	Mat Image2 = rawImage2.clone();
	lWidth = Image2.cols; //图像宽
	lHeight = Image2.rows; //图像高
	double *kG; //指向梯度数据的指针
	kG = new double[lWidth*lHeight];
	if (Image2.channels() == 1)
	{
		Roberts(Image2, kG);
		//设置阈值进行二值化 
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				if (kG[i*lWidth + j] > T)
				{
					Image2.at<uchar>(i, j) = 0;
				}
				else
				{
					Image2.at<uchar>(i, j) = 255;
				}
			}
	}
	else if (Image2.channels() == 3)
	{
		Mat HImage;
		HImage.create(lHeight, lWidth, Image2.type());
		double **s;
		double **H;
		s = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			s[i] = new double[lWidth];
		}
		H = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			H[i] = new double[lWidth];
		}
		for (int j = 0;j < lHeight;j++)
			for (int i = 0;i < lWidth;i++)
			{
				float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
				float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
				float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
				float num1 = 0.5*((r - g) + (r - b));
				float num2 = (r - g)*(r - g) + (r - b)*(g - b);
				float d = sqrt(num2);
				float d1 = num1 / d;
				double ang = acos(d1);
				double I = (r + g + b) / 3.0;
				BYTE Ii = I * 255;
				double min;
				min = r > g ? g : r;
				min = min > b ? b : min;
				H[j][i] = (g >= b) ? ang : 2 * pi - ang;
				H[j][i] = H[j][i] / (2 * pi);
				s[j][i] = 1 - (3.0*min) / (r + g + b);
				HImage.at<Vec3b>(j, i)[2] = Ii;
				HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
				HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
			}
		RobertsColor(HImage, kG);
		//设置阈值进行二值化 
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				if (robertsflag == 1)
				{
					if (kG[i*lWidth + j] > T)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 0;
					}
					else
					{
						Image2.at<Vec3b>(i, j)[0] = 255;
						Image2.at<Vec3b>(i, j)[1] = 255;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}
				else
				{
					if (kG[i*lWidth + j] > T)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}

			}
	}
	delete kG;
	kG = NULL;
	CImage cimage;
	CDC *pDC = GetDC();
	MatToCimage(Image2, cimage);
	cimage.Draw(pDC->GetSafeHdc(), cimage.GetWidth() + 20, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());
	myImage = Image2.clone();
}

void COpencvMFCView::RobertsColor(Mat image, double * kG)
{
	double x;
	double y;
	LONG lWidth;
	LONG lHeight;
	int left1, left2, right1, right2;
	lWidth = image.cols;
	lHeight = image.rows;
	double temp;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			kG[i*lWidth + j] = 0;
		}
	for (int i = 0;i < lHeight - 1;i++)
		for (int j = 0;j < lWidth - 1;j++)
		{
			left1 = image.at<Vec3b>(i, j)[2];
			right1 = image.at<Vec3b>(i + 1, j + 1)[2];
			x = left1 - right1;
			left2 = image.at<Vec3b>(i + 1, j)[2];
			right2 = image.at<Vec3b>(i, j + 1)[2];
			y = right2 - left2;
			temp = sqrt(x*x + y * y) + 0.5;  //欧氏距离
			if (temp > 255)
			{
				temp = 255;
			}
			kG[i*lWidth + j] = temp;
		}
}

void COpencvMFCView::SobelMat(int T)
{
	int x;
	int y;
	LONG lHeight;
	LONG lWidth;
	Mat Image2 = rawImage2.clone();
	lWidth = Image2.cols; //图像宽
	lHeight = Image2.rows; //图像高
	double *kG; //指向梯度数据的指针
	kG = new double[lWidth*lHeight];
	if (Image2.channels() == 1)
	{
		Sobel(Image2, kG);
		//设置阈值进行二值化 
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				if (kG[i*lWidth + j] > T)
				{
					Image2.at<uchar>(i, j) = 0;
				}
				else
				{
					Image2.at<uchar>(i, j) = 255;
				}
			}
	}
	else if (Image2.channels() == 3)
	{
		Mat HImage;
		HImage.create(lHeight, lWidth, Image2.type());
		double **s;
		double **H;
		s = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			s[i] = new double[lWidth];
		}
		H = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			H[i] = new double[lWidth];
		}
		for (int j = 0;j < lHeight;j++)
			for (int i = 0;i < lWidth;i++)
			{
				float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
				float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
				float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
				float num1 = 0.5*((r - g) + (r - b));
				float num2 = (r - g)*(r - g) + (r - b)*(g - b);
				float d = sqrt(num2);
				float d1 = num1 / d;
				double ang = acos(d1);
				double I = (r + g + b) / 3.0;
				BYTE Ii = I * 255;
				double min;
				min = r > g ? g : r;
				min = min > b ? b : min;
				H[j][i] = (g >= b) ? ang : 2 * pi - ang;
				H[j][i] = H[j][i] / (2 * pi);
				s[j][i] = 1 - (3.0*min) / (r + g + b);
				HImage.at<Vec3b>(j, i)[2] = Ii;
				HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
				HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
			}
		SobelColor(HImage, kG);
		//设置阈值进行二值化 
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				if (solbelflag == 1)
				{
					if (kG[i*lWidth + j] > T)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 0;
					}
					else
					{
						Image2.at<Vec3b>(i, j)[0] = 255;
						Image2.at<Vec3b>(i, j)[1] = 255;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}
				else
				{
					if (kG[i*lWidth + j] > T)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}
				
				/*	else
					{
						Image2.at<Vec3b>(i, j)[0] = 255;
						Image2.at<Vec3b>(i, j)[1] = 255;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}*/
			}
	}
	delete kG;
	kG = NULL;
	CImage cimage;
	CDC *pDC = GetDC();
	MatToCimage(Image2, cimage);
	cimage.Draw(pDC->GetSafeHdc(), cimage.GetWidth() + 20, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());
	myImage = Image2.clone();
}

void COpencvMFCView::Sobel(Mat image, double * kG)
{
	double x = 0;
	double y = 0;
	LONG lWidth;
	LONG lHeight;
	int vertical[3][3];
	int level[3][3];
	vertical[0][0] = 1;vertical[0][1] = 2;vertical[0][2] = 1;
	vertical[1][0] = 0;vertical[1][1] = 0;vertical[1][2] = 0;
	vertical[2][0] = -1;vertical[2][1] = -2;vertical[2][2] = -1;

	level[0][0] = -1;level[0][1] = 0;level[0][2] = 1;
	level[1][0] = -2;level[1][1] = 0;level[1][2] = 2;
	level[2][0] = -1;level[2][1] = 0;level[2][2] = 1;
	lWidth = image.cols;
	lHeight = image.rows;
	double temp[3][3];
	double kGtemp;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			kG[i*lWidth + j] = 0;
		}
	for (int i = 1;i < lHeight - 1;i++)
		for (int j = 1;j < lWidth - 1;j++)
		{
			temp[0][0] = image.at<uchar>(i - 1, j - 1);
			temp[0][1] = image.at<uchar>(i - 1, j);
			temp[0][2] = image.at<uchar>(i - 1, j + 1);
			temp[1][0] = image.at<uchar>(i, j - 1);
			temp[1][1] = image.at<uchar>(i, j);
			temp[1][2] = image.at<uchar>(i, j + 1);
			temp[2][0] = image.at<uchar>(i + 1, j - 1);
			temp[2][1] = image.at<uchar>(i + 1, j);
			temp[2][2] = image.at<uchar>(i + 1, j + 1);

			for (int p = 0;p < 3;p++)
				for (int t = 0;t < 3;t++)
				{
					x = x + temp[p][t] * vertical[p][t];
					y = y + temp[p][t] * level[p][t];
				}
			x = x * 0.25;
			y = y * 0.25;
			kGtemp = sqrt(x * x + y * y) + 0.5;
			if (kGtemp > 255)
			{
				kGtemp = 255;
			}
			kG[i*lWidth + j] = kGtemp;
		}

}

void COpencvMFCView::SobelColor(Mat image, double * kG)
{
	double x = 0;
	double y = 0;
	LONG lWidth;
	LONG lHeight;
	int vertical[3][3];
	int level[3][3];
	vertical[0][0] = 1;vertical[0][1] = 2;vertical[0][2] = 1;
	vertical[1][0] = 0;vertical[1][1] = 0;vertical[1][2] = 0;
	vertical[2][0] = -1;vertical[2][1] = -2;vertical[2][2] = -1;

	level[0][0] = -1;level[0][1] = 0;level[0][2] = 1;
	level[1][0] = -2;level[1][1] = 0;level[1][2] = 2;
	level[2][0] = -1;level[2][1] = 0;level[2][2] = 1;
	lWidth = image.cols;
	lHeight = image.rows;
	double temp[3][3];
	double kGtemp;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			kG[i*lWidth + j] = 0;
		}
	for (int i = 1;i < lHeight - 1;i++)
		for (int j = 1;j < lWidth - 1;j++)
		{
			temp[0][0] = image.at<Vec3b>(i - 1, j - 1)[2];
			temp[0][1] = image.at<Vec3b>(i - 1, j)[2];
			temp[0][2] = image.at<Vec3b>(i - 1, j + 1)[2];
			temp[1][0] = image.at<Vec3b>(i, j - 1)[2];
			temp[1][1] = image.at<Vec3b>(i, j)[2];
			temp[1][2] = image.at<Vec3b>(i, j + 1)[2];
			temp[2][0] = image.at<Vec3b>(i + 1, j - 1)[2];
			temp[2][1] = image.at<Vec3b>(i + 1, j)[2];
			temp[2][2] = image.at<Vec3b>(i + 1, j + 1)[2];
			for (int p = 0;p < 3;p++)
				for (int t = 0;t < 3;t++)
				{
					x = x + temp[p][t] * vertical[p][t];
					y = y + temp[p][t] * level[p][t];
				}
			x = x * 0.25;
			y = y * 0.25;
			kGtemp = sqrt(x * x + y * y) + 0.5;
			if (kGtemp > 255)
			{
				kGtemp = 255;
			}
			kG[i*lWidth + j] = kGtemp;
		}
}

void COpencvMFCView::CannyMat(double sig, double rl, double rh)
{
	int x;
	int y;
	LONG lHeight;
	LONG lWidth;
	Mat Image2 = rawImage2.clone();
	lWidth = Image2.cols; //图像宽
	lHeight = Image2.rows; //图像高
	//double *kG; //指向梯度数据的指针
	//kG = new double[lWidth*lHeight];
	if (Image2.channels() == 1)
	{
		Mat Imagetrans1;
		Mat Imagetrans2;
		Imagetrans1.create(lHeight, lWidth, Image2.type());
		Imagetrans1 = Image2.clone();
		Imagetrans2.create(lHeight, lWidth, Image2.type());
		Canny(Imagetrans1, Imagetrans2, sig, rl, rh);
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				Image2.at<uchar>(i, j) = 255 - Imagetrans2.at<uchar>(i, j);
			}
	}
	else if (Image2.channels() == 3)
	{
		Mat HImage;
		HImage.create(lHeight, lWidth, Image2.type());
		double **s;
		double **H;
		s = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			s[i] = new double[lWidth];
		}
		H = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			H[i] = new double[lWidth];
		}
		for (int j = 0;j < lHeight;j++)
			for (int i = 0;i < lWidth;i++)
			{
				float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
				float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
				float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
				float num1 = 0.5*((r - g) + (r - b));
				float num2 = (r - g)*(r - g) + (r - b)*(g - b);
				float d = sqrt(num2);
				float d1 = num1 / d;
				double ang = acos(d1);
				double I = (r + g + b) / 3.0;
				BYTE Ii = I * 255;
				double min;
				min = r > g ? g : r;
				min = min > b ? b : min;
				H[j][i] = (g >= b) ? ang : 2 * pi - ang;
				H[j][i] = H[j][i] / (2 * pi);
				s[j][i] = 1 - (3.0*min) / (r + g + b);
				HImage.at<Vec3b>(j, i)[2] = Ii;
				HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
				HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
			}
		Mat achannels[3];
		split(HImage, achannels);
		Mat Imagetrans1;
		Mat Imagetrans2;
		Imagetrans1.create(lHeight, lWidth, achannels[2].type());
		Imagetrans1 = achannels[2].clone();
		Imagetrans2.create(lHeight, lWidth, achannels[2].type());
		Canny(Imagetrans1, Imagetrans2, sig, rl, rh);
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				achannels[2].at<uchar>(i, j) = 255 - Imagetrans2.at<uchar>(i, j);
				if (achannels[2].at<uchar>(i, j) == 0)
				{
					Image2.at<Vec3b>(i, j)[2] = 255;
					Image2.at<Vec3b>(i, j)[1] = 0;
					Image2.at<Vec3b>(i, j)[0] = 0;
				}
			}

	}
	/*delete kG;
	kG = NULL;*/
	CImage cimage;
	CDC *pDC = GetDC();
	MatToCimage(Image2, cimage);
	cimage.Draw(pDC->GetSafeHdc(), cimage.GetWidth() + 20, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());
}

void COpencvMFCView::Canny(Mat image1, Mat image2, double sig, double rl, double rh)
{
	Mat image3;
	LONG lHeight;
	LONG lWidth;
	lHeight = image1.rows;
	lWidth = image1.cols;
	image3.create(lHeight, lWidth, image1.type());
	int *kGx;
	int *kGy;
	int *GradM; //梯度的幅度
	kGx = new int[lWidth*lHeight];
	kGy = new int[lWidth*lHeight];
	GradM = new int[lWidth*lHeight];
	GaussianSmooth(image1, image3, sig); //原图像进行滤波
	DirGrad(image3, kGx, kGy); //方向导数
	GradMagnitude(kGx, kGy, lWidth, lHeight, GradM);
	NonmaxSuppress(GradM, kGx, kGy, image2);
	Hysteresis(GradM, rl, rh, image2);
	delete kGx;
	kGx = NULL;
	delete kGy;
	kGy = NULL;
	delete GradM;
	GradM = NULL;
}

void COpencvMFCView::GaussianSmooth(Mat image1, Mat image3, double sigma)
{
	LONG lWidth = image1.cols;
	LONG lHeight = image1.rows;
	int windowsize;
	int halflen;
	double *pdKernel; //一维高斯数据滤波器
	double dotMul; //高斯滤波系数的总和
	double weightsum; //高斯滤波系数总和
	double *temp;
	temp = new double[lWidth*lHeight];
	MakeGauss(sigma, &pdKernel, &windowsize);
	halflen = windowsize / 2;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			dotMul = 0;
			weightsum = 0;
			for (int p = -halflen;p <= halflen;p++)
			{
				if ((p + j) >= 0 && (p + j) < lWidth)
				{
					dotMul = dotMul + (double)image1.at<uchar>(i, p + j);
					weightsum = weightsum + pdKernel[halflen + p];
				}
			}
			temp[i*lWidth + j] = dotMul / weightsum;
		}
	for (int j = 0;j < lWidth;j++)
		for (int i = 0;i < lHeight;i++)
		{
			dotMul = 0;
			weightsum = 0;
			for (int p = -halflen;p <= halflen;p++)
			{
				if ((p + i) >= 0 && (p + i) < lHeight)
				{
					dotMul = dotMul + (double)temp[(i + p)*lWidth + j] * pdKernel[halflen + p];
					weightsum = weightsum + pdKernel[halflen + p];
				}
			}
			image3.at<uchar>(i, j) = dotMul / weightsum;
		}
	delete[]pdKernel;
	pdKernel = NULL;
	delete[]temp;
	temp = NULL;
}

void COpencvMFCView::MakeGauss(double sigma, double **pdKernel, int * windowSize)
{
	int i;
	int center;
	double d; //数组某一点到中心点的距离
	double value;
	double sum = 0;
	*windowSize = 1 + 2 * ceil(3 * sigma);
	center = (*windowSize) / 2;
	*pdKernel = new double[*windowSize];
	for (i = 0;i < (*windowSize);i++)
	{
		d = (double)(i - center);
		value = exp(-0.5*d*d / (sigma*sigma)) / (sqrt(2 * pi)*sigma);
		(*pdKernel)[i] = value;
		sum = sum + value;
	}
	for (i = 0;i < (*windowSize);i++)
	{
		(*pdKernel)[i] = (*pdKernel)[i] / sum;
	}
}

void COpencvMFCView::DirGrad(Mat image3, int * kGx, int * kGy)
{
	LONG lWidth;
	LONG lHeight;
	lWidth = image3.cols;
	lHeight = image3.rows;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			int x1 = lWidth - 1 < (j + 1) ? lWidth - 1 : j + 1;
			int x2 = 0 > j - 1 ? 0 : j - 1;
			kGx[i*lWidth + j] = (int)(image3.at<uchar>(i, x1) - image3.at<uchar>(i, x2));
		}
	for (int j = 0;j < lWidth;j++)
		for (int i = 0;i < lHeight;i++)
		{
			int y1 = lHeight - 1 < (i + 1) ? lHeight - 1 : i + 1;
			int y2 = 0 > (i - 1) ? 0 : (i - 1);
			kGy[i*lWidth + j] = (int)(image3.at<uchar>(y1, j) - image3.at<uchar>(y2, j));
		}
}

void COpencvMFCView::GradMagnitude(int * kGx, int * kGy, int lWidth, int lHeight, int * GradM)
{
	double temp1;
	double temp2;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			temp1 = kGx[i*lWidth + j] * kGx[i*lWidth + j];
			temp2 = kGy[i*lWidth + j] * kGy[i*lWidth + j];
			GradM[i*lWidth + j] = (int)(sqrt(temp1 + temp2) + 0.5);
		}
}

void COpencvMFCView::NonmaxSuppress(int * GradM, int * kGx, int * kGy, Mat image2)
{
	LONG lWidth = image2.cols;
	LONG lHeight = image2.rows;

	int nPos;

	// x方向梯度分量
	int gx;
	int gy;

	// 临时变量
	int g1, g2, g3, g4;
	double weight;
	double dTmp1;
	double dTmp2;
	double dTmp;

	// 设置图象边缘部分为不可能的边界点
	for (int i = 0; i < lWidth; i++)
	{
		image2.at<uchar>(0, i) = 0;
		image2.at<uchar>(lHeight - 1, i) = 0;
	}
	for (int j = 0; j < lHeight; j++)
	{
		image2.at<uchar>(j, 0) = 0;
		image2.at<uchar>(j, lWidth - 1) = 0;
	}

	for (int j = 1; j < lHeight - 1; j++)
	{
		for (int i = 1; i < lWidth - 1; i++)
		{
			nPos = j * lWidth + i;

			// 如果当前象素的梯度幅度为0，则不是边界点
			if (GradM[nPos] == 0)
			{
				image2.at<uchar>(j, i) = 0;
			}
			else
			{
				// 当前象素的梯度幅度
				dTmp = GradM[nPos];

				// x，y方向导数
				gx = kGx[nPos];
				gy = kGy[nPos];

				// 如果方向导数y分量比x分量大，说明导数的方向更加“趋向”于y分量。
				if (abs(gy) > abs(gx))
				{
					// 计算插值的比例
					weight = fabs(gx) / fabs(gy);

					g2 = GradM[nPos - lWidth];
					g4 = GradM[nPos + lWidth];

					// 如果x，y两个方向的方向导数的符号相同
					// C是当前象素，与g1-g4的位置关系为：
					//	g1 g2 
					//		 C         
					//		 g4 g3 
					if (gx*gy > 0)
					{
						g1 = GradM[nPos - lWidth - 1];
						g3 = GradM[nPos + lWidth + 1];
					}

					// 如果x，y两个方向的方向导数的符号相反
					// C是当前象素，与g1-g4的位置关系为：
					//	   g2 g1
					//		 C         
					//	g3 g4  
					else
					{
						g1 = GradM[nPos - lWidth + 1];
						g3 = GradM[nPos + lWidth - 1];
					}
				}

				// 如果方向导数x分量比y分量大，说明导数的方向更加“趋向”于x分量
				// 这个判断语句包含了x分量和y分量相等的情况
				else
				{
					// 计算插值的比例
					weight = fabs(gy) / fabs(gx);

					g2 = GradM[nPos + 1];
					g4 = GradM[nPos - 1];

					// 如果x，y两个方向的方向导数的符号相同
					// C是当前象素，与g1-g4的位置关系为：
					//	g3   
					//	g4 C g2       
					//       g1
					if (gx*gy > 0)
					{
						g1 = GradM[nPos + lWidth + 1];
						g3 = GradM[nPos - lWidth - 1];
					}
					// 如果x，y两个方向的方向导数的符号相反
					// C是当前象素，与g1-g4的位置关系为：
					//	     g1
					//	g4 C g2       
					//  g3     
					else
					{
						g1 = GradM[nPos - lWidth + 1];
						g3 = GradM[nPos + lWidth - 1];
					}
				}

				// 下面利用g1-g4对梯度进行插值
				{
					dTmp1 = weight * g1 + (1 - weight)*g2;
					dTmp2 = weight * g3 + (1 - weight)*g4;

					// 当前象素的梯度是局部的最大值
					// 该点可能是个边界点
					if (dTmp >= dTmp1 && dTmp >= dTmp2)
					{
						image2.at<uchar>(j, i) = 128;
					}
					else
					{
						// 不可能是边界点
						image2.at<uchar>(j, i) = 0;
					}
				}
			} //else
		} // for

	}
}

void COpencvMFCView::Hysteresis(int * GradM, double rl, double rh, Mat image2)
{
	int y;
	int x;
	LONG lWidth = image2.cols;
	LONG lHeight = image2.rows;
	int nThdHigh;
	int nThdLow;

	int nPos;

	// 估计TraceEdge需要的低阈值，以及Hysteresis函数使用的高阈值
	EstimateThreshold(GradM, &nThdHigh, &nThdLow, image2, rh, rl);

	// 这个循环用来寻找大于nThdHigh的点，这些点被用来当作边界点，然后用
	  // TraceEdge函数来跟踪该点对应的边界
	for (int i = 0; i < lHeight; i++)
	{
		for (int j = 0; j < lWidth; j++)
		{
			nPos = i * lWidth + j;

			// 如果该象素是可能的边界点，并且梯度大于高阈值，该象素作为
			// 一个边界的起点
			if ((image2.at<uchar>(i, j) == 128) && (GradM[nPos] >= nThdHigh))
			{
				// 设置该点为边界点
				image2.at<uchar>(i, j) = 255;
				TraceEdge(i, j, nThdLow, image2, GradM, lWidth);
			}
		}
	}

	// 那些还没有被设置为边界点的象素已经不可能成为边界点
	for (y = 0; y < lHeight; y++)
	{
		for (x = 0; x < lWidth; x++)
		{
			nPos = y * lWidth + x;
			if (image2.at<uchar>(y, x) != 255)
			{
				// 设置为非边界点
				image2.at<uchar>(y, x) = 0;
			}
		}
	}
}

void COpencvMFCView::EstimateThreshold(int * GradM, int * pnThdHigh, int * pnThdLow, Mat image2, double rh, double rl)
{
	int y;
	int x;
	int k;
	LONG lHeight = image2.rows;
	LONG lWidth = image2.cols;
	// 该数组的大小和梯度值的范围有关，如果采用本程序的算法，那么梯度的范围不会超过pow(2,10)
	int nHist[1024];

	// 可能的边界数目
	int nEdgeNb;

	// 最大梯度值
	int nMaxMag;

	int nHighCount;

	nMaxMag = 0;

	// 初始化
	for (k = 0; k < 1024; k++)
	{
		nHist[k] = 0;
	}

	// 统计直方图，然后利用直方图计算阈值
	for (y = 0; y < lHeight; y++)
	{
		for (x = 0; x < lWidth; x++)
		{
			// 只是统计那些可能是边界点，并且还没有处理过的象素
			if (image2.at<uchar>(y, x) == 128)
			{
				nHist[GradM[y*lWidth + x]]++;
			}
		}
	}

	nEdgeNb = nHist[0];
	nMaxMag = 0;
	// 统计经过“非最大值抑止(non-maximum suppression)”后有多少象素
	for (k = 1; k < 1024; k++)
	{
		if (nHist[k] != 0)
		{
			// 最大梯度值
			nMaxMag = k;
		}

		// 梯度为0的点是不可能为边界点的
		// 经过non-maximum suppression后有多少象素
		nEdgeNb += nHist[k];
	}

	// 梯度比高阈值*pnThdHigh小的象素点总数目
	nHighCount = (int)(rh * nEdgeNb + 0.5);

	k = 1;
	nEdgeNb = nHist[1];

	// 计算高阈值
	while ((k < (nMaxMag - 1)) && (nEdgeNb < nHighCount))
	{
		k++;
		nEdgeNb += nHist[k];
	}

	// 设置高阈值
	*pnThdHigh = k;

	// 设置低阈值
	*pnThdLow = (int)((*pnThdHigh) * rl + 0.5);
}

void COpencvMFCView::TraceEdge(int y, int x, int nLowThd, Mat image2, int * pnMag, int nWidth)
{
	// 对8邻域象素进行查询
	int xNb[8] = { 1, 1, 0,-1,-1,-1, 0, 1 };
	int yNb[8] = { 0, 1, 1, 1,0 ,-1,-1,-1 };

	int yy;
	int xx;

	int k;

	for (k = 0; k < 8; k++)
	{
		yy = y + yNb[k];
		xx = x + xNb[k];
		// 如果该象素为可能的边界点，又没有处理过
		// 并且梯度大于阈值
		if (image2.at<uchar>(yy, xx) == 128 && pnMag[yy*nWidth + xx] >= nLowThd)
		{
			// 把该点设置成为边界点
			image2.at<uchar>(yy, xx) = 255;

			// 以该点为中心进行跟踪
			TraceEdge(yy, xx, nLowThd, image2, pnMag, nWidth);
		}
	}
}


void COpencvMFCView::Laplacian(Mat image, double * kG)
{
	LONG lWidth;
	LONG lHeight;
	int vertical[3][3];
	vertical[0][0] = -1;vertical[0][1] = -1;vertical[0][2] = -1;
	vertical[1][0] = -1;vertical[1][1] = 8;vertical[1][2] = -1;
	vertical[2][0] = -1;vertical[2][1] = -1;vertical[2][2] = -1;
	lWidth = image.cols;
	lHeight = image.rows;
	double temp[3][3];
	double kGtemp;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			kG[i*lWidth + j] = 0;
		}
	for (int i = 1;i < lHeight - 1;i++)
		for (int j = 1;j < lWidth - 1;j++)
		{
			kGtemp = 0;
			temp[0][0] = image.at<uchar>(i - 1, j - 1);
			temp[0][1] = image.at<uchar>(i - 1, j);
			temp[0][2] = image.at<uchar>(i - 1, j + 1);
			temp[1][0] = image.at<uchar>(i, j - 1);
			temp[1][1] = image.at<uchar>(i, j);
			temp[1][2] = image.at<uchar>(i, j + 1);
			temp[2][0] = image.at<uchar>(i + 1, j - 1);
			temp[2][1] = image.at<uchar>(i + 1, j);
			temp[2][2] = image.at<uchar>(i + 1, j + 1);
			for (int p = 0;p < 3;p++)
				for (int t = 0;t < 3;t++)
				{
					kGtemp = kGtemp + temp[p][t] * vertical[p][t];
				}
			if (kGtemp > 255)
			{
				kGtemp = 255;
			}
			kG[i*lWidth + j] = kGtemp;
		}
}

void COpencvMFCView::LaplacianMat(int T)
{
	int x;
	int y;
	LONG lHeight;
	LONG lWidth;
	Mat Image2 = rawImage2.clone();
	lWidth = Image2.cols; //图像宽
	lHeight = Image2.rows; //图像高
	double *kG; //指向梯度数据的指针
	kG = new double[lWidth*lHeight];
	if (Image2.channels() == 1)
	{
		Laplacian(Image2, kG);
		//设置阈值进行二值化 
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				if (kG[i*lWidth + j] > T)
				{
					Image2.at<uchar>(i, j) = 0;
				}
				else
				{
					Image2.at<uchar>(i, j) = 255;
				}
			}
	}
	else if (Image2.channels() == 3)
	{
		Mat HImage;
		HImage.create(lHeight, lWidth, Image2.type());
		double **s;
		double **H;
		s = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			s[i] = new double[lWidth];
		}
		H = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			H[i] = new double[lWidth];
		}
		for (int j = 0;j < lHeight;j++)
			for (int i = 0;i < lWidth;i++)
			{
				float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
				float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
				float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
				float num1 = 0.5*((r - g) + (r - b));
				float num2 = (r - g)*(r - g) + (r - b)*(g - b);
				float d = sqrt(num2);
				float d1 = num1 / d;
				double ang = acos(d1);
				double I = (r + g + b) / 3.0;
				BYTE Ii = I * 255;
				double min;
				min = r > g ? g : r;
				min = min > b ? b : min;
				H[j][i] = (g >= b) ? ang : 2 * pi - ang;
				H[j][i] = H[j][i] / (2 * pi);
				s[j][i] = 1 - (3.0*min) / (r + g + b);
				HImage.at<Vec3b>(j, i)[2] = Ii;
				HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
				HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
			}
		LaplacianColor(HImage, kG);
		//设置阈值进行二值化 
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				if (Laplacianflag == 1)
				{
					if (kG[i*lWidth + j] > T)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 0;
					}
					else
					{
						Image2.at<Vec3b>(i, j)[0] = 255;
						Image2.at<Vec3b>(i, j)[1] = 255;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}
				else
				{
					if (kG[i*lWidth + j] > T)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}
			}
	}
	delete kG;
	kG = NULL;
	CImage cimage;
	CDC *pDC = GetDC();
	MatToCimage(Image2, cimage);
	cimage.Draw(pDC->GetSafeHdc(), cimage.GetWidth() + 20, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());
	myImage = Image2.clone();
}

void COpencvMFCView::LaplacianColor(Mat image, double * kG)
{
	LONG lWidth;
	LONG lHeight;
	int vertical[3][3];
	vertical[0][0] = -1;vertical[0][1] = -1;vertical[0][2] = -1;
	vertical[1][0] = -1;vertical[1][1] = 8;vertical[1][2] = -1;
	vertical[2][0] = -1;vertical[2][1] = -1;vertical[2][2] = -1;
	lWidth = image.cols;
	lHeight = image.rows;
	double temp[3][3];
	double kGtemp;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			kG[i*lWidth + j] = 0;
		}
	for (int i = 1;i < lHeight - 1;i++)
		for (int j = 1;j < lWidth - 1;j++)
		{
			kGtemp = 0;
			temp[0][0] = image.at<Vec3b>(i - 1, j - 1)[2];
			temp[0][1] = image.at<Vec3b>(i - 1, j)[2];
			temp[0][2] = image.at<Vec3b>(i - 1, j + 1)[2];
			temp[1][0] = image.at<Vec3b>(i, j - 1)[2];
			temp[1][1] = image.at<Vec3b>(i, j)[2];
			temp[1][2] = image.at<Vec3b>(i, j + 1)[2];
			temp[2][0] = image.at<Vec3b>(i + 1, j - 1)[2];
			temp[2][1] = image.at<Vec3b>(i + 1, j)[2];
			temp[2][2] = image.at<Vec3b>(i + 1, j + 1)[2];
			for (int p = 0;p < 3;p++)
				for (int t = 0;t < 3;t++)
				{
					kGtemp = kGtemp + temp[p][t] * vertical[p][t];
				}
			if (kGtemp > 255)
			{
				kGtemp = 255;
			}
			kG[i*lWidth + j] = kGtemp;
		}
}

void COpencvMFCView::PriwittMat(int T)
{
	int x;
	int y;
	LONG lHeight;
	LONG lWidth;
	Mat Image2 = rawImage2.clone();
	lWidth = Image2.cols; //图像宽
	lHeight = Image2.rows; //图像高
	double *kG; //指向梯度数据的指针
	kG = new double[lWidth*lHeight];
	if (Image2.channels() == 1)
	{
		Priwitt(Image2, kG);
		//设置阈值进行二值化 
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				if (kG[i*lWidth + j] > T)
				{
					Image2.at<uchar>(i, j) = 0;
				}
				else
				{
					Image2.at<uchar>(i, j) = 255;
				}
			}
	}
	else if (Image2.channels() == 3)
	{
		Mat HImage;
		HImage.create(lHeight, lWidth, Image2.type());
		double **s;
		double **H;
		s = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			s[i] = new double[lWidth];
		}
		H = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			H[i] = new double[lWidth];
		}
		for (int j = 0;j < lHeight;j++)
			for (int i = 0;i < lWidth;i++)
			{
				float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
				float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
				float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
				float num1 = 0.5*((r - g) + (r - b));
				float num2 = (r - g)*(r - g) + (r - b)*(g - b);
				float d = sqrt(num2);
				float d1 = num1 / d;
				double ang = acos(d1);
				double I = (r + g + b) / 3.0;
				BYTE Ii = I * 255;
				double min;
				min = r > g ? g : r;
				min = min > b ? b : min;
				H[j][i] = (g >= b) ? ang : 2 * pi - ang;
				H[j][i] = H[j][i] / (2 * pi);
				s[j][i] = 1 - (3.0*min) / (r + g + b);
				HImage.at<Vec3b>(j, i)[2] = Ii;
				HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
				HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
			}
		PriwittColor(HImage, kG);
		//设置阈值进行二值化 
		for (int i = 0;i < lHeight;i++)
			for (int j = 0;j < lWidth;j++)
			{
				if (priwittflag == 1)
				{
					if (kG[i*lWidth + j] > T)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 0;
					}
					else
					{
						Image2.at<Vec3b>(i, j)[0] = 255;
						Image2.at<Vec3b>(i, j)[1] = 255;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}
				else
				{
					if (kG[i*lWidth + j] > T)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}
			}
	}
	delete kG;
	kG = NULL;
	CImage cimage;
	CDC *pDC = GetDC();
	MatToCimage(Image2, cimage);
	cimage.Draw(pDC->GetSafeHdc(), cimage.GetWidth() + 20, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());
	myImage = Image2.clone();
}

void COpencvMFCView::Priwitt(Mat image, double * kG)
{
	double x = 0;
	double y = 0;
	LONG lWidth;
	LONG lHeight;
	int vertical[3][3];
	int level[3][3];
	vertical[0][0] = 1;vertical[0][1] = 1;vertical[0][2] = 1;
	vertical[1][0] = 0;vertical[1][1] = 0;vertical[1][2] = 0;
	vertical[2][0] = -1;vertical[2][1] = -1;vertical[2][2] = -1;

	level[0][0] = -1;level[0][1] = 0;level[0][2] = 1;
	level[1][0] = -1;level[1][1] = 0;level[1][2] = 1;
	level[2][0] = -1;level[2][1] = 0;level[2][2] = 1;
	lWidth = image.cols;
	lHeight = image.rows;
	double temp[3][3];
	double kGtemp;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			kG[i*lWidth + j] = 0;
		}
	for (int i = 1;i < lHeight - 1;i++)
		for (int j = 1;j < lWidth - 1;j++)
		{
			temp[0][0] = image.at<uchar>(i - 1, j - 1);
			temp[0][1] = image.at<uchar>(i - 1, j);
			temp[0][2] = image.at<uchar>(i - 1, j + 1);
			temp[1][0] = image.at<uchar>(i, j - 1);
			temp[1][1] = image.at<uchar>(i, j);
			temp[1][2] = image.at<uchar>(i, j + 1);
			temp[2][0] = image.at<uchar>(i + 1, j - 1);
			temp[2][1] = image.at<uchar>(i + 1, j);
			temp[2][2] = image.at<uchar>(i + 1, j + 1);

			for (int p = 0;p < 3;p++)
				for (int t = 0;t < 3;t++)
				{
					x = x + temp[p][t] * vertical[p][t];
					y = y + temp[p][t] * level[p][t];
				}
			x = x * (1.0 / 3.0);
			y = y * (1.0 / 3.0);
			kGtemp = sqrt(x * x + y * y) + 0.5;
			if (kGtemp > 255)
			{
				kGtemp = 255;
			}
			kG[i*lWidth + j] = kGtemp;
		}
}

void COpencvMFCView::PriwittColor(Mat image, double * kG)
{
	double x = 0;
	double y = 0;
	LONG lWidth;
	LONG lHeight;
	int vertical[3][3];
	int level[3][3];
	vertical[0][0] = 1;vertical[0][1] = 1;vertical[0][2] = 1;
	vertical[1][0] = 0;vertical[1][1] = 0;vertical[1][2] = 0;
	vertical[2][0] = -1;vertical[2][1] = -1;vertical[2][2] = -1;

	level[0][0] = -1;level[0][1] = 0;level[0][2] = 1;
	level[1][0] = -1;level[1][1] = 0;level[1][2] = 1;
	level[2][0] = -1;level[2][1] = 0;level[2][2] = 1;
	lWidth = image.cols;
	lHeight = image.rows;
	double temp[3][3];
	double kGtemp;
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			kG[i*lWidth + j] = 0;
		}
	for (int i = 1;i < lHeight - 1;i++)
		for (int j = 1;j < lWidth - 1;j++)
		{
			temp[0][0] = image.at<Vec3b>(i - 1, j - 1)[2];
			temp[0][1] = image.at<Vec3b>(i - 1, j)[2];
			temp[0][2] = image.at<Vec3b>(i - 1, j + 1)[2];
			temp[1][0] = image.at<Vec3b>(i, j - 1)[2];
			temp[1][1] = image.at<Vec3b>(i, j)[2];
			temp[1][2] = image.at<Vec3b>(i, j + 1)[2];
			temp[2][0] = image.at<Vec3b>(i + 1, j - 1)[2];
			temp[2][1] = image.at<Vec3b>(i + 1, j)[2];
			temp[2][2] = image.at<Vec3b>(i + 1, j + 1)[2];

			for (int p = 0;p < 3;p++)
				for (int t = 0;t < 3;t++)
				{
					x = x + temp[p][t] * vertical[p][t];
					y = y + temp[p][t] * level[p][t];
				}
			x = x * (1.0 / 3.0);
			y = y * (1.0 / 3.0);
			kGtemp = sqrt(x * x + y * y) + 0.5;
			if (kGtemp > 255)
			{
				kGtemp = 255;
			}
			kG[i*lWidth + j] = kGtemp;
		}
}

Mat COpencvMFCView::regionGrow(Mat image, CPoint p, int T)
{
	//cvtColor(image, image, COLOR_RGB2GRAY);
	int taggrow = 255;
	int startvalue = 255;
	int curvalue = 255;
	long lHeight = image.rows;
	long lWidth = image.cols;
	Mat image2;
	image2.create(lHeight, lWidth, CV_8UC1);
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			image2.at<uchar>(i, j) = 255;
		}
	CPoint pg;
	vector<CPoint> pointvc;
	pointvc.push_back(p);
	image2.at<uchar>(p.y, p.x) = 0;
	startvalue = image.at<uchar>(p.y, p.x);
	int temp[8][2];
	temp[0][0] = -1;temp[0][1] = 0;
	temp[1][0] = 0;temp[1][1] = -1;
	temp[2][0] = 0;temp[2][1] = 1;
	temp[3][0] = 1;temp[3][1] = 0;
	temp[4][0] = 1;temp[4][1] = 1;
	temp[5][0] = -1;temp[5][1] = -1;
	temp[6][0] = -1;temp[6][1] = 1;
	temp[7][0] = 1;temp[7][1] = -1;
	while (!pointvc.empty())
	{
		p = pointvc.back();
		pointvc.pop_back();
		for (int i = 0;i < 8;i++)
		{
			pg.x = p.x + temp[i][0];
			pg.y = p.y + temp[i][1];
			if (pg.y<0 || pg.x<0 || pg.x>lWidth - 1 || pg.y>lHeight - 1)
			{
				continue;
			}
			taggrow = image2.at<uchar>(pg.y, pg.x);
			if (taggrow == 255)
			{
				curvalue = image.at<uchar>(pg.y, pg.x);
				if (abs(startvalue - curvalue) < T)
				{
					image2.at<uchar>(pg.y, pg.x) = 0;
					pointvc.push_back(pg);
				}
			}
		}
	}
	/*image = image2.clone();*/
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			if (image2.at<uchar>(i, j) == 0)
			{
				image.at<uchar>(i, j) = 0;
			}
		}
	return image;
}

Mat COpencvMFCView::regionGrowcolor(Mat image, CPoint p, int T)
{
	int taggrow = 255;
	int startvalue = 255;
	int curvalue = 255;
	long lHeight = image.rows;
	long lWidth = image.cols;
	Mat image2;
	image2.create(lHeight, lWidth, image.type());
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			image2.at<Vec3b>(i, j)[2] = 255;
		}
	CPoint pg;
	vector<CPoint> pointvc;
	pointvc.push_back(p);
	image2.at<Vec3b>(p.y, p.x)[2] = 0;
	startvalue = image.at<Vec3b>(p.y, p.x)[2];
	int temp[8][2];
	temp[0][0] = -1;temp[0][1] = 0;
	temp[1][0] = 0;temp[1][1] = -1;
	temp[2][0] = 0;temp[2][1] = 1;
	temp[3][0] = 1;temp[3][1] = 0;
	temp[4][0] = 1;temp[4][1] = 1;
	temp[5][0] = -1;temp[5][1] = -1;
	temp[6][0] = -1;temp[6][1] = 1;
	temp[7][0] = 1;temp[7][1] = -1;
	while (!pointvc.empty())
	{
		p = pointvc.back();
		pointvc.pop_back();
		for (int i = 0;i < 8;i++)
		{
			pg.x = p.x + temp[i][0];
			pg.y = p.y + temp[i][1];
			if (pg.y<0 || pg.x<0 || pg.x>lWidth - 1 || pg.y>lHeight - 1)
			{
				continue;
			}
			taggrow = image2.at<Vec3b>(pg.y, pg.x)[2];
			if (taggrow == 255)
			{
				curvalue = image.at<Vec3b>(pg.y, pg.x)[2];
				if (abs(startvalue - curvalue) < T)
				{
					image2.at<Vec3b>(pg.y, pg.x)[2] = 0;
					pointvc.push_back(pg);
				}
			}
		}
	}
	/*image = image2.clone();*/
	for (int i = 0;i < lHeight;i++)
		for (int j = 0;j < lWidth;j++)
		{
			if (image2.at<Vec3b>(i, j)[2] == 0)
			{
				image.at<Vec3b>(i, j)[2] = 0;
			}
		}
	return image;
	//return Mat();
}



void COpencvMFCView::Walshei_Har(double * pTd, double * pFd, int power)  //沃尔什变换
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
	CScrollView::AssertValid();
}

void COpencvMFCView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

COpencvMFCDoc* COpencvMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpencvMFCDoc)));
	return (COpencvMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COpencvMFCView 消息处理程序


void COpencvMFCView::OnFourier() //傅里叶变换
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	myImage2 = rawImage2.clone();
	if (myImage2.channels() == 1)
	{
		ForierMat(myImage2);
		myImage = myImage2.clone();
		CImage cimage;
		MatToCimage(myImage2, cimage); //将Mat类转化为CImage类用作显示，该函数的定义在Image.cpp中
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
	else if (myImage2.channels() == 3)
	{
		Mat aChannels[3];
		//利用数组分离
		split(myImage2, aChannels);
		ForierMatRGB(aChannels[0], 1);
		ForierMatRGB(aChannels[1], 2);
		ForierMatRGB(aChannels[2], 3);
		merge(aChannels, 3, myImage2);
		myImage = myImage2.clone();
		CImage cimage;
		MatToCimage(myImage2, cimage); //将Mat类转化为CImage类用作显示，该函数的定义在Image.cpp中
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}

}



void COpencvMFCView::OnFouriertran()  //傅里叶逆变换
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	if (myImage2.channels() == 1)
	{
		InverseFourierMat(myImage2);       //逆转换
		myImage = myImage2.clone();
		CImage cimage;
		MatToCimage(myImage2, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
	else if (myImage2.channels() == 3)
	{
		Mat aChannels[3];
		//利用数组分离
		split(myImage2, aChannels);
		InverseFourierMatRGB(aChannels[0], pFdtB, pTdtB);
		InverseFourierMatRGB(aChannels[1], pFdtG, pTdtG);
		InverseFourierMatRGB(aChannels[2], pFdtR, pTdtR);
		merge(aChannels, 3, myImage2);
		myImage = myImage2.clone();
		CImage cimage;
		MatToCimage(myImage2, cimage); //将Mat类转化为CImage类用作显示，该函数的定义在Image.cpp中
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());

	}
}


void COpencvMFCView::OnDct() //离散余弦变换
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Image = rawImage2.clone();
	if (Image.channels() == 1)
	{
		DctMat(Image);
		myImage = Image.clone();
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
		myImage = Image.clone();
		CImage cimage;
		MatToCimage(Image, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
}


void COpencvMFCView::OnWal() //沃尔什变换
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2 = rawImage2.clone();
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
	if (Walsh_HarTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes))
	{
		myImage = Image2.clone();
		CImage cimage;
		MatToCimage(Image2, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
}


void COpencvMFCView::OnInversedct() //离散余弦逆变换
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	if (Image.channels() == 1)
	{
		InverDctMat(Image);
		myImage = Image.clone();
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
		myImage = Image.clone();
		CImage cimage;
		MatToCimage(Image, cimage); //将Mat类转化为CImage类用作显示
		CDC *pDC = GetDC();
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
}


void COpencvMFCView::OnLineartransform()  //线性增强
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CLineTransDialog dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnSeglinetransform() //分段线性增强
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CLineNum dlg1;
	if (dlg1.DoModal() == IDOK)
	{
		CLinePointset dlg2;
		dlg2.Linenum = dlg1.Linenum;
		dlg2.view = this;
		dlg2.DoModal();
	}

}


void COpencvMFCView::Onloglinetrans() //非线性增强 对数函数
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CLogLinedlg dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnHistogramequal()  //直方图均衡化
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2 = rawImage2.clone();
	long	lSrcWidth = Image2.cols;      //图像的宽度和高度
	long	lSrcHeight = Image2.rows;
	HistogramequalMat();
	CHistogramDialog dlg;
	memcpy(dlg.fPro, fPro, 256 * 4); //源图像分布概率
	memcpy(dlg.temp, temp, 256 * 4);  //累计直方图
	memcpy(dlg.fProT, fProT, 256 * 4); //均衡化后
	CString str1, str2, str3, strmid1, strmid2;
	str1.Format(_T("%d"), lSrcWidth * lSrcHeight);
	str2.Format(_T("%0.02f"), average1);
	str3.Format(_T("%0.02f"), average2);
	strmid1.Format(_T("%0.02f"), mid1);
	strmid2.Format(_T("%0.02f"), mid2);
	dlg.pixel1 = str1;
	dlg.pixel2 = str1;
	dlg.average1 = str2;
	dlg.average2 = str3;
	dlg.mid1 = strmid1;
	dlg.mid2 = strmid2;
	dlg.standard1.Format(_T("%0.02f"), stan1);
	dlg.Standard2.Format(_T("%0.02f"), stan2);
	dlg.DoModal();
	//myImage = Image2.clone();
}


void COpencvMFCView::OnAveragesmooth()  //均值滤波
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2 = rawImage2.clone();
	CDC *pDC = GetDC();
	CtemplateDialog dlg;
	int M;
	if (dlg.DoModal() == IDOK)
	{
		M = _ttoi(dlg.template1);
	}
	if (Image2.channels() == 1)
	{
		Average_Smooth(Image2, M);
	}
	else if (Image2.channels() == 3)
	{
		Mat achannels[3];
		split(Image2, achannels);
		Average_Smooth(achannels[0], M);
		Average_Smooth(achannels[1], M);
		Average_Smooth(achannels[2], M);
		merge(achannels, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());


}


void COpencvMFCView::OnSalt()  //添加椒盐噪声
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2 = rawImage2.clone();
	CSalt dlg;
	float n;
	if (dlg.DoModal() == IDOK)
	{
		n = 0.001*dlg.salt;
		SpicedSalt(Image2, n);
		myImage = Image2.clone();
		CImage cimage2;
		MatToCimage(Image2, cimage2);
		CDC *pDC = GetDC();
		cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
			0, 0, cimage2.GetWidth(), cimage2.GetHeight());
	}

}


void COpencvMFCView::OnGaosi()  //添加高斯噪声
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2 = rawImage2.clone();
	int k;
	CGaosi dlg;
	if (dlg.DoModal() == IDOK)
	{
		k = dlg.gaosi;
		GaosiNoise(Image2, 0, 1, k);
	}
}


void COpencvMFCView::OnGaosifiltering()   //高斯滤波
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	int n;  //模板大小
	CtemplateDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		n = _ttoi(dlg.template1);
	}
	double **structure; //模板二维数组
	structure = new double*[n];
	//structure = (double**)malloc(n * sizeof(int));
	for (int i = 0;i < n;i++)
	{
		structure[i] = new double[n];    //开辟动态二维数组structure
		//structure[i] = (double*)malloc(n * sizeof(int));
	}
	Image2.create(rawImage2.rows, rawImage2.cols, rawImage2.type());
	Image2 = rawImage2.clone();
	CreateGauss(structure, n);  //生成高斯模板
	int **structureint;
	structureint = new int*[n];
	for (int i = 0;i < n;i++)
	{
		structureint[i] = new int[n];    //开辟动态二维数组structure
		//structure[i] = (double*)malloc(n * sizeof(int));
	}
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
		{
			structureint[i][j] = (int)(structure[i][j]);
		}
	if (Image2.channels() == 1)
	{
		Value_Average_Smooth(Image2, structureint, n); //进行高斯平滑
	}
	else if (Image2.channels() == 3)
	{
		Mat achannels[3];
		split(Image2, achannels);
		Value_Average_Smooth(achannels[0], structureint, n); //进行高斯平滑
		Value_Average_Smooth(achannels[1], structureint, n); //进行高斯平滑
		Value_Average_Smooth(achannels[2], structureint, n); //进行高斯平滑
		merge(achannels, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());

}


void COpencvMFCView::OnMid()   //中值滤波
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2 = rawImage2.clone();
	int M;
	CtemplateDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		M = _ttoi(dlg.template1);
	}
	if (Image2.channels() == 1)
	{
		Middle_Smooth(Image2, M);
	}
	else if (Image2.channels() == 3)
	{
		Mat achannels[3];
		split(Image2, achannels);
		Middle_Smooth(achannels[0], M);
		Middle_Smooth(achannels[1], M);
		Middle_Smooth(achannels[2], M);
		merge(achannels, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}


void COpencvMFCView::OnPepper()     //添加胡椒噪声
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CSalt dlg;
	float n;
	if (dlg.DoModal() == IDOK)
	{
		n = 0.001*dlg.salt;
		Mat Image2;
		Image2 = rawImage2.clone();
		Pepper(Image2, n);
		myImage = Image2.clone();
		CImage cimage2;
		MatToCimage(Image2, cimage2);
		CDC *pDC = GetDC();
		cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
			0, 0, cimage2.GetWidth(), cimage2.GetHeight());
	}
}


void COpencvMFCView::Onwhitesalt()  //添加盐燥声
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CSalt dlg;
	float n;
	if (dlg.DoModal() == IDOK)
	{
		n = 0.001*dlg.salt;
		Mat Image2;
		Image2 = rawImage2.clone();
		WhiteSalt(Image2, n);
		myImage = Image2.clone();
		CImage cimage2;
		MatToCimage(Image2, cimage2);
		CDC *pDC = GetDC();
		cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
			0, 0, cimage2.GetWidth(), cimage2.GetHeight());
	}
}


void COpencvMFCView::OnHistogrammatch()   //直方图规定化
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2.create(rawImage2.rows, rawImage2.cols, rawImage2.type());
	Image2 = rawImage2.clone();  //原图

	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
	Mat FIleimage;    //模板图
	if (dlg.DoModal() == IDOK)
	{
		USES_CONVERSION;
		CString Cstr = dlg.GetPathName();
		cv::String str = W2A(Cstr);
		FIleimage = imread(str, -1); //rawImage读取到图像数据，-1表示按按解码方式读，可保留图像源格式	
	}
	if (FIleimage.empty())
	{
		MessageBox(_T("未获取到图像"));
	}
	CImage cimage2;
	CImage fileimage;
	MatToCimage(Image2, cimage2);
	MatToCimage(FIleimage, fileimage);
	CDC *pDC = GetDC();
	fileimage.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, fileimage.GetWidth(), fileimage.GetHeight(),
		0, 0, fileimage.GetWidth(), fileimage.GetHeight());
	pDC->TextOut(10 + cimage2.GetWidth(), fileimage.GetHeight() + 5, _T("模板图像"));
	int nu[256];  //规定直方图映射关系,这里规定直方图的灰度级为64
	float pu0[256]; //规定灰度分布概率
	float pu1[256];
	float pu2[256];
	if (FIleimage.channels() == 1)
	{
		Histogram_Statistic(FIleimage, pu0);
		memcpy(pu1, pu0, 256 * 4);
		memcpy(pu2, pu0, 256 * 4);
	}
	if (FIleimage.channels() == 3)
	{
		Mat channel[3];
		split(FIleimage, channel);
		Histogram_Statistic(channel[0], pu0);
		Histogram_Statistic(channel[1], pu1);
		Histogram_Statistic(channel[2], pu2);
		merge(channel, 3, FIleimage);
	}
	for (int i = 0;i < 256;i++)
	{
		nu[i] = i;
	}
	if (Image2.channels() == 3)
	{
		Mat channel[3];
		split(Image2, channel);
		Histogram_Match(channel[0], 256, nu, pu0);
		Histogram_Match(channel[1], 256, nu, pu1);
		Histogram_Match(channel[2], 256, nu, pu2);
		merge(channel, 3, Image2);
	}
	else if (Image2.channels() == 1)
	{
		Histogram_Match(Image2, 256, nu, pu0);
	}
	myImage = Image2.clone();
	CImage cimage3;
	MatToCimage(Image2, cimage3);
	cimage3.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5 + fileimage.GetWidth() + 5, 0, cimage3.GetWidth(), cimage3.GetHeight(),
		0, 0, cimage3.GetWidth(), cimage3.GetHeight());
	pDC->TextOut(20 + cimage2.GetWidth() + fileimage.GetWidth(), cimage3.GetHeight() + 5, _T("规定后图像"));
	CHistogmatchDIalog dlg1;
	memcpy(dlg1.fPro, fPro, 256 * 4); //源图像分布概率
	memcpy(dlg1.pu, pu0, 256 * 4);  //模板
	memcpy(dlg1.fProT, fProT, 256 * 4); //规定化后
	dlg1.DoModal();
}




void COpencvMFCView::OnInitialUpdate()  //滚动条
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 2000;
	SetScrollSizes(MM_TEXT, sizeTotal);
	CRect re;
	GetClientRect(&re);
	this->SetScrollPos(SB_HORZ, 0);
	this->SetScrollPos(SB_VERT, 0);

}


void COpencvMFCView::OnGategrad() //门限梯度锐化
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CGateGredDialog dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnLaplacian() //拉普拉斯锐化
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2.create(rawImage2.rows, rawImage2.cols, rawImage2.type());
	Image2 = rawImage2.clone();
	if (Image2.channels() == 1)
	{
		Laplacian(Image2);
	}
	else if (Image2.channels() == 3)
	{
		Mat channel[3];
		split(Image2, channel);
		Laplacian(channel[0]);
		Laplacian(channel[1]);
		Laplacian(channel[2]);
		merge(channel, 3, Image2);
	}
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}


void COpencvMFCView::OnPrefectlowfilter()  //理想低通滤波
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2.create(rawImage2.rows, rawImage2.cols, rawImage2.type());
	Image2 = rawImage2.clone();
	int u = 100;
	int v = 100;
	Perfect_Low_Filter(Image2, u, v);
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}


void COpencvMFCView::OnPrefecthighfilter()  //理想高通滤波
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2.create(rawImage2.rows, rawImage2.cols, rawImage2.type());
	Image2 = rawImage2.clone();
	int u = 100;
	int v = 100;
	Perfect_High_Filter(Image2, u, v);
	myImage = Image2.clone();
	CImage cimage2;
	MatToCimage(Image2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 20, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
}




void COpencvMFCView::OnGeometry() //图像几何变换
{
	CgeometryDialog dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnImageplus()  //图像融合
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2 = rawImage2.clone();  //原图
	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
	Mat FIleimage;    //融合图
	if (dlg.DoModal() == IDOK)
	{
		USES_CONVERSION;
		CString Cstr = dlg.GetPathName();
		cv::String str = W2A(Cstr);
		FIleimage = imread(str, -1); //rawImage读取到图像数据，-1表示按按解码方式读，可保留图像源格式	
	}
	if (FIleimage.empty())
	{
		MessageBox(_T("未获取到图像"));
	}
	CImage cimage2;
	CImage fileimage;
	MatToCimage(Image2, cimage2);
	MatToCimage(FIleimage, fileimage);
	CDC *pDC = GetDC();
	fileimage.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, fileimage.GetWidth(), fileimage.GetHeight(),
		0, 0, fileimage.GetWidth(), fileimage.GetHeight());
	CSplitimage dlg1;
	dlg1.view = this;
	dlg1.image1 = Image2.clone();
	dlg1.image2 = FIleimage.clone();
	dlg1.DoModal();
	//Imageplus(Image2, FIleimage, 1, 1, 0);
}


void COpencvMFCView::OnImagesub()  //图像分离
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2;
	Image2 = rawImage2.clone();  //原图
	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
	Mat FIleimage;    //融合图
	if (dlg.DoModal() == IDOK)
	{
		USES_CONVERSION;
		CString Cstr = dlg.GetPathName();
		cv::String str = W2A(Cstr);
		FIleimage = imread(str, -1); //rawImage读取到图像数据，-1表示按按解码方式读，可保留图像源格式	
	}
	if (FIleimage.empty())
	{
		MessageBox(_T("未获取到图像"));
	}
	CImage cimage2;
	CImage fileimage;
	MatToCimage(Image2, cimage2);
	MatToCimage(FIleimage, fileimage);
	CDC *pDC = GetDC();
	fileimage.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, fileimage.GetWidth(), fileimage.GetHeight(),
		0, 0, fileimage.GetWidth(), fileimage.GetHeight());
	ImagesubMat(Image2, FIleimage);
}


void COpencvMFCView::OnWater()  //实现水倒影
{
	Mat Image2 = rawImage2.clone();
	Mat Image3 = Image2.clone();
	Mat achannels[3];
	CImage cimage2;
	CImage cimage3;
	CDC *pDC = GetDC();
	Mat Waterimage = imread("水波纹.bmp", -1);
	int lHeight = Image3.rows;
	int lWidth = Image3.cols;
	Mat Zoomimage[3];
	Mat achannels11[3];
	Mat miximage[3];
	Mat Miximage;
	Mat achannels1[3];
	Mat achannels2[3];
	Mat Endimage;
	LPBYTE lpNewDIBBits;
	LPBYTE lpDIBBits1;
	LPBYTE lpDIBBits2;
	LPBYTE lpDst;
	LPBYTE lpSrc1;
	LPBYTE lpSrc2;
	Mat Waterimage2;
	for (int i = 0;i < 3;i++)
	{
		Zoomimage[i].create(lHeight, lWidth, CV_8UC1);  //创建一个新图像
	}
	split(Waterimage, achannels11);
	Zoom(achannels11[0], Zoomimage[0], lWidth, lHeight); //缩放水波纹图像为背景图像大小
	Zoom(achannels11[1], Zoomimage[1], lWidth, lHeight);
	Zoom(achannels11[2], Zoomimage[2], lWidth, lHeight);
	merge(Zoomimage, 3, Waterimage2);
	MatToCimage(Image2, cimage2);
	int channel = 3;
	if (Image3.channels() == 3)
	{
		channel = 3;
		split(Image3, achannels);
		Convert(achannels[0]);//倒置
		Convert(achannels[1]);
		Convert(achannels[2]);
		merge(achannels, 3, Image3);
	}
	else
	{
		channel = 1;
		Convert(Image3);
	}
	MatToCimage(Image3, cimage3);
	cimage3.Draw(pDC->GetSafeHdc(), 0, cimage2.GetHeight() + 5, cimage3.GetWidth(), cimage3.GetHeight(),
		0, 0, cimage3.GetWidth(), cimage3.GetHeight());
	if (Image3.channels() == 3)
	{
		split(Image3, achannels);
		Middle_Smooth(achannels[0], 5);  //模糊
		Middle_Smooth(achannels[1], 5);
		Middle_Smooth(achannels[2], 5);
		merge(achannels, 3, Image3);
	}
	else
	{
		Middle_Smooth(Image3, 5);
	}
	MatToCimage(Image3, cimage3);
	cimage3.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, cimage3.GetWidth(), cimage3.GetHeight(),
		0, 0, cimage3.GetWidth(), cimage3.GetHeight());

	if (Image3.channels() == 3)
	{
		for (int i = 0;i < 3;i++)
		{
			miximage[i].create(lHeight, lWidth, CV_8UC1);
		}
		split(Image3, achannels1);
		split(Waterimage2, achannels2);
		Imageplus(achannels1[0], achannels2[0], miximage[0], 0.6, 0.4, 15, 0, 0); //叠加
		Imageplus(achannels1[1], achannels2[1], miximage[1], 0.6, 0.4, 15, 0, 0);
		Imageplus(achannels1[2], achannels2[2], miximage[2], 0.6, 0.4, 15, 0, 0);
		merge(miximage, 3, Miximage);
	}
	else
	{
		for (int i = 0;i < 3;i++)
		{
			miximage[i].create(lHeight, lWidth, CV_8UC1);
		}
		split(Waterimage2, achannels2);
		Imageplus(Image3, achannels2[0], miximage[0], 0.6, 0.4, 15, 0, 0); //叠加
		Imageplus(Image3, achannels2[1], miximage[1], 0.6, 0.4, 15, 0, 0);
		Imageplus(Image3, achannels2[2], miximage[2], 0.6, 0.4, 15, 0, 0);
		merge(miximage, 3, Miximage);
	}
	MatToCimage(Miximage, cimage3);
	cimage3.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, cimage2.GetHeight() + 5, cimage3.GetWidth(), cimage3.GetHeight(),
		0, 0, cimage3.GetWidth(), cimage3.GetHeight());
	Endimage.create(lHeight * 2, lWidth, Waterimage2.type());
	lpDIBBits1 = Image2.ptr<uchar>(0);
	lpDIBBits2 = Miximage.ptr<uchar>(0);
	lpNewDIBBits = Endimage.ptr<uchar>(0);// 初始化新分配的内存，设定初始值为0
	lpDst = (LPBYTE)lpNewDIBBits;

	memset(lpDst, (BYTE)255, lWidth * 3 * 2 * lHeight); //为新图像分配值
	for (int j = 0;j < lHeight;j++)              //拼到一张图
		for (int i = 0, t = 0;i < lWidth * channel;i++, t++)
		{
			if (channel == 1)  //灰度图水波纹
			{
				lpSrc1 = (LPBYTE)lpDIBBits1 + lWidth * j + i;
				lpDst = (LPBYTE)lpNewDIBBits + lWidth * 3 * j + t;
				*lpDst = (BYTE)*lpSrc1;
				t++;
				lpDst = (LPBYTE)lpNewDIBBits + lWidth * 3 * j + t;
				*lpDst = (BYTE)*lpSrc1;
				t++;
				lpDst = (LPBYTE)lpNewDIBBits + lWidth * 3 * j + t;
				*lpDst = (BYTE)*lpSrc1;
			}
			else if (channel == 3) //彩色图像水波纹
			{
				lpSrc1 = (LPBYTE)lpDIBBits1 + lWidth * 3 * j + i;
				lpDst = (LPBYTE)lpNewDIBBits + lWidth * 3 * j + i;
				*lpDst = (BYTE)*lpSrc1;
			}
		}
	for (int j = lHeight;j < 2 * lHeight;j++)
		for (int i = 0;i < lWidth * 3;i++)
		{
			lpSrc2 = (LPBYTE)lpDIBBits2 + lWidth * 3 * (j - lHeight) + i;
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * 3 * j + i;
			*lpDst = (BYTE)*lpSrc2;
		}
	MatToCimage(Endimage, cimage3);
	cimage3.Draw(pDC->GetSafeHdc(), 2 * cimage2.GetWidth() + 10, 0, cimage3.GetWidth(), cimage3.GetHeight(),
		0, 0, cimage3.GetWidth(), cimage3.GetHeight());
	pDC->TextOut(10, cimage2.GetHeight() * 2 + 5, _T("倒置"));
	pDC->TextOut(10 + cimage2.GetWidth(), cimage2.GetHeight() * 2 + 5, _T("模糊，叠加"));
	pDC->TextOut(10 + 2 * cimage2.GetWidth(), cimage2.GetHeight() * 2 + 5, _T("最终结果"));
}


void COpencvMFCView::OnFrame() //相框1
{
	Invalidate();
	UpdateWindow();
	Mat Image2;
	Mat Miximage;
	Image2 = rawImage2.clone();
	Mat Image3;
	//给图片扩充边界
	copyMakeBorder(Image2, Image3, (int)(Image2.rows*0.1),
		(int)(Image2.rows*0.1), (int)(Image2.cols*0.1), (int)(Image2.cols*0.1), BORDER_CONSTANT, Scalar(0, 0, 0));
	Mat frame1 = imread("相框1.bmp", -1);
	Miximage.create(Image3.rows, Image3.cols, frame1.type());
	Frame(Image3, Miximage, frame1);
	CImage cimage2;
	MatToCimage(Miximage, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = Miximage.clone();
}


void COpencvMFCView::OnFrame2()  //相框2
{
	Invalidate();
	UpdateWindow();
	Mat Image2;
	Mat Miximage;
	Image2 = rawImage2.clone();
	Mat Image3;
	//给图片扩充边界
	copyMakeBorder(Image2, Image3, (int)(Image2.rows*0.03),
		(int)(Image2.rows*0.03), (int)(Image2.cols*0.03), (int)(Image2.cols*0.03), BORDER_CONSTANT, Scalar(0, 0, 0));
	Mat frame1 = imread("相框2.jpeg", -1);
	Miximage.create(Image3.rows, Image3.cols, frame1.type());
	Frame(Image3, Miximage, frame1);
	CImage cimage2;
	MatToCimage(Miximage, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = Miximage.clone();
}


void COpencvMFCView::OnFrame3()  //相框3
{
	Invalidate();
	UpdateWindow();
	Mat Image2;
	Image2 = rawImage2.clone();
	Mat Miximage;
	Mat Image3;
	//给图片扩充边界
	copyMakeBorder(Image2, Image3, (int)(Image2.rows*0.03),
		(int)(Image2.rows*0.03), (int)(Image2.cols*0.03), (int)(Image2.cols*0.03), BORDER_CONSTANT, Scalar(0, 0, 0));
	Mat frame1 = imread("相框4.jpg", -1);
	Miximage.create(Image3.rows, Image3.cols, frame1.type());
	Frame(Image3, Miximage, frame1);
	CImage cimage2;
	MatToCimage(Miximage, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = Miximage.clone();
}


void COpencvMFCView::OnFrame4()  //相框4
{
	Invalidate();
	UpdateWindow();
	Mat Miximage;
	Mat Image2;
	Image2 = rawImage2.clone();
	Mat Image3;
	//给图片扩充边界
	copyMakeBorder(Image2, Image3, (int)(Image2.rows*0.03),
		(int)(Image2.rows*0.03), (int)(Image2.cols*0.03), (int)(Image2.cols*0.03), BORDER_CONSTANT, Scalar(0, 0, 0));
	Mat frame1 = imread("相框6.jpg", -1);
	Miximage.create(Image3.rows, Image3.cols, frame1.type());
	Frame(Image3, Miximage, frame1);
	CImage cimage2;
	MatToCimage(Miximage, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = Miximage.clone();
}


void COpencvMFCView::OnFrame5() //相框5
{
	Invalidate();
	UpdateWindow();
	Mat Image2;
	Image2 = rawImage2.clone();
	Mat frame0 = imread("heartmodel.jpg", -1);
	Mat Miximage;
	Mat Miximage2;
	Mat Image3;
	//给图片扩充边界
	copyMakeBorder(Image2, Image3, (int)(Image2.rows*0.05),
		(int)(Image2.rows*0.05), (int)(Image2.cols*0.05), (int)(Image2.cols*0.05), BORDER_CONSTANT, Scalar(0, 0, 0));
	Miximage.create(Image3.rows, Image3.cols, frame0.type());
	Miximage2.create(Image3.rows, Image3.cols, frame0.type());
	Frame(Image3, Miximage, frame0);
	Mat frame1 = imread("Heart1.jpg", -1);
	Frame(Miximage, Miximage2, frame1);
	CImage cimage2;
	MatToCimage(Miximage2, cimage2);
	CDC *pDC = GetDC();
	cimage2.Draw(pDC->GetSafeHdc(), cimage2.GetWidth() + 5, 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());  //显示新图像
	myImage = Miximage.clone();

}





void COpencvMFCView::OnHsihigram()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CDC *pDC = GetDC();
	Mat Image2 = rawImage2.clone();
	CImage cimage11;
	MatToCimage(Image2, cimage11);
	pDC->TextOut(10, cimage11.GetHeight() + 5, _T("原图"));
	long	lSrcWidth = Image2.cols;      //图像的宽度和高度
	long	lSrcHeight = Image2.rows;
	Mat HImage;
	HImage.create(lSrcHeight, lSrcWidth, Image2.type());
	double **s;
	double **H;
	s = new double*[lSrcHeight];
	for (int i = 0;i < lSrcHeight;i++)
	{
		s[i] = new double[lSrcWidth];
	}
	H = new double*[lSrcHeight];
	for (int i = 0;i < lSrcHeight;i++)
	{
		H[i] = new double[lSrcWidth];
	}
	CString str;
	double run_time;
	_LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始
	for (int j = 0;j < lSrcHeight;j++)
		for (int i = 0;i < lSrcWidth;i++)
		{
			float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
			float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
			float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
			float num1 = 0.5*((r - g) + (r - b));
			float num2 = (r - g)*(r - g) + (r - b)*(g - b);
			float d = sqrt(num2);
			float d1 = num1 / d;
			double ang = acos(d1);
			double I = (r + g + b) / 3.0;
			BYTE Ii = I * 255;
			double min;
			min = r > g ? g : r;
			min = min > b ? b : min;
			H[j][i] = (g >= b) ? ang : 2 * pi - ang;
			H[j][i] = H[j][i] / (2 * pi);
			s[j][i] = 1 - (3.0*min) / (r + g + b);
			HImage.at<Vec3b>(j, i)[2] = Ii;
			HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
			HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
		}
	HImage = Histogram_Equalization2(HImage);
	for (int j = 0;j < lSrcHeight;j++)
		for (int i = 0;i < lSrcWidth;i++)
		{
			double b, g, r;
			double Ii;
			H[j][i] = HImage.at<Vec3b>(j, i)[0];
			s[j][i] = HImage.at<Vec3b>(j, i)[1];
			Ii = HImage.at<Vec3b>(j, i)[2];
			H[j][i] /= 255.0;
			s[j][i] /= 255.0;
			Ii /= 255.0;
			H[j][i] *= 2 * pi;
			if (H[j][i] >= 0 && H[j][i] < (120.0 / 360.0) * 2 * pi)
			{
				b = Ii * (1 - s[j][i]);
				r = Ii * (1 + (s[j][i] * cos(H[j][i])) / cos((pi / 3.0 - H[j][i])));
				g = 3 * Ii - (b + r);
				Image2.at<Vec3b>(j, i)[0] = b * 255;
				Image2.at<Vec3b>(j, i)[1] = g * 255;
				Image2.at<Vec3b>(j, i)[2] = r * 255;
			}
			else if (H[j][i] >= (120.0 / 360.0) * 2 * pi && H[j][i] < (240.0 / 360.0) * 2 * pi)
			{
				r = Ii * (1 - s[j][i]);
				g = Ii * (1 + (s[j][i] * cos((H[j][i]) - 2.0*pi / 3.0)) / cos((pi - H[j][i])));
				b = 3 * Ii - (r + g);
				Image2.at<Vec3b>(j, i)[0] = b * 255;
				Image2.at<Vec3b>(j, i)[1] = g * 255;
				Image2.at<Vec3b>(j, i)[2] = r * 255;
			}
			else if (H[j][i] >= (240.0 / 360.0) * 2 * pi && H[j][i] < 2 * pi)
			{
				g = Ii * (1 - s[j][i]);;
				b = Ii * (1 + (s[j][i] * cos(H[j][i] - 4.0*pi / 3.0)) / cos(5.0*pi / 3.0 - H[j][i]));;
				r = 3 * Ii - (g + b);
				Image2.at<Vec3b>(j, i)[0] = b * 255;
				Image2.at<Vec3b>(j, i)[1] = g * 255;
				Image2.at<Vec3b>(j, i)[2] = r * 255;
			}

		}
	QueryPerformanceCounter(&time_over);	//计时结束
	run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	str.Format(_T("time:%f us"), run_time);//前后之差即程序运行时间
	CImage cimage2;
	MatToCimage(HImage, cimage2);
	cimage2.Draw(pDC->GetSafeHdc(), 2 * (cimage2.GetWidth() + 20), 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
	pDC->TextOut(2 * (cimage2.GetWidth() + 20), cimage11.GetHeight() + 5, _T("HSI模型下直方图均衡化后"));
	CImage cimage3;
	MatToCimage(Image2, cimage3);
	cimage3.Draw(pDC->GetSafeHdc(), 3 * (cimage2.GetWidth() + 20), 0, cimage3.GetWidth(), cimage3.GetHeight(),
		0, 0, cimage3.GetWidth(), cimage3.GetHeight());
	pDC->TextOut(3 * (cimage2.GetWidth() + 20), cimage11.GetHeight() + 5, _T("HSI转RGB"));
	pDC->TextOut(3 * (cimage2.GetWidth() + 20) + 100, cimage11.GetHeight() + 5, str);
	CHistogramDialog dlg;
	memcpy(dlg.fPro, fPro, 256 * 4); //源图像分布概率
	memcpy(dlg.temp, temp, 256 * 4);  //累计直方图
	memcpy(dlg.fProT, fProT, 256 * 4); //均衡化后
	CString str1, str2, str3, strmid1, strmid2;
	str1.Format(_T("%d"), lSrcWidth * lSrcHeight);
	str2.Format(_T("%0.02f"), average1);
	str3.Format(_T("%0.02f"), average2);
	strmid1.Format(_T("%0.02f"), mid1);
	strmid2.Format(_T("%0.02f"), mid2);
	dlg.pixel1 = str1;
	dlg.pixel2 = str1;
	dlg.average1 = str2;
	dlg.average2 = str3;
	dlg.mid1 = strmid1;
	dlg.mid2 = strmid2;
	dlg.standard1.Format(_T("%0.02f"), stan1);
	dlg.Standard2.Format(_T("%0.02f"), stan2);
	dlg.DoModal();
	myImage = Image2.clone();
}


void COpencvMFCView::OnConverthsi()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CDC *pDC = GetDC();
	Mat Image2 = rawImage2.clone();
	CImage cimage11;
	MatToCimage(Image2, cimage11);
	pDC->TextOut(10, cimage11.GetHeight() + 5, _T("原图"));
	long	lSrcWidth = Image2.cols;      //图像的宽度和高度
	long	lSrcHeight = Image2.rows;
	Mat HImage;
	HImage.create(lSrcHeight, lSrcWidth, Image2.type());
	double **s;
	double **H;
	s = new double*[lSrcHeight];
	for (int i = 0;i < lSrcHeight;i++)
	{
		s[i] = new double[lSrcWidth];
	}
	H = new double*[lSrcHeight];
	for (int i = 0;i < lSrcHeight;i++)
	{
		H[i] = new double[lSrcWidth];
	}
	CString str;
	double run_time;
	_LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始
	for (int j = 0;j < lSrcHeight;j++)
		for (int i = 0;i < lSrcWidth;i++)
		{
			float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
			float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
			float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
			float num1 = 0.5*((r - g) + (r - b));
			float num2 = (r - g)*(r - g) + (r - b)*(g - b);
			float d = sqrt(num2);
			float d1 = num1 / d;
			double ang = acos(d1);
			double I = (r + g + b) / 3.0;
			BYTE Ii = I * 255;
			double min;
			min = r > g ? g : r;
			min = min > b ? b : min;
			H[j][i] = (g >= b) ? ang : 2 * pi - ang;
			H[j][i] = H[j][i] / (2 * pi);
			s[j][i] = 1 - (3.0*min) / (r + g + b);
			HImage.at<Vec3b>(j, i)[2] = Ii;
			HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
			HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
		}
	HImage = ConvertHSI(HImage);

	for (int j = 0;j < lSrcHeight;j++)
		for (int i = 0;i < lSrcWidth;i++)
		{
			double b, g, r;
			double Ii;
			H[j][i] = HImage.at<Vec3b>(j, i)[0];
			s[j][i] = HImage.at<Vec3b>(j, i)[1];
			Ii = HImage.at<Vec3b>(j, i)[2];
			H[j][i] /= 255.0;
			s[j][i] /= 255.0;
			Ii /= 255.0;
			H[j][i] *= 2 * pi;
			if (H[j][i] >= 0 && H[j][i] < (120.0 / 360.0) * 2 * pi)
			{
				b = Ii * (1 - s[j][i]);
				r = Ii * (1 + (s[j][i] * cos(H[j][i])) / cos((pi / 3.0 - H[j][i])));
				g = 3 * Ii - (b + r);
				Image2.at<Vec3b>(j, i)[0] = b * 255;
				Image2.at<Vec3b>(j, i)[1] = g * 255;
				Image2.at<Vec3b>(j, i)[2] = r * 255;
			}
			else if (H[j][i] >= (120.0 / 360.0) * 2 * pi && H[j][i] < (240.0 / 360.0) * 2 * pi)
			{
				r = Ii * (1 - s[j][i]);
				g = Ii * (1 + (s[j][i] * cos((H[j][i]) - 2.0*pi / 3.0)) / cos((pi - H[j][i])));
				b = 3 * Ii - (r + g);
				Image2.at<Vec3b>(j, i)[0] = b * 255;
				Image2.at<Vec3b>(j, i)[1] = g * 255;
				Image2.at<Vec3b>(j, i)[2] = r * 255;
			}
			else if (H[j][i] >= (240.0 / 360.0) * 2 * pi && H[j][i] < 2 * pi)
			{
				g = Ii * (1 - s[j][i]);;
				b = Ii * (1 + (s[j][i] * cos(H[j][i] - 4.0*pi / 3.0)) / cos(5.0*pi / 3.0 - H[j][i]));;
				r = 3 * Ii - (g + b);
				Image2.at<Vec3b>(j, i)[0] = b * 255;
				Image2.at<Vec3b>(j, i)[1] = g * 255;
				Image2.at<Vec3b>(j, i)[2] = r * 255;
			}
		}
	QueryPerformanceCounter(&time_over);	//计时结束
	run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	str.Format(_T("time:%f us"), run_time);//前后之差即程序运行时间
	CImage cimage2;
	MatToCimage(HImage, cimage2);
	cimage2.Draw(pDC->GetSafeHdc(), (cimage2.GetWidth() + 20), 0, cimage2.GetWidth(), cimage2.GetHeight(),
		0, 0, cimage2.GetWidth(), cimage2.GetHeight());
	pDC->TextOut((cimage2.GetWidth() + 20), cimage11.GetHeight() + 5, _T("HSI模型下倒置后"));
	CImage cimage3;
	MatToCimage(Image2, cimage3);
	cimage3.Draw(pDC->GetSafeHdc(), 2 * (cimage2.GetWidth() + 20), 0, cimage3.GetWidth(), cimage3.GetHeight(),
		0, 0, cimage3.GetWidth(), cimage3.GetHeight());
	pDC->TextOut(2 * (cimage2.GetWidth() + 20), cimage11.GetHeight() + 5, _T("HSI转RGB"));
	pDC->TextOut(2 * (cimage2.GetWidth() + 20) + 100, cimage11.GetHeight() + 5, str);
}


void COpencvMFCView::OnConvertrgb()
{
	ConvertMat();
}


void COpencvMFCView::OnHuffman()
{
	LONG lHeight;
	LONG lWidth;
	LONG lLineBytes; //图像每行的字节数
	LONG lCountSum;  //图像像素总数
	LONG i, j;
	double *dProba; // 数组指针用来保存各个亮度信息出现概率
	int nColorNum; //当前图像颜色数目
	nColorNum = 255;
	//------------------------------------ -
	//	   开始计算各个灰度级出现的概率	
	//	   如果需要对指定的序列进行哈夫曼编码,
	//	   只要将这一步改成给各个灰度级概率赋值即可
	//---------------------------------------

	// 分配内存
	dProba = new double[nColorNum];
	//得到图象的宽度和高度
	Mat Image2 = rawImage2.clone();
	lWidth = Image2.cols; //图像宽
	lHeight = Image2.rows; //图像高
	lCountSum = lWidth * lHeight;  //图像总像素数
	BYTE pixel;
	//计算图像每行的字节数
	// 赋零值
	for (i = 0; i < nColorNum; i++)
	{
		dProba[i] = 0.0;
	}
	//计算各个灰度值的计数
	for (i = 0;i < lHeight;i++)
		for (j = 0;j < lWidth;j++)
		{
			pixel = Image2.at<uchar>(i, j);
			dProba[pixel] = dProba[pixel] + 1;
		}
	for (i = 0;i < nColorNum;i++)
	{
		dProba[i] = dProba[i] / (float)lCountSum;
	}
	//---------------------------------------
	//	 构建霍夫曼编码的码表
	//	 并用对话框显示霍夫曼码表
	//-------------------------------------
	CHuffman dlgCoding;

	dlgCoding.dProba = dProba;
	dlgCoding.nColorNum = nColorNum;
	dlgCoding.DoModal();
}


void COpencvMFCView::OnHsihuffman()
{
	LONG lHeight;
	LONG lWidth;
	LONG lLineBytes; //图像每行的字节数
	LONG lCountSum;  //图像像素总数
	LONG i, j;
	double *dProba; // 数组指针用来保存各个灰度值出现概率
	int nColorNum; //当前图像颜色数目
	nColorNum = 255;
	//------------------------------------ -
	//	   开始计算各个灰度级出现的概率	
	//	   如果需要对指定的序列进行哈夫曼编码,
	//	   只要将这一步改成给各个灰度级概率赋值即可
	//---------------------------------------

	// 分配内存
	dProba = new double[nColorNum];
	//得到图象的宽度和高度
	Mat Image2 = rawImage2.clone();
	lWidth = Image2.cols; //图像宽
	lHeight = Image2.rows; //图像高
	lCountSum = lWidth * lHeight;  //图像总像素数
	Mat HImage;
	HImage.create(lHeight, lWidth, Image2.type());
	double **s;
	double **H;
	s = new double*[lHeight];
	for (int i = 0;i < lHeight;i++)
	{
		s[i] = new double[lWidth];
	}
	H = new double*[lHeight];
	for (int i = 0;i < lHeight;i++)
	{
		H[i] = new double[lWidth];
	}
	for (int j = 0;j < lHeight;j++)
		for (int i = 0;i < lWidth;i++)
		{
			float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
			float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
			float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
			float num1 = 0.5*((r - g) + (r - b));
			float num2 = (r - g)*(r - g) + (r - b)*(g - b);
			float d = sqrt(num2);
			float d1 = num1 / d;
			double ang = acos(d1);
			double I = (r + g + b) / 3.0;
			BYTE Ii = I * 255;
			double min;
			min = r > g ? g : r;
			min = min > b ? b : min;
			H[j][i] = (g >= b) ? ang : 2 * pi - ang;
			H[j][i] = H[j][i] / (2 * pi);
			s[j][i] = 1 - (3.0*min) / (r + g + b);
			HImage.at<Vec3b>(j, i)[2] = Ii;
			HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
			HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
		}
	BYTE pixel;
	//计算图像每行的字节数
	// 赋零值
	for (i = 0; i < nColorNum; i++)
	{
		dProba[i] = 0.0;
	}
	//计算各个灰度值的计数
	for (i = 0;i < lHeight;i++)
		for (j = 0;j < lWidth;j++)
		{
			pixel = HImage.at<Vec3b>(i, j)[2];
			dProba[pixel] = dProba[pixel] + 1;
		}
	for (i = 0;i < nColorNum;i++)
	{
		dProba[i] = dProba[i] / (float)lCountSum;
	}
	//---------------------------------------
	//	 构建霍夫曼编码的码表
	//	 并用对话框显示霍夫曼码表
	//-------------------------------------
	CHSIHuffman dlgCoding;

	dlgCoding.dProba = dProba;
	dlgCoding.nColorNum = nColorNum;
	dlgCoding.DoModal();
}


void COpencvMFCView::OnShannonfano()
{
	LONG lHeight;
	LONG lWidth;
	LONG lLineBytes; //图像每行的字节数
	LONG lCountSum;  //图像像素总数
	LONG i, j;
	double *dProba; // 数组指针用来保存各个亮度信息出现概率
	int nColorNum; //当前图像颜色数目
	nColorNum = 255;
	//------------------------------------ -
	//	   开始计算各个灰度级出现的概率	
	//	   如果需要对指定的序列进行哈夫曼编码,
	//	   只要将这一步改成给各个灰度级概率赋值即可
	//---------------------------------------

	// 分配内存
	dProba = new double[nColorNum];
	//得到图象的宽度和高度
	Mat Image2 = rawImage2.clone();
	lWidth = Image2.cols; //图像宽
	lHeight = Image2.rows; //图像高
	lCountSum = lWidth * lHeight;  //图像总像素数
	BYTE pixel;
	//计算图像每行的字节数
	// 赋零值
	for (i = 0; i < nColorNum; i++)
	{
		dProba[i] = 0.0;
	}
	//计算各个灰度值的计数
	for (i = 0;i < lHeight;i++)
		for (j = 0;j < lWidth;j++)
		{
			pixel = Image2.at<uchar>(i, j);
			dProba[pixel] = dProba[pixel] + 1;
		}
	for (i = 0;i < nColorNum;i++)
	{
		dProba[i] = dProba[i] / (float)lCountSum;
	}
	//---------------------------------------
	//	 构建霍夫曼编码的码表
	//	 并用对话框显示霍夫曼码表
	//-------------------------------------
	CShannon dlgCoding;

	dlgCoding.m_dProba = dProba;
	dlgCoding.m_nColorNum = nColorNum;
	dlgCoding.DoModal();
}


void COpencvMFCView::OnAirth()
{
	CAirth dlg;
	dlg.DoModal();
}



void COpencvMFCView::OnRoberts()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	robertsflag = 0;
	CRoberts dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnSobel()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	solbelflag = 0;
	CSobel dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnCanny()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CCanny dlg;
	dlg.view = this;
	dlg.DoModal();
}




void COpencvMFCView::OnPrewitt()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	priwittflag = 0;
	CPriwitt dlg;
	dlg.view = this;
	dlg.DoModal();
}



void COpencvMFCView::OnLaplacianseg()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Laplacianflag = 0;
	CLaplacian dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnReimage()
{
	rawImage2 = myImage.clone();
	CDC *pDC = GetDC();
	CImage cimage;
	MatToCimage(rawImage2, cimage);
	cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());

}


void COpencvMFCView::Onregiongrow()
{
	CRegiongrow dlg;
	if (IDOK == dlg.DoModal())
	{
		regionT = dlg.T;
		MessageBox(_T("鼠标点击选择种子点"));
		growflag = 1;
	}


}

void COpencvMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{

	if (growflag == 1)
	{
		Invalidate();
		UpdateWindow(); //窗口的重绘
		CString str1;
		str1.Format(_T("x坐标:%d"), point.x);
		CString str2;
		str2.Format(_T("y坐标:%d"), point.y);
		CDC *pDC = GetDC();

		Mat Image2 = rawImage2.clone();
		long lHeight = Image2.rows;
		long lWidth = Image2.cols;
		startpoint.x = point.x;
		startpoint.y = point.y;
		if (Image2.channels() == 1)
		{
			Image2 = regionGrow(Image2, startpoint, regionT);
		}
		else if (Image2.channels() == 3)
		{
			Mat HImage;
			HImage.create(lHeight, lWidth, Image2.type());
			double **s;
			double **H;
			s = new double*[lHeight];
			for (int i = 0;i < lHeight;i++)
			{
				s[i] = new double[lWidth];
			}
			H = new double*[lHeight];
			for (int i = 0;i < lHeight;i++)
			{
				H[i] = new double[lWidth];
			}
			for (int j = 0;j < lHeight;j++)
				for (int i = 0;i < lWidth;i++)
				{
					float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
					float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
					float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
					float num1 = 0.5*((r - g) + (r - b));
					float num2 = (r - g)*(r - g) + (r - b)*(g - b);
					float d = sqrt(num2);
					float d1 = num1 / d;
					double ang = acos(d1);
					double I = (r + g + b) / 3.0;
					BYTE Ii = I * 255;
					double min;
					min = r > g ? g : r;
					min = min > b ? b : min;
					H[j][i] = (g >= b) ? ang : 2 * pi - ang;
					H[j][i] = H[j][i] / (2 * pi);
					s[j][i] = 1 - (3.0*min) / (r + g + b);
					HImage.at<Vec3b>(j, i)[2] = Ii;
					HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
					HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
				}
			HImage = regionGrowcolor(HImage, startpoint, regionT);
			for (int j = 0;j < lHeight;j++)
				for (int i = 0;i < lWidth;i++)
				{
					double b, g, r;
					double Ii;
					H[j][i] = HImage.at<Vec3b>(j, i)[0];
					s[j][i] = HImage.at<Vec3b>(j, i)[1];
					Ii = HImage.at<Vec3b>(j, i)[2];
					H[j][i] /= 255.0;
					s[j][i] /= 255.0;
					Ii /= 255.0;
					H[j][i] *= 2 * pi;
					if (H[j][i] >= 0 && H[j][i] < (120.0 / 360.0) * 2 * pi)
					{
						b = Ii * (1 - s[j][i]);
						r = Ii * (1 + (s[j][i] * cos(H[j][i])) / cos((pi / 3.0 - H[j][i])));
						g = 3 * Ii - (b + r);
						Image2.at<Vec3b>(j, i)[0] = b * 255;
						Image2.at<Vec3b>(j, i)[1] = g * 255;
						Image2.at<Vec3b>(j, i)[2] = r * 255;
					}
					else if (H[j][i] >= (120.0 / 360.0) * 2 * pi && H[j][i] < (240.0 / 360.0) * 2 * pi)
					{
						r = Ii * (1 - s[j][i]);
						g = Ii * (1 + (s[j][i] * cos((H[j][i]) - 2.0*pi / 3.0)) / cos((pi - H[j][i])));
						b = 3 * Ii - (r + g);
						Image2.at<Vec3b>(j, i)[0] = b * 255;
						Image2.at<Vec3b>(j, i)[1] = g * 255;
						Image2.at<Vec3b>(j, i)[2] = r * 255;
					}
					else if (H[j][i] >= (240.0 / 360.0) * 2 * pi && H[j][i] < 2 * pi)
					{
						g = Ii * (1 - s[j][i]);;
						b = Ii * (1 + (s[j][i] * cos(H[j][i] - 4.0*pi / 3.0)) / cos(5.0*pi / 3.0 - H[j][i]));;
						r = 3 * Ii - (g + b);
						Image2.at<Vec3b>(j, i)[0] = b * 255;
						Image2.at<Vec3b>(j, i)[1] = g * 255;
						Image2.at<Vec3b>(j, i)[2] = r * 255;
					}

				}
			for (int i = 0;i < lHeight;i++)
				for (int j = 0;j < lWidth;j++)
				{
					if (Image2.at<Vec3b>(i, j)[0] == 0 && Image2.at<Vec3b>(i, j)[1] == 0 && Image2.at<Vec3b>(i, j)[2] == 0)
					{
						Image2.at<Vec3b>(i, j)[0] = 0;
						Image2.at<Vec3b>(i, j)[1] = 0;
						Image2.at<Vec3b>(i, j)[2] = 255;
					}
				}
		}
		CImage cimage;
		MatToCimage(Image2, cimage);
		cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
		pDC->TextOut(20, cimage.GetHeight() + 20, str1);
		pDC->TextOut(20, cimage.GetHeight() + 40, str2);
		rawImage2 = Image2.clone();
	}
	CScrollView::OnLButtonUp(nFlags, point);
}


void COpencvMFCView::OnReload()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	rawImage2 = reImage.clone();
	CImage cimage;
	CDC *pDC = GetDC();
	MatToCimage(rawImage2, cimage);
	cimage.Draw(pDC->GetSafeHdc(), 0, 0, cimage.GetWidth(), cimage.GetHeight(),
		0, 0, cimage.GetWidth(), cimage.GetHeight());
}


void COpencvMFCView::OnThreshold()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Mat Image2 = rawImage2.clone();
	long lHeight = Image2.rows;
	long lWidth = Image2.cols;
	int i, j;
	int gen;
	CGenThresHold dlg;
	if (IDOK == dlg.DoModal())
	{
		gen = dlg.gen;
	}
	int thresHold;
	if (Image2.channels() == 1)
	{
		thresHold = Threshold(Image2, gen);
		Mat image3;
		Image2.copyTo(image3);
		for (i = 0;i < lHeight;i++)
			for (j = 0;j < lWidth;j++)
			{
				int temp = Image2.at<uchar>(i, j);
				if (temp > thresHold)
				{
					temp = 0;
				}
				else if (temp <= thresHold)
				{
					temp = 255;
				}
				image3.at<uchar>(i, j) = temp;
			}
		CImage cimage;
		CDC *pDC = GetDC();
		MatToCimage(image3, cimage);
		cimage.Draw(pDC->GetSafeHdc(), cimage.GetWidth() + 20, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}
	else if (Image2.channels() == 3)
	{
		Mat HImage;
		HImage.create(lHeight, lWidth, Image2.type());
		double **s;
		double **H;
		s = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			s[i] = new double[lWidth];
		}
		H = new double*[lHeight];
		for (int i = 0;i < lHeight;i++)
		{
			H[i] = new double[lWidth];
		}
		for (int j = 0;j < lHeight;j++)
			for (int i = 0;i < lWidth;i++)
			{
				float b = Image2.at<Vec3b>(j, i)[0] / 255.0;
				float g = Image2.at<Vec3b>(j, i)[1] / 255.0;
				float r = Image2.at<Vec3b>(j, i)[2] / 255.0;
				float num1 = 0.5*((r - g) + (r - b));
				float num2 = (r - g)*(r - g) + (r - b)*(g - b);
				float d = sqrt(num2);
				float d1 = num1 / d;
				double ang = acos(d1);
				double I = (r + g + b) / 3.0;
				BYTE Ii = I * 255;
				double min;
				min = r > g ? g : r;
				min = min > b ? b : min;
				H[j][i] = (g >= b) ? ang : 2 * pi - ang;
				H[j][i] = H[j][i] / (2 * pi);
				s[j][i] = 1 - (3.0*min) / (r + g + b);
				HImage.at<Vec3b>(j, i)[2] = Ii;
				HImage.at<Vec3b>(j, i)[1] = s[j][i] * 255;
				HImage.at<Vec3b>(j, i)[0] = H[j][i] * 255;
			}
		Mat achannels[3];
		split(HImage, achannels);
		thresHold = Threshold(achannels[2], gen);
		Mat image3;
		Image2.copyTo(image3);
		for (i = 0;i < lHeight;i++)
			for (j = 0;j < lWidth;j++)
			{
				int temp = achannels[2].at<uchar>(i, j);
				//if (temp > thresHold)
				//{
				//	/*temp = 255;*/
				//	image3.at<Vec3b>(i,j)[2]
				//}
				if (temp < thresHold)
				{
					image3.at<Vec3b>(i, j)[0] = 255;
					image3.at<Vec3b>(i, j)[1] = 255;
					image3.at<Vec3b>(i, j)[2] = 255;
				}
				//image3.at<uchar>(j, i) = temp;
			}
		CImage cimage;
		CDC *pDC = GetDC();
		MatToCimage(image3, cimage);
		cimage.Draw(pDC->GetSafeHdc(), cimage.GetWidth() + 20, 0, cimage.GetWidth(), cimage.GetHeight(),
			0, 0, cimage.GetWidth(), cimage.GetHeight());
	}

	
}


void COpencvMFCView::OnFudiao()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	CValueSet dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnColorregiongrow()
{
	CRegiongrow dlg;
	if (IDOK == dlg.DoModal())
	{
		regionT = dlg.T;
		MessageBox(_T("鼠标点击选择种子点"));
		growflag = 1;
	}
}


void COpencvMFCView::OnPencilroberts()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	robertsflag = 1;
	CRoberts dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnPencilsobel()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	solbelflag = 1;
	CSobel dlg;
	dlg.view = this;
	dlg.DoModal();

}


void COpencvMFCView::OnPencilpriwitt()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	priwittflag = 1;
	CPriwitt dlg;
	dlg.view = this;
	dlg.DoModal();
}


void COpencvMFCView::OnFudiaolaplacian()
{
	Invalidate();
	UpdateWindow(); //窗口的重绘
	Laplacianflag = 1;
	CLaplacian dlg;
	dlg.view = this;
	dlg.DoModal();
}
