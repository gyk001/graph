#pragma once
#include "AdjMatrixStruct.h"
#include "OrthListGrap.h"
#include <afxtempl.h>


// CAdjMatrix 命令目标

class CAdjMatrixGrap : public CObject
{
public:

	CAdjMatrixGrap();
	virtual ~CAdjMatrixGrap();

public:
	// 顶点信息
	VexNode vexs[MAX_VERTEX_NUM]; 
public:
	//弧的信息
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 	               
public:
	// 顶点数
	int vexNum; 

public:
	//清空图数据
	void Clear(void);
public:
	//从十字链表生成邻接矩阵
	void CreateAdjMatrixGrap();
public:
	//保存至文件
	void Save(CString pathName);
public:
	//从文件创建一个图
	bool CreateFromFile(void);
public:
	//从文件创建一个图
	bool CreateFromFile(CString filePath);
public:
	//分割字符串
	bool SplitString(CString str,CString& str1, CString& str2);
public:
	//分割字符串
	bool SplitString(CString str,int num, CStringArray& outStr) ;
public:
	//最短路径-迪杰斯特拉
	void ShortPath_DJJ(CString BeginKey , CStringArray &EndKey, CStringArray &pathResult ,CStringArray & pathLength  );
public:
	//返回节点在数组中的索引
	int LocateVex(CString key);
};


