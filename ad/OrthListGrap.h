#pragma once
#include "OrthListStruct.h"
#include "ChildSiblingTree.h"
#include <queue>
#include <stack>


using namespace std ;

// COrthList 命令目标

class COrthListGrap : public CObject
{
public:
	COrthListGrap();

	virtual ~COrthListGrap();
public:
	// 顶点数量
	int m_iVexNum;
public:
	// 弧数量
	int m_iArcNum;
public:
	//顶点数组
	OrthListVexNode xlist[MAX_VERTEX_NUM];
public:
	//广度优先搜索辅助队列
	queue<int> BFSQueue;
public:
	// 返回data节点的位置，data是唯一的
	int LocateVex(CString key);
public:
	//添加顶点
	Status AddVex(CString key,CString moreInfo, CPoint pt ,int radius= 16);
public:
	//删除顶点
	Status DelVex(CString key);
public:
	// 添加弧
	Status AddArc(int headVex, int tailVex, int weight);
public:
	// 删除弧
	Status DelArc(int headVex, int tailVex);
public:
	// 返回弧指针
	OrthListArcBox* GetArc(int headVex, int tailVex);
public:
	// 得到最前面可以用的节点下标
	int GetCanUse(void);

public:
	//得到前一个同头节点的弧
	OrthListArcBox* FrontHeadArc(OrthListArcBox* pArc);
public:
	//得到前一个同尾节点的弧
	OrthListArcBox* FrontTailArc(OrthListArcBox* pArc);
public:
	//清除访问标记
	void clearVisted(void);
public:
	// 得到index节点的第一个邻接点（有方向）
	int FirstAdjVex(int index);
public:	
	// 得到index节点的下一个临节点
	int NextAdjVex( int index);
public:
	//从顶点vex出发，深度优先搜索遍历<连通图>
	void DepthFirstSearch(int vex ,queue<int> &visitOrder);
public:
	//从顶点vex出发，广度优先搜索遍历 <vex所在连通分量>
	void BreadthFirstSearth(int vex ,queue<int> &VisitOrder);
public:
	// 连通分量
	int ConnComponent(void);
public:
	//返回弧的颜色
	COLORREF GetArcColor(OrthListArcBox* pArc);
public:
	//设置弧的颜色
	void SetArcColor( int headVex, int tailVex, COLORREF color);
public:
	//从邻接矩阵创建十字链表
	void CreateOrthListFromMatrix(void);
public:
	//清除图
	void Clear(void);
public:
	//从From到to进行深度优先访问，
	bool DFSfromto(int from, int to, stack<int> &vexStack);
public:
	// 两点是否存在路径
	bool FindPath(CString headKey, CString tailKey,bool ResetColor = true, bool changColor = true);
public:
	// 重置所有弧的颜色
	void ResetAllArcColor();
public:
	//深度优先搜索
	CString DFSVisitOrder( int begin);
public:
	//广度优先搜索返回遍历序列（字符串）
	CString BFSVisitOrder( int begin);
public:
	//构造深度优先生成森林
	void CreateDFSForest(void);
public:
	//构造广度优先生成森林
	void CreateBFSForest(void);
public:
	void SortPos(CSTree& tree, CPoint &pt) ;
public:
	//构造深度优先生成树
	void CreateDFSTree(int vex, CSTree& tree);
public:
	//环检查
	bool CheckAnnulus(void);
public:
	//标记环
	void MarkAnnulus( CString key );
public:
	//产生新节点（控件）
	CSNode* NewNode(CString key, CPoint pt);
public:
	//关键路径
	bool CriticalPath(void);
public:
	//重置所有顶点控件风格
	void ResetAllVexStyle(void);
public:
	//得到顶点在数组中的逻辑位置
	int GetLogicPos(int pos);
public:
	//描出路径
	void DrawPath(CString Begin, CString End, CString Path);
public:
	//分割字符串
	int SplitString(CString str, CStringArray& outStr);
public:
	//设置修改标记 或 通知其改变
	void SetChangeMark(void);
};


