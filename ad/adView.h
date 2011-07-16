// adView.h : CadView 类的接口
//


#pragma once
#include "afxwin.h"
#include "adDoc.h"
#include "atltypes.h"
#include "ChildSiblingTree.h"

#define GRAP_VIEW	1	//十字链表视图
#define BFS_VIEW	2	//深度优先生成森林视图
#define DFS_VIEW	3	//广度优先生成森林视图


class CadView : public CFormView
{
protected: // 仅从序列化创建
	CadView();
	DECLARE_DYNCREATE(CadView)

public:
	enum{ IDD = IDD_AD_FORM };

// 属性
public:
	CadDoc* GetDocument() const;

// 操作
public:


// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()



protected:
	virtual void OnDraw(CDC* pDC);
public:
	//输出字符串
	void DrawString(CDC* pDC,CString str, CPoint a,CPoint b, COLORREF clr) ;
public:
	//画弧——十字链表
	void DrawArc(CDC* pDC);
public:	
	//画弧——生成树
	void DrawCSArc(CDC* pDC , CSNode * tree);
public:
	//更新状态栏文字
	void UpdateMessage(int flag = 0);
public:
	//画箭头
	void ArrowTo( CDC* pDC,const CPoint from,const CPoint to, COLORREF clr ,int PenWidth,int toRadius=32);
public:
	//显示消息框（添加删除等）
	void ShowMessageBox(Status flag);
public:
	//添加顶点
	void AddVex(void);
public:
	//添加边
	void AddArc(void);
public:
	//删除顶点
	void DelVex(void);
public:
	//删除边
	void DelArc(void);
public:
	//深度优先搜索
	void DepthFirstSearch(void);
public:
	//广度优先搜索
	void BreadthFirstSearth(void);
public:
	// 设置画布大小
	void SetAreaSize( int x, int y );
public:
	// 自动设置画布大小
	void AutoCalcAreaSize();
public:
	//生成新控件
	CDragStatic* NewDragStatic(LPCTSTR strTitle, CPoint pt , int radius);
public:
	// 画布宽度
	int iMaxWidth;
public:
	// 画板高度
	int iMaxHeight;
public:
	//视图模式
	int iViewMode;
public:
	afx_msg void OnMenuAddVex();
public:
	afx_msg void OnMenuDelVex();
public:
	afx_msg void OnMenuAddArc();
public:
	afx_msg void OnMenuDelArc();
public:
	afx_msg void OnMenuShowInfo();
public:
	afx_msg void OnShowArcInfo();
public:
	afx_msg void OnAreaSize();
public:
	afx_msg void OnMenuFindPath();
public:
	afx_msg void OnMenuResetAllColor();
public:
	afx_msg void OnVisitAll();
public:
	afx_msg void OnMenuVisitAll();
public:
	afx_msg void OnMenuOrthlistGrap();
public:
	afx_msg void OnMenuChildSibingDfsTree();
public:
	afx_msg void OnUpdateMenuOrthlistGrap(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuChildSibingTree(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuAddVex(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuDelVex(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuAddArc(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuDelArc(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuShowVexInfo(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuShowArcInfo(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuFindPath(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateVisitAll(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuResetAllColor(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateAreaSize(CCmdUI *pCmdUI);
public:
	afx_msg void OnMenuCheckAnnulus();
public:
	afx_msg void OnMenuChildSibingBfsTree();
public:
	afx_msg void OnUpdateMenuChildSibingBfsTree(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuCheckAnnulus(CCmdUI *pCmdUI);
	afx_msg void OnMenuCriticalPath();
	afx_msg void OnUpdateMenuCriticalPath(CCmdUI *pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuShortPath();
	afx_msg void OnUpdateMenuShortPath(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void ClipChildren(HWND hwnd, HRGN parent);
private:
	// 最后操作的坐标点,如鼠标右键单击的点
	CPoint lastPoint;
};

#ifndef _DEBUG  // adView.cpp 中的调试版本
inline CadDoc* CadView::GetDocument() const
   { return reinterpret_cast<CadDoc*>(m_pDocument); }
#endif

