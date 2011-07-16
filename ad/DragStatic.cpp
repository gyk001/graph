// CDragStatic.cpp : 实现文件
//
#include "stdafx.h"
#include "ad.h"
#include "DragStatic.h"
#include "VexInfoDlg.h"
#include "ArcEditDlg.h"
#include "ShowInfoDlg.h"
#include "AddVexDlg.h"
#include "ShortPathDlg.h"


// CDragStatic

IMPLEMENT_DYNAMIC(CDragStatic, CWnd)

CDragStatic::CDragStatic()
: m_utextFomat(DT_SINGLELINE|DT_CENTER|DT_VCENTER)
//半径
, m_nRadius(15)
//圆心
, m_ptCenter(CPoint(30,30))
{
	m_crText=RGB(0,0,0);
	m_crOverBG=RGB(255,255,0);
	m_crBG=RGB(0,255,0);
}

CDragStatic::~CDragStatic()
{

}


BEGIN_MESSAGE_MAP(CDragStatic, CWnd)
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_COMMAND(ID_MENU_SHOW_VEX_INFO, &CDragStatic::OnShowVexInfo)
	ON_COMMAND(ID_MENU_ADD_VEX, &CDragStatic::OnMenuAddVex)
	ON_COMMAND(ID_MENU_DEL_ARC, &CDragStatic::OnMenuDelArc)
	ON_COMMAND(ID_MENU_DEL_VEX, &CDragStatic::OnMenuDelVex)
	ON_COMMAND(ID_MENU_ADD_ARC, &CDragStatic::OnMenuAddArc)
	ON_COMMAND(ID_MENU_SHOW_ARC_INFO, &CDragStatic::OnMenuShowArcInfo)
	ON_COMMAND(ID_MENU_VISIT_ALL, &CDragStatic::OnMenuVisitAll)
	ON_COMMAND(ID_MENU_FIND_PATH, &CDragStatic::OnMenuFindPath)
	ON_COMMAND(ID_MENU_RESET_ALL_COLOR, &CDragStatic::OnMenuResetAllColor)
	ON_COMMAND(ID_MENU_CRITICAL_PATH, &CDragStatic::OnMenuCriticalPath)
	ON_COMMAND(ID_MENU_CHECK_ANNULUS, &CDragStatic::OnMenuCheckAnnulus)
	ON_COMMAND(ID_MENU_SHORT_PATH, &CDragStatic::OnMenuShortPath)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_NCRBUTTONUP()
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()



// CDragStatic 消息处理程序

BOOL  CDragStatic::Create(
				CString title,
				CWnd* pParentWnd,
				CPoint pt,
				int radius)
{
	m_ptCenter = pt;
	m_nRadius = radius;
	CRect rect(pt.x-m_nRadius, pt.y-m_nRadius,pt.x+m_nRadius , pt.y+m_nRadius);
	CWnd::Create(NULL,title,WS_CHILD |WS_VISIBLE |SS_NOTIFY ,rect,pParentWnd,10000);

	CRect rc(0,0,m_nRadius<<1,m_nRadius<<1);
	//   Set   the   window   region   so   mouse   clicks   only   activate   the   round   section   
	//   of   the   button 
	m_rgn.DeleteObject();   
	SetWindowRgn(NULL,   FALSE);
	m_rgn.CreateEllipticRgnIndirect(rc); 
	SetWindowRgn(m_rgn,   TRUE);
	return TRUE;
}

void CDragStatic::OnMenuShowArcInfo()
{
	pView->OnShowArcInfo();

}

void CDragStatic::OnMenuCheckAnnulus()
{
	pView->OnMenuCheckAnnulus();
};

/*
void CDragStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	BringWindowToTop();
	RedrawWindow();

	//SetCapture();
	m_bLBdown=true;

	m_Point=point;
	GetWindowRect(&m_Rect);
	GetOwner()->ScreenToClient(&m_Rect); 
	CRect rc;
	GetOwner()->GetWindowRect(&rc);
	rc.left+=20;
	rc.top+=20;
	rc.bottom-=20;
	rc.right-=20;
	
	ClipCursor(&rc);   


	m_Point=point;
	ClientToScreen(&m_Point);
	GetOwner()->ScreenToClient(&m_Point);

	CWnd::OnLButtonDown(nFlags, point);

}

void CDragStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pt=point;
	ClientToScreen(&pt);
	GetOwner()->ScreenToClient(&pt);
	
	if (m_bLBdown)
	{
		CPoint btnOldPointer; 
		btnOldPointer=m_Point; 
		m_Point=pt;  
		CRect rect; 
		GetWindowRect(&rect); 
		//TRACE("%d-%d**\n",rect.left,rect.top);
		GetOwner()->ScreenToClient(&rect); 
		//TRACE("%d-%d**\n",rect.left,rect.top);
		rect.left+=pt.x-btnOldPointer.x; 
		rect.right+=pt.x-btnOldPointer.x; 
		rect.top+=pt.y-btnOldPointer.y; 
		rect.bottom+=pt.y-btnOldPointer.y; 
	
		MoveWindow(rect.left,rect.top,rect.Width(),rect.Height()); 

	}
	
	if (m_bOver)        // Cursor is currently over control
	{
		CRect rect;
		GetClientRect(rect);

		if (!rect.PtInRect(point))
		{
			m_bOver = FALSE;
			RedrawWindow();
			ReleaseCapture();
			return;
		}
	}
	else                      // Cursor has just moved over control
	{
		m_bOver = TRUE;
		//RedrawWindow();
		SetCapture();
	}
	
	CWnd::OnMouseMove(nFlags, point);
	GetOwner()->Invalidate(FALSE);
}

void CDragStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLBdown=false;
	//ReleaseCapture();
	 ClipCursor(NULL);   
	Invalidate(FALSE);
	CWnd::OnLButtonUp(nFlags, point);
}
*/

void CDragStatic::SetTextColor(COLORREF crText)
{
	this->m_crText = crText;
	RedrawWindow();
}

void CDragStatic::SetBGColer(COLORREF crBG)
{
	this->m_crBG=crBG;
	RedrawWindow();
}

void CDragStatic::OnMenuShortPath()
{
	if(!pShortPathDlg)
	{
		pShortPathDlg = new CShortPathDlg();
		pShortPathDlg->Create(IDD_DIALOG_SHORT_PATH,this);

	}
	CString strText;
	this->GetWindowText(strText);
	pShortPathDlg->key = strText;	
	pShortPathDlg->ShowWindow(SW_SHOW);
};

void CDragStatic::SetMuliLineMode(bool bMuliLine)
{
	if(bMuliLine)
	{
		m_utextFomat&=~DT_SINGLELINE;
		m_utextFomat|=DT_WORDBREAK;
	}
	else
	{
		m_utextFomat|=DT_SINGLELINE;
		m_utextFomat&=~DT_WORDBREAK;
	}
	RedrawWindow();
}

void CDragStatic::SetOverBGColor(COLORREF crOverBG)
{
	this->m_crOverBG= crOverBG;
}
/*
void CDragStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//准备工作
	CDC* dc=CDC::FromHandle(lpDrawItemStruct->hDC); 
	dc.SetTextColor(m_crText);
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(this->GetFont());
	CRect rect;
	this->GetClientRect(&rect);
	
	//画背景
	CBrush br;
	CPen pn;

	if(m_bOver)
	{
		br.CreateSolidBrush(m_crOverBG);
		pn.CreatePen(PS_SOLID, 8, m_crBG);
	}
	else
	{
		br.CreateSolidBrush(m_crBG);
		pn.CreatePen(PS_SOLID, 6, m_crOverBG);
	}

	dc.SelectObject(br);
	dc.SelectObject(pn);

	// shrink our rect 20 pixels in each direction
	//rect.DeflateRect(6, 6);

	// draw a thick black rectangle filled with blue
	dc.Rectangle(rect);

	
	///输出文字
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CString strText;
	this->GetWindowText(strText);
	if(strText.GetLength()>0)
		dc.DrawText(strText,rect,m_utextFomat);
}
*/

void CDragStatic::OnMove(int x, int y)
{
	CWnd::OnMove(x, y);
	m_ptCenter.x = x + m_nRadius;
	m_ptCenter.y = y + m_nRadius;
	pView->AutoCalcAreaSize();
	if( pView )
	{
		pView->GetDocument()->SetModifiedFlag();
		pView->Invalidate();
	}
}

CPoint CDragStatic::GetPoint(void)
{
	return m_ptCenter;
}

BOOL CDragStatic::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CDragStatic::OnDestroy()
{
	CWnd::OnDestroy();
	
	// TODO: 在此处添加消息处理程序代码
}

void CDragStatic::OnShowVexInfo()
{
	CString str;
	GetWindowText(str);
	int pos = OrthGrap.LocateVex(str);
	CVexInfoDlg dlg;
	dlg.strKey = str;
	dlg.DoModal();
}

void CDragStatic::OnMenuAddVex()
{
	pView->AddVex();
}

void CDragStatic::OnMenuDelArc()
{
	
	CString str;
	GetWindowText(str);
	CArcEditDlg dlg;
	dlg.strFirKey = str;
	dlg.strSecKey = str;
	dlg.SetKind( KIND_DEL );
	if(dlg.DoModal()==IDOK)
	{
		int s = OrthGrap.DelArc(OrthGrap.LocateVex(dlg.strFirKey),OrthGrap.LocateVex(dlg.strSecKey));	
		int s2 = SUCCESS;
		if(dlg.bDouble)
		{
			s2=	OrthGrap.DelArc(OrthGrap.LocateVex(dlg.strSecKey),OrthGrap.LocateVex(dlg.strFirKey));
			pView->ShowMessageBox( s2 );
		}
		if (s2 != SUCCESS )//只显示一个提示框
			pView->ShowMessageBox( s );

		pView->Invalidate();
		pView->UpdateMessage();
	}
}

void CDragStatic::OnMenuDelVex()
{
	CString strkey;
	CVexInfoDlg dlg;
	CString str;
	GetWindowText(str);
	dlg.kindFlag=KIND_DEL;
	dlg.strKey = str;
	if(dlg.DoModal()==IDOK)
	{
		strkey= dlg.strKey;
		OrthGrap.DelVex(strkey);
		UpdateMyView( SUCCESS );
	}
}

void CDragStatic::OnMenuAddArc()
{
	CString str;
	GetWindowText(str);

	CString strkey1;
	CString strkey2;

	int iWeight;
	CArcEditDlg dlg;
	dlg.strFirKey = str ;
	dlg.strSecKey = str ;
	if(dlg.DoModal()==IDOK)
	{
		strkey1= dlg.strFirKey;
		strkey2= dlg.strSecKey;
		iWeight = dlg.uWeight;

		int s = OrthGrap.AddArc(OrthGrap.LocateVex(strkey1),OrthGrap.LocateVex(strkey2), iWeight);
		int s2 = SUCCESS;
		if(dlg.bDouble)
		{
			s2=	OrthGrap.AddArc(OrthGrap.LocateVex(strkey2),OrthGrap.LocateVex(strkey1), iWeight);
			pView->ShowMessageBox( s2 );
		}
		if (s2 != SUCCESS )//只显示一个提示框
			pView->ShowMessageBox( s );
				
		pView->Invalidate();
		pView->UpdateMessage();
	}
}
void CDragStatic::UpdateMyView(int msgFalg)
{
	pView->ShowMessageBox( msgFalg );
	pView->Invalidate();
	pView->UpdateMessage();
}

void CDragStatic::OnMenuVisitAll()
{
	CString str;
	GetWindowText(str);
	CShowInfoDlg dlg;
	dlg.strKey = str;
	dlg.DoModal();	
}

void CDragStatic::OnMenuFindPath()
{
	CString str;
	GetWindowText(str);
	CArcEditDlg dlg;
	dlg.SetKind( KIND_FIND );
	dlg.strFirKey = str;
	dlg.strSecKey = str;
	if(dlg.DoModal()!=IDOK)
		return;
	if(dlg.bDouble)
		OrthGrap.ResetAllArcColor();

	if( !OrthGrap.FindPath( dlg.strFirKey , dlg.strSecKey ))
	{
		MessageBox("没有路径！" ,"查找结果" , MB_OK | MB_ICONEXCLAMATION);
	}
}

void CDragStatic::OnMenuResetAllColor()
{
	pView->OnMenuResetAllColor();
}


void CDragStatic::OnMenuCriticalPath()
{
	pView->OnMenuCriticalPath();
}


void CDragStatic::SetStyle(int style)
{
	switch ( style )
	{
	case VEX_NORMAL:
		m_crText=RGB(0,0,0);
		m_crOverBG=RGB(255,255,0);
		m_crBG=RGB(0,255,0);
		break;
	case VEX_HEAD:
		m_crText=RGB(0,0,0);
		m_crOverBG=RGB(255,255,0);
		m_crBG=RGB(255,0,0);
		break;
	case VEX_TAIL:
		m_crText=RGB(0,0,0);
		m_crOverBG=RGB(255,255,0);
		m_crBG=RGB(0,0,255);
		break;
	case VEX_CIRCLE_POINT:
		m_crText=RGB(0,0,0);
		m_crOverBG=RGB(234,117,55);
		m_crBG=RGB(125,25,55);
		break;
	}
	Invalidate(false);
}


LRESULT CDragStatic::OnNcHitTest(CPoint point)
{
	BringWindowToTop();
	CPoint pt(point);
	ScreenToClient(&pt);
	int tmp = m_nRadius *6/4;
	if(pt.x < tmp || pt.y <tmp)
	{
		return  HTCAPTION;
	}
	else
	{
		return HTBOTTOMRIGHT;
	}
	/*CRect rc ;
	GetClientRect(rc);
	rc.DeflateRect(2,2,2,2);
	TRACE("%d,%d,%d\n",rc.top,rc.bottom,pt.y);
	if( rc.PtInRect(pt) )
	{
		return  HTCAPTION;
	}
	else
	{
		return CWnd::OnNcHitTest(point);
	}*/
}

void CDragStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting


	dc.SetTextColor(m_crText);
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(this->GetFont());
	CRect rect;
	this->GetClientRect(&rect);
	
	//画背景
	CBrush br;
	CPen pn;

	/*if(m_bOver)
	{
		br.CreateSolidBrush(m_crOverBG);
		pn.CreatePen(PS_SOLID, 8, m_crBG);
	}
	else*/
	{
		br.CreateSolidBrush(m_crBG);
		pn.CreatePen(PS_SOLID, 6, m_crOverBG);
	}

	dc.SelectObject(br);
	dc.SelectObject(pn);

	// shrink our rect 20 pixels in each direction
	//rect.DeflateRect(6, 6);

	// draw a thick black rectangle filled with blue
	dc.Rectangle(rect);

	
	///输出文字
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CString strText;
	this->GetWindowText(strText);
	if(strText.GetLength()>0)
		dc.DrawText(strText,rect,m_utextFomat);
}


void CDragStatic::OnNcRButtonUp(UINT nHitTest, CPoint point)
{


	if( pView->iViewMode == GRAP_VIEW )
	{
		CPoint pt=point;
		//非客户区坐标就是屏幕坐标
		//ClientToScreen(&pt); 
		CMenu pSubMenu;
		pSubMenu.LoadMenu(IDR_MENU_POPUP);
		pSubMenu.GetSubMenu(0)->TrackPopupMenu(0 ,pt.x,pt.y,this);//弹出菜单
	}
	CWnd::OnNcRButtonUp(nHitTest, point);
}





void CDragStatic::OnSize(UINT nType, int cx, int cy)
{
	int diameter = cx > cy ? cx :cy;
	diameter = diameter%2 ? diameter+1 :diameter;
	CWnd::OnSize(nType, diameter, diameter);


	m_nRadius = diameter/2;
	m_ptCenter = CPoint( m_nRadius, m_nRadius);


	ClientToScreen(&m_ptCenter);
	GetOwner()->ScreenToClient(&m_ptCenter);
	CRect rc(0,0,diameter,diameter);
	m_rgn.DeleteObject();   
	SetWindowRgn(NULL,   FALSE);
	m_rgn.CreateEllipticRgnIndirect(rc); 
	SetWindowRgn(m_rgn,   TRUE);
}


void CDragStatic::OnSizing(UINT fwSide, LPRECT pRect)
{/*
	CRect rc(pRect);
	int w = rc.Width();
	int h = rc.Height();
	if( w > h)
	{
		rc.bottom = rc.top + w;
	}
	else
	{
		rc.right = rc.left + h;
	}
	TRACE("qqqq%d,%d\n",rc.Width(),rc.Height());
	*/
	CWnd::OnSizing(fwSide, pRect);
	//TRACE("ddddd%d,%d\n",rc.Width(),rc.Height());
	// TODO: 在此处添加消息处理程序代码
}


// 获取半径
int CDragStatic::GetRadius(void)
{
	return m_nRadius;
}
