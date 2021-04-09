
// Opencv_MFCDoc.cpp: COpencvMFCDoc 类的实现
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
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern Mat myImage;
extern Mat Image;
Mat reImage;
Mat rawImage2;
// COpencvMFCDoc
extern CImage cimage;
IMPLEMENT_DYNCREATE(COpencvMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(COpencvMFCDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE_AS, &COpencvMFCDoc::OnFileSaveAs)
END_MESSAGE_MAP()


// COpencvMFCDoc 构造/析构

COpencvMFCDoc::COpencvMFCDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

COpencvMFCDoc::~COpencvMFCDoc()
{
}

BOOL COpencvMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// COpencvMFCDoc 序列化

void COpencvMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void COpencvMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void COpencvMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void COpencvMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COpencvMFCDoc 诊断

#ifdef _DEBUG
void COpencvMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpencvMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COpencvMFCDoc 命令


BOOL COpencvMFCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	//下面几句话为宽字符字符串到ansi字符串的一个转化，因cv::imread函数的第一个参数为String型
	CT2A str1(lpszPathName);
	string str = str1.m_psz;
	TRACE("%s\n", str.c_str());

	rawImage = imread(str, -1); //rawImage读取到图像数据，-1表示按按解码方式读，可保留图像源格式
	myImage.create(rawImage.rows, rawImage.cols, rawImage.type());
	myImage = rawImage.clone(); //今后基于myImage进行图像操作和显示
	rawImage2 = rawImage.clone();
	reImage = rawImage.clone();
	//图像的显示需要还需将Mat转化为CImage类，具体可见工程View类的OnDraw函数
	return TRUE;
}


BOOL COpencvMFCDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类
	CString strFilter;
	strFilter = "BMP位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";
	CFileDialog dlg(FALSE, NULL, NULL, NULL, strFilter);
	if (IDOK != dlg.DoModal())
		return true;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	CString strExtension;
	strFileName = dlg.GetPathName();
	strExtension = dlg.GetFileExt();
	if (strExtension.GetLength() == 0)
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			strExtension = "bmp"; break;
		case 2:
			strExtension = "jpg"; break;
		case 3:
			strExtension = "gif"; break;
		case 4:
			strExtension = "png"; break;
		default:
			break;
		}
		strFileName = strFileName + '.' + strExtension;
	}
	// 图像保存
	std::string strName = CT2A(strFileName);
	if (!imwrite(strName, myImage))
		AfxMessageBox(_T("保存图像失败！"));
	else
		AfxMessageBox(_T("保存图像成功！"));

	return CDocument::OnSaveDocument(lpszPathName);
}


void COpencvMFCDoc::OnFileSaveAs()
{
	CString strFilter;
	strFilter = "BMP位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";
	CFileDialog dlg(FALSE, NULL, NULL, NULL, strFilter);
	if (IDOK != dlg.DoModal())
		return;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	CString strExtension;
	strFileName = dlg.GetPathName();
	strExtension = dlg.GetFileExt();
	if (strExtension.GetLength() == 0)
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			strExtension = "bmp"; break;
		case 2:
			strExtension = "jpg"; break;
		case 3:
			strExtension = "gif"; break;
		case 4:
			strExtension = "png"; break;
		default:
			break;
		}
		strFileName = strFileName + '.' + strExtension;
	}
	// 图像保存
	std::string strName = CT2A(strFileName);
	if (!imwrite(strName, myImage))
		AfxMessageBox(_T("保存图像失败！"));
	else
		AfxMessageBox(_T("保存图像成功！"));
	// TODO: 在此添加命令处理程序代码
}
