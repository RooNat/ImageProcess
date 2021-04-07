
// Opencv_MFCView.h: COpencvMFCView 类的接口
//

#pragma once


class COpencvMFCView : public CView
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
	BOOL  CosTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes,int m);
	BOOL InvestCosTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes, double *pTd, double *pFd);
	void  DisFCosTran(double *pTd, double *pFd, int power);
	void  Walshei_Har(double *pTd, double *pFd, int power);
	BOOL  Walsh_HarTran(uchar *lpSrcStartBits, long lWidth, long lHeight, long lLineBytes);
	void InverseDisFCosTran(double * pTd, double * pFd, int power);
	void DctMat(Mat image);
	void DctMatRGB(Mat image,int m);
	void InverDctMat(Mat image);
	void InverDctMatRGB(Mat image, double *pFd, double *pTd);

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
};

#ifndef _DEBUG  // Opencv_MFCView.cpp 中的调试版本
inline COpencvMFCDoc* COpencvMFCView::GetDocument() const
   { return reinterpret_cast<COpencvMFCDoc*>(m_pDocument); }
#endif

