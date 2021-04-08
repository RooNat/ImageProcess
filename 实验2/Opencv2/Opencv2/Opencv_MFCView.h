
// Opencv_MFCView.h: COpencvMFCView 类的接口
//

#pragma once


class COpencvMFCView : public CScrollView
{
protected: // 仅从序列化创建
	COpencvMFCView() noexcept;
	DECLARE_DYNCREATE(COpencvMFCView)

	// 特性
public:
	COpencvMFCDoc* GetDocument() const;
	struct CplexNum
	{
		double re;
		double im;
	};

	CplexNum Add(CplexNum c1, CplexNum c2)
	{
		CplexNum c;
		c.re = c1.re + c2.re;
		c.im = c1.im + c2.im;
		return c;
	}
	CplexNum Sub(CplexNum c1, CplexNum c2)
	{
		CplexNum c;
		c.re = c1.re - c2.re;
		c.im = c1.im - c2.im;
		return c;
	}
	CplexNum Mul(CplexNum c1, CplexNum c2)
	{
		CplexNum c;
		c.re = c1.re*c2.re - c1.im*c2.im;
		c.im = c1.re*c2.im + c2.re*c1.im;
		return c;
	}
	// 操作
public:
	//原图像灰度分布概率密度变量
	float fPro[256];
	//中间变量
	float temp[256]; //累计密度
	float fProT[256];//均衡化之后灰度分布概率密度变量
	int T[256], nk[256], H[256];
	float average1, average2;
	float mid1, mid2;
	float stan1, stan2;
	int gray[256]; // 灰度计数
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void MatToCimage(Mat &mat, CImage& cImage);
	void ForierMat(Mat image);
	void ForierMatRGB(Mat image, int c);
	void  Fourier(CplexNum * pTd, int lWidth, int lHeight, CplexNum * pFd);
	void  FastFourierTran(CplexNum * pTd, CplexNum * pFd, int power);
	void  InverFastFourierTran(CplexNum * pFd, CplexNum * pTd, int power);
	void  InverseFourier(CplexNum * pFd, CplexNum * pTd, int lWidth, int lHeight);
	void InverseFourierMat(Mat image);
	void InverseFourierMatRGB(Mat image, CplexNum * pFd, CplexNum * pNd);
	BOOL  CosTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes, int m);
	BOOL InvestCosTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes, double *pTd, double *pFd);
	void  DisFCosTran(double *pTd, double *pFd, int power);
	void  Walshei_Har(double *pTd, double *pFd, int power);
	BOOL  Walsh_HarTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes);
	void InverseDisFCosTran(double * pTd, double * pFd, int power);
	void DctMat(Mat image);
	void DctMatRGB(Mat image, int m);
	void InverDctMat(Mat image);
	void InverDctMatRGB(Mat image, double *pFd, double *pTd);
	void Linear_Transform(Mat image, BYTE min, BYTE max);
	void Seg_Linear_Transform(Mat image, int x, BYTE s[], BYTE t[]);
	void Log_Transform(Mat image, double a, double b, double c);
	void Histogram_Equalization(Mat image);
	void SpicedSalt(Mat image, float n);
	void WhiteSalt(Mat image, float n);
	void Pepper(Mat image, float n);
	void Middle_Smooth(Mat image, int M);
	void Histogram_Statistic(Mat image, float *probability);
	void Histogram_Match(Mat image, BYTE bGray, int *npMap, float *fpPro);
	void Average_Smooth(Mat image, int M);
	double Gaosiset(double mu, double sigma);
	void GaosiNoise(Mat img, double mu, double sigma, int k);
	void Value_Average_Smooth(Mat image, int **structure, int M);
	void CreateGauss(double **structure, int M);
	void GateGrad(Mat image, BYTE t);
	void Laplacian(Mat image);
	BOOL Convolution(Mat image, int tempH, int tempW, int tempMX, int tempMY, float *fpTempArray, float fCoef);
	void Perfect_Low_Filter(Mat image, int u, int v);
	void Perfect_High_Filter(Mat image, int u, int v);
	void fourier(double * data, int height, int width, int isign);
	void Rotate(Mat image,Mat image3,double ang);
	void Zoom(Mat image,Mat Rimage,double m);
	void Zoom(Mat image, Mat Rimage, int Rwidth, int Rheight);
	void Convert(Mat image);
	void Inversion(Mat image);
	void Frame(Mat Image3,Mat Miximage,Mat image);
	Mat Histogram_Equalization2(Mat image);
	CplexNum *pTdt;  // 分配内存，存放空域的值   自定义的结构 专门用来存放空域的值
	CplexNum *pFdt;    //存放频域的值
	CplexNum *pTdtB;  // 分配内存，存放空域的值   自定义的结构 专门用来存放空域的值
	CplexNum *pFdtB;    //存放频域的值
	CplexNum *pTdtG;  // 分配内存，存放空域的值   自定义的结构 专门用来存放空域的值
	CplexNum *pFdtG;    //存放频域的值
	CplexNum *pTdtR;  // 分配内存，存放空域的值   自定义的结构 专门用来存放空域的值
	CplexNum *pFdtR;    //存放频域的值
	double *pTdD, *pFdD;
	double *pTdDR, *pTdDG, *pTdDB, *pFdDR, *pFdDG, *pFdDB;
	Mat Image;
	// 实现
public:
	virtual ~COpencvMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFourier(); 
	afx_msg void OnFouriertran();
	afx_msg void OnDct();
	afx_msg void OnWal();
	afx_msg void OnInversedct();
	afx_msg void OnLineartransform();
	void LineTransMat(BYTE min, BYTE max);
	void SegLineTransMat(int Linenum, BYTE s[], BYTE t[]);
	void LogLineTransMat(double a, double b, double c);
	void HistogramequalMat();
	void TransMat(int x, int y);
	void ZoomMat(double m);
	void ZoomMat(int Rwidth, int Rheight);
	void RotateMat(double ang);
	void ConvertMat();
	Mat ConvertHSI(Mat image);
	void InversionMat();
	void Imageplus(Mat image1, Mat image2, Mat Miximage, double alp1, double alp2, int light,int positionx,int positiony);
	void Imagesub(Mat image1, Mat image2, Mat Splitimage);
	void ImageplusMat(Mat image1, Mat image2, double alp1, double alp2, int light,double positionx,double positiony);
	void ImagesubMat(Mat image1, Mat image2);
	void GateGradMat(BYTE t);
	afx_msg void OnSeglinetransform();
	afx_msg void Onloglinetrans();
	afx_msg void OnHistogramequal();
	afx_msg void OnAveragesmooth();
	afx_msg void OnSalt();
	afx_msg void OnGaosi();
	afx_msg void OnGaosifiltering();
	afx_msg void OnMid();
	afx_msg void OnPepper();
	afx_msg void Onwhitesalt();
	afx_msg void OnHistogrammatch();
	virtual void OnInitialUpdate();
	afx_msg void OnGategrad();
	afx_msg void OnLaplacian();
	afx_msg void OnPrefectlowfilter();
	afx_msg void OnPrefecthighfilter();
	afx_msg void OnGeometry();
	afx_msg void OnImageplus();
	afx_msg void OnImagesub();
	afx_msg void OnWater();
	afx_msg void OnFrame();
	afx_msg void OnFrame2();
	afx_msg void OnFrame3();
	afx_msg void OnFrame4();
	afx_msg void OnFrame5();
	afx_msg void OnHsihigram();
	afx_msg void OnConverthsi();
	afx_msg void OnConvertrgb();
};

#ifndef _DEBUG  // Opencv_MFCView.cpp 中的调试版本
inline COpencvMFCDoc* COpencvMFCView::GetDocument() const
{
	return reinterpret_cast<COpencvMFCDoc*>(m_pDocument);
}
#endif

