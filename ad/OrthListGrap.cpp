// OrthList.cpp : 实现文件
//

#include "stdafx.h"
#include "ad.h"
#include "OrthListGrap.h"





// COrthList

COrthListGrap::COrthListGrap()
: m_iVexNum(0)
, m_iArcNum(0)
{

	for (int i= 0 ; i<MAX_VERTEX_NUM ;i++)
	{
		xlist[i].data.key="";
		xlist[i].data.inDegree=0;
		xlist[i].data.outDegree=0;

		xlist[i].m_pThisTail=NULL;
		xlist[i].m_pThisHead=NULL;
		xlist[i].DragBox=NULL;
		xlist[i].m_bUsed=false;
		xlist[i].visited = false;
	}
}

COrthListGrap::~COrthListGrap()
{
	Clear();
}


// 返回key节点的位置，key是唯一的
int COrthListGrap::LocateVex(CString key)
{

	for (int i=0;i<MAX_VERTEX_NUM;i++)
	{
		if (xlist[i].m_bUsed && xlist[i].data.key==key)
		{
			return i;
		}
	}
	return -1;

}

Status COrthListGrap::AddVex(CString key,CString moreInfo, CPoint pt , int radius)
{
	TRACE("	***AddVex( key, *p)***\n");
	int pos = GetCanUse();
	if (pos ==-1)
	{
		return VEX_TOO_MANY;
	}
	key.MakeUpper();

	if (LocateVex(key)!=-1)
	{
		return VEX_EXIST;
	}
	CDragStatic *p = pView->NewDragStatic(key, pt ,radius);


	xlist[pos].m_bUsed=true;
	xlist[pos].data.key = key;
	xlist[pos].m_pThisTail =NULL;
	xlist[pos].m_pThisHead =NULL;
	xlist[pos].data.inDegree = 0;
	xlist[pos].data.outDegree =0;
	xlist[pos].data.moreInfo = moreInfo;
	xlist[pos].DragBox = p;
	SetChangeMark();
	TRACE(" + AddVex( %s , *p )->%d\n",key,pos);
	m_iVexNum++;
	return SUCCESS;
}

// 添加弧
Status COrthListGrap::AddArc(int headVex, int tailVex, int weight)
{
	TRACE("	***AddArx( int headVex, int tailVex)***\n");
	if (headVex==-1||tailVex==-1)
	{
		return VEX_NOT_FOUND;
	}
	if (!xlist[headVex].m_bUsed || ! xlist[tailVex].m_bUsed)//有顶点不存在
	{
		//MessageBox(NULL,"有顶点不存在！","AddArc(int headVex, int tailVex)",MB_OK);
		return VEX_NOT_FOUND;
	}
	if (GetArc(headVex,tailVex))
	{
		//MessageBox(NULL,"该弧已存在！","AddArc(int headVex, int tailVex)",MB_OK);
		return ARC_EXIST;
	}

	OrthListArcBox *p=new OrthListArcBox();
	if (!p)
	{
		//MessageBox(NULL,"创建新节点失败！","AddArc(int headVex, int tailVex)",MB_OK);
		return NEW_ARC_ERR;
	}

	p->color = RGB(255,0,255);
	p->headVex = headVex;
	p->tailVex = tailVex;
	p->data.quan = weight;
	p->PenWidth = 2;

	p->m_pNextSameHead = xlist[headVex].m_pThisHead;
	p->m_pNextSameTail = xlist[tailVex].m_pThisTail;
	xlist[headVex].m_pThisHead= p;
	xlist[tailVex].m_pThisTail = p;

	m_iArcNum++;
	xlist[headVex].data.outDegree++;
	xlist[tailVex].data.inDegree++;
	TRACE(" + AddArc("+xlist[headVex].data.key+" , "+xlist[tailVex].data.key+")"+"%d-%d\n",headVex,tailVex);
	SetChangeMark();
	return SUCCESS;
}


// 删除弧
Status COrthListGrap::DelArc(int headVex, int tailVex)
{
	TRACE("   ***DelArc(int headVex, int tailVex)***\n");
	if (headVex==-1||tailVex==-1)
	{
		return VEX_NOT_FOUND;
	}
	if (! xlist[headVex].m_bUsed || !xlist[tailVex].m_bUsed)
	{
		//MessageBox(NULL,"! xlist[headVex].m_bUsed || !xlist[tailVex].m_bUsed","DelArc(int headVex, int tailVex)",MB_OK);
		return VEX_NOT_FOUND;
	}

	OrthListArcBox *p =GetArc(headVex ,tailVex);

	if (!p)
	{
		return ARC_NOT_FOUND;
	}

	OrthListArcBox *pHeadFront = FrontHeadArc(p);//此弧的前一条同头弧
	OrthListArcBox *pTailFront = FrontTailArc(p);//此弧的前一条同尾弧


	if (pHeadFront)
	{
		pHeadFront->m_pNextSameHead = p->m_pNextSameHead;
	}
	else
	{
		xlist[headVex].m_pThisHead = p->m_pNextSameHead;
	}

	if (pTailFront)
	{
		pTailFront->m_pNextSameTail = p->m_pNextSameTail;
	}
	else
	{
		xlist[tailVex].m_pThisTail = p->m_pNextSameTail;
	}
	delete p;
	m_iArcNum--;
	xlist[headVex].data.outDegree--;
	xlist[tailVex].data.inDegree--;
	SetChangeMark();
	TRACE(" - DelArc("+xlist[headVex].data.key+" , "+xlist[tailVex].data.key+")"+"%d-%d\n",headVex,tailVex);
	return SUCCESS;
}


// 返回弧指针
OrthListArcBox* COrthListGrap::GetArc(int headVex, int tailVex)
{
	TRACE("   ***GetArc(int headVex, int tailVex)***\n");
	if (headVex==-1||tailVex==-1)
	{
		return NULL;
	}
	if (! xlist[headVex].m_bUsed || !xlist[tailVex].m_bUsed)
	{
		return NULL;
	}
	OrthListArcBox *p = xlist[headVex].m_pThisHead;
	while(p!=NULL)
	{
		if (p->tailVex == tailVex)
		{
			return p;
		}
		p=p->m_pNextSameHead;
	}
	return NULL;
}


Status COrthListGrap::DelVex(CString key)
{
	TRACE("   ***DelVex(CString key)***\n");
	int pos = LocateVex(key);
	if(pos == -1)
	{
		//MessageBox(NULL,"无此节点！","DelVex(CString key)",MB_OK);	
		return VEX_NOT_FOUND;
	}

	OrthListArcBox *p=xlist[pos].m_pThisTail;//出弧
	while (p)
	{
		DelArc(p->headVex,p->tailVex);
		p=xlist[pos].m_pThisTail;
	}

	//删除以该点为弧尾的弧
	p = xlist[pos].m_pThisHead;//入弧
	while (p)
	{
		DelArc(p->headVex,p->tailVex);
		p = xlist[pos].m_pThisHead;
	}

	//销毁控件
	if(xlist[pos].DragBox)
	{
		xlist[pos].DragBox->DestroyWindow();
		delete xlist[pos].DragBox;
	}
	xlist[pos].m_bUsed=false;
	m_iVexNum--;
	SetChangeMark();
	TRACE(" - DelVex("+key+")"+" %d\n",pos);
	return SUCCESS;
}



// 得到最前面可以用的节点下标
int COrthListGrap::GetCanUse(void)
{
	for (int i= 0 ; i<MAX_VERTEX_NUM ;i++)
	{
		if (!xlist[i].m_bUsed)
		{
			return i;
		}
	}
	return -1;
}

//前一条同头弧
OrthListArcBox* COrthListGrap::FrontHeadArc(OrthListArcBox* pArc)
{
	OrthListArcBox *p = xlist[pArc->headVex].m_pThisHead;
	OrthListArcBox *pHeadFront = NULL;//此弧的前一条同头弧
	while(p)
	{
		if (p->tailVex == pArc->tailVex)
		{
			break;
		}
		pHeadFront=p;
		p=p->m_pNextSameHead;
	}

	return pHeadFront;
}

//前一条同尾弧
OrthListArcBox* COrthListGrap::FrontTailArc(OrthListArcBox* pArc)
{
	OrthListArcBox *p = xlist[pArc->tailVex].m_pThisTail;
	OrthListArcBox *pTailFront = NULL;//此弧的前一条同尾弧
	while(p)
	{
		if (p->headVex == pArc->headVex)
		{
			break;
		}
		pTailFront=p;
		p=p->m_pNextSameTail;
	}

	return pTailFront;
}

//清空访问标记
void COrthListGrap::clearVisted(void)
{

	for (int i= 0 ; i<MAX_VERTEX_NUM ;i++)
	{
		xlist[i].visited = false;
	}
}

// 得到index节点的第一个邻节点（有方向）
int COrthListGrap::FirstAdjVex(int index)
{
	if (!xlist[index].m_bUsed)
	{
		//TRACE("FirstAdjVex( %s ) = VEX_NOT_FOUND\n",xlist[index].data.key);
		return VEX_NOT_FOUND;
	}
	if (xlist[index].m_pThisHead)
	{
		int vex = xlist[index].m_pThisHead->tailVex;
		//TRACE("FirstAdjVex( %s ) = %s\n",xlist[index].data.key,xlist[vex].data.key);
		xlist[index].m_pNowVisitVexArc = xlist[index].m_pThisHead;
		return vex;
	}
	//TRACE("FirstAdjVex( %s ) = NO_ADJ_VEX\n",xlist[index].data.key);
	return NO_ADJ_VEX;
}

// 得到index节点的下一个临节点
int COrthListGrap::NextAdjVex(int index)
{
	if ( xlist[index].m_pNowVisitVexArc == NULL)
	{
		//TRACE("NextAdjVex( %s ) = NO_ADJ_VEX\n" ,xlist[index].data.key);
		return NO_ADJ_VEX;
	}
	if ( xlist[index].m_pNowVisitVexArc->m_pNextSameHead)
	{
		int vex = xlist[index].m_pNowVisitVexArc->m_pNextSameHead->tailVex;
		//TRACE("NextAdjVex( %s ) = %s\n", xlist[index].data.key ,xlist[vex].data.key);
		xlist[index].m_pNowVisitVexArc = xlist[index].m_pNowVisitVexArc->m_pNextSameHead;
		return vex;
	}
	//TRACE("NextAdjVex( %s ) = NO_ADJ_VEX\n", xlist[index].data.key );
	return NO_ADJ_VEX;
}


//从顶点vex出发，深度优先搜索 <vex所在连通分量> 
void COrthListGrap::DepthFirstSearch(int vex ,queue<int> &visitOrder )
{
	xlist[vex].visited =true;
	visitOrder.push(vex);
	TRACE("------> DepthFirstSearch() -- %s\n",xlist[vex].data.key);
	int i =0 ;
	for(int w=FirstAdjVex( vex ); w!= NO_ADJ_VEX; w=NextAdjVex( vex ),i++)
	{		
		TRACE("    for( i= %d ) %s\n",i,xlist[w].data.key);
		if (!xlist[w].visited)
		{
			DepthFirstSearch(w , visitOrder);     
		}
	}
}

//从顶点vex出发，广度优先搜索 <vex所在连通分量>
void COrthListGrap::BreadthFirstSearth(int vex, queue<int> &visitOrder)
{

	if ( !xlist[vex].visited )
	{       
		xlist[vex].visited = TRUE;   
		// 访问u
		TRACE("------> BreadthFirstSearch() -- %s\n",xlist[vex].data.key);
		BFSQueue.push(vex);             // v入队列
		visitOrder.push(vex);
		while ( !BFSQueue.empty() ) 
		{
			// 队头元素出队并置为u
			int u= BFSQueue.front();
			BFSQueue.pop();       
			int w = FirstAdjVex( u );
			for( ; w!=NO_ADJ_VEX ; w=NextAdjVex( u ))
				if ( !xlist[w].visited)  
				{
					xlist[w].visited = true;
					visitOrder.push( w );
					TRACE("------> BreadthFirstSearch() -- %s\n",xlist[w].data.key);
					BFSQueue.push(w);; // 访问的顶点w入队列
				} // if
		} // while

	} 

}


COLORREF COrthListGrap::GetArcColor(OrthListArcBox* pArc)
{
	return pArc->color;
}

void COrthListGrap::SetArcColor( int headVex, int tailVex, COLORREF color)
{
	OrthListArcBox* pArc = GetArc(headVex, tailVex) ;
	if(pArc)
	{
		pArc->PenWidth = 4;	
		pArc->color = color;
	}
}

//从邻接矩阵生成十字链表
void COrthListGrap::CreateOrthListFromMatrix(void)
{
	Clear();
	if (AdjMatrixGrap.vexNum !=0 )
	{

		for (int i=0; i<AdjMatrixGrap.vexNum; i++ )
		{
			CString strKey = AdjMatrixGrap.vexs[i].key;
			OrthGrap.AddVex(strKey ,AdjMatrixGrap.vexs[i].moreInfo, AdjMatrixGrap.vexs[i].point,AdjMatrixGrap.vexs[i].radius );
		}

		for (int i=0; i<AdjMatrixGrap.vexNum; i++ )
		{
			for (int j=0; j<AdjMatrixGrap.vexNum;j++)
			{
				if(AdjMatrixGrap.arcs[i][j] < MAX_INT)
					OrthGrap.AddArc(i , j ,AdjMatrixGrap.arcs[i][j]);
			}

		}
	}
	pView->UpdateMessage();
}

//清空该十字链表
void COrthListGrap::Clear(void)
{
	for (int i=0;i<MAX_VERTEX_NUM;i++)
	{
		if(xlist[i].m_bUsed)
		{
			TRACE("Clear ->"+xlist[i].data.key+"\n");
			DelVex(xlist[i].data.key);
			
		}
	}
}


//从点from到点头进行深度优先搜索
bool COrthListGrap::DFSfromto(int from, int to, stack<int> &vexStack)
{
	xlist[from].visited =true;
	vexStack.push( from );	//加入路径
	TRACE(" + PUSH( %s ) \n",xlist[from].data.key );
	if (from == to )
	{
		return true;
	}

	int i = 0 ;
	for(int w=FirstAdjVex( from ); w!= NO_ADJ_VEX; w=NextAdjVex( from ) )
	{		
		if (!xlist[w].visited)
		{
			if(DFSfromto(w ,to ,vexStack))
			{			
				return true;
			}
		}
		i++;
		//TRACE(" %s ( %d )\n", xlist[w].data.key,i);

	}
	if( i == xlist[from].data.outDegree)//from的所有邻接点都已访问，即该点不是路径上的点
	{
		TRACE(" - POP( %s ) OutDegree %d \n",xlist[vexStack.top()].data.key ,xlist[vexStack.top()].data.outDegree  );
		vexStack.pop();//删去该点
	}
	return false;
}

// 找出两点的路径，并修改路径上弧的颜色
bool COrthListGrap::FindPath(CString headKey, CString tailKey,bool ResetColor,bool showPath)
{
	if(ResetColor)
	{
		ResetAllArcColor();
		ResetAllVexStyle();
	}
	int headPos = LocateVex( headKey );
	int tailPos = LocateVex( tailKey );

	if ( headPos == -1 || tailPos == -1)
	{
		return false;
	}
	clearVisted();

	stack<int> vexStack;

	DFSfromto( headPos , tailPos ,vexStack);

	if (vexStack.size()<1)
	{
		return false;
	}

	if(showPath)
	{
		int tmp;	
		while ( vexStack.size()>1)
		{
			tmp = vexStack.top();
			vexStack.pop();
			SetArcColor( vexStack.top() ,tmp ,RGB( 255, 255 ,0 ) );
			TRACE(" %s -> %s \n",xlist[vexStack.top()].data.key ,xlist[tmp].data.key);
		}
		xlist[headPos].DragBox->SetStyle(VEX_HEAD);
		xlist[tailPos].DragBox->SetStyle(VEX_TAIL);
		pView->Invalidate();
	}


	return true;

}

void COrthListGrap::ResetAllArcColor()
{
	if( m_iVexNum >=2 )
	{
		OrthListArcBox *p =NULL;

		for (int index=0 ;index<MAX_VERTEX_NUM ;index++)
		{
			if(xlist[index].m_bUsed)
			{
				p = xlist[index].m_pThisTail;//只处理入弧

				while (p)
				{
					p ->color =RGB(255 ,0 ,255 );
					p ->PenWidth = 2 ;
					p = p->m_pNextSameTail;
				}

			}
		}
		pView->Invalidate();

	}
}

CString COrthListGrap::DFSVisitOrder( int begin)
{
	queue<int> VisitOrder;
	CString str = "@ ";

	clearVisted();

	DepthFirstSearch( begin, VisitOrder );
	for (int i = 0 ;i<MAX_VERTEX_NUM; i++ )
	{
		if ( ! xlist[i].visited &&  xlist[i].m_bUsed )
		{
			VisitOrder.push( -1 );
			DepthFirstSearch( i, VisitOrder );
		}
	}


	for ( ; VisitOrder.size()>0 ;VisitOrder.pop() )
	{
		if ( VisitOrder.front() != -1 )
		{
			str = str + "[" + xlist[VisitOrder.front()].data.key+"] ";

		}
		else
		{
			str += "\r\n@ ";
		}
	}

	return str;
}

CString COrthListGrap::BFSVisitOrder( int begin)
{

	queue<int> VisitOrder;
	CString str = "@ ";

	clearVisted();

	while ( !BFSQueue.empty() )
	{
		BFSQueue.pop();
	}

	BreadthFirstSearth( begin, VisitOrder );
	for (int i = 0 ;i<MAX_VERTEX_NUM; i++ )
	{
		if ( ! xlist[i].visited &&  xlist[i].m_bUsed )
		{
			VisitOrder.push( -1 );
			BreadthFirstSearth( i, VisitOrder );
		}
	}


	for ( ; VisitOrder.size()>0 ;VisitOrder.pop() )
	{
		if ( VisitOrder.front() != -1 )
		{
			str = str + "[" + xlist[VisitOrder.front()].data.key+"] ";

		}
		else
		{
			str += "\r\n@ ";
		}
	}

	return str;
}

void COrthListGrap::CreateDFSForest(void)
{
	if( ChSibDFSTree.bNeedChange || !ChSibDFSTree.root)
	{
		if( ChSibDFSTree.root )
			ChSibDFSTree.DelVex( ChSibDFSTree.root );

		ChSibDFSTree.root = NULL;

		clearVisted();

		CSNode *p,*q;



		for ( int i =0 ; i< MAX_VERTEX_NUM ; i++ )
		{
			if ( xlist[i].m_bUsed)
			{
				if ( !xlist[i].visited )
				{
					TRACE("	+++++++++++++++++++++>>> %s\n", xlist[i].data.key);
					p = new CSNode();
					if( !ChSibDFSTree.root )
					{
						ChSibDFSTree.root = p;
					}
					else
					{
						q->nextSibling = p;
					}
					p->firstChild = NULL;
					p->nextSibling = NULL;
					p->key = xlist[i].data.key;			
					p->DragBox = pView->NewDragStatic( xlist[i].data.key ,CPoint(30,30) ,1000);
					q = p;
					CreateDFSTree( i , p);
				}
			}
		}
		SortPos(ChSibDFSTree.root,CPoint( 30,30));
		ChSibDFSTree.bNeedChange = false;
	}
}


void COrthListGrap::CreateBFSForest(void)
{
	if( ChSibBFSTree.bNeedChange || !ChSibBFSTree.root)
	{
		if( ChSibBFSTree.root )
			ChSibBFSTree.DelVex( ChSibBFSTree.root );
		ChSibBFSTree.root = NULL;
		queue<CSNode *> rootQueue;
		clearVisted();
		while ( !BFSQueue.empty() )
		{
			BFSQueue.pop();
		}

		CSNode *p,*q;
		CSNode* pNow;

		for ( int i =0 ; i< MAX_VERTEX_NUM ; i++ )
		{
			if ( xlist[i].m_bUsed)
			{
				if ( !xlist[i].visited )
				{
					xlist[i].visited = true;
					BFSQueue.push( i );
					p = new CSNode();
					p->firstChild = NULL;
					p->nextSibling = NULL;
					p->key = xlist[i].data.key;
					p->DragBox = pView->NewDragStatic( xlist[i].data.key ,CPoint(20,20) ,1000);
					
					rootQueue.push(p);
					TRACE(p->key+"#\n");
					
					if( !ChSibBFSTree.root )
					{
						ChSibBFSTree.root = p;
						q = p;
					}
					else
					{
						q->nextSibling = p;
						q = q->nextSibling;
					}

					while ( !BFSQueue.empty() )
					{
						int j = BFSQueue.front();
						BFSQueue.pop();
		
						bool child = true;
						pNow = rootQueue.front();
						rootQueue.pop();
						TRACE("*\n");
						for ( int w = FirstAdjVex( j ); w!= NO_ADJ_VEX ; w= NextAdjVex(j) )
						{
							if ( !xlist[w].visited )
							{
								xlist[w].visited = true;
								BFSQueue.push( w );
								//TRACE(xlist[w].data.key +" ");
								p = new CSNode();
								p->firstChild = NULL;
								p->key = xlist[w].data.key;
								p->nextSibling = NULL;
								p->DragBox = pView->NewDragStatic( xlist[w].data.key ,CPoint(20,20) ,1000);
								rootQueue.push(p);
								TRACE(p->key+"#\n");
								if (child)
								{
									child = !child;
									pNow->firstChild = p;
									pNow = p;

								}
								else
								{
									pNow->nextSibling =p;
									pNow = p;
								}
							}
						}
					}

				}
			}
		}
		SortPos(ChSibBFSTree.root,CPoint( 30,30));
		ChSibBFSTree.bNeedChange = false;
	}
}

//整理二叉树节点的位置
void COrthListGrap::SortPos(CSTree& tree, CPoint &pt)
{
	if ( !tree)
	{
		return ;
	}
	int y = pt.y;
	tree->DragBox->MoveWindow( pt.x,pt.y,30,30);
	pt.y+=60;
	SortPos(tree->firstChild, pt);
	pt.y = y;
	pt.x +=60;
	SortPos(tree->nextSibling, pt);
}


void COrthListGrap::CreateDFSTree(int vex, CSTree& tree)
{
	//TRACE("	CreateDFSTree >>> %d\n", vex);
	if ( !tree || vex == -1 )
	{
		return ;
	}

	xlist[vex].visited = true ;
	bool first = true;
	CSNode *p = NULL;
	CSNode *q = NULL;

	for ( int  w = FirstAdjVex( vex ) ; w != NO_ADJ_VEX ; w = NextAdjVex(vex))
	{
		if ( ! xlist[w].visited )
		{
			p = new CSNode();
			p->firstChild = NULL;
			p->nextSibling = NULL;
			p->key = xlist[w].data.key;
			p->DragBox = pView->NewDragStatic( xlist[w].data.key ,CPoint(30,30) ,1000);	
			if ( first )
			{
				tree->firstChild = p;
				first = false;
			}
			else
			{
				q->nextSibling = p ;
			}
			q = p;
			CreateDFSTree( w , q);

		}


	}
}

void COrthListGrap::MarkAnnulus( CString key )
{
	int index = LocateVex( key );
	if (index == -1)
	{
		return;
	}
	for ( int w = FirstAdjVex( index); w!=NO_ADJ_VEX ; w= NextAdjVex(index) )
	{
		if ( FindPath( key, xlist[w].data.key,false,false) && FindPath( xlist[w].data.key,key,false,false))
		{
			FindPath( key,  xlist[w].data.key,true) ;
			FindPath( xlist[w].data.key ,key ,false) ;
			ResetAllVexStyle();
			xlist[index].DragBox->SetStyle(VEX_CIRCLE_POINT);
			return;
		}
	}

}

bool COrthListGrap::CheckAnnulus(void)
{
	int InDegree[MAX_VERTEX_NUM];
	clearVisted();
	for (int i = 0; i<MAX_VERTEX_NUM ; i++)
	{
		InDegree[i] = xlist[i].data.inDegree;

	}

	stack <int> zeroIn;
	for ( int i = 0;i<MAX_VERTEX_NUM;i++)
	{
		if ( xlist[i].m_bUsed)
		{
			if ( InDegree[i]==0 )
			{
				zeroIn.push( i );
				TRACE(" push %d \n" ,i);
			}
		}
	}
	int count = 0;
	while (!zeroIn.empty())
	{
		int i = zeroIn.top();
		TRACE(" * %d \n" ,i);
		xlist[i].visited = true;
		zeroIn.pop();
		count ++;
		for ( OrthListArcBox* pArc = xlist[i].m_pThisHead ; pArc ; pArc= pArc->m_pNextSameHead)
		{
			int index = pArc->tailVex;
			TRACE("                                %s\n",xlist[index].data.key);
			InDegree[index]--;
			if( InDegree[index]==0 )
				zeroIn.push( index );
		}
	}
	if (count < m_iVexNum )
	{
		for (int i=0 ;i<MAX_VERTEX_NUM;i++)
		{
			if (xlist[i].m_bUsed && ! xlist[i].visited )
			{
				MarkAnnulus( xlist[i].data.key );
				break;
			}
		}
		return true;//有回路
	}
	return false;
}

CSNode* COrthListGrap::NewNode(CString key, CPoint pt)
{
	CSNode *p = new CSNode();
	p->firstChild = NULL;
	p->nextSibling = NULL;
	p->key = key;
	p->DragBox = pView->NewDragStatic( key ,pt ,1000);
	if (pt.x > pView->iMaxWidth || pt.y >pView->iMaxHeight )
	{
		pView->SetAreaSize( pt.x+20 , pt.y+20 );
		pView->Invalidate(FALSE);
	}
	return p;
}


bool COrthListGrap::CriticalPath(void)
{
	ResetAllArcColor();
	ResetAllVexStyle();
	if ( m_iVexNum <2 )
	{
		return false;
	}

	int InDegree[MAX_VERTEX_NUM]={0};


	int BeginAOE=-1,EndAOE=-1;

	for (int i=0; i<MAX_VERTEX_NUM;i++)
	{
		if ( xlist[i].m_bUsed )
		{
			if ( xlist[i].data.inDegree ==0 )
			{
				if( BeginAOE == -1 )
					BeginAOE=i;
				else
					return false;
			}
			if ( xlist[i].data.outDegree ==0 )
			{
				if( EndAOE == -1 )
					EndAOE=i;
				else
					return false;
			}
			InDegree[i]=xlist[i].data.inDegree;

		}
	}

	if ( BeginAOE ==-1 || EndAOE ==-1 )
	{
		return false;
	}

	int ve[MAX_VERTEX_NUM]={0};//最早开始时间

	stack<int> zeroDegree;
	stack<int> order;

	int count=0;
	zeroDegree.push( BeginAOE );

	
	
	OrthListArcBox *pArc=NULL;	

	while ( ! zeroDegree.empty() )
	{
		int j=zeroDegree.top();
		zeroDegree.pop();		
		TRACE("*"+xlist[j].data.key+"\n");
		
		order.push(j);
		count++;


		for ( pArc=xlist[j].m_pThisHead; pArc ;pArc=pArc->m_pNextSameHead )
		{
			int k=pArc->tailVex;
			InDegree[k]--;
			TRACE(xlist[k].data.key+" %d  ->%d\n",InDegree[k],k);
			if (InDegree[k]==0)
			{
				zeroDegree.push(k);
			}
			if (ve[j]+pArc->data.quan>ve[k])
			{
				ve[k]=ve[j]+pArc->data.quan;
			}
		}

	}
	if (count < m_iVexNum)
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	int vl[MAX_VERTEX_NUM];//最晚开始时间
	for (int j=0 ;j<MAX_VERTEX_NUM ;j++)
	{
		vl[j]= ve[EndAOE];
	}

	while ( ! order.empty())
	{
		int j=order.top();
		order.pop();
		for ( pArc=xlist[j].m_pThisHead; pArc ;pArc=pArc->m_pNextSameHead )
		{
			int k=pArc->tailVex;
			if (vl[k]-pArc->data.quan<vl[j])
			{
				vl[j]=vl[k]-pArc->data.quan;
			}
		}
	}

	for (int j=0; j<MAX_VERTEX_NUM;j++ )
	{
		if ( xlist[j].m_bUsed)
		{

			for ( pArc = xlist[j].m_pThisHead; pArc; pArc=pArc->m_pNextSameHead)
			{
				if ( ve[j] == vl[pArc->tailVex]- pArc->data.quan)
				{
					SetArcColor( pArc->headVex ,pArc->tailVex, RGB(0,0,255));
				}
			}
		}
	}
	xlist[BeginAOE].DragBox->SetStyle( VEX_HEAD);
	xlist[EndAOE].DragBox->SetStyle( VEX_TAIL);

	pView->Invalidate(FALSE);
	return true;
}


void COrthListGrap::ResetAllVexStyle(void)
{
	for (int i=0;i<MAX_VERTEX_NUM;i++)
	{
		if ( xlist[i].m_bUsed)
		{
			xlist[i].DragBox->SetStyle(VEX_NORMAL);
		}
	}
}

//
int COrthListGrap::GetLogicPos(int pos)
{
	if ( !xlist[pos].m_bUsed || pos ==-1 )
	{
		return VEX_NOT_FOUND;
	}
	int LogicPos = 0;
	for ( int i = 0;i<pos ;i++)
	{
		if (xlist[i].m_bUsed)
		{
			LogicPos ++;
		}
	}
	return LogicPos;
}

//描出路径
void COrthListGrap::DrawPath(CString Begin, CString End, CString Path)
{
	int a = LocateVex( Begin );
	int b = LocateVex( End );
	if( a==-1 || b== -1)
	{
		return;
	}
	
	ResetAllArcColor();
	ResetAllVexStyle();

	xlist[a].DragBox->SetStyle( VEX_HEAD);
	xlist[b].DragBox->SetStyle( VEX_TAIL);	
	
	CStringArray pathArr;
	int num = SplitString( Path, pathArr);

	for (int i =0; i<num; i++ )
	{
		SetArcColor( LocateVex( pathArr[i]) ,LocateVex(pathArr[i+1]) , RGB(255,255,0));
	}
	pView ->Invalidate(FALSE);
}

//以 - 分割字符串str到outsrt 返回分隔符的个数
int COrthListGrap::SplitString(CString str,CStringArray& outStr) 
{ 
	int num = 0;
	int pos = -1; 
	if ( str == "-")
	{
		return num;
	}
	pos = str.Find("-"); 
	CString strSun;
	while (pos !=-1)
	{
		strSun = str.Left(pos);
		str.Delete(0,pos+1); 
		pos = str.Find("-"); 
		outStr.Add(strSun); 		
		num++;
	}
	outStr.Add(str);
	return num;
} 

//设置修改标记 或 通知其改变
void COrthListGrap::SetChangeMark(void)
{
	ChSibBFSTree.bNeedChange = true;
	ChSibDFSTree.bNeedChange = true;
	if( pView )
	{
		pView->GetDocument()->SetModifiedFlag();
	}
	if(pShortPathDlg)
	{
		pShortPathDlg->InitCtrl();	
	}
}
