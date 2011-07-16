#pragma once
#include "childsiblingstruct.h"


// CChildSiblingTree

class CChildSiblingTree : public CObject
{
	DECLARE_DYNAMIC(CChildSiblingTree)

public:
	CChildSiblingTree();
	virtual ~CChildSiblingTree();



public:
	// 树根
	CSNode* root;
public:
	//是否需要修改
	bool bNeedChange;

public:
	//删除节点及其子节点
	void DelVex(CSNode* &pVex);
public:
	//隐藏节点及其子节点
	void HideVex(CSNode* &pVex ,int showMode);
public:
	//计算最大坐标点
	void MaxPoint(CSNode *tree,  CPoint& pt);
public:
	CSNode* GetNode(CString key);
private:
	void FindNode(CSNode* pVex ,CString key, CSNode* & result);
};


