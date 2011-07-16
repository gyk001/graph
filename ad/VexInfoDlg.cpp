// VexInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ad.h"
#include "VexInfoDlg.h"


// CVexInfoDlg 对话框

IMPLEMENT_DYNAMIC(CVexInfoDlg, CDialog)

CVexInfoDlg::CVexInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVexInfoDlg::IDD, pParent)
	, strKey(_T(""))
	, iInDegree(0)
	, iOutDegree(0)
	, strMoreInfo(_T(""))
{
}


CVexInfoDlg::~CVexInfoDlg()
{
}

void CVexInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IN, iInDegree);
	DDX_Text(pDX, IDC_OUT, iOutDegree);
	DDX_Text(pDX, IDC_MORE_INFO, strMoreInfo);
	DDX_Control(pDX, IDC_COMBO_KEY_LIST, ctrlKeyList);
}


BEGIN_MESSAGE_MAP(CVexInfoDlg, CDialog)

	ON_CBN_SELCHANGE(IDC_COMBO_KEY_LIST, &CVexInfoDlg::OnCbnSelchangeComboKeyList)
END_MESSAGE_MAP()



BOOL CVexInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	switch ( kindFlag)
	{
	case KIND_ADD:
		break;
	case KIND_DEL:
		SetWindowText("删除节点");
		break;
	}

	for (int i=0 ;i<MAX_VERTEX_NUM;i++)
	{
		if (OrthGrap.xlist[i].m_bUsed)
		{
			ctrlKeyList.AddString(OrthGrap.xlist[i].data.key);
		}
	}
	
	if (strKey!="")
	{
		UpdateInfo(strKey);
		int  index = ctrlKeyList.FindString( -1 ,strKey);
		if(index!=-1)
			ctrlKeyList.SetCurSel(index);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CVexInfoDlg::OnCbnSelchangeComboKeyList()
{
	int   nSel   =   ctrlKeyList.GetCurSel();   
	if(nSel   ==   CB_ERR)   
		return;   
	ctrlKeyList.GetLBText(nSel,strKey);   
	UpdateInfo(strKey);
}

void CVexInfoDlg::UpdateInfo(CString key)
{
	int pos = OrthGrap.LocateVex(key);
	if(pos!=-1)
	{
		iInDegree = OrthGrap.xlist[pos].data.inDegree;
		iOutDegree = OrthGrap.xlist[pos].data.outDegree;
		strMoreInfo = OrthGrap.xlist[pos].data.moreInfo;
		UpdateData(FALSE);
	}
}
