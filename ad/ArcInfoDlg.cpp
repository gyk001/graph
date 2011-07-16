// ArcInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ad.h"
#include "ArcInfoDlg.h"


// CArcInfoDlg 对话框

IMPLEMENT_DYNAMIC(CArcInfoDlg, CDialog)

CArcInfoDlg::CArcInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArcInfoDlg::IDD, pParent)
{

}

CArcInfoDlg::~CArcInfoDlg()
{
}

void CArcInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ARC, ctrlArcList);
}


BEGIN_MESSAGE_MAP(CArcInfoDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CArcInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CArcInfoDlg 消息处理程序

BOOL CArcInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LONG styles=GetWindowLong(ctrlArcList.m_hWnd,GWL_STYLE);
	SetWindowLong(ctrlArcList.m_hWnd,GWL_STYLE,styles | LVS_REPORT );
	ctrlArcList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE);
	ctrlArcList.InsertColumn(0,_T("头节点"),LVCFMT_LEFT,60);
	ctrlArcList.InsertColumn(1,_T("尾节点"),LVCFMT_LEFT,60);
	ctrlArcList.InsertColumn(2,_T("权 重"),LVCFMT_LEFT,80);
	
	OrthListArcBox *p=NULL;
	for (int index=0 ,i=0; index<MAX_VERTEX_NUM; index++)
	{
		if(OrthGrap.xlist[index].m_bUsed)
		{
			
			p = OrthGrap.xlist[index].m_pThisTail;//只画入弧

			while (p)
			{
				ctrlArcList.InsertItem( i ,OrthGrap.xlist[p->headVex].data.key);
				ctrlArcList.SetItemText( i ,1,OrthGrap.xlist[p->tailVex].data.key);
				CString str;
				str.Format("%d",p->data.quan);
				ctrlArcList.SetItemText( i ,2,str);
				p=p->m_pNextSameTail;
				i++;
			}

		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CArcInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
