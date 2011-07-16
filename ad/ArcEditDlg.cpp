// ArcEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "ad.h"
#include "ArcEditDlg.h"


// CArcEdit 对话框

IMPLEMENT_DYNAMIC(CArcEditDlg, CDialog)

CArcEditDlg::CArcEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArcEditDlg::IDD, pParent)
	, strFirKey(_T(""))
	, strSecKey(_T(""))
	, uWeight(1)
	, bDouble(FALSE)
{

}

CArcEditDlg::~CArcEditDlg()
{
}

void CArcEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_1_KEY, strFirKey);
	DDX_Text(pDX, IDC_2_KEY, strSecKey);
	DDX_Text(pDX, IDC_WEIGHT, uWeight);
	DDX_Check(pDX, IDC_CHECK_DOUBLE, bDouble);
}


BEGIN_MESSAGE_MAP(CArcEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CArcEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CArcEdit 消息处理程序

void CArcEditDlg::OnBnClickedOk()
{
	UpdateData();

	if( uWeight< 1 || uWeight>=MAX_INT )
	{
		CString str;
		str.Format("权重必须介于1和%d之间 ！",MAX_INT)	;
		MessageBox(str,"提示",MB_OK|MB_ICONWARNING);
		return;
	}
	strFirKey.Replace(" ","");
	strSecKey.Replace(" ","");
	strFirKey.MakeUpper();
	strSecKey.MakeUpper();
	if (strFirKey != strSecKey )
		if (strFirKey!="" && strSecKey!="")
			OnOK();
}

void CArcEditDlg::SetKind( int kind )
{
	kindFlag = kind;
}

BOOL CArcEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch ( kindFlag )
	{
	case KIND_ADD:
		break;	
	
	case KIND_DEL:
		SetWindowText("删除弧");
		GetDlgItem(IDC_CHECK_DOUBLE)->SetWindowText(" 删除双向弧");
		GetDlgItem(IDC_WEIGHT)->ShowWindow( SW_HIDE );	
		GetDlgItem(IDC_STATIC_WEIGHT)->ShowWindow( SW_HIDE );	
		break;
	case KIND_FIND:
		SetWindowText("查找路径");
		GetDlgItem(IDC_CHECK_DOUBLE)->SetWindowText(" 重置弧颜色");
		GetDlgItem(IDC_WEIGHT)->ShowWindow( SW_HIDE );
		GetDlgItem(IDC_STATIC_WEIGHT)->ShowWindow( SW_HIDE );
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
