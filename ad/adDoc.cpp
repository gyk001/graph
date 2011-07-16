// adDoc.cpp : CadDoc 类的实现
//

#include "stdafx.h"
#include "ad.h"

#include "adDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CadDoc

IMPLEMENT_DYNCREATE(CadDoc, CDocument)

BEGIN_MESSAGE_MAP(CadDoc, CDocument)
END_MESSAGE_MAP()


// CadDoc 构造/析构

CadDoc::CadDoc()
{
	// TODO: 在此添加一次性构造代码

}

CadDoc::~CadDoc()
{
}

BOOL CadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	if ( pView && pView ->iViewMode != GRAP_VIEW )
	{
		 pView ->OnMenuOrthlistGrap();
	}
	OrthGrap.Clear();
	ChSibDFSTree.DelVex(ChSibDFSTree.root);
	ChSibBFSTree.DelVex(ChSibDFSTree.root);
	ChSibBFSTree.bNeedChange = true;
	ChSibDFSTree.bNeedChange = true;
	if( pView)
	{
		pView ->UpdateMessage();
		pView ->Invalidate(FALSE);
	}
	this->SetModifiedFlag(FALSE);
	return TRUE;
}




// CadDoc 序列化

void CadDoc::Serialize(CArchive& ar)
{
	//this->getFil
	if (ar.IsStoring())
	{
		TRACE(_T("store"));

	}
	else
	{
		// TODO: 在此添加加载代码
		TRACE(_T("read"));

	}
}


// CadDoc 诊断

#ifdef _DEBUG
void CadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CadDoc 命令


BOOL CadDoc::OnSaveDocument(LPCTSTR lpszPathName)
{

	AdjMatrixGrap.CreateAdjMatrixGrap();
	AdjMatrixGrap.Save(lpszPathName);
	this->SetModifiedFlag(FALSE);
	return TRUE;
}


BOOL CadDoc::OnOpenDocument(LPCTSTR lpszPathName)
{

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	if( !AdjMatrixGrap.CreateFromFile(lpszPathName))
		return FALSE;
	
	if ( pView->iViewMode != GRAP_VIEW )
	{
			pView->OnMenuOrthlistGrap();
	}
	OrthGrap.CreateOrthListFromMatrix();
	ChSibBFSTree.bNeedChange = true;
	ChSibDFSTree.bNeedChange = true;
	pView->Invalidate();
	this->SetModifiedFlag(FALSE);
	return TRUE;
}
