#pragma once
#include "atltypes.h"

#define VEX_NORMAL			0
#define VEX_HEAD			1
#define VEX_TAIL			2 
#define VEX_CIRCLE_POINT	3



// CDragStatic

class CDragStatic : public CWnd
{
	DECLARE_DYNAMIC(CDragStatic)


public:
	CDragStatic();
	virtual ~CDragStatic();

protected:
	DECLARE_MESSAGE_MAP()
protected:
	//virtual void PreSubclassWindow();
private:
	CPoint m_ptCenter;
	int m_nRadius;
public:
	//左键是否按下
	//bool m_bLBdown;
public:
	//控件区域
	CRect m_Rect;
public:
	//鼠标是否悬浮
	//bool m_bOver;
public:
	//字体格式
	UINT m_utextFomat;
public:
	//辅助坐标点
	//CPoint m_Point;
public:
	//新坐标点
	//CPoint nowPos;
public:
	//字和控件的颜色
	COLORREF m_crText,m_crOverBG,m_crBG;
public:
	//设置字体颜色
	void SetTextColor(COLORREF crText);
public:
	//设置背景色
	void SetBGColer(COLORREF crBG);
public:
	//设置字体多行显示
	void SetMuliLineMode(bool bMuliLine);
public:
	//设置鼠标悬浮色
	void SetOverBGColor(COLORREF crOverBG);
public:
	//更新并显示提示框
	void UpdateMyView(int msgFalg);
public:
	//返回坐标点
	CPoint GetPoint(void);
public:
	//设置控件显示风格
	void SetStyle(int style);
	CRgn       m_rgn; 

public:
//	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	afx_msg void OnMove(int x, int y);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnDestroy();
public:
	afx_msg void OnShowVexInfo();
public:
	afx_msg void OnMenuAddVex();
public:
	afx_msg void OnMenuDelArc();
public:
	afx_msg void OnMenuDelVex();
public:
	afx_msg void OnMenuAddArc();
public:
	afx_msg void OnMenuShowArcInfo();
public:
	afx_msg void OnMenuVisitAll();
public:
	afx_msg void OnMenuFindPath();
public:
	afx_msg void OnMenuResetAllColor();
public:
	afx_msg void OnMenuCriticalPath();
public:
	afx_msg void OnMenuShortPath();
public:
	afx_msg void OnMenuCheckAnnulus();
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL Create(CString title,
				CWnd* pParentWnd,
				CPoint pt=CPoint(30,30) ,
				int radius = 32
             );


	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	// 获取半径
	int GetRadius(void);
};


