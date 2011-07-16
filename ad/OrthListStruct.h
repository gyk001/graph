#include "DragStatic.h"


#define Status int			

#define SUCCESS			0	//成功
#define VEX_EXIST		-1	//顶点已存在
#define ARC_EXIST		-2	//弧已存在
#define VEX_NOT_FOUND	-3	//顶点不存在
#define ARC_NOT_FOUND	-4	//弧不存在
#define NEW_ARC_ERR		-5	//创建新弧失败
#define VEX_TOO_MANY	-6	//顶点数已到上限
#define NO_ADJ_VEX		-7	//没有邻节点

#define MINI_AREA_WIDTH		400
#define MINI_AREA_HEIGHT	300

#define MAX_VERTEX_NUM	300

typedef struct arcInfo  
{
	int quan;
}arcInfo;//弧信息


typedef struct OrthListArcBox{
	int tailVex; 
	int headVex;
	OrthListArcBox* m_pNextSameHead;	//下一个同头节点的弧指针--入弧
	OrthListArcBox* m_pNextSameTail;	//下一个同尾节点的弧指针--出弧
	arcInfo data;
	COLORREF color;		//弧的颜色
	int PenWidth;		//弧的宽度
} OrthListArcBox;//弧节点

typedef struct vexInfo 
{
	CString key;	//关键字--唯一
	int inDegree;	//入度
	int outDegree;	//出度
	CString moreInfo;//备注	
}vexInfo;//顶点信息


typedef struct OrthListVexNode{
	vexInfo data;				//节点的信息
	OrthListArcBox* m_pThisHead;	//第一个以此为弧头的弧指针--入弧	
	OrthListArcBox* m_pThisTail;	//第一个以此为弧尾的弧指针--出弧
	CDragStatic* DragBox;		//控件指针
	bool visited;		//访问标志
	OrthListArcBox* m_pNowVisitVexArc;//链接该节点和当前访问节点的弧指针，遍历使用
	bool m_bUsed;		//节点是否有效
} OrthListVexNode;//顶点节点

