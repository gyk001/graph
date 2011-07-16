// ChildSiblingTree.cpp : 实现文件
//

#include "stdafx.h"
#include "ad.h"
#include "ChildSiblingTree.h"


// CChildSiblingTree

IMPLEMENT_DYNAMIC(CChildSiblingTree, CWnd)

CChildSiblingTree::CChildSiblingTree()
:root( NULL )
,bNeedChange(true)
{

}

CChildSiblingTree::~CChildSiblingTree()
{
	DelVex( root );
}




// CChildSiblingTree 消息处理程序


void CChildSiblingTree::DelVex(CSNode* &pVex )
{
	
	if (pVex)
	{
		if (pVex->DragBox)
		{
			delete pVex->DragBox;
		}			
		TRACE("  CChildSiblingTree::DelVex - %s\n", pVex->key);
		DelVex( pVex->firstChild );
		DelVex( pVex->nextSibling );
		TRACE("- CChildSiblingTree::DelVex %s \n ",pVex->key);		
		delete pVex;
		pVex = NULL;


	}
}


void CChildSiblingTree::HideVex(CSNode* &pVex , int showMode)
{

	if (pVex)
	{
		if (pVex->DragBox)
		{
			pVex->DragBox->ShowWindow( showMode );
		}			

		HideVex( pVex->firstChild ,showMode);
		HideVex( pVex->nextSibling ,showMode);
	}
}


void CChildSiblingTree::MaxPoint(CSNode *tree,  CPoint& pt)
{
	if ( tree )
	{
		pt.x = max(pt.x , tree->DragBox->GetPoint().x);
		pt.y = max(pt.y , tree->DragBox->GetPoint().y);
		MaxPoint( tree->firstChild , pt );	
		MaxPoint( tree->nextSibling , pt );
	}
}

CSNode* CChildSiblingTree::GetNode(CString key)
{
	CSNode * p = NULL;
	FindNode( root , key , p);
	return p;
}

void CChildSiblingTree::FindNode(CSNode* pVex ,CString key, CSNode* & result)
{
	if ( pVex )
	{
		if (pVex->key == key)
		{
			result = pVex;
			return ;
		}
		FindNode( pVex->firstChild ,key ,result);
		FindNode( pVex->nextSibling, key , result);
	}
}
