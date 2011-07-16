// ShortPathDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ad.h"
#include "ShortPathDlg.h"


// CShortPathDlg 对话框

IMPLEMENT_DYNAMIC(CShortPathDlg, CDialog)

CShortPathDlg::CShortPathDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShortPathDlg::IDD, pParent)
	,key ("")
{

}

CShortPathDlg::~CShortPathDlg()
{
}

void CShortPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHORT_PATH, ctrlShortPathList);
	DDX_Control(pDX, IDC_COMBO_KEY, ctrlBeginKeyCombo);
}


BEGIN_MESSAGE_MAP(CShortPathDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_KEY, &CShortPathDlg::OnCbnSelchangeComboKey)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SHORT_PATH, &CShortPathDlg::OnNMDblclkListShortPath)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_MINI_SIZE, &CShortPathDlg::OnBnClickedButtonMiniSize)
END_MESSAGE_MAP()


// CShortPathDlg 消息处理程序

BOOL CShortPathDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LONG styles=GetWindowLong(ctrlShortPathList.m_hWnd,GWL_STYLE);
	SetWindowLong(ctrlShortPathList.m_hWnd,GWL_STYLE,styles | LVS_REPORT );
	ctrlShortPathList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE);
	ctrlShortPathList.InsertColumn(0,_T("终点"),LVCFMT_LEFT,50);
	ctrlShortPathList.InsertColumn(1,_T("路权和"),LVCFMT_LEFT,60);
	ctrlShortPathList.InsertColumn(2,_T("路径"),LVCFMT_LEFT,240);
	InitCtrl();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShortPathDlg::UpdateInfo(CString key)
{
	CStringArray path;
	CStringArray EndKey;
	CStringArray pathLength;
	AdjMatrixGrap.ShortPath_DJJ( key ,EndKey,path,pathLength);
	ctrlShortPathList.DeleteAllItems();
	for ( int i=0; i<path.GetSize(); i++)
	{
		ctrlShortPathList.InsertItem( i , EndKey.GetAt(i));
		ctrlShortPathList.SetItemText( i ,2,path.GetAt(i));	
		ctrlShortPathList.SetItemText( i ,1,pathLength.GetAt(i));			
	}
}

void CShortPathDlg::OnCbnSelchangeComboKey()
{
	int  index = ctrlBeginKeyCombo.GetCurSel();
	if(index!=-1)
	{
		ctrlBeginKeyCombo.GetLBText( index, key );
		UpdateInfo( key );
	}
}

void CShortPathDlg::OnNMDblclkListShortPath(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast <LPNMLISTVIEW>(pNMHDR); 
	
	if( pNMLV->iItem !=-1 )   
	{
		CString b = ctrlShortPathList.GetItemText( pNMLV->iItem,0);
		CString path = ctrlShortPathList.GetItemText( pNMLV->iItem,2);
		OrthGrap.DrawPath( key , b,  path );
	}
	*pResult = 0;
}



void CShortPathDlg::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	pShortPathDlg = NULL;
	delete this;
}


void CShortPathDlg::InitCtrl(void)
{
	ctrlBeginKeyCombo.ResetContent();
	for (int i=0 ;i<MAX_VERTEX_NUM;i++)
	{
		if (OrthGrap.xlist[i].m_bUsed)
		{
			ctrlBeginKeyCombo.AddString(OrthGrap.xlist[i].data.key);
		}
	}
	if (key !="")
	{
		int  index = ctrlBeginKeyCombo.FindString( -1 ,key);
		if(index!=-1)
		{
			ctrlBeginKeyCombo.SetCurSel(index);
			UpdateInfo( key  );
		}
	}
	Invalidate(FALSE);
}

void CShortPathDlg::OnClose()
{
	this->ShowWindow(SW_HIDE);
}

void CShortPathDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if( bShow == TRUE )
	{
		if (key !="")
		{
			int  index = ctrlBeginKeyCombo.FindString( -1 ,key);
			if(index!=-1)
			{
				ctrlBeginKeyCombo.SetCurSel(index);
				UpdateInfo( key  );
			}
		}
	}

	CDialog::OnShowWindow(bShow, nStatus);
}

void CShortPathDlg::OnBnClickedButtonMiniSize()
{
	ShowWindow(SW_SHOWMINIMIZED) ;

}
