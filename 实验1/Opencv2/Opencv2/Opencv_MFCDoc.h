﻿
// Opencv_MFCDoc.h: COpencvMFCDoc 类的接口
//


#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;

class COpencvMFCDoc : public CDocument
{
protected: // 仅从序列化创建
	COpencvMFCDoc() noexcept;
	DECLARE_DYNCREATE(COpencvMFCDoc)

// 特性
public:
// 操作
public:
	Mat rawImage;
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~COpencvMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnFileSaveAs();
};
